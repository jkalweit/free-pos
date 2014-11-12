#include "MenuItem.h"

#include <QMetaProperty>
#include <QDebug>
#include "Pos.h"

MenuItem::MenuItem(QObject *parent, quint32 id, quint32 menuCategoryId, QString name, QString type, float price, bool isDisabled) :
    SimpleSerializable(parent), m_id(id), m_menuCategoryId(menuCategoryId), m_name(name), m_type(type), m_price(price), m_isDisabled(isDisabled), m_currentMenuItemInventoryItemId(0)
{
}

QStringList MenuItem::updatePrefix() {
    return QStringList() << "UpdateMenuItem" << QString::number(m_id) << QString::number(m_menuCategoryId);
}

void MenuItem::setName(QString name) {
    if(m_name != name.trimmed()) {
        m_name = name.trimmed();
        logMenuPropertyChanged(m_name, "name");
        nameChanged(m_name);
    }
}

void MenuItem::setType(QString type) {
    if(m_type != type) {
        m_type = type;
        logMenuPropertyChanged(m_type, "type");
        typeChanged(m_type);
    }
}

void MenuItem::setPrice(float price) {
    if(m_price != price) {
        m_price = price;
        logMenuPropertyChanged(m_price, "price");
        priceChanged(m_price);
    }
}

void MenuItem::setIsDisabled(bool isDisabled) {
    if(m_isDisabled != isDisabled) {
        m_isDisabled = isDisabled;
        logMenuPropertyChanged(m_isDisabled, "isDisabled");
        isDisabledChanged(m_isDisabled);
    }
}


float MenuItem::cost() {
    float cost = 0;

    for(MenuItemInventoryItem *item : m_menuItemInventoryItems) {
        cost += item->cost();
    }

    return cost;
}

float MenuItem::margin() {
    return m_price - cost();
}

void MenuItem::fireCostChanged() {
    costChanged(cost());
    marginChanged(margin());
}


MenuItemInventoryItem* MenuItem::addMenuItemInventoryItem(quint32 inventoryItemId, float quantity) {
    MenuItemInventoryItem* item = new MenuItemInventoryItem(this, ++m_currentMenuItemInventoryItemId, m_menuCategoryId, m_id, inventoryItemId, quantity);
    addMenuItemInventoryItem(item);
    return item;
}

void MenuItem::addMenuItemInventoryItem(MenuItemInventoryItem *menuItemInventoryItem) {
    if(menuItemInventoryItem->property("id").toUInt() > m_currentMenuItemInventoryItemId) m_currentMenuItemInventoryItemId = menuItemInventoryItem->property("id").toUInt();

    m_menuItemInventoryItems.append(menuItemInventoryItem);
    Pos::instance()->appendToMenuHistory("AddMenuItemInventoryItem:" + menuItemInventoryItem->serialize());    
    connect(menuItemInventoryItem, SIGNAL(costChanged(float)),
            this, SLOT(fireCostChanged()));
    menuItemInventoryItemsChanged(menuItemInventoryItems());

    fireCostChanged();
}

QQmlListProperty<MenuItemInventoryItem> MenuItem::menuItemInventoryItems() {
    return QQmlListProperty<MenuItemInventoryItem>(this, m_menuItemInventoryItems);
}

QList<MenuItemInventoryItem*> MenuItem::menuItemInventoryItemsList() {
    return m_menuItemInventoryItems;
}

MenuItemInventoryItem* MenuItem::getMenuItemInventoryItem(quint32 id) {
    for(MenuItemInventoryItem* item : m_menuItemInventoryItems) {
        if(item->property("id").toUInt() == id){
            return item;
        }
    }
    return nullptr;
}


void MenuItem::removeMenuItemInventoryItem(quint32 menuItemInventoryItemId) {
    for(int i = 0; i < m_menuItemInventoryItems.length(); i++) {
        if(m_menuItemInventoryItems[i]->property("id").toUInt() == menuItemInventoryItemId) {
            MenuItemInventoryItem *item = m_menuItemInventoryItems[i];
            m_menuItemInventoryItems.removeAt(i);
            QStringList historyEntry;
            historyEntry << "RemoveMenuItemInventoryItem" << item->property("id").toString() << item->property("menuCategoryId").toString() << item->property("menuItemId").toString();
            Pos::instance()->appendToMenuHistory(serializeList(historyEntry));

            disconnect(item, SIGNAL(costChanged(float)),
                    this, SLOT(fireCostChanged()));

            menuItemInventoryItemsChanged(menuItemInventoryItems());

            fireCostChanged();
            return;
        }
    }
}




QString MenuItem::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << QString::number(m_menuCategoryId) << m_name << m_type << QString::number(m_price) << QString::number(m_isDisabled);
    return serializeList(vals);
}

MenuItem* MenuItem::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 id = split[0].toUInt();
    quint32 menuCategoryId = split[1].toUInt();
    QString name = split[2];
    QString type = split[3];
    float price = split[4].toFloat();
    bool isDisabled = false;
    if(split.length() > 5) {
        isDisabled = split[5].toInt();
    }

    MenuItem *obj = new MenuItem(parent, id, menuCategoryId, name, type, price, isDisabled);
    return obj;
}
