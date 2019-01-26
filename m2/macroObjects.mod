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

IMPLEMENTATION MODULE macroObjects ;

FROM Points IMPORT Point, dupPoint, addPoint, scalePoint, markPoint, initPoint, zeroPoint, negatePoint ;
FROM PolyMatrix3D IMPORT Matrix, MatrixValue, get, root ;
FROM Fractions IMPORT one, zero, isZero, isNegative, getFract, writeFract ;
FROM Assertion IMPORT Assert ;
FROM STextIO IMPORT WriteString, WriteLn ;
FROM SWholeIO IMPORT WriteCard ;
FROM DynamicStrings IMPORT InitString ;
FROM GC IMPORT garbage, entity, initGarbage, markEntity, allocate, rootEntity, rootDeallocate, getData ;
FROM SYSTEM IMPORT TSIZE ;

IMPORT Fractions ;
IMPORT Transform3D ;
IMPORT PolyMatrix3D ;

CONST
   maxPoints = 10 ;

TYPE
   typeOfObject = (tcircle, tpolygon) ;

   Object = POINTER TO RECORD
                          CASE type: typeOfObject OF

                          tcircle    :  oCircle    :  Circle |
                          tpolygon   :  oPolygon   :  Polygon

                          END ;
                          oentity: entity ;
                          next   : Object ;
                       END ;

   Circle = RECORD
               colour   : Colour ;
               filled   : BOOLEAN ;
               thickness: Fract ;
               center   : Point ;
               radius   : Fract ;
            END ;

   Polygon = RECORD
                colour   : Colour ;
                filled   : BOOLEAN ;
                thickness: Fract ;
                noPoints : CARDINAL ;
                pArray   : ARRAY [0..maxPoints] OF Point ;
             END ;

   Macro = POINTER TO RECORD
                         head   : Object ;
                         pos    : Point ;
                         mentity: entity ;
                      END ;


VAR
   objectHeap,
   macroHeap : garbage ;


(*
   dumpFract -
*)

PROCEDURE dumpFract (f: Fract) ;
BEGIN
   writeFract(f)
END dumpFract ;


(*
   dumpPoint - displays point, p.
*)

PROCEDURE dumpPoint (p: Point) ;
BEGIN
   WriteString(" (") ;
   dumpFract(p.x) ;
   WriteString(", ") ;
   dumpFract(p.y) ;
   WriteString(") ")
END dumpPoint ;


(*
   dp - debug point.
*)

PROCEDURE dp (p: Point) ;
BEGIN
   dumpPoint(p) ;
   WriteLn
END dp ;


(*
   dumpColour -
*)

PROCEDURE dumpColour (c: Colour) ;
BEGIN
   WriteCard(c, 4)
END dumpColour ;


(*
   dumpCircle - dumps circle information.
*)

PROCEDURE dumpCircle (o: Object) ;
BEGIN
   WITH o^.oCircle DO
      WriteString("circle ") ;
      IF filled
      THEN
         WriteString("filled with colour ") ;
         dumpColour(colour)
      ELSE
         WriteString("outlined with colour ") ;
         dumpColour(colour) ;
         WriteString(" with a thickness of ") ;
         dumpFract(thickness)
      END ;
      WriteString(" at ") ;
      dumpPoint(center) ;
      WriteString(" radius ") ;
      dumpFract(radius) ;
      WriteLn
   END
END dumpCircle ;


(*
   dumpPolygon - dumps the polygon information.
*)

PROCEDURE dumpPolygon (o: Object) ;
VAR
   i: CARDINAL ;
BEGIN
   WITH o^.oPolygon DO
      WriteString("polygon ") ;
      IF filled
      THEN
         WriteString("filled with colour ") ;
         dumpColour(colour)
      ELSE
         WriteString("outlined with colour ") ;
         dumpColour(colour) ;
         WriteString(" with a thickness of ") ;
         dumpFract(thickness)
      END ;
      WriteString(" coordinates ") ;
      FOR i := 0 TO noPoints-1 DO
         dumpPoint(pArray[i])
      END ;
      WriteLn
   END
END dumpPolygon ;


(*
   dumpObject - dump the object, o.
*)

PROCEDURE dumpObject (o: Object) ;
BEGIN
   CASE o^.type OF

   tcircle :  dumpCircle(o) |
   tpolygon:  dumpPolygon(o)

   END
END dumpObject ;


(*
   dmac - debug macro, m.
*)

PROCEDURE dmac (m: Macro) ;
VAR
   o: Object ;
BEGIN
   WriteString("macro position: ") ;
   dumpPoint(m^.pos) ;
   WriteLn ;
   o := m^.head ;
   WHILE o#NIL DO
      dumpObject(o) ;
      o := o^.next
   END
END dmac ;


(*
   dmat -
*)

PROCEDURE dmat (m: Matrix) ;
VAR
   i, j: CARDINAL ;
   v   : MatrixValue ;
BEGIN
   m := get(m, v) ;
   WriteString('+-') ; WriteLn ;
   WriteString('| ') ; FOR i := 1 TO 3 DO dumpFract(v[1, i]) ; WriteString('  ') END ; WriteLn ;
   WriteString('| ') ; FOR i := 1 TO 3 DO dumpFract(v[2, i]) ; WriteString('  ') END ; WriteLn ;
   WriteString('| ') ; FOR i := 1 TO 3 DO dumpFract(v[3, i]) ; WriteString('  ') END ; WriteLn ;
   WriteString('+-') ;
   WriteString(' ') ; WriteLn
END dmat ;


(*
   initMacro - creates and returns a macro.
*)

PROCEDURE initMacro () : Macro ;
VAR
   m: Macro ;
   e: entity ;
BEGIN
   allocate(macroHeap, e, m) ;
   WITH m^ DO
      head := NIL ;
      pos := initPoint(zero(), zero()) ;
      mentity := e
   END ;
   RETURN m
END initMacro ;


(*
   rootMacro - register macro, m, with the roots of the garbage collector.
*)

PROCEDURE rootMacro (m: Macro) : Macro ;
BEGIN
   rootEntity(macroHeap, m^.mentity, m) ;
   RETURN m
END rootMacro ;


(*
   dup - duplicates and returns a new macro.
*)

PROCEDURE dup (m: Macro) : Macro ;
VAR
   n: Macro ;
   o: Object ;
BEGIN
   n := initMacro() ;
   n^.pos := dupPoint(m^.pos) ;
   o := m^.head ;
   WHILE o#NIL DO
      n := addToEnd(n, dupObject(o, zeroPoint())) ;
      o := o^.next
   END ;
   RETURN n
END dup ;


(*
   dupCircle - return a new circle object based on the values in, o.
               It adds the offset to the object from, p.
*)

PROCEDURE dupCircle (o: Object; p: Point) : Object ;
VAR
   n: Object ;
BEGIN
   n := initObject() ;
   WITH n^ DO
      type := tcircle ;
      WITH oCircle DO
         colour := o^.oCircle.colour ;
         filled := o^.oCircle.filled ;
         thickness := Fractions.dup(o^.oCircle.thickness) ;
         center := addPoint(o^.oCircle.center, p) ;
         radius := Fractions.dup(o^.oCircle.radius)
      END
   END ;
   RETURN n
END dupCircle ;


(*
   dupPolygon - return a new rectangle object based on the values in, o.
                It adds the offset to the object from, p.
*)

PROCEDURE dupPolygon (o: Object; p: Point) : Object ;
VAR
   n: Object ;
   i: CARDINAL ;
BEGIN
   n := initObject() ;
   WITH n^ DO
      type := tpolygon ;
      WITH oPolygon DO
         colour := o^.oPolygon.colour ;
         filled := o^.oPolygon.filled ;
         thickness := Fractions.dup(o^.oPolygon.thickness) ;
         noPoints := o^.oPolygon.noPoints ;
         FOR i := 0 TO noPoints-1 DO
            pArray[i] := addPoint(o^.oPolygon.pArray[i], p)
         END
      END
   END ;
   RETURN n
END dupPolygon ;


(*
   dupObject - returns a duplicate object based on the values in, o.
               It adds the offset to the object from, p.
*)

PROCEDURE dupObject (o: Object; p: Point) : Object ;
BEGIN
   CASE o^.type OF

   tcircle :  RETURN dupCircle(o, p) |
   tpolygon:  RETURN dupPolygon(o, p)

   END
END dupObject ;


(*
   initObject - create and return an uninitialised object.
                The next field is set to NIL.
*)

PROCEDURE initObject () : Object ;
VAR
   o: Object ;
   e: entity ;
BEGIN
   allocate(objectHeap, e, o) ;
   WITH o^ DO
      next := NIL ;
      oentity := e
   END ;
   RETURN o
END initObject ;


(*
   moveTo - assign the internal position in macro, m, to, p.
*)

PROCEDURE moveTo (m: Macro; p: Point) : Macro ;
BEGIN
   WITH m^ DO
      pos := dupPoint(p)
   END ;
   RETURN m
END moveTo ;


(*
   right - move right relatively by, f, units.
*)

PROCEDURE right (m: Macro; f: Fract) : Macro ;
BEGIN
   WITH m^ DO
      pos.x := Fractions.inc(pos.x, f)
   END ;
   RETURN m
END right ;


(*
   left - move left relatively by, f, units.
*)

PROCEDURE left (m: Macro; f: Fract) : Macro ;
BEGIN
   WITH m^ DO
      pos.x := Fractions.dec(pos.x, f)
   END ;
   RETURN m
END left ;


(*
   up - move up relatively by, f, units.
*)

PROCEDURE up (m: Macro; f: Fract) : Macro ;
BEGIN
   WITH m^ DO
      pos.y := Fractions.inc(pos.y, f)
   END ;
   RETURN m
END up ;


(*
   down - move down relatively by, f, units.
*)

PROCEDURE down (m: Macro; f: Fract) : Macro ;
BEGIN
   WITH m^ DO
      pos.y := Fractions.dec(pos.y, f)
   END ;
   RETURN m
END down ;


(*
   addTo - adds object, o, to macro, m.
*)

PROCEDURE addTo (m: Macro; o: Object) : Macro ;
BEGIN
   o^.next := m^.head ;
   m^.head := o ;
   RETURN m
END addTo ;


(*
   triangle - the triangle is defined by the current position:  cp, cp+v1, cp+v2.
*)

PROCEDURE triangle (m: Macro; fill: BOOLEAN; thick: Fract; c: Colour; v1, v2: Point) : Macro ;
VAR
   o: Object ;
BEGIN
   o := initObject() ;
   WITH o^ DO
      type := tpolygon ;
      CASE type OF

      tpolygon:  WITH oPolygon DO
                    filled := fill ;
                    thickness := thick;
                    colour := c ;
                    noPoints := 3 ;
                    pArray[0] := dupPoint(m^.pos) ;
                    pArray[1] := addPoint(dupPoint(m^.pos), v1) ;
                    pArray[2] := addPoint(addPoint(dupPoint(m^.pos), v1), v2)
                 END

      END
   END ;
   RETURN addTo(m, o)
END triangle ;


(*
   rectangle - draw a rectangle at current position which is length, height, units, and is
               filled and has colour, c.
*)

PROCEDURE rectangle (m: Macro; fill: BOOLEAN; thick: Fract; c: Colour; length, height: Fract) : Macro ;
VAR
   o: Object ;
BEGIN
   o := initObject() ;
   WITH o^ DO
      type := tpolygon ;
      CASE type OF

      tpolygon:  WITH oPolygon DO
                    filled := fill ;
                    thickness := thick;
                    colour := c ;
                    noPoints := 4 ;
                    pArray[0] := dupPoint(m^.pos) ;
                    pArray[1].x := Fractions.add(m^.pos.x, length) ;
                    pArray[1].y := Fractions.dup(m^.pos.y) ;
                    pArray[2].x := Fractions.add(m^.pos.x, length) ;
                    pArray[2].y := Fractions.add(m^.pos.y, height) ;
                    pArray[3].x := Fractions.dup(m^.pos.x) ;
                    pArray[3].y := Fractions.add(m^.pos.y, height)
                 END

      END
   END ;
   RETURN addTo(m, o)
END rectangle ;


(*
   circle - draw a circle at current position of, colour, and radius.
*)

PROCEDURE circle (m: Macro; fill: BOOLEAN; thick: Fract; c: Colour; rad: Fract) : Macro ;
VAR
   o: Object ;
BEGIN
   o := initObject() ;
   WITH o^ DO
      type := tcircle ;
      CASE type OF

      tcircle:  WITH oCircle DO
                   filled := fill ;
                   thickness := thick;
                   colour := c ;
                   radius := rad ;
                   center.x := Fractions.dup(m^.pos.x) ;
                   center.y := Fractions.dup(m^.pos.y)
                END

      END
   END ;
   RETURN addTo(m, o)
END circle ;


(*
   angledRect - add angled rectangle to macro, m.  The angled rectangle four points are defined
                by the current position, cp, cp+v1, cp+v1+v2, cp+v2.
*)

PROCEDURE angledRect (m: Macro; fill: BOOLEAN; thick: Fract; c: Colour; v1: Point; v2: Point) : Macro ;
VAR
   o: Object ;
BEGIN
   o := initObject() ;
   WITH o^ DO
      type := tpolygon ;
      CASE type OF

      tpolygon:  WITH oPolygon DO
                    filled := fill ;
                    thickness := thick;
                    colour := c ;
                    noPoints := 4 ;
                    pArray[0] := dupPoint(m^.pos) ;
                    pArray[1] := addPoint(m^.pos, v1) ;
                    pArray[2] := addPoint(m^.pos, addPoint(v1, v2)) ;
                    pArray[3] := addPoint(m^.pos, v2)
                 END

      END
   END ;
   RETURN addTo(m, o)
END angledRect ;


(*
   unRootMacro - unroots macro, m, from the garbage collector.
                 Macro, m, can still be used until the garbage collector is called.
*)

PROCEDURE unRootMacro (m: Macro) : Macro ;
BEGIN
   rootDeallocate(macroHeap, m^.mentity, m) ;
   RETURN m
END unRootMacro ;


(*
   rotate - rotate macro, m, about point, p, with angle, r.
            It returns a new macro.
*)

PROCEDURE rotate (m: Macro; p: Point; r: Fract) : Macro ;
VAR
   a, b, c, d: Matrix ;
   n         : Macro ;
BEGIN
   (* a: translate point, p, to the origin.  *)
   a := Transform3D.translate (negatePoint (dupPoint (p))) ;
   b := Transform3D.rotate (r) ;  (* b: rotate, r, radians.  *)
   c := Transform3D.translate (p) ;  (* c: translate from origin to point, p.  *)
   d := PolyMatrix3D.mult3 (a, b, c) ;  (* d: combine a, b and c transforms.  *)
   n := initMacro () ;
   n := foreachObject (n, m, d) ;  (* n: for every object in, m, transform using, d. *)
   RETURN n
END rotate ;


(*
   translate - translates macro, m, along, vector.
               It returns a new macro.
*)

PROCEDURE translate (m: Macro; vector: Point) : Macro ;
VAR
   a: Matrix ;
   n: Macro ;
BEGIN
   a := Transform3D.translate (vector) ;
   n := initMacro () ;
   RETURN foreachObject (n, m, a)
END translate ;


(*
   scale - scale macro, m, in the x and y axis.  A new
           macro is returned.
*)

PROCEDURE scale (m: Macro; s: Point) : Macro ;
VAR
   a: Matrix ;
   n: Macro ;
BEGIN
   a := Transform3D.scale(s) ;
   n := initMacro() ;
   RETURN foreachObject(n, m, a)
END scale ;


(*
   scalar - scales all scalars within, m, by, f.
            A new macro is returned.
*)

PROCEDURE scalar (m: Macro; f: Fract) : Macro ;
VAR
   n: Macro ;
BEGIN
   n := initMacro() ;
   RETURN foreachObjectScalar(n, m, f)
END scalar ;


(*
   setPointValues -
*)

PROCEDURE setPointValues (VAR v: MatrixValue; p: Point) ;
BEGIN
   v[1, 1] := Fractions.dup(p.x) ;  v[1, 2] := Fractions.dup(p.y) ;   v[1, 3] := one() ;
   v[2, 1] := zero()             ;  v[2, 2] := zero()             ;   v[2, 3] := zero() ;
   v[3, 1] := zero()             ;  v[3, 2] := zero()             ;   v[3, 3] := zero()
END setPointValues ;


(*
   getPointValues - returns a copy of the point values.
*)

PROCEDURE getPointValues (v: MatrixValue) : Point ;
VAR
   p: Point ;
BEGIN
   p.x := Fractions.dup(v[1, 1]) ;
   p.y := Fractions.dup(v[1, 2]) ;
   RETURN p
END getPointValues ;


(*
   mp - multiply point, p, by matrix, a, returning a new point.
*)

PROCEDURE mp (p: Point; a: Matrix) : Point ;
VAR
   v: MatrixValue ;
   i: Matrix ;
   q: Point ;
BEGIN
   setPointValues(v, p) ;
   i := PolyMatrix3D.set(PolyMatrix3D.init(), v) ;
   i := PolyMatrix3D.mult(i, a) ;
   i := PolyMatrix3D.get(i, v) ;
   q := getPointValues(v) ;
   RETURN q
END mp ;


(*
   foreachObjectScalar - foreach object scale the scalar values, by, s.
*)

PROCEDURE foreachObjectScalar (n, m: Macro; s: Fract) : Macro ;
VAR
   o: Object ;
BEGIN
   o := m^.head ;
   WHILE o#NIL DO
      WITH o^ DO
         CASE type OF

         tcircle :  n := addToEnd(n, objectCircleScalar(o, s))

         ELSE
         END
      END ;
      o := o^.next
   END ;
   RETURN n
END foreachObjectScalar ;


(*
   objectCircleScalar - scale the radius by, s.
*)

PROCEDURE objectCircleScalar (o: Object; s: Fract) : Object ;
VAR
   p: Object ;
BEGIN
   p := initObject() ;
   WITH p^ DO
      type := tcircle ;
      oCircle.colour := o^.oCircle.colour ;
      oCircle.filled := o^.oCircle.filled ;
      oCircle.thickness := Fractions.dup(o^.oCircle.thickness) ;
      oCircle.center := o^.oCircle.center ;
      oCircle.radius := Fractions.mult(o^.oCircle.radius, s)
   END ;
   RETURN p
END objectCircleScalar ;


(*
   objectCircleMatrix - return a new circle object after multiplying
                        all points by, a.
*)

PROCEDURE objectCircleMatrix (o: Object; a: Matrix) : Object ;
VAR
   p: Object ;
BEGIN
   p := initObject() ;
   WITH p^ DO
      type := tcircle ;
      oCircle.colour := o^.oCircle.colour ;
      oCircle.filled := o^.oCircle.filled ;
      oCircle.thickness := Fractions.dup(o^.oCircle.thickness) ;
      oCircle.center := mp(o^.oCircle.center, a) ;
      oCircle.radius := Fractions.dup(o^.oCircle.radius)
   END ;
   RETURN p
END objectCircleMatrix ;


(*
   objectPolgonMatrix - return a new polygon object after multiplying
                        all points in, o, by, a.
*)

PROCEDURE objectPolygonMatrix (o: Object; a: Matrix) : Object ;
VAR
   p: Object ;
   i: CARDINAL ;
BEGIN
   p := initObject() ;
   WITH p^ DO
      type := tpolygon ;
      oPolygon.colour := o^.oPolygon.colour ;
      oPolygon.filled := o^.oPolygon.filled ;
      oPolygon.thickness := Fractions.dup(o^.oPolygon.thickness) ;
      oPolygon.noPoints := o^.oPolygon.noPoints ;
      FOR i := 0 TO oPolygon.noPoints-1 DO
         oPolygon.pArray[i] := mp(o^.oPolygon.pArray[i], a)
      END
   END ;
   RETURN p
END objectPolygonMatrix ;


(*
   foreachObject - apply matrix, a, to each object in, m, and add it
                   to macro, n.  Macro, n, is returned.
*)

PROCEDURE foreachObject (n, m: Macro; a: Matrix) : Macro ;
VAR
   o: Object ;
BEGIN
   o := m^.head ;
   WHILE o#NIL DO
      WITH o^ DO
         CASE type OF

         tcircle :  n := addToEnd(n, objectCircleMatrix(o, a)) |
         tpolygon:  n := addToEnd(n, objectPolygonMatrix(o, a))

         END
      END ;
      o := o^.next
   END ;
   RETURN n
END foreachObject ;


(*
   addToEnd -
*)

PROCEDURE addToEnd (m: Macro; o: Object) : Macro ;
VAR
   n: Object ;
BEGIN
   IF m^.head=NIL
   THEN
      m^.head := o
   ELSE
      n := m^.head ;
      WHILE n^.next#NIL DO
         n := n^.next
      END ;
      n^.next := o
   END ;
   o^.next := NIL ;
   RETURN m
END addToEnd ;


(*
   append - returns a new macro which is the result of appending, b, onto the end of, a.
*)

PROCEDURE append (a, b: Macro) : Macro ;
VAR
   c: Macro ;
   o: Object ;
BEGIN
   c := dup(a) ;
   o := b^.head ;
   WHILE o#NIL DO
      c := addToEnd(c, dupObject(o, a^.pos)) ;
      o := o^.next
   END ;
   RETURN c
END append ;


(*
   callCircle -
*)

PROCEDURE callCircle (o: Object; c: cProc) ;
BEGIN
   WITH o^.oCircle DO
      c(center, filled, thickness, radius, colour)
   END
END callCircle ;


(*
   callPolygon -
*)

PROCEDURE callPolygon (o: Object; p: pProc) ;
BEGIN
   WITH o^.oPolygon DO
      p(noPoints, pArray, filled, thickness, colour)
   END
END callPolygon ;


(*
   runCallBacks - for each
                           polygon call p
                           circle call c
                                         in macro, m.
*)

PROCEDURE runCallBacks (m: Macro; p: pProc; c: cProc) ;
VAR
   o: Object ;
BEGIN
   o := m^.head ;
   WHILE o#NIL DO
      CASE o^.type OF

      tcircle   :  callCircle(o, c) |
      tpolygon  :  callPolygon(o, p)

      END ;
      o := o^.next
   END
END runCallBacks ;


(*
   markCircle -
*)

PROCEDURE markCircle (o: Object) ;
BEGIN
   WITH o^.oCircle DO
      Fractions.mark(thickness) ;
      markPoint(center) ;
      Fractions.mark(radius)
   END
END markCircle ;


(*
   markPolygon -
*)

PROCEDURE markPolygon (o: Object) ;
VAR
   i: CARDINAL ;
BEGIN
   WITH o^.oPolygon DO
      Fractions.mark(thickness) ;
      i := 0 ;
      WHILE i<noPoints DO
         markPoint(pArray[i]) ;
         INC(i)
      END
   END
END markPolygon ;


(*
   markObject -
*)

PROCEDURE markObject (o: Object) ;
BEGIN
   WITH o^ DO
      markEntity(o^.oentity) ;
      CASE o^.type OF

      tcircle   :  markCircle(o) |
      tpolygon  :  markPolygon(o)

      END
   END
END markObject ;


(*
   markMacro - marks macro, m, and marks everything.
*)

PROCEDURE markMacro (m: Macro) ;
VAR
   o: Object ;
BEGIN
   WITH m^ DO
      markEntity(mentity) ;
      markPoint(pos) ;
      o := head ;
   END ;
   WHILE o#NIL DO
      markObject(o) ;
      o := o^.next
   END
END markMacro ;


(*
   markMacroEntity - mark macro as specified by, e.
*)

PROCEDURE markMacroEntity (e: entity) ;
BEGIN
   markMacro(getData(e))
END markMacroEntity ;


(*
   markObjectEntity - mark object as specified by, e.
*)

PROCEDURE markObjectEntity (e: entity) ;
BEGIN
   markObject(getData(e))
END markObjectEntity ;


(*
   Init -
*)

PROCEDURE Init ;
VAR
   m: Macro ;
   o: Object ;
BEGIN
   macroHeap := initGarbage(markMacroEntity, TSIZE(m^), InitString('macro')) ;
   objectHeap := initGarbage(markObjectEntity, TSIZE(o^), InitString('objects'))
END Init ;


BEGIN
   Init
END macroObjects.
