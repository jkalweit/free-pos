import QtQuick 2.3
import QtQuick.Controls 1.2


DialogModal {
    id: container
    title: "Select Loyalty Member"

    signal memberSelected(var member)

    customContent: Column {
        id: controls
        spacing: 2


        TextField {
            id: memberName
            maximumLength: 25
            width: parent.width
            height: 50
            placeholderText: "Member name"

            onActiveFocusChanged: {
                if(this.focus){
                    this.selectAll();
                }
            }
        }
        Flickable {
            height: 600
            width: 200
            contentWidth: membersInner.width
            contentHeight: membersInner.height
            clip: true

            Column {
                id: membersInner
                width: 200
                Repeater {
                    model: pos ? pos.loyaltyMembers : 0

                    RectangleFlashButton {
                        text: modelData.firstName + " " + modelData.lastName + ": " + modelData.pointsBalance
                        flashColor: "#FFFFFF"
                        color: "#26a69a"
                        border.color: "#777777" // rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#DDDDDD" : "#777777"
                        border.width: 2
                        textColor: "#212121" //rec.selectedTicket && (rec.selectedTicket.id === modelData.id) ? "#DDDDDD" : "#212121"
                        onBeforeFlash: {
                            memberSelected(modelData);
                        }
                    }
                }
            }
        }
    }
}
