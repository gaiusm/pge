/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RTgen.def.  */


#if !defined (_RTgen_H)
#   define _RTgen_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GRTgenif.h"
#   include "GIOLink.h"
#   include "GIOConsts.h"
#   include "GSYSTEM.h"

#   if defined (_RTgen_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (RTgen_ChanDev_D)
#  define RTgen_ChanDev_D
   typedef void *RTgen_ChanDev;
#endif

typedef enum {RTgen_seqfile, RTgen_streamfile, RTgen_programargs, RTgen_stdchans, RTgen_term, RTgen_socket, RTgen_rndfile} RTgen_DeviceType;


/*
   InitChanDev - initialize and return a ChanDev.
*/

EXTERN RTgen_ChanDev RTgen_InitChanDev (RTgen_DeviceType t, IOLink_DeviceId d, RTgenif_GenDevIF g);

/*
   KillChanDev - deallocates, g.
*/

EXTERN RTgenif_GenDevIF RTgen_KillChanDev (RTgenif_GenDevIF g);

/*
   RaiseEOFinLook - returns TRUE if the Look procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN unsigned int RTgen_RaiseEOFinLook (RTgen_ChanDev g);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN unsigned int RTgen_RaiseEOFinSkip (RTgen_ChanDev g);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN void RTgen_doLook (RTgen_ChanDev g, IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN void RTgen_doSkip (RTgen_ChanDev g, IOLink_DeviceTablePtr d);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN void RTgen_doSkipLook (RTgen_ChanDev g, IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN void RTgen_doWriteLn (RTgen_ChanDev g, IOLink_DeviceTablePtr d);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN void RTgen_doReadText (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * to, unsigned int maxChars, unsigned int *charsRead);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN void RTgen_doWriteText (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * from, unsigned int charsToWrite);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN void RTgen_doReadLocs (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * to, unsigned int maxLocs, unsigned int *locsRead);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

EXTERN void RTgen_doWriteLocs (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * from, unsigned int locsToWrite);

/*
   checkErrno - checks a number of errno conditions and raises
                appropriate ISO exceptions if they occur.
*/

EXTERN void RTgen_checkErrno (RTgen_ChanDev g, IOLink_DeviceTablePtr d);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
