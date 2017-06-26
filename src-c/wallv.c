/* automatically created by mc from ../wallv.mod.  */

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
#   include "GdeviceGroff.h"
#   include "GFractions.h"
#   include "GPoints.h"
#   include "GmacroObjects.h"

#   define testCorner FALSE
#   define testRight FALSE
static Fractions_Fract size;

/*
   placeWall - 
*/

static void placeWall (void);

/*
   fireCue - 
*/

static void fireCue (void);

/*
   fireBox - 
*/

static void fireBox (void);

/*
   placeWall - 
*/

static void placeWall (void);

/*
   fireCue - 
*/

static void fireCue (void);

/*
   fireBox - 
*/

static void fireBox (void);


/*
   placeWall - 
*/

static void placeWall (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 1, 10), Fractions_initFract (0, 1, 10)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_red (), Fractions_initFract (0, 1, 10), Fractions_initFract (0, 8, 10));
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
}


/*
   fireCue - 
*/

static void fireCue (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 5, 10), Fractions_initFract (0, 5, 10)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_green (), size);
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (3));
  popWorld_velocity (Points_initPoint (Fractions_negate (Fractions_initFract (2, 0, 0)), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
  twoDsim_simulateFor (1.0);
}


/*
   fireBox - 
*/

static void fireBox (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 5, 10), Fractions_initFract (0, 5, 10)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_green (), Fractions_initFract (0, 1, 20), Fractions_initFract (0, 1, 20));
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (3));
  popWorld_velocity (Points_initPoint (Fractions_negate (Fractions_initFract (2, 0, 0)), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
  twoDsim_simulateFor (1.0);
}

void _M2_wallv_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (FALSE);
  size = Fractions_initFract (0, 1, 21);
  placeWall ();
  fireBox ();
}

void _M2_wallv_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
