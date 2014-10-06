#include "Ticket.h"

#include <QMetaProperty>
#include <QDebug>
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


