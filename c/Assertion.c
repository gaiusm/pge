/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/Assertion.mod.  */

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
