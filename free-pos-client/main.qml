import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle {
        id: container
        color: "#333333"
        anchors.fill: parent




        Column {
            id: controls
            Button {
                text: "Connect to Server"
                onClicked: client.connectToServer("127.0.0.1", 1337)
            }
            Button {
                text: "Get Menu Categories"
                onClicked: client.getMenuCategories()
            }
        }

        Column {
            id: menuCategories
            anchors.right: parent.right
            spacing: 2

            Repeater {
                model: menu.categories

                Rectangle {
                    width: 150
                    height: 25
                    color: "#3333FF"
                    Text {
                        text: modelData.name
                        color: "#dddddd"
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            menu.selectedCategory = modelData
                        }
                    }
                }
            }
        }

        Column {
            id: menuItems
            anchors.right: menuCategories.left
            anchors.rightMargin: 2
            spacing: 2

            Repeater {
                model: (menu.selectedCategory ? menu.selectedCategory.menuItems : 0)

                Rectangle {
                    width: 150
                    height: 25
                    color: "#6666FF"
                    Text {
                        text: modelData.name
                        color: "white"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                    }

                    Text {
                        text: modelData.price
                        color: "white"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: console.log("Selected item: " + modelData.id)
                    }
                }
            }
        }
    }
}
