import QtQuick 2.3
import QtQuick.Controls 1.2

DialogModal {
    id: container
    property alias title: titleText.text
    property alias text: messageText.text

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
                text: "Ok"
                onClicked: container.visible = false
            }
        }
    }

}
