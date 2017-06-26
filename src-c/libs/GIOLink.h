/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/IOLink.def.  */


#if !defined (_IOLink_H)
#   define _IOLink_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"
#   include "GIOConsts.h"
#   include "GChanConsts.h"
#   include "GSYSTEM.h"

#   if defined (_IOLink_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (IOLink_DeviceId_D)
#  define IOLink_DeviceId_D
   typedef void *IOLink_DeviceId;
#endif

typedef struct IOLink_LookProc_p IOLink_LookProc;

typedef struct IOLink_SkipProc_p IOLink_SkipProc;

typedef struct IOLink_SkipLookProc_p IOLink_SkipLookProc;

typedef struct IOLink_WriteLnProc_p IOLink_WriteLnProc;

typedef struct IOLink_TextReadProc_p IOLink_TextReadProc;

typedef struct IOLink_TextWriteProc_p IOLink_TextWriteProc;

typedef struct IOLink_RawReadProc_p IOLink_RawReadProc;

typedef struct IOLink_RawWriteProc_p IOLink_RawWriteProc;

typedef struct IOLink_GetNameProc_p IOLink_GetNameProc;

typedef struct IOLink_ResetProc_p IOLink_ResetProc;

typedef struct IOLink_FlushProc_p IOLink_FlushProc;

typedef struct IOLink_FreeProc_p IOLink_FreeProc;

typedef void *IOLink_DeviceData;

typedef struct IOLink_DeviceTable_r IOLink_DeviceTable;

typedef IOLink_DeviceTable *IOLink_DeviceTablePtr;

typedef IOChan_ChanExceptions IOLink_DevExceptionRange;

typedef void (*IOLink_LookProc_t) (IOLink_DeviceTablePtr, char *, IOConsts_ReadResults *);
struct IOLink_LookProc_p { IOLink_LookProc_t proc; };

typedef void (*IOLink_SkipProc_t) (IOLink_DeviceTablePtr);
struct IOLink_SkipProc_p { IOLink_SkipProc_t proc; };

typedef void (*IOLink_SkipLookProc_t) (IOLink_DeviceTablePtr, char *, IOConsts_ReadResults *);
struct IOLink_SkipLookProc_p { IOLink_SkipLookProc_t proc; };

typedef void (*IOLink_WriteLnProc_t) (IOLink_DeviceTablePtr);
struct IOLink_WriteLnProc_p { IOLink_WriteLnProc_t proc; };

typedef void (*IOLink_TextReadProc_t) (IOLink_DeviceTablePtr, void *, unsigned int, unsigned int *);
struct IOLink_TextReadProc_p { IOLink_TextReadProc_t proc; };

typedef void (*IOLink_TextWriteProc_t) (IOLink_DeviceTablePtr, void *, unsigned int);
struct IOLink_TextWriteProc_p { IOLink_TextWriteProc_t proc; };

typedef void (*IOLink_RawReadProc_t) (IOLink_DeviceTablePtr, void *, unsigned int, unsigned int *);
struct IOLink_RawReadProc_p { IOLink_RawReadProc_t proc; };

typedef void (*IOLink_RawWriteProc_t) (IOLink_DeviceTablePtr, void *, unsigned int);
struct IOLink_RawWriteProc_p { IOLink_RawWriteProc_t proc; };

typedef void (*IOLink_GetNameProc_t) (IOLink_DeviceTablePtr, char *, unsigned int);
struct IOLink_GetNameProc_p { IOLink_GetNameProc_t proc; };

typedef void (*IOLink_ResetProc_t) (IOLink_DeviceTablePtr);
struct IOLink_ResetProc_p { IOLink_ResetProc_t proc; };

typedef void (*IOLink_FlushProc_t) (IOLink_DeviceTablePtr);
struct IOLink_FlushProc_p { IOLink_FlushProc_t proc; };

typedef void (*IOLink_FreeProc_t) (IOLink_DeviceTablePtr);
struct IOLink_FreeProc_p { IOLink_FreeProc_t proc; };

struct IOLink_DeviceTable_r {
                              IOLink_DeviceData cd;
                              IOLink_DeviceId did;
                              IOChan_ChanId cid;
                              IOConsts_ReadResults result;
                              IOChan_DeviceErrNum errNum;
                              ChanConsts_FlagSet flags;
                              IOLink_LookProc doLook;
                              IOLink_SkipProc doSkip;
                              IOLink_SkipLookProc doSkipLook;
                              IOLink_WriteLnProc doLnWrite;
                              IOLink_TextReadProc doTextRead;
                              IOLink_TextWriteProc doTextWrite;
                              IOLink_RawReadProc doRawRead;
                              IOLink_RawWriteProc doRawWrite;
                              IOLink_GetNameProc doGetName;
                              IOLink_ResetProc doReset;
                              IOLink_FlushProc doFlush;
                              IOLink_FreeProc doFree;
                            };

EXTERN void IOLink_AllocateDeviceId (IOLink_DeviceId *did);
EXTERN void IOLink_MakeChan (IOLink_DeviceId did, IOChan_ChanId *cid);
EXTERN void IOLink_UnMakeChan (IOLink_DeviceId did, IOChan_ChanId *cid);
EXTERN IOLink_DeviceTablePtr IOLink_DeviceTablePtrValue (IOChan_ChanId cid, IOLink_DeviceId did);
EXTERN unsigned int IOLink_IsDevice (IOChan_ChanId cid, IOLink_DeviceId did);
EXTERN void IOLink_RAISEdevException (IOChan_ChanId cid, IOLink_DeviceId did, IOLink_DevExceptionRange x, char *s_, unsigned int _s_high);
EXTERN unsigned int IOLink_IsIOException (void);
EXTERN IOChan_ChanExceptions IOLink_IOException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
