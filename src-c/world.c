/* automatically created by mc from ../world.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#   include "GpopWorld.h"
#   include "GtwoDsim.h"
#   include "GdeviceIf.h"
#   include "GFractions.h"
#   include "GPoints.h"
#   include "GmacroObjects.h"

#   define testCorner FALSE
#   define testRight FALSE
#   define useGroff TRUE
static deviceIf_Colour light;
static deviceIf_Colour dark;

/*
   placeFixed - 
*/

static void placeFixed (void);

/*
   placeNonFixed -
*/

static void placeNonFixed (void);

/*
   placeFixed - 
*/

static void placeFixed (void);

/*
   placeNonFixed -
*/

static void placeNonFixed (void);


/*
   placeFixed - 
*/

static void placeFixed (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_initFract (0, 98, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_initFract (0, 97, 100), Fractions_zero ()), Points_initPoint (Fractions_zero (), Fractions_negate (Fractions_initFract (0, 2, 100))));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 2, 100), Fractions_initFract (0, 3, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_blue (), Points_initPoint (Fractions_initFract (0, 97, 100), Fractions_zero ()), Points_initPoint (Fractions_zero (), Fractions_negate (Fractions_initFract (0, 2, 100))));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_one (), Fractions_initFract (0, 98, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Points_initPoint (Fractions_zero (), Fractions_negate (Fractions_initFract (0, 97, 100))), Points_initPoint (Fractions_negate (Fractions_initFract (0, 3, 100)), Fractions_zero ()));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 3, 100), Fractions_initFract (0, 98, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_green (), Points_initPoint (Fractions_zero (), Fractions_negate (Fractions_initFract (0, 97, 100))), Points_initPoint (Fractions_negate (Fractions_initFract (0, 3, 100)), Fractions_zero ()));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 4, 100), Fractions_initFract (0, 83, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_purple (), Points_initPoint (Fractions_initFract (0, 76, 100), Fractions_negate (Fractions_initFract (0, 2, 100))), Points_initPoint (Fractions_negate (Fractions_initFract (0, 3, 100)), Fractions_negate (Fractions_initFract (0, 2, 100))));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 15, 100), Fractions_initFract (0, 63, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_zero (), Fractions_negate (Fractions_initFract (0, 2, 100))), Points_initPoint (Fractions_initFract (0, 79, 100), Fractions_initFract (0, 6, 100)));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 47, 100), Fractions_initFract (0, 14, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_blue (), Points_initPoint (Fractions_zero (), Fractions_negate (Fractions_initFract (0, 10, 100))), Points_initPoint (Fractions_initFract (0, 5, 100), Fractions_zero ()));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 50, 100), Fractions_initFract (0, 24, 100)));
  m = macroObjects_triangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Points_initPoint (Fractions_negate (Fractions_initFract (0, 8, 100)), Fractions_negate (Fractions_initFract (0, 7, 100))), Points_initPoint (Fractions_initFract (0, 15, 100), Fractions_zero ()));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 17, 100), Fractions_initFract (0, 15, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_green (), Points_initPoint (Fractions_zero (), Fractions_negate (Fractions_initFract (0, 10, 100))), Points_initPoint (Fractions_initFract (0, 5, 100), Fractions_zero ()));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 77, 100), Fractions_initFract (0, 15, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_purple (), Points_initPoint (Fractions_zero (), Fractions_negate (Fractions_initFract (0, 10, 100))), Points_initPoint (Fractions_initFract (0, 5, 100), Fractions_zero ()));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 20, 100), Fractions_initFract (0, 25, 100)));
  m = macroObjects_triangle (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_negate (Fractions_initFract (0, 8, 100)), Fractions_negate (Fractions_initFract (0, 7, 100))), Points_initPoint (Fractions_initFract (0, 15, 100), Fractions_zero ()));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 80, 100), Fractions_initFract (0, 25, 100)));
  m = macroObjects_triangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_blue (), Points_initPoint (Fractions_negate (Fractions_initFract (0, 8, 100)), Fractions_negate (Fractions_initFract (0, 7, 100))), Points_initPoint (Fractions_initFract (0, 15, 100), Fractions_zero ()));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 5, 100), Fractions_initFract (0, 49, 100)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Points_initPoint (Fractions_initFract (0, 51, 100), Fractions_negate (Fractions_initFract (0, 2, 100))), Points_initPoint (Fractions_zero (), Fractions_negate (Fractions_initFract (0, 2, 100))));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 82, 100), Fractions_initFract (0, 42, 100)));
  m = macroObjects_triangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_green (), Points_initPoint (Fractions_negate (Fractions_initFract (0, 6, 100)), Fractions_negate (Fractions_initFract (0, 5, 100))), Points_initPoint (Fractions_initFract (0, 10, 100), Fractions_zero ()));
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
}


/*
   placeNonFixed -
*/

static void placeNonFixed (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 9, 100), Fractions_initFract (0, 91, 100)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), dark, Fractions_initFract (0, 3, 100));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 85, 100), Fractions_initFract (0, 90, 100)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_yellow (), Fractions_initFract (0, 3, 100));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 75, 100), Fractions_initFract (0, 73, 100)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_blue (), Fractions_initFract (0, 3, 100));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 20, 100), Fractions_initFract (0, 89, 100)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), dark, Fractions_initFract (0, 3, 100));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 21, 100), Fractions_initFract (0, 73, 100)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_yellow (), Fractions_initFract (0, 3, 100));
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_mult (Fractions_initFract (10, 0, 1), Fractions_zero ()), Fractions_mult (Fractions_initFract (10, 0, 1), Fractions_initFract (0, 11, 100))));
  popWorld_populate (m, FALSE, TRUE);
}

void _M2_world_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (useGroff);
  light = deviceIf_defineColour (Fractions_initFract (0, 166, 256), Fractions_initFract (0, 124, 256), Fractions_initFract (0, 54, 256));
  dark = deviceIf_defineColour (Fractions_initFract (0, 76, 256), Fractions_initFract (0, 47, 256), Fractions_zero ());
  placeFixed ();
  twoDsim_gravity (-9.81);
  placeNonFixed ();
  twoDsim_simulateFor (25.0);
}

void _M2_world_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
