#include "Ticket.h"

#include <QMetaProperty>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QPainter>
#include "Pos.h"

Ticket::Ticket(QObject *parent, quint32 id, QString name, QDateTime createdStamp, QString paymentType, QDateTime paidStamp, bool isTogo) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_currentCustomerId(0), m_createdStamp(createdStamp),
    m_paymentType(paymentType), m_paidStamp(paidStamp), m_isTogo(isTogo)
{
    connect(this, SIGNAL(nameChanged(QString)),
            this, SLOT(fireNamesChanged()));
}


void Ticket::logPropertyChanged(QVariant value, QString propertyName) {
    QString safe = value.toString().replace("\n", "\\n");
    safe = safe.replace(":", "\\colon");
    safe = "UpdateTicket:" + QString::number(m_id) + ":" + propertyName + ":"  + safe;
    Pos::instance()->appendToHistory(safe);
}


void Ticket::setIsTogo(bool togo) {
    if(m_isTogo != togo) {
        m_isTogo = togo;
        logPropertyChanged(m_isTogo, "isTogo");
        isTogoChanged(m_isTogo);
    }
}

QString Ticket::customerNames() {
    if(m_customers.size() == 0)
        return "";

    QString name = m_customers[0]->property("name").toString();
    for(int i = 1; i < m_customers.size(); i++) {
        name += ", " + m_customers[i]->property("name").toString();;
    }
    return name;
}

QString Ticket::longName() {
    return m_name + ": " + customerNames();
}

bool Ticket::isPaid() {
    return m_paymentType != "";
}

void Ticket::cyclePaymentType() {

    if(m_paymentType == "") {
        m_paymentType = "Credit Card";
    } else if(m_paymentType == "Credit Card") {
        m_paymentType = "Cash";
    } else {
        m_paymentType = "";
    }

    if(!isPaid()) {
        m_paidStamp = QDateTime();
    } else {
        m_paidStamp = QDateTime::currentDateTime();
    }

    logPropertyChanged(m_paymentType, "paymentType");
    logPropertyChanged(m_paidStamp, "paidStamp");

    paymentTypeChanged(m_paymentType);
    paidStampChanged(m_paidStamp);
    isPaidChanged(isPaid());
}


void Ticket::fireTotalsChanged() {
    foodTotalChanged(foodTotal());
    taxTotalChanged(taxTotal());
    barTotalChanged(barTotal());
    totalChanged(total());
}

void Ticket::fireNamesChanged() {
    customerNamesChanged(customerNames());
    longNameChanged(longName());
}

Customer* Ticket::addCustomer(QString name) {
    Customer *obj = new Customer(this, ++m_currentCustomerId, m_id, name.toUpper());
    addCustomer(obj);
    return obj;
}

void Ticket::addCustomer(Customer *customer) {
    connect(customer, SIGNAL(nameChanged(QString)),
            this, SLOT(fireNamesChanged()));
    connect(customer, SIGNAL(foodTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(customer, SIGNAL(taxTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(customer, SIGNAL(barTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(customer, SIGNAL(totalChanged(float)),
            this, SLOT(fireTotalsChanged()));

    m_customers.append(customer);
    Pos::instance()->appendToHistory("AddCustomer:" + customer->serialize());
    customersChanged(customers());
    customerNamesChanged(customerNames());
    longNameChanged(longName());
    fireTotalsChanged();
}

QQmlListProperty<Customer> Ticket::customers() {    
    return QQmlListProperty<Customer>(this, m_customers);
}

Customer* Ticket::getCustomer(quint32 id) {
    for(Customer *c : m_customers) {\
        if(c->property("id").toUInt() == id) return c;
    }
    return nullptr;
}

float Ticket::foodTotal() {
    float sum = 0;
    for(Customer *c : m_customers) {\
        sum += c->foodTotal();
    }
    return sum;
}

float Ticket::taxTotal() {
    float sum = 0;
    for(Customer *c : m_customers) {\
        sum += c->taxTotal();
    }
    return sum;
}

float Ticket::barTotal() {
    float sum = 0;
    for(Customer *c : m_customers) {\
        sum += c->barTotal();
    }
    return sum;
}

float Ticket::total() {
    return foodTotal() + taxTotal() + barTotal();
}

void Ticket::printKitchen() {

    QPrinter printer;

//    QPrintDialog dialog(&printer);
//    dialog.setWindowTitle(tr("Print Document"));
////    if (editor->textCursor().hasSelection())
////        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
//    if (dialog.exec() != QDialog::Accepted) {
//        return;
//    }

    printer.setFullPage(true);
    //printer.setOutputFormat(printer.PdfFormat);
    //printer.setOutputFileName("receipt.pdf");

    qreal currentX = 20;
    qreal currentY = 0;
    qreal lineSpacing = 40;
    qreal width = 232;

    printer.setPaperSize(QSizeF(width, 120), QPrinter::Millimeter);
    printer.setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);


    QPainter painter;
    painter.begin(&printer);

    QRectF textRect(currentX, currentY, width, 20);
    QRectF bounding;

    QFont font;
    font.setPixelSize(22);
    painter.setFont(font);
    painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, "The Coal Yard", &bounding);

    textRect.setY(textRect.y() + bounding.height() + 20);
    font.setPixelSize(16);
    painter.setFont(font);
    painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, "Neighborhood Public House", &bounding);

    textRect.setY(textRect.y() + bounding.height() + lineSpacing);
    font.setPixelSize(12);
    painter.setFont(font);
    painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, "105 Garner St, York SC 29745", &bounding);

    textRect.setY(textRect.y() + bounding.height() + 20);
    painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, "www.TheCoalYard.com", &bounding);

    textRect.setY(textRect.y() + bounding.height() + 20);
    painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, "803.684.9653", &bounding);

    textRect.setY(textRect.y() + bounding.height() + 20);

    for(Customer *c : m_customers) {
        textRect.setX(currentX);
        textRect.setWidth(width);
        textRect.setY(textRect.y() + bounding.height() + 20);
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, c->property("name").toString(), &bounding);

        for(OrderItem *o : c->orderItemsList()) {
            textRect.setX(currentX + 20);
            textRect.setWidth(width - 20);
            textRect.setY(textRect.y() + bounding.height() + 20);
            painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, o->property("quantity").toString(), &bounding);
            textRect.setX(currentX + 50);
            textRect.setWidth(width - 50);
            painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, o->property("name").toString(), &bounding);
            painter.drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, QString::number(o->property("total").toDouble(), 'f', 2), &bounding);
        }
    }

    textRect.setX(currentX + 80);
    textRect.setWidth(width - 80);
    textRect.setY(textRect.y() + bounding.height() + 40);
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, "Food:", &bounding);
    painter.drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, QString::number(foodTotal(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 20);
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, "Tax:", &bounding);
    painter.drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, QString::number(taxTotal(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 20);
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, "Bar:", &bounding);
    painter.drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, QString::number(barTotal(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 20);
    font.setPixelSize(18);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, "Total:", &bounding);
    painter.drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, "$" + QString::number(total(), 'f', 2), &bounding);

    textRect.setY(textRect.y() + bounding.height() + 60);
    textRect.setX(currentX);
    textRect.setWidth(width);
    font.setPixelSize(12);
    font.setBold(false);
    painter.setFont(font);
    painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, "Thank You!", &bounding);

    painter.setPen(Qt::gray);
    textRect.setY(textRect.y() + bounding.height() + 20);
    textRect.setHeight(80);
    painter.drawRect(textRect);
    QPointF lineStart(currentX, bounding.y() + bounding.height() + 20);
    QPointF lineEnd(currentX + width, lineStart.y());
    painter.drawLine(lineStart, lineEnd);

    painter.end();

}

QString Ticket::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << m_name << m_createdStamp.toString();
    return serializeList(vals);
}

Ticket* Ticket::deserialize(QString serialized, QObject *parent)
{
    QStringList vals = deserializeList(serialized);

    quint32 id = vals[0].toInt();
    //quint32 reconciliationId = split[1].toInt();
    QString name = vals[1];
    QDateTime createdStamp = QDateTime::fromString(vals[2]);

    Ticket *obj = new Ticket(parent, id, name, createdStamp);
    return obj;
}


