import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import FreePos 1.0 as FreePos

ApplicationWindow {
    visible: true
    width: 1020
    height: 480
    title: qsTr("Free Pos")

    property var customerBeingEdited
    property bool showEditCustomerDialog: false

//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("File")
//            MenuItem {
//                text: qsTr("&Open")
//                onTriggered: console.log("Open action triggered");
//            }
//            MenuItem {
//                text: qsTr("Exit")
//                onTriggered: Qt.quit();
//            }
//        }
//    }

    Rectangle {
        id: container
        color: "#333333"
        anchors.fill: parent


        Column {
            id: tickets
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.top: parent.top
            anchors.topMargin: 2
            width: 200
            spacing: 2

            TextField {
                id: newCustomerName
                maximumLength: 25
                width: parent.width
                placeholderText: qsTr("Customer name")
                onAccepted: {
                    //console.log("New ticket: " + newTicketName.text)
                    var ticket = rec.addTicket("Bar");
                    ticket.addCustomer(newCustomerName.text);
                    newTicketName.text = "";
                    rec.selectedTicket = ticket;
                }

                onActiveFocusChanged: {
                    if(this.focus){
                        this.selectAll();
                    }
                }
            }




            Repeater {
                model: rec.tickets

                Rectangle {
                    visible: modelData.name.indexOf(newCustomerName.text.toUpperCase()) > -1
                    width: tickets.width
                    height: 25
                    color:  rec.selectedTicket && (rec.selectedTicket.id == modelData.id) ? "#9999FF" : "#2222FF"
                    Text {
                        text: modelData.name + ": " + modelData.customerNames
                        color: rec.selectedTicket && (rec.selectedTicket.id == modelData.id) ? "#000000" : "#DDDDDD"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            rec.selectedTicket = modelData
                        }
                    }
                }
            }
        }


        Rectangle {
            id: ticket
            visible: rec.selectedTicket
            color: "white"
            width: 400
            height: ticketInner.height + (ticketInner.anchors.margins * 2)
            anchors.left: tickets.right
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5

            Column {
                id: ticketInner
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right                
                anchors {
                    margins: 40
                    topMargin: 20
                }

                spacing: 10

                Row {
                    anchors.right: ticketInner.right
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Table: "
                    }

                    ComboBox {
                        model: ListModel {
                            id: model
                            ListElement { text: "Bar"; }
                            ListElement { text: "Deck"; }
                            ListElement { text: "1-1"; }
                            ListElement { text: "1-2"; }
                            ListElement { text: "1-3"; }
                            ListElement { text: "1-4"; }
                            ListElement { text: "1-5"; }
                            ListElement { text: "1-6"; }
                            ListElement { text: "1-7"; }
                            ListElement { text: "1-8"; }
                        }
                        onCurrentIndexChanged: {
                            rec.selectedTicket.name = currentText;
                        }
                    }
                }

//                Text {
//                    text: rec.selectedTicket ? rec.selectedTicket.name : ""
//                    font.bold: true
//                    font.pixelSize: 18
//                }

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

                            Text {
                                id: customerName
                                text: modelData.name
                                font.bold: true                                

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        customerBeingEdited = modelData;
                                        showEditCustomerDialog = true;
                                        editCustomerName.forceActiveFocus();
                                        editCustomerName.selectAll();
                                    }
                                }
                            }

                            Column {
                                id: orderItems
                                anchors.left: parent.left
                                anchors.leftMargin: 20
                                anchors.right: parent.right
                                spacing: 5

                                Repeater {
                                    model: modelData.orderItems

                                    Rectangle {
                                        id: orderItem
                                        width: orderItems.width
                                        height: 20
                                        Text {
                                            anchors.left: parent.left
                                            anchors.leftMargin: 5
                                            text: modelData.quantity
                                        }
                                        Text {
                                            anchors.left: parent.left
                                            anchors.leftMargin: 30
                                            text: modelData.name
                                        }
                                        Text {
                                            anchors.right: parent.right
                                            text: "$" + modelData.subTotal.toFixed(2);
                                        }
                                    }


                                }
                            }
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

        DropShadow {
            visible: rec.selectedTicket
            anchors.fill: ticket
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 16
            color: "#80000000"
            source: ticket
            fast: true
        }


        Column {
            id: menuItems
            visible: menu.selectedCategory
            anchors.right: menuCategories.left
            anchors.rightMargin: 2
            anchors.top: parent.top
            anchors.topMargin: 2
            width: 200
            spacing: 2

            Row {
                TextField {
                    id: newMenuItemName
                    maximumLength: 20
                    width: menuItems.width - newMenuItemPrice.width
                    placeholderText: qsTr("Menu item name")
                    onAccepted: {
                        if(menu.selectedCategory) {
                            if(menu.selectedCategory.addMenuItem(newMenuItemName.text, "Food", newMenuItemPrice.text)) {
                                newMenuItemName.text = "";
                                newMenuItemPrice.text = "";
                            }
                        }
                    }

                    onActiveFocusChanged: {
                        if(this.focus){
                            this.selectAll();
                        }
                    }
                }
                TextField {
                    id: newMenuItemPrice
                    width: 75
                    placeholderText: qsTr("Price")
                    onAccepted: {
                        if(menu.selectedCategory) {
                            if(menu.selectedCategory.addMenuItem(newMenuItemName.text, "Food", newMenuItemPrice.text)) {
                                newMenuItemName.text = "";
                                newMenuItemPrice.text = "";
                            }
                        }
                    }

                    onActiveFocusChanged: {
                        if(this.focus){
                            this.selectAll();
                        }
                    }
                }
            }



            Repeater {
                model: menu.selectedCategory ? menu.selectedCategory.menuItems : 0

                Rectangle {
                    id: menuItemContainer
                    width: menuItems.width
                    height: 25
                    color:  "#DD66FF"
                    Text {
                        text: modelData.name
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                    }
                    Text {
                        text: modelData.price.toFixed(2)
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            flash.start();
                            if(rec.selectedTicket) {
                                rec.selectedTicket.customers[0].addOrderItem(modelData.name, modelData.type, modelData.price, 1, "");
                            }
                        }
                    }

                    SequentialAnimation {
                        id: flash
                        PropertyAnimation { target: menuItemContainer; properties: "color"; to: "white"; duration: 25; }
                        PropertyAnimation { target: menuItemContainer; properties: "color"; to: "#DD66FF"; duration: 25; }
                    }

                }
            }
        }

        Column {
            id: menuCategories
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.top: parent.top
            anchors.topMargin: 2
            width: 200
            spacing: 2

            TextField {
                id: newMenuCategoryName
                maximumLength: 32
                width: parent.width
                placeholderText: qsTr("Category name")
                onAccepted: {
                    menu.addCategory(newMenuCategoryName.text);
                    newMenuCategoryName.text = ""
                }

                onActiveFocusChanged: {
                    if(this.focus){
                        this.selectAll();
                    }
                }
            }




            Repeater {
                model: menu.categories

                Rectangle {
                    width: menuCategories.width
                    height: 25
                    color:  menu.selectedMenuCategory && menu.selectedMenuCategory.id == modelData.id ? "#DD66FF" : "#AA00DD"
                    Text {
                        text: modelData.name
                        color: menu.selectedMenuCategory && menu.selectedMenuCategory.id == modelData.id ? "#000000" : "#DDDDDD"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            menu.selectedCategory = modelData
                        }
                    }
                }
            }
        }


        Rectangle {
            visible: showEditCustomerDialog
            anchors.fill: parent
            color: "#DD000000"

            Row {
                anchors.centerIn: parent

                Text {
                    text: "Name: "
                }

                TextField {
                    id: editCustomerName
                    text: customerBeingEdited ? customerBeingEdited.name : ""
                    width: 150
                    maximumLength: 25
                    placeholderText: qsTr("Customer name")
                    onAccepted: {
                        customerBeingEdited.name = editCustomerName.text;
                        showEditCustomerDialog = false;
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
                        showEditCustomerDialog = false;
                    }
                }
            }
        }









    }


}
