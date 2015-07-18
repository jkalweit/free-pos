import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos

Rectangle {
    id: container
    visible: menu ? menu.selectedCategory : false
    color: "#33FFFFFF"

    signal menuItemSelected(var menuItem, var isNew)

    property var menu
    property bool editMode: false
    property alias newMenuItemName: newMenuItemName

    function selectCurrentItem() {
        if(container.menu.selectedCategory && container.menu.selectedCategory.selectedItem) {
            container.menuItemSelected(container.menu.selectedCategory.selectedItem);
        }
    }

    Keys.onDownPressed: container.menu.selectedCategory.selectedItem = container.menu.selectedCategory.getNextItem(newMenuItemName.text.trim())
    Keys.onUpPressed: container.menu.selectedCategory.selectedItem = container.menu.selectedCategory.getPreviousItem(newMenuItemName.text.trim())
    Keys.onEnterPressed: selectCurrentItem()

    Column {
        id: menuItemControls
        width: parent.width
        spacing: 2

        Row {
            TextField {
                id: newMenuItemName
                maximumLength: 20
                width: menuItemControls.width
                height: 50
                //width: menuItems.width - newMenuItemPrice.width
                placeholderText: qsTr("Menu item name")
                onAccepted: {
                    if(container.editMode && menu.selectedCategory) {
                        var item = menu.selectedCategory.addMenuItem(newMenuItemName.text, "Food", 0);
                        newMenuItemName.text = "";
                        console.log("added item: " + item.name);
                        container.menuItemSelected(item, true);
                    }
                    //menuItems.selectCurrentItem();
                }

                onActiveFocusChanged: {
                    if(this.focus){
                        this.selectAll();
                    }
                }
            }
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
        }
    }

    ListView {
        width: parent.width
        anchors.top: menuItemControls.bottom
        anchors.bottom: container.bottom
        model: menu && menu.selectedCategory ? menu.selectedCategory.menuItems : 0
        clip: true

        delegate: RectangleFlashButton {
            id: menuItemContainer
            width: container.width
            verticalMargin: 10
            border.color: menu.selectedCategory && menu.selectedCategory.selectedItem && (menu.selectedCategory.selectedItem.id === modelData.id) ? "#DDDDDD" : "#777777"
            border.width: 2
            color:  modelData.isDisabled ? "#AAAAAA" : "#9575cd"
            flashColor: "#FFFFFF"

            visible: {
                if(!container.editMode && modelData.isDisabled)
                    return false;
                var filter = newMenuItemName.text.trim().toUpperCase();
                if(filter.length === 0){
                    return true;
                }
                return modelData.name.toUpperCase().indexOf(filter) > -1;
            }

            hidden: !container.editMode && modelData.isDisabled;

            onBeforeFlash: {
                newMenuItemName.text = "";
                container.menu.selectedCategory.selectedItem = modelData;
                container.menuItemSelected(modelData, false);
            }


            customContent: Item {
                anchors.fill: parent
                Text {
                    id: menuItemName
                    text: modelData.name
                    color: "#FFFFFF" //modelData.hasInventory ? "#FFFFFF" : "#DD0000"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    //anchors.leftMargin: 5
                }
                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    Text {
                        text: modelData.price.toFixed(2)
                        anchors.right: parent.right
                        horizontalAlignment: Text.AlignRight
                        color: "#000000"
                    }
//                    Text {
//                        text: modelData.cost.toFixed(2)
//                        anchors.right: parent.right
//                        horizontalAlignment: Text.AlignRight
//                        color: {
//                            var priceRatio = modelData.cost / modelData.price;
//                            if (priceRatio > 1 || priceRatio < 0) // negative price ratio is because of negative price, ie discount
//                                priceRatio = 1;
//                            return Qt.rgba(priceRatio, 0.1, 0.1, 1);
//                        }
//                    }
//                    Text {
//                        text: modelData.margin.toFixed(2)
//                        anchors.right: parent.right
//                        horizontalAlignment: Text.AlignRight
//                        color: {
//                            var priceRatio = modelData.margin / modelData.price;
//                            var marginRatio = modelData.margin / 7;
//                            var green = priceRatio > marginRatio ? priceRatio : marginRatio;
//                            if (green > 1)
//                                green = 1;
//                            return Qt.rgba(0.1, green, 0.1, 1);
//                        }
//                    }
                }
            }
        }


    }
}
