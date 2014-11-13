#include "OrderItemInventoryItem.h"

OrderItemInventoryItem::OrderItemInventoryItem(QObject *parent, quint32 ticketId, quint32 customerId, quint32 orderItemId, quint32 id, quint32 inventoryItemId, QString name, QString unit, float price, float quantity, bool isRemoved, bool isAdded) :
    SimpleSerializable(parent), m_ticketId(ticketId), m_customerId(customerId), m_orderItemId(orderItemId), m_id(id), m_inventoryItemId(inventoryItemId), m_name(name), m_unit(unit), m_price(price), m_quantity(quantity), m_isRemoved(isRemoved), m_isAdded(isAdded)
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

void OrderItemInventoryItem::setIsRemoved(bool isRemoved) {
    if(m_isRemoved != isRemoved) {
        m_isRemoved = isRemoved;
        logPropertyChanged(m_isRemoved, "isRemoved");
        isRemovedChanged(isRemoved);
        fireCostChanged();
    }
}

void OrderItemInventoryItem::setIsAdded(bool isAdded) {
    if(m_isAdded != isAdded) {
        m_isAdded = isAdded;
        logPropertyChanged(m_isAdded, "isAdded");
        isAddedChanged(isAdded);
        fireCostChanged();
    }
}

float OrderItemInventoryItem::cost() {
    if(m_isRemoved) {
        return 0;
    } else {
        return m_quantity * m_price;
    }
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
    vals  << QString::number(m_ticketId) << QString::number(m_customerId) << QString::number(m_orderItemId) << QString::number(m_id) << QString::number(m_inventoryItemId) << m_name << m_unit << QString::number(m_price) << QString::number(m_quantity) << QString::number(m_isRemoved) << QString::number(m_isAdded);
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
    QString unit = split[6];
    float price = split[7].toFloat();
    float quantity = split[8].toFloat();
    bool isRemoved = split[9].toInt();
    bool isAdded = split[10].toInt();

    OrderItemInventoryItem *obj = new OrderItemInventoryItem(parent, ticketId, customerId, orderItemId, id, inventoryItemId, name, unit, price, quantity, isRemoved, isAdded);
    return obj;
}


