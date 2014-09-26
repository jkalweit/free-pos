#include <QMetaProperty>
#include <QDebug>
#include "MenuItem.h"

MenuItem::MenuItem(QObject *parent, quint32 id, quint32 menuCategoryId, QString name) :
    QObject(parent), m_id(id), m_menuCategoryId(menuCategoryId), m_name(name)
{
}

quint32 MenuItem::menuCategoryId() {
    return m_menuCategoryId;
}

QString MenuItem::serialize() const {
    return QString::number(m_id) + ":" + QString::number(m_menuCategoryId) + ":" + m_name;
}

MenuItem* MenuItem::deserialize(QString serialized, QObject *parent)
{
    QStringList split = serialized.split(":");

    quint32 id = split[0].toInt();
    quint32 menuCategoryId = split[1].toInt();
    QString name = split[2];

    MenuItem *obj = new MenuItem(parent, id, menuCategoryId, name);
    qDebug() << "    deserialized: " << obj->serialize();
    return obj;
}

QTextStream& operator<<(QTextStream& stream, const MenuItem& obj) {
    stream << obj.serialize() << endl;
    return stream;
}
QTextStream& operator>>(QTextStream& stream, MenuItem& obj) {

    QString line = stream.readAll();
    qDebug() << "Got line: " << line;
    if(line.length() <= 1){
        qDebug() << "Empty line.";
        return stream;
    }
    MenuItem* obj2 = MenuItem::deserialize(line);
    obj.m_id = obj2->m_id;
    obj.m_menuCategoryId = obj2->m_menuCategoryId;
    obj.m_name = obj2->m_name;

    return stream;
}


