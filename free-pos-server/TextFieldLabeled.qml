import QtQuick 2.3
import QtQuick.Controls 1.2

Row {
    id: container
    property alias label: label.text
    property alias text: editText.text
    property alias placeholderText: editText.placeholderText
    property alias textFieldWidth: editText.width
    signal accepted

    function forceActiveFocus() {
        editText.forceActiveFocus();
    }

    Text {
        id: label
        width: 75
    }


    TextField {
        id: editText
        width: 150

        onTextChanged: container.textChanged()
        onAccepted: container.accepted()

        onActiveFocusChanged: {
            if(this.focus){
                this.selectAll();
            }
        }
    }
}
