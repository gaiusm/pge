/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTExceptions.def.  */


#if !defined (_RTExceptions_H)
#   define _RTExceptions_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_RTExceptions_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (RTExceptions_EHBlock_D)
#  define RTExceptions_EHBlock_D
   typedef void *RTExceptions_EHBlock;
#endif

typedef struct RTExceptions_ProcedureHandler_p RTExceptions_ProcedureHandler;

typedef void (*RTExceptions_ProcedureHandler_t) (void);
struct RTExceptions_ProcedureHandler_p { RTExceptions_ProcedureHandler_t proc; };


/*
   Raise - invoke the exception handler associated with, number,
           in the active EHBlock.  It keeps a record of the number
           and message in the EHBlock for later use.
*/

EXTERN void RTExceptions_Raise (unsigned int number, void * file, unsigned int line, unsigned int column, void * function, void * message);

/*
   SetExceptionBlock - sets, source, as the active EHB.
*/

EXTERN void RTExceptions_SetExceptionBlock (RTExceptions_EHBlock source);

/*
   GetExceptionBlock - returns the active EHB.
*/

EXTERN RTExceptions_EHBlock RTExceptions_GetExceptionBlock (void);

/*
   GetTextBuffer - returns the address of the EHB buffer.
*/

EXTERN void * RTExceptions_GetTextBuffer (RTExceptions_EHBlock e);

/*
   GetTextBufferSize - return the size of the EHB text buffer.
*/

EXTERN unsigned int RTExceptions_GetTextBufferSize (RTExceptions_EHBlock e);

/*
   GetNumber - return the exception number associated with,
               source.
*/

EXTERN unsigned int RTExceptions_GetNumber (RTExceptions_EHBlock source);

/*
   InitExceptionBlock - creates and returns a new exception block.
*/

EXTERN RTExceptions_EHBlock RTExceptions_InitExceptionBlock (void);

/*
   KillExceptionBlock - destroys the EHB, e, and all its handlers.
*/

EXTERN RTExceptions_EHBlock RTExceptions_KillExceptionBlock (RTExceptions_EHBlock e);

/*
   PushHandler - install a handler in EHB, e.
*/

EXTERN void RTExceptions_PushHandler (RTExceptions_EHBlock e, unsigned int number, RTExceptions_ProcedureHandler p);

/*
   PopHandler - removes the handler associated with, number, from
                EHB, e.
*/

EXTERN void RTExceptions_PopHandler (RTExceptions_EHBlock e, unsigned int number);

/*
   DefaultErrorCatch - displays the current error message in
                       the current exception block and then
                       calls HALT.
*/

EXTERN void RTExceptions_DefaultErrorCatch (void);

/*
   BaseExceptionsThrow - configures the Modula-2 exceptions to call
                         THROW which in turn can be caught by an
                         exception block.  If this is not called then
                         a Modula-2 exception will simply call an
                         error message routine and then HALT.
*/

EXTERN void RTExceptions_BaseExceptionsThrow (void);

/*
   IsInExceptionState - returns TRUE if the program is currently
                        in the exception state.
*/

EXTERN unsigned int RTExceptions_IsInExceptionState (void);

/*
   SetExceptionState - returns the current exception state and
                       then sets the current exception state to,
                       to.
*/

EXTERN unsigned int RTExceptions_SetExceptionState (unsigned int to);

/*
   SwitchExceptionState - assigns, from, with the current exception
                          state and then assigns the current exception
                          to, to.
*/

EXTERN void RTExceptions_SwitchExceptionState (unsigned int *from, unsigned int to);

/*
   GetBaseExceptionBlock - returns the initial language exception block
                           created.
*/

EXTERN RTExceptions_EHBlock RTExceptions_GetBaseExceptionBlock (void);

/*
   SetExceptionSource - sets the current exception source to, source.
*/

EXTERN void RTExceptions_SetExceptionSource (void * source);

/*
   GetExceptionSource - returns the current exception source.
*/

EXTERN void * RTExceptions_GetExceptionSource (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
