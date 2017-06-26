/* automatically created by mc from ../Points.def.  */


#if !defined (_Points_H)
#   define _Points_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GFractions.h"

#   if defined (_Points_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

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

EXTERN Points_Point Points_initPoint (Fractions_Fract x, Fractions_Fract y);

/*
   rootPoint - grafts, p, into the roots of the garbage tree.
*/

EXTERN Points_Point Points_rootPoint (Points_Point p);

/*
   unRootPoint - removes, p, from the roots of the garbage tree.
*/

EXTERN Points_Point Points_unRootPoint (Points_Point p);

/*
   dupPoint - returns a duplication of, p.
*/

EXTERN Points_Point Points_dupPoint (Points_Point p);

/*
   markPoint - marks Point, p, to be saved from garbage collection.
*/

EXTERN void Points_markPoint (Points_Point p);

/*
   addPoint - returns a new point (a+b).
*/

EXTERN Points_Point Points_addPoint (Points_Point a, Points_Point b);

/*
   subPoint - returns a new point (a-b).
*/

EXTERN Points_Point Points_subPoint (Points_Point a, Points_Point b);

/*
   negatePoint - negates the point, p.  The same point, p, is returned.
*/

EXTERN Points_Point Points_negatePoint (Points_Point p);

/*
   scalePoint - returns a new point which is scaled by, s.
*/

EXTERN Points_Point Points_scalePoint (Points_Point p, Fractions_Fract s);

/*
   zeroPoint - returns a new point (0, 0)
*/

EXTERN Points_Point Points_zeroPoint (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
