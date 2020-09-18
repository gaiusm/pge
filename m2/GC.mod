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

IMPLEMENTATION MODULE GC ;

FROM Assertion IMPORT Assert ;
FROM Indexing IMPORT Index, InitIndex, KillIndex, GetIndice, PutIndice, HighIndice, LowIndice, ForeachIndiceInIndexDo, RemoveIndiceFromIndex, IncludeIndiceIntoIndex ;
FROM Storage IMPORT ALLOCATE ;
FROM SYSTEM IMPORT ADDRESS ;
FROM libc IMPORT printf, memset ;
FROM DynamicStrings IMPORT string ;

IMPORT gdbif ;

CONST
   EnableChecking = TRUE ;
   PoisonOn  = TRUE ;
   GGCPOISON = 05A5A5A5AH ;    (* poisoned memory contains this code *)
   TraceOn   = FALSE ;
   StatsOn   = FALSE ;

TYPE
   callBack = POINTER TO RECORD
                            callp: callP ;
                            next : callBack ;
                         END ;

   garbage = POINTER TO RECORD
                           roots    : Index ;
                           allocated: Index ;
                           bytes    : CARDINAL ;
                           desc     : String ;
                           walkp    : walkP ;
                           callbacks: callBack ;
                           freeList : entity ;
                           next     : garbage ;
                        END ;

   stateValues = (free, marked, used) ;

   state = SET OF stateValues ;

   entity = POINTER TO RECORD
                          data  : ADDRESS ;
                          rIndex: CARDINAL ;
                          status: state ;
                          next  : entity ;
                       END ;

VAR
   headOfGarbage: garbage ;


(*
   initGarbage - initialises a garbage heap which manages a dynamically
                 allocated data type of noOfBytes length.  It must be
                 the same data structure which is walked by, walkP.
*)

PROCEDURE initGarbage (p: walkP; noOfBytes: CARDINAL; typeName: String) : garbage ;
VAR
   g: garbage ;
BEGIN
   NEW(g) ;
   WITH g^ DO
      roots := InitIndex(1) ;
      allocated := InitIndex(1) ;
      bytes := noOfBytes ;
      desc := typeName ;
      walkp := p ;
      callbacks := NIL ;
      freeList := NIL ;
      next := headOfGarbage ;
   END ;
   headOfGarbage := g ;
   RETURN g
END initGarbage ;


(*
   RunCallBacks - runs all the call backs associated with, g.
*)

PROCEDURE RunCallBacks (g: garbage) ;
VAR
   c: callBack ;
BEGIN
   c := g^.callbacks ;
   WHILE c#NIL DO
      c^.callp ;   (* calls the call back *)
      c := c^.next
   END
END RunCallBacks ;


(*
   collectAll - run the garbage collection on all heaps.
*)

PROCEDURE collectAll ;
BEGIN
   (* gdbif.sleepSpin ; *)
   walkRootsAll ;
   unMarkAll ;
   walkRootsAll ;
   tidyUpAll
END collectAll ;


(*
   unMarkAll -
*)

PROCEDURE unMarkAll ;
VAR
   g: garbage ;
   a: ADDRESS ;
   d: CARDINAL ;
BEGIN
   g := headOfGarbage ;
   WHILE g#NIL DO
      WITH g^ DO
         IF StatsOn
         THEN
            a := string(desc) ;
            printf("garbage collecting on the %s heap", a) ;
            d := HighIndice(allocated) ;
            printf(", total entities %d", d) ;
            d := HighIndice(roots) ;
            printf(", rooted entities %d\n", d)
         END ;
         (* throw away the free list *)
         freeList := NIL ;
         ForeachIndiceInIndexDo(allocated, unMarkEntity)
      END ;
      g := g^.next
   END
END unMarkAll ;


(*
   walkRootsAll -
*)

PROCEDURE walkRootsAll ;
VAR
   g: garbage ;
   a: ADDRESS ;
BEGIN
   g := headOfGarbage ;
   WHILE g#NIL DO
      WITH g^ DO
         IF StatsOn
         THEN
            a := string(desc) ;
            printf(" marking all entities in the roots of %s\n", a)
         END ;
         ForeachIndiceInIndexDo(roots, markEntity) ;
         IF StatsOn
         THEN
            printf(" walking all entities in the roots of %s\n", a)
         END ;
         ForeachIndiceInIndexDo(roots, walkp)
      END ;
      IF StatsOn
      THEN
         printf(" running all call backs associated with %s\n", a)
      END ;
      RunCallBacks(g) ;
      g := g^.next
   END
END walkRootsAll ;


(*
   tidyUpAll -
*)

PROCEDURE tidyUpAll ;
VAR
   g: garbage ;
   a: ADDRESS ;
BEGIN
   g := headOfGarbage ;
   WHILE g#NIL DO
      IF StatsOn
      THEN
         WITH g^ DO
            a := string(desc) ;
            printf(" %s heap now has: ", a)
         END
      END ;
      tidyUpEntities(g) ;
      g := g^.next
   END
END tidyUpAll ;


(*
   collect - collect all used entities and place them onto the free list.
*)

PROCEDURE collect (g: garbage) ;
VAR
   a: ADDRESS ;
   d: CARDINAL ;
BEGIN
   WITH g^ DO
      IF StatsOn
      THEN
         a := string(desc) ;
         printf("garbage collecting on the %s heap\n", a) ;
         d := HighIndice(allocated) ;
         printf(", total entities %d", d) ;
         d := HighIndice(roots) ;
         printf(", rooted entities %d", d)
      END ;
      (* throw away the free list *)
      freeList := NIL ;
      ForeachIndiceInIndexDo(allocated, unMarkEntity) ;
      ForeachIndiceInIndexDo(roots, markEntity) ;
      ForeachIndiceInIndexDo(roots, walkp) ;
      RunCallBacks(g) ;
      tidyUpEntities(g)
   END
END collect ;


(*
   tidyUpEntities -
*)

PROCEDURE tidyUpEntities (g: garbage) ;
VAR
   u, f: CARDINAL ;
   i   : CARDINAL ;
   e   : entity ;
BEGIN
   u := 0 ;
   f := 0 ;
   WITH g^ DO
      i := LowIndice(allocated) ;
      WHILE i<=HighIndice(allocated) DO
         e := GetIndice(allocated, i) ;
         IF marked IN e^.status
         THEN
            INC(u) ;
            e^.status := state{used}
         ELSE
            INC(f) ;
            e^.next := freeList ;
            freeList := e ;
            e^.status := state{free} ;
            IF PoisonOn
            THEN
               IF memset(e^.data, GGCPOISON, bytes)=NIL
               THEN
                  (* ignore return code from memset *)
               END
            END
         END ;
         INC(i)
      END
   END ;
   IF StatsOn
   THEN
      printf(" used %d, and, freed %d\n", u, f)
   END
END tidyUpEntities ;


(*
   markEntity - sets the status of entity, e, to marked.
*)

PROCEDURE markEntity (e: entity) ;
VAR
   a: ADDRESS ;
BEGIN
   WITH e^ DO
      IF TraceOn
      THEN
         a := e^.data ;
         printf("marking address 0x%x using entity (0x%x)\n", a, e)
      END ;
      Assert(NOT (free IN status)) ;   (* corrupt entity, it should never be marked if on the free list *)
      INCL(status, marked)
   END
END markEntity ;


(*
   unMarkEntity - sets the status of entity, e, to nothing.
*)

PROCEDURE unMarkEntity (e: entity) ;
VAR
   a: ADDRESS ;
BEGIN
   IF TraceOn
   THEN
      a := e^.data ;
      printf("unmarking address 0x%x using entity (0x%x)\n", a, e)
   END ;
   EXCL(e^.status, marked)
END unMarkEntity ;


(*
   rootEntity - records data, a, to be part of the roots in heap, g.
                Useful if an entity was created using, allocate,
                and now needs to be remembered.
*)

PROCEDURE rootEntity (g: garbage; e: entity; a: ADDRESS) ;
VAR
   i : CARDINAL ;
   en: entity ;
BEGIN
   WITH g^ DO
      i := LowIndice(roots) ;
      WHILE i<=HighIndice(roots) DO
         en := GetIndice(roots, i) ;
         IF en^.data=a
         THEN
            IF en#e
            THEN
               HALT  (* rooted with a different entity - corruption of data structures *)
            END ;
            (* already rooted *)
            RETURN
         ELSE
            INC(i)
         END
      END ;
      e^.rIndex := HighIndice(roots)+1 ;
      PutIndice(roots, e^.rIndex, e)
   END
END rootEntity ;


(*
   initEntity - records data, a, to be managed by heap, g.  Note that
                it is not rooted.
*)

PROCEDURE initEntity (g: garbage; a: ADDRESS; e: entity) ;
VAR
   i, h: CARDINAL ;
   en  : entity ;
BEGIN
   WITH g^ DO
      i := LowIndice(allocated) ;
      h := HighIndice(allocated) ;
      WHILE i<=h DO
         en := GetIndice(allocated, i) ;
         IF en^.data=a
         THEN
            IF en#e
            THEN
               HALT  (* known by a different entity - corruption of data structures *)
            END ;
            (* already known *)
            RETURN
         ELSE
            INC(i)
         END
      END ;
      PutIndice(allocated, HighIndice(allocated)+1, e)
   END
END initEntity ;


(*
   newEntity - initialises an entity.
*)

PROCEDURE newEntity (e: entity; a: ADDRESS) ;
BEGIN
   WITH e^ DO
      data := a ;
      rIndex := 0 ;
      status := state{used} ;
      next := NIL
   END
END newEntity ;


(*
   findFree - use the free list of, g, to find a spare entity and associated address.
*)

PROCEDURE findFree (g: garbage; VAR e: entity; VAR a: ADDRESS) ;
BEGIN
   WITH g^ DO
      IF freeList=NIL
      THEN
         ALLOCATE(a, bytes) ;
         NEW(e)
      ELSE
         (* freeList entities _will_ be on the allocated array *)
         e := freeList ;
         a := e^.data ;
         freeList := freeList^.next ;
      END ;
      newEntity(e, a)
   END
END findFree ;


(*
   allocate - returns allocated memory from, a.  It also
              returns entity, e, which is associated with, a.
*)

PROCEDURE allocate (g: garbage; VAR e: entity; VAR a: ADDRESS) ;
VAR
   n, b: ADDRESS ;
BEGIN
   findFree(g, e, a) ;
   initEntity(g, a, e) ;
   IF TraceOn
   THEN
      n := string(g^.desc) ;
      b := e ;
      printf("allocated 0x%x (byte length %d) using entity 0x%x associated with %s\n", a, g^.bytes, b, n)
   END
END allocate ;


(*
   rootAllocate - returns allocated memory from, a, with length, bytes.  It also
                  returns entity, e, which is associated with, a.

                  It registers this entity in the root of the garbage collection.
*)

PROCEDURE rootAllocate (g: garbage; VAR e: entity; VAR a: ADDRESS) ;
VAR
   n: ADDRESS ;
BEGIN
   allocate(g, e, a) ;
   rootEntity(g, e, a) ;
   IF TraceOn
   THEN
      n := string(g^.desc) ;
      printf(" rooted address 0x%x (%s)\n", a, n)
   END
END rootAllocate ;


(*
   rootDeallocate - deallocates memory from, a, with length, bytes.
                    It also unregisters entity, e, from the root.
*)

PROCEDURE rootDeallocate (g: garbage; VAR e: entity; VAR a: ADDRESS) ;
VAR
   n: ADDRESS ;
BEGIN
   IF (e#NIL) AND (a#NIL) AND (e^.rIndex#0)
   THEN
      IF TraceOn
      THEN
         n := string(g^.desc) ;
         printf("unrooted address 0x%x (%s)\n", a, n)
      END ;
      WITH g^ DO
         RemoveIndiceFromIndex(roots, e) ;   (* could improve by using e^.rIndex and DeleteIndiceFromIndex --fixme-- *)
         e^.rIndex := 0
      END
   END
END rootDeallocate ;


(*
   getData - returns the address associated with entity, e.
*)

PROCEDURE getData (e: entity) : ADDRESS ;
BEGIN
   RETURN e^.data
END getData ;


(*
   registerCallback - call procedure, p, when the garbage collector is marking used entities.
*)

PROCEDURE registerCallback (g: garbage; p: callP) ;
VAR
   c: callBack ;
BEGIN
   WITH g^ DO
      NEW(c) ;
      c^.next := callbacks ;
      c^.callp := p ;
      callbacks := c
   END
END registerCallback ;


(*
   Init - initialise the global data structures.
*)

PROCEDURE Init ;
BEGIN
   headOfGarbage := NIL
END Init ;


BEGIN
   Init
END GC.
