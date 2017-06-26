#
#  mxmmaxima - parse the output of maxima
#

from mxmtree import tree
from mxmout import *
from mxmutils import *

import mxmstack
import sys

tokens   = [ '(', ')', '-', '+', '*', '/', '^', ';' ]

def mystop ():
    pass

class parse:
    #
    #  readFile - reads the complete input file.
    #

    def __init__ (self, filename, line, lang, content):
        self.inputFile = filename
        self.contents = content
        self.powerpos = 0
        self.columnNo = 0
        self.curpos = 0
        self.lineOffset = line
        self.lineNo = 1
        self.startpos = self.curpos
        self.expressionStack = mxmstack.stack(None)
        self.tokenStack = mxmstack.stack(None)
        self.lang = lang
        self.tok = self.getNext()
        self.terms = []


    def getPolynomials (self, nTerms):
        if self.expression():
            e = self.expressionStack.pop()
            for n in reversed(range(nTerms)):
                self.terms += [e.collectPolynomial(n, 't')]
            self.terms.reverse()
            return self.terms
        return None


    #
    #  isWhite - returns True if s[i] is white space.  If i exceeds
    #            the length of s, False is returned.
    #

    def isWhite (self, s, i):
        if i<len(s):
            return (s[i]==' ') or (s[i] == '\n') or (s[i] == '\t')
        else:
            return False


    #
    #  collectText - returns the text found.
    #

    def collectText (self):
        self.tok = self.tokenStack.pop()
        if (self.tok != None) and (self.tok != ""):
            return self.tok
        if self.curpos >= len(self.contents) or self.contents[self.curpos] == ';':
            self.tok = ";"
            self.pos = self.curpos
            return self.tok
        if self.contents[self.curpos] in tokens:
            self.pos = self.curpos
            self.curpos += 1
            self.columnNo += 1
            self.tok = self.contents[self.pos]
            return self.tok

        # curpos index onto non token (literal or variable)
        self.pos = self.curpos
        while True:
            if self.contents[self.curpos] in tokens:
                self.tok = self.contents[self.pos:self.curpos]
                self.columnNo += len(self.tok)
                return self.tok
            else:
                self.curpos += 1


    #
    #  isWhite - returns True if s[i] is white space.  If i exceeds
    #            the length of s, False is returned.
    #

    def isWhite (self, s, i):
        if i<len(s):
            return (s[i]==' ') or (s[i] == '\n') or (s[i] == '\t')
        else:
            return False


    #
    #  skipWhite - skips all white characters
    #

    def skipWhite (self):
        while self.isWhite(self.contents, self.curpos):
            if self.contents[self.curpos] == '\n':
                self.lineNo += 1
                self.columnNo = 0
                self.curpos += 1
                self.startpos = self.curpos
            else:
                self.curpos += 1
                self.columnNo += 1


    #
    #  getNext - returns the next token.
    #

    def getNext (self):
        self.skipWhite()
        token = self.collectText()
        # printf("token is '%s'\n", token)
        # self.printToken(token)
        return token


    #
    #  expression := unaryOrConstTerm { addOperator constTerm } =:
    #

    def expression (self):
        if self.unaryOrTerm():
            while self.addOperator():
                op = self.expressionStack.pop()
                l = self.expressionStack.pop()
                self.term()
                r = self.expressionStack.pop()
                t = tree(op, self.lang, self.internalError)
                t.operands([l, r])
                t.out()
                self.expressionStack.push(t)
            return True
        return False


    #
    #  unaryOrTerm := "+" unarySimpleExpr | "-" unarySimpleExpr | simpleExpr =:
    #
            
    def unaryOrTerm (self):
        if self.seenToken("+"):
            return self.unarySimpleExpr("+")
        elif self.seenToken("-"):
            return self.unarySimpleExpr("-")
        else:
            return self.simpleExpr()


    #
    #
    #

    def unarySimpleExpr (self, op):
        if self.term():
            if op == '-':
                l = self.expressionStack.pop()
                t = tree('-', self.lang, self.internalError)
                t.operands([l])
                self.expressionStack.push(t)
            self.simpleExprFinal()
            return True
        else:
            return False


    def simpleExprFinal (self):
        while self.addOperator():
            if self.term():
                r = self.expressionStack.pop()
                operator = self.expressionStack.pop()
                l = self.expressionStack.pop()
                t = tree(operator, self.lang, self.internalError)
                t.operands([l, r])
                self.expressionStack.push(t)
            

    #
    #  simpleExpr := constTerm { addOperator constTerm } =:
    #

    def simpleExpr (self):
        if self.term():
            self.simpleExprFinal()
            return True
        return False
                

    #
    #  addOperator := "+" | "-" :=
    #

    def addOperator (self):
        if self.seenToken("+"):
            self.expressionStack.push('+')
            return True
        if self.seenToken("-"):
            self.expressionStack.push('-')
            return True
        return False


    #
    #  term := factor { mulOperator factor } =:
    #

    def term (self):
        if self.factor():
            while True:
                operator = "*"
                if self.mulOperator():
                    operator = self.expressionStack.pop()
                if self.factor():
                    r = self.expressionStack.pop()
                    l = self.expressionStack.pop()
                    t = tree(operator, self.lang, None)
                    t.operands([l, r])
                    self.expressionStack.push(t)
                else:
                    return True
        else:
            return False


    #
    #  mulOperator := "*" | "/"  =:
    #

    def mulOperator (self):
        if self.seenToken("*"):
            self.expressionStack.push('*')
            return True
        if self.seenToken("/"):
            self.expressionStack.push('/')
            return True
        return False


    #
    #  factor := "(" expression ")" | atom [ "^" factor ] =:
    #

    def factor (self):
        if self.seenToken('('):
            # print "factor -> ( expression )"
            self.expression()
            self.expect(')')
            # print "factor True"
            return True
        elif self.litorvar():
            if self.seenToken('^'):
                # print "factor ^ "
                l = self.expressionStack.pop()
                self.factor()
                r = self.expressionStack.pop()
                t = tree('^', self.lang, None)
                t.operands([l, r])
                self.expressionStack.push(t)
            else:
                # print "not seen ^"
                pass
            # print "factor True"
            return True
        else:
            # print "factor False"
            return False


    #
    #  litorvar - consume the current token and push it as an atom to the expression stack.
    #

    def litorvar (self):
        global tokens
        if not (self.tok in tokens):
            self.expressionStack.push(tree(self.tok, self.lang, None))
            self.tok = self.getNext()
            return True
        else:
            return False


    #
    #  seenToken - returns True if token, t, has been seen.  If True the token is consumed.
    #

    def seenToken (self, t):
        if t == self.tok:
            self.tok = self.getNext()
            return True
        else:
            return False


    #
    #  expect - expects a token, t.
    #

    def expect (self, t):
        if t == self.tok:
            self.tok = self.getNext()
        else:
            self.internalError('expecting token ' + t + ' but found ' + self.tok)


    #
    #  internalError - displays the internal error message and the line of input
    #                  causing the problem and exit(1).
    #

    def internalError (self, message):
        self.syntaxError(message)


    #
    #  syntaxError - issue an error message with source file coordination
    #

    def syntaxError (self, message):
        mystop ()
        printHeader(self.inputFile, self.lineNo)
        print self.contents

        j = self.columnNo-len(self.tok)
        s = " " * j
        s += "^" * len(self.tok)
        s += " "
        s += message
        printHeader(self.inputFile, self.lineNo)
        print s
        sys.exit(1)


    #
    #  printToken - displays the current token position.
    #

    def printToken (self, token):
        printHeader(self.inputFile, self.lineNo-1)
        print self.contents

        j = self.columnNo-len(token)
        s = " " * j
        s += "^" * len(token)
        printHeader(self.inputFile, self.lineNo)
        print s
