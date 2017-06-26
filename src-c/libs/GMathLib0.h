/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/MathLib0.def.  */


#if !defined (_MathLib0_H)
#   define _MathLib0_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_MathLib0_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define MathLib0_pi 3.1415926535897932384626433832795028841972
#   define MathLib0_exp1 2.7182818284590452353602874713526624977572
EXTERN double MathLib0_sqrt (double x);
EXTERN double MathLib0_exp (double x);
EXTERN double MathLib0_ln (double x);
EXTERN double MathLib0_sin (double x);
EXTERN double MathLib0_cos (double x);
EXTERN double MathLib0_tan (double x);
EXTERN double MathLib0_arctan (double x);
EXTERN int MathLib0_entier (double x);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
