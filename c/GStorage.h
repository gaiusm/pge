/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/Storage.def.  */


#if !defined (_Storage_H)
#   define _Storage_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_Storage_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   ALLOCATE - attempt to allocate memory from the heap.
              NIL is returned in, a, if ALLOCATE fails.
*/

EXTERN void Storage_ALLOCATE (void * *a, unsigned int Size);

/*
   DEALLOCATE - return, Size, bytes to the heap.
                The variable, a, is set to NIL.
*/

EXTERN void Storage_DEALLOCATE (void * *a, unsigned int Size);

/*
   REALLOCATE - attempts to reallocate storage. The address,
                a, should either be NIL in which case ALLOCATE
                is called, or alternatively it should have already
                been initialized by ALLOCATE. The allocated storage
                is resized accordingly.
*/

EXTERN void Storage_REALLOCATE (void * *a, unsigned int Size);

/*
   Available - returns TRUE if, Size, bytes can be allocated.
*/

EXTERN unsigned int Storage_Available (unsigned int Size);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
