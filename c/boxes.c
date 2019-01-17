/* automatically created by mc from ../git-pge/m2/boxes.mod.  */

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
static Fractions_Fract size;
static deviceIf_Colour light;
static deviceIf_Colour dark;

/*
   placeBoundary - 
*/

static void placeBoundary (void);

/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c);

/*
   dropBox - 
*/

static void dropBox (deviceIf_Colour c);

/*
   fireBox - 
*/

static void fireBox (deviceIf_Colour c);

/*
   placeBoundary - 
*/

static void placeBoundary (void);

/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c);

/*
   dropBox - 
*/

static void dropBox (deviceIf_Colour c);

/*
   fireBox - 
*/

static void fireBox (deviceIf_Colour c);


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
  popWorld_populate (m, TRUE, TRUE);
}


/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  /* drop the ball at the top of stairs with a leftwards velocity  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 17, 20), Fractions_initFract (0, 37, 40)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), c, size);
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
}


/*
   dropBox - 
*/

static void dropBox (deviceIf_Colour c)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  /* drop the ball at the top of stairs with a leftwards velocity  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 17, 20), Fractions_initFract (0, 37, 40)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), c, Fractions_initFract (0, 1, 20), Fractions_initFract (0, 1, 20));
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
}


/*
   fireBox - 
*/

static void fireBox (deviceIf_Colour c)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  /* drop the ball at the top of stairs with a leftwards velocity  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 17, 20), Fractions_initFract (0, 3, 40)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), c, Fractions_initFract (0, 1, 20), Fractions_initFract (0, 1, 20));
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_cardinal (6)));
  popWorld_populate (m, FALSE, TRUE);
}

void _M2_boxes_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (TRUE);
  light = deviceIf_defineColour (Fractions_initFract (0, 166, 256), Fractions_initFract (0, 124, 256), Fractions_initFract (0, 54, 256));
  dark = deviceIf_defineColour (Fractions_initFract (0, 76, 256), Fractions_initFract (0, 47, 256), Fractions_zero ());
  size = Fractions_initFract (0, 1, 21);
  placeBoundary ();
  fireBox ((deviceIf_Colour) deviceIf_green ());
  twoDsim_gravity (-9.81);
  twoDsim_simulateFor (1.0);
}

void _M2_boxes_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
