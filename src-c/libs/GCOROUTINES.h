/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.def.  */


#if !defined (_COROUTINES_H)
#   define _COROUTINES_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_COROUTINES_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define COROUTINES_UnassignedPriority 0
#if !defined (COROUTINES_COROUTINE_D)
#  define COROUTINES_COROUTINE_D
   typedef void *COROUTINES_COROUTINE;
#endif

typedef unsigned int COROUTINES_INTERRUPTSOURCE;

typedef unsigned int COROUTINES_PROTECTION;

EXTERN void COROUTINES_NEWCOROUTINE (PROC procBody, void * workspace, unsigned int size, COROUTINES_COROUTINE *cr, COROUTINES_PROTECTION initProtection);
EXTERN void COROUTINES_TRANSFER (COROUTINES_COROUTINE *from, COROUTINES_COROUTINE to);
EXTERN void COROUTINES_IOTRANSFER (COROUTINES_COROUTINE *from, COROUTINES_COROUTINE to);
EXTERN void COROUTINES_ATTACH (COROUTINES_INTERRUPTSOURCE source);
EXTERN void COROUTINES_DETACH (COROUTINES_INTERRUPTSOURCE source);
EXTERN unsigned int COROUTINES_IsATTACHED (COROUTINES_INTERRUPTSOURCE source);
EXTERN COROUTINES_COROUTINE COROUTINES_HANDLER (COROUTINES_INTERRUPTSOURCE source);
EXTERN COROUTINES_COROUTINE COROUTINES_CURRENT (void);
EXTERN void COROUTINES_LISTEN (COROUTINES_PROTECTION p);
EXTERN COROUTINES_PROTECTION COROUTINES_PROT (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
