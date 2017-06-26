/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/LongIO.def.  */


#if !defined (_LongIO_H)
#   define _LongIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_LongIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void LongIO_ReadReal (IOChan_ChanId cid, long double *real);
EXTERN void LongIO_WriteFloat (IOChan_ChanId cid, long double real, unsigned int sigFigs, unsigned int width);
EXTERN void LongIO_WriteEng (IOChan_ChanId cid, long double real, unsigned int sigFigs, unsigned int width);
EXTERN void LongIO_WriteFixed (IOChan_ChanId cid, long double real, int place, unsigned int width);
EXTERN void LongIO_WriteReal (IOChan_ChanId cid, long double real, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
