#ifndef MENUITEMOPTION_H
#define MENUITEMOPTION_H

#include <QObject>
#include "SimpleSerializable.h"

class MenuItemOption : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
public:
    explicit MenuItemOption(QObject *parent = 0, quint32 menuCategoryId = 0, quint32 menuItemId = 0, quint32 id = 0, QString name = "");

    virtual QStringList updatePrefix();

    void setName(QString name);

    QString serialize() const;
    static MenuItemOption* deserialize(QString serialized, QObject *parent = 0);

signals:
    void nameChanged(quint32);

public slots:

private:
    quint32 m_menuCategoryId;
    quint32 m_menuItemId;
    quint32 m_id;
    QString m_name;
};

#endif // MENUITEMOPTION_H
