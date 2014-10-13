#include <QMetaProperty>
#include <QDebug>
#include "MenuItem.h"

MenuItem::MenuItem(QObject *parent, quint32 id, quint32 menuCategoryId, QString name, QString type, float price) :
    SimpleSerializable(parent), m_id(id), m_menuCategoryId(menuCategoryId), m_name(name), m_type(type), m_price(price)
{
}

QStringList MenuItem::updatePrefix() {
    return QStringList() << "UpdateMenuItem" << QString::number(m_id) << QString(m_menuCategoryId);
}

QString MenuItem::serialize() const {
    QStringList vals;
    vals << QString::number(m_id) << QString::number(m_menuCategoryId) << m_name << m_type << QString::number(m_price);
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

    MenuItem *obj = new MenuItem(parent, id, menuCategoryId, name, type, price);
    return obj;
}
