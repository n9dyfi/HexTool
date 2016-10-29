import QtQuick 1.1
import com.nokia.meego 1.0

Page {

    ItemHeader {
        id: itemHeader
        headerText: "HexTool"
    }

    ItemNumberEntry {
        id: itemNumberEntry
        x: appDefaults.cDEFAULT_MARGIN
        anchors.top: itemHeader.bottom
    }

    ItemButtons {
        id: itemButtons
        anchors.top: itemHeader.bottom
        anchors.left: itemNumberEntry.right
    }

    ItemBinary {
        id: itemBinary
        x: appDefaults.cDEFAULT_MARGIN
        anchors.top: itemNumberEntry.bottom
    }

    ItemRegisters {
        id: itemRegisters
        x: appDefaults.cDEFAULT_MARGIN
        anchors.top: itemBinary.bottom
    }

    ItemFields {
        id: itemIPAddress
        itemWidth: 0.4
        fieldLabel: "IP Address"
        fieldColor: "#9a7d54"
        fieldType: 1
        anchors.left: itemRegisters.right
        anchors.top: itemBinary.bottom
    }

    ItemFields {
        id: itemUnicode
        itemWidth: 0.3
        fieldLabel: "Unicode"
        fieldColor: "#385838"
        fieldType: 2
        anchors.left: itemIPAddress.right
        anchors.top: itemBinary.bottom
    }

    ItemOperations {
        id: itemOperations
        x: appDefaults.cDEFAULT_MARGIN
        anchors.top: itemRegisters.bottom
    }
}
