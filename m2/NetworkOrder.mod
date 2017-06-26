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

IMPLEMENTATION MODULE NetworkOrder ;

FROM SYSTEM IMPORT ADR, LOC ;
FROM network IMPORT htons, htonl ;
IMPORT RawIO ;

FROM Fractions IMPORT Fract, getFract, isZero, isOne, putReal ;
FROM Points IMPORT Point ;
FROM libc IMPORT printf ;


CONST
   debugging = FALSE ;


(*
   writeReal -
*)

PROCEDURE writeReal (file: ChanId; r: REAL) ;
BEGIN
   IF debugging
   THEN
      printf ("about to write real %g\n", r)
   END ;
   RawIO.Write (file, r)
END writeReal ;


(*
   writeCard -
*)

PROCEDURE writeCard (file: ChanId; c: CARDINAL) ;
BEGIN
   c := htonl (c) ;
   RawIO.Write (file, c)
END writeCard ;


(*
   get2x32 -
*)

PROCEDURE get2x32 (l: ARRAY OF LOC; VAR lo, hi: ARRAY OF LOC) ;
VAR
   i: CARDINAL ;
BEGIN
   IF HIGH (l) = HIGH (lo) + HIGH (hi)
   THEN
      i := 0 ;
      WHILE i < HIGH (lo) DO
         lo[i] := l[i] ;
         INC (i)
      END ;
      WHILE i < HIGH (l) DO
         hi[i-HIGH (lo)] := l[i] ;
         INC (i)
      END
   ELSE
      HALT
   END
END get2x32 ;


(*
   set2x32 -
*)

PROCEDURE set2x32 (l: ARRAY OF LOC; lo, hi: ARRAY OF LOC) ;
VAR
   i: CARDINAL ;
BEGIN
   IF HIGH (l) = HIGH (lo) + HIGH (hi)
   THEN
      i := 0 ;
      WHILE i < HIGH (lo) DO
         l[i] := lo[i] ;
         INC (i)
      END ;
      WHILE i < HIGH (l) DO
         l[i] := hi[i-HIGH (lo)] ;
         INC (i)
      END
   ELSE
      HALT
   END
END set2x32 ;


(*
   htonl64 - implements a 64 bit long unsigned network order transformation.
*)

PROCEDURE htonl64 (l: LONGCARD) : LONGCARD ;
VAR
   s     : SHORTCARD ;
   lo, hi: CARDINAL ;
BEGIN
   s := 1 ;
   IF s = htons (s)
   THEN
      (* no change necessary, therefore write out in byte order.  *)
      RETURN l
   END ;
   get2x32 (l, lo, hi) ;
   lo := htonl (lo) ;
   hi := htonl (hi) ;
   set2x32 (l, hi, lo) ;
   RETURN l
END htonl64 ;


(*
   writeLongCard -
*)
(*
PROCEDURE writeLongCard (file: ChanId; l: LONGCARD) ;
BEGIN
   l := htonl64 (l) ;
   RawIO.Write (file, l)
END writeLongCard ;
*)

PROCEDURE writeLongCard (file: ChanId; l: LONGCARD) ;
VAR
   p     : POINTER TO ARRAY [0..1] OF CARDINAL ;
   lo, hi: CARDINAL ;
BEGIN
   p := ADR (l) ;
   lo := p^[0] ;   (* --fixme-- unsafe as it only works on little endian microprocessors *)
   hi := p^[1] ;
   writeCard (file, hi) ;
   writeCard (file, lo)
END writeLongCard ;


(*
   writeFract -
*)

PROCEDURE writeFract (file: ChanId; f: Fract) ;
VAR
   w, n, d: LONGCARD ;
   l      : LOC ;
BEGIN
   IF isZero (f)
   THEN
      l := LOC (0) ;
      RawIO.Write (file, l)
   ELSIF isOne (f)
   THEN
      l := LOC (1) ;
      RawIO.Write (file, l)
   ELSE
      getFract (f, w, n, d) ;
      IF w=0
      THEN
         l := LOC (2) ;
         RawIO.Write (file, l) ;
         writeLongCard (file, n) ;
         writeLongCard (file, d)
      ELSE
         l := LOC (3) ;
         RawIO.Write (file, l) ;
         writeLongCard (file, w) ;
         writeLongCard (file, n) ;
         writeLongCard (file, d)
      END
   END
END writeFract ;


(*
   writeShort -
*)

PROCEDURE writeShort (file: ChanId; s: SHORTCARD) ;
BEGIN
   s := htons (s) ;
   RawIO.Write (file, s)
END writeShort ;


(*
   writeCoord -
*)

PROCEDURE writeCoord (file: ChanId; c: Coord) ;
BEGIN
   writeReal (file, c.x) ;
   writeReal (file, c.y)
END writeCoord ;


(*
   writePoint -
*)

PROCEDURE writePoint (file: ChanId; p: Point) ;
BEGIN
   writeFract (file, p.x) ;
   writeFract (file, p.y)
END writePoint ;


(*
   writePoint -
*)

PROCEDURE writePoint (file: ChanId; p: Point) ;
BEGIN
   writeFract (file, p.x) ;
   writeFract (file, p.y)
END writePoint ;


END NetworkOrder.
