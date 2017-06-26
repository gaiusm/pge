/* automatically created by mc from ../snooker.mod.  */

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
static Fractions_Fract size;
static deviceIf_Colour light;
static deviceIf_Colour dark;

/*
   placeBoundary - 
*/

static void placeBoundary (void);

/*
   placeBalls - 
*/

static void placeBalls (void);

/*
   fireCue - 
*/

static void fireCue (void);

/*
   placeBoundary - 
*/

static void placeBoundary (void);

/*
   placeBalls - 
*/

static void placeBalls (void);

/*
   fireCue - 
*/

static void fireCue (void);


/*
   placeBoundary - 
*/

static void placeBoundary (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_initFract (0, 1, 100), Fractions_one ());
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 99, 100), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_initFract (0, 1, 100), Fractions_one ());
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_one (), Fractions_initFract (0, 1, 100));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_initFract (0, 99, 100)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_one (), Fractions_initFract (0, 1, 100));
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
}


/*
   placeBalls - 
*/

static void placeBalls (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 3, 10), Fractions_initFract (0, 8, 10)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_right (m, Fractions_initFract (0, 1, 10));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_right (m, Fractions_initFract (0, 1, 10));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_right (m, Fractions_initFract (0, 1, 10));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 7, 20), Fractions_initFract (0, 7, 10)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_right (m, Fractions_initFract (0, 1, 10));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_right (m, Fractions_initFract (0, 1, 10));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 4, 10), Fractions_initFract (0, 6, 10)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_right (m, Fractions_initFract (0, 1, 10));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 9, 20), Fractions_initFract (0, 5, 10)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), size);
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, FALSE, TRUE);
}


/*
   fireCue - 
*/

static void fireCue (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 7, 13), Fractions_initFract (0, 1, 10)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_green (), size);
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (3));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_initFract (2, 0, 0)));
  popWorld_populate (m, FALSE, TRUE);
  twoDsim_simulateFor (30.0);
}

void _M2_snooker_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (useGroff);
  light = deviceIf_defineColour (Fractions_initFract (0, 166, 256), Fractions_initFract (0, 124, 256), Fractions_initFract (0, 54, 256));
  dark = deviceIf_defineColour (Fractions_initFract (0, 76, 256), Fractions_initFract (0, 47, 256), Fractions_zero ());
  size = Fractions_initFract (0, 1, 21);
  placeBoundary ();
  placeBalls ();
  fireCue ();
}

void _M2_snooker_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
