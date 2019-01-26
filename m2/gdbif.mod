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

IMPLEMENTATION MODULE gdbif ;


FROM libc IMPORT printf, getpid, sleep ;
FROM FIO IMPORT File, OpenToWrite, Close, WriteString, WriteLine, IsNoError ;
FROM NumberIO IMPORT IntToStr ;


VAR
   invoked,
   mustWait: BOOLEAN ;


(*
   connectSpin - breakpoint placeholder.
*)

PROCEDURE connectSpin ;
BEGIN
   (* do nothing, its purpose is to allow gdb to set breakpoints here.  *)
END connectSpin ;


(*
   sleepSpin - waits for the boolean variable mustWait to become FALSE.
               It sleeps for a second between each test of the variable.
*)

PROCEDURE sleepSpin ;
BEGIN
   IF mustWait
   THEN
      gdbinit ;
      printf ("process %d is waiting for you to:\n", getpid ());
      printf ("(gdb) attach %d\n", getpid ());
      printf ("(gdb) break connectSpin\n");
      printf ("(gdb) print finishSpin()\n");
      REPEAT
         sleep (1);
         printf (".")
      UNTIL NOT mustWait ;
      printf ("ok continuing\n");
      connectSpin
   END
END sleepSpin ;


(*
   finishSpin - sets boolean mustWait to FALSE.
*)

PROCEDURE finishSpin ;
BEGIN
   mustWait := FALSE
END finishSpin ;


(*
   gdbinit - create a ".gdbinit" file in the current directory.
*)

PROCEDURE gdbinit ;
VAR
   file  : File ;
   pidstr: ARRAY [0..7] OF CHAR ;
BEGIN
   file := OpenToWrite (".gdbinit") ;
   IF IsNoError (file)
   THEN
      WriteString (file, "attach ") ;
      IntToStr (getpid (), 0, pidstr) ;
      WriteString (file, pidstr) ;
      WriteLine (file) ;
      WriteString (file, "set mustWait=0") ; WriteLine (file) ;
      WriteString (file, "fin") ; WriteLine (file) ;
      Close (file)
   END
END gdbinit ;


BEGIN
   mustWait := TRUE
END gdbif.
