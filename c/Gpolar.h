/* automatically created by mc from ../git-pge/m2/polar.def.  */


#if !defined (_polar_H)
#   define _polar_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "Gcoord.h"

#   if defined (_polar_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct polar_Polar_r polar_Polar;

struct polar_Polar_r {
                       double r;
                       double w;
                     };


/*
   initPolar - initialises a polar coordinate, r, is the radius (magnitude)
               and, w, is the angle.
*/

EXTERN polar_Polar polar_initPolar (double r, double w);

/*
   polarToCoord - convert a polar coordinate into a cartesian coordinate.
*/

EXTERN coord_Coord polar_polarToCoord (polar_Polar p);

/*
   coordToPolar - return a polar coordinate pair given a cartesian coordinate.
*/

EXTERN polar_Polar polar_coordToPolar (coord_Coord c);

/*
   rotatePolar - return a polar coordinate after rotating it by, w, radians.
*/

EXTERN polar_Polar polar_rotatePolar (polar_Polar p, double w);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
