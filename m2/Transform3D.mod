(* Copyright (C) 2012
                 Free Software Foundation, Inc. *)
(* This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GNU Modula-2 is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with gm2; see the file COPYING.  If not, write to the Free Software
Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. *)

IMPLEMENTATION MODULE Transform3D ;

IMPORT Fractions ;
IMPORT PolyMatrix3D ;

FROM PolyMatrix3D IMPORT MatrixValue, init, set ;
FROM Fractions IMPORT cos, sin, zero, one, dup, negate ;


(*
   rotate - returns a Matrix representing the rotate
            transformation about 0, 0 with r radians.
*)

PROCEDURE rotate (r: Fract) : Matrix ;
VAR
   m: Matrix ;
   v: MatrixValue ;
BEGIN
   v[1, 1] := cos(r)   ;   v[1, 2] :=  negate(sin(r)) ;   v[1, 3] := zero() ;
   v[2, 1] := sin(r)   ;   v[2, 2] :=  cos(r)         ;   v[2, 3] := zero() ;
   v[3, 1] := zero()   ;   v[3, 2] :=  zero()         ;   v[3, 3] := one() ;
   RETURN set(init(), v)
END rotate ;


(*
   scale - returns a Matrix representing the scale
           transformation by vector, p.
*)

PROCEDURE scale (p: Point) : Matrix ;
VAR
   m: Matrix ;
   v: MatrixValue ;
BEGIN
   v[1, 1] := dup(p.x) ;   v[1, 2] :=  zero()    ;   v[1, 3] := zero() ;
   v[2, 1] := zero()   ;   v[2, 2] :=  dup(p.y)  ;   v[2, 3] := zero() ;
   v[3, 1] := zero()   ;   v[3, 2] :=  zero()    ;   v[3, 3] := one() ;
   RETURN set(init(), v)
END scale ;


(*
   translate - returns a Matrix representing the translate
               transformation by vector, p.
*)

PROCEDURE translate (p: Point) : Matrix ;
VAR
   m: Matrix ;
   v: MatrixValue ;
BEGIN
   v[1, 1] := one()    ;   v[1, 2] :=  zero()   ;   v[1, 3] := zero() ;
   v[2, 1] := zero()   ;   v[2, 2] :=  one()    ;   v[2, 3] := zero() ;
   v[3, 1] := dup(p.x) ;   v[3, 2] :=  dup(p.y) ;   v[3, 3] := one() ;
   RETURN set(init(), v)
END translate ;


(*
   reflect - returns a Matrix representing the reflect
             transformation in line: y = mx + c.
*)

PROCEDURE reflect (m, x, c: Fract) : Matrix ;
BEGIN
   HALT ;
   RETURN NIL
END reflect ;


END Transform3D.
