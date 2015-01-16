import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    id: container
    width: 100
    height: 62
    color: "blue"
    property var summaries

    onSummariesChanged: {
        console.log("hello" + container.summaries);
//        console.log("Summaries changed!" + container.summaries.length);
    }

    Column {
        Repeater {
            model: container.summaries ? container.summaries : 1

            Rectangle {
                width: 200
                height: 20
                color: "red"

//                Text {
//                    anchors.left: parent.left
//                    anchors.leftMargin: 0
//                    anchors.verticalCenter: parent.verticalCenter
//                    text: modelData.name
//                }

//                Row {
//                    anchors.right: parent.right
//                    anchors.verticalCenter: parent.verticalCenter
//                    Text {
//                        width: 25
//                        color: modelData.isClockedIn ? "#00AA00" : "#000000"
//                        text: modelData.scheduledOrActualHours.toFixed(2)
//                    }
//                    Text {
//                        width: 32
//                        color: modelData.isClockedIn ? "#00AA00" : "#000000"
//                        text: modelData.scheduledOrActualStartFormatted + "-"
//                    }
//                    Text {
//                        width: 30
//                        color: modelData.isClockedOut ? "#00AA00" : "#000000"
//                        text: modelData.scheduledOrActualEndFormatted
//                    }
//                }

//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//    //                    editShift.rec = container.rec;
//    //                    editShift.shift = modelData;
//    //                    editShift.visible = true;
//                    }
//                }
            }
        }

        Button {
            text: "Close"
            onClicked: container.visible = false
        }

        Button {
            text: "Refresh"
            onClicked: pos.selectedWeek.fireEmployeeShiftsSummariesChanged()
        }
    }
}
