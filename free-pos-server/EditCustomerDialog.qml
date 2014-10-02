import QtQuick 2.3
import QtQuick.Controls 1.2

DialogModal {
    id: editCustomerDialog
    title: "Edit Customer"
    defaultFocus: editName
    property var model

    function close(save) {
        if (save) {
            editCustomerDialog.model.name = editName.text
        }
        editCustomerDialog.visible = false
    }

    customContent: Column {
        spacing: 5

        TextFieldLabeled {
            id: editName
            label: "Name:"
            text: model ? model.name : ""
            placeholderText: "Name"
        }

        Row {
            Button {
                text: "Ok"
                onClicked: {
                    editCustomerDialog.close(true)
                }
            }
            Button {
                text: "Cancel"
                onClicked: {
                    editCustomerDialog.close(false)
                }
            }
        }
    }
}
