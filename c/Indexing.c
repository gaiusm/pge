/* do not edit automatically generated by mc from Indexing.  */
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

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#include <stddef.h>
#include <stdlib.h>
#   include "GStorage.h"
#   include "Gmcrts.h"
#define _Indexing_H
#define _Indexing_C

#   include "Glibc.h"
#   include "GStorage.h"
#   include "GSYSTEM.h"
#   include "GM2RTS.h"

typedef struct Indexing_IndexProcedure_p Indexing_IndexProcedure;

#   define MinSize 128
typedef struct _T1_r _T1;

typedef void * *PtrToAddress;

typedef _T1 *Indexing_Index;

typedef unsigned char *PtrToByte;

typedef void (*Indexing_IndexProcedure_t) (void *);
struct Indexing_IndexProcedure_p { Indexing_IndexProcedure_t proc; };

struct _T1_r {
               void *ArrayStart;
               unsigned int ArraySize;
               unsigned int Used;
               unsigned int Low;
               unsigned int High;
               unsigned int Debug;
               unsigned int Map;
             };


/*
   InitIndex - creates and returns an Index.
*/

Indexing_Index Indexing_InitIndex (unsigned int low);

/*
   KillIndex - returns Index to free storage.
*/

Indexing_Index Indexing_KillIndex (Indexing_Index i);

/*
   DebugIndex - turns on debugging within an index.
*/

Indexing_Index Indexing_DebugIndex (Indexing_Index i);

/*
   InBounds - returns TRUE if indice, n, is within the bounds
              of the dynamic array.
*/

unsigned int Indexing_InBounds (Indexing_Index i, unsigned int n);

/*
   HighIndice - returns the last legally accessible indice of this array.
*/

unsigned int Indexing_HighIndice (Indexing_Index i);

/*
   LowIndice - returns the first legally accessible indice of this array.
*/

unsigned int Indexing_LowIndice (Indexing_Index i);

/*
   PutIndice - places, a, into the dynamic array at position i[n]
*/

void Indexing_PutIndice (Indexing_Index i, unsigned int n, void * a);

/*
   GetIndice - retrieves, element i[n] from the dynamic array.
*/

void * Indexing_GetIndice (Indexing_Index i, unsigned int n);

/*
   IsIndiceInIndex - returns TRUE if, a, is in the index, i.
*/

unsigned int Indexing_IsIndiceInIndex (Indexing_Index i, void * a);

/*
   RemoveIndiceFromIndex - removes, a, from Index, i.
*/

void Indexing_RemoveIndiceFromIndex (Indexing_Index i, void * a);

/*
   DeleteIndice - delete i[j] from the array.
*/

void Indexing_DeleteIndice (Indexing_Index i, unsigned int j);

/*
   IncludeIndiceIntoIndex - if the indice is not in the index, then
                            add it at the end.
*/

void Indexing_IncludeIndiceIntoIndex (Indexing_Index i, void * a);

/*
   ForeachIndiceInIndexDo - for each j indice of i, call procedure p(i[j])
*/

void Indexing_ForeachIndiceInIndexDo (Indexing_Index i, Indexing_IndexProcedure p);


/*
   InitIndex - creates and returns an Index.
*/

Indexing_Index Indexing_InitIndex (unsigned int low)
{
  Indexing_Index i;

  Storage_ALLOCATE ((void **) &i, sizeof (_T1));
  i->Low = low;
  i->High = 0;
  i->ArraySize = MinSize;
  Storage_ALLOCATE (&i->ArrayStart, MinSize);
  i->ArrayStart = libc_memset (i->ArrayStart, 0, (size_t) i->ArraySize);
  i->Debug = FALSE;
  i->Used = 0;
  i->Map = (unsigned int) 0;
  return i;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   KillIndex - returns Index to free storage.
*/

Indexing_Index Indexing_KillIndex (Indexing_Index i)
{
  Storage_DEALLOCATE (&i->ArrayStart, i->ArraySize);
  Storage_DEALLOCATE ((void **) &i, sizeof (_T1));
  return NULL;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   DebugIndex - turns on debugging within an index.
*/

Indexing_Index Indexing_DebugIndex (Indexing_Index i)
{
  i->Debug = TRUE;
  return i;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   InBounds - returns TRUE if indice, n, is within the bounds
              of the dynamic array.
*/

unsigned int Indexing_InBounds (Indexing_Index i, unsigned int n)
{
  if (i == NULL)
    {
      M2RTS_HALT (-1);
      __builtin_unreachable ();
    }
  else
    {
      return (n >= i->Low) && (n <= i->High);
    }
  ReturnException ("/home/gaius/GM2/graft-combine/gm2-floppsie/gcc/m2/gm2-libs/Indexing.def", 25, 1);
  __builtin_unreachable ();
}


/*
   HighIndice - returns the last legally accessible indice of this array.
*/

unsigned int Indexing_HighIndice (Indexing_Index i)
{
  if (i == NULL)
    {
      M2RTS_HALT (-1);
      __builtin_unreachable ();
    }
  else
    {
      return i->High;
    }
  ReturnException ("/home/gaius/GM2/graft-combine/gm2-floppsie/gcc/m2/gm2-libs/Indexing.def", 25, 1);
  __builtin_unreachable ();
}


/*
   LowIndice - returns the first legally accessible indice of this array.
*/

unsigned int Indexing_LowIndice (Indexing_Index i)
{
  if (i == NULL)
    {
      M2RTS_HALT (-1);
      __builtin_unreachable ();
    }
  else
    {
      return i->Low;
    }
  ReturnException ("/home/gaius/GM2/graft-combine/gm2-floppsie/gcc/m2/gm2-libs/Indexing.def", 25, 1);
  __builtin_unreachable ();
}


/*
   PutIndice - places, a, into the dynamic array at position i[n]
*/

void Indexing_PutIndice (Indexing_Index i, unsigned int n, void * a)
{
  unsigned int oldSize;
  void * b;
  unsigned int * * p;

  if (! (Indexing_InBounds (i, n)))
    {
      /* avoid gcc warning by using compound statement even if not strictly necessary.  */
      if (n < i->Low)
        {
          M2RTS_HALT (-1);
          __builtin_unreachable ();
        }
      else
        {
          oldSize = i->ArraySize;
          while (((n-i->Low)*sizeof (void *)) >= i->ArraySize)
            {
              i->ArraySize = i->ArraySize*2;
            }
          if (oldSize != i->ArraySize)
            {
              /* 
               IF Debug
               THEN
                  printf2('increasing memory hunk from %d to %d
              ',
                          oldSize, ArraySize)
               END ;
  */
              Storage_REALLOCATE (&i->ArrayStart, i->ArraySize);
              /* and initialize the remainder of the array to NIL  */
              b = i->ArrayStart;
              b += oldSize;
              b = libc_memset (b, 0, (size_t) i->ArraySize-oldSize);
            }
          i->High = n;
        }
    }
  b = i->ArrayStart;
  b += (n-i->Low)*sizeof (void *);
  p = b;
  (*p) = a;
  i->Used += 1;
  if (i->Debug)
    {
      if (n < 32)
        {
          i->Map |= (1 << (n ));
        }
    }
}


/*
   GetIndice - retrieves, element i[n] from the dynamic array.
*/

void * Indexing_GetIndice (Indexing_Index i, unsigned int n)
{
  PtrToByte b;
  PtrToAddress p;

  if (! (Indexing_InBounds (i, n)))
    {
      M2RTS_HALT (-1);
      __builtin_unreachable ();
    }
  b = i->ArrayStart;
  b += (n-i->Low)*sizeof (void *);
  p = (PtrToAddress) (b);
  if (i->Debug)
    {
      if (((n < 32) && (! ((((1 << (n)) & (i->Map)) != 0)))) && ((*p) != NULL))
        {
          M2RTS_HALT (-1);
          __builtin_unreachable ();
        }
    }
  return (*p);
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   IsIndiceInIndex - returns TRUE if, a, is in the index, i.
*/

unsigned int Indexing_IsIndiceInIndex (Indexing_Index i, void * a)
{
  unsigned int j;
  PtrToByte b;
  PtrToAddress p;

  j = i->Low;
  b = i->ArrayStart;
  while (j <= i->High)
    {
      p = (PtrToAddress) (b);
      if ((*p) == a)
        {
          return TRUE;
        }
      /* we must not INC(p, ..) as p2c gets confused  */
      b += sizeof (void *);
      j += 1;
    }
  return FALSE;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   RemoveIndiceFromIndex - removes, a, from Index, i.
*/

void Indexing_RemoveIndiceFromIndex (Indexing_Index i, void * a)
{
  unsigned int j;
  unsigned int k;
  PtrToAddress p;
  PtrToByte b;

  j = i->Low;
  b = i->ArrayStart;
  while (j <= i->High)
    {
      p = (PtrToAddress) (b);
      b += sizeof (void *);
      if ((*p) == a)
        {
          Indexing_DeleteIndice (i, j);
        }
      j += 1;
    }
}


/*
   DeleteIndice - delete i[j] from the array.
*/

void Indexing_DeleteIndice (Indexing_Index i, unsigned int j)
{
  PtrToAddress p;
  PtrToByte b;

  if (Indexing_InBounds (i, j))
    {
      b = i->ArrayStart;
      b += sizeof (void *)*(j-i->Low);
      p = (PtrToAddress) (b);
      b += sizeof (void *);
      p = libc_memmove ((void *) p, (void *) b, (size_t) (i->High-j)*sizeof (void *));
      i->High -= 1;
      i->Used -= 1;
    }
  else
    {
      M2RTS_HALT (-1);
      __builtin_unreachable ();
    }
}


/*
   IncludeIndiceIntoIndex - if the indice is not in the index, then
                            add it at the end.
*/

void Indexing_IncludeIndiceIntoIndex (Indexing_Index i, void * a)
{
  if (! (Indexing_IsIndiceInIndex (i, a)))
    {
      /* avoid gcc warning by using compound statement even if not strictly necessary.  */
      if (i->Used == 0)
        {
          Indexing_PutIndice (i, Indexing_LowIndice (i), a);
        }
      else
        {
          Indexing_PutIndice (i, (Indexing_HighIndice (i))+1, a);
        }
    }
}


/*
   ForeachIndiceInIndexDo - for each j indice of i, call procedure p(i[j])
*/

void Indexing_ForeachIndiceInIndexDo (Indexing_Index i, Indexing_IndexProcedure p)
{
  unsigned int j;

  j = Indexing_LowIndice (i);
  while (j <= (Indexing_HighIndice (i)))
    {
      (*p.proc) (Indexing_GetIndice (i, j));
      j += 1;
    }
}

void _M2_Indexing_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_Indexing_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
