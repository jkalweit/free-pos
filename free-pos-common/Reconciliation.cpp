#include "Reconciliation.h"

#include <QPainter>
#include <QPrinter>
#include <QFont>
#include <QDir>
#include <QFile>
#include <QMetaProperty>
#include <QDebug>
#include "Pos.h"

Reconciliation::Reconciliation(QObject *parent, quint32 id, QDate date, QString name, QString note,
                               QDateTime openedStamp, QDateTime closedStamp,
                               CashDrawer *begginningDrawer, CashDrawer *endingDrawer,
                               float creditCardTotalActual, float creditCardTotalTips) :
    SimpleSerializable(parent), m_id(id), m_date(date), m_name(name), m_note(note),
    m_openedStamp(openedStamp), m_closedStamp(closedStamp),
    m_beginningDrawer(begginningDrawer), m_endingDrawer(endingDrawer),
    m_currentTicketId(0), m_selectedTicket(nullptr),
    m_creditCardTotalActual(creditCardTotalActual), m_creditCardTotalTips(creditCardTotalTips),
    m_isHistoryDisabled(false), m_shiftCurrId(0)
{
    if(m_beginningDrawer == nullptr)
        m_beginningDrawer = new CashDrawer(this, 1);
    if(m_endingDrawer == nullptr)
        m_endingDrawer = new CashDrawer(this, 2);


    connect(m_beginningDrawer, SIGNAL(totalChanged(float)),
            this, SLOT(fireActualTakeTotalsChanged()));
    connect(m_endingDrawer, SIGNAL(totalChanged(float)),
            this, SLOT(fireActualTakeTotalsChanged()));

    readHistory();
}

QStringList Reconciliation::updatePrefix() {
    return QStringList() << "UpdateReconciliation" << QString::number(m_id);
}

QString Reconciliation::filename() {
    QString year = QString::number(m_date.year());
    QString month = QString::number(m_date.month());
    QString day = QString::number(m_date.day());

    if(month.length() == 1) month = "0" + month;
    if(day.length() == 1) day = "0" + day;

    return year + "-" + month + "-" + day + "_" + m_name + ".txt";
}

void Reconciliation::readHistory() {

    m_isHistoryDisabled = true;

    QFile file("./data/" + filename());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        int delimit = line.indexOf(":");
        QString timestamp = line.mid(0, delimit);
        Q_UNUSED(timestamp);
        QString theRest = line.mid(delimit+1, line.length() - delimit);
        delimit = theRest.indexOf(":");
        QString command = theRest.mid(0, delimit);
        QString payload = theRest.mid(delimit+1, line.length() - delimit);
        QStringList split = SimpleSerializable::deserializeList(payload);

        if(command == "OpenRec") {
//            qDebug() << "Open new rec" << payload;
//            m_selectedRec = Reconciliation::deserialize(payload, this);
        } else if(command == "AddTicket") {
            //qDebug() << "AddTicket: " << payload;
            addTicket(Ticket::deserialize(payload, this));
        } else if(command == "AddCustomer") {
            //qDebug() << "AddCustomer: " << payload;

            Customer *c = Customer::deserialize(payload, this);
            Ticket *ticket = getTicket(c->property("ticketId").toInt());
            if(ticket)
                ticket->addCustomer(c);
            else
                qDebug() << "Ticket does not exist.";
        } else if(command == "AddOrderItem") {
            //qDebug() << "AddOrderItem: " << payload;
            OrderItem *i = OrderItem::deserialize(payload);
            Ticket *ticket = getTicket(i->property("ticketId").toInt());
            if(!ticket) {
                qDebug() << "Ticket does not exist.";
                return;
            }
            Customer *customer = ticket->getCustomer(i->property("customerId").toUInt());
            if(!customer) {
                qDebug() << "Customer does not exist.";
                return;
            }
            customer->addOrderItem(i);
        } else if (command == "UpdateReconciliation") {
            //qDebug() << "UpdateReconciliation: " << payload;
            //quint32 recId = split[0].toUInt();
            QString property = split[1];
            QString value = split[2];
            setProperty(property.toUtf8().data(), value);
        } else if (command == "UpdateCashDrawer") {
            //qDebug() << "UpdateCashDrawer: " << payload;
            //quint32 recId = split[0].toUInt();
            quint32 cashDrawerId = split[0].toUInt();
            QString property = split[1];
            QString value = split[2];
            if(cashDrawerId == 1) {
                beginningDrawer()->setProperty(property.toUtf8().data(), value);
            } else if(cashDrawerId == 2) {
                endingDrawer()->setProperty(property.toUtf8().data(), value);
            }
        } else if (command == "UpdateTicket") {
            //qDebug() << "UpdateTicket: " << payload;
            quint32 ticketId = split[0].toUInt();
            QString property = split[1];
            QString value = split[2];
            Ticket* ticket = getTicket(ticketId);
            ticket->setProperty(property.toUtf8().data(), value);
        } else if (command == "UpdateCustomer") {
            //qDebug() << "UpdateCustomer: " << payload;
            quint32 ticketId = split[0].toUInt();
            quint32 customerId = split[1].toUInt();
            QString property = split[2];
            QString value = split[3];
            Customer* customer = getTicket(ticketId)->getCustomer(customerId);
            customer->setProperty(property.toUtf8().data(), value);
        } else if (command == "UpdateOrderItem") {
            //qDebug() << "UpdateOrderItem: " << payload;
            quint32 ticketId = split[0].toUInt();
            quint32 customerId = split[1].toUInt();
            quint32 orderItemId = split[2].toUInt();
            QString property = split[3];
            QString value = split[4];
            OrderItem* orderItem = getTicket(ticketId)->getCustomer(customerId)->getOrderItem(orderItemId);
            if(property == "submittedStamp" && value.trimmed() == "") {
                orderItem->setProperty("submittedStamp", QDateTime());
            } else {
                orderItem->setProperty(property.toUtf8().data(), value);
            }
        } else if (command == "MoveOrderItem") {
            qDebug() << "MoveOrderItem: " << payload;
            quint32 fromTicketId = split[0].toUInt();
            quint32 fromCustomerId = split[1].toUInt();
            quint32 orderItemId = split[2].toUInt();
            quint32 toTicketId = split[3].toUInt();
            quint32 toCustomerId = split[4].toUInt();

            OrderItem* orderItem = getTicket(fromTicketId)->getCustomer(fromCustomerId)->getOrderItem(orderItemId);
            moveOrderItem(orderItem, toTicketId, toCustomerId);
        } else if (command == "AddOrderItemInventoryItem") {
            //qDebug() << "AddOrderItemInventoryItem: " << payload;
            OrderItemInventoryItem *orderItemInventoryItem = OrderItemInventoryItem::deserialize(payload);
            Ticket *ticket = getTicket(orderItemInventoryItem->ticketId());
            Customer *customer = ticket->getCustomer(orderItemInventoryItem->customerId());
            OrderItem *orderItem = customer->getOrderItem(orderItemInventoryItem->orderItemId());
            orderItem->addOrderItemInventoryItem(orderItemInventoryItem);
        } else if (command == "UpdateOrderItemInventoryItem") {
            //qDebug() << "UpdateOrderItemInventoryItem: " << payload;
            quint32 ticketId = split[0].toUInt();
            quint32 customerId = split[1].toUInt();
            quint32 orderItemId = split[2].toUInt();
            quint32 id = split[3].toUInt();
            QString property = split[4];
            QString value = split[5];

            Ticket *ticket = getTicket(ticketId);
            Customer *customer = ticket->getCustomer(customerId);
            OrderItem *orderItem = customer->getOrderItem(orderItemId);
            OrderItemInventoryItem *item = orderItem->getOrderItemInventoryItem(id);
            item->setProperty(property.toUtf8().data(), value);
        } else if (command == "RemoveOrderItemInventoryItem") {
            //qDebug() << "RemoveOrderItemInventoryItem: " << payload;
            quint32 ticketId = split[0].toUInt();
            quint32 customerId = split[1].toUInt();
            quint32 orderItemId = split[2].toUInt();
            quint32 id = split[3].toUInt();

            Ticket *ticket = getTicket(ticketId);
            Customer *customer = ticket->getCustomer(customerId);
            OrderItem *orderItem = customer->getOrderItem(orderItemId);
            orderItem->removeOrderItemInventoryItem(id);
        } else if (command == "AddOrderItemOption") {
            qDebug() << "AddOrderItemOption: " << payload;
            OrderItemOption *orderItemOption = OrderItemOption::deserialize(payload);
            Ticket *ticket = getTicket(orderItemOption->ticketId());
            Customer *customer = ticket->getCustomer(orderItemOption->customerId());
            OrderItem *orderItem = customer->getOrderItem(orderItemOption->orderItemId());
            orderItem->addOrderItemOption(orderItemOption);
        } else if (command == "UpdateOrderItemOption") {
            qDebug() << "UpdateOrderItemOption: " << payload;
            quint32 ticketId = split[0].toUInt();
            quint32 customerId = split[1].toUInt();
            quint32 orderItemId = split[2].toUInt();
            quint32 id = split[3].toUInt();
            QString property = split[4];
            QString value = split[5];

            Ticket *ticket = getTicket(ticketId);
            Customer *customer = ticket->getCustomer(customerId);
            OrderItem *orderItem = customer->getOrderItem(orderItemId);
            OrderItemOption *item = orderItem->getOrderItemOption(id);
            item->setProperty(property.toUtf8().data(), value);
        } else if (command == "AddEmployeeShift") {
            qDebug() << "AddEmployeeShift: " << payload;
            EmployeeShift *shift = EmployeeShift::deserialize(payload, (QObject*) this);
            addShift(shift);
        } else if (command == "UpdateEmployeeShift") {
            qDebug() << "UpdateEmployeeShift: " << payload;
            quint32 id = split[0].toUInt();
            QString property = split[1];
            QString value = split[2];

            EmployeeShift *item = getShift(id);
            item->setProperty(property.toUtf8().data(), value);
        } else {
            qDebug() << "Unknown command: " << command << " " << payload;
        }
    }

    // optional, as QFile destructor will already do it:
    file.close();

    m_isHistoryDisabled = false;
}

void Reconciliation::appendToHistory(QString item) {
    if(!m_isHistoryDisabled) {
        QFile file("./data/" + filename());
        file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << SimpleSerializable::escapeString(QDateTime::currentDateTime().toString()) << ":" << item << endl;
        file.close();
    }
}

CashDrawer* Reconciliation::beginningDrawer() {
    return m_beginningDrawer;
}

CashDrawer* Reconciliation::endingDrawer() {
    return m_endingDrawer;
}

Ticket* Reconciliation::addTicket(QString name) {
    Ticket *ticket = new Ticket(this, ++m_currentTicketId, name, QDateTime::currentDateTime());
    addTicket(ticket);
    return ticket;
}

void Reconciliation::addTicket(Ticket *ticket) {
    if(ticket->property("id").toUInt() > m_currentTicketId) m_currentTicketId = ticket->property("id").toUInt();

    connect(ticket, SIGNAL(foodTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(ticket, SIGNAL(taxTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(ticket, SIGNAL(barTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(ticket, SIGNAL(totalChanged(float)),
            this, SLOT(fireTotalsChanged()));

    connect(ticket, SIGNAL(paymentTypeChanged(QString)),
            this, SLOT(firePaymentTotalsChanged()));

    connect(ticket, SIGNAL(costChanged(float)),
            this, SLOT(fireCogChanged()));
    connect(ticket, SIGNAL(marginChanged(float)),
            this, SLOT(fireCogChanged()));

    m_tickets.append(ticket);
    Pos::instance()->appendToHistory("AddTicket:" + ticket->serialize());
    ticketsChanged(tickets());
}

void Reconciliation::setName(QString name) {
    if(m_name != name.trimmed()) {
        m_name = name.trimmed();
        logPropertyChanged(m_name, "name");
        nameChanged(m_name);
    }
}

void Reconciliation::setNote(QString note) {
    if(m_note != note.trimmed()) {
        m_note = note.trimmed();
        logPropertyChanged(m_note, "note");
        noteChanged(m_note);
    }
}

Ticket* Reconciliation::getTicket(quint32 id) {
    for(Ticket *ticket : m_tickets) {
        if(ticket->property("id").toUInt() == id)
            return ticket;
    }
    return nullptr;
}

void Reconciliation::setSelectedTicket(Ticket *ticket) {
    if(m_selectedTicket != ticket) {
        m_selectedTicket = ticket;
        selectedTicketChanged(m_selectedTicket);
    }
}

Ticket* Reconciliation::selectedTicket() {
    return m_selectedTicket;
}


Ticket* Reconciliation::getNextTicket(QString nameFilter, bool showIsPaid) {
    bool foundSelected = false;
    Ticket *firstEnabled = nullptr;
    for(int i = 0; i < m_tickets.length(); i++) {
        bool isDisabled = !m_tickets[i]->property("customerNames").toString().toUpper().contains(nameFilter.toUpper()) || (m_tickets[i]->property("isPaid").toBool() && !showIsPaid);
        if(!isDisabled) {
            if(!m_selectedTicket) {
                return m_tickets[i];
            } else if(foundSelected) {
                return m_tickets[i];
            } else if(!firstEnabled)
                firstEnabled = m_tickets[i];
        }
        if(m_selectedTicket && (m_tickets[i]->property("id").toUInt() == m_selectedTicket->property("id").toUInt())) {
            foundSelected = true;
        }
    }

    // if we make it here, then just return first !isDisabled ticket, or nullptr
    return firstEnabled;
}

Ticket* Reconciliation::getPreviousTicket(QString nameFilter, bool showIsPaid) {
    bool foundSelected = false;
    Ticket *firstEnabled = nullptr;
    for(int i = m_tickets.length() - 1; i >= 0 ; i--) {
        bool isDisabled = !m_tickets[i]->property("customerNames").toString().toUpper().contains(nameFilter.toUpper()) || (m_tickets[i]->property("isPaid").toBool() && !showIsPaid);
        if(!isDisabled) {
            if(!m_selectedTicket) {
                return m_tickets[i];
            } else if(foundSelected) {
                return m_tickets[i];
            } else if(!firstEnabled)
                firstEnabled = m_tickets[i];
        }
        if(m_selectedTicket && (m_tickets[i]->property("id").toUInt() == m_selectedTicket->property("id").toUInt())) {
            foundSelected = true;
        }
    }

    // if we make it here, then just return first !isDisabled ticket, or nullptr
    return firstEnabled;
}

void Reconciliation::moveOrderItem(OrderItem *orderItem, quint32 toTicketId, quint32 toCustomerId) {
    int fromTicketId = orderItem->property("ticketId").toInt();
    int fromCustomerId = orderItem->property("customerId").toInt();
    Ticket* fromTicket = getTicket(fromTicketId);
    Customer* fromCustomer = fromTicket->getCustomer(fromCustomerId);
    fromCustomer->removeOrderItem(orderItem);

    // Log the move before changing the id's
    Pos::instance()->appendToHistory(serializeList(QStringList() << "MoveOrderItem" << QString::number(fromTicketId)
                                                   << QString::number(fromCustomerId) << QString::number(orderItem->property("id").toUInt())
                                                   << QString::number(toTicketId) << QString::number(toCustomerId)));

    orderItem->setTicketId(toTicketId);
    orderItem->setCustomerId(toCustomerId);
    Ticket* toTicket = getTicket(toTicketId);
    Customer* toCustomer = toTicket->getCustomer(toCustomerId);
    toCustomer->addOrderItem(orderItem, true);    
}

QQmlListProperty<Ticket> Reconciliation::tickets() {
    return QQmlListProperty<Ticket>(this, m_tickets);
}

QString Reconciliation::fileName() {
    return m_openedStamp.toString("yyyy-MM-dd") + "_" + m_name + ".txt";
}

float Reconciliation::foodTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        sum += c->foodTotal();
    }
    return sum;
}

float Reconciliation::taxTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        sum += c->taxTotal();
    }
    return sum;
}

float Reconciliation::barTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        sum += c->barTotal();
    }
    return sum;
}

float Reconciliation::total() {
    return foodTotal() + taxTotal() + barTotal();
}



float Reconciliation::cog() {
    float cost = 0;
    for(Ticket *item : m_tickets) {
        cost += item->cost();
    }
    return cost;
}

float Reconciliation::laborHours() {
    float hours = 0;
    for(EmployeeShift *item : m_shifts) {
        hours += item->scheduledOrActualHours();
    }
    return hours;
}

float Reconciliation::laborCost() {
    float cost = 0;

    for(EmployeeShift *item : m_shifts) {
        cost += item->cost();
    }

    return cost;
}



float Reconciliation::cost() {
    return cog() + laborCost();
}

float Reconciliation::margin() {
    return foodTotal() + barTotal() - cost();
}



void Reconciliation::fireCogChanged() {
    cogChanged(cog());
    costChanged(cost());
    marginChanged(margin());
}

void Reconciliation::fireLaborCostChanged() {
    laborHoursChanged(laborHours());
    laborCostChanged(laborCost());
    costChanged(cost());
    marginChanged(margin());
}

void Reconciliation::fireTotalsChanged() {
    foodTotalChanged(foodTotal());
    taxTotalChanged(taxTotal());
    barTotalChanged(barTotal());
    totalChanged(total());
}


void Reconciliation::fireActualTakeTotalsChanged() {
    cashTotalActualChanged(cashTotalActual());    
    creditCardTotalActualChanged(m_creditCardTotalActual);
    creditCardTotalTipsChanged(m_creditCardTotalTips);
    takeTotalActualChanged(takeTotalActual());
    discrepancyActualChanged(discrepancyActual());
}

float Reconciliation::creditCardTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        if(c->property("paymentType").toString() == "Credit Card")
            sum += c->total();
    }
    return sum;
}

void Reconciliation::setCreditCardTotalActual(float val) {
    m_creditCardTotalActual = val;
    logPropertyChanged(m_creditCardTotalActual, "creditCardTotalActual");
    creditCardTotalActualChanged(m_creditCardTotalActual);
    fireActualTakeTotalsChanged();
}

void Reconciliation::setCreditCardTotalTips(float val) {
    m_creditCardTotalTips = val;
    logPropertyChanged(m_creditCardTotalTips, "creditCardTotalTips");
    creditCardTotalTipsChanged(m_creditCardTotalTips);
    fireActualTakeTotalsChanged();
}

float Reconciliation::cashTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        if(c->property("paymentType").toString() == "Cash")
            sum += c->total();
    }
    return sum;
}

float Reconciliation::cashTotalActual() {
    return m_endingDrawer->total() - m_beginningDrawer->total();
}

float Reconciliation::takeTotal() {
    float sum = 0;
    for(Ticket *c : m_tickets) {\
        sum += c->total();
    }
    return sum;
}

float Reconciliation::takeTotalActual() {
    return cashTotalActual() + m_creditCardTotalActual + m_creditCardTotalTips;
}

float Reconciliation::discrepancy() {
    return takeTotal() - total();
}

float Reconciliation::discrepancyActual() {
    return takeTotalActual() - total();
}

void Reconciliation::firePaymentTotalsChanged() {
    creditCardTotalChanged(creditCardTotal());
    cashTotalChanged(cashTotal());
    takeTotalChanged(takeTotal());
    discrepancyChanged(discrepancy());
}

bool Reconciliation::hasOpenTickets() {
    for(Ticket *t : m_tickets) {
        if(!t->isPaid()) {
            return true;
        }
    }
    return false;
}

bool Reconciliation::closeRec() {
    if(!isOpen()) {
        qDebug() << "Rec is already closed.";
        return false;
    }

    if(hasOpenTickets()) {
        qDebug() << "Rec has open customers.";
        return false;
    }

    m_closedStamp = QDateTime::currentDateTime();    
    logPropertyChanged(m_closedStamp, "closedStamp");    
    qDebug() << "Closed rec: " << m_closedStamp.toString("MM/dd/yyyy hh:mmAP");

    closedStampChanged(m_closedStamp);
    isOpenChanged(isOpen());

    return !isOpen();
}

bool Reconciliation::isOpen() {
    return m_closedStamp.isNull();
}



QString Reconciliation::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << m_date.toString() << m_name << m_note;
    return serializeList(vals);
}

Reconciliation* Reconciliation::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 id = split[0].toInt();
    QDate date = QDate::fromString(split[1]);
    QString name = split[2];
    QString note = split[3];

    Reconciliation *obj = new Reconciliation(parent, id, date, name, note);
    return obj;
}



void Reconciliation::print() {

    QPrinter printer;


    printer.setFullPage(true);
//    printer.setOutputFormat(printer.PdfFormat);
//    printer.setOutputFileName("reconciliation.pdf");

    qreal currentX = 20;
    qreal currentY = 0;
    qreal lineSpacing = 3;
    qreal width = 232;

    printer.setPaperSize(QSizeF(72, 500), QPrinter::Millimeter);
    printer.setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);


    QPainter painter;
    painter.begin(&printer);

    QRectF textRect(currentX, currentY, width, 500);
    QRectF bounding;

    QFont font;
    font.setPixelSize(12);
    painter.setFont(font);
    painter.drawText(textRect, Qt::AlignHCenter, "The Coal Yard", &bounding);

    textRect.setY(textRect.y() + bounding.height() + lineSpacing);
    font.setPixelSize(14);
    painter.setFont(font);
    painter.drawText(textRect, Qt::AlignHCenter, "Reconciliation", &bounding);

    textRect.setY(textRect.y() + bounding.height() + lineSpacing);
    font.setPixelSize(16);
    painter.setFont(font);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(textRect, Qt::AlignHCenter, m_openedStamp.toString("ddd MM/dd/yyyy"), &bounding);
    textRect.setY(textRect.y() + bounding.height() + lineSpacing);
    painter.drawText(textRect, Qt::AlignHCenter, m_name, &bounding);
    font.setBold(false);
    font.setPixelSize(12);
    painter.setFont(font);
    textRect.setY(textRect.y() + bounding.height() + lineSpacing);
    painter.drawText(textRect, Qt::AlignHCenter, m_note, &bounding);

    textRect.setY(textRect.y() + bounding.height() + 20);


    textRect.setWidth(width/2 + 20);

    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignLeft, "End Drawer:", &bounding);
    painter.drawText(textRect, Qt::AlignRight, QString::number(m_endingDrawer->total(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignLeft, "- Beg Drawer:", &bounding);
    painter.drawText(textRect, Qt::AlignRight, QString::number(m_beginningDrawer->total(), 'f', 2), &bounding);    

    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignLeft, "+ Payouts:", &bounding);
    painter.drawText(textRect, Qt::AlignRight, QString::number(m_endingDrawer->property("payouts").toFloat(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignLeft, "= Cash Take:", &bounding);
    painter.drawText(textRect, Qt::AlignRight, QString::number(cashTotalActual(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignLeft, "+ Checks:", &bounding);
    painter.drawText(textRect, Qt::AlignRight, QString::number(m_endingDrawer->property("checks").toFloat(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignLeft, "+ Gift Cards:", &bounding);
    painter.drawText(textRect, Qt::AlignRight, QString::number(m_endingDrawer->property("giftCards").toFloat(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignLeft, "+ Credit Cards:", &bounding);
    painter.drawText(textRect, Qt::AlignRight, QString::number(m_creditCardTotalActual, 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignLeft, "+ Credit Tips:", &bounding);
    painter.drawText(textRect, Qt::AlignRight, QString::number(m_creditCardTotalTips, 'f', 2), &bounding);





    textRect.setX(width/2 + 40);
    textRect.setWidth(width/2 - 20);
    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignRight, "Food", &bounding);
    textRect.setWidth(width/2 - 65);
    painter.drawText(textRect, Qt::AlignRight, QString::number(foodTotal(), 'f', 2), &bounding);

    textRect.setWidth(width/2 - 20);
    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignRight, "+ Tax", &bounding);
    textRect.setWidth(width/2 - 65);
    painter.drawText(textRect, Qt::AlignRight, QString::number(taxTotal(), 'f', 2), &bounding);

    textRect.setWidth(width/2 - 20);
    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignRight, "+ Bar", &bounding);
    textRect.setWidth(width/2 - 65);
    painter.drawText(textRect, Qt::AlignRight, QString::number(barTotal(), 'f', 2), &bounding);

    textRect.setWidth(width/2 - 20);
    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignRight, "= Sales", &bounding);
    textRect.setWidth(width/2 - 65);
    painter.drawText(textRect, Qt::AlignRight, QString::number(total(), 'f', 2), &bounding);
    textRect.setX(currentX);


    textRect.setWidth(width/2);
    painter.drawText(textRect, Qt::AlignLeft, "= Total Take:", &bounding);
    painter.drawText(textRect, Qt::AlignRight, QString::number(takeTotalActual(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 5);
    painter.drawText(textRect, Qt::AlignLeft, "Discrepancy:", &bounding);
    float discrepancy = discrepancyActual();
    if(discrepancy < 0) {
        painter.drawText(textRect, Qt::AlignRight, QString::number(discrepancy * -1, 'f', 2), &bounding);
    } else {
        textRect.setX(width/2 + 40);
        textRect.setWidth(width/2 - 65);
        painter.drawText(textRect, Qt::AlignRight, QString::number(discrepancy, 'f', 2), &bounding);
    }


    painter.setPen(Qt::gray);
    QPointF lineStart(currentX, bounding.y() + bounding.height() + 20);
    QPointF lineEnd(currentX + width, lineStart.y());
    painter.drawLine(lineStart, lineEnd);

    painter.end();

}




QQmlListProperty<EmployeeShift> Reconciliation::shifts() {
    return QQmlListProperty<EmployeeShift>(this, m_shifts);
}

QList<EmployeeShift*> Reconciliation::shiftsList() {
    return m_shifts;
}

EmployeeShift* Reconciliation::addShift(QString name, QString note, float wage, quint8 scheduledStartHour, quint8 scheduledStartMinute, bool scheduledStartAM, quint8 scheduledEndHour, quint8 scheduledEndMinute, bool scheduledEndAM) {
    EmployeeShift *obj = new EmployeeShift(this, ++m_shiftCurrId, name, note, wage, scheduledStartHour, scheduledStartMinute, scheduledStartAM, scheduledEndHour, scheduledEndMinute, scheduledEndAM);
    addShift(obj);
    return obj;
}

void Reconciliation::addShift(EmployeeShift *value) {
    if(value->id() > m_shiftCurrId) m_shiftCurrId = value->id();
    connect(value, SIGNAL(costChanged(float)),
            this, SLOT(fireLaborCostChanged()));
    m_shifts.append(value);
    appendToHistory("AddEmployeeShift:" + value->serialize());
    shiftsChanged(shifts());
    fireLaborCostChanged();
}

EmployeeShift* Reconciliation::getShift(quint32 id) {
    for(EmployeeShift *value : m_shifts) {
        if(value->property("id").toUInt() == id) {
            return value;
        }
    }
    return nullptr;
}

void Reconciliation::removeShift(quint32 id) {
    for(int i = 0; i < m_shifts.length(); i++) {
        if(m_shifts[i]->property("id").toUInt() == id) {
            //EmployeeShift *item = m_shifts[i];
            m_shifts.removeAt(i);
            shiftsChanged(shifts());
            return;
        }
    }
}



