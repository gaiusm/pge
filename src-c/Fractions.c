/* automatically created by mc from ../Fractions.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#include <stddef.h>
#include <string.h>
#include <limits.h>
#define _Fractions_H
#define _Fractions_C

#   include "Glibc.h"
#   include "GStrLib.h"
#   include "GGC.h"
#   include "GAssertion.h"
#   include "GStringConvert.h"
#   include "GDynamicStrings.h"
#   include "GSYSTEM.h"
#   include "GASCII.h"
#   include "GM2RTS.h"

#   define runRegression FALSE
#   define trigTerm 5
typedef struct doProcedure_p doProcedure;

typedef struct fract_r fract;

typedef enum {oFract, oAdd, oSub, oMult, oDiv, oNegate, oPower, oSin, oCos, oTan} Operator;

typedef enum {NONE, PI, E, ROOT2, ROOT3, ROOT6, EXPR} Special;

typedef fract *Fractions_Fract;

typedef unsigned int (*doProcedure_t) (Fractions_Fract);
struct doProcedure_p { doProcedure_t proc; };

struct fract_r {
                 unsigned int positive;
                 long unsigned int whole;
                 long unsigned int num;
                 long unsigned int demon;
                 Operator op;
                 Fractions_Fract left;
                 Fractions_Fract right;
                 unsigned int dirty;
                 Special special;
                 GC_entity fentity;
               };

static unsigned int Initialized;
static GC_garbage fractHeap;
static Fractions_Fract captured;

/*
   root - grafts fract into the roots of the garbage tree.
*/

Fractions_Fract Fractions_root (Fractions_Fract f);

/*
   unroot - removes, f, from the roots of the garbage tree.
*/

Fractions_Fract Fractions_unroot (Fractions_Fract f);

/*
   pi - returns the approximation of pi as a Fract.
*/

Fractions_Fract Fractions_pi (void);

/*
   zero - returns the fraction, 0.
*/

Fractions_Fract Fractions_zero (void);

/*
   one - returns the fraction, 1/1.
*/

Fractions_Fract Fractions_one (void);

/*
   two - returns the value 2 as a fraction.
*/

Fractions_Fract Fractions_two (void);

/*
   half - returns 1/2.
*/

Fractions_Fract Fractions_half (void);

/*
   quarter - returns 1/4.
*/

Fractions_Fract Fractions_quarter (void);

/*
   oneOverN - returns 1/n.
*/

Fractions_Fract Fractions_oneOverN (long unsigned int n);

/*
   root2 -
*/

Fractions_Fract Fractions_root2 (void);

/*
   root3 - returns 3^.5.
*/

Fractions_Fract Fractions_root3 (void);

/*
   root6 - returns 6^.5.
*/

Fractions_Fract Fractions_root6 (void);

/*
   integer - return, i, as a fraction.
*/

Fractions_Fract Fractions_integer (long int i);

/*
   cardinal - returns a cardinal as a fraction.
*/

Fractions_Fract Fractions_cardinal (long unsigned int i);

/*
   isZero - returns TRUE if the fraction is zero.
*/

unsigned int Fractions_isZero (Fractions_Fract f);

/*
   isOne - returns TRUE if the fraction is one.
*/

unsigned int Fractions_isOne (Fractions_Fract f);

/*
   isEqual - returns TRUE if Fracts, l, and, r, are equal.
*/

unsigned int Fractions_isEqual (Fractions_Fract l, Fractions_Fract r);

/*
   isLess - returns TRUE if l < r.
*/

unsigned int Fractions_isLess (Fractions_Fract l, Fractions_Fract r);

/*
   isGreater - returns TRUE if l > r.
*/

unsigned int Fractions_isGreater (Fractions_Fract l, Fractions_Fract r);

/*
   negate - negate fraction, f.
*/

Fractions_Fract Fractions_negate (Fractions_Fract f);

/*
   power - return l^r.
*/

Fractions_Fract Fractions_power (Fractions_Fract l, Fractions_Fract r);

/*
   mult - return l * r
*/

Fractions_Fract Fractions_mult (Fractions_Fract l, Fractions_Fract r);

/*
   div - return l / r.
*/

Fractions_Fract Fractions_div (Fractions_Fract l, Fractions_Fract r);

/*
   reciprocal - return 1/f.
*/

Fractions_Fract Fractions_reciprocal (Fractions_Fract f);

/*
   sub - returns the expression, l - r.
*/

Fractions_Fract Fractions_sub (Fractions_Fract l, Fractions_Fract r);

/*
   add - returns a new fraction of the result, l+r.
*/

Fractions_Fract Fractions_add (Fractions_Fract l, Fractions_Fract r);

/*
   inc - returns, l, after, r, has been added.
*/

Fractions_Fract Fractions_inc (Fractions_Fract l, Fractions_Fract r);

/*
   dec - returns, l, after, r, has been subtracted.
*/

Fractions_Fract Fractions_dec (Fractions_Fract l, Fractions_Fract r);

/*
   simplify - simplify the fraction or expression.
*/

Fractions_Fract Fractions_simplify (Fractions_Fract f);

/*
   initFract - initialise a fraction, which is expressed as:  w + n/d.
*/

Fractions_Fract Fractions_initFract (long unsigned int w, long unsigned int n, long unsigned int d);

/*
   add3 - returns a new fraction which contains the result of a+b+c.
*/

Fractions_Fract Fractions_add3 (Fractions_Fract a, Fractions_Fract b, Fractions_Fract c);

/*
   mult3 - returns a new fraction which contains the result of a * b * c.
*/

Fractions_Fract Fractions_mult3 (Fractions_Fract a, Fractions_Fract b, Fractions_Fract c);

/*
   mark - marks Fract, f, to be saved from garbage collection.
*/

void Fractions_mark (Fractions_Fract f);

/*
   dup - returns a duplicate of Fract, f.
*/

Fractions_Fract Fractions_dup (Fractions_Fract f);

/*
   areEqual - return TRUE if l = r.
*/

unsigned int Fractions_areEqual (Fractions_Fract l, Fractions_Fract r);

/*
   getReal - returns a REAL value of, f.
*/

double Fractions_getReal (Fractions_Fract f);

/*
   getFract - returns the, whole, numerator and demonimator value of, f.
*/

void Fractions_getFract (Fractions_Fract f, long unsigned int *w, long unsigned int *n, long unsigned int *d);

/*
   getLongReal - returns a LONGREAL value of, f.
*/

long double Fractions_getLongReal (Fractions_Fract f);

/*
   putReal - returns a fraction in the range whole number + x/10000
*/

Fractions_Fract Fractions_putReal (double r);

/*
   writeFract - displays fraction, f.
*/

void Fractions_writeFract (Fractions_Fract f);

/*
   isPositive - returns TRUE if, f, is positive.
*/

unsigned int Fractions_isPositive (Fractions_Fract f);

/*
   isNegative - returns TRUE if the value is negative.
*/

unsigned int Fractions_isNegative (Fractions_Fract f);

/*
   sin - return sin of angle, f.
*/

Fractions_Fract Fractions_sin (Fractions_Fract f);

/*
   cos - return cos of angle, f.
*/

Fractions_Fract Fractions_cos (Fractions_Fract f);

/*
   tan - return tan of angle, f.
*/

Fractions_Fract Fractions_tan (Fractions_Fract f);

/*
   writeCard -
*/

static void writeCard (unsigned int c);

/*
   writeAddress -
*/

static void writeAddress (void * a);

/*
   writeNspace -
*/

static void writeNspace (unsigned int n);

/*
   writeNspace -
*/

static unsigned int capture (Fractions_Fract f);

/*
   isSpecial - return TRUE if, f, is a special.
*/

static unsigned int isSpecial (Fractions_Fract f);

/*
   isConst - returns if, f, is a fractional constant.
*/

static unsigned int isConst (Fractions_Fract f);

/*
   isSpecialConst -
*/

static unsigned int isSpecialConst (Fractions_Fract f);

/*
   isExpr - return TRUE if, f, is an expression.
*/

static unsigned int isExpr (Fractions_Fract f);

/*
   writeString - writes a string to stdout.
*/

static void writeString (char *a_, unsigned int _a_high);

/*
   writeCstring - writes a C string to stdout.
*/

static void writeCstring (void * a);

/*
   writeLongcard -
*/

static void writeLongcard (long unsigned int c);

/*
   writeLongint -
*/

static void writeLongint (long int i);

/*
   writeLn - writes a newline.
*/

static void writeLn (void);

/*
   dirty - sets Fract, f, to dirty.
*/

static Fractions_Fract dirty (Fractions_Fract f);

/*
   clean - sets Fract, f, to clean.
*/

static Fractions_Fract clean (Fractions_Fract f);

/*
   negatec - negates constant, -f.
*/

static Fractions_Fract negatec (Fractions_Fract f);

/*
   negates - negate special.
*/

static Fractions_Fract negates (Fractions_Fract f);

/*
   equalDemon - converts both fractions to have equal demoninators.
*/

static void equalDemon (Fractions_Fract l, Fractions_Fract r);

/*
   addND - add the numerator/demonimator pairs of, l, and, r.
           It propagates the carry into whole.
           l := l+r  is performed.
*/

static void addND (Fractions_Fract l, Fractions_Fract r);

/*
   subND - sub the numerator/demonimator pairs of, l, and, r.
           It returns TRUE if it needs to borrow.
           l := l-r  is performed.
*/

static unsigned int subND (Fractions_Fract l, Fractions_Fract r);

/*
   addc - add constant fractions.
*/

static Fractions_Fract addc (Fractions_Fract l, Fractions_Fract r);

/*
   buildUnary - returns (operator, l).
*/

static Fractions_Fract buildUnary (Operator operator, Fractions_Fract l);

/*
   buildBinary - returns (operator, l, r).
*/

static Fractions_Fract buildBinary (Operator operator, Fractions_Fract l, Fractions_Fract r);

/*
   adds - returns expression l + r.
*/

static Fractions_Fract adds (Fractions_Fract l, Fractions_Fract r);

/*
   powers - return an expression l^r.
*/

static Fractions_Fract powers (Fractions_Fract l, Fractions_Fract r);

/*
   powerc - compute constant, l^r
*/

static Fractions_Fract powerc (Fractions_Fract l, Fractions_Fract r);

/*
   mults - returns expression l * r.
*/

static Fractions_Fract mults (Fractions_Fract l, Fractions_Fract r);

/*
   multc - calculate l * r from constants.
*/

static Fractions_Fract multc (Fractions_Fract l, Fractions_Fract r);

/*
   divc - calculate l / r from constants.
*/

static Fractions_Fract divc (Fractions_Fract l, Fractions_Fract r);

/*
   divs - calculate l / r from one or more specials.
*/

static Fractions_Fract divs (Fractions_Fract l, Fractions_Fract r);

/*
   reciprocals - return 1/f from a special.
*/

static Fractions_Fract reciprocals (Fractions_Fract f);

/*
   reciprocalc - return 1/f from a constant.
*/

static Fractions_Fract reciprocalc (Fractions_Fract f);

/*
   subc - returns a constant from, l - r.
*/

static Fractions_Fract subc (Fractions_Fract l, Fractions_Fract r);

/*
   subs - returns the expression, l - r.
*/

static Fractions_Fract subs (Fractions_Fract l, Fractions_Fract r);

/*
   stop - debugging hook.
*/

static void stop (void);

/*
   simplifyc - returns a simplified fraction, f.
*/

static Fractions_Fract simplifyc (Fractions_Fract f);

/*
   specialToConst - returns TRUE if, f, was changed to a const.
*/

static unsigned int specialToConst (Fractions_Fract f);

/*
   walkFract - walks fract, f, and marks each node.
*/

static void walkFract (Fractions_Fract f);

/*
   walkExpr -
*/

static unsigned int walkExpr (Fractions_Fract f, doProcedure p);

/*
   simplifys - simplify the expression until it cannot be simplified any further.
*/

static Fractions_Fract simplifys (Fractions_Fract f);

/*
   doFract - returns TRUE if fract, f, was simplified.
*/

static unsigned int doFract (Fractions_Fract f);

/*
   doRules - returns TRUE if, f, is altered dues to a simplifcation rule being applied.
*/

static unsigned int doRules (Fractions_Fract f);

/*
   assignValue - performs des^ := expr^ of the values (avoiding any housekeeping fields).
*/

static void assignValue (Fractions_Fract des, Fractions_Fract expr);

/*
   doSub - if, l, and, r, are equal then alter, f, to zero.
*/

static unsigned int doSub (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r);

/*
   doAdd - simplify the addition of two fractions.
*/

static unsigned int doAdd (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r);

/*
   doMult - simplify the multiplication. of two fractions.
*/

static unsigned int doMult (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r);

/*
   doPower - simplify the expression l^r.
*/

static unsigned int doPower (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r);

/*
   doNegate - simplify negate.
*/

static unsigned int doNegate (Fractions_Fract f, Fractions_Fract l);

/*
   doDiv - simplify divide.
*/

static unsigned int doDiv (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r);

/*
   angleIs - if angle a = angle v
             then
                f := r
             fi
*/

static unsigned int angleIs (Fractions_Fract a, Fractions_Fract v, Fractions_Fract f, Fractions_Fract r);

/*
   doSin - lookup the sin of angle, l, and if it is known replace, f, with the result.
*/

static unsigned int doSin (Fractions_Fract f, Fractions_Fract l);

/*
   doCos - lookup the cos of angle, l, and if it is known replace, f, with the result.
*/

static unsigned int doCos (Fractions_Fract f, Fractions_Fract l);

/*
   doTan - lookup the tan of angle, l, and if it is known replace, f, with the result.
*/

static unsigned int doTan (Fractions_Fract f, Fractions_Fract l);

/*
   gcd - return the greatest demoninator of, x, and, y.
*/

static long unsigned int gcd (long unsigned int x, long unsigned int y);

/*
   newFract - return a new fraction.
*/

static Fractions_Fract newFract (void);

/*
   makeSpecial - return a special fraction containing the value, special.
*/

static Fractions_Fract makeSpecial (Fractions_Fract f, Special s);

/*
   pf - short cut to print out a Fract, useful for interactive debugging via gdb.
*/

static void pf (Fractions_Fract f);

/*
   writeMath - write out the string, o, and the fraction, l.
*/

static void writeMath (char *o_, unsigned int _o_high, Fractions_Fract l);

/*
   writeUnary - write the unary operator and fraction, l, as:  (o l)
*/

static void writeUnary (char *o_, unsigned int _o_high, Fractions_Fract l);

/*
   writeBinary - write out:  (l o r)
*/

static void writeBinary (char *o_, unsigned int _o_high, Fractions_Fract l, Fractions_Fract r);

/*
   writeOp - write operator, f.
*/

static void writeOp (Fractions_Fract f);

/*
   writeFracts - write the special in, f.
*/

static void writeFracts (Fractions_Fract f);

/*
   writeFractc - write out the constant, f.
*/

static void writeFractc (Fractions_Fract f);

/*
   pd - writes out the Fract, f, as a decimal.
*/

static void pd (Fractions_Fract f);

/*
   log10 - return the log10 of, l.
*/

static unsigned int log10_ (long unsigned int l);

/*
   writeDecimal - write out, f, as a decimal.
*/

static void writeDecimal (Fractions_Fract f);

/*
   flush -
*/

static Fractions_Fract flush (Fractions_Fract f);

/*
   dupc -
*/

static Fractions_Fract dupc (Fractions_Fract f);

/*
   dups -
*/

static Fractions_Fract dups (Fractions_Fract f);

/*
   dupExpr - duplicate an entire expression.
*/

static Fractions_Fract dupExpr (Fractions_Fract f);

/*
   sinc -
*/

static Fractions_Fract sinc (Fractions_Fract x);

/*
   tanc -
*/

static Fractions_Fract tanc (Fractions_Fract f);

/*
   cosc - return cos of angle, f.
*/

static Fractions_Fract cosc (Fractions_Fract f);

/*
   toConst - returns the same fraction, f, which has been converted into a constant.
*/

static Fractions_Fract toConst (Fractions_Fract f);

/*
   walkFractEntity -
*/

static void walkFractEntity (GC_entity e);

/*
   init - initialise the global data structures.
*/

static void init (void);

/*
   regressionTest - perform some simple sanity regression tests.
*/

static void regressionTest (void);


/*
   writeCard -
*/

static void writeCard (unsigned int c)
{
  char ch;
  int i;

  if (c > 9)
    {
      writeCard (c / 10);
      writeCard (c % 10);
    }
  else
    {
      ch = (char) (((unsigned int) ('0'))+c);
      i = libc_write (1, &ch, 1);
    }
}


/*
   writeAddress -
*/

static void writeAddress (void * a)
{
  writeLongcard ((long unsigned int ) (a));
}


/*
   writeNspace -
*/

static void writeNspace (unsigned int n)
{
  while (n > 0)
    {
      writeString ((char *) " ", 1);
      n -= 1;
    }
}


/*
   writeNspace -
*/

static unsigned int capture (Fractions_Fract f)
{
  captured = f;
  return 1;
}


/*
   isSpecial - return TRUE if, f, is a special.
*/

static unsigned int isSpecial (Fractions_Fract f)
{
  return f->special != NONE;
}


/*
   isConst - returns if, f, is a fractional constant.
*/

static unsigned int isConst (Fractions_Fract f)
{
  return f->special == NONE;
}


/*
   isSpecialConst -
*/

static unsigned int isSpecialConst (Fractions_Fract f)
{
  return ((((f->special == PI) || (f->special == E)) || (f->special == ROOT2)) || (f->special == ROOT3)) || (f->special == ROOT6);
}


/*
   isExpr - return TRUE if, f, is an expression.
*/

static unsigned int isExpr (Fractions_Fract f)
{
  return f->special == EXPR;
}


/*
   writeString - writes a string to stdout.
*/

static void writeString (char *a_, unsigned int _a_high)
{
  int i;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  i = libc_write (1, &a, (int) StrLib_StrLen ((char *) a, _a_high));
}


/*
   writeCstring - writes a C string to stdout.
*/

static void writeCstring (void * a)
{
  int i;

  if (a == NULL)
    writeString ((char *) "(null)", 6);
  else
    i = libc_write (1, a, libc_strlen (a));
}


/*
   writeLongcard -
*/

static void writeLongcard (long unsigned int c)
{
  char ch;
  int i;

  if (c > 9)
    {
      writeLongcard (c / 10);
      writeLongcard (c % 10);
    }
  else
    {
      ch = (char) (((unsigned int) ('0'))+((unsigned int ) (c)));
      i = libc_write (1, &ch, 1);
    }
}


/*
   writeLongint -
*/

static void writeLongint (long int i)
{
  char ch;
  int j;

  if (i < 0)
    {
      writeString ((char *) "-", 1);
      writeLongint (-i);
    }
  else if (i >= 10)
    {
      writeLongint (i / 10);
      writeLongint (i % 10);
    }
  else if (i < 10)
    {
      ch = (char) (((unsigned int) ('0'))+((unsigned int ) (i)));
      j = libc_write (1, &ch, 1);
    }
}


/*
   writeLn - writes a newline.
*/

static void writeLn (void)
{
  char ch;
  int i;

  ch = ASCII_lf;
  i = libc_write (1, &ch, 1);
}


/*
   dirty - sets Fract, f, to dirty.
*/

static Fractions_Fract dirty (Fractions_Fract f)
{
  f->dirty = TRUE;
  return f;
}


/*
   clean - sets Fract, f, to clean.
*/

static Fractions_Fract clean (Fractions_Fract f)
{
  f->dirty = FALSE;
  return f;
}


/*
   negatec - negates constant, -f.
*/

static Fractions_Fract negatec (Fractions_Fract f)
{
  if (! (Fractions_isZero (f)))
    f->positive = ! f->positive;
  return f;
}


/*
   negates - negate special.
*/

static Fractions_Fract negates (Fractions_Fract f)
{
  return buildUnary ((Operator) oNegate, f);
}


/*
   equalDemon - converts both fractions to have equal demoninators.
*/

static void equalDemon (Fractions_Fract l, Fractions_Fract r)
{
  long unsigned int g;
  long unsigned int lg;
  long unsigned int rg;

  if ((l->num == 0) && (r->num == 0))
    {
      l->demon = 0;
      r->demon = 0;
    }
  else if (l->num == 0)
    l->demon = r->demon;
  else if (r->num == 0)
    r->demon = l->demon;
  else
    {
      g = gcd (l->demon, r->demon);
      lg = r->demon / g;
      rg = l->demon / g;
      l->num = l->num*lg;
      l->demon = l->demon*lg;
      r->num = r->num*rg;
      r->demon = l->demon*rg;
    }
}


/*
   addND - add the numerator/demonimator pairs of, l, and, r.
           It propagates the carry into whole.
           l := l+r  is performed.
*/

static void addND (Fractions_Fract l, Fractions_Fract r)
{
  long unsigned int g;
  long unsigned int lg;
  long unsigned int rg;

  if (l->num == 0)
    {
      l->num = r->num;
      l->demon = r->demon;
    }
  else if (r->num == 0)
    {}  /* empty.  */
  else
    {
      g = gcd (l->demon, r->demon);
      lg = r->demon / g;
      rg = l->demon / g;
      l->num = (l->num*lg)+(r->num*rg);
      l->demon = l->demon*lg;
      l = Fractions_simplify (l);
    }
}


/*
   subND - sub the numerator/demonimator pairs of, l, and, r.
           It returns TRUE if it needs to borrow.
           l := l-r  is performed.
*/

static unsigned int subND (Fractions_Fract l, Fractions_Fract r)
{
  long unsigned int g;
  long unsigned int lg;
  long unsigned int rg;

  if (l->num == 0)
    {
      l->num = r->demon-r->num;
      l->demon = r->demon;
      l = dirty (l);
      return r->num != 0;
    }
  else if (r->num == 0)
    return FALSE;
  else
    {
      l = dirty (l);
      g = gcd (l->demon, r->demon);
      lg = r->demon / g;
      rg = l->demon / g;
      if ((l->num*lg) >= (r->num*rg))
        {
          l->num = (l->num*lg)-(r->num*rg);
          l->demon = l->demon*lg;
          return FALSE;
        }
      else
        {
          l->demon = l->demon*lg;
          l->num = (r->num*rg)-(l->num*lg);
          return TRUE;
        }
    }
}


/*
   addc - add constant fractions.
*/

static Fractions_Fract addc (Fractions_Fract l, Fractions_Fract r)
{
  Fractions_Fract f;

  f = Fractions_simplify (Fractions_dup (l));
  r = Fractions_simplify (r);
  f = Fractions_simplify (Fractions_inc (f, r));
  return f;
}


/*
   buildUnary - returns (operator, l).
*/

static Fractions_Fract buildUnary (Operator operator, Fractions_Fract l)
{
  return buildBinary (operator, l, (Fractions_Fract) NULL);
}


/*
   buildBinary - returns (operator, l, r).
*/

static Fractions_Fract buildBinary (Operator operator, Fractions_Fract l, Fractions_Fract r)
{
  Fractions_Fract f;

  f = Fractions_initFract (0, 0, 0);
  f->op = operator;
  f->special = EXPR;
  f->left = l;
  f->right = r;
  return f;
}


/*
   adds - returns expression l + r.
*/

static Fractions_Fract adds (Fractions_Fract l, Fractions_Fract r)
{
  return buildBinary ((Operator) oAdd, l, r);
}


/*
   powers - return an expression l^r.
*/

static Fractions_Fract powers (Fractions_Fract l, Fractions_Fract r)
{
  return buildBinary ((Operator) oPower, l, r);
}


/*
   powerc - compute constant, l^r
*/

static Fractions_Fract powerc (Fractions_Fract l, Fractions_Fract r)
{
  return powers (l, r);
}


/*
   mults - returns expression l * r.
*/

static Fractions_Fract mults (Fractions_Fract l, Fractions_Fract r)
{
  return buildBinary ((Operator) oMult, l, r);
}


/*
   multc - calculate l * r from constants.
*/

static Fractions_Fract multc (Fractions_Fract l, Fractions_Fract r)
{
  Fractions_Fract f;
  unsigned int n;

  l = Fractions_simplify (l);
  if (l == r)
    r = Fractions_dup (l);
  else
    r = Fractions_simplify (r);
  if (l->positive && r->positive)
    f = Fractions_inc (Fractions_inc (Fractions_cardinal (l->whole*r->whole), Fractions_inc (Fractions_initFract (0, l->whole*r->num, r->demon), Fractions_initFract (0, r->whole*l->num, l->demon))), Fractions_initFract (0, l->num*r->num, l->demon*r->demon));
  else if (l->positive)
    {
      Assertion_Assert (! r->positive);
      r = Fractions_negate (r);
      f = Fractions_inc (Fractions_inc (Fractions_negate (Fractions_cardinal (l->whole*r->whole)), Fractions_inc (Fractions_negate (Fractions_initFract (0, l->whole*r->num, r->demon)), Fractions_negate (Fractions_initFract (0, r->whole*l->num, l->demon)))), Fractions_negate (Fractions_initFract (0, l->num*r->num, l->demon*r->demon)));
    }
  else if (r->positive)
    {
      Assertion_Assert (! l->positive);
      l = Fractions_negate (l);
      f = Fractions_inc (Fractions_inc (Fractions_negate (Fractions_cardinal (l->whole*r->whole)), Fractions_inc (Fractions_negate (Fractions_initFract (0, l->whole*r->num, r->demon)), Fractions_negate (Fractions_initFract (0, r->whole*l->num, l->demon)))), Fractions_negate (Fractions_initFract (0, l->num*r->num, l->demon*r->demon)));
    }
  else
    {
      Assertion_Assert (! l->positive && ! r->positive);
      l = Fractions_negate (l);
      r = Fractions_negate (r);
      f = Fractions_inc (Fractions_inc (Fractions_cardinal (l->whole*r->whole), Fractions_inc (Fractions_initFract (0, l->whole*r->num, r->demon), Fractions_initFract (0, r->whole*l->num, l->demon))), Fractions_initFract (0, l->num*r->num, l->demon*r->demon));
    }
  return Fractions_simplify (f);
}


/*
   divc - calculate l / r from constants.
*/

static Fractions_Fract divc (Fractions_Fract l, Fractions_Fract r)
{
  l = Fractions_simplify (l);
  r = Fractions_simplify (r);
  if (Fractions_isZero (r))
    M2RTS_HALT (0);
  if (Fractions_isEqual (l, r))
    return Fractions_one ();
  else
    return Fractions_mult (l, Fractions_reciprocal (r));
}


/*
   divs - calculate l / r from one or more specials.
*/

static Fractions_Fract divs (Fractions_Fract l, Fractions_Fract r)
{
  return buildBinary ((Operator) oDiv, l, r);
}


/*
   reciprocals - return 1/f from a special.
*/

static Fractions_Fract reciprocals (Fractions_Fract f)
{
  return buildBinary ((Operator) oDiv, Fractions_one (), f);
}


/*
   reciprocalc - return 1/f from a constant.
*/

static Fractions_Fract reciprocalc (Fractions_Fract f)
{
  Fractions_Fract r;

  if ((f->num == 0) && (f->whole == 0))
    r = Fractions_initFract (0, 0, 0);
  else if (f->num == 0)
    r = Fractions_initFract (0, 1, f->whole);
  else
    r = Fractions_initFract (0, f->demon, (f->whole*f->demon)+f->num);
  if (! f->positive)
    r = Fractions_negate (r);
  return Fractions_simplify (r);
}


/*
   subc - returns a constant from, l - r.
*/

static Fractions_Fract subc (Fractions_Fract l, Fractions_Fract r)
{
  Fractions_Fract f;

  f = Fractions_simplify (Fractions_dup (l));
  f = Fractions_simplify (Fractions_dec (f, r));
  return f;
}


/*
   subs - returns the expression, l - r.
*/

static Fractions_Fract subs (Fractions_Fract l, Fractions_Fract r)
{
  return buildBinary ((Operator) oSub, l, r);
}


/*
   stop - debugging hook.
*/

static void stop (void)
{
}


/*
   simplifyc - returns a simplified fraction, f.
*/

static Fractions_Fract simplifyc (Fractions_Fract f)
{
  long unsigned int d;

  if (! f->dirty)
    return f;
  if ((f->num != 0) && (f->demon != 0))
    {
      if (f->num > f->demon)
        {
          d = f->num/f->demon;
          if (f->whole >= 0)
            f->whole += d;
          else
            f->whole -= d;
          f->num = f->num % f->demon;
        }
      if ((f->num != 0) && (f->demon != 0))
        {
          d = gcd (f->num, f->demon);
          if (d > 1)
            {
              f->num = f->num / d;
              f->demon = f->demon / d;
            }
        }
      if (f->num == f->demon)
        {
          Assertion_Assert (f->num == 1);
          f->num = 0;
          f->demon = 0;
          f->whole += 1;
        }
    }
  if (f->num == 0)
    f->demon = 0;
  return clean (f);
}


/*
   specialToConst - returns TRUE if, f, was changed to a const.
*/

static unsigned int specialToConst (Fractions_Fract f)
{
  if (isSpecialConst (f))
    {
      f->op = oFract;
      f->special = NONE;
      return TRUE;
    }
  return FALSE;
}


/*
   walkFract - walks fract, f, and marks each node.
*/

static void walkFract (Fractions_Fract f)
{
  Fractions_mark (f);
  switch (f->special)
    {
      case NONE:
      case PI:
      case E:
      case ROOT2:
      case ROOT3:
      case ROOT6:
        break;

      case EXPR:
        switch (f->op)
          {
            case oFract:
              break;

            case oAdd:
            case oSub:
            case oMult:
            case oDiv:
            case oPower:
              walkFract (f->left);
              walkFract (f->right);
              break;

            case oNegate:
            case oSin:
            case oCos:
            case oTan:
              walkFract (f->left);
              break;


            default:
              M2RTS_HALT (0);
              break;
          }
        break;


      default:
        M2RTS_HALT (0);
        break;
    }
}


/*
   walkExpr -
*/

static unsigned int walkExpr (Fractions_Fract f, doProcedure p)
{
  unsigned int changed;

  switch (f->special)
    {
      case NONE:
      case PI:
      case E:
      case ROOT2:
      case ROOT3:
      case ROOT6:
        changed = (*p.proc) (f);
        break;

      case EXPR:
        switch (f->op)
          {
            case oFract:
              changed = (*p.proc) (f);
              break;

            case oAdd:
            case oSub:
            case oMult:
            case oDiv:
            case oPower:
              changed = walkExpr (f->left, p);
              if ((walkExpr (f->right, p)) && ! changed)
                changed = TRUE;
              break;

            case oNegate:
            case oSin:
            case oCos:
            case oTan:
              changed = walkExpr (f->left, p);
              break;


            default:
              M2RTS_HALT (0);
              break;
          }
        break;


      default:
        M2RTS_HALT (0);
        break;
    }
  return changed;
}


/*
   simplifys - simplify the expression until it cannot be simplified any further.
*/

static Fractions_Fract simplifys (Fractions_Fract f)
{
  while (doRules (f))
    {}  /* empty.  */
  return f;
}


/*
   doFract - returns TRUE if fract, f, was simplified.
*/

static unsigned int doFract (Fractions_Fract f)
{
  if (f->dirty)
    {
      f = simplifyc (f);
      return TRUE;
    }
  return FALSE;
}


/*
   doRules - returns TRUE if, f, is altered dues to a simplifcation rule being applied.
*/

static unsigned int doRules (Fractions_Fract f)
{
  switch (f->special)
    {
      case NONE:
        return doFract (f);
        break;

      case PI:
      case E:
      case ROOT2:
      case ROOT3:
      case ROOT6:
        break;

      case EXPR:
        switch (f->op)
          {
            case oFract:
              return doFract (f);
              break;

            case oAdd:
              return doAdd (f, f->left, f->right);
              break;

            case oSub:
              return doSub (f, f->left, f->right);
              break;

            case oMult:
              return doMult (f, f->left, f->right);
              break;

            case oDiv:
              return doDiv (f, f->left, f->right);
              break;

            case oNegate:
              return doNegate (f, f->left);
              break;

            case oPower:
              return doPower (f, f->left, f->right);
              break;

            case oSin:
              return doSin (f, f->left);
              break;

            case oCos:
              return doCos (f, f->left);
              break;

            case oTan:
              return doTan (f, f->left);
              break;


            default:
              M2RTS_HALT (0);
              break;
          }
        break;


      default:
        M2RTS_HALT (0);
        break;
    }
  return FALSE;
}


/*
   assignValue - performs des^ := expr^ of the values (avoiding any housekeeping fields).
*/

static void assignValue (Fractions_Fract des, Fractions_Fract expr)
{
  des->positive = expr->positive;
  des->whole = expr->whole;
  des->num = expr->num;
  des->demon = expr->demon;
  des->op = expr->op;
  des->dirty = expr->dirty;
  des->special = expr->special;
  des->left = expr->left;
  des->right = expr->right;
}


/*
   doSub - if, l, and, r, are equal then alter, f, to zero.
*/

static unsigned int doSub (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r)
{
  unsigned int modified;

  modified = doRules (l);
  if (doRules (r))
    modified = TRUE;
  if (Fractions_areEqual (r, Fractions_zero ()))
    {
      assignValue (f, l);
      return TRUE;
    }
  if (Fractions_areEqual (l, Fractions_zero ()))
    {
      assignValue (f, Fractions_negate (r));
      return TRUE;
    }
  if (Fractions_areEqual (l, r))
    {
      assignValue (f, Fractions_zero ());
      return TRUE;
    }
  if ((isConst (l)) && (isConst (r)))
    {
      assignValue (f, Fractions_sub (l, r));
      return TRUE;
    }
  return modified;
}


/*
   doAdd - simplify the addition of two fractions.
*/

static unsigned int doAdd (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r)
{
  unsigned int modified;

  modified = doRules (l);
  if (doRules (r))
    modified = TRUE;
  if (Fractions_areEqual (l, Fractions_zero ()))
    {
      assignValue (f, r);
      return TRUE;
    }
  if (Fractions_areEqual (r, Fractions_zero ()))
    {
      assignValue (f, l);
      return TRUE;
    }
  if (Fractions_areEqual (l, r))
    {
      f->op = oMult;
      assignValue (l, Fractions_cardinal (2));
      return TRUE;
    }
  if ((isConst (l)) && (isConst (r)))
    {
      assignValue (f, Fractions_add (l, r));
      return TRUE;
    }
  return modified;
}


/*
   doMult - simplify the multiplication. of two fractions.
*/

static unsigned int doMult (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r)
{
  unsigned int modified;

  modified = doRules (l);
  if (doRules (r))
    modified = TRUE;
  if (Fractions_areEqual (r, Fractions_zero ()))
    {
      assignValue (f, Fractions_zero ());
      return TRUE;
    }
  if (Fractions_areEqual (l, Fractions_zero ()))
    {
      assignValue (f, Fractions_zero ());
      return TRUE;
    }
  if (Fractions_areEqual (l, r))
    if ((isSpecialConst (l)) && (l->special == ROOT2))
      {
        assignValue (f, Fractions_cardinal (2));
        modified = TRUE;
      }
    else if ((isSpecialConst (l)) && (l->special == ROOT3))
      {
        assignValue (f, Fractions_cardinal (3));
        modified = TRUE;
      }
    else if ((isSpecialConst (l)) && (l->special == ROOT6))
      {
        assignValue (f, Fractions_cardinal (6));
        modified = TRUE;
      }
    else
      {
        f->op = oPower;
        f->right = Fractions_cardinal (2);
        modified = TRUE;
      }
  else if ((isConst (l)) && (isConst (r)))
    {
      assignValue (f, Fractions_mult (l, r));
      return TRUE;
    }
  return modified;
}


/*
   doPower - simplify the expression l^r.
*/

static unsigned int doPower (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r)
{
  unsigned int modified;

  modified = doRules (l);
  if (doRules (r))
    modified = TRUE;
  if (Fractions_areEqual (l, Fractions_one ()))
    {
      assignValue (f, Fractions_cardinal (1));
      return TRUE;
    }
  else if (((isSpecialConst (l)) && (Fractions_isEqual (r, Fractions_two ()))) && (l->special == ROOT2))
    {
      assignValue (f, Fractions_cardinal (2));
      return TRUE;
    }
  else if (((isSpecialConst (l)) && (Fractions_isEqual (r, Fractions_two ()))) && (l->special == ROOT3))
    {
      assignValue (f, Fractions_cardinal (3));
      return TRUE;
    }
  else if (((isSpecialConst (l)) && (Fractions_isEqual (r, Fractions_two ()))) && (l->special == ROOT6))
    {
      assignValue (f, Fractions_cardinal (6));
      return TRUE;
    }
  else if (((Fractions_isEqual (r, Fractions_two ())) && (isExpr (l))) && (l->op == oDiv))
    {
      assignValue (f, Fractions_div (Fractions_mult (l->left, l->left), Fractions_mult (l->right, l->right)));
      return TRUE;
    }
  return modified;
}


/*
   doNegate - simplify negate.
*/

static unsigned int doNegate (Fractions_Fract f, Fractions_Fract l)
{
  Fractions_Fract result;
  unsigned int modified;

  modified = doRules (l);
  if (l->op == oNegate)
    {
      f->left = l->left;
      return TRUE;
    }
  else if (isConst (l))
    {
      assignValue (f, Fractions_negate (l));
      return TRUE;
    }
  return modified;
}


/*
   doDiv - simplify divide.
*/

static unsigned int doDiv (Fractions_Fract f, Fractions_Fract l, Fractions_Fract r)
{
  unsigned int modified;

  modified = doRules (l);
  if (doRules (r))
    modified = TRUE;
  if (Fractions_areEqual (l, r))
    {
      assignValue (f, Fractions_cardinal (1));
      return TRUE;
    }
  if (Fractions_areEqual (r, Fractions_cardinal (1)))
    {
      assignValue (f, l);
      return TRUE;
    }
  if ((isConst (l)) && (isConst (r)))
    {
      assignValue (f, Fractions_div (l, r));
      return TRUE;
    }
  return modified;
}


/*
   angleIs - if angle a = angle v
             then
                f := r
             fi
*/

static unsigned int angleIs (Fractions_Fract a, Fractions_Fract v, Fractions_Fract f, Fractions_Fract r)
{
  if (Fractions_areEqual (a, v))
    {
      assignValue (f, r);
      return TRUE;
    }
  return FALSE;
}


/*
   doSin - lookup the sin of angle, l, and if it is known replace, f, with the result.
*/

static unsigned int doSin (Fractions_Fract f, Fractions_Fract l)
{
  unsigned int modified;

  modified = doRules (l);
  if (angleIs (l, Fractions_cardinal (0), f, Fractions_cardinal (0)))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_two ()), f, Fractions_one ()))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (3)), f, Fractions_div (Fractions_root3 (), Fractions_two ())))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (4)), f, Fractions_div (Fractions_root2 (), Fractions_two ())))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (6)), f, Fractions_half ()))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (12)), f, Fractions_div (Fractions_sub (Fractions_root6 (), Fractions_root2 ()), Fractions_cardinal (4))))
    return TRUE;
  return modified;
}


/*
   doCos - lookup the cos of angle, l, and if it is known replace, f, with the result.
*/

static unsigned int doCos (Fractions_Fract f, Fractions_Fract l)
{
  unsigned int modified;

  modified = doRules (l);
  if (angleIs (l, Fractions_cardinal (0), f, Fractions_one ()))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_two ()), f, Fractions_zero ()))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (3)), f, Fractions_half ()))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (4)), f, Fractions_div (Fractions_root2 (), Fractions_two ())))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (6)), f, Fractions_div (Fractions_root3 (), Fractions_two ())))
    return TRUE;
  return modified;
}


/*
   doTan - lookup the tan of angle, l, and if it is known replace, f, with the result.
*/

static unsigned int doTan (Fractions_Fract f, Fractions_Fract l)
{
  unsigned int modified;

  modified = doRules (l);
  if (angleIs (l, Fractions_cardinal (0), f, Fractions_zero ()))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (3)), f, Fractions_root3 ()))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (4)), f, Fractions_one ()))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (6)), f, Fractions_div (Fractions_root3 (), Fractions_cardinal (3))))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_pi (), Fractions_cardinal (12)), f, Fractions_sub (Fractions_two (), Fractions_root3 ())))
    return TRUE;
  if (angleIs (l, Fractions_div (Fractions_mult (Fractions_pi (), Fractions_cardinal (5)), Fractions_cardinal (12)), f, Fractions_add (Fractions_two (), Fractions_root3 ())))
    return TRUE;
  if (angleIs (l, Fractions_mult (Fractions_div (Fractions_pi (), Fractions_cardinal (12)), Fractions_cardinal (5)), f, Fractions_add (Fractions_two (), Fractions_root3 ())))
    return TRUE;
  return modified;
}


/*
   gcd - return the greatest demoninator of, x, and, y.
*/

static long unsigned int gcd (long unsigned int x, long unsigned int y)
{
  while (x != y)
    if (x > y)
      x -= y;
    else
      y -= x;
  return x;
}


/*
   newFract - return a new fraction.
*/

static Fractions_Fract newFract (void)
{
  Fractions_Fract f;
  GC_entity e;

  GC_allocate (fractHeap, &e, (void **) &f);
  f->fentity = e;
  return f;
}


/*
   makeSpecial - return a special fraction containing the value, special.
*/

static Fractions_Fract makeSpecial (Fractions_Fract f, Special s)
{
  f->special = s;
  return f;
}


/*
   pf - short cut to print out a Fract, useful for interactive debugging via gdb.
*/

static void pf (Fractions_Fract f)
{
  Fractions_writeFract (f);
  writeLn ();
}


/*
   writeMath - write out the string, o, and the fraction, l.
*/

static void writeMath (char *o_, unsigned int _o_high, Fractions_Fract l)
{
  char o[_o_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (o, o_, _o_high+1);

  writeString ((char *) o, _o_high);
  writeString ((char *) "(", 1);
  writeOp (l);
  writeString ((char *) ")", 1);
}


/*
   writeUnary - write the unary operator and fraction, l, as:  (o l)
*/

static void writeUnary (char *o_, unsigned int _o_high, Fractions_Fract l)
{
  char o[_o_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (o, o_, _o_high+1);

  writeString ((char *) "(", 1);
  writeString ((char *) o, _o_high);
  writeOp (l);
  writeString ((char *) ")", 1);
}


/*
   writeBinary - write out:  (l o r)
*/

static void writeBinary (char *o_, unsigned int _o_high, Fractions_Fract l, Fractions_Fract r)
{
  char o[_o_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (o, o_, _o_high+1);

  writeString ((char *) "(", 1);
  writeOp (l);
  writeString ((char *) o, _o_high);
  writeOp (r);
  writeString ((char *) ")", 1);
}


/*
   writeOp - write operator, f.
*/

static void writeOp (Fractions_Fract f)
{
  switch (f->op)
    {
      case oFract:
        Fractions_writeFract (f);
        break;

      case oAdd:
        writeBinary ((char *) "+", 1, f->left, f->right);
        break;

      case oSub:
        writeBinary ((char *) "-", 1, f->left, f->right);
        break;

      case oMult:
        writeBinary ((char *) "*", 1, f->left, f->right);
        break;

      case oDiv:
        writeBinary ((char *) "/", 1, f->left, f->right);
        break;

      case oNegate:
        writeUnary ((char *) "-", 1, f->left);
        break;

      case oPower:
        writeBinary ((char *) "^", 1, f->left, f->right);
        break;

      case oSin:
        writeMath ((char *) "sin", 3, f->left);
        break;

      case oCos:
        writeMath ((char *) "cos", 3, f->left);
        break;

      case oTan:
        writeMath ((char *) "tan", 3, f->left);
        break;


      default:
        M2RTS_HALT (0);
        break;
    }
}


/*
   writeFracts - write the special in, f.
*/

static void writeFracts (Fractions_Fract f)
{
  switch (f->special)
    {
      case NONE:
        Fractions_writeFract (f);
        break;

      case PI:
        writeString ((char *) "pi", 2);
        break;

      case E:
        writeString ((char *) "e", 1);
        break;

      case ROOT2:
        writeString ((char *) "root2", 5);
        break;

      case ROOT3:
        writeString ((char *) "root3", 5);
        break;

      case ROOT6:
        writeString ((char *) "root6", 5);
        break;

      case EXPR:
        writeOp (f);
        break;


      default:
        M2RTS_HALT (0);
        break;
    }
}


/*
   writeFractc - write out the constant, f.
*/

static void writeFractc (Fractions_Fract f)
{
  if (! f->positive)
    writeString ((char *) "-", 1);
  if (f->whole != 0)
    writeLongcard (f->whole);
  if ((f->demon != 1) && (f->num != 0))
    {
      writeString ((char *) ".", 1);
      writeLongcard (f->num);
      writeString ((char *) "/", 1);
      writeLongcard (f->demon);
    }
  else if (f->whole == 0)
    writeString ((char *) "0", 1);
}


/*
   pd - writes out the Fract, f, as a decimal.
*/

static void pd (Fractions_Fract f)
{
  writeDecimal (f);
  writeLn ();
}


/*
   log10 - return the log10 of, l.
*/

static unsigned int log10_ (long unsigned int l)
{
  long unsigned int c;
  unsigned int i;

  i = 0;
  c = 1;
  while (c < l)
    {
      i += 1;
      c = c*10;
    }
  return i;
}


/*
   writeDecimal - write out, f, as a decimal.
*/

static void writeDecimal (Fractions_Fract f)
{
  unsigned int d;
  long double l;
  DynamicStrings_String s;
  void * a;
  int i;

  if (Fractions_isZero (f))
    writeString ((char *) "0.0", 3);
  else
    {
      d = log10_ (f->whole);
      l = ((long double ) (f->whole))+(((long double ) (f->num))/((long double ) (f->demon)));
      if (! f->positive)
        writeString ((char *) "-", 1);
      s = StringConvert_LongrealToString (l, 20, 20-d);
      a = DynamicStrings_string (s);
      i = libc_write (1, a, libc_strlen (a));
      s = DynamicStrings_KillString (s);
    }
}


/*
   flush -
*/

static Fractions_Fract flush (Fractions_Fract f)
{
  if (isConst (f))
    return f;
  else
    {
      f = simplifys (f);
      if (isConst (f))
        return f;
      else
        M2RTS_HALT (0);
    }
}


/*
   dupc -
*/

static Fractions_Fract dupc (Fractions_Fract f)
{
  Fractions_Fract d;

  d = Fractions_initFract (f->whole, f->num, f->demon);
  if (! f->positive)
    d = Fractions_negate (d);
  d->dirty = f->dirty;
  d->special = f->special;
  d->op = f->op;
  return d;
}


/*
   dups -
*/

static Fractions_Fract dups (Fractions_Fract f)
{
  switch (f->special)
    {
      case NONE:
      case PI:
      case E:
      case ROOT2:
      case ROOT3:
      case ROOT6:
        return dupc (f);
        break;

      case EXPR:
        return dupExpr (f);
        break;


      default:
        M2RTS_HALT (0);
        break;
    }
}


/*
   dupExpr - duplicate an entire expression.
*/

static Fractions_Fract dupExpr (Fractions_Fract f)
{
  Fractions_Fract g;

  g = newFract ();
  assignValue (g, f);
  g->left = NULL;
  g->right = NULL;
  switch (f->op)
    {
      case oFract:
        return g;
        break;

      case oAdd:
      case oSub:
      case oMult:
      case oDiv:
      case oPower:
        g->left = Fractions_dup (f->left);
        g->right = Fractions_dup (f->right);
        break;

      case oNegate:
      case oSin:
      case oCos:
      case oTan:
        g->left = Fractions_dup (f->left);
        break;


      default:
        M2RTS_HALT (0);
        break;
    }
  return g;
}


/*
   sinc -
*/

static Fractions_Fract sinc (Fractions_Fract x)
{
  M2RTS_HALT (0);
  return x;
}


/*
   tanc -
*/

static Fractions_Fract tanc (Fractions_Fract f)
{
  M2RTS_HALT (0);
  return f;
}


/*
   cosc - return cos of angle, f.
*/

static Fractions_Fract cosc (Fractions_Fract f)
{
  M2RTS_HALT (0);
  return f;
}


/*
   toConst - returns the same fraction, f, which has been converted into a constant.
*/

static Fractions_Fract toConst (Fractions_Fract f)
{
  f = Fractions_simplify (f);
  if (walkExpr (f, (doProcedure) {(doProcedure_t) specialToConst}))
    f = Fractions_simplify (f);
  if (isConst (f))
    return f;
  else
    M2RTS_HALT (0);
}


/*
   walkFractEntity -
*/

static void walkFractEntity (GC_entity e)
{
  Fractions_Fract f;

  f = GC_getData (e);
  walkFract (f);
}


/*
   init - initialise the global data structures.
*/

static void init (void)
{
  Fractions_Fract f;

  fractHeap = GC_initGarbage ((GC_walkP) {(GC_walkP_t) walkFractEntity}, (unsigned int) sizeof ((*f)), DynamicStrings_InitString ((char *) "fractions", 9));
}


/*
   regressionTest - perform some simple sanity regression tests.
*/

static void regressionTest (void)
{
  Assertion_Assert (Fractions_isEqual (Fractions_sub (Fractions_half (), Fractions_initFract (1, 1, 2)), Fractions_negate (Fractions_one ())));
  Assertion_Assert (Fractions_isEqual (Fractions_sub (Fractions_initFract (1, 1, 2), Fractions_half ()), Fractions_one ()));
  Assertion_Assert (Fractions_isEqual (Fractions_sub (Fractions_initFract (1, 1, 2), Fractions_negate (Fractions_half ())), Fractions_two ()));
  Assertion_Assert (Fractions_isEqual (Fractions_sub (Fractions_negate (Fractions_two ()), Fractions_negate (Fractions_half ())), Fractions_negate (Fractions_initFract (1, 1, 2))));
  Assertion_Assert (Fractions_isEqual (Fractions_add (Fractions_negate (Fractions_one ()), Fractions_negate (Fractions_half ())), Fractions_negate (Fractions_initFract (1, 1, 2))));
  Assertion_Assert (Fractions_isEqual (Fractions_add (Fractions_negate (Fractions_half ()), Fractions_negate (Fractions_half ())), Fractions_integer (-1)));
  Assertion_Assert (Fractions_isEqual (Fractions_add (Fractions_initFract (0, 1, 4), Fractions_initFract (0, 1, 5)), Fractions_initFract (0, 9, 20)));
  Assertion_Assert (Fractions_isEqual (Fractions_add (Fractions_initFract (0, 9, 4), Fractions_initFract (0, 1, 5)), Fractions_initFract (2, 9, 20)));
  Assertion_Assert (Fractions_isEqual (Fractions_reciprocal (Fractions_initFract (0, 1, 9)), Fractions_cardinal (9)));
  Assertion_Assert (Fractions_isEqual (Fractions_reciprocal (Fractions_initFract (0, 3, 10)), Fractions_initFract (0, 10, 3)));
  Assertion_Assert (Fractions_isEqual (Fractions_reciprocal (Fractions_one ()), Fractions_one ()));
  Assertion_Assert (Fractions_isEqual (Fractions_mult (Fractions_reciprocal (Fractions_cardinal (2)), Fractions_reciprocal (Fractions_cardinal (3))), Fractions_initFract (0, 1, 6)));
  Assertion_Assert (Fractions_isEqual (Fractions_inc (Fractions_reciprocal (Fractions_cardinal (50)), Fractions_reciprocal (Fractions_cardinal (100))), Fractions_initFract (0, 3, 100)));
  Assertion_Assert (Fractions_isEqual (Fractions_mult (Fractions_initFract (0, 22, 7), Fractions_initFract (0, 22, 7)), Fractions_initFract (9, 43, 49)));
  Assertion_Assert (Fractions_isEqual (Fractions_dec (Fractions_initFract (0, 1, 4), Fractions_initFract (0, 1, 2)), Fractions_negate (Fractions_initFract (0, 1, 4))));
  Assertion_Assert (Fractions_isEqual (Fractions_dec (Fractions_initFract (0, 1, 2), Fractions_initFract (0, 1, 4)), Fractions_initFract (0, 1, 4)));
  Assertion_Assert (Fractions_isEqual (Fractions_dec (Fractions_initFract (3, 0, 0), Fractions_initFract (3, 1, 4)), Fractions_negate (Fractions_initFract (0, 1, 4))));
  Assertion_Assert (Fractions_isEqual (Fractions_mult (Fractions_integer (-1), Fractions_one ()), Fractions_integer (-1)));
  Assertion_Assert (Fractions_isEqual (Fractions_integer (-1), Fractions_mult (Fractions_integer (-1), Fractions_one ())));
  Assertion_Assert (Fractions_isEqual (Fractions_mult (Fractions_integer (-2), Fractions_one ()), Fractions_integer (-2)));
  Assertion_Assert (Fractions_isEqual (Fractions_integer (-2), Fractions_mult (Fractions_integer (-2), Fractions_one ())));
  Assertion_Assert (Fractions_isEqual (Fractions_integer (2), Fractions_mult (Fractions_integer (-2), Fractions_integer (-1))));
  Assertion_Assert (Fractions_isEqual (Fractions_mult (Fractions_integer (-2), Fractions_integer (-1)), Fractions_integer (2)));
  Assertion_Assert (Fractions_isEqual (Fractions_mult (Fractions_integer (-2), Fractions_integer (1)), Fractions_integer (-2)));
  Assertion_Assert (Fractions_isEqual (Fractions_mult (Fractions_integer (2), Fractions_integer (-1)), Fractions_integer (-2)));
  Assertion_Assert (Fractions_isEqual (Fractions_add (Fractions_integer (-1), Fractions_integer (-1)), Fractions_integer (-2)));
  Assertion_Assert (Fractions_isEqual (Fractions_integer (-2), Fractions_add (Fractions_integer (-1), Fractions_integer (-1))));
  Assertion_Assert (Fractions_isEqual (Fractions_add (Fractions_integer (-1), Fractions_integer (1)), Fractions_integer (0)));
  Assertion_Assert (Fractions_isEqual (Fractions_add (Fractions_integer (1), Fractions_integer (-1)), Fractions_integer (0)));
  Assertion_Assert (Fractions_isEqual (Fractions_sub (Fractions_integer (-1), Fractions_integer (-1)), Fractions_integer (0)));
  Assertion_Assert (Fractions_isEqual (Fractions_integer (0), Fractions_sub (Fractions_integer (-1), Fractions_integer (-1))));
  Assertion_Assert (Fractions_isEqual (Fractions_sub (Fractions_integer (-1), Fractions_integer (1)), Fractions_integer (-2)));
  Assertion_Assert (Fractions_isEqual (Fractions_sub (Fractions_integer (1), Fractions_integer (-1)), Fractions_integer (2)));
  Fractions_writeFract (Fractions_pi ());
  writeLn ();
  pf (Fractions_simplify (Fractions_sin (Fractions_pi ())));
  writeLn ();
  pf (Fractions_simplify (Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (6)))));
  writeLn ();
  pf (Fractions_simplify (Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (4)))));
  writeLn ();
  pf (Fractions_simplify (Fractions_mult (Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (4))), Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (4))))));
  writeLn ();
  pf (Fractions_simplify (Fractions_tan (Fractions_mult (Fractions_cardinal (5), Fractions_div (Fractions_pi (), Fractions_cardinal (12))))));
  writeLn ();
  pf (Fractions_simplify (Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (12)))));
  writeLn ();
  pf (Fractions_simplify (Fractions_power (Fractions_sub (Fractions_root6 (), Fractions_root2 ()), Fractions_two ())));
  writeLn ();
  pf (Fractions_simplify (Fractions_mult (Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (12))), Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (12))))));
  writeLn ();
  pf (Fractions_simplify (Fractions_div (Fractions_mult (Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (12))), Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (12)))), Fractions_mult (Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (12))), Fractions_sin (Fractions_div (Fractions_pi (), Fractions_cardinal (12)))))));
  writeLn ();
}


/*
   root - grafts fract into the roots of the garbage tree.
*/

Fractions_Fract Fractions_root (Fractions_Fract f)
{
  GC_rootEntity (fractHeap, f->fentity, (void *) f);
  return f;
}


/*
   unroot - removes, f, from the roots of the garbage tree.
*/

Fractions_Fract Fractions_unroot (Fractions_Fract f)
{
  GC_rootDeallocate (fractHeap, &f->fentity, (void **) &f);
  return NULL;
}


/*
   pi - returns the approximation of pi as a Fract.
*/

Fractions_Fract Fractions_pi (void)
{
  return makeSpecial (Fractions_initFract (3, 1, 7), (Special) PI);
}


/*
   zero - returns the fraction, 0.
*/

Fractions_Fract Fractions_zero (void)
{
  return Fractions_initFract (0, 0, 0);
}


/*
   one - returns the fraction, 1/1.
*/

Fractions_Fract Fractions_one (void)
{
  return Fractions_initFract (1, 0, 0);
}


/*
   two - returns the value 2 as a fraction.
*/

Fractions_Fract Fractions_two (void)
{
  return Fractions_initFract (2, 0, 0);
}


/*
   half - returns 1/2.
*/

Fractions_Fract Fractions_half (void)
{
  return Fractions_oneOverN (2);
}


/*
   quarter - returns 1/4.
*/

Fractions_Fract Fractions_quarter (void)
{
  return Fractions_oneOverN (4);
}


/*
   oneOverN - returns 1/n.
*/

Fractions_Fract Fractions_oneOverN (long unsigned int n)
{
  return Fractions_initFract (0, 1, n);
}


/*
   root2 -
*/

Fractions_Fract Fractions_root2 (void)
{
  return makeSpecial (Fractions_initFract (0, 707, 1000), (Special) ROOT2);
}


/*
   root3 - returns 3^.5.
*/

Fractions_Fract Fractions_root3 (void)
{
  return makeSpecial (Fractions_initFract (1, 732, 1000), (Special) ROOT3);
}


/*
   root6 - returns 6^.5.
*/

Fractions_Fract Fractions_root6 (void)
{
  return makeSpecial (Fractions_initFract (2, 449, 1000), (Special) ROOT6);
}


/*
   integer - return, i, as a fraction.
*/

Fractions_Fract Fractions_integer (long int i)
{
  if (i >= 0)
    return Fractions_initFract ((long unsigned int ) (i), 0, 0);
  else
    return Fractions_negate (Fractions_initFract ((long unsigned int ) (-i), 0, 0));
}


/*
   cardinal - returns a cardinal as a fraction.
*/

Fractions_Fract Fractions_cardinal (long unsigned int i)
{
  return Fractions_initFract (i, 0, 0);
}


/*
   isZero - returns TRUE if the fraction is zero.
*/

unsigned int Fractions_isZero (Fractions_Fract f)
{
  f = Fractions_simplify (f);
  return (f->whole == 0) && (f->num == 0);
}


/*
   isOne - returns TRUE if the fraction is one.
*/

unsigned int Fractions_isOne (Fractions_Fract f)
{
  f = Fractions_simplify (f);
  return (f->whole == 1) && (f->num == 0);
}


/*
   isEqual - returns TRUE if Fracts, l, and, r, are equal.
*/

unsigned int Fractions_isEqual (Fractions_Fract l, Fractions_Fract r)
{
  l = Fractions_simplify (l);
  r = Fractions_simplify (r);
  return (((l->positive == r->positive) && (l->whole == r->whole)) && (l->num == r->num)) && (l->demon == r->demon);
}


/*
   isLess - returns TRUE if l < r.
*/

unsigned int Fractions_isLess (Fractions_Fract l, Fractions_Fract r)
{
  Fractions_Fract tl;
  Fractions_Fract tr;

  if (l->positive != r->positive)
    return r->positive;
  if (l->positive)
    {
      if (l->whole < r->whole)
        return TRUE;
      else if (l->whole > r->whole)
        return FALSE;
      l = Fractions_simplify (l);
      r = Fractions_simplify (r);
      tl = Fractions_dup (l);
      tr = Fractions_dup (r);
      equalDemon (tl, tr);
      return tl->num < tr->num;
    }
  else
    {
      if (l->whole > r->whole)
        return TRUE;
      else if (l->whole < r->whole)
        return FALSE;
      l = Fractions_simplify (l);
      r = Fractions_simplify (r);
      tl = Fractions_dup (l);
      tr = Fractions_dup (r);
      equalDemon (tl, tr);
      return tl->num > tr->num;
    }
}


/*
   isGreater - returns TRUE if l > r.
*/

unsigned int Fractions_isGreater (Fractions_Fract l, Fractions_Fract r)
{
  Fractions_Fract tl;
  Fractions_Fract tr;

  if (l->positive != r->positive)
    return l->positive;
  if (l->positive)
    {
      if (l->whole > r->whole)
        return TRUE;
      else if (l->whole < r->whole)
        return FALSE;
      l = Fractions_simplify (l);
      r = Fractions_simplify (r);
      tl = Fractions_dup (l);
      tr = Fractions_dup (r);
      equalDemon (tl, tr);
      return tl->num > tr->num;
    }
  else
    {
      if (l->whole < r->whole)
        return TRUE;
      else if (l->whole > r->whole)
        return FALSE;
      l = Fractions_simplify (l);
      r = Fractions_simplify (r);
      tl = Fractions_dup (l);
      tr = Fractions_dup (r);
      equalDemon (tl, tr);
      return tl->num < tr->num;
    }
}


/*
   negate - negate fraction, f.
*/

Fractions_Fract Fractions_negate (Fractions_Fract f)
{
  f = Fractions_dup (f);
  if (isSpecial (f))
    return negates (f);
  else
    return negatec (f);
}


/*
   power - return l^r.
*/

Fractions_Fract Fractions_power (Fractions_Fract l, Fractions_Fract r)
{
  if ((isSpecial (l)) || (isSpecial (r)))
    return powers (l, r);
  else
    return powerc (l, r);
}


/*
   mult - return l * r
*/

Fractions_Fract Fractions_mult (Fractions_Fract l, Fractions_Fract r)
{
  if ((isSpecial (l)) || (isSpecial (r)))
    return mults (l, r);
  else
    return multc (l, r);
}


/*
   div - return l / r.
*/

Fractions_Fract Fractions_div (Fractions_Fract l, Fractions_Fract r)
{
  if ((isSpecial (l)) || (isSpecial (r)))
    return divs (l, r);
  else
    return divc (l, r);
}


/*
   reciprocal - return 1/f.
*/

Fractions_Fract Fractions_reciprocal (Fractions_Fract f)
{
  if (isSpecial (f))
    return reciprocals (f);
  else
    return reciprocalc (f);
}


/*
   sub - returns the expression, l - r.
*/

Fractions_Fract Fractions_sub (Fractions_Fract l, Fractions_Fract r)
{
  if ((isSpecial (l)) || (isSpecial (r)))
    return subs (l, r);
  else
    return subc (l, r);
}


/*
   add - returns a new fraction of the result, l+r.
*/

Fractions_Fract Fractions_add (Fractions_Fract l, Fractions_Fract r)
{
  if ((isSpecial (l)) || (isSpecial (r)))
    return adds (l, r);
  else
    return addc (l, r);
}


/*
   inc - returns, l, after, r, has been added.
*/

Fractions_Fract Fractions_inc (Fractions_Fract l, Fractions_Fract r)
{
  unsigned int n;

  l = Fractions_simplify (l);
  r = Fractions_simplify (r);
  if (Fractions_isZero (r))
    return l;
  else if (Fractions_isZero (l))
    {
      l->positive = r->positive;
      l->whole = r->whole;
      l->num = r->num;
      l->demon = r->demon;
      return dirty (l);
    }
  if (r == l)
    r = Fractions_dup (l);
  if (l->positive == r->positive)
    {
      l = dirty (l);
      l->whole = l->whole+r->whole;
      addND (l, r);
    }
  else if (l->positive && ! r->positive)
    l = Fractions_dec (l, Fractions_negate (r));
  else if (! l->positive && r->positive)
    l = Fractions_negate (Fractions_dec (Fractions_negate (l), r));
  else
    M2RTS_HALT (0);
  return l;
}


/*
   dec - returns, l, after, r, has been subtracted.
*/

Fractions_Fract Fractions_dec (Fractions_Fract l, Fractions_Fract r)
{
  unsigned int n;
  Fractions_Fract t;
  Fractions_Fract s;

  l = Fractions_simplify (l);
  r = Fractions_simplify (r);
  if (Fractions_isZero (r))
    return l;
  else if (Fractions_isZero (l))
    {
      if (Fractions_isZero (r))
        l->positive = TRUE;
      else
        l->positive = ! r->positive;
      l->whole = r->whole;
      l->num = r->num;
      l->demon = r->demon;
      return dirty (l);
    }
  if (r == l)
    r = Fractions_dup (l);
  if (l->positive && r->positive)
    {
      l = dirty (l);
      if (r->whole <= l->whole)
        {
          l->whole = l->whole-r->whole;
          if (Fractions_isZero (l))
            {
              l->num = r->num;
              l->demon = r->demon;
              if ((l->whole == 0) && (l->num == 0))
                l->positive = TRUE;
              else
                l->positive = FALSE;
            }
          else if (subND (l, r))
            if (l->whole >= 1)
              l->whole -= 1;
            else
              l->positive = FALSE;
        }
      else
        {
          l->whole = r->whole-l->whole;
          l->positive = FALSE;
          s = Fractions_initFract (0, l->num, l->demon);
          t = Fractions_initFract (0, r->num, r->demon);
          if (subND (t, s))
            l->whole -= 1;
          l->num = t->num;
          l->demon = t->demon;
        }
    }
  else if (! l->positive && ! r->positive)
    l = Fractions_inc (l, Fractions_negate (r));
  else if (l->positive && ! r->positive)
    l = Fractions_inc (l, Fractions_negate (r));
  else if (! l->positive && r->positive)
    return Fractions_negate (Fractions_inc (Fractions_negate (l), r));
  else
    M2RTS_HALT (0);
  return Fractions_simplify (l);
}


/*
   simplify - simplify the fraction or expression.
*/

Fractions_Fract Fractions_simplify (Fractions_Fract f)
{
  if (isSpecial (f))
    return simplifys (f);
  else
    return simplifyc (f);
}


/*
   initFract - initialise a fraction, which is expressed as:  w + n/d.
*/

Fractions_Fract Fractions_initFract (long unsigned int w, long unsigned int n, long unsigned int d)
{
  Fractions_Fract f;

  f = newFract ();
  f->positive = TRUE;
  f->whole = w;
  f->num = n;
  f->demon = d;
  f->op = oFract;
  f->left = NULL;
  f->right = NULL;
  f->dirty = TRUE;
  f->special = NONE;
  return f;
}


/*
   add3 - returns a new fraction which contains the result of a+b+c.
*/

Fractions_Fract Fractions_add3 (Fractions_Fract a, Fractions_Fract b, Fractions_Fract c)
{
  return Fractions_add (a, Fractions_add (b, c));
}


/*
   mult3 - returns a new fraction which contains the result of a * b * c.
*/

Fractions_Fract Fractions_mult3 (Fractions_Fract a, Fractions_Fract b, Fractions_Fract c)
{
  return Fractions_mult (a, Fractions_mult (b, c));
}


/*
   mark - marks Fract, f, to be saved from garbage collection.
*/

void Fractions_mark (Fractions_Fract f)
{
  GC_markEntity (f->fentity);
}


/*
   dup - returns a duplicate of Fract, f.
*/

Fractions_Fract Fractions_dup (Fractions_Fract f)
{
  f = Fractions_simplify (f);
  if ((isConst (f)) || (isSpecialConst (f)))
    return dupc (f);
  else
    return dups (f);
}


/*
   areEqual - return TRUE if l = r.
*/

unsigned int Fractions_areEqual (Fractions_Fract l, Fractions_Fract r)
{
  if (l == r)
    return TRUE;
  else if ((! (isSpecial (l))) && (! (isSpecial (r))))
    return Fractions_isEqual (l, r);
  else if ((isSpecialConst (l)) && (isSpecialConst (r)))
    return l->special == r->special;
  else if ((isSpecialConst (l)) || (isSpecialConst (r)))
    return FALSE;
  else if ((isExpr (l)) && (isExpr (r)))
    if (l->op == r->op)
      switch (l->op)
        {
          case oAdd:
          case oMult:
            return ((Fractions_areEqual (l->left, r->left)) && (Fractions_areEqual (l->right, r->right))) || ((Fractions_areEqual (l->left, r->right)) && (Fractions_areEqual (l->right, r->left)));
            break;

          case oSub:
          case oDiv:
          case oPower:
            return (Fractions_areEqual (l->left, r->left)) && (Fractions_areEqual (l->right, r->right));
            break;

          case oSin:
          case oCos:
          case oTan:
          case oNegate:
            return Fractions_areEqual (l->left, r->left);
            break;


          default:
            M2RTS_HALT (0);
            break;
        }
  return FALSE;
}


/*
   getReal - returns a REAL value of, f.
*/

double Fractions_getReal (Fractions_Fract f)
{
  double r;

  f = toConst (f);
  if (Fractions_isZero (f))
    return 0.0;
  else
    {
      r = (double ) (f->whole);
      if ((f->num != 0) && (f->demon != 0))
        r = r+(((double ) (f->num))/((double ) (f->demon)));
      if (f->positive)
        return r;
      else
        return -r;
    }
}


/*
   getFract - returns the, whole, numerator and demonimator value of, f.
*/

void Fractions_getFract (Fractions_Fract f, long unsigned int *w, long unsigned int *n, long unsigned int *d)
{
  f = toConst (f);
  (*w) = f->whole;
  (*n) = f->num;
  (*d) = f->demon;
}


/*
   getLongReal - returns a LONGREAL value of, f.
*/

long double Fractions_getLongReal (Fractions_Fract f)
{
  long double r;

  f = toConst (f);
  if (Fractions_isZero (f))
    return 0.0;
  else
    {
      r = (long double ) (f->whole);
      if ((f->num != 0) && (f->demon != 0))
        r = r+(((long double ) (f->num))/((long double ) (f->demon)));
      if (f->positive)
        return r;
      else
        return -r;
    }
}


/*
   putReal - returns a fraction in the range whole number + x/10000
*/

Fractions_Fract Fractions_putReal (double r)
{
  unsigned int w;
  unsigned int n;

  if (r >= 0.0)
    {
      w = (int) (r);
      n = (int) ((r-((double ) (w)))*10000.0);
      return Fractions_initFract ((long unsigned int) w, (long unsigned int) n, 10000);
    }
  else
    {
      r = -r;
      w = (int) (r);
      n = (int) ((r-((double ) (w)))*10000.0);
      return Fractions_negate (Fractions_initFract ((long unsigned int) w, (long unsigned int) n, 10000));
    }
}


/*
   writeFract - displays fraction, f.
*/

void Fractions_writeFract (Fractions_Fract f)
{
  if (isSpecial (f))
    writeFracts (f);
  else
    writeFractc (f);
}


/*
   isPositive - returns TRUE if, f, is positive.
*/

unsigned int Fractions_isPositive (Fractions_Fract f)
{
  if (isConst (f))
    return f->positive;
  else if (isSpecialConst (f))
    return TRUE;
  else if (isExpr (f))
    return Fractions_isPositive (toConst (f));
}


/*
   isNegative - returns TRUE if the value is negative.
*/

unsigned int Fractions_isNegative (Fractions_Fract f)
{
  return ! (Fractions_isPositive (f));
}


/*
   sin - return sin of angle, f.
*/

Fractions_Fract Fractions_sin (Fractions_Fract f)
{
  if (isSpecial (f))
    return buildUnary ((Operator) oSin, f);
  else
    return sinc (f);
}


/*
   cos - return cos of angle, f.
*/

Fractions_Fract Fractions_cos (Fractions_Fract f)
{
  if (isSpecial (f))
    return buildUnary ((Operator) oCos, f);
  else
    return cosc (f);
}


/*
   tan - return tan of angle, f.
*/

Fractions_Fract Fractions_tan (Fractions_Fract f)
{
  if (isSpecial (f))
    return buildUnary ((Operator) oTan, f);
  else
    return tanc (f);
}

void _M2_Fractions_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  init ();
  if (runRegression)
    regressionTest ();
}

void _M2_Fractions_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
