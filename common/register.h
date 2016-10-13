/****************************************************************************

    FILE:    register.h

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
#ifndef _REGISTER_H
#define _REGISTER_H

/****************************************************************************

  Enum used represent the current register

****************************************************************************/
typedef enum
{
    REG_A = 0,
    REG_B,
    REG_C,
    REG_NUM,    // represents the number of registers
    REG_CURRENT = REG_NUM
}
eRegNum;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

eRegNum GetRegister(void);
eRegNum SetRegister
(
    eRegNum reg  // the new current register
);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
#endif // _REGISTER_H
