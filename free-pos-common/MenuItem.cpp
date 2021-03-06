#include "MenuItem.h"

#include <QMetaProperty>
#include <QDebug>
#include "Pos.h"

MenuItem::MenuItem(QObject *parent, quint32 id, quint32 menuCategoryId, QString name, QString type, float price, bool isDisabled, bool isHiddenFromKitchen, QString prepType) :
    SimpleSerializable(parent), m_id(id), m_menuCategoryId(menuCategoryId), m_name(name), m_type(type), m_price(price), m_isDisabled(isDisabled), m_currentMenuItemInventoryItemId(0), m_currentMenuItemOptionId(0), m_isHiddenFromKitchen(isHiddenFromKitchen), m_prepType(prepType)
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
        fireCostChanged();
    }
}

void MenuItem::setIsDisabled(bool isDisabled) {
    if(m_isDisabled != isDisabled) {
        m_isDisabled = isDisabled;
        logMenuPropertyChanged(m_isDisabled, "isDisabled");
        isDisabledChanged(m_isDisabled);
    }
}

void MenuItem::setPrepType(QString prepType) {
    if(m_prepType != prepType){
        m_prepType = prepType;
        logMenuPropertyChanged(m_prepType, "prepType");
        prepTypeChanged(m_prepType);
    }
}



bool MenuItem::hasInventory() {
    return m_menuItemInventoryItems.length() > 0;
}

float MenuItem::cost() {    

    float cost = costWithoutOptions();

    for(MenuItemOption *item : m_menuItemOptions) {
        cost += Pos::instance()->selectedMenu()->getMenuCategory(item->optionMenuCategoryId())->averageCost();
    }

    return cost;
}

float MenuItem::costWithoutOptions() {
    float cost = 0;

    for(MenuItemInventoryItem *item : m_menuItemInventoryItems) {
        cost += item->cost();
    }

    return cost;
}

float MenuItem::margin() {
    return m_price - cost();
}

bool MenuItem::isHiddenFromKitchen() {
    return m_isHiddenFromKitchen;
}

QString MenuItem::prepType() {
    return m_prepType;
}



void MenuItem::fireCostChanged() {
    costChanged(cost());
    marginChanged(margin());
}


float MenuItem::getCumulativeCostUpToOption(quint32 menuItemOptionId) {

    float cost = 0;

    for(MenuItemOption *item : m_menuItemOptions) {
        if(menuItemOptionId == item->id()) {
            return cost;
        }
        cost += Pos::instance()->selectedMenu()->getMenuCategory(item->optionMenuCategoryId())->averageCost();
    }

    // should only get this far when passing invalid id, such as -1 to get total option cost.
    return cost;
}


float MenuItem::getCumulativeCostUpToInventoryItem(quint32 inventoryItemId) {

    float cost = getCumulativeCostUpToOption(-1); // get cost of all options

    for(MenuItemInventoryItem *item : m_menuItemInventoryItems) {
        if(inventoryItemId == item->id()) {
            return cost;
        }
        cost += item->cost();
    }

    // should only get this far when passing invalid id, such as -1 to get total cost.
    return cost;
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

    hasInventoryChanged(hasInventory());
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

            hasInventoryChanged(hasInventory());
            fireCostChanged();
            return;
        }
    }
}






MenuItemOption* MenuItem::addMenuItemOption(quint32 optionMenuCategoryId) {
    MenuItemOption* item = new MenuItemOption(this, m_menuCategoryId, m_id, ++m_currentMenuItemOptionId, optionMenuCategoryId);
    addMenuItemOption(item);
    return item;
}

void MenuItem::addMenuItemOption(MenuItemOption *menuItemOption) {
    if(menuItemOption->id() > m_currentMenuItemOptionId) m_currentMenuItemOptionId = menuItemOption->id();

    m_menuItemOptions.append(menuItemOption);
    Pos::instance()->appendToMenuHistory("AddMenuItemOption:" + menuItemOption->serialize());
//    connect(menuItemInventoryItem, SIGNAL(costChanged(float)),
//            this, SLOT(fireCostChanged()));
    menuItemOptionsChanged(menuItemOptions());
    fireCostChanged();
}

QQmlListProperty<MenuItemOption> MenuItem::menuItemOptions() {
    return QQmlListProperty<MenuItemOption>(this, m_menuItemOptions);
}

QList<MenuItemOption*> MenuItem::menuItemOptionsList() {
    return m_menuItemOptions;
}

MenuItemOption* MenuItem::getMenuItemOption(quint32 id) {
    for(MenuItemOption* item : m_menuItemOptions) {
        if(item->id() == id){
            return item;
        }
    }
    return nullptr;
}

void MenuItem::removeMenuItemOption(quint32 menuItemOptionId) {
    for(int i = 0; i < m_menuItemOptions.length(); i++) {
        if(m_menuItemOptions[i]->id() == menuItemOptionId) {
            MenuItemOption *item = m_menuItemOptions[i];
            m_menuItemOptions.removeAt(i);
            QStringList historyEntry;
            historyEntry << "RemoveMenuItemOption" << item->path();
            Pos::instance()->appendToMenuHistory(serializeList(historyEntry));

//            disconnect(item, SIGNAL(costChanged(float)),
//                    this, SLOT(fireCostChanged()));

            menuItemOptionsChanged(menuItemOptions());

            //fireCostChanged();
            return;
        }
    }
}










QString MenuItem::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << QString::number(m_menuCategoryId) << m_name << m_type << QString::number(m_price) << QString::number(m_isDisabled) << QString::number(m_isHiddenFromKitchen) << m_prepType;
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
    bool isHiddenFromKitchen = false;
    if(split.length() > 6) {
        isHiddenFromKitchen = split[6].toInt();
    }

    QString prepType = "";
    if(split.length() > 7) {
        prepType = split[7];
    }

    MenuItem *obj = new MenuItem(parent, id, menuCategoryId, name, type, price, isDisabled, isHiddenFromKitchen, prepType);
    return obj;
}
