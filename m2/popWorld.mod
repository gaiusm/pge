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

IMPLEMENTATION MODULE popWorld ;

FROM deviceIf IMPORT Colour, useGroff, useRPC, configDevice ;
FROM macroObjects IMPORT Macro ;
FROM Fractions IMPORT Fract, getReal, cardinal, one, zero, root, unroot ;
FROM Points IMPORT Point, initPoint, rootPoint, unRootPoint ;
FROM libc IMPORT printf ;

IMPORT macroObjects ;
IMPORT twoDsim ;


CONST
   FPSgroff =  80 ;
   FPSpy    =  80 ;

VAR
   pFixed         : BOOLEAN ;
   defaultVelocity: Point ;
   defaultMass    : Fract ;
   defaultRotation: REAL ;


(*
   ppolygon - 
*)

PROCEDURE ppolygon (n: CARDINAL; p: ARRAY OF Point; fill: BOOLEAN; thick: Fract; c: Colour) ;
VAR
   o: CARDINAL ;
BEGIN
   CASE n OF

   3:  o := twoDsim.poly3 (getReal(p[0].x), getReal(p[0].y),
                           getReal(p[1].x), getReal(p[1].y), 
                           getReal(p[2].x), getReal(p[2].y), c) |
   4:  o := twoDsim.poly4 (getReal(p[0].x), getReal(p[0].y),
                           getReal(p[1].x), getReal(p[1].y), 
                           getReal(p[2].x), getReal(p[2].y),
                           getReal(p[3].x), getReal(p[3].y), c) |
   5:  o := twoDsim.poly5 (getReal(p[0].x), getReal(p[0].y),
                           getReal(p[1].x), getReal(p[1].y), 
                           getReal(p[2].x), getReal(p[2].y),
                           getReal(p[3].x), getReal(p[3].y),
                           getReal(p[4].x), getReal(p[4].y), c) |
   6:  o := twoDsim.poly6 (getReal(p[0].x), getReal(p[0].y),
                           getReal(p[1].x), getReal(p[1].y), 
                           getReal(p[2].x), getReal(p[2].y),
                           getReal(p[3].x), getReal(p[3].y),
                           getReal(p[4].x), getReal(p[4].y),
                           getReal(p[5].x), getReal(p[5].y), c)

   ELSE
      printf("too many sides to the polygon, max 6 allowed\n") ;
      HALT
   END ;
   IF pFixed
   THEN
      o := twoDsim.fix (o)
   ELSE
      o := twoDsim.mass (o, getReal(defaultMass)) ;
      o := twoDsim.velocity (o, getReal(defaultVelocity.x), getReal(defaultVelocity.y)) ;
      o := twoDsim.rotate (o, defaultRotation)
   END
END ppolygon ;


(*
   pcircle - 
*)

PROCEDURE pcircle (pos: Point; fill: BOOLEAN; thick: Fract; rad: Fract; c: Colour) ;
VAR
   o: CARDINAL ;
BEGIN
   o := twoDsim.circle (getReal (pos.x), getReal (pos.y), getReal (rad), c) ;
   IF pFixed
   THEN
      o := twoDsim.fix (o)
   ELSE
      o := twoDsim.mass (o, getReal (defaultMass)) ;
      o := twoDsim.velocity (o, getReal (defaultVelocity.x), getReal (defaultVelocity.y)) ;
      o := twoDsim.rotate (o, defaultRotation)
   END
END pcircle ;


(*
   populate - populate the 2D world with the contents of macro, m.
*)

PROCEDURE populate (m: Macro; fixed, solid: BOOLEAN) ;
BEGIN
   pFixed := fixed ;
   macroObjects.runCallBacks (m, ppolygon, pcircle)
END populate ;


(*
   mass - sets the default mass for a movable object.
*)

PROCEDURE mass (m: Fract) ;
BEGIN
   defaultMass := unroot (defaultMass) ;
   defaultMass := root (m)
END mass ;


(*
   velocity - sets the default velocity for a movable object.
*)

PROCEDURE velocity (v: Point) ;
BEGIN
   defaultVelocity := unRootPoint (defaultVelocity) ;
   defaultVelocity := rootPoint (v)
END velocity ;


(*
   rotate - sets the default angular velocity for a movable object.
*)

PROCEDURE rotate (r: Fract) ;
BEGIN
   defaultRotation := getReal (r)
END rotate ;


(*
   init - initialise the 2D world and configure the device to be groff or pygame.
*)

PROCEDURE init (groff: BOOLEAN) ;
BEGIN
   defaultMass := root (one()) ;
   defaultVelocity := rootPoint (initPoint (zero (), zero ())) ;
   IF groff
   THEN
      useGroff ;
      configDevice (initPoint (one (), one ()),
                    initPoint (cardinal (5), cardinal (5)),
                    FPSgroff) ;
      twoDsim.fps (FLOAT (FPSgroff))
   ELSE
      useRPC ;
      configDevice (initPoint (one (), one ()),
                    initPoint(cardinal (1000), cardinal (1000)),
                    FPSpy) ;
      twoDsim.fps (FLOAT (FPSpy))
   END
END init ;


END popWorld.
