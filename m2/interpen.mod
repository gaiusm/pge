IMPLEMENTATION MODULE interpen ;  (*!m2pim+gm2*)

FROM coord IMPORT initCoord, subCoord, dotProd, normaliseCoord, lengthCoord, addCoord, projectVector, equalCoord ;
FROM segment IMPORT Line, initSegment ;
FROM roots IMPORT nearZero ;
FROM libc IMPORT printf, exit ;


TYPE
   Range = RECORD
              maximum,
              minimum: REAL ;
           END ;


(*
   assert -
*)

PROCEDURE assert (condition: BOOLEAN; line: CARDINAL) ;
BEGIN
   IF NOT condition
   THEN
      printf ("%s:%d: assert failed\n", __FILE__, line)
   END
END assert ;


(*
   doSegmentsCollide -
*)

PROCEDURE doSegmentsCollide (a, b: Segment) : BOOLEAN ;
VAR
   axisA, axisB: Line ;
   rangeA, rangeB:  Range ;
BEGIN
   axisA.base := a.point1 ;
   axisA.direction := subCoord (a.point2, a.point1) ;
   IF onOneSide (axisA, b)
   THEN
      RETURN FALSE
   END ;

   axisB.base := b.point1 ;
   axisB.direction := subCoord (b.point2, b.point1) ;
   IF onOneSide (axisB, a)
   THEN
      RETURN FALSE
   END ;

   IF parallelVectors (axisA.direction, axisB.direction)
   THEN
      rangeA := projectSegment (a, axisA.direction) ;
      rangeB := projectSegment (b, axisB.direction) ;
      RETURN overlappingRange (rangeA, rangeB)
   ELSE
      RETURN TRUE
   END
END doSegmentsCollide ;


(*
   pointSegmentCollide - return true if point, p, lies on the segment, s.
*)

PROCEDURE pointSegmentCollide (p: Coord; s: Segment) : BOOLEAN ;
VAR
   d, lp, pr: Coord ;
BEGIN
   d := subCoord (s.point2, s.point1) ;
   lp := subCoord (p, s.point1) ;
   pr := projectVector (lp, d) ;
   RETURN equalCoord (lp, pr) AND (lengthCoord (pr) <= lengthCoord (d)) AND (0.0 <= dotProd (pr, d))
END pointSegmentCollide ;


(*
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

*)

PROCEDURE doSegmentCollide2 (a, b: Segment; VAR p: Coord) : BOOLEAN ;
VAR
   aVec, bVec: Coord ;
   d, s, t   : REAL ;
BEGIN
   aVec := initCoord (a.point2.x-a.point1.x, a.point2.y-a.point1.y) ;
   bVec := initCoord (b.point2.x-b.point1.x, b.point2.y-b.point1.y) ;

   d := -bVec.x * aVec.y + aVec.x * bVec.y ;
   IF nearZero (d)
   THEN
      RETURN FALSE
   END ;
   s := (-aVec.y * (a.point1.x - b.point1.x) + aVec.x * (a.point1.y - b.point1.y)) / d ;
   t := ( bVec.x * (a.point1.y - b.point1.y) - bVec.y * (a.point1.x - b.point1.x)) / d ;

   IF (s >= 0.0) AND (s <= 1.0) AND (t >= 0.0) AND (t <= 1.0)
   THEN
      (* collision detected.  *)
      p.x := a.point1.x + (t * aVec.x) ;
      p.y := a.point1.y + (t * aVec.y) ;
      RETURN TRUE
   END ;
   (* no collision.  *)
   RETURN FALSE
END doSegmentCollide2 ;


(*
   segmentCollide - returns TRUE if segment, a, overlaps with, b.
                    If true is returned then, p, will be set to
                    the intersection point.  ata, atb determine where segment, a,
                    and segment, b, hit (corner or edge).  If ata = corner then
                    ptna is either 0 or 1 representing the point which collided.
                    Likewise if atb = corner then
                    ptna is either 0 or 1 representing the point which collided.
*)

PROCEDURE segmentsCollide (a, b: Segment;
                           VAR p: Coord; VAR ata, atb: whereHit; VAR ptna, ptnb: CARDINAL) : BOOLEAN ;
BEGIN
   IF pointSegmentCollide (a.point1, b)
   THEN
      ptna := 0 ;
      ata := corner ;
      p := a.point1 ;
      atb := edge ;
      ptnb := 0 ;
      RETURN TRUE
   ELSIF pointSegmentCollide (a.point2, b)
   THEN
      ptna := 1 ;
      ata := corner ;
      p := a.point2 ;
      atb := edge ;
      ptnb := 0 ;
      RETURN TRUE
   ELSIF pointSegmentCollide (b.point1, a)
   THEN
      ptna := 0 ;
      ata := corner ;
      p := b.point1 ;
      atb := edge ;
      ptnb := 0 ;
      RETURN TRUE
   ELSIF pointSegmentCollide (b.point2, a)
   THEN
      ptna := 1 ;
      ata := corner ;
      p := b.point2 ;
      atb := edge ;
      ptnb := 0 ;
      RETURN TRUE
   ELSIF doSegmentCollide2 (a, b, p)
   THEN
      ptna := 0 ;
      ata := edge ;
      atb := edge ;
      ptnb := 0 ;
      RETURN TRUE
   END ;
   RETURN FALSE
END segmentsCollide ;


(*
   rotateVector90 -
*)

PROCEDURE rotateVector90 (v: Coord) : Coord ;
VAR
   r: Coord ;
BEGIN
   r.x := -v.y ;
   r.y := v.x ;
   RETURN v
END rotateVector90 ;


(*
   parallelVectors - return TRUE if vectors, a, b, are parallel.
*)

PROCEDURE parallelVectors (a, b: Coord) : BOOLEAN ;
VAR
   normalA: Coord ;
BEGIN
   normalA := rotateVector90 (a) ;
   RETURN nearZero (dotProd (normalA, b))
END parallelVectors ;


(*
   overlappingRange - return TRUE if, r1, and, r2, overlap.
*)

PROCEDURE overlappingRange (r1, r2: Range) : BOOLEAN ;
BEGIN
   (* flip the result of the two ranges not overlapping.  *)
   RETURN NOT ((r1.minimum > r2.maximum) OR (r1.maximum < r2.minimum))
END overlappingRange ;


(*
   unitCoord -
*)

PROCEDURE unitCoord (c: Coord) : Coord ;
BEGIN
   RETURN normaliseCoord (c)
END unitCoord ;


(*
   projectSegment -
*)

PROCEDURE projectSegment (s: Segment; onto: Coord) : Range ;
VAR
   r       : Range ;
   ontoUnit: Coord ;
BEGIN
   ontoUnit := unitCoord (onto) ;
   r.minimum := dotProd (ontoUnit, s.point1) ;
   r.maximum := dotProd (ontoUnit, s.point2) ;
   r := sortRange (r) ;
   RETURN r
END projectSegment ;


(*
   onOneSide -
*)

PROCEDURE onOneSide (axis: Line; s: Segment) : BOOLEAN ;
VAR
   d1, d2, n: Coord ;
BEGIN
   d1 := subCoord (s.point1, axis.base) ;
   d2 := subCoord (s.point2, axis.base) ;
   n := rotateVector90 (axis.direction) ;
   RETURN dotProd (n, d1) * dotProd (n, d2) > 0.0
END onOneSide ;


(*
   sortRange -
*)

PROCEDURE sortRange (r: Range) : Range ;
VAR
   sorted: Range ;
BEGIN
   sorted := r ;
   IF r.minimum > r.maximum
   THEN
      sorted.minimum := r.maximum ;
      sorted.maximum := r.minimum
   END ;
   RETURN sorted
END sortRange ;


(*
   circleCollide - return TRUE if circles, a, b, collide.
*)

PROCEDURE circleCollide (a, b: interCircle) : BOOLEAN ;
VAR
   radiusSum: REAL ;
   distance : Coord ;
BEGIN
   radiusSum := a.radius + b.radius ;
   distance := subCoord (a.center, b.center) ;
   RETURN lengthCoord (distance) <= radiusSum
END circleCollide ;


(*
   circleSegmentCollide - Pre-condition:  interCirle, c, and Segment, s, are well formed.
                          Post-condition:  return TRUE if circle, c, collides with segment, s.
                          If true is returned then the, point, on the line in deepest collision
                          with the circle is filled in and likewise, at, is set to corner or edge.
                          Indicating which part of the segment collides with the circle.
                          ptn will be set to 0 if point1 of the segment collides with the circle.
                          ptn will be set to 1 if point2 of the segment collides with the circle.
*)

PROCEDURE circleSegmentCollide (c: interCircle; s: Segment; VAR point: Coord; VAR at: whereHit; VAR ptn: CARDINAL) : BOOLEAN ;
VAR
   segmentVector, lc, p, nearest: Coord ;
BEGIN
   IF circlePointCollide (c, s.point1)
   THEN
      point := s.point1 ;
      at := corner ;
      ptn := 0 ;
      RETURN TRUE
   ELSIF circlePointCollide (c, s.point2)
   THEN
      point := s.point2 ;
      at := corner ;
      ptn := 1 ;
      RETURN TRUE
   ELSE
      segmentVector := subCoord (s.point2, s.point1) ;
      lc := subCoord (c.center, s.point1) ;
      p := projectVector (lc, segmentVector) ;
      nearest := addCoord (s.point1, p) ;
      IF circlePointCollide (c, nearest) AND (lengthCoord (p) <= lengthCoord (segmentVector)) AND (0.0 <= dotProd (p, segmentVector))
      THEN
         ptn := 0 ;
         point := nearest ;
         at := edge ;
         RETURN TRUE
      END
   END ;
   RETURN FALSE
END circleSegmentCollide ;


(*
   circlePointCollide - returns TRUE if circle, c, and point, p, collide.
*)

PROCEDURE circlePointCollide (c: interCircle; p: Coord) : BOOLEAN ;
VAR
   distance: Coord ;
BEGIN
   distance := subCoord (c.center, p) ;
   RETURN lengthCoord (distance) <= c.radius
END circlePointCollide ;


(*
   testSegmentSegment -
*)

PROCEDURE testSegmentSegment ;
VAR
   a, b, c, d: Coord ;
   s1, s2    : Segment ;
BEGIN
   a := initCoord (3.0, 4.0) ;
   b := initCoord (11.0, 1.0) ;
   c := initCoord (8.0, 4.0) ;
   d := initCoord (11.0, 7.0) ;
   s1 := initSegment (a, b) ;
   s2 := initSegment (c, d) ;
   assert (NOT doSegmentsCollide (s1, s2), __LINE__) ;
END testSegmentSegment ;


(*
   initCircle -
*)

PROCEDURE initCircle (radius: REAL; point: Coord) : interCircle ;
VAR
   c: interCircle ;
BEGIN
   c.radius := radius ;
   c.center := point ;
   RETURN c
END initCircle ;


(*
   testCirclePoint -
*)

PROCEDURE testCirclePoint ;
VAR
   c     : interCircle ;
   p1, p2: Coord ;
BEGIN
   c := initCircle (3.0, initCoord (6.0, 4.0)) ;
   p1 := initCoord (8.0, 3.0) ;
   p2 := initCoord (11.0, 7.0) ;

   assert (circlePointCollide (c, p1), __LINE__) ;
   assert (NOT circlePointCollide (c, p2), __LINE__)
END testCirclePoint ;


(*
   testCircleSegment -
*)

PROCEDURE testCircleSegment ;
VAR
   c  : interCircle ;
   s  : Segment ;
   p  : Coord ;
   at : whereHit ;
   ptn: CARDINAL ;
BEGIN
   c := initCircle (3.0, initCoord (4.0, 4.0)) ;
   s := initSegment (initCoord (8.0, 6.0), initCoord (13.0, 6.0)) ;
   assert (NOT circleSegmentCollide (c, s, p, at, ptn), __LINE__)
END testCircleSegment ;


(*
   unitTest -
*)

PROCEDURE unitTest ;
BEGIN
   testSegmentSegment ;
   testCirclePoint ;
   testCircleSegment
END unitTest ;


END interpen.
