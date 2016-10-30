import QtQuick 1.1
import com.nokia.meego 1.0

Item {

    // API
    property real itemWidth
    property alias fieldLabel: fieldLabel.text
    property string fieldColor
    property int fieldType

    // Dimensions
    width: itemWidth*(appDefaults.cDISPLAY_WIDTH-2*appDefaults.cDEFAULT_MARGIN)
    height: appDefaults.cDISPLAY_HEIGHT/6

    property int nFields: 4
    property int spacing: 4

    property int widthField: (width-(nFields-1)*spacing)/nFields
    property int heightField: 40
    property int heightLabel: 40

    property int yField: 30

    Label {
        id: fieldLabel
        height: heightLabel
    }

    Repeater {
        id: fields
        model: nFields
        Rectangle {
            property alias text: textLabel.text
            x: index*(widthField+spacing)
            y: yField
            width: widthField
            height: heightField
            Label {
                id: textLabel
                anchors.centerIn: parent
            }
            gradient: Gradient {
                GradientStop { position: 0.0; color: "black" }
                GradientStop { position: 0.5; color: fieldColor }
                GradientStop { position: 1.0; color: "black" }
            }
        }
    }

    // signal handler for setField(int type, int index, string value)
    Connections {
        target: appWindow
        onSetField:
            if(type===fieldType)
                fields.itemAt(index).text = value
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            showHeaderEntry(fieldType)
        }
    }
}
