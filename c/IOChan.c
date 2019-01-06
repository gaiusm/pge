/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/IOChan.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <stddef.h>
#   include "Gmcrts.h"
#define _IOChan_H
#define _IOChan_C

#   include "GFIO.h"
#   include "GEXCEPTIONS.h"
#   include "GM2EXCEPTION.h"
#   include "GRTio.h"
#   include "GIOConsts.h"
#   include "GRTentity.h"
#   include "Gerrno.h"
#   include "GErrnoCategory.h"
#   include "GIOLink.h"
#   include "GStdChans.h"
#   include "GM2RTS.h"
#   include "GStorage.h"

typedef RTio_ChanId IOChan_ChanId;

typedef int IOChan_DeviceErrNum;

typedef enum {IOChan_wrongDevice, IOChan_notAvailable, IOChan_skipAtEnd, IOChan_softDeviceError, IOChan_hardDeviceError, IOChan_textParseError, IOChan_notAChannel} IOChan_ChanExceptions;

static EXCEPTIONS_ExceptionSource iochan;
static IOChan_ChanId invalid;
IOChan_ChanId IOChan_InvalidChan (void);
void IOChan_Look (IOChan_ChanId cid, char *ch, IOConsts_ReadResults *res);
void IOChan_Skip (IOChan_ChanId cid);
void IOChan_SkipLook (IOChan_ChanId cid, char *ch, IOConsts_ReadResults *res);
void IOChan_WriteLn (IOChan_ChanId cid);
void IOChan_TextRead (IOChan_ChanId cid, void * to, unsigned int maxChars, unsigned int *charsRead);
void IOChan_TextWrite (IOChan_ChanId cid, void * from, unsigned int charsToWrite);
void IOChan_RawRead (IOChan_ChanId cid, void * to, unsigned int maxLocs, unsigned int *locsRead);
void IOChan_RawWrite (IOChan_ChanId cid, void * from, unsigned int locsToWrite);
void IOChan_GetName (IOChan_ChanId cid, char *s, unsigned int _s_high);
void IOChan_Reset (IOChan_ChanId cid);
void IOChan_Flush (IOChan_ChanId cid);
void IOChan_SetReadResult (IOChan_ChanId cid, IOConsts_ReadResults res);
IOConsts_ReadResults IOChan_ReadResult (IOChan_ChanId cid);
ChanConsts_FlagSet IOChan_CurrentFlags (IOChan_ChanId cid);
unsigned int IOChan_IsChanException (void);
IOChan_ChanExceptions IOChan_ChanException (void);
IOChan_DeviceErrNum IOChan_DeviceError (IOChan_ChanId cid);
static void CheckValid (IOChan_ChanId cid);

static void CheckValid (IOChan_ChanId cid)
{
  /* internal routine to check whether we have a valid channel  */
  if (cid == (IOChan_InvalidChan ()))
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_notAChannel), (char *) "IOChan: ChanId specified is invalid", 35);
}

IOChan_ChanId IOChan_InvalidChan (void)
{
  /* Returns the value identifying the invalid channel.  */
  return invalid;
}

void IOChan_Look (IOChan_ChanId cid, char *ch, IOConsts_ReadResults *res)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* If there is a character as the next item in the input stream cid,
     assigns its value to ch without removing it from the stream;
     otherwise the value of ch is not defined.
     res (and the stored read result) are set to the value
     allRight, endOfLine, or endOfInput.
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.Look: device table ptr is NIL", 36);
  else
    {
      if (dtp->cid == (StdChans_NullChan ()))
        dtp->result = IOConsts_endOfInput;
      else if (((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)) && ((((1 << (ChanConsts_textFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)))
        (*dtp->doLook.proc) (dtp, ch, res);
      else
        (*res) = IOConsts_wrongFormat;
      dtp->result = (*res);
    }
}

void IOChan_Skip (IOChan_ChanId cid)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* If the input stream cid has ended, the exception skipAtEnd is raised;
     otherwise the next character or line mark in cid is removed,
     and the stored read result is set to the value allRight.
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.Skip: device table ptr is NIL", 36);
  else
    if ((dtp->cid == (StdChans_NullChan ())) || (dtp->result == IOConsts_endOfInput))
      EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_skipAtEnd), (char *) "IOChan.Skip: attempt to skip data from a stream that has ended", 62);
    else if (((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)) && ((((1 << (ChanConsts_textFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)))
      {
        (*dtp->doSkip.proc) (dtp);
        dtp->result = IOConsts_allRight;
      }
    else
      EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_notAvailable), (char *) "IOChan.Skip: attempt to skip data from a channel which is not configured as read and text", 89);
}

void IOChan_SkipLook (IOChan_ChanId cid, char *ch, IOConsts_ReadResults *res)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* If the input stream cid has ended, the exception skipAtEnd is raised;
     otherwise the next character or line mark in cid is removed.
     If there is a character as the next item in cid stream,
     assigns its value to ch without removing it from the stream.
     Otherwise, the value of ch is not defined.
     res (and the stored read result) are set to the value allRight,
     endOfLine, or endOfInput.
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.SkipLook: device table ptr is NIL", 40);
  else
    {
      if ((dtp->cid == (StdChans_NullChan ())) || (dtp->result == IOConsts_endOfInput))
        EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_skipAtEnd), (char *) "IOChan.SkipLook: attempt to skip data from a stream that has ended", 66);
      else if (((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)) && ((((1 << (ChanConsts_textFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)))
        (*dtp->doSkipLook.proc) (dtp, ch, &dtp->result);
      else
        EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_notAvailable), (char *) "IOChan.SkipLook: attempt to skip data from a channel which is not configured as read and text", 93);
      (*res) = dtp->result;
    }
}

void IOChan_WriteLn (IOChan_ChanId cid)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Writes a line mark over the channel cid.  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.WriteLn: device table ptr is NIL", 39);
  else
    if (dtp->cid == (StdChans_NullChan ()))
      {}  /* empty.  */
    /* do nothing  */
    else if (((((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)) && ((((1 << (ChanConsts_textFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)))
      (*dtp->doLnWrite.proc) (dtp);
    else
      EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_notAvailable), (char *) "IOChan.WriteLn: attempting to write to a channel which is not configured as write and text", 90);
}

void IOChan_TextRead (IOChan_ChanId cid, void * to, unsigned int maxChars, unsigned int *charsRead)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Reads at most maxChars characters from the current line in cid,
     and assigns corresponding values to successive components of an
     ARRAY OF CHAR variable for which the address of the first
     component is to. The number of characters read is assigned
     to charsRead. The stored read result is set to allRight, 
     endOfLine, or endOfInput.
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.TextRead: device table ptr is NIL", 40);
  else
    if ((dtp->cid == (StdChans_NullChan ())) || (dtp->result == IOConsts_endOfInput))
      {
        (*charsRead) = 0;
        dtp->result = IOConsts_endOfInput;
      }
    else if (((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)) && ((((1 << (ChanConsts_textFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)))
      (*dtp->doTextRead.proc) (dtp, to, maxChars, charsRead);
    else
      EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_notAvailable), (char *) "IOChan.TextRead: attempt to read data from a channel which is not configured as read and text", 93);
}

void IOChan_TextWrite (IOChan_ChanId cid, void * from, unsigned int charsToWrite)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Writes a number of characters given by the value of charsToWrite,
     from successive components of an ARRAY OF CHAR variable for which
     the address of the first component is from, to the channel cid.
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.TextWrite: device table ptr is NIL", 41);
  else
    if (dtp->cid == (StdChans_NullChan ()))
      {}  /* empty.  */
    /* do nothing  */
    else if (((((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)) && ((((1 << (ChanConsts_textFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)))
      (*dtp->doTextWrite.proc) (dtp, from, charsToWrite);
    else
      EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_notAvailable), (char *) "IOChan.TextWrite: attempt to write data to a channel which is not configured as write and text", 94);
}

void IOChan_RawRead (IOChan_ChanId cid, void * to, unsigned int maxLocs, unsigned int *locsRead)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Reads at most maxLocs items from cid, and assigns corresponding
     values to successive components of an ARRAY OF LOC variable for
     which the address of the first component is to. The number of
     characters read is assigned to locsRead. The stored read result
     is set to the value allRight, or endOfInput.
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.RawRead: device table ptr is NIL", 39);
  else
    if ((dtp->cid == (StdChans_NullChan ())) || (dtp->result == IOConsts_endOfInput))
      {
        (*locsRead) = 0;
        dtp->result = IOConsts_endOfInput;
      }
    else if (((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)) && ((((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)))
      (*dtp->doRawRead.proc) (dtp, to, maxLocs, locsRead);
    else
      EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_notAvailable), (char *) "IOChan.RawRead: attempt to read data from a channel which is not configured as read and raw", 91);
}

void IOChan_RawWrite (IOChan_ChanId cid, void * from, unsigned int locsToWrite)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Writes a number of items given by the value of charsToWrite,
     from successive components of an ARRAY OF LOC variable for
     which the address of the first component is from, to the channel cid.
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.RawWrite: device table ptr is NIL", 40);
  else
    if ((dtp->cid == (StdChans_NullChan ())) || (dtp->result == IOConsts_endOfInput))
      dtp->result = IOConsts_endOfInput;
    else if (((((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)) && ((((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (dtp->flags)) != 0)))
      (*dtp->doRawWrite.proc) (dtp, from, locsToWrite);
    else
      EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_notAvailable), (char *) "IOChan.RawWrite: attempt to write data to a channel which is not configured as write and raw", 92);
}

void IOChan_GetName (IOChan_ChanId cid, char *s, unsigned int _s_high)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Copies to s a name associated with the channel cid, possibly truncated
     (depending on the capacity of s).
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.GetName: device table ptr is NIL", 39);
  else
    (*dtp->doGetName.proc) (dtp, (char *) s, _s_high);
}

void IOChan_Reset (IOChan_ChanId cid)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Resets the channel cid to a state defined by the device module.  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.Reset: device table ptr is NIL", 37);
  else
    (*dtp->doReset.proc) (dtp);
}

void IOChan_Flush (IOChan_ChanId cid)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Flushes any data buffered by the device module out to the channel cid.  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.Flush: device table ptr is NIL", 37);
  else
    (*dtp->doFlush.proc) (dtp);
}

void IOChan_SetReadResult (IOChan_ChanId cid, IOConsts_ReadResults res)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Sets the read result value for the channel cid to the value res.  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.SetReadResult: device table ptr is NIL", 45);
  else
    dtp->result = res;
}

IOConsts_ReadResults IOChan_ReadResult (IOChan_ChanId cid)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Returns the stored read result value for the channel cid.
     (This is initially the value notKnown).
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.SetReadResult: device table ptr is NIL", 45);
  else
    return dtp->result;
  ReturnException ("/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/IOChan.def", 8, 1);
}

ChanConsts_FlagSet IOChan_CurrentFlags (IOChan_ChanId cid)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* Returns the set of flags that currently apply to the channel cid.  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.SetReadResult: device table ptr is NIL", 45);
  else
    return dtp->flags;
  ReturnException ("/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/IOChan.def", 8, 1);
}

unsigned int IOChan_IsChanException (void)
{
  /* Returns TRUE if the current coroutine is in the exceptional
     execution state because of the raising of an exception from
     ChanExceptions; otherwise returns FALSE.
  */
  return (EXCEPTIONS_IsExceptionalExecution ()) && (EXCEPTIONS_IsCurrentSource (iochan));
}

IOChan_ChanExceptions IOChan_ChanException (void)
{
  /* If the current coroutine is in the exceptional execution state
     because of the raising of an exception from ChanExceptions,
     returns the corresponding enumeration value, and otherwise
     raises an exception.
  */
  if (IOChan_IsChanException ())
    return (IOChan_ChanExceptions) (EXCEPTIONS_CurrentNumber (iochan));
  else
    M2RTS_NoException ("/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/IOChan.mod", 505, 24, "ChanException");
  ReturnException ("/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/IOChan.def", 8, 1);
}

IOChan_DeviceErrNum IOChan_DeviceError (IOChan_ChanId cid)
{
  IOLink_DeviceId did;
  IOLink_DeviceTablePtr dtp;

  /* If a device error exception has been raised for the channel cid,
     returns the error number stored by the device module.
  */
  CheckValid (cid);
  did = RTio_GetDeviceId ((RTio_ChanId) cid);
  dtp = IOLink_DeviceTablePtrValue (cid, did);
  if (dtp == NULL)
    EXCEPTIONS_RAISE (iochan, (EXCEPTIONS_ExceptionNumber) (unsigned int) (IOChan_hardDeviceError), (char *) "IOChan.DeviceError: device table ptr is NIL", 43);
  else
    return dtp->errNum;
  ReturnException ("/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/IOChan.def", 8, 1);
}

void _M2_IOChan_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  EXCEPTIONS_AllocateSource (&iochan);
  invalid = (IOChan_ChanId) (RTio_InitChanId ());
}

void _M2_IOChan_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
