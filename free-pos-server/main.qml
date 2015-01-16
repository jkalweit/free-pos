import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1020
    height: 800
    visibility: "Maximized"
    title: "CY Pos"












    WeeksView {
        width: parent.width
        height: parent.height
        week: pos.selectedWeek
    }


    RectangleFlashButton {
        width: 100
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        text: "<---"
        onClicked: pos.selectedWeek = pos.previousWeek()
    }

    RectangleFlashButton {
        width: 100
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.bottom: parent.bottom
        text: "--->"
        onClicked: pos.selectedWeek = pos.nextWeek()
    }






    RectangleFlashButton {
        width: 200
        anchors.right: parent.right
        anchors.rightMargin: 200
        anchors.bottom: parent.bottom
        text: "Edit Menu"
        onClicked: editMenuDialog.show()
    }

    RectangleFlashButton {
        width: 200
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        text: "Edit Inventory"
        onClicked: editInventoryDialog.show()
    }




    RectangleFlashButton {
        width: 100
        anchors.left: parent.left
        anchors.leftMargin: 200
        anchors.bottom: parent.bottom
        text: "Payroll Hours"
        onClicked: {
//            var summaries = pos.selectedWeek.getEmployeeShiftsSummaries()
//            console.log("Got the summaries: " + summaries.length);
//            shiftsByWeek.summaries = summaries;
            shiftsByWeek.visible = true;
        }
    }



    EmployeeShiftsByWeek {
        id: shiftsByWeek
        anchors.fill: parent
        visible: false
        summaries: pos.selectedWeek.employeeShiftsSummaries
    }




    EditReconciliation {
        id: editReconciliation
        visible: pos.selectedRec // ? pos.selectedRec.isOpen : false
        model: pos.selectedRec ? pos.selectedRec : 0
    }




    DialogModal {
        id: editMenuDialog
        customContent: Column {
            Text {
                text: "Edit Menu"
                font.pixelSize: 16
                font.bold: true
            }
            MenuView {
                id: editMenuView
                menu: pos.selectedMenu ? pos.selectedMenu : 0
                width: 400
                height: 700
                editMode: true

                onMenuItemSelected: {
                    editMenuItem.menuItem = menuItem;
                    editMenuItem.show();
                }

                onMenuCategorySelected: {
                    if(isNew) {
                        editMenuCategory.menuCategory = menuCategory;
                    }

                    if(menuCategory === editMenuCategory.menuCategory) {
                        editMenuCategory.show();
                    } else {
                        editMenuCategory.menuCategory = menuCategory;
                    }
                }
            }
        }
    }

    DialogModal {
        id: editMenuItem
        property var menuItem
        property bool isItemDisabled

        onVisibleChanged: {
            if(editMenuItem.visible) {

                editMenuItem.menuItem = editMenuItem.menuItem;
                editMenuItem.isItemDisabled = editMenuItem.menuItem.isDisabled;
                if(editMenuItem.menuItem.type === "Alcohol") {
                    editType.currentIndex = 1;
                } else {
                    editType.currentIndex = 0;
                }
            }
        }

        function close(save) {
            if(save) {
                editMenuItem.menuItem.name = editMenuItemName.text;
                editMenuItem.menuItem.price = editMenuItemPrice.text;
                editMenuItem.menuItem.isDisabled = editMenuItem.isItemDisabled;
                editMenuItem.menuItem.type = editType.currentText;
            }
            editMenuItem.visible = false;
        }

        customContent: Column {
            id: innerColumn
            spacing: 5
            Text {
                text: "Edit Menu Item"
                font.pixelSize: 16
                font.bold: true
            }
            TextFieldLabeled {
                id: editMenuItemName
                label: "Item Name:"
                text: editMenuItem.menuItem ? editMenuItem.menuItem.name : ""
            }
            TextFieldLabeled {
                id: editMenuItemPrice
                label: "Price:"
                text: editMenuItem.menuItem ? editMenuItem.menuItem.price.toFixed(2) : ""
            }
            ComboBox {
                id: editType
                model: [ "Food", "Alcohol" ]
            }

            RectangleFlashButton {
                text: "Is Disabled: " + (editMenuItem.isItemDisabled ? "Yes" : "No")
                onClicked: editMenuItem.isItemDisabled = !editMenuItem.isItemDisabled
            }
            Row {
                Button {
                    text: "Add Menu Item Option"
                    onClicked: addMenuItemOption.visible = true
                }
                Button {
                    text: "Add Inventory Item"
                    onClicked: addMenuItemInventoryItemDialog.show()
                }
            }
            Repeater {
                model: editMenuItem.menuItem ? editMenuItem.menuItem.menuItemOptions : 0

                Rectangle {
                    id: menuItemOptionContainer
                    width: innerColumn.width

                    height: menuItemOptionName.height + 10
                    border.color: "#AAFFAA"
                    border.width: 2

                    Rectangle {
                        anchors.right: parent.right
                        anchors.rightMargin: {
                            var cost = editMenuItem.menuItem.cost;
                            var cumulative = editMenuItem.menuItem.getCumulativeCostUpToOption(modelData.id);
                            var ratio = cumulative / cost;
                            return parent.width * ratio;
                        }
                        border.color: "#77AAFFAA"
                        border.width: 2
                        color: "#77FFFF77"
                        height: parent.height
                        width: {
                            var cost = editMenuItem.menuItem.cost;
                            var ratio = pos.selectedMenu.getMenuCategory(modelData.optionMenuCategoryId).averageCost / cost;
                            return parent.width * ratio;
                        }
                    }
                    Text {
                        id: menuItemOptionName
                        text: pos.selectedMenu.getMenuCategory(modelData.optionMenuCategoryId).name
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                    }
                    Text {
                        text: pos.selectedMenu.getMenuCategory(modelData.optionMenuCategoryId).averageCost.toFixed(2)
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                    }
                }
            }
            Repeater {
                model: editMenuItem.menuItem ? editMenuItem.menuItem.menuItemInventoryItems : 0

                Rectangle {
                    id: inventoryItemContainer
                    width: innerColumn.width
                    height: inventoryItemName.height + 10
                    border.color: "#AAAAFF"
                    border.width: 2

                    Rectangle {
                        anchors.right: inventoryItemContainer.right
                        anchors.rightMargin: {
                            var cost = editMenuItem.menuItem.cost;
                            var cumulative = editMenuItem.menuItem.getCumulativeCostUpToInventoryItem(modelData.id);
                            var ratio = cumulative / cost;
                            return parent.width * ratio;
                        }
                        border.color: "#77AAAAFF"
                        border.width: 2
                        color: "#77FFFF77"
                        height: inventoryItemContainer.height
                        width: {
                            var cost = editMenuItem.menuItem.cost;
                            var ratio = modelData.cost / cost;
                            return parent.width * ratio;
                        }
                    }

                    Text {
                        id: inventoryItemName
                        text: pos.selectedInventory.getInventoryItem(modelData.inventoryItemId).name
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                    }
                    Text {
                        text: modelData.quantity.toFixed(2) + " @ " + (modelData.inventoryItem ? modelData.inventoryItem.unitPrice.toFixed(2) + " " + modelData.inventoryItem.unit + " = " + modelData.cost.toFixed(2) : "?")
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            editMenuItemInventoryItem.menuItemInventoryItem = modelData;
                            editMenuItemInventoryItem.show();
                        }
                    }
                }
            }
            TextLabeled {
                label: "Cost:"
                text: editMenuItem.menuItem ? editMenuItem.menuItem.cost.toFixed(2) : ""
            }
            TextLabeled {
                label: "Margin:"
                text: editMenuItem.menuItem ? editMenuItem.menuItem.margin.toFixed(2) : ""
            }
            Row {
                Button {
                    text: "Ok"
                    onClicked: editMenuItem.close(true)
                }
                Button {
                    text: "Cancel"
                    onClicked: editMenuItem.close(false)
                }
            }
        }
    }

    DialogModal {
        id: addMenuItemOption

        function close(save) {
//            if(save) {
//                if(addMenuItemOptionName.text.trim() !== "") {
//                    editMenuItem.menuItem.addMenuItemOption(addMenuItemOptionName.text);
//                } else {
//                    return;
//                }
//            }
//            addMenuItemOptionName.text = "";
            addMenuItemOption.visible = false;
        }

        customContent: Column {
            spacing: 5
            Text {
                text: "Add Menu Item Option"
                font.pixelSize: 16
                font.bold: true
            }
//            TextFieldLabeled {
//                id: addMenuItemOptionName
//                label: "Name"
//                placeholderText: "Option Name"
//            }
            MenuCategoriesView {
                width: 200
                height: 600
                menu: pos.selectedMenu
                onMenuCategorySelected: {
                    editMenuItem.menuItem.addMenuItemOption(menuCategory.id);
                    addMenuItemOption.close(false);
                }
            }
            Row {
//                Button {
//                    text: "Add"
//                    onClicked: addMenuItemOption.close(true)
//                }
                Button {
                    text: "Cancel"
                    onClicked: addMenuItemOption.close(false)
                }
            }
        }
    }

    DialogModal {
        id: addMenuItemInventoryItemDialog
        //signal inventoryItemSelected(var inventoryItem)
        customContent: Column {
            Text {
                text: "Add Inventory Item"
                font.pixelSize: 16
                font.bold: true
            }
            InventoryItems {
                id: editInventoryView
                inventory: pos.selectedInventory ? pos.selectedInventory : 0
                width: 400
                height: 700

                onInventoryItemSelected: {
                    var item = editMenuItem.menuItem.addMenuItemInventoryItem(inventoryItem.id, inventoryItem.defaultQuantity);
                    item.inventoryItem = inventoryItem;
                    addMenuItemInventoryItemDialog.visible = false;
                }
            }
        }
    }


    DialogModal {
        id: editMenuItemInventoryItem
        property var menuItemInventoryItem

        onVisibleChanged: {
            if(editMenuItemInventoryItem.visible) {
                editMenuItemInventoryItem.menuItemInventoryItem = editMenuItemInventoryItem.menuItemInventoryItem;
            }
        }

        function close(save) {
            if(save) {
                editMenuItemInventoryItem.menuItemInventoryItem.quantity = editMenuItemInventoryItemQuantity.text;
            }
            editMenuItemInventoryItem.visible = false;
        }

        customContent: Column {
            spacing: 5
            Text {
                text: "Edit Inventory Item"
                font.pixelSize: 16
                font.bold: true
            }
            TextLabeled {
                label: "Item Name:"
                text: editMenuItemInventoryItem.menuItemInventoryItem ? pos.selectedInventory.getInventoryItem(editMenuItemInventoryItem.menuItemInventoryItem.inventoryItemId).name : ""
            }
            TextFieldLabeled {
                id: editMenuItemInventoryItemQuantity
                label: "Quantity:"
                text: editMenuItemInventoryItem.menuItemInventoryItem ? editMenuItemInventoryItem.menuItemInventoryItem.quantity.toFixed(2) : ""
            }
            Row {
                Button {
                    text: "Ok"
                    onClicked: editMenuItemInventoryItem.close(true)
                }
                Button {
                    text: "Cancel"
                    onClicked: editMenuItemInventoryItem.close(false)
                }
                Button {
                    text: "Delete"
                    onClicked: {
                        var menuItemInventoryItem = editMenuItemInventoryItem.menuItemInventoryItem;
                        var menuCategory = pos.selectedMenu.getMenuCategory(menuItemInventoryItem.menuCategoryId);
                        var menuItem = menuCategory.getMenuItem(menuItemInventoryItem.menuItemId);
                        menuItem.removeMenuItemInventoryItem(menuItemInventoryItem.id);
                        editMenuItemInventoryItem.visible = false;
                    }
                }
            }
        }
    }


    DialogModal {
        id: editMenuCategory
        property var menuCategory
        property bool isCategoryDisabled

        onVisibleChanged: {
            if(editMenuCategory.visible) {
                editMenuCategory.menuCategory = editMenuCategory.menuCategory;
                editMenuCategory.isCategoryDisabled = editMenuCategory.menuCategory.isDisabled
            }
        }

        function close(save) {
            if(save) {
                editMenuCategory.menuCategory.name = editMenuCategoryName.text;
                editMenuCategory.menuCategory.isDisabled = editMenuCategory.isCategoryDisabled;
            }
            editMenuCategory.visible = false;
        }

        customContent: Column {
            Text {
                text: "Edit Menu Category"
                font.pixelSize: 16
                font.bold: true
            }

            TextFieldLabeled {
                id: editMenuCategoryName
                label: "Name:"
                text: editMenuCategory.menuCategory ? editMenuCategory.menuCategory.name : ""
            }
            RectangleFlashButton {
                text: "Is Disabled: " + (editMenuCategory.isCategoryDisabled ? "Yes" : "No")
                onClicked: editMenuCategory.isCategoryDisabled = !editMenuCategory.isCategoryDisabled
            }
            Row {
                Button {
                    text: "Ok"
                    onClicked: editMenuCategory.close(true)
                }
                Button {
                    text: "Cancel"
                    onClicked: editMenuCategory.close(false)
                }
            }
        }
    }


    DialogModal {
        id: editInventoryDialog
        customContent: Column {
            Text {
                text: "Edit Inventory"
                font.pixelSize: 16
                font.bold: true
            }
            InventoryItems {
                inventory: pos.selectedInventory ? pos.selectedInventory : 0
                width: 400
                height: 700

                onInventoryItemSelected: {
                    editInventoryItem.inventoryItem = inventoryItem;
                    editInventoryItem.show();
                }
            }
        }
    }

    DialogModal {
        id: editInventoryItem
        property var inventoryItem

        onInventoryItemChanged: editInventoryItem.updateUnitPrice()

        onVisibleChanged: {
            if(editInventoryItem.visible) {
                editInventoryItem.inventoryItem = editInventoryItem.inventoryItem;

                var units = [ "oz", "Slice", "tsp", "Tbsp", "Each" ];
                editInventoryItemUnit.model = units;
                for(var i = 0; i < units.length; i++) {
                    if(units[i] === editInventoryItem.inventoryItem.unit) {
                        editInventoryItemUnit.currentIndex = i;
                    }
                }
            }
        }

        function updateUnitPrice() {
            var priceQuantity = parseFloat(editInventoryItemPriceQuantity.text);
            var price = parseFloat(editInventoryItemPrice.text);
            if(priceQuantity > 0) {
                editInventoryItemUnitPrice.text = (price / priceQuantity).toFixed(2);
            } else {
                editInventoryItemUnitPrice.text = "Invalid";
            }
        }

        function close(save) {
            if(save) {
                editInventoryItem.inventoryItem.name = editInventoryItemName.text;
                editInventoryItem.inventoryItem.unit = editInventoryItemUnit.currentText;
                editInventoryItem.inventoryItem.priceQuantity = editInventoryItemPriceQuantity.text;
                editInventoryItem.inventoryItem.price = editInventoryItemPrice.text;
                editInventoryItem.inventoryItem.defaultQuantity = editInventoryItemDefaultQuantity.text;
            }
            editInventoryItem.visible = false;
        }

        customContent: Column {
            spacing: 5
            Text {
                text: "Edit Inventory Item"
                font.pixelSize: 16
                font.bold: true
            }
            TextFieldLabeled {
                id: editInventoryItemName
                label: "Item Name:"
                text: editInventoryItem.inventoryItem ? editInventoryItem.inventoryItem.name : ""
            }
            Text {
                text: "[Use the smallest unit used in recipes]"
                width: 225
            }
            Row {
                Text {
                    text: "Unit:"
                    width: 75
                }
                ComboBox {
                    id: editInventoryItemUnit
                    width: 150
                }
            }
            TextFieldLabeled {
                id: editInventoryItemPriceQuantity
                label: "Price Quantity:"
                text: editInventoryItem.inventoryItem ? editInventoryItem.inventoryItem.priceQuantity.toFixed(2) : ""
                onTextChanged: editInventoryItem.updateUnitPrice();
            }
            TextFieldLabeled {
                id: editInventoryItemPrice
                label: "Price:"
                text: editInventoryItem.inventoryItem ? editInventoryItem.inventoryItem.price.toFixed(2) : ""
                onTextChanged: editInventoryItem.updateUnitPrice();
            }
            TextLabeled {
                id: editInventoryItemUnitPrice
                label: "Unit Price:"
                text: ""
            }
            TextFieldLabeled {
                id: editInventoryItemDefaultQuantity
                label: "Default Quantity:"
                text: editInventoryItem.inventoryItem ? editInventoryItem.inventoryItem.defaultQuantity.toFixed(2) : ""
            }
            Row {
                Button {
                    text: "Ok"
                    onClicked: editInventoryItem.close(true)
                }
                Button {
                    text: "Cancel"
                    onClicked: editInventoryItem.close(false)
                }
            }
        }
    }



}
