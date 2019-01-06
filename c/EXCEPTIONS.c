/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/EXCEPTIONS.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <stddef.h>
#include <string.h>
#include <limits.h>
#   include "GStorage.h"
#   include "Gmcrts.h"
#define _EXCEPTIONS_H
#define _EXCEPTIONS_C

#   include "GRTExceptions.h"
#   include "GM2EXCEPTION.h"
#   include "GM2RTS.h"
#   include "GASCII.h"
#   include "GSYSTEM.h"
#   include "GStorage.h"

typedef unsigned int EXCEPTIONS_ExceptionNumber;

typedef struct _T1_r _T1;

typedef _T1 *EXCEPTIONS_ExceptionSource;

struct _T1_r {
               RTExceptions_EHBlock eh;
             };

void EXCEPTIONS_AllocateSource (EXCEPTIONS_ExceptionSource *newSource);
void EXCEPTIONS_RAISE (EXCEPTIONS_ExceptionSource source, EXCEPTIONS_ExceptionNumber number, char *message_, unsigned int _message_high);
EXCEPTIONS_ExceptionNumber EXCEPTIONS_CurrentNumber (EXCEPTIONS_ExceptionSource source);
void EXCEPTIONS_GetMessage (char *text, unsigned int _text_high);
unsigned int EXCEPTIONS_IsCurrentSource (EXCEPTIONS_ExceptionSource source);
unsigned int EXCEPTIONS_IsExceptionalExecution (void);

void EXCEPTIONS_AllocateSource (EXCEPTIONS_ExceptionSource *newSource)
{
  /* Allocates a unique value of type ExceptionSource  */
  Storage_ALLOCATE ((void **) &(*newSource), sizeof (_T1));
  (*newSource)->eh = RTExceptions_InitExceptionBlock ();
}

void EXCEPTIONS_RAISE (EXCEPTIONS_ExceptionSource source, EXCEPTIONS_ExceptionNumber number, char *message_, unsigned int _message_high)
{
  char message[_message_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (message, message_, _message_high+1);

  /* Associates the given values of source, number and message with
     the current context and raises an exception.
  */
  RTExceptions_SetExceptionSource ((void *) source);
  RTExceptions_SetExceptionBlock (source->eh);
  RTExceptions_Raise ((unsigned int) number, "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/EXCEPTIONS.mod", 57, 3, "RAISE", &message);
  /* we should never reach here as Raise should jump to the exception handler  */
  M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/EXCEPTIONS.mod", 73, 59, (char *) "RAISE", 5, (char *) "should never return from RTException.Raise", 42);
}

EXCEPTIONS_ExceptionNumber EXCEPTIONS_CurrentNumber (EXCEPTIONS_ExceptionSource source)
{
  /* If the current coroutine is in the exceptional execution state
     because of the raising of an exception from source, returns the
     corresponding number, and otherwise raises an exception.
  */
  if (RTExceptions_IsInExceptionState ())
    return RTExceptions_GetNumber (source->eh);
  else
    RTExceptions_Raise ((unsigned int) (M2EXCEPTION_coException), "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/EXCEPTIONS.mod", 74, 25, "CurrentNumber", "current coroutine is not in the exceptional execution state");
  ReturnException ("/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/EXCEPTIONS.def", 8, 1);
}

void EXCEPTIONS_GetMessage (char *text, unsigned int _text_high)
{
  unsigned int i;
  unsigned int h;
  char * p;

  /* If the current coroutine is in the exceptional execution state,
     returns the possibly truncated string associated with the
     current context.  Otherwise, in normal execution state,
     returns the empty string.
  */
  if (RTExceptions_IsInExceptionState ())
    {
      h = _text_high;
      i = 0;
      p = RTExceptions_GetTextBuffer (RTExceptions_GetExceptionBlock ());
      while ((p != NULL) && ((*p) != ASCII_nul))
        {
          text[i] = (*p);
          i += 1;
          p += 1;
        }
      if (i <= h)
        text[i] = ASCII_nul;
    }
  else
    text[0] = ASCII_nul;
}

unsigned int EXCEPTIONS_IsCurrentSource (EXCEPTIONS_ExceptionSource source)
{
  /* If the current coroutine is in the exceptional execution state
     because of the raising of an exception from source, returns TRUE,
     and otherwise returns FALSE.
  */
  return (RTExceptions_IsInExceptionState ()) && (source == (RTExceptions_GetExceptionSource ()));
}

unsigned int EXCEPTIONS_IsExceptionalExecution (void)
{
  /* If the current coroutine is in the exceptional execution state
     because of the raising of an exception, returns TRUE,
     and otherwise returns FALSE.
  */
  return RTExceptions_IsInExceptionState ();
}

void _M2_EXCEPTIONS_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_EXCEPTIONS_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
