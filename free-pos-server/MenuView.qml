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

//    Rectangle {
//        id: menuItems
//        visible: menu ? menu.selectedCategory : false
//        anchors.left: parent.left
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        width: parent.width / 2
//        color: "#33FFFFFF"

//        function selectCurrentItem() {
//            if(container.menu.selectedCategory && container.menu.selectedCategory.selectedItem) {
//                container.menuItemSelected(container.menu.selectedCategory.selectedItem);
//            }
//        }

//        Keys.onDownPressed: container.menu.selectedCategory.selectedItem = container.menu.selectedCategory.getNextItem(newMenuItemName.text.trim())
//        Keys.onUpPressed: container.menu.selectedCategory.selectedItem = container.menu.selectedCategory.getPreviousItem(newMenuItemName.text.trim())
//        Keys.onEnterPressed: selectCurrentItem()

//        Column {
//            id: menuItemControls
//            width: parent.width
//            spacing: 2

//            Row {
//                TextField {
//                    id: newMenuItemName
//                    maximumLength: 20
//                    width: menuItemControls.width
//                    height: 50
//                    //width: menuItems.width - newMenuItemPrice.width
//                    placeholderText: qsTr("Menu item name")
//                    onAccepted: {
//                        if(container.editMode && menu.selectedCategory) {
//                            var item = menu.selectedCategory.addMenuItem(newMenuItemName.text, "Food", 0);
//                            newMenuItemName.text = "";
//                            console.log("added item: " + item.name);
//                            container.menuItemSelected(item, true);
//                        }
//                        //menuItems.selectCurrentItem();
//                    }

//                    onActiveFocusChanged: {
//                        if(this.focus){
//                            this.selectAll();
//                        }
//                    }
//                }
////                TextField {
////                    id: newMenuItemPrice
////                    width: 75
////                    placeholderText: qsTr("Price")
////                    onAccepted: {
////                        if(menu.selectedCategory) {
////                            if(menu.selectedCategory.addMenuItem(newMenuItemName.text, "Food", newMenuItemPrice.text)) {
////                                newMenuItemName.text = "";
////                                newMenuItemPrice.text = "";
////                            }
////                        }
////                    }

////                    onActiveFocusChanged: {
////                        if(this.focus){
////                            this.selectAll();
////                        }
////                    }
////                }
//            }
//        }

//        ListView {
//            width: parent.width
//            anchors.top: menuItemControls.bottom
//            anchors.bottom: menuItems.bottom
//            model: menu && menu.selectedCategory ? menu.selectedCategory.menuItems : 0
//            clip: true

//            delegate: RectangleFlash {
//                id: menuItemContainer
//                width: menuItems.width

//                height: menuItemName.height + 40
//                border.color: menu.selectedCategory && menu.selectedCategory.selectedItem && (menu.selectedCategory.selectedItem.id === modelData.id) ? "#DDDDDD" : "#777777"
//                border.width: 2
//                color:  modelData.isDisabled ? "#AAAAAA" : "#9575cd"
//                flashColor: "#FFFFFF"

//                visible: {
//                    if(!container.editMode && modelData.isDisabled)
//                        return false;
//                    var filter = newMenuItemName.text.trim().toUpperCase();
//                    if(filter.length === 0){
//                        return true;
//                    }
//                    return modelData.name.toUpperCase().indexOf(filter) > -1;
//                }

//                onBeforeFlash: {
//                    newMenuItemName.text = "";
//                    container.menu.selectedCategory.selectedItem = modelData;
//                    container.menuItemSelected(modelData, false);
//                }


//                customContent: Item {
//                    anchors.fill: parent
//                    Text {
//                        id: menuItemName
//                        text: modelData.name
//                        color: "#FFFFFF"
//                        anchors.verticalCenter: parent.verticalCenter
//                        anchors.left: parent.left
//                        //anchors.leftMargin: 5
//                    }
//                    Column {
//                        anchors.verticalCenter: parent.verticalCenter
//                        anchors.right: parent.right
//                        Text {
//                            text: modelData.price.toFixed(2)
//                            anchors.right: parent.right
//                            horizontalAlignment: Text.AlignRight
//                            color: "#000000"
//                        }
//                        Text {
//                            text: modelData.cost.toFixed(2)
//                            anchors.right: parent.right
//                            horizontalAlignment: Text.AlignRight
//                            color: {
//                                var priceRatio = modelData.cost / modelData.price;
//                                if (priceRatio > 1 || priceRatio < 0) // negative price ratio is because of negative price, ie discount
//                                    priceRatio = 1;
//                                return Qt.rgba(priceRatio, 0.1, 0.1, 1);
//                            }
//                        }
//                        Text {
//                            text: modelData.margin.toFixed(2)
//                            anchors.right: parent.right
//                            horizontalAlignment: Text.AlignRight
//                            color: {
//                                var priceRatio = modelData.margin / modelData.price;
//                                var marginRatio = modelData.margin / 7;
//                                var green = priceRatio > marginRatio ? priceRatio : marginRatio;
//                                if (green > 1)
//                                    green = 1;
//                                return Qt.rgba(0.1, green, 0.1, 1);
//                            }
//                        }
//                    }
//                }
//            }


//        }
//    }


//    Rectangle {
//        id: menuCategories
//        anchors.right: parent.right
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        width: parent.width / 2
//        color: "#33FFFFFF"

//        Keys.onDownPressed: container.menu.selectedCategory = container.menu.getNextCategory(newMenuCategoryName.text.trim())
//        Keys.onUpPressed: container.menu.selectedCategory = container.menu.getPreviousCategory(newMenuCategoryName.text.trim())

//        Column {
//            id: menuCategoryControls
//            width: parent.width
//            spacing: 2

//            TextField {
//                id: newMenuCategoryName
//                maximumLength: 32
//                width: parent.width
//                height: 50
//                placeholderText: qsTr("Category name")
//                onAccepted: {
//                    if(container.editMode) {
//                        var cat = menu.addCategory(newMenuCategoryName.text);
//                        newMenuCategoryName.text = "";
//                        console.log("added cat: " + cat.name);
//                        container.menuCategorySelected(cat, true);
//                    }
//                }

//                onActiveFocusChanged: {
//                    if(this.focus){
//                        this.selectAll();
//                    }
//                }
//            }
//        }

//        ListView {
//            width: parent.width
//            anchors.top: menuCategoryControls.bottom
//            anchors.bottom: menuCategories.bottom
//            model: container.menu ? container.menu.categories : 0
//            clip: true

//            delegate: RectangleFlashButton {
//                color: modelData.isDisabled ? "#AAAAAA" : "#7e57c2"
//                border.color: menu.selectedCategory && (menu.selectedCategory.id === modelData.id) ? "#DDDDDD" : "#777777"
//                border.width: 2
//                textColor: menu.selectedCategory && (menu.selectedCategory.id === modelData.id) ? "#DDDDDD" : "#000000"
//                flashColor: "#FFFFFF"
//                text: modelData.name

//                visible: {
//                    if(!container.editMode && modelData.isDisabled)
//                        return false;
//                    var filter = newMenuCategoryName.text.trim().toUpperCase()
//                    if(filter.length === 0){
//                        return true;
//                    }
//                    return modelData.name.toUpperCase().indexOf(filter) > -1;
//                }

//                hidden: !container.editMode && modelData.isDisabled;

//                onBeforeFlash: {
//                    menu.selectedCategory = modelData;
//                }

//                onClicked: {
//                    newMenuCategoryName.text = "";
//                    newMenuItemName.forceActiveFocus();
//                    menuCategorySelected(modelData, false);
//                }
//            }
//        }
//    }
}
