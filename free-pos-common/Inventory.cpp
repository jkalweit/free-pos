#include "Inventory.h"
#include "Pos.h"

Inventory::Inventory(QObject *parent) :
    QObject(parent), m_currentInventoryItemId(0)
{
}


InventoryItem* Inventory::addInventoryItem(QString name, float price) {
    InventoryItem *item = new InventoryItem(this, ++m_currentInventoryItemId, name, price);
    addInventoryItem(item);
    return item;
}

void Inventory::addInventoryItem(InventoryItem *item) {
    m_inventoryItems.append(item);
    if(item->property("id").toUInt() > m_currentInventoryItemId)
        m_currentInventoryItemId = item->property("id").toUInt();
    Pos::instance()->appendToInventoryHistory("AddInventoryItem:" + item->serialize());
    inventoryItemsChanged(inventoryItems());
}

InventoryItem* Inventory::getInventoryItem(quint32 id) {
    for(InventoryItem *item : m_inventoryItems) {
        if(item->property("id").toUInt() == id) {
            return item;
        }
    }
    return nullptr;
}

QQmlListProperty<InventoryItem> Inventory::inventoryItems() {
    return QQmlListProperty<InventoryItem>(this, m_inventoryItems);
}


