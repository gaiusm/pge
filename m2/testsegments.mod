MODULE testsegments ;

FROM interpen IMPORT segmentsCollide ;
FROM libc IMPORT printf, exit ;
FROM coord IMPORT Coord, initCoord, equalCoord ;
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
   s0, s1    : Segment ;
   p         : Coord ;
   ptn0, ptn1: CARDINAL ;
   at0, at1  : whereHit ;
BEGIN
   s0 := initSegment (initCoord (0.6, 0.2), initCoord (0.6, 0.8)) ;
   s1 := initSegment (initCoord (0.2, 0.6), initCoord (0.8, 0.6)) ;
   assert (segmentsCollide (s0, s1, p, at0, at1, ptn0, ptn1), __LINE__) ;
   assert (at0 = edge, __LINE__) ;
   assert (at1 = edge, __LINE__) ;
   assert (equalCoord (p, initCoord (0.6, 0.6)), __LINE__) ;
END testCode ;


BEGIN
   testCode
END testsegments.
