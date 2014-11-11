#ifndef INVENTORY_H
#define INVENTORY_H

#include <QDebug>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "InventoryItem.h"

class Inventory : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<InventoryItem> inventoryItems READ inventoryItems NOTIFY inventoryItemsChanged)
public:
    explicit Inventory(QObject *parent = 0);

    Q_INVOKABLE InventoryItem* addInventoryItem(QString name, float price);
    void addInventoryItem(InventoryItem *inventoryItem);
    QQmlListProperty<InventoryItem> inventoryItems();
    Q_INVOKABLE InventoryItem* getInventoryItem(quint32 id);

signals:
    void inventoryItemsChanged(QQmlListProperty<InventoryItem>);

private:
    QList<InventoryItem*> m_inventoryItems;
    quint32 m_currentInventoryItemId;

};

#endif // INVENTORY_H
