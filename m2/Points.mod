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

IMPLEMENTATION MODULE Points ;

FROM Fractions IMPORT root, unroot, dup, mark, add, sub, mult, zero, negate ;


(*
   initPoint - returns a Point from two fractions.
               The fractions are contained within the point structure.
               It does not take a copy of the fractions.
*)

PROCEDURE initPoint (x, y: Fract) : Point ;
VAR
   p: Point ;
BEGIN
   p.x := x ;
   p.y := y ;
   RETURN p
END initPoint ;


(*
   rootPoint - grafts, p, into the roots of the garbage tree.
*)

PROCEDURE rootPoint (p: Point) : Point ;
BEGIN
   p.x := root(p.x) ;
   p.y := root(p.y) ;
   RETURN p
END rootPoint ;


(*
   unRootPoint - removes, p, from the roots of the garbage tree.
*)

PROCEDURE unRootPoint (p: Point) : Point ;
BEGIN
   p.x := unroot(p.x) ;
   p.y := unroot(p.y) ;
   RETURN p
END unRootPoint ;


(*
   dupPoint - returns a duplication of, p.
*)

PROCEDURE dupPoint (p: Point) : Point ;
VAR
   p1: Point ;
BEGIN
   p1.x := dup(p.x) ;
   p1.y := dup(p.y) ;
   RETURN p1
END dupPoint ;


(*
   markPoint - marks Point, p, to be saved from garbage collection.
*)

PROCEDURE markPoint (p: Point) ;
BEGIN
   mark(p.x) ;
   mark(p.y)
END markPoint ;


(*
   addPoint - returns a new point (a+b).
*)

PROCEDURE addPoint (a, b: Point) : Point ;
VAR
   c: Point ;
BEGIN
   c.x := add(a.x, b.x) ;
   c.y := add(a.y, b.y) ;
   RETURN c
END addPoint ;


(*
   subPoint - returns a new point (a-b).
*)

PROCEDURE subPoint (a, b: Point) : Point ;
VAR
   c: Point ;
BEGIN
   c.x := sub(a.x, b.x) ;
   c.y := sub(a.y, b.y) ;
   RETURN c
END subPoint ;


(*
   scalePoint - returns a new point which is scaled by, s.
*)

PROCEDURE scalePoint (p: Point; s: Fract) : Point ;
VAR
   p1: Point ;
BEGIN
   p1.x := mult(p.x, s) ;
   p1.y := mult(p.y, s) ;
   RETURN p1
END scalePoint ;


(*
   zeroPoint - returns a new point (0, 0)
*)

PROCEDURE zeroPoint () : Point ;
BEGIN
   RETURN initPoint(zero(), zero())
END zeroPoint ;


(*
   negatePoint - negates the point, p.  The same point, p, is returned.
*)

PROCEDURE negatePoint (p: Point) : Point ;
BEGIN
   p.x := negate(p.x) ;
   p.y := negate(p.y) ;
   RETURN p
END negatePoint ;


END Points.
