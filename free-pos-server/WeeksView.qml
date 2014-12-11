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
                            width: weekContainer.width / 8
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

//                            RecSummaryView {
//                                id: lunchRec
//                                width: (parent.width / 2) -20
//                                height: 75
//                                anchors.left: parent.left
//                                anchors.leftMargin: 10
//                                anchors.bottom: parent.bottom
//                                anchors.bottomMargin:  195
//                                rec: modelData.lunchRec

//                                onClicked: {
//                                    pos.selectedRec = rec;
//                                }
//                            }

//                            RecSummaryView {
//                                id: dinnerRec
//                                width: (parent.width / 2) - 20
//                                height: 175
//                                anchors.left: parent.left
//                                anchors.leftMargin: 10
//                                anchors.bottom: parent.bottom
//                                anchors.bottomMargin:  10
//                                rec: modelData.dinnerRec

//                                onClicked: {
//                                    pos.selectedRec = rec
//                                }
//                            }

                            Column {
                                id: dayCost
                                spacing: 1
                                width: (parent.width - 20) / 2
                                anchors.right: parent.right
                                anchors.rightMargin: 10
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 10

                                Rectangle {
                                    width: parent.width
                                    height: modelData.lunchRec.cost * 0.075
                                    color: "#FF7777"
                                }


                                Rectangle {
                                    width: parent.width
                                    height: modelData.dinnerRec.cost * 0.075
                                    color: "#DD1111"
                                }

                                Rectangle {
                                    width: parent.width
                                    height: modelData.fixedCostTotal * 0.075
                                    color: "#AA0000"
                                }
                            }


                            Column {
                                spacing: 1
                                width: (parent.width - 20) / 2
                                anchors.right: parent.right
                                anchors.rightMargin: 10 + dayCost.width
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 10


                                Rectangle {
                                    width: parent.width
                                    height: modelData.lunchRec.total * 0.075
                                    color: "#11DD11"
                                }

                                Rectangle {
                                    width: parent.width
                                    height: modelData.dinnerRec.total * 0.075
                                    color: "#00AA00"
                                }
                            }
                        }
                    }

                    Rectangle {
                        width: weekContainer.width / 8
                        height: weekContainer.height
                        border.width: 1
                        border.color: "#777777"
                        color: "transparent"

                        Text {
                            anchors.top: parent.top
                            anchors.topMargin: 10
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Week Totals"
                        }


                        Column {
                            id: weekCost
                            spacing: 1
                            width: (parent.width - 20) / 2
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 10

                            Rectangle {
                                width: parent.width
                                height: modelData.cogTotal * 0.075
                                color: "#FF7777"
                            }

                            Rectangle {
                                width: parent.width
                                height: modelData.fixedCostTotal * 0.075
                                color: "#AA0000"
                            }
                        }


                        Column {
                            spacing: 1
                            width: (parent.width - 20) / 2
                            anchors.right: parent.right
                            anchors.rightMargin: 10 + weekCost.width
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 10

                            Rectangle {
                                width: parent.width
                                height: modelData.salesTotal * 0.075
                                color: "#00AA00"
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
