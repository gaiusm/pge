#!/usr/bin/env python

import pgeif
import pygame
import sys
import struct
import time
import math
from pygame.locals import *


colour_t, box_t, circle_t, spring_t, fb_box_t, fb_circle_t, fb_text_t = range (7)
id2ob = {}
ob2id = {}
batch_d, pyg_d = range (2)
device = None
opened = False
output = None
lastDelay = 0.0
debugging = False
foreground= []
background= []
colours = []
levels = {}
resolution = None
fullscreen = False
screen_initialised = False
pyevent2func = {}
call = {}
idTOcol = {}
nextFrame = 1
screen = None
backcanvas = None
program_name = 'pge'
version_number = '2.0'
Black = (0, 0, 0)
framesPerSecond = 100.0
slow_down_factor = 1.0
allowed_events = [USEREVENT+1]
id2func = {}
idcount = 0
_record = False
font_size = None
font = None


#
#  _printf - keeps C programmers happy :-)
#

def _printf (format, *args):
    print str (format) % args,


#
#  _debugf - _printf when debugging is True
#

def _debugf (format, *args):
    global debugging

    if debugging:
        print str (format) % args,

#
#  _errorf - generate an error associated with pge and raise an exception.
#

def _errorf (format, *args):
    m = str (format) % args
    sys.stdout.write ("pge: " + m)
    raise Exception (m)
    sys.exit (1)

#
#  _internalf - generate an internal error and raise an exception.
#

def _internalf (format, *args):
    m = str (format) % args
    sys.stdout.write ("internal error in pge: " + m)
    raise Exception (m)
    sys.exit (1)

class _myfile:
    def __init__ (self, c):
        self.contents = c
        self.length = len (self.contents)
        self.pos = 0
        _debugf ("length %d bytes", self.length)
    def read (self, n):
        # print "read called for", n, "bytes", self.length-self.pos, "available"
        if self.pos + n <= self.length:
            b = self.contents[self.pos:self.pos+n]
            self.pos += n
            return b
        else:
            _printf ("unexpected eof reached in frame %d\n", nextFrame)
            sys.exit (1)
    def close (self):
        pass
    def left (self):
        return self.length-self.pos

def _emit_short (s):
    global output

    output.write (struct.pack ('!H', s))

def _emit_card (c):
    global output

    output.write (struct.pack ('!I', c))

def _emit_double (d):
    global output

    d = (float) (d)
    output.write (struct.pack ('d', d))

def _emit_fract (f):
    global output

    if f == 0:
        output.write (struct.pack ('B', 0))
    elif f == 1:
        output.write (struct.pack ('B', 1))
    elif f < 1.0:
        output.write (struct.pack ('B', 2))
        output.write (struct.pack ('!QQ', f*10000.0, 10000.0))
    else:
        w = int (f)
        f -= w
        output.write (struct.pack ('B', 3))
        output.write (struct.pack ('!QQQ', w, f*10000.0, 10000.0))


#
#  object - the class of objects in the 2D world.  An object can either
#           be a colour, circle, polygon, spring or text.  A text
#           object can not exist in level 0.  Objects are drawn
#           from lowest level to highest level.  Only objects in
#           level 0 are processed by the physics engine.
#           All other levels are eye candy.
#

class object:
    def __init__ (self, t, o, c = None, level = None):
        self.deleted = False
        self.type = t
        self.o = o
        self.fixed = False
        self.param = None
        self.kg = None
        self.collisionWith = []
        self.collisionp = None
        self.w = None
        if c == None:
            self.c = self
        else:
            self.c = c
        self.level = level

    def _id (self):
        return self.o

    def _get_3_colour (self):
        global idTOcol

        self._check_colour ()
        i = pgeif.h2l (self._get_pgeif_colour ())
        if idTOcol.has_key (i):
            return idTOcol[i]
        _internalf ("3 colour triple should have been defined")

    def _get_pgeif_colour (self):
        self._check_colour ()
        return self.o[-1]

    def _draw (self):
        global screen, device
        if self.type == fb_box_t:
            if device == pyg_d:
                c = self.get_colour ()._get_3_colour ()
                # print c
                x = (int) (self.o[0] * resolution[0])
                y = (int) (self.o[1] * resolution[1])
                w = (int) ((self.o[2] - self.o[0]) * resolution[0])
                h = (int) ((self.o[5] - self.o[1]) * resolution[1])
                pygame.draw.rect (screen, c, (x, flip (y), w, h))
            else:
                self._emit_fill_polygon ()
        elif self.type == fb_circle_t:
            if device == pyg_d:
                c = self.get_colour ()._get_3_colour ()
                # print c
                x = (int) (self.o[0] * resolution[0])
                y = (int) (self.o[1] * resolution[1])
                r = (int) (self.o[2] * resolution[0])
                pygame.draw.circle (screen, c, (x, flip (y)), r, 0)
            else:
                self._emit_fill_circle ()
        elif self.type == colour_t:
            pass
        elif self.type == fb_text_t:
            if device == pyg_d:
                c = self.get_colour ()._get_3_colour ()
                font = get_font (self.o[3])
                t = font.render (self.o[2], True, c)
                textpos = t.get_rect ()
                textpos.top = screen.get_rect ().bottom - (int) (resolution[1] * self.o[1])
                textpos.left = screen.get_rect ().left + (int) (resolution[0] * self.o[0])
                screen.blit (t, textpos)

    def _emit_fill_circle (self):
        output.write (struct.pack ("3s", "dC"))
        _emit_fract (self.o [0])  #  x pos
        _emit_fract (self.o [1])  #  y pos
        _emit_fract (self.o [2])  #  radius
        _emit_short (self.o [3])  #  colour
        # print "_emit_fill_circle, colour is ", self.o [3], self.o [0], self.o [1], self.o [2]

    def _emit_fill_polygon (self):
        output.write (struct.pack ("3s", "dP"))
        n = (len (self.o)-1)/2
        _emit_short (n)
        ier = iter (self.o[:-1])
        # print self.o
        for x in ier:
            _emit_fract (x)
            _emit_fract (next (ier))
        _emit_short (self.o [-1])

    def _name (self):
        if self.type == colour_t:
            return "colour"
        elif self.type == box_t:
            return "box"
        elif self.type == circle_t:
            return "circle"
        else:
            _printf ("fatal error, object not recognised\n")
            sys.exit (1)

    #
    #  velocity - Pre-condition:  an circle or polygon object
    #             which is not fixed and exists at level 0.
    #             Post-condition:  assign the velocity (vx, vy)
    #             to this object.
    #
    def velocity (self, vx, vy):
        self._check_type ([box_t, circle_t], "assign a velocity to a")
        self._check_not_fixed ("assign a velocity")
        self._check_not_deleted ("a velocity")
        # print "velocity for object", self.o, vx, vy
        self.o = self._check_same (pgeif.velocity (self.o, vx, vy))
        return self

    #
    #  accel - Pre-condition:  an circle or polygon object
    #          which is not fixed and exists at level 0.
    #          Post-condition:  assign the accel (vx, vy)
    #          to this object.
    #
    def accel (self, ax, ay):
        self._check_type ([box_t, circle_t], "assign an acceleration to a")
        self._check_not_fixed ("assign an acceleration")
        self._check_not_deleted ("an acceleration")
        self.o = self._check_same (pgeif.accel (self.o, ax, ay))
        return self

    #
    #  fix - Pre-condition:  the object is either a circle or polygon
    #        which exists in level 0.
    #        Post-condition:   mark this object as fixed to its initial
    #        position.
    #
    def fix (self):
        self._check_type ([box_t, circle_t], "fix a")
        self._check_not_deleted (" a fixed position")
        self._check_no_mass ("cannot fix " + self._name () + " as it has a mass")
        self.fixed = True
        self.o = self._check_same (pgeif.fix (self.o))
        # print "fix", self.o
        return self

    #
    #  mass - Pre-condition:  the object is either a circle or polygon
    #         which exists in level 0.  The object must not be fixed.
    #         Post-condition:  object is given mass, m.
    #
    def mass (self, m):
        self._check_type ([box_t, circle_t], "assign a mass to a")
        self._check_not_fixed ("assign a mass")
        self._check_not_deleted (" a mass")
        if m is None:
            _errorf ("cannot give value None as the mass\n")
        self.kg = m
        self.o = self._check_same (pgeif.mass (self.o, m))
        # print "mass", self.o
        return self

    #
    #  apply_impulse - Pre-condition:  the object is either a circle or polygon
    #                  which exists in level 0.  The object must not be fixed.
    #                  Post-condition:  the object is given an impulse along vector,
    #                  unit_vec, with a, magnitude.
    #                  unit_vec is a list of two elements [x, y]
    #                  magnitude is a float.
    #
    def apply_impulse (self, unit_vec, magnitude):
        self._check_type ([box_t, circle_t], "assign an impulse to a")
        self._check_not_fixed ("assign an impulse")
        self._check_not_deleted (" an impulse")
        if (magnitude is None) or (unit_vec is None):
            return
        pgeif.apply_impulse (self.o, unit_vec[0], unit_vec[1], magnitude)
        return self

    #
    #  on_collision_with - Pre-condition:  the object is either a circle or polygon
    #                      which exists in level 0.
    #                      Post-condition:  when this object collides
    #                      with any object in the list, another,
    #                      then function, p, is called.
    #                      The parameter, another, is a list of objects.
    #                      p must be a function which receives two parameters
    #                      an object and an event.
    #
    def on_collision_with (self, another, p):
        if debugging:
            print "ok registering call back", p, another
        self.collisionp = p
        self.collisionWith = another
        return self

    #
    #  on_collision - Pre-condition:  the object is either a circle or polygon
    #                 which exists in level 0.
    #                 Post-condition:  when this object collides call function, p.
    #                 p is a function with two parameters, o and e.
    #                 o is this object.
    #                 e is the event.
    #
    def on_collision (self, p):
        self.on_collision_with ([], p)
        return self

    def _check_type (self, legal, message):
        if not self.type in legal:
            _errorf ("you cannot %s %s object\n", message, self._type_name ())

    def _check_not_fixed (self, message):
        if self.fixed:
            _errorf ("object %s is fixed, you cannot %s\n", self._type_name (), message)

    def _check_colour (self):
        if self.type != colour_t:
            _errorf ("object is expected to be a colour\n")

    def _param_colour (self, message):
        if self.type != colour_t:
            _errorf (message)

    #
    #  rm - Pre-condition:  the object can be a circle, polygon or text at any level.
    #       Post-condition:  the object is removed.
    #
    def rm (self):
        if not self.deleted:
            # _printf ("calling pgeif.rm\n")
            if self.level == 0:
                self.o = pgeif.rm (self.o)
            else:
                _sub (self, self.level)
            self.deleted = True
            # _printf ("returned from pgeif.rm\n")

    def _check_not_deleted (self, message):
        if self.deleted:
            _errorf ("object has been deleted and now it is being given " + message)

    def _check_no_mass (self, message):
        if self.kg != None:
            _errorf (message + "\n")

    def _check_same (self, o):
        if o == self.o:
            return o
        _errorf ("internal error, object %d does not match self.o = %d\n", o, self.o)

    def _collision (self, between, e):
        if debugging:
            print "collision seen, between:", between
        if self.collisionWith == []:
            if self.collisionp != None:
                if debugging:
                    print "before collisionp"
                self.collisionp (self, e)
                if debugging:
                    print "after collisionp"
        else:
            found = False
            for c in self.collisionWith:
                for b in between:
                    if c == b:
                        found = True
            if found and (self.collisionp != None):
                self.collisionp (self, e)

    #
    #  get_param - Pre-condition:  self is a polygon or circle object.
    #              Post-condition:  returns user data given to this object.
    #
    def get_param (self):
        return self.param

    #
    #  set_param - Pre-condition:  self is a polygon or circle object.
    #              Post-condition:  assigns value as the user data to this object.
    #
    def set_param (self, value):
        self.param = value
        return self

    #
    #  set_width - Pre-condition:  self is a polygon or circle object.
    #              Post-confition:  assigns an overall width value to an object.
    #              This value is not used by the physics engine.
    #              It is only present for user convenience.
    #
    def set_width (self, value):
        self.w = value

    #
    #  get_width - Pre-condition:  self is a polygon or circle object which has
    #              had a user defined width set.  Post-condition:  returns the
    #              overall width value for this object.
    #
    def get_width (self):
        self._check_type ([box_t, circle_t], "get the width")
        return self.w

    #
    #  get_mass - Pre-condition:  self is a polygon or circle object.
    #             Post-condition:  return the mass of this object.
    #
    def get_mass (self):
        return self.kg

    #
    #  get_colour - Pre-condition:  self is a polygon or circle object.
    #               Post-condition:  return the colour of this object.
    #
    def get_colour (self):
        return self.c

    #
    #  set_colour - Pre-condition:  self is a polygon or circle object.
    #               Post-condition:  this object will be displayed in colour, c.
    #
    def set_colour (self, c):
        self._check_type ([box_t, circle_t, fb_box_t, fb_circle_t], "set_colour")
        c._param_colour ("first parameter to set_colour is expected to be a colour")
        if self.type in [box_t, circle_t]:
            pgeif.set_colour (self.o, c._get_pgeif_colour ())
        else:
            self.o = self.o [:-1]
            self.o += [c._get_pgeif_colour ()]
        self.c = c
        return self

    #
    #  get_unit_coord - Pre-condition:  object must be a circle.
    #                   Post-condition:  return a list [x, y] representing the
    #                   coordinate center of this object.  Each x, y
    #                   value will be between 0.0 and 1.0.
    #
    def get_unit_coord (self):
        self._check_type ([circle_t], "get the unit coordinate")
        return [self.get_xpos (), self.get_ypos ()]

    #
    #  get_xpos - Pre-condition:  object must be a circle or polygon.
    #             Post-condition:  return the x position of this object.
    #             The value will be between 0.0 and 1.0.
    #
    def get_xpos (self):
        self._check_type ([box_t, circle_t], "get the xpos")
        return pgeif.get_xpos (self.o)

    #
    #  get_ypos - Pre-condition:  object must be a circle or polygon.
    #             Post-condition:  return the y position of this object.
    #             The value will be between 0.0 and 1.0.
    #
    def get_ypos (self):
        self._check_type ([box_t, circle_t], "get the ypos")
        return pgeif.get_ypos (self.o)

    #
    #  get_xvel - Pre-condition:  object must be a circle or polygon.
    #             Post-condition:  return the x velocity of this object.
    #
    def get_xvel (self):
        self._check_type ([box_t, circle_t], "get the xvel")
        return pgeif.get_xvel (self.o)

    #
    #  get_yvel - Pre-condition:  object must be a circle or polygon.
    #             Post-condition:  return the y velocity of this object.
    #
    def get_yvel (self):
        self._check_type ([box_t, circle_t], "get the yvel")
        return pgeif.get_yvel (self.o)

    #
    #  get_xaccel - Pre-condition:  object must be a circle or polygon.
    #               Post-condition:  return the x accel of this object.
    #
    def get_xaccel (self):
        self._check_type ([box_t, circle_t], "get the xaccel")
        return pgeif.get_xaccel (self.o)

    #
    #  get_yaccel - Pre-condition:  object must be a circle or polygon.
    #               Post-condition:  return the y accel of this object.
    #
    def get_yaccel (self):
        self._check_type ([box_t, circle_t], "get the yaccel")
        return pgeif.get_yaccel (self.o)

    #
    #  put_xvel - Pre-condition:  object must be a circle or polygon.
    #             Post-condition:  assigns a float, f, as the x velocity of this
    #             object.
    #
    def put_xvel (self, f):
        # print "put_xvel on a", self._name ()
        self._check_type ([box_t, circle_t], "put the xvel")
        return pgeif.put_xvel (self.o, f)

    #
    #  put_yvel - Pre-condition:  object must be a circle or polygon.
    #             Post-condition:  assigns a float, f, as the y velocity of this
    #             object.
    #
    def put_yvel (self, f):
        self._check_type ([box_t, circle_t], "put the yvel")
        return pgeif.put_yvel (self.o, f)

    #
    #  put_xaccel - Pre-condition:  object must be a circle or polygon.
    #               Post-condition:  assigns a float, f, as the x
    #               acceleration of this object.
    #
    def put_xaccel (self, f):
        self._check_type ([box_t, circle_t], "put the xaccel")
        return pgeif.put_xaccel (self.o, f)

    #
    #  put_xaccel - Pre-condition:  object must be a circle or polygon.
    #               Post-condition:  assigns a float, f, as the y
    #               acceleration of this object.
    #
    def put_yaccel (self, f):
        self._check_type ([box_t, circle_t], "put the yaccel")
        return pgeif.put_yaccel (self.o, f)

    #
    #  moving_towards - Pre-condition:  object must be a non fixed
    #                   circle or polygon.
    #                   Post-condition:  returns True if this object
    #                   is moving towards point [x, y].
    #                   x and y must be in the range of 0.0 and 1.0.
    #
    def moving_towards (self, x, y):
        self._check_type ([box_t, circle_t], "test moving_towards")
        if self.fixed:
            return False
        return pgeif.moving_towards (self.o, x, y)

    #
    #  draw - draw a spring using colour, c, and a width, w.
    #         It is drawn under the objects it connects.
    #         The spring object is returned.
    #
    def draw (self, c, w):
        self._check_not_deleted ("spring no longer exists")
        self._check_type ([spring_t], "expected a spring")
        c._param_colour ("the second parameter to draw is expected to be a colour")
        print self.o, c._get_pgeif_colour (), w
        pgeif.draw_spring (self.o, c._get_pgeif_colour (), w)
        return self

#
#  _colspace - convert a float value 0.0..1.0 into integer 0..255.
#

def _colspace (f):
    return (int)(f * 255.0)


#
#  rgb - Pre-condition:  None.
#        Post-condition:  create a colour object from the red, green, blue triple.
#        The r, g, b, values must between 0.0 and 1.0.
#

def rgb (r, g, b):
    global idTOcol

    # print "in rgb (", r, g, b, ")"
    c = pgeif.rgb (float(r), float(g), float(b))
    # print "after pgeif.rgb ->", c
    o = object (colour_t, [float(r), float(g), float(b), c])
    o._check_colour ()
    c = pgeif.h2l (c)
    idTOcol[c] = (_colspace (r), _colspace (g), _colspace (b))
    # print "define colour triple as:", idTOcol[c]
    return o

#
#  white - Pre-condition:  None.
#          Post-condition:  return a colour object representing the colour white.
#

def white ():
    c = pgeif.white ()
    o = object (colour_t, [1.0, 1.0, 1.0, c])
    c = pgeif.h2l (c)
    idTOcol[c] = (255, 255, 255)
    return o

#
#  _register - register a colour pair id:ob in two dictoraries
#              so we can look either up given the other.
#

def _register (id, ob):
    global id2ob, od2id

    _debugf ("registering %d\n", id)
    id2ob[id] = ob
    ob2id[ob] = id


#
#  text - place text string, s, at position [x, y] in colour, c.
#         The size will be in font size and placed in the foreground or
#         background depending upon level.  You are not allowed
#         to place text in level zero.
#

def text (x, y, s, c, size, level):
    global device, screen
    c._param_colour ("fourth parameter to text is expected to be a colour")
    if level == 0:
        _errorf ("not allowed to place in level 0")
    else:
        ob = object (fb_text_t, [x, y, s, size, c._get_pgeif_colour ()], c, level)
        _add (ob, level)
    return ob

#
#  box - create a box at position, [x, y].  x and y have the range 0.0 to 1.0.
#        w and h are the width and height and are in the range 0.0 to 1.0.
#        c is a colour object.
#        level is optional, if it is not present it defaults to zero.
#        Otherwise the level determines whether it exists in the foreground
#        or background.
#

def box (x, y, w, h, c, level = 0):
    # print "box:", x, y, w, h, c, level
    c._param_colour ("fifth parameter to box is expected to be a colour")
    if level == 0:
        id = pgeif.box (x, y, w, h, c._get_pgeif_colour ())
        # print "box colour =", c, c._get_pgeif_colour ()
        ob = object (box_t, id, c, level)
        ob.set_width (w)
        _debugf ("box ")
        _register (id, ob)
    else:
        ob = object (fb_box_t, [x, y, x+w, y, x+w, y+h, x+w, y+h, x, y+h, c._get_pgeif_colour ()], c, level)
        # print "box colour =", c, c._get_pgeif_colour ()
        _add (ob, level)
    return ob


#
#  poly3 - create a triangle at position, [x0, y0], [x1, y1], [x2, y2] all
#          values have the range 0.0 to 1.0.
#          c is a colour object.
#          level is optional, if it is not present it defaults to zero.
#          Otherwise the level determines whether it exists in the foreground
#          or background.
#

def poly3 (x0, y0, x1, y1, x2, y2, c, level = 0):
    c._param_colour ("seventh parameter to box is expected to be a colour")
    if level == 0:
        id = pgeif.poly3 (x0, y0, x1, y1, x2, y2, c._get_pgeif_colour ())
        ob = object (box_t, id, c, level)
        _debugf ("poly3 ")
        _register (id, ob)
    else:
        ob = object (fb_box_t, [x0, y0, x1, y1, x2, y2, c._get_pgeif_colour ()], c, level)
        _add (ob, level)
    return ob

#
#  poly4 - create a polygon of four vertices at position, [x0, y0],
#          [x1, y1], [x2, y2], [x3, y3] all
#          values have the range 0.0 to 1.0.
#          c is a colour object.
#          level is optional, if it is not present it defaults to zero.
#          Otherwise the level determines whether it exists in the foreground
#          or background.
#          The coordinates must either be given in clockwise or anticlockwise
#          order.
#

def poly4 (x0, y0, x1, y1, x2, y2, x3, y3, c, level = 0):
    c._param_colour ("seventh parameter to box is expected to be a colour")
    if level == 0:
        id = pgeif.poly4 (x0, y0, x1, y1, x2, y2, x3, y3, c._get_pgeif_colour ())
        ob = object (box_t, id, c, level)
        _debugf ("poly3 ")
        _register (id, ob)
    else:
        ob = object (fb_box_t, [x0, y0, x1, y1, x2, y2, x3, y3, c._get_pgeif_colour ()], c, level)
        _add (ob, level)
    return ob


#
#  _add - adds an object at foreground/background, level.
#         A level value of > 0 will be placed into the
#         foreground.
#         A level value of < 0 will be placed into the
#         background.
#

def _add (ob, level):
    global foreground, background, levels

    if level > 0:
        if not (level in foreground):
            foreground += [level]
            foreground.sort ()
    else:
        if not (level in background):
            background += [level]
            background.sort ()

    if levels.has_key (level):
        levels[level] += [ob]
    else:
        levels[level] = [ob]
    # print levels[level]

#
#  _sub - removes the object placed by the function _add.
#

def _sub (ob, level):
    global foreground, background

    if levels.has_key (level):
        levels[level].remove (ob)

    if level > 0:
        f = []
        for l in foreground:
            if levels.has_key (l):
                f += [l]
        foreground = f
        foreground.sort ()
    else:
        b = []
        for l in background:
            if levels.has_key (l):
                b += [l]
        background = b
        background.sort ()


#
#  spring - place a spring of at rest length, l, and Hook's
#           value of, k, between object ob1 and object ob2.
#           The objects, ob1, and, ob2, must be either
#           a circle or a polygon.  A spring only exists at
#           level 0 (in the physics engine).
#           If, l, is omitted then it is assummed that the
#           spring starts at rest between, ob1, and, ob2.
#

def spring (ob1, ob2, k, l = None):
    ob1._check_not_deleted ("a spring attachment")
    ob2._check_not_deleted ("a spring attachment")
    ob1._check_type ([box_t, circle_t], "creating a spring, first parameter")
    ob2._check_type ([box_t, circle_t], "creating a spring, second parameter")
    if l == None:
        l = -1
    print "before pgeif.spring"
    id = pgeif.spring (ob1.o, ob2.o, k, l)
    print "after pgeif.spring"
    ob = object (spring_t, id, None, 0)
    _register (id, ob)
    return ob


#
#  circle - place a circle at coordinate (x, y)
#           The circle has a radius, r, and is filled with colour, c.
#           If the level == 0 it is placed into the physics engine.
#           A level < 0 is placed into the background.
#           A level > 0 is placed into the foreground.
#

def circle (x, y, r, c, level = 0):
    c._param_colour ("fourth parameter to box is expected to be a colour")
    if level == 0:
        id = pgeif.circle (x, y, r, c._get_pgeif_colour ())
        # print "circle id =", id
        # _debugf ("circle ")
        ob = object (circle_t, id, c, level)
        _register (id, ob)
    else:
        # print "circle, colour =", c
        # print "pge: colour", c._get_pgeif_colour ()
        ob = object (fb_circle_t, [x, y, r, c._get_pgeif_colour ()], c, level)
        _add (ob, level)
    return ob


#
#  _unpackFract - returns three integers:  w, n, d
#                 representing fraction.
#

def _unpackFract (s):
    b = s[0]
    v = struct.unpack ("B", b)[0]

    if v == 0:
        return (0, 0, 0)
    elif v == 1:
        return (1, 0, 0)
    elif v == 2:
        b = s[1:17]
        r = struct.unpack('!QQ', b)
        return (0, r[0], r[1])
    else:
        b = s[1:33]
        return struct.unpack('!QQQ', b)


#
#  _unpackReal
#

def _unpackReal (s):
    if len (s) >= 8:
        return struct.unpack ('d', s[:8])[0]
    else:
        _printf ("insufficient data passed to _unpackReal\n")


def _unpackCard (s):
    if len (s) >= 4:
        return struct.unpack ('!I', s[:4])[0]
    else:
        _printf ("insufficient data passed to _unpackCard\n")


def _unpackCardPair (s):
    if len (s) >= 8:
        return [struct.unpack ('!I', s[:4])[0],
                struct.unpack ('!I', s[4:8])[0]]
    else:
        _printf ("insufficient data passed to _unpackCardPair (%d bytes)\n", len (s))

def _unpackIdPair (s):
    p = _unpackCardPair (s)
    p[0] = pgeif.l2h (p[0])
    p[1] = pgeif.l2h (p[1])
    return p

def _unpackPoint (s):
    if len (s) >= 16:
        return [_unpackReal (s[:8]), _unpackReal (s[8:])]
    else:
        _printf ("insufficient data passed to _unpackPoint\n")

#
#  _draw_foreground - draws all the foreground objects in order.
#

def _draw_foreground ():
    # print "draw foreground", foreground
    if foreground != []:
        for l in foreground:
            # print "drawing level", l
            for o in levels[l]:
                o._draw ()

#
#  _draw_background - draws all the foreground objects in order.
#

def _draw_background ():
    # print "draw background", background
    if background != []:
        for l in background:
            # print "drawing level", l
            for o in levels[l]:
                o._draw ()

#
#  _draw
#

def _draw ():
    _draw_background ()
    _draw_foreground ()
    _doFlipBuffer ()


no_event, frame_event, collision_event, function_event, spring_event, final_event = range (6)

#
# the event class is used by the user through call back functions.  In particular
# the user can find out the collision_between two objects, cancel a timer event or
# query whether a timer event was cancelled.
#

class event:
    def __init__ (self, t, d, l):
        _debugf ("creating event (data is %d bytes)\n", l)
        self._type = t
        self._edata = d
        self._elength = l
        self._fdata = None
        self._flength = 0
        self._cData = None
        self._clength = 0
        self._cancelled = False
        # the following are the event data values
        self.__point = None
        self.__between = None
        self.__etime = 0.0
        self.__etype = 0
        self.__kind = 0
        self.__id = None
        if self._edata == None:
            _debugf ("final or timer event\n")
        else:
            _debugf ("*********** current time is %f ***********\n", pgeif.get_time ())
            self.__etime = _unpackReal (self._edata) # 8 bytes REAL
            _debugf ("*********** event time is %f *************\n", self.__etime)
            if t == collision_event:
                self.__etype = _unpackCard (self._edata[8:12]) # 4 bytes etype
                self.__point = _unpackPoint (self._edata[12:])
                self.__between = _unpackIdPair (self._edata[28:])
                # print "assigning between values", self.__between

                # etype == 0 is a draw frame event
                # etype == 1 two circles colliding
                if self.__etype == 2 or self.__etype == 3:
                    # circle/polygon collision or polygon/polygon collision
                    self.__kind = _unpackCard (self._edata[36:])
                _debugf ("collision event created which indicates a collision in %f seconds\n", self.__etime)
            elif t == frame_event:
                _debugf ("frame event %d in %f seconds\n", t, self.__etime)
            elif t == function_event:
                _debugf ("function event %d in %f seconds\n", t, self.__etime)
                self.__etype = _unpackCard (self._edata[8:12]) # 4 bytes etype
                self.__id = _unpackCard (self._edata[12:16]) # 4 bytes id
            elif t == spring_event:
                _debugf ("spring event %d in %f seconds\n", t, self.__etime)
                self.__etype = _unpackCard (self._edata[8:12]) # 4 bytes etype
                self.__id = _unpackCard (self._edata[12:16]) # 4 bytes id
                self.__kind = _unpackCard (self._edata[16:20]) # 4 bytes id
            else:
                _printf ("unknown event %d in %f seconds\n", t, self.__etime)
    def _set_frame_contents (self, data, length):
        self._fData = data
        self._flength = length
    def _set_colour_contents (self, data, length):
        self._cData = data
        self._clength = length
    def _process (self):
        global id2func
        # _printf ("current time %f, moving time forward until this event: %f\n", pgeif.get_time (), self.__etime)
        pgeif.skip_until (self.__etime)
        # _printf ("current time is now %f\n", pgeif.get_time ())
        _debugf ("_flush_delay\n")
        _flush_delay ()
        _debugf ("about to call process_event\n")
        pgeif.process_event ()
        _debugf ("find out which event\n")
        if self._type == frame_event:
            self._handle_frame_buffer ()
        elif self._type == collision_event:
            _debugf ("collision event seen, in %f seconds\n", self.__etime)
            # pgeif.skip_until (self.__etime)
            self._handle_frame_buffer ()
            _collision (self._between (), self)
        elif self._type == function_event:
            # print "_process found timer_event", self.__id
            i = self.__id
            if id2func.has_key (i):
                # print "function", i, "about to be called"
                id2func[i] (self)
                # print "function", i, "finished"
            else:
                # print "function", i, "has been cancelled"
                pass
    def _handle_frame_buffer (self):
        cData = pgeif.get_cbuf ()
        _debugf ("cData len = %d\n", len (cData))
        self._set_colour_contents (cData, len (cData))
        fData = pgeif.get_fbuf ()
        _debugf ("fData len = %d\n", len (fData))
        self._set_frame_contents (fData, len (fData))
        _draw_frame (self._cData, self._clength,
                    self._fData, self._flength)
        pgeif.empty_fbuffer ()
        pgeif.empty_cbuffer ()
    def _check (self, et):
        if self._type != et:
            _printf ("fatal error, unexpected event type\n")
            sys.exit (1)
    def _between (self):
        global id2ob

        self._check (collision_event)
        # returns the two object ids of the colliding objects
        _debugf ("id0 = %d, id1 = %d\n", self.__between[0], self.__between[1])
        ob1 = id2ob[self.__between[0]]
        ob2 = id2ob[self.__between[1]]
        return [ob1, ob2]
    def _get_time (self):
        return self.__etime
    #
    #  collision_between - Pre-condition:  event object must a collision event.
    #                      Post-condition:  returns a list of two objects which
    #                      are in collision.
    #
    def collision_between (self):
        return self._between ()
    #
    #  cancel - Pre-condition:  event must be a timer event.
    #           Post-condition:  timer event is cancelled.
    #
    def cancel (self):
        self._cancelled = True
    #
    #  was_cancelled - Pre-condition:  event must be a timer event.
    #                  Post-condition:  returns True if this event was cancelled.
    #
    def was_cancelled (self):
        return self._cancelled
    #
    #  get_timer_id - Pre-condition:  event must be a timer event
    #                 Post-condition:  timer id is returned.
    #
    def get_timer_id (self):
        return self.__id

#
#  _get_next_event - returns a next event object which has
#                    contains any relevant information from
#                    the physics engine.
#

def _get_next_event ():
    global device
    _debugf ("_get_next_event\n")
    _setDefaultDevice ()
    if pgeif.is_collision ():
        _debugf ("pgeif.is_collision\n")
        _debugf ("pgeif.get_ebuf\n")
        eData = pgeif.get_ebuf ()
        _debugf ("event (...\n")
        return event (collision_event, eData, len (eData))
    elif pgeif.is_frame ():
        _debugf ("pgeif.is_frame\n")
        _debugf ("pgeif.get_ebuf\n")
        eData = pgeif.get_ebuf ()
        # print "testing -> ", _unpackReal (eData)
        return event (frame_event, eData, len (eData))
    elif pgeif.is_function ():
        # _printf ("pgeif.is_function\n")
        eData = pgeif.get_ebuf ()
        return event (function_event, eData, len (eData))
    elif pgeif.is_spring ():
        _debugf ("pgeif.is_spring\n")
        _debugf ("pgeif.get_ebuf\n")
        eData = pgeif.get_ebuf ()
        _debugf ("event (...\n")
        return event (spring_event, eData, len (eData))
    else:
        _printf ("fatal error: unknown event type (terminating simulation)\n")
        sys.exit (1)
        return event (no_event, None, 0)

#
#  _collision - call the _collision method for every object
#               in the, between, list.
#

def _collision (between, event):
    for o in between:
        o._collision (between, event)

#
#  _process - call the _process method for in the object, pe.
#

def _process (pe):
    pe._process ()

#
#  _add_relative - adds, r a list [time, event]
#                  to the pge_event_queue.  It maintains
#                  their position using a relative ordered queue.
#

def _add_relative (r):
    global pge_event_queue

    if pge_event_queue == []:
        # catch the easy case early
        pge_event_queue = [r]
        return

    abs_time = r[0]
    acc_time = pge_event_queue[0][0]
    if abs_time < acc_time:
        # at the front of the queue
        pge_event_queue[0][0] -= abs_time
        pge_event_queue = [r] + pge_event_queue
        return

    i = 0
    while True:
        if i == len (pge_event_queue)-1:
            # end of queue
            abs_time -= acc_time
            pge_event_queue += [[abs_time, r[1]]]
            return
        i += 1
        if acc_time + pge_event_queue[i][0] < abs_time:
            acc_time += pge_event_queue[i][0]
        else:
            # r needs to be before i
            r = [abs_time - acc_time, r[1]]
            pge_event_queue = pge_event_queue[:i] + [r] + pge_event_queue[i:]
            # and alter relative value of, i
            acc_time += pge_event_queue[i][0]
            if i < len (pge_event_queue)-1:
                pge_event_queue = pge_event_queue[:i] + [[acc_time-abs_time, pge_event_queue[i][1]]] + pge_event_queue[i+1:]
            else:
                pge_event_queue = pge_event_queue[:i] + [[acc_time-abs_time, pge_event_queue[i][1]]]
            return

pge_event_queue = []

#
#  _display_element - debugging function to display an event element.
#

def _display_element (e, t):
    print "[", e[0], "ms ",
    if e[1]._type == frame_event:
        print "displayframe",
    elif e[1]._type == collision_event:
        print "collision",
    elif e[1]._type == function_event:
        print "timer",
    else:
        print "final",
    print " at", e[0] + (int) (t * 1000.0), "ms",
    print "], ",

#
#  _display_event_queue - debugging function to display the entire event queue.
#

def _display_event_queue (q):
    if q == []:
        print "event queue is empty"
    else:
        print "event queue: "
        t = pgeif.get_time ()
        for e in q:
            _display_element (e, t)
            t += e[1]._get_time ()
        print ""

prev_event_time = 0.0

#
#  _post_event - places an event, e, at time, t, onto the event queue.
#

def _post_event (e, t):
    global pge_event_queue, debugging, prev_event_time
    if t != -1:
        t = (int) (t * 1000.0)
        _add_relative ([t, e])
        if debugging:
            _display_event_queue (pge_event_queue)
        c = pge_event_queue[0][0] + (int) (pgeif.get_time () * 1000.0)
        # if c < prev_event_time:
        #   _printf ("clock skew detected\n")
        prev_event_time = c
    return e

#
#  _wait_for_event - waits until an event occurs.  If a queued event
#                    exists remove it.  It also checks the pygame event
#                    queue.
#

def _wait_for_event ():
    global pge_event_queue, slow_down_factor, device, _record, debugging

    if debugging:
        print "_wait_for_event, pge_event_queue ="
        _display_event_queue (pge_event_queue)
    if device == pyg_d:
        pygame.event.set_allowed (None)
        pygame.event.set_allowed (allowed_events)

    if pge_event_queue == []:
        return [pygame.event.wait()] + pygame.event.get()

    ms = pge_event_queue[0][0]
    if _record:
        _record_time (ms)
    if ms == 0:
        # adding [None] to the list indicates an immediate pge event
        # we obtain all pygame events to avoid starvation of input
        return pygame.event.get() + [None]

    # _printf ("setting timer in pygame to %d ms\n", ms)
    pygame.time.set_timer (USEREVENT+1, (int) (ms * slow_down_factor))
    return [pygame.event.wait()] + pygame.event.get()

#
#  _finish_event - creates and returns a final_event.
#

def _finish_event ():
    return event (final_event, None, 0)

#
#  at_time - informs the physics engine to create a call to function, p, at
#            time, t, in the future.  It returns a integer reference for the
#            timed function.
#            Pre-condition:  t is a time seconds (float) in the future.
#                            p, is a function which takes a single parameter
#                            the event.
#            Post-condition:  function p is placed into the timer list
#                             and a timer id (integer) is returned.
#

def at_time (t, p):
    global idcount, id2func, slow_down_factor
    idcount += 1
    pgeif.create_function_event (t / slow_down_factor, idcount)
    id2func[idcount] = p
    return idcount

#
#  at_cancel - Pre-condition:  the integer reference for the timed function.
#              Post-condition:  cancel the timed function.
#

def at_cancel (i):
    global id2func
    if id2func.has_key (i):
        del id2func[i]
    else:
        error ("at_cancel cannot delete function %d as it no longer exists\n", i)

#
#  record - record the game.  A file output.raw will be created which
#           can be post processed by pgeplayback.
#           Pre-condition:  None.
#           Post-condition:  the record flag is set and the game will
#                            be recorded.
#

def record ():
    global _record
    _record = True

#
#  _draw_frame - draws a frame on the chosen device.
#

def _draw_frame (cdata, clength, fdata, flength):
    global device

    if device == pyg_d:
        _pyg_draw_frame (cdata, clength, fdata, flength)
    else:
        _batch_draw_frame (cdata, clength, fdata, flength)

#
#  _pyg_draw_frame - draws a frame on the pygame display.
#

def _pyg_draw_frame (cdata, clength, fdata, flength):
    global nextFrame, call, _record

    # _printf ("enter _pyg_draw_frame: in frame %d  (length = %d bytes)\n", nextFrame, flength+clength)
    # _printf ("drawing background\n")
    if _record:
        _begin_record_frame (cdata, clength, fdata, flength)
    elif flength > 0:
        _draw_background ()
    f = _myfile (cdata + fdata)
    while f.left () >= 3:
        header = struct.unpack ("3s", f.read (3))[0]
        header = header[:2]
        if call.has_key (header):
            f = call[header] (f)
        else:
            print "not understood header =", header
            sys.exit (1)
    # _printf ("drawing foreground\n")
    if flength > 0:
        _draw_foreground ()
    if _record:
        _end_record_frame ()
    if flength > 0:
        _doFlipBuffer ()  # flipping the buffer for an empty frame looks ugly

    # print "end of draw"
    nextFrame += 1
    _debugf ("moving onto frame %d\n", nextFrame)


def _check_opened ():
    global opened, output

    if not opened:
        opened = True
        output = open ("output.raw", "w")


def _begin_record_frame (cdata, clength, fdata, flength):
    global opened, output, nextFrame

    _check_opened ()
    output.write (struct.pack ("3s", "fn")) # frame note
    _emit_card (nextFrame)
    if clength > 0:
        _debugf ("writing colour data length = %d bytes\n", clength)
        output.write (cdata)
    if flength > 0:
        _draw_background ()
        _debugf ("writing frame data length = %d bytes\n", flength)
        output.write (fdata)
    else:
        pass
        # _printf ("length of zero!!\n")
        # sys.exit (2)


def _end_record_frame ():
    output.write (struct.pack ("3s", "fb")) # flip buffer


#
#  _record_time - records the time delay.
#

def _record_time (ms):
    global output, slow_down_factor
    ms = ((float) (ms)) * slow_down_factor / 1000.0
    # print "recording time", ms
    output.write (struct.pack ("3s", "sl")) # sleep
    _emit_double (ms)

#
#  _batch_draw_frame - records the frame.
#

def _batch_draw_frame (cdata, clength, fdata, flength):
    global opened, output, nextFrame

    _debugf ("_batch_draw_frame\n")
    if fdata is None:
        _printf ("no data in the frame!\n")
        sys.exit (1)
    if not opened:
        opened = True
        output = open ("output.raw", "w")
        nextFrame = 1
    _begin_record_frame (cdata, clength, fdata, flength)
    _end_record_frame ()
    nextFrame += 1


#
#  gravity - Pre-condition:  None.
#            Post-condition:  turn on pge world gravity, if parameter
#            is missing the default of 9.81ms^2 is used.
#

def gravity (value=-9.81):
    pgeif.gravity (value)


#
#  get_font - Pre-condition:  None.
#             Post-condition:  return the font corresponding
#             to size pixels height.
#

def get_font (size):
    global font, font_size
    if size == font_size:
        return font
    else:
        font_size = size
        font = pygame.font.Font (None, font_size)
        return font

#
#  _init_screen - initialise the pygame screen.
#

def _init_screen ():
    global resolution, fullscreen, screen_initialised, backcanvas, screen, program_name, version_number

    if not screen_initialised:
        pygame.init ()
        if fullscreen:
            screen = pygame.display.set_mode (resolution, FULLSCREEN)
        else:
            screen = pygame.display.set_mode (resolution)
        screen_initialised = True
        pygame.display.set_caption (program_name + ' ' + version_number)
        backcanvas = pygame.Surface (screen.get_size ())
        backcanvas = backcanvas.convert ()
        backcanvas.fill (Black)


#
#  register_handler - Pre-condition:  None.
#                     Post-condition:  call, function, if any event in pyeventlist
#                     occurs.
#

def register_handler (function, pyeventlist):
    global pyevent2func, allowed_events
    for e in pyeventlist:
        pyevent2func[e] = function
    allowed_events += pyeventlist

#
#  deregister_handler - Pre-condition:  None.
#                       Post-condition:  remove the handlers for pyeventlist.
#

def deregister_handler (pyeventlist):
    global pyevent2func, allowed_events
    for e in pyeventlist:
        del pyevent2func[e]
        allowed_events.remove (e)


#
# runpy - Pre-condition:  all objects have been initialised correctly in the 2D world.
#         Post-condition:  runs pge for time, t, seconds and also
#         process the pygame events the objects appear in the Pygame screen.
#

def runpy (t=-1):
    global pge_event_queue

    _init_screen ()
    pgeif.use_time_delay (False)
    cData = pgeif.get_cbuf ()
    fData = pgeif.get_fbuf ()
    _check_opened ()
    _draw_frame (cData, len (cData), fData, len (fData))
    pgeif.empty_fbuffer ()
    pgeif.empty_cbuffer ()
    if pge_event_queue == []:
        # no events yet, so collect the next from the physics engine
        ev = _get_next_event ()
        nev = _post_event (ev, ev._get_time ())
    # always add the final event which is the only way to finish the while loop
    fin = _post_event (_finish_event (), t)
    while True:
        for e in _wait_for_event ():
            if (e == None) or (e.type == USEREVENT+1):
                # immediate pge event pending or user event has fired
                # take the event off queue
                pe = pge_event_queue [0][1]
                pge_event_queue = pge_event_queue [1:]
                if pe == fin:
                    # the finish event, we're done and out of here
                    return
                _process (pe)
                ev = _get_next_event ()
                nev = _post_event (ev, ev._get_time ())
            elif pyevent2func.has_key (e.type):
                pyevent2func[e.type] (e)


#
#  runbatch - Pre-condition:  all objects have been initialised correctly in the 2D world.
#             Post-condition:  runs pge for time, t.  If t < 0.0 then simulate for 30.0 seconds max.
#             Nothing is rendered visually, but the graphics can be directed to a file using the
#             record function.
#

def runbatch (t):
    if t < 0.0:
        t = 30.0
    _debugf ("runbatch (%f)\n", t)
    if pgeif.check_objects ():
        cData = pgeif.get_cbuf ()
        fData = pgeif.get_fbuf ()
        _draw_frame (cData, len (cData), fData, len (fData))
        pgeif.empty_fbuffer ()
        pgeif.empty_cbuffer ()
        nev = _get_next_event ()
        acc = 0.0
        while acc+nev._get_time () < t:
            old = acc
            acc = acc + nev._get_time ()
            delay (nev._get_time ())
            if int(acc) != int(old):
                _printf ("%d/%d seconds completed %d%%\n", int (acc), int (t), int (acc*100.0/t))
            _process (nev)
            nev = _get_next_event ()
    else:
        _errorf ("'runbatch' detected a non fixed object has no mass, all moving objects must have a mass\n")

#
#  display_set_mode - Pre-condition: this must be called before pge.run.
#                                    The parameter is a list [x, y].
#                                    Current limitation the y parameter
#                                    is overwritten by the x value.
#                     Post-condition:  the resolution will be used when pge.run.
#                                      is called.
#

def display_set_mode (r):
    global resolution
    r[1] = r[0]
    resolution = r

#
#  display_fullscreen - Pre-condition:  this must be called before pge.run.
#                       Post-condition:  configure the Pygame to use fullscreen.
#

def display_fullscreen (b):
    global fullscreen
    fullscreen = b

#
#  fps - Pre-condition:  this must be called before pge.run.
#        Post-condition:  the game engine will render the world at, f, frames per second.
#

def fps (f):
    global framesPerSecond
    framesPerSecond = f


#
#  run - Pre-condition:  all objects and any screen resolution must be configured.
#        Post-condition:  runs pge for time, t, seconds and also
#        process the pygame events
#

def run (t=-1):
    global device

    _setDefaultDevice ()
    pgeif.fps (framesPerSecond)
    if device == pyg_d:
        runpy (t)
    else:
        runbatch (t)


def _setDevice (d):
    global device

    if device == None:
        device = d
        if device == pyg_d:
            pygame.init ()
        pgeif.use_buffer ()
    else:
        _printf ("cannot change device once pge has started\n")


def _setDefaultDevice ():
    global device

    if device == None:
        device = pyg_d
        pgeif.use_buffer ()

#
#  batch - Pre-condition:  None.
#          Post-condition:  configures pge to run in batch mode, without any display
#          and without any pygame.  No input events are allowed in this mode.
#

def batch ():
    _setDevice (batch_d)


#
#  interactive - Pre-condition:  None.
#                Post-condition:  configures pge to use pygame and it allows interactivity from
#                the python pygame event queue.
#

def interactive ():
    _setDevice (pyg_d)


#
#  finish_record - Pre-condition:  record must have been called.
#                  Post-condition:  finish recording the game and flush the record file.
#

def finish_record ():
    global output, opened
    if opened:
        output.close ()
        opened = False

def _load_sound (name):
    class _NoneSound:
        def play(self):
            pass
    if not pygame.mixer or not pygame.mixer.get_init():
        return _NoneSound()
    try:
        sound = pygame.mixer.Sound(name)
    except pygame.error, message:
        print 'cannot load sound file:', name
        return _NoneSound()
    return sound


def play (name):
    global output

    _flush_delay ()
    if device == pyg_d:
        s = _load_sound (name)
        s.play ()
    else:
        output.write (struct.pack ("3s", "ps"))
        output.write (name)
        output.write ('\0')


#
#  message - write out text to the output.
#

def message (text):
    output.write (struct.pack ("3s", "ms"))
    output.write (text)


#
#  turn the drawing of collision frames on or off.
#
#        actual:   determines whether an extra frame is generated
#                  at the time of actual collision.
#        predict:  draws a frame predicting the next collision.
#                  It will show the points predicted to collide.
#

def draw_collision (actual, predict):
    pgeif.draw_collision (actual, predict)


#
#  collision_colour - if draw_collision is called and
#                     with its first parameter, actual = True, then
#                     the objects in collision will have colour, c.
#

def collision_colour (c):
    c._param_colour ("first parameter to collision_colour is expected to be a colour")
    pgeif.set_collision_colour (c._get_pgeif_colour ())


#
#  dump_world - this is a debugging routine which allows users to
#               obtain a textual dump of the objects in the
#               physics engine.
#

def dump_world ():
    pgeif.dump_world ()


#
#  _flush_delay - write out or implement the collected delay time.
#

def _flush_delay ():
    global lastDelay

    if lastDelay > 0.0:
        _debugf ("delay of %f\n", lastDelay)
        if device == pyg_d:
            time.sleep (lastDelay)
        else:
            output.write (struct.pack ("3s", "sl"))
            output.write (struct.pack ("d", lastDelay))
        lastDelay = 0.0


#
#  delay - introduce a delay for, t.
#

def delay (t):
    global lastDelay
    lastDelay += t


#
#  slow_down - slow down the physics engine by a factor of, t.
#

def slow_down (t):
    global slow_down_factor
    slow_down_factor = t


def _readShort (f):
    b = f.read (2)
    c = struct.unpack ('!H', b)[0]
    return f, c


def _toCol (f):
    return toFloat (f)*255

#
#  _readFract - returns three integers:  w, n, d
#               representing fraction.
#

def _readFract (f):
    b = f.read (1)
    v = struct.unpack ("B", b)[0]

    if v == 0:
        return f, (0, 0, 0)
    elif v == 1:
        return f, (1, 0, 0)
    elif v == 2:
        b = f.read (8*2)
        r = struct.unpack('!QQ', b)
        return f, (0, r[0], r[1])
    else:
        b = f.read (8*3)
        return f, struct.unpack('!QQQ', b)

#
#  _mults -
#

def _mults (s, f):
    if s == 0:
        return 0
    if f[1] == 0 or f[2] == 0:
        return f[0]*s
    return f[0]+f[1]*s/f[2]


def toFloat (f):
    if f[1] == 0 or f[2] == 0:
        return float(f[0])
    return float(f[0]) + float(f[1])/float(f[2])


def _doRegisterColour (f):
    global idTOcol, debugging

    f, c = _readShort (f)
    f, rf = _readFract (f)
    f, gf = _readFract (f)
    f, bf = _readFract (f)
    if debugging:
        print rf, gf, bf
    r = _toCol (rf)
    g = _toCol (gf)
    b = _toCol (bf)
    idTOcol[c] = (r, g, b)
    return f

def _doExit (f):
    _debugf ("doExit called\n")
    sys.exit (0)
    return f

#
#  _readColourRaw - returns the file and colour id (short).
#

def _readColourRaw (f):
    f, c = _readShort (f)
    return f, c


#
#  _readColour - returns the file and colour triple.
#

def _readColour (f):
    f, c = _readColourRaw (f)
    _debugf ("colour value %d\n", c)
    col = idTOcol[c]
    return f, col


#
#  drawFillPolygon -
#

def _doDrawFillPolygon (f):
    global screen, debugging

    _debugf ("doDrawFillPolygon\n")
    f, n = _readShort (f)
    l = []
    for i in range (n):
        f, xf = _readFract (f)
        f, yf = _readFract (f)
        if debugging:
            print xf, yf,
        x = _mults (resolution[0], xf)
        y = _mults (resolution[1], yf)
        l += [[x, flip (y)]]

    f, c = _readColour (f)
    if debugging:
        print "drawFillPolygon (colour =", c, " l =", l, ")"
    pygame.draw.polygon (screen, c, l, 0)
    return f


#
#  flip - returns the y value flipped against the resolution.
#

def flip (y):
    global resolution
    return min (resolution[0], resolution[1])-y


#
#  doDrawFillCircle -
#

def _doDrawFillCircle (f):
    global screen, debugging

    f, xf = _readFract (f)
    f, yf = _readFract (f)
    f, rf = _readFract (f)
    x = _mults (resolution[0], xf)
    y = _mults (resolution[1], yf)
    r = _mults (resolution[0], rf)

    f, c = _readColour (f)
    _debugf("circle  x = %d  y = %d,  r = %d\n", x, y, r)
    if debugging:
        print "  colour =", c
    pygame.draw.circle (screen, c, (x, flip (y)), r, 0)
    return f


def _wait_for_n ():
    _printf ("press 'n' to continue\n")
    while True:
        e = pygame.event.wait ()
        # print e
        if e.type == KEYDOWN and e.key == K_n:
            _printf (" ... continuing\n")
            return

#
#  flipBuffer - flips the screen buffer.
#

def _doFlipBuffer ():
    global background, screen, nextFrame, backcanvas, program_name

    # _printf ("doFlipBuffer called for frame (%d)\n", nextFrame)
    pygame.display.set_caption (program_name + ' ' + version_number + ' (%d)' % (nextFrame))
    pygame.display.flip ()
    screen.blit (backcanvas, (0, 0))
    # _wait_for_n ()

def _doSleep (f):
    global lastDelay
    f, t = _readReal (f)
    # lastDelay += t
    return f


def _readReal (f):
    b = f.read (8)
    return f, struct.unpack ("d", b)[0]


#
#  doDrawPolygon -
#

def _doDrawPolygon (f):
    global debugging, screen

    f, n = _readShort (f)
    l = []
    _debugf ("drawPolygon: %d", n)
    for i in range (n):
        f, xf = _readFract (f)
        f, yf = _readFract (f)
        if debugging:
            print xf, yf,
        x = _mults (resolution[0], xf)
        y = _mults (resolution[1], yf)
        l += [[x, flip(y)]]

    f, t = _readFract (f)
    if debugging:
        print "draw polygon", l, "thickness", t
    # pygame.draw.polygon (screen, c, l, 0)
    return f

def _doMessage (f):
    text = ""
    b = f.read (1)
    while int(b) != 0:
        text += b
        b = f.read (1)
    _printf ("Frame [%d]: %s\n", nextFrame, text)

#
#  _doPass - a nop.
#

def _doPass (f):
    return f


call['rc'] = _doRegisterColour
call['dp'] = _doDrawPolygon
call['dP'] = _doDrawFillPolygon
# call['dc'] = doDrawCircle
call['dC'] = _doDrawFillCircle
call['fb'] = _doPass
# call['fr'] = doFramesPerSecond
call['ex'] = _doExit
call['sl'] = _doSleep
# call['ps'] = doPlay
# call['fn'] = doFrameNote
call['ms'] = _doMessage


#
#  coordinate geometry utilities
#

#
#  pyg_to_unit_coord - inputs :  v  a list of two integers in the range 0..xresolution, 0..yresolution.
#                      returns:  a list of two floating point numbers between 0.0 and 1.0

def pyg_to_unit_coord (v):
    global resolution

    if resolution == None:
        _errorf ("you must assign the screen resolution with a call to 'display_set_mode' before calling 'pyg_to_unit_coord'\n")
    if len (v) == 2:
        return [(float) (v[0]) / (float) (resolution[0]),
                (float) (resolution[1] - v[1]) / (float) (resolution[1])]
    else:
        _errorf ("'pyg_to_unit_coord' expects a list of two integers\n")


#
#  normalise - input a vector [x, y]
#              return the vector after it has been normalised.
#

def normalise (v):
    x = (float) (v[0])
    y = (float) (v[1])
    l = magnitude ([x, y])
    return [x/l, y/l]


#
#  magnitude - return the modulus or magnitude of a vector or
#              the Pythagorean value of the vector.
#

def magnitude (v):
    return math.sqrt (v[0]*v[0] + v[1]*v[1])

#
#  sub_coord - returns the vector a - b.
#

def sub_coord (a, b):
    return [a[0]-b[0], a[1]-b[1]]
