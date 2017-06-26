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

MODULE testpy ;

IMPORT devicePy ;

FROM Fractions IMPORT initFract, zero, half, one, cardinal ;
FROM devicePy IMPORT green, red, blue ;
FROM Points IMPORT Point, initPoint ;

VAR
   p: ARRAY [0..3] OF Point ;
BEGIN
   devicePy.configDevice(initPoint(one(), one()), initPoint(cardinal(1024), cardinal(1024)), 1) ;
   devicePy.glyphCircle(initPoint(half(), half()), TRUE, zero(), initFract(0, 1, 50), green()) ;
   p[0] := initPoint(zero(), zero()) ;
   p[1] := initPoint(half(), zero()) ;
   p[2] := initPoint(half(), initFract(0, 1, 5)) ;
   p[3] := initPoint(zero(), initFract(0, 1, 5)) ;
   devicePy.glyphPolygon(4, p, TRUE, zero(), red()) ;
   devicePy.flipBuffer
END testpy.
