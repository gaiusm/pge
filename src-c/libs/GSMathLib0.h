/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/SMathLib0.def.  */


#if !defined (_SMathLib0_H)
#   define _SMathLib0_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_SMathLib0_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define SMathLib0_pi 3.1415926535897932384626433832795028841972
#   define SMathLib0_exp1 2.7182818284590452353602874713526624977572
EXTERN float SMathLib0_sqrt (float x);
EXTERN float SMathLib0_exp (float x);
EXTERN float SMathLib0_ln (float x);
EXTERN float SMathLib0_sin (float x);
EXTERN float SMathLib0_cos (float x);
EXTERN float SMathLib0_tan (float x);
EXTERN float SMathLib0_arctan (float x);
EXTERN int SMathLib0_entier (float x);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
