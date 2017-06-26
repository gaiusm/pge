(* Copyright (C) 2011 Free Software Foundation, Inc. *)
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
Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA. *)

IMPLEMENTATION MODULE coord ;

FROM libm IMPORT cos, sin, sqrt ;
FROM roots IMPORT nearZero ;


(*
   initCoord - initialises a coordinate pair.
*)

PROCEDURE initCoord (x, y: REAL) : Coord ;
VAR
   c: Coord ;
BEGIN
   c.x := x ;
   c.y := y ;
   RETURN c
END initCoord ;


(*
   normaliseCoord - return a Coord whose length is 1.
*)

PROCEDURE normaliseCoord (c: Coord) : Coord ;
VAR
   h: REAL ;
BEGIN
   h := lengthCoord(c) ;
   IF nearZero(h)
   THEN
      h := 1.0
   END ;
   c.x := c.x / h ;
   c.y := c.y / h ;
   RETURN c
END normaliseCoord ;


(*
   perpendiculars - fill in c1 and c2 which are the two perpendicular values to, c.
*)

PROCEDURE perpendiculars (c: Coord; VAR c1, c2: Coord) ;
BEGIN
   c1 := initCoord (-c.y, c.x) ;
   c2 := initCoord (c.y, -c.x)
END perpendiculars ;


(*
   perpendicular - return the perpendicular of, c.
                   This is the one defined by Hill 1994 where, c, is rotated
                   90 degrees anticlockwise.
*)

PROCEDURE perpendicular (c: Coord) : Coord ;
BEGIN
   RETURN initCoord (-c.y, c.x)
END perpendicular ;


(*
   scaleCoord - scale the coord, c, by, s.
*)

PROCEDURE scaleCoord (c: Coord; s: REAL) : Coord ;
BEGIN
   c.x := c.x * s ;
   c.y := c.y * s ;
   RETURN c
END scaleCoord ;


(*
   subCoord - returns a - b.
*)

PROCEDURE subCoord (a, b: Coord) : Coord ;
BEGIN
   RETURN initCoord (a.x-b.x, a.y-b.y)
END subCoord ;


(*
   addCoord - returns a + b.
*)

PROCEDURE addCoord (a, b: Coord) : Coord ;
BEGIN
   RETURN initCoord (a.x+b.x, a.y+b.y)
END addCoord ;


(*
   lengthCoord - returns sqrt(c.x*c.x + c.y*c.y)
*)

PROCEDURE lengthCoord (c: Coord) : REAL ;
BEGIN
   RETURN sqrt (c.x*c.x + c.y*c.y)
END lengthCoord ;


(*
   rotateCoord - rotate point, c, about the origin at theta radians.
*)

PROCEDURE rotateCoord (c: Coord; theta: REAL) : Coord ;
BEGIN
   RETURN initCoord (c.x * cos (theta) - c.y * sin (theta),
                     c.x * sin (theta) + c.y * cos (theta))
END rotateCoord ;


(*
   dotProd - performs a dot product of, a, and, b.
*)

PROCEDURE dotProd (a, b: Coord) : REAL ;
BEGIN
   RETURN a.x*b.x + a.y*b.y
END dotProd ;


END coord.
