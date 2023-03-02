#!/usr/bin/env python3

import pge, sys
from pygame.locals import *


#
#  bubble class which is used to record, colour, circle and children
#  children are bubbles which connect below the current bubble
#

class bubble:
    def __init__ (self, cir, col):
        self.circle = cir
        self.colour = col
        self.circle.fix ()
        self.circle.on_collision (bubble_hits_bubble)
        self.children = []  #  no bubbles attached below this bubble
    #
    #  addChild - adds bubble, b, as a child of self.
    #
    def addChild (self, b):
        self.children += [b]
    #
    #  removeChild - removes all bubbles in blist from the children field.
    #
    def removeChild (self, blist):
        if self.children != []:
            self.children = [x for x in self.children if x not in blist]


bubbleDict = {}  # allows us to obtain a bubble list from a pge circle
currentCircle = None
currentColour = None


#
#  printf - keeps C programmers happy :-)
#

def printf (format, *args):
    sys.stdout.write (str (format) % args)
    sys.stdout.flush ()


#
#  hit_chair - chair callback which destroys an object gradually.
#              param is expected to be a list of two values.
#              the first value is the current hit count and the second
#              is the value at construction.
#

def hit_chair (pge_object, pge_event):
    hit_value = pge_object.get_param ()
    if hit_value == 1:
        pge_object.rm ()
    else:
        hit_value -= 1
        pge_object.set_colour (hit_colour[hit_value])
        pge_object.set_param (hit_value)


#
#     |
#     |
#     +----+
#     |    |
#    x,y

def chair (x, y, width, height, facing_left, thickness, hits):
    if facing_left:
        printf ("about to create leg of chair\n")
        leg = pge.box (x, y, thickness, height/2, hit_colour[-1]).fix ()
        printf ("about to create back of chair\n")
        back = pge.box (x+width-thickness, y, thickness, height, hit_colour[-1]).fix ()
        printf ("about to create back of chair\n")
        seat = pge.box (x, y + height /2, width, thickness, hit_colour[-1]).fix ()
    else:
        printf ("about to create leg of chair\n")
        leg = pge.box (x+width-thickness, y, thickness, height/2, hit_colour[-1]).fix ()
        printf ("about to create back of chair\n")
        back = pge.box (x, y, thickness, height, hit_colour[-1]).fix ()
        printf ("about to create back of chair\n")
        seat = pge.box (x, y + height /2, width, thickness, hit_colour[-1]).fix ()
    seat.on_collision (hit_chair)
    seat.set_param (hits)
    leg.on_collision (hit_chair)
    leg.set_param (hits)
    back.on_collision (hit_chair)
    back.set_param (hits)


#
#  printColour - print the colour string.
#

def printColour (c):
    global colourNames
    print(colourNames[c], end=' ')


#
#  dumpData - display all bubble colours and their chains and children
#

def dumpData (message):
    print("dumpData", message)
    print("bubbleDict", bubbleDict)
    for c in list(bubbleDict.keys ()):
        print("pge circle", end=' ')
        print(" is in a list with: ", end=' ')
        for l in bubbleDict[c]:
            printColour (l.colour)
            if l.children != []:
                print(" [ children: ", end=' ')
                for c in l.children:
                    printColour (c.colour)
                    print(", ", end=' ')
                print("]", end=' ')
            print(", ", end=' ')
        print(" ")

#
#  removeChildren - remove all bubbles in blist from all children in all bubbles.
#

def removeChildren (blist):
    for circle in list(bubbleDict.keys ()):
        for b in bubbleDict[circle]:
            b.removeChild (blist)

#
#  unfreezeList - unfreeze all bubbles in blist and return any children bubbles
#                 of these bubbles.  Remove any reference to these circles/bubbles
#                 as they will be deleted as soon as they hit the bottom edge.
#

def unfreezeList (blist):
    todo = []
    for b in blist:
        print("bubble", b, "should be unfixed")
        b.circle.unfix ()
        if b.circle in bubbleDict:
            todo += bubbleDict[b.circle]
            del bubbleDict[b.circle]
        todo += b.children
        removeChildren (todo)
    return todo


#
#  unfreezeAll - unfreeze all bubbles attached to circle (via children)
#

def unfreezeAll (circle):
    global bubbleDict
    print("unfreezeAll", circle)
    dumpData ("unfreezeAll")
    blist = bubbleDict[circle]
    while blist != []:
        blist = unfreezeList (blist)
    currentCircle.unfix ()
    dumpData ("finished unfreeze")

#
#  bubble_hits_bar - the callback for the bubble hitting the top edge.
#

def bubble_hits_bar (o, e):
    global bubbleDict, currentCircle
    print("bubble_hits_bar", currentCircle)
    if currentCircle != None:
        if currentCircle in bubbleDict:
            print("odd the bubble is already registered")
        else:
            initChain (currentCircle, currentColour)
    currentCircle = None
    dumpData ("end of bubble_hits_bar")

#
#  initChain - create an initial bubble in a chain of one.
#

def initChain (circle, colour):
    global bubbleDict
    b = bubble (circle, colour)
    bubbleDict[circle] = [b]   # the first bubble in a chain is keyed via a circle


#
#  updateChains - adds currentCircle/currentColour bubble to the chain specified by circle.
#

def updateChains (circle):
    global bubbleDict
    print("updateChains")
    blist = bubbleDict[circle]
    print("blist", blist, "len (blist) =", len (blist))
    blist += [bubble (currentCircle, currentColour)]
    print("blistis now", blist, "len (blist) =", len (blist))
    # and update all circle -> chain entries
    for b in blist:
        bubbleDict[b.circle] = blist


#
#  addBubble - Prerequiste  :  circle is a pge object which has not been deleted.
#              Postrequisite:  assuming that circle is already known in the bubbleDict
#                              and if the collided chain has two bubbles of the same colour
#                              then unfreeze these bubble and their children.
#                              A same colour collision is appended to the chain.
#                              A different colour collision creates a new chain with
#                              a single bubble.
#

def addBubble (circle):
    global bubbleDict
    print("addBubble")
    if circle in bubbleDict:
        blist = bubbleDict[circle]
        print(blist, len (blist))
        if blist[0].colour == currentColour:
            print("same colour", blist)
            if len (blist) == 2:
                unfreezeAll (circle)
                return
            else:
                print("not enough of the same colour bubbles to unfreeze them")
                updateChains (circle)
        else:
            print("bubble hit is a different colour")
            b = bubble (currentCircle, currentColour)
            blist[-1].addChild (b)
            bubbleDict[currentCircle] = [b]
        dumpData ("end of addBubble")
    else:
        print("addBubble - does not know about circle", circle)

#
#  bubble_hits_bubble - call back for a circle hitting a frozen bubble.
#

def bubble_hits_bubble (o, e):
    global currentCircle
    print("bubble hits bubble, currentCircle =", currentCircle)
    if currentCircle != None:
        b = e.collision_between ()
        for o in b:
            if o.is_fixed ():
                print("object, o, is fixed", o)
            else:
                print("object, o, is not fixed", o)
            if not currentCircle.is_fixed ():
                addBubble (o)
        currentCircle = None
    dumpData ("end of bubble_hits_bubble")


print("starting frozenbubble")
pge.interactive ()
# pge.batch ()
pge.record ()

white = pge.rgb (1.0, 1.0, 1.0)
t = pge.rgb (1.0/2.0, 2.0/3.0, 3.0/4.0)
wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (0.65, 0.1, 0.2)
steel = pge.rgb (0.5, 0.5, 0.5)
copper = pge.rgb (0.5, 0.3, 0.2)
gold = pge.rgb (0.8, 0.6, 0.15)
ball_size = 0.02
boarder = 0.01
green = pge.rgb (0.1, 0.6, 0.2)
# blue = pge.rgb (0.0, 0.0, 1.0)
blue = pge.rgb (0.0, 100.0/255.0, 1.0)
gap = 0.01
previous = None
seconds_left = None
hit_colour = [gold, copper, steel, wood_dark, wood_light, white]

slowdown = 5
simulatedtime = 60
colourNames = { green: "green",
                red  : "red",
                blue : "blue" }


def finish_game (event, param):
    sys.exit (0)

def placeBoarders (thickness, color):
    print("placeBoarders")
    n = pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()
    e = pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    s = pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    w = pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    return n, e, s, w

def fire (e, colour):
    global currentColour, currentCircle
    mouse = pge.pyg_to_unit_coord (e.pos)
    currentColour = colour
    currentCircle = pge.circle (0.5, 0.21, 0.03, currentColour).mass (1.0)
    currentCircle.put_yvel (7*mouse[1])
    currentCircle.put_xvel ((0.5-mouse[0])*-6.0)


def fire_circle (e):
    if e.button == 1:
        fire (e, red)
    elif e.button == 2:
        fire (e, blue)
    elif e.button == 3:
        fire (e, green)


def mouse_press (e):
    global currentCircle, currentColour
    if currentCircle == None:
        fire_circle (e)


def myquit (e):
    print("goodbye, dumping world")
    pge.dump_world ()
    sys.exit (0)

def delete_ball (o, e):
    print("delete_ball called")
    p = e.collision_between ()
    if p != None and p != []:
        for i in p:
            if i != o:
                i.rm ()

def fire_bubble ():
    global currentCircle, currentColour
    if currentCircle == None:
        currentColour = red
        currentCircle = pge.circle (0.5, 0.1, 0.03, currentColour)
        currentCircle.mass (1.0)
        currentCircle.put_yvel (8.0)
        # pge.dump_world ()

def key_pressed (e):
    if e.key == K_ESCAPE:
        myquit (e)
    elif e.key == K_UP:
        fire_bubble ()


def place_bubble (x, colour):
    global currentColour, currentCircle
    currentColour = colour
    currentCircle = pge.circle (0.5, 0.21, 0.03, currentColour).mass (1.0)
    currentCircle.put_yvel (7.0)
    currentCircle.put_xvel ((0.5-x)*-6.0)
    pge.run (0.2)

#
#
#

def createLevel ():
    for x in [0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8]:
        place_bubble (x, red)
    for x in [0.2, 0.3, 0.4, 0.5, 0.6, 0.7]:
        place_bubble (x+0.07, red)
    for x in [0.3, 0.42, 0.54, 0.66]:
        place_bubble (x, blue)


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
    global g, blue, steel, slowdown, seconds_left

    n, e, s, w = placeBoarders (boarder, wood_dark)
    s.on_collision (delete_ball)
    n.on_collision (bubble_hits_bar)
    # platform = pge.box (0.1, 0.1, 0.2, 0.05, steel).fix ()
    # platform.set_visible (False)
    chair (0.1, 0.1, 0.1, 0.1, False, 0.01, 2)  # left chair
    chair (0.3, 0.1, 0.1, 0.1, False, 0.01, 3)  # left chair
    chair (0.6, 0.1, 0.1, 0.1, True, 0.01, 4)  # right chair
    chair (0.8, 0.1, 0.1, 0.1, True, 0.01, 5)  # right chair
    print("before run")
    pge.gravity ()
    pge.dump_world ()
    pge.draw_collision (False, False)
    pge.slow_down (6.0)  # slows down real time by a factor of
    pge.fps (200)
    pge.display_set_mode ([800, 800])
    pge.register_handler (mouse_press, [MOUSEBUTTONDOWN])
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    createLevel ()

    seconds_left = 10 * slowdown
    timer ()
    pge.run (simulatedtime)
    pge.run (10.0)
    pge.finish_record ()


print("before main()")
main ()
