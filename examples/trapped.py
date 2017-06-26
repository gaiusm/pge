#!/usr/bin/env python

import pge, sys
# import pgemacro

print "starting exampleBoxes"
pge.batch ()

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
gap = 0.01
captured = None


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

def double_it (o, e):
    print "double_it", o._name()
    return
    p = e.collision_between ()
    print "after between ->", p
    if p != None and p != []:
        for i in p:
            if i != o:
                x = i.get_xvel ()
                y = i.get_yvel ()
                print "x velocity of", i, "is", x, "y velocity is", y
                i.put_xvel (x*1.1)
                # i.put_yvel (y*1.1)

def placeRamps ():
    r1 = pge.poly4 (0.3 , 0.4,
                    0.85, 0.42,
                    0.85, 0.43,
                    0.3 , 0.41, wood_dark).fix ()
    r2 = pge.poly4 (0.15, 0.6,
                    0.75, 0.58,
                    0.75, 0.57,
                    0.15, 0.59, wood_dark).fix ()

                
def placeTriangle (p0, p1, p2, colour):
    t = pge.poly3 (p0[0], p0[1], p1[0], p1[1], p2[0], p2[1], colour).on_collision (double_it)
    t.fix ()

def placeSilos ():
    for x in [0.3, 0.6]:
        s = pge.poly4 (x, 0.0,
                       x, 0.07,
                       x+0.01, 0.07,
                       x+0.01, 0.0, wood_dark).fix ()
                       

def callMe (p):
    print "box has collided!"

def play_wood (o, e):
    pge.play ("/home/gaius/Sandpit/cluedo/sounds/bounce.wav")

def play_crack (o, e):
    pge.play ("/home/gaius/Sandpit/penguin-tower/sounds/crack-single.wav")

def play_bounce (o, e):
    pge.play ("/home/gaius/Sandpit/cluedo/sounds/cardsnap.wav")

def delete_it (o, e):
    global captured

    if o==captured:
        print "no need to delete this ball"
    else:
        print "yes need to delete", o

def box_of (thickness, pos, width, color):
    global captured

    e1 = pge.box (pos[0], pos[1], width, thickness, color).fix ().on_collision (delete_it)
    e2 = pge.box (pos[0], pos[1], thickness, width, color).fix ().on_collision (delete_it)
    e3 = pge.box (pos[0]+width-thickness, pos[1], thickness, width, color).fix ().on_collision (delete_it)
    e4 = pge.box (pos[0], pos[1]+width-thickness, width, thickness, color).fix ().on_collision (delete_it)
    captured = placeBall (blue, pos[0]+2.0*thickness+0.05, pos[1]+1.0*thickness+0.05, 0.05).mass (1.5)

def main ():
    sb = placeBall (steel, 0.57, 0.8, 0.05).mass (1).on_collision (play_crack)
    cb = placeBall (copper, 0.81, 0.8, 0.05).mass (.75).on_collision (play_bounce)
    gb = placeBall (gold, 0.19, 0.7, 0.05).mass (1.25).on_collision (play_bounce)

    f = placeBall (wood_light, 0.95, 0.05, 0.1).fix ()
    # l = placeBox ([0.3, 0.3], [0.3, 0.5], [0.5, 0.5], [0.5, 0.3], white)
    t1 = placeTriangle ([0.2, 0.3], [0.4, 0.3], [0.3, 0.4], white)
    t2 = placeTriangle ([0.6, 0.3], [0.8, 0.3], [0.7, 0.4], white)
    placeRamps ()
    b1, b2, b3, b4 = placeBoarders (boarder, wood_dark)
    for b in [b1, b2, b3, b4]:
        b.on_collision (play_crack)
    box_of (boarder, [0.0, 0.8], 0.2, wood_dark)
    placeSilos ()

    print "before run"
    pge.gravity ()
    pge.dump_world ()
    pge.run (18.0)
    pge.finish ()

print "before main()"
main ()
