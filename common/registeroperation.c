/****************************************************************************

    FILE:    registeroperation.c

    COMMENTS:

    EXPORTED FUNCTIONS:
        RegisterOperation

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
#include "registeroperation.h"
#include "value.h"
#include "signed.h"

/****************************************************************************

    Perform a mathmatical/logical operation on registers A and B and store
    the result in register C

****************************************************************************/
int RegisterOperation
(
    eRegNum reg1,
    eRegNum reg2,
    eRegNum reg3,
    eOpType op
)
{
    int a,b,c;

    a = GetValue(reg1);
    b = GetValue(reg2);

    switch (op)
    {
        case OP_INVERSE:        c = ~a;     break;
        case OP_INCREMENT:      c = a + 1;  break;
        case OP_DECREMENT:      c = a - 1;  break;
        case OP_LEFT_SHIFT:     c = a << 1; break;
        case OP_RIGHT_SHIFT:
            // Unsigned numbers do not retain the high bit when right shifted, only signed numbers do this
            if (GetSigned())
            {
                c = a >> 1; 
            }
            else
            {
                c = (unsigned int)a >> 1;
            }
            break;

        case OP_AND:            c = a & b;  break;
        case OP_OR:             c = a | b;  break;
        case OP_XOR:            c = a ^ b;  break;

        case OP_ADD:            c = a + b;  break;
        case OP_SUBTRACT:       c = a - b;  break;
        case OP_MULTIPLY:       c = a * b;  break;

        case OP_DIVIDE:
            if (b != 0)
            {
                c = (a / b);
            }
                else
            {
                c = -1;
            }
            break;

        default:
            return (-1);
    }

    SetValue(c, reg3);
    return (c);
}


