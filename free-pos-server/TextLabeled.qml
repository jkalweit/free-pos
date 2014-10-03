import QtQuick 2.3

Row {
    id: container
    property alias label: label.text
    property alias text: text.text

    Text {
        id: label
        width: 75
    }


    Text {
        id: text
        width: 150
    }
}

