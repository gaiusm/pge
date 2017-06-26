/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/SEnvironment.def.  */


#if !defined (_SEnvironment_H)
#   define _SEnvironment_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GDynamicStrings.h"

#   if defined (_SEnvironment_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   GetEnvironment - gets the environment variable, env, and places
      	       	    a copy of its value into String, s.
                    TRUE is returned if successful.
*/

EXTERN unsigned int SEnvironment_GetEnvironment (DynamicStrings_String env, DynamicStrings_String *s);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
