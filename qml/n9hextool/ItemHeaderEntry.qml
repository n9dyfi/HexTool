import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    id: itemHeaderEntry
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

    // setHeaderEntry(int index, string value)
    Connections {
        target: appWindow
        onSetHeaderEntry: {
            fields.itemAt(index).text = value
        }
    }
    Connections {
        target: appWindow
        onSetHeaderEntryFocus: {
            fields.itemAt(index).focus = true
            fields.itemAt(index).selectAll()
        }
    }

    // ItemIPAddress mouse area was clicked
    Connections {
        target: appWindow
        onShowHeaderEntryForIPAddress: {
            itemHeaderEntry.modeMaxLength = 3
            itemHeaderEntry.visible = true
            itemHeaderEntry.mode = 1
            btnHelp.mode = 1
        }
    }

    // ItemChars mouse area was clicked
    Connections {
        target: appWindow
        onShowHeaderEntryForChars: {
            itemHeaderEntry.modeMaxLength = 1
            itemHeaderEntry.visible = true
            itemHeaderEntry.mode = 2
            btnHelp.mode = 2
        }
    }

    // Close button in ItemHeaderEntry was clicked - end entry
    Connections {
        target: appWindow
        onBtnCloseClicked: {
            // reset maxLength to 3, otherwise we cannot change content from chars to IP address
            itemHeaderEntry.modeMaxLength = 3
            itemHeaderEntry.visible = false
            mode = 0
            btnHelp.mode = 0
            parent.focus = true;
        }
    }

    Connections {
        target: appWindow
        onSetHeaderEntryEnabled: {
            fields.itemAt(index).enabled = isEnabled
            fields.itemAt(index).visible = isEnabled
        }
    }
}
