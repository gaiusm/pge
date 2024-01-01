#!/usr/bin/env python3

import pge, sys
from pygame.locals import *

print("starting boxes")
# pge.batch ()
pge.interactive ()

wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)
blue = pge.rgb (0.0, 0.0, 1.0)
green = pge.rgb (0.0, 1.0, 0.0)

border = 0.01
slowdown = 12

def finish_game (event = None, unused = None):
    sys.exit (0)


def myquit (e):
    print("goodbye")
    finish_game ()

def key_pressed (e):
    if e.key == K_ESCAPE:
        myquit (e)

def placeBorders (thickness, color):
    print("placeBorders")
    pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()

def placeBox (p, w, c):
    return pge.box (p[0], p[1], w, w, c)

def placeBall (p, r, c):
    return pge.circle (p[0], p[1], r, c)

def main ():
    pge.slow_down (slowdown)  # slows down real time by a factor of
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.display_set_mode ([800, 800])
    pge.draw_collision (False, False)
    pge.record ()
    placeBox ([0.39, 0.3], 0.1, red).fix ()
    placeBorders (border, wood_dark)
    placeBox ([0.47, 0.7], 0.1, blue).mass (1.0)
    # placeBox ([0.35, 0.7], 0.1, green).mass (1.0)
    # placeBall ([0.25, 0.85], 0.03, green).mass (1.0)
    pge.gravity ()
    # pge.run (1.65)
    pge.run (2.5)
    pge.finish_record ()

print("before main()")
main ()
