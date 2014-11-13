#include "OrderItemOption.h"

OrderItemOption::OrderItemOption(QObject *parent, quint32 ticketId, quint32 customerId, quint32 orderItemId, quint32 id, QString name, float cost) :
    SimpleSerializable(parent), m_ticketId(ticketId), m_customerId(customerId), m_orderItemId(orderItemId), m_id(id), m_name(name), m_cost(cost)
{
}

QStringList OrderItem::updatePrefix() {
    return QStringList() << "UpdateOrderItemOption" << QString::number(m_ticketId) << QString::number(m_customerId) << QString::number(m_orderItemId) << QString::number(m_id);
}





QString OrderItem::serialize() const {
    QStringList vals;
    vals << QString::number(m_ticketId) << QString::number(m_customerId) << QString::number(m_orderItemId) << QString::number(m_id) << m_name << QString::number(m_cost);
    return serializeList(vals);
}

OrderItem* OrderItem::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 ticketId = split[0].toInt();
    quint32 customerId = split[1].toInt();
    quint32 orderItemId = split[2].toInt();
    quint32 id = split[3].toInt();
    QString name = split[4];
    float cost = split[5].toFloat();

    OrderItemOption *obj = new OrderItemOption(parent, ticketId, customerId, orderItemId, id, name, cost);
    return obj;
}
