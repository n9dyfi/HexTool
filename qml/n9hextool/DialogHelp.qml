import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    signal show
    onShow: dialog.open()
    QueryDialog {
        id: dialog
        titleText: "HexTool Help"
        // formatting strings (bold & italics)
        property string b1: "<font color=\"cyan\"><b>"
        property string b2: "</b></font>"
        property string i1: "<font color=\"orange\"><i>"
        property string i2: "</i></font>"
        message: qsTr("You can put different numbers in registers "+
                      b1+"A"+b2+" and "+b1+"B"+b2+
                      " and make logical and mathematical operations."+
                      " The result is shown in register "+b1+"C"+b2+".<br>"+
                      "The "+i1+"arrow"+i2+" buttons: shift operations (current register).<br>"+
                      "The "+i1+"flip"+i2+" button: endian swap (hexadecimal value).<br>"+
                      "The "+i1+"not"+i2+" button: invert (binary).<br>"+
                      "The small "+i1+"+"+i2+" and "+i1+"-"+i2+" button: increases/decreases (decimal value).<br>"+
                      "The "+i1+"one/zero"+i2+" button: change the label 0/1 (binary).<br>"+
                      "The "+i1+"neg"+i2+" button: inverse (decimal value [signed])")
        rejectButtonText: qsTr("OK")
    }
}
