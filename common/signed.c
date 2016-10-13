/****************************************************************************

    FILE:    signed.c

    COMMENTS:

    EXPORTED FUNCTIONS:
        GetSigned
        SetSigned

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
#include "signed.h"


/****************************************************************************

  Global variable and access functions to hold the signed/unsigned mode

****************************************************************************/
static eSigned S_signed = UNSIGNED;


eSigned GetSigned
(
    void
)
{
    return (S_signed);
}


eSigned SetSigned
(
    eSigned isSigned   // new signed mode to set
)
{
    S_signed = isSigned;
    return (S_signed);
}
