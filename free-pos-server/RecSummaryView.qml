import QtQuick 2.0

Rectangle {
    id: container
    width: 100
    height: 100
    property var rec
    property bool isDinner: false
    signal clicked(var rec)

    color: rec.isOpen ? "#DDDDFF" : "#AAAAAA"

    Rectangle {
        width: container.width / 2
        height: rec.total * 0.075
        anchors.left: container.left
        anchors.bottom: container.bottom
        color: isDinner ? "#00AA00" : "#11DD11"

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            text: rec.total.toFixed(0)
        }
    }

    Rectangle {
        width: container.width / 2
        height:  rec.cost * 0.075
        anchors.right: container.right
        anchors.bottom: container.bottom
        color: isDinner ? "#DD1111" : "#FF7777"

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            text: rec.cost.toFixed(0)
        }
    }

    Text {
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: rec.name
    }

    MouseArea {
        anchors.fill: parent
        onClicked: container.clicked(container.rec);
    }
}
