/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/LongMath.def.  */


#if !defined (_LongMath_H)
#   define _LongMath_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_LongMath_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define LongMath_pi 3.1415926535897932384626433832795028841972
#   define LongMath_exp1 2.7182818284590452353602874713526624977572
EXTERN long double LongMath_sqrt (long double x);
EXTERN long double LongMath_exp (long double x);
EXTERN long double LongMath_ln (long double x);
EXTERN long double LongMath_sin (long double x);
EXTERN long double LongMath_cos (long double x);
EXTERN long double LongMath_tan (long double x);
EXTERN long double LongMath_arcsin (long double x);
EXTERN long double LongMath_arccos (long double x);
EXTERN long double LongMath_arctan (long double x);
EXTERN long double LongMath_power (long double base, long double exponent);
EXTERN int LongMath_round (long double x);
EXTERN unsigned int LongMath_IsRMathException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
