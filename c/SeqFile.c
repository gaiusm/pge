/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/SeqFile.mod.  */

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
#define _SeqFile_H
#define _SeqFile_C

#   include "GRTgen.h"
#   include "GRTfio.h"
#   include "GIOLink.h"
#   include "GRTgenif.h"
#   include "GFIO.h"
#   include "Gerrno.h"
#   include "GIOConsts.h"
#   include "GChanConsts.h"
#   include "GSYSTEM.h"
#   include "GRTio.h"
#   include "GErrnoCategory.h"

#   define SeqFile_read (SeqFile_FlagSet) ((1 << (ChanConsts_readFlag-ChanConsts_readFlag)))
#   define SeqFile_write (SeqFile_FlagSet) ((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)))
#   define SeqFile_old (SeqFile_FlagSet) ((1 << (ChanConsts_oldFlag-ChanConsts_readFlag)))
#   define SeqFile_text (SeqFile_FlagSet) ((1 << (ChanConsts_textFlag-ChanConsts_readFlag)))
#   define SeqFile_raw (SeqFile_FlagSet) ((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)))
typedef ChanConsts_FlagSet SeqFile_FlagSet;

#if !defined (IOChan_ChanId_D)
#  define IOChan_ChanId_D
   typedef void *IOChan_ChanId;
#endif

typedef IOChan_ChanId SeqFile_ChanId;

typedef ChanConsts_OpenResults SeqFile_OpenResults;

static RTgen_ChanDev dev;
static IOLink_DeviceId did;
void SeqFile_OpenWrite (SeqFile_ChanId *cid, char *name_, unsigned int _name_high, SeqFile_FlagSet flags, SeqFile_OpenResults *res);

/*
   OpenAppend - attempts to obtain and open a channel connected
                to a stored rewindable file of the given name.
                The write and old flags are implied; without
                the raw flag, text is implied.  If successful,
                assigns to cid the identity of the opened channel,
                assigns the value opened to res, and selects output
                mode, with the write position corresponding to the
                length of the file.  If a channel cannot be opened
                as required, the value of res indicates the reason,
                and cid identifies the invalid channel.
  */

void SeqFile_OpenAppend (SeqFile_ChanId *cid, char *name_, unsigned int _name_high, SeqFile_FlagSet flags, SeqFile_OpenResults *res);
void SeqFile_OpenRead (SeqFile_ChanId *cid, char *name_, unsigned int _name_high, SeqFile_FlagSet flags, SeqFile_OpenResults *res);

/*
   IsSeqFile - tests if the channel identified by cid is open to a
               rewindable sequential file.
*/

unsigned int SeqFile_IsSeqFile (SeqFile_ChanId cid);

/*
   Reread - if the channel identified by cid is not open
            to a rewindable sequential file, the exception
            wrongDevice is raised; otherwise attempts to set
            the read position to the start of the file, and
            to select input mode.  If the operation cannot
            be performed (perhaps because of insufficient
            permissions) neither input mode nor output
            mode is selected.
*/

void SeqFile_Reread (SeqFile_ChanId cid);

/*
   Rewrite - if the channel identified by cid is not open to a
             rewindable sequential file, the exception wrongDevice
             is raised; otherwise, attempts to truncate the
             file to zero length, and to select output mode.
             If the operation cannot be performed (perhaps
             because of insufficient permissions) neither input
             mode nor output mode is selected.
*/

void SeqFile_Rewrite (SeqFile_ChanId cid);

/*
   Close - if the channel identified by cid is not open to a sequential
           stream, the exception wrongDevice is raised; otherwise
           closes the channel, and assigns the value identifying
           the invalid channel to cid.
*/

void SeqFile_Close (SeqFile_ChanId *cid);
static void look (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);
static void skip (IOLink_DeviceTablePtr d);
static void skiplook (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);
static void lnwrite (IOLink_DeviceTablePtr d);
static void textread (IOLink_DeviceTablePtr d, void * to, unsigned int maxChars, unsigned int *charsRead);
static void textwrite (IOLink_DeviceTablePtr d, void * from, unsigned int charsToWrite);
static void rawread (IOLink_DeviceTablePtr d, void * to, unsigned int maxLocs, unsigned int *locsRead);
static void rawwrite (IOLink_DeviceTablePtr d, void * from, unsigned int locsToWrite);
static void getname (IOLink_DeviceTablePtr d, char *a, unsigned int _a_high);
static void flush (IOLink_DeviceTablePtr d);

/*
   checkOpenErrno - assigns, e, and, res, depending upon file result of opening,
                    file.
*/

static void checkOpenErrno (FIO_File file, int *e, SeqFile_OpenResults *res);

/*
   newCid - returns a ChanId which represents the opened file, name.
            res is set appropriately on return.
*/

static SeqFile_ChanId newCid (char *fname_, unsigned int _fname_high, SeqFile_FlagSet f, SeqFile_OpenResults *res, unsigned int toRead, IOLink_ResetProc whichreset);

/*
   resetAppend - ensures that +write and -read and seeks to
                 the end of the file.
*/

static void resetAppend (IOLink_DeviceTablePtr d);

/*
   resetRead - 
*/

static void resetRead (IOLink_DeviceTablePtr d);

/*
   resetWrite - 
*/

static void resetWrite (IOLink_DeviceTablePtr d);

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

static void getname (IOLink_DeviceTablePtr d, char *a, unsigned int _a_high)
{
  FIO_GetFileName (RTio_GetFile ((RTio_ChanId) d->cid), (char *) a, _a_high);
}

static void flush (IOLink_DeviceTablePtr d)
{
  FIO_FlushBuffer (RTio_GetFile ((RTio_ChanId) d->cid));
}


/*
   checkOpenErrno - assigns, e, and, res, depending upon file result of opening,
                    file.
*/

static void checkOpenErrno (FIO_File file, int *e, SeqFile_OpenResults *res)
{
  if (FIO_IsNoError (file))
    (*e) = 0;
  else
    (*e) = errno_geterrno ();
  (*res) = ErrnoCategory_GetOpenResults ((*e));
}


/*
   newCid - returns a ChanId which represents the opened file, name.
            res is set appropriately on return.
*/

static SeqFile_ChanId newCid (char *fname_, unsigned int _fname_high, SeqFile_FlagSet f, SeqFile_OpenResults *res, unsigned int toRead, IOLink_ResetProc whichreset)
{
  RTio_ChanId c;
  FIO_File file;
  int e;
  IOLink_DeviceTablePtr p;
  char fname[_fname_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (fname, fname_, _fname_high+1);

  if (toRead)
    file = FIO_OpenToRead ((char *) fname, _fname_high);
  else
    file = FIO_OpenToWrite ((char *) fname, _fname_high);
  checkOpenErrno (file, &e, res);
  if (FIO_IsNoError (file))
    {
      IOLink_MakeChan (did, (IOChan_ChanId*) &c);
      RTio_SetFile (c, file);
      p = IOLink_DeviceTablePtrValue ((IOChan_ChanId) c, did);
      p->flags = f;
      p->errNum = e;
      p->doLook.proc = look;
      p->doSkip.proc = skip;
      p->doSkipLook.proc = skiplook;
      p->doLnWrite.proc = lnwrite;
      p->doTextRead.proc = textread;
      p->doTextWrite.proc = textwrite;
      p->doRawRead.proc = rawread;
      p->doRawWrite.proc = rawwrite;
      p->doGetName.proc = getname;
      p->doReset = whichreset;
      p->doFlush.proc = flush;
      p->doFree.proc = handlefree;
      return c;
    }
  else
    return IOChan_InvalidChan ();
}


/*
   resetAppend - ensures that +write and -read and seeks to
                 the end of the file.
*/

static void resetAppend (IOLink_DeviceTablePtr d)
{
  FIO_File f;

  d->flags = (d->flags|SeqFile_write) & (~SeqFile_read);
  FIO_SetPositionFromEnd (RTio_GetFile ((RTio_ChanId) d->cid), 0);
  RTgen_checkErrno (dev, d);
}


/*
   resetRead - 
*/

static void resetRead (IOLink_DeviceTablePtr d)
{
  SeqFile_Reread ((SeqFile_ChanId) d->cid);
}


/*
   resetWrite - 
*/

static void resetWrite (IOLink_DeviceTablePtr d)
{
  SeqFile_Rewrite ((SeqFile_ChanId) d->cid);
}


/*
   handlefree - 
*/

static void handlefree (IOLink_DeviceTablePtr d)
{
  FIO_File f;

  (*d->doFlush.proc) (d);
  RTgen_checkErrno (dev, d);
  f = RTio_GetFile ((RTio_ChanId) (d->cid));
  if (FIO_IsNoError (f))
    FIO_Close (f);
  RTgen_checkErrno (dev, d);
}


/*
   Init - 
*/

static void Init (void)
{
  RTgenif_GenDevIF gen;

  IOLink_AllocateDeviceId (&did);
  gen = RTgenif_InitGenDevIF (did, (RTgenif_readchar) {(RTgenif_readchar_t) RTfio_doreadchar}, (RTgenif_unreadchar) {(RTgenif_unreadchar_t) RTfio_dounreadchar}, (RTgenif_geterrno) {(RTgenif_geterrno_t) RTfio_dogeterrno}, (RTgenif_readbytes) {(RTgenif_readbytes_t) RTfio_dorbytes}, (RTgenif_writebytes) {(RTgenif_writebytes_t) RTfio_dowbytes}, (RTgenif_writeln) {(RTgenif_writeln_t) RTfio_dowriteln}, (RTgenif_iseof) {(RTgenif_iseof_t) RTfio_iseof}, (RTgenif_iseoln) {(RTgenif_iseoln_t) RTfio_iseoln}, (RTgenif_iserror) {(RTgenif_iserror_t) RTfio_iserror});
  dev = RTgen_InitChanDev ((RTgen_DeviceType) RTgen_streamfile, did, gen);
}

void SeqFile_OpenWrite (SeqFile_ChanId *cid, char *name_, unsigned int _name_high, SeqFile_FlagSet flags, SeqFile_OpenResults *res)
{
  char name[_name_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (name, name_, _name_high+1);

  /* 
   Attempts to obtain and open a channel connected to a stored rewindable
   file of the given name.  The write flag is implied; without the raw
   flag, text is implied.  If successful, assigns to cid the identity of
   the opened channel, assigns the value opened to res, and selects
   output mode, with the write position at the start of the file (i.e.
   the file is of zero length).  If a channel cannot be opened as required,
   the value of res indicates the reason, and cid identifies the
   invalid channel.
  */
  flags |= (1 << (ChanConsts_writeFlag-ChanConsts_readFlag ));
  if (! ((((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (flags)) != 0)))
    flags |= (1 << (ChanConsts_textFlag-ChanConsts_readFlag ));
  (*cid) = newCid ((char *) name, _name_high, flags, res, FALSE, (IOLink_ResetProc) {(IOLink_ResetProc_t) resetWrite});
}


/*
   OpenAppend - attempts to obtain and open a channel connected
                to a stored rewindable file of the given name.
                The write and old flags are implied; without
                the raw flag, text is implied.  If successful,
                assigns to cid the identity of the opened channel,
                assigns the value opened to res, and selects output
                mode, with the write position corresponding to the
                length of the file.  If a channel cannot be opened
                as required, the value of res indicates the reason,
                and cid identifies the invalid channel.
  */

void SeqFile_OpenAppend (SeqFile_ChanId *cid, char *name_, unsigned int _name_high, SeqFile_FlagSet flags, SeqFile_OpenResults *res)
{
  char name[_name_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (name, name_, _name_high+1);

  flags = (flags|ChanConsts_write)|ChanConsts_old;
  if (! ((((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (flags)) != 0)))
    flags |= (1 << (ChanConsts_textFlag-ChanConsts_readFlag ));
  (*cid) = newCid ((char *) name, _name_high, flags, res, FALSE, (IOLink_ResetProc) {(IOLink_ResetProc_t) resetAppend});
  if (SeqFile_IsSeqFile ((*cid)))
    {
      FIO_SetPositionFromEnd (RTio_GetFile ((RTio_ChanId) (*cid)), 0);
      RTgen_checkErrno (dev, RTio_GetDevicePtr ((RTio_ChanId) (*cid)));
    }
}

void SeqFile_OpenRead (SeqFile_ChanId *cid, char *name_, unsigned int _name_high, SeqFile_FlagSet flags, SeqFile_OpenResults *res)
{
  char name[_name_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (name, name_, _name_high+1);

  /* 
   Attempts to obtain and open a channel connected to a stored rewindable
   file of the given name.  The read and old flags are implied; without
   the raw flag, text is implied.  If successful, assigns to cid the
   identity of the opened channel, assigns the value opened to res, and
   selects input mode, with the read position corresponding to the start
   of the file.  If a channel cannot be opened as required, the value of
   res indicates the reason, and cid identifies the invalid channel.
  */
  flags = (flags|ChanConsts_read)|ChanConsts_old;
  if (! ((((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (flags)) != 0)))
    flags |= (1 << (ChanConsts_textFlag-ChanConsts_readFlag ));
  (*cid) = newCid ((char *) name, _name_high, flags, res, TRUE, (IOLink_ResetProc) {(IOLink_ResetProc_t) resetRead});
}


/*
   IsSeqFile - tests if the channel identified by cid is open to a
               rewindable sequential file.
*/

unsigned int SeqFile_IsSeqFile (SeqFile_ChanId cid)
{
  return (((cid != NULL) && ((IOChan_InvalidChan ()) != cid)) && (IOLink_IsDevice ((IOChan_ChanId) cid, did))) && (((((1 << (ChanConsts_readFlag)) & (IOChan_CurrentFlags ((IOChan_ChanId) cid))) != 0)) || ((((1 << (ChanConsts_writeFlag)) & (IOChan_CurrentFlags ((IOChan_ChanId) cid))) != 0)));
}


/*
   Reread - if the channel identified by cid is not open
            to a rewindable sequential file, the exception
            wrongDevice is raised; otherwise attempts to set
            the read position to the start of the file, and
            to select input mode.  If the operation cannot
            be performed (perhaps because of insufficient
            permissions) neither input mode nor output
            mode is selected.
*/

void SeqFile_Reread (SeqFile_ChanId cid)
{
  IOLink_DeviceTablePtr d;

  if (SeqFile_IsSeqFile (cid))
    {
      d = IOLink_DeviceTablePtrValue ((IOChan_ChanId) cid, did);
      d->flags &= (~(1 << (ChanConsts_writeFlag-ChanConsts_readFlag )));
      if ((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (d->flags)) != 0))
        {
          FIO_SetPositionFromBeginning (RTio_GetFile ((RTio_ChanId) d->cid), 0);
          RTgen_checkErrno (dev, d);
        }
      else
        d->flags &= (~(1 << (ChanConsts_readFlag-ChanConsts_readFlag )));
    }
  else
    IOLink_RAISEdevException ((IOChan_ChanId) cid, did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "SeqFile.'\"Reread\"': channel is not a sequential file", 52);
}


/*
   Rewrite - if the channel identified by cid is not open to a
             rewindable sequential file, the exception wrongDevice
             is raised; otherwise, attempts to truncate the
             file to zero length, and to select output mode.
             If the operation cannot be performed (perhaps
             because of insufficient permissions) neither input
             mode nor output mode is selected.
*/

void SeqFile_Rewrite (SeqFile_ChanId cid)
{
  IOLink_DeviceTablePtr d;

  if (SeqFile_IsSeqFile (cid))
    {
      d = IOLink_DeviceTablePtrValue ((IOChan_ChanId) cid, did);
      d->flags &= (~(1 << (ChanConsts_readFlag-ChanConsts_readFlag )));
      if ((((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)) & (d->flags)) != 0))
        {
          FIO_SetPositionFromBeginning (RTio_GetFile ((RTio_ChanId) d->cid), 0);
          RTgen_checkErrno (dev, d);
        }
      else
        d->flags &= (~(1 << (ChanConsts_writeFlag-ChanConsts_readFlag )));
    }
  else
    IOLink_RAISEdevException ((IOChan_ChanId) cid, did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "SeqFile.'\"Rewrite\"': channel is not a sequential file", 53);
}


/*
   Close - if the channel identified by cid is not open to a sequential
           stream, the exception wrongDevice is raised; otherwise
           closes the channel, and assigns the value identifying
           the invalid channel to cid.
*/

void SeqFile_Close (SeqFile_ChanId *cid)
{
  if (SeqFile_IsSeqFile ((*cid)))
    {
      IOLink_UnMakeChan (did, (IOChan_ChanId*) cid);
      (*cid) = IOChan_InvalidChan ();
    }
  else
    IOLink_RAISEdevException ((IOChan_ChanId) (*cid), did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "SeqFile.'\"Close\"': channel is not a sequential file", 51);
}

void _M2_SeqFile_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_SeqFile_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
