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

MODULE snooker ;

IMPORT popWorld ;
IMPORT twoDsim ;

FROM deviceIf IMPORT Colour, defineColour, red, blue, green ;
FROM Fractions IMPORT Fract, initFract, zero, one, two, cardinal ;
FROM Points IMPORT Point, initPoint ;

FROM macroObjects IMPORT Macro, circle, moveTo, up, down, left, right,
                         append, translate, rootMacro, dup, unRootMacro, initMacro, rectangle ;

CONST
   useGroff = TRUE ;


(*
   placeBoundary - 
*)

PROCEDURE placeBoundary ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;

   (* left edge *)
   m := moveTo(m, initPoint(zero(), zero())) ;
   m := rectangle(m, TRUE, zero(), dark, initFract(0, 1, 100), one()) ;

   (* right edge *)
   m := moveTo(m, initPoint(initFract(0, 99, 100), zero())) ;
   m := rectangle(m, TRUE, zero(), dark, initFract(0, 1, 100), one()) ;

   (* bot edge *)
   m := moveTo(m, initPoint(zero(), zero())) ;
   m := rectangle(m, TRUE, zero(), dark, one(), initFract(0, 1, 100)) ;

   (* top edge *)
   m := moveTo(m, initPoint(zero(), initFract(0, 99, 100))) ;
   m := rectangle(m, TRUE, zero(), dark, one(), initFract(0, 1, 100)) ;
   m := rootMacro(m) ;

   popWorld.populate(m, TRUE, TRUE)

END placeBoundary ;


(*
   placeBalls - 
*)

PROCEDURE placeBalls ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;

   m := moveTo(m, initPoint(initFract(0, 3, 10), initFract(0, 8, 10))) ;
   m := circle(m, TRUE, zero(), red(), size) ;
   m := right(m, initFract(0, 1, 10)) ;
   m := circle(m, TRUE, zero(), red(), size) ;
   m := right(m, initFract(0, 1, 10)) ;
   m := circle(m, TRUE, zero(), red(), size) ;
   m := right(m, initFract(0, 1, 10)) ;
   m := circle(m, TRUE, zero(), red(), size) ;

   m := moveTo(m, initPoint(initFract(0, 7, 20), initFract(0, 7, 10))) ;
   m := circle(m, TRUE, zero(), red(), size) ;
   m := right(m, initFract(0, 1, 10)) ;
   m := circle(m, TRUE, zero(), red(), size) ;
   m := right(m, initFract(0, 1, 10)) ;
   m := circle(m, TRUE, zero(), red(), size) ;

   m := moveTo(m, initPoint(initFract(0, 4, 10), initFract(0, 6, 10))) ;
   m := circle(m, TRUE, zero(), red(), size) ;
   m := right(m, initFract(0, 1, 10)) ;
   m := circle(m, TRUE, zero(), red(), size) ;

   m := moveTo(m, initPoint(initFract(0, 9, 20), initFract(0, 5, 10))) ;
   m := circle(m, TRUE, zero(), red(), size) ;

   m := rootMacro(m) ;
   popWorld.populate(m, FALSE, TRUE)
END placeBalls ;


(*
   fireCue - 
*)

PROCEDURE fireCue ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;

   m := moveTo(m, initPoint(initFract(0, 7, 13), initFract(0, 1, 10))) ;
   m := circle(m, TRUE, zero(), green(), size) ;
   m := rootMacro(m) ;
   popWorld.mass(cardinal(3)) ;
   popWorld.velocity(initPoint(zero(), initFract(2, 0, 0))) ;
   popWorld.populate(m, FALSE, TRUE) ;
   twoDsim.simulateFor(30.0)
END fireCue ;


VAR
   size       : Fract ;
   light, dark: Colour ;
BEGIN
   popWorld.init(useGroff) ;

   light := defineColour(initFract(0, 166, 256),
                         initFract(0, 124, 256),
                         initFract(0, 54, 256)) ;
   dark := defineColour(initFract(0, 76, 256),
                        initFract(0, 47, 256),
                        zero()) ;

   size := initFract(0, 1, 21) ;
   placeBoundary ;
   placeBalls ;
   fireCue
END snooker.
