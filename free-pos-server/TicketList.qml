import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos




Rectangle {
    id: tickets
    property bool showPaid: false

    Column {
        id: ticketsControls
        width: parent.width
        spacing: 2

        RectangleFlashButton {
            text: tickets.showPaid ? "Hide Paid" : "Show Paid"
            onClicked: tickets.showPaid = !tickets.showPaid
        }


        TextField {
            id: newCustomerName
            maximumLength: 25
            width: parent.width
            height: 50
            placeholderText: qsTr("Customer name")
            onAccepted: {
                var ticket = rec.addTicket("Bar");
                ticket.addCustomer(newCustomerName.text);
                newCustomerName.text = "";
                rec.selectedTicket = ticket;
            }

            onActiveFocusChanged: {
                if(this.focus){
                    this.selectAll();
                }
            }
        }



    //    Repeater {
    //        model: rec.tickets

    //        RectangleFlashButton {
    //            text: modelData.customerNames
    //            color:  {
    //                //if(rec.selectedTicket && (rec.selectedTicket.id === modelData.id)) {
    //                    return modelData.isPaid ? "#DDDDDD" : "#3333FF"
    //                //}
    //            }
    //            border.color: rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#DDDDDD" : "transparent"
    //            border.width: 2
    //            textColor: rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#DDDDDD" : "#000000"
    //            visible: {
    //                if(!showPaid && modelData.isPaid)
    //                    return false;
    //                var filter = newCustomerName.text.trim().toUpperCase()
    //                if(filter.length === 0){
    //                    return true;
    //                }
    //                return modelData.customerNames.toUpperCase().indexOf(filter) > -1;
    //            }
    //            onBeforeFlash: {
    //                rec.selectedTicket = modelData
    //            }
    //        }
    //    }
    }

    Flickable {
        width: tickets.width
        anchors.top: ticketsControls.bottom
        anchors.bottom: tickets.bottom
        contentWidth: ticketsInner.width
        contentHeight: ticketsInner.height
        clip: true

        Column {
            id: ticketsInner
            width: tickets.width
            Repeater {
                model: rec.tickets

                RectangleFlashButton {
                    text: modelData.customerNames
                    flashColor: "#FFFFFF"
                    color:  modelData.isPaid ? "#888888" : "#3333FF"
                    border.color: rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#DDDDDD" : "#777777"
                    border.width: 2
                    textColor: rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#DDDDDD" : "#000000"
                    visible: {
                        if(!tickets.showPaid && modelData.isPaid)
                            return false;
                        var filter = newCustomerName.text.trim().toUpperCase()
                        if(filter.length === 0){
                            return true;
                        }
                        return modelData.customerNames.toUpperCase().indexOf(filter) > -1;
                    }
                    onBeforeFlash: {
                        rec.selectedTicket = modelData
                    }
                }
            }
        }
    }


}
