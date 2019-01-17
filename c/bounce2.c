/* automatically created by mc from ../git-pge/m2/bounce2.mod.  */

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

#   define useGroff TRUE
static deviceIf_Colour light;
static deviceIf_Colour dark;

/*
   placeBoundary - 
*/

static void placeBoundary (void);

/*
   fireBox - 
*/

static void fireBox (deviceIf_Colour c);

/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c);

/*
   placeBoundary - 
*/

static void placeBoundary (void);

/*
   fireBox - 
*/

static void fireBox (deviceIf_Colour c);

/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c);


/*
   placeBoundary - 
*/

static void placeBoundary (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
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
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
}


/*
   fireBox - 
*/

static void fireBox (deviceIf_Colour c)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 10, 20), Fractions_initFract (0, 30, 40)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), c, Fractions_initFract (0, 1, 40), Fractions_initFract (0, 1, 40));
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_half (), Fractions_negate (Fractions_half ())));
  popWorld_populate (m, FALSE, TRUE);
}


/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c)
{
  macroObjects_Macro m;
  Fractions_Fract size;

  m = macroObjects_initMacro ();
  /* drop the ball at the top of stairs with a leftwards velocity  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 17, 20), Fractions_initFract (0, 37, 40)));
  size = Fractions_initFract (0, 1, 21);
  m = macroObjects_circle (m, TRUE, Fractions_zero (), c, size);
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
}

void _M2_bounce2_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (useGroff);
  light = deviceIf_defineColour (Fractions_initFract (0, 166, 256), Fractions_initFract (0, 124, 256), Fractions_initFract (0, 54, 256));
  dark = deviceIf_defineColour (Fractions_initFract (0, 76, 256), Fractions_initFract (0, 47, 256), Fractions_zero ());
  placeBoundary ();
  fireBox ((deviceIf_Colour) deviceIf_green ());
  twoDsim_simulateFor (1.0);
  fireBox ((deviceIf_Colour) deviceIf_red ());
  twoDsim_simulateFor (30.0);  /* 15.0 ok  */
}

void _M2_bounce2_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
