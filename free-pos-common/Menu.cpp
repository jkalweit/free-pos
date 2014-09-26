#include "Menu.h"

#include <QDebug>

Menu::Menu(QObject *parent) :
    QObject(parent), m_selectedCategory(nullptr)
{
}

void Menu::addCategory(MenuCategory *category) {
    m_categories.append(category);
    categoriesChanged(categories());
}

void Menu::addItem(MenuItem* item) {
    for(int i = 0; i < m_categories.size(); i++)
    {
        uint id = m_categories[i]->property("id").toUInt();
        qDebug() << "Comparing: " << m_categories[i]->property("name").toString() << ": " << id << " to " << item->menuCategoryId();
        if(id == item->menuCategoryId()) {
            m_categories[i]->addMenuItem(item);
            break;
        }
    }
    categoriesChanged(categories());
}

QQmlListProperty<MenuCategory> Menu::categories() {
    return QQmlListProperty<MenuCategory>(this, m_categories);
}

MenuCategory* Menu::selectedCategory() {
    return m_selectedCategory;
}

void Menu::setSelectedCategory(MenuCategory *category) {
    m_selectedCategory = category;
    selectedCategoryChanged(m_selectedCategory);
}
