import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    id: container
    color: "#333333"
    anchors.fill: parent
    property var model
    visible: model ? true : false


    TicketList {
        id: ticketList
        rec: model
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.bottom: parent.bottom
        width: 200

        onTicketSelected: {
            rec.selectedTicket = ticket;
        }
    }



    Flickable {
        width: ticket.width
        contentWidth: ticket.width
        contentHeight: ticket.height
        anchors.left: ticketList.right
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        clip: true

        Rectangle {
            id: ticket
            visible: model ? model.selectedTicket : false
            color: "white"
            width: 400
            height: ticketInner.height + (ticketInner.anchors.margins * 2)

            Column {
                id: ticketInner
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 30
                spacing: 20

                RectangleFlash {
                    width: parent.width / 2
                    height: togoText.height + 20
                    anchors.right: parent.right
                    flashColor: "#000000"
                    onClicked: model.selectedTicket.isTogo = !model.selectedTicket.isTogo

                    customContent: Text {
                        id: togoText
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Togo: " + (model.selectedTicket && model.selectedTicket.isTogo ? "YES" : "No")
                        font.bold: model && model.selectedTicket && model.selectedTicket.isTogo
                        font.pixelSize: model && model.selectedTicket && model.selectedTicket.isTogo ? 20 : 16
                        color: model && model.selectedTicket && model.selectedTicket.isTogo ? "red" : "#000000"
                    }
                }

                Column {
                    id: customers
                    width: parent.width
                    spacing: 3

                    Repeater {
                        model: container.model && container.model.selectedTicket ? container.model.selectedTicket.customers : 0

                        Column {
                            id: customer
                            width: customers.width
                            property var model: modelData

                            RectangleFlash {
                                width: parent.width
                                height: customerName.height + 10
                                onClicked: {
                                    editCustomerDialog.model = modelData;
                                    editCustomerDialog.show();
                                }
                                customContent: Text {
                                    id: customerName
                                    text: modelData.name
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                    font.pixelSize: 20
                                }
                            }

                            Column {
                                id: orderItems
                                anchors.left: parent.left
                                anchors.leftMargin: 20
                                anchors.right: parent.right

                                Repeater {
                                    id: orderItemsRepeater
                                    model: modelData.orderItems

                                    RectangleFlash {
                                        id: orderItem
                                        width: orderItems.width
                                        height: orderItemInner.height + 20
                                        property var model: modelData
                                        color: modelData.isSubmitted ? "transparent" : "#9977DD77"
                                        //property alias flash: flashAnimation
                                        visible: !(modelData.deleted && !modelData.isSubmitted) // do not show if deleted and not submitted

                                        customContent: Column {
                                            id: orderItemInner
                                            width: parent.width
                                            Rectangle {
                                                width: parent.width
                                                height: 20
                                                color: "transparent"

                                                Text {
                                                    anchors.left: parent.left
                                                    anchors.leftMargin: 0
                                                    text: Number(modelData.quantity.toFixed(2))
                                                    font.strikeout: modelData.deleted
                                                }
                                                Text {
                                                    anchors.left: parent.left
                                                    anchors.leftMargin: 40
                                                    text: modelData.name
                                                    font.strikeout: modelData.deleted
                                                }
                                                Text {
                                                    anchors.right: parent.right
                                                    text: modelData.subTotal.toFixed(2);
                                                    font.strikeout: modelData.deleted
                                                }
                                            }

                                            Text {
                                                anchors.left: parent.left
                                                anchors.leftMargin: 40
                                                text: modelData.note
                                                font.italic: true
                                                font.strikeout: modelData.deleted
                                            }

//                                            Repeater {
//                                                model: modelData.orderItemInventoryItems

//                                                Text {
//                                                    text: modelData.name
//                                                }
//                                            }
                                        }


                                        onClicked: {
                                            editOrderItemDialog.rec = container.model
                                            editOrderItemDialog.customer = customer.model
                                            editOrderItemDialog.show(model)
                                        }
                                    }
                                }
                            }
                        }
                    }

                }

                Rectangle {
                    id: ticketFooter
                    width: parent.width
                    height: totals.height > ticketControls.height ? totals.height : ticketControls.height

                    Column {
                        id: ticketControls
                        width: parent.width / 2 - 10
                        anchors.left: parent.left


                        Rectangle {
                            width: parent.width
                            height:openedText.height + 20
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            Text{
                                id: openedText
                                text: model.selectedTicket ? "Opened: " + Qt.formatTime(model.selectedTicket.createdStamp, "hh:mmAP") : ""
                                anchors.verticalCenter: parent.verticalCenter
                            }

                        }

                        RectangleFlash {
                            width: parent.width
                            height: printKitchen.height + 10
                            onClicked: {
                                model.selectedTicket.printKitchen();
                            }

                            customContent: Text{
                                id: printKitchen
                                text: "Print Kitchen"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }

                        RectangleFlash {
                            width: parent.width
                            height: printReceipt.height + 10
                            onClicked: {
                                model.selectedTicket.printReceipt();
                            }

                            customContent: Text{
                                id: printReceipt
                                text: "Print Receipt" //model.selectedTicket && model.selectedTicket.isPaid ? model.selectedTicket.paymentType + " " + Qt.formatTime(model.selectedTicket.paidStamp, "hh:mmAP") : "Unpaid"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }

                        RectangleFlash {
                            width: parent.width
                            height: paidText.height + 10
                            onClicked: {
                                model.selectedTicket.cyclePaymentType();
                            }

                            customContent: Text{
                                id: paidText
                                text: model.selectedTicket && model.selectedTicket.isPaid ? model.selectedTicket.paymentType + " " + Qt.formatTime(model.selectedTicket.paidStamp, "hh:mmAP") : "Unpaid"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }

                    Column {
                        id: totals
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        width: parent.width / 2
                        spacing: 5
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Food:"
                                anchors.left: parent.left
                            }
                            Text {
                                text: model.selectedTicket ? model.selectedTicket.foodTotal.toFixed(2) : ""
                                anchors.right: parent.right
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Tax:"
                                anchors.left: parent.left
                            }
                            Text {
                                text: model.selectedTicket ? model.selectedTicket.taxTotal.toFixed(2) : ""
                                anchors.right: parent.right
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Bar:"
                                anchors.left: parent.left
                            }
                            Text {
                                text: model.selectedTicket ? model.selectedTicket.barTotal.toFixed(2) : ""
                                anchors.right: parent.right
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Total:"
                                anchors.left: parent.left
                                font {
                                    bold: true
                                    pixelSize: 16
                                }

                            }
                            Text {
                                text: "$" + (model.selectedTicket ? model.selectedTicket.total.toFixed(2) : "")
                                anchors.right: parent.right
                                font {
                                    bold: true
                                    pixelSize: 16
                                }
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Cost:"
                                anchors.left: parent.left
                            }
                            Text {
                                text: model.selectedTicket ? model.selectedTicket.cost.toFixed(2) : ""
                                anchors.right: parent.right
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Margin:"
                                anchors.left: parent.left
                            }
                            Text {
                                text: model.selectedTicket ? model.selectedTicket.margin.toFixed(2) : ""
                                anchors.right: parent.right
                            }
                        }
                    }
                }
            }
        }
    }

    MenuView {
        id: menuView
        menu: pos.selectedMenu ? pos.selectedMenu : 0
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 400

        onMenuItemSelected: {
            if(model && model.selectedTicket) {
                model.selectedTicket.customers[0].addOrderItem(menuItem, 1, "");
            }
        }
    }

    Rectangle {
        id: recTotals
        width: 200
        height: recTotalsInner.height + 20
        anchors.right: container.right
        anchors.rightMargin: 400
        anchors.bottom: container.bottom
        opacity: 0.50
        Column {
            id: recTotalsInner
            anchors.top: recTotals.top
            anchors.topMargin: 10
            anchors.left: recTotals.left
            anchors.leftMargin: 10
            anchors.right: recTotals.right
            anchors.rightMargin: 10
            spacing: 5                        

            Rectangle {
                width: parent.width
                height: 20
                color: "transparent"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    text: "Current Rec:"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    text: model ? model.name : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 15
                color: "transparent"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    text: "Food:"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    text: model ? "$" + model.foodTotal.toFixed(2) : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 15
                color: "transparent"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    text: "Tax:"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    text: model ? "$" + model.taxTotal.toFixed(2) : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 20
                color: "transparent"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    text: "Bar:"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    text: model ? "$" + model.barTotal.toFixed(2) : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 20
                color: "transparent"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    text: "Total:"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    text: model ? "$" + model.total.toFixed(2) : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 20
                color: "transparent"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    text: "Cost:"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    text: model ? "$" + model.cost.toFixed(2) : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 20
                color: "transparent"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    text: "Margin:"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    text: model ? "$" + model.margin.toFixed(2) : ""
                }
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: editRecDialog.show()
        }
    }

    EditCustomerDialog {
        id: editCustomerDialog
    }

    EditOrderItemDialog {
        id: editOrderItemDialog        
    }

    EditRecDialog {
        id: editRecDialog
        model: container.model
    }

    RectangleFlashButton {
        width: 200
        anchors.right: container.right
        anchors.rightMargin: 200
        anchors.bottom: container.bottom
        text: "Edit Menu"
        onClicked: editMenuDialog.show()
    }

    RectangleFlashButton {
        width: 200
        anchors.right: container.right
        anchors.rightMargin: 0
        anchors.bottom: container.bottom
        text: "Edit Inventory"
        onClicked: editInventoryDialog.show()
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
            Button {
                text: "Add Inventory Item"
                onClicked: addMenuItemInventoryItemDialog.show()
            }
            ListView {
                width: 300
                height: 200
                model: editMenuItem.menuItem ? editMenuItem.menuItem.menuItemInventoryItems : 0
                clip: true

                delegate: RectangleFlash {
                    id: inventoryItemContainer
                    width: parent.width
                    //property alias model: modelData

                    height: inventoryItemName.height + 10
                    border.color: "blue" // menu.selectedCategory && menu.selectedCategory.selectedItem && (menu.selectedCategory.selectedItem.id === modelData.id) ? "#DDDDDD" : "#777777"
                    border.width: 2
                    //color:  modelData.isDisabled ? "#AAAAAA" : "#9575cd"
                    flashColor: "#FFFFFF"

                    onClicked: {
                        editMenuItemInventoryItem.menuItemInventoryItem = modelData;
                        editMenuItemInventoryItem.show();
                    }

                    customContent: Item {
                        anchors.fill: parent
                        Text {
                            id: inventoryItemName
                            text: pos.selectedInventory.getInventoryItem(modelData.inventoryItemId).name
                            color: "#000000"
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                        }
                        Text {
                            text: modelData.quantity.toFixed(2) + " " + modelData.inventoryItem.unit + " @ " + (modelData.inventoryItem ? modelData.inventoryItem.price.toFixed(2) + " = " + modelData.cost.toFixed(2) : "?")
                            color: "#000000"
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
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
                    console.log('Selected Inventory Item:', inventoryItem.name);
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
                    model: [ "oz", "Slice", "tsp", "Tbsp", "Each" ]
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
