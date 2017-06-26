/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/StdChans.def.  */


#if !defined (_StdChans_H)
#   define _StdChans_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_StdChans_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef IOChan_ChanId StdChans_ChanId;

EXTERN StdChans_ChanId StdChans_StdInChan (void);
EXTERN StdChans_ChanId StdChans_StdOutChan (void);
EXTERN StdChans_ChanId StdChans_StdErrChan (void);
EXTERN StdChans_ChanId StdChans_NullChan (void);
EXTERN StdChans_ChanId StdChans_InChan (void);
EXTERN StdChans_ChanId StdChans_OutChan (void);
EXTERN StdChans_ChanId StdChans_ErrChan (void);
EXTERN void StdChans_SetInChan (StdChans_ChanId cid);
EXTERN void StdChans_SetOutChan (StdChans_ChanId cid);
EXTERN void StdChans_SetErrChan (StdChans_ChanId cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
