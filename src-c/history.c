/* automatically created by mc from ../history.mod.  */

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
#define _history_H
#define _history_C

#   include "GStorage.h"
#   include "Groots.h"
#   include "Glibc.h"

#   define Debugging FALSE
#   define Purge TRUE
#   define HalfSecond 0.5
typedef struct _T1_r _T1;

typedef _T1 *hList;

typedef enum {history_corner, history_edge} history_whereHit;

struct _T1_r {
               unsigned int id1;
               unsigned int id2;
               history_whereHit where1;
               history_whereHit where2;
               coord_Coord cp;
               double t;
               hList next;
             };

static double currentTime;
static hList free;
static hList pastQ;
static hList futureQ;

/*
   isDuplicate - returns TRUE if the collision at, cp,
                 and, time, has occurred before.
                 The time (currentTime+relTime) must be the absolute
                 time of the collision.
*/

unsigned int history_isDuplicate (double currentTime, double relTime, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp);

/*
   forgetFuture - destroy the anticipated future queue.
*/

void history_forgetFuture (void);

/*
   occurred - mark the collision as having occurred at, currentTime, between, objects
              id1 and id2 at position, cp.  This collision is placed onto the past queue.
              If the event described by id1, id2 at, time, is also present
              on the future queue it is removed.
*/

void history_occurred (double currentTime, unsigned int id1, unsigned int id2, coord_Coord cp);

/*
   anticipate - anticipate a collision at time, aTime, in the future at
                position, cp.
                A duplicate will ignored.  A non duplicate
                collision will be placed onto the futureQ.
*/

void history_anticipate (double aTime, unsigned int id1, unsigned int id2, coord_Coord cp);

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
   isSame - do, a, and, b, reference the same collision?  Note we do not use the contact
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
   init - fill in the fields of, n, and return n.
*/

static hList init (hList n, double time, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp);

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
   addToPastQ -
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
  libc_printf ((char *) "time %g id pair (%d, %d)\\n", 26, l->t, l->id1, l->id2);
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

  if (free == NULL)
    Storage_ALLOCATE ((void **) &h, sizeof (_T1));
  else
    {
      h = free;
      free = free->next;
    }
  return h;
}


/*
   disposeHList - returns, h, to the free list.
*/

static void disposeHList (hList h)
{
  h->next = free;
  free = h;
}


/*
   isSame - do, a, and, b, reference the same collision?  Note we do not use the contact
            point of collision as polygon/polygon collisions might hit on the corner or
            edge.  Instead we assume if we know the time, polygon, face this is good enough.
            twoDsim will test for multiple points on a line and we need to identify
            duplicates per polygon and line.
*/

static unsigned int isSame (hList a, hList b)
{
  return ((((roots_nearZero (a->t-b->t)) && (history_isPair (a->id1, a->id2, b->id1, b->id2))) && (a->where1 == b->where1)) && (a->where2 == b->where2)) && (roots_nearCoord (a->cp, b->cp));
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
   init - fill in the fields of, n, and return n.
*/

static hList init (hList n, double time, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp)
{
  n->id1 = id1;
  n->id2 = id2;
  n->where1 = w1;
  n->where2 = w2;
  n->cp = cp;
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
      currentTime = time;
      if (Purge)
        {
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
   addToPastQ -
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
  else
    {
      p = pastQ;
      q = p->next;
      while (q != NULL)
        {
          if (n->t > q->t)
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
        return FALSE;
      h = h->next;
    }
  return FALSE;
}


/*
   isDuplicate - returns TRUE if the collision at, cp,
                 and, time, has occurred before.
                 The time (currentTime+relTime) must be the absolute
                 time of the collision.
*/

unsigned int history_isDuplicate (double currentTime, double relTime, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp)
{
  hList h;
  hList n;

  if (Debugging)
    dumpLists ();
  n = init (newHList (), currentTime+relTime, id1, id2, w1, w2, cp);
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
   occurred - mark the collision as having occurred at, currentTime, between, objects
              id1 and id2 at position, cp.  This collision is placed onto the past queue.
              If the event described by id1, id2 at, time, is also present
              on the future queue it is removed.
*/

void history_occurred (double currentTime, unsigned int id1, unsigned int id2, coord_Coord cp)
{
  hList n;

  if (Debugging)
    dumpLists ();
  n = init (newHList (), currentTime, id1, id2, (history_whereHit) history_edge, (history_whereHit) history_edge, cp);
  if (Debugging)
    {
      libc_printf ((char *) "collision has occurred ", 23);
      dumpHlist (n);
      libc_printf ((char *) "collision has occurred, old queues\\n", 36);
      dumpLists ();
    }
  updateTime (currentTime);
  history_forgetFuture ();
  addToPastQ (n);
  if (Debugging)
    {
      libc_printf ((char *) "collision has occurred queues altered\\n", 39);
      dumpLists ();
    }
}


/*
   anticipate - anticipate a collision at time, aTime, in the future at
                position, cp.
                A duplicate will ignored.  A non duplicate
                collision will be placed onto the futureQ.
*/

void history_anticipate (double aTime, unsigned int id1, unsigned int id2, coord_Coord cp)
{
  hList n;

  if (Debugging)
    dumpLists ();
  n = init (newHList (), aTime, id1, id2, (history_whereHit) history_edge, (history_whereHit) history_edge, cp);
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
  free = NULL;
}

void _M2_history_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
