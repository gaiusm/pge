/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/LMathLib0.def.  */


#if !defined (_LMathLib0_H)
#   define _LMathLib0_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_LMathLib0_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define LMathLib0_pi 3.1415926535897932384626433832795028841972
#   define LMathLib0_exp1 2.7182818284590452353602874713526624977572
EXTERN long double LMathLib0_sqrt (long double x);
EXTERN long double LMathLib0_exp (long double x);
EXTERN long double LMathLib0_ln (long double x);
EXTERN long double LMathLib0_sin (long double x);
EXTERN long double LMathLib0_cos (long double x);
EXTERN long double LMathLib0_tan (long double x);
EXTERN long double LMathLib0_arctan (long double x);
EXTERN int LMathLib0_entier (long double x);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
