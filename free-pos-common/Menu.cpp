#include "Menu.h"

#include <QDebug>

Menu::Menu(QObject *parent) :
    QObject(parent), m_selectedCategory(nullptr), m_currentCategoryId(0)
{
}

MenuCategory* Menu::addCategory(QString name) {
    MenuCategory *category = new MenuCategory(this, ++m_currentCategoryId, name);
    addCategory(category);
    return category;
}

void Menu::addCategory(MenuCategory *category) {
    m_categories.append(category);
    categoriesChanged(categories());
}


QQmlListProperty<MenuCategory> Menu::categories() {
    return QQmlListProperty<MenuCategory>(this, m_categories);
}

MenuCategory* Menu::selectedCategory() {
    return m_selectedCategory;
}

void Menu::setSelectedCategory(MenuCategory *category) {
    if(m_selectedCategory != category) {
        m_selectedCategory = category;
        selectedCategoryChanged(m_selectedCategory);
    }
}
