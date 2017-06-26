/* automatically created by mc from ../GC.mod.  */

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
#define _GC_H
#define _GC_C

#   include "GAssertion.h"
#   include "GIndexing.h"
#   include "GStorage.h"
#   include "GSYSTEM.h"
#   include "Glibc.h"
#   include "GDynamicStrings.h"
#   include "Ggdbif.h"
#   include "GM2RTS.h"

typedef struct GC_walkP_p GC_walkP;

typedef struct GC_callP_p GC_callP;

#   define EnableChecking TRUE
#   define PoisonOn TRUE
#   define GGCPOISON 0x0A5A5A5A5
#   define TraceOn FALSE
#   define StatsOn FALSE
typedef struct _T1_r _T1;

typedef struct _T2_r _T2;

typedef _T2 *callBack;

typedef struct _T3_r _T3;

typedef enum {free, marked, used} stateValues;

typedef unsigned int state;

typedef _T1 *GC_garbage;

typedef _T3 *GC_entity;

typedef void (*GC_walkP_t) (void *);
struct GC_walkP_p { GC_walkP_t proc; };

typedef void (*GC_callP_t) (void);
struct GC_callP_p { GC_callP_t proc; };

struct _T3_r {
               void *data;
               unsigned int rIndex;
               state status;
               GC_entity next;
             };

struct _T1_r {
               Indexing_Index roots;
               Indexing_Index allocated;
               unsigned int bytes;
               DynamicStrings_String desc;
               GC_walkP walkp;
               callBack callbacks;
               GC_entity freeList;
               GC_garbage next;
             };

struct _T2_r {
               GC_callP callp;
               callBack next;
             };

static GC_garbage headOfGarbage;

/*
   initGarbage - initialises a garbage heap which manages a dynamically
                 allocated data type of noOfBytes length.  It must be
                 the same data structure which is walked by, walkP.
*/

GC_garbage GC_initGarbage (GC_walkP p, unsigned int noOfBytes, DynamicStrings_String typeName);

/*
   collect - collect all used entities and place them onto the free list.
*/

void GC_collect (GC_garbage g);

/*
   markEntity - sets the status of entity, e, to marked.
*/

void GC_markEntity (GC_entity e);

/*
   allocate - returns allocated memory from, a.  It also
              returns entity, e, which is associated with, a.
*/

void GC_allocate (GC_garbage g, GC_entity *e, void * *a);

/*
   rootAllocate - returns allocated memory from, a, with length, bytes.  It also
                  returns entity, e, which is associated with, a.

                  It registers this entity in the root of the garbage collection.
*/

void GC_rootAllocate (GC_garbage g, GC_entity *e, void * *a);

/*
   rootDeallocate - deallocates memory from, a, with length, bytes.
                    It also unregisters entity, e, from the root.
*/

void GC_rootDeallocate (GC_garbage g, GC_entity *e, void * *a);

/*
   rootEntity - records data, a, to be part of the roots in heap, g.
                Useful if an entity was created using, allocate,
                and now needs to be remembered.
*/

void GC_rootEntity (GC_garbage g, GC_entity e, void * a);

/*
   getData - returns the address associated with entity, e.
*/

void * GC_getData (GC_entity e);

/*
   registerCallback - call procedure, p, when the garbage collector is marking used entities.
*/

void GC_registerCallback (GC_garbage g, GC_callP p);

/*
   collectAll - run the garbage collection on all heaps.
*/

void GC_collectAll (void);

/*
   RunCallBacks - runs all the call backs associated with, g.
*/

static void RunCallBacks (GC_garbage g);

/*
   unMarkAll -
*/

static void unMarkAll (void);

/*
   walkRootsAll -
*/

static void walkRootsAll (void);

/*
   tidyUpAll -
*/

static void tidyUpAll (void);

/*
   tidyUpEntities -
*/

static void tidyUpEntities (GC_garbage g);

/*
   unMarkEntity - sets the status of entity, e, to nothing.
*/

static void unMarkEntity (GC_entity e);

/*
   initEntity - records data, a, to be managed by heap, g.  Note that
                it is not rooted.
*/

static void initEntity (GC_garbage g, void * a, GC_entity e);

/*
   newEntity - initialises an entity.
*/

static void newEntity (GC_entity e, void * a);

/*
   findFree - use the free list of, g, to find a spare entity and associated address.
*/

static void findFree (GC_garbage g, GC_entity *e, void * *a);

/*
   Init - initialise the global data structures.
*/

static void Init (void);


/*
   RunCallBacks - runs all the call backs associated with, g.
*/

static void RunCallBacks (GC_garbage g)
{
  callBack c;

  c = g->callbacks;
  while (c != NULL)
    {
      (*c->callp.proc) ();
      c = c->next;
    }
}


/*
   unMarkAll -
*/

static void unMarkAll (void)
{
  GC_garbage g;
  void * a;
  unsigned int d;

  g = headOfGarbage;
  while (g != NULL)
    {
      if (StatsOn)
        {
          a = DynamicStrings_string (g->desc);
          libc_printf ((char *) "garbage collecting on the %s heap", 33, a);
          d = Indexing_HighIndice (g->allocated);
          libc_printf ((char *) ", total entities %d", 19, d);
          d = Indexing_HighIndice (g->roots);
          libc_printf ((char *) ", rooted entities %d\\n", 22, d);
        }
      g->freeList = NULL;
      Indexing_ForeachIndiceInIndexDo (g->allocated, (Indexing_IndexProcedure) {(Indexing_IndexProcedure_t) unMarkEntity});
      g = g->next;
    }
}


/*
   walkRootsAll -
*/

static void walkRootsAll (void)
{
  GC_garbage g;
  void * a;

  g = headOfGarbage;
  while (g != NULL)
    {
      if (StatsOn)
        {
          a = DynamicStrings_string (g->desc);
          libc_printf ((char *) " marking all entities in the roots of %s\\n", 42, a);
        }
      Indexing_ForeachIndiceInIndexDo (g->roots, (Indexing_IndexProcedure) {(Indexing_IndexProcedure_t) GC_markEntity});
      if (StatsOn)
        libc_printf ((char *) " walking all entities in the roots of %s\\n", 42, a);
      Indexing_ForeachIndiceInIndexDo (g->roots, (Indexing_IndexProcedure) {(Indexing_IndexProcedure_t) g->walkp.proc});
      if (StatsOn)
        libc_printf ((char *) " running all call backs associated with %s\\n", 44, a);
      RunCallBacks (g);
      g = g->next;
    }
}


/*
   tidyUpAll -
*/

static void tidyUpAll (void)
{
  GC_garbage g;
  void * a;

  g = headOfGarbage;
  while (g != NULL)
    {
      if (StatsOn)
        {
          a = DynamicStrings_string (g->desc);
          libc_printf ((char *) " %s heap now has: ", 18, a);
        }
      tidyUpEntities (g);
      g = g->next;
    }
}


/*
   tidyUpEntities -
*/

static void tidyUpEntities (GC_garbage g)
{
  unsigned int u;
  unsigned int f;
  unsigned int i;
  GC_entity e;

  u = 0;
  f = 0;
  i = Indexing_LowIndice (g->allocated);
  while (i <= (Indexing_HighIndice (g->allocated)))
    {
      e = Indexing_GetIndice (g->allocated, i);
      if ((((1 << (marked-free)) & (e->status)) != 0))
        {
          u += 1;
          e->status = (state) ((1 << (used-free)));
        }
      else
        {
          f += 1;
          e->next = g->freeList;
          g->freeList = e;
          e->status = (state) ((1 << (free-free)));
          if (PoisonOn)
            if ((libc_memset (e->data, GGCPOISON, g->bytes)) == NULL)
              {}  /* empty.  */
        }
      i += 1;
    }
  if (StatsOn)
    libc_printf ((char *) " used %d, and, freed %d\\n", 25, u, f);
}


/*
   unMarkEntity - sets the status of entity, e, to nothing.
*/

static void unMarkEntity (GC_entity e)
{
  void * a;

  if (TraceOn)
    {
      a = e->data;
      libc_printf ((char *) "unmarking address 0x%x using entity (0x%x)\\n", 44, a, e);
    }
  e->status &= (~(1 << (marked-free )));
}


/*
   initEntity - records data, a, to be managed by heap, g.  Note that
                it is not rooted.
*/

static void initEntity (GC_garbage g, void * a, GC_entity e)
{
  unsigned int i;
  unsigned int h;
  GC_entity en;

  i = Indexing_LowIndice (g->allocated);
  h = Indexing_HighIndice (g->allocated);
  while (i <= h)
    {
      en = Indexing_GetIndice (g->allocated, i);
      if (en->data == a)
        {
          if (en != e)
            M2RTS_HALT (0);
          return;
        }
      else
        i += 1;
    }
  Indexing_PutIndice (g->allocated, (Indexing_HighIndice (g->allocated))+1, (void *) e);
}


/*
   newEntity - initialises an entity.
*/

static void newEntity (GC_entity e, void * a)
{
  e->data = a;
  e->rIndex = 0;
  e->status = (state) ((1 << (used-free)));
  e->next = NULL;
}


/*
   findFree - use the free list of, g, to find a spare entity and associated address.
*/

static void findFree (GC_garbage g, GC_entity *e, void * *a)
{
  if (g->freeList == NULL)
    {
      Storage_ALLOCATE (a, g->bytes);
      Storage_ALLOCATE ((void **) &(*e), sizeof (_T3));
    }
  else
    {
      (*e) = g->freeList;
      (*a) = (*e)->data;
      g->freeList = g->freeList->next;
    }
  newEntity ((*e), (*a));
}


/*
   Init - initialise the global data structures.
*/

static void Init (void)
{
  headOfGarbage = NULL;
}


/*
   initGarbage - initialises a garbage heap which manages a dynamically
                 allocated data type of noOfBytes length.  It must be
                 the same data structure which is walked by, walkP.
*/

GC_garbage GC_initGarbage (GC_walkP p, unsigned int noOfBytes, DynamicStrings_String typeName)
{
  GC_garbage g;

  Storage_ALLOCATE ((void **) &g, sizeof (_T1));
  g->roots = Indexing_InitIndex (1);
  g->allocated = Indexing_InitIndex (1);
  g->bytes = noOfBytes;
  g->desc = typeName;
  g->walkp = p;
  g->callbacks = NULL;
  g->freeList = NULL;
  g->next = headOfGarbage;
  headOfGarbage = g;
  return g;
}


/*
   collect - collect all used entities and place them onto the free list.
*/

void GC_collect (GC_garbage g)
{
  void * a;
  unsigned int d;

  if (StatsOn)
    {
      a = DynamicStrings_string (g->desc);
      libc_printf ((char *) "garbage collecting on the %s heap\\n", 35, a);
      d = Indexing_HighIndice (g->allocated);
      libc_printf ((char *) ", total entities %d", 19, d);
      d = Indexing_HighIndice (g->roots);
      libc_printf ((char *) ", rooted entities %d", 20, d);
    }
  g->freeList = NULL;
  Indexing_ForeachIndiceInIndexDo (g->allocated, (Indexing_IndexProcedure) {(Indexing_IndexProcedure_t) unMarkEntity});
  Indexing_ForeachIndiceInIndexDo (g->roots, (Indexing_IndexProcedure) {(Indexing_IndexProcedure_t) GC_markEntity});
  Indexing_ForeachIndiceInIndexDo (g->roots, (Indexing_IndexProcedure) {(Indexing_IndexProcedure_t) g->walkp.proc});
  RunCallBacks (g);
  tidyUpEntities (g);
}


/*
   markEntity - sets the status of entity, e, to marked.
*/

void GC_markEntity (GC_entity e)
{
  void * a;

  if (TraceOn)
    {
      a = e->data;
      libc_printf ((char *) "marking address 0x%x using entity (0x%x)\\n", 42, a, e);
    }
  Assertion_Assert (! ((((1 << (free-free)) & (e->status)) != 0)));
  e->status |= (1 << (marked-free ));
}


/*
   allocate - returns allocated memory from, a.  It also
              returns entity, e, which is associated with, a.
*/

void GC_allocate (GC_garbage g, GC_entity *e, void * *a)
{
  void * n;
  void * b;

  findFree (g, e, a);
  initEntity (g, (*a), (*e));
  if (TraceOn)
    {
      n = DynamicStrings_string (g->desc);
      b = (*e);
      libc_printf ((char *) "allocated 0x%x (byte length %d) using entity 0x%x associated with %s\\n", 70, (*a), g->bytes, b, n);
    }
}


/*
   rootAllocate - returns allocated memory from, a, with length, bytes.  It also
                  returns entity, e, which is associated with, a.

                  It registers this entity in the root of the garbage collection.
*/

void GC_rootAllocate (GC_garbage g, GC_entity *e, void * *a)
{
  void * n;

  GC_allocate (g, e, a);
  GC_rootEntity (g, (*e), (*a));
  if (TraceOn)
    {
      n = DynamicStrings_string (g->desc);
      libc_printf ((char *) " rooted address 0x%x (%s)\\n", 27, (*a), n);
    }
}


/*
   rootDeallocate - deallocates memory from, a, with length, bytes.
                    It also unregisters entity, e, from the root.
*/

void GC_rootDeallocate (GC_garbage g, GC_entity *e, void * *a)
{
  void * n;

  if ((((*e) != NULL) && ((*a) != NULL)) && ((*e)->rIndex != 0))
    {
      if (TraceOn)
        {
          n = DynamicStrings_string (g->desc);
          libc_printf ((char *) "unrooted address 0x%x (%s)\\n", 28, (*a), n);
        }
      Indexing_RemoveIndiceFromIndex (g->roots, (void *) (*e));
      (*e)->rIndex = 0;
    }
}


/*
   rootEntity - records data, a, to be part of the roots in heap, g.
                Useful if an entity was created using, allocate,
                and now needs to be remembered.
*/

void GC_rootEntity (GC_garbage g, GC_entity e, void * a)
{
  unsigned int i;
  GC_entity en;

  i = Indexing_LowIndice (g->roots);
  while (i <= (Indexing_HighIndice (g->roots)))
    {
      en = Indexing_GetIndice (g->roots, i);
      if (en->data == a)
        {
          if (en != e)
            M2RTS_HALT (0);
          return;
        }
      else
        i += 1;
    }
  e->rIndex = (Indexing_HighIndice (g->roots))+1;
  Indexing_PutIndice (g->roots, e->rIndex, (void *) e);
}


/*
   getData - returns the address associated with entity, e.
*/

void * GC_getData (GC_entity e)
{
  return e->data;
}


/*
   registerCallback - call procedure, p, when the garbage collector is marking used entities.
*/

void GC_registerCallback (GC_garbage g, GC_callP p)
{
  callBack c;

  Storage_ALLOCATE ((void **) &c, sizeof (_T2));
  c->next = g->callbacks;
  c->callp = p;
  g->callbacks = c;
}


/*
   collectAll - run the garbage collection on all heaps.
*/

void GC_collectAll (void)
{
  walkRootsAll ();
  unMarkAll ();
  walkRootsAll ();
  tidyUpAll ();
}

void _M2_GC_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_GC_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
