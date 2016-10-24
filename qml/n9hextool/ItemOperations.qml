import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    width: appDefaults.cDISPLAY_WIDTH-2*appDefaults.cDEFAULT_MARGIN
    height: appDefaults.cDISPLAY_HEIGHT/10

    property int spacingBtn: 4
    property variant ops : ["AND","OR","XOR","+","-","x","/","<<",">>","flip"]
    property int nButtons : ops.length
    property int widthBtn: (width-(nButtons-1)*spacingBtn)/nButtons

    Repeater {
        model: ops
        Button {
            x: index*(widthBtn+spacingBtn)
            text: modelData
            width: widthBtn
            height: appDefaults.cBUTTON_HEIGHT
            onClicked: on_pushButton_regop_pressed(index)
        }
    }

    Annotation {
        label: "ItemOperations"
    }

}
