#!/usr/bin/env python

import sys, getopt

from mxmparser import parse


#
#  a program to convert a maxima expression into Modula-2, C, or eqn
#

inputFile   = ""
outputFile  = "-"
defaultLang = "c"
verbose     = False


#
#  usage - issue the max2code usage and quit.
#

def usage (value):
    print "max2code [-h][-v][-o outputfile][-l c][-l m2][--lang=m2][--lang=c] inputfile"
    sys.exit(value)


#
#  parseArgs - handle all user supplied arguments.
#

def parseArgs ():
    global inputFile, outputFile, defaultLang, verbose

    try:
        optlist, remaining = getopt.getopt(sys.argv[1:], ':l:o:v', ['lang=m2', 'lang=c'])
    except getopt.GetoptError:
        usage(1)

    # print optlist
    for opt in optlist:
        if opt[0] == '-h':
            usage(0)
        if opt[0] == '-v':
            verbose = True
        if opt[0] == '-o':
            outputFile = opt[1]
        if opt[0] == '-l':
            if not setDefaultLang(opt[1]):
                usage(1)
    if remaining != []:
        inputFile = remaining[0]


#
#  main - reads in the input file and displays each token.
#

def main ():
    global inputFile, outputFile, defaultLang, verbose

    parseArgs()
    if outputFile == "":
        print "no output file specified"
        usage(1)
    if inputFile == "":
        print "no input file specified"
        usage(1)
    else:
        p = parse(inputFile, outputFile, defaultLang, verbose)


#
#  Init
#

main()
