/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/ProgramArgs.def.  */


#if !defined (_ProgramArgs_H)
#   define _ProgramArgs_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_ProgramArgs_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef IOChan_ChanId ProgramArgs_ChanId;

EXTERN ProgramArgs_ChanId ProgramArgs_ArgChan (void);
EXTERN unsigned int ProgramArgs_IsArgPresent (void);
EXTERN void ProgramArgs_NextArg (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
