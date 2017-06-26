/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/ErrnoCategory.def.  */


#if !defined (_ErrnoCategory_H)
#   define _ErrnoCategory_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GChanConsts.h"

#   if defined (_ErrnoCategory_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   IsErrnoHard - returns TRUE if the value of errno is associated with
                 a hard device error.
*/

EXTERN unsigned int ErrnoCategory_IsErrnoHard (int e);

/*
   IsErrnoSoft - returns TRUE if the value of errno is associated with
                 a soft device error.
*/

EXTERN unsigned int ErrnoCategory_IsErrnoSoft (int e);

/*
   UnAvailable - returns TRUE if the value of errno indicates that
                 the resource or device is unavailable for some
                 reason.
*/

EXTERN unsigned int ErrnoCategory_UnAvailable (int e);

/*
   GetOpenResults - maps errno onto the ISO Modula-2 enumerated
                    type, OpenResults.
*/

EXTERN ChanConsts_OpenResults ErrnoCategory_GetOpenResults (int e);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
