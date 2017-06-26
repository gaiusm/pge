#!/usr/bin/env python

import pge, sys, time
from pygame.locals import *


print "starting exampleBoxes"
# pge.batch ()
pge.interactive ()
pge.record ()

t = pge.rgb (1.0/2.0, 2.0/3.0, 3.0/4.0)
wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)

green = pge.rgb (0.0, 1.0, 0.0)
blue = pge.rgb (0.0, 0.0, 1.0)

steel = pge.rgb (0.5, 0.5, 0.5)
copper = pge.rgb (0.5, 0.3, 0.2)
gold = pge.rgb (0.8, 0.6, 0.15)
ball_size = 0.02
boarder = 0.01
white = pge.rgb (1.0, 1.0, 1.0)

dark_red = pge.rgb (85.0/255.0, 25.0/255.0, 25.0/255.0)
dark_green = pge.rgb (25.0/255.0, 100.0/255.0, 50.0/255.0)
dark_blue = pge.rgb (25.0/255.0, 50.0/255.0, 150.0/255.0)

gap = 0.01
captured = []
sides = []
winner = False
looser = False
seconds_left = None
previous = None
slowdown = 5
simulatedtime = 7*2


def myquit (e):
    print "goodbye"
    sys.exit (0)

def finish_game ():
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

def delete_ball (o, e):
    global winner, looser
    for b in e.collision_between ():
        if b in captured:
            b.rm ()
            captured.remove (b)
            if captured == []:
                if not looser:
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

def placeSilos ():
    for x in [0.3, 0.6]:
        s = pge.poly4 (x, 0.0,
                       x, 0.07,
                       x+0.01, 0.07,
                       x+0.01, 0.0, wood_dark).fix ()


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
    captured += [placeBall (dark_blue, pos[0]+2.0*thickness+0.05, pos[1]+1.0*thickness+0.05, 0.05).mass (1.5)]

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

def place_matchboxes ():
    for x in range (4):
        box_of (boarder, [((float)(x*2))/10.0+0.1, 0.08], 0.2, wood_light)
    for x in [1.5]:
        box_of (boarder, [((float)(x*2))/10.0+0.1, 0.58], 0.2, wood_light)

def place_triangles (height):
    t1 = placeTriangle ([0.2, height], [0.4, height], [0.3, height+0.1], white)
    t2 = placeTriangle ([0.6, height], [0.8, height], [0.7, height+0.1], white)

def timer ():
    global seconds_left, previous
    if seconds_left >= 0:
        pge.at_time (1.0, timer)
        s = "%d" % seconds_left
        if previous != None:
            previous.rm ()
        previous = pge.text (0.8, 0.9, s, white, 100, 1)
        seconds_left -= 1

def main ():
    global gb, sides, winner, looser, seconds_left, slowdown, simulatedtime

    place_triangles (0.3)
    b1, b2, b3, b4 = placeBoarders (boarder, wood_dark)
    b1.on_collision (delete_ball)

    place_matchboxes ()
    gb = placeBall (gold, 0.19, 0.8, 0.05).mass (1.25).on_collision_with (sides, delete_it)
    cb = placeBall (copper, 0.81, 0.7, 0.05).mass (.75).on_collision_with (sides, delete_it)
    placeSilos ()

    # placeBall (dark_blue, 0.55, 0.4, 0.05).mass (1.5)

    print "before run"
    pge.gravity ()
    pge.dump_world ()
    pge.draw_collision (True, False)
    pge.slow_down (slowdown)  # slows down real time by a factor of
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.register_handler (mouse_hit, [MOUSEBUTTONDOWN])
    pge.display_set_mode ([800, 800])
    # pge.display_fullscreen (True)
    seconds_left = simulatedtime * slowdown
    timer ()
    pge.run (simulatedtime)
    if not winner:
        looser = True
        pge.text (0.2, 0.3, "Looser", white, 100, 1)
        pge.at_time (4.0, finish_game)
    pge.run (4.0)
    pge.finish ()

print "before main()"
main ()
