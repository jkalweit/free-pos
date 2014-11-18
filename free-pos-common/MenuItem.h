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

    Q_PROPERTY(QQmlListProperty<MenuItemInventoryItem> menuItemInventoryItems READ menuItemInventoryItems NOTIFY menuItemInventoryItemsChanged)
    Q_PROPERTY(QQmlListProperty<MenuItemOption> menuItemOptions READ menuItemOptions NOTIFY menuItemOptionsChanged)

    Q_PROPERTY(float cost READ cost NOTIFY costChanged)
    Q_PROPERTY(float margin READ margin NOTIFY marginChanged)
public:
    explicit MenuItem(QObject *parent = 0, quint32 id = 0, quint32 m_menuCategoryId = 0, QString name = "", QString type = "", float price = 0, bool isDisabled = false);

    virtual QStringList updatePrefix();

    quint32 menuCategoryId();
    void setName(QString name);
    void setType(QString type);
    void setPrice(float price);
    void setIsDisabled(bool isDisabled);

    float cost();
    float margin();

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

    void menuItemInventoryItemsChanged(QQmlListProperty<MenuItemInventoryItem>);
    void menuItemOptionsChanged(QQmlListProperty<MenuItemOption>);

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

    quint32 m_currentMenuItemInventoryItemId;
    QList<MenuItemInventoryItem*> m_menuItemInventoryItems;

    quint32 m_currentMenuItemOptionId;
    QList<MenuItemOption*> m_menuItemOptions;
};

#endif // MENUITEM_H
