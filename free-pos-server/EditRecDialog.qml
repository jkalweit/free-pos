import QtQuick 2.3
import QtQuick.Controls 1.2


DialogModal {
    id: container
    title: "Edit Reconciliation"
    property var model
    defaultFocus: editName

    onVisibleChanged: {
        if(this.visible) {
            //var tmp = model
            model = model
            beginningDrawer.model = model.beginningDrawer
            endingDrawer.model = model.endingDrawer
            if(model.name === "Dinner")
                editName.currentIndex = 1
            else
                editName.currentIndex = 0
        }
    }

    function close(save) {
        if(save) {
            model.name = editName.currentText;
            model.note = editNote.text;

            beginningDrawer.saveChanges();
            endingDrawer.saveChanges();
        }
        container.visible = false;
    }

    customContent: Column {
        spacing: 5


        Row {
            Text {
                width: 75
                text: ""
            }

            ComboBox {
                id: editName
                width: 150
                model: [ "Lunch", "Dinner" ]
            }
        }

        Row {
            Text {
                width: 75
                text: "Opened:"
            }


            Text {
                width: 150
                text: model ? Qt.formatDateTime(container.model.openedStamp, "ddd MM/dd/yyyy hh:mmAP") : ""
            }
        }

        Row {
            Text {
                width: 75
                text: "Closed:"
            }


            Text {
                width: 150
                text: model ? Qt.formatDateTime(model.closedStamp, "ddd MM/dd/yyyy hh:mmAP") : ""
            }
        }

        TextFieldLabeled {
            id: editNote
            label: "Note:"
            text: model ? model.note : ""
            textFieldWidth: 415
            placeholderText: "Note"
        }

        Row {
            EditDrawer {
                id: beginningDrawer
                model: container.model ? container.model.beginningDrawer : 0
            }

            Rectangle {
                id: spacer
                width: 40
                height: 10
            }

            EditDrawer {
                id: endingDrawer
                model: container.model ? container.model.endingDrawer : 0
            }
        }


        Row {
            Button {
                text: "Close Rec"
                onClicked: {
                    if(model.hasOpenTickets()) {
                        message.title = "Cannot Close Rec";
                        message.text = "There are open tickets.";
                        message.show();
                        return;
                    }

                    confirm.title = "Close Rec?";
                    confirm.text = "";
                    confirm.yes.connect(function () {
                        model.closeRec();
                        container.visible = false;
                    });
                    confirm.show();
                }
            }
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
        }
    }

    DialogModalMessage {
        id: message
    }

    DialogModalConfirm {
        id: confirm
    }
}
