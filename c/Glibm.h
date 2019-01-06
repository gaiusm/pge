/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/libm.def.  */


#if !defined (_libm_H)
#   define _libm_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_libm_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN double libm_sin (double x);
EXTERN long double libm_sinl (long double x);
EXTERN float libm_sinf (float x);
EXTERN double libm_cos (double x);
EXTERN long double libm_cosl (long double x);
EXTERN float libm_cosf (float x);
EXTERN double libm_tan (double x);
EXTERN long double libm_tanl (long double x);
EXTERN float libm_tanf (float x);
EXTERN double libm_sqrt (double x);
EXTERN long double libm_sqrtl (long double x);
EXTERN float libm_sqrtf (float x);
EXTERN double libm_asin (double x);
EXTERN long double libm_asinl (long double x);
EXTERN float libm_asinf (float x);
EXTERN double libm_acos (double x);
EXTERN long double libm_acosl (long double x);
EXTERN float libm_acosf (float x);
EXTERN double libm_atan (double x);
EXTERN long double libm_atanl (long double x);
EXTERN float libm_atanf (float x);
EXTERN double libm_atan2 (double x, double y);
EXTERN long double libm_atan2l (long double x, long double y);
EXTERN float libm_atan2f (float x, float y);
EXTERN double libm_exp (double x);
EXTERN long double libm_expl (long double x);
EXTERN float libm_expf (float x);
EXTERN double libm_log (double x);
EXTERN long double libm_logl (long double x);
EXTERN float libm_logf (float x);
EXTERN double libm_exp10 (double x);
EXTERN long double libm_exp10l (long double x);
EXTERN float libm_exp10f (float x);
EXTERN double libm_pow (double x, double y);
EXTERN long double libm_powl (long double x, long double y);
EXTERN float libm_powf (float x, float y);
EXTERN double libm_floor (double x);
EXTERN long double libm_floorl (long double x);
EXTERN float libm_floorf (float x);
EXTERN double libm_ceil (double x);
EXTERN long double libm_ceill (long double x);
EXTERN float libm_ceilf (float x);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
