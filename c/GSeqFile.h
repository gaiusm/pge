/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/SeqFile.def.  */


#if !defined (_SeqFile_H)
#   define _SeqFile_H

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

#   if defined (_SeqFile_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define SeqFile_read (SeqFile_FlagSet) ((1 << (ChanConsts_readFlag-ChanConsts_readFlag)))
#   define SeqFile_write (SeqFile_FlagSet) ((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)))
#   define SeqFile_old (SeqFile_FlagSet) ((1 << (ChanConsts_oldFlag-ChanConsts_readFlag)))
#   define SeqFile_text (SeqFile_FlagSet) ((1 << (ChanConsts_textFlag-ChanConsts_readFlag)))
#   define SeqFile_raw (SeqFile_FlagSet) ((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)))
typedef IOChan_ChanId SeqFile_ChanId;

typedef ChanConsts_FlagSet SeqFile_FlagSet;

typedef ChanConsts_OpenResults SeqFile_OpenResults;

EXTERN void SeqFile_OpenWrite (SeqFile_ChanId *cid, char *name_, unsigned int _name_high, SeqFile_FlagSet flags, SeqFile_OpenResults *res);
EXTERN void SeqFile_OpenAppend (SeqFile_ChanId *cid, char *name_, unsigned int _name_high, SeqFile_FlagSet flags, SeqFile_OpenResults *res);
EXTERN void SeqFile_OpenRead (SeqFile_ChanId *cid, char *name_, unsigned int _name_high, SeqFile_FlagSet flags, SeqFile_OpenResults *res);
EXTERN unsigned int SeqFile_IsSeqFile (SeqFile_ChanId cid);
EXTERN void SeqFile_Reread (SeqFile_ChanId cid);
EXTERN void SeqFile_Rewrite (SeqFile_ChanId cid);
EXTERN void SeqFile_Close (SeqFile_ChanId *cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
