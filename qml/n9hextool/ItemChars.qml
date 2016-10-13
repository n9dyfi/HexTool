import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    width: 0.3*(appDefaults.cDISPLAY_WIDTH-2*appDefaults.cDEFAULT_MARGIN)
    height: appDefaults.cDISPLAY_HEIGHT/6

    property int nChars: 4
    property int spacingChar: 4
    property int widthChar: (width-(nChars-1)*spacingChar)/nChars
    property int heightChar: 40

    property int maxLength: 1
    property int heightLbl: 40
    property int yChar: 30

    Label {
        id: charLabel
        height: heightLbl
        text: "Unicode"
    }

    Repeater {
        id: charFields
        model: nChars
        Rectangle {
            property alias text: textLabel.text
            x: index*(widthChar+spacingChar)
            y: yChar
            width: widthChar
            height: heightChar
            Label {
                id: textLabel
                anchors.centerIn: parent
            }
            gradient: Gradient {
                GradientStop { position: 0.0; color: "black" }
                GradientStop { position: 0.5; color: "#385838" }
                GradientStop { position: 1.0; color: "black" }
            }
        }
    }

    Annotation {
        label: "ItemChars"
    }

    Connections {
        target: appWindow
        onSetChar: charFields.itemAt(index).text = value
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            showHeaderEntry(2)
        }
    }
}
