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
                model: editOrderItemDialog.model ? editOrderItemDialog.model.orderItemInventoryItems : 0

                RectangleFlashButton {
                    width: 200
                    height: inventoryItemName.height + 20
                    visible: !(modelData.isAdded && modelData.isRemoved)
                    color: modelData.isAdded ? "#DDFFDD" : "#FFFFFF";
                    onClicked: {
                        modelData.isRemoved = !modelData.isRemoved;
                    }

                    customContent: Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        Text {
                            id: inventoryItemName
                            text: modelData.name
                            font.strikeout: modelData.isRemoved
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                        }
                        Text {
                            text: modelData.quantity.toFixed(2) + " " + modelData.unit
                            font.strikeout: modelData.isRemoved
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                        }
                    }
                }
            }
        }

        RectangleFlash {
            width: parent.width
            height: addOrderItemInventoryItemText.height + 20
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
            text: model ? model.cost.toFixed(2) : ""
        }

        TextLabeled {
            label: "Margin"
            text: model ? model.margin.toFixed(2) : ""
        }

        RectangleFlash {
            width: parent.width
            height: submittedText.height + 10
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
            Button {
                text: "Cancel"
                onClicked: {
                    container.close(false);
                }
            }
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
}
