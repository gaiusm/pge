/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/EXCEPTIONS.def.  */


#if !defined (_EXCEPTIONS_H)
#   define _EXCEPTIONS_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_EXCEPTIONS_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (EXCEPTIONS_ExceptionSource_D)
#  define EXCEPTIONS_ExceptionSource_D
   typedef void *EXCEPTIONS_ExceptionSource;
#endif

typedef unsigned int EXCEPTIONS_ExceptionNumber;

EXTERN void EXCEPTIONS_AllocateSource (EXCEPTIONS_ExceptionSource *newSource);
EXTERN void EXCEPTIONS_RAISE (EXCEPTIONS_ExceptionSource source, EXCEPTIONS_ExceptionNumber number, char *message_, unsigned int _message_high);
EXTERN EXCEPTIONS_ExceptionNumber EXCEPTIONS_CurrentNumber (EXCEPTIONS_ExceptionSource source);
EXTERN void EXCEPTIONS_GetMessage (char *text, unsigned int _text_high);
EXTERN unsigned int EXCEPTIONS_IsCurrentSource (EXCEPTIONS_ExceptionSource source);
EXTERN unsigned int EXCEPTIONS_IsExceptionalExecution (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
