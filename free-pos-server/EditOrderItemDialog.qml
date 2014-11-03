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
                height: 100
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


        TextFieldLabeled {
            id: editQuantity
            label: "Quantity:"
            text: editOrderItemDialog.model ? Number(editOrderItemDialog.model.quantity.toFixed(2)) : ""
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            placeholderText: "Quantity"

            onAccepted: container.close(true);
        }

        TextFieldLabeled {
            id: editPrice
            label: "Price"
            text: model ? Number(model.price.toFixed(2)) : ""
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            placeholderText: "price"

            onAccepted: container.close(true);
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
