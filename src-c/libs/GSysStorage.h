/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/SysStorage.def.  */


#if !defined (_SysStorage_H)
#   define _SysStorage_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_SysStorage_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   ALLOCATE - attempt to allocate memory from the heap.
              NIL is returned in, a, if ALLOCATE fails.
*/

EXTERN void SysStorage_ALLOCATE (void * *a, unsigned int Size);

/*
   DEALLOCATE - return, Size, bytes to the heap.
                The variable, a, is set to NIL.
*/

EXTERN void SysStorage_DEALLOCATE (void * *a, unsigned int Size);

/*
   REALLOCATE - attempts to reallocate storage. The address,
                a, should either be NIL in which case ALLOCATE
                is called, or alternatively it should have already
                been initialized by ALLOCATE. The allocated storage
                is resized accordingly.
*/

EXTERN void SysStorage_REALLOCATE (void * *a, unsigned int Size);

/*
   Available - returns TRUE if, Size, bytes can be allocated.
*/

EXTERN unsigned int SysStorage_Available (unsigned int Size);

/*
   Init - initializes the heap.
*/

EXTERN void SysStorage_Init (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
