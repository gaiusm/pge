/* automatically created by mc from ../git-pge/m2/interpen.def.  */


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
#   include "Ghistory.h"

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

EXTERN unsigned int interpen_segmentsCollide (segment_Segment a, segment_Segment b, coord_Coord *p, history_whereHit *ata, history_whereHit *atb, unsigned int *ptna, unsigned int *ptnb);

/*
   circleCollide - return TRUE if circles, a, b, collide.
*/

EXTERN unsigned int interpen_circleCollide (interpen_interCircle a, interpen_interCircle b);

/*
   circleSegmentCollide - Pre-condition:  interCirle, c, and Segment, s, are well formed.
                          Post-condition:  return TRUE if circle, c, collides with segment, s.
                          If true is returned then the, point, on the line in deepest collision
                          with the circle is filled in and likewise, at, is set to corner or edge.
                          Indicating which part of the segment collides with the circle.
                          ptn will be set to 0 if point1 of the segment collides with the circle.
                          ptn will be set to 1 if point2 of the segment collides with the circle.
*/

EXTERN unsigned int interpen_circleSegmentCollide (interpen_interCircle c, segment_Segment s, coord_Coord *point, history_whereHit *at, unsigned int *ptn);

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
