/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod.  */

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
#define _COROUTINES_H
#define _COROUTINES_C

#   include "Gpth.h"
#   include "GRTExceptions.h"
#   include "GSYSTEM.h"
#   include "GEXCEPTIONS.h"
#   include "GRTint.h"
#   include "GStorage.h"
#   include "GM2RTS.h"
#   include "Glibc.h"

#   define COROUTINES_UnassignedPriority 0
typedef unsigned int COROUTINES_INTERRUPTSOURCE;

typedef unsigned int COROUTINES_PROTECTION;

#   define MinStack ((8*16)*1024)
typedef struct _T1_r _T1;

typedef _T1 *COROUTINES_COROUTINE;

typedef struct _T2_r _T2;

typedef _T2 *SourceList;

typedef enum {suspended, ready, new, running} Status;

struct _T1_r {
               void *context;
               RTExceptions_EHBlock ehblock;
               unsigned int inexcept;
               EXCEPTIONS_ExceptionSource source;
               void *wspace;
               unsigned int nLocs;
               Status status;
               COROUTINES_PROTECTION protection;
               SourceList attached;
               COROUTINES_COROUTINE next;
             };

struct _T2_r {
               SourceList next;
               COROUTINES_INTERRUPTSOURCE vec;
               COROUTINES_COROUTINE curco;
               SourceList chain;
               COROUTINES_COROUTINE *ptrToTo;
               COROUTINES_COROUTINE *ptrToFrom;
             };

static SourceList freeList;
static COROUTINES_COROUTINE head;
static COROUTINES_COROUTINE currentCoRoutine;
static void * illegalFinish;
static unsigned int initMain;
static unsigned int initPthreads;
void COROUTINES_NEWCOROUTINE (PROC procBody, void * workspace, unsigned int size, COROUTINES_COROUTINE *cr, COROUTINES_PROTECTION initProtection);
void COROUTINES_TRANSFER (COROUTINES_COROUTINE *from, COROUTINES_COROUTINE to);

/*
   localInit - checks to see whether we need to initialize libpth.
*/

void COROUTINES_IOTRANSFER (COROUTINES_COROUTINE *from, COROUTINES_COROUTINE to);

/*
   Dispose - returns, l, to the freeList.
*/

void COROUTINES_ATTACH (COROUTINES_INTERRUPTSOURCE source);
void COROUTINES_DETACH (COROUTINES_INTERRUPTSOURCE source);

/*
   getAttached - returns the first COROUTINE associated with, source.
                 It returns NIL is no COROUTINE is associated with, source.
*/

unsigned int COROUTINES_IsATTACHED (COROUTINES_INTERRUPTSOURCE source);
COROUTINES_COROUTINE COROUTINES_HANDLER (COROUTINES_INTERRUPTSOURCE source);
COROUTINES_COROUTINE COROUTINES_CURRENT (void);
void COROUTINES_LISTEN (COROUTINES_PROTECTION p);

/*
   IOTransferHandler - handles interrupts related to a pending IOTRANSFER.
*/

COROUTINES_PROTECTION COROUTINES_PROT (void);

/*
   localMain - creates the holder for the main process.
*/

static void localMain (void);

/*
   Finished - generates an error message. Modula-2 processes
              should never terminate.
*/

static void Finished (void * p);

/*
   localInit - checks to see whether we need to initialize libpth.
*/

static void localInit (void);

/*
   New - assigns, l, to a new SourceList.
*/

static void New (SourceList *l);

/*
   Dispose - returns, l, to the freeList.
*/

static void Dispose (SourceList l);

/*
   getAttached - returns the first COROUTINE associated with, source.
                 It returns NIL is no COROUTINE is associated with, source.
*/

static COROUTINES_COROUTINE getAttached (COROUTINES_INTERRUPTSOURCE source);

/*
   ListenLoop - should be called instead of users writing:

                LOOP
                   LISTEN
                END

                It performs the same function but yields
                control back to the underlying operating system.
                It also checks for deadlock.
                This will yield processor to the underlying
                operating system under GNU pth.
                This function returns when an interrupt occurs.
                (File descriptor becomes ready or time event expires).
*/

static void ListenLoop (void);

/*
   removeAttached - removes all sources of interrupt from COROUTINE, c.
*/

static void removeAttached (COROUTINES_COROUTINE c);

/*
   IOTransferHandler - handles interrupts related to a pending IOTRANSFER.
*/

static void IOTransferHandler (unsigned int InterruptNo, unsigned int Priority, SourceList l);

/*
   TurnInterrupts - switches processor interrupts to the protection
                    level, to.  It returns the old value.
*/

static COROUTINES_PROTECTION TurnInterrupts (COROUTINES_PROTECTION to);

/*
   Init - 
*/

static void Init (void);


/*
   localMain - creates the holder for the main process.
*/

static void localMain (void)
{
  if (! initMain)
    {
      initMain = TRUE;
      Storage_ALLOCATE ((void **) &currentCoRoutine, sizeof (_T1));
      if ((pth_pth_uctx_create (&currentCoRoutine->context)) == 0)
        M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 166, (char *) "localMain", 9, (char *) "unable to create context for main", 33);
      currentCoRoutine->ehblock = RTExceptions_GetExceptionBlock ();
      currentCoRoutine->inexcept = RTExceptions_IsInExceptionState ();
      currentCoRoutine->source = RTExceptions_GetExceptionSource ();
      currentCoRoutine->wspace = NULL;
      currentCoRoutine->nLocs = 0;
      currentCoRoutine->status = running;
      currentCoRoutine->protection = COROUTINES_UnassignedPriority;
      currentCoRoutine->attached = NULL;
      currentCoRoutine->next = head;
      head = currentCoRoutine;
    }
}


/*
   Finished - generates an error message. Modula-2 processes
              should never terminate.
*/

static void Finished (void * p)
{
  M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 191, (char *) "Finished", 8, (char *) "process terminated illegally", 28);
}


/*
   localInit - checks to see whether we need to initialize libpth.
*/

static void localInit (void)
{
  if (! initPthreads)
    {
      if ((pth_pth_init ()) == 0)
        M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 205, (char *) "localInit", 9, (char *) "failed to initialize pthreads", 29);
      initPthreads = TRUE;
      if ((pth_pth_uctx_create (&illegalFinish)) == 0)
        M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 211, (char *) "localInit", 9, (char *) "unable to create user context", 29);
      if ((pth_pth_uctx_make ((pth_pth_uctx_t) illegalFinish, NULL, (pth_size_t) MinStack, NULL, (pth_proc) {(pth_proc_t) Finished}, NULL, (pth_pth_uctx_t) NULL)) == 0)
        M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 216, (char *) "localInit", 9, (char *) "unable to make user context", 27);
    }
  localMain ();
}


/*
   New - assigns, l, to a new SourceList.
*/

static void New (SourceList *l)
{
  if (freeList == NULL)
    Storage_ALLOCATE ((void **) &(*l), sizeof (_T2));
  else
    {
      (*l) = freeList;
      freeList = freeList->next;
    }
}


/*
   Dispose - returns, l, to the freeList.
*/

static void Dispose (SourceList l)
{
  l->next = freeList;
  freeList = l;
}


/*
   getAttached - returns the first COROUTINE associated with, source.
                 It returns NIL is no COROUTINE is associated with, source.
*/

static COROUTINES_COROUTINE getAttached (COROUTINES_INTERRUPTSOURCE source)
{
  SourceList l;
  COROUTINES_COROUTINE c;

  c = head;
  while (c != NULL)
    {
      l = c->attached;
      while (l != NULL)
        if (l->vec == source)
          return c;
        else
          l = l->next;
      c = c->next;
    }
  return NULL;
}


/*
   ListenLoop - should be called instead of users writing:

                LOOP
                   LISTEN
                END

                It performs the same function but yields
                control back to the underlying operating system.
                It also checks for deadlock.
                This will yield processor to the underlying
                operating system under GNU pth.
                This function returns when an interrupt occurs.
                (File descriptor becomes ready or time event expires).
*/

static void ListenLoop (void)
{
  localInit ();
  RTint_Listen (TRUE, (RTint_DespatchVector) {(RTint_DespatchVector_t) IOTransferHandler}, (unsigned int) COROUTINES_UnassignedPriority);
}


/*
   removeAttached - removes all sources of interrupt from COROUTINE, c.
*/

static void removeAttached (COROUTINES_COROUTINE c)
{
  SourceList l;

  l = c->attached;
  while (l != NULL)
    {
      RTint_ExcludeVector ((unsigned int) l->vec);
      l = l->next;
    }
}


/*
   IOTransferHandler - handles interrupts related to a pending IOTRANSFER.
*/

static void IOTransferHandler (unsigned int InterruptNo, unsigned int Priority, SourceList l)
{
  SourceList ourself;

  localInit ();
  if (l == NULL)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 454, (char *) "IOTransferHandler", 17, (char *) "no coroutine attached to this interrupt vector which was initiated by IOTRANSFER", 80);
  else
    {
      ourself = RTint_AttachVector (InterruptNo, (void *) l->chain);
      if (ourself != l)
        M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 461, (char *) "IOTransferHandler", 17, (char *) "inconsistancy of return result", 30);
      if (l->chain == NULL)
        removeAttached (l->curco);
      else
        libc_printf ((char *) "odd vector has been chained\\n", 29);
      (*l->ptrToTo)->context = currentCoRoutine->context;
      COROUTINES_TRANSFER (l->ptrToTo, (*l->ptrToFrom));
    }
}


/*
   TurnInterrupts - switches processor interrupts to the protection
                    level, to.  It returns the old value.
*/

static COROUTINES_PROTECTION TurnInterrupts (COROUTINES_PROTECTION to)
{
  COROUTINES_PROTECTION old;

  localInit ();
  old = currentCoRoutine->protection;
  RTint_Listen (FALSE, (RTint_DespatchVector) {(RTint_DespatchVector_t) IOTransferHandler}, (unsigned int) old);
  currentCoRoutine->protection = to;
  RTint_Listen (FALSE, (RTint_DespatchVector) {(RTint_DespatchVector_t) IOTransferHandler}, (unsigned int) to);
  return old;
}


/*
   Init - 
*/

static void Init (void)
{
  freeList = NULL;
  initPthreads = FALSE;
  initMain = FALSE;
  currentCoRoutine = NULL;
}

void COROUTINES_NEWCOROUTINE (PROC procBody, void * workspace, unsigned int size, COROUTINES_COROUTINE *cr, COROUTINES_PROTECTION initProtection)
{
  typedef struct ThreadProcess_p ThreadProcess;

  typedef void (*ThreadProcess_t) (void *);
  struct ThreadProcess_p { ThreadProcess_t proc; };

  void * ctx;
  ThreadProcess tp;

  /* Creates a new coroutine whose body is given by procBody, and
     returns the identity of the coroutine in cr. workspace is a
     pointer to the work space allocated to the coroutine; size
     specifies the size of this workspace in terms of SYSTEM.LOC.

     The optarg, initProtection, may contain a single parameter
     which specifies the initial protection level of the coroutine.
  */
  localInit ();
  tp = (ThreadProcess) {(ThreadProcess_t) procBody.proc};
  if ((pth_pth_uctx_create (&ctx)) == 0)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 101, (char *) "NEWCOROUTINE", 12, (char *) "unable to create user context", 29);
  if ((pth_pth_uctx_make ((pth_pth_uctx_t) ctx, workspace, (pth_size_t) size, NULL, (pth_proc) {(pth_proc_t) tp.proc}, NULL, (pth_pth_uctx_t) illegalFinish)) == 0)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 105, (char *) "NEWCOROUTINE", 12, (char *) "unable to make user context", 27);
  Storage_ALLOCATE ((void **) &(*cr), sizeof (_T1));
  if (initProtection == COROUTINES_UnassignedPriority)
    initProtection = COROUTINES_PROT ();
  (*cr)->context = ctx;
  (*cr)->ehblock = RTExceptions_InitExceptionBlock ();
  (*cr)->inexcept = FALSE;
  (*cr)->source = NULL;
  (*cr)->wspace = workspace;
  (*cr)->nLocs = size;
  (*cr)->status = new;
  (*cr)->protection = initProtection;
  (*cr)->attached = NULL;
  (*cr)->next = head;
  head = (*cr);
}

void COROUTINES_TRANSFER (COROUTINES_COROUTINE *from, COROUTINES_COROUTINE to)
{
  /* Returns the identity of the calling coroutine in from, and
     transfers control to the coroutine specified by to.
  */
  localInit ();
  (*from) = currentCoRoutine;
  if (to->context == (*from)->context)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 137, (char *) "TRANSFER", 8, (char *) "error when attempting to context switch to the same process", 59);
  (*from)->inexcept = RTExceptions_SetExceptionState (to->inexcept);
  (*from)->source = RTExceptions_GetExceptionSource ();
  currentCoRoutine = to;
  RTExceptions_SetExceptionBlock (currentCoRoutine->ehblock);
  RTExceptions_SetExceptionSource ((void *) currentCoRoutine->source);
  if ((pth_pth_uctx_switch ((pth_pth_uctx_t) (*from)->context, (pth_pth_uctx_t) to->context)) == 0)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/COROUTINES.mod", 73, 147, (char *) "TRANSFER", 8, (char *) "an error as it was unable to change the user context", 52);
}


/*
   localInit - checks to see whether we need to initialize libpth.
*/

void COROUTINES_IOTRANSFER (COROUTINES_COROUTINE *from, COROUTINES_COROUTINE to)
{
  SourceList l;

  /* Returns the identity of the calling coroutine in from and
     transfers control to the coroutine specified by to.  On
     occurrence of an interrupt, associated with the caller, control
     is transferred back to the caller, and the identity of the
     interrupted coroutine is returned in from.  The calling coroutine
     must be associated with a source of interrupts.
  */
  localInit ();
  l = currentCoRoutine->attached;
  if (l == NULL)
    libc_printf ((char *) "no source of interrupts associated with coroutine\\n", 51);
  while (l != NULL)
    {
      l->ptrToFrom = from;
      l->ptrToTo = &to;
      l->curco = currentCoRoutine;
      l->chain = RTint_AttachVector ((unsigned int) l->vec, (void *) l);
      if (l->chain != NULL)
        libc_printf ((char *) "not expecting multiple COROUTINES to be waiting on a single interrupt source\\n", 78);
      RTint_IncludeVector ((unsigned int) l->vec);
      l = l->next;
    }
  COROUTINES_TRANSFER (from, to);
}


/*
   Dispose - returns, l, to the freeList.
*/

void COROUTINES_ATTACH (COROUTINES_INTERRUPTSOURCE source)
{
  SourceList l;

  /* Associates the specified source of interrupts with the calling
     coroutine.  */
  localInit ();
  l = currentCoRoutine->attached;
  while (l != NULL)
    if (l->vec == source)
      return;
    else
      l = l->next;
  New (&l);
  l->vec = source;
  l->next = currentCoRoutine->attached;
  currentCoRoutine->attached = l;
}

void COROUTINES_DETACH (COROUTINES_INTERRUPTSOURCE source)
{
  SourceList l;
  SourceList m;

  /* Dissociates the specified source of interrupts from the calling
     coroutine.  */
  localInit ();
  l = currentCoRoutine->attached;
  m = l;
  while (l != NULL)
    if (l->vec == source)
      {
        if (m == currentCoRoutine->attached)
          currentCoRoutine->attached = currentCoRoutine->attached->next;
        else
          m->next = l->next;
        Dispose (l);
        return;
      }
    else
      {
        m = l;
        l = l->next;
      }
}


/*
   getAttached - returns the first COROUTINE associated with, source.
                 It returns NIL is no COROUTINE is associated with, source.
*/

unsigned int COROUTINES_IsATTACHED (COROUTINES_INTERRUPTSOURCE source)
{
  /* Returns TRUE if and only if the specified source of interrupts is
     currently associated with a coroutine; otherwise returns FALSE.
  */
  localInit ();
  return (getAttached (source)) != NULL;
}

COROUTINES_COROUTINE COROUTINES_HANDLER (COROUTINES_INTERRUPTSOURCE source)
{
  /* Returns the coroutine, if any, that is associated with the source
     of interrupts. The result is undefined if IsATTACHED(source) =
     FALSE.
  */
  localInit ();
  return getAttached (source);
}

COROUTINES_COROUTINE COROUTINES_CURRENT (void)
{
  /* Returns the identity of the calling coroutine.  */
  localInit ();
  return currentCoRoutine;
}

void COROUTINES_LISTEN (COROUTINES_PROTECTION p)
{
  /* Momentarily changes the protection of the calling coroutine to p.  */
  localInit ();
  RTint_Listen (FALSE, (RTint_DespatchVector) {(RTint_DespatchVector_t) IOTransferHandler}, (unsigned int) COROUTINES_UnassignedPriority);
}


/*
   IOTransferHandler - handles interrupts related to a pending IOTRANSFER.
*/

COROUTINES_PROTECTION COROUTINES_PROT (void)
{
  /* Returns the protection of the calling coroutine.  */
  localInit ();
  return currentCoRoutine->protection;
}

void _M2_COROUTINES_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_COROUTINES_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
