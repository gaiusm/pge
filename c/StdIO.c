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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _StdIO_H
#define _StdIO_C

#   include "GIO.h"
#   include "GM2RTS.h"

typedef struct StdIO_ProcWrite_p StdIO_ProcWrite;

typedef struct StdIO_ProcRead_p StdIO_ProcRead;

#   define MaxStack 40
typedef struct _T1_a _T1;

typedef struct _T2_a _T2;

typedef void (*StdIO_ProcWrite_t) (char);
struct StdIO_ProcWrite_p { StdIO_ProcWrite_t proc; };

typedef void (*StdIO_ProcRead_t) (char *);
struct StdIO_ProcRead_p { StdIO_ProcRead_t proc; };

struct _T1_a { StdIO_ProcWrite array[MaxStack+1]; };
struct _T2_a { StdIO_ProcRead array[MaxStack+1]; };
static _T1 StackW;
static unsigned int StackWPtr;
static _T2 StackR;
static unsigned int StackRPtr;

/*
   Read - is the generic procedure that all higher application layers
          should use to receive a character.
*/

void StdIO_Read (char *ch);

/*
   Write - is the generic procedure that all higher application layers
           should use to emit a character.
*/

void StdIO_Write (char ch);

/*
   PushOutput - pushes the current Write procedure onto a stack,
                any future references to Write will actually invoke
                procedure, p.
*/

void StdIO_PushOutput (StdIO_ProcWrite p);

/*
   PopOutput - restores Write to use the previous output procedure.
*/

void StdIO_PopOutput (void);

/*
   GetCurrentOutput - returns the current output procedure.
*/

StdIO_ProcWrite StdIO_GetCurrentOutput (void);

/*
   PushInput - pushes the current Read procedure onto a stack,
               any future references to Read will actually invoke
               procedure, p.
*/

void StdIO_PushInput (StdIO_ProcRead p);

/*
   PopInput - restores Write to use the previous output procedure.
*/

void StdIO_PopInput (void);

/*
   GetCurrentInput - returns the current input procedure.
*/

StdIO_ProcRead StdIO_GetCurrentInput (void);


/*
   Read - is the generic procedure that all higher application layers
          should use to receive a character.
*/

void StdIO_Read (char *ch)
{
  (*StackR.array[StackRPtr].proc) (ch);
}


/*
   Write - is the generic procedure that all higher application layers
           should use to emit a character.
*/

void StdIO_Write (char ch)
{
  (*StackW.array[StackWPtr].proc) (ch);
}


/*
   PushOutput - pushes the current Write procedure onto a stack,
                any future references to Write will actually invoke
                procedure, p.
*/

void StdIO_PushOutput (StdIO_ProcWrite p)
{
  if (StackWPtr == MaxStack)
    M2RTS_HALT (-1);
  else
    {
      StackWPtr += 1;
      StackW.array[StackWPtr] = p;
    }
}


/*
   PopOutput - restores Write to use the previous output procedure.
*/

void StdIO_PopOutput (void)
{
  if (StackWPtr == 1)
    M2RTS_HALT (-1);
  else
    StackWPtr -= 1;
}


/*
   GetCurrentOutput - returns the current output procedure.
*/

StdIO_ProcWrite StdIO_GetCurrentOutput (void)
{
  if (StackWPtr > 0)
    return StackW.array[StackWPtr];
  else
    M2RTS_HALT (-1);
}


/*
   PushInput - pushes the current Read procedure onto a stack,
               any future references to Read will actually invoke
               procedure, p.
*/

void StdIO_PushInput (StdIO_ProcRead p)
{
  if (StackRPtr == MaxStack)
    M2RTS_HALT (-1);
  else
    {
      StackRPtr += 1;
      StackR.array[StackRPtr] = p;
    }
}


/*
   PopInput - restores Write to use the previous output procedure.
*/

void StdIO_PopInput (void)
{
  if (StackRPtr == 1)
    M2RTS_HALT (-1);
  else
    StackRPtr -= 1;
}


/*
   GetCurrentInput - returns the current input procedure.
*/

StdIO_ProcRead StdIO_GetCurrentInput (void)
{
  if (StackRPtr > 0)
    return StackR.array[StackRPtr];
  else
    M2RTS_HALT (-1);
}

void _M2_StdIO_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  StackWPtr = 0;
  StackRPtr = 0;
  StdIO_PushOutput ((StdIO_ProcWrite) {(StdIO_ProcWrite_t) IO_Write});
  StdIO_PushInput ((StdIO_ProcRead) {(StdIO_ProcRead_t) IO_Read});
}

void _M2_StdIO_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
