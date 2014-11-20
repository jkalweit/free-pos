#ifndef MENUITEMINVENTORYITEM_H
#define MENUITEMINVENTORYITEM_H

#include <QTextStream>
#include <QObject>
#include "SimpleSerializable.h"
#include "InventoryItem.h"

class MenuItemInventoryItem : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    Q_PROPERTY(quint32 menuCategoryId MEMBER m_menuCategoryId NOTIFY menuCategoryIdChanged)
    Q_PROPERTY(quint32 menuItemId MEMBER m_menuItemId NOTIFY menuItemIdChanged)
    Q_PROPERTY(quint32 inventoryItemId MEMBER m_inventoryItemId NOTIFY inventoryItemIdChanged)
    Q_PROPERTY(float quantity MEMBER m_quantity WRITE setQuantity NOTIFY quantityChanged)
    Q_PROPERTY(InventoryItem* inventoryItem READ inventoryItem WRITE setInventoryItem NOTIFY inventoryItemChanged)
    Q_PROPERTY(float cost READ cost NOTIFY costChanged)
public:
    explicit MenuItemInventoryItem(QObject *parent = 0, quint32 id = 0, quint32 menuCategoryId = 0, quint32 menuItemId = 0, quint32 inventoryItemId = 0, float quantity = 0);

    virtual QStringList updatePrefix();

    quint32 id();

    void setQuantity(float quantity);
    float cost();

    InventoryItem* inventoryItem();
    void setInventoryItem(InventoryItem* inventoryItem);

    QString serialize() const;
    static MenuItemInventoryItem* deserialize(QString serialized, QObject *parent = 0);


signals:
    void idChanged(quint32);
    void menuCategoryIdChanged(quint32);
    void menuItemIdChanged(quint32);
    void inventoryItemIdChanged(quint32);
    void inventoryItemChanged(InventoryItem*);
    void quantityChanged(float);
    void costChanged(float);

public slots:
    void fireCostChanged();

private:
    quint32 m_id;
    quint32 m_menuCategoryId;
    quint32 m_menuItemId;
    quint32 m_inventoryItemId;    
    float m_quantity;

    InventoryItem *m_inventoryItem;

};

#endif // MENUITEMINVENTORYITEM_H
