#!/usr/bin/env python

import pge, sys

print "starting boxes"
pge.batch ()

wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)
blue = pge.rgb (0.0, 0.0, 1.0)

boarder = 0.01


def placeBoarders (thickness, color):
    print "placeBoarders"
    pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()

def placeBox (p, w, c):
    return pge.box (p[0], p[1], w, w, c)

def main ():
    pge.record ()
    placeBox ([0.4, 0.4], 0.1, red).fix ()
    placeBoarders (boarder, wood_dark)
    placeBox ([0.47, 0.7], 0.1, blue).mass (1.0)
    pge.gravity ()
    pge.run (3.0)
    pge.finish_record ()

print "before main()"
main ()
