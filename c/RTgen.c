/* automatically created by mc from ../git-pge/m2/RTgen.mod.  */

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
#include <stdlib.h>
#   include "GStorage.h"
typedef struct RTgenif_readchar_p RTgenif_readchar;

typedef struct IOLink_DeviceTable_r IOLink_DeviceTable;

typedef void *IOLink_DeviceData;

typedef IOLink_DeviceTable *IOLink_DeviceTablePtr;

typedef unsigned int FIO_File;

typedef struct _T5_r _T5;

typedef _T5 *RTio_ChanId;

typedef RTio_ChanId IOChan_ChanId;

typedef int IOChan_DeviceErrNum;

typedef struct IOLink_LookProc_p IOLink_LookProc;

typedef struct IOLink_SkipProc_p IOLink_SkipProc;

typedef struct IOLink_SkipLookProc_p IOLink_SkipLookProc;

typedef struct IOLink_WriteLnProc_p IOLink_WriteLnProc;

typedef struct IOLink_TextReadProc_p IOLink_TextReadProc;

typedef struct IOLink_TextWriteProc_p IOLink_TextWriteProc;

typedef struct IOLink_RawReadProc_p IOLink_RawReadProc;

typedef struct IOLink_RawWriteProc_p IOLink_RawWriteProc;

typedef struct IOLink_GetNameProc_p IOLink_GetNameProc;

typedef struct IOLink_ResetProc_p IOLink_ResetProc;

typedef struct IOLink_FlushProc_p IOLink_FlushProc;

typedef struct IOLink_FreeProc_p IOLink_FreeProc;

typedef struct RTgenif_unreadchar_p RTgenif_unreadchar;

typedef struct RTgenif_geterrno_p RTgenif_geterrno;

typedef struct RTgenif_readbytes_p RTgenif_readbytes;

typedef struct RTgenif_writebytes_p RTgenif_writebytes;

typedef struct RTgenif_writeln_p RTgenif_writeln;

typedef struct RTgenif_iseof_p RTgenif_iseof;

typedef struct RTgenif_iseoln_p RTgenif_iseoln;

typedef struct RTgenif_iserror_p RTgenif_iserror;

#   define SYSTEM_BITSPERBYTE 8
#   define SYSTEM_BYTESPERWORD 4
typedef unsigned int EXCEPTIONS_ExceptionNumber;

typedef struct _T6_r _T6;

typedef _T6 *EXCEPTIONS_ExceptionSource;

#   define ASCII_nul (char) 000
#   define ASCII_soh (char) 001
#   define ASCII_stx (char) 002
#   define ASCII_etx (char) 003
#   define ASCII_eot (char) 004
#   define ASCII_enq (char) 005
#   define ASCII_ack (char) 006
#   define ASCII_bel (char) 007
#   define ASCII_bs (char) 010
#   define ASCII_ht (char) 011
#   define ASCII_nl (char) 012
#   define ASCII_vt (char) 013
#   define ASCII_np (char) 014
#   define ASCII_cr (char) 015
#   define ASCII_so (char) 016
#   define ASCII_si (char) 017
#   define ASCII_dle (char) 020
#   define ASCII_dc1 (char) 021
#   define ASCII_dc2 (char) 022
#   define ASCII_dc3 (char) 023
#   define ASCII_dc4 (char) 024
#   define ASCII_nak (char) 025
#   define ASCII_syn (char) 026
#   define ASCII_etb (char) 027
#   define ASCII_can (char) 030
#   define ASCII_em (char) 031
#   define ASCII_sub (char) 032
#   define ASCII_esc (char) 033
#   define ASCII_fs (char) 034
#   define ASCII_gs (char) 035
#   define ASCII_rs (char) 036
#   define ASCII_us (char) 037
#   define ASCII_sp (char) 040
#   define ASCII_lf ASCII_nl
#   define ASCII_ff ASCII_np
#   define ASCII_eof ASCII_eot
#   define ASCII_tab ASCII_ht
#   define ASCII_del (char) 0177
#   define ASCII_EOL ASCII_nl
extern FIO_File FIO_StdErr;
extern FIO_File FIO_StdOut;
extern FIO_File FIO_StdIn;
#   define errno_EINTR 4
#   define errno_ERANGE 34
#   define errno_EAGAIN 11
typedef IOChan_ChanId StdChans_ChanId;

typedef long int libc_time_t;

typedef struct libc_tm_r libc_tm;

typedef libc_tm *libc_ptrToTM;

typedef struct libc_timeb_r libc_timeb;

typedef struct RTExceptions_ProcedureHandler_p RTExceptions_ProcedureHandler;

typedef struct _T7_r _T7;

typedef struct _T8_a _T8;

typedef _T7 *RTExceptions_EHBlock;

typedef struct SysExceptions_PROCEXCEPTION_p SysExceptions_PROCEXCEPTION;

typedef struct deviceExceptions_a deviceExceptions;

typedef struct _T1_r _T1;

typedef enum {RTgen_seqfile, RTgen_streamfile, RTgen_programargs, RTgen_stdchans, RTgen_term, RTgen_socket, RTgen_rndfile} RTgen_DeviceType;

typedef enum {IOConsts_notKnown, IOConsts_allRight, IOConsts_outOfRange, IOConsts_wrongFormat, IOConsts_endOfLine, IOConsts_endOfInput} IOConsts_ReadResults;

typedef unsigned int ChanConsts_FlagSet;

typedef enum {ChanConsts_readFlag, ChanConsts_writeFlag, ChanConsts_oldFlag, ChanConsts_textFlag, ChanConsts_rawFlag, ChanConsts_interactiveFlag, ChanConsts_echoFlag} ChanConsts_ChanFlags;

#   define ChanConsts_read (ChanConsts_FlagSet) ((1 << (ChanConsts_readFlag-ChanConsts_readFlag)))
#   define ChanConsts_write (ChanConsts_FlagSet) ((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)))
#   define ChanConsts_old (ChanConsts_FlagSet) ((1 << (ChanConsts_oldFlag-ChanConsts_readFlag)))
#   define ChanConsts_text (ChanConsts_FlagSet) ((1 << (ChanConsts_textFlag-ChanConsts_readFlag)))
#   define ChanConsts_raw (ChanConsts_FlagSet) ((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)))
#   define ChanConsts_interactive (ChanConsts_FlagSet) ((1 << (ChanConsts_interactiveFlag-ChanConsts_readFlag)))
#   define ChanConsts_echo (ChanConsts_FlagSet) ((1 << (ChanConsts_echoFlag-ChanConsts_readFlag)))
typedef enum {IOChan_wrongDevice, IOChan_notAvailable, IOChan_skipAtEnd, IOChan_softDeviceError, IOChan_hardDeviceError, IOChan_textParseError, IOChan_notAChannel} IOChan_ChanExceptions;

typedef IOChan_ChanExceptions IOLink_DevExceptionRange;

typedef enum {ChanConsts_opened, ChanConsts_wrongNameFormat, ChanConsts_wrongFlags, ChanConsts_tooManyOpen, ChanConsts_outOfChans, ChanConsts_wrongPermissions, ChanConsts_noRoomOnDevice, ChanConsts_noSuchFile, ChanConsts_fileExists, ChanConsts_wrongFileType, ChanConsts_noTextOperations, ChanConsts_noRawOperations, ChanConsts_noMixedOperations, ChanConsts_alreadyOpen, ChanConsts_otherProblem} ChanConsts_OpenResults;

#   define MaxBuffer 4096
typedef enum {M2EXCEPTION_indexException, M2EXCEPTION_rangeException, M2EXCEPTION_caseSelectException, M2EXCEPTION_invalidLocation, M2EXCEPTION_functionException, M2EXCEPTION_wholeValueException, M2EXCEPTION_wholeDivException, M2EXCEPTION_realValueException, M2EXCEPTION_realDivException, M2EXCEPTION_complexValueException, M2EXCEPTION_complexDivException, M2EXCEPTION_protException, M2EXCEPTION_sysException, M2EXCEPTION_coException, M2EXCEPTION_exException} M2EXCEPTION_M2Exceptions;

typedef _T1 *RTgen_ChanDev;

typedef void (*IOLink_LookProc_t) (IOLink_DeviceTablePtr, char *, IOConsts_ReadResults *);
struct IOLink_LookProc_p { IOLink_LookProc_t proc; };

typedef void (*IOLink_SkipProc_t) (IOLink_DeviceTablePtr);
struct IOLink_SkipProc_p { IOLink_SkipProc_t proc; };

typedef void (*IOLink_SkipLookProc_t) (IOLink_DeviceTablePtr, char *, IOConsts_ReadResults *);
struct IOLink_SkipLookProc_p { IOLink_SkipLookProc_t proc; };

typedef void (*IOLink_WriteLnProc_t) (IOLink_DeviceTablePtr);
struct IOLink_WriteLnProc_p { IOLink_WriteLnProc_t proc; };

typedef void (*IOLink_TextReadProc_t) (IOLink_DeviceTablePtr, void *, unsigned int, unsigned int *);
struct IOLink_TextReadProc_p { IOLink_TextReadProc_t proc; };

typedef void (*IOLink_TextWriteProc_t) (IOLink_DeviceTablePtr, void *, unsigned int);
struct IOLink_TextWriteProc_p { IOLink_TextWriteProc_t proc; };

typedef void (*IOLink_RawReadProc_t) (IOLink_DeviceTablePtr, void *, unsigned int, unsigned int *);
struct IOLink_RawReadProc_p { IOLink_RawReadProc_t proc; };

typedef void (*IOLink_RawWriteProc_t) (IOLink_DeviceTablePtr, void *, unsigned int);
struct IOLink_RawWriteProc_p { IOLink_RawWriteProc_t proc; };

typedef void (*IOLink_GetNameProc_t) (IOLink_DeviceTablePtr, char *, unsigned int);
struct IOLink_GetNameProc_p { IOLink_GetNameProc_t proc; };

typedef void (*IOLink_ResetProc_t) (IOLink_DeviceTablePtr);
struct IOLink_ResetProc_p { IOLink_ResetProc_t proc; };

typedef void (*IOLink_FlushProc_t) (IOLink_DeviceTablePtr);
struct IOLink_FlushProc_p { IOLink_FlushProc_t proc; };

typedef void (*IOLink_FreeProc_t) (IOLink_DeviceTablePtr);
struct IOLink_FreeProc_p { IOLink_FreeProc_t proc; };

struct _T6_r {
               RTExceptions_EHBlock eh;
             };

struct libc_tm_r {
                   int tm_sec;
                   int tm_min;
                   int tm_hour;
                   int tm_mday;
                   int tm_mon;
                   int tm_year;
                   int tm_wday;
                   int tm_yday;
                   int tm_isdst;
                   long int tm_gmtoff;
                   void *tm_zone;
                 };

struct libc_timeb_r {
                      libc_time_t time;
                      short unsigned int millitm;
                      short unsigned int timezone;
                      short unsigned int dstflag;
                    };

typedef void (*RTExceptions_ProcedureHandler_t) (void);
struct RTExceptions_ProcedureHandler_p { RTExceptions_ProcedureHandler_t proc; };

struct _T8_a { char array[MaxBuffer+1]; };
typedef void (*SysExceptions_PROCEXCEPTION_t) (void *);
struct SysExceptions_PROCEXCEPTION_p { SysExceptions_PROCEXCEPTION_t proc; };

struct deviceExceptions_a { unsigned int array[RTgen_rndfile-RTgen_seqfile+1]; };
typedef struct _T2_r _T2;

typedef struct _T3_r _T3;

typedef struct _T4_r _T4;

typedef _T2 *IOLink_DeviceId;

typedef struct _T9_r _T9;

typedef _T9 *Handler;

typedef _T3 *RTentity_Group;

typedef _T4 *RTgenif_GenDevIF;

typedef char (*RTgenif_readchar_t) (RTgenif_GenDevIF, IOLink_DeviceTablePtr);
struct RTgenif_readchar_p { RTgenif_readchar_t proc; };

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

struct _T5_r {
               IOLink_DeviceId did;
               IOLink_DeviceTablePtr dtp;
               FIO_File file;
             };

struct _T2_r {
               RTentity_Group cids;
             };

struct _T3_r {
               RTentity_Group left;
               RTentity_Group right;
               void *entity;
               unsigned int entityKey;
             };

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

struct _T9_r {
               RTExceptions_ProcedureHandler p;
               unsigned int n;
               Handler right;
               Handler left;
               Handler stack;
             };

struct _T7_r {
               _T8 buffer;
               unsigned int number;
               Handler handlers;
               RTExceptions_EHBlock right;
             };

struct _T1_r {
               RTgen_DeviceType type;
               IOLink_DeviceId did;
               RTgenif_GenDevIF genif;
             };

struct _T4_r {
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

static deviceExceptions raiseEofInLook;
static deviceExceptions raiseEofInSkip;
void SYSTEM_ShiftVal (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, int ShiftCount);
void SYSTEM_ShiftLeft (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, unsigned int ShiftCount);
void SYSTEM_ShiftRight (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, unsigned int ShiftCount);
void SYSTEM_RotateVal (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, int RotateCount);
void SYSTEM_RotateLeft (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, unsigned int RotateCount);
void SYSTEM_RotateRight (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, unsigned int RotateCount);
void M2RTS_ExecuteTerminationProcedures (void);
unsigned int M2RTS_InstallTerminationProcedure (PROC p);
void M2RTS_ExecuteInitialProcedures (void);
unsigned int M2RTS_InstallInitialProcedure (PROC p);
void M2RTS_Terminate (void);
void M2RTS_HALT (int exitcode);
void M2RTS_Halt (char *file_, unsigned int _file_high, unsigned int line, char *function_, unsigned int _function_high, char *description_, unsigned int _description_high);
void M2RTS_ExitOnHalt (int e);
void M2RTS_ErrorMessage (char *message_, unsigned int _message_high, char *file_, unsigned int _file_high, unsigned int line, char *function_, unsigned int _function_high);
unsigned int M2RTS_Length (char *a_, unsigned int _a_high);
void M2RTS_AssignmentException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ReturnException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_IncException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_DecException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_InclException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ExclException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ShiftException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_RotateException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_StaticArraySubscriptException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_DynamicArraySubscriptException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ForLoopBeginException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ForLoopToException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ForLoopEndException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_PointerNilException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_NoReturnException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_CaseException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeNonPosDivException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeNonPosModException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeZeroDivException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeZeroRemException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeValueException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_RealValueException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_NoException (void * filename, unsigned int line, unsigned int column, void * scope);

/*
   InitChanDev - initialize and return a ChanDev.
*/

RTgen_ChanDev RTgen_InitChanDev (RTgen_DeviceType t, IOLink_DeviceId d, RTgenif_GenDevIF g);

/*
   KillChanDev - deallocates, g.
*/

RTgenif_GenDevIF RTgen_KillChanDev (RTgenif_GenDevIF g);

/*
   RaiseEOFinLook - returns TRUE if the Look procedure
                    should raise an exception if it
                    sees end of file.
*/

unsigned int RTgen_RaiseEOFinLook (RTgen_ChanDev g);

/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

unsigned int RTgen_RaiseEOFinSkip (RTgen_ChanDev g);

/*
   doLook - if there is a character as the next item in
            the input stream then it assigns its value
            to ch without removing it from the stream;
            otherwise the value of ch is not defined.
            r and result are set to the value allRight,
            endOfLine, or endOfInput.
*/

void RTgen_doLook (RTgen_ChanDev g, IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);

/*
   doSkip - 
*/

void RTgen_doSkip (RTgen_ChanDev g, IOLink_DeviceTablePtr d);

/*
   doSkip - 
*/

void RTgen_doSkipLook (RTgen_ChanDev g, IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r);

/*
   doSkip - 
*/

void RTgen_doWriteLn (RTgen_ChanDev g, IOLink_DeviceTablePtr d);

/*
   doSkip - 
*/

void RTgen_doReadText (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * to, unsigned int maxChars, unsigned int *charsRead);
void RTgen_doWriteText (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * from, unsigned int charsToWrite);
void RTgen_doReadLocs (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * to, unsigned int maxLocs, unsigned int *locsRead);
void RTgen_doWriteLocs (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * from, unsigned int locsToWrite);

/*
   checkErrno - checks a number of errno conditions and raises
                appropriate ISO exceptions if they occur.
*/

void RTgen_checkErrno (RTgen_ChanDev g, IOLink_DeviceTablePtr d);
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
void IOLink_AllocateDeviceId (IOLink_DeviceId *did);
void IOLink_MakeChan (IOLink_DeviceId did, IOChan_ChanId *cid);
void IOLink_UnMakeChan (IOLink_DeviceId did, IOChan_ChanId *cid);
IOLink_DeviceTablePtr IOLink_DeviceTablePtrValue (IOChan_ChanId cid, IOLink_DeviceId did);
unsigned int IOLink_IsDevice (IOChan_ChanId cid, IOLink_DeviceId did);
void IOLink_RAISEdevException (IOChan_ChanId cid, IOLink_DeviceId did, IOLink_DevExceptionRange x, char *s_, unsigned int _s_high);
unsigned int IOLink_IsIOException (void);
IOChan_ChanExceptions IOLink_IOException (void);
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
unsigned int ErrnoCategory_IsErrnoHard (int e);
unsigned int ErrnoCategory_IsErrnoSoft (int e);
unsigned int ErrnoCategory_UnAvailable (int e);
ChanConsts_OpenResults ErrnoCategory_GetOpenResults (int e);
void Storage_ALLOCATE (void * *a, unsigned int Size);
void Storage_DEALLOCATE (void * *a, unsigned int Size);
void Storage_REALLOCATE (void * *a, unsigned int Size);
unsigned int Storage_Available (unsigned int Size);

/*
   InitChanId - return a new ChanId.
*/

RTio_ChanId RTio_InitChanId (void);
RTio_ChanId RTio_KillChanId (RTio_ChanId c);

/*
   NilChanId - return a NIL pointer.
*/

RTio_ChanId RTio_NilChanId (void);

/*
   GetDeviceId - returns the device id, from, c.
*/

IOLink_DeviceId RTio_GetDeviceId (RTio_ChanId c);

/*
   SetDeviceId - returns the device id, from, c.
*/

void RTio_SetDeviceId (RTio_ChanId c, IOLink_DeviceId d);

/*
   GetDevicePtr - returns the device table ptr, from, c.
*/

IOLink_DeviceTablePtr RTio_GetDevicePtr (RTio_ChanId c);

/*
   SetDevicePtr - sets the device table ptr in, c.
*/

void RTio_SetDevicePtr (RTio_ChanId c, IOLink_DeviceTablePtr p);

/*
   GetFile - returns the file field from, c.
*/

FIO_File RTio_GetFile (RTio_ChanId c);

/*
   SetFile - sets the file field in, c.
*/

void RTio_SetFile (RTio_ChanId c, FIO_File f);
RTentity_Group RTentity_InitGroup (void);
RTentity_Group RTentity_KillGroup (RTentity_Group g);
unsigned int RTentity_GetKey (RTentity_Group g, void * a);
void RTentity_PutKey (RTentity_Group g, void * a, unsigned int key);

/*
   DelKey - deletes an entry in the binary tree.

            NB in order for this to work we must
            ensure that the InitGroup sets
            both left and right to NIL.
*/

void RTentity_DelKey (RTentity_Group g, void * a);
unsigned int RTentity_IsIn (RTentity_Group g, void * a);
void EXCEPTIONS_AllocateSource (EXCEPTIONS_ExceptionSource *newSource);
void EXCEPTIONS_RAISE (EXCEPTIONS_ExceptionSource source, EXCEPTIONS_ExceptionNumber number, char *message_, unsigned int _message_high);
EXCEPTIONS_ExceptionNumber EXCEPTIONS_CurrentNumber (EXCEPTIONS_ExceptionSource source);
void EXCEPTIONS_GetMessage (char *text, unsigned int _text_high);
unsigned int EXCEPTIONS_IsCurrentSource (EXCEPTIONS_ExceptionSource source);
unsigned int EXCEPTIONS_IsExceptionalExecution (void);
unsigned int FIO_IsNoError (FIO_File f);
unsigned int FIO_IsActive (FIO_File f);
unsigned int FIO_Exists (char *fname_, unsigned int _fname_high);
FIO_File FIO_OpenToRead (char *fname_, unsigned int _fname_high);
FIO_File FIO_OpenToWrite (char *fname_, unsigned int _fname_high);
FIO_File FIO_OpenForRandom (char *fname_, unsigned int _fname_high, unsigned int towrite, unsigned int newfile);
void FIO_Close (FIO_File f);
unsigned int FIO_exists (void * fname, unsigned int flength);
FIO_File FIO_openToRead (void * fname, unsigned int flength);
FIO_File FIO_openToWrite (void * fname, unsigned int flength);
FIO_File FIO_openForRandom (void * fname, unsigned int flength, unsigned int towrite, unsigned int newfile);
void FIO_FlushBuffer (FIO_File f);
unsigned int FIO_ReadNBytes (FIO_File f, unsigned int nBytes, void * a);
void FIO_ReadAny (FIO_File f, unsigned char *a, unsigned int _a_high);
unsigned int FIO_WriteNBytes (FIO_File f, unsigned int nBytes, void * a);
void FIO_WriteAny (FIO_File f, unsigned char *a, unsigned int _a_high);
void FIO_WriteChar (FIO_File f, char ch);
unsigned int FIO_EOF (FIO_File f);
unsigned int FIO_EOLN (FIO_File f);
unsigned int FIO_WasEOLN (FIO_File f);
char FIO_ReadChar (FIO_File f);
void FIO_UnReadChar (FIO_File f, char ch);
void FIO_WriteLine (FIO_File f);
void FIO_WriteString (FIO_File f, char *a_, unsigned int _a_high);
void FIO_ReadString (FIO_File f, char *a, unsigned int _a_high);
void FIO_WriteCardinal (FIO_File f, unsigned int c);
unsigned int FIO_ReadCardinal (FIO_File f);
int FIO_GetUnixFileDescriptor (FIO_File f);
void FIO_SetPositionFromBeginning (FIO_File f, long int pos);
void FIO_SetPositionFromEnd (FIO_File f, long int pos);
long int FIO_FindPosition (FIO_File f);
void FIO_GetFileName (FIO_File f, char *a, unsigned int _a_high);
void * FIO_getFileName (FIO_File f);
unsigned int FIO_getFileNameLength (FIO_File f);
void FIO_FlushOutErr (void);
M2EXCEPTION_M2Exceptions M2EXCEPTION_M2Exception (void);
unsigned int M2EXCEPTION_IsM2Exception (void);
int errno_geterrno (void);
StdChans_ChanId StdChans_StdInChan (void);
StdChans_ChanId StdChans_StdOutChan (void);
StdChans_ChanId StdChans_StdErrChan (void);
StdChans_ChanId StdChans_NullChan (void);
StdChans_ChanId StdChans_InChan (void);
StdChans_ChanId StdChans_OutChan (void);
StdChans_ChanId StdChans_ErrChan (void);
void StdChans_SetInChan (StdChans_ChanId cid);
void StdChans_SetOutChan (StdChans_ChanId cid);
void StdChans_SetErrChan (StdChans_ChanId cid);
ssize_t libc_write (int d, void * buf, size_t nbytes);
ssize_t libc_read (int d, void * buf, size_t nbytes);
int libc_system (void * a);
void libc_abort (void);
void * libc_malloc (size_t size);
void libc_free (void * ptr);
void * libc_realloc (void * ptr, size_t size);
int libc_isatty (int fd);
void libc_exit (int r);
void * libc_getenv (void * s);
int libc_getpid (void);
int libc_dup (int d);
int libc_close (int d);
int libc_open (void * filename, int oflag, ...);
int libc_creat (void * filename, unsigned int mode);
long int libc_lseek (int fd, long int offset, int whence);
void libc_perror (char *string_, unsigned int _string_high);
int libc_readv (int fd, void * v, int n);
int libc_writev (int fd, void * v, int n);
void * libc_getcwd (void * buf, size_t size);
int libc_chown (void * filename, int uid, int gid);
size_t libc_strlen (void * a);
void * libc_strcpy (void * dest, void * src);
void * libc_strncpy (void * dest, void * src, unsigned int n);
int libc_unlink (void * file);
void * libc_memcpy (void * dest, void * src, size_t size);
void * libc_memset (void * s, int c, size_t size);
void * libc_memmove (void * dest, void * src, size_t size);
int libc_printf (char *format_, unsigned int _format_high, ...);
int libc_setenv (void * name, void * value, int overwrite);
void libc_srand (int seed);
int libc_rand (void);
libc_time_t libc_time (void * a);
void * libc_localtime (libc_time_t *t);
int libc_ftime (libc_timeb *t);
int libc_shutdown (int s, int how);
int libc_rename (void * oldpath, void * newpath);
int libc_setjmp (void * env);
void libc_longjmp (void * env, int val);
void libc_atexit (PROC proc);
void * libc_ttyname (int filedes);
unsigned int libc_sleep (unsigned int seconds);

/*
   Raise - invoke the exception handler associated with, number,
           in the active EHBlock.  It keeps a record of the number
           and message in the EHBlock for later use.
*/

void RTExceptions_Raise (unsigned int number, void * file, unsigned int line, unsigned int column, void * function, void * message);

/*
   SetExceptionBlock - sets, source, as the active EHB.
*/

void RTExceptions_SetExceptionBlock (RTExceptions_EHBlock source);

/*
   GetExceptionBlock - returns the active EHB.
*/

RTExceptions_EHBlock RTExceptions_GetExceptionBlock (void);

/*
   GetTextBuffer - returns the address of the EHB buffer.
*/

void * RTExceptions_GetTextBuffer (RTExceptions_EHBlock e);

/*
   GetTextBufferSize - return the size of the EHB text buffer.
*/

unsigned int RTExceptions_GetTextBufferSize (RTExceptions_EHBlock e);

/*
   GetNumber - return the exception number associated with,
               source.
*/

unsigned int RTExceptions_GetNumber (RTExceptions_EHBlock source);

/*
   InitExceptionBlock - creates and returns a new exception block.
*/

RTExceptions_EHBlock RTExceptions_InitExceptionBlock (void);

/*
   KillExceptionBlock - destroys the EHB, e, and all its handlers.
*/

RTExceptions_EHBlock RTExceptions_KillExceptionBlock (RTExceptions_EHBlock e);

/*
   PushHandler - install a handler in EHB, e.
*/

void RTExceptions_PushHandler (RTExceptions_EHBlock e, unsigned int number, RTExceptions_ProcedureHandler p);

/*
   PopHandler - removes the handler associated with, number, from
                EHB, e.
*/

void RTExceptions_PopHandler (RTExceptions_EHBlock e, unsigned int number);

/*
   DefaultErrorCatch - displays the current error message in
                       the current exception block and then
                       calls HALT.
*/

void RTExceptions_DefaultErrorCatch (void);

/*
   BaseExceptionsThrow - configures the Modula-2 exceptions to call
                         THROW which in turn can be caught by an
                         exception block.  If this is not called then
                         a Modula-2 exception will simply call an
                         error message routine and then HALT.
*/

void RTExceptions_BaseExceptionsThrow (void);

/*
   IsInExceptionState - returns TRUE if the program is currently
                        in the exception state.
*/

unsigned int RTExceptions_IsInExceptionState (void);

/*
   SetExceptionState - returns the current exception state and
                       then sets the current exception state to,
                       to.
*/

unsigned int RTExceptions_SetExceptionState (unsigned int to);

/*
   SwitchExceptionState - assigns, from, with the current exception
                          state and then assigns the current exception
                          to, to.
*/

void RTExceptions_SwitchExceptionState (unsigned int *from, unsigned int to);

/*
   GetBaseExceptionBlock - returns the initial language exception block
                           created.
*/

RTExceptions_EHBlock RTExceptions_GetBaseExceptionBlock (void);

/*
   SetExceptionSource - sets the current exception source to, source.
*/

void RTExceptions_SetExceptionSource (void * source);

/*
   GetExceptionSource - returns the current exception source.
*/

void * RTExceptions_GetExceptionSource (void);
void StrLib_StrConCat (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high, char *c, unsigned int _c_high);
unsigned int StrLib_StrLess (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high);
unsigned int StrLib_StrEqual (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high);
unsigned int StrLib_StrLen (char *a_, unsigned int _a_high);
void StrLib_StrCopy (char *a_, unsigned int _a_high, char *b, unsigned int _b_high);
unsigned int StrLib_IsSubString (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high);
void StrLib_StrRemoveWhitePrefix (char *a_, unsigned int _a_high, char *b, unsigned int _b_high);
void SysExceptions_InitExceptionHandlers (SysExceptions_PROCEXCEPTION indexf, SysExceptions_PROCEXCEPTION range, SysExceptions_PROCEXCEPTION casef, SysExceptions_PROCEXCEPTION invalidloc, SysExceptions_PROCEXCEPTION function, SysExceptions_PROCEXCEPTION wholevalue, SysExceptions_PROCEXCEPTION wholediv, SysExceptions_PROCEXCEPTION realvalue, SysExceptions_PROCEXCEPTION realdiv, SysExceptions_PROCEXCEPTION complexvalue, SysExceptions_PROCEXCEPTION complexdiv, SysExceptions_PROCEXCEPTION protection, SysExceptions_PROCEXCEPTION systemf, SysExceptions_PROCEXCEPTION coroutine, SysExceptions_PROCEXCEPTION exception);
static void checkValid (RTgen_ChanDev g, IOLink_DeviceTablePtr d);

/*
   checkErrno - checks a number of errno conditions and raises
                appropriate ISO exceptions if they occur.
*/

static void checkPreRead (RTgen_ChanDev g, IOLink_DeviceTablePtr d, unsigned int raise, unsigned int raw);

/*
   checkPostRead - only checks whether an error occurred.
                   The result is not set as the result is
                   set prior to a read occuring.
*/

static void checkPostRead (RTgen_ChanDev g, IOLink_DeviceTablePtr d);
static void checkPreWrite (RTgen_ChanDev g, IOLink_DeviceTablePtr d);
static void checkPostWrite (RTgen_ChanDev g, IOLink_DeviceTablePtr d);

/*
   checkFlags - checks read/write  raw/text consistancy flags.
*/

static void checkFlags (ChanConsts_FlagSet f, IOLink_DeviceTablePtr d);

static void checkValid (RTgen_ChanDev g, IOLink_DeviceTablePtr d)
{
  /* internal routine to check whether we have a valid channel  */
  if ((RTgenif_getDID (g->genif)) != d->did)
    IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "operation attempted on an invalid channel", 41);
  if ((d->cid == (IOChan_InvalidChan ())) || (d->cid == NULL))
    IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "operation attempted on an invalid channel", 41);
  if (d != (IOLink_DeviceTablePtrValue (d->cid, d->did)))
    IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "operation attempted on an invalid channel", 41);
}


/*
   checkErrno - checks a number of errno conditions and raises
                appropriate ISO exceptions if they occur.
*/

static void checkPreRead (RTgen_ChanDev g, IOLink_DeviceTablePtr d, unsigned int raise, unsigned int raw)
{
  if (RTgenif_isEOF (g->genif, d))
    {
      d->result = IOConsts_endOfInput;
      if (raise)
        IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_skipAtEnd, (char *) "attempting to read beyond end of file", 37);
    }
  else if (! raw && (RTgenif_isEOLN (g->genif, d)))
    d->result = IOConsts_endOfLine;
  else
    d->result = IOConsts_allRight;
}


/*
   checkPostRead - only checks whether an error occurred.
                   The result is not set as the result is
                   set prior to a read occuring.
*/

static void checkPostRead (RTgen_ChanDev g, IOLink_DeviceTablePtr d)
{
  RTgen_checkErrno (g, d);
}

static void checkPreWrite (RTgen_ChanDev g, IOLink_DeviceTablePtr d)
{
}

static void checkPostWrite (RTgen_ChanDev g, IOLink_DeviceTablePtr d)
{
  /* nothing to do  */
  RTgen_checkErrno (g, d);
}


/*
   checkFlags - checks read/write  raw/text consistancy flags.
*/

static void checkFlags (ChanConsts_FlagSet f, IOLink_DeviceTablePtr d)
{
  if (((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (f)) != 0)) && (! ((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (d->flags)) != 0))))
    IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "attempting to read from a channel which was configured to write", 63);
  if (((((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)) & (f)) != 0)) && (! ((((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)) & (d->flags)) != 0))))
    IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_wrongDevice, (char *) "attempting to write to a channel which was configured to read", 61);
  if (((((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (f)) != 0)) && (! ((((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (d->flags)) != 0))))
    {
      /* avoid gcc warning by using compound statement even if not strictly necessary.  */
      if ((((1 << (ChanConsts_readFlag-ChanConsts_readFlag)) & (d->flags)) != 0))
        IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "attempting to read raw LOCs from a channel which was configured to read text", 76);
      else
        IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "attempting to write raw LOCs from a channel which was configured to write text", 78);
    }
}


/*
   InitChanDev - initialize and return a ChanDev.
*/

RTgen_ChanDev RTgen_InitChanDev (RTgen_DeviceType t, IOLink_DeviceId d, RTgenif_GenDevIF g)
{
  RTgen_ChanDev c;

  Storage_ALLOCATE ((void **) &c, sizeof (_T1));
  c->type = t;
  c->did = d;
  c->genif = g;
  return c;
}


/*
   KillChanDev - deallocates, g.
*/

RTgenif_GenDevIF RTgen_KillChanDev (RTgenif_GenDevIF g)
{
  Storage_DEALLOCATE ((void **) &g, sizeof (_T4));
  return NULL;
}


/*
   RaiseEOFinLook - returns TRUE if the Look procedure
                    should raise an exception if it
                    sees end of file.
*/

unsigned int RTgen_RaiseEOFinLook (RTgen_ChanDev g)
{
  return raiseEofInLook.array[g->type-RTgen_seqfile];
}


/*
   RaiseEOFinSkip - returns TRUE if the Skip procedure
                    should raise an exception if it
                    sees end of file.
*/

unsigned int RTgen_RaiseEOFinSkip (RTgen_ChanDev g)
{
  return raiseEofInSkip.array[g->type-RTgen_seqfile];
}


/*
   doLook - if there is a character as the next item in
            the input stream then it assigns its value
            to ch without removing it from the stream;
            otherwise the value of ch is not defined.
            r and result are set to the value allRight,
            endOfLine, or endOfInput.
*/

void RTgen_doLook (RTgen_ChanDev g, IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r)
{
  checkValid (g, d);
  RTgen_checkErrno (g, d);
  checkPreRead (g, d, RTgen_RaiseEOFinLook (g), (((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (d->flags)) != 0));
  if (((d->result == IOConsts_allRight) || (d->result == IOConsts_notKnown)) || (d->result == IOConsts_endOfLine))
    {
      (*ch) = RTgenif_doReadChar (g->genif, d);
      if (RTgenif_isEOF (g->genif, d))
        d->result = IOConsts_endOfInput;
      else
        {
          (*ch) = RTgenif_doUnReadChar (g->genif, d, (*ch));
          checkPostRead (g, d);
        }
    }
  (*r) = d->result;
}


/*
   doSkip - 
*/

void RTgen_doSkip (RTgen_ChanDev g, IOLink_DeviceTablePtr d)
{
  char ch;

  checkValid (g, d);
  checkPreRead (g, d, RTgen_RaiseEOFinSkip (g), (((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)) & (d->flags)) != 0));
  ch = RTgenif_doReadChar (g->genif, d);
  checkPostRead (g, d);
}


/*
   doSkip - 
*/

void RTgen_doSkipLook (RTgen_ChanDev g, IOLink_DeviceTablePtr d, char *ch, IOConsts_ReadResults *r)
{
  checkValid (g, d);
  RTgen_doLook (g, d, ch, &d->result);
  if (((d->result == IOConsts_allRight) || (d->result == IOConsts_notKnown)) || (d->result == IOConsts_endOfLine))
    {
      (*ch) = RTgenif_doUnReadChar (g->genif, d, (*ch));
      checkPostRead (g, d);
    }
  (*r) = d->result;
}


/*
   doSkip - 
*/

void RTgen_doWriteLn (RTgen_ChanDev g, IOLink_DeviceTablePtr d)
{
  checkValid (g, d);
  checkPreWrite (g, d);
  if (RTgenif_doWrLn (g->genif, d))
    {}  /* empty.  */
  checkPostWrite (g, d);
}


/*
   doSkip - 
*/

void RTgen_doReadText (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * to, unsigned int maxChars, unsigned int *charsRead)
{
  unsigned int i;

  checkValid (g, d);
  checkFlags (ChanConsts_read|ChanConsts_text, d);
  if (maxChars > 0)
    {
      d->flags |= (1 << (ChanConsts_textFlag-ChanConsts_readFlag ));
      checkPreRead (g, d, FALSE, FALSE);
      (*charsRead) = 0;
      do {
        if (RTgenif_doRBytes (g->genif, d, to, maxChars, &i))
          {
            (*charsRead) += i;
            to += i;
            maxChars -= i;
          }
        else
          {
            RTgen_checkErrno (g, d);
            /* if our target system does not support errno then we  */
            IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "textread unrecoverable errno", 28);
          }
      } while (! ((maxChars == 0) || (RTgenif_isEOF (g->genif, d))));
      checkPostRead (g, d);
    }
}

void RTgen_doWriteText (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * from, unsigned int charsToWrite)
{
  unsigned int i;

  checkValid (g, d);
  checkFlags (ChanConsts_write|ChanConsts_text, d);
  checkPreWrite (g, d);
  d->flags |= (1 << (ChanConsts_textFlag-ChanConsts_readFlag ));
  while ((charsToWrite > 0) && (RTgenif_doWBytes (g->genif, d, from, charsToWrite, &i)))
    {
      from += i;
      charsToWrite -= i;
    }
  if (RTgenif_isError (g->genif, d))
    {
      RTgen_checkErrno (g, d);
      /* if our target system does not support errno then we  */
      IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "textwrite unrecoverable errno", 29);
    }
  checkPostWrite (g, d);
}

void RTgen_doReadLocs (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * to, unsigned int maxLocs, unsigned int *locsRead)
{
  unsigned int i;

  checkValid (g, d);
  checkFlags (ChanConsts_read|ChanConsts_raw, d);
  if (maxLocs > 0)
    {
      d->flags |= (1 << (ChanConsts_rawFlag-ChanConsts_readFlag ));
      checkPreRead (g, d, FALSE, TRUE);
      (*locsRead) = 0;
      do {
        if (RTgenif_doRBytes (g->genif, d, to, maxLocs, &i))
          {
            (*locsRead) += i;
            to += i;
            maxLocs -= i;
          }
        else
          {
            RTgen_checkErrno (g, d);
            /* if our target system does not support errno then we  */
            IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "rawread unrecoverable errno", 27);
          }
      } while (! ((maxLocs == 0) || (RTgenif_isEOF (g->genif, d))));
      checkPostRead (g, d);
    }
}

void RTgen_doWriteLocs (RTgen_ChanDev g, IOLink_DeviceTablePtr d, void * from, unsigned int locsToWrite)
{
  unsigned int i;

  checkValid (g, d);
  checkFlags (ChanConsts_write|ChanConsts_raw, d);
  checkPreWrite (g, d);
  d->flags |= (1 << (ChanConsts_rawFlag-ChanConsts_readFlag ));
  while ((RTgenif_doWBytes (g->genif, d, from, locsToWrite, &i)) && (i < locsToWrite))
    {
      from += i;
      locsToWrite -= i;
    }
  if (RTgenif_isError (g->genif, d))
    {
      RTgen_checkErrno (g, d);
      /* if our target system does not support errno then we  */
      IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "rawwrite unrecoverable errno", 28);
    }
  checkPostWrite (g, d);
}


/*
   checkErrno - checks a number of errno conditions and raises
                appropriate ISO exceptions if they occur.
*/

void RTgen_checkErrno (RTgen_ChanDev g, IOLink_DeviceTablePtr d)
{
  if (RTgenif_isError (g->genif, d))
    {
      d->errNum = RTgenif_doGetErrno (g->genif, d);
      if (ErrnoCategory_IsErrnoHard ((int) d->errNum))
        IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "unrecoverable (errno)", 21);
      else if (ErrnoCategory_UnAvailable ((int) d->errNum))
        IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "unavailable (errno)", 19);
      else if (d->errNum > 0)
        IOLink_RAISEdevException (d->cid, d->did, (IOLink_DevExceptionRange) IOChan_notAvailable, (char *) "recoverable (errno)", 19);
    }
}

void _M2_RTgen_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  /* seqfile, streamfile, programargs, stdchans, term , socket, rndfile  */
  raiseEofInLook = (deviceExceptions) ((1 << (FALSE)));
  raiseEofInSkip = (deviceExceptions) ((1 << (TRUE)));
}

void _M2_RTgen_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
