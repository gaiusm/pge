/* automatically created by mc from ../git-pge/m2/segment.def.  */


#if !defined (_segment_H)
#   define _segment_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "Gcoord.h"

#   if defined (_segment_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct segment_Segment_r segment_Segment;

typedef struct segment_Line_r segment_Line;

struct segment_Segment_r {
                           coord_Coord point1;
                           coord_Coord point2;
                         };

struct segment_Line_r {
                        coord_Coord base;
                        coord_Coord direction;
                      };


/*
   initSegment -
*/

EXTERN segment_Segment segment_initSegment (coord_Coord p1, coord_Coord p2);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
