#ifndef MENUCATEGORY_H
#define MENUCATEGORY_H

#include <QObject>
#include <QQmlListProperty>
#include "SimpleSerializable.h"
#include "MenuItem.h"

class MenuCategory : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id NOTIFY idChanged)
    Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<MenuItem> menuItems READ menuItems NOTIFY menuItemsChanged)
    Q_PROPERTY(bool isDisabled MEMBER m_isDisabled WRITE setIsDisabled NOTIFY isDisabledChanged)
    Q_PROPERTY(MenuItem *selectedItem READ selectedItem WRITE setSelectedItem NOTIFY selectedItemChanged)
public:
    explicit MenuCategory(QObject *parent = 0, quint32 id = 0, QString name = "", bool isDisabled = false);

    virtual QStringList updatePrefix();

    QQmlListProperty<MenuItem> menuItems();
    Q_INVOKABLE MenuItem* addMenuItem(QString name, QString type, float price);
    void addMenuItem(MenuItem *menuItem);
    MenuItem* getMenuItem(quint32 id);
    MenuItem* selectedItem();
    Q_INVOKABLE MenuItem* getNextItem(QString nameFilter);
    Q_INVOKABLE MenuItem* getPreviousItem(QString nameFilter);
    void setSelectedItem(MenuItem *item);

    void setName(QString name);
    void setIsDisabled(bool isDisabled);

    QString serialize() const;
    static MenuCategory* deserialize(QString serialized, QObject *parent = 0);

signals:
    void idChanged(quint32);
    void nameChanged(QString);
    void menuItemsChanged(QQmlListProperty<MenuItem>);
    void isDisabledChanged(bool);
    void selectedItemChanged(MenuItem*);

public slots:

private:
    quint32 m_id;
    QString m_name;
    quint32 m_currentMenuItemId;
    QList<MenuItem*> m_menuItems;
    bool m_isDisabled;
    MenuItem *m_selectedItem;
};

#endif // MENUCATEGORY_H
