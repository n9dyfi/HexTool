import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    property bool optsl: false
    property bool optsignext: false
    property bool optzerobased: false

    initialPage: mainPage

    // Application defaults, visible in all pages
    AppDefaults {
        id: appDefaults
    }

    // QML component loader
    Loader {
        id: myLoader
    }

    MainPage {
        id: mainPage
        // Lock the screen orientation to landscape (except for the simulator)
        orientationLock: (appDefaults.cSIMU_MODE)?
          PageOrientation.Automatic:PageOrientation.LockLandscape
    }

    // Signals for MainMenu
    signal menuClearClicked()
    signal menuLoadClicked()
    signal menuSaveClicked()
    signal menuOptionsClicked()
    signal menuAboutClicked()

    // Button in the header
    signal btnHeaderClicked(int mode)
    signal btnHelpClicked()
    signal btnCloseClicked()

    // Signals for ItemNumberEntry
    signal setText(int index, string value)
    signal entryTextChanged(int index, string text)
    signal on_pushButton_neg_clicked()
    signal on_pushButton_increase_clicked()
    signal on_pushButton_decrease_clicked()

    // Signals for ItemIPAddress
    signal setIPAddress(int index, string value)
    signal setIPAddressFocus(int index)
    signal on_lineEdit_ipaddress_textChanged(int index, string text)
    signal showHeaderEntry(int mode)

    // Signals for ItemChars
    signal setChar(int index, string value)
    signal setCharEnabled(int index, bool isEnabled)
    signal setCharsFocus(int index)
    signal on_lineEdit_ascii_textChanged(int index, string text)

    // Signals for ItemHeaderEntry
    signal on_lineEdit_textChanged(int mode, int index, string text)
    signal setHeaderEntry(int index, string value)
    signal setHeaderEntryFocus(int index)
    signal setHeaderEntryEnabled(int index, bool isEnabled)
    signal showHeaderEntryForIPAddress()
    signal showHeaderEntryForChars()

    // Signals for ItemBinary
    signal setBit(int index, string value)
    signal setBitGroup32Enabled(bool isEnabled)
    signal setBitGroup16Enabled(bool isEnabled)
    signal groupButton_clicked(int bit)
    signal on_pushButton_bitNumbering_pressed(bool zeroBased)

    // Signals for ItemButtons
    signal on_radioButton_bitsize_clicked(int index)
    signal setBitSize(int index)
    signal on_checkBox_signed_toggled(bool isChecked)
    signal on_pushButton_not_pressed()
    signal on_pushButton_clr_clicked()
    signal setSigned(bool isChecked)

    // Signals for ItemRegisters
    signal setReg(int index)
    signal on_radiobutton_register_clicked(int index)

    // Signals for ItemOperations
    signal on_pushButton_regop_pressed(int index)

    // Signals for OptionsPage
    signal optDialog(bool saveload, bool signext)
    signal setOpts(bool saveload, bool signext, bool zerobased)

    MainMenu {
        id: mainMenu
        visualParent: pageStack
    }

    // Menu>About was clicked
    onMenuAboutClicked: {
        myLoader.source = "DialogAbout.qml"
        myLoader.item.show()
    }

    // Menu>Options was clicked, open options page
    // and pass in the current options
    onMenuOptionsClicked: {
        pageStack.push(Qt.resolvedUrl("OptionsPage.qml"),
                       {saveload:optsl,signext:optsignext});
    }

    onBtnHelpClicked: {
        myLoader.source = "DialogHelp.qml"
        myLoader.item.show()
    }

    // Save options when OptionsPage is closed with "Ok"
    onOptDialog: {
        optsl = saveload
        optsignext = signext
    }

    // Update options from HexTool class via setOpts signal
    onSetOpts: {
        optsl = saveload
        optsignext = signext
        optzerobased = zerobased
    }
}
