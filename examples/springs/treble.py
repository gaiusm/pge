#!/usr/bin/env python

import pge, sys
from pygame.locals import *


print "starting exampleBoxes"
# pge.batch ()
pge.interactive ()

t = pge.rgb (1.0/2.0, 2.0/3.0, 3.0/4.0)
wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)
green = pge.rgb (0.0, 1.0, 0.0)
blue = pge.rgb (0.0, 0.0, 1.0)
blue_dark = pge.rgb (0.1, 0.1, 0.8)
steel = pge.rgb (0.5, 0.5, 0.5)
copper = pge.rgb (0.5, 0.3, 0.2)
gold = pge.rgb (0.8, 0.6, 0.15)
ball_size = 0.02
boarder = 0.01
white = pge.rgb (1.0, 1.0, 1.0)
gap = 0.01
captured = None
sides = []
yellow = pge.rgb (0.8, 0.6, 0.15)
fps_text = None
last_fps = 0


def myquit (e):
    print "goodbye"
    sys.exit (0)

def key_pressed (e):
    if e.key == K_ESCAPE:
        myquit (e)

def placeBoarders (thickness, color):
    print "placeBoarders"
    e1 = pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    e2 = pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    e3 = pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    e4 = pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()
    return e1, e2, e3, e4

def placeBall (kind, x, y, r):
    return pge.circle (x, y, r, kind)

def update_fps (e, o):
    global last_fps, fps_text

    fn = pge.get_frame_no ()
    s = "fps %d" % (fn - last_fps)
    if fps_text != None:
        fps_text.rm ()
    fps_text = pge.text (0.8, 0.1, s, white, 50, 1)
    last_fps = fn
    local_fps ()


def local_fps ():
    f = pge.at_time (1.0, update_fps)

def main ():
    global gb, sides

    placeBoarders (0.01, wood_dark)

    first = placeBall (wood_dark, 0.55, 0.95, 0.02).fix ()
    second = placeBall (wood_light, 0.36, 0.85, 0.02).mass (1.0)
    third = placeBall (wood_dark, 0.74, 0.52, 0.02).mass (1.0)
    fourth = placeBall (wood_dark, 0.4, 0.51, 0.02).mass (1.0)
    s = pge.spring (first, second, 100.0, 2.0, 0.03).draw (yellow, 0.002)
    s = pge.spring (second, third, 100.0, 2.0, 0.08).draw (yellow, 0.002)
    s = pge.spring (third, fourth, 100.0, 2.0, 0.08).draw (yellow, 0.002)
    print "before run"
    pge.record ()
    pge.draw_collision (False, False)
    pge.collision_colour (red)
    pge.gravity ()
    pge.dump_world ()
    pge.slow_down (6.0)  # slows down real time by a factor of
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.display_set_mode ([800, 800])
    local_fps ()
    pge.run (20.0)
    pge.finish_record ()

print "before main()"
main ()
