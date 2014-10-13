#include <QMetaProperty>
#include <QDebug>
#include "MenuCategory.h"
#include "Pos.h"

MenuCategory::MenuCategory(QObject *parent, quint32 id, QString name) :
    QObject(parent), m_id(id), m_name(name), m_currentMenuItemId(0)
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

QQmlListProperty<MenuItem> MenuCategory::menuItems() {
    return QQmlListProperty<MenuItem>(this, m_menuItems);
}

QString MenuCategory::serialize() const {
    return QString::number(m_id) + ":" + m_name;
}

MenuCategory* MenuCategory::deserialize(QString serialized, QObject *parent)
{
    QStringList split = serialized.split(":");

    quint32 id = split[0].toInt();
    QString name = split[1];

    MenuCategory *obj = new MenuCategory(parent, id, name);
    return obj;
}


