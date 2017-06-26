/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/M2RTS.def.  */


#if !defined (_M2RTS_H)
#   define _M2RTS_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_M2RTS_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   ExecuteTerminationProcedures - calls each installed termination
                                  procedure in reverse order.
*/

EXTERN void M2RTS_ExecuteTerminationProcedures (void);

/*
   InstallTerminationProcedure - installs a procedure, p, which will
                                 be called when the procedure
                                 ExecuteTerminationProcedures
                                 is invoked.  It returns TRUE is the
                                 procedure is installed.
*/

EXTERN unsigned int M2RTS_InstallTerminationProcedure (PROC p);

/*
   ExecuteInitialProcedures - executes the initial procedures installed
                              by InstallInitialProcedure.
*/

EXTERN void M2RTS_ExecuteInitialProcedures (void);

/*
   InstallInitialProcedure - installs a procedure to be executed just
                             before the BEGIN code section of the main
                             program module.
*/

EXTERN unsigned int M2RTS_InstallInitialProcedure (PROC p);

/*
   HALT - terminate the current program.  The procedure
          ExecuteTerminationProcedures
          is called before the program is stopped.  The parameter
          exitcode is optional.  If the parameter is not supplied
          HALT will call libc 'abort', otherwise it will exit with
          the code supplied.  Supplying a parameter to HALT has the
          same effect as calling ExitOnHalt with the same code and
          then calling HALT with no parameter.
*/

EXTERN void M2RTS_HALT (int exitcode);

/*
   Halt - provides a more user friendly version of HALT, which takes
          four parameters to aid debugging.
*/

EXTERN void M2RTS_Halt (char *file_, unsigned int _file_high, unsigned int line, char *function_, unsigned int _function_high, char *description_, unsigned int _description_high);

/*
   ExitOnHalt - if HALT is executed then call exit with the exit code, e.
*/

EXTERN void M2RTS_ExitOnHalt (int e);

/*
   ErrorMessage - emits an error message to stderr and then calls exit (1).
*/

EXTERN void M2RTS_ErrorMessage (char *message_, unsigned int _message_high, char *file_, unsigned int _file_high, unsigned int line, char *function_, unsigned int _function_high);

/*
   IsTerminating - Returns true if any coroutine has started program termination
                   and false otherwise.
*/

EXTERN unsigned int M2RTS_IsTerminating (void);

/*
   HasHalted - Returns true if a call to HALT has been made and false
               otherwise.
*/

EXTERN unsigned int M2RTS_HasHalted (void);

/*
   Length - returns the length of a string, a. This is called whenever
            the user calls LENGTH and the parameter cannot be calculated
            at compile time.
*/

EXTERN unsigned int M2RTS_Length (char *a_, unsigned int _a_high);
EXTERN void M2RTS_AssignmentException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_IncException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_DecException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_InclException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_ExclException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_ShiftException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_RotateException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_StaticArraySubscriptException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_DynamicArraySubscriptException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_ForLoopBeginException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_ForLoopToException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_ForLoopEndException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_PointerNilException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_NoReturnException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_CaseException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_WholeNonPosDivException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_WholeNonPosModException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_WholeZeroDivException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_WholeZeroRemException (void * filename, unsigned int line, unsigned int column, void * scope);
EXTERN void M2RTS_NoException (void * filename, unsigned int line, unsigned int column, void * scope);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
