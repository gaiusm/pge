/* automatically created by mc from ../twoDsim.def.  */


#if !defined (_twoDsim_H)
#   define _twoDsim_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"
#   include "GdeviceIf.h"
#   include "Ghistory.h"

#   if defined (_twoDsim_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   gravity - turn on gravity at: g m^2
*/

EXTERN void twoDsim_gravity (double g);

/*
   box - place a box in the world at (x0,y0), (x0+i,y0),
         (x0+i, y0+j), (x0, y0+j).
*/

EXTERN unsigned int twoDsim_box (double x0, double y0, double i, double j, deviceIf_Colour colour);

/*
   poly3 - place a triangle in the world at:
           (x0,y0),(x1,y1),(x2,y2)
*/

EXTERN unsigned int twoDsim_poly3 (double x0, double y0, double x1, double y1, double x2, double y2, deviceIf_Colour colour);

/*
   poly4 - place a quadrangle in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3)  the points must be in order,
           either anticlockwise or clockwise.
*/

EXTERN unsigned int twoDsim_poly4 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, deviceIf_Colour colour);

/*
   poly5 - place a pentagon in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3), (x4,y4)
           the points must be in order, either anticlockwise or clockwise.
*/

EXTERN unsigned int twoDsim_poly5 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, deviceIf_Colour colour);

/*
   poly6 - place a hexagon in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3), (x4,y4), (x5,y5)
           the points must be in order, either anticlockwise or clockwise.
*/

EXTERN unsigned int twoDsim_poly6 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, deviceIf_Colour colour);

/*
   get_xpos - returns the first point, x, coordinate of object.
*/

EXTERN double twoDsim_get_xpos (unsigned int id);

/*
   get_ypos - returns the first point, y, coordinate of object.
*/

EXTERN double twoDsim_get_ypos (unsigned int id);

/*
   get_xvel - returns the x velocity of object.
*/

EXTERN double twoDsim_get_xvel (unsigned int id);

/*
   get_yvel - returns the y velocity of object.
*/

EXTERN double twoDsim_get_yvel (unsigned int id);

/*
   get_xaccel - returns the x acceleration of object.
*/

EXTERN double twoDsim_get_xaccel (unsigned int id);

/*
   get_yaccel - returns the y acceleration of object.
*/

EXTERN double twoDsim_get_yaccel (unsigned int id);

/*
   put_xvel - assigns the x velocity of object.
*/

EXTERN void twoDsim_put_xvel (unsigned int id, double r);

/*
   put_yvel - assigns the y velocity of object.
*/

EXTERN void twoDsim_put_yvel (unsigned int id, double r);

/*
   put_xaccel - assigns the x acceleration of object.
*/

EXTERN void twoDsim_put_xaccel (unsigned int id, double r);

/*
   put_yaccel - assigns the y acceleration of object.
*/

EXTERN void twoDsim_put_yaccel (unsigned int id, double r);

/*
   apply_impulse - apply an impulse to object, id,
                   along the vector [x, y] with magnitude, m.
                   Nothing happens if the object is fixed.
                   Currently only circles can have impulses
                   applied.
*/

EXTERN void twoDsim_apply_impulse (unsigned int id, double x, double y, double m);

/*
   moving_towards - returns TRUE if object, id, is moving towards
                    a point x, y.
*/

EXTERN unsigned int twoDsim_moving_towards (unsigned int id, double x, double y);

/*
   set_colour - set the colour of object, id, to colour.
                id must be a box or circle.
*/

EXTERN void twoDsim_set_colour (unsigned int id, deviceIf_Colour colour);

/*
   mass - specify the mass of an object and return the, id.
*/

EXTERN unsigned int twoDsim_mass (unsigned int id, double m);

/*
   fix - fix the object to the world.
*/

EXTERN unsigned int twoDsim_fix (unsigned int id);

/*
   circle - adds a circle to the world.  Center
            defined by: x0, y0 radius, radius.
*/

EXTERN unsigned int twoDsim_circle (double x0, double y0, double radius, deviceIf_Colour colour);

/*
   velocity - give an object, id, a velocity, vx, vy.
*/

EXTERN unsigned int twoDsim_velocity (unsigned int id, double vx, double vy);

/*
   accel - give an object, id, an acceleration, ax, ay.
*/

EXTERN unsigned int twoDsim_accel (unsigned int id, double ax, double ay);

/*
   rotate - gives object, id, an initial orientation.
*/

EXTERN unsigned int twoDsim_rotate (unsigned int id, double angle);

/*
   rvel - gives object, id, an angular velocity, angle.
*/

EXTERN unsigned int twoDsim_rvel (unsigned int id, double angle);

/*
   fps - set frames per second.
*/

EXTERN void twoDsim_fps (double f);

/*
   replayRate - set frames per second during replay.
*/

EXTERN void twoDsim_replayRate (double f);

/*
   simulateFor - render for, t, seconds.
*/

EXTERN void twoDsim_simulateFor (double t);

/*
   getTime - returns the current time in the simulation.
*/

EXTERN double twoDsim_getTime (void);

/*
   skipTime - attempts to skip, t, seconds.  It returns the amount
              of time actually skipped.  This function will not skip
              past the next event.
*/

EXTERN double twoDsim_skipTime (double t);

/*
   timeUntil - returns the relative time from now until the next event.
*/

EXTERN double twoDsim_timeUntil (void);

/*
   processEvent - skips any outstanding time and processes the next event.
                  Time is adjusted to the time of the next event.
*/

EXTERN void twoDsim_processEvent (void);

/*
   isCollision - returns TRUE if the next event is a collision event.
*/

EXTERN unsigned int twoDsim_isCollision (void);

/*
   isFrame - returns TRUE if the next event is a frame event.
*/

EXTERN unsigned int twoDsim_isFrame (void);

/*
   isFunction - returns TRUE if the next event is a function event.
*/

EXTERN unsigned int twoDsim_isFunction (void);

/*
   createFunctionEvent - creates a function event at time, t,
                         in the future.
*/

EXTERN void twoDsim_createFunctionEvent (double t, unsigned int id);

/*
   rm - delete this object from the simulated world.
        The same id is returned.
*/

EXTERN unsigned int twoDsim_rm (unsigned int id);

/*
   getEventBuffer - collects the event buffer limits in the following parameters.
*/

EXTERN void twoDsim_getEventBuffer (void * *start, unsigned int *length, unsigned int *used);

/*
   buildFrame - populate the frame buffer contents with the world at the current time.
*/

EXTERN void twoDsim_buildFrame (void);

/*
   emptyCbuffer - empty the colour buffer.
*/

EXTERN void twoDsim_emptyCbuffer (void);

/*
   emptyFbuffer - empty the frame buffer.
*/

EXTERN void twoDsim_emptyFbuffer (void);

/*
   useTimeDelay - should the frame buffer include the time delay command?
*/

EXTERN void twoDsim_useTimeDelay (unsigned int on);

/*
   drawCollisionFrames - turn the drawing of collision frames on or off.
                         actual:   determines whether an extra frame is generated
                                   at the time of actual collision.
                         predict:  draws a frame predicting the next collision.
                                   It will show the points predicted to collide.
*/

EXTERN void twoDsim_drawCollisionFrames (unsigned int actual, unsigned int predict);

/*
   setCollisionColour - assigns, c, as the colour for objects colliding.
*/

EXTERN void twoDsim_setCollisionColour (deviceIf_Colour c);

/*
   dumpWorld - dump a list of all objects and their characteristics.
*/

EXTERN void twoDsim_dumpWorld (void);

/*
   checkObjects - perform a check to make sure that all non fixed objects have a mass.
                  If an object does not have a mass then an error message is written
                  and the library exits with exit code 1.
*/

EXTERN void twoDsim_checkObjects (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
