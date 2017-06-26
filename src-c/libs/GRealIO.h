/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RealIO.def.  */


#if !defined (_RealIO_H)
#   define _RealIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_RealIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void RealIO_ReadReal (IOChan_ChanId cid, double *real);
EXTERN void RealIO_WriteFloat (IOChan_ChanId cid, double real, unsigned int sigFigs, unsigned int width);
EXTERN void RealIO_WriteEng (IOChan_ChanId cid, double real, unsigned int sigFigs, unsigned int width);
EXTERN void RealIO_WriteFixed (IOChan_ChanId cid, double real, int place, unsigned int width);
EXTERN void RealIO_WriteReal (IOChan_ChanId cid, double real, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
