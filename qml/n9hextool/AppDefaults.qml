import QtQuick 1.1

Item {

    property string cVERSION : "1.0.1"
    property string cHOMEPAGE : "http://talk.maemo.org/showthread.php?t=93299"
    property int cCOLOR_SCHEME : 6
    property int cDEFAULT_MARGIN : 12

    property int cHEADER_DEFAULT_HEIGHT_PORTRAIT : 72
    property int cHEADER_DEFAULT_TOP_SPACING_PORTRAIT : 15
    property int cHEADER_DEFAULT_BOTTOM_SPACING_PORTRAIT : 15

    property int cHEADER_DEFAULT_HEIGHT_LANDSCAPE : 64
    property int cHEADER_DEFAULT_TOP_SPACING_LANDSCAPE : 9
    property int cHEADER_DEFAULT_BOTTOM_SPACING_LANDSCAPE : 13

    property string cFONT_FAMILY : "Nokia pure Text Light"
    property int cFONT_SIZE_LARGE : 32
    property int cFONT_SIZE_SMALL : 24
    property int cFONT_SIZE_TINY : 18
    property string cFONT_FAMILY_BUTTON : "Nokia pure Text"
    property int cFONT_SIZE_BUTTON : 20

    property string cBUTTON_BACKGROUND: "image://theme/color"+theme.colorScheme+"-meegotouch-button-accent-background"
    property string cBUTTON_FONT_FAMILY : "Nokia pure Text"
    property int cBUTTON_FONT_SIZE : 20
    property int cBUTTON_HEIGHT : 40

    property int cHEADER_HEIGHT : (inPortrait)?cHEADER_DEFAULT_HEIGHT_PORTRAIT:
                          cHEADER_DEFAULT_HEIGHT_LANDSCAPE
    property int cHEADER_TOP_SPACING : (inPortrait)?cHEADER_DEFAULT_TOP_SPACING_PORTRAIT:
                         cHEADER_DEFAULT_TOP_SPACING_LANDSCAPE
    property int cHEADER_BOTTOM_SPACING : (inPortrait)?cHEADER_DEFAULT_BOTTOM_SPACING_PORTRAIT:
                         cHEADER_DEFAULT_BOTTOM_SPACING_LANDSCAPE
    property int cHEADER_REDUCED_BOTTOM_SPACING : (inPortrait)?
                         0.75*cHEADER_DEFAULT_BOTTOM_SPACING_PORTRAIT:
                         0.5*cHEADER_DEFAULT_BOTTOM_SPACING_LANDSCAPE

    property string cTEXT_COLOR : (theme.inverted)?"white":"black"
    property int cSIMU_MODE : (screen.displayWidth < screen.displayHeight)
    property int cDISPLAY_WIDTH : (cSIMU_MODE)?screen.displayHeight:screen.displayWidth
    property int cDISPLAY_HEIGHT : (cSIMU_MODE)?screen.displayWidth:screen.displayHeight
    property int cDPI : screen.dpi

    Component.onCompleted: {
        theme.inverted = true
        theme.colorScheme = cCOLOR_SCHEME
    }
}
