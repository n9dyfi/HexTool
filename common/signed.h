/****************************************************************************

    FILE:    signed.h

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
#ifndef _SIGNED_H
#define _SIGNED_H

typedef enum
{
    UNSIGNED = 0,
    SIGNED
}
eSigned;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

eSigned GetSigned(void);
eSigned SetSigned
(
    eSigned isSigned   // new signed mode to set
);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
#endif // _SIGNED_H
