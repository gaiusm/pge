(* Copyright (C) 2014 Free Software Foundation, Inc. *)
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

IMPLEMENTATION MODULE pgeif ;


FROM Storage IMPORT ALLOCATE ;
IMPORT deviceIf ;
IMPORT twoDsim ;
FROM deviceIf IMPORT useBuffer ;
FROM SYSTEM IMPORT THROW, ADDRESS, ADR ;
FROM Indexing IMPORT Index, InitIndex, GetIndice, PutIndice, HighIndice, IncludeIndiceIntoIndex, InBounds ;
FROM Fractions IMPORT Fract, putReal ;
FROM deviceIf IMPORT Colour ;
FROM libc IMPORT printf, exit ;
FROM roots IMPORT nearZero ;

CONST
   debugging = FALSE ;
   tracing   = FALSE ;

TYPE
   TypeOfDef = (colour, object) ;

   def = POINTER TO RECORD
                       type      : TypeOfDef ;
                       definition: CARDINAL ;
                    END ;


VAR
   listOfDefs: Index ;


(*
   trace -
*)

PROCEDURE trace (id: CARDINAL; name: ARRAY OF CHAR) : CARDINAL ;
BEGIN
   IF tracing
   THEN
      printf ("pgeif:  %s as id=%d\n", ADR (name), id)
   END ;
   RETURN id
END trace ;


(*
   Assert -
*)

PROCEDURE Assert (b: BOOLEAN) ;
BEGIN
   IF NOT b
   THEN
      printf ("assert failed\n");
      exit (1)
   END
END Assert ;


(*
   init - initialise the modules data structures.
*)

PROCEDURE init ;
BEGIN
   listOfDefs := InitIndex (1)
END init ;


(*
   newDef -
*)

PROCEDURE newDef (t: TypeOfDef; d: CARDINAL) : def ;
VAR
   f: def ;
BEGIN
   NEW (f) ;
   WITH f^ DO
      type := t ;
      definition := d
   END ;
   RETURN f
END newDef ;


(*
   addDef - adds a definition (type, d) into the global list and
            returns an index to the definition, id.
*)

PROCEDURE addDef (type: TypeOfDef; d: CARDINAL) : CARDINAL ;
VAR
   id: CARDINAL ;
   f : def ;
BEGIN
   f := newDef (type, d) ;
   IncludeIndiceIntoIndex (listOfDefs, f) ;
   id := HighIndice (listOfDefs) ;
   Assert (GetIndice (listOfDefs, id)=f) ;
   IF debugging
   THEN
      printf ("pgeif:  map (pgeid %d) onto (twoDsim %d)\n", id, d)
   END ;
   RETURN id
END addDef ;


(*
   lookupDef - return the definition of, d, and check its type
               is, t.
*)

PROCEDURE lookupDef (t: TypeOfDef; d: CARDINAL) : CARDINAL ;
VAR
   f: def ;
BEGIN
   IF debugging
   THEN
      printf ("inside lookupDef (d = %d)\n", d)
   END ;
   IF InBounds (listOfDefs, d)
   THEN
      f := GetIndice (listOfDefs, d) ;
      IF debugging
      THEN
         printf ("inside lookupDef (type = %d, definition = %d)\n", f^.type, f^.definition)
      END ;
      WITH f^ DO
         IF t=type
         THEN
            RETURN definition
         ELSE
	    IF debugging
            THEN
               printf ("throwing an exception in lookupDef (1)  t = %d, type = %d\n", t, type)
            END ;
            THROW (ORD (IncorrectType))
         END
      END
   ELSE
      IF debugging
      THEN
         printf ("throwing an exception in lookupDef (2)\n")
      END ;
      THROW (ORD (IdOutOfBounds))
   END
END lookupDef ;


(*
   rgb - make a colour object using red, blue and green components.
         The colour object is returned.
*)

PROCEDURE rgb (r, g, b: REAL) : CARDINAL ;
VAR
   rf, gf, bf: Fract ;
BEGIN
   rf := putReal (r) ;
   gf := putReal (g) ;
   bf := putReal (b) ;
   RETURN trace (addDef (colour, deviceIf.defineColour (rf, gf, bf)), "colour")
END rgb ;


(*
   white - returns the colour, white.
*)

PROCEDURE white () : CARDINAL ;
BEGIN
   RETURN trace (addDef (colour, deviceIf.white ()), "white")
END white ;


(*
   black - returns the colour, black.
*)

PROCEDURE black () : CARDINAL ;
BEGIN
   RETURN trace (addDef (colour, deviceIf.black ()), "black")
END black ;


(*
   red - returns the colour, red.
*)

PROCEDURE red () : CARDINAL ;
BEGIN
   RETURN trace (addDef (colour, deviceIf.red ()), "red")
END red ;


(*
   green - returns the colour, green.
*)

PROCEDURE green () : CARDINAL ;
BEGIN
   RETURN trace (addDef (colour, deviceIf.green ()), "green")
END green ;


(*
   blue - returns the colour, blue.
*)

PROCEDURE blue () : CARDINAL ;
BEGIN
   RETURN trace (addDef (colour, deviceIf.blue ()), "blue")
END blue ;


(*
   yellow - returns the colour, yellow.
*)

PROCEDURE yellow () : CARDINAL ;
BEGIN
   RETURN trace (addDef (colour, deviceIf.yellow ()), "yellow")
END yellow ;


(*
   purple - returns the colour, purple.
*)

PROCEDURE purple () : CARDINAL ;
BEGIN
   RETURN trace (addDef (colour, deviceIf.purple ()), "purple")
END purple ;


(*
   gravity - turn on gravity at: g m^2
*)

PROCEDURE gravity (g: REAL) ;
BEGIN
   twoDsim.gravity (g)
END gravity ;


(*
   check_range -
*)

PROCEDURE check_range (r: REAL; function, param: ARRAY OF CHAR) : REAL ;
BEGIN
   IF nearZero (r)
   THEN
      RETURN 0.0
   ELSIF nearZero (r-1.0)
   THEN
      RETURN 1.0
   ELSIF (r>0.0) AND (r<1.0)
   THEN
      RETURN r
   ELSE
      printf ("%s: parameter value %s is out of range (%g) (using 0.0)\n", ADR(function), ADR(param), r) ;
      RETURN 0.0
      (* THROW (ORD (ValueOutOfRange)) *)
   END
END check_range ;


(*
   get_xpos - returns the first point, x, coordinate of object.
*)

PROCEDURE get_xpos (id: CARDINAL) : REAL ;
BEGIN
   RETURN check_range (twoDsim.get_xpos (lookupDef (object, id)),
                       __FUNCTION__, "id")
END get_xpos ;


(*
   get_ypos - returns the first point, y, coordinate of object.
*)

PROCEDURE get_ypos (id: CARDINAL) : REAL ;
BEGIN
   RETURN check_range (twoDsim.get_ypos (lookupDef (object, id)),
                       __FUNCTION__, "id")
END get_ypos ;


(*
   get_xvel - returns the X velocity of object.
*)

PROCEDURE get_xvel (id: CARDINAL) : REAL ;
BEGIN
   RETURN twoDsim.get_xvel (lookupDef (object, id))
END get_xvel ;


(*
   get_yvel - returns the Y velocity of object.
*)

PROCEDURE get_yvel (id: CARDINAL) : REAL ;
BEGIN
   RETURN twoDsim.get_yvel (lookupDef (object, id))
END get_yvel ;


(*
   get_xaccel - returns the X accelaration of object.
*)

PROCEDURE get_xaccel (id: CARDINAL) : REAL ;
BEGIN
   RETURN twoDsim.get_xaccel (lookupDef (object, id))
END get_xaccel ;


(*
   get_yaccel - returns the Y accelaration of object.
*)

PROCEDURE get_yaccel (id: CARDINAL) : REAL ;
BEGIN
   RETURN twoDsim.get_yaccel (lookupDef (object, id))
END get_yaccel ;


(*
   put_xvel - assigns the X velocity of object.
*)

PROCEDURE put_xvel (id: CARDINAL; r: REAL) ;
BEGIN
   twoDsim.put_xvel (lookupDef (object, id), r)
END put_xvel ;


(*
   put_yvel - assigns the Y velocity of object.
*)

PROCEDURE put_yvel (id: CARDINAL; r: REAL) ;
BEGIN
   twoDsim.put_yvel (lookupDef (object, id), r)
END put_yvel ;


(*
   put_xaccel - assigns the X accelaration of object.
*)

PROCEDURE put_xaccel (id: CARDINAL; r: REAL) ;
BEGIN
   twoDsim.put_xaccel (lookupDef (object, id), r)
END put_xaccel ;


(*
   put_yaccel - assigns the Y accelaration of object.
*)

PROCEDURE put_yaccel (id: CARDINAL; r: REAL) ;
BEGIN
   twoDsim.put_yaccel (lookupDef (object, id), r)
END put_yaccel ;


(*
   draw_spring - draw spring, id, using colour, c, and a width, w.
*)

PROCEDURE draw_spring (id: CARDINAL; c: CARDINAL; w: REAL) ;
BEGIN
   twoDsim.draw_spring (lookupDef (object, id),
                        lookupDef (colour, c), w)
END draw_spring ;


(*
   end_spring - draw the objects at the end of the spring with
                colour, c, when the object comes to rest.
*)

PROCEDURE end_spring (id: CARDINAL; c: CARDINAL) ;
BEGIN
   twoDsim.end_spring (lookupDef (object, id),
                       lookupDef (colour, c))
END end_spring ;


(*
   mid_spring - when the spring reaches its rest point draw
                the objects connected by the spring with
                colour, c.
*)

PROCEDURE mid_spring (id: CARDINAL; c: CARDINAL) ;
BEGIN
   twoDsim.mid_spring (lookupDef (object, id),
                       lookupDef (colour, c))
END mid_spring ;


(*
   when_spring - when the spring, id, reaches, length call, func.
*)

PROCEDURE when_spring (id: CARDINAL; length: REAL; func: CARDINAL) ;
BEGIN
   twoDsim.when_spring (lookupDef (object, id), length, func)
END when_spring ;


(*
   apply_impulse - applies an impulse of magnitude along vector
                   [x, y] for object, id.
*)

PROCEDURE apply_impulse (id: CARDINAL; x, y: REAL; m: REAL) ;
BEGIN
   twoDsim.apply_impulse (lookupDef (object, id), x, y, m)
END apply_impulse ;


(*
   moving_towards - returns TRUE if object, id, is moving towards
                    a point x, y.
*)

PROCEDURE moving_towards (id: CARDINAL; x, y: REAL) : BOOLEAN ;
BEGIN
   RETURN twoDsim.moving_towards (lookupDef (object, id), x, y)
END moving_towards ;


(*
   set_colour - sets colour of object, id, to, c.
*)

PROCEDURE set_colour (id: CARDINAL; c: CARDINAL) ;
BEGIN
   twoDsim.set_colour (lookupDef (object, id),
                       lookupDef (colour, c))
END set_colour ;


(*
   box - place a box in the world at (x0,y0),(x0+i,y0+j)
*)

PROCEDURE box (x0, y0, i, j: REAL; c: CARDINAL) : CARDINAL ;
VAR
   k: REAL ;
BEGIN
   x0 := check_range (x0, __FUNCTION__, "x0") ;
   y0 := check_range (y0, __FUNCTION__, "y0") ;
   k := check_range (x0+i, __FUNCTION__, "x0+i") ;
   k := check_range (y0+j, __FUNCTION__, "y0+j") ;
   RETURN trace (addDef (object, twoDsim.box (x0, y0, i, j,
                                              lookupDef (colour, c))),
                 "box")
END box ;


(*
   poly3 - place a triangle in the world at:
           (x0,y0),(x1,y1),(x2,y2)
*)

PROCEDURE poly3 (x0, y0, x1, y1, x2, y2: REAL; c: CARDINAL) : CARDINAL ;
VAR
   k: REAL ;
BEGIN
   x0 := check_range (x0, __FUNCTION__, "x0") ;
   y0 := check_range (y0, __FUNCTION__, "y0") ;
   x1 := check_range (x1, __FUNCTION__, "x1") ;
   y1 := check_range (y1, __FUNCTION__, "y1") ;
   x2 := check_range (x2, __FUNCTION__, "x2") ;
   y2 := check_range (y2, __FUNCTION__, "y2") ;

   RETURN trace (addDef (object,
                         twoDsim.poly3 (x0, y0, x1, y1, x2, y2,
                                        lookupDef (colour, c))),
                 "poly3")
END poly3 ;


(*
   poly4 - place a rectangle in the world at:
           (x0,y0),(x1,y1),(x2,y2),(x3,y3)
*)

PROCEDURE poly4 (x0, y0, x1, y1, x2, y2, x3, y3: REAL; c: CARDINAL) : CARDINAL ;
VAR
   k: REAL ;
BEGIN
   x0 := check_range (x0, __FUNCTION__, "x0") ;
   y0 := check_range (y0, __FUNCTION__, "y0") ;
   x1 := check_range (x1, __FUNCTION__, "x1") ;
   y1 := check_range (y1, __FUNCTION__, "y1") ;
   x2 := check_range (x2, __FUNCTION__, "x2") ;
   y2 := check_range (y2, __FUNCTION__, "y2") ;
   x3 := check_range (x3, __FUNCTION__, "x3") ;
   y3 := check_range (y3, __FUNCTION__, "y3") ;

   RETURN trace (addDef (object,
                         twoDsim.poly4 (x0, y0, x1, y1, x2, y2, x3, y3,
                                        lookupDef (colour, c))),
                 "poly4")
END poly4 ;


(*
   poly5 - place a pentagon in the world at:
           (x0,y0),(x1,y1),(x2,y2),(x3,y3),(x4,y4)
*)

PROCEDURE poly5 (x0, y0, x1, y1, x2, y2, x3, y3, x4, y4: REAL; c: CARDINAL) : CARDINAL ;
VAR
   k: REAL ;
BEGIN
   x0 := check_range (x0, __FUNCTION__, "x0") ;
   y0 := check_range (y0, __FUNCTION__, "y0") ;
   x1 := check_range (x1, __FUNCTION__, "x1") ;
   y1 := check_range (y1, __FUNCTION__, "y1") ;
   x2 := check_range (x2, __FUNCTION__, "x2") ;
   y2 := check_range (y2, __FUNCTION__, "y2") ;
   x3 := check_range (x3, __FUNCTION__, "x3") ;
   y3 := check_range (y3, __FUNCTION__, "y3") ;
   x4 := check_range (x4, __FUNCTION__, "x4") ;
   y4 := check_range (y4, __FUNCTION__, "y4") ;

   RETURN trace (addDef (object,
                         twoDsim.poly5 (x0, y0, x1, y1, x2, y2, x3, y3, x4, y4,
                                        lookupDef (colour, c))),
                 "poly5")
END poly5 ;


(*
   poly6 - place a hexagon in the world at:
           (x0,y0),(x1,y1),(x2,y2),(x3,y3),(x4,y4),(x5,y5)
*)

PROCEDURE poly6 (x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5: REAL; c: CARDINAL) : CARDINAL ;
VAR
   k: REAL ;
BEGIN
   x0 := check_range (x0, __FUNCTION__, "x0") ;
   y0 := check_range (y0, __FUNCTION__, "y0") ;
   x1 := check_range (x1, __FUNCTION__, "x1") ;
   y1 := check_range (y1, __FUNCTION__, "y1") ;
   x2 := check_range (x2, __FUNCTION__, "x2") ;
   y2 := check_range (y2, __FUNCTION__, "y2") ;
   x3 := check_range (x3, __FUNCTION__, "x3") ;
   y3 := check_range (y3, __FUNCTION__, "y3") ;
   x4 := check_range (x4, __FUNCTION__, "x4") ;
   y4 := check_range (y4, __FUNCTION__, "y4") ;
   x5 := check_range (x5, __FUNCTION__, "x5") ;
   y5 := check_range (y5, __FUNCTION__, "y5") ;

   RETURN trace (addDef (object,
                         twoDsim.poly6 (x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5,
                                        lookupDef (colour, c))),
                 "poly6")
END poly6 ;


(*
   mass - specify the mass of an object and return the, id.
*)

PROCEDURE mass (id: CARDINAL; m: REAL) : CARDINAL ;
VAR
   ti: CARDINAL ;
BEGIN
   ti := trace (twoDsim.mass (lookupDef (object, id), m), "mass") ;
   RETURN id
END mass ;


(*
   get_mass - returns the mass of a circle or polygon object.
*)

PROCEDURE get_mass (id: CARDINAL) : REAL ;
BEGIN
   RETURN twoDsim.get_mass (lookupDef (object, id))
END get_mass ;


(*
   get_gravity - returns the gravity of a circle or polygon object.
*)

PROCEDURE get_gravity (id: CARDINAL) : REAL ;
BEGIN
   RETURN twoDsim.get_gravity (lookupDef (object, id))
END get_gravity ;


(*
   set_gravity - sets the per object gravity, g, to a circle or
                 polygon object.
*)

PROCEDURE set_gravity (id: CARDINAL; g: REAL) ;
BEGIN
   twoDsim.set_gravity (lookupDef (object, id), g)
END set_gravity ;


(*
   fix - fix the object to the world.
*)

PROCEDURE fix (id: CARDINAL) : CARDINAL ;
VAR
   ti: CARDINAL ;
BEGIN
   ti := trace (twoDsim.fix (lookupDef (object, id)), "fix") ;
   RETURN id
END fix ;


(*
   unfix - unfix the object from the world.
*)

PROCEDURE unfix (id: CARDINAL) : CARDINAL ;
VAR
   ti: CARDINAL ;
BEGIN
   ti := trace (twoDsim.unfix (lookupDef (object, id)), "unfix") ;
   RETURN id
END unfix ;


(*
   is_fixed - returns TRUE if the object, id, is fixed.
*)

PROCEDURE is_fixed (id: CARDINAL) : BOOLEAN ;
BEGIN
   RETURN twoDsim.isFixed (lookupDef (object, id))
END is_fixed ;


(*
   spring - join object, id1, and, id2, with a string of defined
            by hooks constant, k, the spring is at rest if it has
            length, l.  If l < 0 then the game engine considers
            the spring to naturally be at rest for the distance
            between id1 and id2.
*)

PROCEDURE spring (id1, id2: CARDINAL; k, d, l: REAL) : CARDINAL ;
VAR
   ti, id: CARDINAL ;
BEGIN
   printf ("before twoDsim.spring\n") ;
   ti := twoDsim.spring (lookupDef (object, id1), lookupDef (object, id2), k, d, l) ;
   printf ("before addDef\n") ;
   id := addDef (object, ti) ;
   printf ("before lookupDef\n") ;
   Assert (ti = lookupDef (object, id)) ;
   printf ("before trace\n") ;
   RETURN trace (id, "spring")
END spring ;


(*
   circle - adds a circle to the world.  Center
            defined by: x0, y0 radius, radius.
*)

PROCEDURE circle (x0, y0, radius: REAL; c: Colour) : CARDINAL ;
VAR
   ti, id: CARDINAL ;
BEGIN
   ti := twoDsim.circle (x0, y0, radius, lookupDef (colour, c)) ;
   id := addDef (object, ti) ;
   Assert (ti = lookupDef (object, id)) ;
   RETURN trace (id, "circle")
END circle ;


(*
   velocity - give an object, id, a velocity, vx, vy.
*)

PROCEDURE velocity (id: CARDINAL; vx, vy: REAL) : CARDINAL ;
VAR
   ti: CARDINAL ;
BEGIN
   IF debugging
   THEN
      printf ("inside velocity (id = %d)\n", id)
   END ;
   ti := trace (twoDsim.velocity (lookupDef (object, id), vx, vy),
                "velocity") ;
   RETURN id
END velocity ;


(*
   accel - give an object, id, an acceleration, ax, ay.
*)

PROCEDURE accel (id: CARDINAL; ax, ay: REAL) : CARDINAL ;
VAR
   ti: CARDINAL ;
BEGIN
   ti := twoDsim.accel (lookupDef (object, id), ax, ay) ;
   RETURN id
END accel ;


(*
   rotate - rotates object with a angular velocity, angle.
*)

PROCEDURE rotate (id: CARDINAL; angle: REAL) : CARDINAL ;
VAR
   ti: CARDINAL ;
BEGIN
   ti := twoDsim.rotate (lookupDef (object, id), angle) ;
   RETURN id
END rotate ;


(*
   fps - set frames per second.
*)

PROCEDURE fps (f: REAL) ;
BEGIN
   twoDsim.fps (f)
END fps ;


PROCEDURE get_time () : REAL ;
BEGIN
   RETURN twoDsim.getTime ()
END get_time ;


PROCEDURE is_collision () : BOOLEAN ;
BEGIN
   RETURN twoDsim.isCollision ()
END is_collision ;


PROCEDURE is_frame () : BOOLEAN ;
BEGIN
   RETURN twoDsim.isFrame ()
END is_frame ;


PROCEDURE is_function () : BOOLEAN ;
BEGIN
   RETURN twoDsim.isFunction ()
END is_function ;


(*
   is_spring - returns TRUE if the next event is a spring event.
*)

PROCEDURE is_spring () : BOOLEAN ;
BEGIN
   RETURN twoDsim.isSpring ()
END is_spring ;


(*
   create_function_event - creates a function event at time, t,
                           in the future.  Function id is called
                           with parameter, param.
*)

PROCEDURE create_function_event (t: REAL; id, param: CARDINAL) ;
BEGIN
   twoDsim.createFunctionEvent (t, id, param)
END create_function_event ;


(*
   time_until - returns the relative time from now until the next event.
*)

PROCEDURE time_until () : REAL ;
BEGIN
   RETURN twoDsim.timeUntil ()
END time_until ;


(*
   skip_until - advances time for, t, units or until the next event is reached.
                The amount of time skipped is returned.  This function will not
                skip past the next event.
*)

PROCEDURE skip_until (t: REAL) : REAL ;
BEGIN
   RETURN twoDsim.skipTime (t)
END skip_until ;


(*
   process_event - advance time to the next event and then
                   process the event.
*)

PROCEDURE process_event ;
BEGIN
   twoDsim.processEvent
END process_event ;


(*
   rm - delete this object from the simulated world.
        The same id is returned.
*)

PROCEDURE rm (id: CARDINAL) : CARDINAL ;
VAR
   ti: CARDINAL ;
BEGIN
   ti := twoDsim.rm (lookupDef (object, id)) ;
   RETURN id
END rm ;


(*
   use_buffer - use the buffer device to record the output frames.
*)

PROCEDURE use_buffer ;
VAR
   t: REAL ;
BEGIN
   deviceIf.useBuffer () ;
   t := time_until ()
END use_buffer ;


(*
   empty_fbuffer - empty the frame buffer.
*)

PROCEDURE empty_fbuffer ;
BEGIN
   twoDsim.emptyFbuffer
END empty_fbuffer ;


(*
   empty_cbuffer - empty the colour buffer.
*)

PROCEDURE empty_cbuffer ;
BEGIN
   twoDsim.emptyCbuffer
END empty_cbuffer ;


(*
   batch - use the batch device to record the output frames.
*)

PROCEDURE batch ;
BEGIN
   deviceIf.useGroff ()
END batch ;


(*
   use_time_delay - should the frame buffer include the time delay command?
*)

PROCEDURE use_time_delay (on: BOOLEAN) ;
BEGIN
   twoDsim.useTimeDelay (on)
END use_time_delay ;


(*
   draw_collision - turn on drawing of the actual collision frame
                    and the prediction frame.
*)

PROCEDURE draw_collision (actual, predict: BOOLEAN) ;
BEGIN
   twoDsim.drawCollisionFrames (actual, predict)
END draw_collision ;


(*
   set_collision_colour - when two objects collide they will both be draw using
                          colour, c.
*)

PROCEDURE set_collision_colour (c: CARDINAL) ;
BEGIN
   twoDsim.setCollisionColour (lookupDef (colour, c))
END set_collision_colour ;


(*
   dump_world - dump a list of all objects and their characteristics.
*)

PROCEDURE dump_world ;
BEGIN
   twoDsim.dumpWorld
END dump_world ;


(*
   check_objects - perform a check to make sure that all non fixed
                   objects have a mass and return TRUE if this is
                   the case.
*)

PROCEDURE check_objects () : BOOLEAN ;
BEGIN
   RETURN twoDsim.checkObjects ()
END check_objects ;


(*
   l2h - translate a twoDsim, id, to the pgeid.
*)

PROCEDURE l2h (id: CARDINAL) : CARDINAL ;
VAR
   d   : def ;
   i, h: CARDINAL ;
BEGIN
   h := HighIndice (listOfDefs) ;
   i := 1 ;
   WHILE i<=h DO
      d := GetIndice (listOfDefs, i) ;
      IF (d^.definition=id) AND (d^.type=object)
      THEN
         RETURN i
      END ;
      INC(i)
   END ;
   RETURN 0
END l2h ;


(*
   h2l - translate a pgeif, id, to the twoDsim.
*)

PROCEDURE h2l (id: CARDINAL) : CARDINAL ;
VAR
   d: def ;
BEGIN
   d := GetIndice (listOfDefs, id) ;
   RETURN d^.definition
END h2l ;


(*
   nofree - do not free, a.
*)

PROCEDURE nofree (a: ADDRESS) : ADDRESS ;
BEGIN
   (* do nothing *)
   RETURN a
END nofree ;


(*
   fps - set frames per second.
*)

PROCEDURE fps (f: REAL) ;
BEGIN
   twoDsim.fps (f)
END fps ;


BEGIN
   init
END pgeif.
