/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/Storage.def.  */


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

typedef enum {Storage_nilDeallocation, Storage_pointerToUnallocatedStorage, Storage_wrongStorageToUnallocate} Storage_StorageExceptions;

EXTERN void Storage_ALLOCATE (void * *addr, unsigned int amount);
EXTERN void Storage_DEALLOCATE (void * *addr, unsigned int amount);
EXTERN void Storage_REALLOCATE (void * *addr, unsigned int amount);
EXTERN unsigned int Storage_IsStorageException (void);
EXTERN Storage_StorageExceptions Storage_StorageException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
