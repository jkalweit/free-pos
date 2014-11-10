import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos

Rectangle {
    id: container
    color: "transparent"
    property var inventory
    signal inventoryItemSelected(var inventoryItem, var isNew)

    TextField {
        id: newInventoryItemName
        maximumLength: 20
        width: parent.width
        height: 50
        anchors.top: parent.top
        anchors.left: parent.left
        placeholderText: qsTr("Inventory item name")
        onAccepted: {
            var item = inventory.addInventoryItem(newInventoryItemName.text, 0);
            newInventoryItemName.text = "";
            console.log("added item: " + item.name);
            container.inventoryItemSelected(item, true);
        }

        onActiveFocusChanged: {
            if(this.focus){
                this.selectAll();
            }
        }
    }

    ListView {
        width: parent.width
        anchors.top: newInventoryItemName.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        model: inventory && inventory.inventoryItems ? inventory.inventoryItems : 0
        clip: true

        delegate: RectangleFlash {
            id: inventoryItemContainer
            width: container.width

            height: inventoryItemName.height + 10
            border.color: "white" // menu.selectedCategory && menu.selectedCategory.selectedItem && (menu.selectedCategory.selectedItem.id === modelData.id) ? "#DDDDDD" : "#777777"
            border.width: 2
            //color:  modelData.isDisabled ? "#AAAAAA" : "#9575cd"
            flashColor: "#FFFFFF"

//            visible: {
//                if(!container.editMode && modelData.isDisabled)
//                    return false;
//                var filter = newMenuItemName.text.trim().toUpperCase();
//                if(filter.length === 0){
//                    return true;
//                }
//                return modelData.name.toUpperCase().indexOf(filter) > -1;
//            }

            onBeforeFlash: {
                newInventoryItemName.text = "";
                container.inventoryItemSelected(modelData, false);
            }

            customContent: Item {
                anchors.fill: parent
                Text {
                    id: inventoryItemName
                    text: modelData.name
                    color: "#000000"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                }
                Text {
                    text: modelData.price.toFixed(2)
                    color: "#000000"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                }
            }
        }
    }
}
