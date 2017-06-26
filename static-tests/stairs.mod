(* Copyright (C) 2012 Free Software Foundation, Inc. *)
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

MODULE stairs ;


IMPORT popWorld ;
IMPORT twoDsim ;

FROM deviceIf IMPORT Colour, red, blue, green ;
FROM Fractions IMPORT Fract, initFract, zero, one, two, cardinal, negate ;
FROM Points IMPORT Point, initPoint ;

FROM macroObjects IMPORT Macro, circle, moveTo, up, down, left, right,
                         append, translate, rootMacro, dup, unRootMacro, initMacro, rectangle ;


CONST
   testCorner = FALSE ;
   testRight  = FALSE ;


(*
   placeStairs - 
*)

PROCEDURE placeStairs ;
VAR
   m: Macro ;
   i: CARDINAL ;
BEGIN
   m := initMacro() ;
   FOR i := 0 TO 7 DO
      m := moveTo(m, initPoint(initFract(0, 2+i, 10), initFract(0, i, 10))) ;
      m := rectangle(m, TRUE, zero(), red(), initFract(0, 8-i, 10), initFract(0, 1, 10))
   END ;
   m := moveTo(m, initPoint(zero(), zero())) ;
   m := rectangle(m, TRUE, zero(), red(), initFract(0, 1, 10), one()) ;

   m := rootMacro(m) ;
   popWorld.populate(m, TRUE, TRUE)
END placeStairs ;


(*
   dropBall - 
*)

PROCEDURE dropBall ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;

   (* drop the ball at the top of stairs with a leftwards velocity *)
   m := moveTo(m, initPoint(initFract(0, 9, 10), initFract(0, 9, 10))) ;

   m := circle(m, TRUE, zero(), green(), size) ;
   m := rootMacro(m) ;
   popWorld.mass(cardinal(1)) ;
   popWorld.velocity(initPoint(negate(initFract(0, 1, 2)), zero())) ;
   popWorld.populate(m, FALSE, TRUE) ;
END dropBall ;


VAR
   size: Fract ;
BEGIN
   popWorld.init(TRUE) ;
   size := initFract(0, 1, 21) ;
   placeStairs ;
   dropBall ;
   twoDsim.gravity(-9.81) ;
   twoDsim.simulateFor(7.0)
END stairs.
