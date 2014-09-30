#include "Ticket.h"

#include <QMetaProperty>
#include <QDebug>


Ticket::Ticket(QObject *parent, quint32 id, QString name, QDateTime paidStamp) :
    QObject(parent), m_id(id), m_name(name), m_currentCustomerId(0), m_paidStamp(paidStamp)
{
    connect(this, SIGNAL(nameChanged(QString)),
            this, SLOT(fireNamesChanged()));
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
    return !m_paidStamp.isNull();
}

void Ticket::toggleIsPaid() {
    if(isPaid()) {
        m_paidStamp = QDateTime();
    } else {
        m_paidStamp = QDateTime::currentDateTime();
    }

    isPaidChanged(isPaid());
    paidStampChanged(m_paidStamp);
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
    customersChanged(customers());
    customerNamesChanged(customerNames());
    longNameChanged(longName());
    fireTotalsChanged();
}

QQmlListProperty<Customer> Ticket::customers() {    
    return QQmlListProperty<Customer>(this, m_customers);
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
    return QString::number(m_id) + ":" + m_name;
}

Ticket* Ticket::deserialize(QString serialized, QObject *parent)
{
    QStringList split = serialized.split(":");

    quint32 id = split[0].toInt();
    //quint32 reconciliationId = split[1].toInt();
    QString name = split[1];

    Ticket *obj = new Ticket(parent, id, name);
    qDebug() << "    deserialized: " << obj->serialize();
    return obj;
}

QTextStream& operator<<(QTextStream& stream, const Ticket& obj) {
    stream << obj.serialize() << endl;
    return stream;
}
QTextStream& operator>>(QTextStream& stream, Ticket& obj) {

    QString line = stream.readAll();
    qDebug() << "Got line: " << line;
    if(line.length() <= 1){
        qDebug() << "Empty line.";
        return stream;
    }
    Ticket* obj2 = Ticket::deserialize(line);
    obj.m_id = obj2->m_id;
    //obj.m_reconciliationId = obj2->m_reconciliationId;
    obj.m_name = obj2->m_name;

    return stream;
}




