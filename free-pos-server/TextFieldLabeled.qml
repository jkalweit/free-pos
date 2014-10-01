import QtQuick 2.3
import QtQuick.Controls 1.2

Row {
    property alias label: label.text
    property alias text: editText.text
    property alias placeholderText: editText.placeholderText

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
        maximumLength: 25
        onAccepted: {
            //editCurrentRecDialog.close(true);
        }

        onActiveFocusChanged: {
            if(this.focus){
                this.selectAll();
            }
        }
    }
}
