#ifndef MENU_H
#define MENU_H

#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include "MenuCategory.h"
#include "MenuItem.h"

class Menu : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<MenuCategory> categories READ categories NOTIFY categoriesChanged)
    Q_PROPERTY(MenuCategory *selectedCategory READ selectedCategory WRITE setSelectedCategory NOTIFY selectedCategoryChanged)
public:
    explicit Menu(QObject *parent = 0);

    Q_INVOKABLE MenuCategory* addCategory(QString name);
    void addCategory(MenuCategory *category);
    QQmlListProperty<MenuCategory> categories();

    MenuCategory* selectedCategory();
    void setSelectedCategory(MenuCategory *category);
    MenuCategory* getMenuCategory(quint32 id);

signals:
    void categoriesChanged(QQmlListProperty<MenuCategory>);
    void selectedCategoryChanged(MenuCategory*);

private:
    QList<MenuCategory*> m_categories;
    MenuCategory *m_selectedCategory;
    quint32 m_currentCategoryId;
};

#endif // MENU_H
