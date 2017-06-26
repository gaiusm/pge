/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/SArgs.def.  */


#if !defined (_SArgs_H)
#   define _SArgs_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GDynamicStrings.h"

#   if defined (_SArgs_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   GetArg - returns the nth argument from the command line.
            The success of the operation is returned.
            If TRUE is returned then the string, s, contains a
            new string, otherwise s is set to NIL.
*/

EXTERN unsigned int SArgs_GetArg (DynamicStrings_String *s, unsigned int i);

/*
   Narg - returns the number of arguments available from
          command line.
*/

EXTERN unsigned int SArgs_Narg (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
