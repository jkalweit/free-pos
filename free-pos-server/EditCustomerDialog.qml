import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    id: editCustomerDialog
    visible: false
    anchors.fill: parent
    color: "#AA000000"
    property var model

    Keys.onEscapePressed: this.close(false)

    function show(customer) {
        editCustomerDialog.model = customer
        editCustomerDialog.visible = true
        editCustomerName.forceActiveFocus();
        editCustomerName.selectAll();
    }

    function close(save) {
        if(save) {
            editCustomerDialog.model.name = editCustomerName.text;
        }
        editCustomerDialog.visible = false;
    }

    Rectangle {
        width: editCustomerInner.width + 80
        height: editCustomerInner.height + 80
        anchors.centerIn: parent
        color: "#FFFFFF"
        border.color: "#000000"
        border.width: 2

        Column {
            id: editCustomerInner
            anchors.centerIn: parent
            spacing: 20

            Text {
                text: "Edit Customer"
                font.bold: true
                font.pixelSize: 20
            }

            Column {

                Row {

                    Text {
                        text: "Name: "
                    }


                    TextField {
                        id: editCustomerName
                        text: editCustomerDialog.model ? editCustomerDialog.model.name : ""
                        width: 150
                        maximumLength: 25
                        placeholderText: qsTr("Customer name")
                        onAccepted: {
                            editCustomerDialog.close(true);
                        }

                        onActiveFocusChanged: {
                            if(this.focus){
                                this.selectAll();
                            }
                        }
                    }

                    Button {
                        text: "Ok"
                        onClicked: {
                            editCustomerDialog.close(true);
                        }
                    }
                    Button {
                        text: "Cancel"
                        onClicked: {
                            editCustomerDialog.close(false);
                        }
                    }
                }
            }
        }
    }
}

