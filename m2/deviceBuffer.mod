(* Copyright (C) 2015 Free Software Foundation, Inc. *)
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

IMPLEMENTATION MODULE deviceBuffer ;


FROM libc IMPORT system, printf ;
FROM SYSTEM IMPORT ADR, ADDRESS, TSIZE ;
FROM FormatStrings IMPORT Sprintf1, Sprintf2, Sprintf3 ;
FROM DynamicStrings IMPORT String, InitString, KillString, CopyOut, Mark, string ;
FROM SeqFile IMPORT write, text, read, raw, ChanId, FlagSet ;
FROM ChanConsts IMPORT OpenResults ;
FROM ClientSocket IMPORT OpenSocket, Close ;
FROM TextIO IMPORT WriteString, WriteLn ;
FROM RealIO IMPORT WriteFixed ;
IMPORT Indexing ;
FROM Points IMPORT Point, unRootPoint, dupPoint, initPoint, subPoint, addPoint, markPoint ;
FROM Fractions IMPORT Fract, initFract, unroot, negate, dup, mult, sub, inc, areEqual, getReal, isNegative, getFract, mark, cardinal, two, one, zero, isZero, root, isGreater, isLess, add, div ;
FROM Storage IMPORT ALLOCATE ;
FROM StringConvert IMPORT LongCardinalToString ;
FROM GC IMPORT garbage, entity, rootAllocate, markEntity, initGarbage, getData ;
FROM delay IMPORT wait, nextFrameTime ;
FROM Assertion IMPORT Assert ;
FROM rpc IMPORT cc, initcc, rpcStatus ;

IMPORT Fractions ;
IMPORT rpc ;


CONST
   Debugging = FALSE ;
   Height    = 5 ;
   Width     = Height ;
   Header    = 1 ;
   Margin    = 1 ;
   MaxName   = 20 ;
   maxPoints = 10 ;

TYPE
   typeOfGlyph = (circle, polygon) ;

   clipCode = SET OF (leftEdge, rightEdge, topEdge, botEdge) ;

   colourDesc = POINTER TO RECORD
                              r, g, b   : Fract ;
                              registered: BOOLEAN ;
                              id        : CARDINAL ;
                           END ;

   circleDesc = RECORD
                   center   : Point ;
                   filled   : BOOLEAN ;
                   thickness: Fract ;
                   radius   : Fract ;
                   colour   : colourDesc ;
                END ;

   polygonDesc = RECORD
                    filled   : BOOLEAN ;
                    thickness: Fract ;
                    noPoints : CARDINAL ;
                    pArray   : ARRAY [0..maxPoints] OF Point ;
                    colour   : colourDesc ;
                 END ;

   glyphDesc = POINTER TO RECORD
                             CASE type: typeOfGlyph OF

                             circle :  gCircle :  circleDesc |
                             polygon:  gPolygon:  polygonDesc

                             END ;
                             next: glyphDesc ;
                          END ;

   configDesc = POINTER TO RECORD
                              centity      : entity ;
                              inMax, outMax: Point ;
                              same         : BOOLEAN ;
                              buffer       : ADDRESS ;
                              length       : CARDINAL ;
                           END ;

   gProcedure = PROCEDURE (glyphDesc) ;


VAR
   frameNo      : CARDINAL ;
   file         : ChanId ;
   cArray       : Indexing.Index ;
   cNum         : CARDINAL ;
   config       : configDesc ;
   gHead, gFree : glyphDesc ;
   cPurple,
   cYellow,
   cWhite,
   cBlack,
   cRed,
   cGreen,
   cBlue        : Colour ;
   configHeap   : garbage ;


(*
   flushGlyphs - draw each glyph in list, gHead, and
                 then kill each glyph.
*)

PROCEDURE flushGlyphs ;
VAR
   f, g: glyphDesc ;
BEGIN
   g := gHead ;
   WHILE g#NIL DO
      drawGlyph(g) ;
      f := g ;
      g := g^.next ;
      killGlyph(f)
   END ;
   gHead := NIL
END flushGlyphs ;


(*
   empty - returns TRUE if the gHead list is empty.
*)

PROCEDURE empty () : BOOLEAN ;
BEGIN
   RETURN gHead = NIL
END empty ;


(*
   addToEnd - adds, g, to the end of, gHead.
*)

PROCEDURE addToEnd (g: glyphDesc) ;
VAR
   f: glyphDesc ;
BEGIN
   IF gHead=NIL
   THEN
      gHead := g
   ELSE
      f := gHead ;
      WHILE f^.next#NIL DO
         f := f^.next
      END ;
      f^.next := g
   END
END addToEnd ;


(*
   newGlyph - returns a new glyphDesc.  It initialises next to NIL.
*)

PROCEDURE newGlyph () : glyphDesc ;
VAR
   g: glyphDesc ;
BEGIN
   IF gFree=NIL
   THEN
      NEW(g)
   ELSE
      g := gFree ;
      gFree := gFree^.next
   END ;
   g^.next := NIL ;
   RETURN g
END newGlyph ;


(*
   disposeGlyph - returns, g, to the free list.
*)

PROCEDURE disposeGlyph (VAR g: glyphDesc) ;
BEGIN
   g^.next := gFree ;
   gFree := g
END disposeGlyph ;


(*
   killGlyph - releases any resource held by, g, and disposes of, g.
*)

PROCEDURE killGlyph (VAR g: glyphDesc) ;
BEGIN
   WITH g^ DO
      CASE type OF

      circle :  killCircle(g) |
      polygon:  killPolygon(g)

      END
   END ;
   disposeGlyph(g)
END killGlyph ;


(*
   killCircle - returns any Fracts held by circle to the free list.
                We leave colour alone.
*)

PROCEDURE killCircle (g: glyphDesc) ;
BEGIN
   WITH g^ DO
      IF type=circle
      THEN
         WITH gCircle DO
            center := unRootPoint(center) ;
            thickness := unroot(thickness) ;
            radius := unroot(radius)
         END
      ELSE
         HALT
      END
   END
END killCircle ;


(*
   killPolygon - returns any Fracts held by polygon to the free list.
                 We leave colour alone.
*)

PROCEDURE killPolygon (g: glyphDesc) ;
VAR
   i: CARDINAL ;
BEGIN
   WITH g^ DO
      IF type=polygon
      THEN
         WITH gPolygon DO
            thickness := unroot(thickness) ;
            FOR i := 0 TO noPoints-1 DO
               pArray[i] := unRootPoint(pArray[i])
            END
         END
      ELSE
         HALT
      END
   END
END killPolygon ;


(*
   foreachGlyphDo - foreach glyph do, p(g).
*)

PROCEDURE foreachGlyphDo (p: gProcedure) ;
VAR
   g: glyphDesc ;
BEGIN
   g := gHead ;
   WHILE g#NIL DO
      p(g) ;
      g := g^.next
   END
END foreachGlyphDo ;


(*
   defineColour - defines a colour by: r, g, b.  The fracts
                  are given to the colour and a colour index
                  is returned.  Colours live for ever and are
                  never freed.  The values, r, g, b, are dup'ed
                  and root'ed.
*)

PROCEDURE defineColour (r, g, b: Fract) : CARDINAL ;
VAR
   c: colourDesc ;
BEGIN
   NEW(c) ;
   INC(cNum) ;
   c^.r := root(dup(r)) ;
   c^.g := root(dup(g)) ;
   c^.b := root(dup(b)) ;
   c^.registered := FALSE ;
   Indexing.PutIndice(cArray, cNum, c) ;
   RETURN cNum
END defineColour ;


(*
   newFrame - creates a new frame.
*)

PROCEDURE newFrame ;
VAR
   res: OpenResults ;
   r  : INTEGER ;
BEGIN
   INC(frameNo) ;
   IF frameNo=1
   THEN
      REPEAT
         OpenSocket(file, 'localhost', 6000, read+write+raw+text, res) ;
         IF res#opened
         THEN
            printf("unable to connect to localhost:6000\n") ;
            r := system(ADR("sleep 1"))
         END
      UNTIL res=opened ;
      IF rpc.resolution(file, initcc(towhole(config^.outMax.x), towhole(config^.outMax.y)))#ready
      THEN

      END
   END ;
   IF frameNo=341
   THEN
      stop
   END ;
   foreachGlyphDo(registerColour)
END newFrame ;


(*
   regColour - register colour, c, with pygame.
*)

PROCEDURE regColour (c: colourDesc) ;
VAR
   x, y, z, n, d: LONGCARD ;
BEGIN
   WITH c^ DO
      IF NOT registered
      THEN
         getFract(mult(r, cardinal(255)), x, n, d) ;
         getFract(mult(g, cardinal(255)), y, n, d) ;
         getFract(mult(b, cardinal(255)), z, n, d) ;
         IF rpc.colour(file, VAL(CARDINAL, x), VAL(CARDINAL, y), VAL(CARDINAL, z), id)=ready
         THEN
            registered := TRUE
         END
      END
   END
END regColour ;


(*
   registerColour - registers the colour in, g, with PyGame.
*)

PROCEDURE registerColour (g: glyphDesc) ;
BEGIN
   WITH g^ DO
      CASE type OF

      circle :  regColour(gCircle.colour) |
      polygon:  regColour(gPolygon.colour)

      END
   END
END registerColour ;


(*
   flipBuffer - renders the current buffer and then sets up a new buffer to be
                populated by new glyphs.
*)

PROCEDURE flipBuffer ;
BEGIN
   IF NOT empty()
   THEN
      newFrame ;
      flushGlyphs ;
      IF rpc.flipbuffer(file)#ready
      THEN

      END
   END
END flipBuffer ;


(*
   drawGlyph - draws glyph, g.
*)

PROCEDURE drawGlyph (g: glyphDesc) ;
BEGIN
   WITH g^ DO
      CASE type OF

      circle :  drawCircle(g) |
      polygon:  drawPolygon(g)

      END
   END
END drawGlyph ;


(*
   WriteLongCard - writes, c, to the output file.
*)

PROCEDURE WriteLongCard (c: LONGCARD) ;
VAR
   s: String ;
   a: ARRAY [0..20] OF CHAR ;
BEGIN
   s := LongCardinalToString(c, 0, ' ', 10, FALSE) ;
   CopyOut(a, s) ;
   s := KillString(s) ;
   WriteString(file, a)
END WriteLongCard ;


(*
   scaleX -
*)

PROCEDURE scaleX (x: Fract) : Fract ;
BEGIN
   IF config^.same
   THEN
      RETURN dup(x)
   ELSE
      RETURN Fractions.div(Fractions.mult(config^.outMax.x, x), config^.inMax.x) ;
   END
END scaleX ;


(*
   scaleY - it assumes that, y, is an absolute position on the y axis.
*)

PROCEDURE scaleY (y: Fract) : Fract ;
BEGIN
   IF config^.same
   THEN
      RETURN dup(y)
   ELSE
      RETURN Fractions.div(Fractions.mult(config^.outMax.y, y), config^.inMax.y) ;
   END
END scaleY ;


(*
   dumpFract -
*)

PROCEDURE dumpFract (f: Fract) ;
VAR
   w, n, d: LONGCARD ;
BEGIN
   IF isZero(f)
   THEN
      printf(" 0")
   ELSE
      IF isNegative(f)
      THEN
         printf(" -")
      END ;
      getFract(f, w, n, d) ;
      printf("%ld", w) ;
      IF n#0
      THEN
         printf(".%ld/%ld", n, d)
      END
   END
END dumpFract ;


(*
   dumpPoint - displays point, p.
*)

PROCEDURE dumpPoint (p: Point) ;
BEGIN
   printf(" (") ;
   dumpFract(p.x) ;
   printf(", ") ;
   dumpFract(p.y) ;
   printf(") ")
END dumpPoint ;


(*
   dumpPolygon -
*)

PROCEDURE dumpPolygon (g: glyphDesc) ;
VAR
   i: CARDINAL ;
BEGIN
   WITH g^.gPolygon DO
      IF filled
      THEN
         printf("polygon filled ")
      ELSE
         printf("polygon outlined by thickness ") ; dumpFract(thickness) ;
      END ;
      printf("in colour ") ; dumpColour(colour) ;
      FOR i := 0 TO noPoints-1 DO
         dumpPoint(pArray[i])
      END ;
      printf(" \n")
   END
END dumpPolygon ;


(*
   dumpColour -
*)

PROCEDURE dumpColour (c: colourDesc) ;
BEGIN
END dumpColour ;


(*
   dumpCircle -
*)

PROCEDURE dumpCircle (g: glyphDesc) ;
BEGIN
   WITH g^.gCircle DO
      IF filled
      THEN
         printf("circle filled ")
      ELSE
         printf("circle outlined by thickness ") ; dumpFract(thickness) ;
      END ;
      printf("in colour ") ; dumpColour(colour) ; printf(" at ") ;
      dumpPoint(center) ; printf(" radius ") ; dumpFract(radius) ; printf(" \n")
   END
END dumpCircle ;


(*
   dumpg - dumps, g, for debugging.
*)

PROCEDURE dumpg (g: glyphDesc) ;
BEGIN
   WITH g^ DO
      CASE type OF

      circle :  dumpCircle(g) |
      polygon:  dumpPolygon(g)

      END
   END
END dumpg ;


(*
   tocardx - returns a CARDINAL once it has been scaled by the device resolution.
*)

PROCEDURE tocardx (f: Fract) : CARDINAL ;
VAR
   w, n, d: LONGCARD ;
BEGIN
   getFract(scaleX(f), w, n, d) ;
   RETURN VAL(CARDINAL, w)
END tocardx ;


(*
   tocardy - returns a CARDINAL once it has been scaled by the device resolution.
*)

PROCEDURE tocardy (f: Fract) : CARDINAL ;
VAR
   w, n, d: LONGCARD ;
BEGIN
   getFract(scaleY(f), w, n, d) ;
   RETURN VAL(CARDINAL, w)
END tocardy ;


(*
   tocard -
*)

PROCEDURE tocard (f: Fract) : CARDINAL ;
VAR
   w, n, d: LONGCARD ;
BEGIN
   getFract(scaleX(f), w, n, d) ;
   RETURN VAL(CARDINAL, w)
END tocard ;


(*
   tocc - transforms a point into, cc, by scaling it appropriately.
*)

PROCEDURE tocc (p: Point) : cc ;
BEGIN
   RETURN initcc(tocardx(p.x), tocardy(p.y))
END tocc ;


(*
   towhole - returns the whole number of, f, unscaled.
*)

PROCEDURE towhole (f: Fract) : CARDINAL ;
VAR
   w, n, d: LONGCARD ;
BEGIN
   getFract(f, w, n, d) ;
   RETURN VAL(CARDINAL, w)
END towhole ;


(*
   drawCircle -
*)

PROCEDURE drawCircle (g: glyphDesc) ;
BEGIN
   WITH g^.gCircle DO
      IF rpc.circle(file, colour^.id, tocc(center), tocard(radius))#ready
      THEN
      END
   END
END drawCircle ;


(*
   glyphCircle - draw a circle at point, pos.  If fill then it is filled by colour, c,
                 otherwise it is drawn in outline with a thickness, thick, in colour, c.
                 Note that this procedure takes copies of all fractions and points.
*)

PROCEDURE glyphCircle (pos: Point; fill: BOOLEAN; thick: Fract; rad: Fract; c: Colour) ;
VAR
   g: glyphDesc ;
BEGIN
   g := newGlyph() ;
   WITH g^ DO
      type := circle ;
      WITH gCircle DO
         colour := Indexing.GetIndice(cArray, c) ;
         center := dupPoint(pos) ;
         filled := fill ;
         thickness := Fractions.dup(thick) ;
         radius := Fractions.dup(rad)
      END
   END ;
   addToEnd(g)
END glyphCircle ;


(*
   glyphLine - draw a line between:  start and end of, thick, thickness and colour, c.
*)

PROCEDURE glyphLine (start, end: Point; thick: Fract; c: Colour) ;
VAR
   p: ARRAY [0..1] OF Point ;
BEGIN
   p[0] := start ;
   p[1] := end ;
   glyphPolygon(2, p, FALSE, thick, c)
END glyphLine ;


(*
   glyphPolygon - draw a polygon from pos, with n points.
                  If fill then it is filled with colour, c, else it is drawn with
                  thickness in outline using colour, c.
                  Note that this procedure takes copies of all fractions and points.
*)

PROCEDURE glyphPolygon (n: CARDINAL; p: ARRAY OF Point; fill: BOOLEAN; thick: Fract; c: Colour) ;
VAR
   i: CARDINAL ;
   g: glyphDesc ;
BEGIN
   g := newGlyph() ;
   WITH g^ DO
      type := polygon ;
      WITH gPolygon DO
         colour := Indexing.GetIndice(cArray, c) ;
         filled := fill ;
         thickness := Fractions.dup(thick) ;
         noPoints := n ;
         IF n>maxPoints
         THEN
            HALT
         END ;
         FOR i := 0 TO n-1 DO
            pArray[i] := dupPoint(p[i])
         END
      END
   END ;
   addToEnd(g)
END glyphPolygon ;


(*
   clipped - returns the clip set for point, p.
*)

PROCEDURE clipped (p: Point) : clipCode ;
VAR
   c: clipCode ;
BEGIN
   c := clipCode{} ;
   IF isLess(p.x, zero())
   THEN
      c := clipCode{leftEdge}
   ELSIF isGreater(p.x, one())
   THEN
      c := clipCode{rightEdge}
   END ;
   IF isLess(p.y, zero())
   THEN
      c := clipCode{botEdge}
   ELSIF isGreater(p.y, one())
   THEN
      c := clipCode{topEdge}
   END ;
   RETURN c
END clipped ;


(*
   drawLine - draws line (if visibly on screen after clipping),
              p1, p2, given colour and thickness.
*)

PROCEDURE drawLine (p1, p2: Point; colour: colourDesc; thickness: Fract) ;
VAR
   o1, o2: Point ;
BEGIN
   IF clipLine(p1, p2, o1, o2)
   THEN
      IF rpc.drawLine(file, colour^.id, tocc(o1), tocc(o2), tocard(thickness))#ready
      THEN

      END
   END
END drawLine ;


(*
   clipLine - clips line: p1, p2.  It returns TRUE if any part of
              line p1, and, p2 can be placed on the screen.
              It then assigns the values o1, o2 to these coordinates.
              If FALSE is returned then o1, o2 are unassigned.
*)

PROCEDURE clipLine (p1, p2: Point; VAR o1, o2: Point) : BOOLEAN ;
VAR
   x, y     : Fract ;
   c, c1, c2: clipCode ;
BEGIN
   p1 := dupPoint(p1) ;
   p2 := dupPoint(p2) ;
   c1 := clipped(p1) ;
   c2 := clipped(p2) ;
   LOOP
      IF c1*c2 # clipCode{}
      THEN
         RETURN FALSE
      ELSIF c1+c2 = clipCode{}
      THEN
         o1 := p1 ;
         o2 := p2 ;
         RETURN TRUE
      END ;

      c := c1 ;
      IF c=clipCode{}
      THEN
         c := c2
      END ;
      IF leftEdge IN c
      THEN
         (* we cross the left edge *)
         y := mult(add(p1.y, sub(p2.y, p1.y)), div(negate(p1.x), sub(p2.x, p1.x))) ;
         x := zero() ;
      ELSIF rightEdge IN c
      THEN
         (* we cross the right edge *)
         y := mult(add(p1.y, sub(p2.y, p1.y)), div(sub(one(), p1.x), sub(p2.x, p1.x))) ;
         x := one()
      ELSIF botEdge IN c
      THEN
         (* we cross the bottom edge *)
         x := mult(add(p1.x, sub(p2.x, p1.x)), div(negate(p1.y), sub(p2.y, p1.y))) ;
         y := zero()
      ELSIF topEdge IN c
      THEN
         (* we cross the top edge *)
         x := mult(add(p1.x, sub(p2.x, p1.x)), div(sub(one(), p1.y), sub(p2.y, p1.y))) ;
         y := one()
      END ;
      IF c=c1
      THEN
         p1.x := x ;
         p1.y := y ;
         c1 := clipped(initPoint(x, y))
      ELSE
         p2.x := x ;
         p2.y := y ;
         c2 := clipped(initPoint(x, y))
      END
   END
END clipLine ;


PROCEDURE stop ; BEGIN END stop ;


(*
   drawPolygon -
*)

PROCEDURE drawPolygon (g: glyphDesc) ;
VAR
   i, j  : CARDINAL ;
   ccList: ARRAY [0..maxPoints] OF cc ;
   p,
   o1, o2: Point ;
BEGIN
   WITH g^.gPolygon DO
      IF noPoints=2
      THEN
         drawLine(pArray[0], pArray[1], colour, thickness)
      ELSE
         j := 0 ;
         p := dupPoint(pArray[0]) ;
         FOR i := 1 TO noPoints-1 DO
            IF clipLine(p, pArray[i], o1, o2)
            THEN
               ccList[j] := tocc(o1) ;
               INC(j) ;
               p := unRootPoint(p) ;
               p := dupPoint(o2)
            END
         END ;
         IF j>0
         THEN
            ccList[j] := tocc(p) ;
            INC(j) ;
            IF rpc.polygon(file, colour^.id, j, ccList)#ready
            THEN
               HALT
            END
         END
      END
   END
END drawPolygon ;


(*
   white - returns the colour, white.
*)

PROCEDURE white () : CARDINAL ;
BEGIN
   RETURN cWhite
END white ;


(*
   black - returns the colour, black.
*)

PROCEDURE black () : CARDINAL ;
BEGIN
   RETURN cBlack
END black ;


(*
   red - returns the colour, red.
*)

PROCEDURE red () : CARDINAL ;
BEGIN
   RETURN cRed
END red ;


(*
   green - returns the colour, green.
*)

PROCEDURE green () : CARDINAL ;
BEGIN
   RETURN cGreen
END green ;


(*
   blue - returns the colour, blue.
*)

PROCEDURE blue () : CARDINAL ;
BEGIN
   RETURN cBlue
END blue ;


(*
   yellow - returns the colour, yellow.
*)

PROCEDURE yellow () : CARDINAL ;
BEGIN
   RETURN cYellow
END yellow ;


(*
   purple - returns the colour, purple.
*)

PROCEDURE purple () : CARDINAL ;
BEGIN
   RETURN cPurple
END purple ;


(*
   configDevice - configure the output device to have outMax resolution and
                  a buffer.
*)

PROCEDURE configDevice (inMax, outMax: Point; buffer: ADDRESS; length: CARDINAL) ;
BEGIN
   config^.inMax := dupPoint(inMax) ;
   config^.outMax := dupPoint(outMax) ;
   config^.same := Fractions.areEqual(inMax.x, outMax.x) AND
                   Fractions.areEqual(inMax.y, outMax.y) ;
   config^.buffer := buffer ;
   config^.length := length
END configDevice ;


(*
   markConfig -
*)

PROCEDURE markConfig (e: entity) ;
VAR
   c: configDesc ;
BEGIN
   c := getData(e) ;
   IF c=config
   THEN
      WITH config^ DO
         markEntity(centity) ;
         markPoint(inMax) ;
         markPoint(outMax)
      END
   ELSE
      HALT
   END
END markConfig ;


(*
   Init -
*)

PROCEDURE Init ;
VAR
   e     : entity ;
   buffer: ADDRESS ;
   length: CARDINAL ;
BEGIN
   frameNo := 0 ;
   cNum := 0 ;
   cArray := Indexing.InitIndex(1) ;
   gHead := NIL ;
   gFree := NIL ;
   cBlack := defineColour(zero(), zero(), zero()) ;
   cWhite := defineColour(one(), one(), one()) ;
   cRed := defineColour(initFract(0, 65, 100), initFract(0, 1, 10), initFract(0, 2, 10)) ;
   cGreen := defineColour(initFract(0, 1, 10), initFract(0, 4, 10), initFract(0, 2, 10)) ;
   cBlue := defineColour(initFract(0, 1, 10), initFract(0, 2, 10), initFract(0, 6, 10)) ;
   cYellow := defineColour(initFract(1, 0, 0), initFract(0, 66, 100), initFract(0, 7, 100)) ;
   cPurple := defineColour(initFract(0, 79, 255), initFract(0, 47, 255), initFract(0, 70, 255)) ;

   configHeap := initGarbage(markConfig, TSIZE(config^), InitString('config')) ;
   rootAllocate(configHeap, e, config) ;
   config^.centity := e ;

   length := 4096 ;
   ALLOCATE(buffer, length) ;

   configDevice(initPoint(one(), one()), initPoint(cardinal(Width), cardinal(Height)), buffer, length)
END Init ;


END deviceBuffer.
