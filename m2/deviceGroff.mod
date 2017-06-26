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

IMPLEMENTATION MODULE deviceGroff ;


FROM libc IMPORT system, printf ;
FROM SYSTEM IMPORT ADR, ADDRESS, TSIZE ;
FROM FormatStrings IMPORT Sprintf1, Sprintf2, Sprintf3 ;
FROM DynamicStrings IMPORT String, InitString, KillString, CopyOut, Mark, string ;
FROM SeqFile IMPORT OpenResults, OpenWrite, write, text, ChanId, Close ;
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

IMPORT Fractions ;


CONST
   Debugging = FALSE ;
   Exec      =  TRUE ;
   Height    = 5 ;
   Width     = Height ;
   Header    = 1 ;
   Margin    = 1 ;
   MaxName   = 20 ;
   maxPoints = 10 ;

TYPE
   typeOfGlyph = (circle, polygon) ;

   edges = (leftEdge, rightEdge, topEdge, botEdge) ;

   clipCode = SET OF edges ;

   colourDesc = POINTER TO RECORD
                              name   : String ;
                              r, g, b: Fract ;
                              used   : BOOLEAN ;
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
                              fps          : CARDINAL ;
                              separateFiles,
                              mpeg,
                              ps,
                              evince       : BOOLEAN ;
                           END ;

   gProcedure = PROCEDURE (glyphDesc) ;


VAR
   frameNo      : CARDINAL ;
   filename     : String ;
   file         : ChanId ;
   cArray       : Indexing.Index ;
   cNum         : CARDINAL ;
   config       : configDesc ;
   evinceRunning: BOOLEAN ;
   gHead, gFree : glyphDesc ;
   cPurple,
   cYellow,
   cWhite,
   cBlack,
   cRed,
   cGreen,
   cBlue        : Colour ;
   configHeap   : garbage ;
   firstFrame   : BOOLEAN ;


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
   makeTemporaryName -
*)

PROCEDURE makeTemporaryName (a: ARRAY OF CHAR) : String ;
VAR
   s: String ;
BEGIN
   s := Mark(InitString(a)) ;
   RETURN( Sprintf2(InitString('%s%d'), s, cNum) )
END makeTemporaryName ;


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
   c^.name := makeTemporaryName('colour') ;
   c^.r := root(dup(r)) ;
   c^.g := root(dup(g)) ;
   c^.b := root(dup(b)) ;
   c^.used := FALSE ;
   Indexing.PutIndice(cArray, cNum, c) ;
   RETURN cNum
END defineColour ;


(*
   writeColourDef - writes out the colour definition.
*)

PROCEDURE writeColourDef (c: colourDesc) ;
VAR
   a: ARRAY [0..MaxName] OF CHAR ;
   d: REAL ;
BEGIN
   WITH c^ DO
      WriteString(file, '.defcolor ') ;
      CopyOut(a, name) ;
      WriteString(file, a) ; WriteString(file, ' rgb ') ;
      d := getReal(r) ; WriteFixed(file, d, 4, 4) ; WriteString(file, 'f ') ;
      d := getReal(g) ; WriteFixed(file, d, 4, 4) ; WriteString(file, 'f ') ;
      d := getReal(b) ; WriteFixed(file, d, 4, 4) ; WriteString(file, 'f ') ;
      WriteLn(file)
   END
END writeColourDef ;


(*
   writeColour -
*)

PROCEDURE writeColour (c: colourDesc) ;
VAR
   a: ARRAY [0..MaxName] OF CHAR ;
BEGIN
   WITH c^ DO
      CopyOut(a, name) ;
      WriteString(file, a)
   END
END writeColour ;


(*
   setColourUnused -
*)

PROCEDURE setColourUnused (c: colourDesc) ;
BEGIN
   c^.used := FALSE
END setColourUnused ;


(*
   writeColourUsed -
*)

PROCEDURE writeColourUsed (c: colourDesc) ;
BEGIN
   IF c^.used
   THEN
      writeColourDef(c)
   END
END writeColourUsed ;


(*
   newFrame - creates a new frame.
*)

PROCEDURE newFrame ;
VAR
   name: ARRAY [0..MaxName] OF CHAR ;
   res : OpenResults ;
BEGIN
   IF NOT empty()
   THEN
      INC(frameNo) ;
      IF frameNo=16
      THEN
         stop
      END ;
      filename := Sprintf1(InitString('f%06d.ms'), frameNo) ;
      CopyOut(name, filename) ;
      OpenWrite(file, name, text+write, res) ;
      Indexing.ForeachIndiceInIndexDo(cArray, setColourUnused) ;
      foreachGlyphDo(setColourUsed) ;
      Indexing.ForeachIndiceInIndexDo(cArray, writeColourUsed) ;
      WriteString(file, '.ll 8i') ; WriteLn(file) ;
      WriteString(file, '.nop \&') ; WriteLn(file)
   END
END newFrame ;


(*
   setColourUsed -
*)

PROCEDURE setColourUsed (g: glyphDesc) ;
BEGIN
   WITH g^ DO
      CASE type OF

      circle :  gCircle.colour^.used := TRUE |
      polygon:  gPolygon.colour^.used := TRUE

      END
   END
END setColourUsed ;


(*
   debugSystem -
*)

PROCEDURE debugSystem (s: String) ;
VAR
   r: INTEGER ;
BEGIN
   IF Debugging
   THEN
      printf("%s\n", string(s))
   END ;
   r := system(string(s)) ;
   IF r#0
   THEN
      printf("%s  -> returned %d\n", string(s), r)
   END
END debugSystem ;


(*
   generatePNG - generate a png file, this assumes that configDesc.separateFiles is TRUE.
*)

PROCEDURE generatePNG ;
VAR
   s: String ;
BEGIN
   IF config^.separateFiles
   THEN
      s := Sprintf2(InitString('groff %s > f%06d.ps'),
                    filename, frameNo) ;
      debugSystem(s) ;
      s := KillString(s) ;
      s := Sprintf2(InitString('gs -dNOPAUSE -sDEVICE=pnmraw -sOutputFile=t%06d.pnm -dGraphicsAlphaBits=4 -q -dBATCH f%06d.ps > /dev/null 2>&1'),
                    frameNo, frameNo) ;
      debugSystem(s) ;
      s := KillString(s) ;
      s := Sprintf2(InitString('pnmcrop -quiet < t%06d.pnm | pnmtopng > e%06d.png 2> /dev/null'),
                    frameNo, frameNo) ;
      debugSystem(s) ;
      s := KillString(s) ;

      s := Sprintf2(InitString('convert e%06d.png -type truecolor f%06d.png 2> /dev/null'),
                    frameNo, frameNo) ;
      debugSystem(s) ;
      s := KillString(s) ;
      s := Sprintf3(InitString('rm t%06d.pnm f%06d.ps e%06d.png'),
                    frameNo, frameNo, frameNo) ;
      debugSystem(s) ;
      s := KillString(s) ;
      filename := KillString(filename)
   END
END generatePNG ;


(*
   generatePS - generate a PS file, which is dynamically re-read by 'evince'.
*)

PROCEDURE generatePS ;
VAR
   s: String ;
BEGIN
   s := Sprintf1(InitString('groff %s > PS'), filename) ;
   debugSystem(s) ;
   s := KillString(s) ;
   IF NOT evinceRunning
   THEN
      s := InitString('gv --watch PS &') ;
      debugSystem(s) ;
      s := KillString(s) ;
      evinceRunning := TRUE
   END
END generatePS ;


(*
   flipBuffer - renders the current buffer and then sets up a new buffer to be
                populated by new glyphs.
*)

PROCEDURE flipBuffer ;
BEGIN
(*
   IF (config^.fps#0) AND (NOT firstFrame)
   THEN
      wait
   END ;
*)
   IF NOT empty()
   THEN
      newFrame ;
      flushGlyphs ;
      Close(file) ;
      nextFrameTime(config^.fps) ;
      firstFrame := FALSE ;
      IF config^.mpeg
      THEN
         generatePNG
      END ;
      IF config^.ps
      THEN
         generatePS
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
   writeUnit - writes out, u, to the output, file.
*)

PROCEDURE writeUnit (u: Fract) ;
VAR
   w, n, d: LONGCARD ;
BEGIN
   IF isZero(u)
   THEN
      WriteString(file, '(u;0i)')
   ELSE
      IF isNegative(u)
      THEN
         WriteString(file, '-')
      END ;
      getFract(u, w, n, d) ;
      IF (d=0) OR (n=0)
      THEN
         WriteString(file, '(u;') ;
         WriteLongCard(w) ;
         WriteString(file, 'i)')
      ELSE
         WriteString(file, '(u;') ;
         WriteString(file, '(') ;
         IF w>0
         THEN
            WriteLongCard(w) ;
            WriteString(file, 'i+(') ;
            n := n MOD 10000 ;
            WriteLongCard(n) ;
            WriteString(file, 'i/') ;
            d := d MOD 10000 ;
            WriteLongCard(d) ;
            WriteString(file, ')')
         ELSE
            WriteLongCard(n) ;
            WriteString(file, 'i/') ;
            WriteLongCard(d)
         END ;
         WriteString(file, '))')
      END
   END
END writeUnit ;


(*
   scaleX -
*)

PROCEDURE scaleX (x: Fract) : Fract ;
BEGIN
   RETURN relScaleX(x)
END scaleX ;


(*
   relScaleX -
*)

PROCEDURE relScaleX (x: Fract) : Fract ;
BEGIN
   IF config^.same
   THEN
      RETURN dup(x)
   ELSE
      RETURN Fractions.div(Fractions.mult(config^.outMax.x, x), config^.inMax.x) ;
   END
END relScaleX ;


(*
   scaleY - it assumes that, y, is an absolute position on the y axis.
*)

PROCEDURE scaleY (y: Fract) : Fract ;
VAR
   r: Fract ;
BEGIN
   r := relScaleY(y) ;
   RETURN Fractions.add(config^.outMax.y, r)
END scaleY ;


(*
   relScaleY - scales, y, it assumes this is a relative y movement.
*)

PROCEDURE relScaleY (y: Fract) : Fract ;
VAR
   r: Fract ;
BEGIN
   IF config^.same
   THEN
      r := negate(y)
   ELSE
      r := Fractions.negate(Fractions.div(Fractions.mult(config^.outMax.y, y), config^.inMax.y))
   END ;
   RETURN r
END relScaleY ;


(*
   scalePoint - returns a new point after x and y have been scaled to
                fit the output resolution.  Point, p, is an absolute
                position.
*)

PROCEDURE scalePoint (p: Point) : Point ;
VAR
   p1: Point ;
BEGIN
   p1.x := scaleX(p.x) ;
   p1.y := scaleY(p.y) ;
   RETURN p1
END scalePoint ;


(*
   addOffset - adds the x, y, offsets to a point, p.  The same point, p,
               is returned.  Currently only an offset in the Y axis is added.
*)

PROCEDURE addOffset (p: Point) : Point ;
BEGIN
   p.x := inc(p.x, cardinal(Margin)) ;
   p.y := inc(p.y, cardinal(Header)) ;
   RETURN p
END addOffset ;


(*
   moveTo - moves to the absolute position defined by, p.
*)

PROCEDURE moveTo (p: Point) ;
VAR
   p1  : Point ;
   x, y: Fract ;
BEGIN
   p1 := scalePoint(p) ;
   p1 := addOffset(p1) ;

   (* y position *)
   WriteString(file, ".sp |") ; writeUnit(p1.y) ; WriteLn(file) ;

   (* x position *)
   WriteString(file, ".nop \h'") ;
   writeUnit(p1.x) ; WriteString(file, "'") ; WriteLn(file) ;

   p1 := unRootPoint(p1)
END moveTo ;


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
VAR
   s: ADDRESS ;
BEGIN
   s := string(c^.name) ;
   printf("%s", s)
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
   drawCircle -
*)

PROCEDURE drawCircle (g: glyphDesc) ;
BEGIN
   WITH g^.gCircle DO
      moveTo(initPoint(sub(center.x, radius), center.y)) ;
      WriteString(file, ".nop ") ;
      IF filled
      THEN
         WriteString(file, '\M[') ; writeColour(colour) ; WriteString(file, ']') ;
         (* WriteString(file, "\h'") ; writeUnit(scaleX(sub(center.x, radius))) ; WriteString(file, "'") ; *)
         WriteString(file, "\D'C ") ; writeUnit(scaleX(mult(radius, two()))) ; WriteString(file, "'\M[]") ; WriteLn(file)
      ELSE
         WriteString(file, "\D't ") ; writeUnit(thickness) ;
         WriteString(file, "'\h'-") ; writeUnit(thickness) ;
         WriteString(file, "'\c") ;  WriteLn(file) ;
         WriteString(file, '.nop \m[') ; writeColour(colour) ; WriteString(file, ']') ;
         (* WriteString(file, "\h'") ; writeUnit(scaleX(sub(center.x, radius))) ; WriteString(file, "'") ; *)
         WriteString(file, "\D'c ") ; writeUnit(scaleX(mult(radius, two()))) ; WriteString(file, "'\m[]") ; WriteLn(file)
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
   o     : Point ;
   o1, o2: Point ;
BEGIN
   IF clipLine(p1, p2, o1, o2)
   THEN
      moveTo(o1) ;
      WriteString(file, ".nop ") ;
      WriteString(file, "\D't ") ; writeUnit(thickness) ;
      WriteString(file, "'\h'-") ; writeUnit(thickness) ;
      WriteString(file, "'\m[") ;
      writeColour(colour) ;
      WriteString(file, "]\D'l ") ;
      o := subPoint(o2, o1) ;
      writeUnit(relScaleX(o.x)) ; WriteString(file, " ") ;
      writeUnit(relScaleY(o.y)) ; WriteString(file, "'\m[] ") ;
      WriteLn(file)
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
   first : BOOLEAN ;
   i     : CARDINAL ;
   p, q,
   o1, o2: Point ;
BEGIN
   WITH g^.gPolygon DO
      IF noPoints=2
      THEN
         drawLine(pArray[0], pArray[1], colour, thickness)
      ELSE
         first := TRUE ;
         p := dupPoint(pArray[0]) ;
         FOR i := 1 TO noPoints-1 DO
            IF clipLine(p, pArray[i], o1, o2)
            THEN
               IF first
               THEN
                  moveTo(p) ;
                  WriteString(file, ".nop ") ;
                  IF filled
                  THEN
                     WriteString(file, "\M[") ;
                     writeColour(colour) ;
                     WriteString(file, "]\D'P ") ;
                  ELSE
                     WriteString(file, "\D't ") ; writeUnit(thickness) ;
                     WriteString(file, "'\h'-") ; writeUnit(thickness) ;
                     WriteString(file, "'\m[") ;
                     writeColour(colour) ;
                     WriteString(file, "]\D'p ") ;
                  END ;
                  first := FALSE
               END ;
               p := subPoint(o2, o1) ;
               writeUnit(relScaleX(p.x)) ; WriteString(file, " ") ;
               writeUnit(relScaleY(p.y)) ; WriteString(file, " ") ;
               p := unRootPoint(p) ;
               p := dupPoint(o2)
            END
         END ;
         IF NOT first
         THEN
            IF filled
            THEN
               WriteString(file, "'\M[]")
            ELSE
               WriteString(file, "'\m[]")
            END ;
            WriteLn(file)
         END ;
         p := unRootPoint(p)
      END
   END
END drawPolygon ;


(*
   produceAVI - generate an AVI file from the sequence of png images.
*)

PROCEDURE produceAVI (fps: CARDINAL; width, height: CARDINAL) ;
VAR
   s: String ;
BEGIN
   IF Exec
   THEN
      s := Sprintf3(InitString('mencoder "mf://f*.png" -mf w=%d:h=%d:fps=%d:type=png -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o movie.avi'),
                    width, height, fps) ;
      debugSystem(s) ;
      s := KillString(s) ;
      (*
       s := InitString('rm -f *.pnm *.png f*.ms') ;
       debugSystem(s) ;
       s := KillString(s)
      *)
   END
END produceAVI ;


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
   configDevice - configure the output device to have outMax resolution and whether
                  it should produce a sequence of individual troff files which
                  can be combined to make a mpeg movie.  Or alternatively whether
                  each frame should be dynamically rendered into a postscript
                  file displayed by 'gv'.
*)

PROCEDURE configDevice (inMax, outMax: Point; fps: CARDINAL;
                        separateFiles, mpeg, ps, gv: BOOLEAN) ;
BEGIN
   config^.inMax := dupPoint(inMax) ;
   config^.outMax := dupPoint(outMax) ;
   config^.fps := fps ;
   config^.mpeg := mpeg ;
   config^.ps := ps ;
   config^.evince := gv ;
   config^.separateFiles := separateFiles ;
   config^.same := Fractions.areEqual(inMax.x, outMax.x) AND
                   Fractions.areEqual(inMax.y, outMax.y)
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
   Init - initialise this module.
*)

PROCEDURE Init ;
VAR
   e: entity ;
BEGIN
   frameNo := 0 ;
   filename := NIL ;
   cNum := 0 ;
   cArray := Indexing.InitIndex(1) ;
   evinceRunning := FALSE ;
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
   firstFrame := TRUE ;

   configDevice(initPoint(one(), one()), initPoint(cardinal(Width), cardinal(Height)), 1,
                FALSE, FALSE, FALSE, TRUE)
END Init ;


END deviceGroff.
