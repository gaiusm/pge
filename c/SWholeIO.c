/* This file is part of GNU Modula-2.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA  02110-1301  USA  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _SWholeIO_H
#define _SWholeIO_C

#   include "GStdChans.h"
#   include "GWholeIO.h"

void SWholeIO_ReadInt (int *int_);
void SWholeIO_WriteInt (int int_, unsigned int width);
void SWholeIO_ReadCard (unsigned int *card);
void SWholeIO_WriteCard (unsigned int card, unsigned int width);

void SWholeIO_ReadInt (int *int_)
{
  /* Skips leading spaces, and removes any remaining characters
     from the default input stream that form part of a signed
     whole number.  The value of this number is assigned to int.
     The read result is set to the value allRight, outOfRange,
     wrongFormat, endOfLine, or endOfInput.
  */
  WholeIO_ReadInt ((IOChan_ChanId) StdChans_StdInChan (), int);
}

void SWholeIO_WriteInt (int int_, unsigned int width)
{
  /* Writes the value of int to the default output stream in
     text form, in a field of the given minimum width.  */
  WholeIO_WriteInt ((IOChan_ChanId) StdChans_StdOutChan (), int_, width);
}

void SWholeIO_ReadCard (unsigned int *card)
{
  /* Skips leading spaces, and removes any remaining characters
     from the default input stream that form part of an unsigned
     whole number.  The value of this number is assigned to card.
     The read result is set to the value allRight, outOfRange,
     wrongFormat, endOfLine, or endOfInput.
  */
  WholeIO_ReadCard ((IOChan_ChanId) StdChans_StdInChan (), card);
}

void SWholeIO_WriteCard (unsigned int card, unsigned int width)
{
  /* Writes the value of card to the default output stream in
     text form, in a field of the given minimum width.  */
  WholeIO_WriteCard ((IOChan_ChanId) StdChans_StdOutChan (), card, width);
}

void _M2_SWholeIO_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_SWholeIO_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
