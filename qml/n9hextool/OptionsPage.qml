import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: optionsPage

    // Options that can be set
    property bool saveload
    property bool signext

    property int spacingTop: 0.1*height
    property int spacingBox: 0.05*height
    property int spacingBtn: 0.05*width
    property int widthBtn: 0.2*width

    ItemHeader {
        id: header
        headerText: "HexTool Options"
    }

    Column {
        anchors.centerIn: parent
        spacing: spacingTop
        Column {
            id: checkBoxes
            spacing: spacingBox
            CheckBox {
                id: saveloadBox
                text: "load and save during start and exit"
                checked: saveload
            }
            CheckBox {
                id: signextBox
                text: "sign extension"
                checked: signext
            }
        }
        Row {
            spacing: spacingBtn
            Button {
                text: "Ok"
                width: widthBtn
                onClicked: {
                    // return options
                    optDialog(saveloadBox.checked,signextBox.checked)
                    pageStack.pop()
                }
            }
            Button {
                text: "Cancel"
                width: widthBtn
                onClicked: pageStack.pop()
            }
        }
    }
}
