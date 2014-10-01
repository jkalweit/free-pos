import QtQuick 2.3
import QtQuick.Controls 1.2


DialogModal {
    id: editCurrentRecDialog
    title: "Current Reconciliation"
    property var model
    defaultFocus: editName

    onVisibleChanged: {
        if(this.visible) {
            model = rec
        }
    }

    function close(save) {
        if(save) {
            rec.name = editName.text;
            rec.beginningDrawer.c100s = Number(edit100s.text)
        }
        editCurrentRecDialog.visible = false;
    }

    customContent: Column {
        spacing: 5

        TextFieldLabeled {
            id: editName
            label: "Name:"
            text: model ? model.name : ""
            placeholderText: "Rec name"
        }

        TextFieldLabeled {
            id: edit100s
            label: "100s:"
            text: model ? model.beginningDrawer.c100s : ""
            placeholderText: "100s"
        }

//        Row {

//            Text {
//                text: "Name: "
//            }


//            TextField {
//                id: editName
//                text: model ? model.name : ""
//                width: 150
//                maximumLength: 25
//                placeholderText: qsTr("Rec name")
//                onAccepted: {
//                    editCurrentRecDialog.close(true);
//                }

//                onActiveFocusChanged: {
//                    if(this.focus){
//                        this.selectAll();
//                    }
//                }
//            }
//        }
        Row {
            Button {
                text: "Ok"
                onClicked: {
                    editCurrentRecDialog.close(true);
                }
            }
            Button {
                text: "Cancel"
                onClicked: {
                    editCurrentRecDialog.close(false);
                }
            }
        }
    }
}
