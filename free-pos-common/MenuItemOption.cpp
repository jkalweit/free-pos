#include "MenuItemOption.h"

MenuItemOption::MenuItemOption(QObject *parent, quint32 menuCategoryId, quint32 menuItemId, quint32 id, QString name) :
    SimpleSerializable(parent), m_menuCategoryId(menuCategoryId), m_menuItemId(menuItemId), m_id(id), m_name(name)
{
}

