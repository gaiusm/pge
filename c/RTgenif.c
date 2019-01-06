/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/RTgenif.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <stddef.h>
#   include "GStorage.h"
#define _RTgenif_H
#define _RTgenif_C

#   include "GStorage.h"

typedef struct RTgenif_readchar_p RTgenif_readchar;

typedef struct RTgenif_unreadchar_p RTgenif_unreadchar;

typedef struct RTgenif_geterrno_p RTgenif_geterrno;

typedef struct RTgenif_readbytes_p RTgenif_readbytes;

typedef struct RTgenif_writebytes_p RTgenif_writebytes;

typedef struct RTgenif_writeln_p RTgenif_writeln;

typedef struct RTgenif_iseof_p RTgenif_iseof;

typedef struct RTgenif_iseoln_p RTgenif_iseoln;

typedef struct RTgenif_iserror_p RTgenif_iserror;

#if !defined (IOLink_DeviceId_D)
#  define IOLink_DeviceId_D
   typedef void *IOLink_DeviceId;
#endif

typedef struct _T1_r _T1;

typedef struct IOLink_DeviceTable_r IOLink_DeviceTable;

typedef IOLink_DeviceTable *IOLink_DeviceTablePtr;

typedef void *IOLink_DeviceData;

#if !defined (IOChan_ChanId_D)
#  define IOChan_ChanId_D
   typedef void *IOChan_ChanId;
#endif

typedef _T1 *RTgenif_GenDevIF;

typedef enum {IOConsts_notKnown, IOConsts_allRight, IOConsts_outOfRange, IOConsts_wrongFormat, IOConsts_endOfLine, IOConsts_endOfInput} IOConsts_ReadResults;

typedef int IOChan_DeviceErrNum;

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

typedef unsigned int ChanConsts_FlagSet;

typedef struct IOLink_LookProc_p IOLink_LookProc;

typedef void (*IOLink_LookProc_t) (IOLink_DeviceTablePtr, char *, IOConsts_ReadResults *);
struct IOLink_LookProc_p { IOLink_LookProc_t proc; };

struct _T1_r {
               IOLink_DeviceId did;
               RTgenif_readchar dorc;
               RTgenif_unreadchar dourc;
               RTgenif_geterrno dogeterrno;
               RTgenif_readbytes dorbytes;
               RTgenif_writebytes dowbytes;
               RTgenif_writeln dowrln;
               RTgenif_iseof doeof;
               RTgenif_iseoln doeoln;
               RTgenif_iserror doerror;
             };

typedef struct IOLink_SkipProc_p IOLink_SkipProc;

typedef void (*IOLink_SkipProc_t) (IOLink_DeviceTablePtr);
struct IOLink_SkipProc_p { IOLink_SkipProc_t proc; };

typedef struct IOLink_SkipLookProc_p IOLink_SkipLookProc;

typedef void (*IOLink_SkipLookProc_t) (IOLink_DeviceTablePtr, char *, IOConsts_ReadResults *);
struct IOLink_SkipLookProc_p { IOLink_SkipLookProc_t proc; };

typedef struct IOLink_WriteLnProc_p IOLink_WriteLnProc;

typedef void (*IOLink_WriteLnProc_t) (IOLink_DeviceTablePtr);
struct IOLink_WriteLnProc_p { IOLink_WriteLnProc_t proc; };

typedef struct IOLink_TextReadProc_p IOLink_TextReadProc;

typedef void (*IOLink_TextReadProc_t) (IOLink_DeviceTablePtr, void *, unsigned int, unsigned int *);
struct IOLink_TextReadProc_p { IOLink_TextReadProc_t proc; };

typedef struct IOLink_TextWriteProc_p IOLink_TextWriteProc;

typedef void (*IOLink_TextWriteProc_t) (IOLink_DeviceTablePtr, void *, unsigned int);
struct IOLink_TextWriteProc_p { IOLink_TextWriteProc_t proc; };

typedef struct IOLink_RawReadProc_p IOLink_RawReadProc;

typedef void (*IOLink_RawReadProc_t) (IOLink_DeviceTablePtr, void *, unsigned int, unsigned int *);
struct IOLink_RawReadProc_p { IOLink_RawReadProc_t proc; };

typedef struct IOLink_RawWriteProc_p IOLink_RawWriteProc;

typedef void (*IOLink_RawWriteProc_t) (IOLink_DeviceTablePtr, void *, unsigned int);
struct IOLink_RawWriteProc_p { IOLink_RawWriteProc_t proc; };

typedef struct IOLink_GetNameProc_p IOLink_GetNameProc;

typedef void (*IOLink_GetNameProc_t) (IOLink_DeviceTablePtr, char *, unsigned int);
struct IOLink_GetNameProc_p { IOLink_GetNameProc_t proc; };

typedef struct IOLink_ResetProc_p IOLink_ResetProc;

typedef void (*IOLink_ResetProc_t) (IOLink_DeviceTablePtr);
struct IOLink_ResetProc_p { IOLink_ResetProc_t proc; };

typedef struct IOLink_FlushProc_p IOLink_FlushProc;

typedef void (*IOLink_FlushProc_t) (IOLink_DeviceTablePtr);
struct IOLink_FlushProc_p { IOLink_FlushProc_t proc; };

typedef struct IOLink_FreeProc_p IOLink_FreeProc;

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

RTgenif_GenDevIF RTgenif_InitGenDevIF (IOLink_DeviceId d, RTgenif_readchar rc, RTgenif_unreadchar urc, RTgenif_geterrno geterr, RTgenif_readbytes rbytes, RTgenif_writebytes wbytes, RTgenif_writeln wl, RTgenif_iseof eof, RTgenif_iseoln eoln, RTgenif_iserror iserr);

/*
   getDID - returns the device id belonging to this generic interface.
*/

IOLink_DeviceId RTgenif_getDID (RTgenif_GenDevIF g);

/*
   doReadChar - returns the next character from the generic device.
*/

char RTgenif_doReadChar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   doUnReadChar - pushes back a character to the generic device.
*/

char RTgenif_doUnReadChar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, char ch);

/*
   doGetErrno - returns the errno relating to the generic device.
*/

int RTgenif_doGetErrno (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   doRBytes - attempts to read, n, bytes from the generic device.
              It set the actual amount read and returns a boolean
              to determine whether an error occurred.
*/

unsigned int RTgenif_doRBytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * to, unsigned int max, unsigned int *actual);

/*
   doWBytes - attempts to write, n, bytes to the generic device.
              It sets the actual amount written and returns a
              boolean to determine whether an error occurred.
*/

unsigned int RTgenif_doWBytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * from, unsigned int max, unsigned int *actual);

/*
   doWrLn - writes an end of line marker and returns
            TRUE if successful.
*/

unsigned int RTgenif_doWrLn (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   isEOF - returns true if the end of file was reached.
*/

unsigned int RTgenif_isEOF (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   isEOLN - returns true if the end of line was reached.
*/

unsigned int RTgenif_isEOLN (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   isError - returns true if an error was seen in the device.
*/

unsigned int RTgenif_isError (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   KillGenDevIF - deallocates a generic device.
*/

RTgenif_GenDevIF RTgenif_KillGenDevIF (RTgenif_GenDevIF g);

RTgenif_GenDevIF RTgenif_InitGenDevIF (IOLink_DeviceId d, RTgenif_readchar rc, RTgenif_unreadchar urc, RTgenif_geterrno geterr, RTgenif_readbytes rbytes, RTgenif_writebytes wbytes, RTgenif_writeln wl, RTgenif_iseof eof, RTgenif_iseoln eoln, RTgenif_iserror iserr)
{
  RTgenif_GenDevIF g;

  /* 
   InitGenDev - initializes a generic device.
  */
  Storage_ALLOCATE ((void **) &g, sizeof (_T1));
  g->did = d;
  g->dorc = rc;
  g->dourc = urc;
  g->dogeterrno = geterr;
  g->dorbytes = rbytes;
  g->dowbytes = wbytes;
  g->dowrln = wl;
  g->doeof = eof;
  g->doeoln = eoln;
  g->doerror = iserr;
  return g;
}


/*
   getDID - returns the device id belonging to this generic interface.
*/

IOLink_DeviceId RTgenif_getDID (RTgenif_GenDevIF g)
{
  return g->did;
}


/*
   doReadChar - returns the next character from the generic device.
*/

char RTgenif_doReadChar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return (*g->dorc.proc) (g, d);
}


/*
   doUnReadChar - pushes back a character to the generic device.
*/

char RTgenif_doUnReadChar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, char ch)
{
  return (*g->dourc.proc) (g, d, ch);
}


/*
   doGetErrno - returns the errno relating to the generic device.
*/

int RTgenif_doGetErrno (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return (*g->dogeterrno.proc) (g, d);
}


/*
   doRBytes - attempts to read, n, bytes from the generic device.
              It set the actual amount read and returns a boolean
              to determine whether an error occurred.
*/

unsigned int RTgenif_doRBytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * to, unsigned int max, unsigned int *actual)
{
  return (*g->dorbytes.proc) (g, d, to, max, actual);
}


/*
   doWBytes - attempts to write, n, bytes to the generic device.
              It sets the actual amount written and returns a
              boolean to determine whether an error occurred.
*/

unsigned int RTgenif_doWBytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * from, unsigned int max, unsigned int *actual)
{
  return (*g->dowbytes.proc) (g, d, from, max, actual);
}


/*
   doWrLn - writes an end of line marker and returns
            TRUE if successful.
*/

unsigned int RTgenif_doWrLn (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return (*g->dowrln.proc) (g, d);
}


/*
   isEOF - returns true if the end of file was reached.
*/

unsigned int RTgenif_isEOF (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return (*g->doeof.proc) (g, d);
}


/*
   isEOLN - returns true if the end of line was reached.
*/

unsigned int RTgenif_isEOLN (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return (*g->doeoln.proc) (g, d);
}


/*
   isError - returns true if an error was seen in the device.
*/

unsigned int RTgenif_isError (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return (*g->doerror.proc) (g, d);
}


/*
   KillGenDevIF - deallocates a generic device.
*/

RTgenif_GenDevIF RTgenif_KillGenDevIF (RTgenif_GenDevIF g)
{
  Storage_DEALLOCATE ((void **) &g, sizeof (_T1));
  return NULL;
}

void _M2_RTgenif_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_RTgenif_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
