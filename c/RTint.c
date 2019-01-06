/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.mod.  */

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
#include <limits.h>
#   include "GStorage.h"
#   include "Gmcrts.h"
#define _RTint_H
#define _RTint_C

#   include "GM2RTS.h"
#   include "GStorage.h"
#   include "Gpth.h"
#   include "GCOROUTINES.h"
#   include "Glibc.h"
#   include "GAssertion.h"
#   include "GSelective.h"

typedef struct RTint_DespatchVector_p RTint_DespatchVector;

#   define Microseconds 1000000
#   define DebugTime 0
#   define Debugging FALSE
typedef struct _T1_r _T1;

typedef _T1 *Vector;

typedef struct _T2_a _T2;

typedef enum {input, output, time} VectorType;

typedef void (*RTint_DespatchVector_t) (unsigned int, unsigned int, void *);
struct RTint_DespatchVector_p { RTint_DespatchVector_t proc; };

struct _T1_r {
               VectorType type;
               unsigned int priority;
               void *arg;
               Vector pending;
               Vector exists;
               unsigned int no;
               int File;
               Selective_Timeval rel;
               Selective_Timeval abs_;
               unsigned int queued;
             };

struct _T2_a { Vector array[(7)-(COROUTINES_UnassignedPriority)+1]; };
static unsigned int VecNo;
static Vector Exists;
static _T2 Pending;

/*
   InitInputVector - returns an interrupt vector which is associated
                     with the file descriptor, fd.
*/

unsigned int RTint_InitInputVector (int fd, unsigned int pri);

/*
   InitOutputVector - returns an interrupt vector which is associated
                      with the file descriptor, fd.
*/

unsigned int RTint_InitOutputVector (int fd, unsigned int pri);

/*
   InitTimeVector - returns an interrupt vector associated with
                    the relative time.
*/

unsigned int RTint_InitTimeVector (unsigned int micro, unsigned int secs, unsigned int pri);

/*
   ReArmTimeVector - reprimes the vector, vec, to deliver an interrupt
                     at the new relative time.
*/

void RTint_ReArmTimeVector (unsigned int vec, unsigned int micro, unsigned int secs);

/*
   GetTimeVector - assigns, micro, and, secs, with the remaining
                   time before this interrupt will expire.
                   This value is only updated when a Listen
                   occurs.
*/

void RTint_GetTimeVector (unsigned int vec, unsigned int *micro, unsigned int *secs);

/*
   AttachVector - adds the pointer, p, to be associated with the interrupt
                  vector. It returns the previous value attached to this
                  vector.
*/

void * RTint_AttachVector (unsigned int vec, void * p);

/*
   IncludeVector - includes, vec, into the despatcher list of
                   possible interrupt causes.
*/

void RTint_IncludeVector (unsigned int vec);

/*
   ExcludeVector - excludes, vec, from the despatcher list of
                   possible interrupt causes.
*/

void RTint_ExcludeVector (unsigned int vec);

/*
   Listen - will either block indefinitely (until an interrupt)
            or alteratively will test to see whether any interrupts
            are pending.
            If a pending interrupt was found then, call, is called
            and then this procedure returns.
            It only listens for interrupts > pri.
*/

void RTint_Listen (unsigned int untilInterrupt, RTint_DespatchVector call, unsigned int pri);

/*
   Max - returns the maximum: i or j.
*/

static int Max (int i, int j);
static int Min (int i, int j);

/*
   FindVector - searches the exists list for a vector of type, t,
                which is associated with file descriptor, fd.
*/

static Vector FindVector (int fd, VectorType t);

/*
   FindVectorNo - searches the Exists list for vector, vec.
*/

static Vector FindVectorNo (unsigned int vec);

/*
   FindPendingVector - searches the pending list for vector, vec.
*/

static Vector FindPendingVector (unsigned int vec);

/*
   AddFd - adds the file descriptor, fd, to set, s, updating, max.
*/

static void AddFd (Selective_SetOfFd *s, int *max, int fd);

/*
   DumpPendingQueue - displays the pending queue.
*/

static void DumpPendingQueue (void);

/*
   DumpPendingQueue - displays the pending queue.
*/

static void stop (void);

/*
   AddTime - t1 := t1 + t2
*/

static void AddTime (Selective_Timeval t1, Selective_Timeval t2);

/*
   IsGreaterEqual - returns TRUE if, a>=b
*/

static unsigned int IsGreaterEqual (Selective_Timeval a, Selective_Timeval b);

/*
   SubTime - assigns, s and m, to a - b.
*/

static void SubTime (unsigned int *s, unsigned int *m, Selective_Timeval a, Selective_Timeval b);

/*
   Init - 
*/

static void Init (void);


/*
   Max - returns the maximum: i or j.
*/

static int Max (int i, int j)
{
  if (i > j)
    return i;
  else
    return j;
}

static int Min (int i, int j)
{
  /* 
   Max - returns the minimum: i or j.
  */
  if (i < j)
    return i;
  else
    return j;
}


/*
   FindVector - searches the exists list for a vector of type, t,
                which is associated with file descriptor, fd.
*/

static Vector FindVector (int fd, VectorType t)
{
  Vector v;

  v = Exists;
  while (v != NULL)
    {
      if ((v->type == t) && (v->File == fd))
        return v;
      v = v->exists;
    }
  return NULL;
}


/*
   FindVectorNo - searches the Exists list for vector, vec.
*/

static Vector FindVectorNo (unsigned int vec)
{
  Vector v;

  v = Exists;
  while ((v != NULL) && (v->no != vec))
    v = v->exists;
  return v;
}


/*
   FindPendingVector - searches the pending list for vector, vec.
*/

static Vector FindPendingVector (unsigned int vec)
{
  unsigned int i;
  Vector v;

  for (i=COROUTINES_UnassignedPriority; i<=7; i++)
    {
      v = Pending.array[i-(COROUTINES_UnassignedPriority)];
      while ((v != NULL) && (v->no != vec))
        v = v->pending;
      if ((v != NULL) && (v->no == vec))
        return v;
    }
  return NULL;
}


/*
   AddFd - adds the file descriptor, fd, to set, s, updating, max.
*/

static void AddFd (Selective_SetOfFd *s, int *max, int fd)
{
  (*max) = Max (fd, (*max));
  if ((*s) == NULL)
    {
      (*s) = Selective_InitSet ();
      Selective_FdZero ((*s));
    }
  /* printf('%d, ', fd)  */
  Selective_FdSet (fd, (*s));
}


/*
   DumpPendingQueue - displays the pending queue.
*/

static void DumpPendingQueue (void)
{
  COROUTINES_PROTECTION p;
  Vector v;
  unsigned int s;
  unsigned int m;

  libc_printf ((char *) "Pending queue\\n", 15);
  for (p=COROUTINES_UnassignedPriority; p<=7; p++)
    {
      libc_printf ((char *) "[%d]  ", 6, p);
      v = Pending.array[p-(COROUTINES_UnassignedPriority)];
      while (v != NULL)
        {
          if ((v->type == input) || (v->type == output))
            libc_printf ((char *) "(fd=%d) (vec=%d)", 16, v->File, v->no);
          else if (v->type == time)
            {
              Selective_GetTime (v->rel, &s, &m);
              Assertion_Assert (m < Microseconds);
              libc_printf ((char *) "time (%d.%6d secs)\\n", 20, s, m);
            }
          v = v->pending;
        }
      libc_printf ((char *) " \\n", 3);
    }
}


/*
   DumpPendingQueue - displays the pending queue.
*/

static void stop (void)
{
}


/*
   AddTime - t1 := t1 + t2
*/

static void AddTime (Selective_Timeval t1, Selective_Timeval t2)
{
  unsigned int a;
  unsigned int b;
  unsigned int s;
  unsigned int m;

  Selective_GetTime (t1, &s, &m);
  Assertion_Assert (m < Microseconds);
  Selective_GetTime (t2, &a, &b);
  Assertion_Assert (b < Microseconds);
  a += s;
  b += m;
  if (b >= Microseconds)
    {
      b -= Microseconds;
      a += 1;
    }
  Selective_SetTime (t1, a, b);
}


/*
   IsGreaterEqual - returns TRUE if, a>=b
*/

static unsigned int IsGreaterEqual (Selective_Timeval a, Selective_Timeval b)
{
  unsigned int as;
  unsigned int am;
  unsigned int bs;
  unsigned int bm;

  Selective_GetTime (a, &as, &am);
  Assertion_Assert (am < Microseconds);
  Selective_GetTime (b, &bs, &bm);
  Assertion_Assert (bm < Microseconds);
  return (as > bs) || ((as == bs) && (am >= bm));
}


/*
   SubTime - assigns, s and m, to a - b.
*/

static void SubTime (unsigned int *s, unsigned int *m, Selective_Timeval a, Selective_Timeval b)
{
  unsigned int as;
  unsigned int am;
  unsigned int bs;
  unsigned int bm;

  Selective_GetTime (a, &as, &am);
  Assertion_Assert (am < Microseconds);
  Selective_GetTime (b, &bs, &bm);
  Assertion_Assert (bm < Microseconds);
  if (IsGreaterEqual (a, b))
    {
      (*s) = as-bs;
      if (am >= bm)
        {
          (*m) = am-bm;
          Assertion_Assert ((*m) < Microseconds);
        }
      else
        {
          Assertion_Assert ((*s) > 0);
          (*s) -= 1;
          (*m) = (Microseconds+am)-bm;
          Assertion_Assert ((*m) < Microseconds);
        }
    }
  else
    {
      (*s) = 0;
      (*m) = 0;
    }
}


/*
   Init - 
*/

static void Init (void)
{
  COROUTINES_PROTECTION p;

  Exists = NULL;
  for (p=COROUTINES_UnassignedPriority; p<=7; p++)
    Pending.array[p-(COROUTINES_UnassignedPriority)] = NULL;
}


/*
   InitInputVector - returns an interrupt vector which is associated
                     with the file descriptor, fd.
*/

unsigned int RTint_InitInputVector (int fd, unsigned int pri)
{
  Vector v;

  if (Debugging)
    libc_printf ((char *) "InitInputVector fd = %d priority = %d\\n", 39, fd, pri);
  v = FindVector (fd, (VectorType) input);
  if (v == NULL)
    {
      Storage_ALLOCATE ((void **) &v, sizeof (_T1));
      VecNo += 1;
      v->type = input;
      v->priority = pri;
      v->arg = NULL;
      v->pending = NULL;
      v->exists = Exists;
      v->no = VecNo;
      v->File = fd;
      Exists = v;
      return VecNo;
    }
  else
    return v->no;
}


/*
   InitOutputVector - returns an interrupt vector which is associated
                      with the file descriptor, fd.
*/

unsigned int RTint_InitOutputVector (int fd, unsigned int pri)
{
  Vector v;

  v = FindVector (fd, (VectorType) output);
  if (v == NULL)
    {
      Storage_ALLOCATE ((void **) &v, sizeof (_T1));
      VecNo += 1;
      v->type = output;
      v->priority = pri;
      v->arg = NULL;
      v->pending = NULL;
      v->exists = Exists;
      v->no = VecNo;
      v->File = fd;
      Exists = v;
      return VecNo;
    }
  else
    return v->no;
}


/*
   InitTimeVector - returns an interrupt vector associated with
                    the relative time.
*/

unsigned int RTint_InitTimeVector (unsigned int micro, unsigned int secs, unsigned int pri)
{
  Vector v;

  Storage_ALLOCATE ((void **) &v, sizeof (_T1));
  VecNo += 1;
  Assertion_Assert (micro < Microseconds);
  v->type = time;
  v->priority = pri;
  v->arg = NULL;
  v->pending = NULL;
  v->exists = Exists;
  v->no = VecNo;
  v->rel = Selective_InitTime (secs+DebugTime, micro);
  v->abs_ = Selective_InitTime (0, 0);
  v->queued = FALSE;
  Exists = v;
  return VecNo;
}


/*
   ReArmTimeVector - reprimes the vector, vec, to deliver an interrupt
                     at the new relative time.
*/

void RTint_ReArmTimeVector (unsigned int vec, unsigned int micro, unsigned int secs)
{
  Vector v;

  Assertion_Assert (micro < Microseconds);
  v = FindVectorNo (vec);
  if (v == NULL)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.mod", 64, 256, (char *) "ReArmTimeVector", 15, (char *) "cannot find vector supplied", 27);
  else
    Selective_SetTime (v->rel, secs+DebugTime, micro);
}


/*
   GetTimeVector - assigns, micro, and, secs, with the remaining
                   time before this interrupt will expire.
                   This value is only updated when a Listen
                   occurs.
*/

void RTint_GetTimeVector (unsigned int vec, unsigned int *micro, unsigned int *secs)
{
  Vector v;

  v = FindVectorNo (vec);
  if (v == NULL)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.mod", 64, 280, (char *) "GetTimeVector", 13, (char *) "cannot find vector supplied", 27);
  else
    {
      Selective_GetTime (v->rel, secs, micro);
      Assertion_Assert ((*micro) < Microseconds);
    }
}


/*
   AttachVector - adds the pointer, p, to be associated with the interrupt
                  vector. It returns the previous value attached to this
                  vector.
*/

void * RTint_AttachVector (unsigned int vec, void * p)
{
  Vector v;
  void * l;

  v = FindVectorNo (vec);
  if (v == NULL)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.mod", 64, 305, (char *) "AttachVector", 12, (char *) "cannot find vector supplied", 27);
  else
    {
      l = v->arg;
      v->arg = p;
      return l;
    }
  ReturnException ("/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.def", 2, 1);
}


/*
   IncludeVector - includes, vec, into the despatcher list of
                   possible interrupt causes.
*/

void RTint_IncludeVector (unsigned int vec)
{
  Vector v;
  unsigned int m;
  unsigned int s;
  int r;

  v = FindPendingVector (vec);
  if (v == NULL)
    {
      v = FindVectorNo (vec);
      if (v == NULL)
        M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.mod", 64, 331, (char *) "IncludeVector", 13, (char *) "cannot find vector supplied", 27);
      else
        {
          /* printf('including vector %d  (fd = %d)
          ', vec, v^.File) ;  */
          v->pending = Pending.array[v->priority-(COROUTINES_UnassignedPriority)];
          Pending.array[v->priority-(COROUTINES_UnassignedPriority)] = v;
          if ((v->type == time) && ! v->queued)
            {
              v->queued = TRUE;
              r = Selective_GetTimeOfDay (v->abs_);
              Assertion_Assert (r == 0);
              Selective_GetTime (v->abs_, &s, &m);
              Assertion_Assert (m < Microseconds);
              AddTime (v->abs_, v->rel);
              Selective_GetTime (v->abs_, &s, &m);
              Assertion_Assert (m < Microseconds);
            }
        }
    }
  else
    {
      if (Debugging)
        libc_printf ((char *) "odd vector %d (fd %d) is already attached to the pending queue\\n", 64, vec, v->File);
      stop ();
    }
}


/*
   ExcludeVector - excludes, vec, from the despatcher list of
                   possible interrupt causes.
*/

void RTint_ExcludeVector (unsigned int vec)
{
  Vector v;
  Vector u;

  v = FindPendingVector (vec);
  if (v == NULL)
    M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.mod", 64, 372, (char *) "ExcludeVector", 13, (char *) "cannot find pending vector supplied", 35);
  else
    {
      /* printf('excluding vector %d
      ', vec) ;  */
      if (Pending.array[v->priority-(COROUTINES_UnassignedPriority)] == v)
        Pending.array[v->priority-(COROUTINES_UnassignedPriority)] = Pending.array[v->priority-(COROUTINES_UnassignedPriority)]->pending;
      else
        {
          u = Pending.array[v->priority-(COROUTINES_UnassignedPriority)];
          while (u->pending != v)
            u = u->pending;
          u->pending = v->pending;
        }
      if (v->type == time)
        v->queued = FALSE;
    }
}


/*
   Listen - will either block indefinitely (until an interrupt)
            or alteratively will test to see whether any interrupts
            are pending.
            If a pending interrupt was found then, call, is called
            and then this procedure returns.
            It only listens for interrupts > pri.
*/

void RTint_Listen (unsigned int untilInterrupt, RTint_DespatchVector call, unsigned int pri)
{
  unsigned int found;
  int r;
  Selective_Timeval b4;
  Selective_Timeval after;
  Selective_Timeval t;
  Vector v;
  Selective_SetOfFd i;
  Selective_SetOfFd o;
  unsigned int b4s;
  unsigned int b4m;
  unsigned int afs;
  unsigned int afm;
  unsigned int s;
  unsigned int m;
  int maxFd;
  unsigned int p;

  if (pri < (7))
    {
      if (Debugging)
        DumpPendingQueue ();
      maxFd = -1;
      t = NULL;
      i = NULL;
      o = NULL;
      t = Selective_InitTime ((unsigned int) INT_MAX, 0);
      p = 7;
      found = FALSE;
      while (p > pri)
        {
          v = Pending.array[p-(COROUTINES_UnassignedPriority)];
          while (v != NULL)
            {
              switch (v->type)
                {
                  case input:
                    AddFd (&i, &maxFd, v->File);
                    break;

                  case output:
                    AddFd (&o, &maxFd, v->File);
                    break;

                  case time:
                    if (IsGreaterEqual (t, v->abs_))
                      {
                        Selective_GetTime (v->abs_, &s, &m);
                        Assertion_Assert (m < Microseconds);
                        if (Debugging)
                          libc_printf ((char *) "shortest delay is %d.%d\\n", 25, s, m);
                        Selective_SetTime (t, s, m);
                        found = TRUE;
                      }
                    break;


                  default:
                    CaseException ("/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.def", 2, 1);
                }
              v = v->pending;
            }
          p -= 1;
        }
      if (! untilInterrupt)
        Selective_SetTime (t, 0, 0);
      if (((untilInterrupt && (i == NULL)) && (o == NULL)) && ! found)
        M2RTS_Halt ((char *) "/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.mod", 64, 592, (char *) "Listen", 6, (char *) "deadlock found, no more processes to run and no interrupts active", 65);
      /* printf('}
      ') ;  */
      if (((! found && (maxFd == -1)) && (i == NULL)) && (o == NULL))
        {
          t = Selective_KillTime (t);
          return;
        }
      else
        {
          Selective_GetTime (t, &s, &m);
          Assertion_Assert (m < Microseconds);
          b4 = Selective_InitTime (0, 0);
          after = Selective_InitTime (0, 0);
          r = Selective_GetTimeOfDay (b4);
          Assertion_Assert (r == 0);
          SubTime (&s, &m, t, b4);
          Selective_SetTime (t, s, m);
          if (Debugging)
            libc_printf ((char *) "select waiting for %u.%u seconds\\n", 34, s, m);
          do {
            r = pth_pth_select (maxFd+1, (void *) i, (void *) o, NULL, (void *) t);
            if (r == -1)
              {
                libc_perror ((char *) "pth_select", 10);
                r = pth_pth_select (maxFd+1, (void *) i, (void *) o, NULL, NULL);
                if (r == -1)
                  libc_perror ((char *) "pth_select timeout argument is faulty", 37);
                r = pth_pth_select (maxFd+1, (void *) i, NULL, NULL, (void *) t);
                if (r == -1)
                  libc_perror ((char *) "pth_select output fd argument is faulty", 39);
                r = pth_pth_select (maxFd+1, NULL, (void *) o, NULL, (void *) t);
                if (r == -1)
                  libc_perror ((char *) "pth_select input fd argument is faulty", 38);
                else
                  libc_perror ((char *) "pth_select maxFD+1 argument is faulty", 37);
              }
          } while (! (r != -1));
        }
      p = 7;
      while (p > pri)
        {
          v = Pending.array[p-(COROUTINES_UnassignedPriority)];
          while (v != NULL)
            {
              switch (v->type)
                {
                  case input:
                    if ((i != NULL) && (Selective_FdIsSet (v->File, i)))
                      {
                        if (Debugging)
                          {
                            libc_printf ((char *) "read (fd=%d) is ready (vec=%d)\\n", 32, v->File, v->no);
                            DumpPendingQueue ();
                          }
                        (*call.proc) (v->no, v->priority, v->arg);
                      }
                    break;

                  case output:
                    if ((o != NULL) && (Selective_FdIsSet (v->File, o)))
                      {
                        if (Debugging)
                          {
                            libc_printf ((char *) "write (fd=%d) is ready (vec=%d)\\n", 33, v->File, v->no);
                            DumpPendingQueue ();
                          }
                        (*call.proc) (v->no, v->priority, v->arg);
                      }
                    break;

                  case time:
                    if (untilInterrupt || TRUE)
                      {
                        r = Selective_GetTimeOfDay (after);
                        Assertion_Assert (r == 0);
                        if (Debugging)
                          {
                            Selective_GetTime (t, &s, &m);
                            Assertion_Assert (m < Microseconds);
                            Selective_GetTime (after, &afs, &afm);
                            Assertion_Assert (afm < Microseconds);
                            Selective_GetTime (b4, &b4s, &b4m);
                            Assertion_Assert (b4m < Microseconds);
                            libc_printf ((char *) "waited %d.%d + %d.%d now is %d.%d\\n", 35, s, m, b4s, b4m, afs, afm);
                          }
                        if (IsGreaterEqual (after, v->abs_))
                          {
                            if (Debugging)
                              {
                                DumpPendingQueue ();
                                libc_printf ((char *) "time has expired calling despatcher\\n", 37);
                              }
                            (*call.proc) (v->no, v->priority, v->arg);
                          }
                        else if (Debugging)
                          libc_printf ((char *) "must wait longer as time has not expired\\n", 42);
                      }
                    break;


                  default:
                    CaseException ("/home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/RTint.def", 2, 1);
                }
              v = v->pending;
            }
          p -= 1;
        }
      if (t != NULL)
        t = Selective_KillTime (t);
      if (b4 != NULL)
        t = Selective_KillTime (b4);
      if (after != NULL)
        t = Selective_KillTime (after);
      if (i != NULL)
        i = Selective_KillSet (i);
      if (o != NULL)
        o = Selective_KillSet (o);
    }
}

void _M2_RTint_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_RTint_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
