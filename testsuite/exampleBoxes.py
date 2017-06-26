#!/usr/bin/env python

import pge, sys
# import pgemacro

print "starting exampleBoxes"
pge.batch ()

t = pge.rgb (1.0/2.0, 2.0/3.0, 3.0/4.0)
wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)
metal = pge.rgb (0.5, 0.5, 0.5)
ball_size = 0.04
boarder = 0.01
white = pge.rgb (1.0, 1.0, 1.0)
gap = 0.01

# pge.finish ()
# sys.exit (0)


def play_wood (o):
    print "play_wood - wants to play bounce.wav"
    pge.play ("/home/gaius/Sandpit/cluedo/sounds/bounce.wav")

def play_crack (o):
    print "play_crack - wants to play crack-single.wav"
    pge.play ("/home/gaius/Sandpit/penguin-tower/sounds/crack-single.wav")

def play_bounce (o):
    print "play_bounce - wants to play cardsnap.wav"
    pge.play ("/home/gaius/Sandpit/cluedo/sounds/cardsnap.wav")

def placeBoarders (thickness, color):
    print "placeBoarders"
    e1 = pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    e2 = pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    e3 = pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    e4 = pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()
    for e in [e1, e2, e3, e4]:
        e.on_collision (play_wood)
    return e1, e2, e3, e4


def placeBall (x, y, r):
    return pge.circle (x, y, r, metal)


def crate (x, y, w):
    c = pge.box (x, y, w, w, wood_dark).on_collision (crate_split).set_param ([6, w]).mass (1.0)

def is_odd (e):
    return (e % 2) == 1

def crate_split (p):
    global gap

    print "crate_split", p
    pge.dump_world ()
    e = p.get_param ()
    print "after get_param"
    w = e[1] / 2
    wg = w - gap
    if wg<0.0:
        print "error gap must be >= 0.0 and not", wg
        sys.exit (1)
    if e != None:
        if e[0] == 0:
            print "crate piece completely gone"
            # at the end of 6 collisions the crates disappear
            p.rm ()
            play_crack (p)
        elif is_odd (e[0]):
            pge.process_event ()  # update the velocities of objects (immediately after collision)
            print "crate sub divides"
            # subdivide into smaller crates, every odd bounce
            m = p.get_mass ()
            print "mass of crate is", m
            pge.dump_world ()
            print "get crate colour"
            c = p.get_colour ()
            print "colour of crate is", c
            pge.dump_world ()
            print e
            print "get_xpos"
            x = p.get_xpos () - e[1]/2
            pge.dump_world ()
            y = p.get_ypos () - e[1]/2
            vx = p.get_xvel ()
            vy = p.get_yvel ()
            ax = p.get_xaccel ()
            ay = p.get_yaccel ()
            print "**************** x, y, w, wg = ", x, y, w, wg, vx, vy, ax, ay
            pge.dump_world ()
            print "rm", p
            p.rm ()
            print "finished rm, python dumping world"
            pge.dump_world ()
            for v in [[0, 0], [0, w], [w, 0], [w, w]]:
                print "creating sub box", v, "gap =", wg
                b = pge.box (v[0]+x, v[1]+y, wg, wg, c).mass (m).on_collision (crate_split).velocity (vx, vy).accel (ax, ay)
                print "set_param", [e[0]-1, w]
                b.set_param ([e[0]-1, w])
                pge.dump_world ()
            print "play_crack", p
            play_crack (p)
        else:
            print "crate bounces without breaking"
            # allow collision (bounce) without splitting every even bounce
            p.set_param ([e[0]-1, e[1]])
            play_bounce (p)

def main ():
    c = pge.circle (0.5, 0.5, 0.3, white, -1)
    l = pge.box (0.0, 0.25, 1.0, 0.02, wood_light, 1)
    b1, b2, b3, b4 = placeBoarders (boarder, wood_dark)
    # b = placeBall (0.5, 0.5, 0.02)
    # b.mass (1.0).on_collision (play_bounce).velocity (0.9, 0.0)
    crate (0.6, 0.6, 0.2)
    print "before run"
    pge.gravity ()
    pge.dump_world ()
    pge.run (10.0)
    pge.finish ()

print "before main()"
main ()
