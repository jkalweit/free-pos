#ifndef MENUITEM_H
#define MENUITEM_H

#include <QTextStream>
#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"

class MenuItem : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type MEMBER m_type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(float price MEMBER m_price WRITE setPrice NOTIFY priceChanged)
    Q_PROPERTY(bool isDisabled MEMBER m_isDisabled WRITE setIsDisabled NOTIFY isDisabledChanged)
public:
    explicit MenuItem(QObject *parent = 0, quint32 id = 0, quint32 m_menuCategoryId = 0, QString name = "", QString type = "", float price = 0, bool isDisabled = false);

    virtual QStringList updatePrefix();

    quint32 menuCategoryId();
    void setName(QString name);
    void setType(QString type);
    void setPrice(float price);
    void setIsDisabled(bool isDisabled);

    QString serialize() const;
    static MenuItem* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void typeChanged(QString);
    void priceChanged(float);
    void isDisabledChanged(bool);

public slots:

private:
    quint32 m_id;
    quint32 m_menuCategoryId;
    QString m_name;
    QString m_type;
    float m_price;
    bool m_isDisabled;
};

#endif // MENUITEM_H
