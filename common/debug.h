/****************************************************************************

    FILE:    debug.h

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
#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef WIN32
    // In debug mode, we want all symbols to be global so that we can debug easily
    #ifdef _DEBUG
        #define STATIC
    #else
        #define STATIC static
    #endif  // _DEBUG
#endif

#endif // _DEBUG_H
