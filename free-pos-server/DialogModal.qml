import QtQuick 2.3
import QtQuick.Controls 1.2


Rectangle {
    id: dialogModal
    anchors.fill: parent
    visible: false
    color: "#AA000000"
    property alias title: titleText.text
    property alias customContent: dialogColumn.data
    property var defaultFocus

    function show() {
        this.visible = true
        if(defaultFocus) {
            defaultFocus.forceActiveFocus();
        }
    }

    Keys.onReturnPressed: this.close(true)
    Keys.onEscapePressed: this.close(false)
    Keys.priority: Keys.BeforeItem

    Rectangle {
        width: dialogInner.width + 80
        height: dialogInner.height + 80
        anchors.centerIn: parent
        color: "#FFFFFF"
        border.color: "#000000"
        border.width: 2
        Column {
            id: dialogInner
            anchors.centerIn: parent
            spacing: 20

            Text {
                id: titleText
                font.bold: true
                font.pixelSize: 20
            }

            Column {
                id: dialogColumn
            }
        }
    }
}
