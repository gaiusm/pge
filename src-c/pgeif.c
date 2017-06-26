/* automatically created by mc from ../pgeif.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#include <string.h>
#include <limits.h>
#   include "GStorage.h"
#   include "Gmcrts.h"
#define _pgeif_H
#define _pgeif_C

#   include "GStorage.h"
#   include "GdeviceIf.h"
#   include "GtwoDsim.h"
#   include "GSYSTEM.h"
#   include "GIndexing.h"
#   include "GFractions.h"
#   include "Glibc.h"
#   include "Groots.h"

#   define debugging FALSE
#   define tracing FALSE
typedef struct _T1_r _T1;

typedef _T1 *def;

typedef enum {pgeif_IncorrectType, pgeif_IdOutOfBounds, pgeif_ValueOutOfRange} pgeif_ExceptionKind;

typedef enum {colour, object} TypeOfDef;

struct _T1_r {
               TypeOfDef type;
               unsigned int definition;
             };

static Indexing_Index listOfDefs;

/*
   rgb - make a colour object using red, blue and green components.
         The colour object is returned.
*/

unsigned int pgeif_rgb (double r, double g, double b);

/*
   white - returns the colour, white.
*/

unsigned int pgeif_white (void);

/*
   black - returns the colour, black.
*/

unsigned int pgeif_black (void);

/*
   red - returns the colour, red.
*/

unsigned int pgeif_red (void);

/*
   green - returns the colour, green.
*/

unsigned int pgeif_green (void);

/*
   blue - returns the colour, blue.
*/

unsigned int pgeif_blue (void);

/*
   yellow - returns the colour, yellow.
*/

unsigned int pgeif_yellow (void);

/*
   purple - returns the colour, purple.
*/

unsigned int pgeif_purple (void);

/*
   gravity - turn on gravity at: g m^2
*/

void pgeif_gravity (double g);

/*
   box - place a box in the world at (x0,y0),(x0+i,y0+j)
*/

unsigned int pgeif_box (double x0, double y0, double i, double j, unsigned int c);

/*
   poly3 - place a triangle in the world at:
           (x0,y0),(x1,y1),(x2,y2)
*/

unsigned int pgeif_poly3 (double x0, double y0, double x1, double y1, double x2, double y2, unsigned int c);

/*
   poly4 - place a rectangle in the world at:
           (x0,y0),(x1,y1),(x2,y2),(x3,y3)
*/

unsigned int pgeif_poly4 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, unsigned int c);

/*
   poly5 - place a pentagon in the world at:
           (x0,y0),(x1,y1),(x2,y2),(x3,y3),(x4,y4)
*/

unsigned int pgeif_poly5 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, unsigned int c);

/*
   poly6 - place a hexagon in the world at:
           (x0,y0),(x1,y1),(x2,y2),(x3,y3),(x4,y4),(x5,y5)
*/

unsigned int pgeif_poly6 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, unsigned int c);

/*
   mass - specify the mass of an object and return the, id.
*/

unsigned int pgeif_mass (unsigned int id, double m);

/*
   fix - fix the object to the world.
*/

unsigned int pgeif_fix (unsigned int id);

/*
   circle - adds a circle to the world.  Center
            defined by: x0, y0 radius, radius.
*/

unsigned int pgeif_circle (double x0, double y0, double radius, unsigned int c);

/*
   velocity - give an object, id, a velocity, vx, vy.
*/

unsigned int pgeif_velocity (unsigned int id, double vx, double vy);

/*
   accel - give an object, id, an acceleration, ax, ay.
*/

unsigned int pgeif_accel (unsigned int id, double ax, double ay);

/*
   rotate - rotates object with a angular velocity, angle.
*/

unsigned int pgeif_rotate (unsigned int id, double angle);

/*
   fps - set frames per second.
*/

unsigned int pgeif_is_collision (void);

/*
   fps - set frames per second.
*/

unsigned int pgeif_is_frame (void);

/*
   fps - set frames per second.
*/

unsigned int pgeif_is_function (void);

/*
   create_function_event - creates a function event at time, t,
                           in the future.
*/

void pgeif_create_function_event (double t, unsigned int id);

/*
   time_until - returns the relative time from now until the next event.
*/

double pgeif_time_until (void);

/*
   skip_until - advances time for, t, units or until the next event is reached.
                The amount of time skipped is returned.  This function will not
                skip past the next event.
*/

double pgeif_skip_until (double t);

/*
   process_event - advance time to the next event and then
                   process the event.
*/

void pgeif_process_event (void);

/*
   fps - set frames per second.
*/

double pgeif_get_time (void);

/*
   rm - delete this object from the simulated world.
        The same id is returned.
*/

unsigned int pgeif_rm (unsigned int id);

/*
   get_xpos - returns the first point, x, coordinate of object.
*/

double pgeif_get_xpos (unsigned int id);

/*
   get_ypos - returns the first point, y, coordinate of object.
*/

double pgeif_get_ypos (unsigned int id);

/*
   get_xvel - returns the X velocity of object.
*/

double pgeif_get_xvel (unsigned int id);

/*
   get_yvel - returns the Y velocity of object.
*/

double pgeif_get_yvel (unsigned int id);

/*
   get_xaccel - returns the X accelaration of object.
*/

double pgeif_get_xaccel (unsigned int id);

/*
   get_yaccel - returns the Y accelaration of object.
*/

double pgeif_get_yaccel (unsigned int id);

/*
   put_xvel - assigns the X velocity of object.
*/

void pgeif_put_xvel (unsigned int id, double r);

/*
   put_yvel - assigns the Y velocity of object.
*/

void pgeif_put_yvel (unsigned int id, double r);

/*
   put_xaccel - assigns the X accelaration of object.
*/

void pgeif_put_xaccel (unsigned int id, double r);

/*
   put_yaccel - assigns the Y accelaration of object.
*/

void pgeif_put_yaccel (unsigned int id, double r);

/*
   set_colour - sets colour of object, id, to, c.
*/

void pgeif_set_colour (unsigned int id, unsigned int c);

/*
   apply_impulse - applies an impulse of magnitude along vector
                   [x, y] for object, id.
*/

void pgeif_apply_impulse (unsigned int id, double x, double y, double m);

/*
   moving_towards - returns TRUE if object, id, is moving towards
                    a point x, y.
*/

unsigned int pgeif_moving_towards (unsigned int id, double x, double y);

/*
   batch - use the batch device to record the output frames.
*/

void pgeif_batch (void);

/*
   use_buffer - use the buffer device to record the output frames.
*/

void pgeif_use_buffer (void);

/*
   empty_cbuffer - empty the colour buffer.
*/

void pgeif_empty_cbuffer (void);

/*
   empty_fbuffer - empty the frame buffer.
*/

void pgeif_empty_fbuffer (void);

/*
   use_time_delay - should the frame buffer include the time delay command?
*/

void pgeif_use_time_delay (unsigned int on);

/*
   draw_collision - turn on drawing of the actual collision frame
                    and the prediction frame.
*/

void pgeif_draw_collision (unsigned int actual, unsigned int predict);

/*
   set_collision_colour - when two objects collide they will both be draw using
                          colour, c.
*/

void pgeif_set_collision_colour (unsigned int c);

/*
   dump_world - dump a list of all objects and their characteristics.
*/

void pgeif_dump_world (void);

/*
   check_objects - perform a check to make sure that all non fixed
                   objects have a mass.
*/

void pgeif_check_objects (void);

/*
   l2h - translate a twoDsim, id, to the pgeid.
*/

unsigned int pgeif_l2h (unsigned int id);

/*
   h2l - translate a pgeif, id, to the twoDsim.
*/

unsigned int pgeif_h2l (unsigned int id);

/*
   fps - set frames per second.
*/

void pgeif_fps (double f);

/*
   trace -
*/

static unsigned int trace (unsigned int id, char *name_, unsigned int _name_high);

/*
   Assert -
*/

static void Assert (unsigned int b);

/*
   init - initialise the modules data structures.
*/

static void init (void);

/*
   newDef -
*/

static def newDef (TypeOfDef t, unsigned int d);

/*
   addDef - adds a definition (type, d) into the global list and
            returns an index to the definition, id.
*/

static unsigned int addDef (TypeOfDef type, unsigned int d);

/*
   lookupDef - return the definition of, d, and check its type
               is, t.
*/

static unsigned int lookupDef (TypeOfDef t, unsigned int d);

/*
   check_range -
*/

static double check_range (double r, char *function_, unsigned int _function_high, char *param_, unsigned int _param_high);

/*
   nofree - do not free, a.
*/

static void * nofree (void * a);


/*
   trace -
*/

static unsigned int trace (unsigned int id, char *name_, unsigned int _name_high)
{
  char name[_name_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (name, name_, _name_high+1);

  if (tracing)
    libc_printf ((char *) "pgeif:  %s as id=%d\\n", 21, &name, id);
  return id;
}


/*
   Assert -
*/

static void Assert (unsigned int b)
{
  if (! b)
    {
      libc_printf ((char *) "assert failed\\n", 15);
      libc_exit (1);
    }
}


/*
   init - initialise the modules data structures.
*/

static void init (void)
{
  listOfDefs = Indexing_InitIndex (1);
}


/*
   newDef -
*/

static def newDef (TypeOfDef t, unsigned int d)
{
  def f;

  Storage_ALLOCATE ((void **) &f, sizeof (_T1));
  f->type = t;
  f->definition = d;
  return f;
}


/*
   addDef - adds a definition (type, d) into the global list and
            returns an index to the definition, id.
*/

static unsigned int addDef (TypeOfDef type, unsigned int d)
{
  unsigned int id;
  def f;

  f = newDef (type, d);
  Indexing_IncludeIndiceIntoIndex (listOfDefs, (void *) f);
  id = Indexing_HighIndice (listOfDefs);
  Assert ((Indexing_GetIndice (listOfDefs, id)) == f);
  if (debugging)
    libc_printf ((char *) "pgeif:  map (pgeid %d) onto (twoDsim %d)\\n", 42, id, d);
  return id;
}


/*
   lookupDef - return the definition of, d, and check its type
               is, t.
*/

static unsigned int lookupDef (TypeOfDef t, unsigned int d)
{
  def f;

  if (debugging)
    libc_printf ((char *) "inside lookupDef (d = %d)\\n", 27, d);
  if (Indexing_InBounds (listOfDefs, d))
    {
      f = Indexing_GetIndice (listOfDefs, d);
      if (debugging)
        libc_printf ((char *) "inside lookupDef (type = %d, definition = %d)\\n", 47, f->type, f->definition);
      if (t == f->type)
        return f->definition;
      else
        {
          if (debugging)
            libc_printf ((char *) "throwing an exception in lookupDef (1)  t = %d, type = %d\\n", 59, t, f->type);
          throw ((unsigned int) (pgeif_IncorrectType));
        }
    }
  else
    {
      if (debugging)
        libc_printf ((char *) "throwing an exception in lookupDef (2)\\n", 40);
      throw ((unsigned int) (pgeif_IdOutOfBounds));
    }
  ReturnException ("..//pgeif.def", 1, 15);
}


/*
   check_range -
*/

static double check_range (double r, char *function_, unsigned int _function_high, char *param_, unsigned int _param_high)
{
  char function[_function_high+1];
  char param[_param_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (function, function_, _function_high+1);
  memcpy (param, param_, _param_high+1);

  if (roots_nearZero (r))
    return 0.0;
  else if (roots_nearZero (r-1.0))
    return 1.0;
  else if ((r > 0.0) && (r < 1.0))
    return r;
  else
    {
      libc_printf ((char *) "%s: parameter value %s is out of range (%g) (using 0.0)\\n", 57, &function, &param, r);
      return 0.0;
    }
}


/*
   nofree - do not free, a.
*/

static void * nofree (void * a)
{
  return a;
}


/*
   rgb - make a colour object using red, blue and green components.
         The colour object is returned.
*/

unsigned int pgeif_rgb (double r, double g, double b)
{
  Fractions_Fract rf;
  Fractions_Fract gf;
  Fractions_Fract bf;

  rf = Fractions_putReal (r);
  gf = Fractions_putReal (g);
  bf = Fractions_putReal (b);
  return trace (addDef ((TypeOfDef) colour, deviceIf_defineColour (rf, gf, bf)), (char *) "colour", 6);
}


/*
   white - returns the colour, white.
*/

unsigned int pgeif_white (void)
{
  return trace (addDef ((TypeOfDef) colour, deviceIf_white ()), (char *) "white", 5);
}


/*
   black - returns the colour, black.
*/

unsigned int pgeif_black (void)
{
  return trace (addDef ((TypeOfDef) colour, deviceIf_black ()), (char *) "black", 5);
}


/*
   red - returns the colour, red.
*/

unsigned int pgeif_red (void)
{
  return trace (addDef ((TypeOfDef) colour, deviceIf_red ()), (char *) "red", 3);
}


/*
   green - returns the colour, green.
*/

unsigned int pgeif_green (void)
{
  return trace (addDef ((TypeOfDef) colour, deviceIf_green ()), (char *) "green", 5);
}


/*
   blue - returns the colour, blue.
*/

unsigned int pgeif_blue (void)
{
  return trace (addDef ((TypeOfDef) colour, deviceIf_blue ()), (char *) "blue", 4);
}


/*
   yellow - returns the colour, yellow.
*/

unsigned int pgeif_yellow (void)
{
  return trace (addDef ((TypeOfDef) colour, deviceIf_yellow ()), (char *) "yellow", 6);
}


/*
   purple - returns the colour, purple.
*/

unsigned int pgeif_purple (void)
{
  return trace (addDef ((TypeOfDef) colour, deviceIf_purple ()), (char *) "purple", 6);
}


/*
   gravity - turn on gravity at: g m^2
*/

void pgeif_gravity (double g)
{
  twoDsim_gravity (g);
}


/*
   box - place a box in the world at (x0,y0),(x0+i,y0+j)
*/

unsigned int pgeif_box (double x0, double y0, double i, double j, unsigned int c)
{
  double k;

  x0 = check_range (x0, (char *) "box", 3, (char *) "x0", 2);
  y0 = check_range (y0, (char *) "box", 3, (char *) "y0", 2);
  k = check_range (x0+i, (char *) "box", 3, (char *) "x0+i", 4);
  k = check_range (y0+j, (char *) "box", 3, (char *) "y0+j", 4);
  return trace (addDef ((TypeOfDef) object, twoDsim_box (x0, y0, i, j, (deviceIf_Colour) lookupDef ((TypeOfDef) colour, c))), (char *) "box", 3);
}


/*
   poly3 - place a triangle in the world at:
           (x0,y0),(x1,y1),(x2,y2)
*/

unsigned int pgeif_poly3 (double x0, double y0, double x1, double y1, double x2, double y2, unsigned int c)
{
  double k;

  x0 = check_range (x0, (char *) "poly3", 5, (char *) "x0", 2);
  y0 = check_range (y0, (char *) "poly3", 5, (char *) "y0", 2);
  x1 = check_range (x1, (char *) "poly3", 5, (char *) "x1", 2);
  y1 = check_range (y1, (char *) "poly3", 5, (char *) "y1", 2);
  x2 = check_range (x2, (char *) "poly3", 5, (char *) "x2", 2);
  y2 = check_range (y2, (char *) "poly3", 5, (char *) "y2", 2);
  return trace (addDef ((TypeOfDef) object, twoDsim_poly3 (x0, y0, x1, y1, x2, y2, (deviceIf_Colour) lookupDef ((TypeOfDef) colour, c))), (char *) "poly3", 5);
}


/*
   poly4 - place a rectangle in the world at:
           (x0,y0),(x1,y1),(x2,y2),(x3,y3)
*/

unsigned int pgeif_poly4 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, unsigned int c)
{
  double k;

  x0 = check_range (x0, (char *) "poly4", 5, (char *) "x0", 2);
  y0 = check_range (y0, (char *) "poly4", 5, (char *) "y0", 2);
  x1 = check_range (x1, (char *) "poly4", 5, (char *) "x1", 2);
  y1 = check_range (y1, (char *) "poly4", 5, (char *) "y1", 2);
  x2 = check_range (x2, (char *) "poly4", 5, (char *) "x2", 2);
  y2 = check_range (y2, (char *) "poly4", 5, (char *) "y2", 2);
  x3 = check_range (x3, (char *) "poly4", 5, (char *) "x3", 2);
  y3 = check_range (y3, (char *) "poly4", 5, (char *) "y3", 2);
  return trace (addDef ((TypeOfDef) object, twoDsim_poly4 (x0, y0, x1, y1, x2, y2, x3, y3, (deviceIf_Colour) lookupDef ((TypeOfDef) colour, c))), (char *) "poly4", 5);
}


/*
   poly5 - place a pentagon in the world at:
           (x0,y0),(x1,y1),(x2,y2),(x3,y3),(x4,y4)
*/

unsigned int pgeif_poly5 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, unsigned int c)
{
  double k;

  x0 = check_range (x0, (char *) "poly5", 5, (char *) "x0", 2);
  y0 = check_range (y0, (char *) "poly5", 5, (char *) "y0", 2);
  x1 = check_range (x1, (char *) "poly5", 5, (char *) "x1", 2);
  y1 = check_range (y1, (char *) "poly5", 5, (char *) "y1", 2);
  x2 = check_range (x2, (char *) "poly5", 5, (char *) "x2", 2);
  y2 = check_range (y2, (char *) "poly5", 5, (char *) "y2", 2);
  x3 = check_range (x3, (char *) "poly5", 5, (char *) "x3", 2);
  y3 = check_range (y3, (char *) "poly5", 5, (char *) "y3", 2);
  x4 = check_range (x4, (char *) "poly5", 5, (char *) "x4", 2);
  y4 = check_range (y4, (char *) "poly5", 5, (char *) "y4", 2);
  return trace (addDef ((TypeOfDef) object, twoDsim_poly5 (x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, (deviceIf_Colour) lookupDef ((TypeOfDef) colour, c))), (char *) "poly5", 5);
}


/*
   poly6 - place a hexagon in the world at:
           (x0,y0),(x1,y1),(x2,y2),(x3,y3),(x4,y4),(x5,y5)
*/

unsigned int pgeif_poly6 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, unsigned int c)
{
  double k;

  x0 = check_range (x0, (char *) "poly6", 5, (char *) "x0", 2);
  y0 = check_range (y0, (char *) "poly6", 5, (char *) "y0", 2);
  x1 = check_range (x1, (char *) "poly6", 5, (char *) "x1", 2);
  y1 = check_range (y1, (char *) "poly6", 5, (char *) "y1", 2);
  x2 = check_range (x2, (char *) "poly6", 5, (char *) "x2", 2);
  y2 = check_range (y2, (char *) "poly6", 5, (char *) "y2", 2);
  x3 = check_range (x3, (char *) "poly6", 5, (char *) "x3", 2);
  y3 = check_range (y3, (char *) "poly6", 5, (char *) "y3", 2);
  x4 = check_range (x4, (char *) "poly6", 5, (char *) "x4", 2);
  y4 = check_range (y4, (char *) "poly6", 5, (char *) "y4", 2);
  x5 = check_range (x5, (char *) "poly6", 5, (char *) "x5", 2);
  y5 = check_range (y5, (char *) "poly6", 5, (char *) "y5", 2);
  return trace (addDef ((TypeOfDef) object, twoDsim_poly6 (x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, (deviceIf_Colour) lookupDef ((TypeOfDef) colour, c))), (char *) "poly6", 5);
}


/*
   mass - specify the mass of an object and return the, id.
*/

unsigned int pgeif_mass (unsigned int id, double m)
{
  unsigned int ti;

  ti = trace (twoDsim_mass (lookupDef ((TypeOfDef) object, id), m), (char *) "mass", 4);
  return id;
}


/*
   fix - fix the object to the world.
*/

unsigned int pgeif_fix (unsigned int id)
{
  unsigned int ti;

  ti = trace (twoDsim_fix (lookupDef ((TypeOfDef) object, id)), (char *) "fix", 3);
  return id;
}


/*
   circle - adds a circle to the world.  Center
            defined by: x0, y0 radius, radius.
*/

unsigned int pgeif_circle (double x0, double y0, double radius, unsigned int c)
{
  unsigned int ti;
  unsigned int id;

  ti = twoDsim_circle (x0, y0, radius, (deviceIf_Colour) lookupDef ((TypeOfDef) colour, (unsigned int) c));
  id = addDef ((TypeOfDef) object, ti);
  Assert (ti == (lookupDef ((TypeOfDef) object, id)));
  return trace (id, (char *) "circle", 6);
}


/*
   velocity - give an object, id, a velocity, vx, vy.
*/

unsigned int pgeif_velocity (unsigned int id, double vx, double vy)
{
  unsigned int ti;

  if (debugging)
    libc_printf ((char *) "inside velocity (id = %d)\\n", 27, id);
  ti = trace (twoDsim_velocity (lookupDef ((TypeOfDef) object, id), vx, vy), (char *) "velocity", 8);
  return id;
}


/*
   accel - give an object, id, an acceleration, ax, ay.
*/

unsigned int pgeif_accel (unsigned int id, double ax, double ay)
{
  unsigned int ti;

  ti = twoDsim_accel (lookupDef ((TypeOfDef) object, id), ax, ay);
  return id;
}


/*
   rotate - rotates object with a angular velocity, angle.
*/

unsigned int pgeif_rotate (unsigned int id, double angle)
{
  unsigned int ti;

  ti = twoDsim_rotate (lookupDef ((TypeOfDef) object, id), angle);
  return id;
}


/*
   fps - set frames per second.
*/

unsigned int pgeif_is_collision (void)
{
  return twoDsim_isCollision ();
}


/*
   fps - set frames per second.
*/

unsigned int pgeif_is_frame (void)
{
  return twoDsim_isFrame ();
}


/*
   fps - set frames per second.
*/

unsigned int pgeif_is_function (void)
{
  return twoDsim_isFunction ();
}


/*
   create_function_event - creates a function event at time, t,
                           in the future.
*/

void pgeif_create_function_event (double t, unsigned int id)
{
  twoDsim_createFunctionEvent (t, id);
}


/*
   time_until - returns the relative time from now until the next event.
*/

double pgeif_time_until (void)
{
  return twoDsim_timeUntil ();
}


/*
   skip_until - advances time for, t, units or until the next event is reached.
                The amount of time skipped is returned.  This function will not
                skip past the next event.
*/

double pgeif_skip_until (double t)
{
  return twoDsim_skipTime (t);
}


/*
   process_event - advance time to the next event and then
                   process the event.
*/

void pgeif_process_event (void)
{
  twoDsim_processEvent ();
}


/*
   fps - set frames per second.
*/

double pgeif_get_time (void)
{
  return twoDsim_getTime ();
}


/*
   rm - delete this object from the simulated world.
        The same id is returned.
*/

unsigned int pgeif_rm (unsigned int id)
{
  unsigned int ti;

  ti = twoDsim_rm (lookupDef ((TypeOfDef) object, id));
  return id;
}


/*
   get_xpos - returns the first point, x, coordinate of object.
*/

double pgeif_get_xpos (unsigned int id)
{
  return check_range (twoDsim_get_xpos (lookupDef ((TypeOfDef) object, id)), (char *) "get_xpos", 8, (char *) "id", 2);
}


/*
   get_ypos - returns the first point, y, coordinate of object.
*/

double pgeif_get_ypos (unsigned int id)
{
  return check_range (twoDsim_get_ypos (lookupDef ((TypeOfDef) object, id)), (char *) "get_ypos", 8, (char *) "id", 2);
}


/*
   get_xvel - returns the X velocity of object.
*/

double pgeif_get_xvel (unsigned int id)
{
  return twoDsim_get_xvel (lookupDef ((TypeOfDef) object, id));
}


/*
   get_yvel - returns the Y velocity of object.
*/

double pgeif_get_yvel (unsigned int id)
{
  return twoDsim_get_yvel (lookupDef ((TypeOfDef) object, id));
}


/*
   get_xaccel - returns the X accelaration of object.
*/

double pgeif_get_xaccel (unsigned int id)
{
  return twoDsim_get_xaccel (lookupDef ((TypeOfDef) object, id));
}


/*
   get_yaccel - returns the Y accelaration of object.
*/

double pgeif_get_yaccel (unsigned int id)
{
  return twoDsim_get_yaccel (lookupDef ((TypeOfDef) object, id));
}


/*
   put_xvel - assigns the X velocity of object.
*/

void pgeif_put_xvel (unsigned int id, double r)
{
  twoDsim_put_xvel (lookupDef ((TypeOfDef) object, id), r);
}


/*
   put_yvel - assigns the Y velocity of object.
*/

void pgeif_put_yvel (unsigned int id, double r)
{
  twoDsim_put_yvel (lookupDef ((TypeOfDef) object, id), r);
}


/*
   put_xaccel - assigns the X accelaration of object.
*/

void pgeif_put_xaccel (unsigned int id, double r)
{
  twoDsim_put_xaccel (lookupDef ((TypeOfDef) object, id), r);
}


/*
   put_yaccel - assigns the Y accelaration of object.
*/

void pgeif_put_yaccel (unsigned int id, double r)
{
  twoDsim_put_yaccel (lookupDef ((TypeOfDef) object, id), r);
}


/*
   set_colour - sets colour of object, id, to, c.
*/

void pgeif_set_colour (unsigned int id, unsigned int c)
{
  twoDsim_set_colour (lookupDef ((TypeOfDef) object, id), (deviceIf_Colour) lookupDef ((TypeOfDef) colour, c));
}


/*
   apply_impulse - applies an impulse of magnitude along vector
                   [x, y] for object, id.
*/

void pgeif_apply_impulse (unsigned int id, double x, double y, double m)
{
  twoDsim_apply_impulse (lookupDef ((TypeOfDef) object, id), x, y, m);
}


/*
   moving_towards - returns TRUE if object, id, is moving towards
                    a point x, y.
*/

unsigned int pgeif_moving_towards (unsigned int id, double x, double y)
{
  return twoDsim_moving_towards (lookupDef ((TypeOfDef) object, id), x, y);
}


/*
   batch - use the batch device to record the output frames.
*/

void pgeif_batch (void)
{
  deviceIf_useGroff ();
}


/*
   use_buffer - use the buffer device to record the output frames.
*/

void pgeif_use_buffer (void)
{
  double t;

  deviceIf_useBuffer ();
  t = pgeif_time_until ();
}


/*
   empty_cbuffer - empty the colour buffer.
*/

void pgeif_empty_cbuffer (void)
{
  twoDsim_emptyCbuffer ();
}


/*
   empty_fbuffer - empty the frame buffer.
*/

void pgeif_empty_fbuffer (void)
{
  twoDsim_emptyFbuffer ();
}


/*
   use_time_delay - should the frame buffer include the time delay command?
*/

void pgeif_use_time_delay (unsigned int on)
{
  twoDsim_useTimeDelay (on);
}


/*
   draw_collision - turn on drawing of the actual collision frame
                    and the prediction frame.
*/

void pgeif_draw_collision (unsigned int actual, unsigned int predict)
{
  twoDsim_drawCollisionFrames (actual, predict);
}


/*
   set_collision_colour - when two objects collide they will both be draw using
                          colour, c.
*/

void pgeif_set_collision_colour (unsigned int c)
{
  twoDsim_setCollisionColour ((deviceIf_Colour) lookupDef ((TypeOfDef) colour, c));
}


/*
   dump_world - dump a list of all objects and their characteristics.
*/

void pgeif_dump_world (void)
{
  twoDsim_dumpWorld ();
}


/*
   check_objects - perform a check to make sure that all non fixed
                   objects have a mass.
*/

void pgeif_check_objects (void)
{
  twoDsim_checkObjects ();
}


/*
   l2h - translate a twoDsim, id, to the pgeid.
*/

unsigned int pgeif_l2h (unsigned int id)
{
  def d;
  unsigned int i;
  unsigned int h;

  h = Indexing_HighIndice (listOfDefs);
  i = 1;
  while (i <= h)
    {
      d = Indexing_GetIndice (listOfDefs, i);
      if ((d->definition == id) && (d->type == object))
        return i;
      i += 1;
    }
  return 0;
}


/*
   h2l - translate a pgeif, id, to the twoDsim.
*/

unsigned int pgeif_h2l (unsigned int id)
{
  def d;

  d = Indexing_GetIndice (listOfDefs, id);
  return d->definition;
}


/*
   fps - set frames per second.
*/

void pgeif_fps (double f)
{
  twoDsim_fps (f);
}

void _M2_pgeif_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  init ();
}

void _M2_pgeif_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
