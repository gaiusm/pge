#!/usr/bin/env python3

import pge, sys, time
from pygame.locals import *


print("starting snooker")
# pge.batch ()
pge.interactive ()
pge.record ()

t = pge.rgb (1.0/2.0, 2.0/3.0, 3.0/4.0)
wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)
green = pge.rgb (0.0, 1.0, 0.0)
blue = pge.rgb (0.0, 0.0, 1.0)

ball_size = 0.02
boarder = 0.01
white = pge.rgb (1.0, 1.0, 1.0)
gap = 0.01
captured = []
sides = []
slowdown = 5
simulatedtime = 6


def myquit (e):
    print("goodbye")
    sys.exit (0)

def finish_game (e = None):
    sys.exit (0)

def key_pressed (e):
    if e.key == K_ESCAPE:
        myquit (e)

def placeBoarders (thickness, color):
    print("placeBoarders")
    e1 = pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    e2 = pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    e3 = pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    e4 = pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()
    return e1, e2, e3, e4

def delete_ball (o, e):
    global winner, loser, captured
    for b in e.collision_between ():
        if b in captured:
            b.rm ()
            captured.remove (b)
            if captured == []:
                if not loser:
                    winner = True
                    pge.text (0.2, 0.3, "Winner", white, 100, 1)
                    pge.at_time (4.0, finish_game)


def placeBall (kind, x, y, r):
    return pge.circle (x, y, r, kind)


def placeBox (p0, p1, p2, p3, colour):
    t = pge.poly4 (p0[0], p0[1], p1[0], p1[1],
                   p2[0], p2[1], p3[0], p3[1], colour)
    t.fix ()

def push_it (o, e):
    p = e.collision_between ()
    if p != None and p != []:
        for i in p:
            if i != o:
                i.put_xvel (i.get_xvel () * 1.15)
                i.put_yvel (i.get_yvel () * 1.15)

def placeTriangle (p0, p1, p2, colour):
    t = pge.poly3 (p0[0], p0[1], p1[0], p1[1], p2[0], p2[1], colour).on_collision (push_it).fix ()

def delete_it (o, e):
    global sides

    for i in e.collision_between ():
        if i in sides:
            i.rm ()

def box_of (thickness, pos, width, color):
    global captured, sides

    floor = pge.box (pos[0], pos[1], width, thickness, color).fix ()
    left = pge.box (pos[0], pos[1], thickness, width, color).fix ()
    right = pge.box (pos[0]+width-thickness, pos[1], thickness, width, color).fix ()
    top = pge.box (pos[0], pos[1]+width-thickness, width, thickness, color).fix ()
    sides += [floor, left, right, top]
    captured += [placeBall (blue, pos[0]+2.0*thickness+0.05, pos[1]+1.0*thickness+0.05, 0.05).mass (1.5)]

def mouse_hit (e):
    global gb
    mouse = pge.pyg_to_unit_coord (e.pos)
    if e.button == 1:
        gb.put_xvel (gb.get_xvel ()-0.3)
    elif e.button == 3:
        gb.put_xvel (gb.get_xvel ()+0.3)
    elif gb.moving_towards (mouse[0], mouse[1]):
        ball = gb.get_unit_coord ()
        # print "mouse =", mouse, "ball =", ball
        gb.apply_impulse (pge.sub_coord (mouse, ball), 0.3)
    else:
        gb.put_yvel (gb.get_yvel ()+0.3)

def main ():
    global gb, sides, winner, loser, seconds_left, slowdown, simulatedtime

    t1 = placeTriangle ([0.2, 0.3], [0.4, 0.3], [0.3, 0.4], white)
    t2 = placeTriangle ([0.6, 0.3], [0.8, 0.3], [0.7, 0.4], white)
    b1, b2, b3, b4 = placeBoarders (boarder, wood_dark)
    b1.on_collision (delete_ball)

    gb = placeBall (green, 0.19, 0.8, 0.05).mass (1.25).on_collision_with (sides, delete_it)

    print("before run")
    pge.draw_collision (True, False)
    pge.slow_down (slowdown)  # slows down real time by a factor of
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.register_handler (mouse_hit, [MOUSEBUTTONDOWN])
    pge.display_set_mode ([800, 800])
    seconds_left = simulatedtime * slowdown
    pge.gravity ()
    pge.run (simulatedtime)
    pge.run (4.0)
    pge.finish_record ()

print("before main()")
main ()
