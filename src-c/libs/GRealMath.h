/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RealMath.def.  */


#if !defined (_RealMath_H)
#   define _RealMath_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_RealMath_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define RealMath_pi 3.1415926535897932384626433832795028841972
#   define RealMath_exp1 2.7182818284590452353602874713526624977572
EXTERN double RealMath_sqrt (double x);
EXTERN double RealMath_exp (double x);
EXTERN double RealMath_ln (double x);
EXTERN double RealMath_sin (double x);
EXTERN double RealMath_cos (double x);
EXTERN double RealMath_tan (double x);
EXTERN double RealMath_arcsin (double x);
EXTERN double RealMath_arccos (double x);
EXTERN double RealMath_arctan (double x);
EXTERN double RealMath_power (double base, double exponent);
EXTERN int RealMath_round (double x);
EXTERN unsigned int RealMath_IsRMathException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
