import QtQuick 2.3
import QtQuick.Controls 1.2

DialogModal {
    id: container
    property alias title: titleText.text
    property alias text: messageText.text
    signal yes;
    signal no;

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
                text: "Yes"
                onClicked: {
                    container.visible = false;
                    yes();
                }
            }
        }

        Row {
            Button {
                text: "No"
                onClicked: {
                    container.visible = false;
                    no();
                }
            }
        }
    }

}
