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

MODULE para ;


IMPORT popWorld ;
IMPORT twoDsim ;

FROM deviceGroff IMPORT Colour, red, blue, green ;
FROM Fractions IMPORT Fract, initFract, zero, one, two, cardinal, negate ;
FROM Points IMPORT Point, initPoint ;

FROM macroObjects IMPORT Macro, circle, moveTo, up, down, left, right,
                         append, translate, rootMacro, dup, unRootMacro, initMacro, rectangle,
                         triangle ;


CONST
   testCorner = FALSE ;
   testRight  = FALSE ;


(*
   placeWall - 
*)

PROCEDURE placeWall ;
VAR
   m: Macro ;
   i: CARDINAL ;
BEGIN
   m := initMacro() ;

   m := moveTo(m, initPoint(zero(), zero())) ;
   m := rectangle(m, TRUE, zero(), red(), initFract(0, 1, 10), one()) ;

   m := rootMacro(m) ;
   popWorld.populate(m, TRUE, TRUE)
END placeWall ;


(*
   dropBall - 
*)

PROCEDURE dropBall ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;

   m := moveTo(m, initPoint(initFract(0, 7, 20), initFract(0, 7, 20))) ;

   m := circle(m, TRUE, zero(), green(), size) ;
   m := rootMacro(m) ;
   popWorld.mass(cardinal(1)) ;
   popWorld.velocity(initPoint(negate(cardinal(3)), cardinal(6))) ;
   popWorld.populate(m, FALSE, TRUE) ;
END dropBall ;


VAR
   size: Fract ;
BEGIN
   popWorld.init(FALSE) ;
   size := initFract(0, 1, 21) ;
   placeWall ;
   dropBall ;
   twoDsim.gravity(-9.81) ;
   twoDsim.simulateFor(0.25)
END para.
