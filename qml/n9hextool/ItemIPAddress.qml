import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    width: 0.4*(appDefaults.cDISPLAY_WIDTH-2*appDefaults.cDEFAULT_MARGIN)
    height: appDefaults.cDISPLAY_HEIGHT/6

    property int widthAddr: width/4-spacingAddr
    property int heightAddr: 40
    property int spacingAddr: 4

    property int nOctets: 4
    property int heightLbl: 40
    property int yAddr: 30

    Label {
        id: addressLabel
        height: heightLbl
        text: "IP Address"
    }

    Repeater {
        id: addressFields
        model: nOctets
        Rectangle {
            property alias text: textLabel.text
            x: index*(widthAddr+spacingAddr)
            y: yAddr
            width: widthAddr
            height: heightAddr
            Label {
                id: textLabel
                anchors.centerIn: parent
            }
            gradient: Gradient {
                GradientStop { position: 0.0; color: "black" }
                GradientStop { position: 0.5; color: "#9a7d54" }
                GradientStop { position: 1.0; color: "black" }
            }
        }
    }

    Annotation {
        label: "ItemIPAddress"
    }

    Connections {
        target: appWindow
        onSetIPAddress: addressFields.itemAt(index).text = value
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            showHeaderEntry(1)
        }
    }
}
