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
            //employeeShiftsEdit.visible = true;
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
}
