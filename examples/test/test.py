#!/usr/bin/env python

import pge, sys, time
from pygame.locals import *


print "starting breakout"
# pge.batch ()
pge.interactive ()
pge.record ()

t = pge.rgb (1.0/2.0, 2.0/3.0, 3.0/4.0)
wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)
green = pge.rgb (0.0, 1.0, 0.0)
blue = pge.rgb (0.0, 0.0, 1.0)

dark_red = pge.rgb (166.0/255.0, 25.0/255.0, 50.0/255.0)
dark_green = pge.rgb (25.0/255.0, 100.0/255.0, 50.0/255.0)
dark_blue = pge.rgb (25.0/255.0, 50.0/255.0, 150.0/255.0)

steel = pge.rgb (0.5, 0.5, 0.5)
copper = pge.rgb (0.5, 0.3, 0.2)
gold = pge.rgb (0.8, 0.6, 0.15)
ball_size = 0.02
boarder = 0.01
white = pge.rgb (1.0, 1.0, 1.0)
gap = 0.01
blocks = []
winner = False
loser = False
seconds_left = None
previous = None
slowdown = 6


def finish_game (i = None):
    sys.exit (0)


def myquit (e):
    print "goodbye"
    finish_game ()


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
    global gb, winner, loser, seconds_left

    b1, b2, b3, b4 = placeBoarders (boarder, wood_dark)
    g1 = placeBall (gold, 0.19, 0.8, 0.05).mass (1.25)
    g2 = placeBall (gold, 0.59, 0.8, 0.05).mass (1.25)
    g3 = placeBall (gold, 0.7, 0.8, 0.05).mass (1.25)
    g4 = placeBall (gold, 0.81, 0.8, 0.05).mass (1.25)
    g5 = placeBall (gold, 0.92, 0.8, 0.05).mass (1.25)
    g6 = placeBall (gold, 0.92, 0.69, 0.05).mass (1.25)

    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])

    print "before run"
    pge.gravity ()
    pge.dump_world ()
    pge.draw_collision (True, False)
    pge.slow_down (slowdown)  # slows down real time by a factor of
    pge.display_set_mode ([800, 800])
    # pge.display_fullscreen (True)
    seconds_left = 10*slowdown
    pge.run (10.0)
    pge.finish_record ()


print "before main()"
main ()
