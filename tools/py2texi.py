#!/usr/bin/python

# Copyright (C) 2016
#               Free Software Foundation, Inc.
# This file is part of GNU Modula-2.
#
# GNU Modula-2 is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Modula-2 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Modula-2; see the file COPYING.  If not, write to the
# Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#

import sys
import os
import glob
import string
import getopt

comments = []
in_class = False
class_name = None
def_name = None
in_comment = False
indentation = 0


#
#  printf - keeps C programmers happy :-)
#

def printf (format, *args):
    print str(format) % args,


def isBlank (l):
    for c in l:
        if not c in string.whitespace:
            return False
    return True

def isComment (l):
    global in_comment, indentation, comments
    i = 0
    for c in l:
        if c in string.whitespace:
            i += 1
        elif c == '#':
            if indentation != i:
                comments = []
            indentation = i
            in_comment = True
            return True
        else:
            in_comment = False
            return False
    return in_comment


def rememberComment (l):
    global comments
    comments += [l]


def isDef (l):
    return isWord (l, "def")

def isClass (l):
    return isWord (l, "class")

def isWord (l, w):
    l = l.lstrip ()
    if (len (l) > len (w)) and (l[:len (w)] == w):
        return True
    return False

def strip_colon (l):
    l = l.strip ()
    if (len (l) > 0) and (l[-1] == ':'):
        l = l[:-1]
    return l

def remove_keyword (l, word):
    l = l.strip ()
    if (len (l) > 3) and (l[:len(word)] == word):
        l = l[len(word):]
        l = l.strip ()
    return l


def rememberDef (l):
    global def_name, class_name

    l = remove_keyword (l, "def")
    def_name = strip_colon (l.lstrip ().strip ())


def rememberClass (l):
    global class_name
    l = remove_keyword (l, "class")
    class_name = strip_colon (l.lstrip ())

def outputComment ():
    global comments

    if comments == []:
        printf ("this section needs commenting\n\n")
    else:
        blank = True
        for l in comments:
            l = l.lstrip ()
            if l[0] == '#':
                if len (l) > 1:
                    l = l[1:]
                else:
                    l = ""
            l = l.lstrip ()
            l = l.strip ()
            if l == "":
                if not blank:
                    print
                blank = True
            else:
                print l
        printf ("\n")

def outputClass ():
    global class_name
    if user_class ():
        printf ("@subsection class %s\n\n", class_name)
        outputComment ()
    comments = []

def user_class ():
    return (class_name != None) and ((len (class_name) > 1) and (class_name[0] != "_"))

def allowed_class ():
    return (class_name == None) or ((len (class_name) > 1) and (class_name[0] != "_"))

def user_def ():
    return (def_name != None) and (len (def_name) > 1) and (def_name[0] != "_")

def outputDef ():
    global def_name, class_name

    if user_def () and allowed_class ():
        if class_name == None:
            printf ("@findex %s\n", def_name)
            printf ("@subsection %s\n\n", def_name)
        else:
            printf ("@findex %s.%s\n", class_name, def_name)
            printf ("@subsection %s.%s\n\n", class_name, def_name)
        outputComment ()
    comments = []

#
#  parsePy - scans the py file for defs, comments and classes.
#

def parsePy (filename):
    global comments
    lines = open (filename).readlines ()
    for l in lines:
        if isBlank (l):
            pass
        elif isComment (l):
            rememberComment (l)
        elif isDef (l):
            rememberDef (l)
            outputDef ()
        elif isClass (l):
            rememberClass (l)
            outputClass ()
        else:
            comments = []


def displayCopyright ():
    print "@c Copyright (C) 2016"
    print "@c Free Software Foundation, Inc."
    print """
@c Permission is granted to copy, distribute and/or modify this document
@c under the terms of the GNU Free Documentation License, Version 1.2 or
@c any later version published by the Free Software Foundation.
"""

def usage (code):
    print "py2texi.py [-h][-uupnode][-ffilename]"
    sys.exit (code)

def collectArgs ():
    filename=""
    try:
        optlist, list = getopt.getopt (sys.argv[1:],':hf:')
    except getopt.GetoptError:
        usage (1)
    for opt in optlist:
        if opt[0] == '-h':
            usage (0)
        if opt[0] == '-f':
            filename = opt[1]
    return filename


filename = collectArgs ()

if filename == "":
    usage (1)
else:
    parsePy (filename)
