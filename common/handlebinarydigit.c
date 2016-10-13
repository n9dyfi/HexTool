/****************************************************************************

    FILE:    handlebinarydigit.c

    COMMENTS:

    EXPORTED FUNCTIONS:
        HandleBinaryDigit

 ****************************************************************************

    LICENSE:

    HexTool -  a simple program to convert numbers on the fly
    Copyright (C) 2003 Ryan Harkin; www.harkin.org/HexTool

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
#include "debug.h"
#include "register.h"
#include "numbits.h"
#include "value.h"


/****************************************************************************

  Set the bit specified in the values in the decimal and hex edit boxes

  This function is called because the user toggled a check box associated
  with the binary values.

  First read the value in the decimal edit box, set the bit and update the 
  value in the same edit box again.  This will cause the hex edit box to
  update automatically.

****************************************************************************/
void SetBit
(
    unsigned bit,    // which bit? (1 based number)
    int state   // set or clear the bit?
)
{
    int value;

    if (bit < GetNumBits())
    {
        value = GetValue(REG_CURRENT);
        if (state)
        {
            value |= (1<<bit);
        }
        else
        {
            value &= ~(1<<bit);
        }
        SetValue(value, REG_CURRENT);
    }
}


/****************************************************************************

    PURPOSE:    Handle the events for the binary digit buttons

    COMMENTS:   Pressing a button toggles the digit

****************************************************************************/
void HandleBinaryDigit
(
    unsigned bit
)
{
    if ( bit < GetNumBits() )
    {
        int value = GetValue(REG_CURRENT);

        if ( value & (1 << bit) )
        {
            SetBit ( bit, 0 );
        }
        else
        {
            SetBit ( bit, 1 );
        }
    }
}
