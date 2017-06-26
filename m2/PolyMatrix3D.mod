(* Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010
                 Free Software Foundation, Inc. *)
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
Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. *)

IMPLEMENTATION MODULE PolyMatrix3D ;

FROM SYSTEM IMPORT ADR, TSIZE, ADDRESS ;
FROM libc IMPORT strlen, strncpy, write, exit ;
FROM Assertion IMPORT Assert ;
FROM StrIO IMPORT WriteString, WriteLn ;
FROM ASCII IMPORT nul, tab, lf ;
FROM DynamicStrings IMPORT InitString ;
FROM GC IMPORT garbage, entity, initGarbage, markEntity, allocate, rootDeallocate, rootAllocate, rootEntity, getData ;

IMPORT Fractions ;


CONST
   PoisonOn = FALSE ;    (* to enable debugging of this module, turn on PoisonOn and DebugOn  *)
   DebugOn  = FALSE ;
   CheckOn  = FALSE ;    (* to enable debugging of users of this module turn on               *)
   TraceOn  = FALSE ;    (* CheckOn and TraceOn.                                              *)

TYPE
   Matrix = POINTER TO RECORD
                          value  : MatrixValue ;
                          gentity: entity ;
                       END ;

VAR
   matrixHeap: garbage ;


(*
   init - creates an unrooted matrix and returns the matrix object.
*)

PROCEDURE init () : Matrix ;
VAR
   m   : Matrix ;
   e   : entity ;
   i, j: CARDINAL ;
BEGIN
   allocate(matrixHeap, e, m) ;
   m^.gentity := e ;
   WITH m^ DO
      FOR j := 1 TO MaxDimension DO
         FOR i := 1 TO MaxDimension DO
            value[i, j] := NIL
         END
      END
   END ;
   RETURN m
END init ;


(*
   root - grafts matrix into the roots of the garbage tree.
*)

PROCEDURE root (m: Matrix) : Matrix ;
BEGIN
   rootEntity(matrixHeap, m^.gentity, m) ;
   RETURN m
END root ;


(*
   kill - removes, m, from the roots of the garbage tree.
*)

PROCEDURE kill (m: Matrix) : Matrix ;
BEGIN
   rootDeallocate(matrixHeap, m^.gentity, m) ;
   RETURN NIL
END kill ;


(*
   eval - returns, m, after all values have been simplified.
*)

PROCEDURE eval (m: Matrix) : Matrix ;
VAR
   i, j: CARDINAL ;
BEGIN
   WITH m^ DO
      FOR i := 1 TO MaxDimension DO
         FOR j := 1 TO MaxDimension DO
            value[i, j] := Fractions.simplify(value[i, j])
         END
      END
   END ;
   RETURN m
END eval ;


(*
   set - sets the elements of a Matrix with the values.
*)

PROCEDURE set (m: Matrix; v: MatrixValue) : Matrix ;
BEGIN
   WITH m^ DO
      value := v
   END ;
   RETURN m
END set ;


(*
   get - gets the elements of a Matrix into value MatrixValues.
*)

PROCEDURE get (m: Matrix; VAR v: MatrixValue) : Matrix ;
BEGIN
   WITH m^ DO
      v := value
   END ;
   RETURN m
END get ;


(*
   add - adds a and b together and returns the result.
*)

PROCEDURE add (a, b: Matrix) : Matrix ;
VAR
   i, j: CARDINAL ;
   m   : Matrix ;
BEGIN
   m := init() ;
   WITH m^ DO
      FOR i := 1 TO MaxDimension DO
         FOR j := 1 TO MaxDimension DO
            value[i, j] := Fractions.add(a^.value[i, j], b^.value[i, j])
         END
      END
   END ;
   RETURN m
END add ;


(*
   dup - returns a copy of, m.
*)

PROCEDURE dup (m: Matrix) : Matrix ;
VAR
   n   : Matrix ;
   i, j: CARDINAL ;
BEGIN
   n := init() ;
   FOR i := 1 TO MaxDimension DO
      FOR j := 1 TO MaxDimension DO
         n^.value[i, j] := Fractions.dup(m^.value[i, j])
      END
   END ;
   RETURN n
END dup ;


(*
   mult - multiplies a and b together and returns the result.
*)

PROCEDURE mult (a, b: Matrix) : Matrix ;
VAR
   i, j: CARDINAL ;
   m   : Matrix ;
BEGIN
   m := init() ;
   WITH m^ DO
      (* 1st row *)
      value[1, 1] := Fractions.add3(Fractions.mult(a^.value[1, 1], b^.value[1, 1]),
                                    Fractions.mult(a^.value[1, 2], b^.value[2, 1]),
                                    Fractions.mult(a^.value[1, 3], b^.value[3, 1])) ;
      value[1, 2] := Fractions.add3(Fractions.mult(a^.value[1, 1], b^.value[1, 2]),
                                    Fractions.mult(a^.value[1, 2], b^.value[2, 2]),
                                    Fractions.mult(a^.value[1, 3], b^.value[3, 2])) ;
      value[1, 3] := Fractions.add3(Fractions.mult(a^.value[1, 1], b^.value[1, 3]),
                                    Fractions.mult(a^.value[1, 2], b^.value[2, 3]),
                                    Fractions.mult(a^.value[1, 3], b^.value[3, 3])) ;
      (* 2nd row *)
      value[2, 1] := Fractions.add3(Fractions.mult(a^.value[2, 1], b^.value[1, 1]),
                                    Fractions.mult(a^.value[2, 2], b^.value[2, 1]),
                                    Fractions.mult(a^.value[2, 3], b^.value[3, 1])) ;
      value[2, 2] := Fractions.add3(Fractions.mult(a^.value[2, 1], b^.value[1, 2]),
                                    Fractions.mult(a^.value[2, 2], b^.value[2, 2]),
                                    Fractions.mult(a^.value[2, 3], b^.value[3, 2])) ;
      value[2, 3] := Fractions.add3(Fractions.mult(a^.value[2, 1], b^.value[1, 3]),
                                    Fractions.mult(a^.value[2, 2], b^.value[2, 3]),
                                    Fractions.mult(a^.value[2, 3], b^.value[3, 3])) ;
      (* 3rd row *)
      value[3, 1] := Fractions.add3(Fractions.mult(a^.value[3, 1], b^.value[1, 1]),
                                    Fractions.mult(a^.value[3, 2], b^.value[2, 1]),
                                    Fractions.mult(a^.value[3, 3], b^.value[3, 1])) ;
      value[3, 2] := Fractions.add3(Fractions.mult(a^.value[3, 1], b^.value[1, 2]),
                                    Fractions.mult(a^.value[3, 2], b^.value[2, 2]),
                                    Fractions.mult(a^.value[3, 3], b^.value[3, 2])) ;
      value[3, 3] := Fractions.add3(Fractions.mult(a^.value[3, 1], b^.value[1, 3]),
                                    Fractions.mult(a^.value[3, 2], b^.value[2, 3]),
                                    Fractions.mult(a^.value[3, 3], b^.value[3, 3]))
   END ;
   RETURN m
END mult ;


(*
   mult3 - performs a * (b * c) returns the result.
*)

PROCEDURE mult3 (a, b, c: Matrix) : Matrix ;
BEGIN
   RETURN mult(a, mult(b, c))
END mult3 ;


(*
   mark - marks the matrix as used.
*)

PROCEDURE mark (m: Matrix) : Matrix ;
VAR
   i, j: CARDINAL ;
BEGIN
   markEntity(m^.gentity) ;
   (* and mark all its values *)
   WITH m^ DO
      FOR i := 1 TO MaxDimension DO
         FOR j := 1 TO MaxDimension DO
            Fractions.mark(value[i, j])
         END
      END
   END ;
   RETURN m
END mark ;


(*
   walkMatrix - walks the Matrix data structures, marking it as used.
*)

PROCEDURE walkMatrix (m: Matrix) ;
BEGIN
   m := mark(m)
END walkMatrix ;


(*
   walkMatrixEntity - walks macro, m, associated with entity, e.
*)

PROCEDURE walkMatrixEntity (e: entity) ;
BEGIN
   walkMatrix(getData(e))
END walkMatrixEntity ;


(*
   Init - 
*)

PROCEDURE Init ;
VAR
   m: Matrix ;
BEGIN
   matrixHeap := initGarbage(walkMatrixEntity, TSIZE(m^), InitString('matrices'))
END Init ;


BEGIN
   Init
END PolyMatrix3D.
