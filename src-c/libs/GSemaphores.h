/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/Semaphores.def.  */


#if !defined (_Semaphores_H)
#   define _Semaphores_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_Semaphores_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (Semaphores_SEMAPHORE_D)
#  define Semaphores_SEMAPHORE_D
   typedef void *Semaphores_SEMAPHORE;
#endif

EXTERN void Semaphores_Create (Semaphores_SEMAPHORE *s, unsigned int initialCount);
EXTERN void Semaphores_Destroy (Semaphores_SEMAPHORE *s);
EXTERN void Semaphores_Claim (Semaphores_SEMAPHORE s);
EXTERN void Semaphores_Release (Semaphores_SEMAPHORE s);
EXTERN unsigned int Semaphores_CondClaim (Semaphores_SEMAPHORE s);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
