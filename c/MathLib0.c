/* automatically created by mc from /home/gaius/GM2/graft-5.4.0/gcc-5.4.0/gcc/gm2/gm2-libs/MathLib0.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include <complex.h>
#define _MathLib0_H
#define _MathLib0_C

#   include "Gcbuiltin.h"
#   include "Glibm.h"

#   define MathLib0_pi 3.1415926535897932384626433832795028841972
#   define MathLib0_exp1 2.7182818284590452353602874713526624977572
double MathLib0_sqrt (double x);
double MathLib0_exp (double x);
double MathLib0_ln (double x);
double MathLib0_sin (double x);
double MathLib0_cos (double x);
double MathLib0_tan (double x);
double MathLib0_arctan (double x);
int MathLib0_entier (double x);
static long double sqrtl (long double x);
static float sqrts (float x);
static float exps (float x);
static long double expl (long double x);
static float lns (float x);
static long double lnl (long double x);
static long double sinl (long double x);
static float sins (float x);
static float coss (float x);
static long double cosl (long double x);
static long double tanl (long double x);
static float tans (float x);
static float arctans (float x);
static long double arctanl (long double x);
static int entiers (float x);
static int entierl (long double x);

static long double sqrtl (long double x)
{
  return cbuiltin_sqrtl (x);
}

static float sqrts (float x)
{
  return cbuiltin_sqrtf (x);
}

static float exps (float x)
{
  return libm_expf (x);
}

static long double expl (long double x)
{
  return libm_expl (x);
}

static float lns (float x)
{
  return (libm_logf (x))/(libm_logf (MathLib0_exp1));
}

static long double lnl (long double x)
{
  return (libm_logl (x))/(libm_logl (MathLib0_exp1));
}

static long double sinl (long double x)
{
  return cbuiltin_sinl (x);
}

static float sins (float x)
{
  return cbuiltin_sinf (x);
}

static float coss (float x)
{
  return cbuiltin_cosf (x);
}

static long double cosl (long double x)
{
  return cbuiltin_cosl (x);
}

static long double tanl (long double x)
{
  return libm_tanl (x);
}

static float tans (float x)
{
  return libm_tanf (x);
}

static float arctans (float x)
{
  return libm_atanf (x);
}

static long double arctanl (long double x)
{
  return libm_atanl (x);
}

static int entiers (float x)
{
  return (int) (libm_floorf (x));
}

static int entierl (long double x)
{
  return (int) (libm_floorl (x));
}

double MathLib0_sqrt (double x)
{
  return cbuiltin_sqrt (x);
}

double MathLib0_exp (double x)
{
  return libm_exp (x);
}

double MathLib0_ln (double x)
{
  return (libm_log (x))/(libm_log (MathLib0_exp1));
}

double MathLib0_sin (double x)
{
  return cbuiltin_sin (x);
}

double MathLib0_cos (double x)
{
  return cbuiltin_cos (x);
}

double MathLib0_tan (double x)
{
  return libm_tan (x);
}

double MathLib0_arctan (double x)
{
  return libm_atan (x);
}

int MathLib0_entier (double x)
{
  return (int) (libm_floor (x));
}

void _M2_MathLib0_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_MathLib0_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
