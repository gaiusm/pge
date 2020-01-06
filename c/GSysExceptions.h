

#if !defined (_SysExceptions_H)
#   define _SysExceptions_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_SysExceptions_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct SysExceptions_PROCEXCEPTION_p SysExceptions_PROCEXCEPTION;

typedef void (*SysExceptions_PROCEXCEPTION_t) (void *);
struct SysExceptions_PROCEXCEPTION_p { SysExceptions_PROCEXCEPTION_t proc; };

EXTERN void SysExceptions_InitExceptionHandlers (SysExceptions_PROCEXCEPTION indexf, SysExceptions_PROCEXCEPTION range, SysExceptions_PROCEXCEPTION casef, SysExceptions_PROCEXCEPTION invalidloc, SysExceptions_PROCEXCEPTION function, SysExceptions_PROCEXCEPTION wholevalue, SysExceptions_PROCEXCEPTION wholediv, SysExceptions_PROCEXCEPTION realvalue, SysExceptions_PROCEXCEPTION realdiv, SysExceptions_PROCEXCEPTION complexvalue, SysExceptions_PROCEXCEPTION complexdiv, SysExceptions_PROCEXCEPTION protection, SysExceptions_PROCEXCEPTION systemf, SysExceptions_PROCEXCEPTION coroutine, SysExceptions_PROCEXCEPTION exception);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
