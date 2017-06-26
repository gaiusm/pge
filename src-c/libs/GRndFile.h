/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RndFile.def.  */


#if !defined (_RndFile_H)
#   define _RndFile_H

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

#   if defined (_RndFile_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define RndFile_read (RndFile_FlagSet) ((1 << (ChanConsts_readFlag-ChanConsts_readFlag)))
#   define RndFile_write (RndFile_FlagSet) ((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)))
#   define RndFile_old (RndFile_FlagSet) ((1 << (ChanConsts_oldFlag-ChanConsts_readFlag)))
#   define RndFile_text (RndFile_FlagSet) ((1 << (ChanConsts_textFlag-ChanConsts_readFlag)))
#   define RndFile_raw (RndFile_FlagSet) ((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)))
#   define RndFile_FilePosSize (sizeof (long int))
typedef IOChan_ChanId RndFile_ChanId;

typedef ChanConsts_FlagSet RndFile_FlagSet;

typedef ChanConsts_OpenResults RndFile_OpenResults;

typedef long int RndFile_FilePos;

EXTERN void RndFile_OpenOld (RndFile_ChanId *cid, char *name_, unsigned int _name_high, RndFile_FlagSet flags, RndFile_OpenResults *res);
EXTERN void RndFile_OpenClean (RndFile_ChanId *cid, char *name_, unsigned int _name_high, RndFile_FlagSet flags, RndFile_OpenResults *res);
EXTERN unsigned int RndFile_IsRndFile (RndFile_ChanId cid);
EXTERN unsigned int RndFile_IsRndFileException (void);
EXTERN RndFile_FilePos RndFile_StartPos (RndFile_ChanId cid);
EXTERN RndFile_FilePos RndFile_CurrentPos (RndFile_ChanId cid);
EXTERN RndFile_FilePos RndFile_EndPos (RndFile_ChanId cid);
EXTERN RndFile_FilePos RndFile_NewPos (RndFile_ChanId cid, int chunks, unsigned int chunkSize, RndFile_FilePos from);
EXTERN void RndFile_SetPos (RndFile_ChanId cid, RndFile_FilePos pos);
EXTERN void RndFile_Close (RndFile_ChanId *cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
