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

IMPLEMENTATION MODULE history ;

FROM Storage IMPORT ALLOCATE ;
FROM roots IMPORT nearZero, nearSame, nearCoord ;
FROM libc IMPORT printf ;

CONST
   Debugging = FALSE ;
   Purge     =  TRUE ;
   HalfSecond=   0.5 ;

TYPE
   historyType = (collision, spring) ;

   collisionT = RECORD
                   id1,
                   id2   : CARDINAL ;
                   where1,
                   where2: whereHit ;
                   cp    : Coord ;
                END ;

   springT = RECORD
                id   : CARDINAL ;
                where: springPoint ;
             END ;

   hList = POINTER TO RECORD
                         CASE type: historyType OF

                         collision:  collisionF : collisionT |
			 spring   :  springF : springT |

                         END ;
                         t   : REAL ;
                         next: hList ;
                      END ;

VAR
   currentTime: REAL ;
   free,
   pastQ,
   futureQ    : hList ;


(*
   dumpHlist -
*)

PROCEDURE dumpHlist (l: hList) ;
BEGIN
   printf ("time %g ", l^.t) ;
   CASE l^.type OF

   collision:  printf ("collision id pair (%d, %d)\n", l^.collisionF.id1, l^.collisionF.id2) |
   spring   :  printf ("spring id (%d) ", l^.springF.id) ;
               CASE l^.springF.where OF

               midPoint:  printf ("midpoint") |
               endPoint:  printf ("endpoint") |
               callPoint: printf ("callpoint")

               END

   END ;
   printf ("`n")
END dumpHlist ;


(*
   dumpLists -
*)

PROCEDURE dumpLists ;
VAR
   l: hList ;
BEGIN
   l := pastQ ;
   printf ("Dumping lists\n") ;
   printf ("  past Q\n") ;
   WHILE l # NIL DO
      printf ("  ") ;
      dumpHlist (l) ;
      l := l^.next
   END ;
   l := futureQ ;
   printf ("  futureQ:\n") ;
   WHILE l # NIL DO
      printf ("  ") ;
      dumpHlist (l) ;
      l := l^.next
   END
END dumpLists ;


(*
   newHList - returns a new hList.
*)

PROCEDURE newHList () : hList ;
VAR
   h: hList ;
BEGIN
   IF free=NIL
   THEN
      NEW (h)
   ELSE
      h := free ;
      free := free^.next
   END ;
   RETURN h
END newHList ;


(*
   disposeHList - returns, h, to the free list.
*)

PROCEDURE disposeHList (h: hList) ;
BEGIN
   h^.next := free ;
   free := h
END disposeHList ;


(*
   isPair - are (a, b) the same as (x, y) or
             is (a, b) the same as (y, x)
*)

PROCEDURE isPair (a, b, x, y: CARDINAL) : BOOLEAN ;
BEGIN
   RETURN ((a=x) AND (b=y)) OR
          ((a=y) AND (b=x))
END isPair ;


(*
   assert -
*)

PROCEDURE assert (b: BOOLEAN; line: CARDINAL) ;
BEGIN
   IF NOT b
   THEN
      printf (__FILE__) ;
      printf (":%d:error assert failed\n", line) ;
      HALT
   END
END assert ;


(*
   isSameS -
*)

PROCEDURE isSameS (a, b: hList) : BOOLEAN ;
BEGIN
   assert (a^.type = spring, __LINE__) ;
   assert (b^.type = spring, __LINE__) ;
   RETURN (a^.springF.id = b^.springF.id) AND
          (a^.springF.where = b^.springF.where)
END isSameS ;


(*
   isSameC -
*)

PROCEDURE isSameC (a, b: hList) : BOOLEAN ;
BEGIN
   assert (a^.type = collision, __LINE__) ;
   assert (b^.type = collision, __LINE__) ;
   RETURN isPair (a^.collisionF.id1, a^.collisionF.id2,
                  b^.collisionF.id1, b^.collisionF.id2) AND
      (a^.collisionF.where1 = b^.collisionF.where1) AND
      (a^.collisionF.where2 = b^.collisionF.where2) AND
      (* where1 and where2 are not used yet.  *)
      nearCoord (a^.collisionF.cp, b^.collisionF.cp)
END isSameC ;


(*
   isSame - do, a, and, b, reference the same history object?  We check
            spring and collision frames.

            Note we do not use the contact
            point of collision as polygon/polygon collisions might hit on the corner or
            edge.  Instead we assume if we know the time, polygon, face this is good enough.
            twoDsim will test for multiple points on a line and we need to identify
            duplicates per polygon and line.
*)

PROCEDURE isSame (a, b: hList) : BOOLEAN ;
BEGIN
   RETURN nearZero (a^.t-b^.t) AND
           (a^.type = b^.type) AND
           (((a^.type = collision) AND isSameC (a, b)) OR
            ((a^.type = spring) AND isSameS (a, b)))
END isSame ;


(*
   disposeAll - return NIL.  Place complete contents of, l, onto the free list.
*)

PROCEDURE disposeAll (l: hList) : hList ;
VAR
   a: hList ;
BEGIN
   WHILE l#NIL DO
      a := l ;
      l := l^.next ;
      disposeHList (a)
   END ;
   RETURN NIL
END disposeAll ;


(*
   initS - fill in the fields of, n, and return n.
*)

PROCEDURE initS (n: hList; time: REAL; id: CARDINAL; w: springPoint) : hList ;
BEGIN
   n^.type := spring ;
   n^.springF.id := id ;
   n^.springF.where := w ;
   n^.t := time ;
   n^.next := NIL ;
   RETURN n
END initS ;


(*
   initC - fill in the fields of, n, and return n.
*)

PROCEDURE initC (n: hList; time: REAL; id1, id2: CARDINAL; w1, w2: whereHit; cp: Coord) : hList ;
BEGIN
   n^.type := collision ;
   n^.collisionF.id1 := id1 ;
   n^.collisionF.id2 := id2 ;
   n^.collisionF.where1 := w1 ;
   n^.collisionF.where2 := w2 ;
   n^.collisionF.cp := cp ;
   n^.t := time ;
   n^.next := NIL ;
   RETURN n
END initC ;


(*
   isDuplicateS - returns TRUE if the spring event for object, id,
                  and, time, has occurred before.
                  The time (currentTime+relTime) must be the absolute
                  time of the collision.
*)

PROCEDURE isDuplicateS (currentTime, relTime: REAL;
                        id: CARDINAL; where: springPoint) : BOOLEAN ;
VAR
   h, n: hList ;
BEGIN
   IF Debugging
   THEN
      dumpLists
   END ;
   n := initS (newHList (), currentTime+relTime, id, where) ;
   IF Debugging
   THEN
      printf ("checking for duplicates of: ") ;
      dumpHlist (n)
   END ;
   IF isDuplicateFuture (n) OR isDuplicatePast (n)
   THEN
      IF Debugging
      THEN
         printf ("duplicate spring event found (ignoring): ") ;
         dumpHlist (n)
      END ;
      disposeHList (n) ;
      RETURN TRUE
   END ;
   IF Debugging
   THEN
      printf ("unique spring event found: ") ;
      dumpHlist (n)
   END ;
   disposeHList (n) ;
   RETURN FALSE
END isDuplicateS ;


(*
   isDuplicateC - returns TRUE if the collision at, cp,
                  and, time, has occurred before.
                  The time (currentTime+relTime) must be the absolute
                  time of the collision.
*)

PROCEDURE isDuplicateC (currentTime, relTime: REAL;
                        id1, id2: CARDINAL; w1, w2: whereHit; cp: Coord) : BOOLEAN ;
VAR
   h, n: hList ;
BEGIN
   IF Debugging
   THEN
      dumpLists
   END ;
   n := initC (newHList (), currentTime+relTime, id1, id2, w1, w2, cp) ;
   IF Debugging
   THEN
      printf ("checking for duplicates of: ") ;
      dumpHlist (n)
   END ;
   IF isDuplicateFuture (n) OR isDuplicatePast (n)
   THEN
      IF Debugging
      THEN
         printf ("duplicate collision found (ignoring): ") ;
         dumpHlist (n)
      END ;
      disposeHList (n) ;
      RETURN TRUE
   END ;
   (* updateTime (currentTime) ; *)
   IF Debugging
   THEN
      printf ("unique collision found: ") ;
      dumpHlist (n)
   END ;
   disposeHList (n) ;
   RETURN FALSE
END isDuplicateC ;


(*
   forgetFuture - destroy the anticipated future queue.
*)

PROCEDURE forgetFuture ;
BEGIN
   futureQ := disposeAll (futureQ)
END forgetFuture ;


(*
   occurredS - mark the spring event as having occurred at, currentTime, for spring, id.
               This event is placed onto the past queue.
               If this event is also present on the future queue it is removed.
*)

PROCEDURE occurredS (currentTime: REAL; id: CARDINAL; w: springPoint) ;
VAR
   n: hList ;
BEGIN
   IF Debugging
   THEN
      dumpLists
   END ;
   n := initS (newHList(), currentTime, id, w) ;
   IF Debugging
   THEN
      printf ("spring event has occurred ") ;
      dumpHlist (n) ;
      printf ("spring event has occurred, old queues\n") ;
      dumpLists
   END ;
   updateTime (currentTime) ;
   forgetFuture ;
   (* removeFromFutureQ (n) ; *)
   addToPastQ (n) ;
   IF Debugging
   THEN
      printf ("spring event has occurred queues altered\n") ;
      dumpLists
   END
END occurredS ;


(*
   anticipateS - anticipate a spring event at time, aTime,
                 in the future with spring, i, at, w.
                 A duplicate will ignored.  A non duplicate
                 collision will be placed onto the futureQ.
*)

PROCEDURE anticipateS (aTime: REAL; id: CARDINAL; w: springPoint) ;
VAR
   n: hList ;
BEGIN
   IF Debugging
   THEN
      dumpLists
   END ;
   n := initS (newHList(), aTime, id, w) ;
   IF Debugging
   THEN
      printf ("anticipated spring event at: ") ;
      dumpHlist (n) ;
      printf ("anticipated spring event, old queues\n") ;
      dumpLists
   END ;
   IF isDuplicatePast (n) OR isDuplicateFuture (n)
   THEN
      IF Debugging
      THEN
         printf ("anticipated spring event, duplicate, ignoring\n")
      END ;
      disposeHList (n)
   ELSE
      addToFutureQ (n) ;
      IF Debugging
      THEN
         printf ("anticipated spring event, new queues\n") ;
         dumpLists
      END
   END
END anticipateS ;


(*
   occurredC - mark the collision as having occurred at, currentTime, between, objects
              id1 and id2 at position, cp.  This collision is placed onto the past queue.
              If the event described by id1, id2 at, time, is also present
              on the future queue it is removed.
*)

PROCEDURE occurredC (currentTime: REAL; id1, id2: CARDINAL; cp: Coord) ;
VAR
   n: hList ;
BEGIN
   IF Debugging
   THEN
      dumpLists
   END ;
   n := initC (newHList(), currentTime, id1, id2, edge, edge, cp) ;
   IF Debugging
   THEN
      printf ("collision has occurred ") ;
      dumpHlist (n) ;
      printf ("collision has occurred, old queues\n") ;
      dumpLists
   END ;
   updateTime (currentTime) ;
   forgetFuture ;
   (* removeFromFutureQ (n) ; *)
   addToPastQ (n) ;
   IF Debugging
   THEN
      printf ("collision has occurred queues altered\n") ;
      dumpLists
   END
END occurredC ;


(*
   anticipateC - anticipate a collision at time, aTime, in the future at
                 position, cp.
                 A duplicate will ignored.  A non duplicate
                 collision will be placed onto the futureQ.
*)

PROCEDURE anticipateC (aTime: REAL; id1, id2: CARDINAL; cp: Coord) ;
VAR
   n: hList ;
BEGIN
   IF Debugging
   THEN
      dumpLists
   END ;
   n := initC (newHList(), aTime, id1, id2, edge, edge, cp) ;
   IF Debugging
   THEN
      printf ("anticipated collision at: ") ;
      dumpHlist (n) ;
      printf ("anticipated collision, old queues\n") ;
      dumpLists
   END ;
   IF isDuplicatePast (n) OR isDuplicateFuture (n)
   THEN
      IF Debugging
      THEN
         printf ("anticipated collision, duplicate, ignoring\n")
      END ;
      disposeHList (n)
   ELSE
      addToFutureQ (n) ;
      IF Debugging
      THEN
         printf ("anticipated collision, new queues\n") ;
         dumpLists
      END
   END
END anticipateC ;


(*
   tooClose - returns TRUE if |a-b| < HalfSecond
*)

PROCEDURE tooClose (a, b: REAL) : BOOLEAN ;
BEGIN
   IF Debugging
   THEN
      printf ("a = %g, b = %g\n", a, b)
   END ;
   IF a > b
   THEN
      RETURN (a-b) < HalfSecond
   ELSE
      RETURN (b-a) < HalfSecond
   END
END tooClose ;


(*
   updateTime -
*)

PROCEDURE updateTime (time: REAL) ;
VAR
   p, h: hList ;
BEGIN
   IF NOT nearSame (time, currentTime)
   THEN
      (* time has advanced, see if we can purge the pastQ.  *)
      currentTime := time ;
      IF Purge
      THEN
         (* in the pastQ time is decreasing.  *)
         h := pastQ ;
         p := NIL ;
         WHILE h # NIL DO
            IF tooClose (h^.t, currentTime)
            THEN
               IF Debugging
               THEN
                  printf ("too close to delete\n")
               END ;
               p := h ;
               h := h^.next
            ELSIF h^.t < currentTime
            THEN
               IF Debugging
               THEN
                  printf ("yes can delete\n")
               END ;
               IF p = NIL
               THEN
                  pastQ := NIL
               ELSE
                  p^.next := NIL
               END ;
               h := disposeAll (h) ;
               RETURN
            ELSE
               IF Debugging
               THEN
                  printf ("ignoring\n")
               END ;
               p := h ;
               h := h^.next
            END
         END
      END
   END
END updateTime ;


(*
   removeFromFutureQ -
*)

PROCEDURE removeFromFutureQ (n: hList) ;
VAR
   p, q: hList ;
BEGIN
   p := futureQ ;
   WHILE p#NIL DO
      q := p^.next ;
      IF (q#NIL) AND isSame (q, n)
      THEN
         p^.next := q^.next ;
	 disposeHList (q) ;
	 q := p^.next
      ELSE
         q := p ;
	 p := p^.next
      END
   END ;
   IF (futureQ#NIL) AND isSame (futureQ, n)
   THEN
      q := futureQ ;
      futureQ := futureQ^.next ;
      disposeHList (q)
   END
END removeFromFutureQ ;


(*
   addToPastQ - stores the history collision in reverse order.
                Highest time values (latest times are at the front).
*)

PROCEDURE addToPastQ (n: hList) ;
VAR
   p, q: hList ;
BEGIN
   IF pastQ = NIL
   THEN
      pastQ := n ;
      n^.next := NIL
   ELSIF n^.t > pastQ^.t
   THEN
      n^.next := pastQ ;
      pastQ := n ;
   ELSIF pastQ^.next = NIL
   THEN
      pastQ^.next := n ;
      n^.next := NIL
   ELSE
      p := pastQ ;
      q := p^.next ;
      IF q=NIL
      THEN
         HALT
      END ;
      WHILE (q#NIL) AND (n^.t <= q^.t) DO
         p := q ;
         q := q^.next
      END ;
      n^.next := q ;
      p^.next := n
   END
END addToPastQ ;


(*
   addToFutureQ -
*)

PROCEDURE addToFutureQ (n: hList) ;
VAR
   p, q: hList ;
BEGIN
   IF futureQ = NIL
   THEN
      futureQ := n ;
      n^.next := NIL
   ELSIF n^.t < futureQ^.t
   THEN
      n^.next := futureQ ;
      futureQ := n ;
   ELSE
      p := futureQ ;
      q := p^.next ;
      WHILE q#NIL DO
         IF n^.t < q^.t
         THEN
            n^.next := q ;
            p^.next := n ;
            RETURN
         END ;
         p := q ;
         q := q^.next
      END
   END
END addToFutureQ ;


(*
   isDuplicateFuture -
*)

PROCEDURE isDuplicateFuture (n: hList) : BOOLEAN ;
VAR
   h: hList ;
BEGIN
   h := futureQ ;
   (* in the futureQ time is increasing.  *)
   WHILE h # NIL DO
      IF isSame (n, h)
      THEN
         IF Debugging
         THEN
            printf ("found collision event on the futureq: ") ; dumpHlist (n)
         END ;
         RETURN TRUE
      ELSIF (h^.t > n^.t) AND (NOT nearSame (h^.t, n^.t))
      THEN
         (* h is now too far in the future to ever be considered the same.  *)
	 RETURN FALSE
      END ;
      h := h^.next
   END ;
   RETURN FALSE
END isDuplicateFuture ;


(*
   isDuplicatePast -
*)

PROCEDURE isDuplicatePast (n: hList) : BOOLEAN ;
VAR
   h: hList ;
BEGIN
   h := pastQ ;
   (* in the pastQ time is decreasing.  *)
   WHILE h # NIL DO
      IF isSame (n, h)
      THEN
         IF Debugging
         THEN
            printf ("found collision event on the pastq: ") ; dumpHlist (n)
         END ;
         RETURN TRUE
      ELSIF (h^.t < n^.t) AND (NOT nearSame (h^.t, n^.t))
      THEN
         (* h is now too far in the past to ever be considered the same.  *)
	 RETURN FALSE
      END ;
      h := h^.next
   END ;
   RETURN FALSE
END isDuplicatePast ;


BEGIN
   currentTime := 0.0 ;
   pastQ := NIL ;
   futureQ := NIL ;
   free := NIL
END history.
