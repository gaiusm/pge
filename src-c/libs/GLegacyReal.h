/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/LegacyReal.def.  */


#if !defined (_LegacyReal_H)
#   define _LegacyReal_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_LegacyReal_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef float LegacyReal_REAL;

#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
