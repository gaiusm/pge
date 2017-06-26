/* automatically created by mc from ../Points.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _Points_H
#define _Points_C

#   include "GFractions.h"

typedef struct Points_Point_r Points_Point;

struct Points_Point_r {
                        Fractions_Fract x;
                        Fractions_Fract y;
                      };


/*
   initPoint - returns a Point from two fractions.
               The fractions are contained within the point structure.
               It does not take a copy of the fractions.
*/

Points_Point Points_initPoint (Fractions_Fract x, Fractions_Fract y);

/*
   rootPoint - grafts, p, into the roots of the garbage tree.
*/

Points_Point Points_rootPoint (Points_Point p);

/*
   unRootPoint - removes, p, from the roots of the garbage tree.
*/

Points_Point Points_unRootPoint (Points_Point p);

/*
   dupPoint - returns a duplication of, p.
*/

Points_Point Points_dupPoint (Points_Point p);

/*
   markPoint - marks Point, p, to be saved from garbage collection.
*/

void Points_markPoint (Points_Point p);

/*
   addPoint - returns a new point (a+b).
*/

Points_Point Points_addPoint (Points_Point a, Points_Point b);

/*
   subPoint - returns a new point (a-b).
*/

Points_Point Points_subPoint (Points_Point a, Points_Point b);

/*
   negatePoint - negates the point, p.  The same point, p, is returned.
*/

Points_Point Points_negatePoint (Points_Point p);

/*
   scalePoint - returns a new point which is scaled by, s.
*/

Points_Point Points_scalePoint (Points_Point p, Fractions_Fract s);

/*
   zeroPoint - returns a new point (0, 0)
*/

Points_Point Points_zeroPoint (void);


/*
   initPoint - returns a Point from two fractions.
               The fractions are contained within the point structure.
               It does not take a copy of the fractions.
*/

Points_Point Points_initPoint (Fractions_Fract x, Fractions_Fract y)
{
  Points_Point p;

  p.x = x;
  p.y = y;
  return p;
}


/*
   rootPoint - grafts, p, into the roots of the garbage tree.
*/

Points_Point Points_rootPoint (Points_Point p)
{
  p.x = Fractions_root (p.x);
  p.y = Fractions_root (p.y);
  return p;
}


/*
   unRootPoint - removes, p, from the roots of the garbage tree.
*/

Points_Point Points_unRootPoint (Points_Point p)
{
  p.x = Fractions_unroot (p.x);
  p.y = Fractions_unroot (p.y);
  return p;
}


/*
   dupPoint - returns a duplication of, p.
*/

Points_Point Points_dupPoint (Points_Point p)
{
  Points_Point p1;

  p1.x = Fractions_dup (p.x);
  p1.y = Fractions_dup (p.y);
  return p1;
}


/*
   markPoint - marks Point, p, to be saved from garbage collection.
*/

void Points_markPoint (Points_Point p)
{
  Fractions_mark (p.x);
  Fractions_mark (p.y);
}


/*
   addPoint - returns a new point (a+b).
*/

Points_Point Points_addPoint (Points_Point a, Points_Point b)
{
  Points_Point c;

  c.x = Fractions_add (a.x, b.x);
  c.y = Fractions_add (a.y, b.y);
  return c;
}


/*
   subPoint - returns a new point (a-b).
*/

Points_Point Points_subPoint (Points_Point a, Points_Point b)
{
  Points_Point c;

  c.x = Fractions_sub (a.x, b.x);
  c.y = Fractions_sub (a.y, b.y);
  return c;
}


/*
   negatePoint - negates the point, p.  The same point, p, is returned.
*/

Points_Point Points_negatePoint (Points_Point p)
{
  p.x = Fractions_negate (p.x);
  p.y = Fractions_negate (p.y);
  return p;
}


/*
   scalePoint - returns a new point which is scaled by, s.
*/

Points_Point Points_scalePoint (Points_Point p, Fractions_Fract s)
{
  Points_Point p1;

  p1.x = Fractions_mult (p.x, s);
  p1.y = Fractions_mult (p.y, s);
  return p1;
}


/*
   zeroPoint - returns a new point (0, 0)
*/

Points_Point Points_zeroPoint (void)
{
  return Points_initPoint (Fractions_zero (), Fractions_zero ());
}

void _M2_Points_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_Points_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
