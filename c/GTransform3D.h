/* automatically created by mc from ../git-pge/m2/Transform3D.def.  */


#if !defined (_Transform3D_H)
#   define _Transform3D_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GPolyMatrix3D.h"
#   include "GFractions.h"
#   include "GPoints.h"

#   if defined (_Transform3D_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   reflect - returns a Matrix representing the reflect
             transformation in line: y = mx + c.
*/

EXTERN PolyMatrix3D_Matrix Transform3D_reflect (Fractions_Fract m, Fractions_Fract x, Fractions_Fract c);

/*
   rotate - returns a Matrix representing the rotate
            transformation about 0, 0 with r radians.
*/

EXTERN PolyMatrix3D_Matrix Transform3D_rotate (Fractions_Fract r);

/*
   scale - returns a Matrix representing the scale
           transformation by vector, p.
*/

EXTERN PolyMatrix3D_Matrix Transform3D_scale (Points_Point p);

/*
   translate - returns a Matrix representing the translate
               transformation by vector, p.
*/

EXTERN PolyMatrix3D_Matrix Transform3D_translate (Points_Point p);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
