import QtQuick 2.3
import QtQuick.Controls 1.2
import FreePos 1.0 as FreePos
//import QtMultimedia 5.0


ApplicationWindow {
    visible: true
    width: 1020
    height: 800
    title: "CY Pos"


    EditReconciliation {
        id: editReconciliation
        visible: pos.selectedRec ? pos.selectedRec.isOpen : false
        model: pos.selectedRec ? pos.selectedRec : 0
    }

    DialogModalMessage {
        title: "No Open Rec"
        buttonText: "Open New Rec"
        visible: !pos.selectedRec || !pos.selectedRec.isOpen
        closeOnAcknowledge: false
        onAcknowledged: {
            pos.selectedRec = pos.openNewRec()
        }
    }

}
