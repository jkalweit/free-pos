#include "InventoryItem.h"

InventoryItem::InventoryItem(QObject *parent, quint32 id, QString name, QString unit, float defaultQuantity, float priceQuantity, float price) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_unit(unit), m_defaultQuantity(defaultQuantity), m_priceQuantity(priceQuantity), m_price(price)
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

void InventoryItem::setUnit(QString unit) {
    if(m_unit != unit) {
        m_unit = unit;
        logInventoryPropertyChanged(m_unit, "unit");
        unitChanged(m_unit);
    }
}

void InventoryItem::setDefaultQuantity(float defaultQuantity) {
    if(m_defaultQuantity != defaultQuantity) {
        m_defaultQuantity = defaultQuantity;
        logInventoryPropertyChanged(m_defaultQuantity, "defaultQuantity");
        defaultQuantityChanged(m_defaultQuantity);
        defaultCostChanged(defaultCost());
    }
}

void InventoryItem::setPriceQuantity(float priceQuantity) {
    if(m_priceQuantity != priceQuantity) {
        m_priceQuantity = priceQuantity;
        logInventoryPropertyChanged(m_priceQuantity, "priceQuantity");
        priceQuantityChanged(m_priceQuantity);
        unitPriceChanged(unitPrice());
        defaultCostChanged(defaultCost());
    }
}

void InventoryItem::setPrice(float price) {
    if(m_price != price) {
        m_price = price;
        logInventoryPropertyChanged(m_price, "price");
        priceChanged(m_price);
        unitPriceChanged(unitPrice());
        defaultCostChanged(defaultCost());
    }
}

float InventoryItem::unitPrice() {
    if(m_priceQuantity != 0) {
        return m_price / m_priceQuantity;
    } else {
        return 0;
    }
}

float InventoryItem::defaultCost() {
    return m_defaultQuantity * unitPrice();
}

QString InventoryItem::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << m_name << m_unit << QString::number(m_defaultQuantity) << QString::number(m_priceQuantity) << QString::number(m_price);
    return serializeList(vals);
}

InventoryItem* InventoryItem::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 id = split[0].toUInt();
    QString name = split[1];
    QString unit = split[2];
    float defaultQuantity = split[3].toFloat();
    float priceQuantity = split[4].toFloat();
    float price = split[5].toFloat();

    InventoryItem *obj = new InventoryItem(parent, id, name, unit, defaultQuantity, priceQuantity, price);
    return obj;
}

