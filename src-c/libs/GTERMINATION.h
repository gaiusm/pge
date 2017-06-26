/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/TERMINATION.def.  */


#if !defined (_TERMINATION_H)
#   define _TERMINATION_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_TERMINATION_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN unsigned int TERMINATION_IsTerminating (void);
EXTERN unsigned int TERMINATION_HasHalted (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
