#include "Menu.h"

#include <QDebug>
#include "Pos.h"

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
    if(category->property("id").toUInt() > m_currentCategoryId)
        m_currentCategoryId = category->property("id").toUInt();
    Pos::instance()->appendToMenuHistory("AddMenuCategory:" + category->serialize());
    categoriesChanged(categories());
}

MenuCategory* Menu::getMenuCategory(quint32 id) {
    for(MenuCategory *category : m_categories) {
        if(category->property("id").toUInt() == id) {
            return category;
        }
    }
    return nullptr;
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
