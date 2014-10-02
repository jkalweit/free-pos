import QtQuick 2.3


Column {
    property var model
    spacing: 5

    function saveChanges() {
        model.c100s = Number(edit100s.text)
        model.c50s = Number(edit50s.text)
        model.c20s = Number(edit20s.text)
        model.c10s = Number(edit10s.text)
        model.c5s = Number(edit5s.text)
        model.c1s = Number(edit1s.text)
        model.coins = Number(editCoins.text)
    }

    function updateTotal() {
        var total = Number(edit100s.text) +
                    Number(edit50s.text) +
                    Number(edit20s.text) +
                    Number(edit10s.text) +
                    Number(edit5s.text) +
                    Number(edit1s.text) +
                    Number(editCoins.text);
        totalText.text = "$" + total.toFixed(2);
    }


    TextFieldLabeled {
        id: edit100s
        label: "100s:"
        text: model ? model.c100s : ""
        placeholderText: "100s"
        onTextChanged: updateTotal()
    }
    TextFieldLabeled {
        id: edit50s
        label: "50s:"
        text: model ? model.c50s : ""
        placeholderText: "50s"
        onTextChanged: updateTotal()
    }
    TextFieldLabeled {
        id: edit20s
        label: "20s:"
        text: model ? model.c20s : ""
        placeholderText: "20s"
        onTextChanged: updateTotal()
    }
    TextFieldLabeled {
        id: edit10s
        label: "10s:"
        text: model ? model.c10s : ""
        placeholderText: "10s"
        onTextChanged: updateTotal()
    }
    TextFieldLabeled {
        id: edit5s
        label: "5s:"
        text: model ? model.c5s : ""
        placeholderText: "5s"
        onTextChanged: updateTotal()
    }
    TextFieldLabeled {
        id: edit1s
        label: "1s:"
        text: model ? model.c1s : ""
        placeholderText: "1s"
        onTextChanged: updateTotal()
    }
    TextFieldLabeled {
        id: editCoins
        label: "Coins:"
        text: model ? model.coins : ""
        placeholderText: "Coins"
        onTextChanged: updateTotal()
    }

    Row {
        Text {
            width: 75
            text: "Total:"
        }


        Text {
            id: totalText
            width: 150
        }
    }
}
