#ifndef MENUITEMOPTION_H
#define MENUITEMOPTION_H

#include <QObject>
#include "SimpleSerializable.h"
//#include "MenuCategory.h"

class MenuItemOption : public SimpleSerializable
{
    Q_OBJECT
    Q_PROPERTY(quint32 id MEMBER m_id READ id NOTIFY idChanged)
    //Q_PROPERTY(QString name MEMBER m_name WRITE setName NOTIFY nameChanged)
    //Q_PROPERTY(MenuCategory* optionMenuCategory READ optionMenuCategory WRITE setOptionMenuCategory NOTIFY optionMenuCategoryChanged)
    Q_PROPERTY(quint32 optionMenuCategoryId MEMBER m_optionMenuCategoryId READ optionMenuCategoryId NOTIFY optionMenuCategoryIdChanged)
public:
    explicit MenuItemOption(QObject *parent = 0, quint32 menuCategoryId = 0, quint32 menuItemId = 0, quint32 id = 0, quint32 optionMenuCategoryId = 0); // , QString name = "");

    QStringList path();
    virtual QStringList updatePrefix();

    quint32 menuCategoryId();
    quint32 menuItemId();
    quint32 id();
    quint32 optionMenuCategoryId();

//    MenuCategory *optionMenuCategory();
//    void setOptionMenuCategory(MenuCategory *optionMenuCategory);

    //void setName(QString name);

    QString serialize() const;
    static MenuItemOption* deserialize(QString serialized, QObject *parent = 0);

signals:
    void optionMenuCategoryIdChanged(quint32);
    void idChanged(quint32);
    //void nameChanged(QString);
    //void optionMenuCategoryChanged(MenuCategory*);

public slots:

private:
    quint32 m_menuCategoryId;
    quint32 m_menuItemId;
    quint32 m_id;
    QString m_name;
    quint32 m_optionMenuCategoryId;

    //MenuCategory *m_optionMenuCategory;
};

#endif // MENUITEMOPTION_H
