/* automatically created by mc from ../git-pge/m2/GC.def.  */


#if !defined (_GC_H)
#   define _GC_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"
#   include "GDynamicStrings.h"

#   if defined (_GC_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (GC_garbage_D)
#  define GC_garbage_D
   typedef void *GC_garbage;
#endif

#if !defined (GC_entity_D)
#  define GC_entity_D
   typedef void *GC_entity;
#endif

typedef struct GC_walkP_p GC_walkP;

typedef struct GC_callP_p GC_callP;

typedef void (*GC_walkP_t) (void *);
struct GC_walkP_p { GC_walkP_t proc; };

typedef void (*GC_callP_t) (void);
struct GC_callP_p { GC_callP_t proc; };


/*
   initGarbage - initialises a garbage heap which manages a dynamically
                 allocated data type of noOfBytes length.  It must be
                 the same data structure which is walked by, walkP.
*/

EXTERN GC_garbage GC_initGarbage (GC_walkP p, unsigned int noOfBytes, DynamicStrings_String typeName);

/*
   collect - collect all used entities and place them onto the free list.
*/

EXTERN void GC_collect (GC_garbage g);

/*
   markEntity - sets the status of entity, e, to marked.
*/

EXTERN void GC_markEntity (GC_entity e);

/*
   allocate - returns allocated memory from, a.  It also
              returns entity, e, which is associated with, a.
*/

EXTERN void GC_allocate (GC_garbage g, GC_entity *e, void * *a);

/*
   rootAllocate - returns allocated memory from, a, with length, bytes.  It also
                  returns entity, e, which is associated with, a.

                  It registers this entity in the root of the garbage collection.
*/

EXTERN void GC_rootAllocate (GC_garbage g, GC_entity *e, void * *a);

/*
   rootDeallocate - deallocates memory from, a, with length, bytes.
                    It also unregisters entity, e, from the root.
*/

EXTERN void GC_rootDeallocate (GC_garbage g, GC_entity *e, void * *a);

/*
   rootEntity - records data, a, to be part of the roots in heap, g.
                Useful if an entity was created using, allocate,
                and now needs to be remembered.
*/

EXTERN void GC_rootEntity (GC_garbage g, GC_entity e, void * a);

/*
   getData - returns the address associated with entity, e.
*/

EXTERN void * GC_getData (GC_entity e);

/*
   registerCallback - call procedure, p, when the garbage collector is marking used entities.
*/

EXTERN void GC_registerCallback (GC_garbage g, GC_callP p);

/*
   collectAll - run the garbage collection on all heaps.
*/

EXTERN void GC_collectAll (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
