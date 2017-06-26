/* automatically created by mc from ../Fractions.def.  */


#if !defined (_Fractions_H)
#   define _Fractions_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_Fractions_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (Fractions_Fract_D)
#  define Fractions_Fract_D
   typedef void *Fractions_Fract;
#endif


/*
   root - grafts fract into the roots of the garbage tree.
*/

EXTERN Fractions_Fract Fractions_root (Fractions_Fract f);

/*
   unroot - removes, f, from the roots of the garbage tree.
*/

EXTERN Fractions_Fract Fractions_unroot (Fractions_Fract f);

/*
   pi - returns the approximation of pi as a Fract.
*/

EXTERN Fractions_Fract Fractions_pi (void);

/*
   zero - returns the fraction, 0.
*/

EXTERN Fractions_Fract Fractions_zero (void);

/*
   one - returns the fraction, 1/1.
*/

EXTERN Fractions_Fract Fractions_one (void);

/*
   two - returns the value 2 as a fraction.
*/

EXTERN Fractions_Fract Fractions_two (void);

/*
   half - returns 1/2.
*/

EXTERN Fractions_Fract Fractions_half (void);

/*
   quarter - returns 1/4.
*/

EXTERN Fractions_Fract Fractions_quarter (void);

/*
   oneOverN - returns 1/n.
*/

EXTERN Fractions_Fract Fractions_oneOverN (long unsigned int n);

/*
   root2 - returns 2^.5
*/

EXTERN Fractions_Fract Fractions_root2 (void);

/*
   root3 - returns 3^.5
*/

EXTERN Fractions_Fract Fractions_root3 (void);

/*
   root6 - returns 6^.5
*/

EXTERN Fractions_Fract Fractions_root6 (void);

/*
   integer - return, i, as a fraction.
*/

EXTERN Fractions_Fract Fractions_integer (long int i);

/*
   cardinal - returns a cardinal as a fraction.
*/

EXTERN Fractions_Fract Fractions_cardinal (long unsigned int i);

/*
   isZero - returns TRUE if the fraction is zero.
*/

EXTERN unsigned int Fractions_isZero (Fractions_Fract f);

/*
   isOne - returns TRUE if the fraction is one.
*/

EXTERN unsigned int Fractions_isOne (Fractions_Fract f);

/*
   isEqual - returns TRUE if Fracts, l, and, r, are equal.
*/

EXTERN unsigned int Fractions_isEqual (Fractions_Fract l, Fractions_Fract r);

/*
   isLess - returns TRUE if l < r.
*/

EXTERN unsigned int Fractions_isLess (Fractions_Fract l, Fractions_Fract r);

/*
   isGreater - returns TRUE if l > r.
*/

EXTERN unsigned int Fractions_isGreater (Fractions_Fract l, Fractions_Fract r);

/*
   negate - negate fraction, f.
*/

EXTERN Fractions_Fract Fractions_negate (Fractions_Fract f);

/*
   power - return l^r.
*/

EXTERN Fractions_Fract Fractions_power (Fractions_Fract l, Fractions_Fract r);

/*
   mult - return l * r.
*/

EXTERN Fractions_Fract Fractions_mult (Fractions_Fract l, Fractions_Fract r);

/*
   div - return l / r.
*/

EXTERN Fractions_Fract Fractions_div (Fractions_Fract l, Fractions_Fract r);

/*
   reciprocal - return 1/f.
*/

EXTERN Fractions_Fract Fractions_reciprocal (Fractions_Fract f);

/*
   sub - returns the expression, l - r.
*/

EXTERN Fractions_Fract Fractions_sub (Fractions_Fract l, Fractions_Fract r);

/*
   add - returns a new fraction of the result, l+r.
*/

EXTERN Fractions_Fract Fractions_add (Fractions_Fract l, Fractions_Fract r);

/*
   inc - returns, l, after, r, has been added.
*/

EXTERN Fractions_Fract Fractions_inc (Fractions_Fract l, Fractions_Fract r);

/*
   dec - returns, l, after, r, has been subtracted.
*/

EXTERN Fractions_Fract Fractions_dec (Fractions_Fract l, Fractions_Fract r);

/*
   simplify - simplify the fraction or expression.
*/

EXTERN Fractions_Fract Fractions_simplify (Fractions_Fract f);

/*
   initFract - initialise a fraction, which is expressed as:  w + n/d.
*/

EXTERN Fractions_Fract Fractions_initFract (long unsigned int w, long unsigned int n, long unsigned int d);

/*
   add3 - returns a new fraction which contains the result of a+b+c.
*/

EXTERN Fractions_Fract Fractions_add3 (Fractions_Fract a, Fractions_Fract b, Fractions_Fract c);

/*
   mult3 - returns a new fraction which contains the result of a * b * c.
*/

EXTERN Fractions_Fract Fractions_mult3 (Fractions_Fract a, Fractions_Fract b, Fractions_Fract c);

/*
   mark - marks Fract, f, to be saved from garbage collection.
*/

EXTERN void Fractions_mark (Fractions_Fract f);

/*
   dup - returns a duplicate of Fract, f.
*/

EXTERN Fractions_Fract Fractions_dup (Fractions_Fract f);

/*
   areEqual - return TRUE if l = r.
*/

EXTERN unsigned int Fractions_areEqual (Fractions_Fract l, Fractions_Fract r);

/*
   getReal - returns a REAL value of, f.
*/

EXTERN double Fractions_getReal (Fractions_Fract f);

/*
   getFract - returns the, whole, numerator and demonimator value of, f.
*/

EXTERN void Fractions_getFract (Fractions_Fract f, long unsigned int *w, long unsigned int *n, long unsigned int *d);

/*
   getLongReal - returns a LONGREAL value of, f.
*/

EXTERN long double Fractions_getLongReal (Fractions_Fract f);

/*
   putReal - returns a fraction in the range whole number + x/10000
*/

EXTERN Fractions_Fract Fractions_putReal (double r);

/*
   writeFract - displays fraction, f.
*/

EXTERN void Fractions_writeFract (Fractions_Fract f);

/*
   isPositive - returns TRUE if, f, is positive.
*/

EXTERN unsigned int Fractions_isPositive (Fractions_Fract f);

/*
   isNegative - returns TRUE if the value is negative.
*/

EXTERN unsigned int Fractions_isNegative (Fractions_Fract f);

/*
   sin - return sin of angle, f.
*/

EXTERN Fractions_Fract Fractions_sin (Fractions_Fract f);

/*
   cos - return cos of angle, f.
*/

EXTERN Fractions_Fract Fractions_cos (Fractions_Fract f);

/*
   tan - return tan of angle, f.
*/

EXTERN Fractions_Fract Fractions_tan (Fractions_Fract f);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
