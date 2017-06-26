/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/ShortWholeIO.def.  */


#if !defined (_ShortWholeIO_H)
#   define _ShortWholeIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_ShortWholeIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void ShortWholeIO_ReadInt (IOChan_ChanId cid, short int *int_);
EXTERN void ShortWholeIO_WriteInt (IOChan_ChanId cid, short int int_, unsigned int width);
EXTERN void ShortWholeIO_ReadCard (IOChan_ChanId cid, short unsigned int *card);
EXTERN void ShortWholeIO_WriteCard (IOChan_ChanId cid, short unsigned int card, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
