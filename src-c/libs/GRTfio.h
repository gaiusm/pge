/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RTfio.def.  */


#if !defined (_RTfio_H)
#   define _RTfio_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"
#   include "GIOLink.h"
#   include "GRTgenif.h"

#   if defined (_RTfio_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   doreadchar - returns a CHAR from the file associated with, g.
*/

EXTERN char RTfio_doreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   dounreadchar - pushes a CHAR back onto the file associated
                  with, g.
*/

EXTERN char RTfio_dounreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, char ch);

/*
   dogeterrno - returns the errno relating to the generic device.
*/

EXTERN int RTfio_dogeterrno (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   dorbytes - reads upto, max, bytes setting, actual, and
              returning FALSE if an error (not due to eof)
              occurred.
*/

EXTERN unsigned int RTfio_dorbytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * to, unsigned int max, unsigned int *actual);

/*
   dowbytes - writes up to, nBytes.  It returns FALSE
              if an error occurred and it sets actual
              to the amount of data written.
*/

EXTERN unsigned int RTfio_dowbytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * from, unsigned int nBytes, unsigned int *actual);

/*
   dowriteln - attempt to write an end of line marker to the
               file and returns TRUE if successful.
*/

EXTERN unsigned int RTfio_dowriteln (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   iseof - returns TRUE if end of file has been seen.
*/

EXTERN unsigned int RTfio_iseof (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   iseoln - returns TRUE if end of line has been seen.
*/

EXTERN unsigned int RTfio_iseoln (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   iserror - returns TRUE if an error was seen on the device.
             Note that reaching EOF is not classified as an
             error.
*/

EXTERN unsigned int RTfio_iserror (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
