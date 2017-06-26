/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/TermFile.def.  */


#if !defined (_TermFile_H)
#   define _TermFile_H

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

#   if defined (_TermFile_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define TermFile_read (TermFile_FlagSet) ((1 << (ChanConsts_readFlag-ChanConsts_readFlag)))
#   define TermFile_write (TermFile_FlagSet) ((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)))
#   define TermFile_text (TermFile_FlagSet) ((1 << (ChanConsts_textFlag-ChanConsts_readFlag)))
#   define TermFile_raw (TermFile_FlagSet) ((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)))
#   define TermFile_echo (TermFile_FlagSet) ((1 << (ChanConsts_echoFlag-ChanConsts_readFlag)))
typedef IOChan_ChanId TermFile_ChanId;

typedef ChanConsts_FlagSet TermFile_FlagSet;

typedef ChanConsts_OpenResults TermFile_OpenResults;

EXTERN void TermFile_Open (TermFile_ChanId *cid, TermFile_FlagSet flagset, TermFile_OpenResults *res);
EXTERN unsigned int TermFile_IsTermFile (TermFile_ChanId cid);
EXTERN void TermFile_Close (TermFile_ChanId *cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
