import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    width: 0.65*(appDefaults.cDISPLAY_WIDTH-2*appDefaults.cDEFAULT_MARGIN)
    height: 0.22*appDefaults.cDISPLAY_HEIGHT

    property int spacingField : 5
    // width for plus and minus buttons
    property int widthPlusMinus : 40
    // text field widths
    property variant fieldWidths : [140,175,170]
    property int nFields : fieldWidths.length
    property variant maxEntryLength : [8,11,11]
    property int yField : 0.45*height
    // for the "neg" button
    property int widthBtn: 70
    property int heightBtn: 40

    Repeater {
        id: entryFields
        model: nFields
        TextField {
            property int rightEdge : x+fieldWidths[index]+spacingField
            width: fieldWidths[index]
            x: (index>0)?entryFields.itemAt(index-1).rightEdge:0
            y: yField
            maximumLength: maxEntryLength[index]
            onTextChanged: {
                entryTextChanged(index,text)
            }
            // close the keyboard
            Keys.onReturnPressed: {
                parent.focus = true;
            }
        }
    }

    // Labels for the text fields
    Repeater {
        id: entryLabels
        model: ["hex","oct","dec"]
        Label {
            property int rightEdge : x+fieldWidths[index]+spacingField
            x: (index>0)?entryLabels.itemAt(index-1).rightEdge:0
            y: yField-height
            text: modelData
            width: fieldWidths[index]
        }
    }

    Button{
        text: "neg"
        anchors.right: plusMinus.left
        y: yField-height
        width: widthBtn; height: heightBtn
        onClicked: on_pushButton_neg_clicked()
    }


    Column {
        id: plusMinus
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        Item {
            height: 20
            width: widthPlusMinus
        }
        Button {
            text: "+"
            width: widthPlusMinus
            height: widthPlusMinus
            onClicked: on_pushButton_increase_clicked()
        }
        Button {
            text: "-"
            width: widthPlusMinus
            height: widthPlusMinus
            onClicked: on_pushButton_decrease_clicked()
        }
    }

    Annotation {
        label: "ItemNumberEntry"
    }

    Connections {
        target: appWindow
        onSetText: entryFields.itemAt(index).text = value
    }
}
