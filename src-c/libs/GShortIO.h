/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/ShortIO.def.  */


#if !defined (_ShortIO_H)
#   define _ShortIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_ShortIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void ShortIO_ReadReal (IOChan_ChanId cid, float *real);
EXTERN void ShortIO_WriteFloat (IOChan_ChanId cid, float real, unsigned int sigFigs, unsigned int width);
EXTERN void ShortIO_WriteEng (IOChan_ChanId cid, float real, unsigned int sigFigs, unsigned int width);
EXTERN void ShortIO_WriteFixed (IOChan_ChanId cid, float real, int place, unsigned int width);
EXTERN void ShortIO_WriteReal (IOChan_ChanId cid, float real, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
