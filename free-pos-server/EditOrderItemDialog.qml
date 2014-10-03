import QtQuick 2.3
import QtQuick.Controls 1.2


DialogModal {
    id: container
    title: "Edit Order Item"
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
            label: "Quantity"
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
                text: (model && model.deleted) ? "Un-Delete" : "Delete"
                onClicked: {
                    model.deleted = !model.deleted;
                    container.close(true);
                }
            }
        }
    }
}
