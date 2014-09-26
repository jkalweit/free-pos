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

    void addCategory(MenuCategory *category);
    QQmlListProperty<MenuCategory> categories();

    void addItem(MenuItem* item);

    MenuCategory* selectedCategory();
    void setSelectedCategory(MenuCategory *category);

signals:
    void categoriesChanged(QQmlListProperty<MenuCategory>);
    void selectedCategoryChanged(MenuCategory*);

private:
    QList<MenuCategory*> m_categories;
    MenuCategory *m_selectedCategory;
};

#endif // MENU_H
