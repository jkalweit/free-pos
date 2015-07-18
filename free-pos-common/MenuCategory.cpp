#include <QMetaProperty>
#include <QDebug>
#include "MenuCategory.h"
#include "Pos.h"

MenuCategory::MenuCategory(QObject *parent, quint32 id, QString name, bool isDisabled) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_currentMenuItemId(0), m_isDisabled(isDisabled), m_selectedItem(nullptr)
{
}

QStringList MenuCategory::updatePrefix() {
    return QStringList() << "UpdateMenuCategory" << QString::number(m_id);
}

float MenuCategory::averageCost() {

    float cost = 0;
    float count = 0;

    for(MenuItem *item : m_menuItems) {
        if(!item->property("isDisabled").toBool()) {
            cost += item->costWithoutOptions();
            count++;
        }
    }

    return count > 0 ? cost / count : 0;
}

void MenuCategory::fireMenuItemsChanged() {
    averageCostChanged(averageCost());
    menuItemsChanged(menuItems());
}

MenuItem* MenuCategory::addMenuItem(QString name, QString type, float price) {
    MenuItem* item = new MenuItem(this, ++m_currentMenuItemId, m_id, name, type, price);
    addMenuItem(item);
    return item;
}

void MenuCategory::addMenuItem(MenuItem *menuItem) {
    m_menuItems.append(menuItem);
    if(menuItem->property("id").toUInt() > m_currentMenuItemId) {
        m_currentMenuItemId = menuItem->property("id").toUInt();
    }

    connect(menuItem, SIGNAL(costChanged(float)),
            this, SLOT(fireMenuItemsChanged()));
    connect(menuItem, SIGNAL(isDisabledChanged(bool)),
            this, SLOT(fireMenuItemsChanged()));

    Pos::instance()->appendToMenuHistory("AddMenuItem:" + menuItem->serialize());
    fireMenuItemsChanged();
}

MenuItem* MenuCategory::getMenuItem(quint32 id) {
    for(MenuItem *item: m_menuItems) {
        if(item->property("id").toUInt() == id) {
            return item;
        }
    }
    return nullptr;
}


bool compareMenuItems(MenuItem *a, MenuItem *b) {
    return a->property("name").toString() < b->property("name").toString();
}

QQmlListProperty<MenuItem> MenuCategory::menuItems() {
    std::sort(m_menuItems.begin(), m_menuItems.end(), compareMenuItems);
    return QQmlListProperty<MenuItem>(this, m_menuItems);
}

MenuItem* MenuCategory::selectedItem() {
    return m_selectedItem;
}

void MenuCategory::setSelectedItem(MenuItem *item) {
    if(m_selectedItem != item) {
        m_selectedItem = item;
        selectedItemChanged(m_selectedItem);
    }
}

MenuItem* MenuCategory::getNextItem(QString nameFilter) {
    bool foundSelected = false;
    MenuItem *firstEnabled = nullptr;
    for(int i = 0; i < m_menuItems.length(); i++) {
        bool isDisabled = !m_menuItems[i]->property("name").toString().toUpper().contains(nameFilter.toUpper()) || m_menuItems[i]->property("isDisabled").toBool();
        if(!isDisabled) {
            if(!m_selectedItem) {
                return m_menuItems[i];
            } else if(foundSelected) {
                return m_menuItems[i];
            } else if(!firstEnabled)
                firstEnabled = m_menuItems[i];
        }
        if(m_selectedItem && (m_menuItems[i]->property("id").toUInt() == m_selectedItem->property("id").toUInt())) {
            foundSelected = true;
        }
    }

    // if we make it here, then just return first !isDisabled item, or nullptr
    return firstEnabled;
}

MenuItem* MenuCategory::getPreviousItem(QString nameFilter) {
    bool foundSelected = false;
    MenuItem *firstEnabled = nullptr;
    for(int i = m_menuItems.length() - 1; i >= 0 ; i--) {
        bool isDisabled = !m_menuItems[i]->property("name").toString().toUpper().contains(nameFilter.toUpper()) || m_menuItems[i]->property("isDisabled").toBool();
        if(!isDisabled) {
            if(!m_selectedItem) {
                return m_menuItems[i];
            } else if(foundSelected) {
                return m_menuItems[i];
            } else if(!firstEnabled)
                firstEnabled = m_menuItems[i];
        }
        if(m_selectedItem && (m_menuItems[i]->property("id").toUInt() == m_selectedItem->property("id").toUInt())) {
            foundSelected = true;
        }
    }

    // if we make it here, then just return first !isDisabled item, or nullptr
    return firstEnabled;
}





void MenuCategory::setName(QString name) {
    if(m_name != name.trimmed()) {
        m_name = name.trimmed();
        logMenuPropertyChanged(m_name, "name");
        nameChanged(m_name);
    }
}

void MenuCategory::setIsDisabled(bool isDisabled) {
    if(m_isDisabled != isDisabled) {
        m_isDisabled = isDisabled;
        logMenuPropertyChanged(m_isDisabled, "isDisabled");
        isDisabledChanged(m_isDisabled);
    }
}

QString MenuCategory::serialize() const {
    return serializeList(QStringList() << QString::number(m_id) << m_name << QString::number(m_isDisabled));
}

MenuCategory* MenuCategory::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 id = split[0].toInt();
    QString name = split[1];
    bool isDisabled = false;
    if(split.length() > 2) {
        isDisabled = split[2].toInt();
    }

    MenuCategory *obj = new MenuCategory(parent, id, name, isDisabled);
    return obj;
}


