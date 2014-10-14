#include "Reconciliation.h"

#include <QPainter>
#include <QPrinter>
#include <QFont>
#include <QMetaProperty>
#include <QDebug>
#include "Pos.h"

Reconciliation::Reconciliation(QObject *parent, quint32 id, QString name, QString note,
                               QDateTime openedStamp, QDateTime closedStamp,
                               CashDrawer *begginningDrawer, CashDrawer *endingDrawer,
                               float creditCardTotalActual, float creditCardTotalTips) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_note(note),
    m_openedStamp(openedStamp), m_closedStamp(closedStamp),
    m_beginningDrawer(begginningDrawer), m_endingDrawer(endingDrawer),
    m_currentTicketId(0), m_selectedTicket(nullptr), m_creditCardTotalActual(creditCardTotalActual), m_creditCardTotalTips(creditCardTotalTips)
{
    if(m_beginningDrawer == nullptr)
        m_beginningDrawer = new CashDrawer(this, 1);
    if(m_endingDrawer == nullptr)
        m_endingDrawer = new CashDrawer(this, 2);


    connect(m_beginningDrawer, SIGNAL(totalChanged(float)),
            this, SLOT(fireActualTakeTotalsChanged()));
    connect(m_endingDrawer, SIGNAL(totalChanged(float)),
            this, SLOT(fireActualTakeTotalsChanged()));
}

QStringList Reconciliation::updatePrefix() {
    return QStringList() << "UpdateReconciliation" << QString::number(m_id);
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

    m_tickets.append(ticket);
    Pos *pos = Pos::instance();
    pos->appendToHistory("AddTicket:" + ticket->serialize());
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
    if(!Pos::instance()->closeCurrentRec()) {
        m_closedStamp = QDateTime();
        logPropertyChanged(m_closedStamp, "closedStamp");
    } else {
        qDebug() << "Closed rec: " << m_closedStamp.toString("MM/dd/yyyy hh:mmAP");        
    }

    closedStampChanged(m_closedStamp);
    isOpenChanged(isOpen());

    return !isOpen();
}

bool Reconciliation::isOpen() {
    return m_closedStamp.isNull();
}



QString Reconciliation::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << m_name << m_note << m_openedStamp.toString();
    return serializeList(vals);
}

Reconciliation* Reconciliation::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 id = split[0].toInt();
    QString name = split[1];
    QString note = split[2];
    QDateTime opened = QDateTime::fromString(split[3]);

    Reconciliation *obj = new Reconciliation(parent, id, name, note, opened);
    return obj;
}



void Reconciliation::print() {

    QPrinter printer;


    printer.setFullPage(true);
    printer.setOutputFormat(printer.PdfFormat);
    printer.setOutputFileName("reconciliation.pdf");

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

    textRect.setY(textRect.y() + bounding.height() + 20);

    font.setPixelSize(12);
    painter.setFont(font);
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
        textRect.setX(width/2 + 40);
        textRect.setWidth(width/2 - 65);
        painter.drawText(textRect, Qt::AlignRight, QString::number(discrepancy * -1, 'f', 2), &bounding);
    } else {
        painter.drawText(textRect, Qt::AlignRight, QString::number(discrepancy, 'f', 2), &bounding);
    }



    painter.end();

}


