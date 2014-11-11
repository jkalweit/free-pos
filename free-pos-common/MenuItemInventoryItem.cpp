#include "MenuItemInventoryItem.h"

MenuItemInventoryItem::MenuItemInventoryItem(QObject *parent, quint32 id, quint32 menuCategoryId, quint32 menuItemId, quint32 inventoryItemId, float quantity) :
    SimpleSerializable(parent), m_id(id), m_menuCategoryId(menuCategoryId), m_menuItemId(menuItemId), m_inventoryItemId(inventoryItemId), m_quantity(quantity)
{
}

QStringList MenuItemInventoryItem::updatePrefix() {
    return QStringList() << "UpdateMenuItemInventoryItem" << QString::number(m_id) << QString::number(m_menuCategoryId) << QString::number(m_menuItemId);
}

void MenuItemInventoryItem::setQuantity(float quantity) {
    if(m_quantity != quantity) {
        m_quantity = quantity;
        logMenuPropertyChanged(m_quantity, "quantity");
        quantityChanged(m_quantity);
    }
}

QString MenuItemInventoryItem::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << QString::number(m_menuCategoryId) << QString::number(m_menuItemId) << QString::number(m_inventoryItemId) << QString::number(m_quantity);
    return serializeList(vals);
}

MenuItemInventoryItem* MenuItemInventoryItem::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 id = split[0].toUInt();
    quint32 menuCategoryId = split[1].toUInt();
    quint32 menuItemId = split[2].toUInt();
    quint32 inventoryItemId = split[3].toUInt();
    float quantity = split[4].toFloat();

    MenuItemInventoryItem *obj = new MenuItemInventoryItem(parent, id, menuCategoryId, menuItemId, inventoryItemId, quantity);
    return obj;
}
