MODULE circle ;

IMPORT twoDsim ;
IMPORT deviceIf ;

FROM deviceIf IMPORT Colour ;
FROM Fractions IMPORT Fract, initFract, zero, one, two, cardinal, negate, div, pi ;
FROM libc IMPORT printf ;

CONST
   boarder = 0.01 ;

VAR
   wood_light,
   wood_dark,
   red, blue : CARDINAL ;


PROCEDURE placeBoarders (thickness: REAL; color: CARDINAL) ;
VAR
   b: CARDINAL ;
BEGIN
   b := twoDsim.box (0.0, 0.0, 1.0, thickness, color) ;
   b := twoDsim.fix (b) ;
   b := twoDsim.box (0.0, 0.0, thickness, 1.0, color) ;
   b := twoDsim.fix (b) ;
   b := twoDsim.box (1.0-thickness, 0.0, thickness, 1.0, color) ;
   b := twoDsim.fix (b) ;
   b := twoDsim.box (0.0, 1.0-thickness, 1.0, thickness, color) ;
   b := twoDsim.fix (b)
END placeBoarders ;


PROCEDURE placeBox (x, y, w: REAL; c: CARDINAL) : CARDINAL ;
BEGIN
   RETURN twoDsim.box (x, y, w, w, c)
END placeBox ;


(*
   initColours - 
*)

PROCEDURE initColours ;
BEGIN
   wood_light := deviceIf.defineColour (initFract (0, 166, 256),
                                        initFract (0, 124, 256),
                                        initFract (0, 54, 256)) ;
   wood_dark := deviceIf.defineColour (initFract (0, 76, 256),
                                       initFract (0, 47, 256),
                                       zero ()) ;
   red := deviceIf.defineColour (one (), zero (), zero ()) ;
   blue := deviceIf.defineColour (zero (), zero (), one ())
END initColours ;


PROCEDURE startWorld ;
VAR
   b: CARDINAL ;
BEGIN
   b := placeBox (0.4, 0.4, 0.1, red) ;
   b := twoDsim.fix (b) ;
   placeBoarders (boarder, wood_dark) ;
   b := twoDsim.circle (0.53, 0.7, 0.04, blue) ;
   b := twoDsim.mass (b, 1.0) ;
   twoDsim.gravity (-9.81) ;

   twoDsim.simulateFor (3.0)
END startWorld ; 


BEGIN
   deviceIf.useGroff ;
   twoDsim.drawCollisionFrames (TRUE, TRUE) ;
   twoDsim.fps (80.0) ;
   initColours ;
   startWorld
END circle.
