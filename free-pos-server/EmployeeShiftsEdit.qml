import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    id: container
    anchors.fill: parent
    color: "blue"


    Column {
        Button {
            text: "X"
            onClicked: container.visible = false;
        }
        Button {
            text: "Text"
            onClicked: editShiftDialog.visible = true;
        }
    }


}
