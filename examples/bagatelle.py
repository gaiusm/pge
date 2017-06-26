#!/usr/bin/env python

import pge, sys
from pygame.locals import *


print "starting bagatelle"
pge.interactive ()
# pge.batch ()

t = pge.rgb (1.0/2.0, 2.0/3.0, 3.0/4.0)
wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)
steel = pge.rgb (0.5, 0.5, 0.5)
copper = pge.rgb (0.5, 0.3, 0.2)
gold = pge.rgb (0.8, 0.6, 0.15)
ball_size = 0.02
boarder = 0.01
white = pge.rgb (1.0, 1.0, 1.0)
green = pge.rgb (0.0, 1.0, 0.0)
gap = 0.01
g = None


def placeBoarders (thickness, color):
    print "placeBoarders"
    e1 = pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    e2 = pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    e3 = pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    e4 = pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()
    return e1, e2, e3, e4


def placeBall (kind, x, y, r):
    return pge.circle (x, y, r, kind)


def placeBox (p0, p1, p2, p3):
    t = pge.poly4 (p0[0], p0[1], p1[0], p1[1],
                   p2[0], p2[1], p3[0], p3[1], white)
    t.fix ()

def callMe (p):
    print "box has collided!"

def play_wood (o, e):
    pge.play ("/home/gaius/Sandpit/cluedo/sounds/bounce.wav")

def play_crack (o, e):
    pge.play ("/home/gaius/Sandpit/penguin-tower/sounds/crack-single.wav")

def play_bounce (o, e):
    pge.play ("/home/gaius/Sandpit/cluedo/sounds/cardsnap.wav")

def key_pressed (e):
    if e.key == K_ESCAPE:
        myquit (e)

def mouse_hit (e):
    global g
    print "mouse down", e.pos
    mouse = pge.pyg_to_unit_coord (e.pos)
    ball = g.get_unit_coord ()
    g.apply_impulse (pge.normalise (pge.sub_coord (mouse, ball)),
                     0.8)

    # pge.magnitude (pge.sub_coord (mouse, ball)))

def myquit (e):
    print "goodbye"
    sys.exit (0)

def main ():
    global g
    # s = placeBall (steel, 0.54, 0.8, 0.05).mass (1).on_collision (play_crack)
    # c = placeBall (copper, 0.85, 0.8, 0.05).mass (.75).on_collision (play_bounce)
    g = placeBall (gold, 0.15, 0.8, 0.05).mass (1.25).on_collision (play_bounce)
    f = placeBall (red, 0.95, 0.05, 0.1).fix ()
    l = placeBox ([0.3, 0.3], [0.3, 0.5], [0.5, 0.5], [0.5, 0.3])
    b1, b2, b3, b4 = placeBoarders (boarder, wood_dark)
    for b in [b1, b2, b3, b4]:
        b.on_collision (play_crack)

    print "before run"
    pge.gravity ()
    pge.dump_world ()
    pge.draw_collision (True, False)
    pge.collision_colour (green)
    pge.slow_down (6.0)  # slows down real time by a factor of
    pge.display_set_mode ([640, 640])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.register_handler (mouse_hit, [MOUSEBUTTONDOWN])
    pge.register_handler (myquit, [QUIT])
    pge.run (30.0)
    pge.finish ()

print "before main()"
main ()
