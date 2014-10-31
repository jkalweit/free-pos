#include <QMetaProperty>
#include <QDebug>
#include "MenuCategory.h"
#include "Pos.h"

MenuCategory::MenuCategory(QObject *parent, quint32 id, QString name, bool isDisabled) :
    SimpleSerializable(parent), m_id(id), m_name(name), m_currentMenuItemId(0), m_isDisabled(isDisabled)
{
}

QStringList MenuCategory::updatePrefix() {
    return QStringList() << "UpdateMenuCategory" << QString::number(m_id);
}

MenuItem* MenuCategory::addMenuItem(QString name, QString type, float price) {
    MenuItem* item = new MenuItem(this, ++m_currentMenuItemId, m_id, name, type, price);
    addMenuItem(item);
    return item;
}

void MenuCategory::addMenuItem(MenuItem *menuItem) {
    m_menuItems.append(menuItem);
    if(menuItem->property("id").toUInt() > m_currentMenuItemId)
        m_currentMenuItemId = menuItem->property("id").toUInt();
    Pos::instance()->appendToMenuHistory("AddMenuItem:" + menuItem->serialize());
    menuItemsChanged(menuItems());
}

MenuItem* MenuCategory::getMenuItem(quint32 id) {
    for(MenuItem *item: m_menuItems) {
        if(item->property("id").toUInt() == id) {
            return item;
        }
    }
    return nullptr;
}


QQmlListProperty<MenuItem> MenuCategory::menuItems() {
    return QQmlListProperty<MenuItem>(this, m_menuItems);
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


