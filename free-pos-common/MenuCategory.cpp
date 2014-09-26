#include <QMetaProperty>
#include <QDebug>
#include "MenuCategory.h"

MenuCategory::MenuCategory(QObject *parent, quint32 id, QString name) :
    QObject(parent), m_id(id), m_name(name)
{
}

void MenuCategory::addMenuItem(MenuItem *menuItem) {
    m_menuItems.append(menuItem);
    menuItemsChanged(menuItems());
}

QQmlListProperty<MenuItem> MenuCategory::menuItems() {
    qDebug() << "MenuItems count: " << m_menuItems.size();
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
    qDebug() << "    deserialized: " << obj->serialize();
    return obj;
}

QTextStream& operator<<(QTextStream& stream, const MenuCategory& obj) {
    stream << obj.serialize() << endl;
    return stream;
}
QTextStream& operator>>(QTextStream& stream, MenuCategory& obj) {

    QString line = stream.readAll();
    qDebug() << "Got line: " << line;
    if(line.length() <= 1){
        qDebug() << "Empty line.";
        return stream;
    }
    MenuCategory* obj2 = MenuCategory::deserialize(line);
    obj.m_id = obj2->m_id;
    obj.m_name = obj2->m_name;

    return stream;
}

