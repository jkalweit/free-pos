import QtQuick 2.3
import QtQuick.Controls 1.2

DialogModal {
    id: container
    property alias title: titleText.text
    property alias text: messageText.text
    property alias buttonText: okButton.text
    property bool closeOnAcknowledge: true
    signal acknowledged()

    customContent: Column {
        spacing: 40

        Text {
            id: titleText
            font.pixelSize: 18
            font.bold: true
        }

        Text {
            id: messageText
        }

        Row {
            Button {
                id: okButton
                text: "Ok"
                onClicked: {
                    if(closeOnAcknowledge)
                        container.visible = false;

                    acknowledged();
                }
            }
        }
    }

}
