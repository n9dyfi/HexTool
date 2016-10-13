/****************************************************************************

    FILE:    value.h

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
#ifndef _VALUE_H
#define _VALUE_H

#ifndef _REGISTER_H
#pragma message("WARNING: you must include register.h before including value.h")
#endif


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int GetValue
(
    eRegNum reg  // the register would we like to get the value for
);
int SetValue
(
    int     value,  // the new value
    eRegNum reg     // the register we want to set
);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
#endif // _VALUE_H
