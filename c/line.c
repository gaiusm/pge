/* automatically created by mc from ../git-pge/m2/line.mod.  */

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
static deviceIf_Colour light;
static deviceIf_Colour dark;

/*
   placeBoundary - 
*/

static void placeBoundary (macroObjects_Macro m);

/*
   placeWorld - 
*/

static void placeWorld (void);

/*
   dropBox - 
*/

static void dropBox (deviceIf_Colour c, Fractions_Fract x);

/*
   placeBoundary - 
*/

static void placeBoundary (macroObjects_Macro m);

/*
   placeWorld - 
*/

static void placeWorld (void);

/*
   dropBox - 
*/

static void dropBox (deviceIf_Colour c, Fractions_Fract x);


/*
   placeBoundary - 
*/

static void placeBoundary (macroObjects_Macro m)
{
  /* left edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_initFract (0, 1, 100), Fractions_one ());
  /* right edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 99, 100), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_initFract (0, 1, 100), Fractions_one ());
  /* bot edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_one (), Fractions_initFract (0, 1, 100));
  /* top edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_initFract (0, 99, 100)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_one (), Fractions_initFract (0, 1, 100));
}


/*
   placeWorld - 
*/

static void placeWorld (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  placeBoundary (m);
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
}


/*
   dropBox - 
*/

static void dropBox (deviceIf_Colour c, Fractions_Fract x)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  /* drop the ball at the top of stairs with a leftwards velocity  */
  m = macroObjects_moveTo (m, Points_initPoint (x, Fractions_initFract (0, 37, 40)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), c, Fractions_initFract (0, 1, 20), Fractions_initFract (0, 1, 20));
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_zero ()));
  popWorld_rotate (Fractions_initFract (0, 10, 1));
  popWorld_populate (m, FALSE, TRUE);
}

void _M2_line_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (TRUE);
  light = deviceIf_defineColour (Fractions_initFract (0, 166, 256), Fractions_initFract (0, 124, 256), Fractions_initFract (0, 54, 256));
  dark = deviceIf_defineColour (Fractions_initFract (0, 76, 256), Fractions_initFract (0, 47, 256), Fractions_zero ());
  placeWorld ();
  twoDsim_gravity (-9.81);
  dropBox ((deviceIf_Colour) deviceIf_red (), Fractions_initFract (0, 10, 20));
  twoDsim_simulateFor (4.0);
}

void _M2_line_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
