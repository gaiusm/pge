/* automatically created by mc from ../stairs.mod.  */

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

/*
   placeStairs - 
*/

static void placeStairs (void);

/*
   dropBall - 
*/

static void dropBall (void);

/*
   placeStairs - 
*/

static void placeStairs (void);

/*
   dropBall - 
*/

static void dropBall (void);


/*
   placeStairs - 
*/

static void placeStairs (void)
{
  macroObjects_Macro m;
  unsigned int i;

  m = macroObjects_initMacro ();
  for (i=0; i<=7; i++)
    {
      m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 2+i, 10), Fractions_initFract (0, (long unsigned int) i, 10)));
      m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Fractions_initFract (0, 8-i, 10), Fractions_initFract (0, 1, 10));
    }
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Fractions_initFract (0, 1, 10), Fractions_one ());
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
}


/*
   dropBall - 
*/

static void dropBall (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 9, 10), Fractions_initFract (0, 9, 10)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_green (), size);
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_negate (Fractions_initFract (0, 1, 2)), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
}

void _M2_stairs_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (TRUE);
  size = Fractions_initFract (0, 1, 21);
  placeStairs ();
  dropBall ();
  twoDsim_gravity (-9.81);
  twoDsim_simulateFor (7.0);
}

void _M2_stairs_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
