#ifndef MENUITEM_H
#define MENUITEM_H

#include <QTextStream>
#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"
#include "MenuItemInventoryItem.h"
#include "MenuItemOption.h"

class MenuItem : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type MEMBER m_type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(float price MEMBER m_price WRITE setPrice NOTIFY priceChanged)
    Q_PROPERTY(bool isDisabled MEMBER m_isDisabled WRITE setIsDisabled NOTIFY isDisabledChanged)
    Q_PROPERTY(bool isHiddenFromKitchen MEMBER m_isHiddenFromKitchen READ isHiddenFromKitchen NOTIFY isHiddenFromKitchenChanged)
    Q_PROPERTY(QString prepType MEMBER m_prepType READ prepType WRITE setPrepType NOTIFY prepTypeChanged)

    Q_PROPERTY(QQmlListProperty<MenuItemInventoryItem> menuItemInventoryItems READ menuItemInventoryItems NOTIFY menuItemInventoryItemsChanged)
    Q_PROPERTY(QQmlListProperty<MenuItemOption> menuItemOptions READ menuItemOptions NOTIFY menuItemOptionsChanged)

    Q_PROPERTY(bool hasInventory READ hasInventory NOTIFY hasInventoryChanged)
    Q_PROPERTY(float cost READ cost NOTIFY costChanged)
    Q_PROPERTY(float margin READ margin NOTIFY marginChanged)
public:
   explicit MenuItem(QObject *parent = 0, quint32 id = 0, quint32 m_menuCategoryId = 0, QString name = "", QString type = "", float price = 0, bool isDisabled = false, bool isHiddenFromKitchen = false, QString prepType = "");

    virtual QStringList updatePrefix();

    quint32 menuCategoryId();
    void setName(QString name);
    void setType(QString type);
    void setPrice(float price);
    void setIsDisabled(bool isDisabled);
    void setPrepType(QString prepType);

    bool hasInventory();
    float cost();
    float costWithoutOptions();
    float margin();
    bool isHiddenFromKitchen();
    QString prepType();

    Q_INVOKABLE float getCumulativeCostUpToOption(quint32 menuItemOptionId);
    Q_INVOKABLE float getCumulativeCostUpToInventoryItem(quint32 inventoryItemId);

    QQmlListProperty<MenuItemInventoryItem> menuItemInventoryItems();
    QList<MenuItemInventoryItem*> menuItemInventoryItemsList();
    Q_INVOKABLE MenuItemInventoryItem* addMenuItemInventoryItem(quint32 inventoryItemId, float quantity);
    void addMenuItemInventoryItem(MenuItemInventoryItem *menuItemInventoryItem);
    MenuItemInventoryItem* getMenuItemInventoryItem(quint32 id);
    Q_INVOKABLE void removeMenuItemInventoryItem(quint32 menuItemInventoryItemId);

    QQmlListProperty<MenuItemOption> menuItemOptions();
    QList<MenuItemOption*> menuItemOptionsList();
    Q_INVOKABLE MenuItemOption* addMenuItemOption(quint32 optionMenuCategoryId);
    void addMenuItemOption(MenuItemOption *menuItemOption);
    MenuItemOption* getMenuItemOption(quint32 id);
    Q_INVOKABLE void removeMenuItemOption(quint32 menuItemOption);

    QString serialize() const;
    static MenuItem* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void typeChanged(QString);
    void priceChanged(float);
    void isDisabledChanged(bool);
    void isHiddenFromKitchenChanged(bool);
    void prepTypeChanged(QString);

    void menuItemInventoryItemsChanged(QQmlListProperty<MenuItemInventoryItem>);
    void menuItemOptionsChanged(QQmlListProperty<MenuItemOption>);

    void hasInventoryChanged(bool);
    void costChanged(float);
    void marginChanged(float);

public slots:
    void fireCostChanged();    

private:
    quint32 m_id;
    quint32 m_menuCategoryId;
    QString m_name;
    QString m_type;    
    float m_price;
    bool m_isDisabled;
    bool m_isHiddenFromKitchen;
    QString m_prepType;

    quint32 m_currentMenuItemInventoryItemId;
    QList<MenuItemInventoryItem*> m_menuItemInventoryItems;

    quint32 m_currentMenuItemOptionId;
    QList<MenuItemOption*> m_menuItemOptions;
};

#endif // MENUITEM_H
