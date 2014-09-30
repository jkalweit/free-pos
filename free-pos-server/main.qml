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
        }


        Rectangle {
            id: editCustomerDialog
            visible: false
            anchors.fill: parent
            color: "#AA000000"
            property var model

            function show(customer) {
                editCustomerDialog.model = customer
                editCustomerDialog.visible = true
                editCustomerName.forceActiveFocus();
                editCustomerName.selectAll();
            }

            function close(save) {
                if(save) {
                    editCustomerDialog.model.name = editCustomerName.text;
                }
                editCustomerDialog.visible = false;
            }

            Rectangle {
                width: editCustomerInner.width + 80
                height: editCustomerInner.height + 80
                anchors.centerIn: parent
                color: "#FFFFFF"
                border.color: "#000000"
                border.width: 2

                Column {
                    id: editCustomerInner
                    anchors.centerIn: parent
                    spacing: 20

                    Text {
                        text: "Edit Customer"
                        font.bold: true
                        font.pixelSize: 20
                    }

                    Column {

                        Row {

                            Text {
                                text: "Name: "
                            }


                            TextField {
                                id: editCustomerName
                                text: editCustomerDialog.model ? editCustomerDialog.model.name : ""
                                width: 150
                                maximumLength: 25
                                placeholderText: qsTr("Customer name")
                                onAccepted: {
                                    editCustomerDialog.close(true);
                                }

                                onActiveFocusChanged: {
                                    if(this.focus){
                                        this.selectAll();
                                    }
                                }
                            }

                            Button {
                                text: "Ok"
                                onClicked: {
                                    editCustomerDialog.close(true);
                                }
                            }
                            Button {
                                text: "Cancel"
                                onClicked: {
                                    editCustomerDialog.close(false);
                                }
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: editOrderItemDialog
            anchors.fill: parent
            visible: false
            color: "#AA000000"
            property var model //OrderItem

            function show(orderItem) {
                editOrderItemDialog.model = orderItem;
                editOrderItemDialog.visible = true;
                editNote.forceActiveFocus();
                editNote.cursorPosition = editNote.text.length;
            }


            function close(save) {
                if(save) {
                    editOrderItemDialog.model.quantity = Number(editQuantity.text);
                    editOrderItemDialog.model.price = Number(editPrice.text);
                    editOrderItemDialog.model.note = editNote.text.trim();
                }
                editOrderItemDialog.visible = false;
            }

            Rectangle {
                width: orderItemEditInner.width + 80
                height: orderItemEditInner.height + 80
                anchors.centerIn: parent
                color: "#FFFFFF"
                border.color: "#000000"
                border.width: 2
                Column {
                    id: orderItemEditInner
                    anchors.centerIn: parent
                    spacing: 20


                    Text {
                        text: "Edit Order Item"
                        font.bold: true
                        font.pixelSize: 20
                    }

                    Column {
                        spacing: 5

                        Row {
                            Text {
                                width: 100
                                text: "Note: "
                            }


                            Rectangle {
                                width: 250
                                height: 100
                                border.width: 1
                                border.color: "#AAAAAA"

                                TextEdit {
                                    id: editNote
                                    text: editOrderItemDialog.model ? editOrderItemDialog.model.note : ""
                                    anchors.fill: parent
                                    anchors.margins: 5
        //                            onAccepted: {
        //                                editOrderItemDialog.close(true);
        //                            }


                                    KeyNavigation.tab: editQuantity
                                    KeyNavigation.backtab: editPrice
                                    KeyNavigation.priority: KeyNavigation.BeforeItem

                                    onActiveFocusChanged: {
//                                        if(this.focus){
//                                            this.selectAll();
//                                        }
                                    }


                                }
                            }
                        }


                        Row {
                            Text {
                                width: 100
                                text: "Quantity: "
                            }


                            TextField {
                                id: editQuantity
                                text: editOrderItemDialog.model ? Number(editOrderItemDialog.model.quantity.toFixed(2)) : ""
                                inputMethodHints: Qt.ImhFormattedNumbersOnly
                                width: 150
                                maximumLength: 25
                                placeholderText: qsTr("Quantity")

                                onAccepted: {
                                    editOrderItemDialog.close(true);
                                }

                                onActiveFocusChanged: {
                                    if(this.focus){
                                        this.selectAll();
                                    }
                                }
                            }
                        }

                        Row {

                            Text {
                                width: 100
                                text: "Price: "
                            }


                            TextField {
                                id: editPrice
                                text: editOrderItemDialog.model ? Number(editOrderItemDialog.model.price.toFixed(2)) : ""
                                width: 150
                                maximumLength: 25
                                inputMethodHints: Qt.ImhFormattedNumbersOnly
                                placeholderText: qsTr("Price")
                                onAccepted: {
                                    editOrderItemDialog.close(true);
                                }

                                onActiveFocusChanged: {
                                    if(this.focus){
                                        this.selectAll();
                                    }
                                }
                            }


                            Button {
                                text: "Ok"
                                onClicked: {
                                    editOrderItemDialog.close(true);
                                }
                            }
                            Button {
                                text: "Cancel"
                                onClicked: {
                                    editOrderItemDialog.close(false);
                                }
                            }
                            Button {
                                text: (editOrderItemDialog.model && editOrderItemDialog.model.deleted) ? "Un-Delete" : "Delete"
                                onClicked: {
                                    editOrderItemDialog.model.deleted = !editOrderItemDialog.model.deleted;
                                    editOrderItemDialog.close(true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }


}
