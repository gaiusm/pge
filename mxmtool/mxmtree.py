#
#  mxmtree - handle all the tree creation and walking
#

from mxmutils import *


defaultLang = "c"
atom, node = range(2)
output = ""


#
#  printf - keeps C programmers happy :-)
#

def printf (format, *args):
    print str(format) % args,


#
#  setDefaultLang - sets the default language to either C or Modula-2.
#                   It returns True if successful.
#

def setDefaultLang (lang):
    global defaultLang

    if (lang == "c" or lang == "C"):
        defaultLang = "c"
        return True
    if (lang == "m2" or lang == "M2"):
        defaultLang = "m2"
        return True
    return False


#
#  create a tree entity which is either a node or an atom.
#

class tree:
    global atom, node
    

    def __init__ (self, n, l, e):
        self.name = n
        self.kind = atom
        self.lang = l
        self.error = e
        self.ignore = False

    def operands (self, o):
        self.kind = node
        # print "adding operands", o
        self.operands = o
        if self.lang == "":
            self.error('must set lang by calling the tree constructor')

    def debug (self):
        global output

        output = ""
        self._debug_tree ()
        # if self.lang == "m2":
        #    printf ("(* debug of the tree:  ")
        #    print output,
        #    printf ("  *)\n")
        # if self.lang == "c":
        #    printf ("/* debug of the tree:  ")
        #    print output,
        #    printf ("  */\n")

    def _debug_tree (self):
        global output

        if self.kind == atom:
            output += self.name
        elif self.kind == node:
            output += ' ('
            if len (self.operands) == 1:
                output += self.name
                self.operands[0]._debug_tree ()
            else:
                for i, o in enumerate (self.operands):
                    if o is None:
                        output += "None"
                    else:
                        o._debug_tree ()
                        if i < len (self.operands)-1:
                            output += self.name
            output += ') '

    def out (self):
        global output

        output = ""
        self.capture()
        printf(output)

    def capture (self):
        if self.lang == "m2":
            self.lang_m2()
        if self.lang == "c":
            self.lang_m2()

    def lang_m2 (self):
        global output
        if self.ignore:
            output += '0.0'
            return
        if self.kind == atom:
            if isdigit(self.name[0]):
                output += self.name + '.0'
            elif self.name == '%pi':
                output += 'pi'
            else:
                output += self.name
        else:
            l = self.operands
            if len(l) == 1:
                output += '(' + self.name
                l[0].lang_m2()
                output += ')'
            elif len(l)>1:
                if self.name == '^':
                    if len(l) != 2:
                        self.error('expecting ^ to have two operands only')
                    self.doM2Power()
                else:
                    if len (output)>0 and output[-1]==')':
                        output += ' + '
                    output += '('
                    l[0].lang_m2()
                    for o in self.operands[1:]:
                        output += self.name
                        o.lang_m2()
                    output += ')'

    def doM2Power (self):
        global output
        if self.isToPower('2'):
            output += ' sqr('
            self.operands[0].lang_m2()
            output += ') '
        elif self.isToPower('3'):
            output += ' cub('
            self.operands[0].lang_m2()
            output += ') '
        elif self.isToPower('4'):
            output += ' quart('
            self.operands[0].lang_m2()
            output += ') '
        elif self.isToPower('5'):
            output += ' pent('
            self.operands[0].lang_m2()
            output += ') '
        elif self.isToPower('6'):
            output += ' hex('
            self.operands[0].lang_m2()
            output += ') '
        elif self.isToPower('7'):
            output += ' sept('
            self.operands[0].lang_m2()
            output += ') '
        elif self.isToPower('8'):
            output += ' oct('
            self.operands[0].lang_m2()
            output += ') '
        else:
            output += ' topower('
            self.operands[0].lang_m2()
            output += ', '
            self.operands[1].lang_m2()
            output += ') '

    def isZero (self):
        return self.isVariable('0.0') or self.isVariable('0') or self.ignore

    def isOne (self):
        return self.isVariable('1.0') or self.isVariable('1')

    def setAtom (self, value):
        self.kind = atom
        self.name = value

    def isToPower (self, power):
        return self.name == '^' and self.operands[1].isAtom() and self.operands[1].name == power
    
    def isAtom (self):
        return self.kind == atom

    def isNode (self):
        return self.kind == node

    def isVariable (self, variable):
        return self.isAtom() and self.name == variable

    def isPolynomial (self, nTerm, variable):
        global node
        if (nTerm >= 2) and self.kind == node and self.name == '^' and self.isToPower(str(nTerm)) and self.operands[0].isVariable(variable):
            # * (t ^ nTerm)    (polynomial term 2..n)
            return True
        if self.isVariable(variable) and nTerm == 1:
            # * t     (polynomial term 1)
            return True
        return False


    #
    #  findPolynomial - 
    #

    def findPolynomial (self, nTerm, variable):
        global node, output

        if self.kind == node:
            if self.name == '*':
                if self.operands[0].isPolynomial (nTerm, variable):
                    self.operands[1].reduce()
                    self.operands[1].capture()
                    self.ignore = True
                    return True
                elif self.operands[1].isPolynomial (nTerm, variable):
                    self.operands[0].reduce()
                    self.operands[0].capture()
                    self.ignore = True
                    return True
            i = 0
            for o in self.operands:
                if o.findPolynomial (nTerm, variable):
                    if i > 0:
                        if self.name == '-':
                            output = '-' + output
                i += 1
        return False


    def modifyOperand (self, i, l):
        if i != -1:
            if i == 0:
                if len(self.operands) == 1:
                    self.operands = []
                else:
                    self.operands = self.operands[1:]
            elif i == len(self.operands)-1:
                self.operands = self.operands[:-1]
            else:
                self.operands = self.operands[0:i]+self.operands[i+1:]
        self.operands += l


    #
    #
    #

    def associative (self, operator):
        if self.name == operator:
            finished = False
            while not finished:
                c = -1
                l = []
                for i, o in enumerate(self.operands):
                    if o.isNode() and o.name == operator:
                        l = o.operands
                        c = i
                        break
                else:
                    finished = True
                self.modifyOperand(c, l)


    #
    #  simplify - simplify   * 1.0   * 0.0
    #                        + 0.0
    #

    def simplify (self):
        if self.name == '*':
            finished = False
            while not finished:
                c = -1
                for i, o in enumerate(self.operands):
                    if o.ignore:
                        o.setAtom('problem')
                        o.ignore = False
                        return
                    elif o.isZero():
                        self.setAtom('0')
                        return
                    if self.isOne():
                        c = i
                        break
                else:
                    finished = True
                self.modifyOperand(c, [])
        elif self.name == '+':
            finished = False
            while not finished:
                c = -1
                for i, o in enumerate(self.operands):
                    if o.isZero():
                        stop()
                        c = i
                        break
                else:
                    finished = True
                self.modifyOperand(c, [])
                

    #
    #  reduce - collapse multiple * operators and multiple + operators
    #

    def reduce (self):
        global node

        return
        if self.isNode():
            self.associative('*')
            self.associative('+')
            self.simplify()
            if self.operands != []:
                for o in self.operands:
                    o.reduce()


    #
    #  collectPolynomial - return the expression for the nth Term, nTerm, in the expression.
    #                      The polynomials _must_ be collected in highest order first
    #                      as the tree is destructively returned.  When nTerm == 0 the
    #                      remainder of the tree is returned.
    #

    def collectPolynomial (self, nTerm, variable):
        global output

        self.debug ()
        output = ""
        if nTerm == 0:
            stop()
            # self.reduce()
            self.capture()
        else:
            self.findPolynomial (nTerm, variable)
        return output
