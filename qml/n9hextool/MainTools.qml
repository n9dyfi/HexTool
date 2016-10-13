import QtQuick 1.1
import com.nokia.meego 1.0

ToolBar {
    anchors.bottom: parent.bottom
    tools:
        ToolBarLayout {
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: (mainMenu.status === DialogStatus.Closed) ? mainMenu.open() : mainMenu.close()
        }
    }
}
