/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/WholeIO.def.  */


#if !defined (_WholeIO_H)
#   define _WholeIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_WholeIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void WholeIO_ReadInt (IOChan_ChanId cid, int *int_);
EXTERN void WholeIO_WriteInt (IOChan_ChanId cid, int int_, unsigned int width);
EXTERN void WholeIO_ReadCard (IOChan_ChanId cid, unsigned int *card);
EXTERN void WholeIO_WriteCard (IOChan_ChanId cid, unsigned int card, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
