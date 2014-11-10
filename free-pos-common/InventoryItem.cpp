#include "InventoryItem.h"

InventoryItem::InventoryItem(QObject *parent, quint32 id, QString name, float price) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_price(price)
{
}

QStringList InventoryItem::updatePrefix() {
    return QStringList() << "UpdateInventoryItem" << QString::number(m_id);
}

void InventoryItem::setName(QString name) {
    if(m_name != name.trimmed()) {
        m_name = name.trimmed();
        logInventoryPropertyChanged(m_name, "name");
        nameChanged(m_name);
    }
}

void InventoryItem::setPrice(float price) {
    if(m_price != price) {
        m_price = price;
        logInventoryPropertyChanged(m_price, "price");
        priceChanged(m_price);
    }
}

QString InventoryItem::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << m_name << QString::number(m_price);
    return serializeList(vals);
}

InventoryItem* InventoryItem::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 id = split[0].toUInt();
    QString name = split[1];
    float price = split[2].toFloat();

    InventoryItem *obj = new InventoryItem(parent, id, name, price);
    return obj;
}

