/* automatically created by mc from ../git-pge/m2/test.mod.  */

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
#   define useGroff FALSE
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
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 0, 8550), Fractions_initFract (0, 225, 8550)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_initFract (0, 8550, 8550), Fractions_initFract (0, 0, 8550)), Points_initPoint (Fractions_initFract (0, 0, 8550), Fractions_initFract (0, 225, 8550)));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 8325, 8550), Fractions_initFract (0, 450, 8550)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_initFract (0, 225, 8550), Fractions_initFract (0, 0, 8550)), Points_initPoint (Fractions_initFract (0, 0, 8550), Fractions_initFract (0, 2475, 8550)));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 0, 8550), Fractions_initFract (0, 2925, 8550)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_initFract (0, 8550, 8550), Fractions_initFract (0, 0, 8550)), Points_initPoint (Fractions_initFract (0, 0, 8550), Fractions_initFract (0, 225, 8550)));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 0, 8550), Fractions_initFract (0, 450, 8550)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_initFract (0, 225, 8550), Fractions_initFract (0, 0, 8550)), Points_initPoint (Fractions_initFract (0, 0, 8550), Fractions_initFract (0, 2475, 8550)));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 2677, 8550), Fractions_initFract (0, 1462, 8550)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Fractions_initFract (0, 287, 8550));
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
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
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 4972, 8550), Fractions_initFract (0, 1170, 8550)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_yellow (), Fractions_initFract (0, 282, 8550));
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
}

void _M2_test_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (useGroff);
  light = deviceIf_defineColour (Fractions_initFract (0, 166, 256), Fractions_initFract (0, 124, 256), Fractions_initFract (0, 54, 256));
  dark = deviceIf_defineColour (Fractions_initFract (0, 76, 256), Fractions_initFract (0, 47, 256), Fractions_zero ());
  placeFixed ();
  twoDsim_gravity (-9.81);
  placeNonFixed ();
  twoDsim_simulateFor (25.0);
}

void _M2_test_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
