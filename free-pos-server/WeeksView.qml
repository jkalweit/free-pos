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
                height: 300
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

                            RecSummaryView {
                                id: lunchRec
                                width: (parent.width / 2) -20
                                height: 75
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin:  195
                                rec: modelData.lunchRec

                                onClicked: {
                                    pos.selectedRec = rec;
                                }
                            }

                            RecSummaryView {
                                id: dinnerRec
                                width: (parent.width / 2) - 20
                                height: 175
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin:  10
                                rec: modelData.dinnerRec

                                onClicked: {
                                    pos.selectedRec = rec;
                                }
                            }

                            Rectangle {
                                id: dayCost
                                width: (parent.width / 2) -20
                                height: 100 // modelData.costTotal * 0.075
                                anchors.right: parent.right
                                anchors.rightMargin: 10
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 10
                                color: "#FF7777"
                            }

                            Rectangle {
                                width: (parent.width / 2) -20
                                height: modelData.salesTotal * 0.075
                                anchors.right: parent.right
                                anchors.rightMargin: 10 + dayCost.width
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 10
                                color: "#77FF77"
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
