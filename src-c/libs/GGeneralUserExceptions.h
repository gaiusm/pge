/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/GeneralUserExceptions.def.  */


#if !defined (_GeneralUserExceptions_H)
#   define _GeneralUserExceptions_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_GeneralUserExceptions_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef enum {GeneralUserExceptions_problem, GeneralUserExceptions_disaster} GeneralUserExceptions_GeneralExceptions;

EXTERN void GeneralUserExceptions_RaiseGeneralException (GeneralUserExceptions_GeneralExceptions exception, char *text_, unsigned int _text_high);
EXTERN unsigned int GeneralUserExceptions_IsGeneralException (void);
EXTERN GeneralUserExceptions_GeneralExceptions GeneralUserExceptions_GeneralException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
