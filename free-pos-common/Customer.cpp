#include "Customer.h"

#include <QMetaProperty>
#include <QDebug>



Customer::Customer(QObject *parent, quint32 id, quint32 ticketId, QString name) :
    QObject(parent), m_id(id), m_ticketId(ticketId), m_name(name), m_currentOrderItemId(0)
{
}

void Customer::setName(QString name) {
    QString normalized = name.toUpper().trimmed();
    if(m_name != normalized) {
        m_name = normalized;
        nameChanged(m_name);
    }
}


float Customer::foodTotal() {
    float sum = 0;
    QString type;
    for(OrderItem *o : m_orderItems) {
        type = o->property("type").toString();
        if(type != "Alcohol") {
            sum += o->subTotal();
        }
    }
    return sum;
}

float Customer::taxTotal() {
    return foodTotal() * 0.09;
}

float Customer::barTotal() {
    float sum = 0;
    QString type;
    for(OrderItem *o : m_orderItems) {
        type = o->property("type").toString();
        if(type == "Alcohol") {
            sum += o->subTotal();
        }
    }
    return sum;
}

float Customer::total() {
    return foodTotal() + taxTotal() + barTotal();
}

void Customer::fireTotalsChanged() {
    foodTotalChanged(foodTotal());
    taxTotalChanged(taxTotal());
    totalChanged(total());
}

OrderItem* Customer::addOrderItem(QString name, QString type, float price, float quantity, QString note) {
    OrderItem* orderItem = new OrderItem(this, ++m_currentOrderItemId, name, type, price, quantity, note);
    addOrderItem(orderItem);
    return orderItem;
}

void Customer::addOrderItem(OrderItem *orderItem) {
    connect(orderItem, SIGNAL(subTotalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(orderItem, SIGNAL(taxChanged(float)),
            this, SLOT(fireTotalsChanged()));
    connect(orderItem, SIGNAL(totalChanged(float)),
            this, SLOT(fireTotalsChanged()));
    m_orderItems.append(orderItem);
    orderItemsChanged(orderItems());
    fireTotalsChanged();
}

QQmlListProperty<OrderItem> Customer::orderItems() {
    return QQmlListProperty<OrderItem>(this, m_orderItems);
}

QString Customer::serialize() const {
    return QString::number(m_id) + ":" + QString::number(m_ticketId) + ":" + m_name;
}

Customer* Customer::deserialize(QString serialized, QObject *parent)
{
    QStringList split = serialized.split(":");

    quint32 id = split[0].toInt();
    quint32 ticketId = split[1].toInt();
    QString name = split[2];

    Customer *obj = new Customer(parent, id, ticketId, name);
    qDebug() << "    deserialized: " << obj->serialize();
    return obj;
}

QTextStream& operator<<(QTextStream& stream, const Customer& obj) {
    stream << obj.serialize() << endl;
    return stream;
}
QTextStream& operator>>(QTextStream& stream, Customer& obj) {

    QString line = stream.readAll();
    qDebug() << "Got line: " << line;
    if(line.length() <= 1){
        qDebug() << "Empty line.";
        return stream;
    }
    Customer* obj2 = Customer::deserialize(line);
    obj.m_id = obj2->m_id;
    obj.m_ticketId = obj2->m_ticketId;
    obj.m_name = obj2->m_name;

    return stream;
}



