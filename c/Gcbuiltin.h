/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/cbuiltin.def.  */


#if !defined (_cbuiltin_H)
#   define _cbuiltin_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include <complex.h>
#   include "GSYSTEM.h"

#   if defined (_cbuiltin_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void * cbuiltin_alloca (unsigned int i);
EXTERN void * cbuiltin_memcpy (void * dest, void * src, unsigned int n);
EXTERN unsigned int cbuiltin_isfinite (double x);
EXTERN unsigned int cbuiltin_isfinitel (long double x);
EXTERN unsigned int cbuiltin_isfinitef (float x);
EXTERN unsigned int cbuiltin_isinf_sign (double x);
EXTERN unsigned int cbuiltin_isinf_signl (long double x);
EXTERN unsigned int cbuiltin_isinf_signf (float x);
EXTERN float cbuiltin_sinf (float x);
EXTERN double cbuiltin_sin (double x);
EXTERN long double cbuiltin_sinl (long double x);
EXTERN float cbuiltin_cosf (float x);
EXTERN double cbuiltin_cos (double x);
EXTERN long double cbuiltin_cosl (long double x);
EXTERN float cbuiltin_atan2f (float x, float y);
EXTERN double cbuiltin_atan2 (double x, double y);
EXTERN long double cbuiltin_atan2l (long double x, long double y);
EXTERN float cbuiltin_sqrtf (float x);
EXTERN double cbuiltin_sqrt (double x);
EXTERN long double cbuiltin_sqrtl (long double x);
EXTERN float cbuiltin_fabsf (float x);
EXTERN double cbuiltin_fabs (double x);
EXTERN long double cbuiltin_fabsl (long double x);
EXTERN float cbuiltin_logf (float x);
EXTERN double cbuiltin_log (double x);
EXTERN long double cbuiltin_logl (long double x);
EXTERN float cbuiltin_expf (float x);
EXTERN double cbuiltin_exp (double x);
EXTERN long double cbuiltin_expl (long double x);
EXTERN float cbuiltin_log10f (float x);
EXTERN double cbuiltin_log10 (double x);
EXTERN long double cbuiltin_log10l (long double x);
EXTERN float cbuiltin_exp10f (float x);
EXTERN double cbuiltin_exp10 (double x);
EXTERN long double cbuiltin_exp10l (long double x);
EXTERN int cbuiltin_ilogbf (float x);
EXTERN int cbuiltin_ilogb (double x);
EXTERN int cbuiltin_ilogbl (long double x);
EXTERN double cbuiltin_significand (double r);
EXTERN float cbuiltin_significandf (float s);
EXTERN long double cbuiltin_significandl (long double l);
EXTERN double cbuiltin_modf (double x, double *y);
EXTERN float cbuiltin_modff (float x, float *y);
EXTERN long double cbuiltin_modfl (long double x, long double *y);
EXTERN double cbuiltin_nextafter (double x, double y);
EXTERN float cbuiltin_nextafterf (float x, float y);
EXTERN long double cbuiltin_nextafterl (long double x, long double y);
EXTERN double cbuiltin_nexttoward (double x, double y);
EXTERN float cbuiltin_nexttowardf (float x, float y);
EXTERN long double cbuiltin_nexttowardl (long double x, long double y);
EXTERN double cbuiltin_scalb (double x, double n);
EXTERN float cbuiltin_scalbf (float x, float n);
EXTERN long double cbuiltin_scalbl (long double x, long double n);
EXTERN double cbuiltin_scalbn (double x, int n);
EXTERN float cbuiltin_scalbnf (float x, int n);
EXTERN long double cbuiltin_scalbnl (long double x, int n);
EXTERN double cbuiltin_scalbln (double x, long int n);
EXTERN float cbuiltin_scalblnf (float x, long int n);
EXTERN long double cbuiltin_scalblnl (long double x, long int n);
EXTERN float cbuiltin_cabsf (float complex z);
EXTERN double cbuiltin_cabs (double complex z);
EXTERN long double cbuiltin_cabsl (long double complex z);
EXTERN float cbuiltin_cargf (float complex z);
EXTERN double cbuiltin_carg (double complex z);
EXTERN long double cbuiltin_cargl (long double complex z);
EXTERN float complex cbuiltin_conjf (float complex z);
EXTERN double complex cbuiltin_conj (double complex z);
EXTERN long double complex cbuiltin_conjl (long double complex z);
EXTERN float complex cbuiltin_cpowf (float complex base, float exp);
EXTERN double complex cbuiltin_cpow (double complex base, double exp);
EXTERN long double complex cbuiltin_cpowl (long double complex base, long double exp);
EXTERN float complex cbuiltin_csqrtf (float complex z);
EXTERN double complex cbuiltin_csqrt (double complex z);
EXTERN long double complex cbuiltin_csqrtl (long double complex z);
EXTERN float complex cbuiltin_cexpf (float complex z);
EXTERN double complex cbuiltin_cexp (double complex z);
EXTERN long double complex cbuiltin_cexpl (long double complex z);
EXTERN float complex cbuiltin_clogf (float complex z);
EXTERN double complex cbuiltin_clog (double complex z);
EXTERN long double complex cbuiltin_clogl (long double complex z);
EXTERN float complex cbuiltin_csinf (float complex z);
EXTERN double complex cbuiltin_csin (double complex z);
EXTERN long double complex cbuiltin_csinl (long double complex z);
EXTERN float complex cbuiltin_ccosf (float complex z);
EXTERN double complex cbuiltin_ccos (double complex z);
EXTERN long double complex cbuiltin_ccosl (long double complex z);
EXTERN float complex cbuiltin_ctanf (float complex z);
EXTERN double complex cbuiltin_ctan (double complex z);
EXTERN long double complex cbuiltin_ctanl (long double complex z);
EXTERN float complex cbuiltin_casinf (float complex z);
EXTERN double complex cbuiltin_casin (double complex z);
EXTERN long double complex cbuiltin_casinl (long double complex z);
EXTERN float complex cbuiltin_cacosf (float complex z);
EXTERN double complex cbuiltin_cacos (double complex z);
EXTERN long double complex cbuiltin_cacosl (long double complex z);
EXTERN float complex cbuiltin_catanf (float complex z);
EXTERN double complex cbuiltin_catan (double complex z);
EXTERN long double complex cbuiltin_catanl (long double complex z);
EXTERN void * cbuiltin_index (void * s, int c);
EXTERN void * cbuiltin_rindex (void * s, int c);
EXTERN int cbuiltin_memcmp (void * s1, void * s2, unsigned int n);
EXTERN void * cbuiltin_memmove (void * s1, void * s2, unsigned int n);
EXTERN void * cbuiltin_memset (void * s, int c, unsigned int n);
EXTERN void * cbuiltin_strcat (void * dest, void * src);
EXTERN void * cbuiltin_strncat (void * dest, void * src, unsigned int n);
EXTERN void * cbuiltin_strcpy (void * dest, void * src);
EXTERN void * cbuiltin_strncpy (void * dest, void * src, unsigned int n);
EXTERN int cbuiltin_strcmp (void * s1, void * s2);
EXTERN int cbuiltin_strncmp (void * s1, void * s2, unsigned int n);
EXTERN int cbuiltin_strlen (void * s);
EXTERN void * cbuiltin_strstr (void * haystack, void * needle);
EXTERN void * cbuiltin_strpbrk (void * s, void * accept);
EXTERN unsigned int cbuiltin_strspn (void * s, void * accept);
EXTERN unsigned int cbuiltin_strcspn (void * s, void * accept);
EXTERN void * cbuiltin_strchr (void * s, int c);
EXTERN void * cbuiltin_strrchr (void * s, int c);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
