import QtQuick 2.3
import QtQuick.Controls 1.2


Rectangle {
    id: container
    width: 200
    height: 125
    property var rec

    Text {
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        text: container.rec.name + " Shifts"
    }

    Button {
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        width: 25
        text: "+"
        onClicked: {
            editShiftDialog.rec = container.rec;
            editShiftDialog.visible = true;
        }
    }

    Column {
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 35


        Repeater {
            model: container.rec.shifts
            Rectangle {
                width: parent.width
                height: 20

                Rectangle {
                    width: 10
                    height: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#DDDDDD"
                }

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    text: modelData.name
                }

                Text {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text: modelData.scheduledHours.toFixed(2) + ": " + modelData.scheduledStartFormatted + " - " + modelData.scheduledEndFormatted
                }
            }
        }
    }

    DialogModal {
        id: editShiftDialog
        title: "Edit Shift"
        defaultFocus: employeeName
        property var rec

        function close(save) {
            if (save) {
                //editShiftDialog.model.name = editName.text
                var scheduledStartAMbool = scheduledStartAM.currentText === "AM";
                var scheduledStopAMbool = scheduledStopAM.currentText === "AM";

                editShiftDialog.rec.addShift(employeeName.currentText,
                                         editNote.text,
                                         scheduledStartHour.text,
                                         scheduledStartMinute.text,
                                         scheduledStartAMbool,
                                         scheduledStopHour.text,
                                         scheduledStopMinute.text,
                                         scheduledStopAMbool);
            }

            editShiftDialog.visible = false
        }

        customContent: Column {
            spacing: 5


            ComboBox {
                id: employeeName
                width: 150
                model: [ "Aerin", "Jake", "Keely", "Kelly", "Khallid", "Leslie", "Stassie", "Thatcher", "Will" ]
            }

            TextFieldLabeled {
                id: editNote
                label: "Note:"
                //text: model ? model.note : ""
                placeholderText: "Note"
            }

            Row {
                Text {
                    width: 75
                    text: "Scheduled:"
                }
                TextField {
                    id: scheduledStartHour
                    width: 25
                }
                Text {
                    text: ":"
                }
                TextField {
                    id: scheduledStartMinute
                    width: 25
                }
                ComboBox {
                    id: scheduledStartAM
                    width: 50
                    model: [ "PM", "AM" ]
                }

                Text {
                    text: "   to   "
                }
                TextField {
                    id: scheduledStopHour
                    width: 25
                }
                Text {
                    text: ":"
                }
                TextField {
                    id: scheduledStopMinute
                    width: 25
                }
                ComboBox {
                    id: scheduledStopAM
                    width: 50
                    model: [ "PM", "AM" ]
                }
            }

            Row {
                Button {
                    text: "Ok"
                    onClicked: {
                        editShiftDialog.close(true)
                    }
                }
                Button {
                    text: "Cancel"
                    onClicked: {
                        editShiftDialog.close(false)
                    }
                }
            }
        }
    }

}
