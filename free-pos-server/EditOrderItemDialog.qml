import QtQuick 2.3
import QtQuick.Controls 1.2


Rectangle {
    id: editOrderItemDialog
    anchors.fill: parent
    visible: false
    color: "#AA000000"
    property var model //OrderItem

    function show(orderItem) {
        editOrderItemDialog.model = orderItem;
        editOrderItemDialog.visible = true;
        editNote.forceActiveFocus();
        editNote.cursorPosition = editNote.text.length;
    }


    function close(save) {
        if(save) {
            editOrderItemDialog.model.quantity = Number(editQuantity.text);
            editOrderItemDialog.model.price = Number(editPrice.text);
            editOrderItemDialog.model.note = editNote.text.trim();
        }
        editOrderItemDialog.visible = false;
    }

    Keys.onEscapePressed: this.close(false)

    Rectangle {
        width: orderItemEditInner.width + 80
        height: orderItemEditInner.height + 80
        anchors.centerIn: parent
        color: "#FFFFFF"
        border.color: "#000000"
        border.width: 2
        Column {
            id: orderItemEditInner
            anchors.centerIn: parent
            spacing: 20


            Text {
                text: "Edit Order Item"
                font.bold: true
                font.pixelSize: 20
            }

            Column {
                spacing: 5

                Row {
                    Text {
                        width: 100
                        text: "Note: "
                    }


                    Rectangle {
                        width: 250
                        height: 100
                        border.width: 1
                        border.color: "#AAAAAA"

                        TextEdit {
                            id: editNote
                            text: editOrderItemDialog.model ? editOrderItemDialog.model.note : ""
                            anchors.fill: parent
                            anchors.margins: 5
//                            onAccepted: {
//                                editOrderItemDialog.close(true);
//                            }


                            KeyNavigation.tab: editQuantity
                            KeyNavigation.backtab: editPrice
                            KeyNavigation.priority: KeyNavigation.BeforeItem

                            onActiveFocusChanged: {
//                                        if(this.focus){
//                                            this.selectAll();
//                                        }
                            }


                        }
                    }
                }


                Row {
                    Text {
                        width: 100
                        text: "Quantity: "
                    }


                    TextField {
                        id: editQuantity
                        text: editOrderItemDialog.model ? Number(editOrderItemDialog.model.quantity.toFixed(2)) : ""
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        width: 150
                        maximumLength: 25
                        placeholderText: qsTr("Quantity")

                        onAccepted: {
                            editOrderItemDialog.close(true);
                        }

                        onActiveFocusChanged: {
                            if(this.focus){
                                this.selectAll();
                            }
                        }
                    }
                }

                Row {

                    Text {
                        width: 100
                        text: "Price: "
                    }


                    TextField {
                        id: editPrice
                        text: editOrderItemDialog.model ? Number(editOrderItemDialog.model.price.toFixed(2)) : ""
                        width: 150
                        maximumLength: 25
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        placeholderText: qsTr("Price")
                        onAccepted: {
                            editOrderItemDialog.close(true);
                        }

                        onActiveFocusChanged: {
                            if(this.focus){
                                this.selectAll();
                            }
                        }
                    }


                    Button {
                        text: "Ok"
                        onClicked: {
                            editOrderItemDialog.close(true);
                        }
                    }
                    Button {
                        text: "Cancel"
                        onClicked: {
                            editOrderItemDialog.close(false);
                        }
                    }
                    Button {
                        text: (editOrderItemDialog.model && editOrderItemDialog.model.deleted) ? "Un-Delete" : "Delete"
                        onClicked: {
                            editOrderItemDialog.model.deleted = !editOrderItemDialog.model.deleted;
                            editOrderItemDialog.close(true);
                        }
                    }
                }
            }
        }
    }
}
