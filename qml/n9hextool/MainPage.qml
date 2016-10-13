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

    ItemIPAddress {
        id: itemIPAddress
        anchors.left: itemRegisters.right
        anchors.top: itemBinary.bottom
    }

    ItemChars {
        id: itemChars
        anchors.left: itemIPAddress.right
        anchors.top: itemBinary.bottom
    }

    ItemOperations {
        id: itemOperations
        x: appDefaults.cDEFAULT_MARGIN
        anchors.top: itemRegisters.bottom
    }
}
