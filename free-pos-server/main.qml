import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos

ApplicationWindow {
    visible: true
    width: 1020
    height: 800
    title: qsTr("CY Pos")


    Rectangle {
        id: container
        color: "#333333"
        anchors.fill: parent




        TicketList {
            id: ticketList
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
            width: 200
        }


        Rectangle {
            id: ticket
            visible: rec.selectedTicket
            color: "white"
            width: 400
            height: ticketInner.height + (ticketInner.anchors.margins * 2)
            anchors.left: ticketList.right
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5

            Column {
                id: ticketInner
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right                
                anchors.margins: 40
                spacing: 10

                RectangleFlash {
                    width: parent.width / 2
                    height: togoText.height + 20
                    anchors.right: parent.right
                    flashColor: "#000000"
                    onClicked: rec.selectedTicket.isTogo = !rec.selectedTicket.isTogo

                    Text {
                        id: togoText
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Togo: " + (rec.selectedTicket && rec.selectedTicket.isTogo ? "YES" : "No")
                        font.bold: rec.selectedTicket && rec.selectedTicket.isTogo
                        font.pixelSize: rec.selectedTicket && rec.selectedTicket.isTogo ? 20 : 16
                        color: rec.selectedTicket && rec.selectedTicket.isTogo ? "red" : "#000000"
                    }
                }

                Column {
                    id: customers
                    width: parent.width
                    spacing: 3

                    Repeater {
                        model: rec.selectedTicket ? rec.selectedTicket.customers : 0

                        Column {
                            id: customer
                            width: customers.width
                            spacing: 5

                            RectangleFlash {
                                width: parent.width
                                height: customerName.height + 10
                                onClicked: {
                                    editCustomerDialog.show(modelData);
                                }
                                Text {
                                    id: customerName
                                    text: modelData.name
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                    font.pixelSize: 16
                                }
                            }

                            Column {
                                id: orderItems
                                anchors.left: parent.left
                                anchors.leftMargin: 20
                                anchors.right: parent.right
                                spacing: 5

                                Repeater {
                                    id: orderItemsRepeater
                                    model: modelData.orderItems

                                    Rectangle {
                                        id: orderItem
                                        width: orderItems.width
                                        height: orderItemInner.height
                                        property var model: modelData
                                        //property alias flash: flashAnimation

                                        Column {
                                            id: orderItemInner
                                            width: parent.width
                                            Rectangle {
                                                width: parent.width
                                                height: 20

                                                Text {
                                                    anchors.left: parent.left
                                                    anchors.leftMargin: 0
                                                    text: Number(modelData.quantity.toFixed(2))
                                                    font.strikeout: modelData.deleted
                                                }
                                                Text {
                                                    anchors.left: parent.left
                                                    anchors.leftMargin: 40
                                                    text: modelData.name
                                                    font.strikeout: modelData.deleted
                                                }
                                                Text {
                                                    anchors.right: parent.right
                                                    text: modelData.subTotal.toFixed(2);
                                                    font.strikeout: modelData.deleted
                                                }
                                            }

                                            Text {
                                                anchors.left: parent.left
                                                anchors.leftMargin: 40
                                                text: modelData.note
                                                font.italic: true
                                                font.strikeout: modelData.deleted
                                            }

                                        }


                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: editOrderItemDialog.show(model)
                                        }

//                                        SequentialAnimation {
//                                            id: flashAnimation
//                                            PropertyAnimation { target: orderItem; properties: "color"; to: "#DD66FF"; duration: 100; }
//                                            PropertyAnimation { target: orderItem; properties: "color"; to: "transparent"; duration: 100; }
//                                        }

//                                        Component.onCompleted: {
//                                            console.log("onCompleted: " + modelData.id);
//                                            this.flash.start();
//                                        }

                                    }


                                }
                            }
                        }
                    }

                }

                Rectangle {
                    id: ticketFooter
                    width: parent.width
                    height: totals.height

                    Column {
                        id: ticketControls
                        width: parent.width / 2
                        anchors.left: parent.left


                        RectangleFlash {
                            width: parent.width
                            height: paidText.height + 10
                            onClicked: {
                                rec.selectedTicket.toggleIsPaid();
                            }

                            Text{
                                id: paidText
                                text: rec.selectedTicket && rec.selectedTicket.isPaid ? "Paid: " + Qt.formatTime(rec.selectedTicket.paidStamp, "hh:mmAP") : "Unpaid"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }

                    Column {
                        id: totals
                        anchors.right: parent.right
                        width: parent.width / 2
                        spacing: 5
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Food:"
                                anchors.left: parent.left
                            }
                            Text {
                                text: rec.selectedTicket ? rec.selectedTicket.foodTotal.toFixed(2) : ""
                                anchors.right: parent.right
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Tax:"
                                anchors.left: parent.left
                            }
                            Text {
                                text: rec.selectedTicket ? rec.selectedTicket.taxTotal.toFixed(2) : ""
                                anchors.right: parent.right
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Bar:"
                                anchors.left: parent.left
                            }
                            Text {
                                text: rec.selectedTicket ? rec.selectedTicket.barTotal.toFixed(2) : ""
                                anchors.right: parent.right
                            }
                        }
                        Rectangle {
                            width: parent.width
                            height: 15
                            Text {
                                text: "Total:"
                                anchors.left: parent.left
                                font {
                                    bold: true
                                    pixelSize: 16
                                }

                            }
                            Text {
                                text: "$" + (rec.selectedTicket ? rec.selectedTicket.total.toFixed(2) : "")
                                anchors.right: parent.right
                                font {
                                    bold: true
                                    pixelSize: 16
                                }
                            }
                        }
                    }


                }
            }

        }

        MenuView {
            id: menuView
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 400
        }

        Rectangle {
            id: recTotals
            width: 200
            height: recTotalsInner.height + 20
            anchors.right: container.right
            anchors.rightMargin: 400
            anchors.bottom: container.bottom
            Column {
                id: recTotalsInner
                anchors.top: recTotals.top
                anchors.topMargin: 10
                anchors.left: recTotals.left
                anchors.leftMargin: 10
                anchors.right: recTotals.right
                anchors.rightMargin: 10
                spacing: 5
                Rectangle {
                    width: parent.width
                    height: 20
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        text: "Current Rec:"
                    }
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        text: rec.name
                    }
                }
                Rectangle {
                    width: parent.width
                    height: 15
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        text: "Food:"
                    }
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        text: "$" + rec.foodTotal.toFixed(2)
                    }
                }
                Rectangle {
                    width: parent.width
                    height: 15
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        text: "Tax:"
                    }
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        text: "$" + rec.taxTotal.toFixed(2)
                    }
                }
                Rectangle {
                    width: parent.width
                    height: 20
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        text: "Bar:"
                    }
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        text: "$" + rec.barTotal.toFixed(2)
                    }
                }
                Rectangle {
                    width: parent.width
                    height: 20
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        text: "Total:"
                    }
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        text: "$" + rec.total.toFixed(2)
                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: editCurrentRecDialog.show()
            }
        }

        EditCustomerDialog {
            id: editCustomerDialog
        }

        EditOrderItemDialog {
            id: editOrderItemDialog
        }

        EditCurrentRecDialog {
            id: editCurrentRecDialog        
        }
    }


}
