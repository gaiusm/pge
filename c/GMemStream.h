/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/MemStream.def.  */


#if !defined (_MemStream_H)
#   define _MemStream_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"
#   include "GChanConsts.h"
#   include "GSYSTEM.h"

#   if defined (_MemStream_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void MemStream_OpenWrite (IOChan_ChanId *cid, ChanConsts_FlagSet flags, ChanConsts_OpenResults *res, void * *buffer, unsigned int *length, unsigned int *used, unsigned int deallocOnClose);
EXTERN void MemStream_OpenRead (IOChan_ChanId *cid, ChanConsts_FlagSet flags, ChanConsts_OpenResults *res, void * buffer, unsigned int length, unsigned int deallocOnClose);

/*
   Close - if the channel identified by cid is not open to
           a memory stream, the exception wrongDevice is
           raised; otherwise closes the channel, and assigns
           the value identifying the invalid channel to cid.
*/

EXTERN void MemStream_Close (IOChan_ChanId *cid);

/*
   Rewrite - assigns the buffer index to zero.  Subsequent
             writes will overwrite the previous buffer contents.
*/

EXTERN void MemStream_Rewrite (IOChan_ChanId cid);

/*
   Reread - assigns the buffer index to zero.  Subsequent
            reads will read the previous buffer contents.
*/

EXTERN void MemStream_Reread (IOChan_ChanId cid);

/*
   IsMem - tests if the channel identified by cid is open as
           a memory stream.
*/

EXTERN unsigned int MemStream_IsMem (IOChan_ChanId cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
