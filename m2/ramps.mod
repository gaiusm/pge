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

MODULE ramps ;


IMPORT popWorld ;
IMPORT twoDsim ;

FROM deviceIf IMPORT Colour, red, blue, green, yellow, purple, defineColour ;
FROM Fractions IMPORT Fract, initFract, zero, one, two, cardinal, negate, div, pi ;
FROM Points IMPORT Point, initPoint ;

FROM macroObjects IMPORT Macro, circle, moveTo, up, down, left, right, rotate,
                         append, translate, rootMacro, dup, unRootMacro, initMacro, rectangle,
                         triangle ;


CONST
   testCorner = FALSE ;
   testRight  = FALSE ;


(*
   placeBoundary - 
*)

PROCEDURE placeBoundary (m: Macro) ;
BEGIN
   (* left edge *)
   m := moveTo(m, initPoint(zero(), zero())) ;
   m := rectangle(m, TRUE, zero(), red(), initFract(0, 1, 100), one()) ;

   (* right edge *)
   m := moveTo(m, initPoint(initFract(0, 99, 100), zero())) ;
   m := rectangle(m, TRUE, zero(), red(), initFract(0, 1, 100), one()) ;

   (* bot edge *)
   m := moveTo(m, initPoint(zero(), zero())) ;
   m := rectangle(m, TRUE, zero(), red(), one(), initFract(0, 1, 100)) ;

   (* top edge *)
   m := moveTo(m, initPoint(zero(), initFract(0, 99, 100))) ;
   m := rectangle(m, TRUE, zero(), red(), one(), initFract(0, 1, 100)) ;
END placeBoundary ;


(*
   placeRamps - 
*)

PROCEDURE placeRamps ;
VAR
   m, n, p: Macro ;
BEGIN
   m := initMacro() ;
   n := initMacro() ;

   m := moveTo(m, initPoint(initFract(0, 3, 10), initFract(0, 6, 10))) ;

   m := triangle(m, TRUE, zero(), light,
                 initPoint(initFract(0, 7, 10), zero()),
                 initPoint(zero(), initFract(0, 1, 10))) ;

   m := moveTo(m, initPoint(initFract(0, 7, 10), initFract(0, 3, 10))) ;
   m := triangle(m, TRUE, zero(), light,
                 initPoint(negate(initFract(0, 7, 10)), zero()),
                 initPoint(zero(), initFract(0, 1, 10))) ;


(*
   n := rectangle(n, TRUE, zero(), light, initFract(0, 8, 10), initFract(0, 1, 10)) ;
   p := dup(n) ;
   n := rotate(n, initPoint(zero(), zero()), div(pi(), cardinal(20))) ;
   m := append(m, n) ;
   
   m := moveTo(m, initPoint(initFract(0, 1, 10), initFract(0, 2, 10))) ;
   p := rotate(p, initPoint(zero(), zero()), negate(div(pi(), cardinal(20)))) ;
   m := append(m, p) ;
*)

   placeBoundary(m) ;

   m := rootMacro(m) ;
   popWorld.populate(m, TRUE, TRUE)
END placeRamps ;


(*
   dropBall - 
*)

PROCEDURE dropBall (c: Colour) ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;

   (* drop the ball at the top of stairs with a leftwards velocity *)
   m := moveTo(m, initPoint(initFract(0, 17, 20), initFract(0, 15, 20))) ;

   m := circle(m, TRUE, zero(), c, size) ;
   m := rootMacro(m) ;
   popWorld.mass(cardinal(1)) ;
   popWorld.velocity(initPoint(zero(), zero())) ;
   popWorld.populate(m, FALSE, TRUE) ;
END dropBall ;


VAR
   size       : Fract ;
   light, dark: Colour ;
BEGIN
   popWorld.init(FALSE) ;
   light := defineColour(initFract(0, 166, 256),
                         initFract(0, 124, 256),
                         initFract(0, 54, 256)) ;
   dark := defineColour(initFract(0, 76, 256),
                        initFract(0, 47, 256),
                        zero()) ;

   size := initFract(0, 1, 21) ;
   placeRamps ;
   dropBall(green()) ;
   twoDsim.gravity(-9.81) ;
   twoDsim.simulateFor(1.0) ;
   dropBall(yellow()) ;
   twoDsim.simulateFor(1.0) ;
   dropBall(red()) ;
   twoDsim.simulateFor(1.0) ;
   dropBall(purple()) ;
   twoDsim.simulateFor(10.0)
END ramps.
