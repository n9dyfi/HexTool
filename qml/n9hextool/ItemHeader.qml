import QtQuick 1.1
import com.nokia.meego 1.0

Item {

    property alias headerText: titleLabel.text
    property alias buttonVisible: btnHelp.visible
    property alias menuVisible: menuIcon.visible

    // Header dimensions
    height: appDefaults.cHEADER_HEIGHT
    width: parent.width
    property variant buttonDim : [130,40]

    // Header background image
    Rectangle {
        id: titleImage
        height: parent.height
        width: parent.width
        gradient: Gradient {
            GradientStop { position: 0.0; color: "black" }
            GradientStop { position: 0.5; color: "#575757" }
            GradientStop { position: 1.0; color: "black" }
        }
    }

    // Define the label styling
    LabelStyle {
        id: labelStyle
        fontFamily: appDefaults.cFONT_FAMILY
        fontPixelSize: appDefaults.cFONT_SIZE_LARGE
    }

    // Define the button styling
    ButtonStyle {
        id: buttonStyle
        textColor: "white"
        fontFamily: appDefaults.cFONT_FAMILY_BUTTON
        fontPixelSize: appDefaults.cFONT_SIZE_BUTTON
    }

    ItemHeaderEntry {
        id: itemHeaderEntry
        anchors.centerIn: parent
        visible: false
    }

    // Help button
    Button {
        id: btnHelp
        property int mode: 0    // HELP=0|IPADDR|CHAR
        property variant modeText: ["Help","Close","Close"]
        width: buttonDim[0]; height: buttonDim[1]
        platformStyle: buttonStyle
        anchors { right: menuIcon.left; rightMargin: appDefaults.cDEFAULT_MARGIN
            verticalCenter: parent.verticalCenter}
        text: "Help"
        onClicked: {
            btnHeaderClicked(mode)
        }
        onModeChanged: text=modeText[mode]
    }

    // Pull-down menu
    ToolIcon {
        id: menuIcon
        platformIconId: "toolbar-view-menu"
        anchors.right: (parent === undefined) ? undefined : parent.right
        onClicked: (mainMenu.status === DialogStatus.Closed) ? mainMenu.open() : mainMenu.close()
    }

    // Header text
    Label {
        id: titleLabel
        platformStyle: labelStyle
        anchors {
            top:parent.top; topMargin:appDefaults.cHEADER_TOP_SPACING
            left:parent.left; leftMargin:appDefaults.cDEFAULT_MARGIN
        }
    }
}
