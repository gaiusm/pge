/* automatically created by mc from ../pgeif.def.  */


#if !defined (_pgeif_H)
#   define _pgeif_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_pgeif_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef enum {pgeif_IncorrectType, pgeif_IdOutOfBounds, pgeif_ValueOutOfRange} pgeif_ExceptionKind;


/*
   rgb - make a colour object using red, blue and green components.
         The colour object is returned.
*/

EXTERN unsigned int pgeif_rgb (double r, double g, double b);

/*
   white - returns the colour, white.
*/

EXTERN unsigned int pgeif_white (void);

/*
   black - returns the colour, black.
*/

EXTERN unsigned int pgeif_black (void);

/*
   red - returns the colour, red.
*/

EXTERN unsigned int pgeif_red (void);

/*
   green - returns the colour, green.
*/

EXTERN unsigned int pgeif_green (void);

/*
   blue - returns the colour, blue.
*/

EXTERN unsigned int pgeif_blue (void);

/*
   yellow - returns the colour, yellow.
*/

EXTERN unsigned int pgeif_yellow (void);

/*
   purple - returns the colour, purple.
*/

EXTERN unsigned int pgeif_purple (void);

/*
   gravity - turn on gravity at: g m^2
*/

EXTERN void pgeif_gravity (double g);

/*
   box - place a box in the world at (x0,y0),(x0+i,y0+j)
*/

EXTERN unsigned int pgeif_box (double x0, double y0, double i, double j, unsigned int c);

/*
   poly3 - place a triangle in the world at:
           (x0,y0), (x1,y1), (x2,y2)
*/

EXTERN unsigned int pgeif_poly3 (double x0, double y0, double x1, double y1, double x2, double y2, unsigned int c);

/*
   poly4 - place a rectangle in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3)
*/

EXTERN unsigned int pgeif_poly4 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, unsigned int c);

/*
   poly5 - place a pentagon in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3), (x4,y4)
*/

EXTERN unsigned int pgeif_poly5 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, unsigned int c);

/*
   poly6 - place a hexagon in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3), (x4,y4), (x5,y5)
*/

EXTERN unsigned int pgeif_poly6 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, unsigned int c);

/*
   mass - specify the mass of an object and return the, id.
*/

EXTERN unsigned int pgeif_mass (unsigned int id, double m);

/*
   fix - fix the object to the world.
*/

EXTERN unsigned int pgeif_fix (unsigned int id);

/*
   circle - adds a circle to the world.  Center
            defined by: x0, y0 radius, radius.
*/

EXTERN unsigned int pgeif_circle (double x0, double y0, double radius, unsigned int c);

/*
   velocity - give an object, id, a velocity, vx, vy.
*/

EXTERN unsigned int pgeif_velocity (unsigned int id, double vx, double vy);

/*
   accel - give an object, id, an acceleration, ax, ay.
*/

EXTERN unsigned int pgeif_accel (unsigned int id, double ax, double ay);

/*
   rotate - rotates object with a angular velocity, angle.
*/

EXTERN unsigned int pgeif_rotate (unsigned int id, double angle);

/*
   is_collision - returns TRUE if next event is a collision event.
*/

EXTERN unsigned int pgeif_is_collision (void);

/*
   is_frame - returns TRUE if the next event is a redraw frame event.
*/

EXTERN unsigned int pgeif_is_frame (void);

/*
   is_function - returns TRUE if the next event is a function event.
*/

EXTERN unsigned int pgeif_is_function (void);

/*
   create_function_event - creates a function event at time, t,
                           in the future.
*/

EXTERN void pgeif_create_function_event (double t, unsigned int id);

/*
   time_until - returns the relative time from now until the next event.
*/

EXTERN double pgeif_time_until (void);

/*
   skip_until - advances time for, t, units or until the next event is reached.
*/

EXTERN double pgeif_skip_until (double t);

/*
   process_event - advance time to the next event and then
                   process the event.
*/

EXTERN void pgeif_process_event (void);

/*
   get_time - return the current simulation time.
*/

EXTERN double pgeif_get_time (void);

/*
   rm - delete this object from the simulated world.
        The same id is returned.
*/

EXTERN unsigned int pgeif_rm (unsigned int id);

/*
   get_xpos - returns the first point, x, coordinate of object.
*/

EXTERN double pgeif_get_xpos (unsigned int id);

/*
   get_ypos - returns the first point, y, coordinate of object.
*/

EXTERN double pgeif_get_ypos (unsigned int id);

/*
   get_xvel - returns the X velocity of object.
*/

EXTERN double pgeif_get_xvel (unsigned int id);

/*
   get_yvel - returns the Y velocity of object.
*/

EXTERN double pgeif_get_yvel (unsigned int id);

/*
   get_xaccel - returns the X acceleration of object.
*/

EXTERN double pgeif_get_xaccel (unsigned int id);

/*
   get_yaccel - returns the Y acceleration of object.
*/

EXTERN double pgeif_get_yaccel (unsigned int id);

/*
   put_xvel - assigns the X velocity of object.
*/

EXTERN void pgeif_put_xvel (unsigned int id, double r);

/*
   put_yvel - assigns the Y velocity of object.
*/

EXTERN void pgeif_put_yvel (unsigned int id, double r);

/*
   put_xaccel - assigns the X acceleration of object.
*/

EXTERN void pgeif_put_xaccel (unsigned int id, double r);

/*
   put_yaccel - assigns the Y acceleration of object.
*/

EXTERN void pgeif_put_yaccel (unsigned int id, double r);

/*
   set_colour - sets colour of object, id, to, c.
*/

EXTERN void pgeif_set_colour (unsigned int id, unsigned int c);

/*
   apply_impulse - applies an impulse of magnitude along vector
                   [x, y] for object, id.
*/

EXTERN void pgeif_apply_impulse (unsigned int id, double x, double y, double m);

/*
   moving_towards - returns TRUE if object, id, is moving towards
                    a point x, y.
*/

EXTERN unsigned int pgeif_moving_towards (unsigned int id, double x, double y);

/*
   batch - use the batch device to record the output frames.
*/

EXTERN void pgeif_batch (void);

/*
   use_buffer - use the buffer device to record the output frames.
*/

EXTERN void pgeif_use_buffer (void);

/*
   empty_cbuffer - empty the colour buffer.
*/

EXTERN void pgeif_empty_cbuffer (void);

/*
   empty_fbuffer - empty the frame buffer.
*/

EXTERN void pgeif_empty_fbuffer (void);
EXTERN void pgeif_use_time_delay (unsigned int on);

/*
   draw_collision - turn on drawing of the actual collision frame
                    and the prediction frame.
*/

EXTERN void pgeif_draw_collision (unsigned int actual, unsigned int predict);

/*
   set_collision_colour - when two objects collide they will both be draw using
                          colour, c.
*/

EXTERN void pgeif_set_collision_colour (unsigned int c);

/*
   dump_world - dump a list of all objects and their characteristics.
*/

EXTERN void pgeif_dump_world (void);

/*
   check_objects - perform a check to make sure that all non fixed
                   objects have a mass.
*/

EXTERN void pgeif_check_objects (void);

/*
   l2h - translate a twoDsim, id, to the pgeid.
*/

EXTERN unsigned int pgeif_l2h (unsigned int id);

/*
   h2l - translate a pgeif, id, to the twoDsim.
*/

EXTERN unsigned int pgeif_h2l (unsigned int id);

/*
   fps - set frames per second.
*/

EXTERN void pgeif_fps (double f);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
