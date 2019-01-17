/* automatically created by mc from ../git-pge/m2/MemStream.mod.  */

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
#   include "GStorage.h"
#   include <complex.h>
#define _MemStream_H
#define _MemStream_C

#   include "GRTgen.h"
#   include "GRTdata.h"
#   include "GIOLink.h"
#   include "GBuiltins.h"
#   include "GAssertion.h"
#   include "GStrings.h"
#   include "GRTgenif.h"
#   include "GFIO.h"
#   include "GIOConsts.h"
#   include "GChanConsts.h"
#   include "GSYSTEM.h"
#   include "GASCII.h"
#   include "GStorage.h"
#   include "Glibc.h"
#   include "GRTio.h"
#   include "Gerrno.h"
#   include "GErrnoCategory.h"
#   include "GIOChan.h"

#   define InitialLength 4096
#   define Debugging FALSE
typedef struct _T1_r _T1;

typedef unsigned char *PtrToLoc;

typedef char *PtrToChar;

typedef void * *PtrToAddress;

typedef unsigned int *PtrToCardinal;

typedef _T1 *MemInfo;

struct _T1_r {
               void *buffer;
               unsigned int length;
               unsigned int index;
               PtrToAddress pBuffer;
               PtrToCardinal pLength;
               PtrToCardinal pUsed;
               unsigned int dealloc;
               unsigned int eof;
               unsigned int eoln;
             };

static RTgen_ChanDev dev;
static IOLink_DeviceId did;
static RTdata_ModuleId mid;
void MemStream_OpenWrite (IOChan_ChanId *cid, ChanConsts_FlagSet flags, ChanConsts_OpenResults *res, void * *buffer, unsigned int *length, unsigned int *used, unsigned int deallocOnClose);
void MemStream_OpenRead (IOChan_ChanId *cid, ChanConsts_FlagSet flags, ChanConsts_OpenResults *res, void * buffer, unsigned int length, unsigned int deallocOnClose);

/*
   Close - if the channel identified by cid is not open to a sequential
           stream, the exception wrongDevice is raised; otherwise
           closes the channel, and assigns the value identifying
           the invalid channel to cid.
*/

void MemStream_Close (IOChan_ChanId *cid);

/*
   Rewrite - if the channel identified by cid is not open to a
             memory stream, the exception wrongDevice
             is raised; otherwise, it sets the index to 0.
             Subsequent writes will overwrite the previous buffer
             contents.
*/

void MemStream_Rewrite (IOChan_ChanId cid);

/*
   Reread - if the channel identified by cid is not open
            to a memory stream, the exception
            wrongDevice is raised; otherwise it sets the
            index to 0.  Subsequent reads will read the
            previous buffer contents.
*/

void MemStream_Reread (IOChan_ChanId cid);

/*
   IsMem - tests if the channel identified by cid is open as
           a memory stream.
*/

unsigned int MemStream_IsMem (IOChan_ChanId cid);

/*
   Min -
*/

static unsigned int Min (unsigned int a, unsigned int b);

/*
   Min -
*/

static void look (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);

/*
   Min -
*/

static void skip (IOLink_DeviceTablePtr d);

/*
   Min -
*/

static void skiplook (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);

/*
   Min -
*/

static void lnwrite (IOLink_DeviceTablePtr d);

/*
   Min -
*/

static void textread (IOLink_DeviceTablePtr d, void * to, unsigned int maxChars, unsigned int *charsRead);

/*
   Min -
*/

static void textwrite (IOLink_DeviceTablePtr d, void * from, unsigned int charsToWrite);

/*
   Min -
*/

static void rawread (IOLink_DeviceTablePtr d, void * to, unsigned int maxLocs, unsigned int *locsRead);

/*
   Min -
*/

static void rawwrite (IOLink_DeviceTablePtr d, void * from, unsigned int locsToWrite);

/*
   Min -
*/

static void getname (IOLink_DeviceTablePtr d, char *a, unsigned int _a_high);

/*
   Min -
*/

static void flush (IOLink_DeviceTablePtr d);

/*
   doreadchar - returns a CHAR from the file associated with, g.
*/

static char doreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   dounreadchar - pushes a CHAR back onto the file associated with, g.
*/

static char dounreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, char ch);

/*
   dogeterrno - always return 0 as the memstream device never invokes errno.
*/

static int dogeterrno (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d);

/*
   dorbytes - reads upto, max, bytes setting, actual, and
              returning FALSE if an error (not due to eof)
              occurred.
*/

static unsigned int dorbytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * to, unsigned int max, unsigned int *actual);

/*
   memDump -
*/

static void memDump (void * a, unsigned int len);

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
   iseof - returns TRUE if end of file has been seen.
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
   AssignLength -
*/

static void AssignLength (MemInfo m, unsigned int l);

/*
   AssignBuffer -
*/

static void AssignBuffer (MemInfo m, void * b);

/*
   AssignIndex -
*/

static void AssignIndex (MemInfo m, unsigned int i);

/*
   newCidWrite - returns a ChanId which represents the opened file, name.
                 res is set appropriately on return.
*/

static IOChan_ChanId newCidWrite (ChanConsts_FlagSet f, ChanConsts_OpenResults *res, void * *buffer, unsigned int *length, unsigned int *used, unsigned int deallocOnClose);

/*
   newCidRead - returns a ChanId which represents the opened file, name.
                res is set appropriately on return.
*/

static IOChan_ChanId newCidRead (ChanConsts_FlagSet f, ChanConsts_OpenResults *res, void * buffer, unsigned int length, unsigned int deallocOnClose);

/*
   freeMemInfo -
*/

static void freeMemInfo (void * a);

/*
   resetRead - wrap a call to Reread.
*/

static void resetRead (IOLink_DeviceTablePtr d);

/*
   resetWrite - wrap a call to Rewrite.
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


/*
   Min -
*/

static unsigned int Min (unsigned int a, unsigned int b)
{
  if (a < b)
    return a;
  else
    return b;
}


/*
   Min -
*/

static void look (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r)
{
  RTgen_doLook (dev, d, ch, r);
}


/*
   Min -
*/

static void skip (IOLink_DeviceTablePtr d)
{
  RTgen_doSkip (dev, d);
}


/*
   Min -
*/

static void skiplook (IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r)
{
  RTgen_doSkipLook (dev, d, ch, r);
}


/*
   Min -
*/

static void lnwrite (IOLink_DeviceTablePtr d)
{
  RTgen_doWriteLn (dev, d);
}


/*
   Min -
*/

static void textread (IOLink_DeviceTablePtr d, void * to, unsigned int maxChars, unsigned int *charsRead)
{
  RTgen_doReadText (dev, d, to, maxChars, charsRead);
}


/*
   Min -
*/

static void textwrite (IOLink_DeviceTablePtr d, void * from, unsigned int charsToWrite)
{
  RTgen_doWriteText (dev, d, from, charsToWrite);
}


/*
   Min -
*/

static void rawread (IOLink_DeviceTablePtr d, void * to, unsigned int maxLocs, unsigned int *locsRead)
{
  RTgen_doReadLocs (dev, d, to, maxLocs, locsRead);
}


/*
   Min -
*/

static void rawwrite (IOLink_DeviceTablePtr d, void * from, unsigned int locsToWrite)
{
  RTgen_doWriteLocs (dev, d, from, locsToWrite);
}


/*
   Min -
*/

static void getname (IOLink_DeviceTablePtr d, char *a, unsigned int _a_high)
{
  Strings_Assign ((char *) "memstream", 9, (char *) a, _a_high);
}


/*
   Min -
*/

static void flush (IOLink_DeviceTablePtr d)
{
}


/*
   doreadchar - returns a CHAR from the file associated with, g.
*/

static char doreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  MemInfo m;
  PtrToChar pc;

  m = RTdata_GetData (d, mid);
  if (m->index < m->length)
    {
      pc = m->buffer;
      pc += m->index;
      m->index += 1;
      AssignIndex (m, m->index);
      m->eoln = (*pc) == ASCII_nl;
      m->eof = FALSE;
      return (*pc);
    }
  else
    {
      m->eof = TRUE;
      m->eoln = FALSE;
      return ASCII_nul;
    }
}


/*
   dounreadchar - pushes a CHAR back onto the file associated with, g.
*/

static char dounreadchar (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, char ch)
{
  MemInfo m;
  PtrToChar pc;

  m = RTdata_GetData (d, mid);
  if (m->index > 0)
    {
      m->index -= 1;
      AssignIndex (m, m->index);
      m->eof = FALSE;
      pc = m->buffer;
      pc += m->index;
      m->eoln = ch == ASCII_nl;
      Assertion_Assert ((*pc) == ch);  /* expecting to be pushing characters in exactly the reverse order  */
    }
  else
    Assertion_Assert (FALSE);  /* expecting to be pushing characters in exactly the reverse order  */
   /* expecting to be pushing characters in exactly the reverse order  */
  return ch;
}


/*
   dogeterrno - always return 0 as the memstream device never invokes errno.
*/

static int dogeterrno (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return 0;
}


/*
   dorbytes - reads upto, max, bytes setting, actual, and
              returning FALSE if an error (not due to eof)
              occurred.
*/

static unsigned int dorbytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * to, unsigned int max, unsigned int *actual)
{
  MemInfo m;
  PtrToLoc pl;

  m = RTdata_GetData (d, mid);
  pl = m->buffer;
  pl += m->index;
  (*actual) = Min (max, m->length-m->index);
  to = Builtins_memcpy (to, (void *) pl, (*actual));
  m->index += (*actual);
  AssignIndex (m, m->index);
  m->eof = FALSE;
  m->eoln = FALSE;
  return TRUE;
}


/*
   memDump -
*/

static void memDump (void * a, unsigned int len)
{
  unsigned int i;
  unsigned int j;
  unsigned char * p;

  p = a;
  j = 0;
  for (i=0; i<=len; i++)
    {
      if ((j % 16) == 0)
        libc_printf ((char *) "\\n%p  %02x", 10, p, (unsigned int ) ((*p)));
      else
        libc_printf ((char *) " %02x", 5, (unsigned int ) ((*p)));
      p += 1;
      j += 1;
    }
  libc_printf ((char *) "\\n", 2);
}


/*
   dowbytes -
*/

static unsigned int dowbytes (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d, void * from, unsigned int nBytes, unsigned int *actual)
{
  MemInfo m;
  PtrToLoc pl;

  m = RTdata_GetData (d, mid);
  if ((m->index+nBytes) > m->length)
    {
      /* buffer needs to grow  */
      while ((m->index+nBytes) > m->length)
        m->length = m->length*2;
      Storage_REALLOCATE (&m->buffer, m->length);
      AssignLength (m, m->length);
      AssignBuffer (m, m->buffer);
    }
  pl = m->buffer;
  pl += m->index;
  (*actual) = Min (nBytes, m->length-m->index);
  if (Debugging)
    {
      libc_printf ((char *) "memcpy (0x%p, 0x%p, %d)\\n", 25, pl, from, (*actual));
      memDump ((void *) pl, (*actual));
    }
  pl = Builtins_memcpy ((void *) pl, from, (*actual));
  m->index += (*actual);
  AssignIndex (m, m->index);
  return TRUE;
}


/*
   dowriteln - attempt to write an end of line marker to the
               file and returns TRUE if successful.
*/

static unsigned int dowriteln (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  char ch;
  unsigned int n;

  ch = ASCII_nl;
  return dowbytes (g, d, &ch, (unsigned int) sizeof (ch), &n);
}


/*
   iseof - returns TRUE if end of file has been seen.
*/

static unsigned int iseof (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  MemInfo m;

  if (Debugging)
    libc_printf ((char *) "mid = %p, d = %p\\n", 18, mid, d);
  if (Debugging)
    libc_printf ((char *) "mid = %p, d = %p\\n", 18, mid, d);
  m = RTdata_GetData (d, mid);
  return m->eof;
}


/*
   iseoln - returns TRUE if end of line is seen.
*/

static unsigned int iseoln (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  MemInfo m;

  m = RTdata_GetData (d, mid);
  return m->eoln;
}


/*
   iserror - returns TRUE if an error was seen on the device.
*/

static unsigned int iserror (RTgenif_GenDevIF g, IOLink_DeviceTablePtr d)
{
  return FALSE;
}


/*
   AssignLength -
*/

static void AssignLength (MemInfo m, unsigned int l)
{
  m->length = l;
  if (m->pLength != NULL)
    (*m->pLength) = l;
}


/*
   AssignBuffer -
*/

static void AssignBuffer (MemInfo m, void * b)
{
  m->buffer = b;
  if (m->pBuffer != NULL)
    (*m->pBuffer) = b;
}


/*
   AssignIndex -
*/

static void AssignIndex (MemInfo m, unsigned int i)
{
  m->index = i;
  if (m->pUsed != NULL)
    (*m->pUsed) = i;
}


/*
   newCidWrite - returns a ChanId which represents the opened file, name.
                 res is set appropriately on return.
*/

static IOChan_ChanId newCidWrite (ChanConsts_FlagSet f, ChanConsts_OpenResults *res, void * *buffer, unsigned int *length, unsigned int *used, unsigned int deallocOnClose)
{
  IOChan_ChanId c;
  IOLink_DeviceTablePtr d;
  MemInfo m;

  IOLink_MakeChan (did, &c);
  d = IOLink_DeviceTablePtrValue (c, did);
  Storage_ALLOCATE ((void **) &m, sizeof (_T1));
  m->pBuffer = buffer;
  m->pLength = length;
  m->pUsed = used;
  m->dealloc = deallocOnClose;
  Storage_ALLOCATE (&m->buffer, InitialLength);
  if (Debugging)
    libc_printf ((char *) "memory buffer address = 0x%p\\n", 30, m->buffer);
  (*res) = ChanConsts_opened;
  if (m->buffer == NULL)
    (*res) = ChanConsts_noRoomOnDevice;
  AssignBuffer (m, m->buffer);
  AssignLength (m, InitialLength);
  AssignIndex (m, 0);
  RTdata_InitData (d, mid, (void *) m, (RTdata_FreeProcedure) {(RTdata_FreeProcedure_t) freeMemInfo});
  d->flags = f;
  d->errNum = 0;
  d->doLook.proc = look;
  d->doSkip.proc = skip;
  d->doSkipLook.proc = skiplook;
  d->doLnWrite.proc = lnwrite;
  d->doTextRead.proc = textread;
  d->doTextWrite.proc = textwrite;
  d->doRawRead.proc = rawread;
  d->doRawWrite.proc = rawwrite;
  d->doGetName.proc = getname;
  d->doReset.proc = resetWrite;
  d->doFlush.proc = flush;
  d->doFree.proc = handlefree;
  return c;
}


/*
   newCidRead - returns a ChanId which represents the opened file, name.
                res is set appropriately on return.
*/

static IOChan_ChanId newCidRead (ChanConsts_FlagSet f, ChanConsts_OpenResults *res, void * buffer, unsigned int length, unsigned int deallocOnClose)
{
  IOChan_ChanId c;
  IOLink_DeviceTablePtr d;
  MemInfo m;

  IOLink_MakeChan (did, &c);
  d = IOLink_DeviceTablePtrValue (c, did);
  (*res) = ChanConsts_opened;
  Storage_ALLOCATE ((void **) &m, sizeof (_T1));
  m->pBuffer = NULL;
  m->pLength = NULL;
  m->pUsed = NULL;
  m->dealloc = deallocOnClose;
  AssignBuffer (m, buffer);
  AssignLength (m, length);
  AssignIndex (m, 0);
  RTdata_InitData (d, mid, (void *) m, (RTdata_FreeProcedure) {(RTdata_FreeProcedure_t) freeMemInfo});
  d->flags = f;
  d->errNum = 0;
  d->doLook.proc = look;
  d->doSkip.proc = skip;
  d->doSkipLook.proc = skiplook;
  d->doLnWrite.proc = lnwrite;
  d->doTextRead.proc = textread;
  d->doTextWrite.proc = textwrite;
  d->doRawRead.proc = rawread;
  d->doRawWrite.proc = rawwrite;
  d->doGetName.proc = getname;
  d->doReset.proc = resetRead;
  d->doFlush.proc = flush;
  d->doFree.proc = handlefree;
  return c;
}


/*
   freeMemInfo -
*/

static void freeMemInfo (void * a)
{
  MemInfo m;

  Storage_DEALLOCATE (&a, (unsigned int) sizeof ((*m)));
}


/*
   resetRead - wrap a call to Reread.
*/

static void resetRead (IOLink_DeviceTablePtr d)
{
  MemStream_Reread (d->cid);
}


/*
   resetWrite - wrap a call to Rewrite.
*/

static void resetWrite (IOLink_DeviceTablePtr d)
{
  MemStream_Rewrite (d->cid);
}


/*
   handlefree -
*/

static void handlefree (IOLink_DeviceTablePtr d)
{
}


/*
   Init -
*/

static void Init (void)
{
  RTgenif_GenDevIF gen;

  RTdata_MakeModuleId (&mid);
  if (Debugging)
    libc_printf ((char *) "mid = %d\\n", 10, mid);
  IOLink_AllocateDeviceId (&did);
  gen = RTgenif_InitGenDevIF (did, (RTgenif_readchar) {(RTgenif_readchar_t) doreadchar}, (RTgenif_unreadchar) {(RTgenif_unreadchar_t) dounreadchar}, (RTgenif_geterrno) {(RTgenif_geterrno_t) dogeterrno}, (RTgenif_readbytes) {(RTgenif_readbytes_t) dorbytes}, (RTgenif_writebytes) {(RTgenif_writebytes_t) dowbytes}, (RTgenif_writeln) {(RTgenif_writeln_t) dowriteln}, (RTgenif_iseof) {(RTgenif_iseof_t) iseof}, (RTgenif_iseoln) {(RTgenif_iseoln_t) iseoln}, (RTgenif_iserror) {(RTgenif_iserror_t) iserror});
  dev = RTgen_InitChanDev ((RTgen_DeviceType) RTgen_streamfile, did, gen);
}

void MemStream_OpenWrite (IOChan_ChanId *cid, ChanConsts_FlagSet flags, ChanConsts_OpenResults *res, void * *buffer, unsigned int *length, unsigned int *used, unsigned int deallocOnClose)
{
  /* 
   Attempts to obtain and open a channel connected to a contigeous
   buffer in memory.  The write flag is implied; without the raw
   flag, text is implied.  If successful, assigns to cid the identity of
   the opened channel, assigns the value opened to res.
   If a channel cannot be opened as required,
   the value of res indicates the reason, and cid identifies the
   invalid channel.

   The parameters, buffer, length and used maybe updated as
   data is written.  The buffer maybe reallocated
   and its address might alter, however the parameters will
   always reflect the current active buffer.  When this
   channel is closed the buffer is deallocated and
   buffer will be set to NIL, length and used will be set to
   zero.
  */
  if (Debugging)
    libc_printf ((char *) "OpenWrite called\\n", 18);
  flags |= (1 << (ChanConsts_writeFlag-ChanConsts_readFlag ));
  if (! ((((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (flags)) != 0)))
    flags |= (1 << (ChanConsts_textFlag-ChanConsts_readFlag ));
  (*cid) = newCidWrite (flags, res, buffer, length, used, deallocOnClose);
}

void MemStream_OpenRead (IOChan_ChanId *cid, ChanConsts_FlagSet flags, ChanConsts_OpenResults *res, void * buffer, unsigned int length, unsigned int deallocOnClose)
{
  /* 
   Attempts to obtain and open a channel connected to a contigeous
   buffer in memory.  The read and old flags are implied; without
   the raw flag, text is implied.  If successful, assigns to cid the
   identity of the opened channel, assigns the value opened to res, and
   selects input mode, with the read position corresponding to the start
   of the buffer.  If a channel cannot be opened as required, the value of
   res indicates the reason, and cid identifies the invalid channel.
  */
  flags = (flags|ChanConsts_read)|ChanConsts_old;
  if (! ((((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (flags)) != 0)))
    flags |= (1 << (ChanConsts_textFlag-ChanConsts_readFlag ));
  (*cid) = newCidRead (flags, res, buffer, length, deallocOnClose);
}


/*
   Close - if the channel identified by cid is not open to a sequential
           stream, the exception wrongDevice is raised; otherwise
           closes the channel, and assigns the value identifying
           the invalid channel to cid.
*/

void MemStream_Close (IOChan_ChanId *cid)
{
  if (MemStream_IsMem ((*cid)))
    {
      IOLink_UnMakeChan (did, cid);
      (*cid) = IOChan_InvalidChan ();
    }
  else
    IOLink_RAISEdevException ((*cid), did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "MemStream.'\"Close\"': channel is not a sequential file", 53);
}


/*
   Rewrite - if the channel identified by cid is not open to a
             memory stream, the exception wrongDevice
             is raised; otherwise, it sets the index to 0.
             Subsequent writes will overwrite the previous buffer
             contents.
*/

void MemStream_Rewrite (IOChan_ChanId cid)
{
  IOLink_DeviceTablePtr d;
  MemInfo m;

  if (MemStream_IsMem (cid))
    {
      d = IOLink_DeviceTablePtrValue (cid, did);
      d->flags &= (~(1 << (ChanConsts_readFlag-ChanConsts_readFlag )));
      if ((((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)) & (d->flags)) != 0))
        {
          m = RTdata_GetData (d, mid);
          AssignIndex (m, 0);
        }
      else
        d->flags &= (~(1 << (ChanConsts_writeFlag-ChanConsts_readFlag )));
    }
  else
    IOLink_RAISEdevException (cid, did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "MemStream.'\"Rewrite\"': channel is not a memory stream", 53);
}


/*
   Reread - if the channel identified by cid is not open
            to a memory stream, the exception
            wrongDevice is raised; otherwise it sets the
            index to 0.  Subsequent reads will read the
            previous buffer contents.
*/

void MemStream_Reread (IOChan_ChanId cid)
{
  IOLink_DeviceTablePtr d;
  MemInfo m;

  if (MemStream_IsMem (cid))
    {
      d = IOLink_DeviceTablePtrValue (cid, did);
      d->flags &= (~(1 << (ChanConsts_writeFlag-ChanConsts_readFlag )));
      if ((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (d->flags)) != 0))
        {
          m = RTdata_GetData (d, mid);
          AssignIndex (m, 0);
        }
      else
        d->flags &= (~(1 << (ChanConsts_readFlag-ChanConsts_readFlag )));
    }
  else
    IOLink_RAISEdevException (cid, did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "MemStream.'\"Reread\"': channel is not a memory stream", 52);
}


/*
   IsMem - tests if the channel identified by cid is open as
           a memory stream.
*/

unsigned int MemStream_IsMem (IOChan_ChanId cid)
{
  return (((cid != NULL) && ((IOChan_InvalidChan ()) != cid)) && (IOLink_IsDevice (cid, did))) && (((((1 << (ChanConsts_readFlag)) & (IOChan_CurrentFlags (cid))) != 0)) || ((((1 << (ChanConsts_writeFlag)) & (IOChan_CurrentFlags (cid))) != 0)));
}

void _M2_MemStream_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_MemStream_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
