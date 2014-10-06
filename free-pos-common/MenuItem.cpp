#include <QMetaProperty>
#include <QDebug>
#include "MenuItem.h"

MenuItem::MenuItem(QObject *parent, quint32 id, QString name, QString type, float price) :
    QObject(parent), m_id(id), m_name(name), m_type(type), m_price(price)
{
}

QString MenuItem::serialize() const {
    //m_name.replace(":", "");
    return QString::number(m_id) + ":" + m_name + ":" + m_type + ":" + QString::number(m_price);
}

MenuItem* MenuItem::deserialize(QString serialized, QObject *parent)
{
    QStringList split = serialized.split(":");

    quint32 id = split[0].toInt();
    QString name = split[1];
    QString type = split[2];
    float price = split[3].toFloat();

    MenuItem *obj = new MenuItem(parent, id, name, type, price);
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
    obj.m_name = obj2->m_name;
    obj.m_type = obj2->m_type;
    obj.m_price = obj2->m_price;

    return stream;
}


