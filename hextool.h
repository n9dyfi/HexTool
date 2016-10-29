/****************************************************************************

    FILE:    hextool.h

    COMMENTS:

 ****************************************************************************

    LICENSE:

    HexTool -  a simple program to convert numbers on the fly
    Copyright (C) 2003 Ryan Harkin, 2014 Christian Weniger; www.harkin.org/HexTool

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

#ifndef HEXTOOL_H
#define HEXTOOL_H

#include <QObject>

#include <common/debug.h>
#include <common/handlebinarydigit.h>
#include <common/numbits.h>
#include <common/register.h>
#include <common/registeroperation.h>
#include <common/signed.h>
#include <common/value.h>

class HexTool : public QObject
{
    Q_OBJECT
public:
    explicit HexTool(QObject *qml, QObject *parent = 0);

    bool optsl;         // option: save & load
    bool optsignext;    // option: sign extension
    bool optzerobased;  // option: zero-based index

private slots:
    void groupButton_clicked(int);

    void on_radioButton_32bit_clicked();
    void on_radioButton_16bit_clicked();
    void on_radioButton_8bit_clicked();
    void on_lineEdit_dec_textChanged(QString);
    void on_lineEdit_hex_textChanged(QString);
    void on_pushButton_not_pressed();
    void on_checkBox_signed_toggled(bool isSigned);

    void closeEvent();
    void btnHeaderClicked(int);
    void on_pushButton_regop_pressed(int index);
    void on_radiobutton_register_clicked(int);
    void on_pushButton_endianSwap_pressed();
    void on_pushButton_bitNumbering_pressed(bool);
    void entryTextChanged(int,QString);

    void on_radioButton_bitsize_clicked(int bitsize);





    void on_lineEdit_ipaddress_textChanged(int,QString);
    void on_lineEdit_ascii_textChanged(int,QString);
    void on_lineEdit_textChanged(int,int,QString);

    // Display IP address / character entry fields in the header
    void showHeaderEntry(int mode);

    void on_pushButton_increase_clicked();
    void on_pushButton_decrease_clicked();

    void on_radioButton_registerA_clicked();
    void on_radioButton_registerB_clicked();
    void on_radioButton_registerC_clicked();

    void on_lineEdit_oct_textChanged(QString);

    void on_pushButton_clr_clicked();
    void clearAll();
    void save_ini();
    void load_ini();

    void optDialog(bool,bool);

    void on_pushButton_neg_clicked();

signals:
    void setReg(int);
    void setText(int, QString);
    void setField(int, int, QString);
    void setSigned(bool);
    void setOpts(bool,bool,bool);
    void btnHelpClicked();
    void btnCloseClicked();

    // Signals for ItemBinary
    void setBit(int, QString);
    void setBitGroup16Enabled(bool);
    void setBitGroup32Enabled(bool);

    // Signals for ItemButtons
    void setBitSize(int);

    // Signals for ItemHeaderEntry
    void setHeaderEntry(int, QString);
    void setHeaderEntryVisible(int);
    void setHeaderEntryEnabled(int,bool);
    void setHeaderEntryFocus(int);

private:

    int headerEntryVisible;

    void UpdateDisplay();
    void ToggleBit(int b);
    int  HandleOperation(eOpType op);
    void HandleIpAddrEditBox(int field, unsigned int val);
    void HandleAsciiEditBox(int field, unsigned int val);

    void SetUiState();
};


#endif // HEXTOOL_H
