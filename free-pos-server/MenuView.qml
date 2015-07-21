import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos

Rectangle {
    id: container
    color: "transparent"
    property var menu
    property bool editMode: false
    signal menuItemSelected(var menuItem, var isNew)
    signal menuCategorySelected(var menuCategory, var isNew)

    MenuItemsView {
        id: menuItemsView
        menu: container.menu
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2
        editMode: container.editMode
        onMenuItemSelected: container.menuItemSelected(menuItem, isNew)
    }

    MenuCategoriesView {
        menu: container.menu
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2
        editMode: container.editMode
        onMenuCategorySelected: {
            menuItemsView.newMenuItemName.forceActiveFocus();
            container.menuCategorySelected(menuCategory, isNew);
        }
    }
}
