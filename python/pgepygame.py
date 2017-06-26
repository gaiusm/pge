#!/usr/bin/env python

import os, pygame, string, sys, getopt, math, struct
from pygame.locals import *
from socket import *


#
#  global variables
#
versionNumber     = '0.4'
BoardEdge         = 40
#
resolution        = (1024, 1024)
#
#
Black             = (0, 0, 0)
lightGrey         = (200, 200, 200)
fullscreen        = False
debugging         = False
programName       = "GNU PGE"
pgePort           = 6000

call              = {}

colTOid           = {}
idTOcol           = {}
maxColour         = 0


#
#  printf - keeps C programmers happy :-)
#

def printf (format, *args):
    print str(format) % args,

#
#  error - issues an error message and exits.
#

def error (format, *args):
    print str(format) % args,
    sys.exit(1)


#
#  debugf - issues prints if debugging is set
#

def debugf (format, *args):
    global debugging
    if debugging:
        print str(format) % args,


#
#  flip - returns the y value flipped against the resolution.
#

def flip (y):
    global resolution

    return resolution[1]-y


#
#  initScreen - initialise the screen to the desired resolution.
#

def initScreen ():
    global screen, background, fullscreen, resolution, lightGrey

    pygame.init()
    if fullscreen:
        screen = pygame.display.set_mode(resolution, FULLSCREEN)
    else:
        screen = pygame.display.set_mode(resolution)
    pygame.display.set_caption(programName + ' ' + versionNumber)
    background = pygame.Surface(screen.get_size())
    background = background.convert()
    background.fill(lightGrey)

#
#  registerColour - read the r, g, b, from the connection and
#                   looks up the id from the colour dictionary.
#                   It returns the colour id to the connection socket.
#                   If (r, g, b) does not exist then it is added to
#                   the dictionary and a reverse dictionary lookup
#                   is also added.
#

def registerColour (connection):
    global maxColour, colTOid, idTOcol

    connection, bytes = get(connection, 3)
    r, g, b = struct.unpack('BBB', bytes)
    debugf("colour %d, %d, %d\n", r, g, b)
    if not colTOid.has_key((r, g, b)):
        maxColour += 1
        colTOid[(r, g, b)] = maxColour
        idTOcol[maxColour] = (r, g, b)
    debugf("colour id %d\n", colTOid[(r, g, b)])
    connection.send(struct.pack('<I', colTOid[(r, g, b)]))
    return connection


#
#  drawCircle -
#

def drawCircle (connection):
    global idTOcol, screen

    connection, bytes = get(connection, 4*4)
    c, x, y, r = struct.unpack('<IIII', bytes)
    debugf("circle colour %d  x = %d  y = %d,  r = %d\n", c, x, y, r)
    pygame.draw.circle(screen, idTOcol[c], (x, flip(y)), r, 0)
    return connection


#
#  drawPolygon -
#

def drawPolygon (connection):
    connection, bytes = get(connection, 4*2)
    c, n = struct.unpack('<II', bytes)
    debugf("polygon colour %d  sides %d\n", c, n)
    l = []
    i = 0
    while i<n:
        connection, bytes = get(connection, 4*2)
        x, y = struct.unpack('II', bytes)
        # print "point ", x, y
        l += [[x, flip(y)]]
        i += 1
    # print l
    pygame.draw.polygon(screen, idTOcol[c], l, 0)
    return connection


#
#
#

def get (connection, nBytes):
    bytes = ""
    while nBytes>0:
        last = connection.recv(nBytes)
        bytes += last
        nBytes -= len(last)
    return connection, bytes


#
#
#

def setResolution (connection):
    global resolution

    connection, bytes = get(connection, 4*2)
    x, y = struct.unpack('<II', bytes)
    debugf("resolution set to %d, %d\n", x, y)
    resolution = (x, y)
    initScreen()
    return connection


#
#  flipBuffer - flips the screen buffer.
#

def flipBuffer (connection):
    global background

    pygame.display.flip()
    # background.fill(lightGrey)
    return connection


#
#  serveRPC - sets up a server TCP socket and calls the correct
#             function depending upon the first character in the
#             packet.
#

def serveRPC ():
    global pgePort, call

    s = socket(AF_INET, SOCK_STREAM)
    # bind it to the server port number
    s.bind(('', pgePort))
    s.listen(1)
    # wait for next client to connect
    connection, address = s.accept()
    while True:
        debugf("before recv\n")
        data = connection.recv(1)
        debugf("received packet %c\n", data)
        if data:
            if call.has_key(data):
                connection = call[data](connection)
            else:
                printf("error unexpected packet %c\n", data)
        else:
            debugf("connection closed\n")
            break
    # connection.close()


#
#
#

def main():
    global call

    call['P'] = drawPolygon
    call['C'] = drawCircle
    call['r'] = setResolution
    call['f'] = flipBuffer
    call['o'] = registerColour
    serveRPC()


main()
