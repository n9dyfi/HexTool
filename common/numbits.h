/****************************************************************************

    FILE:    numbits.h

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
#ifndef _NUM_BITS_H
#define _NUM_BITS_H

/****************************************************************************

  Enum used to represent the number of bits that we are currently using.

  I've made the values correspond to the number of bits so that the program
  can perform for(;;) loops based on the return value of GetNumBits().
  But I didn't want to be able to set the number of bits to an invalid
  value using SetNumBits().

****************************************************************************/
typedef enum
{
    NUMBITS_8  = 8,
    NUMBITS_16 = 16,
    NUMBITS_32 = 32
}
eNumBits;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

eNumBits GetNumBits(void);
eNumBits SetNumBits
(
    eNumBits num    // the new global bit depth (i.e. not per-register)
);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // _NUM_BITS_H
