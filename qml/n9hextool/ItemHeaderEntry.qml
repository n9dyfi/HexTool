import QtQuick 1.1
import com.nokia.meego 1.0

Item {

    width: 0.4*(appDefaults.cDISPLAY_WIDTH-2*appDefaults.cDEFAULT_MARGIN)
    height: heightField

    property int nFields: 4
    property int spacingField: 4
    property int widthField: (width-(nFields-1)*spacingField)/nFields
    property int heightField: 40

    property int heightLbl: 40
    property int yField: 30

    property int mode: 0
    property int modeMaxLength: 3

    Repeater {
        id: fields
        model: nFields
        TextField {
            width: widthField
            height: heightField
            x: index*(widthField+spacingField)
            // This is required for textChanged signal
            inputMethodHints: Qt.ImhNoPredictiveText;
            onTextChanged: {
                on_lineEdit_textChanged(mode,index,text)
            }
            // close the keyboard
            Keys.onReturnPressed: {
                parent.focus = true;
            }
            onVisibleChanged: {
                maximumLength = modeMaxLength
            }
        }
    }

    Annotation {
        label: "ItemHeaderEntry"
    }

    // signal handler for setHeaderEntry(int index, string value)
    Connections {
        target: appWindow
        onSetHeaderEntry: {
            fields.itemAt(index).text = value
        }
    }

    // signal handler for setHeaderEntryFocus(int index)
    Connections {
        target: appWindow
        onSetHeaderEntryFocus: {
            fields.itemAt(index).focus = true
            fields.itemAt(index).selectAll()
        }
    }

    // signal handler for setHeaderEntryVisible(int mode)
    Connections {
        target: appWindow
        onSetHeaderEntryVisible: {
            itemHeaderEntry.modeMaxLength = (mode===1)?3:1
            itemHeaderEntry.visible = true
            itemHeaderEntry.mode = mode
            btnHelp.mode = mode
        }
    }

    // Close button in ItemHeaderEntry was clicked - end entry
    Connections {
        target: appWindow
        onBtnCloseClicked: {
            // reset maxLength to 3, otherwise we cannot change
            // content from chars to IP address
            itemHeaderEntry.modeMaxLength = 3
            itemHeaderEntry.visible = false
            mode = 0
            btnHelp.mode = 0
            parent.focus = true;
        }
    }

    Connections {
        target: appWindow
        // signal handler for setHeaderEntryEnabled(int index, bool isEnabled)
        onSetHeaderEntryEnabled: {
            fields.itemAt(index).enabled = isEnabled
            fields.itemAt(index).visible = isEnabled
        }
    }
}
