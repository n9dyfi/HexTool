import QtQuick 1.1
import com.nokia.meego 1.0

Rectangle {
    property alias label: label.text
    anchors.fill: parent
    opacity: 0.5
    border.color: "orange"
    border.width: 2
    visible: appDefaults.cSHOW_ANNOTATIONS
    Label {
        id: label
        color: "black"
        anchors.centerIn: parent
    }
}
