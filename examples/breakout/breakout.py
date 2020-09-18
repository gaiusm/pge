#!/usr/bin/env python3

import pge, sys, time
from pygame.locals import *


print("starting breakout")
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


def finish_game (event = None, unused = None):
    sys.exit (0)


def myquit (e):
    print("goodbye")
    finish_game ()


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


def placeBall (kind, x, y, r):
    return pge.circle (x, y, r, kind)


def push_it (o, e):
    p = e.collision_between ()
    if p != None and p != []:
        for i in p:
            if i != o:
                i.put_xvel (i.get_xvel () * 1.15)
                i.put_yvel (i.get_yvel () * 1.15)


def placeTriangle (p0, p1, p2, colour):
    t = pge.poly3 (p0[0], p0[1], p1[0], p1[1], p2[0], p2[1], colour).on_collision (push_it).fix ()


def delete_me (o, e):
    global blocks, winner, loser

    blocks.remove (o)
    o.rm ()
    if blocks == []:
        if not loser:
            winner = True
            pge.text (0.2, 0.3, "Winner", white, 100, 1)
            pge.at_time (4.0, finish_game)


def box_of (pos, width, height, color):
    global blocks

    blocks += [pge.box (pos[0], pos[1], width, height, color).fix ().on_collision (delete_me)]


def mouse_hit (e):
    global gb
    mouse = pge.pyg_to_unit_coord (e.pos)
    if e.button == 1:
        if mouse[0] > gb.get_xpos ():
            gb.put_xvel (gb.get_xvel ()-0.3)
        elif mouse[0] < gb.get_xpos ():
            gb.put_xvel (gb.get_xvel ()+0.3)
        if mouse[1] > gb.get_ypos ():
            gb.put_yvel (gb.get_yvel ()-0.3)
        elif mouse[1] < gb.get_ypos ():
            gb.put_yvel (gb.get_yvel ()+0.3)


def place_boxes ():
    for y in range (3):
        for x in range (9):
            box_of ([((float)(x))/10.0+0.06, (float)(y)/10.0+0.03], 0.08, 0.08, dark_blue)

def timer (e = None, f = None):
    global seconds_left, previous
    if seconds_left >= 0:
        pge.at_time (1.0, timer)
        s = "%d" % seconds_left
        if previous != None:
            previous.rm ()
        previous = pge.text (0.8, 0.9, s, white, 100, 1)
        seconds_left -= 1


def out_of_time ():
    global loser, winner
    if not winner:
        loser = True
        pge.text (0.3, 0.7, "Loser", white, 100, 1)
        pge.at_time (4.0, finish_game)


def main ():
    global gb, winner, loser, seconds_left

    b1, b2, b3, b4 = placeBoarders (boarder, wood_dark)
    place_boxes ()
    t1 = placeTriangle ([0.2, 0.4], [0.4, 0.4], [0.3, 0.5], white)
    t2 = placeTriangle ([0.6, 0.4], [0.8, 0.4], [0.7, 0.5], white)
    gb = placeBall (gold, 0.19, 0.8, 0.05).mass (1.25)

    print("before run")
    pge.gravity ()
    # pge.dump_world ()
    pge.draw_collision (True, False)
    pge.slow_down (slowdown)  # slows down real time by a factor of
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.register_handler (mouse_hit, [MOUSEBUTTONDOWN])
    pge.display_set_mode ([800, 800])
    # pge.display_fullscreen (True)
    pge.local_fps ()
    seconds_left = 10*slowdown
    timer ()
    pge.run (10.0)
    out_of_time ()
    pge.run (4.0)
    pge.finish_record ()


print("before main()")
main ()
