/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/ChanConsts.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _ChanConsts_H
#define _ChanConsts_C


typedef enum {ChanConsts_readFlag, ChanConsts_writeFlag, ChanConsts_oldFlag, ChanConsts_textFlag, ChanConsts_rawFlag, ChanConsts_interactiveFlag, ChanConsts_echoFlag} ChanConsts_ChanFlags;

typedef enum {ChanConsts_opened, ChanConsts_wrongNameFormat, ChanConsts_wrongFlags, ChanConsts_tooManyOpen, ChanConsts_outOfChans, ChanConsts_wrongPermissions, ChanConsts_noRoomOnDevice, ChanConsts_noSuchFile, ChanConsts_fileExists, ChanConsts_wrongFileType, ChanConsts_noTextOperations, ChanConsts_noRawOperations, ChanConsts_noMixedOperations, ChanConsts_alreadyOpen, ChanConsts_otherProblem} ChanConsts_OpenResults;

#   define ChanConsts_read (ChanConsts_FlagSet) ((1 << (ChanConsts_readFlag-ChanConsts_readFlag)))
#   define ChanConsts_write (ChanConsts_FlagSet) ((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)))
#   define ChanConsts_old (ChanConsts_FlagSet) ((1 << (ChanConsts_oldFlag-ChanConsts_readFlag)))
#   define ChanConsts_text (ChanConsts_FlagSet) ((1 << (ChanConsts_textFlag-ChanConsts_readFlag)))
#   define ChanConsts_raw (ChanConsts_FlagSet) ((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)))
#   define ChanConsts_interactive (ChanConsts_FlagSet) ((1 << (ChanConsts_interactiveFlag-ChanConsts_readFlag)))
#   define ChanConsts_echo (ChanConsts_FlagSet) ((1 << (ChanConsts_echoFlag-ChanConsts_readFlag)))
typedef unsigned int ChanConsts_FlagSet;


void _M2_ChanConsts_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_ChanConsts_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
