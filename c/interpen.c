/* automatically created by mc from ../git-pge/m2/interpen.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#define _interpen_H
#define _interpen_C

#   include "Gcoord.h"
#   include "Gsegment.h"
#   include "Groots.h"
#   include "Glibc.h"

typedef struct interpen_interCircle_r interpen_interCircle;

typedef struct Range_r Range;

typedef enum {history_corner, history_edge} history_whereHit;

struct interpen_interCircle_r {
                                double radius;
                                coord_Coord center;
                              };

struct Range_r {
                 double maximum;
                 double minimum;
               };

unsigned int interpen_segmentsCollide (segment_Segment a, segment_Segment b, coord_Coord *p, history_whereHit *ata, history_whereHit *atb, unsigned int *ptna, unsigned int *ptnb);

/*
   circleCollide - return TRUE if circles, a, b, collide.
*/

unsigned int interpen_circleCollide (interpen_interCircle a, interpen_interCircle b);

/*
   circleSegmentCollide - Pre-condition:  interCirle, c, and Segment, s, are well formed.
                          Post-condition:  return TRUE if circle, c, collides with segment, s.
                          If true is returned then the, point, on the line in deepest collision
                          with the circle is filled in and likewise, at, is set to corner or edge.
                          Indicating which part of the segment collides with the circle.
                          ptn will be set to 0 if point1 of the segment collides with the circle.
                          ptn will be set to 1 if point2 of the segment collides with the circle.
*/

unsigned int interpen_circleSegmentCollide (interpen_interCircle c, segment_Segment s, coord_Coord *point, history_whereHit *at, unsigned int *ptn);

/*
   initCircle -
*/

interpen_interCircle interpen_initCircle (double radius, coord_Coord point);

/*
   unitTest -
*/

void interpen_unitTest (void);

/*
   assert -
*/

static void assert (unsigned int condition, unsigned int line);

/*
   doSegmentsCollide -
*/

static unsigned int doSegmentsCollide (segment_Segment a, segment_Segment b);

/*
   pointSegmentCollide - return true if point, p, lies on the segment, s.
*/

static unsigned int pointSegmentCollide (coord_Coord p, segment_Segment s);

/*
   doSegmentCollide2 -



// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines
// intersect the intersection point may be stored in the floats i_x and i_y.
char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return 1;
    }

    return 0; // No collision
}

Andre LeMothe

*/

static unsigned int doSegmentCollide2 (segment_Segment a, segment_Segment b, coord_Coord *p);

/*
   rotateVector90 -
*/

static coord_Coord rotateVector90 (coord_Coord v);

/*
   parallelVectors - return TRUE if vectors, a, b, are parallel.
*/

static unsigned int parallelVectors (coord_Coord a, coord_Coord b);

/*
   overlappingRange - return TRUE if, r1, and, r2, overlap.
*/

static unsigned int overlappingRange (Range r1, Range r2);

/*
   unitCoord -
*/

static coord_Coord unitCoord (coord_Coord c);

/*
   projectSegment -
*/

static Range projectSegment (segment_Segment s, coord_Coord onto);

/*
   onOneSide -
*/

static unsigned int onOneSide (segment_Line axis, segment_Segment s);

/*
   sortRange -
*/

static Range sortRange (Range r);

/*
   circlePointCollide - returns TRUE if circle, c, and point, p, collide.
*/

static unsigned int circlePointCollide (interpen_interCircle c, coord_Coord p);

/*
   testSegmentSegment -
*/

static void testSegmentSegment (void);

/*
   testCirclePoint -
*/

static void testCirclePoint (void);

/*
   testCircleSegment -
*/

static void testCircleSegment (void);


/*
   assert -
*/

static void assert (unsigned int condition, unsigned int line)
{
  if (! condition)
    libc_printf ((char *) "%s:%d: assert failed\\n", 22, "../git-pge/m2/interpen.mod", line);
}


/*
   doSegmentsCollide -
*/

static unsigned int doSegmentsCollide (segment_Segment a, segment_Segment b)
{
  segment_Line axisA;
  segment_Line axisB;
  Range rangeA;
  Range rangeB;

  axisA.base = a.point1;
  axisA.direction = coord_subCoord (a.point2, a.point1);
  if (onOneSide (axisA, b))
    return FALSE;
  axisB.base = b.point1;
  axisB.direction = coord_subCoord (b.point2, b.point1);
  if (onOneSide (axisB, a))
    return FALSE;
  if (parallelVectors (axisA.direction, axisB.direction))
    {
      rangeA = projectSegment (a, axisA.direction);
      rangeB = projectSegment (b, axisB.direction);
      return overlappingRange (rangeA, rangeB);
    }
  else
    return TRUE;
}


/*
   pointSegmentCollide - return true if point, p, lies on the segment, s.
*/

static unsigned int pointSegmentCollide (coord_Coord p, segment_Segment s)
{
  coord_Coord d;
  coord_Coord lp;
  coord_Coord pr;

  d = coord_subCoord (s.point2, s.point1);
  lp = coord_subCoord (p, s.point1);
  pr = coord_projectVector (lp, d);
  return ((coord_equalCoord (lp, pr)) && ((coord_lengthCoord (pr)) <= (coord_lengthCoord (d)))) && (0.0 <= (coord_dotProd (pr, d)));
}


/*
   doSegmentCollide2 -



// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines
// intersect the intersection point may be stored in the floats i_x and i_y.
char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return 1;
    }

    return 0; // No collision
}

Andre LeMothe

*/

static unsigned int doSegmentCollide2 (segment_Segment a, segment_Segment b, coord_Coord *p)
{
  coord_Coord aVec;
  coord_Coord bVec;
  double d;
  double s;
  double t;

  aVec = coord_initCoord (a.point2.x-a.point1.x, a.point2.y-a.point1.y);
  bVec = coord_initCoord (b.point2.x-b.point1.x, b.point2.y-b.point1.y);
  d = (-(bVec.x*aVec.y))+(aVec.x*bVec.y);
  if (roots_nearZero (d))
    return FALSE;
  s = ((-(aVec.y*(a.point1.x-b.point1.x)))+(aVec.x*(a.point1.y-b.point1.y)))/d;
  t = ((bVec.x*(a.point1.y-b.point1.y))-(bVec.y*(a.point1.x-b.point1.x)))/d;
  if ((((s >= 0.0) && (s <= 1.0)) && (t >= 0.0)) && (t <= 1.0))
    {
      /* collision detected.  */
      (*p).x = a.point1.x+(t*aVec.x);
      (*p).y = a.point1.y+(t*aVec.y);
      return TRUE;
    }
  /* no collision.  */
  return FALSE;
}


/*
   rotateVector90 -
*/

static coord_Coord rotateVector90 (coord_Coord v)
{
  coord_Coord r;

  r.x = -v.y;
  r.y = v.x;
  return v;
}


/*
   parallelVectors - return TRUE if vectors, a, b, are parallel.
*/

static unsigned int parallelVectors (coord_Coord a, coord_Coord b)
{
  coord_Coord normalA;

  normalA = rotateVector90 (a);
  return roots_nearZero (coord_dotProd (normalA, b));
}


/*
   overlappingRange - return TRUE if, r1, and, r2, overlap.
*/

static unsigned int overlappingRange (Range r1, Range r2)
{
  /* flip the result of the two ranges not overlapping.  */
  return ! ((r1.minimum > r2.maximum) || (r1.maximum < r2.minimum));
}


/*
   unitCoord -
*/

static coord_Coord unitCoord (coord_Coord c)
{
  return coord_normaliseCoord (c);
}


/*
   projectSegment -
*/

static Range projectSegment (segment_Segment s, coord_Coord onto)
{
  Range r;
  coord_Coord ontoUnit;

  ontoUnit = unitCoord (onto);
  r.minimum = coord_dotProd (ontoUnit, s.point1);
  r.maximum = coord_dotProd (ontoUnit, s.point2);
  r = sortRange (r);
  return r;
}


/*
   onOneSide -
*/

static unsigned int onOneSide (segment_Line axis, segment_Segment s)
{
  coord_Coord d1;
  coord_Coord d2;
  coord_Coord n;

  d1 = coord_subCoord (s.point1, axis.base);
  d2 = coord_subCoord (s.point2, axis.base);
  n = rotateVector90 (axis.direction);
  return ((coord_dotProd (n, d1))*(coord_dotProd (n, d2))) > 0.0;
}


/*
   sortRange -
*/

static Range sortRange (Range r)
{
  Range sorted;

  sorted = r;
  if (r.minimum > r.maximum)
    {
      sorted.minimum = r.maximum;
      sorted.maximum = r.minimum;
    }
  return sorted;
}


/*
   circlePointCollide - returns TRUE if circle, c, and point, p, collide.
*/

static unsigned int circlePointCollide (interpen_interCircle c, coord_Coord p)
{
  coord_Coord distance;

  distance = coord_subCoord (c.center, p);
  return (coord_lengthCoord (distance)) <= c.radius;
}


/*
   testSegmentSegment -
*/

static void testSegmentSegment (void)
{
  coord_Coord a;
  coord_Coord b;
  coord_Coord c;
  coord_Coord d;
  segment_Segment s1;
  segment_Segment s2;

  a = coord_initCoord (3.0, 4.0);
  b = coord_initCoord (11.0, 1.0);
  c = coord_initCoord (8.0, 4.0);
  d = coord_initCoord (11.0, 7.0);
  s1 = segment_initSegment (a, b);
  s2 = segment_initSegment (c, d);
  assert (! (doSegmentsCollide (s1, s2)), 382);
}


/*
   testCirclePoint -
*/

static void testCirclePoint (void)
{
  interpen_interCircle c;
  coord_Coord p1;
  coord_Coord p2;

  c = interpen_initCircle (3.0, coord_initCoord (6.0, 4.0));
  p1 = coord_initCoord (8.0, 3.0);
  p2 = coord_initCoord (11.0, 7.0);
  assert (circlePointCollide (c, p1), 413);
  assert (! (circlePointCollide (c, p2)), 414);
}


/*
   testCircleSegment -
*/

static void testCircleSegment (void)
{
  interpen_interCircle c;
  segment_Segment s;
  coord_Coord p;
  history_whereHit at;
  unsigned int ptn;

  c = interpen_initCircle (3.0, coord_initCoord (4.0, 4.0));
  s = segment_initSegment (coord_initCoord (8.0, 6.0), coord_initCoord (13.0, 6.0));
  assert (! (interpen_circleSegmentCollide (c, s, &p, &at, &ptn)), 432);
}

unsigned int interpen_segmentsCollide (segment_Segment a, segment_Segment b, coord_Coord *p, history_whereHit *ata, history_whereHit *atb, unsigned int *ptna, unsigned int *ptnb)
{
  /* 
   segmentCollide - returns TRUE if segment, a, overlaps with, b.
                    If true is returned then, p, will be set to
                    the intersection point.  ata, atb determine where segment, a,
                    and segment, b, hit (corner or edge).  If ata = corner then
                    ptna is either 0 or 1 representing the point which collided.
                    Likewise if atb = corner then
                    ptna is either 0 or 1 representing the point which collided.
  */
  if (pointSegmentCollide (a.point1, b))
    {
      (*ptna) = 0;
      (*ata) = history_corner;
      (*p) = a.point1;
      (*atb) = history_edge;
      (*ptnb) = 0;
      return TRUE;
    }
  else if (pointSegmentCollide (a.point2, b))
    {
      (*ptna) = 1;
      (*ata) = history_corner;
      (*p) = a.point2;
      (*atb) = history_edge;
      (*ptnb) = 0;
      return TRUE;
    }
  else if (pointSegmentCollide (b.point1, a))
    {
      (*ptna) = 0;
      (*ata) = history_corner;
      (*p) = b.point1;
      (*atb) = history_edge;
      (*ptnb) = 0;
      return TRUE;
    }
  else if (pointSegmentCollide (b.point2, a))
    {
      (*ptna) = 1;
      (*ata) = history_corner;
      (*p) = b.point2;
      (*atb) = history_edge;
      (*ptnb) = 0;
      return TRUE;
    }
  else if (doSegmentCollide2 (a, b, p))
    {
      (*ptna) = 0;
      (*ata) = history_edge;
      (*atb) = history_edge;
      (*ptnb) = 0;
      return TRUE;
    }
  return FALSE;
}


/*
   circleCollide - return TRUE if circles, a, b, collide.
*/

unsigned int interpen_circleCollide (interpen_interCircle a, interpen_interCircle b)
{
  double radiusSum;
  coord_Coord distance;

  radiusSum = a.radius+b.radius;
  distance = coord_subCoord (a.center, b.center);
  return (coord_lengthCoord (distance)) <= radiusSum;
}


/*
   circleSegmentCollide - Pre-condition:  interCirle, c, and Segment, s, are well formed.
                          Post-condition:  return TRUE if circle, c, collides with segment, s.
                          If true is returned then the, point, on the line in deepest collision
                          with the circle is filled in and likewise, at, is set to corner or edge.
                          Indicating which part of the segment collides with the circle.
                          ptn will be set to 0 if point1 of the segment collides with the circle.
                          ptn will be set to 1 if point2 of the segment collides with the circle.
*/

unsigned int interpen_circleSegmentCollide (interpen_interCircle c, segment_Segment s, coord_Coord *point, history_whereHit *at, unsigned int *ptn)
{
  coord_Coord segmentVector;
  coord_Coord lc;
  coord_Coord p;
  coord_Coord nearest;

  if (circlePointCollide (c, s.point1))
    {
      (*point) = s.point1;
      (*at) = history_corner;
      (*ptn) = 0;
      return TRUE;
    }
  else if (circlePointCollide (c, s.point2))
    {
      (*point) = s.point2;
      (*at) = history_corner;
      (*ptn) = 1;
      return TRUE;
    }
  else
    {
      segmentVector = coord_subCoord (s.point2, s.point1);
      lc = coord_subCoord (c.center, s.point1);
      p = coord_projectVector (lc, segmentVector);
      nearest = coord_addCoord (s.point1, p);
      if (((circlePointCollide (c, nearest)) && ((coord_lengthCoord (p)) <= (coord_lengthCoord (segmentVector)))) && (0.0 <= (coord_dotProd (p, segmentVector))))
        {
          (*ptn) = 0;
          (*point) = nearest;
          (*at) = history_edge;
          return TRUE;
        }
    }
  return FALSE;
}


/*
   initCircle -
*/

interpen_interCircle interpen_initCircle (double radius, coord_Coord point)
{
  interpen_interCircle c;

  c.radius = radius;
  c.center = point;
  return c;
}


/*
   unitTest -
*/

void interpen_unitTest (void)
{
  testSegmentSegment ();
  testCirclePoint ();
  testCircleSegment ();
}

void _M2_interpen_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_interpen_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
