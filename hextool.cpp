/****************************************************************************

    FILE:    hextool.cpp

 ****************************************************************************

    LICENSE:

    HexTool -  a simple program to convert numbers on the fly
    Copyright (C) 2003 Ryan Harkin and 2014 Christian Weniger; www.harkin.org/HexTool

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2 as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

****************************************************************************/

#include "hextool.h"

#include <QSettings>
#include <QDir>
#include <QDebug>

HexTool::HexTool(QObject *qml, QObject *parent) :
    QObject(parent)
{
    optsl=false;
    optsignext=false;
    optzerobased=false;

    headerEntryVisible=0;

    SetSigned(UNSIGNED);
    SetNumBits(NUMBITS_32);
    SetRegister(REG_A);

    // connect QML signals to HexTool slots
    connect(qml, SIGNAL(menuClearClicked()),
             this, SLOT(clearAll()));
    connect(qml, SIGNAL(menuLoadClicked()),
             this, SLOT(load_ini()));
    connect(qml, SIGNAL(menuSaveClicked()),
             this, SLOT(save_ini()));
    connect(qml, SIGNAL(on_radioButton_bitsize_clicked(int)),
             this, SLOT(on_radioButton_bitsize_clicked(int)));

    // Signals from ItemButtons
    connect(qml, SIGNAL(on_pushButton_neg_clicked()),
             this, SLOT(on_pushButton_neg_clicked()));
    connect(qml, SIGNAL(on_checkBox_signed_toggled(bool)),
             this, SLOT(on_checkBox_signed_toggled(bool)));
    connect(qml, SIGNAL(on_pushButton_clr_clicked()),
             this, SLOT(on_pushButton_clr_clicked()));

    // Signals from ItemBinary
    connect(qml, SIGNAL(groupButton_clicked(int)),
             this, SLOT(groupButton_clicked(int)));
    connect(qml, SIGNAL(on_pushButton_bitNumbering_pressed(bool)),
            this, SLOT(on_pushButton_bitNumbering_pressed(bool)));

    // Signals from ItemNumberEntry
    connect(qml, SIGNAL(entryTextChanged(int, QString)),
             this, SLOT(entryTextChanged(int, QString)));
    connect(qml, SIGNAL(on_pushButton_not_pressed()),
            this, SLOT(on_pushButton_not_pressed()));
    connect(qml, SIGNAL(on_pushButton_increase_clicked()),
            this, SLOT(on_pushButton_increase_clicked()));
    connect(qml, SIGNAL(on_pushButton_decrease_clicked()),
            this, SLOT(on_pushButton_decrease_clicked()));

    // Signals from ItemRegisters
    connect(qml, SIGNAL(on_radiobutton_register_clicked(int)),
             this, SLOT(on_radiobutton_register_clicked(int)));

    // Signals from ItemOperations
    connect(qml, SIGNAL(on_pushButton_regop_pressed(int)),
             this, SLOT(on_pushButton_regop_pressed(int)));

    // Signals from OptionsPage
    connect(qml, SIGNAL(optDialog(bool,bool)),
            this, SLOT(optDialog(bool,bool)));

    // Signals from ItemFields (IP Address & Unicode)
    connect(qml, SIGNAL(showHeaderEntry(int)),
            this, SLOT(showHeaderEntry(int)));

    // Signals from MainPage
    connect(qml, SIGNAL(btnHeaderClicked(int)),
            this, SLOT(btnHeaderClicked(int)));
    connect(this, SIGNAL(btnHelpClicked()),
             qml, SLOT(btnHelpClicked()));
    connect(this, SIGNAL(btnCloseClicked()),
             qml, SLOT(btnCloseClicked()));

    // Connect C++ signals to QML signals
    connect(this, SIGNAL(setReg(int)),
             qml, SIGNAL(setReg(int)));
    connect(this, SIGNAL(setText(int, QString)),
             qml, SIGNAL(setText(int, QString)));
    connect(this, SIGNAL(setField(int, int, QString)),
             qml, SIGNAL(setField(int, int, QString)));
    connect(this, SIGNAL(setOpts(bool,bool,bool)),
             qml, SIGNAL(setOpts(bool,bool,bool)));
    connect(this, SIGNAL(setSigned(bool)),
             qml, SIGNAL(setSigned(bool)));

    // Signals to ItemBinary
    connect(this, SIGNAL(setBit(int, QString)),
             qml, SIGNAL(setBit(int, QString)));
    connect(this, SIGNAL(setBitGroup16Enabled(bool)),
             qml, SIGNAL(setBitGroup16Enabled(bool)));
    connect(this, SIGNAL(setBitGroup32Enabled(bool)),
             qml, SIGNAL(setBitGroup32Enabled(bool)));

    // Signals to ItemButtons
    connect(this, SIGNAL(setBitSize(int)),
             qml, SIGNAL(setBitSize(int)));

    // Signals from HeaderItemEntry
    connect(qml, SIGNAL(on_lineEdit_textChanged(int,int,QString)),
            this, SLOT(on_lineEdit_textChanged(int,int,QString)));

    // Signals to ItemHeaderEntry
    connect(this, SIGNAL(setHeaderEntry(int, QString)),
             qml, SIGNAL(setHeaderEntry(int, QString)));
    connect(this, SIGNAL(setHeaderEntryVisible(int)),
            qml, SLOT(setHeaderEntryVisible(int)));
    connect(this, SIGNAL(setHeaderEntryEnabled(int,bool)),
             qml, SIGNAL(setHeaderEntryEnabled(int,bool)));
    connect(this, SIGNAL(setHeaderEntryFocus(int)),
             qml, SIGNAL(setHeaderEntryFocus(int)));

    // Setup the user interface to an initial state
    SetUiState();

    /********automatic load settings**************************/
    QFileInfo fi(QDir::homePath() + "/.hextool/settings.ini");
    if (fi.exists())
    {
        QSettings settings(QDir::homePath() + "/.hextool/settings.ini", QSettings::IniFormat);
        settings.beginGroup("Options");
        optsl=settings.value("optsl").toBool();
        settings.endGroup();
        if (optsl)
        {
            load_ini();
        }
    }
    /**********************************************************/
    // Pass options to main.qml
    emit(setOpts(optsl,optsignext,optzerobased));
}


/****************************************************************************

    Qt Event Handler

    control:    hextool widget
    signal:     closed, exit

    It is used for automatic save during exit.

****************************************************************************/
void HexTool::closeEvent()
{
    if (optsl)
    {
        save_ini();
    }
    else
    {
        QFileInfo fi(QDir::homePath() + "/.hextool/settings.ini");
        if (fi.exists())
        {
            QSettings settings(QDir::homePath() + "/.hextool/settings.ini", QSettings::IniFormat);
            settings.beginGroup("Options");
            settings.setValue("optsl", optsl);
            settings.endGroup();
        }

    }

}

void HexTool::on_lineEdit_textChanged(int mode, int index, QString text)
{
    enum {NOTVISIBLE=0,IPADDR,CHAR};

    // did we just initialize the text fields by ourselves?
    if(mode==NOTVISIBLE)
        return;

    // did we remove the last character?
    if(text=="")
        return;

    if(mode==IPADDR)
    {
        switch(index)
        {
        case 0:
            HandleIpAddrEditBox(3, text.toUInt());
            break;
        case 1:
            HandleIpAddrEditBox(2, text.toUInt());
            break;
        case 2:
            HandleIpAddrEditBox(1, text.toUInt());
            break;
        case 3:
            HandleIpAddrEditBox(0, text.toUInt());
            break;
        }
        return;
    }

    if(mode==CHAR)
    {
        int val = (int)text[0].unicode();
        switch(index)
        {
        case 0:
            HandleAsciiEditBox(3, val);
            break;
        case 1:
            HandleAsciiEditBox(2, val);
            break;
        case 2:
            HandleAsciiEditBox(1, val);
            break;
        case 3:
            HandleAsciiEditBox(0, val);
            break;
        }
    }
}
void HexTool::btnHeaderClicked(int mode)
{
    enum {HELP=0,IPADR,CHARS};
    switch(mode)
    {
    case HELP:
        emit(btnHelpClicked());
        break;
    case IPADR:
        headerEntryVisible = HELP;
        emit(btnCloseClicked());
        break;
    case CHARS:
        headerEntryVisible = HELP;
        emit(btnCloseClicked());
        break;
    }
}
// Mouse area was clicked either in ItemIPAddres or in ItemChars
// Copy contents to the TextField elements
void HexTool::showHeaderEntry(int mode)
{
    enum {IPADR=1,CHARS};

    // Already visible? Close it.
    if(headerEntryVisible)
    {
        btnHeaderClicked(mode);
        return;
    }

    // Update visibility state: 0 -> 1 (IP address) or 2 (Unicode)
    headerEntryVisible = mode;

    // Initialize the contents for the entry fields
    UpdateDisplay();

    // Make the entry fields visible
    emit(setHeaderEntryVisible(mode));
}
/****************************************************************************

    Update Display function

    Refreshes the gui.
//QString::number(value,8) //octal
//int hex = str.toInt(&ok, 16);
//int dec = str.toInt(&ok, 10);
****************************************************************************/
void HexTool::UpdateDisplay()
{
    static bool updatingDisplay = false;
    enum {HEX=0,OCT,DEC};

    if (!updatingDisplay)
    {
    updatingDisplay = true;

    int value = GetValue(REG_CURRENT);
#ifdef QT_DEBUG
    qDebug() << "value from current reg [raw]:" << QString::number(value);
#endif

    char str[128];
    if (GetSigned()==UNSIGNED)
    {
        sprintf(str, "%u", value);

#ifdef QT_DEBUG
        qDebug() << "dec char128 [unsigned]:" << str;
#endif
    }
    else
    {
         switch (GetNumBits())
         {
             case NUMBITS_8:     sprintf(str, "%d", (qint8) value);    break;
             case NUMBITS_16:    sprintf(str, "%d", (qint16)value);    break;
             case NUMBITS_32:    sprintf(str, "%d", (qint32)value);    break;
         }
#ifdef QT_DEBUG
    qDebug() << "dec char128 [signed]:" << str;
#endif
    }
    emit(setText(DEC,str));

    sprintf(str, "%X", value);
    emit(setText(HEX,str));

    sprintf(str, "%o", value);
    emit(setText(OCT,str));

    // Update IP address

    sprintf(str, "%d", (quint8)((value & 0x000000FF) >> 0));
    emit(setField(1,3,str));
    if(headerEntryVisible==1) emit(setHeaderEntry(3,str));

    sprintf(str, "%d", (quint8)((value & 0x0000FF00) >> 8));
    emit(setField(1,2,str));
    if(headerEntryVisible==1) emit(setHeaderEntry(2,str));

    sprintf(str, "%d", (quint8)((value & 0x00FF0000) >> 16));
    emit(setField(1,1,str));
    if(headerEntryVisible==1) emit(setHeaderEntry(1,str));

    sprintf(str, "%d", (quint8)((value & 0xFF000000) >> 24));
    emit(setField(1,0,str));
    if(headerEntryVisible==1) emit(setHeaderEntry(0,str));

    // Update characters

    sprintf(str, "%c", (quint8)((value & 0x000000FF) >> 0));
    emit(setField(2,3,str));
    if(headerEntryVisible==2) emit(setHeaderEntry(3,str));

    sprintf(str, "%c", (quint8)((value & 0x0000FF00) >> 8));
    emit(setField(2,2,str));
    if(headerEntryVisible==2) emit(setHeaderEntry(2,str));

    sprintf(str, "%c", (quint8)((value & 0x00FF0000) >> 16));
    emit(setField(2,1,str));
    if(headerEntryVisible==2) emit(setHeaderEntry(1,str));

    sprintf(str, "%c", (quint8)((value & 0xFF000000) >> 24));
    emit(setField(2,0,str));
    if(headerEntryVisible==2) emit(setHeaderEntry(0,str));

    ////////////////////////////////////////////////////////////////////////
    int bitVal;

    for (int bit=0; bit<8; bit++)
    {
        bitVal = (value & (1<<bit))?1:0;
        sprintf(str, "%d", bitVal);
        emit(setBit(bit,str));
    }

    if (GetNumBits() != 8)  // 16 or 32
    {

        emit(setBitGroup16Enabled(true));
        emit(setHeaderEntryEnabled(2,true));

        for (int bit=8; bit<16; bit++)
        {
            bitVal = (value & (1<<bit))?1:0;
            sprintf(str, "%d", bitVal);
            emit(setBit(bit,str));
        }

        if (GetNumBits() != 16) // 32
        {

            emit(setBitGroup32Enabled(true));
            emit(setHeaderEntryEnabled(0,true));
            emit(setHeaderEntryEnabled(1,true));

            for (int bit=16; bit<32; bit++)
            {
                bitVal = (value & (1<<bit))?1:0;
                sprintf(str, "%d", bitVal);
                emit(setBit(bit,str));
            }
        }
        else //16
        {

            for (int i=1; i<=16; i++)
            {
                emit(setBit(i+15,""));
            }
            emit(setBitGroup32Enabled(false));
            emit(setHeaderEntryEnabled(0,false));
            //ui->lineEdit_ipaddress2->setDisabled(true);
            emit(setHeaderEntryEnabled(1,false));
        }
    }
    else // 8
    {
        for (int i=0; i<=23; i++)
        {
            //ui->buttonGroup->button(i+8)->setText("");
            setBit(i+8,"");
        }
        emit(setBitGroup16Enabled(false));
        emit(setBitGroup32Enabled(false));
        emit(setHeaderEntryEnabled(0,false));
        emit(setHeaderEntryEnabled(1,false));
        emit(setHeaderEntryEnabled(2,false));
    }
    updatingDisplay = false;
    }
}
/****************************************************************************

    Qt Signal Handler and toggle bit function

    control: pushbuttongroup
    signal: clicked

    Toggles single bits

****************************************************************************/

void HexTool::groupButton_clicked(int bit) { ToggleBit(bit-1); }

void HexTool::ToggleBit(int bit)
{
    HandleBinaryDigit(bit);
    UpdateDisplay();
}

/****************************************************************************

    Qt Signal Handler

    control:    lineEdit_dec
    signal:     textChanged

    The decimal number edit box has changed

****************************************************************************/
void HexTool::on_lineEdit_dec_textChanged(QString strValue)
{
    int value;
    if (GetSigned()==UNSIGNED)
    {
        value = (int)strValue.toUInt();
#ifdef QT_DEBUG
        qDebug() << "input unsigned dec:" << QString::number(value);
#endif
    }
    else
    {
        value = (int)strValue.toInt();
#ifdef QT_DEBUG
        qDebug() << "input signed dec:" << QString::number(value);
#endif
    }
    SetValue(value, REG_CURRENT);
    UpdateDisplay();
}
/****************************************************************************

    Qt Signal Handler

    control:    lineEdit_oct
    signal:     textChanged

    The octal number edit box has changed

****************************************************************************/
void HexTool::on_lineEdit_oct_textChanged(QString strValue)
{
    int value;
    value = (int)strValue.toUInt(0,8);
    SetValue(value, REG_CURRENT);
    UpdateDisplay();
}

/****************************************************************************

    Qt Signal Handler

    control:    lineEdit_hex
    signal:     textChanged

    The hexadecimal number edit box has changed

****************************************************************************/
void HexTool::on_lineEdit_hex_textChanged(QString strValue)
{
    int value;
    value = (int)strValue.toUInt(0,16);
    SetValue(value, REG_CURRENT);
    UpdateDisplay();
}
/****************************************************************************

    Qt Signal Handler

    control:    pushButton_clr
    signal:     clicked

    The clr button was clicked clears current register

****************************************************************************/
void HexTool::on_pushButton_clr_clicked()
{
    int value;
    value=0;
    SetValue(value, REG_CURRENT);
    UpdateDisplay();
}
/****************************************************************************

    Qt Signal Handler

    control:    radioButton_8bit
    signal:     pressed

    The radio button for 8 bit mode has been selected (aka pressed)

****************************************************************************/
void HexTool::on_radioButton_8bit_clicked()
{
    SetNumBits(NUMBITS_8);
    UpdateDisplay();
}

/****************************************************************************

    Qt Signal Handler

    control:    radioButton_16bit
    signal:     pressed

    The radio button for 16 bit mode has been selected (aka pressed)

****************************************************************************/
void HexTool::on_radioButton_16bit_clicked()
{
    int bitsize;
    int value = GetValue(REG_CURRENT);
#ifdef QT_DEBUG
        qDebug() << "not changed value(r16):" << QString::number(value);
#endif
    bitsize=GetNumBits();
    if (bitsize==8 && (GetSigned()==SIGNED) && optsignext)
    {
        qint8 signedvalue=value;
        SetNumBits(NUMBITS_16);
        SetValue(signedvalue, REG_CURRENT);
#ifdef QT_DEBUG
        qDebug() << "changed value(r16):" << QString::number(signedvalue);
#endif
    }
    else
    {
        SetNumBits(NUMBITS_16);
    }
    UpdateDisplay();
}

/****************************************************************************

    Qt Signal Handler

    control:    radioButton_32bit
    signal:     pressed

    The radio button for 32 bit mode has been selected (aka pressed)

****************************************************************************/
void HexTool::on_radioButton_32bit_clicked()
{
    int bitsize;
    int value=GetValue(REG_CURRENT);
#ifdef QT_DEBUG
    qDebug() << "not changed value(r32):" << QString::number(value);
#endif
    bitsize=GetNumBits();
    if (bitsize!=32 && (GetSigned()==SIGNED) && optsignext)
    {
        SetNumBits(NUMBITS_32);
        if (bitsize==8)
        {
            qint8 signedvalue=value;
            SetValue(signedvalue, REG_CURRENT);
#ifdef QT_DEBUG
        qDebug() << "changed value(r32):" << QString::number(signedvalue);
#endif
        }
        else if (bitsize==16)
        {
            qint16 signedvalue=value;
            SetValue(signedvalue, REG_CURRENT);
#ifdef QT_DEBUG
        qDebug() << "changed value:(r32)" << QString::number(signedvalue);
#endif
        }
    }
    else
    {
        SetNumBits(NUMBITS_32);
    }
    UpdateDisplay();
}
/****************************************************************************

    Qt Signal Handler

    control:    pushButton_not
    signal:     pressed

    The NOT button has been pressed

****************************************************************************/
void HexTool::on_pushButton_not_pressed()
{
    RegisterOperation(REG_CURRENT, REG_CURRENT, REG_CURRENT, OP_INVERSE);
    UpdateDisplay();
}
/****************************************************************************

   Qt Signal Handler

    control:    checkBox_signed
    signal:     toggled

    The checkbox for signed has been toggled for signed/unsigned operation

****************************************************************************/
void HexTool::on_checkBox_signed_toggled(bool isChecked)
{
    eSigned sig;

    if (isChecked)
        sig=SIGNED;
    else
        sig=UNSIGNED;

    SetSigned(sig);
    UpdateDisplay();
}
/****************************************************************************

    Qt Signal Handler

    control:    pushButton_bitNumbering
    signal:     pressed

    Toggle the labelling of the bits from zero based to 1 based

****************************************************************************/
void HexTool::on_pushButton_bitNumbering_pressed(bool zeroBased)
{
    optzerobased = zeroBased;   // Save the setting
}
/****************************************************************************

    Qt Signal Handler

    control:    pushButton_endianSwap
    signal:     pressed

    Toggles the endian between Big and Little endian

****************************************************************************/
void HexTool::on_pushButton_endianSwap_pressed()
{
    unsigned int value = GetValue(REG_CURRENT);
    unsigned int newValue = 0;

    switch (GetNumBits())
    {
      case 32:
        {
          newValue |= (value & 0x000000ff) << 24;
          newValue |= (value & 0x0000ff00) <<  8;
          newValue |= (value & 0x00ff0000) >>  8;
          newValue |= (value & 0xff000000) >> 24;
        }
        break;

      case 16:
        {
          newValue |= (value & 0x000000ff) << 8;
          newValue |= (value & 0x0000ff00) >> 8;
        }
        break;

      default:
      case 8:
        // don't do anything!
        newValue = value;
        break;
    }
    SetValue(newValue, REG_CURRENT);
    UpdateDisplay();
}

/****************************************************************************

    Qt Signal Handler

    control:    pushButton increase and decrease
    signal:     clicked

    increases decreases value by one

****************************************************************************/
void HexTool::on_pushButton_increase_clicked()
{
    int value = GetValue(REG_CURRENT);
    value++;
    SetValue(value, REG_CURRENT);
    UpdateDisplay();
}

void HexTool::on_pushButton_decrease_clicked()
{
    int value = GetValue(REG_CURRENT);
    value--;
    SetValue(value, REG_CURRENT);
    UpdateDisplay();
}

/****************************************************************************

    Qt Signal Handler

    control:    pushButton_neg
    signal:     clicked

    Makes the decimal value negative or positive in signed mode

****************************************************************************/
void HexTool::on_pushButton_neg_clicked()
{
    if (GetSigned()==SIGNED){
        int negatedValue=-GetValue(REG_CURRENT);
        QString strValue = QString::number(negatedValue);
        emit(setText(2,strValue));
        entryTextChanged(2,strValue);
    }
}

/****************************************************************************

    Qt Signal Handler

    control:    radioButton_register[A|B|C]
    signal:     clicked

    Select the current register that is being displayed

****************************************************************************/
void HexTool::on_radioButton_registerA_clicked()
{
    SetRegister(REG_A);
    UpdateDisplay();
}

void HexTool::on_radioButton_registerB_clicked()
{
    SetRegister(REG_B);
    UpdateDisplay();
}

void HexTool::on_radioButton_registerC_clicked()
{
    SetRegister(REG_C);
    UpdateDisplay();
}

/****************************************************************************

    This is the generic function to handle register operations after the user
    has clicked on one of the buttons.

****************************************************************************/
int HexTool::HandleOperation
(
    eOpType op
)
{
    // Perform the operation on the registers
    int retVal = RegisterOperation(REG_A, REG_B, REG_C, op);

    // change the display to show register C
    SetRegister(REG_C);
    emit(setReg(REG_C));

    // Update the display
    UpdateDisplay();

    return (retVal);
}

/****************************************************************************

    on_pushButton_regop_pressed Register operation button pressed

****************************************************************************/
void HexTool::on_pushButton_regop_pressed(int index)
{
    enum BtnName {BTN_AND=0,BTN_OR,BTN_XOR,BTN_PLUS,BTN_MINUS,BTN_MULT,
                 BTN_DIV,BTN_LSHIFT,BTN_RSHIFT,BTN_FLIP};

    switch(index) {
    case BTN_AND:
        HandleOperation(OP_AND);
        break;
    case BTN_OR:
        HandleOperation(OP_OR);
        break;
    case BTN_XOR:
        HandleOperation(OP_XOR);
        break;
    case BTN_PLUS:
        HandleOperation(OP_ADD);
        break;
    case BTN_MINUS:
        HandleOperation(OP_SUBTRACT);
        break;
    case BTN_MULT:
        HandleOperation(OP_MULTIPLY);
        break;
    case BTN_DIV:
        HandleOperation(OP_DIVIDE);
        break;
    case BTN_LSHIFT:
        RegisterOperation(REG_CURRENT, REG_CURRENT, REG_CURRENT, OP_LEFT_SHIFT);
        UpdateDisplay();
        break;
    case BTN_RSHIFT:
        RegisterOperation(REG_CURRENT, REG_CURRENT, REG_CURRENT, OP_RIGHT_SHIFT);
        UpdateDisplay();
        break;
    case BTN_FLIP:
        on_pushButton_endianSwap_pressed();
        break;
    };
}

/****************************************************************************

    This generic handler deals with the user editing the IP Address edit
    boxes.
    It will automatically move the focus to the next control if the user
    enters a 3 digit number, because each part of an IP address is always
    in the range 0...255.
    Users are also forbidden from entering numbers greater than 255.

****************************************************************************/
void HexTool::HandleIpAddrEditBox
(
    int field,
    unsigned int val
)
{
    if (field < 4)
    {
        if ((val & 0xFFFFFF00) == 0)
        {
            int currentValue    = GetValue(REG_CURRENT);    // the current value stored in the current register
            int newValue        = 0;                        // the new value that we want to to set the register to

            switch (field)   // which byte was modified (i.e. which ASCI edit box)
            {
                case 0: newValue = (currentValue & 0xFFFFFF00) | (val      ); break;
                case 1: newValue = (currentValue & 0xFFFF00FF) | (val <<  8); break;
                case 2: newValue = (currentValue & 0xFF00FFFF) | (val << 16); break;
                case 3: newValue = (currentValue & 0x00FFFFFF) | (val << 24); break;
            }

            SetValue(newValue, REG_CURRENT);
            UpdateDisplay();

            // If the value has changed, skip to the next character
            if ((newValue != currentValue) && (val > 99))
            {
                int nextField=0;
                switch (field)
                {
                case 0:
                    switch (GetNumBits())
                    {
                    case NUMBITS_8:  nextField = 0; break;
                    case NUMBITS_16: nextField = 1; break;
                    case NUMBITS_32: nextField = 3; break;
                    }
                    break;
                case 1: nextField = 0; break;
                case 2: nextField = 1; break;
                case 3: nextField = 2; break;
                }
                emit(setHeaderEntryFocus(3-nextField));
            }
        }
        else
        {
            // refuse to accept more than 255 in an IP Addr edit box
            UpdateDisplay();
        }
    }
}


/****************************************************************************

    Qt Signal Handler

    control:    lineEdit_ipaddressX
    signal:     textChanged

    When the users edits the ip address fields, these handlers pass control
    to the generic HandleIpAddrEditBox function.

****************************************************************************/
void HexTool::on_lineEdit_ipaddress_textChanged(int index, QString text)
{
    switch(index)
    {
    case 0:
        HandleIpAddrEditBox(3, text.toUInt());
        break;
    case 1:
        HandleIpAddrEditBox(2, text.toUInt());
        break;
    case 2:
        HandleIpAddrEditBox(1, text.toUInt());
        break;
    case 3:
        HandleIpAddrEditBox(0, text.toUInt());
        break;
    }
}
/****************************************************************************

    The generic handler called when the users types into the ASCII edit boxes.
    The UI is programmed to only allow 1 character using the form designer.
    This function automatically moves focus to the next ASCII edit control,
    wrapping back to the first.

****************************************************************************/
void HexTool::HandleAsciiEditBox
(
    int field,
    unsigned int val
)
{
    if (field < 4)
    {
        int newByte         = val & 0x000000FF;// the byte that was just typed in the ASCII edit box
        int currentValue    = GetValue(REG_CURRENT);    // the current value stored in the current register
        int newValue        = 0;                        // the new value that we want to to set the register to

        switch (field)   // which byte was modified (i.e. which ASCI edit box)
        {
            case 0: newValue = (currentValue & 0xFFFFFF00) | (newByte      ); break;
            case 1: newValue = (currentValue & 0xFFFF00FF) | (newByte <<  8); break;
            case 2: newValue = (currentValue & 0xFF00FFFF) | (newByte << 16); break;
            case 3: newValue = (currentValue & 0x00FFFFFF) | (newByte << 24); break;
        }

        SetValue(newValue, REG_CURRENT);
        UpdateDisplay();

        // If the value has changed, skip to the next character
        if (newValue != currentValue)
        {
            int nextField=0;
            switch (field)
            {
            case 0:
                switch (GetNumBits())
                {
                case NUMBITS_8:  nextField = 0; break;
                case NUMBITS_16: nextField = 1; break;
                case NUMBITS_32: nextField = 3; break;
                }
                break;
            case 1: nextField = 0; break;
            case 2: nextField = 1; break;
            case 3: nextField = 2; break;
            }
            emit(setHeaderEntryFocus(3-nextField));
        }
    }
}
/****************************************************************************

    Qt Signal Handler

    control:    lineEdit_asciiX
    signal:     textChanged

    Passes control on to a generic handler after extracting the new ASCII
    value that was entered.

****************************************************************************/
void HexTool::on_lineEdit_ascii_textChanged(int index, QString text)
{
    int val = (int)text[0].unicode();

    switch(index)
    {
    case 0:
        HandleAsciiEditBox(3, val);
        break;
    case 1:
        HandleAsciiEditBox(2, val);
        break;
    case 2:
        HandleAsciiEditBox(1, val);
        break;
    case 3:
        HandleAsciiEditBox(0, val);
        break;
    }
}
/****************************************************************************

    clearAll function clears values from all register

****************************************************************************/
void HexTool::clearAll()
{
    int value;
    value=0;
    SetValue(value, REG_A);
    SetValue(value, REG_B);
    SetValue(value, REG_C);
    UpdateDisplay();

}
/****************************************************************************

    Save function

    Saves status of radiobuttons, checkbox, all register values and
    the options in an ini file

****************************************************************************/
void HexTool::save_ini()
{

    QSettings settings(QDir::homePath() + "/.hextool/settings.ini", QSettings::IniFormat);
    settings.beginGroup("General");

    // Save signed selection, bit size and register selection

    settings.setValue("signed",(GetSigned()==SIGNED));
    int bitsize = GetNumBits();
    settings.setValue("bitsize",bitsize);
    settings.setValue("lastreg",GetRegister());

    settings.setValue("valuerega", GetValue(REG_A));
    settings.setValue("valueregb", GetValue(REG_B));
    settings.setValue("valueregc", GetValue(REG_C));
    settings.endGroup();
    settings.beginGroup("Options");
    settings.setValue("optsl", optsl);
    settings.setValue("optsignext", optsignext);
    settings.setValue("optzerobased", optzerobased);
    settings.endGroup();
}
/****************************************************************************

    Load function

    Loads status of radiobuttons, checkbox, all register values and
    the options from an ini file

****************************************************************************/
void HexTool::load_ini()
{
    QFileInfo fi(QDir::homePath() + "/.hextool/settings.ini");
    if (!fi.exists())
    {
    }
    else
    {
        int bitsize;
        int reg_id;
        int valueA;
        int valueB;
        int valueC;
        QSettings settings(QDir::homePath() + "/.hextool/settings.ini", QSettings::IniFormat);
        settings.beginGroup("General");
        emit(setSigned(settings.value("signed").toBool()));
        bitsize=settings.value("bitsize").toInt(); // 8,16,32
        reg_id=settings.value("lastreg").toInt();  // 0-2
        valueA=settings.value("valuerega").toInt();
        valueB=settings.value("valueregb").toInt();
        valueC=settings.value("valueregc").toInt();
        settings.endGroup();
        settings.beginGroup("Options");
        optsl=settings.value("optsl").toBool();
        optsignext=settings.value("optsignext").toBool();
        optzerobased=settings.value("optzerobased").toBool();
        settings.endGroup();

        switch (bitsize)
        {
        case 32:
           emit(setBitSize(0));
           on_radioButton_32bit_clicked();
           break;
        case 16:
           emit(setBitSize(1));
           on_radioButton_16bit_clicked();
           break;
        case 8:
           emit(setBitSize(2));
           on_radioButton_8bit_clicked();
           break;
        default:
           qDebug() << "switch:" << QString::number(bitsize);
        }
        switch (reg_id)
        {
        case 0:
           emit(setReg(REG_A));
           SetRegister(REG_A);
           break;
        case 1:
           emit(setReg(REG_B));
           SetRegister(REG_B);
           break;
        case 2:
           emit(setReg(REG_C));
           SetRegister(REG_C);
           break;
        default:
           qDebug() << "switch:" << QString::number(reg_id);
        }

        SetValue(valueA, REG_A);
        SetValue(valueB, REG_B);
        SetValue(valueC, REG_C);
        UpdateDisplay();

    }
}
void HexTool::SetUiState()
{
    int bitsize;
    int reg_id;
    bool isSigned;

    isSigned = (GetSigned()==SIGNED);
    emit(setSigned(isSigned));

    bitsize = GetNumBits();

    switch (bitsize)
    {
    case 32:
       emit(setBitSize(0));
       on_radioButton_32bit_clicked();
       break;
    case 16:
       emit(setBitSize(1));
       on_radioButton_16bit_clicked();
       break;
    case 8:
       emit(setBitSize(2));
       on_radioButton_8bit_clicked();
       break;
    default:
       qDebug() << "switch:" << QString::number(bitsize);
    }

    reg_id = GetRegister();

    switch (reg_id)
    {
    case 0:
       emit(setReg(REG_A));
       break;
    case 1:
       emit(setReg(REG_B));
       break;
    case 2:
       emit(setReg(REG_C));
       break;
    default:
       qDebug() << "switch:" << QString::number(reg_id);
    }

}

/****************************************************************************

    QDialog: Options

    Shows the option checkboxes and returns bool statements

****************************************************************************/
void HexTool::optDialog(bool saveload, bool signext)
{
    optsl=saveload;
    optsignext=signext;
}

/****************************************************************************

    Handle new entry (user types a number and clicks enter)

    control:    ItemNumberEntry/entryFields
    signal:     Keys.onReturnPressed

    The number edit box has changed

****************************************************************************/
void HexTool::entryTextChanged(int index, QString strValue)
{
    switch(index) {
    case 0:     // hex
        on_lineEdit_hex_textChanged(strValue);
        break;
    case 1:     // oct
        on_lineEdit_oct_textChanged(strValue);
        break;
    case 2:     // dec
        on_lineEdit_dec_textChanged(strValue);
        break;
    }
}


void HexTool::on_radioButton_bitsize_clicked(int bitsize)
{
    switch(bitsize) {
    case 2:
        on_radioButton_8bit_clicked();
        break;
    case 1:
        on_radioButton_16bit_clicked();
        break;
    case 0:
        on_radioButton_32bit_clicked();
        break;
    }
}

void HexTool::on_radiobutton_register_clicked(int index)
{
    switch(index)
    {
    case REG_A:
        on_radioButton_registerA_clicked();
        break;
    case REG_B:
        on_radioButton_registerB_clicked();
        break;
    case REG_C:
        on_radioButton_registerC_clicked();
        break;
    }
}



