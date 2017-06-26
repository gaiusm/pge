/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/ComplexMath.def.  */


#if !defined (_ComplexMath_H)
#   define _ComplexMath_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include <complex.h>

#   if defined (_ComplexMath_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define ComplexMath_i ( (0.0) + (0.0 * I))
#   define ComplexMath_one ( (1.0) + (1.0 * I))
#   define ComplexMath_zero ( (0.0) + (0.0 * I))
EXTERN double ComplexMath_abs (double complex z);
EXTERN double ComplexMath_arg (double complex z);
EXTERN double complex ComplexMath_conj (double complex z);
EXTERN double complex ComplexMath_power (double complex base, double exponent);
EXTERN double complex ComplexMath_sqrt (double complex z);
EXTERN double complex ComplexMath_exp (double complex z);
EXTERN double complex ComplexMath_ln (double complex z);
EXTERN double complex ComplexMath_sin (double complex z);
EXTERN double complex ComplexMath_cos (double complex z);
EXTERN double complex ComplexMath_tan (double complex z);
EXTERN double complex ComplexMath_arcsin (double complex z);
EXTERN double complex ComplexMath_arccos (double complex z);
EXTERN double complex ComplexMath_arctan (double complex z);
EXTERN double complex ComplexMath_polarToComplex (double abs_, double arg);
EXTERN double complex ComplexMath_scalarMult (double scalar, double complex z);
EXTERN unsigned int ComplexMath_IsCMathException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
