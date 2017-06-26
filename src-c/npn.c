/* automatically created by mc from ../npn.mod.  */

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

#   include "GmacroObjects.h"
#   include "GGC.h"
#   include "GdeviceGroff.h"
#   include "GPoints.h"
#   include "GFractions.h"
#   include "Gdelay.h"

#   define fps 1
static Fractions_Fract componentOutline;
static Fractions_Fract componentWire;
static Fractions_Fract transistorEdge;
static Fractions_Fract transistorCircle;
static Fractions_Fract transistorBase;
static Fractions_Fract unit;
static Fractions_Fract thickness;
static macroObjects_Macro frame;

/*
   board - 
*/

static void board (void);

/*
   origin - returns (0, 0)
*/

static Points_Point origin (void);

/*
   rotatingBox - 
*/

static void rotatingBox (void);

/*
   toFrame - 
*/

static void toFrame (macroObjects_Macro m);

/*
   movingBox - 
*/

static void movingBox (void);

/*
   movingBox - 
*/

static macroObjects_Macro transistorNPN (void);

/*
   testNPN - 
*/

static void testNPN (void);

/*
   unitf - return a unit fraction of value, w + n/d.
*/

static Fractions_Fract unitf (long unsigned int w, long unsigned int n, long unsigned int d);

/*
   init - 
*/

static void init (void);

/*
   board - 
*/

static void board (void);

/*
   origin - returns (0, 0)
*/

static Points_Point origin (void);

/*
   rotatingBox - 
*/

static void rotatingBox (void);

/*
   toFrame - 
*/

static void toFrame (macroObjects_Macro m);

/*
   movingBox - 
*/

static void movingBox (void);

/*
   movingBox - 
*/

static macroObjects_Macro transistorNPN (void);

/*
   testNPN - 
*/

static void testNPN (void);

/*
   unitf - return a unit fraction of value, w + n/d.
*/

static Fractions_Fract unitf (long unsigned int w, long unsigned int n, long unsigned int d);

/*
   init - 
*/

static void init (void);


/*
   board - 
*/

static void board (void)
{
  macroObjects_Macro m;
  macroObjects_Macro g;
  macroObjects_Macro r;
  unsigned int i;
  unsigned int j;
  unsigned int light;

  m = macroObjects_initMacro ();
  g = macroObjects_initMacro ();
  g = macroObjects_rectangle (g, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_green (), unitf (1, 0, 0), unitf (1, 0, 0));
  r = macroObjects_initMacro ();
  r = macroObjects_rectangle (r, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_red (), unitf (1, 0, 0), unitf (1, 0, 0));
  light = TRUE;
  for (j=1; j<=8; j++)
    {
      for (i=1; i<=8; i++)
        {
          m = macroObjects_right (m, unitf (1, 0, 0));
          if (light)
            m = macroObjects_append (m, g);
          else
            m = macroObjects_append (m, r);
          light = ! light;
        }
      light = ! light;
      m = macroObjects_up (m, unitf (1, 0, 0));
      m = macroObjects_left (m, unitf (8, 0, 0));
    }
}


/*
   origin - returns (0, 0)
*/

static Points_Point origin (void)
{
  return Points_initPoint (unitf (0, 0, 0), unitf (0, 0, 0));
}


/*
   rotatingBox - 
*/

static void rotatingBox (void)
{
  macroObjects_Macro m;
  macroObjects_Macro n;
  unsigned int i;

  m = macroObjects_initMacro ();
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_blue (), unitf (1, 0, 0), unitf (1, 0, 0));
  m = macroObjects_right (m, unitf (1, 0, 0));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_red (), unitf (1, 0, 0), unitf (1, 0, 0));
  m = macroObjects_up (m, unitf (1, 0, 0));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_green (), unitf (1, 0, 0), unitf (1, 0, 0));
  m = macroObjects_left (m, unitf (1, 0, 0));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_black (), unitf (1, 0, 0), unitf (1, 0, 0));
  m = macroObjects_moveTo (m, Points_initPoint (unitf (3, 0, 0), unitf (3, 0, 0)));
  m = macroObjects_circle (m, FALSE, transistorCircle, (deviceIf_Colour) deviceGroff_red (), unitf (1, 0, 0));
  for (i=0; i<=8; i++)
    {
      toFrame (m);
      m = macroObjects_rotate (macroObjects_unRootMacro (m), Points_initPoint (unitf (2, 0, 0), unitf (2, 0, 0)), Fractions_div (Fractions_pi (), Fractions_two ()));
      m = macroObjects_rootMacro (m);
      GC_collectAll ();
    }
}


/*
   toFrame - 
*/

static void toFrame (macroObjects_Macro m)
{
  macroObjects_Macro n;

  n = macroObjects_dup (m);
  n = macroObjects_moveTo (n, origin ());
  n = macroObjects_append (n, frame);
  macroObjects_runCallBacks (n, (macroObjects_pProc) {(macroObjects_pProc_t) deviceGroff_glyphPolygon}, (macroObjects_cProc) {(macroObjects_cProc_t) deviceGroff_glyphCircle});
  deviceGroff_flipBuffer ();
}


/*
   movingBox - 
*/

static void movingBox (void)
{
  macroObjects_Macro m;
  unsigned int i;

  m = macroObjects_initMacro ();
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_blue (), unitf (1, 0, 0), unitf (1, 0, 0));
  m = macroObjects_right (m, unitf (1, 0, 0));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_red (), unitf (1, 0, 0), unitf (1, 0, 0));
  m = macroObjects_up (m, unitf (1, 0, 0));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_green (), unitf (1, 0, 0), unitf (1, 0, 0));
  m = macroObjects_left (m, unitf (1, 0, 0));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_black (), unitf (1, 0, 0), unitf (1, 0, 0));
  for (i=0; i<=3; i++)
    {
      toFrame (m);
      m = macroObjects_translate (m, Points_initPoint (unitf (0, 0, 0), unitf (1, 0, 0)));
    }
  for (i=0; i<=3; i++)
    {
      toFrame (m);
      m = macroObjects_translate (m, Points_initPoint (unitf (1, 0, 0), unitf (0, 0, 0)));
    }
  for (i=0; i<=3; i++)
    {
      toFrame (m);
      m = macroObjects_translate (m, Points_initPoint (unitf (0, 0, 0), Fractions_negate (unitf (1, 0, 0))));
    }
  for (i=0; i<=3; i++)
    {
      toFrame (m);
      m = macroObjects_translate (m, Points_initPoint (Fractions_negate (unitf (1, 0, 0)), unitf (0, 0, 0)));
    }
}


/*
   movingBox - 
*/

static macroObjects_Macro transistorNPN (void)
{
  macroObjects_Macro m;
  macroObjects_Macro n;
  Fractions_Fract height;
  Fractions_Fract width;

  m = macroObjects_initMacro ();
  width = unitf (0, 1, 4);
  height = unitf (1, 0, 0);
  m = macroObjects_right (m, unitf (1, 1, 4));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_red (), width, height);
  m = macroObjects_left (m, Fractions_mult (Fractions_initFract (0, 3, 4), width));
  m = macroObjects_right (m, unitf (1, 0, 0));
  m = macroObjects_up (m, unitf (0, 1, 2));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_green (), transistorEdge, Fractions_mult (width, Fractions_two ()));
  m = macroObjects_down (m, unitf (2, 0, 0));
  m = macroObjects_up (m, Fractions_sub (unitf (1, 0, 0), Fractions_mult (width, Fractions_two ())));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_blue (), transistorEdge, Fractions_mult (width, Fractions_two ()));
  m = macroObjects_left (m, Fractions_mult (width, Fractions_initFract (0, 4, 3)));
  m = macroObjects_up (m, unitf (0, 2, 2));
  m = macroObjects_circle (m, FALSE, transistorCircle, (deviceIf_Colour) deviceGroff_red (), unitf (1, 2, 3));
  m = macroObjects_moveTo (m, Points_initPoint (unitf (1, 2, 4), unitf (0, 0, 0)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_black (), Points_initPoint (Fractions_mult (width, Fractions_two ()), unitf (0, 1, 2)), Points_initPoint (Fractions_zero (), unitf (0, 1, 2)));
  return m;
}


/*
   testNPN - 
*/

static void testNPN (void)
{
  macroObjects_Macro m;
  macroObjects_Macro n;
  unsigned int i;

  m = transistorNPN ();
  m = macroObjects_rootMacro (m);
  toFrame (m);
  GC_collectAll ();
  for (i=0; i<=8; i++)
    {
      m = macroObjects_rotate (macroObjects_unRootMacro (m), Points_initPoint (unitf (1, 0, 0), unitf (1, 0, 0)), Fractions_div (Fractions_pi (), Fractions_two ()));
      m = macroObjects_rootMacro (m);
      toFrame (m);
      GC_collectAll ();
    }
}


/*
   unitf - return a unit fraction of value, w + n/d.
*/

static Fractions_Fract unitf (long unsigned int w, long unsigned int n, long unsigned int d)
{
  return Fractions_mult (Fractions_initFract (w, n, d), unit);
}


/*
   init - 
*/

static void init (void)
{
  unit = Fractions_root (Fractions_initFract (0, 25, 100));
  transistorBase = Fractions_root (unitf (0, 4*4, 100));
  transistorEdge = Fractions_root (unitf (0, 3*4, 100));
  transistorCircle = Fractions_root (unitf (0, 2*4, 100));
  componentOutline = Fractions_root (unitf (0, 17*4, 100));
  componentWire = Fractions_root (unitf (0, 15*4, 100));
  thickness = Fractions_root (unitf (0, 1*4, 100));
  deviceGroff_configDevice (Points_initPoint (Fractions_cardinal (5), Fractions_cardinal (5)), Points_initPoint (Fractions_cardinal (5), Fractions_cardinal (5)), 1, FALSE, FALSE, TRUE, TRUE);
  frame = macroObjects_initMacro ();
  frame = macroObjects_rectangle (frame, FALSE, thickness, (deviceIf_Colour) deviceGroff_black (), unitf (20, 0, 0), unitf (20, 0, 0));
  frame = macroObjects_rootMacro (frame);
}

void _M2_npn_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  init ();
  testNPN ();
}

void _M2_npn_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
