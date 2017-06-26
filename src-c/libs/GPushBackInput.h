/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/PushBackInput.def.  */


#if !defined (_PushBackInput_H)
#   define _PushBackInput_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GFIO.h"
#   include "GDynamicStrings.h"

#   if defined (_PushBackInput_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   Open - opens a file for reading.
*/

EXTERN FIO_File PushBackInput_Open (char *a_, unsigned int _a_high);

/*
   GetCh - gets a character from either the push back stack or
           from file, f.
*/

EXTERN char PushBackInput_GetCh (FIO_File f);

/*
   PutCh - pushes a character onto the push back stack, it also
           returns the character which has been pushed.
*/

EXTERN char PushBackInput_PutCh (FIO_File f, char ch);

/*
   PutString - pushes a string onto the push back stack.
*/

EXTERN void PushBackInput_PutString (FIO_File f, char *a_, unsigned int _a_high);

/*
   Error - emits an error message with the appropriate file, line combination.
*/

EXTERN void PushBackInput_Error (char *a_, unsigned int _a_high);

/*
   WarnError - emits an error message with the appropriate file, line combination.
               It does not terminate but when the program finishes an exit status of
               1 will be issued.
*/

EXTERN void PushBackInput_WarnError (char *a_, unsigned int _a_high);

/*
   WarnString - emits an error message with the appropriate file, line combination.
                It does not terminate but when the program finishes an exit status of
                1 will be issued.
*/

EXTERN void PushBackInput_WarnString (DynamicStrings_String s);

/*
   Close - closes the opened file.
*/

EXTERN void PushBackInput_Close (FIO_File f);

/*
   GetExitStatus - returns the exit status which will be 1 if any warnings were issued.
*/

EXTERN unsigned int PushBackInput_GetExitStatus (void);

/*
   SetDebug - sets the debug flag on or off.
*/

EXTERN void PushBackInput_SetDebug (unsigned int d);

/*
   GetColumnPosition - returns the column position of the current character.
*/

EXTERN unsigned int PushBackInput_GetColumnPosition (void);

/*
   GetCurrentLine - returns the current line number.
*/

EXTERN unsigned int PushBackInput_GetCurrentLine (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
