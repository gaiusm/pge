#!/usr/bin/env python

import sys
import getopt

# object codes
fig_o_customColor, fig_o_ellipse, fig_o_polygon, fig_o_spline, fig_o_text, fig_o_arc, fig_o_compound_begin = range(7)
fig_o_compound_end = -6

# polygon type constants
fig_pt_polyline, fig_pt_box, fig_pt_polygon, fig_pt_arcbox, fig_pt_picturebbox = range(1, 6)


#
#  printf - keeps C programmers happy :-)
#

def printf (format, *args):
    print str(format) % args,

colorNo = 0


#
#  chooseOne - cycles through a list.
#

def chooseOne (l):
    global colorNo

    if colorNo >= len(l):
        colorNo = 0
    c = l[colorNo]
    colorNo += 1
    return c


class fig:
    #
    #  initialiser for fig
    #
    def __init__ (self, filein, fileout):
        self.filename = filein
        self.outputFile = fileout
        self.lineno = 1
        self.objects = []
        self.forces = []
        self.readContents()
        self.parse()
        self.generateModula2()
    
    #
    #  readContents - reads the contents of the fig file
    #
    def readContents (self):
        self.contents = open(self.filename, 'r').readlines()
        print self.contents

    def error (self, message):
        printf("%s:%d:%s\n", self.filename, self.lineno, message)
        sys.exit(1)

    def expect (self, token):
        if len(self.contents)>0:
            if len(token) > len(self.contents[0]):
                error("expecting " + token + " " + self.contents[0])
            elif token == self.contents[0][:len(token)]:
                if len(self.contents)>1:
                    self.contents = [self.contents[0][len(token):].lstrip()] + self.contents[1:]
                else:
                    self.contents = [self.contents[0][len(token):].lstrip()]
                if self.contents[0] == '':
                    self.skipLine()
            else:
                error("expecting " + token)
        else:
            error("expecting " + token)

    def isToken (self, token):
        if len(self.contents)>0:
            if len(token) > len(self.contents[0]):
                return False
            elif token == self.contents[0][:len(token)]:
                return True
        return False

    def skipLine (self):
        if len(self.contents)>0:
            self.contents = self.contents[1:]
        else:
            self.contents = []
        self.lineno += 1


    def skipAny (self, l):
        for i in l:
            if self.isToken(i):
                self.expect(i)
                return

    def skipComments (self):
        while self.isToken('#'):
            self.skipLine()

    def skipColours32 (self):
        while self.isToken('0'):
            self.skipLine()
        
    #
    #  skipHeader32 - 
    #

    def skipHeader32 (self):
        self.skipAny(['Landscape', 'Portrait'])
        self.skipAny(['Flush left', 'Center'])
        self.skipAny(['Inches', 'Metric'])
        self.skipLine()  # papersize
        self.skipLine()  # magnification
        self.skipAny(['Multiple', 'Single'])
        self.skipLine()  # transparent
        self.skipComments()
        self.skipLine() # pixels per inch


    #
    #  parsePolygon32 - add the polygon details to self.objects
    #

    def parsePolygon32 (self):
        characteristics = self.contents[0].split()
        self.skipLine ()
        points = self.contents[0].split()
        self.skipLine ()
        if characteristics[-1] == "2":
            points = self.contents[0].split()
            print "force points are", points
            if characteristics[-3] == "0" and characteristics[-2] == "1":
                print "found force backward"
                self.forces += [["force", "backward", points]]
            elif characteristics[-3] == "1" and characteristics[-2] == "0":
                print "found force forward"
                self.forces += [["force", "forward", points]]
        elif characteristics[2] == "0":
            # solid, we treat as fixed
            print "found fixed polygon", points
            self.objects += [["fixed", "polygon", points]]
        else:
            print "found non fixed polygon", points
            self.objects += [["nonfixed", "polygon", points]]


    #
    #  parseEllipse32 - add the circle details to self.objects
    #

    def parseEllipse32 (self):
        ellipse = self.contents[0].split ()
        if ellipse[2] == "0":
            print "found fixed circle", ellipse[-8:-4]
            # solid (ellipse) treat as a fixed circle
            self.objects += [["fixed", "circle", ellipse[-8:-4]]]
        else:
            # treat as a nonfixed circle
            print "found non fixed circle", ellipse[-8:-4]
            self.objects += [["nonfixed", "circle", ellipse[-8:-4]]]
        self.skipLine ()


    #
    #  parseObjects32 - 
    #

    def parseObjects32 (self):
        while (self.isToken('%d' % fig_o_customColor) or
               self.isToken('%d' % fig_o_ellipse) or
               self.isToken('%d' % fig_o_polygon) or
               self.isToken('%d' % fig_o_spline) or
               self.isToken('%d' % fig_o_text) or
               self.isToken('%d' % fig_o_arc)):
            if self.isToken('%d' % fig_o_customColor):
                self.skipColours32()
            elif self.isToken('%d' % fig_o_ellipse):
                self.parseEllipse32 ()
            elif self.isToken('%d' % fig_o_polygon):
                self.parsePolygon32 ()
            elif self.isToken('%d' % fig_o_spline):
                self.skipLine ()
            elif self.isToken('%d' % fig_o_text):
                self.skipLine ()
            elif self.isToken('%d' % fig_o_arc):
                self.skipLine ()


    #
    #  parse32 - parse #FIG 3.2
    #

    def parse32 (self):
        self.skipHeader32 ()
        self.parseObjects32 ()


    #
    #  boilerPlate - detect version number and parse a known format
    #

    def boilerPlate (self):
        self.expect("#FIG")
        if self.isToken("3.2"):
            self.expect("3.2")
            self.skipLine()
            self.parse32()
        else:
            self.error("unsupported fig version")


    #
    #  parse - read in useful objects (ignore the rest)
    #

    def parse (self):
        self.boilerPlate()


    def examinePoint (self, x, y):
        if self.minp == -1:
            self.minp = x
        if self.maxp == -1:
            self.maxp = x
        self.minp = min(self.minp, min(x, y))
        self.maxp = max(self.maxp, max(x, y))
        return self.minp, self.maxp


    def examinePolygon (self, o):
        for i in range(0, len(o[2]), 2):
            x = int(o[2][i])
            y = int(o[2][i+1])
            self.minp, self.maxp = self.examinePoint (x, y)
        return self.minp, self.maxp
            

    def examineCircle (self, o):
        self.minp, self.maxp = self.examinePoint (int(o[2][0])+int(o[2][2]),
                                                  int(o[2][1])+int(o[2][3]))
        self.minp, self.maxp = self.examinePoint (int(o[2][0])-int(o[2][2]),
                                                  int(o[2][1])-int(o[2][3]))
        return self.minp, self.maxp


    def examineExtent (self, o):
        if o[1] == 'circle':
            return self.examineCircle (o)
        elif o[1] == 'polygon':
            return self.examinePolygon (o)
        else:
            self.error('unexpected object: ' + o[1])


    def findExtents (self):
        self.minp, self.maxp = -1, -1
        for o in self.objects:
            print "finding extent of", o
            self.minp, self.maxp = self.examineExtent(o)
        return self.minp, self.maxp


    def relScale (self, n):
        d = self.maxp-self.minp
        return (n*100)/d


    def absScale (self, n):
        return self.relScale (n-self.minp)


    def doFract (self, n):
        if (n<-100) or (n>100):
            print n, "error"
            # self.error("incorrect position calculated")
        if n == 0:
            self.fo.write("zero()")
        elif n == 100:
            self.fo.write("one()")
        elif n>=0:
            sn = "%d" % n
            self.fo.write("initFract(0,")
            self.fo.write(sn)
            self.fo.write(",100)")
        elif n<0:
            n = -n
            sn = "%d" % n
            self.fo.write("negate(initFract(0,")
            self.fo.write(sn)
            self.fo.write(",100))")


    def doPoint (self, x, y):
        self.fo.write("initPoint (")
        self.doFract(x)
        self.fo.write(", ")
        self.doFract(-y)
        self.fo.write(")")


    def moveTo (self, x, y):
        self.fo.write("   m := moveTo(m, initPoint(")
        self.doFract(x)
        self.fo.write(", ")
        self.doFract(y)
        self.fo.write(")) ;\n")


    def getAbs (self, x, y):
        x = self.absScale(x)
        y = 100-self.absScale(y)
        return x, y


    def getRel (self, x, y):
        x = self.relScale(x)
        y = self.relScale(y)
        return x, y


    def doPopulate (self, style):
        if style == "fixed":
            self.fo.write("""
   m := rootMacro(m) ;
   popWorld.populate(m, TRUE, TRUE) ;
""")
        else:
            self.fo.write("""
   m := rootMacro(m) ;

   popWorld.mass(cardinal(1)) ;
""")
            if self.forces != []:
                print self.forces[0]
                self.doForce (self.forces[0])
            self.fo.write("""
   popWorld.populate(m, FALSE, TRUE) ;
""")


    def checkVectorSum (self, x0, x1, x2):
        ox = x0
        print "x:", x0, x1, x2,
        tx = x0 + x1 + x2
        if tx<0:
            x0 += (-tx)
        elif tx>100:
            x0 -= (tx-100)
        if ox == x0:
            print
        else:
            print "  ->", x0, x1, x2
        return x0, x1, x2


    def snapTriangle (self, x, y, v1x, v1y, v2x, v2y):
        return self.snapAngledRect (x, y, v1x, v1y, v2x, v2y)


    #
    #  snapAngledRect - checks to see that the angled rectangle
    #                   can live within coordinates 0..100
    #

    def snapAngledRect (self, x, y, v1x, v1y, v2x, v2y):
        x, v1x, v2x = self.checkVectorSum(x, v1x, v2x)
        y, v1y, v2y = self.checkVectorSum(100-y, v1y, v2y)
        y = 100-y
        return x, y, v1x, v1y, v2x, v2y


    def doPolygonsM2 (self, style):
        for o in self.objects:
            if (o[0] == style) and (o[1] == 'polygon'):
                if style == 'fixed':
                    colour = chooseOne(['light', 'blue()', 'red()', 'green()', 'purple()'])
                else:
                    colour = chooseOne(['dark', 'yellow()', 'blue()'])
                x, y     = self.getAbs(int(o[2][0]), int(o[2][1]))
                v1x, v1y = self.getRel(int(o[2][2])-int(o[2][0]),
                                       int(o[2][3])-int(o[2][1]))
                v2x, v2y = self.getRel(int(o[2][4])-int(o[2][2]),
                                       int(o[2][5])-int(o[2][3]))

                # v1x = int(o[2][2])-int(o[2][0])
                # v1y = int(o[2][3])-int(o[2][1])
                # v2x = int(o[2][4])-int(o[2][2])
                # v2y = int(o[2][5])-int(o[2][3])
                if len(o[2]) == 8:
                    # three pairs and a return point
                    x, y, v1x, v1y, v2x, v2y = self.snapTriangle(x, y, v1x, v1y, v2x, v2y)
                    self.moveTo(x, y)
                    self.fo.write("   m := triangle (m, TRUE, zero(), ")
                elif len(o[2]) >= 10:
                    # four pair and a return point
                    x, y, v1x, v1y, v2x, v2y = self.snapAngledRect(x, y, v1x, v1y, v2x, v2y)
                    self.moveTo(x, y)
                    self.fo.write("   m := angledRect (m, TRUE, zero(), ")
                self.fo.write(colour)
                self.fo.write(",\n              ")
                self.doPoint(v1x, v1y)
                self.fo.write(",\n              ")
                self.doPoint(v2x, v2y)
                self.fo.write(") ;\n")


    def doCirclesM2 (self, style):
        for o in self.objects:
            if (o[0] == style) and (o[1] == 'circle'):
                if style == 'fixed':
                    colour = chooseOne(['light', 'blue()', 'red()', 'green()', 'purple()'])
                else:
                    colour = chooseOne(['dark', 'yellow()', 'blue()'])
                if o[2][2] == o[2][3]:
                    x, y = self.getAbs(int(o[2][0]), int(o[2][1]))
                    self.moveTo(x, y)
                    radius = "%d" % self.relScale(int(o[2][3]))
                    self.fo.write("   m := circle (m, TRUE, zero(), ")
                    self.fo.write(colour)
                    self.fo.write(", initFract(0, ")
                    self.fo.write(radius)
                    self.fo.write(",100)) ;\n")


    def generateModula2 (self):
        if self.objects != []:
            print "objects are: ", self.objects
            self.minp, self.maxp = self.findExtents()
            print "max extents are:", self.minp, self.maxp
            self.createModule()

    def doStyle (self, style):
        self.doPolygonsM2 (style)
        self.doCirclesM2 (style)
        self.doPopulate (style)

    def createModule (self):
        self.fo = open(self.outputFile, 'w')
        moduleName = self.outputFile.split('.')[0]
        self.fo.write("MODULE ")
        self.fo.write(moduleName)
        self.fo.write(""" ;

IMPORT popWorld ;
IMPORT twoDsim ;

FROM deviceIf IMPORT Colour, red, blue, green, yellow, purple, defineColour ;
FROM Fractions IMPORT Fract, initFract, zero, one, two, cardinal, negate, mult, div, pi ;
FROM Points IMPORT Point, initPoint ;

FROM macroObjects IMPORT Macro, circle, moveTo, up, down, left, right, rotate,
                         append, translate, rootMacro, dup, unRootMacro, initMacro, rectangle,
                         triangle, angledRect ;


CONST
   testCorner = FALSE ;
   testRight  = FALSE ;
   useGroff   = FALSE ;


(*
   placeFixed - 
*)

PROCEDURE placeFixed ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;
""")

        self.doStyle ("fixed")
        self.fo.write("""
END placeFixed ;


(*
   placeNonFixed -
*)

PROCEDURE placeNonFixed ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;
""")

        self.doStyle ("nonfixed")
        self.fo.write("""
END placeNonFixed ;


VAR
   light, dark: Colour ;
BEGIN
   popWorld.init(useGroff) ;
   light := defineColour(initFract(0, 166, 256),
                         initFract(0, 124, 256),
                         initFract(0, 54, 256)) ;
   dark := defineColour(initFract(0, 76, 256),
                        initFract(0, 47, 256),
                        zero()) ;

   placeFixed ;
   twoDsim.gravity(-9.81) ;

   placeNonFixed ;

   twoDsim.simulateFor(25.0)
""")
        self.fo.write("END ")
        self.fo.write(moduleName)
        self.fo.write(".\n")
        self.fo.close()

    def doForceValue (self, v):
        self.fo.write("mult(initFract(10, 0, 1),")
        self.doFract(v)
        self.fo.write(")")

    def doForce (self, f):
        if f[0] == 'force':
            vx, vy = self.getRel (int(f[2][2])-int(f[2][0]),
                                  int(f[2][1])-int(f[2][3]))
            if f[1] == 'backward':
                vx = -vx
                vy = -vy

            self.fo.write("""
   popWorld.velocity(initPoint(""")
            self.doForceValue(vx)
            self.fo.write(", ")
            self.doForceValue(vy)
            self.fo.write(")) ;")


# if __name__ == "__main__":

#
#  usage - issue the fig usage and quit.
#

def usage (value):
    print "fig [-h] inputfile outputfile"
    sys.exit(value)


def main ():
    try:
        optlist, remaining = getopt.getopt(sys.argv[1:], ':h')
    except getopt.GetoptError:
        usage(1)

    for opt in optlist:
        if opt[0] == '-h':
            usage(0)

    if len(remaining) != 2:
        usage(1)
    f = fig(remaining[0], remaining[1])


main()
