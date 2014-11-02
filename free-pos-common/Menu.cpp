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

MenuCategory* Menu::getNextCategory(QString nameFilter) {
    bool foundSelected = false;
    MenuCategory *firstEnabled = nullptr;
    for(int i = 0; i < m_categories.length(); i++) {
        bool isDisabled = !m_categories[i]->property("name").toString().toUpper().contains(nameFilter.toUpper()) || m_categories[i]->property("isDisabled").toBool();
        if(!isDisabled) {
            if(!m_selectedCategory) {
                return m_categories[i];
            } else if(foundSelected) {
                return m_categories[i];
            } else if(!firstEnabled)
                firstEnabled = m_categories[i];
        }
        if(m_selectedCategory && m_categories[i]->property("id").toUInt() == m_selectedCategory->property("id").toUInt()) {
            foundSelected = true;
        }
    }

    // if we make it here, then just return first !isDisabled category, or nullptr
    return firstEnabled;
}

MenuCategory* Menu::getPreviousCategory(QString nameFilter) {
    bool foundSelected = false;
    MenuCategory *firstEnabled = nullptr;
    for(int i = m_categories.length() - 1; i >= 0 ; i--) {
        bool isDisabled = !m_categories[i]->property("name").toString().toUpper().contains(nameFilter.toUpper()) || m_categories[i]->property("isDisabled").toBool();
        if(!isDisabled) {
            if(!m_selectedCategory) {
                return m_categories[i];
            } else if(foundSelected) {
                return m_categories[i];
            } else if(!firstEnabled)
                firstEnabled = m_categories[i];
        }
        if(m_selectedCategory && m_categories[i]->property("id").toUInt() == m_selectedCategory->property("id").toUInt()) {
            foundSelected = true;
        }
    }

    // if we make it here, then just return first !isDisabled category, or nullptr
    return firstEnabled;
}
