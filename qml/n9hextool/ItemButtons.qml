import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    id: itemButtons
    width: 0.35*(appDefaults.cDISPLAY_WIDTH-2*appDefaults.cDEFAULT_MARGIN)
    height: 0.22*appDefaults.cDISPLAY_HEIGHT

    property int bW: 70
    property int bH: 40
    property int bSp: 4

    signal setChecked(int checkedIndex)

    Row {
        id: upperRow
        y: 0.1*parent.height
        anchors.right: parent.right

        Repeater {
            id: radioButtons
            model: ["32","16","8"]
            Button {
                checkable: true
                checked: false
                text: modelData
                width: bW
                height: bH
                onClicked: {
                    // inform all radio buttons
                    setChecked(index)
                    // inform the C++ side
                    on_radioButton_bitsize_clicked(index)
                }
                // Implement radio button like behaviour
                Connections {
                    target: itemButtons
                    onSetChecked: checked = (index===checkedIndex)
                }
            }
        }
    }

    // Handle signal from the C++ side
    Connections {
        target: appWindow
        onSetBitSize: setChecked(index)
    }

    Row {
        id: lowerRow
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        spacing: 2*bSp
        Button{
            text: qsTr("not")
            width: bW; height: bH
            onClicked: on_pushButton_not_pressed()
        }
        CheckBox {
            id: signed
            text: "signed "
            onCheckedChanged: on_checkBox_signed_toggled(checked)
        }
        Button{
            text: qsTr("clr")
            width: bW; height: bH
            onClicked: on_pushButton_clr_clicked()
        }
    }

    Connections {
        target: appWindow
        onSetSigned: signed.checked = isChecked
    }

    Annotation {
        label: "ItemButtons"
    }
}
