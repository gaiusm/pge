/* automatically created by mc from ../git-pge/m2/segment.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _segment_H
#define _segment_C


typedef struct segment_Segment_r segment_Segment;

typedef struct segment_Line_r segment_Line;

typedef struct coord_Coord_r coord_Coord;

struct coord_Coord_r {
                       double x;
                       double y;
                     };

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

segment_Segment segment_initSegment (coord_Coord p1, coord_Coord p2);


/*
   initSegment -
*/

segment_Segment segment_initSegment (coord_Coord p1, coord_Coord p2)
{
  segment_Segment s;

  s.point1 = p1;
  s.point2 = p2;
  return s;
}

void _M2_segment_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_segment_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
