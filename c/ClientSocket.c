/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/ClientSocket.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#   include "GM2RTS.h"
#define _ClientSocket_H
#define _ClientSocket_C

#   include "GASCII.h"
#   include "GChanConsts.h"
#   include "GRTio.h"
#   include "GRTgenif.h"
#   include "GRTdata.h"
#   include "GIOChan.h"
#   include "GIOConsts.h"
#   include "GIOLink.h"
#   include "GStorage.h"
#   include "GStrings.h"
#   include "GSYSTEM.h"
#   include "Glibc.h"
#   include "Gerrno.h"
#   include "GErrnoCategory.h"
#   include "GWholeStr.h"
#   include "GRTgen.h"
#   include "Gwrapsock.h"

typedef void *ClientInfo;

typedef unsigned char *PtrToLoc;

static RTdata_ModuleId mid;
static IOLink_DeviceId did;
static RTgen_ChanDev dev;
static unsigned int ClientInfoSize;

/*
   OpenSocket - opens a TCP client connection to host:port.
*/

void ClientSocket_OpenSocket (IOChan_ChanId *cid, char *host_, unsigned int _host_high, unsigned int port, ChanConsts_FlagSet f, ChanConsts_OpenResults *res);

/*
   Close - if the channel identified by cid is not open to a socket
           stream, the exception wrongDevice is raised; otherwise
           closes the channel, and assigns the value identifying
           the invalid channel to cid.
*/

void ClientSocket_Close (IOChan_ChanId *cid);

/*
   IsSocket - tests if the channel identified by cid is open as
              a client socket stream.
*/

unsigned int ClientSocket_IsSocket (IOChan_ChanId cid);
static void look (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);
static void skip (IOLink_DeviceTablePtr d);
static void skiplook (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);
static void lnwrite (IOLink_DeviceTablePtr d);
static void textread (IOLink_DeviceTablePtr d, void * to, unsigned int maxChars, unsigned int *charsRead);
static void textwrite (IOLink_DeviceTablePtr d, void * from, unsigned int charsToWrite);
static void rawread (IOLink_DeviceTablePtr d, void * to, unsigned int maxLocs, unsigned int *locsRead);
static void rawwrite (IOLink_DeviceTablePtr d, void * from, unsigned int locsToWrite);

/*
   doreadchar - returns a CHAR from the file associated with, g.
*/

static char doreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   dounreadchar - pushes a CHAR back onto the file associated with, g.
*/

static char dounreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, char ch);

/*
   dogeterrno - returns the errno relating to the generic device.
*/

static int dogeterrno (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   dorbytes - reads upto, max, bytes setting, actual, and
              returning FALSE if an error (not due to eof)
              occurred.
*/

static unsigned int dorbytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * to, unsigned int max, unsigned int *actual);

/*
   dowbytes - 
*/

static unsigned int dowbytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * from, unsigned int nBytes, unsigned int *actual);

/*
   dowriteln - attempt to write an end of line marker to the
               file and returns TRUE if successful.
*/

static unsigned int dowriteln (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   iseof - returns TRUE if end of file is seen.
*/

static unsigned int iseof (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   iseoln - returns TRUE if end of line is seen.
*/

static unsigned int iseoln (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   iserror - returns TRUE if an error was seen on the device.
*/

static unsigned int iserror (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   iserror - returns TRUE if an error was seen on the device.
*/

static void getname (IOLink_DeviceTablePtr d, char *a, unsigned int _a_high);

/*
   freeData - disposes of, c.
*/

static void freeData (ClientInfo c);

/*
   handlefree - 
*/

static void handlefree (IOLink_DeviceTablePtr d);

/*
   Init - 
*/

static void Init (void);

static void look (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r)
{
  /* This file is part of GNU Modula-2.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  */
  RTgen_doLook (dev, d, ch, r);
}

static void skip (IOLink_DeviceTablePtr d)
{
  RTgen_doSkip (dev, d);
}

static void skiplook (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r)
{
  RTgen_doSkipLook (dev, d, ch, r);
}

static void lnwrite (IOLink_DeviceTablePtr d)
{
  RTgen_doWriteLn (dev, d);
}

static void textread (IOLink_DeviceTablePtr d, void * to, unsigned int maxChars, unsigned int *charsRead)
{
  RTgen_doReadText (dev, d, to, maxChars, charsRead);
}

static void textwrite (IOLink_DeviceTablePtr d, void * from, unsigned int charsToWrite)
{
  RTgen_doWriteText (dev, d, from, charsToWrite);
}

static void rawread (IOLink_DeviceTablePtr d, void * to, unsigned int maxLocs, unsigned int *locsRead)
{
  RTgen_doReadLocs (dev, d, to, maxLocs, locsRead);
}

static void rawwrite (IOLink_DeviceTablePtr d, void * from, unsigned int locsToWrite)
{
  RTgen_doWriteLocs (dev, d, from, locsToWrite);
}


/*
   doreadchar - returns a CHAR from the file associated with, g.
*/

static char doreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  int i;
  int fd;
  ClientInfo c;
  char ch;

  c = RTdata_GetData (d, mid);
  fd = wrapsock_getClientSocketFd ((wrapsock_clientInfo) c);
  if (! (wrapsock_getPushBackChar ((wrapsock_clientInfo) c, &ch)))
    {
      do {
        i = libc_read (fd, &ch, (size_t) sizeof (ch));
      } while (! (i != 0));
      if (i < 0)
        d->errNum = errno_geterrno ();
    }
  return ch;
}


/*
   dounreadchar - pushes a CHAR back onto the file associated with, g.
*/

static char dounreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, char ch)
{
  int fd;
  ClientInfo c;

  c = RTdata_GetData (d, mid);
  fd = wrapsock_getClientSocketFd ((wrapsock_clientInfo) c);
  if (! (wrapsock_setPushBackChar ((wrapsock_clientInfo) c, ch)))
    IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "ClientSocket.dounreadchar: number of characters pushed back exceeds buffer", 74);
  return ch;
}


/*
   dogeterrno - returns the errno relating to the generic device.
*/

static int dogeterrno (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return errno_geterrno ();
}


/*
   dorbytes - reads upto, max, bytes setting, actual, and
              returning FALSE if an error (not due to eof)
              occurred.
*/

static unsigned int dorbytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * to, unsigned int max, unsigned int *actual)
{
  int fd;
  ClientInfo c;
  PtrToLoc p;
  int i;

  c = RTdata_GetData (d, mid);
  if (max > 0)
    {
      p = to;
      if (wrapsock_getPushBackChar ((wrapsock_clientInfo) c, (char *) p))
        {
          (*actual) = 1;
          return TRUE;
        }
      fd = wrapsock_getClientSocketFd ((wrapsock_clientInfo) c);
      i = libc_read (fd, (void *) p, (size_t) max);
      if (i >= 0)
        {
          (*actual) = i;
          return TRUE;
        }
      else
        {
          d->errNum = errno_geterrno ();
          (*actual) = 0;
          return FALSE;
        }
    }
}


/*
   dowbytes - 
*/

static unsigned int dowbytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * from, unsigned int nBytes, unsigned int *actual)
{
  int fd;
  ClientInfo c;
  int i;

  c = RTdata_GetData (d, mid);
  fd = wrapsock_getClientSocketFd ((wrapsock_clientInfo) c);
  i = libc_write (fd, from, (size_t) nBytes);
  if (i >= 0)
    {
      (*actual) = i;
      return TRUE;
    }
  else
    {
      d->errNum = errno_geterrno ();
      (*actual) = 0;
      return FALSE;
    }
}


/*
   dowriteln - attempt to write an end of line marker to the
               file and returns TRUE if successful.
*/

static unsigned int dowriteln (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  typedef struct _T1_a _T1;

  struct _T1_a { char array[1+1]; };
  _T1 a;
  unsigned int i;

  a.array[0] = ASCII_cr;
  a.array[1] = ASCII_lf;
  return (dowbytes (g, d, &a, (unsigned int) sizeof (a), &i)) && (i == (sizeof (a)));
}


/*
   iseof - returns TRUE if end of file is seen.
*/

static unsigned int iseof (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  char ch;

  ch = doreadchar (g, d);
  if (d->errNum == 0)
    {
      ch = dounreadchar (g, d, ch);
      return FALSE;
    }
  else
    return TRUE;
}


/*
   iseoln - returns TRUE if end of line is seen.
*/

static unsigned int iseoln (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  char ch;

  ch = doreadchar (g, d);
  if (d->errNum == 0)
    {
      ch = dounreadchar (g, d, ch);
      return ch == ASCII_lf;
    }
  else
    return FALSE;
}


/*
   iserror - returns TRUE if an error was seen on the device.
*/

static unsigned int iserror (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return d->errNum != 0;
}


/*
   iserror - returns TRUE if an error was seen on the device.
*/

static void getname (IOLink_DeviceTablePtr d, char *a, unsigned int _a_high)
{
  typedef struct _T2_a _T2;

  struct _T2_a { char array[6+1]; };
  ClientInfo c;
  _T2 b;

  c = RTdata_GetData (d, mid);
  wrapsock_getClientHostname ((wrapsock_clientInfo) c, a, _a_high);
  Strings_Append ((char *) ":", 1, (char *) a, _a_high);
  WholeStr_IntToStr ((int) wrapsock_getClientPortNo ((wrapsock_clientInfo) c), (char *) &b.array[0], 6);
  Strings_Append ((char *) &b.array[0], 6, (char *) a, _a_high);
}


/*
   freeData - disposes of, c.
*/

static void freeData (ClientInfo c)
{
  Storage_DEALLOCATE ((void **) &c, ClientInfoSize);
}


/*
   handlefree - 
*/

static void handlefree (IOLink_DeviceTablePtr d)
{
  ClientInfo c;
  int fd;
  int i;

  c = RTdata_GetData (d, mid);
  fd = wrapsock_getClientSocketFd ((wrapsock_clientInfo) c);
  i = libc_close (fd);
  RTgen_checkErrno (dev, d);
  RTdata_KillData (d, mid);
}


/*
   Init - 
*/

static void Init (void)
{
  RTgenif_GenDevIF gen;

  RTdata_MakeModuleId (&mid);
  ClientInfoSize = wrapsock_getSizeOfClientInfo ();
  IOLink_AllocateDeviceId (&did);
  gen = RTgenif_InitGenDevIF (did, (RTgenif_readchar) {(RTgenif_readchar_t) doreadchar}, (RTgenif_unreadchar) {(RTgenif_unreadchar_t) dounreadchar}, (RTgenif_geterrno) {(RTgenif_geterrno_t) dogeterrno}, (RTgenif_readbytes) {(RTgenif_readbytes_t) dorbytes}, (RTgenif_writebytes) {(RTgenif_writebytes_t) dowbytes}, (RTgenif_writeln) {(RTgenif_writeln_t) dowriteln}, (RTgenif_iseof) {(RTgenif_iseof_t) iseof}, (RTgenif_iseoln) {(RTgenif_iseoln_t) iseoln}, (RTgenif_iserror) {(RTgenif_iserror_t) iserror});
  dev = RTgen_InitChanDev ((RTgen_DeviceType) RTgen_streamfile, did, gen);
}


/*
   OpenSocket - opens a TCP client connection to host:port.
*/

void ClientSocket_OpenSocket (IOChan_ChanId *cid, char *host_, unsigned int _host_high, unsigned int port, ChanConsts_FlagSet f, ChanConsts_OpenResults *res)
{
  IOLink_DeviceTablePtr d;
  ClientInfo c;
  int e;
  char host[_host_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (host, host_, _host_high+1);

  IOLink_MakeChan (did, cid);  /* create new channel  */
  Storage_ALLOCATE ((void **) &c, ClientInfoSize);  /* allocate client socket memory  */
  d = IOLink_DeviceTablePtrValue ((*cid), did);  /* allocate client socket memory  */
  RTdata_InitData (d, mid, (void *) c, (RTdata_FreeProcedure) {(RTdata_FreeProcedure_t) freeData});  /* attach memory to device and module  */
  (*res) = wrapsock_clientOpen ((wrapsock_clientInfo) c, &host, M2RTS_Length (host, _host_high), port);  /* attach memory to device and module  */
  if ((*res) == ChanConsts_opened)
    e = 0;
  else
    e = errno_geterrno ();
  d->flags = f;
  d->errNum = e;
  d->doLook.proc = look;
  d->doSkip.proc = skip;
  d->doSkipLook.proc = skiplook;
  d->doLnWrite.proc = lnwrite;
  d->doTextRead.proc = textread;
  d->doTextWrite.proc = textwrite;
  d->doRawRead.proc = rawread;
  d->doRawWrite.proc = rawwrite;
  d->doGetName.proc = getname;
  d->doFree.proc = handlefree;
}


/*
   Close - if the channel identified by cid is not open to a socket
           stream, the exception wrongDevice is raised; otherwise
           closes the channel, and assigns the value identifying
           the invalid channel to cid.
*/

void ClientSocket_Close (IOChan_ChanId *cid)
{
  if (ClientSocket_IsSocket ((*cid)))
    {
      IOLink_UnMakeChan (did, cid);
      (*cid) = IOChan_InvalidChan ();
    }
  else
    IOLink_RAISEdevException ((*cid), did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "ClientSocket.'\"Close\"': channel is not a socket stream", 54);
}


/*
   IsSocket - tests if the channel identified by cid is open as
              a client socket stream.
*/

unsigned int ClientSocket_IsSocket (IOChan_ChanId cid)
{
  return (((cid != NULL) && ((IOChan_InvalidChan ()) != cid)) && (IOLink_IsDevice (cid, did))) && (((((1 << (ChanConsts_readFlag)) & (IOChan_CurrentFlags (cid))) != 0)) || ((((1 << (ChanConsts_writeFlag)) & (IOChan_CurrentFlags (cid))) != 0)));
}

void _M2_ClientSocket_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_ClientSocket_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
