/* automatically created by mc from ../git-pge-frozen/m2/interpen.mod.  */

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

struct interpen_interCircle_r {
                                double radius;
                                coord_Coord center;
                              };

struct Range_r {
                 double maximum;
                 double minimum;
               };

unsigned int interpen_segmentsCollide (segment_Segment a, segment_Segment b);

/*
   circleCollide - return TRUE if circles, a, b, collide.
*/

unsigned int interpen_circleCollide (interpen_interCircle a, interpen_interCircle b);

/*
   circleSegmentCollide -
*/

unsigned int interpen_circleSegmentCollide (interpen_interCircle c, segment_Segment s);

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
    libc_printf ((char *) "%s:%d: assert failed\\n", 22, "../git-pge-frozen/m2/interpen.mod", line);
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
  assert (! (interpen_segmentsCollide (s1, s2)), 227);
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
  assert (circlePointCollide (c, p1), 258);
  assert (! (circlePointCollide (c, p2)), 259);
}


/*
   testCircleSegment -
*/

static void testCircleSegment (void)
{
  interpen_interCircle c;
  segment_Segment s;

  c = interpen_initCircle (3.0, coord_initCoord (4.0, 4.0));
  s = segment_initSegment (coord_initCoord (8.0, 6.0), coord_initCoord (13.0, 6.0));
}

unsigned int interpen_segmentsCollide (segment_Segment a, segment_Segment b)
{
  segment_Line axisA;
  segment_Line axisB;
  Range rangeA;
  Range rangeB;

  /* 
   segmentCollide - returns TRUE if segment, a, overlaps with, b.
                    If true is returned then collisionPoint will be set to the intersection
                    point.
  */
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
   circleSegmentCollide -
*/

unsigned int interpen_circleSegmentCollide (interpen_interCircle c, segment_Segment s)
{
  coord_Coord d;
  coord_Coord lc;
  coord_Coord p;
  coord_Coord nearest;

  if ((circlePointCollide (c, s.point1)) || (circlePointCollide (c, s.point2)))
    return TRUE;
  else
    {
      d = coord_subCoord (s.point2, s.point1);
      lc = coord_subCoord (c.center, s.point1);
      p = coord_subCoord (lc, d);
      nearest = coord_addCoord (s.point1, p);
      return ((circlePointCollide (c, nearest)) && ((coord_lengthCoord (p)) <= (coord_lengthCoord (d)))) && (0.0 <= (coord_dotProd (p, d)));
    }
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
