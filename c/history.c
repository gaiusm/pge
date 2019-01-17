/* automatically created by mc from ../git-pge/m2/history.mod.  */

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
#   include "GStorage.h"
#   include "Gmcrts.h"
#define _history_H
#define _history_C

#   include "GStorage.h"
#   include "Groots.h"
#   include "Glibc.h"
#   include "GM2RTS.h"

#   define Debugging FALSE
#   define Purge TRUE
#   define HalfSecond 0.5
typedef struct collisionT_r collisionT;

typedef struct springT_r springT;

typedef struct _T1_r _T1;

typedef _T1 *hList;

typedef enum {history_corner, history_edge} history_whereHit;

typedef enum {history_midPoint, history_endPoint, history_callPoint} history_springPoint;

typedef enum {collision, spring} historyType;

struct collisionT_r {
                      unsigned int id1;
                      unsigned int id2;
                      history_whereHit where1;
                      history_whereHit where2;
                      coord_Coord cp;
                    };

struct springT_r {
                   unsigned int id;
                   history_springPoint where;
                 };

struct _T1_r {
               historyType type;  /* case tag */
               union {
                       collisionT collisionF;
                       springT springF;
                     };
               double t;
               hList next;
             };

static double currentTime;
static hList free_;
static hList pastQ;
static hList futureQ;

/*
   isDuplicateC - returns TRUE if the collision at, cp,
                  and, time, has occurred before.
                  The time (currentTime+relTime) must be the absolute
                  time of the collision.
*/

unsigned int history_isDuplicateC (double currentTime, double relTime, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp);

/*
   forgetFuture - destroy the anticipated future queue.
*/

void history_forgetFuture (void);

/*
   occurredC - mark the collision as having occurred at, currentTime, between, objects
              id1 and id2 at position, cp.  This collision is placed onto the past queue.
              If the event described by id1, id2 at, time, is also present
              on the future queue it is removed.
*/

void history_occurredC (double currentTime, unsigned int id1, unsigned int id2, coord_Coord cp);

/*
   anticipateC - anticipate a collision at time, aTime, in the future at
                 position, cp.
                 A duplicate will ignored.  A non duplicate
                 collision will be placed onto the futureQ.
*/

void history_anticipateC (double aTime, unsigned int id1, unsigned int id2, coord_Coord cp);

/*
   isDuplicateS - returns TRUE if the spring event for object, id,
                  and, time, has occurred before.
                  The time (currentTime+relTime) must be the absolute
                  time of the collision.
*/

unsigned int history_isDuplicateS (double currentTime, double relTime, unsigned int id, history_springPoint where);

/*
   anticipateS - anticipate a spring event at time, aTime,
                 in the future with spring, i, at, w.
                 A duplicate will ignored.  A non duplicate
                 collision will be placed onto the futureQ.
*/

void history_anticipateS (double aTime, unsigned int id, history_springPoint w);

/*
   occurredS - mark the spring event as having occurred at, currentTime, for spring, id.
               This event is placed onto the past queue.
               If this event is also present on the future queue it is removed.
*/

void history_occurredS (double currentTime, unsigned int id, history_springPoint w);

/*
   isPair - are (a, b) the same as (x, y) or
             is (a, b) the same as (y, x)
*/

unsigned int history_isPair (unsigned int a, unsigned int b, unsigned int x, unsigned int y);

/*
   dumpHlist -
*/

static void dumpHlist (hList l);

/*
   dumpLists -
*/

static void dumpLists (void);

/*
   newHList - returns a new hList.
*/

static hList newHList (void);

/*
   disposeHList - returns, h, to the free list.
*/

static void disposeHList (hList h);

/*
   assert -
*/

static void assert (unsigned int b, unsigned int line);

/*
   isSameS -
*/

static unsigned int isSameS (hList a, hList b);

/*
   isSameC -
*/

static unsigned int isSameC (hList a, hList b);

/*
   isSame - do, a, and, b, reference the same history object?  We check
            spring and collision frames.

            Note we do not use the contact
            point of collision as polygon/polygon collisions might hit on the corner or
            edge.  Instead we assume if we know the time, polygon, face this is good enough.
            twoDsim will test for multiple points on a line and we need to identify
            duplicates per polygon and line.
*/

static unsigned int isSame (hList a, hList b);

/*
   disposeAll - return NIL.  Place complete contents of, l, onto the free list.
*/

static hList disposeAll (hList l);

/*
   initS - fill in the fields of, n, and return n.
*/

static hList initS (hList n, double time, unsigned int id, history_springPoint w);

/*
   initC - fill in the fields of, n, and return n.
*/

static hList initC (hList n, double time, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp);

/*
   tooClose - returns TRUE if |a-b| < HalfSecond
*/

static unsigned int tooClose (double a, double b);

/*
   updateTime -
*/

static void updateTime (double time);

/*
   removeFromFutureQ -
*/

static void removeFromFutureQ (hList n);

/*
   addToPastQ - stores the history collision in reverse order.
                Highest time values (latest times are at the front).
*/

static void addToPastQ (hList n);

/*
   addToFutureQ -
*/

static void addToFutureQ (hList n);

/*
   isDuplicateFuture -
*/

static unsigned int isDuplicateFuture (hList n);

/*
   isDuplicatePast -
*/

static unsigned int isDuplicatePast (hList n);


/*
   dumpHlist -
*/

static void dumpHlist (hList l)
{
  libc_printf ((char *) "time %g ", 8, l->t);
  switch (l->type)
    {
      case collision:
        libc_printf ((char *) "collision id pair (%d, %d)\\n", 28, l->collisionF.id1, l->collisionF.id2);
        break;

      case spring:
        libc_printf ((char *) "spring id (%d) ", 15, l->springF.id);
        switch (l->springF.where)
          {
            case history_midPoint:
              libc_printf ((char *) "midpoint", 8);
              break;

            case history_endPoint:
              libc_printf ((char *) "endpoint", 8);
              break;

            case history_callPoint:
              libc_printf ((char *) "callpoint", 9);
              break;


            default:
              CaseException ("../git-pge/m2/history.def", 1, 15);
          }
        break;


      default:
        CaseException ("../git-pge/m2/history.def", 1, 15);
    }
  libc_printf ((char *) "`n", 2);
}


/*
   dumpLists -
*/

static void dumpLists (void)
{
  hList l;

  l = pastQ;
  libc_printf ((char *) "Dumping lists\\n", 15);
  libc_printf ((char *) "  past Q\\n", 10);
  while (l != NULL)
    {
      libc_printf ((char *) "  ", 2);
      dumpHlist (l);
      l = l->next;
    }
  l = futureQ;
  libc_printf ((char *) "  futureQ:\\n", 12);
  while (l != NULL)
    {
      libc_printf ((char *) "  ", 2);
      dumpHlist (l);
      l = l->next;
    }
}


/*
   newHList - returns a new hList.
*/

static hList newHList (void)
{
  hList h;

  if (free_ == NULL)
    Storage_ALLOCATE ((void **) &h, sizeof (_T1));
  else
    {
      h = free_;
      free_ = free_->next;
    }
  return h;
}


/*
   disposeHList - returns, h, to the free list.
*/

static void disposeHList (hList h)
{
  h->next = free_;
  free_ = h;
}


/*
   assert -
*/

static void assert (unsigned int b, unsigned int line)
{
  if (! b)
    {
      libc_printf ((char *) "../git-pge/m2/history.mod", 25);
      libc_printf ((char *) ":%d:error assert failed\\n", 25, line);
      M2RTS_HALT (-1);
    }
}


/*
   isSameS -
*/

static unsigned int isSameS (hList a, hList b)
{
  assert (a->type == spring, 177);
  assert (b->type == spring, 178);
  return (a->springF.id == b->springF.id) && (a->springF.where == b->springF.where);
}


/*
   isSameC -
*/

static unsigned int isSameC (hList a, hList b)
{
  assert (a->type == collision, 190);
  assert (b->type == collision, 191);
  /* where1 and where2 are not used yet.  */
  return (((history_isPair (a->collisionF.id1, a->collisionF.id2, b->collisionF.id1, b->collisionF.id2)) && (a->collisionF.where1 == b->collisionF.where1)) && (a->collisionF.where2 == b->collisionF.where2)) && (roots_nearCoord (a->collisionF.cp, b->collisionF.cp));
}


/*
   isSame - do, a, and, b, reference the same history object?  We check
            spring and collision frames.

            Note we do not use the contact
            point of collision as polygon/polygon collisions might hit on the corner or
            edge.  Instead we assume if we know the time, polygon, face this is good enough.
            twoDsim will test for multiple points on a line and we need to identify
            duplicates per polygon and line.
*/

static unsigned int isSame (hList a, hList b)
{
  return ((roots_nearZero (a->t-b->t)) && (a->type == b->type)) && (((a->type == collision) && (isSameC (a, b))) || ((a->type == spring) && (isSameS (a, b))));
}


/*
   disposeAll - return NIL.  Place complete contents of, l, onto the free list.
*/

static hList disposeAll (hList l)
{
  hList a;

  while (l != NULL)
    {
      a = l;
      l = l->next;
      disposeHList (a);
    }
  return NULL;
}


/*
   initS - fill in the fields of, n, and return n.
*/

static hList initS (hList n, double time, unsigned int id, history_springPoint w)
{
  n->type = spring;
  n->springF.id = id;
  n->springF.where = w;
  n->t = time;
  n->next = NULL;
  return n;
}


/*
   initC - fill in the fields of, n, and return n.
*/

static hList initC (hList n, double time, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp)
{
  n->type = collision;
  n->collisionF.id1 = id1;
  n->collisionF.id2 = id2;
  n->collisionF.where1 = w1;
  n->collisionF.where2 = w2;
  n->collisionF.cp = cp;
  n->t = time;
  n->next = NULL;
  return n;
}


/*
   tooClose - returns TRUE if |a-b| < HalfSecond
*/

static unsigned int tooClose (double a, double b)
{
  if (Debugging)
    libc_printf ((char *) "a = %g, b = %g\\n", 16, a, b);
  if (a > b)
    return (a-b) < HalfSecond;
  else
    return (b-a) < HalfSecond;
}


/*
   updateTime -
*/

static void updateTime (double time)
{
  hList p;
  hList h;

  if (! (roots_nearSame (time, currentTime)))
    {
      /* time has advanced, see if we can purge the pastQ.  */
      currentTime = time;
      if (Purge)
        {
          /* in the pastQ time is decreasing.  */
          h = pastQ;
          p = NULL;
          while (h != NULL)
            if (tooClose (h->t, currentTime))
              {
                if (Debugging)
                  libc_printf ((char *) "too close to delete\\n", 21);
                p = h;
                h = h->next;
              }
            else if (h->t < currentTime)
              {
                if (Debugging)
                  libc_printf ((char *) "yes can delete\\n", 16);
                if (p == NULL)
                  pastQ = NULL;
                else
                  p->next = NULL;
                h = disposeAll (h);
                return;
              }
            else
              {
                if (Debugging)
                  libc_printf ((char *) "ignoring\\n", 10);
                p = h;
                h = h->next;
              }
        }
    }
}


/*
   removeFromFutureQ -
*/

static void removeFromFutureQ (hList n)
{
  hList p;
  hList q;

  p = futureQ;
  while (p != NULL)
    {
      q = p->next;
      if ((q != NULL) && (isSame (q, n)))
        {
          p->next = q->next;
          disposeHList (q);
          q = p->next;
        }
      else
        {
          q = p;
          p = p->next;
        }
    }
  if ((futureQ != NULL) && (isSame (futureQ, n)))
    {
      q = futureQ;
      futureQ = futureQ->next;
      disposeHList (q);
    }
}


/*
   addToPastQ - stores the history collision in reverse order.
                Highest time values (latest times are at the front).
*/

static void addToPastQ (hList n)
{
  hList p;
  hList q;

  if (pastQ == NULL)
    {
      pastQ = n;
      n->next = NULL;
    }
  else if (n->t > pastQ->t)
    {
      n->next = pastQ;
      pastQ = n;
    }
  else if (pastQ->next == NULL)
    {
      pastQ->next = n;
      n->next = NULL;
    }
  else
    {
      p = pastQ;
      q = p->next;
      if (q == NULL)
        M2RTS_HALT (-1);
      while ((q != NULL) && (n->t <= q->t))
        {
          p = q;
          q = q->next;
        }
      n->next = q;
      p->next = n;
    }
}


/*
   addToFutureQ -
*/

static void addToFutureQ (hList n)
{
  hList p;
  hList q;

  if (futureQ == NULL)
    {
      futureQ = n;
      n->next = NULL;
    }
  else if (n->t < futureQ->t)
    {
      n->next = futureQ;
      futureQ = n;
    }
  else
    {
      p = futureQ;
      q = p->next;
      while (q != NULL)
        {
          if (n->t < q->t)
            {
              n->next = q;
              p->next = n;
              return;
            }
          p = q;
          q = q->next;
        }
    }
}


/*
   isDuplicateFuture -
*/

static unsigned int isDuplicateFuture (hList n)
{
  hList h;

  h = futureQ;
  /* in the futureQ time is increasing.  */
  while (h != NULL)
    {
      if (isSame (n, h))
        {
          if (Debugging)
            {
              libc_printf ((char *) "found collision event on the futureq: ", 38);
              dumpHlist (n);
            }
          return TRUE;
        }
      else if ((h->t > n->t) && (! (roots_nearSame (h->t, n->t))))
        /* h is now too far in the future to ever be considered the same.  */
        return FALSE;
      h = h->next;
    }
  return FALSE;
}


/*
   isDuplicatePast -
*/

static unsigned int isDuplicatePast (hList n)
{
  hList h;

  h = pastQ;
  /* in the pastQ time is decreasing.  */
  while (h != NULL)
    {
      if (isSame (n, h))
        {
          if (Debugging)
            {
              libc_printf ((char *) "found collision event on the pastq: ", 36);
              dumpHlist (n);
            }
          return TRUE;
        }
      else if ((h->t < n->t) && (! (roots_nearSame (h->t, n->t))))
        /* h is now too far in the past to ever be considered the same.  */
        return FALSE;
      h = h->next;
    }
  return FALSE;
}


/*
   isDuplicateC - returns TRUE if the collision at, cp,
                  and, time, has occurred before.
                  The time (currentTime+relTime) must be the absolute
                  time of the collision.
*/

unsigned int history_isDuplicateC (double currentTime, double relTime, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp)
{
  hList h;
  hList n;

  if (Debugging)
    dumpLists ();
  n = initC (newHList (), currentTime+relTime, id1, id2, w1, w2, cp);
  if (Debugging)
    {
      libc_printf ((char *) "checking for duplicates of: ", 28);
      dumpHlist (n);
    }
  if ((isDuplicateFuture (n)) || (isDuplicatePast (n)))
    {
      if (Debugging)
        {
          libc_printf ((char *) "duplicate collision found (ignoring): ", 38);
          dumpHlist (n);
        }
      disposeHList (n);
      return TRUE;
    }
  /* updateTime (currentTime) ;  */
  if (Debugging)
    {
      libc_printf ((char *) "unique collision found: ", 24);
      dumpHlist (n);
    }
  disposeHList (n);
  return FALSE;
}


/*
   forgetFuture - destroy the anticipated future queue.
*/

void history_forgetFuture (void)
{
  futureQ = disposeAll (futureQ);
}


/*
   occurredC - mark the collision as having occurred at, currentTime, between, objects
              id1 and id2 at position, cp.  This collision is placed onto the past queue.
              If the event described by id1, id2 at, time, is also present
              on the future queue it is removed.
*/

void history_occurredC (double currentTime, unsigned int id1, unsigned int id2, coord_Coord cp)
{
  hList n;

  if (Debugging)
    dumpLists ();
  n = initC (newHList (), currentTime, id1, id2, (history_whereHit) history_edge, (history_whereHit) history_edge, cp);
  if (Debugging)
    {
      libc_printf ((char *) "collision has occurred ", 23);
      dumpHlist (n);
      libc_printf ((char *) "collision has occurred, old queues\\n", 36);
      dumpLists ();
    }
  updateTime (currentTime);
  history_forgetFuture ();
  /* removeFromFutureQ (n) ;  */
  addToPastQ (n);
  if (Debugging)
    {
      libc_printf ((char *) "collision has occurred queues altered\\n", 39);
      dumpLists ();
    }
}


/*
   anticipateC - anticipate a collision at time, aTime, in the future at
                 position, cp.
                 A duplicate will ignored.  A non duplicate
                 collision will be placed onto the futureQ.
*/

void history_anticipateC (double aTime, unsigned int id1, unsigned int id2, coord_Coord cp)
{
  hList n;

  if (Debugging)
    dumpLists ();
  n = initC (newHList (), aTime, id1, id2, (history_whereHit) history_edge, (history_whereHit) history_edge, cp);
  if (Debugging)
    {
      libc_printf ((char *) "anticipated collision at: ", 26);
      dumpHlist (n);
      libc_printf ((char *) "anticipated collision, old queues\\n", 35);
      dumpLists ();
    }
  if ((isDuplicatePast (n)) || (isDuplicateFuture (n)))
    {
      if (Debugging)
        libc_printf ((char *) "anticipated collision, duplicate, ignoring\\n", 44);
      disposeHList (n);
    }
  else
    {
      addToFutureQ (n);
      if (Debugging)
        {
          libc_printf ((char *) "anticipated collision, new queues\\n", 35);
          dumpLists ();
        }
    }
}


/*
   isDuplicateS - returns TRUE if the spring event for object, id,
                  and, time, has occurred before.
                  The time (currentTime+relTime) must be the absolute
                  time of the collision.
*/

unsigned int history_isDuplicateS (double currentTime, double relTime, unsigned int id, history_springPoint where)
{
  hList h;
  hList n;

  if (Debugging)
    dumpLists ();
  n = initS (newHList (), currentTime+relTime, id, where);
  if (Debugging)
    {
      libc_printf ((char *) "checking for duplicates of: ", 28);
      dumpHlist (n);
    }
  if ((isDuplicateFuture (n)) || (isDuplicatePast (n)))
    {
      if (Debugging)
        {
          libc_printf ((char *) "duplicate spring event found (ignoring): ", 41);
          dumpHlist (n);
        }
      disposeHList (n);
      return TRUE;
    }
  if (Debugging)
    {
      libc_printf ((char *) "unique spring event found: ", 27);
      dumpHlist (n);
    }
  disposeHList (n);
  return FALSE;
}


/*
   anticipateS - anticipate a spring event at time, aTime,
                 in the future with spring, i, at, w.
                 A duplicate will ignored.  A non duplicate
                 collision will be placed onto the futureQ.
*/

void history_anticipateS (double aTime, unsigned int id, history_springPoint w)
{
  hList n;

  if (Debugging)
    dumpLists ();
  n = initS (newHList (), aTime, id, w);
  if (Debugging)
    {
      libc_printf ((char *) "anticipated spring event at: ", 29);
      dumpHlist (n);
      libc_printf ((char *) "anticipated spring event, old queues\\n", 38);
      dumpLists ();
    }
  if ((isDuplicatePast (n)) || (isDuplicateFuture (n)))
    {
      if (Debugging)
        libc_printf ((char *) "anticipated spring event, duplicate, ignoring\\n", 47);
      disposeHList (n);
    }
  else
    {
      addToFutureQ (n);
      if (Debugging)
        {
          libc_printf ((char *) "anticipated spring event, new queues\\n", 38);
          dumpLists ();
        }
    }
}


/*
   occurredS - mark the spring event as having occurred at, currentTime, for spring, id.
               This event is placed onto the past queue.
               If this event is also present on the future queue it is removed.
*/

void history_occurredS (double currentTime, unsigned int id, history_springPoint w)
{
  hList n;

  if (Debugging)
    dumpLists ();
  n = initS (newHList (), currentTime, id, w);
  if (Debugging)
    {
      libc_printf ((char *) "spring event has occurred ", 26);
      dumpHlist (n);
      libc_printf ((char *) "spring event has occurred, old queues\\n", 39);
      dumpLists ();
    }
  updateTime (currentTime);
  history_forgetFuture ();
  /* removeFromFutureQ (n) ;  */
  addToPastQ (n);
  if (Debugging)
    {
      libc_printf ((char *) "spring event has occurred queues altered\\n", 42);
      dumpLists ();
    }
}


/*
   isPair - are (a, b) the same as (x, y) or
             is (a, b) the same as (y, x)
*/

unsigned int history_isPair (unsigned int a, unsigned int b, unsigned int x, unsigned int y)
{
  return ((a == x) && (b == y)) || ((a == y) && (b == x));
}

void _M2_history_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  currentTime = 0.0;
  pastQ = NULL;
  futureQ = NULL;
  free_ = NULL;
}

void _M2_history_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
