/* automatically created by mc from ../RTExceptions.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#include <stddef.h>
#include <string.h>
#include <limits.h>
#   include "GStorage.h"
#   include "Gmcrts.h"
#define _RTExceptions_H
#define _RTExceptions_C

#   include "GASCII.h"
#   include "GStrLib.h"
#   include "GStorage.h"
#   include "GSYSTEM.h"
#   include "Glibc.h"
#   include "GM2RTS.h"
#   include "GSysExceptions.h"
#   include "GM2EXCEPTION.h"
#   include "Ggdbif.h"

typedef struct RTExceptions_ProcedureHandler_p RTExceptions_ProcedureHandler;

#   define MaxBuffer 4096
typedef struct handler_r handler;

typedef handler *Handler;

typedef struct ehblock_r ehblock;

typedef struct _T1_a _T1;

typedef char *PtrToChar;

typedef ehblock *RTExceptions_EHBlock;

typedef void (*RTExceptions_ProcedureHandler_t) (void);
struct RTExceptions_ProcedureHandler_p { RTExceptions_ProcedureHandler_t proc; };

struct _T1_a { char array[MaxBuffer+1]; };
struct handler_r {
                   RTExceptions_ProcedureHandler p;
                   unsigned int n;
                   Handler right;
                   Handler left;
                   Handler stack;
                 };

struct ehblock_r {
                   _T1 buffer;
                   unsigned int number;
                   Handler handlers;
                   RTExceptions_EHBlock right;
                 };

static unsigned int inException;
static Handler freeHandler;
static RTExceptions_EHBlock freeEHB;
static RTExceptions_EHBlock currentEHB;
static void * currentSource;

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

/*
   ErrorString - writes a string to stderr.
*/

static void ErrorString (char *a_, unsigned int _a_high);

/*
   findHandler -
*/

static Handler findHandler (RTExceptions_EHBlock e, unsigned int number);

/*
   InvokeHandler - invokes the associated handler for the current
                   exception in the active EHB.
*/

static void InvokeHandler (void);

/*
   DoThrow - throw the exception number in the exception block.
*/

static void DoThrow (void);

/*
   addChar - adds, ch, to the current exception handler text buffer
             at index, i.  The index in then incremented.
*/

static void addChar (char ch, unsigned int *i);

/*
   stripPath - returns the filename from the path.
*/

static void * stripPath (void * s);

/*
   addFile - adds the filename determined by, s, however it strips
             any preceeding path.
*/

static void addFile (void * s, unsigned int *i);

/*
   addStr - adds a C string from address, s, into the current
            handler text buffer.
*/

static void addStr (void * s, unsigned int *i);

/*
   addNum - adds a number, n, to the current handler
            text buffer.
*/

static void addNum (unsigned int n, unsigned int *i);

/*
   New - returns a new EHBlock.
*/

static RTExceptions_EHBlock New (void);

/*
   NewHandler - returns a new handler.
*/

static Handler NewHandler (void);

/*
   KillHandler - returns, NIL, and places, h, onto the free list.
*/

static Handler KillHandler (Handler h);

/*
   KillHandlers - kills all handlers in the list.
*/

static Handler KillHandlers (Handler h);

/*
   InitHandler -
*/

static Handler InitHandler (Handler h, Handler l, Handler r, Handler s, unsigned int number, RTExceptions_ProcedureHandler proc);

/*
   SubHandler -
*/

static void SubHandler (Handler h);

/*
   AddHandler - add, e, to the end of the list of handlers.
*/

static void AddHandler (RTExceptions_EHBlock e, Handler h);

/*
   indexf - raise an index out of bounds exception.
*/

static void indexf (void * a);

/*
   range - raise an assignment out of range exception.
*/

static void range (void * a);

/*
   casef - raise a case selector out of range exception.
*/

static void casef (void * a);

/*
   invalidloc - raise an invalid location exception.
*/

static void invalidloc (void * a);

/*
   function - raise a ... function ... exception.  --fixme-- what does this exception catch?
*/

static void function (void * a);

/*
   wholevalue - raise an illegal whole value exception.
*/

static void wholevalue (void * a);

/*
   wholediv - raise a division by zero exception.
*/

static void wholediv (void * a);

/*
   realvalue - raise an illegal real value exception.
*/

static void realvalue (void * a);

/*
   realdiv - raise a division by zero in a real number exception.
*/

static void realdiv (void * a);

/*
   complexvalue - raise an illegal complex value exception.
*/

static void complexvalue (void * a);

/*
   complexdiv - raise a division by zero in a complex number exception.
*/

static void complexdiv (void * a);

/*
   protection - raise a protection exception.
*/

static void protection (void * a);

/*
   systemf - raise a system exception.
*/

static void systemf (void * a);

/*
   coroutine - raise a coroutine exception.
*/

static void coroutine (void * a);

/*
   exception - raise a exception exception.
*/

static void exception (void * a);

/*
   Init - initialises this module.
*/

static void Init (void);

/*
   TidyUp - deallocate memory used by this module.
*/

static void TidyUp (void);


/*
   ErrorString - writes a string to stderr.
*/

static void ErrorString (char *a_, unsigned int _a_high)
{
  int n;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  n = libc_write (2, &a, (int) StrLib_StrLen ((char *) a, _a_high));
}


/*
   findHandler -
*/

static Handler findHandler (RTExceptions_EHBlock e, unsigned int number)
{
  Handler h;

  h = e->handlers->right;
  while ((h != e->handlers) && (number != h->n))
    h = h->right;
  if (h == e->handlers)
    return NULL;
  else
    return h;
}


/*
   InvokeHandler - invokes the associated handler for the current
                   exception in the active EHB.
*/

static void InvokeHandler (void)
{
  Handler h;

  h = findHandler (currentEHB, currentEHB->number);
  if (h == NULL)
    {
      gdbif_sleepSpin ();
      throw (RTExceptions_GetNumber (RTExceptions_GetExceptionBlock ()));
    }
  else
    (*h->p.proc) ();
}


/*
   DoThrow - throw the exception number in the exception block.
*/

static void DoThrow (void)
{
  throw (RTExceptions_GetNumber (RTExceptions_GetExceptionBlock ()));
}


/*
   addChar - adds, ch, to the current exception handler text buffer
             at index, i.  The index in then incremented.
*/

static void addChar (char ch, unsigned int *i)
{
  if (((*i) <= MaxBuffer) && (currentEHB != NULL))
    {
      currentEHB->buffer.array[(*i)] = ch;
      (*i) += 1;
    }
}


/*
   stripPath - returns the filename from the path.
*/

static void * stripPath (void * s)
{
  PtrToChar f;
  PtrToChar p;

  p = s;
  f = s;
  while ((*p) != ASCII_nul)
    if ((*p) == '/')
      {
        p += 1;
        f = p;
      }
    else
      p += 1;
  return f;
}


/*
   addFile - adds the filename determined by, s, however it strips
             any preceeding path.
*/

static void addFile (void * s, unsigned int *i)
{
  PtrToChar p;

  p = stripPath (s);
  while ((p != NULL) && ((*p) != ASCII_nul))
    {
      addChar ((*p), i);
      p += 1;
    }
}


/*
   addStr - adds a C string from address, s, into the current
            handler text buffer.
*/

static void addStr (void * s, unsigned int *i)
{
  PtrToChar p;

  p = s;
  while ((p != NULL) && ((*p) != ASCII_nul))
    {
      addChar ((*p), i);
      p += 1;
    }
}


/*
   addNum - adds a number, n, to the current handler
            text buffer.
*/

static void addNum (unsigned int n, unsigned int *i)
{
  if (n < 10)
    addChar ((char) ((n % 10)+((unsigned int) ('0'))), i);
  else
    {
      addNum (n / 10, i);
      addNum (n % 10, i);
    }
}


/*
   New - returns a new EHBlock.
*/

static RTExceptions_EHBlock New (void)
{
  RTExceptions_EHBlock e;

  if (freeEHB == NULL)
    Storage_ALLOCATE ((void **) &e, sizeof (ehblock));
  else
    {
      e = freeEHB;
      freeEHB = freeEHB->right;
    }
  return e;
}


/*
   NewHandler - returns a new handler.
*/

static Handler NewHandler (void)
{
  Handler h;

  if (freeHandler == NULL)
    Storage_ALLOCATE ((void **) &h, sizeof (handler));
  else
    {
      h = freeHandler;
      freeHandler = freeHandler->right;
    }
  return h;
}


/*
   KillHandler - returns, NIL, and places, h, onto the free list.
*/

static Handler KillHandler (Handler h)
{
  h->right = freeHandler;
  freeHandler = h;
  return NULL;
}


/*
   KillHandlers - kills all handlers in the list.
*/

static Handler KillHandlers (Handler h)
{
  h->left->right = freeHandler;
  freeHandler = h;
  return NULL;
}


/*
   InitHandler -
*/

static Handler InitHandler (Handler h, Handler l, Handler r, Handler s, unsigned int number, RTExceptions_ProcedureHandler proc)
{
  h->p = proc;
  h->n = number;
  h->right = r;
  h->left = l;
  h->stack = s;
  return h;
}


/*
   SubHandler -
*/

static void SubHandler (Handler h)
{
  h->right->left = h->left;
  h->left->right = h->right;
}


/*
   AddHandler - add, e, to the end of the list of handlers.
*/

static void AddHandler (RTExceptions_EHBlock e, Handler h)
{
  h->right = e->handlers;
  h->left = e->handlers->left;
  e->handlers->left->right = h;
  e->handlers->left = h;
}


/*
   indexf - raise an index out of bounds exception.
*/

static void indexf (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_indexException), "../RTExceptions.mod", 605, 9, "indexf", "array index out of bounds");
}


/*
   range - raise an assignment out of range exception.
*/

static void range (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_rangeException), "../RTExceptions.mod", 617, 9, "range", "assignment out of range");
}


/*
   casef - raise a case selector out of range exception.
*/

static void casef (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_caseSelectException), "../RTExceptions.mod", 629, 9, "casef", "case selector out of range");
}


/*
   invalidloc - raise an invalid location exception.
*/

static void invalidloc (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_invalidLocation), "../RTExceptions.mod", 641, 9, "invalidloc", "invalid address referenced");
}


/*
   function - raise a ... function ... exception.  --fixme-- what does this exception catch?
*/

static void function (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_functionException), "../RTExceptions.mod", 653, 9, "function", "... function ... ");
}


/*
   wholevalue - raise an illegal whole value exception.
*/

static void wholevalue (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_wholeValueException), "../RTExceptions.mod", 665, 9, "wholevalue", "illegal whole value exception");
}


/*
   wholediv - raise a division by zero exception.
*/

static void wholediv (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_wholeDivException), "../RTExceptions.mod", 677, 9, "wholediv", "illegal whole value exception");
}


/*
   realvalue - raise an illegal real value exception.
*/

static void realvalue (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_realValueException), "../RTExceptions.mod", 689, 9, "realvalue", "illegal real value exception");
}


/*
   realdiv - raise a division by zero in a real number exception.
*/

static void realdiv (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_realDivException), "../RTExceptions.mod", 701, 9, "realdiv", "real number division by zero exception");
}


/*
   complexvalue - raise an illegal complex value exception.
*/

static void complexvalue (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_complexValueException), "../RTExceptions.mod", 713, 9, "complexvalue", "illegal complex value exception");
}


/*
   complexdiv - raise a division by zero in a complex number exception.
*/

static void complexdiv (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_complexDivException), "../RTExceptions.mod", 725, 9, "complexdiv", "complex number division by zero exception");
}


/*
   protection - raise a protection exception.
*/

static void protection (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_protException), "../RTExceptions.mod", 737, 9, "protection", "protection exception");
}


/*
   systemf - raise a system exception.
*/

static void systemf (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_sysException), "../RTExceptions.mod", 749, 9, "systemf", "system exception");
}


/*
   coroutine - raise a coroutine exception.
*/

static void coroutine (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_coException), "../RTExceptions.mod", 761, 9, "coroutine", "coroutine exception");
}


/*
   exception - raise a exception exception.
*/

static void exception (void * a)
{
  RTExceptions_Raise ((unsigned int) (M2EXCEPTION_exException), "../RTExceptions.mod", 773, 9, "exception", "exception exception");
}


/*
   Init - initialises this module.
*/

static void Init (void)
{
  inException = FALSE;
  freeHandler = NULL;
  freeEHB = NULL;
  currentEHB = RTExceptions_InitExceptionBlock ();
  currentSource = NULL;
  RTExceptions_BaseExceptionsThrow ();
  SysExceptions_InitExceptionHandlers ((SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) indexf}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) range}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) casef}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) invalidloc}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) function}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) wholevalue}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) wholediv}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) realvalue}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) realdiv}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) complexvalue}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) complexdiv}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) protection}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) systemf}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) coroutine}, (SysExceptions_PROCEXCEPTION) {(SysExceptions_PROCEXCEPTION_t) exception});
}


/*
   TidyUp - deallocate memory used by this module.
*/

static void TidyUp (void)
{
  Handler f;
  RTExceptions_EHBlock e;

  if (currentEHB != NULL)
    currentEHB = RTExceptions_KillExceptionBlock (currentEHB);
  while (freeHandler != NULL)
    {
      f = freeHandler;
      freeHandler = freeHandler->right;
      Storage_DEALLOCATE ((void **) &f, sizeof (handler));
    }
  while (freeEHB != NULL)
    {
      e = freeEHB;
      freeEHB = freeEHB->right;
      Storage_DEALLOCATE ((void **) &e, sizeof (ehblock));
    }
}


/*
   Raise - invoke the exception handler associated with, number,
           in the active EHBlock.  It keeps a record of the number
           and message in the EHBlock for later use.
*/

void RTExceptions_Raise (unsigned int number, void * file, unsigned int line, unsigned int column, void * function, void * message)
{
  unsigned int i;

  currentEHB->number = number;
  i = 0;
  addFile (file, &i);
  addChar (':', &i);
  addNum (line, &i);
  addChar (':', &i);
  addNum (column, &i);
  addChar (':', &i);
  addStr (message, &i);
  addChar (' ', &i);
  addChar ('i', &i);
  addChar ('n', &i);
  addChar (' ', &i);
  addStr (function, &i);
  addChar (ASCII_nl, &i);
  addChar (ASCII_nul, &i);
  InvokeHandler ();
}


/*
   SetExceptionBlock - sets, source, as the active EHB.
*/

void RTExceptions_SetExceptionBlock (RTExceptions_EHBlock source)
{
  currentEHB = source;
}


/*
   GetExceptionBlock - returns the active EHB.
*/

RTExceptions_EHBlock RTExceptions_GetExceptionBlock (void)
{
  return currentEHB;
}


/*
   GetTextBuffer - returns the address of the EHB buffer.
*/

void * RTExceptions_GetTextBuffer (RTExceptions_EHBlock e)
{
  return &e->buffer;
}


/*
   GetTextBufferSize - return the size of the EHB text buffer.
*/

unsigned int RTExceptions_GetTextBufferSize (RTExceptions_EHBlock e)
{
  return sizeof (e->buffer);
}


/*
   GetNumber - return the exception number associated with,
               source.
*/

unsigned int RTExceptions_GetNumber (RTExceptions_EHBlock source)
{
  return source->number;
}


/*
   InitExceptionBlock - creates and returns a new exception block.
*/

RTExceptions_EHBlock RTExceptions_InitExceptionBlock (void)
{
  RTExceptions_EHBlock e;

  e = New ();
  e->number = UINT_MAX;
  e->handlers = NewHandler ();
  e->handlers->right = e->handlers;
  e->handlers->left = e->handlers;
  e->right = e;
  return e;
}


/*
   KillExceptionBlock - destroys the EHB, e, and all its handlers.
*/

RTExceptions_EHBlock RTExceptions_KillExceptionBlock (RTExceptions_EHBlock e)
{
  e->handlers = KillHandlers (e->handlers);
  e->right = freeEHB;
  freeEHB = e;
  return NULL;
}


/*
   PushHandler - install a handler in EHB, e.
*/

void RTExceptions_PushHandler (RTExceptions_EHBlock e, unsigned int number, RTExceptions_ProcedureHandler p)
{
  Handler h;
  Handler i;

  h = findHandler (e, number);
  if (h == NULL)
    i = InitHandler (NewHandler (), (Handler) NULL, (Handler) NULL, (Handler) NULL, number, p);
  else
    {
      SubHandler (h);
      i = InitHandler (NewHandler (), (Handler) NULL, (Handler) NULL, h, number, p);
    }
  AddHandler (e, i);
}


/*
   PopHandler - removes the handler associated with, number, from
                EHB, e.
*/

void RTExceptions_PopHandler (RTExceptions_EHBlock e, unsigned int number)
{
  Handler h;
  Handler i;

  h = findHandler (e, number);
  if (h != NULL)
    {
      SubHandler (h);
      if (h->stack != NULL)
        AddHandler (e, h->stack);
      h = KillHandler (h);
    }
}


/*
   DefaultErrorCatch - displays the current error message in
                       the current exception block and then
                       calls HALT.
*/

void RTExceptions_DefaultErrorCatch (void)
{
  RTExceptions_EHBlock e;
  int n;

  e = RTExceptions_GetExceptionBlock ();
  n = libc_write (2, RTExceptions_GetTextBuffer (e), libc_strlen (RTExceptions_GetTextBuffer (e)));
  M2RTS_HALT (0);
}


/*
   BaseExceptionsThrow - configures the Modula-2 exceptions to call
                         THROW which in turn can be caught by an
                         exception block.  If this is not called then
                         a Modula-2 exception will simply call an
                         error message routine and then HALT.
*/

void RTExceptions_BaseExceptionsThrow (void)
{
  M2EXCEPTION_M2Exceptions i;

  for (i=M2EXCEPTION_indexException; i<=M2EXCEPTION_exException; i++)
    RTExceptions_PushHandler (RTExceptions_GetExceptionBlock (), (unsigned int ) (i), (RTExceptions_ProcedureHandler) {(RTExceptions_ProcedureHandler_t) DoThrow});
}


/*
   IsInExceptionState - returns TRUE if the program is currently
                        in the exception state.
*/

unsigned int RTExceptions_IsInExceptionState (void)
{
  return inException;
}


/*
   SetExceptionState - returns the current exception state and
                       then sets the current exception state to,
                       to.
*/

unsigned int RTExceptions_SetExceptionState (unsigned int to)
{
  unsigned int old;

  old = inException;
  inException = to;
  return old;
}


/*
   SwitchExceptionState - assigns, from, with the current exception
                          state and then assigns the current exception
                          to, to.
*/

void RTExceptions_SwitchExceptionState (unsigned int *from, unsigned int to)
{
  (*from) = inException;
  inException = to;
}


/*
   GetBaseExceptionBlock - returns the initial language exception block
                           created.
*/

RTExceptions_EHBlock RTExceptions_GetBaseExceptionBlock (void)
{
  if (currentEHB == NULL)
    M2RTS_Halt ((char *) "../RTExceptions.mod", 19, 591, (char *) "GetBaseExceptionBlock", 21, (char *) "currentEHB has not been initialized yet", 39);
  else
    return currentEHB;
  ReturnException ("/home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/RTExceptions.def", 2, 1);
}


/*
   SetExceptionSource - sets the current exception source to, source.
*/

void RTExceptions_SetExceptionSource (void * source)
{
  currentSource = source;
}


/*
   GetExceptionSource - returns the current exception source.
*/

void * RTExceptions_GetExceptionSource (void)
{
  return currentSource;
}

void _M2_RTExceptions_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_RTExceptions_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  TidyUp ();
}
