/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/LongWholeIO.def.  */


#if !defined (_LongWholeIO_H)
#   define _LongWholeIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_LongWholeIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void LongWholeIO_ReadInt (IOChan_ChanId cid, long int *int_);
EXTERN void LongWholeIO_WriteInt (IOChan_ChanId cid, long int int_, unsigned int width);
EXTERN void LongWholeIO_ReadCard (IOChan_ChanId cid, long unsigned int *card);
EXTERN void LongWholeIO_WriteCard (IOChan_ChanId cid, long unsigned int card, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
