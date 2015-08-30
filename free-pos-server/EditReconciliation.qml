import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtMultimedia 5.0


Rectangle {
    id: container
    color: "#333333"
    anchors.fill: parent
    property var model
    visible: model ? true : false


    MouseArea {
        id: preventClickThrough
        anchors.fill: parent
        onClicked: {
            // do nothing
        }
    }


    TicketList {
        id: ticketList
        rec: model
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.bottom: parent.bottom
        width: 250

        onTicketSelected: {
            rec.selectedTicket = ticket;
        }
    }

    Button {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        text: "x"
        onClicked: {
            pos.unselectRec();
        }
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
                            property var model: modelData

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
                                        color: modelData.isSubmitted ? "transparent" : "#9977DD77"
                                        //property alias flash: flashAnimation
                                        visible: !(modelData.deleted && !modelData.isSubmitted) // do not show if deleted and not submitted

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

                                            Repeater {
                                                model: modelData.orderItemOptions

                                                Text {
                                                    anchors.left: orderItemInner.left
                                                    anchors.leftMargin: 40
                                                    text: "*" + modelData.menuItemName
                                                }
                                            }

                                            Repeater {
                                                model: modelData.orderItemInventoryItems

                                                Text {
                                                    anchors.left: orderItemInner.left
                                                    anchors.leftMargin: 40
                                                    visible: (!modelData.isAdded && modelData.isRemoved) || (modelData.isAdded && !modelData.isRemoved)
                                                    text: modelData.name
                                                    font.strikeout: modelData.isRemoved
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


                                        onClicked: {
                                            editOrderItemDialog.rec = container.model
                                            //editOrderItemDialog.customer = customer.model
                                            editOrderItemDialog.show(model)
                                        }
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

                        Row {

//                            RectangleFlash {
//                                width: ticketControls.width / 2
//                                height: printKitchen.height + 30
//                                onClicked: {
//                                    model.selectedTicket.printKitchen();
//                                }

//                                customContent: Text{
//                                    id: printKitchen
//                                    text: "Print Kitch"
//                                    anchors.verticalCenter: parent.verticalCenter
//                                }
//                            }

                            RectangleFlash {
                                width: ticketControls.width
                                height: sendKitchen.height + 30
                                onClicked: {
                                    model.selectedTicket.sendKitchen();
                                    model.selectedTicket.printKitchen();
                                }

                                customContent: Text{
                                    id: sendKitchen
                                    text: "Send Kitchen"
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }
                        }



                        RectangleFlash {
                            width: parent.width
                            height: printReceipt.height + 30
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
                            height: paidText.height + 30
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
//                        Rectangle {
//                            width: parent.width
//                            height: 15
//                            Text {
//                                text: "Cost:"
//                                anchors.left: parent.left
//                            }
//                            Text {
//                                text: model.selectedTicket ? model.selectedTicket.cog.toFixed(2) + "+" + model.selectedTicket.actualTax.toFixed(2) : ""
//                                anchors.right: parent.right
//                            }
//                        }
//                        Rectangle {
//                            width: parent.width
//                            height: 15
//                            Text {
//                                text: "Margin:"
//                                anchors.left: parent.left
//                            }
//                            Text {
//                                text: model.selectedTicket ? model.selectedTicket.margin.toFixed(2) : ""
//                                anchors.right: parent.right
//                            }
//                        }
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                visible: !model.isOpen
                onClicked: {
                    // do nothing, prevent click through
                }
            }
        }
    }

    MenuView {
        id: menuView
        visible: model ? model.isOpen : false
        menu: pos.selectedMenu ? pos.selectedMenu : 0
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 500

        onMenuItemSelected: {
            if(model && model.selectedTicket) {
                var orderItem = model.selectedTicket.customers[0].addOrderItem(menuItem, 1, "");
                if(orderItem.type !== 'Alcohol') {
                    editOrderItemDialog.rec = container.model
                    //editOrderItemDialog.customer = customer.model
                    editOrderItemDialog.show(orderItem)
                }
            }
        }
    }



    Rectangle {
        id: recTotals
        width: 200
        height: 200
        anchors.right: container.right
        anchors.rightMargin: menuView.width
        anchors.bottom: container.bottom
        opacity: 0.80
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
//            Rectangle {
//                width: parent.width
//                height: 20
//                color: "transparent"
//                Text {
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.left: parent.left
//                    anchors.leftMargin: 5
//                    text: "Cost:"
//                }
//                Text {
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.right: parent.right
//                    anchors.rightMargin: 5
//                    text: model ? "$" + model.cost.toFixed(2) : ""
//                }
//            }
//            Rectangle {
//                width: parent.width
//                height: 20
//                color: "transparent"
//                Text {
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.left: parent.left
//                    anchors.leftMargin: 5
//                    text: "Margin:"
//                }
//                Text {
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.right: parent.right
//                    anchors.rightMargin: 5
//                    text: model ? "$" + model.margin.toFixed(2) : ""
//                }
//            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: editRecDialog.show()
        }
    }


    LoyaltyMemberSelect {
        id: loyaltyMemberSelectDialog
        onMemberSelected: {
            var ticket = model.addTicket("Bar");
            ticket.addCustomer(member.firstName + " " + member.lastName, member.id);
            ticketList.clearNameTextBox();
            model.selectedTicket = ticket;
            loyaltyMemberSelectDialog.visible = false;
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


    SoundEffect {
        id: alertSound
        source: "qrc:/airhorn.wav"
        volume: 1
    }

    Dialog {
        id: messageDialog
        visible: pos.isDialogMessageShown
        title: "Attention!"

        onVisibleChanged: {
            if(this.visible && alertSound.status) {
                console.log("Playing alert sound...");
                console.log("Status: " + alertSound.status);
                alertSound.play();
            }else {
                console.log("Not playing sound.")
            }
        }

        contentItem: Rectangle {
            color: "#B71C1C"
            implicitWidth: 400
            implicitHeight: 400
            Text {
                id: message
                text: pos.dialogMessage
                color: "white"
                font.pixelSize: 16
                font.bold: true
                anchors.centerIn: parent
            }
        }
    }

}
