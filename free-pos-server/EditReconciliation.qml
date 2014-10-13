import QtQuick 2.3


Rectangle {
    id: container
    color: "#333333"
    anchors.fill: parent
    property var model
    visible: model ? true : false


    TicketList {
        id: ticketList
        rec: model
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.bottom: parent.bottom
        width: 200
    }



    Flickable {
        width: ticket.width
        contentWidth: ticket.width
        contentHeight: ticket.height
        anchors.left: ticketList.right
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        clip: true

        Rectangle {
            id: ticket
            visible: model ? model.selectedTicket : false
            color: "white"
            width: 400
            height: ticketInner.height + (ticketInner.anchors.margins * 2)

            Column {
                id: ticketInner
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 30
                spacing: 20

                RectangleFlash {
                    width: parent.width / 2
                    height: togoText.height + 20
                    anchors.right: parent.right
                    flashColor: "#000000"
                    onClicked: model.selectedTicket.isTogo = !model.selectedTicket.isTogo

                    customContent: Text {
                        id: togoText
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Togo: " + (model.selectedTicket && model.selectedTicket.isTogo ? "YES" : "No")
                        font.bold: model && model.selectedTicket && model.selectedTicket.isTogo
                        font.pixelSize: model && model.selectedTicket && model.selectedTicket.isTogo ? 20 : 16
                        color: model && model.selectedTicket && model.selectedTicket.isTogo ? "red" : "#000000"
                    }
                }

                Column {
                    id: customers
                    width: parent.width
                    spacing: 3

                    Repeater {
                        model: container.model && container.model.selectedTicket ? container.model.selectedTicket.customers : 0

                        Column {
                            id: customer
                            width: customers.width

                            RectangleFlash {
                                width: parent.width
                                height: customerName.height + 10
                                onClicked: {
                                    editCustomerDialog.model = modelData;
                                    editCustomerDialog.show();
                                }
                                customContent: Text {
                                    id: customerName
                                    text: modelData.name
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                    font.pixelSize: 20
                                }
                            }

                            Column {
                                id: orderItems
                                anchors.left: parent.left
                                anchors.leftMargin: 20
                                anchors.right: parent.right

                                Repeater {
                                    id: orderItemsRepeater
                                    model: modelData.orderItems

                                    RectangleFlash {
                                        id: orderItem
                                        width: orderItems.width
                                        height: orderItemInner.height + 20
                                        property var model: modelData
                                        //property alias flash: flashAnimation

                                        customContent: Column {
                                            id: orderItemInner
                                            width: parent.width
                                            Rectangle {
                                                width: parent.width
                                                height: 20
                                                color: "transparent"

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


                                        onClicked: editOrderItemDialog.show(model)
                                    }
                                }
                            }
                        }
                    }

                }

                Rectangle {
                    id: ticketFooter
                    width: parent.width
                    height: totals.height > ticketControls.height ? totals.height : ticketControls.height

                    Column {
                        id: ticketControls
                        width: parent.width / 2 - 10
                        anchors.left: parent.left


                        Rectangle {
                            width: parent.width
                            height:openedText.height + 20
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            Text{
                                id: openedText
                                text: model.selectedTicket ? "Opened: " + Qt.formatTime(model.selectedTicket.createdStamp, "hh:mmAP") : ""
                                anchors.verticalCenter: parent.verticalCenter
                            }

                        }

                        RectangleFlash {
                            width: parent.width
                            height: printKitchen.height + 10
                            onClicked: {
                                model.selectedTicket.printKitchen();
                            }

                            customContent: Text{
                                id: printKitchen
                                text: "Print Kitchen" //model.selectedTicket && model.selectedTicket.isPaid ? model.selectedTicket.paymentType + " " + Qt.formatTime(model.selectedTicket.paidStamp, "hh:mmAP") : "Unpaid"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }

                        RectangleFlash {
                            width: parent.width
                            height: printReceipt.height + 10
                            onClicked: {
                                model.selectedTicket.printReceipt();
                            }

                            customContent: Text{
                                id: printReceipt
                                text: "Print Receipt" //model.selectedTicket && model.selectedTicket.isPaid ? model.selectedTicket.paymentType + " " + Qt.formatTime(model.selectedTicket.paidStamp, "hh:mmAP") : "Unpaid"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }

                        RectangleFlash {
                            width: parent.width
                            height: paidText.height + 10
                            onClicked: {
                                model.selectedTicket.cyclePaymentType();
                            }

                            customContent: Text{
                                id: paidText
                                text: model.selectedTicket && model.selectedTicket.isPaid ? model.selectedTicket.paymentType + " " + Qt.formatTime(model.selectedTicket.paidStamp, "hh:mmAP") : "Unpaid"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }

                    Column {
                        id: totals
                        anchors.bottom: parent.bottom
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
                                text: model.selectedTicket ? model.selectedTicket.foodTotal.toFixed(2) : ""
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
                                text: model.selectedTicket ? model.selectedTicket.taxTotal.toFixed(2) : ""
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
                                text: model.selectedTicket ? model.selectedTicket.barTotal.toFixed(2) : ""
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
                                text: "$" + (model.selectedTicket ? model.selectedTicket.total.toFixed(2) : "")
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
    }

    MenuView {
        id: menuView
        menu: pos.selectedMenu ? pos.selectedMenu : 0
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 400

        onMenuItemSelected: {
            if(model && model.selectedTicket) {
                model.selectedTicket.customers[0].addOrderItem(menuItem.name, menuItem.type, menuItem.price, 1, "");
            }
        }
    }

    Rectangle {
        id: recTotals
        width: 200
        height: recTotalsInner.height + 20
        anchors.right: container.right
        anchors.rightMargin: 400
        anchors.bottom: container.bottom
        opacity: 0.50
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
                color: "transparent"
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
                    text: model ? model.name : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 15
                color: "transparent"
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
                    text: model ? "$" + model.foodTotal.toFixed(2) : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 15
                color: "transparent"
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
                    text: model ? "$" + model.taxTotal.toFixed(2) : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 20
                color: "transparent"
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
                    text: model ? "$" + model.barTotal.toFixed(2) : ""
                }
            }
            Rectangle {
                width: parent.width
                height: 20
                color: "transparent"
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
                    text: model ? "$" + model.total.toFixed(2) : ""
                }
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: editRecDialog.show()
        }
    }

    EditCustomerDialog {
        id: editCustomerDialog
    }

    EditOrderItemDialog {
        id: editOrderItemDialog
    }

    EditRecDialog {
        id: editRecDialog
        model: container.model
    }
}
