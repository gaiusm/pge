/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RTio.def.  */


#if !defined (_RTio_H)
#   define _RTio_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GFIO.h"
#   include "GIOLink.h"

#   if defined (_RTio_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (RTio_ChanId_D)
#  define RTio_ChanId_D
   typedef void *RTio_ChanId;
#endif


/*
   InitChanId - return a new ChanId.
*/

EXTERN RTio_ChanId RTio_InitChanId (void);

/*
   KillChanId - deallocate a ChanId.
*/

EXTERN RTio_ChanId RTio_KillChanId (RTio_ChanId c);

/*
   NilChanId - return a NIL pointer.
*/

EXTERN RTio_ChanId RTio_NilChanId (void);

/*
   GetDeviceId - returns the device id, from, c.
*/

EXTERN IOLink_DeviceId RTio_GetDeviceId (RTio_ChanId c);

/*
   SetDeviceId - sets the device id in, c.
*/

EXTERN void RTio_SetDeviceId (RTio_ChanId c, IOLink_DeviceId d);

/*
   GetDevicePtr - returns the device table ptr, from, c.
*/

EXTERN IOLink_DeviceTablePtr RTio_GetDevicePtr (RTio_ChanId c);

/*
   SetDevicePtr - sets the device table ptr in, c.
*/

EXTERN void RTio_SetDevicePtr (RTio_ChanId c, IOLink_DeviceTablePtr p);

/*
   GetFile - returns the file field from, c.
*/

EXTERN FIO_File RTio_GetFile (RTio_ChanId c);

/*
   SetFile - sets the file field in, c.
*/

EXTERN void RTio_SetFile (RTio_ChanId c, FIO_File f);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
