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

IMPLEMENTATION MODULE polar ;

FROM coord IMPORT initCoord ;
FROM roots IMPORT nearZero ;
FROM libm IMPORT sin, cos, sqrt, asin ;
FROM libc IMPORT printf ;
FROM MathLib0 IMPORT pi ;


(*
   Assert - 
*)

PROCEDURE Assert (b: BOOLEAN) ;
BEGIN
   IF NOT b
   THEN
      printf("error assert failed\n") ;
      HALT
   END
END Assert ;


(*
   sqr - 
*)

PROCEDURE sqr (a: REAL) : REAL ;
BEGIN
   RETURN a*a
END sqr ;


(*
   initPolar - initialises a polar coordinate, r, is the radius (magnitude)
               and, w, is the angle.
*)

PROCEDURE initPolar (r, w: REAL) : Polar ;
VAR
   p: Polar ;
BEGIN
   p.r := r ;
   p.w := w ;
   RETURN p
END initPolar ;


(*
   polarToCoord - convert a polar coordinate into a cartesian coordinate.
*)

PROCEDURE polarToCoord (p: Polar) : Coord ;
BEGIN
   RETURN initCoord (p.r * cos (p.w), p.r * sin (p.w))
END polarToCoord ;


(*
   assertEqual - 
*)

PROCEDURE assertEqual (c1, c2: Coord) ;
BEGIN
   Assert (nearZero (c1.x-c2.x) AND nearZero (c1.y-c2.y))
END assertEqual ;


(*
   coordToPolar - return a polar coordinate pair given a cartesian coordinate.
*)

PROCEDURE coordToPolar (c: Coord) : Polar ;
VAR
   r: REAL ;
   p: Polar ;
BEGIN
   r := sqrt (sqr (c.x) + sqr (c.y)) ;
   IF nearZero(r)
   THEN
      p := initPolar (0.0, 0.0)
   ELSIF (c.x>=0.0) AND (c.y>=0.0)
   THEN
      (* quadrant 1 *)
      p := initPolar (r, asin(c.y/r))
   ELSIF (c.x<0.0) AND (c.y>=0.0)
   THEN
      (* quadrant 2 *)
      p := initPolar (r, pi-asin (c.y/r))
   ELSIF (c.x<0.0) AND (c.y<0.0)
   THEN
      (* quadrant 3 *)
      p := initPolar (r, pi+asin (-c.y/r))
   ELSIF (c.x>=0.0) AND (c.y<0.0)
   THEN
      (* quadrant 4 *)
      p := initPolar (r, 2.0*pi-asin (-c.y/r))
   END ;
   assertEqual (polarToCoord (p), c) ;
   RETURN p
END coordToPolar ;


(*
   rotatePolar - return a polar coordinate after rotating it by, w, radians.
*)

PROCEDURE rotatePolar (p: Polar; w: REAL) : Polar ;
BEGIN
   p.w := p.w + w ;
   RETURN p
END rotatePolar ;


END polar.
