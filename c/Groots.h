/* automatically created by mc from ../git-pge/m2/roots.def.  */


#if !defined (_roots_H)
#   define _roots_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "Gcoord.h"

#   if defined (_roots_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   findOctic - returns TRUE if a root >= 0 exists for the equation:

                 8     7    6    5    4    3    2
               ax  + bx + cx + dx + ex + fx + gx + hx + i = 0
*/

EXTERN unsigned int roots_findOctic (double a, double b, double c, double d, double e, double f, double g, double h, double i, double *x0);

/*
   findQuadratic - returns TRUE if scalar values of x can be found
                   for.

                     2
                   ax  +  bx + c == 0
*/

EXTERN unsigned int roots_findQuadratic (double a, double b, double c, double *x0, double *x1);

/*
   findQuadraticRoots - returns the number of scalar values of x >= 0 which satisfy:

                          2
                        ax  +  bx + c == 0

                        x[0] will be the smallest root >= 0
                        x[1] is the next root.
*/

EXTERN unsigned int roots_findQuadraticRoots (double a, double b, double c, double *x, unsigned int _x_high);

/*
   findQuartic - returns TRUE if a scalar root can be found for:

                   4      3      2
                 ax  +  bx  +  cx  +  dx +  e  == 0

                 TRUE is only returned if a positive value for
                 x is found and it returns the smallest value for x.
*/

EXTERN unsigned int roots_findQuartic (double a, double b, double c, double d, double e, double *x);

/*
   findQuarticRoots - returns the number of positive scalar roots which can be found for:

                        4      3      2
                      ax  +  bx  +  cx  +  dx +  e  == 0
*/

EXTERN unsigned int roots_findQuarticRoots (double a, double b, double c, double d, double e, double *x, unsigned int _x_high);

/*
   findAllRootsQuartic - returns all the real roots for:

                           4      3      2
                         ax  +  bx  +  cx  +  dx +  e  == 0
*/

EXTERN unsigned int roots_findAllRootsQuartic (double a, double b, double c, double d, double e, double *x, unsigned int _x_high);

/*
   nearZero - returns TRUE if, r, is close to 0.0
*/

EXTERN unsigned int roots_nearZero (double r);

/*
   nearSame - returns TRUE if, |a-b| < epsilon
*/

EXTERN unsigned int roots_nearSame (double a, double b);

/*
   nearCoord - returns TRUE if position, a, is very close to, b.
*/

EXTERN unsigned int roots_nearCoord (coord_Coord a, coord_Coord b);

/*
   setTrace - turns tracing on/off.
*/

EXTERN void roots_setTrace (unsigned int on);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
