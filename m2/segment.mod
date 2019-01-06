IMPLEMENTATION MODULE segment ;  (*!m2pim+gm2*)


(*
   initSegment -
*)

PROCEDURE initSegment (p1, p2: Coord) : Segment ;
VAR
   s: Segment ;
BEGIN
   s.point1 := p1 ;
   s.point2 := p2 ;
   RETURN s
END initSegment ;


END segment.
