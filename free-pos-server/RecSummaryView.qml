import QtQuick 2.0

Rectangle {
    id: container
    width: 100
    height: 100
    property var rec
    signal clicked(var rec)

    color: rec.isOpen ? "#AAAAFF" : "#AAAAAA"    

    Rectangle {
        width: container.width / 2
        height: rec.total * 0.075
        anchors.left: container.left
        anchors.bottom: container.bottom
        color: "#77FF77"

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
        color: "#FF7777"

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
