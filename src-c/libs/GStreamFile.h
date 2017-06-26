/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/StreamFile.def.  */


#if !defined (_StreamFile_H)
#   define _StreamFile_H

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

#   if defined (_StreamFile_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define StreamFile_read (StreamFile_FlagSet) ((1 << (ChanConsts_readFlag-ChanConsts_readFlag)))
#   define StreamFile_write (StreamFile_FlagSet) ((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)))
#   define StreamFile_old (StreamFile_FlagSet) ((1 << (ChanConsts_oldFlag-ChanConsts_readFlag)))
#   define StreamFile_text (StreamFile_FlagSet) ((1 << (ChanConsts_textFlag-ChanConsts_readFlag)))
#   define StreamFile_raw (StreamFile_FlagSet) ((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)))
typedef IOChan_ChanId StreamFile_ChanId;

typedef ChanConsts_FlagSet StreamFile_FlagSet;

typedef ChanConsts_OpenResults StreamFile_OpenResults;

EXTERN void StreamFile_Open (StreamFile_ChanId *cid, char *name_, unsigned int _name_high, StreamFile_FlagSet flags, StreamFile_OpenResults *res);
EXTERN unsigned int StreamFile_IsStreamFile (StreamFile_ChanId cid);
EXTERN void StreamFile_Close (StreamFile_ChanId *cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
