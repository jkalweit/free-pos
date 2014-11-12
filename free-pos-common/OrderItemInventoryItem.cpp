#include "OrderItemInventoryItem.h"

OrderItemInventoryItem::OrderItemInventoryItem(QObject *parent, quint32 ticketId, quint32 customerId, quint32 orderItemId, quint32 id, quint32 inventoryItemId, QString name, float price, float quantity) :
    SimpleSerializable(parent), m_ticketId(ticketId), m_customerId(customerId), m_orderItemId(orderItemId), m_id(id), m_inventoryItemId(inventoryItemId), m_name(name), m_price(price), m_quantity(quantity)
{
}

QStringList OrderItemInventoryItem::updatePrefix() {
    return QStringList() << "UpdateOrderItemInventoryItem" << QString::number(m_ticketId) << QString::number(m_customerId) << QString::number(m_orderItemId) << QString::number(m_id);
}

void OrderItemInventoryItem::setQuantity(float quantity) {
    if(m_quantity != quantity) {
        m_quantity = quantity;
        logPropertyChanged(m_quantity, "quantity");
        quantityChanged(m_quantity);
        fireCostChanged();
    }
}

float OrderItemInventoryItem::cost() {
    return m_quantity * m_price;
}

quint32 OrderItemInventoryItem::ticketId() {
    return m_ticketId;
}

quint32 OrderItemInventoryItem::customerId() {
    return m_customerId;
}

quint32 OrderItemInventoryItem::orderItemId() {
    return m_orderItemId;
}

quint32 OrderItemInventoryItem::id() {
    return m_id;
}


void OrderItemInventoryItem::fireCostChanged() {
    costChanged(cost());
}

QString OrderItemInventoryItem::serialize() const {
    QStringList vals;
    vals  << QString::number(m_ticketId) << QString::number(m_customerId) << QString::number(m_orderItemId) << QString::number(m_id) << QString::number(m_inventoryItemId) << m_name << QString::number(m_price) << QString::number(m_quantity);
    return serializeList(vals);
}

OrderItemInventoryItem* OrderItemInventoryItem::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 ticketId = split[0].toUInt();
    quint32 customerId = split[1].toUInt();
    quint32 orderItemId = split[2].toUInt();
    quint32 id = split[3].toUInt();
    quint32 inventoryItemId = split[4].toUInt();
    QString name = split[5];
    float price = split[6].toFloat();
    float quantity = split[7].toFloat();

    OrderItemInventoryItem *obj = new OrderItemInventoryItem(parent, ticketId, customerId, orderItemId, id, inventoryItemId, name, price, quantity);
    return obj;
}


