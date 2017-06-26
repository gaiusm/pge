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

IMPLEMENTATION MODULE rpc ;

FROM SYSTEM IMPORT BYTE ;
FROM RawIO IMPORT Write, Read ;
FROM libc IMPORT printf ;


(*
   writeString - writes a string to the socket, file.
*)

PROCEDURE writeString (file: ChanId; a: ARRAY OF CHAR; VAR res: rpcStatus) ;
VAR
   i, n: CARDINAL ;
BEGIN
   i := 0 ;
   n := HIGH (a) ;
   WHILE (i<=n) AND (res=ready) DO
      Write (file, a[i]) ;
      INC (i)
   END
END writeString ;


(*
   writeCardinal - writes a cardinal to the socket, file.
*)

PROCEDURE writeCardinal (file: ChanId; c: CARDINAL; VAR res: rpcStatus) ;
BEGIN
   IF res=ready
   THEN
      Write (file, c)
   END
END writeCardinal ;


(*
   writeByte - writes the lowest single byte of cardinal, c.
*)

PROCEDURE writeByte (file: ChanId; c: CARDINAL; VAR res: rpcStatus) ;
VAR
   b: BYTE ;
BEGIN
   IF res=ready
   THEN
      b := VAL (BYTE, c MOD 0100H) ;
      Write (file, b)
   END
END writeByte ;


(*
   readCardinal - reads a cardinal from, file.
*)

PROCEDURE readCardinal (file: ChanId; VAR res: rpcStatus) : CARDINAL ;
VAR
   cid: CARDINAL ;
BEGIN
   cid := 0 ;
   IF res=ready
   THEN
      Read (file, cid)
   END ;
   RETURN cid
END readCardinal ;


(*
   colour - registers a colour with pygame and cid is assigned with the python colour, id.
*)

PROCEDURE colour (file: ChanId; r, g, b: CARDINAL; VAR cid: CARDINAL) : rpcStatus ;
VAR
   res: rpcStatus ;
BEGIN
   res := ready ;
   writeString (file, 'o', res) ;
   writeByte (file, r, res) ;
   writeByte (file, g, res) ;
   writeByte (file, b, res) ;
   cid := readCardinal (file, res) ;
   (* printf("colour id returned, %d\n", cid) ; *)
   RETURN res
END colour ;


(*
   polygon - writes a filled polygon to the pygame display.
             Polygon to be filled with colour, cid.
*)

PROCEDURE polygon (file: ChanId; cid: CARDINAL; n: CARDINAL; p: ARRAY OF cc) : rpcStatus ;
VAR
   i: CARDINAL ;
   res: rpcStatus ;
BEGIN
   res := ready ;
   writeString (file, 'P', res) ;
   writeCardinal (file, cid, res) ;
   writeCardinal (file, n, res) ;
   i := 0 ;
   WHILE i<n DO
      writeCardinal (file, p[i].x, res) ;
      writeCardinal (file, p[i].y, res) ;
      INC(i)
   END ;
   RETURN res
END polygon ;


(*
   circle - writes a filled circle to the pygame display.
            Circle to be filled with colour, cid.
*)

PROCEDURE circle (file: ChanId; cid: CARDINAL; center: cc; radius: CARDINAL) : rpcStatus ;
VAR
   i  : CARDINAL ;
   res: rpcStatus ;
BEGIN
   res := ready ;
   (* printf("circle\n") ; *)
   writeString (file, 'C', res) ;
   writeCardinal (file, cid, res) ;
   writeCardinal (file, center.x, res) ;
   writeCardinal (file, center.y, res) ;
   writeCardinal (file, radius, res) ;
   (* printf("done\n") ; *)
   RETURN res
END circle ;


(*
   drawLine - draw a line on the pygame screen from p1 to p2 with thickness and colour, id.
*)

PROCEDURE drawLine (file: ChanId; cid: CARDINAL; p1, p2: cc; thickness: CARDINAL) : rpcStatus ;
VAR
   res: rpcStatus ;
BEGIN
   res := ready ;
   writeString (file, 'l', res) ;
   writeCardinal (file, cid, res) ;
   writeCardinal (file, p1.x, res) ;
   writeCardinal (file, p1.y, res) ;
   writeCardinal (file, p2.x, res) ;
   writeCardinal (file, p2.y, res) ;
   RETURN res
END drawLine ;


(*
   resolution - sets the resolution of Pygame.
*)

PROCEDURE resolution (file: ChanId; res: cc) : rpcStatus ;
VAR
   ret: rpcStatus ;
BEGIN
   ret := ready ;
   writeString (file, 'r', ret) ;
   (* printf("x, y = %d, %d\n", res.x, res.y) ; *)
   writeCardinal (file, res.x, ret) ;
   writeCardinal (file, res.y, ret) ;
   RETURN ret
END resolution ;


(*
   initcc - initialises a, cc, structure.
*)

PROCEDURE initcc (x, y: CARDINAL) : cc ;
VAR
   c: cc ;
BEGIN
   c.x := x ;
   c.y := y ;
   RETURN c
END initcc ;


(*
   flipbuffer - flips the pygame frame buffer.
*)

PROCEDURE flipbuffer (file: ChanId) : rpcStatus ;
VAR
   res: rpcStatus ;
BEGIN
   res := ready ;
   writeString (file, 'f', res) ;
   RETURN res
END flipbuffer ;


END rpc.
