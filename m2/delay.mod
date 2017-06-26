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

IMPLEMENTATION MODULE delay ;


FROM Selective IMPORT Timeval, GetTimeOfDay, InitTime, GetTime, InitSet, KillSet,
                      SetOfFd, SetTime, Select, FdZero ;

CONST
   M          = 1000000 ;
   debugDelay = 0 ;

VAR
   noDelay    : BOOLEAN ;
   delayT     : Timeval ;
   sec, usec  : CARDINAL ;
   firstSec   : CARDINAL ;
   actualFps  : CARDINAL ;
   totalFrames: CARDINAL ;


(*
   getActualFPS - return the actual frames per second.
*)

PROCEDURE getActualFPS () : CARDINAL ;
BEGIN
   RETURN actualFps
END getActualFPS ;


(*
   nextFrameTime - calculates the time of the next frame, given the frames
                   per second.  This should be called once for every frame.
*)

PROCEDURE nextFrameTime (fps: CARDINAL) ;
VAR
   dt: CARDINAL ;
BEGIN
   INC(totalFrames) ;
   IF fps=0
   THEN
      noDelay := TRUE
   ELSE
      IF GetTimeOfDay(delayT)=0
      THEN
      END ;
      GetTime(delayT, sec, usec) ;
      IF firstSec=0
      THEN
         firstSec := sec ;
         actualFps := fps
      ELSIF firstSec<sec
      THEN
         actualFps := totalFrames DIV (sec-firstSec)
      END ;
      dt := M DIV fps ;
      INC(usec, dt) ;
      IF usec>M
      THEN
         DEC(usec, M) ;
         INC(sec)
      END ;
      INC(sec, debugDelay)
   END
END nextFrameTime ;


(*
   isEarlier - 
*)

PROCEDURE isEarlier (s1, u1, s2, u2: CARDINAL) : BOOLEAN ;
BEGIN
   IF s1<s2
   THEN
      RETURN TRUE
   ELSIF s1>s2
   THEN
      RETURN FALSE
   ELSE
      RETURN u1<u2
   END
END isEarlier ;


(*
   wait - waits until 
*)

PROCEDURE wait ;
VAR
   r, w, e: SetOfFd ;
   u, s   : CARDINAL ;
BEGIN
   IF NOT noDelay
   THEN
      IF GetTimeOfDay(delayT)=0
      THEN
      END ;
      GetTime(delayT, s, u) ;
      IF isEarlier(s, u, sec, usec)
      THEN
         DEC(sec, s) ;
         IF usec<u
         THEN
            usec := (M+usec)-u ;
            IF sec>0
            THEN
               DEC(sec)
            ELSE
               HALT  (* algorithmic error.. *)
            END
         ELSE
            DEC(usec, u)
         END ;
         SetTime(delayT, sec, usec) ;
         
         r := InitSet() ;
         w := InitSet() ;
         e := InitSet() ;
         FdZero(r) ;
         IF Select(0, r, w, e, delayT)=0
         THEN
            (* do nothing *)
         END ;
         r := KillSet(r) ;
         w := KillSet(w) ;
         e := KillSet(e)
      END
   END
END wait ;


BEGIN
   delayT := InitTime(0, 0) ;
   firstSec := 0 ;
   totalFrames := 0
END delay.
