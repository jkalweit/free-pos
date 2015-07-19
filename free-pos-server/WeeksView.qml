import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    id: container
    width: parent.width
    height: 900
    color: "#555555"
    property var week

    Rectangle {
        id: weekContainer
        width: container.width
        height: container.height

        Row {
            Repeater {
                model: container.week ? container.week.days : 0

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

                    RecSummaryView {
                        id: lunchRec
                        width: parent.width -20
                        height: 75
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin:  30
                        rec: modelData.lunchRec

                        onClicked: {
                            pos.selectedRec = rec;
                        }
                    }

                    RecSummaryView {
                        id: dinnerRec
                        width: parent.width - 20
                        height: 175
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: lunchRec.bottom
                        anchors.topMargin:  10
                        rec: modelData.dinnerRec
                        isDinner: true

                        onClicked: {
                            pos.selectedRec = rec
                        }
                    }

                    Rectangle {
                        id: dayTotals
                        width: parent.width - 20
                        height: 225
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 300


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
                                height: modelData.lunchRec.actualTax * 0.075
                                color: "#FF7722"
                            }

                            Rectangle {
                                width: parent.width
                                height: modelData.dinnerRec.actualTax * 0.075
                                color: "#DD7700"
                            }

                            Rectangle {
                                width: parent.width
                                height: modelData.lunchRec.cog * 0.075
                                color: "#FF7777"
                            }

                            Rectangle {
                                width: parent.width
                                height: modelData.dinnerRec.cog * 0.075
                                color: "#DD1111"
                            }

                            Rectangle {
                                width: parent.width
                                height: modelData.lunchRec.laborCost * 0.075
                                color: "#7777FF"
                            }

                            Rectangle {
                                width: parent.width
                                height: modelData.dinnerRec.laborCost * 0.075
                                color: "#1111DD"
                            }

                            Rectangle {
                                width: parent.width
                                height: modelData.fixedCostTotal * 0.075
                                color: "#AA0000"
                            }

                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
//                                    anchors.bottom: parent.bottom
//                                    anchors.bottomMargin: 10
                                text: modelData.costTotal.toFixed(0)
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

                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
//                                    anchors.bottom: parent.bottom
//                                    anchors.bottomMargin: 10
                                text: modelData.salesTotal.toFixed(0)
                            }
                        }

                    }

                    EmployeeShiftsView {
                        id: lunchShifts
                        height: 110
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.top: dayTotals.bottom
                        anchors.topMargin: 10
                        rec: modelData.lunchRec
                    }

                    EmployeeShiftsView {
                        id: dinnerShifts
                        width: parent.width - 20
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: lunchShifts.bottom
                        anchors.topMargin: 10
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        rec: modelData.dinnerRec
                    }
                }
            }

            Rectangle {
                id: totals
                width: weekContainer.width / 8
                height: weekContainer.height
                border.width: 1
                border.color: "#777777"
                color: "transparent"

                Text {
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Week Totals -"
                }


                Rectangle {
                    id: weekTotals
                    width: parent.width - 20
                    height: 545
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.top: parent.top
                    anchors.topMargin: 30


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
                            height: container.week ? container.week.lunchActualTaxTotal * 0.075 : 0
                            color: "#FF9922"
                        }

                        Rectangle {
                            width: parent.width
                            height: container.week ? container.week.dinnerActualTaxTotal * 0.075 : 0
                            color: "#DD7700"
                        }

                        Rectangle {
                            width: parent.width
                            height: container.week ? container.week.lunchCogTotal * 0.075 : 0
                            color: "#FF7777"
                        }

                        Rectangle {
                            width: parent.width
                            height: container.week ? container.week.dinnerCogTotal * 0.075 : 0
                            color: "#DD1111"
                        }

                        Rectangle {
                            width: parent.width
                            height: container.week ? container.week.lunchLaborCostTotal * 0.075 : 0
                            color: "#7777FF"
                        }

                        Rectangle {
                            width: parent.width
                            height: container.week ? container.week.dinnerLaborCostTotal * 0.075 : 0
                            color: "#7777DD"
                        }

                        Rectangle {
                            width: parent.width
                            height: container.week ? container.week.fixedCostTotal * 0.075 : 0
                            color: "#AA0000"
                        }

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
//                                anchors.bottom: parent.bottom
//                                anchors.bottomMargin: 10
                            text: container.week ? container.week.costTotal.toFixed(0) : 0
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
                            height: container.week ? container.week.lunchSalesTotal * 0.075 : 0
                            color: "#11DD11"
                        }

                        Rectangle {
                            width: parent.width
                            height: container.week ? container.week.dinnerSalesTotal * 0.075 : 0
                            color: "#00AA00"
                        }

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: container.week ? container.week.salesTotal.toFixed(0) : 0
                        }
                    }

                }

            }
        }
    }


    EmployeeShiftsEdit {
        id: employeeShiftsEdit
        anchors.fill: parent
        visible: false
    }

    DialogModal {
        id: editShiftDialog
        title: "Add Shift"
        defaultFocus: employeeName
        property var rec

        function close(save) {
            if (save) {
                //editShiftDialog.model.name = editName.text
                var scheduledStartAMbool = scheduledStartAM.currentText === "AM";
                var scheduledStopAMbool = scheduledStopAM.currentText === "AM";

                editShiftDialog.rec.addShift(employeeName.currentText,
                                         editNote.text,
                                         0, //wage.text,
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
                model: [ "Aerin", "Chris", "Grace", "Jake", "John", "Keely", "Kelly", "Michael", "Sarah", "Stassie", "", "[Guest]" ]
            }

            TextFieldLabeled {
                id: editNote
                label: "Note:"
                //text: model ? model.note : ""
                placeholderText: "Note"
            }

            //TextFieldLabeled {
            //    id: wage
            //    label: "Wage:"
                //text: model ? model.note : ""
            //    placeholderText: "Wage"
            //}

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
                    color: editShift.shift && editShift.shift.isClockedIn ? "#00AA00" : "#000000"
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
                    color: editShift.shift && editShift.shift.isClockedIn ? "#00AA00" : "#000000"
                    text: editShift.shift ? editShift.shift.scheduledOrActualHours.toFixed(2) : ""
                }
                Text {
                    color: editShift.shift && editShift.shift.isClockedIn ? "#00AA00" : "#000000"
                    text: editShift.shift ? editShift.shift.startFormatted : ""
                }
                Text {
                    color: editShift.shift && editShift.shift.isClockedIn ? "#00AA00" : "#000000"
                    text: "-"
                }
                Text {
                    color: editShift.shift && editShift.shift.isClockedOut ? "#00AA00" : "#000000"
                    text: editShift.shift ? editShift.shift.endFormatted : ""
                }
                Text {
                    color: editShift.shift && editShift.shift.isClockedOut ? "#00AA00" : "#000000"
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
