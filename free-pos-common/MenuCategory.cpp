#include <QMetaProperty>
#include <QDebug>
#include "MenuCategory.h"

MenuCategory::MenuCategory(QObject *parent, quint32 id, QString name) :
    QObject(parent), m_id(id), m_name(name)
{
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
//    for(int i=0; i<obj.metaObject()->propertyCount(); ++i) {
//        if(obj.metaObject()->property(i).isStored(&obj)) {
//            stream << obj.metaObject()->property(i).name() << ":" << obj.metaObject()->property(i).read(&obj).toString() << "/";
//        }
//    }
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
    MenuCategory* cat = MenuCategory::deserialize(line);
    obj.m_id = cat->m_id;
    obj.m_name = cat->m_name;
    //obj.m
//    QVariant var;
//    for(int i=0; i<obj.metaObject()->propertyCount(); ++i) {
//        if(obj.metaObject()->property(i).isStored(&obj)) {
//            ds >> var;
//            obj.metaObject()->property(i).write(&obj, var);
//        }
//    }
    return stream;
}

