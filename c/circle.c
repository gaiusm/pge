/* automatically created by mc from ../git-pge/m2/circle.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   include "GtwoDsim.h"
#   include "GdeviceIf.h"
#   include "GFractions.h"
#   include "Glibc.h"

#   define boarder 0.01
static unsigned int wood_light;
static unsigned int wood_dark;
static unsigned int red;
static unsigned int blue;
static void placeBoarders (double thickness, unsigned int color);
static unsigned int placeBox (double x, double y, double w, unsigned int c);

/*
   initColours - 
*/

static void initColours (void);

/*
   initColours - 
*/

static void startWorld (void);
static void placeBoarders (double thickness, unsigned int color);
static unsigned int placeBox (double x, double y, double w, unsigned int c);

/*
   initColours - 
*/

static void initColours (void);

/*
   initColours - 
*/

static void startWorld (void);

static void placeBoarders (double thickness, unsigned int color)
{
  unsigned int b;

  /* 
   projectVector - returns the vector, onto, after it has been
                   projected by, project.
  */
  b = twoDsim_box (0.0, 0.0, 1.0, thickness, (deviceIf_Colour) color);
  b = twoDsim_fix (b);
  b = twoDsim_box (0.0, 0.0, thickness, 1.0, (deviceIf_Colour) color);
  b = twoDsim_fix (b);
  b = twoDsim_box (1.0-thickness, 0.0, thickness, 1.0, (deviceIf_Colour) color);
  b = twoDsim_fix (b);
  b = twoDsim_box (0.0, 1.0-thickness, 1.0, thickness, (deviceIf_Colour) color);
  b = twoDsim_fix (b);
}

static unsigned int placeBox (double x, double y, double w, unsigned int c)
{
  return twoDsim_box (x, y, w, w, (deviceIf_Colour) c);
}


/*
   initColours - 
*/

static void initColours (void)
{
  wood_light = deviceIf_defineColour (Fractions_initFract (0, 166, 256), Fractions_initFract (0, 124, 256), Fractions_initFract (0, 54, 256));
  wood_dark = deviceIf_defineColour (Fractions_initFract (0, 76, 256), Fractions_initFract (0, 47, 256), Fractions_zero ());
  red = deviceIf_defineColour (Fractions_one (), Fractions_zero (), Fractions_zero ());
  blue = deviceIf_defineColour (Fractions_zero (), Fractions_zero (), Fractions_one ());
}


/*
   initColours - 
*/

static void startWorld (void)
{
  unsigned int b;

  b = placeBox (0.4, 0.4, 0.1, red);
  b = twoDsim_fix (b);
  placeBoarders (boarder, wood_dark);
  b = twoDsim_circle (0.53, 0.7, 0.04, (deviceIf_Colour) blue);
  b = twoDsim_mass (b, 1.0);
  twoDsim_gravity (-9.81);
  twoDsim_simulateFor (3.0);
}

void _M2_circle_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  deviceIf_useGroff ();
  twoDsim_drawCollisionFrames (TRUE, TRUE);
  twoDsim_fps (80.0);
  initColours ();
  startWorld ();
}

void _M2_circle_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
