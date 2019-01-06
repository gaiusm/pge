/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/RTgenif.def.  */


#if !defined (_RTgenif_H)
#   define _RTgenif_H

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

#   if defined (_RTgenif_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (RTgenif_GenDevIF_D)
#  define RTgenif_GenDevIF_D
   typedef void *RTgenif_GenDevIF;
#endif

typedef struct RTgenif_readchar_p RTgenif_readchar;

typedef struct RTgenif_unreadchar_p RTgenif_unreadchar;

typedef struct RTgenif_geterrno_p RTgenif_geterrno;

typedef struct RTgenif_readbytes_p RTgenif_readbytes;

typedef struct RTgenif_writebytes_p RTgenif_writebytes;

typedef struct RTgenif_writeln_p RTgenif_writeln;

typedef struct RTgenif_iseof_p RTgenif_iseof;

typedef struct RTgenif_iseoln_p RTgenif_iseoln;

typedef struct RTgenif_iserror_p RTgenif_iserror;

typedef char (*RTgenif_readchar_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr);
struct RTgenif_readchar_p { RTgenif_readchar_t proc; };

typedef char (*RTgenif_unreadchar_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr, char);
struct RTgenif_unreadchar_p { RTgenif_unreadchar_t proc; };

typedef int (*RTgenif_geterrno_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr);
struct RTgenif_geterrno_p { RTgenif_geterrno_t proc; };

typedef unsigned int (*RTgenif_readbytes_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr, void *, unsigned int, unsigned int *);
struct RTgenif_readbytes_p { RTgenif_readbytes_t proc; };

typedef unsigned int (*RTgenif_writebytes_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr, void *, unsigned int, unsigned int *);
struct RTgenif_writebytes_p { RTgenif_writebytes_t proc; };

typedef unsigned int (*RTgenif_writeln_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr);
struct RTgenif_writeln_p { RTgenif_writeln_t proc; };

typedef unsigned int (*RTgenif_iseof_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr);
struct RTgenif_iseof_p { RTgenif_iseof_t proc; };

typedef unsigned int (*RTgenif_iseoln_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr);
struct RTgenif_iseoln_p { RTgenif_iseoln_t proc; };

typedef unsigned int (*RTgenif_iserror_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr);
struct RTgenif_iserror_p { RTgenif_iserror_t proc; };


/*
   InitGenDevIF - initializes a generic device.
*/

EXTERN RTgenif_GenDevIF RTgenif_InitGenDevIF (IOLink_DeviceId d, RTgenif_readchar rc, RTgenif_unreadchar urc, RTgenif_geterrno geterr, RTgenif_readbytes rbytes, RTgenif_writebytes wbytes, RTgenif_writeln wl, RTgenif_iseof eof, RTgenif_iseoln eoln, RTgenif_iserror iserr);

/*
   getDID - returns the device id this generic interface.
*/

EXTERN IOLink_DeviceId RTgenif_getDID (RTgenif_GenDevIF g);

/*
   doReadChar - returns the next character from the generic
                device.
*/

EXTERN char RTgenif_doReadChar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   doUnReadChar - pushes back a character to the generic device.
*/

EXTERN char RTgenif_doUnReadChar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, char ch);

/*
   doGetErrno - returns the errno relating to the generic device.
*/

EXTERN int RTgenif_doGetErrno (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   doRBytes - attempts to read, n, bytes from the generic device.
              It set the actual amount read and returns a boolean
              to determine whether an error occurred.
*/

EXTERN unsigned int RTgenif_doRBytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * to, unsigned int max, unsigned int *actual);

/*
   doWBytes - attempts to write, n, bytes to the generic device.
              It sets the actual amount written and returns a
              boolean to determine whether an error occurred.
*/

EXTERN unsigned int RTgenif_doWBytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * from, unsigned int max, unsigned int *actual);

/*
   doWrLn - writes an end of line marker and returns
            TRUE if successful.
*/

EXTERN unsigned int RTgenif_doWrLn (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   isEOF - returns true if the end of file was reached.
*/

EXTERN unsigned int RTgenif_isEOF (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   isEOLN - returns true if the end of line was reached.
*/

EXTERN unsigned int RTgenif_isEOLN (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   isError - returns true if an error was seen in the device.
*/

EXTERN unsigned int RTgenif_isError (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   KillGenDevIF - deallocates a generic device.
*/

EXTERN RTgenif_GenDevIF RTgenif_KillGenDevIF (RTgenif_GenDevIF g);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
