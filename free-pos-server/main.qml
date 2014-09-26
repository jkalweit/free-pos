import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Column {
        Row {
            Button {
                text: "Open InMemory DB"
                onClicked: server.openDb()
            }
            Button {
                text: "Open freeposdb.db3"
                onClicked: server.openDb("freeposdb.db3")
            }
        }

        Button {
            text: "Create DB"
            onClicked: server.createDb()
        }
        Button {
            text: "Add Test Data"
            onClicked: server.addTestData()
        }
    }


}
