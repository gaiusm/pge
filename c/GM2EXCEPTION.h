/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/M2EXCEPTION.def.  */


#if !defined (_M2EXCEPTION_H)
#   define _M2EXCEPTION_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_M2EXCEPTION_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef enum {M2EXCEPTION_indexException, M2EXCEPTION_rangeException, M2EXCEPTION_caseSelectException, M2EXCEPTION_invalidLocation, M2EXCEPTION_functionException, M2EXCEPTION_wholeValueException, M2EXCEPTION_wholeDivException, M2EXCEPTION_realValueException, M2EXCEPTION_realDivException, M2EXCEPTION_complexValueException, M2EXCEPTION_complexDivException, M2EXCEPTION_protException, M2EXCEPTION_sysException, M2EXCEPTION_coException, M2EXCEPTION_exException} M2EXCEPTION_M2Exceptions;

EXTERN M2EXCEPTION_M2Exceptions M2EXCEPTION_M2Exception (void);
EXTERN unsigned int M2EXCEPTION_IsM2Exception (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
