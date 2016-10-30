import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    signal show
    onShow: dialog.open()
    QueryDialog {
        id: dialog
        titleText: "HexTool Options"
        Item {
            width: parent.width
            height: 0.5*parent.height
            Column {
                spacing: 10
                CheckBox {
                    text: "load and save during start and exit"
                }
                CheckBox {
                    text: "sign extension"
                }
            }
        }
        acceptButtonText: qsTr("Ok")
        rejectButtonText: qsTr("Cancel")
    }
}
