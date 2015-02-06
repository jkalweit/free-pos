import QtQuick 2.3
import QtQuick.Controls 1.2


DialogModal {
    id: container
    title: "Edit Order Item"
    property var rec
    property var customer
    property var model //OrderItem

    function show(orderItem) {
        container.model = orderItem;
        container.visible = true;
        editNote.forceActiveFocus();
        editNote.cursorPosition = editNote.text.length;
    }

    function close(save) {
        if(save) {
            container.model.quantity = Number(editQuantity.text);
            container.model.price = Number(editPrice.text);
            container.model.note = editNote.text.trim();
        }
        container.visible = false;
    }

    customContent: Column {
        id: innerColumn
        spacing: 5


        TextLabeled {
            label: "Name:"
            text: editOrderItemDialog.model ? editOrderItemDialog.model.name : ""
        }

        TextLabeled {
            label: "Added:"
            text: editOrderItemDialog.model ? Qt.formatTime(editOrderItemDialog.model.createdStamp, "hh:mmAP") : ""
        }

        Row {
            Text {
                width: 75
                text: "Note: "
            }


            Rectangle {
                width: 250
                height: 50
                border.width: 1
                border.color: "#AAAAAA"

                TextEdit {
                    id: editNote
                    text: model ? model.note : ""
                    anchors.fill: parent
                    anchors.margins: 5

                    KeyNavigation.tab: editQuantity
                    KeyNavigation.backtab: editPrice
                    KeyNavigation.priority: KeyNavigation.BeforeItem

                }
            }
        }

        Column {
            anchors.left: parent.left
            anchors.leftMargin: 75
            spacing: 2

            Repeater {
                model: editOrderItemDialog.model ? editOrderItemDialog.model.orderItemOptions : 0


                Rectangle {
                    id: orderItemOptionContainer
                    width: 225

                    height: orderItemOptionName.height + 30
                    border.color: "#AAFFAA"
                    border.width: 2

                    Rectangle {
                        anchors.right: parent.right
                        anchors.rightMargin: {
                            var cost = container.model.cost;
                            var cumulative = container.model.getCumulativeCostUpToOption(modelData.id);
                            var ratio = cumulative / cost;
                            return parent.width * ratio;
                        }
                        border.color: "#77AAFFAA"
                        border.width: 2
                        color: "#77FFFF77"
                        height: parent.height
                        width: {
                            var cost = container.model.cost;
                            var ratio = modelData.cost / cost;
                            return parent.width * ratio;
                        }
                    }
                    Text {
                        id: orderItemOptionName
                        text: pos.selectedMenu.getMenuCategory(modelData.optionMenuCategoryId).name + ": " + modelData.menuItemName
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                    }
                    Text {
                        text: modelData.cost.toFixed(2)
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            selectOrderItemOption.orderItemOption = modelData;
                            selectOrderItemOption.visible = true;
                        }
                    }
                }


//                RectangleFlash {
//                    width: 225
//                    height: selectOrderItemOptionText.height + 20
//                    color: (modelData.menuItemName !== "") ? "#DDDDFF" : "#FFFFDD"
//                    onClicked: {
//                        selectOrderItemOption.orderItemOption = modelData;
//                        selectOrderItemOption.visible = true;
//                    }

//                    customContent: Text{
//                        id: selectOrderItemOptionText
//                        text: pos.selectedMenu.getMenuCategory(modelData.optionMenuCategoryId).name + ": " + modelData.menuItemName + ": " + modelData.cost.toFixed(2)
//                        anchors.verticalCenter: parent.verticalCenter
//                    }
//                }


            }


            Repeater {
                model: editOrderItemDialog.model ? editOrderItemDialog.model.orderItemInventoryItems : 0

                Rectangle {
                    width: 225
                    height: inventoryItemName.height + 30
                    visible: !(modelData.isAdded && modelData.isRemoved)
                    color: modelData.isAdded ? "#DDFFDD" : "#FFFFFF";
                    border.color: "#77AAFFAA"
                    border.width: 2

                    Rectangle {
                        anchors.right: parent.right
                        anchors.rightMargin: {
                            var cost = container.model.cost;
                            var cumulative = container.model.getCumulativeCostUpToInventoryItem(modelData.id);
                            var ratio = cumulative / cost;
                            return parent.width * ratio;
                        }
                        border.color: "#77AAFFAA"
                        border.width: 2
                        color: "#77FFFF77"
                        height: parent.height
                        width: {
                            var cost = container.model.cost;
                            var ratio = modelData.cost / cost;
                            return parent.width * ratio;
                        }
                    }

                    Text {
                        id: inventoryItemName
                        text: modelData.name
                        font.strikeout: modelData.isRemoved
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                    }
                    Text {
                        text: modelData.quantity.toFixed(2) + " " + modelData.unit + " = " + modelData.cost.toFixed(2)
                        font.strikeout: modelData.isRemoved
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            modelData.isRemoved = !modelData.isRemoved;
                        }
                    }
                }
            }

//                RectangleFlashButton {
//                    width: 225
//                    height: inventoryItemName.height + 20
//                    visible: !(modelData.isAdded && modelData.isRemoved)
//                    color: modelData.isAdded ? "#DDFFDD" : "#FFFFFF";
//                    onClicked: {
//                        modelData.isRemoved = !modelData.isRemoved;
//                    }

//                    customContent: Rectangle {
//                        anchors.fill: parent
//                        color: "transparent"
//                        Text {
//                            id: inventoryItemName
//                            text: modelData.name
//                            font.strikeout: modelData.isRemoved
//                            anchors.verticalCenter: parent.verticalCenter
//                            anchors.left: parent.left
//                        }
//                        Text {
//                            text: modelData.quantity.toFixed(2) + " " + modelData.unit
//                            font.strikeout: modelData.isRemoved
//                            anchors.verticalCenter: parent.verticalCenter
//                            anchors.right: parent.right
//                        }
//                    }
//                }
//            }
            RectangleFlash {
                width: 225
                height: addOrderItemInventoryItemText.height + 30
                color: "#DDDDDD"
                onClicked: {
                    addOrderItemInventoryItem.visible = true
                }

                customContent: Text{
                    id: addOrderItemInventoryItemText
                    text: "Add Extra"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        TextFieldLabeled {
            id: editQuantity
            label: "Quantity:"
            text: editOrderItemDialog.model ? editOrderItemDialog.model.quantity.toFixed(2) : ""
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            placeholderText: "Quantity"

            onAccepted: container.close(true);
        }

        TextFieldLabeled {
            id: editPrice
            label: "Price"
            text: model ? model.price.toFixed(2) : ""
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            placeholderText: "price"

            onAccepted: container.close(true);
        }

        TextLabeled {
            label: "Cost"
            text: model ? model.cog.toFixed(2) : ""
        }

        TextLabeled {
            label: "Margin"
            text: model ? model.margin.toFixed(2) : ""
        }

        RectangleFlash {
            width: parent.width
            height: submittedText.height + 30
            onClicked: {
                editOrderItemDialog.model.cycleSubmittedStamp();
            }

            customContent: Text{
                id: submittedText
                text: editOrderItemDialog.model && editOrderItemDialog.model.isSubmitted ? "Submitted " + Qt.formatTime(editOrderItemDialog.model.submittedStamp, "hh:mmAP") : "Not Submitted"
                anchors.verticalCenter: parent.verticalCenter
            }
        }


        Row {
            Button {
                text: "Ok"
                onClicked: {
                    container.close(true);
                }
            }
//            Button {
//                text: "Cancel"
//                onClicked: {
//                    container.close(false);
//                }
//            }
            Button {
                text: "Move"
                onClicked: {
                    moveOrderItem.show();
                }
            }
            Button {
                text: (model && model.deleted) ? "Un-Delete" : "Delete"
                onClicked: {
                    model.deleted = !model.deleted;
                    container.close(true);
                }
            }
        }
    }


    DialogModal {
        id: addOrderItemInventoryItem
        anchors.right: parent.right
        //signal inventoryItemSelected(var inventoryItem)
        customContent: Column {
            Text {
                text: "Add Extra Item"
                font.pixelSize: 16
                font.bold: true
            }
            InventoryItems {
                inventory: pos.selectedInventory ? pos.selectedInventory : 0
                width: 400
                height: 700

                onInventoryItemSelected: {
                    var item = container.model.addOrderItemInventoryItem(inventoryItem.id, inventoryItem.name, inventoryItem.unit, inventoryItem.price, inventoryItem.defaultQuantity);
                    item.isAdded = true;
                    //addOrderItemInventoryItem.visible = false;
                }
            }
        }
    }


    DialogModal {
        id: moveOrderItem
        title: "Move Order Item"

        customContent: Column {
            spacing: 5

            TicketList {
                id: ticketList
                rec: pos.selectedRec
                showPaid: false
//                anchors.left: parent.left
//                anchors.leftMargin: 2
//                anchors.top: parent.top
//                anchors.topMargin: 2
//                anchors.bottom: parent.bottom
                width: 200
                height: 700
                onTicketSelected: {
                    if (ticket.id === model.ticketId && ticket.customers[0].id === model.customerId) {
                      // do nothing, selected the same destination
                    } else if(ticket.isPaid) {
                        cannotMoveOrderItem.show()
                    } else {
                        moveOrderItem.visible = false;
                        container.close(true); // save changes before moving
                        rec.moveOrderItem(model, ticket.id, ticket.customers[0].id);
                    }
                }
            }

            Button {
                text: "Cancel"
                onClicked: moveOrderItem.visible = false
            }
        }
    }

    DialogModalMessage {
        id: cannotMoveOrderItem
        title: "Cannot Move Order Item"
        text: "Destination ticket has already been paid."
    }


    DialogModal {
        id: selectOrderItemOption
        property var orderItemOption

        property var previousMenuCategory

        onVisibleChanged: {
            if(selectOrderItemOption.visible) {
                previousMenuCategory = pos.selectedMenu.selectedCategory;
                pos.selectedMenu.selectedCategory = pos.selectedMenu.getMenuCategory(orderItemOption.optionMenuCategoryId);
            } else {
                pos.selectedMenu.selectedCategory = previousMenuCategory;
            }
        }

        customContent: Column {
            Text {
                text: "Select Order Item Option"
                font.pixelSize: 16
                font.bold: true
            }
            MenuItemsView {
                id: menuItemsView
                menu: pos.selectedMenu
                width: 200
                height: 600
                onMenuItemSelected: {
                    selectOrderItemOption.orderItemOption.menuItemName = menuItem.name;
                    selectOrderItemOption.orderItemOption.cost = menuItem.cost;
                    selectOrderItemOption.visible = false;
                }
            }
            Button {
                onClicked: {
                    if(pos.menu.selectedCategory) {
                        console.log("Test: " + pos.menu.selectedCategory.name);
                    }else {
                        console.log("Nope.");
                    }
                }
            }
        }
    }
}
