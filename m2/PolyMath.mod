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

IMPLEMENTATION MODULE PolyMath ;


TYPE
   Poly = POINTER TO RECORD
                        value: ADDRESS ;
                        inc,
                        dec,
                        add,
                        sub,
                        div,
                        mult : binPoly ;
                        sin,
                        cos,
                        tan,    
                        neg,
                        kill,
                        dup,
                        mark : unPoly ;
                        next : Poly ;
                     END ;

VAR
   freeList: Poly ;


(*
   newPoly - returns a new Poly entity.
*)

PROCEDURE newPoly () : Poly ;
VAR
   p: Poly ;
BEGIN
   IF freeList=NIL
   THEN
      NEW(p)
   ELSE
      p := freeList ;
      freeList := freeList^.next ;
      WITH p^ DO
         next := NIL
      END
   END ;
   RETURN p
END newPoly ;


(*
   initPoly - initialises the polymorphic data type, p, to have a value, v.
              The operators:

                inc    i
                dec    e
                add    a
                sub    s
                div    d
                mult   m
                negate n
                kill   k
                dup    u
                mark   r

              are also assignment.
*)

PROCEDURE initPoly (si, co, ta, i, e, a, s, d, m: binPoly; n, k, u, r: unPoly; v: ADDRESS) : Poly ;
VAR
   p: Poly ;
BEGIN
   p := newPoly() ;
   WITH p^ DO
      sin := si ;
      cos := co ;
      tan := ta ;
      inc := i ;
      dec := e ;
      add := a ;
      sub := s ;
      div := d ;
      mult := m ;
      negate := n ;
      kill := k ;
      dup := u ;
      mark := r ;
      value := v
   END ;
   RETURN p
END initPoly ;


(*
   clonePoly - returns a new poly, which is initialised to use the functions used in, c.
*)

PROCEDURE clonePoly (c: Poly) : Poly ;
VAR
   p: Poly ;
BEGIN
   WITH c^ DO
      p := initPoly(sin, cos, tan, inc, dec, add, sub, div, mult, negate, kill, dup, mark, NIL)
   END ;
   RETURN p
END clonePoly ;


(*
   add3 - returns the result of (a + b + c).  A new Poly is created.
*)

PROCEDURE add3 (a, b, c: Poly) : Poly ;
VAR
   p: Poly ;
BEGIN
   p := inc(add(a, b), c) ;
   RETURN p
END add3 ;


(*
   add - returns a new poly which contains the value of:   (l + r)
*)

PROCEDURE add (l, r: Poly) : Poly ;
VAR
   p: Poly ;
BEGIN
   p := clonePoly(l) ;
   p^ := l^ ;
   p^.value := l^.add(l^.value, r^.value) ;
   RETURN p
END add ;


(*
   mult - returns a new poly which contains the value of:   (l * r)
*)

PROCEDURE mult (l, r: Poly) : Poly ;
VAR
   p: Poly ;
BEGIN
   p := clonePoly(l) ;
   p^.value := l^.mult(l^.value, r^.value) ;
   RETURN p
END mult ;


(*
   div - returns a new poly which contains the value of:   (l / r)
*)

PROCEDURE div (l, r: Poly) : Poly ;
VAR
   p: Poly ;
BEGIN
   p := clonePoly(l) ;
   p^.value := l^.div(l^.value, r^.value) ;
   p := addToGarbage(l) ;
   p := addToGarbage(r) ;
   RETURN p
END div ;


(*
   sub - returns a new poly which contains the value of:   (l - r)
*)

PROCEDURE sub (l, r: Poly) : Poly ;
VAR
   p: Poly ;
BEGIN
   p := clonePoly(l) ;
   p^.value := l^.sub(l^.value, r^.value) ;
   RETURN p
END sub ;


(*
   inc - returns, l, after, r, has been added to it.
         Notice that a new poly is NOT created.
*)

PROCEDURE inc (l, r: Poly) : Poly ;
BEGIN
   l^.value := l^.inc(l^.value, r^.value) ;
   RETURN l
END inc ;


(*
   dec - returns, l, after, r, has been subtracted from it.
         Notice that a new poly is NOT created.
*)

PROCEDURE dec (l, r: Poly) : Poly ;
BEGIN
   l^.value := l^.dec(l^.value, r^.value) ;
   RETURN l
END dec ;


(*
   mark - marks Poly, p, ready for garbage collection.
*)

PROCEDURE mark (p: Poly) : Poly ;
BEGIN
(*
   IF PoisonOn
   THEN
      p := CheckPoisoned(p)
   END ;
*)
   IF (p#NIL) AND (p^.state=inuse)
   THEN
      p^.state := marked
   END ;
   RETURN p
END mark ;




BEGIN
   freeList := NIL
END PolyMath.
