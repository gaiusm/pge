/* This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GNU Modula-2 is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with gm2; see the file COPYING.  If not, write to the Free Software
Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "Gmcrts.h"
#define _M2EXCEPTION_H
#define _M2EXCEPTION_C

#   include "GRTExceptions.h"
#   include "GSYSTEM.h"

typedef enum {M2EXCEPTION_indexException, M2EXCEPTION_rangeException, M2EXCEPTION_caseSelectException, M2EXCEPTION_invalidLocation, M2EXCEPTION_functionException, M2EXCEPTION_wholeValueException, M2EXCEPTION_wholeDivException, M2EXCEPTION_realValueException, M2EXCEPTION_realDivException, M2EXCEPTION_complexValueException, M2EXCEPTION_complexDivException, M2EXCEPTION_protException, M2EXCEPTION_sysException, M2EXCEPTION_coException, M2EXCEPTION_exException} M2EXCEPTION_M2Exceptions;

M2EXCEPTION_M2Exceptions M2EXCEPTION_M2Exception (void);
unsigned int M2EXCEPTION_IsM2Exception (void);

M2EXCEPTION_M2Exceptions M2EXCEPTION_M2Exception (void)
{
  /* If the current coroutine is in the exceptional execution state because of the raising
     of a language exception, returns the corresponding enumeration value, and otherwise
     raises an exception.
  */
  if (M2EXCEPTION_IsM2Exception ())
    return (M2EXCEPTION_M2Exceptions) (RTExceptions_GetNumber (RTExceptions_GetExceptionBlock ()));
  else
    RTExceptions_Raise ((unsigned int) (M2EXCEPTION_exException), "/home/gaius/GM2/graft-9.1.0/gcc-9.1.0/gcc/gm2/gm2-libs-iso/M2EXCEPTION.mod", 36, 25, "M2Exception", "current coroutine is not in the exceptional execution state");
  ReturnException ("/home/gaius/GM2/graft-9.1.0/gcc-9.1.0/gcc/gm2/gm2-libs-iso/M2EXCEPTION.def", 8, 1);
}

unsigned int M2EXCEPTION_IsM2Exception (void)
{
  /* If the current coroutine is in the exceptional execution state because of the raising
     of a language exception, returns TRUE, and otherwise returns FALSE.
  */
  return (RTExceptions_IsInExceptionState ()) && ((RTExceptions_GetBaseExceptionBlock ()) == (RTExceptions_GetExceptionBlock ()));
}

void _M2_M2EXCEPTION_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_M2EXCEPTION_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
