import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos




Rectangle {
    id: tickets
    color: "#33FFFFFF"
    property var rec
    property bool showPaid: true

    signal ticketSelected(var ticket)

    Keys.onDownPressed: tickets.rec.selectedTicket = tickets.rec.getNextTicket(newCustomerName.text.trim(), tickets.showPaid)
    Keys.onUpPressed: tickets.rec.selectedTicket = tickets.rec.getPreviousTicket(newCustomerName.text.trim(), tickets.showPaid)

    function clearNameTextBox() {
        newCustomerName.text = "";
    }

    Column {
        id: ticketsControls
        width: parent.width
        spacing: 2

        RectangleFlashButton {
            text: "Paid Tickets: " + (tickets.showPaid ? "Shown" : "Hidden")
            onClicked: tickets.showPaid = !tickets.showPaid
        }

//        RectangleFlashButton {
//            text: "Loyalty Members"
//            onClicked: loyaltyMemberSelectDialog.show()
//        }


        TextField {
            id: newCustomerName
            maximumLength: 25
            width: parent.width
            height: 50
            placeholderText: qsTr("Customer name")
            onAccepted: {
                var ticket = rec.addTicket("Bar");
                ticket.addCustomer(newCustomerName.text);
                clearNameTextBox();
                rec.selectedTicket = ticket;
            }

            onActiveFocusChanged: {
                if(this.focus){
                    this.selectAll();
                }
            }
        }
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
                model: rec ? rec.tickets : 0

                RectangleFlashButton {
                    text: modelData.customerNames
                    flashColor: "#FFFFFF"
                    color: modelData.isPaid ? "#888888" : (modelData.hasLoyaltyMember ? "#9a26a6" : "#26a69a")
                    border.color: rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#DDDDDD" : "#777777"
                    border.width: 2
                    textColor: rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#DDDDDD" : "#212121"
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
                        ticketSelected(modelData);
                    }
                }
            }
        }
    }


}
