import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos

Rectangle {
    id: container
    color: "transparent"
    property var menu
    property bool editMode: false
    signal menuItemSelected(var menuItem)
    signal menuCategorySelected(var menuCategory)

    Rectangle {
        id: menuItems
        visible: menu ? menu.selectedCategory : false
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2
        color: "#33FFFFFF"

//        Column {
//            id: menuItemControls
//            width: parent.width
//            spacing: 2

//            Row {
//                TextField {
//                    id: newMenuItemName
//                    maximumLength: 20
//                    width: menuItems.width - newMenuItemPrice.width
//                    placeholderText: qsTr("Menu item name")
//                    onAccepted: {
//                        if(menu.selectedCategory) {
//                            if(menu.selectedCategory.addMenuItem(newMenuItemName.text, "Food", newMenuItemPrice.text)) {
//                                newMenuItemName.text = "";
//                                newMenuItemPrice.text = "";
//                            }
//                        }
//                    }

//                    onActiveFocusChanged: {
//                        if(this.focus){
//                            this.selectAll();
//                        }
//                    }
//                }
//                TextField {
//                    id: newMenuItemPrice
//                    width: 75
//                    placeholderText: qsTr("Price")
//                    onAccepted: {
//                        if(menu.selectedCategory) {
//                            if(menu.selectedCategory.addMenuItem(newMenuItemName.text, "Food", newMenuItemPrice.text)) {
//                                newMenuItemName.text = "";
//                                newMenuItemPrice.text = "";
//                            }
//                        }
//                    }

//                    onActiveFocusChanged: {
//                        if(this.focus){
//                            this.selectAll();
//                        }
//                    }
//                }
//            }
//        }

        ListView {
            width: parent.width
            anchors.top: parent.top
            anchors.bottom: menuItems.bottom
            model: menu && menu.selectedCategory ? menu.selectedCategory.menuItems : 0
            clip: true

            delegate: RectangleFlash {
                id: menuItemContainer
                width: menuItems.width
                height: menuItemName.height + 40
                color:  "#9575cd"
                flashColor: "#FFFFFF"
                border.width: 1
                border.color: "#777777"

                onBeforeFlash: {
                    container.menuItemSelected(modelData);
                }


                customContent: Item {
                    anchors.fill: parent
                    Text {
                        id: menuItemName
                        text: modelData.name
                        color: "#FFFFFF"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        //anchors.leftMargin: 5
                    }
                    Text {
                        text: modelData.price.toFixed(2)
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        //anchors.rightMargin: 5
                    }
                }
            }


        }
    }

    Rectangle {
        id: menuCategories
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2
        color: "#33FFFFFF"

        Column {
            id: menuCategoryControls
            width: parent.width
            spacing: 2

            TextField {
                id: newMenuCategoryName
                maximumLength: 32
                width: parent.width
                placeholderText: qsTr("Category name")
                onAccepted: {
                    if(container.editMode) {
                        menu.addCategory(newMenuCategoryName.text);
                        newMenuCategoryName.text = "";
                    }
                }

                onActiveFocusChanged: {
                    if(this.focus){
                        this.selectAll();
                    }
                }
            }
        }

        ListView {
            width: parent.width
            anchors.top: menuCategoryControls.bottom
            anchors.bottom: menuCategories.bottom
            model: container.menu ? container.menu.categories : 0
            clip: true

            delegate: RectangleFlashButton {
                visible: {
                    if(!container.editMode && modelData.isDisabled)
                        return false;
                    var filter = newMenuCategoryName.text.trim().toUpperCase()
                    if(filter.length === 0){
                        return true;
                    }
                    return modelData.name.toUpperCase().indexOf(filter) > -1;
                }

                color: modelData.isDisabled ? "#AAAAAA" : "#7e57c2"
                border.color: menu.selectedCategory && (menu.selectedCategory.id === modelData.id) ? "#DDDDDD" : "#777777"
                border.width: 2
                textColor: menu.selectedCategory && (menu.selectedCategory.id === modelData.id) ? "#DDDDDD" : "#000000"
                flashColor: "#FFFFFF"
                text: modelData.name
                onBeforeFlash: {
                    menu.selectedCategory = modelData;
                }

                onClicked: menuCategorySelected(modelData);
            }
        }
    }
}
