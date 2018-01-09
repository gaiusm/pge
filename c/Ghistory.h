/* automatically created by mc from ../git-pge/m2/history.def.  */


#if !defined (_history_H)
#   define _history_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "Gcoord.h"

#   if defined (_history_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef enum {history_corner, history_edge} history_whereHit;

typedef enum {history_midPoint, history_endPoint, history_callPoint} history_springPoint;


/*
   isDuplicateC - returns TRUE if the collision at, cp,
                  and, time, has occurred before.
                  The time (currentTime+relTime) must be the absolute
                  time of the collision.
*/

EXTERN unsigned int history_isDuplicateC (double currentTime, double relTime, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp);

/*
   forgetFuture - destroy the anticipated future queue.
*/

EXTERN void history_forgetFuture (void);

/*
   occurredC - mark the collision as having occurred at, currentTime, between, objects
               id1 and id2 at position, cp.  This collision is placed onto the past queue.
               If the event described by id1, id2 at, time, is also present
               on the future queue it is removed.
*/

EXTERN void history_occurredC (double currentTime, unsigned int id1, unsigned int id2, coord_Coord cp);

/*
   anticipateC - anticipate a collision at time, aTime, in the future at
                 position, cp.
                 A duplicate will ignored.  A non duplicate
                 collision will be placed onto the futureQ.
*/

EXTERN void history_anticipateC (double aTime, unsigned int id1, unsigned int id2, coord_Coord cp);

/*
   isDuplicateS - returns TRUE if the spring event for object, id,
                  and, time, has occurred before.
                  The time (currentTime+relTime) must be the absolute
                  time of the collision.
*/

EXTERN unsigned int history_isDuplicateS (double currentTime, double relTime, unsigned int id, history_springPoint where);

/*
   anticipateS - anticipate a spring event at time, aTime,
                 in the future with spring, i, at, w.
                 A duplicate will ignored.  A non duplicate
                 collision will be placed onto the futureQ.
*/

EXTERN void history_anticipateS (double aTime, unsigned int id, history_springPoint w);

/*
   occurredS - mark the spring event as having occurred at, currentTime, for spring, id.
               This event is placed onto the past queue.
               If this event is also present on the future queue it is removed.
*/

EXTERN void history_occurredS (double currentTime, unsigned int id, history_springPoint w);

/*
   isPair - are (a, b) the same as (x, y) or
             is (a, b) the same as (y, x)
*/

EXTERN unsigned int history_isPair (unsigned int a, unsigned int b, unsigned int x, unsigned int y);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
