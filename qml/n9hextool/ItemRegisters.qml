import QtQuick 1.1
import com.nokia.meego 1.0

Item {

    width: 0.3*(appDefaults.cDISPLAY_WIDTH-2*appDefaults.cDEFAULT_MARGIN)
    height: appDefaults.cDISPLAY_HEIGHT/6

    property variant regNames : ["A","B","C"]
    property int spacingReg: 4
    property int widthReg: width/regNames.length-spacingReg
    property int heightReg: 40
    property int heightLbl: 40
    property int yReg: 30

    signal setChecked(int checkedIndex)

    Label {
        id: registerLabel
        height: heightLbl
        text: "Register"
    }

    Repeater {
        id: registers
        model: regNames
        Button {
            x: index*(widthReg+spacingReg)
            y: yReg
            checkable: true
            checked: false
            text: modelData
            width: widthReg
            height: heightReg
            onClicked: {
                // inform all radio buttons
                setChecked(index)
                // inform the C++ side
                on_radiobutton_register_clicked(index)
            }
            // Implement radio button like behaviour
            Connections {
                target: itemRegisters
                onSetChecked: checked = (index===checkedIndex)
            }
        }
    }

    Connections {
        target: appWindow
        onSetReg: setChecked(index)
    }

    Annotation {
        label: "ItemRegisters"
    }

}
