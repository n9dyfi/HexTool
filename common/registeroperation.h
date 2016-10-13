/****************************************************************************

    FILE:    eoptype.h

    COMMENTS:

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
#ifndef _EOPTYPE_H
#define _EOPTYPE_H

#ifndef _REGISTER_H
#pragma message("WARNING: you must include register.h before including registeroperation.h")
#endif

/****************************************************************************

  Enum used represent operations that can be performed on a register

****************************************************************************/
typedef enum
{
    // single register operations
    OP_INCREMENT,
    OP_DECREMENT,
    OP_LEFT_SHIFT,
    OP_RIGHT_SHIFT,
    OP_INVERSE,

    // multiple register logical operations
    OP_AND,
    OP_OR,
    OP_XOR,

    // multiple register mathematical operations
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE
}
eOpType;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int RegisterOperation
(
    eRegNum reg1,
    eRegNum reg2,
    eRegNum reg3,
    eOpType op
);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
#endif // _EOPTYPE_H
