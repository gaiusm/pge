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
balli = 0
balllist = [[gold, 1.5], [steel, 1.0], [copper, 0.5]]
winner = False
loser = False
seconds_left = None
previous = None
slowdown = 5
simulatedtime = 6


def myquit (e):
    print "goodbye"
    sys.exit (0)

def finish_game (event, param):
    sys.exit (0)

def placeBoarders (thickness, color):
    print "placeBoarders"
    n = pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()
    e = pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    s = pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    w = pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    return n, e, s, w

def placeBall (kind, x, y, r):
    return pge.circle (x, y, r, kind)

def callMe (p):
    print "box has collided!"

def play_wood (o, e):
    pass

def play_crack (o, e):
    pass

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

def mouse_press (e):
    global balli, balllist
    if (e.button == 1) or (e.button == 3):
        c = balllist[balli][0]
        w = balllist[balli][1]
        balli = (balli + 1) % len (balllist)
        mouse = pge.pyg_to_unit_coord (e.pos)
        b = placeBall (c, 0.92, 0.21, 0.05).mass (w)
        print mouse, 0.5-mouse[0], 6*mouse[1]
        b.put_yvel (6*mouse[1])
        b.put_xvel (0.5-mouse[0])

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

def push_it (o, e):
    p = e.collision_between ()
    if p != None and p != []:
        for i in p:
            if i != o:
                i.put_xvel (i.get_xvel () * 1.15)
                i.put_yvel (i.get_yvel () * 1.15)

def boost (o, e):
    p = e.collision_between ()
    if p != None and p != []:
        for i in p:
            if i != o:
                i.put_xvel (i.get_xvel () * 1.2)
                i.put_yvel (i.get_yvel () * 1.2)


def extra ():
    print "hello at some time in the future"

def myquit (e):
    print "goodbye"
    sys.exit (0)

def placeShoot ():
    s = pge.box (0.82, 0.0, 0.01, 0.6, wood_dark).fix ()

def placeTriangle (p0, p1, p2, colour):
    t = pge.poly3 (p0[0], p0[1], p1[0], p1[1], p2[0], p2[1], colour).on_collision (push_it).fix ()

def delete_ball (o, e):
    print "delete_ball called"
    p = e.collision_between ()
    if p != None and p != []:
        for i in p:
            if i != o:
                i.rm ()

def placeSilos ():
    for x in [0.3, 0.6]:
        s = pge.poly4 (x, 0.0,
                       x, 0.07,
                       x+0.01, 0.07,
                       x+0.01, 0.0, wood_dark).fix ()
    pge.text (0.15, 0.05, "+10", blue, 50, 1)
    pge.text (0.40, 0.05, "+5", blue, 50, 1)
    pge.text (0.65, 0.05, "+15", blue, 50, 1)
    pge.text (0.90, 0.05, "-20", red, 50, 1)

def timer (a = None, b = None):
    global seconds_left, previous
    if seconds_left >= 0:
        pge.at_time (1.0, timer)
        s = "%d" % seconds_left
        if previous != None:
            previous.rm ()
        previous = pge.text (0.8, 0.9, s, white, 100, 1)
        seconds_left -= 1

def main ():
    global g, blue, steel, slowdown, seconds_left

    print "about to create white text"
    t1 = placeTriangle ([0.2, 0.4], [0.4, 0.4], [0.3, 0.5], white)
    t2 = placeTriangle ([0.6, 0.4], [0.8, 0.4], [0.7, 0.5], white)

    r = placeBall (copper, 0.5, 0.7, 0.07).fix ().on_collision (boost)
    placeBall (steel, 0.95, 0.95, 0.01).fix ()
    for b in range (4):
        placeBall (steel, b*2/10.0+0.1, 0.25, 0.01).fix ()
    placeSilos ()
    print "completed white text"
    n, e, s, w = placeBoarders (boarder, wood_dark)
    s.on_collision (delete_ball)
    placeShoot ()

    print "before run"
    pge.gravity ()
    pge.dump_world ()
    pge.draw_collision (True, False)
    # pge.collision_colour (green)
    pge.slow_down (6.0)  # slows down real time by a factor of
    pge.fps (200)
    pge.display_set_mode ([800, 800])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.register_handler (mouse_press, [MOUSEBUTTONDOWN])
    pge.register_handler (myquit, [QUIT])

    seconds_left = simulatedtime * slowdown
    timer ()
    pge.run (simulatedtime)
    if not winner:
        loser = True
        pge.text (0.2, 0.3, "Loser", white, 100, 1)
        pge.at_time (4.0, finish_game)
    pge.run (4.0)
    pge.finish_record ()

print "before main()"
main ()
