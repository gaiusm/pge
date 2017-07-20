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

def snapIt (e, o):
    o.rm ()

def main ():
    global gb, sides, springs

    spring_power = 500.0
    damping = 20.0

    placeBoarders (0.01, wood_dark)

    left = placeBall (wood_light, 0.50, 0.75, 0.03).fix ()

    prev = left
    springs = []
    for x in range (35, 75, 10):
        step = placeBall (wood_dark, float (x) / 100.0, 0.70, 0.03).mass (0.3)
        s = pge.spring (prev, step, spring_power, damping, 0.1).draw (yellow, 0.002)
        s.when (0.2, snapIt)
        springs += [s]
        prev = step

    gb = placeBall (steel, 0.7, 0.95, 0.01).mass (2.0)
    print "before run"
    pge.record ()
    pge.draw_collision (True, False)
    pge.collision_colour (red)
    pge.gravity ()
    pge.dump_world ()
    pge.slow_down (6.0)  # slows down real time by a factor of
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.display_set_mode ([1000, 1000])
    pge.run (10.0)
    pge.finish_record ()

print "before main()"
main ()
