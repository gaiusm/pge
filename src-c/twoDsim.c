/* automatically created by mc from ../twoDsim.mod.  */

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

#include <stddef.h>
#include <string.h>
#include <limits.h>
#   include "GStorage.h"
#   include "Gmcrts.h"
#define _twoDsim_H
#define _twoDsim_C

#   include "GSYSTEM.h"
#   include "GStorage.h"
#   include "GIndexing.h"
#   include "Glibc.h"
#   include "GdeviceIf.h"
#   include "Glibm.h"
#   include "Groots.h"
#   include "GFractions.h"
#   include "GPoints.h"
#   include "GGC.h"
#   include "Gcoord.h"
#   include "Gpolar.h"
#   include "Ghistory.h"
#   include "Gdelay.h"
#   include "GMathLib0.h"
#   include "GIOChan.h"
#   include "GChanConsts.h"
#   include "GNetworkOrder.h"
#   include "GStrLib.h"
#   include "GMemStream.h"
#   include "Ggdbif.h"
#   include "GM2RTS.h"

#   define MaxPolygonPoints 6
#   define DefaultFramesPerSecond 100.0
#   define Debugging FALSE
#   define DebugTrace FALSE
#   define BufferedTime 0.1
#   define InactiveTime 1.0
#   define Elasticity 0.98
typedef struct descP_p descP;

typedef struct cDesc_r cDesc;

typedef struct cpDesc_r cpDesc;

typedef struct ppDesc_r ppDesc;

typedef struct fcDesc_r fcDesc;

typedef struct Spring_r Spring;

typedef struct Circle_r Circle;

typedef struct Polygon_r Polygon;

typedef struct eventProc_p eventProc;

typedef struct _T1_r _T1;

typedef _T1 *eventDesc;

typedef struct _T2_r _T2;

typedef _T2 *Object;

typedef struct _T3_a _T3;

typedef struct _T4_r _T4;

typedef _T4 *eventQueue;

typedef enum {polygonOb, circleOb, springOb} ObjectType;

typedef enum {frameKind, functionKind, collisionKind} eventKind;

typedef enum {frameEvent, circlesEvent, circlePolygonEvent, polygonPolygonEvent, functionEvent} eventType;

#   define thickness 0.01
typedef eventDesc (*descP_t) (eventDesc, unsigned int, unsigned int, unsigned int, unsigned int, history_whereHit, history_whereHit, coord_Coord);
struct descP_p { descP_t proc; };

struct cDesc_r {
                 coord_Coord cPoint;
                 unsigned int cid1;
                 unsigned int cid2;
               };

struct cpDesc_r {
                  coord_Coord cPoint;
                  unsigned int pid;
                  unsigned int cid;
                  history_whereHit wpid;
                  unsigned int lineNo;
                  unsigned int pointNo;
                };

struct ppDesc_r {
                  coord_Coord cPoint;
                  unsigned int pid1;
                  unsigned int pid2;
                  history_whereHit wpid1;
                  history_whereHit wpid2;
                  unsigned int lineCorner1;
                  unsigned int lineCorner2;
                };

struct fcDesc_r {
                  unsigned int id;
                };

struct Spring_r {
                  unsigned int id1;
                  unsigned int id2;
                  double k;
                };

struct Circle_r {
                  coord_Coord pos;
                  double r;
                  double mass;
                  deviceIf_Colour col;
                };

typedef void (*eventProc_t) (eventQueue);
struct eventProc_p { eventProc_t proc; };

struct _T3_a { polar_Polar array[MaxPolygonPoints+1]; };
struct Polygon_r {
                   unsigned int nPoints;
                   _T3 points;
                   double mass;
                   deviceIf_Colour col;
                   coord_Coord cOfG;
                 };

struct _T1_r {
               eventType etype;  /* case tag */
               union {
                       cDesc cc;
                       cpDesc cp;
                       ppDesc pp;
                       fcDesc fc;
                     };
               eventDesc next;
             };

struct _T4_r {
               eventKind kind;
               double time;
               eventProc p;
               eventDesc ePtr;
               eventQueue next;
             };

struct _T2_r {
               unsigned int id;
               unsigned int deleted;
               unsigned int fixed;
               unsigned int stationary;
               double vx;
               double vy;
               double ax;
               double ay;
               double inertia;
               double angleOrientation;
               double angularVelocity;
               double angularMomentum;
               unsigned int interpen;
               ObjectType object;  /* case tag */
               union {
                       Polygon p;
                       Circle c;
                       Spring s;
                     };
             };

static Indexing_Index objects;
static unsigned int maxId;
static double lastDrawTime;
static double lastUpdateTime;
static double currentTime;
static double replayPerSecond;
static double framesPerSecond;
static double simulatedGravity;
static eventQueue eventQ;
static eventQueue freeEvents;
static eventDesc freeDesc;
static unsigned int trace;
static unsigned int writeTimeDelay;
static unsigned int drawPrediction;
static unsigned int drawCollisionFrame;
static unsigned int haveCollisionColour;
static deviceIf_Colour collisionColour;
static void * bufferStart;
static unsigned int bufferLength;
static unsigned int bufferUsed;
static unsigned int fileOpened;
static IOChan_ChanId file;

/*
   gravity - turn on gravity at: g m^2
*/

void twoDsim_gravity (double g);

/*
   box - place a box in the world at (x0,y0), (x0+i,y0),
         (x0+i, y0+j), (x0, y0+j).
*/

unsigned int twoDsim_box (double x0, double y0, double i, double j, deviceIf_Colour colour);

/*
   poly3 - place a triangle in the world at:
           (x0,y0), (x1,y1), (x2,y2)
*/

unsigned int twoDsim_poly3 (double x0, double y0, double x1, double y1, double x2, double y2, deviceIf_Colour colour);

/*
   poly4 - place a quadrangle in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3)  the points must be in order,
           either anticlockwise or clockwise.
*/

unsigned int twoDsim_poly4 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, deviceIf_Colour colour);

/*
   poly5 - place a pentagon in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3), (x4,y4)
           the points must be in order, either anticlockwise or clockwise.
*/

unsigned int twoDsim_poly5 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, deviceIf_Colour colour);

/*
   poly6 - place a hexagon in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3), (x4,y4), (x5,y5)
           the points must be in order, either anticlockwise or clockwise.
*/

unsigned int twoDsim_poly6 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, deviceIf_Colour colour);

/*
   get_xpos - returns the x coordinate of the center of gravity of object, id.
*/

double twoDsim_get_xpos (unsigned int id);

/*
   get_ypos - returns the first point, y, coordinate of object.
*/

double twoDsim_get_ypos (unsigned int id);

/*
   get_xvel - returns the x velocity of object.
*/

double twoDsim_get_xvel (unsigned int id);

/*
   get_yvel - returns the y velocity of object.
*/

double twoDsim_get_yvel (unsigned int id);

/*
   get_xaccel - returns the x acceleration of object.
*/

double twoDsim_get_xaccel (unsigned int id);

/*
   get_yaccel - returns the y acceleration of object.
*/

double twoDsim_get_yaccel (unsigned int id);

/*
   put_xvel - assigns the x velocity of object.
*/

void twoDsim_put_xvel (unsigned int id, double r);

/*
   put_yvel - assigns the y velocity of object.
*/

void twoDsim_put_yvel (unsigned int id, double r);

/*
   put_xaccel - assigns the x acceleration of object.
*/

void twoDsim_put_xaccel (unsigned int id, double r);

/*
   put_yaccel - assigns the y acceleration of object.
*/

void twoDsim_put_yaccel (unsigned int id, double r);

/*
   apply_impulse - apply an impulse to object, id,
                   along the vector [x, y] with magnitude, m.
                   Nothing happens if the object is fixed.
                   Currently only circles can have impulses
                   applied.
*/

void twoDsim_apply_impulse (unsigned int id, double x, double y, double m);

/*
   moving_towards - returns TRUE if object, id, is moving towards
                    a point x, y.
*/

unsigned int twoDsim_moving_towards (unsigned int id, double x, double y);

/*
   set_colour - set the colour of object, id, to colour.
                id must be a box or circle.
*/

void twoDsim_set_colour (unsigned int id, deviceIf_Colour colour);

/*
   mass - specify the mass of an object and return the, id.
          Only polygon (and box) and circle objects may have
          a mass.
*/

unsigned int twoDsim_mass (unsigned int id, double m);

/*
   fix - fix the object to the world.
*/

unsigned int twoDsim_fix (unsigned int id);

/*
   circle - adds a circle to the world.  Center
            defined by: x0, y0 radius, r.
*/

unsigned int twoDsim_circle (double x0, double y0, double radius, deviceIf_Colour colour);

/*
   velocity - give an object, id, a velocity, vx, vy.
*/

unsigned int twoDsim_velocity (unsigned int id, double vx, double vy);

/*
   accel - give an object, id, an acceleration, ax, ay.
*/

unsigned int twoDsim_accel (unsigned int id, double ax, double ay);

/*
   rotate - gives object, id, an initial orientation.
*/

unsigned int twoDsim_rotate (unsigned int id, double angle);

/*
   rvel - gives object, id, an angular velocity, angle.
*/

unsigned int twoDsim_rvel (unsigned int id, double angle);

/*
   fps - set frames per second.
*/

void twoDsim_fps (double f);

/*
   replayRate - set frames per second during replay.
*/

void twoDsim_replayRate (double f);

/*
   simulateFor - render for, t, seconds.
*/

void twoDsim_simulateFor (double t);

/*
   getTime - returns the current time in the simulation.
*/

double twoDsim_getTime (void);

/*
   skipTime - attempts to skip, t, seconds.  It returns the amount
              of time actually skipped.  This function will not skip
              past the next event.
*/

double twoDsim_skipTime (double t);

/*
   timeUntil - returns the relative time from now until the next event.
*/

double twoDsim_timeUntil (void);

/*
   processEvent - skips any outstanding time and processes the next event.
                  Time is adjusted to the time of the next event.
*/

void twoDsim_processEvent (void);

/*
   isCollision - returns TRUE if the next event is a collision event.
*/

unsigned int twoDsim_isCollision (void);

/*
   isFrame - returns TRUE if the next event is a frame event.
*/

unsigned int twoDsim_isFrame (void);

/*
   isFunction - returns TRUE if the next event is a function event.
*/

unsigned int twoDsim_isFunction (void);

/*
   createFunctionEvent - creates a function event at time, t,
                         in the future.
*/

void twoDsim_createFunctionEvent (double t, unsigned int id);

/*
   rm - delete this object from the simulated world.
        The same id is returned.
*/

unsigned int twoDsim_rm (unsigned int id);

/*
   getEventBuffer - collects the event buffer limits in the following parameters.
*/

void twoDsim_getEventBuffer (void * *start, unsigned int *length, unsigned int *used);

/*
   buildFrame - populate the frame buffer contents with the world at the current time.
*/

void twoDsim_buildFrame (void);

/*
   emptyCbuffer - empty the colour buffer.
*/

void twoDsim_emptyCbuffer (void);

/*
   emptyFbuffer - empty the frame buffer.
*/

void twoDsim_emptyFbuffer (void);

/*
   useTimeDelay - should the frame buffer include the time delay command?
*/

void twoDsim_useTimeDelay (unsigned int on);

/*
   drawCollisionFrames - turn the drawing of collision frames on or off.
                         actual:   determines whether an extra frame is generated
                                   at the time of actual collision.
                         predict:  draws a frame predicting the next collision.
                                   It will show the points predicted to collide.
*/

void twoDsim_drawCollisionFrames (unsigned int actual, unsigned int predict);

/*
   setCollisionColour - assigns, c, as the colour for objects colliding.
*/

void twoDsim_setCollisionColour (deviceIf_Colour c);

/*
   dumpWorld - dump a list of all objects and their characteristics.
*/

void twoDsim_dumpWorld (void);

/*
   checkObjects - perform a check to make sure that all non fixed objects have a mass.
*/

void twoDsim_checkObjects (void);

/*
   Assert -
*/

static void Assert (unsigned int b, unsigned int line);

/*
   AssertR -
*/

static void AssertR (double a, double b);

/*
   AssertRDebug -
*/

static void AssertRDebug (double a, double b, char *message_, unsigned int _message_high);

/*
   dumpCircle -
*/

static void dumpCircle (Object o);

/*
   dumpPolygon -
*/

static void dumpPolygon (Object o);

/*
   checkDeleted -
*/

static void checkDeleted (Object o);

/*
   DumpObject -
*/

static void DumpObject (Object o);

/*
   c2p - returns a Point given a Coord.
*/

static Points_Point c2p (coord_Coord c);

/*
   newObject - creates an object of, type, and returns its, id.
*/

static unsigned int newObject (ObjectType type);

/*
   circle_moving_towards - return TRUE if object, optr, is moving towards
                           point, x, y.  The object may still miss point x, y
                           but it is moving closer to this position.
*/

static unsigned int circle_moving_towards (Object optr, double x, double y);

/*
   apply_impulse_to_circle - apply an impulse to moving circle, movable,
                             along the vector [x, y] with magnitude, m.
*/

static void apply_impulse_to_circle (Object movable, double x, double y, double m);

/*
   objectExists -
*/

static unsigned int objectExists (Object o);

/*
   doCheckInterpenCircleCircle -
*/

static unsigned int doCheckInterpenCircleCircle (Object fixed, Object movable);

/*
   doCheckInterpenCircleCircleMoving -
*/

static unsigned int doCheckInterpenCircleCircleMoving (Object c1, Object c2);

/*
   distanceLinePoint - c is a point.  p1->p2 is the line in question.
                       p3 is assigned to the closest point on the line
                       to the point, c.  d is the distance from c to p3.
                       TRUE is returned if the point, c, lies above or
                       below the line once the line is rotated onto the x
                       axis.  (The point, c, would also rotated to solve
                       this question).
*/

static unsigned int distanceLinePoint (coord_Coord c, coord_Coord p1, coord_Coord p2, coord_Coord *p3, double *d);

/*
   checkLimits -
*/

static coord_Coord checkLimits (coord_Coord c, double r);

/*
   doCheckInterpenCirclePolygon -
*/

static unsigned int doCheckInterpenCirclePolygon (Object iptr, Object jptr);

/*
   doCheckInterpenPolygon -
*/

static unsigned int doCheckInterpenPolygon (Object iptr, Object jptr);

/*
   doCheckInterpenCircle -
*/

static unsigned int doCheckInterpenCircle (Object iptr, Object jptr);

/*
   initInterpen -
*/

static void initInterpen (void);

/*
   max - return the maximum of a and b.
*/

static unsigned int max (unsigned int a, unsigned int b);

/*
   checkInterpenCircle -
*/

static void checkInterpenCircle (void);

/*
   checkInterpenPolygon -
*/

static void checkInterpenPolygon (void);

/*
   checkInterpen -
*/

static void checkInterpen (void);

/*
   resetStationary -
*/

static void resetStationary (void);

/*
   spring - join object, id1, and, id2, with a string of defined
            by hooks constant, k.
*/

static unsigned int spring (unsigned int id1, unsigned int id2, double k);

/*
   calculateCofG -
*/

static coord_Coord calculateCofG (unsigned int n, coord_Coord *p_, unsigned int _p_high);

/*
   calcArea -
*/

static double calcArea (unsigned int n, coord_Coord *p_, unsigned int _p_high);

/*
   debugCircle - displays a circle at position, p, with radius, r, in colour, c.
*/

static void debugCircle (coord_Coord p, double r, deviceIf_Colour c);

/*
   debugLine - displays a line from, p1, to, p2, in the debugging colour.
*/

static void debugLine (coord_Coord p1, coord_Coord p2, deviceIf_Colour c);

/*
   doCircle - pass parameters to the groffDevice.
*/

static void doCircle (coord_Coord p, double r, deviceIf_Colour c);

/*
   doPolygon -
*/

static void doPolygon (unsigned int n, coord_Coord *p_, unsigned int _p_high, deviceIf_Colour c);

/*
   drawBoarder -
*/

static void drawBoarder (deviceIf_Colour c);

/*
   drawBackground -
*/

static void drawBackground (deviceIf_Colour c);

/*
   getVelCoord - returns a velocity coordinate pair for Object, o.
*/

static coord_Coord getVelCoord (Object o);

/*
   getAccelCoord - returns an acceleration coordinate pair for Object, o.
*/

static coord_Coord getAccelCoord (Object o);

/*
   getCollisionColour - returns the collision colour if requiredDebug,
                        otherwise return, c.
*/

static deviceIf_Colour getCollisionColour (deviceIf_Colour c, unsigned int requiredDebug);

/*
   doDrawFrame -
*/

static void doDrawFrame (Object optr, double dt, unsigned int needsDebug);

/*
   getCollisionObjects -
*/

static void getCollisionObjects (Object *id1, Object *id2, eventQueue e);

/*
   drawFrame - draws the current world into the frame buffer.
               If e is not NIL then it will be a collision event
               which describes the objects colliding.  The
               drawFrame will draw these objects using
               the debugging colour.
*/

static void drawFrame (eventQueue e);

/*
   drawFrameEvent -
*/

static void drawFrameEvent (eventQueue e);

/*
   incRadians - return (a + b) mod 2pi.   The value returned will be between 0..2pi
*/

static double incRadians (double a, double b);

/*
   updatePolygon -
*/

static void updatePolygon (Object optr, double dt);

/*
   updateCircle -
*/

static void updateCircle (Object optr, double dt);

/*
   updateOb -
*/

static void updateOb (Object optr, double dt);

/*
   doUpdatePhysics - updates all positions of objects based on the passing of
                     dt seconds.
*/

static void doUpdatePhysics (double dt);

/*
   updatePhysics - updates the velocity of all objects based on
                   the elapsed time from the last collision until now.
*/

static void updatePhysics (void);

/*
   displayEvent -
*/

static void displayEvent (eventQueue e);

/*
   printQueue - prints out the event queue.
*/

static void printQueue (void);

/*
   updateStats -
*/

static void updateStats (double dt);

/*
   doFunctionEvent -
*/

static void doFunctionEvent (eventQueue e);

/*
   doNextEvent -
*/

static double doNextEvent (void);

/*
   checkZero -
*/

static void checkZero (double *v);

/*
   checkZeroCoord -
*/

static coord_Coord checkZeroCoord (coord_Coord c);

/*
   inElastic -
*/

static void inElastic (double *v);

/*
   nearZeroVelocity - returns TRUE if, r, is close to 0.0
*/

static unsigned int nearZeroVelocity (double r);

/*
   checkStationary - checks to see if object, o, should be put into
                     the stationary state.
*/

static void checkStationary (Object o);

/*
   checkStationaryCollision - stationary object, a, has been bumped by
                              moving object, b.  We move a slightly and
                              give it an initial velocity and change its
                              state from stationary to moving.
*/

static void checkStationaryCollision (Object a, Object b);

/*
   collideFixedCircles - works out the new velocity given that the circle
                         movable collides with the fixed circle.
*/

static void collideFixedCircles (Object movable, Object fixed);

/*
   collideAgainstFixedCircle - the movable object collides against a point, center.
                               center, is the center point of the other fixed circle.
                               This procedure works out the new velocity of the movable
                               circle given these constraints.
*/

static void collideAgainstFixedCircle (Object movable, coord_Coord center);

/*
   collideMovableCircles -
*/

static void collideMovableCircles (Object iptr, Object jptr);

/*
   circleCollision - call fixed or movable circle collision depending upon whether
                     one or two circles are fixed.
                     Apart from taking into account rotation of either circle this
                     is complete.
*/

static void circleCollision (Object iptr, Object jptr);

/*
   collideCircleAgainstFixedEdge - modifies the circle velocity based upon the edge it hits.
                                   We use the formula:

                                   V = 2 * (-I . N ) * N + I

                                   where:

                                   I is the initial velocity vector
                                   V is the final velocity vector
                                   N is the normal to the line
*/

static void collideCircleAgainstFixedEdge (Object cPtr, coord_Coord p1, coord_Coord p2);

/*
   circlePolygonCollision -
*/

static void circlePolygonCollision (eventQueue e, Object cPtr, Object pPtr);

/*
   collidePolygonAgainstFixedCircle - polygon, o, is moving and has hit
                                      a fixed circle at position, collision.
*/

static void collidePolygonAgainstFixedCircle (Object o, coord_Coord collision);

/*
   collidePolygonAgainstFixedEdge - p1, p2 is the fixed edge and, o, is the
                                    moving polygon.
*/

static void collidePolygonAgainstFixedEdge (Object o, coord_Coord p1, coord_Coord p2);

/*
   rotationalVelocity - return a vector containing the velocity
                        if polygon is rotating at angular speed, w,
                        and non rotation speed is, u and the relative
                        position is, r.
*/

static coord_Coord rotationalVelocity (double w, coord_Coord u, coord_Coord r);

/*
   calcInertia - calculate the inertia of a polygon.
*/

static void calcInertia (Object id);

/*
   updatePolygonVelocity - update both linear and angular velocities of
                           object, o, using impulse, j.
                           n is the perpendicular to the impact.
                           rp is the distance of the c of g of an object,
                           o, to the point of collision.
*/

static void updatePolygonVelocity (Object o, double j, coord_Coord n, coord_Coord rpn);

/*
   polygonPolygonCollision - two polygons collide, we call the appropriate routines
                             depending upon whether one polygon is fixed.
*/

static void polygonPolygonCollision (eventQueue e, Object id1, Object id2);

/*
   reflect - reflect velocity, v, off line, l.

             V = 2 * (-I . n ) * n + I

             where:

             I is the initial velocity vector
             V is the final velocity vector
             n is the normal to the line, l.
*/

static coord_Coord reflect (coord_Coord v, coord_Coord l);

/*
   collidePolygonAgainstFixedPolygon - id1 is moving and id2 is fixed.
*/

static void collidePolygonAgainstFixedPolygon (eventQueue e, Object id1, Object id2);

/*
   collidePolygonAgainstMovingPolygon - both, id1, and, id2, are moving.
*/

static void collidePolygonAgainstMovingPolygon (eventQueue e, Object id1, Object id2);

/*
   physicsCollision - handle the physics of a collision between
                      the two objects defined in, e.
*/

static void physicsCollision (eventQueue e);

/*
   doCollision - called whenever a collision event is processed.
*/

static void doCollision (eventQueue e);

/*
   sqr -
*/

static double sqr (double v);

/*
   cub -
*/

static double cub (double v);

/*
   quad -
*/

static double quad (double v);

/*
   pent -
*/

static double pent (double v);

/*
   hex -
*/

static double hex (double v);

/*
   sept -
*/

static double sept (double v);

/*
   oct -
*/

static double oct (double v);

/*
   getCircleValues - assumes, o, is a circle and retrieves:
                     center    (x, y)
                     radius    radius
                     velocity  (vx, vy)
                     accel     (ax, ay)
*/

static void getCircleValues (Object o, double *x, double *y, double *radius, double *vx, double *vy, double *ax, double *ay);

/*
   getObjectValues - fills in velocity and acceleration x, y, values.
*/

static void getObjectValues (Object o, double *vx, double *vy, double *ax, double *ay);

/*
   getObjectOrbitingValues -
*/

static void getObjectOrbitingValues (Object o, double *r, double *w, coord_Coord *cofg);

/*
   maximaCircleCollisionOrbiting -
   x1 y1 x2 y2

   a, g, l, r       is  initial position of the point (not the c of g)
   b, h, m, s       is  initial velocity
   c, i, n, u       is  acceleration
   e, k, p, v       is  angular velocity
   f, q, k, w       is  the initial angular offset for the center of circle relative to the c of g.
                    The c of g is the center of the orbit.
   d,    o          the distance of the point from the c of g.
*/

static void maximaCircleCollisionOrbiting (double *array, unsigned int _array_high, double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double m, double n, double o, double p, double q, double r, double s, double u, double v, double w, double x);

/*
   earlierCircleCollisionOrbiting -

           t          is the time of this collision (if any)
           tc         is the time of the next collision.

           c1p        is the initial position of the center of circle 1.
                      This may not be the c of g of this circle if it is in orbit.
           c1radius   is the radius of the circle.
           c1r        rotational offset of point 1.
           c1cofg     center of gravity of point 1.
           c1w        rotational angular velocity of point 1.
           c1a        acceleration of point 1.

           c2p        is the initial position of the center of circle 2.
                      This may not be the c of g of this circle if it is in orbit.
           c2radius   is the radius of the circle.
           c2r        rotational offset of point 2.
           c2cofg     center of gravity of point 2.
           c2w        rotational angular velocity of point 2.
           c2a        acceleration of point 2.
*/

static unsigned int earlierCircleCollisionOrbiting (double *t, double *tc, coord_Coord c1p, double c1radius, double c1r, double c1w, coord_Coord c1cofg, coord_Coord c1v, coord_Coord c1a, coord_Coord c2p, double c2radius, double c2r, double c2w, coord_Coord c2cofg, coord_Coord c2v, coord_Coord c2a);

/*
   maximaCircleCollision -
*/

static void maximaCircleCollision (double *array, unsigned int _array_high, double a, double b, double c, double d, double e, double f, double g, double h, double k, double l, double m, double n, double o, double p);

/*
   earlierCircleCollision - let the following abreviations be assigned.
                            Note i is one circle, j is another circle.
                                 v is velocity, a, acceleration, x, y axis.
                                 r is radius.

                            Single letter variables are used since wxmaxima
                            only operates with these.  Thus the output from wxmaxima
                            can be cut and pasted into the program.

                            a = xi
                            b = xj
                            c = vxi
                            d = vxj
                            e = aix
                            f = ajx
                            g = yi
                            h = yj
                            k = vyi
                            l = vyj
                            m = aiy
                            n = ajy
                            o = ri
                            p = rj

                            t                       is the time of this collision (if any)
                            bestTimeOfCollision     is earlier known collision so far.
*/

static unsigned int earlierCircleCollision (eventDesc edesc, unsigned int id1, unsigned int id2, double *t, double bestTimeOfCollision, coord_Coord *cp, double a, double b, double c, double d, double e, double f, double g, double h, double k, double l, double m, double n, double o, double p);

/*
   findCollisionCircles -

   using:

   S = UT + (AT^2)/2
   compute xin and yin which are the new (x,y) positions of object i at time, t.
   compute xjn and yjn which are the new (x,y) positions of object j at time, t.
   now compute difference between objects and if they are ri+rj  (radius of circle, i, and, j)
   apart then we have a collision at time, t.

   xin = xi + vxi * t + (aix * t^2) / 2.0
   yin = yi + vyi * t + (aiy * t^2) / 2.0

   xjn = xj + vxj * t + (ajx * t^2) / 2.0
   yjn = yj + vyj * t + (ajy * t^2) / 2.0

   ri + rj == sqrt(abs(xin-xjn)^2 + abs(yin-yjn)^2)     for values of t

   ri + rj == sqrt(((xi + vxi * t + aix * t^2 / 2.0) - (xj + vxj * t + ajx * t^2 / 2.0))^2 +
                   ((yi + vyi * t + aiy * t^2 / 2.0) - (yj + vyj * t + ajy * t^2 / 2.0))^2)

   let:

   a = xi
   b = xj
   c = vxi
   d = vxj
   e = aix
   f = ajx
   g = yi
   h = yj
   k = vyi
   l = vyj
   m = aiy
   n = ajy
   o = ri
   p = rj
   t = t

   o  + p  == sqrt(((a  + c   * t + e   * t^2 / 2.0) - (b  + d   * t +   f * t^2 / 2.0))^2 +
                   ((g  + k   * t + m   * t^2 / 2.0) - (h  + l   * t +   n * t^2 / 2.0))^2)

   o  + p  == sqrt(((a  + c   * t + e   * t^2 / 2.0) - (b  + d   * t +   f * t^2 / 2.0))^2 +
                   ((g  + k   * t + m   * t^2 / 2.0) - (h  + l   * t +   n * t^2 / 2.0))^2)

   0       == ((a  + c   * t + e   * t^2 / 2.0) - (b  + d   * t +   f * t^2 / 2.0))^2 +
              ((g  + k   * t + m   * t^2 / 2.0) - (h  + l   * t +   n * t^2 / 2.0))^2 -
              (o  + p)^2

   now using wxmaxima
   expand ; factor ; ratsimp

   p+o    ==  (sqrt((n^2-2*m*n+m^2+f^2-2*e*f+e^2)*t^4+
                   ((4*l-4*k)*n+(4*k-4*l)*m+(4*d-4*c)*f+(4*c-4*d)*e)*t^3+
                   ((4*h-4*g)*n+(4*g-4*h)*m+4*l^2-8*k*l+4*k^2+(4*b-4*a)*f+(4*a-4*b)*e+4*d^2-8*c*d+4*c^2)*t^2+
                   ((8*h-8*g)*l+(8*g-8*h)*k+(8*b-8*a)*d+(8*a-8*b)*c)*t+4*h^2-8*g*h+4*g^2+4*b^2-8*a*b+4*a^2))/2

   2*(p+o) ==  (sqrt((n^2-2*m*n+m^2+f^2-2*e*f+e^2)*t^4+
                    ((4*l-4*k)*n+(4*k-4*l)*m+(4*d-4*c)*f+(4*c-4*d)*e)*t^3+
                    ((4*h-4*g)*n+(4*g-4*h)*m+4*l^2-8*k*l+4*k^2+(4*b-4*a)*f+(4*a-4*b)*e+4*d^2-8*c*d+4*c^2)*t^2+
                    ((8*h-8*g)*l+(8*g-8*h)*k+(8*b-8*a)*d+(8*a-8*b)*c)*t+4*h^2-8*g*h+4*g^2+4*b^2-8*a*b+4*a^2))

   (2*(p+o))^2 == ((n^2-2*m*n+m^2+f^2-2*e*f+e^2)*t^4+
                   ((4*l-4*k)*n+(4*k-4*l)*m+(4*d-4*c)*f+(4*c-4*d)*e)*t^3+
                   ((4*h-4*g)*n+(4*g-4*h)*m+4*l^2-8*k*l+4*k^2+(4*b-4*a)*f+(4*a-4*b)*e+4*d^2-8*c*d+4*c^2)*t^2+
                   ((8*h-8*g)*l+(8*g-8*h)*k+(8*b-8*a)*d+(8*a-8*b)*c)*t+4*h^2-8*g*h+4*g^2+4*b^2-8*a*b+4*a^2))

   0           ==  (n^2-2*m*n+m^2+f^2-2*e*f+e^2)*t^4+
                   ((4*l-4*k)*n+(4*k-4*l)*m+(4*d-4*c)*f+(4*c-4*d)*e)*t^3+
                   ((4*h-4*g)*n+(4*g-4*h)*m+4*l^2-8*k*l+4*k^2+(4*b-4*a)*f+(4*a-4*b)*e+4*d^2-8*c*d+4*c^2)*t^2+
                   ((8*h-8*g)*l+(8*g-8*h)*k+(8*b-8*a)*d+(8*a-8*b)*c)*t+
                   4*h^2-8*g*h+4*g^2+4*b^2-8*a*b+4*a^2)-
                   ((2*(p+o))^2)

   solve polynomial:

   A := sqr(n)-2.0*m*n+sqr(m)+sqr(f)-2.0*e*f+sqr(e) ;
   B := (4.0*l-4.0*k)*n+(4.0*k-4.0*l)*m+(4.0*d-4.0*c)*f+(4.0*c-4.0*d)*e ;
   C := (4.0*h-4.0*g)*n+(4.0*g-4.0*h)*m+4.0*sqr(l)-8.0*k*l+4.0*sqr(k)+(4.0*b-4.0*a)*f+(4.0*a-4.0*b)*e+4.0*sqr(d)-8.0*c*d+4.0*sqr(c) ;
   D := (8.0*h-8.0*g)*l+(8.0*g-8.0*h)*k+(8.0*b-8.0*a)*d+(8.0*a-8.0*b)*c ;
   E := 4.0*sqr(h)-8.0*g*h+4.0*sqr(g)+4.0*sqr(b)-8.0*a*b+4.0*sqr(a)-sqr(2.0*(p+o)) ;
*/

static void findCollisionCircles (Object iptr, Object jptr, eventDesc *edesc, double *tc);

/*
   stop -
*/

static void stop (void);

/*
   makeCirclesPolygonDesc - returns an eventDesc describing the collision between a circle and a polygon.
*/

static eventDesc makeCirclesPolygonDesc (eventDesc edesc, unsigned int cid, unsigned int pid, unsigned int lineNo, unsigned int pointNo, history_whereHit wpid1, history_whereHit wpid2, coord_Coord collisionPoint);

/*
   checkIfPointHits - return TRUE if t0 is either the first hit found or
                      is sooner than, tc.  It determines a hit by working out
                      the final position of partical:

                      x = s + ut + 1/2a t^2

                      if x>=0.0 and x <= length then it hits.
*/

static unsigned int checkIfPointHits (double timeOfPrevCollision, double t, double length, double s, double u, double a);

/*
   newPositionScalar - calculates the new position of a scalar in the future.
*/

static double newPositionScalar (double s, double u, double a, double t);

/*
   newPositionRotationSinScalar - works out the new Y position for a point whose:

                                  current cofg Y position is:   c
                                  initial Y velocity is     :   u
                                  Y acceleration is         :   a
                                  angular velocity          :   w
                                  orientation               :   o
                                  polar coord position rel
                                  to cofg is                :   p
*/

static double newPositionRotationSinScalar (double c, double u, double a, double t, double w, double o, polar_Polar p);

/*
   newPositionRotationCosScalar - works out the new X position for a point whose:

                                  current cofg X position is:   c
                                  initial X velocity is     :   u
                                  X acceleration is         :   a
                                  angular velocity          :   w
                                  orientation               :   o
                                  polar coord position rel
                                  to cofg is                :   p
*/

static double newPositionRotationCosScalar (double c, double u, double a, double t, double w, double o, polar_Polar p);

/*
   newPositionCoord - calculates the new position of point in the future.
*/

static coord_Coord newPositionCoord (coord_Coord c, coord_Coord u, coord_Coord a, double t);

/*
   newPositionRotationCoord - calculates the new position of point, c+v, in the future.
                              Given angular velocity         : w
                                    orientation              : o
                                    time                     : t
                                    initial vel              : u
                                    accel                    : a
                                    c of g                   : c
                                    polar coord of the point : p
*/

static coord_Coord newPositionRotationCoord (coord_Coord c, coord_Coord u, coord_Coord a, double t, double w, double o, polar_Polar p);

/*
   hLine - debugging procedure to display a line on a half scale axis.
*/

static void hLine (coord_Coord p1, coord_Coord p2, deviceIf_Colour c);

/*
   hPoint - debugging procedure to display a line on a half scale axis.
*/

static void hPoint (coord_Coord p, deviceIf_Colour c);

/*
   hCircle - debugging procedure to display a circle on a half scale axis.
*/

static void hCircle (coord_Coord p, double r, deviceIf_Colour c);

/*
   hVec - display a normalised vector on a half scale axis
*/

static void hVec (coord_Coord p, deviceIf_Colour c);

/*
   hFlush - flip the debugging buffer.
*/

static void hFlush (void);

/*
   checkPointCollision -
*/

static unsigned int checkPointCollision (double *timeOfPrevCollision, double t, double length, double cx, double rvx, double rax, coord_Coord c, coord_Coord cvel, coord_Coord caccel, coord_Coord *collisionPoint, unsigned int id1, unsigned int id2);

/*
   earlierPointLineCollision - returns TRUE if we can find a collision between a point, c,
                               travelling at cvel with acceleration, caccel and a line
                               p1, p2, travelling at velocity, lvel, and acceleration laccel.
                               If a collision is found then the collisionPoint is also
                               calculated.
*/

static unsigned int earlierPointLineCollision (double *timeOfCollision, coord_Coord c, coord_Coord cvel, coord_Coord caccel, coord_Coord p1, coord_Coord p2, coord_Coord lvel, coord_Coord laccel, coord_Coord *collisionPoint, unsigned int id1, unsigned int id2);

/*
   sortLine - orders points, p1 and, p2, according to their x value.
*/

static void sortLine (coord_Coord *p1, coord_Coord *p2);
static void findEarlierCircleEdgeCollision (double *timeOfCollision, unsigned int cid, unsigned int pid, unsigned int lineP, unsigned int lineC, eventDesc *edesc, coord_Coord center, double radius, coord_Coord velCircle, coord_Coord accelCircle, coord_Coord p1, coord_Coord p2, coord_Coord velLine, coord_Coord accelLine, descP createDesc);

/*
   getPolygonCoord -
*/

static coord_Coord getPolygonCoord (Object pPtr, unsigned int pointno);

/*
   getPolygonLine - assigns, p1, p2, with the, line, coordinates of polygon, pPtr.
*/

static void getPolygonLine (unsigned int line, Object pPtr, coord_Coord *c1, coord_Coord *c2);

/*
   findCollisionCircleLine - find the time (if any) between line number, lineP, in polygon, pPtr,
                             and the circle, cPtr.  cPtr can also be a polygon in which case lineC
                             is the particular line under question.  Line on line collision is broken
                             down into circle line calls which allows for code reuse.

                             Neither cPtr or pPtr are orbiting.
*/

static void findCollisionCircleLine (Object cPtr, Object pPtr, unsigned int lineP, unsigned int lineC, coord_Coord center, double radius, eventDesc *edesc, double *timeOfCollision, descP createDesc);

/*
   findCollisionCircleLineOrbiting - find the time (if any) between line number, lineP, in polygon, pPtr,
                                     and the circle, cPtr.  cPtr can also be a polygon in which case lineC
                                     is the particular line under question.  Line on line collision is broken
                                     down into circle line calls which allows for code reuse.

                                     Either cPtr or pPtr or both are orbiting.
*/

static void findCollisionCircleLineOrbiting (Object cPtr, Object pPtr, unsigned int lineP, unsigned int lineC, coord_Coord center, double radius, eventDesc *edesc, double *timeOfCollision, descP createDesc);

/*
   findCollisionCirclePolygon - find the smallest positive time (if any) between the polygon and circle.
                                If a collision if found then, tc, is assigned to the time and cid, pid
                                are set to the circle id and polygon id respectively.
*/

static void findCollisionCirclePolygon (Object cPtr, Object pPtr, eventDesc *edesc, double *tc);

/*
   makePolygonPolygonDesc - return a new eventDesc indicating that we have a polygon/polygon collision
                            event.
*/

static eventDesc makePolygonPolygon (eventDesc edesc, unsigned int id1, unsigned int id2, unsigned int lineCorner1, unsigned int lineCorner2, history_whereHit wpid1, history_whereHit wpid2, coord_Coord collisionPoint);

/*
   isOrbiting - return TRUE if object, o, is rotating.
*/

static unsigned int isOrbiting (Object o);

/*
   findCollisionLineLine - find the smallest time in the future when two lines collide.
                           The event descriptor, edesc, will contain the description of the collision
                           and, tc, the time of collision in the future.
*/

static void findCollisionLineLine (Object iPtr, Object jPtr, unsigned int iLine, unsigned int jLine, eventDesc *edesc, double *tc);

/*
   findCollisionLineLine - find the smallest time in the future when two lines collide.
                           The event descriptor, edesc, will contain the description of the collision
                           and, tc, the time of collision in the future.
*/

static void findCollisionLineLineOrbiting (Object iPtr, Object jPtr, unsigned int iLine, unsigned int jLine, eventDesc *edesc, double *tc);
static void findCollisionLineLineNonOrbiting (Object iPtr, Object jPtr, unsigned int iLine, unsigned int jLine, eventDesc *edesc, double *tc);

/*
   Abs - return the absolute value of, r.
*/

static double Abs (double r);

/*
   findAllTimesOfCollisionRLineRPoint -
                                                       4         4   4
                                             - ((16 j k  - 16 d e ) t

                                                       3               3         3               3   3
                                              + (64 j k  l - 32 %pi j k  - 64 d e  f + 32 %pi d e ) t

                                                       2  2             2            2          2                2  2
                                              + (96 j k  l  - 96 %pi j k  l + (24 %pi  - 32) j k  + 32 i - 96 d e  f

                                                          2                 2     2          2
                                              + 96 %pi d e  f + (32 - 24 %pi ) d e  - 32 c) t

                                                         3               2          2                              3
                                              + (64 j k l  - 96 %pi j k l  + (48 %pi  - 64) j k l + (32 %pi - 8 %pi ) j k

                                                               3               2               2
                                              + 64 h - 64 d e f  + 96 %pi d e f  + (64 - 48 %pi ) d e f

                                                      3                                 4             3
                                              + (8 %pi  - 32 %pi) d e - 64 b) t + 16 j l  - 32 %pi j l

                                                       2          2                  3            4        2
                                              + (24 %pi  - 32) j l  + (32 %pi - 8 %pi ) j l + (%pi  - 8 %pi  + 64) j + 64 g

                                                      4             3               2     2         3
                                              - 16 d f  + 32 %pi d f  + (32 - 24 %pi ) d f  + (8 %pi  - 32 %pi) d f

                                                      4        2
                                              + (- %pi  + 8 %pi  - 64) d - 64 a)/64 = 0
*/

static unsigned int findAllTimesOfCollisionRLineRPoint (double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double *t, unsigned int _t_high);

/*
   findEarliestCollisionRLineRPoint - find the earliest time when rotating point, j, collides with rotating line, i.
*/

static void findEarliestCollisionRLineRPoint (Object iPtr, Object jPtr, unsigned int i, unsigned int j, eventDesc *edesc, double *tc, double si, double ui, double ai, double ri, double wi, double oi, double sj, double uj, double aj, double rj, double wj, double oj, coord_Coord p1, coord_Coord p2);

/*
   findCollisionLineRPoint -
*/

static void findCollisionLineRPoint (Object iPtr, Object rPtr, unsigned int i, unsigned int j, eventDesc *edesc, double *tc);

/*
   findCollisionLineRLine - find the time of collision between line, iPtr, and rotating line, rPtr.
*/

static void findCollisionLineRLine (Object iPtr, Object rPtr, unsigned int i, unsigned int j, eventDesc *edesc, double *tc);

/*
   findCollisionPolygonPolygon - find the smallest positive time (if any) between the polygons, iPtr
                                 and jPtr colliding.
                                 If a collision if found then, tc, is assigned to the time and the
                                 event descriptor is filled in.
*/

static void findCollisionPolygonPolygon (Object iPtr, Object jPtr, eventDesc *edesc, double *tc);

/*
   findCollisionPolygonRPolygon - find the smallest positive time (if any) between the polygons, iPtr
                                  and rPtr colliding.
                                  rPtr is a rotating polygon and iPtr is not rotating.
                                  If a collision if found then, tc, is assigned to the time and the
                                  event descriptor is filled in.
                                  We check possible collision times between all lines of both polygons,
                                  we separate out the rotating polygon from non rotating polygon
                                  as the collision equations only generate a polynomial order 4 rather
                                  than order 8 if both are rotating.
*/

static void findCollisionPolygonRPolygon (Object iPtr, Object rPtr, eventDesc *edesc, double *tc);

/*
   findCollision -
*/

static void findCollision (Object iptr, Object jptr, eventDesc *edesc, double *tc);

/*
   debugFrame - debug frame at time, e.
*/

static void debugFrame (eventQueue e);

/*
   addDebugging - add a debugging event at time, t.
*/

static void addDebugging (double t, eventDesc edesc);

/*
   anticipateCollision - stores the collision in the anticipated list.
*/

static void anticipateCollision (double tc, eventDesc edesc);

/*
   collisionOccurred - stores the collision in the history list.
*/

static void collisionOccurred (eventDesc edesc);

/*
   subEvent - remove event, e, from the relative time ordered event queue.
*/

static void subEvent (eventQueue e);

/*
   removeCollisionEvent -
*/

static void removeCollisionEvent (void);

/*
   addNextCollisionEvent -
*/

static void addNextCollisionEvent (void);

/*
   skipFor - skip displaying any frames for, t, simulated seconds.
*/

static void skipFor (double t);

/*
   resetQueue -
*/

static void resetQueue (void);

/*
   disposeEvent - returns the event to the free queue.
*/

static void disposeEvent (eventQueue e);

/*
   disposeDesc - returns the event desc to the free queue.
*/

static void disposeDesc (eventDesc *d);

/*
   newDesc - returns a new eventDesc.
*/

static eventDesc newDesc (void);

/*
   newEvent - returns a new eventQueue.
*/

static eventQueue newEvent (void);

/*
   makeCirclesDesc - return a eventDesc which describes two circles colliding.
*/

static eventDesc makeCirclesDesc (eventDesc *edesc, unsigned int cid1, unsigned int cid2, coord_Coord cp);

/*
   addRelative - adds event, e, into the relative event queue.
*/

static void addRelative (eventQueue e);

/*
   addEvent - adds an event which has no collision associated with it.
              Typically this is a debugging event or display frame event.
*/

static void addEvent (eventKind k, double t, eventProc dop);

/*
   addCollisionEvent - adds a collision event, the edesc is attached to the,
                       eventQueue, which is placed onto the eventQ.
*/

static void addCollisionEvent (double t, eventProc dop, eventDesc edesc);

/*
   isEvent - return TRUE if the next event is of kind, k.
*/

static unsigned int isEvent (eventKind k);

/*
   dumpTime -
*/

static void dumpTime (void);

/*
   recordEvent -
*/

static void recordEvent (void);

/*
   pumpQueue - prime the event queue with initial frame and collision events.
*/

static void pumpQueue (void);

/*
   up - recreate the event queue.
        The pair up/down must be used to shutdown
        the event queue if the world is to be altered.
*/

static void up (void);

/*
   down - shutdown the event queue.
*/

static void down (void);

/*
   killQueue - destroys the event queue and returns events to the free list.
*/

static void killQueue (void);

/*
   writeCircles -
*/

static void writeCircles (cDesc c);

/*
   writeKind -
*/

static void writeKind (history_whereHit k);

/*
   writeCirclePolygon -
*/

static void writeCirclePolygon (cpDesc c);

/*
   writePolygonPolygon -
*/

static void writePolygonPolygon (ppDesc p);

/*
   writeFunction -
*/

static void writeFunction (fcDesc fc);

/*
   writeDesc -
*/

static void writeDesc (eventDesc p);

/*
   writeEvent - writes the first event to the file.
*/

static void writeEvent (eventQueue e);

/*
   memDump -
*/

static void memDump (void * a, unsigned int len);

/*
   checkOpened - checks to see of the MemStream file has been created and if not then
                 it is opened.
*/

static void checkOpened (void);

/*
   Init -
*/

static void Init (void);


/*
   Assert -
*/

static void Assert (unsigned int b, unsigned int line)
{
  if (! b)
    {
      libc_printf ((char *) "twoDsim.mod:%d:error assert failed\\n", 36, line);
      M2RTS_HALT (0);
    }
}


/*
   AssertR -
*/

static void AssertR (double a, double b)
{
  if (! (roots_nearZero (a-b)))
    libc_printf ((char *) "error assert failed: %g should equal %g difference is %g\\n", 58, a, b, a-b);
}


/*
   AssertRDebug -
*/

static void AssertRDebug (double a, double b, char *message_, unsigned int _message_high)
{
  typedef struct _T5_a _T5;

  struct _T5_a { char array[10+1]; };
  _T5 copy;
  char message[_message_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (message, message_, _message_high+1);

  if (! (roots_nearZero (a-b)))
    {
      StrLib_StrCopy ((char *) message, _message_high, (char *) &copy.array[0], 10);
      libc_printf ((char *) "%s failed  %g should equal %g difference is %g\\n", 48, &copy, a, b, a-b);
    }
}


/*
   dumpCircle -
*/

static void dumpCircle (Object o)
{
  libc_printf ((char *) "circle at (%g, %g) radius %g mass %g colour %d\\n", 48, o->c.pos.x, o->c.pos.y, o->c.r, o->c.mass, o->c.col);
}


/*
   dumpPolygon -
*/

static void dumpPolygon (Object o)
{
  unsigned int i;
  coord_Coord c0;

  libc_printf ((char *) "polygon mass %g colour %d\\n", 27, o->p.mass, o->p.col);
  libc_printf ((char *) "  c of g  (%g,%g)\\n", 19, o->p.cOfG.x, o->p.cOfG.y);
  for (i=0; i<=o->p.nPoints-1; i++)
    {
      c0 = coord_addCoord (o->p.cOfG, polar_polarToCoord (polar_rotatePolar ((polar_Polar) o->p.points.array[i], o->angleOrientation)));
      libc_printf ((char *) "  point at (%g,%g)\\n", 20, c0.x, c0.y);
    }
}


/*
   checkDeleted -
*/

static void checkDeleted (Object o)
{
  if (o->deleted)
    libc_printf ((char *) "object %d has been deleted, should not be accessing it now\\n", 60, o->id);
}


/*
   DumpObject -
*/

static void DumpObject (Object o)
{
  libc_printf ((char *) "object %d ", 10, o->id);
  if (o->deleted)
    {
      libc_printf ((char *) "is deleted\\n", 12);
      return;
    }
  else if (o->fixed)
    libc_printf ((char *) "is fixed ", 9);
  else
    {
      libc_printf ((char *) "is movable ", 11);
      if (o->stationary)
        libc_printf ((char *) "but is now stationary ", 22);
      else if (! (roots_nearZero (o->angularVelocity)))
        libc_printf ((char *) " and has a rotating velocity of %g\\n", 36, o->angularVelocity);
      else if (! (roots_nearZero (o->angleOrientation)))
        libc_printf ((char *) " and its current orientation is %g\\n", 36, o->angleOrientation);
    }
  switch (o->object)
    {
      case circleOb:
        dumpCircle (o);
        break;

      case polygonOb:
        dumpPolygon (o);
        break;

      case springOb:
        libc_printf ((char *) "spring\\n", 8);
        break;


      default:
        break;
    }
  if (! o->fixed && ! o->stationary)
    libc_printf ((char *) "    velocity (%g, %g) acceleration (%g, %g)\\n", 45, o->vx, o->vy, o->ax, o->ay);
}


/*
   c2p - returns a Point given a Coord.
*/

static Points_Point c2p (coord_Coord c)
{
  return Points_initPoint (Fractions_putReal (c.x), Fractions_putReal (c.y));
}


/*
   newObject - creates an object of, type, and returns its, id.
*/

static unsigned int newObject (ObjectType type)
{
  Object optr;

  maxId += 1;
  Storage_ALLOCATE ((void **) &optr, sizeof (_T2));
  optr->id = maxId;
  optr->deleted = FALSE;
  optr->fixed = FALSE;
  optr->stationary = FALSE;
  optr->object = type;
  optr->vx = 0.0;
  optr->vy = 0.0;
  optr->ax = 0.0;
  optr->ay = 0.0;
  optr->angularVelocity = 0.0;
  optr->angularMomentum = 0.0;
  optr->angleOrientation = 0.0;
  optr->inertia = 0.0;
  optr->interpen = 0;
  Indexing_PutIndice (objects, maxId, (void *) optr);
  return maxId;
}


/*
   circle_moving_towards - return TRUE if object, optr, is moving towards
                           point, x, y.  The object may still miss point x, y
                           but it is moving closer to this position.
*/

static unsigned int circle_moving_towards (Object optr, double x, double y)
{
  double contactVel;
  coord_Coord relativePosition;
  coord_Coord relativeVelocity;

  relativePosition = coord_initCoord (optr->c.pos.x-x, optr->c.pos.y-y);
  relativeVelocity = coord_initCoord (optr->vx, optr->vy);
  contactVel = coord_dotProd (relativeVelocity, relativePosition);
  return contactVel < 0.0;
}


/*
   apply_impulse_to_circle - apply an impulse to moving circle, movable,
                             along the vector [x, y] with magnitude, m.
*/

static void apply_impulse_to_circle (Object movable, double x, double y, double m)
{
  double contactVel;
  double theta;
  double r;
  double j;
  coord_Coord c;
  coord_Coord impulsePos;
  coord_Coord unitCollision;
  coord_Coord relativeVelocity;

  impulsePos.x = movable->c.pos.x;
  impulsePos.y = movable->c.pos.y;
  if (roots_nearZero (x))
    if (y > 0.0)
      impulsePos.y = impulsePos.y+movable->c.r;
    else
      impulsePos.y = impulsePos.y-movable->c.r;
  else if (roots_nearZero (y))
    if (x > 0.0)
      impulsePos.x = impulsePos.x+movable->c.r;
    else
      impulsePos.x = impulsePos.x-movable->c.r;
  else
    if ((x > 0.0) && (y > 0.0))
      {
        theta = libm_atan (y/x);
        impulsePos.x = impulsePos.x+((libm_cos (theta))*movable->c.r);
        impulsePos.y = impulsePos.y+((libm_sin (theta))*movable->c.r);
      }
    else if ((x < 0.0) && (y < 0.0))
      {
        x = -x;
        y = -y;
        theta = libm_atan (y/x);
        impulsePos.x = impulsePos.x-((libm_cos (theta))*movable->c.r);
        impulsePos.y = impulsePos.y-((libm_sin (theta))*movable->c.r);
      }
    else if ((x > 0.0) && (y < 0.0))
      {
        y = -y;
        theta = libm_atan (y/x);
        impulsePos.x = impulsePos.x+((libm_cos (theta))*movable->c.r);
        impulsePos.y = impulsePos.y-((libm_sin (theta))*movable->c.r);
      }
    else
      {
        x = -x;
        theta = libm_atan (y/x);
        impulsePos.x = impulsePos.x-((libm_cos (theta))*movable->c.r);
        impulsePos.y = impulsePos.y+((libm_sin (theta))*movable->c.r);
      }
  c = coord_initCoord (movable->c.pos.x-impulsePos.x, movable->c.pos.y-impulsePos.y);
  r = libm_sqrt ((c.x*c.x)+(c.y*c.y));
  unitCollision = coord_initCoord (c.x/r, c.y/r);
  relativeVelocity = coord_initCoord (movable->vx, movable->vy);
  contactVel = coord_dotProd (relativeVelocity, c);
  if (contactVel < 0.0)
    {
      j = (-((1.0+1.0)*((relativeVelocity.x*unitCollision.x)+(relativeVelocity.y*unitCollision.y))))/(((unitCollision.x*unitCollision.x)+(unitCollision.y*unitCollision.y))*(1.0/movable->c.mass));
      movable->vx = movable->vx+((j*unitCollision.x)/movable->c.mass);
      movable->vy = movable->vy+((j*unitCollision.y)/movable->c.mass);
    }
  checkStationary (movable);
}


/*
   objectExists -
*/

static unsigned int objectExists (Object o)
{
  return (o != NULL) && ! o->deleted;
}


/*
   doCheckInterpenCircleCircle -
*/

static unsigned int doCheckInterpenCircleCircle (Object fixed, Object movable)
{
  coord_Coord d;
  coord_Coord v;
  double h1;
  double h0;

  d = coord_subCoord (movable->c.pos, fixed->c.pos);
  h0 = fixed->c.r+movable->c.r;
  h1 = libm_sqrt ((d.x*d.x)+(d.y*d.y));
  if (h0 > h1)
    {
      if (trace)
        libc_printf ((char *) "interpen found two moving circles interpenetrating %d, %d   h0 = %g, h1 = %g\\n", 78, fixed->id, movable->id, h0, h1);
      v = coord_scaleCoord (coord_normaliseCoord (d), h0);
      movable->c.pos = coord_addCoord (fixed->c.pos, v);
      movable->vx = movable->vx+((v.x*(h0-h1))/h0);
      movable->vy = movable->vy+((v.y*(h0-h1))/h0);
      movable->interpen += 1;
      return movable->interpen;
    }
  return 0;
}


/*
   doCheckInterpenCircleCircleMoving -
*/

static unsigned int doCheckInterpenCircleCircleMoving (Object c1, Object c2)
{
  coord_Coord d;
  coord_Coord v;
  double h1;
  double h0;

  d = coord_subCoord (c2->c.pos, c1->c.pos);
  h0 = c1->c.r+c2->c.r;
  h1 = libm_sqrt ((d.x*d.x)+(d.y*d.y));
  if (h0 > h1)
    {
      if (trace)
        libc_printf ((char *) "interpen found two moving circles interpenetrating %d, %d   h0 = %g, h1 = %g\\n", 78, c1->id, c2->id, h0, h1);
      v = coord_scaleCoord (coord_normaliseCoord (d), h0);
      c2->c.pos = coord_addCoord (c1->c.pos, v);
      c2->vx = c2->vx+((v.x*(h0-h1))/h0);
      c2->vy = c2->vy+((v.y*(h0-h1))/h0);
      c2->interpen += 1;
      return c2->interpen;
    }
  return 0;
}


/*
   distanceLinePoint - c is a point.  p1->p2 is the line in question.
                       p3 is assigned to the closest point on the line
                       to the point, c.  d is the distance from c to p3.
                       TRUE is returned if the point, c, lies above or
                       below the line once the line is rotated onto the x
                       axis.  (The point, c, would also rotated to solve
                       this question).
*/

static unsigned int distanceLinePoint (coord_Coord c, coord_Coord p1, coord_Coord p2, coord_Coord *p3, double *d)
{
  double A;
  double B;
  double C;
  double D;
  double dot;
  double lengthSq;
  double normalised;

  A = c.x-p1.x;
  B = c.y-p1.y;
  C = p2.x-p1.x;
  D = p2.y-p1.y;
  dot = (A*C)+(B*D);
  lengthSq = (sqr (C))+(sqr (D));
  normalised = -1.0;
  if (! (roots_nearZero (lengthSq)))
    normalised = dot/lengthSq;
  if (normalised < 0.0)
    {
      (*p3) = p1;
      return FALSE;
    }
  else if (normalised > 1.0)
    {
      (*p3) = p2;
      return FALSE;
    }
  (*p3) = checkZeroCoord (coord_initCoord (p1.x+(normalised*C), p1.y+(normalised*D)));
  (*d) = coord_lengthCoord (coord_subCoord (c, (*p3)));
  return TRUE;
}


/*
   checkLimits -
*/

static coord_Coord checkLimits (coord_Coord c, double r)
{
  if ((c.x-r) < 0.0)
    c.x = r;
  else if ((c.x+r) > 1.0)
    c.x = 1.0-r;
  if ((c.y-r) < 0.0)
    c.y = r;
  else if ((c.y+r) > 1.0)
    c.y = 1.0-r;
  return c;
}


/*
   doCheckInterpenCirclePolygon -
*/

static unsigned int doCheckInterpenCirclePolygon (Object iptr, Object jptr)
{
  double d;
  double r;
  unsigned int i;
  unsigned int n;
  coord_Coord v;
  coord_Coord c;
  coord_Coord p1;
  coord_Coord p2;
  coord_Coord p3;

  Assert (iptr->object == circleOb, 1116);
  Assert (jptr->object == polygonOb, 1117);
  c = checkZeroCoord (iptr->c.pos);
  r = iptr->c.r;
  n = jptr->p.nPoints;
  i = 1;
  while (i <= n)
    {
      getPolygonLine (i, jptr, &p1, &p2);
      if (((distanceLinePoint (c, p1, p2, &p3, &d)) && (! (roots_nearZero (r-d)))) && (r > d))
        if (! iptr->fixed)
          {
            if (roots_nearZero (d))
              libc_printf ((char *) "distance is nearzero, seen collision between circle and line, new position %g, %g\\n", 83, iptr->c.pos.x, iptr->c.pos.y);
            else
              {
                v = coord_subCoord (c, p3);
                v = checkZeroCoord (coord_scaleCoord (v, r/d));
                iptr->c.pos = checkZeroCoord (coord_addCoord (p3, v));
                checkStationary (iptr);
              }
            iptr->c.pos = checkLimits (iptr->c.pos, r);
            iptr->interpen += 1;
            return iptr->interpen;
          }
      i += 1;
    }
  iptr->c.pos = checkLimits (iptr->c.pos, r);
  return 0;
}


/*
   doCheckInterpenPolygon -
*/

static unsigned int doCheckInterpenPolygon (Object iptr, Object jptr)
{
  if ((iptr->object == circleOb) && (jptr->object == polygonOb))
    return doCheckInterpenCirclePolygon (iptr, jptr);
  else if ((iptr->object == polygonOb) && (jptr->object == circleOb))
    return doCheckInterpenCirclePolygon (jptr, iptr);
  return 0;
}


/*
   doCheckInterpenCircle -
*/

static unsigned int doCheckInterpenCircle (Object iptr, Object jptr)
{
  if ((iptr->object == circleOb) && (jptr->object == circleOb))
    {
      /* avoid gcc warning by using compound statement even if not strictly necessary.  */
      if (iptr->fixed && ! jptr->fixed)
        return doCheckInterpenCircleCircle (iptr, jptr);
      else if (! iptr->fixed && jptr->fixed)
        return doCheckInterpenCircleCircle (jptr, iptr);
      else
        return doCheckInterpenCircleCircleMoving (iptr, jptr);
    }
  return 0;
}


/*
   initInterpen -
*/

static void initInterpen (void)
{
  unsigned int n;
  unsigned int i;
  Object iptr;

  n = Indexing_HighIndice (objects);
  i = 1;
  while (i <= n)
    {
      iptr = Indexing_GetIndice (objects, i);
      if (objectExists (iptr))
        iptr->interpen = 0;
      i += 1;
    }
}


/*
   max - return the maximum of a and b.
*/

static unsigned int max (unsigned int a, unsigned int b)
{
  if (a > b)
    return a;
  else
    return b;
}


/*
   checkInterpenCircle -
*/

static void checkInterpenCircle (void)
{
  unsigned int n;
  unsigned int i;
  unsigned int j;
  unsigned int c;
  Object iptr;
  Object jptr;

  initInterpen ();
  n = Indexing_HighIndice (objects);
  do {
    c = 0;
    i = 1;
    while (i <= n)
      {
        iptr = Indexing_GetIndice (objects, i);
        if (objectExists (iptr))
          {
            j = i+1;
            while (j <= n)
              {
                jptr = Indexing_GetIndice (objects, j);
                if (objectExists (jptr))
                  c = max (doCheckInterpenCircle (iptr, jptr), c);
                j += 1;
              }
          }
        i += 1;
      }
  } while (! ((c >= n) || (c == 0)));
}


/*
   checkInterpenPolygon -
*/

static void checkInterpenPolygon (void)
{
  unsigned int n;
  unsigned int i;
  unsigned int j;
  unsigned int c;
  Object iptr;
  Object jptr;

  initInterpen ();
  n = Indexing_HighIndice (objects);
  do {
    c = 0;
    i = 1;
    while (i <= n)
      {
        iptr = Indexing_GetIndice (objects, i);
        if (objectExists (iptr))
          {
            j = i+1;
            while (j <= n)
              {
                jptr = Indexing_GetIndice (objects, j);
                if (objectExists (jptr))
                  c = max (doCheckInterpenPolygon (iptr, jptr), c);
                j += 1;
              }
          }
        i += 1;
      }
  } while (! ((c >= n) || (c == 0)));
}


/*
   checkInterpen -
*/

static void checkInterpen (void)
{
  checkInterpenPolygon ();
  checkInterpenCircle ();
}


/*
   resetStationary -
*/

static void resetStationary (void)
{
  unsigned int n;
  unsigned int i;
  Object iptr;

  n = Indexing_HighIndice (objects);
  i = 1;
  while (i <= n)
    {
      iptr = Indexing_GetIndice (objects, i);
      if (objectExists (iptr))
        if (iptr->stationary)
          {
            iptr->vx = 0.0;
            iptr->vy = 0.0;
            iptr->stationary = FALSE;
          }
      i += 1;
    }
}


/*
   spring - join object, id1, and, id2, with a string of defined
            by hooks constant, k.
*/

static unsigned int spring (unsigned int id1, unsigned int id2, double k)
{
  unsigned int id;
  Object optr;

  id = newObject ((ObjectType) springOb);
  optr = Indexing_GetIndice (objects, id);
  optr->s.k = k;
  optr->s.id1 = id1;
  optr->s.id2 = id2;
  return id;
}


/*
   calculateCofG -
*/

static coord_Coord calculateCofG (unsigned int n, coord_Coord *p_, unsigned int _p_high)
{
  double A;
  double B;
  double C;
  double D;
  double a;
  double x;
  double y;
  unsigned int i;
  unsigned int j;
  coord_Coord p[_p_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (p, p_, (_p_high+1) * sizeof (coord_Coord));

  a = (calcArea (n, (coord_Coord *) p, _p_high))*6.0;
  x = 0.0;
  y = 0.0;
  if (Debugging)
    {
      libc_printf ((char *) "calculateCofG begin:  %d points\\n", 33, n);
      for (i=0; i<=n-1; i++)
        libc_printf ((char *) "%d:   %g, %g\\n", 14, i, p[i].x, p[i].y);
    }
  for (i=0; i<=n-1; i++)
    {
      j = (i+1) % n;
      if (Debugging)
        {
          libc_printf ((char *) "x = %g,  y = %g\\n", 17, x, y);
          A = p[i].x+p[j].x;
          B = (p[i].x*p[j].y)-(p[j].x*p[i].y);
          C = p[i].y+p[j].y;
          D = (p[i].x*p[j].y)-(p[j].x*p[i].y);
          libc_printf ((char *) "A = %g,  B = %g\\n", 17, A, B);
          libc_printf ((char *) "C = %g,  D = %g\\n", 17, A, B);
          libc_printf ((char *) "A * B = %g,  C * D = %g\\n", 25, A*B, C*D);
        }
      x = x+((p[i].x+p[j].x)*((p[i].x*p[j].y)-(p[j].x*p[i].y)));
      y = y+((p[i].y+p[j].y)*((p[i].x*p[j].y)-(p[j].x*p[i].y)));
    }
  if (Debugging)
    libc_printf ((char *) "cofg = %g, %g\\n", 15, x/a, y/a);
  return coord_initCoord (x/a, y/a);
}


/*
   calcArea -
*/

static double calcArea (unsigned int n, coord_Coord *p_, unsigned int _p_high)
{
  unsigned int i;
  unsigned int j;
  double a;
  double r;
  double b;
  coord_Coord p[_p_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (p, p_, (_p_high+1) * sizeof (coord_Coord));

  a = 0.0;
  if (Debugging)
    libc_printf ((char *) "calculating area: ", 18);
  for (i=0; i<=n-1; i++)
    {
      if (Debugging)
        libc_printf ((char *) "(%g, %g) ", 9, p[i].x, p[i].y);
      j = (i+1) % n;
      r = p[i].x*p[j].y;
      b = p[i].y*p[j].x;
      if (Debugging)
        {
          libc_printf ((char *) " [x1 x y1 = %g x %g = %g = r] ", 30, p[i].x, p[j].y, r);
          libc_printf ((char *) " [x1 x y1 = %g x %g = %g = b] ", 30, p[i].y, p[j].x, b);
        }
      a = (a+r)-b;
      if (Debugging)
        libc_printf ((char *) " [a = %g] ", 10, a);
    }
  if (Debugging)
    libc_printf ((char *) "end area = %g\\n", 15, a/2.0);
  return a/2.0;
}


/*
   debugCircle - displays a circle at position, p, with radius, r, in colour, c.
*/

static void debugCircle (coord_Coord p, double r, deviceIf_Colour c)
{
  deviceIf_glyphCircle (c2p (p), TRUE, Fractions_zero (), Fractions_putReal (r), c);
}


/*
   debugLine - displays a line from, p1, to, p2, in the debugging colour.
*/

static void debugLine (coord_Coord p1, coord_Coord p2, deviceIf_Colour c)
{
  typedef struct _T6_a _T6;

  struct _T6_a { Points_Point array[3+1]; };
  _T6 p;
  coord_Coord dy;
  coord_Coord dxy;

  sortLine (&p1, &p2);
  dy = coord_initCoord (0.0, thickness*2.0);
  dxy = coord_initCoord (thickness, thickness);
  p.array[0] = c2p (coord_subCoord (p1, dxy));
  p.array[1] = c2p (coord_addCoord (coord_subCoord (p1, dxy), dy));
  p.array[2] = c2p (coord_addCoord (p2, dxy));
  p.array[3] = c2p (coord_subCoord (coord_addCoord (p2, dxy), dy));
  deviceIf_glyphPolygon (4, (Points_Point *) &p.array[0], 3, TRUE, Fractions_zero (), c);
}


/*
   doCircle - pass parameters to the groffDevice.
*/

static void doCircle (coord_Coord p, double r, deviceIf_Colour c)
{
  deviceIf_glyphCircle (c2p (p), TRUE, Fractions_zero (), Fractions_putReal (r), c);
}


/*
   doPolygon -
*/

static void doPolygon (unsigned int n, coord_Coord *p_, unsigned int _p_high, deviceIf_Colour c)
{
  typedef struct _T7_a _T7;

  struct _T7_a { Points_Point array[MaxPolygonPoints+1]; };
  _T7 points;
  unsigned int i;
  coord_Coord p[_p_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (p, p_, (_p_high+1) * sizeof (coord_Coord));

  for (i=0; i<=n-1; i++)
    {
      if (Debugging)
        libc_printf ((char *) "polygon point %d: %g, %g\\n", 26, i, p[i].x, p[i].y);
      points.array[i] = c2p ((coord_Coord) p[i]);
    }
  deviceIf_glyphPolygon (n, (Points_Point *) &points.array[0], MaxPolygonPoints, TRUE, Fractions_zero (), c);
}


/*
   drawBoarder -
*/

static void drawBoarder (deviceIf_Colour c)
{
  typedef struct _T8_a _T8;

  struct _T8_a { Points_Point array[3+1]; };
  _T8 p;

  p.array[0] = Points_initPoint (Fractions_zero (), Fractions_zero ());
  p.array[1] = Points_initPoint (Fractions_one (), Fractions_zero ());
  p.array[2] = Points_initPoint (Fractions_one (), Fractions_one ());
  p.array[3] = Points_initPoint (Fractions_zero (), Fractions_one ());
  deviceIf_glyphPolygon (4, (Points_Point *) &p.array[0], 3, FALSE, Fractions_initFract (0, 1, 100), c);
}


/*
   drawBackground -
*/

static void drawBackground (deviceIf_Colour c)
{
  typedef struct _T9_a _T9;

  struct _T9_a { Points_Point array[3+1]; };
  _T9 p;

  p.array[0] = Points_initPoint (Fractions_zero (), Fractions_zero ());
  p.array[1] = Points_initPoint (Fractions_one (), Fractions_zero ());
  p.array[2] = Points_initPoint (Fractions_one (), Fractions_one ());
  p.array[3] = Points_initPoint (Fractions_zero (), Fractions_one ());
  deviceIf_glyphPolygon (4, (Points_Point *) &p.array[0], 3, TRUE, Fractions_zero (), c);
}


/*
   getVelCoord - returns a velocity coordinate pair for Object, o.
*/

static coord_Coord getVelCoord (Object o)
{
  checkDeleted (o);
  if (o->fixed || o->stationary)
    return coord_initCoord (0.0, 0.0);
  else
    return coord_initCoord (o->vx, o->vy);
}


/*
   getAccelCoord - returns an acceleration coordinate pair for Object, o.
*/

static coord_Coord getAccelCoord (Object o)
{
  checkDeleted (o);
  if (o->fixed || o->stationary)
    return coord_initCoord (0.0, 0.0);
  else
    return coord_initCoord (o->ax, o->ay+simulatedGravity);
}


/*
   getCollisionColour - returns the collision colour if requiredDebug,
                        otherwise return, c.
*/

static deviceIf_Colour getCollisionColour (deviceIf_Colour c, unsigned int requiredDebug)
{
  if (requiredDebug && haveCollisionColour)
    return collisionColour;
  else
    return c;
}


/*
   doDrawFrame -
*/

static void doDrawFrame (Object optr, double dt, unsigned int needsDebug)
{
  typedef struct _T10_a _T10;

  struct _T10_a { coord_Coord array[MaxPolygonPoints+1]; };
  unsigned int i;
  coord_Coord co;
  coord_Coord vc;
  coord_Coord ac;
  _T10 po;
  deviceIf_Colour oc;

  if (DebugTrace)
    libc_printf ((char *) "doDrawFrame (%g)\\n", 18, dt);
  checkDeleted (optr);
  vc = getVelCoord (optr);
  ac = getAccelCoord (optr);
  switch (optr->object)
    {
      case circleOb:
        doCircle (newPositionCoord (optr->c.pos, vc, ac, dt), optr->c.r, getCollisionColour (optr->c.col, needsDebug));
        break;

      case springOb:
        break;

      case polygonOb:
        for (i=0; i<=optr->p.nPoints-1; i++)
          {
            po.array[i] = newPositionRotationCoord (optr->p.cOfG, vc, ac, dt, optr->angularVelocity, optr->angleOrientation, (polar_Polar) optr->p.points.array[i]);
            if (Debugging)
              libc_printf ((char *) "po[%d].x = %g, po[%d].y = %g\\n", 30, i, po.array[i].x, i, po.array[i].y);
            co = coord_addCoord (optr->p.cOfG, polar_polarToCoord (polar_rotatePolar ((polar_Polar) optr->p.points.array[i], optr->angleOrientation)));
            if (Debugging)
              libc_printf ((char *) " [co.x = %g, co.y = %g]\\n", 25, co.x, co.y);
            if (roots_nearZero (dt))
              if ((! (roots_nearZero (co.x-po.array[i].x))) || (! (roots_nearZero (co.y-po.array[i].y))))
                {
                  libc_printf ((char *) "these values should be the same\\n", 33);
                  libc_exit (1);
                }
          }
        doPolygon (optr->p.nPoints, (coord_Coord *) &po.array[0], MaxPolygonPoints, getCollisionColour (optr->p.col, needsDebug));
        break;


      default:
        CaseException ("..//twoDsim.def", 2, 1);
    }
}


/*
   getCollisionObjects -
*/

static void getCollisionObjects (Object *id1, Object *id2, eventQueue e)
{
  (*id1) = NULL;
  (*id2) = NULL;
  if (e != NULL)
    switch (e->ePtr->etype)
      {
        case circlesEvent:
          (*id1) = Indexing_GetIndice (objects, e->ePtr->cc.cid1);
          (*id2) = Indexing_GetIndice (objects, e->ePtr->cc.cid2);
          break;

        case circlePolygonEvent:
          (*id1) = Indexing_GetIndice (objects, e->ePtr->cp.cid);
          (*id2) = Indexing_GetIndice (objects, e->ePtr->cp.pid);
          break;

        case polygonPolygonEvent:
          (*id1) = Indexing_GetIndice (objects, e->ePtr->pp.pid1);
          (*id2) = Indexing_GetIndice (objects, e->ePtr->pp.pid2);
          break;


        default:
          CaseException ("..//twoDsim.def", 2, 1);
      }
}


/*
   drawFrame - draws the current world into the frame buffer.
               If e is not NIL then it will be a collision event
               which describes the objects colliding.  The
               drawFrame will draw these objects using
               the debugging colour.
*/

static void drawFrame (eventQueue e)
{
  double dt;
  unsigned int i;
  unsigned int n;
  Object id1;
  Object id2;
  Object optr;

  Assert ((e == NULL) || (e->kind == collisionKind), 1913);
  getCollisionObjects (&id1, &id2, e);
  if (DebugTrace)
    libc_printf ((char *) "start drawFrame\\n", 17);
  if (writeTimeDelay)
    deviceIf_writeTime (currentTime-lastDrawTime);
  lastDrawTime = currentTime;
  dt = currentTime-lastUpdateTime;
  if (DebugTrace)
    libc_printf ((char *) "before drawBoarder\\n", 20);
  drawBoarder ((deviceIf_Colour) deviceIf_black ());
  if (DebugTrace)
    libc_printf ((char *) "after drawBoarder\\n", 19);
  n = Indexing_HighIndice (objects);
  i = 1;
  while (i <= n)
    {
      optr = Indexing_GetIndice (objects, i);
      if ((optr != NULL) && ! optr->deleted)
        {
          if (Debugging)
            DumpObject (optr);
          doDrawFrame (optr, dt, (optr == id1) || (optr == id2));
        }
      i += 1;
    }
}


/*
   drawFrameEvent -
*/

static void drawFrameEvent (eventQueue e)
{
  if (DebugTrace)
    libc_printf ((char *) "start drawFrameEvent\\n", 22);
  deviceIf_frameNote ();
  if (DebugTrace)
    libc_printf ((char *) "before drawFrame\\n", 18);
  drawFrame ((eventQueue) NULL);
  if (DebugTrace)
    libc_printf ((char *) "before flipBuffer\\n", 19);
  deviceIf_flipBuffer ();
  if (DebugTrace)
    libc_printf ((char *) "before addEvent\\n", 17);
  addEvent ((eventKind) frameKind, 1.0/framesPerSecond, (eventProc) {(eventProc_t) drawFrameEvent});
  if (DebugTrace)
    libc_printf ((char *) "collectAll\\n", 12);
  GC_collectAll ();
  if (DebugTrace)
    libc_printf ((char *) "end drawFrameEvent\\n", 20);
}


/*
   incRadians - return (a + b) mod 2pi.   The value returned will be between 0..2pi
*/

static double incRadians (double a, double b)
{
  a = a+b;
  if (roots_nearZero (a))
    a = 0.0;
  else
    {
      while (a < 0.0)
        a = a+(2.0*MathLib0_pi);
      while (a > (2.0*MathLib0_pi))
        a = a-(2.0*MathLib0_pi);
    }
  return a;
}


/*
   updatePolygon -
*/

static void updatePolygon (Object optr, double dt)
{
  if (! optr->deleted)
    {
      optr->p.cOfG.x = newPositionScalar (optr->p.cOfG.x, optr->vx, optr->ax, dt);
      optr->p.cOfG.y = newPositionScalar (optr->p.cOfG.y, optr->vy, optr->ay+simulatedGravity, dt);
      optr->vx = optr->vx+(optr->ax*dt);
      optr->vy = optr->vy+((optr->ay+simulatedGravity)*dt);
      optr->angleOrientation = incRadians (optr->angleOrientation, optr->angularVelocity*dt);
    }
}


/*
   updateCircle -
*/

static void updateCircle (Object optr, double dt)
{
  double vn;

  if (! optr->deleted)
    {
      optr->c.pos.x = newPositionScalar (optr->c.pos.x, optr->vx, optr->ax, dt);
      optr->vx = optr->vx+(optr->ax*dt);
      optr->c.pos.y = newPositionScalar (optr->c.pos.y, optr->vy, optr->ay+simulatedGravity, dt);
      optr->vy = optr->vy+((optr->ay+simulatedGravity)*dt);
    }
}


/*
   updateOb -
*/

static void updateOb (Object optr, double dt)
{
  if ((! optr->deleted && ! optr->fixed) && ! optr->stationary)
    switch (optr->object)
      {
        case polygonOb:
          updatePolygon (optr, dt);
          break;

        case circleOb:
          updateCircle (optr, dt);
          break;

        case springOb:
          break;


        default:
          CaseException ("..//twoDsim.def", 2, 1);
      }
}


/*
   doUpdatePhysics - updates all positions of objects based on the passing of
                     dt seconds.
*/

static void doUpdatePhysics (double dt)
{
  unsigned int i;
  unsigned int n;
  Object optr;

  n = Indexing_HighIndice (objects);
  i = 1;
  while (i <= n)
    {
      optr = Indexing_GetIndice (objects, i);
      updateOb (optr, dt);
      i += 1;
    }
}


/*
   updatePhysics - updates the velocity of all objects based on
                   the elapsed time from the last collision until now.
*/

static void updatePhysics (void)
{
  doUpdatePhysics (currentTime-lastUpdateTime);
  lastUpdateTime = currentTime;
}


/*
   displayEvent -
*/

static void displayEvent (eventQueue e)
{
  libc_printf ((char *) "%g %p ", 6, e->time, e->p);
  if (e->kind == frameKind)
    libc_printf ((char *) "frameKind ", 10);
  else if (e->kind == collisionKind)
    libc_printf ((char *) "collisionKind ", 14);
  else if (e->kind == functionKind)
    libc_printf ((char *) "functionEvent ", 14);
  else
    libc_printf ((char *) "unknown kind ", 13);
  if (e->ePtr == NULL)
    libc_printf ((char *) "\\n", 2);
  else
    switch (e->ePtr->etype)
      {
        case frameEvent:
          libc_printf ((char *) "display frame event\\n", 21);
          break;

        case circlesEvent:
          libc_printf ((char *) "circle %d and circle %d colliding event\\n", 41, e->ePtr->cc.cid1, e->ePtr->cc.cid2);
          break;

        case circlePolygonEvent:
          libc_printf ((char *) "circle %d and polygon %d colliding event\\n", 42, e->ePtr->cp.cid, e->ePtr->cp.pid);
          if (e->ePtr->cp.wpid == history_corner)
            libc_printf ((char *) "  hits polygon on its corner %d\\n", 33, e->ePtr->cp.pointNo);
          else
            libc_printf ((char *) "  hits polygon on its edge %d\\n", 31, e->ePtr->cp.lineNo);
          break;

        case polygonPolygonEvent:
          libc_printf ((char *) "polygon %d and polygon %d colliding event\\n", 43, e->ePtr->pp.pid1, e->ePtr->pp.pid2);
          if (e->ePtr->pp.wpid1 == history_corner)
            libc_printf ((char *) "  polygon (%d) corner %d hits", 29, e->ePtr->pp.pid1, e->ePtr->pp.lineCorner1);
          else
            libc_printf ((char *) "  polygon (%d) edge %d hits ", 28, e->ePtr->pp.pid1, e->ePtr->pp.lineCorner1);
          if (e->ePtr->pp.wpid2 == history_corner)
            libc_printf ((char *) " polygon (%d) on corner %d\\n", 28, e->ePtr->pp.pid2, e->ePtr->pp.lineCorner2);
          else
            libc_printf ((char *) " polygon (%d) on edge %d\\n", 26, e->ePtr->pp.pid2, e->ePtr->pp.lineCorner2);
          break;

        case functionEvent:
          libc_printf ((char *) "function event %d\\n", 19, e->ePtr->fc.id);
          break;


        default:
          CaseException ("..//twoDsim.def", 2, 1);
      }
}


/*
   printQueue - prints out the event queue.
*/

static void printQueue (void)
{
  eventQueue e;

  if (DebugTrace || TRUE)
    {
      libc_printf ((char *) "current time = %g,  lastDrawTime = %g,  lastUpdateTime = %g\\n", 61, currentTime, lastDrawTime, lastUpdateTime);
      libc_printf ((char *) "The event queue\\n", 17);
      libc_printf ((char *) "===============\\n", 17);
      e = eventQ;
      while (e != NULL)
        {
          displayEvent (e);
          e = e->next;
        }
    }
}


/*
   updateStats -
*/

static void updateStats (double dt)
{
  unsigned int lastTime;
  unsigned int nextTime;
  unsigned int fps;

  lastTime = (int) (currentTime*10.0);
  nextTime = (int) ((currentTime+dt)*10.0);
  if (lastTime != nextTime)
    {
      fps = delay_getActualFPS ();
      libc_printf ((char *) "%d.%d seconds simulated, fps: %d\\n", 34, nextTime / 10, nextTime % 10, fps);
    }
}


/*
   doFunctionEvent -
*/

static void doFunctionEvent (eventQueue e)
{
  if (DebugTrace)
    {
      libc_printf ((char *) "doFunctionEvent\\n", 17);
      printQueue ();
    }
  resetQueue ();
  if (DebugTrace)
    {
      libc_printf ((char *) "adjusting the queue\\n", 21);
      printQueue ();
      libc_printf ((char *) "end of FunctionEvent\\n", 22);
    }
}


/*
   doNextEvent -
*/

static double doNextEvent (void)
{
  eventQueue e;
  double dt;
  eventProc p;

  if (eventQ == NULL)
    {
      libc_printf ((char *) "no more events on the event queue\\n", 35);
      libc_exit (1);
      return 0.0;
    }
  else
    {
      e = eventQ;
      eventQ = eventQ->next;
      dt = e->time;
      p = e->p;
      currentTime = currentTime+dt;
      Assert ((((p.proc == drawFrameEvent) || (p.proc == doCollision)) || (p.proc == debugFrame)) || (p.proc == doFunctionEvent), 2262);
      (*p.proc) (e);
      disposeDesc (&e->ePtr);
      disposeEvent (e);
      updateStats (dt);
      checkInterpen ();
      return dt;
    }
}


/*
   checkZero -
*/

static void checkZero (double *v)
{
  if ((((*v) > 0.0) && ((*v) < 0.01)) || (((*v) < 0.0) && ((*v) > -0.01)))
    (*v) = 0.0;
}


/*
   checkZeroCoord -
*/

static coord_Coord checkZeroCoord (coord_Coord c)
{
  if (roots_nearZero (c.x))
    c.x = 0.0;
  if (roots_nearZero (c.y))
    c.y = 0.0;
  return c;
}


/*
   inElastic -
*/

static void inElastic (double *v)
{
  (*v) = (*v)*Elasticity;
  checkZero (v);
}


/*
   nearZeroVelocity - returns TRUE if, r, is close to 0.0
*/

static unsigned int nearZeroVelocity (double r)
{
  if (r >= 0.0)
    return r < 0.01;
  else
    return -r < 0.01;
}


/*
   checkStationary - checks to see if object, o, should be put into
                     the stationary state.
*/

static void checkStationary (Object o)
{
  if (objectExists (o))
    if (! o->fixed)
      {
        inElastic (&o->vx);
        inElastic (&o->vy);
        o->stationary = (nearZeroVelocity (o->vx)) && (nearZeroVelocity (o->vy));
        if (o->stationary)
          {
            o->vx = 0.0;
            o->vy = 0.0;
            if (Debugging)
              DumpObject (o);
          }
      }
}


/*
   checkStationaryCollision - stationary object, a, has been bumped by
                              moving object, b.  We move a slightly and
                              give it an initial velocity and change its
                              state from stationary to moving.
*/

static void checkStationaryCollision (Object a, Object b)
{
  if (a->stationary && ! a->deleted)
    {
      if (Debugging)
        libc_printf ((char *) "object %d has bumped into a stationary object %d\\n", 50, b->id, a->id);
      a->vy = 1.0;
      if (a->c.pos.x < b->c.pos.x)
        a->c.pos.x = a->c.pos.x-0.001;
      else
        a->c.pos.x = a->c.pos.x+0.001;
      a->c.pos.y = a->c.pos.y+0.001;
      a->stationary = FALSE;
      if (Debugging)
        DumpObject (a);
    }
  else if (b->stationary && ! b->deleted)
    checkStationaryCollision (b, a);
}


/*
   collideFixedCircles - works out the new velocity given that the circle
                         movable collides with the fixed circle.
*/

static void collideFixedCircles (Object movable, Object fixed)
{
  collideAgainstFixedCircle (movable, fixed->c.pos);
}


/*
   collideAgainstFixedCircle - the movable object collides against a point, center.
                               center, is the center point of the other fixed circle.
                               This procedure works out the new velocity of the movable
                               circle given these constraints.
*/

static void collideAgainstFixedCircle (Object movable, coord_Coord center)
{
  double r;
  double j;
  coord_Coord c;
  coord_Coord normalCollision;
  coord_Coord relativeVelocity;

  c.x = movable->c.pos.x-center.x;
  c.y = movable->c.pos.y-center.y;
  r = libm_sqrt ((c.x*c.x)+(c.y*c.y));
  normalCollision.x = c.x/r;
  normalCollision.y = c.y/r;
  relativeVelocity.x = movable->vx;
  relativeVelocity.y = movable->vy;
  j = (-((1.0+1.0)*((relativeVelocity.x*normalCollision.x)+(relativeVelocity.y*normalCollision.y))))/(((normalCollision.x*normalCollision.x)+(normalCollision.y*normalCollision.y))*(1.0/movable->c.mass));
  movable->vx = movable->vx+((j*normalCollision.x)/movable->c.mass);
  movable->vy = movable->vy+((j*normalCollision.y)/movable->c.mass);
  checkStationary (movable);
}


/*
   collideMovableCircles -
*/

static void collideMovableCircles (Object iptr, Object jptr)
{
  double r;
  double j;
  coord_Coord c;
  coord_Coord normalCollision;
  coord_Coord relativeVelocity;

  c.x = iptr->c.pos.x-jptr->c.pos.x;
  c.y = iptr->c.pos.y-jptr->c.pos.y;
  r = libm_sqrt ((c.x*c.x)+(c.y*c.y));
  normalCollision.x = c.x/r;
  normalCollision.y = c.y/r;
  relativeVelocity.x = iptr->vx-jptr->vx;
  relativeVelocity.y = iptr->vy-jptr->vy;
  j = (-((1.0+1.0)*((relativeVelocity.x*normalCollision.x)+(relativeVelocity.y*normalCollision.y))))/(((normalCollision.x*normalCollision.x)+(normalCollision.y*normalCollision.y))*((1.0/iptr->c.mass)+(1.0/jptr->c.mass)));
  iptr->vx = iptr->vx+((j*normalCollision.x)/iptr->c.mass);
  iptr->vy = iptr->vy+((j*normalCollision.y)/iptr->c.mass);
  jptr->vx = jptr->vx-((j*normalCollision.x)/jptr->c.mass);
  jptr->vy = jptr->vy-((j*normalCollision.y)/jptr->c.mass);
  checkStationaryCollision (iptr, jptr);
  checkStationary (iptr);
  checkStationary (jptr);
}


/*
   circleCollision - call fixed or movable circle collision depending upon whether
                     one or two circles are fixed.
                     Apart from taking into account rotation of either circle this
                     is complete.
*/

static void circleCollision (Object iptr, Object jptr)
{
  if (iptr->fixed)
    collideFixedCircles (jptr, iptr);
  else if (jptr->fixed)
    collideFixedCircles (iptr, jptr);
  else
    collideMovableCircles (iptr, jptr);
}


/*
   collideCircleAgainstFixedEdge - modifies the circle velocity based upon the edge it hits.
                                   We use the formula:

                                   V = 2 * (-I . N ) * N + I

                                   where:

                                   I is the initial velocity vector
                                   V is the final velocity vector
                                   N is the normal to the line
*/

static void collideCircleAgainstFixedEdge (Object cPtr, coord_Coord p1, coord_Coord p2)
{
  coord_Coord l;
  coord_Coord vel;

  sortLine (&p1, &p2);
  l = coord_subCoord (p2, p1);
  vel = coord_initCoord (cPtr->vx, cPtr->vy);
  vel = reflect (vel, l);
  cPtr->vx = vel.x;
  cPtr->vy = vel.y;
  checkStationary (cPtr);
}


/*
   circlePolygonCollision -
*/

static void circlePolygonCollision (eventQueue e, Object cPtr, Object pPtr)
{
  unsigned int ln;
  coord_Coord p1;
  coord_Coord p2;

  if (e->ePtr->etype == circlePolygonEvent)
    switch (e->ePtr->cp.wpid)
      {
        case history_corner:
          if (cPtr->fixed)
            M2RTS_HALT (0);
          else if (pPtr->fixed)
            collideAgainstFixedCircle (cPtr, e->ePtr->cp.cPoint);
          else
            M2RTS_HALT (0);
          break;

        case history_edge:
          if (cPtr->fixed)
            M2RTS_HALT (0);
          else if (pPtr->fixed)
            {
              ln = e->ePtr->cp.lineNo;
              getPolygonLine (ln, pPtr, &p1, &p2);
              collideCircleAgainstFixedEdge (cPtr, p1, p2);
            }
          else
            M2RTS_HALT (0);
          break;


        default:
          CaseException ("..//twoDsim.def", 2, 1);
      }
  else
    M2RTS_HALT (0);
}


/*
   collidePolygonAgainstFixedCircle - polygon, o, is moving and has hit
                                      a fixed circle at position, collision.
*/

static void collidePolygonAgainstFixedCircle (Object o, coord_Coord collision)
{
  collideAgainstFixedCircle (o, collision);
  if (Debugging)
    DumpObject (o);
}


/*
   collidePolygonAgainstFixedEdge - p1, p2 is the fixed edge and, o, is the
                                    moving polygon.
*/

static void collidePolygonAgainstFixedEdge (Object o, coord_Coord p1, coord_Coord p2)
{
  collideCircleAgainstFixedEdge (o, p1, p2);
  if (Debugging)
    DumpObject (o);
}


/*
   rotationalVelocity - return a vector containing the velocity
                        if polygon is rotating at angular speed, w,
                        and non rotation speed is, u and the relative
                        position is, r.
*/

static coord_Coord rotationalVelocity (double w, coord_Coord u, coord_Coord r)
{
  return coord_addCoord (u, coord_scaleCoord (r, w));
}


/*
   calcInertia - calculate the inertia of a polygon.
*/

static void calcInertia (Object id)
{
  coord_Coord ci;
  coord_Coord cj;
  double top;
  double bot;
  double t;
  double b;
  unsigned int i;
  unsigned int j;

  if (id->object == polygonOb)
    {
      top = 0.0;
      bot = 0.0;
      for (i=0; i<=id->p.nPoints-1; i++)
        {
          j = (i+1) % id->p.nPoints;
          ci = coord_addCoord (id->p.cOfG, polar_polarToCoord (polar_rotatePolar ((polar_Polar) id->p.points.array[i], id->angleOrientation)));
          cj = coord_addCoord (id->p.cOfG, polar_polarToCoord (polar_rotatePolar ((polar_Polar) id->p.points.array[j], id->angleOrientation)));
          t = ((((((sqr (ci.x))+(sqr (ci.y)))+(ci.x*cj.x))+(ci.y*cj.y))+(sqr (cj.x)))+(sqr (cj.y)))*((ci.x*cj.y)-(cj.x*ci.y));
          top = top+t;
          b = (ci.x*cj.y)-(cj.x*ci.y);
          bot = bot+b;
        }
      id->inertia = (id->p.mass*top)/(bot*6.0);
    }
  else
    id->inertia = id->c.mass;
}


/*
   updatePolygonVelocity - update both linear and angular velocities of
                           object, o, using impulse, j.
                           n is the perpendicular to the impact.
                           rp is the distance of the c of g of an object,
                           o, to the point of collision.
*/

static void updatePolygonVelocity (Object o, double j, coord_Coord n, coord_Coord rpn)
{
  coord_Coord va;

  va = coord_initCoord (o->vx, o->vy);
  va = coord_addCoord (va, coord_scaleCoord (n, j/o->p.mass));
  o->vx = va.x;
  o->vy = va.y;
  o->angularVelocity = o->angularVelocity+((coord_dotProd (rpn, coord_scaleCoord (n, j)))/o->inertia);
}


/*
   polygonPolygonCollision - two polygons collide, we call the appropriate routines
                             depending upon whether one polygon is fixed.
*/

static void polygonPolygonCollision (eventQueue e, Object id1, Object id2)
{
  collidePolygonAgainstMovingPolygon (e, id1, id2);
}


/*
   reflect - reflect velocity, v, off line, l.

             V = 2 * (-I . n ) * n + I

             where:

             I is the initial velocity vector
             V is the final velocity vector
             n is the normal to the line, l.
*/

static coord_Coord reflect (coord_Coord v, coord_Coord l)
{
  coord_Coord n;

  n = coord_perpendicular (l);
  n = coord_normaliseCoord (n);
  return coord_addCoord (coord_scaleCoord (n, -(2.0*(coord_dotProd (v, n)))), v);
}


/*
   collidePolygonAgainstFixedPolygon - id1 is moving and id2 is fixed.
*/

static void collidePolygonAgainstFixedPolygon (eventQueue e, Object id1, Object id2)
{
  double I_;
  double m;
  double j;
  coord_Coord l;
  coord_Coord n;
  coord_Coord rap;
  coord_Coord rapn;
  coord_Coord p1;
  coord_Coord p2;
  coord_Coord p;
  coord_Coord v;

  Assert (! id1->fixed, 2794);
  Assert (id2->fixed, 2795);
  Assert (e->ePtr->etype == polygonPolygonEvent, 2796);
  if (Debugging)
    libc_printf ((char *) "collidePolygonAgainstFixedPolygon\\n", 35);
  drawFrame (e);
  p = e->ePtr->pp.cPoint;
  if (e->ePtr->pp.wpid2 == history_edge)
    {
      getPolygonLine (e->ePtr->pp.lineCorner2, (Object) Indexing_GetIndice (objects, e->ePtr->pp.pid2), &p1, &p2);
      l = coord_subCoord (p2, p1);
      debugLine (p1, p2, (deviceIf_Colour) deviceIf_yellow ());
    }
  else
    l = coord_subCoord (p, id2->p.cOfG);
  v = rotationalVelocity (id1->angularVelocity, coord_initCoord (id1->vx, id1->vy), coord_subCoord (p, id1->p.cOfG));
  rap = coord_subCoord (p, id1->p.cOfG);
  rapn = coord_perpendicular (rap);
  I_ = (sqr (coord_dotProd (rapn, n)))/id1->inertia;
  m = 1.0/id1->p.mass;
  debugCircle (id1->p.cOfG, 0.002, (deviceIf_Colour) deviceIf_yellow ());
  debugCircle (id2->p.cOfG, 0.002, (deviceIf_Colour) deviceIf_purple ());
  j = (-(1.0*(coord_dotProd (v, n))))/(((coord_dotProd (n, n))*m)+I_);
  updatePolygonVelocity (id1, -j, n, rapn);
  deviceIf_flipBuffer ();
}


/*
   collidePolygonAgainstMovingPolygon - both, id1, and, id2, are moving.
*/

static void collidePolygonAgainstMovingPolygon (eventQueue e, Object id1, Object id2)
{
  coord_Coord p1;
  coord_Coord p2;
  coord_Coord p;
  coord_Coord n;
  coord_Coord n2;
  coord_Coord v1;
  coord_Coord va;
  coord_Coord vb;
  coord_Coord vap;
  coord_Coord vbp;
  coord_Coord vab;
  coord_Coord rap;
  coord_Coord rbp;
  coord_Coord sum;
  coord_Coord vF1;
  coord_Coord vF2;
  double ca;
  double cb;
  double denominator;
  double vabDotN;
  double modifiedVel;
  double j1;
  double j2;
  double m;

  if (Debugging)
    {
      displayEvent (e);
      DumpObject (id1);
      DumpObject (id2);
    }
  Assert (e->ePtr->etype == polygonPolygonEvent, 2860);
  p = e->ePtr->pp.cPoint;
  deviceIf_frameNote ();
  drawFrame (e);
  if ((e->ePtr->pp.wpid1 == history_edge) && (e->ePtr->pp.wpid2 == history_edge))
    {
      if (Debugging)
        libc_printf ((char *) "the edges of two polygon collide\\n", 34);
      getPolygonLine (e->ePtr->pp.lineCorner1, (Object) Indexing_GetIndice (objects, e->ePtr->pp.pid1), &p1, &p2);
      sortLine (&p1, &p2);
      v1 = coord_subCoord (p2, p1);
      coord_perpendiculars (v1, &n, &n2);
      debugLine (p1, p2, (deviceIf_Colour) deviceIf_yellow ());
    }
  else if (e->ePtr->pp.wpid1 == history_edge)
    {
      if (Debugging)
        libc_printf ((char *) "the edge of polygon collides with corner of polygon\\n", 53);
      Assert (e->ePtr->pp.wpid2 == history_corner, 2885);
      getPolygonLine (e->ePtr->pp.lineCorner2, (Object) Indexing_GetIndice (objects, e->ePtr->pp.pid2), &p1, &p2);
      v1 = coord_subCoord (p2, p1);
      coord_perpendiculars (v1, &n, &n2);
      debugLine (p1, p2, (deviceIf_Colour) deviceIf_yellow ());
    }
  else if (e->ePtr->pp.wpid2 == history_edge)
    {
      if (Debugging)
        libc_printf ((char *) "the edge of polygon collides with corner of polygon\\n", 53);
      Assert (e->ePtr->pp.wpid1 == history_corner, 2898);
      getPolygonLine (e->ePtr->pp.lineCorner1, (Object) Indexing_GetIndice (objects, e->ePtr->pp.pid1), &p1, &p2);
      v1 = coord_subCoord (p2, p1);
      coord_perpendiculars (v1, &n, &n2);
      debugLine (p1, p2, (deviceIf_Colour) deviceIf_yellow ());
    }
  else
    libc_printf ((char *) "the corners of two polygon collide\\n", 36);
  debugCircle (id1->p.cOfG, 0.002, (deviceIf_Colour) deviceIf_yellow ());
  debugCircle (id2->p.cOfG, 0.002, (deviceIf_Colour) deviceIf_purple ());
  rap = coord_subCoord (p, id1->p.cOfG);
  rbp = coord_subCoord (p, id2->p.cOfG);
  vap = coord_addCoord (coord_initCoord (id1->vx, id1->vy), coord_scaleCoord (rap, id1->angularVelocity));
  vbp = coord_addCoord (coord_initCoord (id2->vx, id2->vy), coord_scaleCoord (rap, id2->angularVelocity));
  vab = coord_subCoord (vap, vbp);
  if (id1->fixed)
    m = 0.0;
  else
    m = 1.0/id1->p.mass;
  if (! id2->fixed)
    m = m+(1.0/id2->p.mass);
  denominator = m*(coord_dotProd (n, n));
  if (id1->fixed)
    ca = 0.0;
  else
    ca = (sqr (coord_dotProd (coord_perpendicular (rap), n)))/id1->inertia;
  if (id2->fixed)
    cb = 0.0;
  else
    cb = (sqr (coord_dotProd (coord_perpendicular (rbp), n)))/id2->inertia;
  denominator = (denominator+ca)+cb;
  vabDotN = coord_dotProd (vab, n);
  if (Debugging)
    libc_printf ((char *) "vabDotN = %g\\n", 14, vabDotN);
  modifiedVel = vabDotN/denominator;
  j1 = -((1.0+Elasticity)*modifiedVel);
  j2 = (1.0+Elasticity)*modifiedVel;
  if (Debugging)
    libc_printf ((char *) "j1 = %g, j2 = %g\\n", 18, j1, j2);
  if (! id1->fixed)
    {
      vF1 = coord_addCoord (coord_initCoord (id1->vx, id1->vy), coord_scaleCoord (n, j1/id1->p.mass));
      id1->vx = vF1.x;
      id1->vy = vF1.y;
    }
  if (! id2->fixed)
    {
      vF2 = coord_addCoord (coord_initCoord (id2->vx, id2->vy), coord_scaleCoord (n, j2/id2->p.mass));
      id2->vx = vF2.x;
      id2->vy = vF2.y;
    }
  if (id1->fixed)
    j2 = j2*2.0;
  if (id2->fixed)
    j1 = j1*2.0;
  if (! id1->fixed)
    {
      id1->angularMomentum = id1->angularMomentum+(coord_dotProd (rap, coord_scaleCoord (n, j1)));
      id1->angularVelocity = (1.0/id1->inertia)*id1->angularMomentum;
    }
  if (! id2->fixed)
    {
      id2->angularMomentum = id2->angularMomentum+(coord_dotProd (rbp, coord_scaleCoord (n, j2)));
      id2->angularVelocity = (1.0/id2->inertia)*id2->angularMomentum;
    }
  deviceIf_flipBuffer ();
}


/*
   physicsCollision - handle the physics of a collision between
                      the two objects defined in, e.
*/

static void physicsCollision (eventQueue e)
{
  Object id1;
  Object id2;

  switch (e->ePtr->etype)
    {
      case circlesEvent:
        id1 = Indexing_GetIndice (objects, e->ePtr->cc.cid1);
        id2 = Indexing_GetIndice (objects, e->ePtr->cc.cid2);
        circleCollision (id1, id2);
        break;

      case circlePolygonEvent:
        id1 = Indexing_GetIndice (objects, e->ePtr->cp.cid);
        id2 = Indexing_GetIndice (objects, e->ePtr->cp.pid);
        circlePolygonCollision (e, id1, id2);
        break;

      case polygonPolygonEvent:
        id1 = Indexing_GetIndice (objects, e->ePtr->pp.pid1);
        id2 = Indexing_GetIndice (objects, e->ePtr->pp.pid2);
        polygonPolygonCollision (e, id1, id2);
        break;


      default:
        CaseException ("..//twoDsim.def", 2, 1);
    }
}


/*
   doCollision - called whenever a collision event is processed.
*/

static void doCollision (eventQueue e)
{
  updatePhysics ();
  collisionOccurred (e->ePtr);
  if (drawCollisionFrame)
    {
      if (Debugging)
        libc_printf ((char *) "issuing collision draw frame\\n", 30);
      deviceIf_frameNote ();
      drawFrame (e);
      deviceIf_flipBuffer ();
    }
  physicsCollision (e);
  addNextCollisionEvent ();
}


/*
   sqr -
*/

static double sqr (double v)
{
  return v*v;
}


/*
   cub -
*/

static double cub (double v)
{
  return (v*v)*v;
}


/*
   quad -
*/

static double quad (double v)
{
  return ((v*v)*v)*v;
}


/*
   pent -
*/

static double pent (double v)
{
  return (quad (v))*v;
}


/*
   hex -
*/

static double hex (double v)
{
  return (cub (v))*(cub (v));
}


/*
   sept -
*/

static double sept (double v)
{
  return (quad (v))*(cub (v));
}


/*
   oct -
*/

static double oct (double v)
{
  return (quad (v))*(quad (v));
}


/*
   getCircleValues - assumes, o, is a circle and retrieves:
                     center    (x, y)
                     radius    radius
                     velocity  (vx, vy)
                     accel     (ax, ay)
*/

static void getCircleValues (Object o, double *x, double *y, double *radius, double *vx, double *vy, double *ax, double *ay)
{
  (*x) = o->c.pos.x;
  (*y) = o->c.pos.y;
  (*radius) = o->c.r;
  getObjectValues (o, vx, vy, ax, ay);
}


/*
   getObjectValues - fills in velocity and acceleration x, y, values.
*/

static void getObjectValues (Object o, double *vx, double *vy, double *ax, double *ay)
{
  if (o->fixed || o->stationary)
    {
      (*vx) = 0.0;
      (*vy) = 0.0;
      (*ax) = 0.0;
      (*ay) = 0.0;
    }
  else
    {
      (*vx) = o->vx;
      (*vy) = o->vy;
      (*ax) = o->ax;
      (*ay) = o->ay+simulatedGravity;
    }
}


/*
   getObjectOrbitingValues -
*/

static void getObjectOrbitingValues (Object o, double *r, double *w, coord_Coord *cofg)
{
  (*r) = o->angleOrientation;
  (*w) = o->angularVelocity;
  switch (o->object)
    {
      case polygonOb:
        (*cofg) = o->p.cOfG;
        break;

      case circleOb:
        (*cofg) = o->c.pos;
        break;


      default:
        M2RTS_HALT (0);
        break;
    }
}


/*
   maximaCircleCollisionOrbiting -
   x1 y1 x2 y2

   a, g, l, r       is  initial position of the point (not the c of g)
   b, h, m, s       is  initial velocity
   c, i, n, u       is  acceleration
   e, k, p, v       is  angular velocity
   f, q, k, w       is  the initial angular offset for the center of circle relative to the c of g.
                    The c of g is the center of the orbit.
   d,    o          the distance of the point from the c of g.
*/

static void maximaCircleCollisionOrbiting (double *array, unsigned int _array_high, double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double m, double n, double o, double p, double q, double r, double s, double u, double v, double w, double x)
{
}


/*
   earlierCircleCollisionOrbiting -

           t          is the time of this collision (if any)
           tc         is the time of the next collision.

           c1p        is the initial position of the center of circle 1.
                      This may not be the c of g of this circle if it is in orbit.
           c1radius   is the radius of the circle.
           c1r        rotational offset of point 1.
           c1cofg     center of gravity of point 1.
           c1w        rotational angular velocity of point 1.
           c1a        acceleration of point 1.

           c2p        is the initial position of the center of circle 2.
                      This may not be the c of g of this circle if it is in orbit.
           c2radius   is the radius of the circle.
           c2r        rotational offset of point 2.
           c2cofg     center of gravity of point 2.
           c2w        rotational angular velocity of point 2.
           c2a        acceleration of point 2.
*/

static unsigned int earlierCircleCollisionOrbiting (double *t, double *tc, coord_Coord c1p, double c1radius, double c1r, double c1w, coord_Coord c1cofg, coord_Coord c1v, coord_Coord c1a, coord_Coord c2p, double c2radius, double c2r, double c2w, coord_Coord c2cofg, coord_Coord c2v, coord_Coord c2a)
{
  typedef struct _T11_a _T11;

  struct _T11_a { double array[8+1]; };
  double d1;
  double d2;
  double A;
  double B;
  double C;
  double D;
  double E;
  double F;
  double G;
  double H;
  double I_;
  double T;
  _T11 array;

  d1 = coord_lengthCoord (coord_subCoord (c1p, c1cofg));
  d2 = coord_lengthCoord (coord_subCoord (c2p, c2cofg));
  maximaCircleCollisionOrbiting ((double *) &array.array[0], 8, c1p.x, c1v.x, c1a.x, d1, c1w, c1r, c2p.x, c2v.x, c2a.x, c2w, c2r, c1p.y, c1v.y, c1a.y, d2, c1w, c1r, c2p.y, c2v.y, c2a.y, c2w, c2r, c1radius+c2radius);
  A = array.array[8];
  B = array.array[7];
  C = array.array[6];
  D = array.array[5];
  E = array.array[4];
  F = array.array[3];
  G = array.array[2];
  H = array.array[1];
  I_ = array.array[0];
  if (roots_findOctic (A, B, C, D, E, F, G, H, I_, t))
    {
      T = ((((((((A*(oct ((*t))))+(B*(sept ((*t)))))+(C*(hex ((*t)))))+(D*(pent ((*t)))))+(E*(quad ((*t)))))+(F*(cub ((*t)))))+(G*(sqr ((*t)))))+(H*(*t)))+I_;
      if (Debugging)
        libc_printf ((char *) "%gt^8 + %gt^7 +%gt^6 + %gt^5 + %gt^4 + %gt^3 + %gt^2 + %gt + %g = %g    (t=%g)\\n", 80, A, B, C, D, E, F, G, H, I_, T, (*t));
      if ((((*tc) < 0.0) || ((*t) < (*tc))) && (! (roots_nearZero ((*t)))))
        return TRUE;
    }
  return FALSE;
}


/*
   maximaCircleCollision -
*/

static void maximaCircleCollision (double *array, unsigned int _array_high, double a, double b, double c, double d, double e, double f, double g, double h, double k, double l, double m, double n, double o, double p)
{
}


/*
   earlierCircleCollision - let the following abreviations be assigned.
                            Note i is one circle, j is another circle.
                                 v is velocity, a, acceleration, x, y axis.
                                 r is radius.

                            Single letter variables are used since wxmaxima
                            only operates with these.  Thus the output from wxmaxima
                            can be cut and pasted into the program.

                            a = xi
                            b = xj
                            c = vxi
                            d = vxj
                            e = aix
                            f = ajx
                            g = yi
                            h = yj
                            k = vyi
                            l = vyj
                            m = aiy
                            n = ajy
                            o = ri
                            p = rj

                            t                       is the time of this collision (if any)
                            bestTimeOfCollision     is earlier known collision so far.
*/

static unsigned int earlierCircleCollision (eventDesc edesc, unsigned int id1, unsigned int id2, double *t, double bestTimeOfCollision, coord_Coord *cp, double a, double b, double c, double d, double e, double f, double g, double h, double k, double l, double m, double n, double o, double p)
{
  typedef struct _T12_a _T12;

  struct _T12_a { double array[4+1]; };
  double A;
  double B;
  double C;
  double D;
  double E;
  double T;
  _T12 array;
  coord_Coord c1;
  coord_Coord c2;
  coord_Coord cp1;
  coord_Coord cp2;
  coord_Coord v12;
  coord_Coord r12;

  A = (((((sqr (n))-((2.0*m)*n))+(sqr (m)))+(sqr (f)))-((2.0*e)*f))+(sqr (e));
  B = (((((4.0*l)-(4.0*k))*n)+(((4.0*k)-(4.0*l))*m))+(((4.0*d)-(4.0*c))*f))+(((4.0*c)-(4.0*d))*e);
  C = (((((((((((4.0*h)-(4.0*g))*n)+(((4.0*g)-(4.0*h))*m))+(4.0*(sqr (l))))-((8.0*k)*l))+(4.0*(sqr (k))))+(((4.0*b)-(4.0*a))*f))+(((4.0*a)-(4.0*b))*e))+(4.0*(sqr (d))))-((8.0*c)*d))+(4.0*(sqr (c)));
  D = (((((8.0*h)-(8.0*g))*l)+(((8.0*g)-(8.0*h))*k))+(((8.0*b)-(8.0*a))*d))+(((8.0*a)-(8.0*b))*c);
  E = ((((((4.0*(sqr (h)))-((8.0*g)*h))+(4.0*(sqr (g))))+(4.0*(sqr (b))))-((8.0*a)*b))+(4.0*(sqr (a))))-(sqr (2.0*(p+o)));
  if (roots_findQuartic (A, B, C, D, E, t))
    {
      T = ((((A*((sqr ((*t)))*(sqr ((*t)))))+(B*((sqr ((*t)))*(*t))))+(C*(sqr ((*t)))))+(D*(*t)))+E;
      if (Debugging)
        {
          libc_printf ((char *) "%gt^4 + %gt^3 +%gt^2 + %gt + %g = %g    (t=%g)\\n", 48, A, B, C, D, E, T, (*t));
          libc_printf ((char *) "found collision at %g\\n", 23, (*t));
        }
      Assert ((*t) >= 0.0, 3383);
      if ((edesc == NULL) || ((*t) < bestTimeOfCollision))
        {
          c1 = newPositionCoord (coord_initCoord (a, g), coord_initCoord (c, k), coord_initCoord (e, m), (*t));
          c2 = newPositionCoord (coord_initCoord (b, h), coord_initCoord (d, l), coord_initCoord (f, n), (*t));
          v12 = coord_subCoord (c1, c2);
          Assert (roots_nearCoord (c1, coord_addCoord (c2, v12)), 3394);
          cp2 = coord_addCoord (c2, coord_scaleCoord (v12, o/(o+p)));
          cp1 = coord_subCoord (c1, coord_scaleCoord (v12, p/(o+p)));
          (*cp) = cp2;
          if (roots_nearSame (coord_lengthCoord (v12), o+p))
            {
              Assert (roots_nearCoord (cp1, cp2), 3411);
              if (! (history_isDuplicate (currentTime, (*t), id1, id2, (history_whereHit) history_edge, (history_whereHit) history_edge, (*cp))))
                return TRUE;
            }
          else
            libc_printf ((char *) "false the collisions points do not touch ignoring = %g, %g\\n", 60, (*cp).x, (*cp).y);
        }
    }
  return FALSE;
}


/*
   findCollisionCircles -

   using:

   S = UT + (AT^2)/2
   compute xin and yin which are the new (x,y) positions of object i at time, t.
   compute xjn and yjn which are the new (x,y) positions of object j at time, t.
   now compute difference between objects and if they are ri+rj  (radius of circle, i, and, j)
   apart then we have a collision at time, t.

   xin = xi + vxi * t + (aix * t^2) / 2.0
   yin = yi + vyi * t + (aiy * t^2) / 2.0

   xjn = xj + vxj * t + (ajx * t^2) / 2.0
   yjn = yj + vyj * t + (ajy * t^2) / 2.0

   ri + rj == sqrt(abs(xin-xjn)^2 + abs(yin-yjn)^2)     for values of t

   ri + rj == sqrt(((xi + vxi * t + aix * t^2 / 2.0) - (xj + vxj * t + ajx * t^2 / 2.0))^2 +
                   ((yi + vyi * t + aiy * t^2 / 2.0) - (yj + vyj * t + ajy * t^2 / 2.0))^2)

   let:

   a = xi
   b = xj
   c = vxi
   d = vxj
   e = aix
   f = ajx
   g = yi
   h = yj
   k = vyi
   l = vyj
   m = aiy
   n = ajy
   o = ri
   p = rj
   t = t

   o  + p  == sqrt(((a  + c   * t + e   * t^2 / 2.0) - (b  + d   * t +   f * t^2 / 2.0))^2 +
                   ((g  + k   * t + m   * t^2 / 2.0) - (h  + l   * t +   n * t^2 / 2.0))^2)

   o  + p  == sqrt(((a  + c   * t + e   * t^2 / 2.0) - (b  + d   * t +   f * t^2 / 2.0))^2 +
                   ((g  + k   * t + m   * t^2 / 2.0) - (h  + l   * t +   n * t^2 / 2.0))^2)

   0       == ((a  + c   * t + e   * t^2 / 2.0) - (b  + d   * t +   f * t^2 / 2.0))^2 +
              ((g  + k   * t + m   * t^2 / 2.0) - (h  + l   * t +   n * t^2 / 2.0))^2 -
              (o  + p)^2

   now using wxmaxima
   expand ; factor ; ratsimp

   p+o    ==  (sqrt((n^2-2*m*n+m^2+f^2-2*e*f+e^2)*t^4+
                   ((4*l-4*k)*n+(4*k-4*l)*m+(4*d-4*c)*f+(4*c-4*d)*e)*t^3+
                   ((4*h-4*g)*n+(4*g-4*h)*m+4*l^2-8*k*l+4*k^2+(4*b-4*a)*f+(4*a-4*b)*e+4*d^2-8*c*d+4*c^2)*t^2+
                   ((8*h-8*g)*l+(8*g-8*h)*k+(8*b-8*a)*d+(8*a-8*b)*c)*t+4*h^2-8*g*h+4*g^2+4*b^2-8*a*b+4*a^2))/2

   2*(p+o) ==  (sqrt((n^2-2*m*n+m^2+f^2-2*e*f+e^2)*t^4+
                    ((4*l-4*k)*n+(4*k-4*l)*m+(4*d-4*c)*f+(4*c-4*d)*e)*t^3+
                    ((4*h-4*g)*n+(4*g-4*h)*m+4*l^2-8*k*l+4*k^2+(4*b-4*a)*f+(4*a-4*b)*e+4*d^2-8*c*d+4*c^2)*t^2+
                    ((8*h-8*g)*l+(8*g-8*h)*k+(8*b-8*a)*d+(8*a-8*b)*c)*t+4*h^2-8*g*h+4*g^2+4*b^2-8*a*b+4*a^2))

   (2*(p+o))^2 == ((n^2-2*m*n+m^2+f^2-2*e*f+e^2)*t^4+
                   ((4*l-4*k)*n+(4*k-4*l)*m+(4*d-4*c)*f+(4*c-4*d)*e)*t^3+
                   ((4*h-4*g)*n+(4*g-4*h)*m+4*l^2-8*k*l+4*k^2+(4*b-4*a)*f+(4*a-4*b)*e+4*d^2-8*c*d+4*c^2)*t^2+
                   ((8*h-8*g)*l+(8*g-8*h)*k+(8*b-8*a)*d+(8*a-8*b)*c)*t+4*h^2-8*g*h+4*g^2+4*b^2-8*a*b+4*a^2))

   0           ==  (n^2-2*m*n+m^2+f^2-2*e*f+e^2)*t^4+
                   ((4*l-4*k)*n+(4*k-4*l)*m+(4*d-4*c)*f+(4*c-4*d)*e)*t^3+
                   ((4*h-4*g)*n+(4*g-4*h)*m+4*l^2-8*k*l+4*k^2+(4*b-4*a)*f+(4*a-4*b)*e+4*d^2-8*c*d+4*c^2)*t^2+
                   ((8*h-8*g)*l+(8*g-8*h)*k+(8*b-8*a)*d+(8*a-8*b)*c)*t+
                   4*h^2-8*g*h+4*g^2+4*b^2-8*a*b+4*a^2)-
                   ((2*(p+o))^2)

   solve polynomial:

   A := sqr(n)-2.0*m*n+sqr(m)+sqr(f)-2.0*e*f+sqr(e) ;
   B := (4.0*l-4.0*k)*n+(4.0*k-4.0*l)*m+(4.0*d-4.0*c)*f+(4.0*c-4.0*d)*e ;
   C := (4.0*h-4.0*g)*n+(4.0*g-4.0*h)*m+4.0*sqr(l)-8.0*k*l+4.0*sqr(k)+(4.0*b-4.0*a)*f+(4.0*a-4.0*b)*e+4.0*sqr(d)-8.0*c*d+4.0*sqr(c) ;
   D := (8.0*h-8.0*g)*l+(8.0*g-8.0*h)*k+(8.0*b-8.0*a)*d+(8.0*a-8.0*b)*c ;
   E := 4.0*sqr(h)-8.0*g*h+4.0*sqr(g)+4.0*sqr(b)-8.0*a*b+4.0*sqr(a)-sqr(2.0*(p+o)) ;
*/

static void findCollisionCircles (Object iptr, Object jptr, eventDesc *edesc, double *tc)
{
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
  double g;
  double h;
  double k;
  double l;
  double m;
  double n;
  double o;
  double p;
  double t;
  unsigned int i;
  unsigned int j;
  double T;
  coord_Coord cp;

  getCircleValues (iptr, &a, &g, &o, &c, &k, &e, &m);
  getCircleValues (jptr, &b, &h, &p, &d, &l, &f, &n);
  if (earlierCircleCollision ((*edesc), iptr->id, jptr->id, &t, (*tc), &cp, a, b, c, d, e, f, g, h, k, l, m, n, o, p))
    {
      (*tc) = t;
      (*edesc) = makeCirclesDesc (edesc, iptr->id, jptr->id, cp);
    }
}


/*
   stop -
*/

static void stop (void)
{
}


/*
   makeCirclesPolygonDesc - returns an eventDesc describing the collision between a circle and a polygon.
*/

static eventDesc makeCirclesPolygonDesc (eventDesc edesc, unsigned int cid, unsigned int pid, unsigned int lineNo, unsigned int pointNo, history_whereHit wpid1, history_whereHit wpid2, coord_Coord collisionPoint)
{
  Assert (wpid1 == history_corner, 3583);
  if (edesc == NULL)
    edesc = newDesc ();
  edesc->etype = circlePolygonEvent;
  edesc->cp.pid = pid;
  edesc->cp.cid = cid;
  edesc->cp.cPoint = collisionPoint;
  edesc->cp.wpid = wpid2;
  edesc->cp.lineNo = lineNo;
  edesc->cp.pointNo = pointNo;
  return edesc;
}


/*
   checkIfPointHits - return TRUE if t0 is either the first hit found or
                      is sooner than, tc.  It determines a hit by working out
                      the final position of partical:

                      x = s + ut + 1/2a t^2

                      if x>=0.0 and x <= length then it hits.
*/

static unsigned int checkIfPointHits (double timeOfPrevCollision, double t, double length, double s, double u, double a)
{
  double x;

  if (trace)
    libc_printf ((char *) "current best collision time is %g the new collision exists at time %g\\n", 71, timeOfPrevCollision, t);
  if ((timeOfPrevCollision == -1.0) || (t < timeOfPrevCollision))
    {
      x = newPositionScalar (s, u, a, t);
      if (trace)
        libc_printf ((char *) "line 0.0 .. %g  and point at %g ", 32, length, x);
      if ((x >= 0.0) && (x <= length))
        {
          if (trace)
            libc_printf ((char *) "will hit line\\n", 15);
          return TRUE;
        }
      if (trace)
        libc_printf ((char *) "misses line\\n", 13);
    }
  else if (trace)
    libc_printf ((char *) "the new time %g should be ignored as the best is %g\\n", 53, t, timeOfPrevCollision);
  return FALSE;
}


/*
   newPositionScalar - calculates the new position of a scalar in the future.
*/

static double newPositionScalar (double s, double u, double a, double t)
{
  return (s+(u*t))+((a*(t*t))/2.0);
}


/*
   newPositionRotationSinScalar - works out the new Y position for a point whose:

                                  current cofg Y position is:   c
                                  initial Y velocity is     :   u
                                  Y acceleration is         :   a
                                  angular velocity          :   w
                                  orientation               :   o
                                  polar coord position rel
                                  to cofg is                :   p
*/

static double newPositionRotationSinScalar (double c, double u, double a, double t, double w, double o, polar_Polar p)
{
  double O;

  if (Debugging)
    libc_printf ((char *) "c = %g, u = %g, a = %g, t = %g\\n", 32, c, u, a, t);
  O = newPositionScalar (c, u, a, t);
  if (Debugging)
    libc_printf ((char *) "O = %g, p.r = %g, p.w = %g, sin (w*t + o + p.w) = %g\\n", 54, O, p.r, p.w, libm_sin (((w*t)+o)+p.w));
  return O+(p.r*(libm_sin (((w*t)+o)+p.w)));
}


/*
   newPositionRotationCosScalar - works out the new X position for a point whose:

                                  current cofg X position is:   c
                                  initial X velocity is     :   u
                                  X acceleration is         :   a
                                  angular velocity          :   w
                                  orientation               :   o
                                  polar coord position rel
                                  to cofg is                :   p
*/

static double newPositionRotationCosScalar (double c, double u, double a, double t, double w, double o, polar_Polar p)
{
  double O;

  O = newPositionScalar (c, u, a, t);
  return O+(p.r*(libm_cos (((w*t)+o)+p.w)));
}


/*
   newPositionCoord - calculates the new position of point in the future.
*/

static coord_Coord newPositionCoord (coord_Coord c, coord_Coord u, coord_Coord a, double t)
{
  return coord_initCoord (newPositionScalar (c.x, u.x, a.x, t), newPositionScalar (c.y, u.y, a.y, t));
}


/*
   newPositionRotationCoord - calculates the new position of point, c+v, in the future.
                              Given angular velocity         : w
                                    orientation              : o
                                    time                     : t
                                    initial vel              : u
                                    accel                    : a
                                    c of g                   : c
                                    polar coord of the point : p
*/

static coord_Coord newPositionRotationCoord (coord_Coord c, coord_Coord u, coord_Coord a, double t, double w, double o, polar_Polar p)
{
  if (Debugging)
    libc_printf ((char *) "t = %g, w = %g, o = %g\\n", 24, t, w, o);
  return coord_initCoord (newPositionRotationCosScalar (c.x, u.x, a.x, t, w, o, p), newPositionRotationSinScalar (c.y, u.y, a.y, t, w, o, p));
}


/*
   hLine - debugging procedure to display a line on a half scale axis.
*/

static void hLine (coord_Coord p1, coord_Coord p2, deviceIf_Colour c)
{
  typedef struct _T13_a _T13;

  struct _T13_a { Points_Point array[1+1]; };
  _T13 p;

  p1 = coord_scaleCoord (p1, 0.5);
  p2 = coord_scaleCoord (p2, 0.5);
  p1 = coord_addCoord (p1, coord_initCoord (0.5, 0.5));
  p2 = coord_addCoord (p2, coord_initCoord (0.5, 0.5));
  p.array[0] = c2p (p1);
  p.array[1] = c2p (p2);
  deviceIf_glyphPolygon (2, (Points_Point *) &p.array[0], 1, FALSE, Fractions_initFract (0, 1, 16), c);
}


/*
   hPoint - debugging procedure to display a line on a half scale axis.
*/

static void hPoint (coord_Coord p, deviceIf_Colour c)
{
  p = coord_scaleCoord (p, 0.5);
  p = coord_addCoord (p, coord_initCoord (0.5, 0.5));
  deviceIf_glyphCircle (c2p (p), TRUE, Fractions_zero (), Fractions_putReal (0.05), c);
}


/*
   hCircle - debugging procedure to display a circle on a half scale axis.
*/

static void hCircle (coord_Coord p, double r, deviceIf_Colour c)
{
  p = coord_scaleCoord (p, 0.5);
  p = coord_addCoord (p, coord_initCoord (0.5, 0.5));
  deviceIf_glyphCircle (c2p (p), TRUE, Fractions_zero (), Fractions_putReal (r), c);
}


/*
   hVec - display a normalised vector on a half scale axis
*/

static void hVec (coord_Coord p, deviceIf_Colour c)
{
  p = coord_normaliseCoord (p);
  hLine (coord_initCoord (0.0, 0.0), coord_initCoord (p.x, 0.0), c);
  hLine (coord_initCoord (0.0, 0.0), coord_initCoord (0.0, p.y), c);
}


/*
   hFlush - flip the debugging buffer.
*/

static void hFlush (void)
{
  deviceIf_frameNote ();
  drawBoarder ((deviceIf_Colour) deviceIf_black ());
  deviceIf_flipBuffer ();
  GC_collectAll ();
}


/*
   checkPointCollision -
*/

static unsigned int checkPointCollision (double *timeOfPrevCollision, double t, double length, double cx, double rvx, double rax, coord_Coord c, coord_Coord cvel, coord_Coord caccel, coord_Coord *collisionPoint, unsigned int id1, unsigned int id2)
{
  if (trace)
    libc_printf ((char *) "entering checkPointCollision with the current best time %g\\n", 60, (*timeOfPrevCollision));
  if (checkIfPointHits ((*timeOfPrevCollision), t, length, cx, rvx, rax))
    {
      if (trace)
        libc_printf ((char *) "it crosses the region of interest (current best time %g)\\n", 58, (*timeOfPrevCollision));
      (*collisionPoint) = newPositionCoord (c, cvel, caccel, t);
      if (history_isDuplicate (currentTime, t, id1, id2, (history_whereHit) history_edge, (history_whereHit) history_edge, (*collisionPoint)))
        {
          if (trace)
            libc_printf ((char *) "but it is a duplicate (best time still %g)\\n", 44, (*timeOfPrevCollision));
          return FALSE;
        }
      else
        {
          if (trace)
            libc_printf ((char *) "point hits line, new best time of collision (%g)\\n", 50, t);
          (*timeOfPrevCollision) = t;
          return TRUE;
        }
    }
  else
    if (trace)
      libc_printf ((char *) "the point missed the line (best time is still %g)\\n", 51, (*timeOfPrevCollision));
  return FALSE;
}


/*
   earlierPointLineCollision - returns TRUE if we can find a collision between a point, c,
                               travelling at cvel with acceleration, caccel and a line
                               p1, p2, travelling at velocity, lvel, and acceleration laccel.
                               If a collision is found then the collisionPoint is also
                               calculated.
*/

static unsigned int earlierPointLineCollision (double *timeOfCollision, coord_Coord c, coord_Coord cvel, coord_Coord caccel, coord_Coord p1, coord_Coord p2, coord_Coord lvel, coord_Coord laccel, coord_Coord *collisionPoint, unsigned int id1, unsigned int id2)
{
  coord_Coord p3;
  coord_Coord c0;
  coord_Coord c1;
  coord_Coord rvel;
  coord_Coord raccel;
  double x;
  double t0;
  double t1;
  double hypot;
  double theta;

  if (trace)
    libc_printf ((char *) "earlierPointLineCollision entered and best time is %g\\n", 55, (*timeOfCollision));
  rvel = coord_subCoord (cvel, lvel);
  raccel = coord_subCoord (caccel, laccel);
  if (trace)
    libc_printf ((char *) "relative vel  (%g, %g),  accel (%g, %g)\\n", 41, rvel.x, rvel.y, raccel.x, raccel.y);
  p3 = coord_subCoord (p2, p1);
  hypot = coord_lengthCoord (p3);
  theta = libm_asin (p3.y/hypot);
  if (trace)
    libc_printf ((char *) "rotating line by %g degrees  (length of line is %g)\\n", 53, (180.0*theta)/3.14159, hypot);
  c0 = coord_subCoord (c, p1);
  c1 = coord_rotateCoord (c0, -theta);
  rvel = coord_rotateCoord (rvel, -theta);
  raccel = coord_rotateCoord (raccel, -theta);
  raccel = checkZeroCoord (raccel);
  rvel = checkZeroCoord (rvel);
  if (trace)
    libc_printf ((char *) "after rotation we have relative vel  (%g, %g),  accel (%g, %g)\\n", 64, rvel.x, rvel.y, raccel.x, raccel.y);
  if (FALSE)
    {
      hLine (coord_initCoord (0.0, 0.0), coord_initCoord (hypot, 0.0), (deviceIf_Colour) deviceIf_purple ());
      hPoint (c1, (deviceIf_Colour) deviceIf_purple ());
      hFlush ();
    }
  if (roots_findQuadratic (raccel.y/2.0, rvel.y, c1.y, &t0, &t1))
    {
      if (trace)
        libc_printf ((char *) "earlierPointLineCollision after findQuadratic and best time is %g\\n", 67, (*timeOfCollision));
      if ((t0 < 0.0) && (t1 < 0.0))
        {
          if (trace)
            libc_printf ((char *) "the point never crosses the line in the future\\n", 48);
          return FALSE;
        }
      else
        if (t0 == t1)
          {
            if (trace)
              libc_printf ((char *) "the point crosses the line once\\n", 33);
            if (checkPointCollision (timeOfCollision, t0, hypot, c1.x, rvel.x, raccel.x, c, cvel, caccel, collisionPoint, id1, id2))
              return TRUE;
          }
        else
          if (t0 < 0.0)
            {
              if (trace)
                {
                  libc_printf ((char *) "the point crosses the line once in the future and once in the past\\n", 68);
                  libc_printf ((char *) "only examining root %g, remember best is %g\\n", 45, t1, (*timeOfCollision));
                }
              if (checkPointCollision (timeOfCollision, t1, hypot, c1.x, rvel.x, raccel.x, c, cvel, caccel, collisionPoint, id1, id2))
                return TRUE;
            }
          else if (t1 < 0.0)
            {
              if (trace)
                libc_printf ((char *) "the point crosses the line once in the future and once in the past\\n", 68);
              if (checkPointCollision (timeOfCollision, t0, hypot, c1.x, rvel.x, raccel.x, c, cvel, caccel, collisionPoint, id1, id2))
                return TRUE;
            }
          else
            {
              if (trace)
                libc_printf ((char *) "the point crosses the line twice in the future\\n", 48);
              if (t0 < t1)
                {
                  if (checkPointCollision (timeOfCollision, t0, hypot, c1.x, rvel.x, raccel.x, c, cvel, caccel, collisionPoint, id1, id2))
                    {
                      if (trace)
                        libc_printf ((char *) "the point crosses the line first time in correct place\\n", 56);
                      return TRUE;
                    }
                  if (checkPointCollision (timeOfCollision, t1, hypot, c1.x, rvel.x, raccel.x, c, cvel, caccel, collisionPoint, id1, id2))
                    {
                      if (trace)
                        libc_printf ((char *) "the point crosses the line, first time misses and second time hits\\n", 68);
                      return TRUE;
                    }
                }
              else
                {
                  if (checkPointCollision (timeOfCollision, t1, hypot, c1.x, rvel.x, raccel.x, c, cvel, caccel, collisionPoint, id1, id2))
                    {
                      if (trace)
                        libc_printf ((char *) "the point crosses the line first time in correct place\\n", 56);
                      return TRUE;
                    }
                  if (checkPointCollision (timeOfCollision, t0, hypot, c1.x, rvel.x, raccel.x, c, cvel, caccel, collisionPoint, id1, id2))
                    {
                      if (trace)
                        libc_printf ((char *) "the point crosses the line, first time misses and second time hits\\n", 68);
                      return TRUE;
                    }
                }
            }
    }
  if (trace)
    libc_printf ((char *) "this point and line should be discarded\\n", 41);
  return FALSE;
}


/*
   sortLine - orders points, p1 and, p2, according to their x value.
*/

static void sortLine (coord_Coord *p1, coord_Coord *p2)
{
  coord_Coord t;

  if ((*p1).x > (*p2).x)
    {
      t = (*p1);
      (*p1) = (*p2);
      (*p2) = t;
    }
  else if (((*p1).x == (*p2).x) && ((*p1).y > (*p2).y))
    {
      t = (*p1);
      (*p1) = (*p2);
      (*p2) = t;
    }
}

static void findEarlierCircleEdgeCollision (double *timeOfCollision, unsigned int cid, unsigned int pid, unsigned int lineP, unsigned int lineC, eventDesc *edesc, coord_Coord center, double radius, coord_Coord velCircle, coord_Coord accelCircle, coord_Coord p1, coord_Coord p2, coord_Coord velLine, coord_Coord accelLine, descP createDesc)
{
  coord_Coord v1;
  coord_Coord n1;
  coord_Coord d1;
  coord_Coord d2;
  coord_Coord p3;
  coord_Coord p4;
  coord_Coord p5;
  coord_Coord p6;
  coord_Coord collisonPoint;

  sortLine (&p1, &p2);
  v1 = coord_subCoord (p2, p1);
  coord_perpendiculars (v1, &d1, &d2);
  d1 = coord_scaleCoord (coord_normaliseCoord (d1), radius);
  d2 = coord_scaleCoord (coord_normaliseCoord (d2), radius);
  p3 = coord_addCoord (p1, d1);
  p4 = coord_addCoord (p1, d2);
  p5 = coord_addCoord (p2, d1);
  p6 = coord_addCoord (p2, d2);
  if (earlierPointLineCollision (timeOfCollision, center, velCircle, accelCircle, p3, p5, velLine, accelLine, &collisonPoint, cid, pid))
    {
      if (Debugging)
        libc_printf ((char *) "circle hits line (%g, %g) (%g, %g) in %g\\n", 42, p1.x, p1.y, p2.x, p2.y, (*timeOfCollision));
      (*edesc) = (*createDesc.proc) ((*edesc), cid, pid, lineP, lineC, (history_whereHit) history_corner, (history_whereHit) history_edge, collisonPoint);
      if (drawPrediction)
        {
          deviceIf_frameNote ();
          drawFrame ((eventQueue) NULL);
          debugCircle (center, 0.02, (deviceIf_Colour) deviceIf_white ());
          debugLine (p3, p5, (deviceIf_Colour) deviceIf_yellow ());
          debugCircle (collisonPoint, 0.02, (deviceIf_Colour) deviceIf_white ());
          deviceIf_flipBuffer ();
          GC_collectAll ();
        }
    }
  if (earlierPointLineCollision (timeOfCollision, center, velCircle, accelCircle, p4, p6, velLine, accelLine, &collisonPoint, cid, pid))
    {
      if (Debugging)
        libc_printf ((char *) "circle hits line (%g, %g) (%g, %g) in %g\\n", 42, p1.x, p1.y, p2.x, p2.y, (*timeOfCollision));
      (*edesc) = (*createDesc.proc) ((*edesc), cid, pid, lineP, lineC, (history_whereHit) history_corner, (history_whereHit) history_edge, collisonPoint);
      if (drawPrediction)
        {
          deviceIf_frameNote ();
          drawFrame ((eventQueue) NULL);
          debugCircle (center, 0.02, (deviceIf_Colour) deviceIf_white ());
          debugLine (p4, p6, (deviceIf_Colour) deviceIf_yellow ());
          debugCircle (collisonPoint, 0.02, (deviceIf_Colour) deviceIf_white ());
          deviceIf_flipBuffer ();
          GC_collectAll ();
        }
    }
}


/*
   getPolygonCoord -
*/

static coord_Coord getPolygonCoord (Object pPtr, unsigned int pointno)
{
  return checkZeroCoord (coord_addCoord (pPtr->p.cOfG, polar_polarToCoord (polar_rotatePolar ((polar_Polar) pPtr->p.points.array[pointno], pPtr->angleOrientation))));
}


/*
   getPolygonLine - assigns, p1, p2, with the, line, coordinates of polygon, pPtr.
*/

static void getPolygonLine (unsigned int line, Object pPtr, coord_Coord *c1, coord_Coord *c2)
{
  (*c1) = getPolygonCoord (pPtr, line-1);
  if (line == pPtr->p.nPoints)
    (*c2) = getPolygonCoord (pPtr, 0);
  else
    (*c2) = getPolygonCoord (pPtr, line);
}


/*
   findCollisionCircleLine - find the time (if any) between line number, lineP, in polygon, pPtr,
                             and the circle, cPtr.  cPtr can also be a polygon in which case lineC
                             is the particular line under question.  Line on line collision is broken
                             down into circle line calls which allows for code reuse.

                             Neither cPtr or pPtr are orbiting.
*/

static void findCollisionCircleLine (Object cPtr, Object pPtr, unsigned int lineP, unsigned int lineC, coord_Coord center, double radius, eventDesc *edesc, double *timeOfCollision, descP createDesc)
{
  coord_Coord velCircle;
  coord_Coord accelCircle;
  coord_Coord velLine;
  coord_Coord accelLine;
  coord_Coord p1;
  coord_Coord p2;
  coord_Coord cp;
  double cx;
  double cy;
  double r;
  double cvx;
  double cvy;
  double cax;
  double cay;
  double pvx;
  double pvy;
  double pax;
  double pay;
  double t;
  unsigned int cid;
  unsigned int pid;

  cid = cPtr->id;
  pid = pPtr->id;
  getPolygonLine (lineP, pPtr, &p1, &p2);
  getObjectValues (cPtr, &cvx, &cvy, &cax, &cay);
  getObjectValues (pPtr, &pvx, &pvy, &pax, &pay);
  if (earlierCircleCollision ((*edesc), cid, pid, &t, (*timeOfCollision), &cp, p1.x, center.x, pvx, cvx, pax, cax, p1.y, center.y, pvy, cvy, pay, cay, radius, 0.0))
    {
      if (Debugging)
        libc_printf ((char *) "circle hits corner at %g, %g  in %g\\n", 37, p1.x, p1.y, t);
      (*timeOfCollision) = t;
      (*edesc) = (*createDesc.proc) ((*edesc), cid, pid, lineP, lineC, (history_whereHit) history_corner, (history_whereHit) history_corner, p1);
      if (drawPrediction)
        {
          deviceIf_frameNote ();
          drawFrame ((eventQueue) NULL);
          debugCircle (center, 0.02, (deviceIf_Colour) deviceIf_white ());
          debugCircle (p1, 0.02, (deviceIf_Colour) deviceIf_white ());
          deviceIf_flipBuffer ();
          GC_collectAll ();
        }
    }
  if (earlierCircleCollision ((*edesc), cid, pid, &t, (*timeOfCollision), &cp, p2.x, center.x, pvx, cvx, pax, cax, p2.y, center.y, pvy, cvy, pay, cay, radius, 0.0))
    {
      if (Debugging)
        libc_printf ((char *) "circle hits corner at %g, %g  in %g  (lineP+1)\\n", 48, p2.x, p2.y, t);
      (*timeOfCollision) = t;
      (*edesc) = (*createDesc.proc) ((*edesc), cid, pid, lineP+1, lineC, (history_whereHit) history_corner, (history_whereHit) history_corner, p2);
      if (drawPrediction)
        {
          deviceIf_frameNote ();
          drawFrame ((eventQueue) NULL);
          debugCircle (cPtr->c.pos, 0.02, (deviceIf_Colour) deviceIf_white ());
          debugCircle (p2, 0.02, (deviceIf_Colour) deviceIf_white ());
          deviceIf_flipBuffer ();
          GC_collectAll ();
        }
    }
  velCircle = coord_initCoord (cvx, cvy);
  accelCircle = coord_initCoord (cax, cay);
  velLine = coord_initCoord (pvx, pvy);
  accelLine = coord_initCoord (pax, pay);
  findEarlierCircleEdgeCollision (timeOfCollision, cid, pid, lineP, lineC, edesc, center, radius, velCircle, accelCircle, p1, p2, velLine, accelLine, createDesc);
}


/*
   findCollisionCircleLineOrbiting - find the time (if any) between line number, lineP, in polygon, pPtr,
                                     and the circle, cPtr.  cPtr can also be a polygon in which case lineC
                                     is the particular line under question.  Line on line collision is broken
                                     down into circle line calls which allows for code reuse.

                                     Either cPtr or pPtr or both are orbiting.
*/

static void findCollisionCircleLineOrbiting (Object cPtr, Object pPtr, unsigned int lineP, unsigned int lineC, coord_Coord center, double radius, eventDesc *edesc, double *timeOfCollision, descP createDesc)
{
  double t;
  double cr;
  double cw;
  double pr;
  double pw;
  coord_Coord cv;
  coord_Coord ca;
  coord_Coord ccofg;
  coord_Coord pv;
  coord_Coord pa;
  coord_Coord pcofg;
  coord_Coord p1;
  coord_Coord p2;
  unsigned int cid;
  unsigned int pid;

  cid = cPtr->id;
  pid = pPtr->id;
  getPolygonLine (lineP, pPtr, &p1, &p2);
  getObjectValues (cPtr, &cv.x, &cv.y, &ca.x, &ca.y);
  getObjectValues (pPtr, &pv.x, &pv.y, &pa.x, &pa.y);
  getObjectOrbitingValues (cPtr, &cr, &cw, &ccofg);
  getObjectOrbitingValues (pPtr, &pr, &pw, &pcofg);
  if (earlierCircleCollisionOrbiting (&t, timeOfCollision, center, radius, cr, cw, ccofg, cv, ca, p1, 0.0, pr, pw, pcofg, pv, pa))
    {
      if (Debugging)
        libc_printf ((char *) "circle hits corner at %g, %g  in %g seconds\\n", 45, p1.x, p1.y, t);
      (*timeOfCollision) = t;
      (*edesc) = (*createDesc.proc) ((*edesc), cid, pid, lineP, lineC, (history_whereHit) history_corner, (history_whereHit) history_corner, p1);
      if (drawPrediction)
        {
          deviceIf_frameNote ();
          drawFrame ((eventQueue) NULL);
          debugCircle (center, 0.02, (deviceIf_Colour) deviceIf_white ());
          debugCircle (p1, 0.02, (deviceIf_Colour) deviceIf_white ());
          deviceIf_flipBuffer ();
          GC_collectAll ();
        }
    }
  if (earlierCircleCollisionOrbiting (&t, timeOfCollision, center, radius, cr, cw, ccofg, cv, ca, p2, 0.0, pr, pw, pcofg, pv, pa))
    {
      if (Debugging)
        libc_printf ((char *) "circle hits corner at %g, %g  in %g seconds  (lineP+1)\\n", 56, p2.x, p2.y, t);
      (*timeOfCollision) = t;
      (*edesc) = (*createDesc.proc) ((*edesc), cid, pid, lineP+1, lineC, (history_whereHit) history_corner, (history_whereHit) history_corner, p2);
      if (drawPrediction)
        {
          deviceIf_frameNote ();
          drawFrame ((eventQueue) NULL);
          debugCircle (cPtr->c.pos, 0.02, (deviceIf_Colour) deviceIf_white ());
          debugCircle (p2, 0.02, (deviceIf_Colour) deviceIf_white ());
          deviceIf_flipBuffer ();
          GC_collectAll ();
        }
    }
}


/*
   findCollisionCirclePolygon - find the smallest positive time (if any) between the polygon and circle.
                                If a collision if found then, tc, is assigned to the time and cid, pid
                                are set to the circle id and polygon id respectively.
*/

static void findCollisionCirclePolygon (Object cPtr, Object pPtr, eventDesc *edesc, double *tc)
{
  unsigned int i;

  Assert (cPtr->object == circleOb, 4404);
  Assert (pPtr->object == polygonOb, 4405);
  if (isOrbiting (pPtr))
    for (i=1; i<=pPtr->p.nPoints; i++)
      findCollisionCircleLineOrbiting (cPtr, pPtr, i, 0, cPtr->c.pos, cPtr->c.r, edesc, tc, (descP) {(descP_t) makeCirclesPolygonDesc});
  else
    for (i=1; i<=pPtr->p.nPoints; i++)
      findCollisionCircleLine (cPtr, pPtr, i, 0, cPtr->c.pos, cPtr->c.r, edesc, tc, (descP) {(descP_t) makeCirclesPolygonDesc});
}


/*
   makePolygonPolygonDesc - return a new eventDesc indicating that we have a polygon/polygon collision
                            event.
*/

static eventDesc makePolygonPolygon (eventDesc edesc, unsigned int id1, unsigned int id2, unsigned int lineCorner1, unsigned int lineCorner2, history_whereHit wpid1, history_whereHit wpid2, coord_Coord collisionPoint)
{
  if (edesc == NULL)
    edesc = newDesc ();
  edesc->etype = polygonPolygonEvent;
  edesc->pp.cPoint = collisionPoint;
  edesc->pp.pid1 = id1;
  edesc->pp.pid2 = id2;
  edesc->pp.wpid1 = wpid1;
  edesc->pp.wpid2 = wpid2;
  edesc->pp.lineCorner1 = lineCorner1;
  edesc->pp.lineCorner2 = lineCorner2;
  return edesc;
}


/*
   isOrbiting - return TRUE if object, o, is rotating.
*/

static unsigned int isOrbiting (Object o)
{
  return ! (roots_nearZero (o->angularVelocity));
}


/*
   findCollisionLineLine - find the smallest time in the future when two lines collide.
                           The event descriptor, edesc, will contain the description of the collision
                           and, tc, the time of collision in the future.
*/

static void findCollisionLineLine (Object iPtr, Object jPtr, unsigned int iLine, unsigned int jLine, eventDesc *edesc, double *tc)
{
  if ((isOrbiting (iPtr)) || (isOrbiting (jPtr)))
    findCollisionLineLineOrbiting (iPtr, jPtr, iLine, jLine, edesc, tc);
  else
    findCollisionLineLineNonOrbiting (iPtr, jPtr, iLine, jLine, edesc, tc);
}


/*
   findCollisionLineLine - find the smallest time in the future when two lines collide.
                           The event descriptor, edesc, will contain the description of the collision
                           and, tc, the time of collision in the future.
*/

static void findCollisionLineLineOrbiting (Object iPtr, Object jPtr, unsigned int iLine, unsigned int jLine, eventDesc *edesc, double *tc)
{
  coord_Coord i0;
  coord_Coord i1;
  coord_Coord j0;
  coord_Coord j1;

  getPolygonLine (iLine, iPtr, &i0, &i1);
  getPolygonLine (jLine, jPtr, &j0, &j1);
  findCollisionCircleLineOrbiting (iPtr, jPtr, iLine, jLine, i0, 0.0, edesc, tc, (descP) {(descP_t) makePolygonPolygon});
  findCollisionCircleLineOrbiting (iPtr, jPtr, iLine, jLine, i1, 0.0, edesc, tc, (descP) {(descP_t) makePolygonPolygon});
  findCollisionCircleLineOrbiting (jPtr, iPtr, iLine, jLine, j0, 0.0, edesc, tc, (descP) {(descP_t) makePolygonPolygon});
  findCollisionCircleLineOrbiting (jPtr, iPtr, iLine, jLine, j1, 0.0, edesc, tc, (descP) {(descP_t) makePolygonPolygon});
}

static void findCollisionLineLineNonOrbiting (Object iPtr, Object jPtr, unsigned int iLine, unsigned int jLine, eventDesc *edesc, double *tc)
{
  coord_Coord i0;
  coord_Coord i1;
  coord_Coord j0;
  coord_Coord j1;

  getPolygonLine (iLine, iPtr, &i0, &i1);
  getPolygonLine (jLine, jPtr, &j0, &j1);
  findCollisionCircleLine (iPtr, jPtr, iLine, jLine, i0, 0.0, edesc, tc, (descP) {(descP_t) makePolygonPolygon});
  findCollisionCircleLine (iPtr, jPtr, iLine, jLine, i1, 0.0, edesc, tc, (descP) {(descP_t) makePolygonPolygon});
  findCollisionCircleLine (jPtr, iPtr, iLine, jLine, j0, 0.0, edesc, tc, (descP) {(descP_t) makePolygonPolygon});
  findCollisionCircleLine (jPtr, iPtr, iLine, jLine, j1, 0.0, edesc, tc, (descP) {(descP_t) makePolygonPolygon});
}


/*
   Abs - return the absolute value of, r.
*/

static double Abs (double r)
{
  if (r < 0.0)
    return -r;
  else
    return r;
}


/*
   findAllTimesOfCollisionRLineRPoint -
                                                       4         4   4
                                             - ((16 j k  - 16 d e ) t

                                                       3               3         3               3   3
                                              + (64 j k  l - 32 %pi j k  - 64 d e  f + 32 %pi d e ) t

                                                       2  2             2            2          2                2  2
                                              + (96 j k  l  - 96 %pi j k  l + (24 %pi  - 32) j k  + 32 i - 96 d e  f

                                                          2                 2     2          2
                                              + 96 %pi d e  f + (32 - 24 %pi ) d e  - 32 c) t

                                                         3               2          2                              3
                                              + (64 j k l  - 96 %pi j k l  + (48 %pi  - 64) j k l + (32 %pi - 8 %pi ) j k

                                                               3               2               2
                                              + 64 h - 64 d e f  + 96 %pi d e f  + (64 - 48 %pi ) d e f

                                                      3                                 4             3
                                              + (8 %pi  - 32 %pi) d e - 64 b) t + 16 j l  - 32 %pi j l

                                                       2          2                  3            4        2
                                              + (24 %pi  - 32) j l  + (32 %pi - 8 %pi ) j l + (%pi  - 8 %pi  + 64) j + 64 g

                                                      4             3               2     2         3
                                              - 16 d f  + 32 %pi d f  + (32 - 24 %pi ) d f  + (8 %pi  - 32 %pi) d f

                                                      4        2
                                              + (- %pi  + 8 %pi  - 64) d - 64 a)/64 = 0
*/

static unsigned int findAllTimesOfCollisionRLineRPoint (double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double *t, unsigned int _t_high)
{
  double A;
  double B;
  double C;
  double D;
  double E;

  A = ((16.0*j)*(quad (k)))-((16.0*d)*(quad (e)));
  B = (((((64.0*j)*(cub (k)))*l)-(((32.0*MathLib0_pi)*j)*(cub (k))))-(((64.0*d)*(cub (e)))*f))+(((32.0*MathLib0_pi)*d)*(cub (e)));
  C = (((((((((96.0*j)*(sqr (k)))*(sqr (l)))-((((96.0*MathLib0_pi)*j)*(sqr (k)))*l))+((((24.0*(sqr (MathLib0_pi)))-32.0)*j)*(sqr (k))))+(32.0*i))-(((96.0*d)*(sqr (e)))*(sqr (f))))+((((96.0*MathLib0_pi)*d)*(sqr (e)))*f))+(((32.0-(24.0*(sqr (MathLib0_pi))))*d)*(sqr (e))))-(32.0*c);
  D = (((((((((((64.0*j)*k)*(cub (l)))-((((96.0*MathLib0_pi)*j)*k)*(sqr (l))))+(((((48.0*(sqr (MathLib0_pi)))-64.0)*j)*k)*l))+((((32.0*MathLib0_pi)-(8.0*(sqr (MathLib0_pi))))*j)*k))+(64.0*h))-(((64.0*d)*e)*(cub (f))))+((((96.0*MathLib0_pi)*d)*e)*(sqr (f))))+((((64.0-(48.0*(sqr (MathLib0_pi))))*d)*e)*f))+((((8.0*(cub (MathLib0_pi)))-(32.0*MathLib0_pi))*d)*e))-(64.0*b);
  E = ((((((((((((16.0*j)*(quad (l)))-(((32.0*MathLib0_pi)*j)*(cub (l))))+((((24.0*(sqr (MathLib0_pi)))-32.0)*j)*(sqr (l))))+((((32.0*MathLib0_pi)-(8.0*(cub (MathLib0_pi))))*j)*l))+((((cub (MathLib0_pi))-(8.0*(sqr (MathLib0_pi))))+64.0)*j))+(64.0*g))-((16.0*d)*(quad (f))))+(((32.0*MathLib0_pi)*d)*(cub (f))))+(((32.0-(24.0*(sqr (MathLib0_pi))))*d)*(sqr (f))))+((((8.0*(cub (MathLib0_pi)))-(32.0*MathLib0_pi))*d)*f))+((((-(quad (MathLib0_pi)))+(8.0*(sqr (MathLib0_pi))))-64.0)*d))-(64.0*a);
  return roots_findAllRootsQuartic (A, B, C, D, E, (double *) t, _t_high);
}


/*
   findEarliestCollisionRLineRPoint - find the earliest time when rotating point, j, collides with rotating line, i.
*/

static void findEarliestCollisionRLineRPoint (Object iPtr, Object jPtr, unsigned int i, unsigned int j, eventDesc *edesc, double *tc, double si, double ui, double ai, double ri, double wi, double oi, double sj, double uj, double aj, double rj, double wj, double oj, coord_Coord p1, coord_Coord p2)
{
  typedef struct _T14_a _T14;

  struct _T14_a { double array[3+1]; };
  _T14 t;
  unsigned int k;
  unsigned int n;
  double l;

}


/*
   findCollisionLineRPoint -
*/

static void findCollisionLineRPoint (Object iPtr, Object rPtr, unsigned int i, unsigned int j, eventDesc *edesc, double *tc)
{
  polar_Polar jp;
  polar_Polar pol1;
  polar_Polar pol2;
  double o;
  double offset;
  double jw;
  double iw;
  coord_Coord jpos;
  coord_Coord p1;
  coord_Coord p2;
  coord_Coord iu;
  coord_Coord ia;
  coord_Coord ju;
  coord_Coord ja;
  coord_Coord rcofg;

  findEarliestCollisionRLineRPoint (iPtr, rPtr, i, j, edesc, tc, p1.y, iu.y, ia.y, offset, iw, o, jpos.y, ju.y, ja.y, jp.r, jw, jp.w, p1, p2);
}


/*
   findCollisionLineRLine - find the time of collision between line, iPtr, and rotating line, rPtr.
*/

static void findCollisionLineRLine (Object iPtr, Object rPtr, unsigned int i, unsigned int j, eventDesc *edesc, double *tc)
{
  findCollisionLineRPoint (iPtr, rPtr, i, j-1, edesc, tc);
  findCollisionLineRPoint (iPtr, rPtr, i, j, edesc, tc);
  findCollisionLineRPoint (rPtr, iPtr, j, i-1, edesc, tc);
  findCollisionLineRPoint (rPtr, iPtr, j, i, edesc, tc);
}


/*
   findCollisionPolygonPolygon - find the smallest positive time (if any) between the polygons, iPtr
                                 and jPtr colliding.
                                 If a collision if found then, tc, is assigned to the time and the
                                 event descriptor is filled in.
*/

static void findCollisionPolygonPolygon (Object iPtr, Object jPtr, eventDesc *edesc, double *tc)
{
  unsigned int i;
  unsigned int j;

  Assert (iPtr != jPtr, 4719);
  i = 1;
  while (i <= iPtr->p.nPoints)
    {
      j = 1;
      while (j <= jPtr->p.nPoints)
        {
          findCollisionLineLine (iPtr, jPtr, i, j, edesc, tc);
          j += 1;
        }
      i += 1;
    }
}


/*
   findCollisionPolygonRPolygon - find the smallest positive time (if any) between the polygons, iPtr
                                  and rPtr colliding.
                                  rPtr is a rotating polygon and iPtr is not rotating.
                                  If a collision if found then, tc, is assigned to the time and the
                                  event descriptor is filled in.
                                  We check possible collision times between all lines of both polygons,
                                  we separate out the rotating polygon from non rotating polygon
                                  as the collision equations only generate a polynomial order 4 rather
                                  than order 8 if both are rotating.
*/

static void findCollisionPolygonRPolygon (Object iPtr, Object rPtr, eventDesc *edesc, double *tc)
{
  unsigned int i;
  unsigned int j;

}


/*
   findCollision -
*/

static void findCollision (Object iptr, Object jptr, eventDesc *edesc, double *tc)
{
  if (trace)
    libc_printf ((char *) "findCollision entered and best time is %g\\n", 43, (*tc));
  if (! (iptr->fixed && jptr->fixed))
    {
      /* avoid gcc warning by using compound statement even if not strictly necessary.  */
      if ((iptr->object == circleOb) && (jptr->object == circleOb))
        {
          findCollisionCircles (iptr, jptr, edesc, tc);
          if (trace)
            libc_printf ((char *) "findCollision (circles) best time is %g\\n", 41, (*tc));
        }
      else if ((iptr->object == circleOb) && (jptr->object == polygonOb))
        findCollisionCirclePolygon (iptr, jptr, edesc, tc);
      else if ((iptr->object == polygonOb) && (jptr->object == circleOb))
        findCollisionCirclePolygon (jptr, iptr, edesc, tc);
      else if ((iptr->object == polygonOb) && (jptr->object == polygonOb))
        findCollisionPolygonPolygon (jptr, iptr, edesc, tc);
    }
  if (trace)
    libc_printf ((char *) "findCollision exiting and best time is %g\\n", 43, (*tc));
}


/*
   debugFrame - debug frame at time, e.
*/

static void debugFrame (eventQueue e)
{
  drawBackground ((deviceIf_Colour) deviceIf_yellow ());
  drawFrame ((eventQueue) NULL);
}


/*
   addDebugging - add a debugging event at time, t.
*/

static void addDebugging (double t, eventDesc edesc)
{
  eventQueue e;

  e = newEvent ();
  e->time = t;
  e->p.proc = debugFrame;
  e->ePtr = edesc;
  e->next = NULL;
  addRelative (e);
}


/*
   anticipateCollision - stores the collision in the anticipated list.
*/

static void anticipateCollision (double tc, eventDesc edesc)
{
  switch (edesc->etype)
    {
      case circlesEvent:
        history_anticipate (currentTime+tc, edesc->cc.cid1, edesc->cc.cid2, edesc->cc.cPoint);
        break;

      case circlePolygonEvent:
        history_anticipate (currentTime+tc, edesc->cp.pid, edesc->cp.cid, edesc->cp.cPoint);
        break;

      case polygonPolygonEvent:
        history_anticipate (currentTime+tc, edesc->pp.pid1, edesc->pp.pid2, edesc->pp.cPoint);
        break;


      default:
        CaseException ("..//twoDsim.def", 2, 1);
    }
}


/*
   collisionOccurred - stores the collision in the history list.
*/

static void collisionOccurred (eventDesc edesc)
{
  switch (edesc->etype)
    {
      case circlesEvent:
        history_occurred (currentTime, edesc->cc.cid1, edesc->cc.cid2, edesc->cc.cPoint);
        break;

      case circlePolygonEvent:
        history_occurred (currentTime, edesc->cp.pid, edesc->cp.cid, edesc->cp.cPoint);
        break;

      case polygonPolygonEvent:
        history_occurred (currentTime, edesc->pp.pid1, edesc->pp.pid2, edesc->pp.cPoint);
        break;


      default:
        CaseException ("..//twoDsim.def", 2, 1);
    }
}


/*
   subEvent - remove event, e, from the relative time ordered event queue.
*/

static void subEvent (eventQueue e)
{
  eventQueue before;
  eventQueue f;

  f = eventQ;
  before = NULL;
  while ((f != e) && (f != NULL))
    {
      before = f;
      f = f->next;
    }
  if (f != NULL)
    {
      Assert (f == e, 4882);
      if (before == NULL)
        {
          Assert (eventQ == f, 4885);
          Assert (eventQ == e, 4886);
          eventQ = eventQ->next;
          if (eventQ != NULL)
            eventQ->time = eventQ->time+e->time;
        }
      else
        {
          before->next = e->next;
          if (e->next != NULL)
            e->next->time = e->next->time+e->time;
        }
      disposeEvent (e);
    }
}


/*
   removeCollisionEvent -
*/

static void removeCollisionEvent (void)
{
  eventQueue e;

  e = eventQ;
  while (e != NULL)
    if (e->kind == collisionKind)
      {
        subEvent (e);
        return;
      }
    else
      e = e->next;
}


/*
   addNextCollisionEvent -
*/

static void addNextCollisionEvent (void)
{
  double tc;
  double old;
  unsigned int ic;
  unsigned int jc;
  unsigned int i;
  unsigned int j;
  unsigned int n;
  Object iptr;
  Object jptr;
  eventDesc edesc;

  removeCollisionEvent ();
  n = Indexing_HighIndice (objects);
  i = 1;
  edesc = NULL;
  tc = -1.0;
  while (i <= n)
    {
      iptr = Indexing_GetIndice (objects, i);
      if (objectExists (iptr))
        {
          j = i+1;
          while (j <= n)
            {
              jptr = Indexing_GetIndice (objects, j);
              if ((iptr != jptr) && (objectExists (jptr)))
                {
                  if (trace)
                    {
                      libc_printf ((char *) "** checking pair %d, %d\\n", 25, iptr->id, jptr->id);
                      old = tc;
                    }
                  findCollision (iptr, jptr, &edesc, &tc);
                  if (trace && (old != tc))
                    libc_printf ((char *) "** collision found between pair %d, %d at time %g\\n", 51, iptr->id, jptr->id, tc);
                }
              j += 1;
            }
        }
      i += 1;
    }
  if (edesc != NULL)
    {
      addCollisionEvent (tc, (eventProc) {(eventProc_t) doCollision}, edesc);
      anticipateCollision (tc, edesc);
    }
  else
    libc_printf ((char *) "no more collisions found\\n", 26);
}


/*
   skipFor - skip displaying any frames for, t, simulated seconds.
*/

static void skipFor (double t)
{
  twoDsim_simulateFor (t);
}


/*
   resetQueue -
*/

static void resetQueue (void)
{
  eventQueue c;
  eventQueue f;
  eventQueue e;

  c = NULL;
  f = NULL;
  e = eventQ;
  while ((e != NULL) && ((c == NULL) || (f == NULL)))
    {
      if (e->kind == collisionKind)
        c = e;
      else if (e->kind == frameKind)
        f = e;
      e = e->next;
    }
  if (f == NULL)
    addEvent ((eventKind) frameKind, (1.0/framesPerSecond)-(currentTime-lastDrawTime), (eventProc) {(eventProc_t) drawFrameEvent});
  if (c == NULL)
    addNextCollisionEvent ();
}


/*
   disposeEvent - returns the event to the free queue.
*/

static void disposeEvent (eventQueue e)
{
  disposeDesc (&e->ePtr);
  e->next = freeEvents;
  freeEvents = e;
}


/*
   disposeDesc - returns the event desc to the free queue.
*/

static void disposeDesc (eventDesc *d)
{
  if ((*d) != NULL)
    {
      (*d)->next = freeDesc;
      freeDesc = (*d);
      (*d) = NULL;
    }
}


/*
   newDesc - returns a new eventDesc.
*/

static eventDesc newDesc (void)
{
  eventDesc e;

  if (freeDesc == NULL)
    Storage_ALLOCATE ((void **) &e, sizeof (_T1));
  else
    {
      e = freeDesc;
      freeDesc = freeDesc->next;
    }
  return e;
}


/*
   newEvent - returns a new eventQueue.
*/

static eventQueue newEvent (void)
{
  eventQueue e;

  if (freeEvents == NULL)
    Storage_ALLOCATE ((void **) &e, sizeof (_T4));
  else
    {
      e = freeEvents;
      freeEvents = freeEvents->next;
    }
  e->ePtr = NULL;
  return e;
}


/*
   makeCirclesDesc - return a eventDesc which describes two circles colliding.
*/

static eventDesc makeCirclesDesc (eventDesc *edesc, unsigned int cid1, unsigned int cid2, coord_Coord cp)
{
  if ((*edesc) == NULL)
    (*edesc) = newDesc ();
  (*edesc)->etype = circlesEvent;
  (*edesc)->cc.cPoint = cp;
  (*edesc)->cc.cid1 = cid1;
  (*edesc)->cc.cid2 = cid2;
  return (*edesc);
}


/*
   addRelative - adds event, e, into the relative event queue.
*/

static void addRelative (eventQueue e)
{
  eventQueue before;
  eventQueue after;

  if (Debugging)
    {
      libc_printf ((char *) "addRelative entered, event abs time = %g\\n", 42, e->time);
      printQueue ();
    }
  if (eventQ == NULL)
    eventQ = e;
  else if (e->time < eventQ->time)
    {
      eventQ->time = eventQ->time-e->time;
      e->next = eventQ;
      eventQ = e;
    }
  else
    {
      if (Debugging)
        printQueue ();
      before = eventQ;
      after = eventQ->next;
      e->time = e->time-before->time;
      while ((after != NULL) && (after->time < e->time))
        {
          before = after;
          e->time = e->time-before->time;
          after = after->next;
        }
      if (after != NULL)
        after->time = after->time-e->time;
      before->next = e;
      e->next = after;
    }
  if (Debugging)
    {
      libc_printf ((char *) "addRelative changed queue to:\\n", 31);
      printQueue ();
      libc_printf ((char *) "addRelative finishing now\\n", 27);
    }
}


/*
   addEvent - adds an event which has no collision associated with it.
              Typically this is a debugging event or display frame event.
*/

static void addEvent (eventKind k, double t, eventProc dop)
{
  eventQueue e;

  if (Debugging)
    libc_printf ((char *) "new event will occur at time %g in the future\\n", 47, t);
  Assert (t >= 0.0, 5194);
  e = newEvent ();
  e->kind = k;
  e->time = t;
  e->p = dop;
  e->ePtr = NULL;
  e->next = NULL;
  addRelative (e);
}


/*
   addCollisionEvent - adds a collision event, the edesc is attached to the,
                       eventQueue, which is placed onto the eventQ.
*/

static void addCollisionEvent (double t, eventProc dop, eventDesc edesc)
{
  eventQueue e;

  if (Debugging)
    libc_printf ((char *) "collision will occur in %g simulated seconds\\n", 46, t);
  Assert (t >= 0.0, 5220);
  e = newEvent ();
  e->kind = collisionKind;
  e->time = t;
  e->p = dop;
  e->ePtr = edesc;
  e->next = NULL;
  if (Debugging)
    {
      libc_printf ((char *) "collision about to be added to this queue\\n", 43, t);
      printQueue ();
      libc_printf ((char *) "collision about to be added to this queue\\n", 43, t);
    }
  addRelative (e);
  if (Debugging)
    {
      libc_printf ((char *) "collision now added to this queue\\n", 35, t);
      printQueue ();
    }
}


/*
   isEvent - return TRUE if the next event is of kind, k.
*/

static unsigned int isEvent (eventKind k)
{
  if (eventQ == NULL)
    return FALSE;
  else
    return eventQ->kind == k;
}


/*
   dumpTime -
*/

static void dumpTime (void)
{
  libc_printf ((char *) "  absolute time is %f\\n", 23, currentTime);
  libc_printf ((char *) "  last update time is %f\\n", 26, lastUpdateTime);
}


/*
   recordEvent -
*/

static void recordEvent (void)
{
  checkOpened ();
  if (eventQ != NULL)
    {
      if (DebugTrace)
        libc_printf ((char *) "before writeEvent\\n", 19);
      writeEvent (eventQ);
      if (DebugTrace)
        libc_printf ((char *) "after writeEvent\\n", 18);
    }
}


/*
   pumpQueue - prime the event queue with initial frame and collision events.
*/

static void pumpQueue (void)
{
  resetQueue ();
  recordEvent ();
}


/*
   up - recreate the event queue.
        The pair up/down must be used to shutdown
        the event queue if the world is to be altered.
*/

static void up (void)
{
  history_forgetFuture ();
  resetQueue ();
  if (DebugTrace)
    {
      libc_printf ((char *) "exiting up\\n", 12);
      printQueue ();
      libc_printf ((char *) "remaking queue\\n", 16);
      removeCollisionEvent ();
      libc_printf ((char *) "collision event removed\\n", 25);
      printQueue ();
      libc_printf ((char *) "collision event added\\n", 23);
      resetQueue ();
      printQueue ();
      libc_printf ((char *) "and again (collision event added)\\n", 35);
      removeCollisionEvent ();
      resetQueue ();
      printQueue ();
      libc_printf ((char *) "exiting finishing\\n", 19);
    }
}


/*
   down - shutdown the event queue.
*/

static void down (void)
{
  if (DebugTrace)
    {
      libc_printf ((char *) "entered down\\n", 14);
      printQueue ();
    }
  updatePhysics ();
  removeCollisionEvent ();
}


/*
   killQueue - destroys the event queue and returns events to the free list.
*/

static void killQueue (void)
{
  eventQueue e;

  if (eventQ != NULL)
    {
      e = eventQ;
      while (e->next != NULL)
        e = e->next;
      e->next = freeEvents;
      freeEvents = eventQ;
      eventQ = NULL;
    }
}


/*
   writeCircles -
*/

static void writeCircles (cDesc c)
{
  if (DebugTrace)
    libc_printf ((char *) "writeCircleCircle %d %d\\n", 25, c.cid1, c.cid2);
  NetworkOrder_writeCoord (file, c.cPoint);
  NetworkOrder_writeCard (file, c.cid1);
  NetworkOrder_writeCard (file, c.cid2);
}


/*
   writeKind -
*/

static void writeKind (history_whereHit k)
{
  NetworkOrder_writeCard (file, (unsigned int) (k));
}


/*
   writeCirclePolygon -
*/

static void writeCirclePolygon (cpDesc c)
{
  if (DebugTrace)
    libc_printf ((char *) "writeCirclePolygon %d %d\\n", 26, c.pid, c.cid);
  NetworkOrder_writeCoord (file, c.cPoint);
  NetworkOrder_writeCard (file, c.pid);
  NetworkOrder_writeCard (file, c.cid);
  writeKind (c.wpid);
}


/*
   writePolygonPolygon -
*/

static void writePolygonPolygon (ppDesc p)
{
  if (DebugTrace)
    libc_printf ((char *) "writePolygonPolygon %d %d\\n", 27, p.pid1, p.pid2);
  NetworkOrder_writeCoord (file, p.cPoint);
  NetworkOrder_writeCard (file, p.pid1);
  NetworkOrder_writeCard (file, p.pid2);
  writeKind (p.wpid1);
  writeKind (p.wpid2);
}


/*
   writeFunction -
*/

static void writeFunction (fcDesc fc)
{
  NetworkOrder_writeCard (file, fc.id);
}


/*
   writeDesc -
*/

static void writeDesc (eventDesc p)
{
  if (p == NULL)
    NetworkOrder_writeCard (file, (unsigned int) (frameEvent));
  else
    {
      NetworkOrder_writeCard (file, (unsigned int) (p->etype));
      switch (p->etype)
        {
          case frameEvent:
            break;

          case circlesEvent:
            writeCircles (p->cc);
            break;

          case circlePolygonEvent:
            writeCirclePolygon (p->cp);
            break;

          case polygonPolygonEvent:
            writePolygonPolygon (p->pp);
            break;

          case functionEvent:
            writeFunction (p->fc);
            break;


          default:
            CaseException ("..//twoDsim.def", 2, 1);
        }
    }
}


/*
   writeEvent - writes the first event to the file.
*/

static void writeEvent (eventQueue e)
{
  MemStream_Rewrite (file);
  if (DebugTrace)
    {
      libc_printf ((char *) "time of next event in twoDsim is %g\\n", 37, e->time);
      displayEvent (e);
    }
  if (DebugTrace)
    libc_printf ((char *) "check time is %g\\n", 18, e->time);
  NetworkOrder_writeReal (file, e->time);
  writeDesc (e->ePtr);
}


/*
   memDump -
*/

static void memDump (void * a, unsigned int len)
{
  unsigned int i;
  unsigned int j;
  unsigned char * p;

  p = a;
  j = 0;
  for (i=0; i<=len; i++)
    {
      if ((j % 16) == 0)
        libc_printf ((char *) "\\n%p  %02x", 10, p, (unsigned int ) ((*p)));
      else
        libc_printf ((char *) " %02x", 5, (unsigned int ) ((*p)));
      p += 1;
      j += 1;
    }
  libc_printf ((char *) "\\n", 2);
}


/*
   checkOpened - checks to see of the MemStream file has been created and if not then
                 it is opened.
*/

static void checkOpened (void)
{
  ChanConsts_OpenResults res;

  if (! fileOpened)
    {
      fileOpened = TRUE;
      MemStream_OpenWrite (&file, ChanConsts_write|ChanConsts_raw, &res, &bufferStart, &bufferLength, &bufferUsed, TRUE);
      if (res != ChanConsts_opened)
        {
          libc_printf ((char *) "twoDsim.checkOpened: something went wrong when trying to open the memstream file (res = %d)\\n", 93, res);
          libc_exit (1);
        }
    }
}


/*
   Init -
*/

static void Init (void)
{
  trace = DebugTrace;
  roots_setTrace (trace);
  maxId = 0;
  objects = Indexing_InitIndex (1);
  framesPerSecond = DefaultFramesPerSecond;
  replayPerSecond = 0.0;
  simulatedGravity = 0.0;
  eventQ = NULL;
  freeEvents = NULL;
  freeDesc = NULL;
  currentTime = 0.0;
  lastUpdateTime = 0.0;
  lastDrawTime = 0.0;
  drawCollisionFrame = FALSE;
  drawPrediction = FALSE;
  fileOpened = FALSE;
  writeTimeDelay = TRUE;
  haveCollisionColour = FALSE;
}


/*
   gravity - turn on gravity at: g m^2
*/

void twoDsim_gravity (double g)
{
  simulatedGravity = g;
}


/*
   box - place a box in the world at (x0,y0), (x0+i,y0),
         (x0+i, y0+j), (x0, y0+j).
*/

unsigned int twoDsim_box (double x0, double y0, double i, double j, deviceIf_Colour colour)
{
  return twoDsim_poly4 (x0, y0, x0+i, y0, x0+i, y0+j, x0, y0+j, colour);
}


/*
   poly3 - place a triangle in the world at:
           (x0,y0), (x1,y1), (x2,y2)
*/

unsigned int twoDsim_poly3 (double x0, double y0, double x1, double y1, double x2, double y2, deviceIf_Colour colour)
{
  typedef struct _T15_a _T15;

  struct _T15_a { coord_Coord array[2+1]; };
  unsigned int id;
  unsigned int i;
  Object optr;
  _T15 co;

  if (Debugging)
    libc_printf ((char *) "begin poly3 (%g, %g, %g, %g, %g, %g)\\n", 38, x0, y0, x1, y1, x2, y2);
  id = newObject ((ObjectType) polygonOb);
  optr = Indexing_GetIndice (objects, id);
  co.array[0] = coord_initCoord (x0, y0);
  co.array[1] = coord_initCoord (x1, y1);
  co.array[2] = coord_initCoord (x2, y2);
  optr->p.nPoints = 3;
  optr->p.cOfG = calculateCofG (optr->p.nPoints, (coord_Coord *) &co.array[0], 2);
  for (i=0; i<=optr->p.nPoints-1; i++)
    optr->p.points.array[i] = polar_coordToPolar (coord_subCoord ((coord_Coord) co.array[i], optr->p.cOfG));
  optr->p.col = colour;
  optr->p.mass = 0.0;
  if (Debugging)
    {
      libc_printf ((char *) "end poly3\\n", 11);
      twoDsim_dumpWorld ();
    }
  return id;
}


/*
   poly4 - place a quadrangle in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3)  the points must be in order,
           either anticlockwise or clockwise.
*/

unsigned int twoDsim_poly4 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, deviceIf_Colour colour)
{
  typedef struct _T16_a _T16;

  struct _T16_a { coord_Coord array[3+1]; };
  unsigned int id;
  unsigned int i;
  Object optr;
  _T16 co;

  id = newObject ((ObjectType) polygonOb);
  optr = Indexing_GetIndice (objects, id);
  co.array[0] = coord_initCoord (x0, y0);
  co.array[1] = coord_initCoord (x1, y1);
  co.array[2] = coord_initCoord (x2, y2);
  co.array[3] = coord_initCoord (x3, y3);
  optr->p.nPoints = 4;
  optr->p.cOfG = calculateCofG (optr->p.nPoints, (coord_Coord *) &co.array[0], 3);
  for (i=0; i<=optr->p.nPoints-1; i++)
    optr->p.points.array[i] = polar_coordToPolar (coord_subCoord ((coord_Coord) co.array[i], optr->p.cOfG));
  optr->p.col = colour;
  optr->p.mass = 0.0;
  return id;
}


/*
   poly5 - place a pentagon in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3), (x4,y4)
           the points must be in order, either anticlockwise or clockwise.
*/

unsigned int twoDsim_poly5 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, deviceIf_Colour colour)
{
  typedef struct _T17_a _T17;

  struct _T17_a { coord_Coord array[4+1]; };
  unsigned int id;
  unsigned int i;
  Object optr;
  _T17 co;

  id = newObject ((ObjectType) polygonOb);
  optr = Indexing_GetIndice (objects, id);
  co.array[0] = coord_initCoord (x0, y0);
  co.array[1] = coord_initCoord (x1, y1);
  co.array[2] = coord_initCoord (x2, y2);
  co.array[3] = coord_initCoord (x3, y3);
  co.array[4] = coord_initCoord (x4, y4);
  optr->p.nPoints = 5;
  optr->p.cOfG = calculateCofG (optr->p.nPoints, (coord_Coord *) &co.array[0], 4);
  for (i=0; i<=optr->p.nPoints-1; i++)
    optr->p.points.array[i] = polar_coordToPolar (coord_subCoord ((coord_Coord) co.array[i], optr->p.cOfG));
  optr->p.col = colour;
  optr->p.mass = 0.0;
  return id;
}


/*
   poly6 - place a hexagon in the world at:
           (x0,y0), (x1,y1), (x2,y2), (x3,y3), (x4,y4), (x5,y5)
           the points must be in order, either anticlockwise or clockwise.
*/

unsigned int twoDsim_poly6 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, deviceIf_Colour colour)
{
  typedef struct _T18_a _T18;

  struct _T18_a { coord_Coord array[5+1]; };
  unsigned int id;
  unsigned int i;
  Object optr;
  _T18 co;

  id = newObject ((ObjectType) polygonOb);
  optr = Indexing_GetIndice (objects, id);
  co.array[0] = coord_initCoord (x0, y0);
  co.array[1] = coord_initCoord (x1, y1);
  co.array[2] = coord_initCoord (x2, y2);
  co.array[3] = coord_initCoord (x3, y3);
  co.array[4] = coord_initCoord (x4, y4);
  co.array[5] = coord_initCoord (x5, y5);
  optr->p.nPoints = 6;
  optr->p.cOfG = calculateCofG (optr->p.nPoints, (coord_Coord *) &co.array[0], 5);
  for (i=0; i<=optr->p.nPoints-1; i++)
    optr->p.points.array[i] = polar_coordToPolar (coord_subCoord ((coord_Coord) co.array[i], optr->p.cOfG));
  optr->p.col = colour;
  optr->p.mass = 0.0;
  return id;
}


/*
   get_xpos - returns the x coordinate of the center of gravity of object, id.
*/

double twoDsim_get_xpos (unsigned int id)
{
  double dt;
  Object optr;

  updatePhysics ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  switch (optr->object)
    {
      case polygonOb:
        return optr->p.cOfG.x;
        break;

      case circleOb:
        return optr->c.pos.x;
        break;


      default:
        libc_printf ((char *) "get_xpos: only expecting polygon\\n", 34);
        M2RTS_HALT (0);
        break;
    }
}


/*
   get_ypos - returns the first point, y, coordinate of object.
*/

double twoDsim_get_ypos (unsigned int id)
{
  double dt;
  Object optr;

  updatePhysics ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  switch (optr->object)
    {
      case polygonOb:
        return optr->p.cOfG.y;
        break;

      case circleOb:
        return optr->c.pos.y;
        break;


      default:
        libc_printf ((char *) "get_ypos: only expecting polygon\\n", 34);
        M2RTS_HALT (0);
        break;
    }
}


/*
   get_xvel - returns the x velocity of object.
*/

double twoDsim_get_xvel (unsigned int id)
{
  Object optr;

  if (trace)
    libc_printf ((char *) "get_xvel for object %d\\n", 24, id);
  down ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  checkStationary (optr);
  up ();
  return optr->vx;
}


/*
   get_yvel - returns the y velocity of object.
*/

double twoDsim_get_yvel (unsigned int id)
{
  Object optr;

  if (trace)
    libc_printf ((char *) "get_yvel for object %d\\n", 24, id);
  down ();
  updatePhysics ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  checkStationary (optr);
  up ();
  return optr->vy;
}


/*
   get_xaccel - returns the x acceleration of object.
*/

double twoDsim_get_xaccel (unsigned int id)
{
  Object optr;

  updatePhysics ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  return optr->ax;
}


/*
   get_yaccel - returns the y acceleration of object.
*/

double twoDsim_get_yaccel (unsigned int id)
{
  Object optr;

  updatePhysics ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  return optr->ay;
}


/*
   put_xvel - assigns the x velocity of object.
*/

void twoDsim_put_xvel (unsigned int id, double r)
{
  Object optr;

  down ();
  updatePhysics ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  optr->vx = r;
  checkStationary (optr);
  up ();
}


/*
   put_yvel - assigns the y velocity of object.
*/

void twoDsim_put_yvel (unsigned int id, double r)
{
  Object optr;

  down ();
  updatePhysics ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  optr->vy = r;
  checkStationary (optr);
  up ();
}


/*
   put_xaccel - assigns the x acceleration of object.
*/

void twoDsim_put_xaccel (unsigned int id, double r)
{
  Object optr;

  down ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  optr->ax = r;
  up ();
}


/*
   put_yaccel - assigns the y acceleration of object.
*/

void twoDsim_put_yaccel (unsigned int id, double r)
{
  Object optr;

  down ();
  optr = Indexing_GetIndice (objects, id);
  checkDeleted (optr);
  optr->ay = r;
  up ();
}


/*
   apply_impulse - apply an impulse to object, id,
                   along the vector [x, y] with magnitude, m.
                   Nothing happens if the object is fixed.
                   Currently only circles can have impulses
                   applied.
*/

void twoDsim_apply_impulse (unsigned int id, double x, double y, double m)
{
  Object optr;

  down ();
  optr = Indexing_GetIndice (objects, id);
  if (! optr->fixed)
    switch (optr->object)
      {
        case circleOb:
          apply_impulse_to_circle (optr, x, y, m);
          break;


        default:
          break;
      }
  up ();
}


/*
   moving_towards - returns TRUE if object, id, is moving towards
                    a point x, y.
*/

unsigned int twoDsim_moving_towards (unsigned int id, double x, double y)
{
  Object optr;
  unsigned int res;

  down ();
  optr = Indexing_GetIndice (objects, id);
  if (! optr->fixed)
    switch (optr->object)
      {
        case circleOb:
          res = circle_moving_towards (optr, x, y);
          break;


        default:
          res = FALSE;
          break;
      }
  up ();
  return res;
}


/*
   set_colour - set the colour of object, id, to colour.
                id must be a box or circle.
*/

void twoDsim_set_colour (unsigned int id, deviceIf_Colour colour)
{
  Object optr;

  optr = Indexing_GetIndice (objects, id);
  switch (optr->object)
    {
      case polygonOb:
        optr->p.col = colour;
        break;

      case circleOb:
        optr->c.col = colour;
        break;


      default:
        libc_printf ((char *) "cannot set the colour of this object\\n", 38);
        break;
    }
}


/*
   mass - specify the mass of an object and return the, id.
          Only polygon (and box) and circle objects may have
          a mass.
*/

unsigned int twoDsim_mass (unsigned int id, double m)
{
  Object optr;

  optr = Indexing_GetIndice (objects, id);
  switch (optr->object)
    {
      case polygonOb:
        optr->p.mass = m;
        break;

      case circleOb:
        optr->c.mass = m;
        break;


      default:
        break;
    }
  calcInertia (optr);
  return id;
}


/*
   fix - fix the object to the world.
*/

unsigned int twoDsim_fix (unsigned int id)
{
  Object optr;

  optr = Indexing_GetIndice (objects, id);
  optr->fixed = TRUE;
  return id;
}


/*
   circle - adds a circle to the world.  Center
            defined by: x0, y0 radius, r.
*/

unsigned int twoDsim_circle (double x0, double y0, double radius, deviceIf_Colour colour)
{
  unsigned int id;
  Object optr;

  id = newObject ((ObjectType) circleOb);
  optr = Indexing_GetIndice (objects, id);
  optr->c.pos.x = x0;
  optr->c.pos.y = y0;
  optr->c.r = radius;
  optr->c.mass = 0.0;
  optr->c.col = colour;
  return id;
}


/*
   velocity - give an object, id, a velocity, vx, vy.
*/

unsigned int twoDsim_velocity (unsigned int id, double vx, double vy)
{
  Object optr;

  optr = Indexing_GetIndice (objects, id);
  if (optr->fixed)
    libc_printf ((char *) "object %d is fixed and therefore cannot be given a velocity\\n", 61, id);
  else
    {
      optr->vx = vx;
      optr->vy = vy;
    }
  return id;
}


/*
   accel - give an object, id, an acceleration, ax, ay.
*/

unsigned int twoDsim_accel (unsigned int id, double ax, double ay)
{
  Object optr;

  optr = Indexing_GetIndice (objects, id);
  if (optr->fixed)
    libc_printf ((char *) "object %d is fixed and therefore cannot be given an acceleration\\n", 66, id);
  else
    {
      optr->ax = ax;
      optr->ay = ay;
    }
  return id;
}


/*
   rotate - gives object, id, an initial orientation.
*/

unsigned int twoDsim_rotate (unsigned int id, double angle)
{
  Object optr;

  if (! (roots_nearZero (angle)))
    {
      optr = Indexing_GetIndice (objects, id);
      checkDeleted (optr);
      if (optr->fixed)
        libc_printf ((char *) "object %d is fixed and therefore cannot be given an angular velocity\\n", 70, id);
      else
        optr->angleOrientation = angle;
    }
  return id;
}


/*
   rvel - gives object, id, an angular velocity, angle.
*/

unsigned int twoDsim_rvel (unsigned int id, double angle)
{
  Object optr;

  if (! (roots_nearZero (angle)))
    {
      optr = Indexing_GetIndice (objects, id);
      checkDeleted (optr);
      if (optr->fixed)
        libc_printf ((char *) "object %d is fixed and therefore cannot be given an angular velocity\\n", 70, id);
      else
        optr->angularVelocity = angle;
    }
  return id;
}


/*
   fps - set frames per second.
*/

void twoDsim_fps (double f)
{
  framesPerSecond = f;
}


/*
   replayRate - set frames per second during replay.
*/

void twoDsim_replayRate (double f)
{
  replayPerSecond = f;
}


/*
   simulateFor - render for, t, seconds.
*/

void twoDsim_simulateFor (double t)
{
  double s;
  double dt;

  s = 0.0;
  twoDsim_checkObjects ();
  if (s < t)
    {
      pumpQueue ();
      printQueue ();
      while (s < t)
        {
          dt = doNextEvent ();
          s = s+dt;
        }
      updatePhysics ();
      printQueue ();
    }
}


/*
   getTime - returns the current time in the simulation.
*/

double twoDsim_getTime (void)
{
  return currentTime;
}


/*
   skipTime - attempts to skip, t, seconds.  It returns the amount
              of time actually skipped.  This function will not skip
              past the next event.
*/

double twoDsim_skipTime (double t)
{
  double dt;

  if (Debugging)
    {
      libc_printf ((char *) "skipTime %f\\n", 13, t);
      dumpTime ();
    }
  pumpQueue ();
  if (eventQ == NULL)
    {
      libc_printf ((char *) "  no events in the queue\\n", 26);
      dumpTime ();
      libc_printf ((char *) "finishing skipTime\\n", 20);
      return 0.0;
    }
  else
    {
      if (t > eventQ->time)
        {
          dt = eventQ->time;
          if (! (roots_nearZero (dt)))
            currentTime = currentTime+dt;
          eventQ->time = 0.0;
        }
      else
        {
          dt = eventQ->time-t;
          if (roots_nearZero (dt))
            {
              currentTime = currentTime+eventQ->time;
              eventQ->time = 0.0;
            }
          else
            {
              currentTime = currentTime+t;
              eventQ->time = eventQ->time-t;
            }
        }
      if (Debugging)
        {
          dumpTime ();
          libc_printf ((char *) "finishing skipTime\\n", 20);
        }
      return dt;
    }
}


/*
   timeUntil - returns the relative time from now until the next event.
*/

double twoDsim_timeUntil (void)
{
  pumpQueue ();
  if (eventQ == NULL)
    return 0.0;
  else
    return eventQ->time;
}


/*
   processEvent - skips any outstanding time and processes the next event.
                  Time is adjusted to the time of the next event.
*/

void twoDsim_processEvent (void)
{
  double dt;

  if (Debugging)
    libc_printf ((char *) "processEvent before pumpQueue\\n", 31);
  pumpQueue ();
  if (DebugTrace)
    {
      libc_printf ((char *) "before doNextEvent\\n", 20);
      printQueue ();
    }
  dt = doNextEvent ();
  if (DebugTrace)
    libc_printf ((char *) "finished doNextEvent\\n", 22);
}


/*
   isCollision - returns TRUE if the next event is a collision event.
*/

unsigned int twoDsim_isCollision (void)
{
  if (Debugging)
    libc_printf ((char *) "isCollision before pumpQueue\\n", 30);
  pumpQueue ();
  return isEvent ((eventKind) collisionKind);
}


/*
   isFrame - returns TRUE if the next event is a frame event.
*/

unsigned int twoDsim_isFrame (void)
{
  if (Debugging)
    libc_printf ((char *) "isFrame before pumpQueue\\n", 26);
  pumpQueue ();
  return isEvent ((eventKind) frameKind);
}


/*
   isFunction - returns TRUE if the next event is a function event.
*/

unsigned int twoDsim_isFunction (void)
{
  if (Debugging)
    libc_printf ((char *) "isFunction before pumpQueue\\n", 29);
  pumpQueue ();
  return isEvent ((eventKind) functionKind);
}


/*
   createFunctionEvent - creates a function event at time, t,
                         in the future.
*/

void twoDsim_createFunctionEvent (double t, unsigned int id)
{
  eventQueue e;
  eventDesc edesc;

  pumpQueue ();
  if (Debugging)
    libc_printf ((char *) "function event %d will occur in %g simulated seconds\\n", 54, id, t);
  edesc = newDesc ();
  edesc->etype = functionEvent;
  edesc->fc.id = id;
  e = newEvent ();
  e->kind = functionKind;
  e->time = t;
  e->p.proc = doFunctionEvent;
  e->ePtr = edesc;
  e->next = NULL;
  if (Debugging)
    {
      libc_printf ((char *) "queue before function event\\n", 29);
      printQueue ();
    }
  addRelative (e);
  if (Debugging)
    {
      libc_printf ((char *) "queue after function event\\n", 28);
      printQueue ();
    }
}


/*
   rm - delete this object from the simulated world.
        The same id is returned.
*/

unsigned int twoDsim_rm (unsigned int id)
{
  Object optr;

  down ();
  optr = Indexing_GetIndice (objects, id);
  if (DebugTrace)
    {
      libc_printf ((char *) "rm %d\\n", 7, id);
      libc_printf ((char *) "here is the world before rm\\n", 29);
      twoDsim_dumpWorld ();
    }
  optr->deleted = TRUE;
  if (DebugTrace)
    {
      libc_printf ((char *) "rm complete, here is the world after rm\\n", 41);
      twoDsim_dumpWorld ();
    }
  resetStationary ();
  up ();
  return id;
}


/*
   getEventBuffer - collects the event buffer limits in the following parameters.
*/

void twoDsim_getEventBuffer (void * *start, unsigned int *length, unsigned int *used)
{
  double * f;

  recordEvent ();
  (*start) = bufferStart;
  (*length) = bufferLength;
  (*used) = bufferUsed;
  f = bufferStart;
  if (DebugTrace)
    {
      libc_printf ((char *) "event buffer ptr = 0x%p, length = %d, used = %d\\n", 49, (*start), (*length), (*used));
      libc_printf ((char *) "ptr to real is %g\\n", 19, (*f));
      memDump ((*start), 8);
    }
}


/*
   buildFrame - populate the frame buffer contents with the world at the current time.
*/

void twoDsim_buildFrame (void)
{
  deviceIf_frameNote ();
  drawFrame ((eventQueue) NULL);
  deviceIf_flipBuffer ();
}


/*
   emptyCbuffer - empty the colour buffer.
*/

void twoDsim_emptyCbuffer (void)
{
  deviceIf_emptyCbuffer ();
}


/*
   emptyFbuffer - empty the frame buffer.
*/

void twoDsim_emptyFbuffer (void)
{
  deviceIf_emptyFbuffer ();
}


/*
   useTimeDelay - should the frame buffer include the time delay command?
*/

void twoDsim_useTimeDelay (unsigned int on)
{
  writeTimeDelay = on;
}


/*
   drawCollisionFrames - turn the drawing of collision frames on or off.
                         actual:   determines whether an extra frame is generated
                                   at the time of actual collision.
                         predict:  draws a frame predicting the next collision.
                                   It will show the points predicted to collide.
*/

void twoDsim_drawCollisionFrames (unsigned int actual, unsigned int predict)
{
  drawCollisionFrame = actual;
  drawPrediction = predict;
}


/*
   setCollisionColour - assigns, c, as the colour for objects colliding.
*/

void twoDsim_setCollisionColour (deviceIf_Colour c)
{
  collisionColour = c;
  haveCollisionColour = TRUE;
}


/*
   dumpWorld - dump a list of all objects and their characteristics.
*/

void twoDsim_dumpWorld (void)
{
  unsigned int i;
  unsigned int n;

  n = Indexing_HighIndice (objects);
  i = 1;
  while (i <= n)
    {
      DumpObject ((Object) Indexing_GetIndice (objects, i));
      i += 1;
    }
}


/*
   checkObjects - perform a check to make sure that all non fixed objects have a mass.
*/

void twoDsim_checkObjects (void)
{
  unsigned int i;
  unsigned int n;
  Object optr;
  unsigned int error;

  error = FALSE;
  n = Indexing_HighIndice (objects);
  i = 1;
  while (i <= n)
    {
      optr = Indexing_GetIndice (objects, i);
      if (! optr->fixed && ! optr->deleted)
        switch (optr->object)
          {
            case polygonOb:
              if (roots_nearZero (optr->p.mass))
                {
                  libc_printf ((char *) "polygon %d is not fixed and does not have a mass\\n", 50, optr->id);
                  error = TRUE;
                }
              break;

            case circleOb:
              if (roots_nearZero (optr->c.mass))
                {
                  libc_printf ((char *) "circle %d is not fixed and does not have a mass\\n", 49, optr->id);
                  error = TRUE;
                }
              break;


            default:
              break;
          }
      i += 1;
    }
  if (error)
    libc_exit (1);
}

void _M2_twoDsim_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_twoDsim_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
