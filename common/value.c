/****************************************************************************

    FILE:    value.c

    COMMENTS:

    EXPORTED FUNCTIONS:
        GetValue
        SetValue

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
#include "numbits.h"
#include "register.h"
#include "value.h"



/****************************************************************************

  Global variable and access functions used to store the values for each
  register

  The global is initialised as startup because it will vary in size depending
  on the value of REG_NUM

  I store the value as an int, but it gets used as different types
  depending on which options are set (signed/unsigned, 8/16/32 bit, ...)

****************************************************************************/
static int S_value[REG_NUM];


int GetValue
(
    eRegNum reg  // the register would we like to get the value for
)
{
    if (reg == REG_CURRENT)
    {
        reg = GetRegister();
    }

    // Filter the value for the number of bits we are currently displaying
    switch (GetNumBits())
    {
        case NUMBITS_8:     S_value[reg] &= 0xFF;   break;
        case NUMBITS_16:    S_value[reg] &= 0xFFFF; break;
        default:
            break;
    }

    return (S_value[reg]);
}


int SetValue
(
    int     value,  // the new value
    eRegNum  reg     // the register we want to set
)
{
    if (reg == REG_CURRENT)
    {
        reg = GetRegister();
    }

    S_value[reg] = value;
    return (value);
}
