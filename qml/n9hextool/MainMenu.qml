import QtQuick 1.1
import com.nokia.meego 1.0

Menu {

    MenuLayout {

        MenuItem {
            text: qsTr("ClearAll")
            onClicked: {
                menuClearClicked()
            }
        }
        MenuItem {
            text: qsTr("Load")
            onClicked: {
                menuLoadClicked()
            }
        }
        MenuItem {
            text: qsTr("Save")
            onClicked: {
                menuSaveClicked()
            }
        }
        MenuItem {
            text: qsTr("Options")
            onClicked: {
                menuOptionsClicked()
            }
        }
        MenuItem {
            text: qsTr("About")
            onClicked: {
                menuAboutClicked()
            }
        }
    }
}
