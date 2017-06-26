/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/SCmdArgs.def.  */


#if !defined (_SCmdArgs_H)
#   define _SCmdArgs_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GDynamicStrings.h"

#   if defined (_SCmdArgs_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   GetArg - returns the nth argument from the command line, CmdLine
            the success of the operation is returned.
*/

EXTERN unsigned int SCmdArgs_GetArg (DynamicStrings_String CmdLine, unsigned int n, DynamicStrings_String *Argi);

/*
   Narg - returns the number of arguments available from
          command line, CmdLine.
*/

EXTERN unsigned int SCmdArgs_Narg (DynamicStrings_String CmdLine);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
