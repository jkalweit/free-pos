#include "MenuItemOption.h"

#include <QMetaProperty>

MenuItemOption::MenuItemOption(QObject *parent, quint32 menuCategoryId, quint32 menuItemId, quint32 id, quint32 optionMenuCategoryId) :
    SimpleSerializable(parent), m_menuCategoryId(menuCategoryId), m_menuItemId(menuItemId), m_id(id), m_optionMenuCategoryId(optionMenuCategoryId) //, m_name(name), m_optionMenuCategory(nullptr)
{
}

QStringList MenuItemOption::path() {
    return QStringList() << QString::number(m_menuCategoryId) << QString::number(m_menuItemId) << QString::number(m_id);
}

QStringList MenuItemOption::updatePrefix() {
    return QStringList() << "UpdateMenuItemOption" << path();
}

quint32 MenuItemOption::menuCategoryId() {
    return m_menuCategoryId;
}

quint32 MenuItemOption::menuItemId() {
    return m_menuItemId;
}

quint32 MenuItemOption::id() {
    return m_id;
}

quint32 MenuItemOption::optionMenuCategoryId() {
    return m_optionMenuCategoryId;
}

//MenuCategory* MenuItemOption::optionMenuCategory() {
//    return m_optionMenuCategory;
//}

//void MenuItemOption::setOptionMenuCategory(MenuItem *optionMenuCategory) {
//    if(m_optionMenuCategory != optionMenuCategory) {
//        m_optionMenuCategory = optionMenuCategory;
//        optionMenuCategoryChanged(m_optionMenuCategory);
//    }
//}

//void MenuItemOption::setName(QString name) {
//    if(m_name != name.trimmed()) {
//        m_name = name.trimmed();
//        logMenuPropertyChanged(m_name, "name");
//        nameChanged(m_name);
//    }
//}




QString MenuItemOption::serialize() const {
    QStringList vals;
    vals << QString::number(m_menuCategoryId) << QString::number(m_menuItemId) << QString::number(m_id) << QString::number(m_optionMenuCategoryId);
    return serializeList(vals);
}

MenuItemOption* MenuItemOption::deserialize(QString serialized, QObject *parent)
{
    QStringList split = deserializeList(serialized);

    quint32 menuCategoryId = split[0].toUInt();
    quint32 menuItemId = split[1].toUInt();
    quint32 id = split[2].toUInt();
    quint32 optionMenuCategoryId = split[3].toUInt();
    //QString name = split[3];

    MenuItemOption *obj = new MenuItemOption(parent, menuCategoryId, menuItemId, id, optionMenuCategoryId);
    return obj;
}
