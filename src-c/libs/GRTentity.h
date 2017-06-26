/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RTentity.def.  */


#if !defined (_RTentity_H)
#   define _RTentity_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_RTentity_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (RTentity_Group_D)
#  define RTentity_Group_D
   typedef void *RTentity_Group;
#endif

EXTERN RTentity_Group RTentity_InitGroup (void);
EXTERN RTentity_Group RTentity_KillGroup (RTentity_Group g);
EXTERN unsigned int RTentity_GetKey (RTentity_Group g, void * a);
EXTERN void RTentity_PutKey (RTentity_Group g, void * a, unsigned int key);
EXTERN void RTentity_DelKey (RTentity_Group g, void * a);
EXTERN unsigned int RTentity_IsIn (RTentity_Group g, void * a);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
