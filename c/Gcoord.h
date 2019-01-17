/* automatically created by mc from ../git-pge/m2/coord.def.  */


#if !defined (_coord_H)
#   define _coord_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_coord_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct coord_Coord_r coord_Coord;

struct coord_Coord_r {
                       double x;
                       double y;
                     };


/*
   initCoord - initialises a coordinate pair.
*/

EXTERN coord_Coord coord_initCoord (double x, double y);

/*
   normaliseCoord - return a Coord whose length is 1.
*/

EXTERN coord_Coord coord_normaliseCoord (coord_Coord c);

/*
   perpendiculars - fill in c1 and c2 which are the two perpendicular values to, c.
                    c1 is the one defined by Hill 1994 where c is rotated
                    90 degrees anticlockwise.
*/

EXTERN void coord_perpendiculars (coord_Coord c, coord_Coord *c1, coord_Coord *c2);

/*
   perpendicular - return the perpendicular of, c.
                   This is the one defined by Hill 1994 where c is rotated
                   90 degrees anticlockwise.
*/

EXTERN coord_Coord coord_perpendicular (coord_Coord c);

/*
   scaleCoord - scale the coord, c, by, s.
*/

EXTERN coord_Coord coord_scaleCoord (coord_Coord c, double s);

/*
   negateCoord - negates both components of the vector, c.
*/

EXTERN coord_Coord coord_negateCoord (coord_Coord c);

/*
   subCoord - returns a - b.
*/

EXTERN coord_Coord coord_subCoord (coord_Coord a, coord_Coord b);

/*
   addCoord - returns a + b.
*/

EXTERN coord_Coord coord_addCoord (coord_Coord a, coord_Coord b);

/*
   lengthCoord - returns sqrt(c.x*c.x + c.y*c.y)
*/

EXTERN double coord_lengthCoord (coord_Coord c);

/*
   rotateCoord - rotate point, c, about the origin at theta radians.
*/

EXTERN coord_Coord coord_rotateCoord (coord_Coord c, double theta);

/*
   dotProd - performs a dot product of, a, and, b.
*/

EXTERN double coord_dotProd (coord_Coord a, coord_Coord b);

/*
   nearZeroCoord - returns TRUE if, a, is very close to (0, 0)
*/

EXTERN unsigned int coord_nearZeroCoord (coord_Coord a);

/*
   equalCoord - return true if a == b.  (very closely equal).
*/

EXTERN unsigned int coord_equalCoord (coord_Coord a, coord_Coord b);

/*
   projectVector - returns the vector, onto, after it has been
                   projected by, project.
*/

EXTERN coord_Coord coord_projectVector (coord_Coord project, coord_Coord onto);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
