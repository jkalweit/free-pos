import QtQuick 2.3

Rectangle {
    id: container
    signal beforeFlash
    signal clicked
    property string flashColor: "#FF000000"
    property int flashDuration: 100


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            container.beforeFlash(); // to change color before flash -JDK
            flash.start();
            container.clicked();
        }
    }

    SequentialAnimation {
        id: flash
        PropertyAnimation { target: container; properties: "color"; to: container.flashColor; duration: 0; }
        PropertyAnimation { target: container; properties: "color"; to: container.color; duration: container.flashDuration; }
    }

}
