#ifndef MENUCATEGORY_H
#define MENUCATEGORY_H

#include <QTextStream>
#include <QObject>
#include <QQmlListProperty>
#include "MenuItem.h"

class MenuCategory : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<MenuItem> menuItems READ menuItems NOTIFY menuItemsChanged)
public:
    explicit MenuCategory(QObject *parent = 0, quint32 id = 0, QString name = "");

    QQmlListProperty<MenuItem> menuItems();
    Q_INVOKABLE MenuItem* addMenuItem(QString name, QString type, float price);
    void addMenuItem(MenuItem *menuItem);

    QString serialize() const;
    static MenuCategory* deserialize(QString serialized, QObject *parent = 0);

    friend QTextStream& operator<<(QTextStream& stream, const MenuCategory& obj);
    friend QTextStream& operator>>(QTextStream& stream, MenuCategory& obj);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void menuItemsChanged(QQmlListProperty<MenuItem>);

public slots:

private:
    quint32 m_id;
    QString m_name;
    quint32 m_currentMenuItemId;
    QList<MenuItem*> m_menuItems;    
};

#endif // MENUCATEGORY_H
