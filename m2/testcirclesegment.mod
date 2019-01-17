MODULE testcirclesegment ;

FROM interpen IMPORT circleSegmentCollide, circleCollide, interCircle, initCircle ;
FROM libc IMPORT printf, exit ;
FROM coord IMPORT Coord, initCoord ;
FROM segment IMPORT Segment, initSegment ;
FROM history IMPORT whereHit ;


(*
   assert -
*)

PROCEDURE assert (b: BOOLEAN; line: CARDINAL) ;
BEGIN
   IF NOT b
   THEN
      printf ("%s:%d: assert failed\n", __FILE__, line)
   END
END assert ;


PROCEDURE testCode ;
VAR
   c  : interCircle ;
   ca : Coord ;
   s  : Segment ;
   p  : Coord ;
   ptn: CARDINAL ;
   at : whereHit ;
BEGIN
   ca := initCoord (0.6, 0.7) ;
   c := initCircle (0.05, ca) ;
   s := initSegment (initCoord (0.625, 0.2), initCoord (0.625, 0.8)) ;
   assert (circleSegmentCollide (c, s, p, at, ptn), __LINE__) ;
END testCode ;


BEGIN
   testCode
END testcirclesegment.
