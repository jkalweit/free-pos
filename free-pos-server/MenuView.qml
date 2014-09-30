import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos

Rectangle {

    Column {
        id: menuItems
        visible: menu.selectedCategory
        anchors.right: menuCategories.left
        anchors.rightMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 2
        width: parent.width / 2
        spacing: 2

        Row {
            TextField {
                id: newMenuItemName
                maximumLength: 20
                width: menuItems.width - newMenuItemPrice.width
                placeholderText: qsTr("Menu item name")
                onAccepted: {
                    if(menu.selectedCategory) {
                        if(menu.selectedCategory.addMenuItem(newMenuItemName.text, "Food", newMenuItemPrice.text)) {
                            newMenuItemName.text = "";
                            newMenuItemPrice.text = "";
                        }
                    }
                }

                onActiveFocusChanged: {
                    if(this.focus){
                        this.selectAll();
                    }
                }
            }
            TextField {
                id: newMenuItemPrice
                width: 75
                placeholderText: qsTr("Price")
                onAccepted: {
                    if(menu.selectedCategory) {
                        if(menu.selectedCategory.addMenuItem(newMenuItemName.text, "Food", newMenuItemPrice.text)) {
                            newMenuItemName.text = "";
                            newMenuItemPrice.text = "";
                        }
                    }
                }

                onActiveFocusChanged: {
                    if(this.focus){
                        this.selectAll();
                    }
                }
            }
        }



        Repeater {
            model: menu.selectedCategory ? menu.selectedCategory.menuItems : 0

            Rectangle {
                id: menuItemContainer
                width: menuItems.width
                height: 25
                color:  "#DD66FF"
                Text {
                    text: modelData.name
                    color: "#000000"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Text {
                    text: modelData.price.toFixed(2)
                    color: "#000000"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        flash.start();
                        if(rec.selectedTicket) {
                            rec.selectedTicket.customers[0].addOrderItem(modelData.name, modelData.type, modelData.price, 1, "");
                        }
                    }
                }

                SequentialAnimation {
                    id: flash
                    PropertyAnimation { target: menuItemContainer; properties: "color"; to: "white"; duration: 25; }
                    PropertyAnimation { target: menuItemContainer; properties: "color"; to: "#DD66FF"; duration: 25; }
                }

            }
        }
    }

    Column {
        id: menuCategories
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 2
        width: parent.width / 2
        spacing: 2

        TextField {
            id: newMenuCategoryName
            maximumLength: 32
            width: parent.width
            placeholderText: qsTr("Category name")
            onAccepted: {
                menu.addCategory(newMenuCategoryName.text);
                newMenuCategoryName.text = ""
            }

            onActiveFocusChanged: {
                if(this.focus){
                    this.selectAll();
                }
            }
        }

        Repeater {
            model: menu.categories

            Rectangle {
                width: menuCategories.width
                height: 25
                color:  menu.selectedMenuCategory && menu.selectedMenuCategory.id == modelData.id ? "#DD66FF" : "#AA00DD"
                Text {
                    text: modelData.name
                    color: menu.selectedMenuCategory && menu.selectedMenuCategory.id == modelData.id ? "#000000" : "#DDDDDD"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        menu.selectedCategory = modelData
                    }
                }
            }
        }
    }

}
