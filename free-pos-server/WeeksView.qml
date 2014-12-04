import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    id: container
    width: 100
    height: 62
    color: "#555555"

    Column {
        spacing: 5

//        Button {
//            text: "Add Week"
//            onClicked: pos.addWeek()
//        }


        Repeater {
            model: pos.weeks
            Rectangle {
                id: weekContainer
                width: container.width
                height: 200
                color: pos.selectedWeek && pos.selectedWeek.id === modelData.id ? "#DDFFDD" : "#FFFFFF"

                Row {
                    Repeater {
                        model: modelData.days

                        Rectangle {
                            width: weekContainer.width / 7
                            height: weekContainer.height
                            border.width: 1
                            border.color: "#777777"
                            color: "transparent"

                            Text {
                                anchors.top: parent.top
                                anchors.topMargin: 10
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: Qt.formatDate(modelData.date, "ddd M/d/yyyy")
                            }

                            Rectangle {
                                id: lunchRec
                                width: parent.width -20
                                height: 75
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin:  95
                                color: modelData.lunchRec.isOpen ? "#AAAAFF" : "#AAAAAA"

                                Text {
                                    anchors.centerIn: parent
                                    text: modelData.lunchRec.name + ": " + modelData.lunchRec.total.toFixed(2)
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        pos.selectedRec = modelData.lunchRec;
                                    }
                                }
                            }

                            Rectangle {
                                id: dinnerRec
                                width: parent.width -20
                                height: 75
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin:  10
                                color: modelData.dinnerRec.isOpen ? "#AAAAFF" : "#AAAAAA"

                                Text {
                                    anchors.centerIn: parent
                                    text: modelData.dinnerRec.name + ": " + modelData.dinnerRec.total.toFixed(2)
                                }


                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: pos.selectedRec = modelData.dinnerRec
                                }
                            }
                        }
                    }
                }

    //                MouseArea {
    //                    anchors.fill: parent
    //                    onClicked: {
    //                        pos.selectedWeek = modelData
    //                    }
    //                }
            }
        }
    }
}
