import QtQuick 2.3


Column {
    id: container
    property var model
    property bool showPayouts: false
    spacing: 5

//    function saveChanges() {
//        container.model.c100s = Number(edit100s.text)
//        container.model.c50s = Number(edit50s.text)
//        container.model.c20s = Number(edit20s.text)
//        container.model.c10s = Number(edit10s.text)
//        container.model.c5s = Number(edit5s.text)
//        container.model.c1s = Number(edit1s.text)
//        container.model.coins = Number(editCoins.text)
//    }

//    function updateTotal() {
//        var total = Number(edit100s.text) +
//                    Number(edit50s.text) +
//                    Number(edit20s.text) +
//                    Number(edit10s.text) +
//                    Number(edit5s.text) +
//                    Number(edit1s.text) +
//                    Number(editCoins.text);
//        //totalText.text = "$" + total.toFixed(2);
//    }


    function updateIfDifferent(target, field, val) {
        if(target[field].toFixed(2) !== val.toFixed(2))
            target[field] = val;
    }

    TextFieldLabeled {
        id: edit100s
        label: "100s:"
        text: container.model ? container.model.c100s : ""
        placeholderText: "100s"
        onEditingFinished: updateIfDifferent(container.model, "c100s", Number(edit100s.text))
    }
    TextFieldLabeled {
        id: edit50s
        label: "50s:"
        text: container.model ? container.model.c50s : ""
        placeholderText: "50s"
        onEditingFinished: updateIfDifferent(container.model, "c50s", Number(edit50s.text))
    }
    TextFieldLabeled {
        id: edit20s
        label: "20s:"
        text: container.model ? container.model.c20s : ""
        placeholderText: "20s"
        onEditingFinished: updateIfDifferent(container.model, "c20s", Number(edit20s.text))
    }
    TextFieldLabeled {
        id: edit10s
        label: "10s:"
        text: container.model ? container.model.c10s : ""
        placeholderText: "10s"
        onEditingFinished: updateIfDifferent(container.model, "c10s", Number(edit10s.text))
    }
    TextFieldLabeled {
        id: edit5s
        label: "5s:"
        text: container.model ? container.model.c5s : ""
        placeholderText: "5s"
        onEditingFinished: updateIfDifferent(container.model, "c5s", Number(edit5s.text));
     }

    TextFieldLabeled {
        id: edit1s
        label: "1s:"
        text: container.model ? container.model.c1s : ""
        placeholderText: "1s"
        onEditingFinished: updateIfDifferent(container.model, "c1s", Number(edit1s.text))
    }
    TextFieldLabeled {
        id: editCoins
        label: "Coins:"
        text: container.model ? container.model.coins.toFixed(2) : ""
        placeholderText: "Coins"
        onEditingFinished: updateIfDifferent(container.model, "coins", Number(editCoins.text))
    }    
    TextFieldLabeled {
        id: editPayouts
        visible: showPayouts
        label: "Payouts:"
        text: container.model ? container.model.payouts.toFixed(2) : ""
        placeholderText: "Payouts"
        onEditingFinished: updateIfDifferent(container.model, "payouts", Number(editPayouts.text))
    }
    TextFieldLabeled {
        id: editChecks
        visible: showPayouts
        label: "Checks:"
        text: container.model ? container.model.checks.toFixed(2) : ""
        placeholderText: "Checks"
        onEditingFinished: updateIfDifferent(container.model, "checks", Number(editChecks.text))
    }
    TextFieldLabeled {
        id: editGiftCards
        visible: showPayouts
        label: "Gift Cards:"
        text: container.model ? container.model.giftCards.toFixed(2) : ""
        placeholderText: "Gift Cards"
        onEditingFinished: updateIfDifferent(container.model, "giftCards", Number(editGiftCards.text))
    }
    Rectangle {
        id: editPayoutsReplacement
        width: editPayouts.width
        height: editPayouts.height
        visible: !showPayouts
    }
    Rectangle {
        id: editPayoutsReplacement2
        width: editPayouts.width
        height: editPayouts.height
        visible: !showPayouts
    }
    Rectangle {
        id: editPayoutsReplacement3
        width: editPayouts.width
        height: editPayouts.height
        visible: !showPayouts
    }

    Row {
        Text {
            width: 75
            text: "Total:"
        }


        Text {
            id: totalText
            width: 150
            text: container.model ? "$" + container.model.total.toFixed(2) : ""
        }
    }
}
