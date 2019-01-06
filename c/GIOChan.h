/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/IOChan.def.  */


#if !defined (_IOChan_H)
#   define _IOChan_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOConsts.h"
#   include "GChanConsts.h"
#   include "GSYSTEM.h"

#   if defined (_IOChan_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (IOChan_ChanId_D)
#  define IOChan_ChanId_D
   typedef void *IOChan_ChanId;
#endif

typedef int IOChan_DeviceErrNum;

typedef enum {IOChan_wrongDevice, IOChan_notAvailable, IOChan_skipAtEnd, IOChan_softDeviceError, IOChan_hardDeviceError, IOChan_textParseError, IOChan_notAChannel} IOChan_ChanExceptions;

EXTERN IOChan_ChanId IOChan_InvalidChan (void);
EXTERN void IOChan_Look (IOChan_ChanId cid, char *ch, IOConsts_ReadResults *res);
EXTERN void IOChan_Skip (IOChan_ChanId cid);
EXTERN void IOChan_SkipLook (IOChan_ChanId cid, char *ch, IOConsts_ReadResults *res);
EXTERN void IOChan_WriteLn (IOChan_ChanId cid);
EXTERN void IOChan_TextRead (IOChan_ChanId cid, void * to, unsigned int maxChars, unsigned int *charsRead);
EXTERN void IOChan_TextWrite (IOChan_ChanId cid, void * from, unsigned int charsToWrite);
EXTERN void IOChan_RawRead (IOChan_ChanId cid, void * to, unsigned int maxLocs, unsigned int *locsRead);
EXTERN void IOChan_RawWrite (IOChan_ChanId cid, void * from, unsigned int locsToWrite);
EXTERN void IOChan_GetName (IOChan_ChanId cid, char *s, unsigned int _s_high);
EXTERN void IOChan_Reset (IOChan_ChanId cid);
EXTERN void IOChan_Flush (IOChan_ChanId cid);
EXTERN void IOChan_SetReadResult (IOChan_ChanId cid, IOConsts_ReadResults res);
EXTERN IOConsts_ReadResults IOChan_ReadResult (IOChan_ChanId cid);
EXTERN ChanConsts_FlagSet IOChan_CurrentFlags (IOChan_ChanId cid);
EXTERN unsigned int IOChan_IsChanException (void);
EXTERN IOChan_ChanExceptions IOChan_ChanException (void);
EXTERN IOChan_DeviceErrNum IOChan_DeviceError (IOChan_ChanId cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
