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
    property bool saveByDefault: true

    MouseArea {
        id: preventClickThrough
        anchors.fill: parent
        onClicked: {
            if(saveByDefault) {
                if(dialogModal.close) {
                    dialogModal.close(true);
                }
                else {
                    dialogModal.visible = false;
                }
            }
        }
    }

    function show() {
        this.visible = true
        if(defaultFocus) {
            this.forceActiveFocus(); // to take away focus from defaultFocus in order to trigger ActiveFocusChanged when we forceActiveFocus()
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

        MouseArea {
            id: preventClickThroughInner
            anchors.fill: parent
        }

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
