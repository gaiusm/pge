/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/Scan.def.  */


#if !defined (_Scan_H)
#   define _Scan_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_Scan_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
 OpenSource - opens a source file for reading.                  */

EXTERN unsigned int Scan_OpenSource (char *a_, unsigned int _a_high);

/*
 CloseSource - closes the current source file from reading.     */

EXTERN void Scan_CloseSource (void);

/*
 GetNextSymbol gets the next source symbol and returns it in a. */

EXTERN void Scan_GetNextSymbol (char *a, unsigned int _a_high);
EXTERN void Scan_WriteError (char *a_, unsigned int _a_high);

/*
   TerminateOnError - exits with status 1 if we call WriteError.
*/

EXTERN void Scan_TerminateOnError (void);

/*
   DefineComments - defines the start of comments within the source
                    file.

                    The characters in Start define the comment start
                    and characters in End define the end.
                    The BOOLEAN eoln determine whether the comment
                    is terminated by end of line. If eoln is TRUE
                    then End is ignored.

                    If this procedure is never called then no comments
                    are allowed.
*/

EXTERN void Scan_DefineComments (char *Start_, unsigned int _Start_high, char *End_, unsigned int _End_high, unsigned int eoln);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
