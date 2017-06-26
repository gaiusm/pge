/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/MemUtils.def.  */


#if !defined (_MemUtils_H)
#   define _MemUtils_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_MemUtils_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   MemCopy - copys a region of memory to the required destination.
*/

EXTERN void MemUtils_MemCopy (void * from, unsigned int length, void * to);

/*
   MemZero - sets a region of memory: a..a+length to zero.
*/

EXTERN void MemUtils_MemZero (void * a, unsigned int length);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
