#!/usr/bin/env python

import pge, sys
from pygame.locals import *


print "starting ramps"
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
yellow = pge.rgb (0.8, 0.6, 0.15)
gap = 0.01
captured = None
sides = []


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

def snap_it (e, o):
    global springs

    for s in springs:
        s.rm ()

def placeRamps ():
    global springs
    r1 = pge.poly4 (0.3 , 0.8,
                    0.85, 0.82,
                    0.85, 0.83,
                    0.3 , 0.81, wood_dark).fix ()

    r2 = pge.poly4 (0.3 , 0.4,
                    0.85, 0.42,
                    0.85, 0.43,
                    0.3 , 0.41, wood_dark).fix ()

    r3 = pge.poly4 (0.15, 0.6,
                    0.32, 0.58,
                    0.32, 0.57,
                    0.15, 0.59, wood_dark).fix ()

    p1 = pge.circle (0.32, 0.57, 0.01, wood_dark).fix ()
    p2 = pge.circle (0.60, 0.55, 0.01, wood_dark).fix ()
    spring_power = 10.0
    damping = 1.0
    break_length = 0.2

    springs = []
    prev = p1
    for x in range (37, 55, 5):
        step = placeBall (wood_dark, float (x) / 100.0, 0.56, 0.01).mass (0.01)
        s = pge.spring (prev, step, spring_power, damping, 0.02).draw (yellow, 0.002)
        s.when (break_length, snap_it)
        prev = step
        springs += [s]
    s = pge.spring (p2, prev, spring_power, damping, 0.02).draw (yellow, 0.002)
    s.when (break_length, snap_it)
    springs += [s]



def placeTriangle (p0, p1, p2, colour):
    t = pge.poly3 (p0[0], p0[1], p1[0], p1[1], p2[0], p2[1], colour).on_collision (push_it).fix ()

def placeSilos ():
    for x in [0.3, 0.6]:
        s = pge.poly4 (x, 0.0,
                       x, 0.07,
                       x+0.01, 0.07,
                       x+0.01, 0.0, wood_dark).fix ()


def callMe (p):
    print "box has collided!"

def play_wood (o, e):
    pass

def play_crack (o, e):
    pass

def play_bounce (o, e):
    pass

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
    sides = [floor, left, right, top]
    captured = placeBall (blue_dark, pos[0]+2.0*thickness+0.05, pos[1]+1.0*thickness+0.05, 0.05).mass (1.5)

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
    global gb, sides

    f = placeBall (wood_light, 0.95, 0.05, 0.1).fix ()
    # l = placeBox ([0.3, 0.3], [0.3, 0.5], [0.5, 0.5], [0.5, 0.3], white)
    placeRamps ()
    b1, b2, b3, b4 = placeBoarders (boarder, wood_dark)
    for b in [b1, b2, b3, b4]:
        b.on_collision (play_crack)
    box_of (boarder, [0.1, 0.08], 0.2, wood_light)
    gb = placeBall (gold, 0.79, 0.89, 0.05).mass (1.25).on_collision_with (sides, delete_it)
    placeSilos ()

    print "before run"
    pge.gravity ()
    pge.dump_world ()
    pge.draw_collision (True, False)
    pge.slow_down (6.0)  # slows down real time by a factor of
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.register_handler (mouse_hit, [MOUSEBUTTONDOWN])
    pge.display_set_mode ([800, 800])
    pge.run (18.0)
    pge.finish_record ()

print "before main()"
main ()
