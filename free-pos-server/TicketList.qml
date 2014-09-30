import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos


Column {
    id: tickets
    spacing: 2

    TextField {
        id: newCustomerName
        maximumLength: 25
        width: parent.width
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



    Repeater {
        model: rec.tickets

        Rectangle {
            visible: {
                var filter = newCustomerName.text.trim().toUpperCase()
                if(filter.length === 0){
                    return true;
                }
                return modelData.customerNames.toUpperCase().indexOf(filter) > -1;
            }
            width: tickets.width
            height: 25
            color:  rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#9999FF" : "#2222FF"
            Text {
                text: modelData.customerNames // modelData.longName
                color: rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#000000" : "#DDDDDD"
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
