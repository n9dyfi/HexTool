import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    signal show
    onShow: dialog.open()
    QueryDialog {
        id: dialog
        titleText: "HexTool "+appDefaults.cVERSION
        message: qsTr("Ported and code changes by n9dyfi.") + "\n\n"+
                 qsTr("Based on Version 1.7.1 by omnium and halftux.");
        acceptButtonText: qsTr("Go to maemo.org")
        rejectButtonText: qsTr("Close")
        onAccepted: {
            Qt.openUrlExternally(appDefaults.cHOMEPAGE)
        }
    }
}
