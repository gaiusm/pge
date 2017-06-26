MODULE test ;

IMPORT popWorld ;
IMPORT twoDsim ;

FROM deviceIf IMPORT Colour, red, blue, green, yellow, purple, defineColour ;
FROM Fractions IMPORT Fract, initFract, zero, one, two, cardinal, negate, div, pi ;
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
   m := moveTo(m, initPoint(initFract(0,0,8550), initFract(0,225,8550))) ;
   m := angledRect (m, TRUE, zero(), light,
              initPoint (initFract (0,8550,8550),initFract (0,0,8550)),
              initPoint (initFract (0,0,8550),initFract (0,225,8550))) ;
   m := moveTo(m, initPoint(initFract(0,8325,8550), initFract(0,450,8550))) ;
   m := angledRect (m, TRUE, zero(), light,
              initPoint (initFract (0,225,8550),initFract (0,0,8550)),
              initPoint (initFract (0,0,8550),initFract (0,2475,8550))) ;
   m := moveTo(m, initPoint(initFract(0,0,8550), initFract(0,2925,8550))) ;
   m := angledRect (m, TRUE, zero(), light,
              initPoint (initFract (0,8550,8550),initFract (0,0,8550)),
              initPoint (initFract (0,0,8550),initFract (0,225,8550))) ;
   m := moveTo(m, initPoint(initFract(0,0,8550), initFract(0,450,8550))) ;
   m := angledRect (m, TRUE, zero(), light,
              initPoint (initFract (0,225,8550),initFract (0,0,8550)),
              initPoint (initFract (0,0,8550),initFract (0,2475,8550))) ;
   m := moveTo(m, initPoint(initFract(0,2677,8550), initFract(0,1462,8550))) ;
   m := circle (m, TRUE, zero(), red(), initFract(0, 287, 8550)) ;

         m := rootMacro(m) ;
         popWorld.populate(m, TRUE, TRUE) ;

   m := rootMacro(m) ;
   popWorld.populate(m, TRUE, TRUE)
END placeFixed ;


(*
   placeNonFixed -
*)

PROCEDURE placeNonFixed ;
VAR
   m: Macro ;
BEGIN
   m := initMacro() ;
   m := moveTo(m, initPoint(initFract(0,4972,8550), initFract(0,1170,8550))) ;
   m := circle (m, TRUE, zero(), yellow(), initFract(0, 282, 8550)) ;

         m := rootMacro(m) ;

         popWorld.mass(cardinal(1)) ;
         popWorld.velocity(initPoint(zero(), zero())) ;
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
END test.
