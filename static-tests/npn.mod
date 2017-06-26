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

MODULE npn ;

IMPORT macroObjects ;

FROM GC IMPORT collectAll ;
FROM macroObjects IMPORT Macro, rootMacro, unRootMacro ;
FROM deviceGroff IMPORT configDevice, red, green, blue, black ;
FROM Points IMPORT Point, initPoint ;
FROM Fractions IMPORT Fract, initFract, cardinal, mult, sub, negate, zero, one, two, pi, div, root, unroot ;
FROM delay IMPORT wait, nextFrameTime ;

IMPORT deviceGroff ;


VAR
   componentOutline,
   componentWire,
   transistorEdge,
   transistorCircle,
   transistorBase,
   unit,
   thickness       : Fract ;
   frame           : Macro ;


CONST
   fps = 1 ;


(*
   board - 
*)

PROCEDURE board ;
VAR
   m,
   g, r  : Macro ;
   i, j  : CARDINAL ;
   light : BOOLEAN ;
BEGIN
   m := macroObjects.initMacro() ;
   g := macroObjects.initMacro() ;
   g := macroObjects.rectangle(g, TRUE, zero(), green(), unitf(1, 0, 0), unitf(1, 0, 0)) ;   (* 1x1 box *)

   r := macroObjects.initMacro() ;
   r := macroObjects.rectangle(r, TRUE, zero(), red(), unitf(1, 0, 0), unitf(1, 0, 0)) ;   (* 1x1 box *)

   light := TRUE ;
   FOR j := 1 TO 8 DO
      FOR i := 1 TO 8 DO
         m := macroObjects.right(m, unitf(1, 0, 0)) ;
         IF light
         THEN
            m := macroObjects.append(m, g)
         ELSE
            m := macroObjects.append(m, r)
         END ;
         light := NOT light
      END ;
      light := NOT light ;
      m := macroObjects.up(m, unitf(1, 0, 0)) ;
      m := macroObjects.left(m, unitf(8, 0, 0))
   END
END board ;


(*
   origin - returns (0, 0)
*)

PROCEDURE origin () : Point ;
BEGIN
   RETURN initPoint(unitf(0, 0, 0), unitf(0, 0, 0))
END origin ;


(*
   rotatingBox - 
*)

PROCEDURE rotatingBox ;
VAR
   m, n: Macro ;
   i   : CARDINAL ;
BEGIN
   m := macroObjects.initMacro() ;

   m := macroObjects.rectangle(m, TRUE, zero(), blue(), unitf(1, 0, 0), unitf(1, 0, 0)) ;
   m := macroObjects.right(m, unitf(1, 0, 0)) ;

   m := macroObjects.rectangle(m, TRUE, zero(), red(), unitf(1, 0, 0), unitf(1, 0, 0)) ;
   m := macroObjects.up(m, unitf(1, 0, 0)) ;
   m := macroObjects.rectangle(m, TRUE, zero(), green(), unitf(1, 0, 0), unitf(1, 0, 0)) ;
   m := macroObjects.left(m, unitf(1, 0, 0)) ;
   m := macroObjects.rectangle(m, TRUE, zero(), black(), unitf(1, 0, 0), unitf(1, 0, 0)) ;

   m := macroObjects.moveTo(m, initPoint(unitf(3, 0, 0), unitf(3, 0, 0))) ;
   m := macroObjects.circle(m, FALSE, transistorCircle, red(), unitf(1, 0, 0)) ;

   FOR i := 0 TO 8 DO
      toFrame(m) ;
      m := macroObjects.rotate(unRootMacro(m), initPoint(unitf(2, 0, 0), unitf(2, 0, 0)), div(pi(), two())) ;

      m := rootMacro(m) ;
      collectAll
   END

END rotatingBox ;


(*
   toFrame - 
*)

PROCEDURE toFrame (m: Macro) ;
VAR
   n: Macro ;
BEGIN
   n := macroObjects.dup(m) ;
   n := macroObjects.moveTo(n, origin()) ;
   n := macroObjects.append(n, frame) ;
   macroObjects.runCallBacks(n, deviceGroff.glyphPolygon, deviceGroff.glyphCircle) ;
   deviceGroff.flipBuffer ;
   (* collectAll *)
END toFrame ;


(*
   movingBox - 
*)

PROCEDURE movingBox ;
VAR
   m: Macro ;
   i: CARDINAL ;
BEGIN
   m := macroObjects.initMacro() ;

   m := macroObjects.rectangle(m, TRUE, zero(), blue(), unitf(1, 0, 0), unitf(1, 0, 0)) ;
   m := macroObjects.right(m, unitf(1, 0, 0)) ;
   m := macroObjects.rectangle(m, TRUE, zero(), red(), unitf(1, 0, 0), unitf(1, 0, 0)) ;
   m := macroObjects.up(m, unitf(1, 0, 0)) ;
   m := macroObjects.rectangle(m, TRUE, zero(), green(), unitf(1, 0, 0), unitf(1, 0, 0)) ;
   m := macroObjects.left(m, unitf(1, 0, 0)) ;
   m := macroObjects.rectangle(m, TRUE, zero(), black(), unitf(1, 0, 0), unitf(1, 0, 0)) ;

   FOR i := 0 TO 3 DO
      toFrame(m) ;
      m := macroObjects.translate(m, initPoint(unitf(0, 0, 0), unitf(1, 0, 0)))
   END ;
   FOR i := 0 TO 3 DO
      toFrame(m) ;
      m := macroObjects.translate(m, initPoint(unitf(1, 0, 0), unitf(0, 0, 0)))
   END ;
   FOR i := 0 TO 3 DO
      toFrame(m) ;
      m := macroObjects.translate(m, initPoint(unitf(0, 0, 0), negate(unitf(1, 0, 0))))
   END ;
   FOR i := 0 TO 3 DO
      toFrame(m) ;
      m := macroObjects.translate(m, initPoint(negate(unitf(1, 0, 0)), unitf(0, 0, 0)))
   END

END movingBox ;


PROCEDURE transistorNPN () : Macro ;
VAR
   m, n  : Macro ;
   height,
   width : Fract ;
BEGIN
   m := macroObjects.initMacro() ;

   width := unitf(0, 1, 4) ;
   height := unitf(1, 0, 0) ;

   (* m := macroObjects.up(m, unitf(1, 0, 0)) ; *)

   (* base *)
   m := macroObjects.right(m, unitf(1, 1, 4)) ;
   m := macroObjects.rectangle(m, TRUE, zero(), red(), width, height) ;

   (* collector foot *)
   m := macroObjects.left(m, mult(initFract(0, 3, 4), width)) ;
   m := macroObjects.right(m, unitf(1, 0, 0)) ;
   m := macroObjects.up(m, unitf(0, 1, 2)) ;
   m := macroObjects.rectangle(m, TRUE, zero(), green(), transistorEdge, mult(width, two())) ;

   (* emitter foot *)
   m := macroObjects.down(m, unitf(2, 0, 0)) ;
   m := macroObjects.up(m, sub(unitf(1, 0, 0), mult(width, two()))) ;
   m := macroObjects.rectangle(m, TRUE, zero(), blue(), transistorEdge, mult(width, two())) ;

   (* transistor circle *)
   (* m := macroObjects.left(m, unitf(1, 0, 0)) ; *)
   m := macroObjects.left(m, mult(width, initFract(0, 4, 3))) ;
   m := macroObjects.up(m, unitf(0, 2, 2)) ;
   m := macroObjects.circle(m, FALSE, transistorCircle, red(), unitf(1, 2, 3)) ;


   m := macroObjects.moveTo(m, initPoint(unitf(1, 2, 4), unitf(0, 0, 0))) ;
   m := macroObjects.angledRect(m, TRUE, zero(), black(),
                                initPoint(mult(width, two()), unitf(0, 1, 2)),
                                initPoint(zero(), unitf(0, 1, 2))) ;

   (* end of test *)
(*
   width := unroot(width) ;
   height := unroot(height) ;
*)
   
   RETURN m
END transistorNPN ;


(*
   testNPN - 
*)

PROCEDURE testNPN ;
VAR
   m, n: Macro ;
   i   : CARDINAL ;
BEGIN
   m := transistorNPN() ;
   m := rootMacro(m) ;
   toFrame(m) ;
   collectAll ;
   FOR i := 0 TO 8 DO
      m := macroObjects.rotate(unRootMacro(m), initPoint(unitf(1, 0, 0), unitf(1, 0, 0)), div(pi(), two())) ;

      m := rootMacro(m) ;
      toFrame(m) ;
      collectAll 
   END
END testNPN ;


(*
   unitf - return a unit fraction of value, w + n/d.
*)

PROCEDURE unitf (w, n, d: LONGCARD) : Fract ;
BEGIN
   RETURN mult(initFract(w, n, d), unit)
END unitf ;


(*
   init - 
*)

PROCEDURE init ;
BEGIN
   unit             := root(initFract(0, 25, 100)) ;    (* .25i *)
   transistorBase   := root(unitf(0, 4*4, 100)) ;       (* .04i *)
   transistorEdge   := root(unitf(0, 3*4, 100)) ;       (* 3/100  .03i *)
   transistorCircle := root(unitf(0, 2*4, 100)) ;       (* 2/100  .02i *)
   componentOutline := root(unitf(0, 17*4, 100)) ;      (* 17/100 *)
   componentWire    := root(unitf(0, 15*4, 100)) ;      (* 15/100 *)
   thickness        := root(unitf(0,  1*4, 100)) ;      (* 1/100i *)
   configDevice(initPoint(cardinal(5), cardinal(5)), initPoint(cardinal(5), cardinal(5)), 1,
                FALSE, FALSE, TRUE, TRUE) ;
   frame := macroObjects.initMacro() ;
   frame := macroObjects.rectangle(frame, FALSE, thickness, black(), unitf(20, 0, 0), unitf(20, 0, 0)) ;
   frame := rootMacro(frame)
END init ;


BEGIN
   init ;
   testNPN
END npn.
