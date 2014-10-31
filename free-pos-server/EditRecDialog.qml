import QtQuick 2.3
import QtQuick.Controls 1.2


DialogModal {
    id: container
    title: "Edit Reconciliation"
    property var model
    defaultFocus: editNote

    function updateIfDifferent(target, field, val){
        if(target[field].toFixed(2) !== val.toFixed(2))
            target[field] = val;
    }

    onVisibleChanged: {
        if(this.visible) {
            //var tmp = model
            model = pos.selectedRec
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
            saveData();
            //beginningDrawer.saveChanges();
            //endingDrawer.saveChanges();
        }
        container.visible = false;
    }

    function saveData() {
        model.name = editName.currentText;
        model.note = editNote.text;
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

        Rectangle {
            id: spacer6
            width: 1
            height: 40
        }

        Row {
            Text {
                height: 50
                width: 225
                text: "Beginning"
                font.pixelSize: 16
                font.bold: true
            }
            Rectangle {
                id: spacer5
                width: 40
                height: 10
            }
            Text {
                height: 50
                width: 225
                text: "Ending"
                font.pixelSize: 16
                font.bold: true
            }
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
                showPayouts: true
            }

            Rectangle {
                id: spacer2
                width: 40
                height: 10
            }

            Column {
                spacing: 5

                Row {
                    Text {
                        height: 50
                        width: 225
                        text: "System"
                        font.pixelSize: 16
                        font.bold: true
                    }
                    Text {
                        height: 50
                        width: 225
                        text: "Actual"
                        font.pixelSize: 16
                        font.bold: true
                    }
                }


                Row {
                    TextLabeled {
                        label: "Cash:"
                        text: container.model ? container.model.cashTotal.toFixed(2) : ""
                    }
                    TextLabeled {
                        label: "Cash:"
                        text: container.model ? container.model.cashTotalActual.toFixed(2) : ""
                    }
                }

                Row {
                    TextLabeled {
                        label: ""
                    }

                    TextFieldLabeled {
                        id: editCreditTips
                        label: "Credit Tips:"
                        text: container.model ? container.model.creditCardTotalTips.toFixed(2) : 0
                        onEditingFinished: container.updateIfDifferent(container.model, "creditCardTotalTips", Number(editCreditTips.text))
                    }
                }

                Row {
                    TextLabeled {
                        label: "Credit:"
                        text: container.model ? container.model.creditCardTotal.toFixed(2) : ""
                    }



                    TextFieldLabeled {
                        id: editCreditActual
                        label: "Credit:"
                        text: container.model ? container.model.creditCardTotalActual.toFixed(2) : 0
                        onEditingFinished: container.updateIfDifferent(container.model, "creditCardTotalActual", Number(editCreditActual.text))
                    }
                }

                Row {

                    TextLabeled {
                        label: "Total Take:"
                        text: container.model ? container.model.takeTotal.toFixed(2) : ""
                    }

                    TextLabeled {
                        label: "Total Take:"
                        text: container.model ? container.model.takeTotalActual.toFixed(2) : ""
                    }
                }

                Rectangle {
                    id: spacer4
                    width: 1
                    height: 40
                }

                Row {

                    TextLabeled {}

                    TextLabeled {
                        label: "Food:"
                        text: container.model ? container.model.foodTotal.toFixed(2) : ""
                    }
                }

                Row {

                    TextLabeled {}

                    TextLabeled {
                        label: "Tax:"
                        text: container.model ? container.model.taxTotal.toFixed(2) : ""
                    }
                }

                Row {

                    TextLabeled {}

                    TextLabeled {
                        label: "Alcohol:"
                        text: container.model ? container.model.barTotal.toFixed(2) : ""
                    }
                }

                Row {

                    TextLabeled {}

                    TextLabeled {
                        label: "Total Sales:"
                        text: container.model ? container.model.total.toFixed(2) : ""
                    }
                }

                Rectangle {
                    id: spacer7
                    width: 1
                    height: 40
                }

                Row {

                    TextLabeled {
                        label: "Diff:"
                        text: container.model ? container.model.discrepancy.toFixed(2) : ""
                    }

                    TextLabeled {
                        label: "Diff:"
                        text: container.model ? container.model.discrepancyActual.toFixed(2) : ""
                    }
                }


                Rectangle {
                    id: spacer3
                    width: 1
                    height: 40
                }


                Row {
                    Button {
                        id: printButton
                        width: 120
                        text: "Print Rec"
                        onClicked: {
                            printButton.forceActiveFocus();
                            saveData();
                            model.print();
                        }
                    }

                    Button {
                        width: 100
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
                                saveData();
                                if(model.closeRec()) {
                                    container.visible = false;
                                }
                            });
                            confirm.show();
                        }
                    }

                    Button {
                        width: 225
                        text: "Ok"
                        onClicked: {
                            container.close(true);
                        }
                    }
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
