IMPLEMENTATION MODULE interpen ;  (*!m2pim+gm2*)

FROM coord IMPORT initCoord, subCoord, dotProd, normaliseCoord, lengthCoord, addCoord ;
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
   segmentCollide - returns TRUE if segment, a, overlaps with, b.
                    If true is returned then collisionPoint will be set to the intersection
                    point.
*)

PROCEDURE segmentsCollide (a, b: Segment) : BOOLEAN ;
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
   circleSegmentCollide -
*)

PROCEDURE circleSegmentCollide (c: interCircle; s: Segment) : BOOLEAN ;
VAR
   d, lc, p, nearest: Coord ;
BEGIN
   IF circlePointCollide (c, s.point1) OR circlePointCollide (c, s.point2)
   THEN
      RETURN TRUE
   ELSE
      d := subCoord (s.point2, s.point1) ;
      lc := subCoord (c.center, s.point1) ;
      p := subCoord (lc, d) ;
      nearest := addCoord (s.point1, p) ;
      RETURN circlePointCollide (c, nearest) AND (lengthCoord (p) <= lengthCoord (d)) AND (0.0 <= dotProd (p, d))
   END
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
   assert (NOT segmentsCollide (s1, s2), __LINE__) ;
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
   c: interCircle ;
   s: Segment ;
BEGIN
   c := initCircle (3.0, initCoord (4.0, 4.0)) ;
   s := initSegment (initCoord (8.0, 6.0), initCoord (13.0, 6.0))
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
