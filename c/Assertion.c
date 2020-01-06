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
MA 02110-1301 USA  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _Assertion_H
#define _Assertion_C

#   include "GStrIO.h"
#   include "GM2RTS.h"


/*
   Assert - tests the boolean Condition, if it fails then HALT is called.
*/

void Assertion_Assert (unsigned int Condition);


/*
   Assert - tests the boolean Condition, if it fails then HALT is called.
*/

void Assertion_Assert (unsigned int Condition)
{
  if (! Condition)
    {
      StrIO_WriteString ((char *) "assert failed - halting system", 30);
      StrIO_WriteLn ();
      M2RTS_HALT (-1);
    }
}

void _M2_Assertion_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_Assertion_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
