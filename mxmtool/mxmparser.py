#
#  mxmparser -
#

from mxmout import *
from mxmutils import *
from tempfile import NamedTemporaryFile

import mxmmaxima
import mxmstack
import string
import sys
import os


tokens        = [ '<code>', '<eof>' ]
keywords      = [ 'polynomial', 'terms', 'initialise', 'term', 'finalise', 'begin', 'end' ]
commentLeader = '//'


#
#  internalError - displays the internal error message and the line of input
#                  causing the problem and exit(1).
#

def internalError (message):
    stop()
    print message
    sys.exit(1)


class parse:
    #
    #  the constructor for parse, perform parsing and output the result.
    #

    def __init__ (self, filein, fileout, language, verbose):
        self.filename = filein
        self.outputFile = fileout
        self.language = language
        self.lineno = 1
        self.column = 0
        self.polynomials = []
        self.embedded = []
        self.nTerms = 0
        self.lastNumber = 0
        self.contents = ""
        self.readContents()
        self.parse()
        self.parseMaximaOutput(self.maxima(verbose))
        self.issueResults()


    #
    #  parseMaximaOutput - call mxmmaxima.parse and place all polynomial terms into self.polynomials
    #

    def parseMaximaOutput (self, lines):
        l = string.join(lines, '')
        # print "maxima produced:", l
        p = mxmmaxima.parse(self.filename, self.lineno, self.language, l)
        m = p.getPolynomials(self.nTerms)
        if m != None:
            if self.nTerms == len(m):
                # print m
                self.polynomials = m
            else:
                internalError('expecting ' + str(self.nTerms) + ' terms')

    #
    #  makeTemporary - return a temporary filename
    #

    def makeTemporary (self):
        return NamedTemporaryFile(delete=False).name


    #
    #
    #

    def seen (self, line, sequence):
        if len(line)>len(sequence):
            return line[:len(sequence)] == sequence
        else:
            return line == sequence


    def writeEmbedded (self, f):
        lines = self.embedded[-1]
        for l in lines.split ('\n'):
            line = l.lstrip().rstrip()
            f.write(line + '\n')
            # print line
        f.write('stringout("outfile.m",%);\n')
        f.write('quit();\n')


    #
    #  maxima - call maxima and transform the equation into polynomials.
    #

    def maxima (self, verbose):
        i = self.makeTemporary()
        o = self.makeTemporary()
        f = open(i, 'w')
        self.writeEmbedded (f)
        f.close()
        c = 'maxima -b %s > %s\n' % (i, o)
        m = []
        if os.system(c) == 0:
            c = "rm %s\n" % o
            os.system(c)
            if verbose:
                printf("maxima finished\n")
                os.system("cat " + o)
            o = "outfile.m"
            if os.path.exists (o):
                if verbose:
                    printf("maxima generated output file\n")
            else:
                internalError ("maxima has not generated the file output.m")
            m = open(o, 'r').readlines()
            if verbose:
                print "output from maxima is:"
                print string.join(m, '')
            c = "rm %s\n" % i
            os.system(c)
            c = "rm %s\n" % o
            os.system(c)
        else:
            c = 'maxima -b %s\n' % i
            os.system(c)
            c = "rm %s\n" % i
            os.system(c)
            c = "rm %s\n" % o
            os.system(c)
            syntaxError('maxima failed to process equation')
        return m


    #
    #  issueResults - flushes out the embedded code and polynomials to
    #                 the required output file (or stdout).
    #

    def issueResults (self):
        #
        #  initialisation
        #
        if self.outputFile == '-':
            f = sys.stdout
        else:
            f = open (self.outputFile, 'w')
        f.write(self.embedded[0])

        for i in range(1, len(self.embedded)-2):
            f.write(self.embedded[i])
            f.write(self.polynomials[i-1])
            f.write(";\n")
        #
        #  finalisation
        #
        f.write(self.embedded[-2])
        f.flush()
        if self.outputFile != '-':
            f.close()


    #
    #  readContents - reads the contents of filename and remvoves all comments
    #                 and removes all embedded code.
    #

    def readContents (self):
        self.contents = self.stripComments(self.filename)
        self.contents, self.embedded = self.removeEmbeddedCode(self.contents)
        self.contents += " <eof>"
        # print self.contents
        # print self.embedded


    #
    #  stripComments - remove all text to the right of // for each line
    #                  and return the contents of the filename.
    #

    def stripComments (self, filename):
        global commentLeader
        try:
            contents = ""
            for line in open(filename, 'r').readlines():
                i = string.rfind(line, commentLeader)
                if i == -1:
                    contents += line
                else:
                    contents += line[:i]
            return contents
        except:
            internalError("cannot open " + filename)


    #
    #  removeEmbeddedCode - remove all text between { and } inclusive.
    #                       It is replaced by <code> and the text
    #                       is placed into a list.
    #                       The altered text is returned together with the
    #                       list.
    #

    def removeEmbeddedCode (self, contents):
        new = ""
        code = ""
        codeList = []
        inside = 0
        for c in contents:
            if inside > 0:
                if c == '{':
                    inside += 1
                elif c == '}':
                    inside -= 1
                if inside == 0:
                    codeList += [code]
                    new += " <code> "
                    code = ""
                else:
                    code += c
            else:
                if c == '{':
                    inside = 1
                else:
                    new += c
        return new, codeList


    #
    #  syntaxError - prints an error message.
    #

    def syntaxError (self, default, alternative):
        printHeader(self.filename, self.lineno)
        if alternative == None:
            printf(default)
        else:
            printf(alternative)
        printf("\n")
        print self.contents


    #
    #  skipWhite - skips white text
    #

    def skipWhite (self):
        while isWhite(self.contents[0]):
            if self.contents[0] == '\n':
                self.column = 0
                self.lineno += 1
            self.contents = self.contents[1:]


    #
    #  expect - eats token from the contents, if it does not see
    #           token then it issues a syntaxError.
    #

    def expect (self, token, message = None):
        self.skipWhite()
        if len(self.contents)>len(token):
            if token == self.contents[:len(token)]:
                self.contents = self.contents[len(token):]
                self.column += len(token)
                self.skipWhite()
            else:
                self.syntaxError('expecting ' + token, message)
                self.syntaxError('seen ' + self.contents[:20], None)
        elif self.contents != token:
            self.syntaxError('expecting ' + token, message)
            self.syntaxError('seen ' + self.contents[:20], None)


    #
    #  seenNumber - returns True if a number is seen and it sets lastNumber with
    #               the decimal value
    #

    def seenNumber (self):
        self.skipWhite()
        self.lastNumber = 0
        if isdigit(self.contents[0]):
            while isdigit(self.contents[0]):
                self.lastNumber *= 10
                self.lastNumber += ord(self.contents[0])-ord('0')
                self.contents = self.contents[1:]
                self.column += 1
            self.skipWhite()
            return True
        return False


    #
    #  parsePolynomialTerms
    #

    def parsePolynomialTerms (self):
        self.expect('polynomial')
        self.expect('terms')
        if self.seenNumber():
            self.nTerms = self.lastNumber
        else:
            self.syntaxError('expecting number denoting the number of terms')


    #
    #  parseInitialisation - initialise <code>
    #

    def parseInitialisation (self):
        self.expect('initialise')
        self.expect('<code>', '{ embedded initialisation sequence }')


    #
    #  parseFinalise - finalise <code>
    #

    def parseFinalise (self):
        self.expect('finalise')
        self.expect('<code>', '{ embedded finalisation sequence }')


    #
    #  parseMaxima - <code>
    #

    def parseMaxima (self):
        self.expect('<code>', '{ maxima code sequence expected }')


    #
    #  parseTerm - term <number>
    #

    def parseTerm (self, no):
        self.expect('term')
        if self.seenNumber():
            if self.lastNumber == no:
                s = '%d'% no
                self.expect('<code>', '{ embedded code for term ' + s + ' + expected }')
            else:
                self.syntaxError('out of sequence term, expecting ' + s)


    #
    #  parseTerms - { term <number }
    #

    def parseTerms (self):
        for t in range(self.nTerms):
            self.parseTerm(t)


    #
    #  parse - parse the MXM file.
    #

    def parse (self):
        self.parsePolynomialTerms()
        self.parseInitialisation()
        self.parseTerms()
        self.parseFinalise()
        self.parseMaxima()
