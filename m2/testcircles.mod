MODULE testcircles ;

FROM interpen IMPORT circleCollide, interCircle, initCircle ;
FROM libc IMPORT printf, exit ;
FROM coord IMPORT Coord, initCoord ;


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
   a, b  : interCircle ;
   ca, cb: Coord ;
BEGIN
   ca := initCoord (0.6, 0.7);
   cb := initCoord (0.675, 0.7);
   a := initCircle (0.05, ca);
   b := initCircle (0.05, cb);
   assert (circleCollide (a, b), __LINE__);

   ca := initCoord (0.6, 0.7);
   cb := initCoord (0.6, 0.625);
   a := initCircle (0.05, ca);
   b := initCircle (0.05, cb);
   assert (circleCollide (a, b), __LINE__);

   ca := initCoord (0.6, 0.7);
   cb := initCoord (0.4, 0.7);
   a := initCircle (0.05, ca);
   b := initCircle (0.05, cb);
   assert (NOT circleCollide (a, b), __LINE__);
END testCode ;


BEGIN
   testCode
END testcircles.
