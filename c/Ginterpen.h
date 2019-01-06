/* automatically created by mc from ../git-pge-frozen/m2/interpen.def.  */


#if !defined (_interpen_H)
#   define _interpen_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "Gcoord.h"
#   include "Gsegment.h"

#   if defined (_interpen_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct interpen_interCircle_r interpen_interCircle;

struct interpen_interCircle_r {
                                double radius;
                                coord_Coord center;
                              };


/*
   segmentsCollide - returns TRUE if segment, a, overlaps with, b.
                     If true is returned then collisionPoint will be set to the intersection
                     point.

; VAR collisionPoint: Coord
*/

EXTERN unsigned int interpen_segmentsCollide (segment_Segment a, segment_Segment b);

/*
   circleCollide - return TRUE if circles, a, b, collide.
*/

EXTERN unsigned int interpen_circleCollide (interpen_interCircle a, interpen_interCircle b);

/*
   circleSegmentCollide - return TRUE if circle, c, collides with segment, s.
*/

EXTERN unsigned int interpen_circleSegmentCollide (interpen_interCircle c, segment_Segment s);

/*
   initCircle -
*/

EXTERN interpen_interCircle interpen_initCircle (double radius, coord_Coord point);

/*
   unitTest -
*/

EXTERN void interpen_unitTest (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
