import QtQuick 2.0

RectangleFlash {
    width: parent ? parent.width : buttonText.width + (buttonText.anchors.leftMargin * 2)
    height: buttonText.height + (verticalMargin * 2)
    property alias text: buttonText.text
    property alias textColor: buttonText.color
    property int verticalMargin: 10

    Text {
        id: buttonText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
    }
}
