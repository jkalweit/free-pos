import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos

Rectangle {
    id: container
    color: "#33FFFFFF"

    property var menu
    property bool editMode: false
    signal menuCategorySelected(var menuCategory, var isNew)



    Keys.onDownPressed: container.menu.selectedCategory = container.menu.getNextCategory(newMenuCategoryName.text.trim())
    Keys.onUpPressed: container.menu.selectedCategory = container.menu.getPreviousCategory(newMenuCategoryName.text.trim())

    Column {
        id: menuCategoryControls
        width: parent.width
        spacing: 2

        TextField {
            id: newMenuCategoryName
            maximumLength: 32
            width: parent.width
            height: 50
            placeholderText: qsTr("Category name")
            onAccepted: {
                if(container.editMode) {
                    var cat = menu.addCategory(newMenuCategoryName.text);
                    newMenuCategoryName.text = "";
                    console.log("added cat: " + cat.name);
                    container.menuCategorySelected(cat, true);
                }
            }

            onActiveFocusChanged: {
                if(this.focus){
                    this.selectAll();
                }
            }
        }
    }

    ListView {
        width: parent.width
        anchors.top: menuCategoryControls.bottom
        anchors.bottom: container.bottom
        model: container.menu ? container.menu.categories : 0
        clip: true

        delegate: RectangleFlashButton {
            color: modelData.isDisabled ? "#AAAAAA" : "#7e57c2"
            border.color: menu.selectedCategory && (menu.selectedCategory.id === modelData.id) ? "#DDDDDD" : "#777777"
            border.width: 2
            textColor: menu.selectedCategory && (menu.selectedCategory.id === modelData.id) ? "#DDDDDD" : "#000000"
            flashColor: "#FFFFFF"
            text: modelData.name
            verticalMargin: 10

            visible: {
                if(!container.editMode && modelData.isDisabled)
                    return false;
                var filter = newMenuCategoryName.text.trim().toUpperCase()
                if(filter.length === 0){
                    return true;
                }
                return modelData.name.toUpperCase().indexOf(filter) > -1;
            }

            hidden: !container.editMode && modelData.isDisabled;

            onBeforeFlash: {
                menu.selectedCategory = modelData;
            }

            onClicked: {
                newMenuCategoryName.text = "";                
                menuCategorySelected(modelData, false);
            }
        }
    }
}
