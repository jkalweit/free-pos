import QtQuick 2.3
import QtQuick.Controls 1.2


Rectangle {
    id: container
    width: 200
    height: 125
    color: "#DDDDFF"
    property var rec

    Text {
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
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
        width: container.width
        anchors.top: parent.top
        anchors.topMargin: 35


        Repeater {
            model: container.rec.shifts
            Rectangle {
                width: container.width
                height: 20

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.verticalCenter: parent.verticalCenter
                    text: modelData.name
                }

                Row {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        width: 25
                        color: modelData.isClockedIn ? "#00AA00" : "#000000"
                        text: modelData.scheduledOrActualHours.toFixed(2)
                    }
                    Text {
                        width: 32
                        color: modelData.isClockedIn ? "#00AA00" : "#000000"
                        text: modelData.scheduledOrActualStartFormatted + "-"
                    }
                    Text {
                        width: 30
                        color: modelData.isClockedOut ? "#00AA00" : "#000000"
                        text: modelData.scheduledOrActualEndFormatted
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        editShift.rec = container.rec;
                        editShift.shift = modelData;
                        editShift.visible = true;
                    }
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
                                         wage.text,
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

            TextFieldLabeled {
                id: wage
                label: "Wage:"
                //text: model ? model.note : ""
                placeholderText: "Wage"
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

    DialogModal {
        id: editShift
        title: "Shift"
        color: "#FF0000"
        defaultFocus: employeeNote
        property var rec
        property var shift

        function close(save) {
            if (save) {
                editShift.shift.note = employeeNote.text;
            }

            editShift.visible = false
        }

        customContent: Column {
            spacing: 5


            TextLabeled {
                text: editShift.shift ? editShift.shift.name : ""
            }

            TextFieldLabeled {
                id: employeeNote
                label: "Note:"
                text: editShift.shift ? editShift.shift.note : ""
                placeholderText: "Note"
            }


            Row {
                spacing: 5
                Text {
                    width: 75
                    text: "Scheduled:"
                }
                Text {
                    color: modelData.isClockedIn ? "#00AA00" : "#000000"
                    text: editShift.shift ? editShift.shift.scheduledHours.toFixed(2) : ""
                }
                Text {
                    text: editShift.shift ? editShift.shift.scheduledStartFormatted : ""
                }
                Text {
                    text: "-"
                }
                Text {
                    text: editShift.shift ? editShift.shift.scheduledEndFormatted : ""
                }
            }


            Row {
                spacing: 5
                Text {
                    width: 75
                    text: "Actual:"
                }
                Text {
                    color: modelData.isClockedIn ? "#00AA00" : "#000000"
                    text: editShift.shift ? editShift.shift.scheduledOrActualHours.toFixed(2) : ""
                }
                Text {
                    color: modelData.isClockedIn ? "#00AA00" : "#000000"
                    text: editShift.shift ? editShift.shift.startFormatted : ""
                }
                Text {
                    color: modelData.isClockedIn ? "#00AA00" : "#000000"
                    text: "-"
                }
                Text {
                    color: modelData.isClockedOut ? "#00AA00" : "#000000"
                    text: editShift.shift ? editShift.shift.endFormatted : ""
                }
                Text {
                    color: modelData.isClockedOut ? "#00AA00" : "#000000"
                    text: editShift.shift ? "$" + editShift.shift.cost.toFixed(2) : ""
                }
            }

            Row {
                Button {
                    text: "Clock In"
                    onClicked: editShift.shift.clockIn();
                    enabled: editShift.shift ? editShift.shift.canClockIn : false;
                }
                Button {
                    text: "Clock Out"
                    onClicked: editShift.shift.clockOut();
                    enabled: editShift.shift ? editShift.shift.canClockOut : false;
                }
                Button {
                    text: "Ok"
                    onClicked: {
                        editShift.close(true)
                    }
                }
            }
        }
    }

}
