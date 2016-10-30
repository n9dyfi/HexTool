import QtQuick 1.1
import com.nokia.meego 1.0

Item {

    width: appDefaults.cDISPLAY_WIDTH-2*appDefaults.cDEFAULT_MARGIN
    height: appDefaults.cDISPLAY_HEIGHT/3.2

    property int widthBtn: (width-12*spacingBtn-3*spacingGrp)/16
    property int heightBtn: 40
    property int spacingBtn: 4
    property int spacingGrp: 20
    property int spacingRow: 70
    property int offsetBtnRow: 35
    property int widthLbl: 4*(widthBtn+spacingBtn)+spacingGrp

    property bool zeroBased: optzerobased
    property bool enable32: true
    property bool enable16: true

    // Bits
    Repeater {
        id: bitFields
        model: 32
        Button {
            property int iRow: Math.floor(index/16)
            property int iGroup: Math.floor(index/4)
            property bool isEnabled: (index<16)?enable32:(index<24)?enable16:true
            x: (index-iRow*16)*(widthBtn+spacingBtn)+spacingGrp*(iGroup-(iGroup>3)*4)
            y: offsetBtnRow+iRow*spacingRow
            text: "0"
            width: widthBtn
            height: heightBtn
            enabled: isEnabled
            onClicked: groupButton_clicked(32-index)     // bit number, LSB=1
        }
    }

    // Bit position numbers
    Repeater {
        model: 8
        Label {
            property int bitIndex: 31-index*4
            property int iRow: Math.floor(index/4)
            x: (index-iRow*4)*widthLbl
            y: iRow*spacingRow
            text: (zeroBased)?bitIndex:bitIndex+1
            width: widthLbl
        }
    }

    // Button to toggle the start value for the bit index: 0/1
    Button {
        x: 15*(widthBtn+spacingBtn)+3*spacingGrp
        y: spacingRow
        text: (zeroBased)?0:1
        width: widthBtn;height:heightBtn
        onClicked: {
            zeroBased = !zeroBased
            on_pushButton_bitNumbering_pressed(zeroBased)
        }
    }

    Connections {
        target: appWindow
        onSetBit: bitFields.itemAt(31-index).text = value
    }

    Connections {
        target: appWindow
        onSetBitGroup16Enabled: {
            enable16 = isEnabled
        }
    }

    Connections {
        target: appWindow
        onSetBitGroup32Enabled: {
            enable32 = isEnabled
        }
    }
}
