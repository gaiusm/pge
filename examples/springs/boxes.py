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

def main ():
    global gb, sides

    spring_power = 100.0
    damping = 1.0

    placeBoarders (0.01, wood_dark)

    top_left = placeBall (wood_light, 0.25, 0.85, 0.02).mass (0.1)
    top_right = placeBall (wood_light, 0.45, 0.80, 0.02).mass (0.1)
    bot_left = placeBall (wood_light, 0.25, 0.65, 0.02).mass (0.1)
    bot_right = placeBall (wood_light, 0.45, 0.60, 0.02).mass (0.1)
    s0 = pge.spring (top_left, top_right, spring_power, damping).draw (yellow, 0.002)
    s1 = pge.spring (top_right, bot_right, spring_power, damping).draw (yellow, 0.002)
    s2 = pge.spring (bot_right, bot_left, spring_power, damping).draw (yellow, 0.002)
    s3 = pge.spring (bot_left, top_left, spring_power, damping).draw (yellow, 0.002)
    s4 = pge.spring (top_left, bot_right, spring_power, damping).draw (yellow, 0.002)
    s5 = pge.spring (bot_left, top_right, spring_power, damping).draw (yellow, 0.002)

    for i in range (2, 7):
        gb1 = placeBall (steel, float (i)/10.0, 0.9, 0.01).mass (1.0)
    gb1 = placeBall (steel, 0.4, 0.9, 0.01).mass (1.0)
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
