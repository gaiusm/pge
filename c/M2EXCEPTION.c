/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/M2EXCEPTION.mod.  */

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
    RTExceptions_Raise ((unsigned int) (M2EXCEPTION_exException), "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/M2EXCEPTION.mod", 36, 25, "M2Exception", "current coroutine is not in the exceptional execution state");
  ReturnException ("", 0, 0);
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
