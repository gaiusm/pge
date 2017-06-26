MODULE foo ;

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
   m := moveTo(m, initPoint(zero(), initFract(0,98,100))) ;
   m := angledRect (m, TRUE, zero(), light,
              initPoint (initFract(0,97,100), zero()),
              initPoint (zero(), negate(initFract(0,2,100)))) ;
   m := moveTo(m, initPoint(initFract(0,2,100), initFract(0,3,100))) ;
   m := angledRect (m, TRUE, zero(), blue(),
              initPoint (initFract(0,97,100), zero()),
              initPoint (zero(), negate(initFract(0,2,100)))) ;
   m := moveTo(m, initPoint(one(), initFract(0,98,100))) ;
   m := angledRect (m, TRUE, zero(), red(),
              initPoint (zero(), negate(initFract(0,97,100))),
              initPoint (negate(initFract(0,3,100)), zero())) ;
   m := moveTo(m, initPoint(initFract(0,3,100), initFract(0,98,100))) ;
   m := angledRect (m, TRUE, zero(), green(),
              initPoint (zero(), negate(initFract(0,97,100))),
              initPoint (negate(initFract(0,3,100)), zero())) ;
   m := moveTo(m, initPoint(initFract(0,4,100), initFract(0,83,100))) ;
   m := angledRect (m, TRUE, zero(), purple(),
              initPoint (initFract(0,76,100), negate(initFract(0,2,100))),
              initPoint (negate(initFract(0,3,100)), negate(initFract(0,2,100)))) ;
   m := moveTo(m, initPoint(initFract(0,15,100), initFract(0,63,100))) ;
   m := angledRect (m, TRUE, zero(), light,
              initPoint (zero(), negate(initFract(0,2,100))),
              initPoint (initFract(0,79,100), initFract(0,6,100))) ;
   m := moveTo(m, initPoint(initFract(0,47,100), initFract(0,14,100))) ;
   m := angledRect (m, TRUE, zero(), blue(),
              initPoint (zero(), negate(initFract(0,10,100))),
              initPoint (initFract(0,5,100), zero())) ;
   m := moveTo(m, initPoint(initFract(0,50,100), initFract(0,24,100))) ;
   m := triangle (m, TRUE, zero(), red(),
              initPoint (negate(initFract(0,8,100)), negate(initFract(0,7,100))),
              initPoint (initFract(0,15,100), zero())) ;
   m := moveTo(m, initPoint(initFract(0,17,100), initFract(0,15,100))) ;
   m := angledRect (m, TRUE, zero(), green(),
              initPoint (zero(), negate(initFract(0,10,100))),
              initPoint (initFract(0,5,100), zero())) ;
   m := moveTo(m, initPoint(initFract(0,77,100), initFract(0,15,100))) ;
   m := angledRect (m, TRUE, zero(), purple(),
              initPoint (zero(), negate(initFract(0,10,100))),
              initPoint (initFract(0,5,100), zero())) ;
   m := moveTo(m, initPoint(initFract(0,20,100), initFract(0,25,100))) ;
   m := triangle (m, TRUE, zero(), light,
              initPoint (negate(initFract(0,8,100)), negate(initFract(0,7,100))),
              initPoint (initFract(0,15,100), zero())) ;
   m := moveTo(m, initPoint(initFract(0,80,100), initFract(0,25,100))) ;
   m := triangle (m, TRUE, zero(), blue(),
              initPoint (negate(initFract(0,8,100)), negate(initFract(0,7,100))),
              initPoint (initFract(0,15,100), zero())) ;
   m := moveTo(m, initPoint(initFract(0,5,100), initFract(0,49,100))) ;
   m := angledRect (m, TRUE, zero(), red(),
              initPoint (initFract(0,51,100), negate(initFract(0,2,100))),
              initPoint (zero(), negate(initFract(0,2,100)))) ;
   m := moveTo(m, initPoint(initFract(0,82,100), initFract(0,42,100))) ;
   m := triangle (m, TRUE, zero(), green(),
              initPoint (negate(initFract(0,6,100)), negate(initFract(0,5,100))),
              initPoint (initFract(0,10,100), zero())) ;

   m := rootMacro(m) ;
   popWorld.populate(m, TRUE, TRUE) ;

END placeFixed ;


(*
   placeNonFixed -
*)

PROCEDURE placeNonFixed ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;
   m := moveTo(m, initPoint(initFract(0,9,100), initFract(0,91,100))) ;
   m := circle (m, TRUE, zero(), dark, initFract(0, 3,100)) ;
   m := moveTo(m, initPoint(initFract(0,85,100), initFract(0,90,100))) ;
   m := circle (m, TRUE, zero(), yellow(), initFract(0, 3,100)) ;
   m := moveTo(m, initPoint(initFract(0,75,100), initFract(0,73,100))) ;
   m := circle (m, TRUE, zero(), blue(), initFract(0, 3,100)) ;
   m := moveTo(m, initPoint(initFract(0,20,100), initFract(0,89,100))) ;
   m := circle (m, TRUE, zero(), dark, initFract(0, 3,100)) ;

   m := rootMacro(m) ;

   popWorld.mass(cardinal(1)) ;

   popWorld.velocity(initPoint(mult(initFract(10, 0, 1),zero()), mult(initFract(10, 0, 1),initFract(0,11,100)))) ;
   popWorld.populate(m, FALSE, TRUE) ;

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
END foo.
