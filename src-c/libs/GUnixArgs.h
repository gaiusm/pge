/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/UnixArgs.def.  */


#if !defined (_UnixArgs_H)
#   define _UnixArgs_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_UnixArgs_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN unsigned int UnixArgs_ArgC;
EXTERN void * UnixArgs_ArgV;
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
