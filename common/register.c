/****************************************************************************

    FILE:    register.c

    COMMENTS:

    EXPORTED FUNCTIONS:
        GetRegister
        SetRegister

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



/****************************************************************************

  global variable and access functions used to get/set the current register

****************************************************************************/

static eRegNum S_current_reg = REG_A;


eRegNum GetRegister
(
    void
)
{
    return (S_current_reg);
}


eRegNum SetRegister
(
    eRegNum reg  // the new current register
)
{
    if (reg != REG_CURRENT)
    {
        S_current_reg = reg;
    }
    return (S_current_reg);
}
