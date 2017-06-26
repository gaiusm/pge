#!/usr/bin/env python

import pge, sys
from pygame.locals import *


print "starting bagatelle"
pge.interactive ()
# pge.batch ()
pge.record ()

print "defining white"
white = pge.rgb (1.0, 1.0, 1.0)
print "completed definition"
t = pge.rgb (1.0/2.0, 2.0/3.0, 3.0/4.0)
wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)
steel = pge.rgb (0.5, 0.5, 0.5)
copper = pge.rgb (0.5, 0.3, 0.2)
gold = pge.rgb (0.8, 0.6, 0.15)
ball_size = 0.02
boarder = 0.01
green = pge.rgb (0.0, 1.0, 0.0)
# blue = pge.rgb (0.0, 0.0, 1.0)
blue = pge.rgb (0.0, 100.0/255.0, 1.0)
gap = 0.01
g = None



def placeBoarders (thickness, color):
    print "placeBoarders"
    n = pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()
    e = pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    s = pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    w = pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    return n, e, s, w


def placeBall (kind, x, y, r):
    return pge.circle (x, y, r, kind)


def placeBox (p0, p1, p2, p3):
    t = pge.poly4 (p0[0], p0[1], p1[0], p1[1],
                   p2[0], p2[1], p3[0], p3[1], blue)
    t.fix ()

def callMe (p):
    print "box has collided!"

def play_wood (o, e):
    pge.play ("/home/gaius/Sandpit/cluedo/sounds/bounce.wav")

def play_crack (o, e):
    pge.play ("/home/gaius/Sandpit/penguin-tower/sounds/crack-single.wav")

bounces = 0

def play_bounce (o, e):
    global g, bounces
    return
    pge.play ("/home/gaius/Sandpit/cluedo/sounds/cardsnap.wav")
    if bounces % 2 == 0:
        g.set_colour (red)
    else:
        g.set_colour (gold)
    bounces += 1
    if bounces == 50:
        g.rm ()
        g = placeBall (gold, 0.15, 0.8, 0.05).mass (1.25).on_collision (play_bounce)
        bounces = 0

def key_pressed (e):
    if e.key == K_ESCAPE:
        myquit (e)
    elif e.key == K_UP:
        print "K_UP"
        moveit ([0, 1])
    elif e.key == K_DOWN:
        print "K_DOWN"
        moveit ([0, -1])
    elif e.key == K_LEFT:
        print "K_LEFT"
        moveit ([-1, 0])
    elif e.key == K_RIGHT:
        print "K_RIGHT"
        moveit ([1, 0])

def mouse_hit (e):
    global g
    mouse = pge.pyg_to_unit_coord (e.pos)
    if e.button == 1:
        g.put_xvel (g.get_xvel ()-0.3)
    elif e.button == 3:
        g.put_xvel (g.get_xvel ()+0.3)
    elif g.moving_towards (mouse[0], mouse[1]):
        ball = g.get_unit_coord ()
        # print "mouse =", mouse, "ball =", ball
        g.apply_impulse (pge.sub_coord (mouse, ball), 0.3)
    else:
        g.put_yvel (g.get_yvel ()+0.3)

def moveit (vec):
    global g
    if vec[0] != 0:
        x = g.get_xvel ()
        print "xvel =", x, vec[0],
        # x = x + (float) (vec[0]) * 0.2
        print " new x =", x
        # g.put_xvel (x)
    if vec[1] != 0:
        y = g.get_yvel ()
        print "yvel =", y, vec[1],
        y = y + (float) (vec[1]) * 0.2
        print " new y =", y
        g.put_yvel (y)


def extra ():
    print "hello at some time in the future"

def myquit (e):
    print "goodbye"
    sys.exit (0)

def main ():
    global g, blue

    print white
    print "about to create white text"
    x = pge.box (0.1, 0.2, 0.2, 0.2, blue, -1)
    z = pge.circle (0.3, 0.3, 0.14, white, 1)
    print "about to create white text"
    t = pge.text (0.1, 0.12, "hello", white, 36, 11)
    print "completed white text"
    # s1 = placeBall (steel, 0.43, 0.8, 0.05).mass (1).on_collision (play_crack)
    s = placeBall (steel, 0.54, 0.8, 0.05).mass (1).on_collision (play_crack)
    c = placeBall (copper, 0.85, 0.8, 0.05).mass (.75).on_collision (play_bounce)
    # c = placeBall (copper, 0.85, 0.8, 0.05).fix ()
    g = placeBall (gold, 0.15, 0.8, 0.05).mass (1.25).on_collision (play_bounce)
    # f = placeBall (red, 0.95, 0.05, 0.1).fix ()
    l = placeBox ([0.3, 0.3], [0.3, 0.5], [0.5, 0.5], [0.5, 0.3])
    b1, b2, b3, b4 = placeBoarders (boarder, wood_dark)
    for b in [b1, b2, b3, b4]:
        b.on_collision (play_crack)

    print "before run"
    pge.gravity ()
    pge.dump_world ()
    pge.draw_collision (True, False)
    # pge.collision_colour (green)
    pge.slow_down (5.0)  # slows down real time by a factor of
    pge.fps (200)
    pge.display_set_mode ([800, 800])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.register_handler (mouse_hit, [MOUSEBUTTONDOWN])
    pge.register_handler (myquit, [QUIT])
    # pge.display_fullscreen (True)
    # pge.at_time (3.0, extra)
    # pge.at_time (5.0, extra)
    # pge.at_time (7.0, extra)
    for i in range (40):
        pge.run (0.5)
        # g.apply_impulse ([0.1, 0.1], 0.3)
        #    g.put_xvel (g.get_xvel ()+.1)
        c = placeBall (copper, 0.85, 0.8, 0.05).mass (.75)

    # c = placeBall (copper, 0.85, 0.8, 0.05).mass (.75)
    pge.run (10.0)
    pge.finish ()

print "before main()"
main ()
