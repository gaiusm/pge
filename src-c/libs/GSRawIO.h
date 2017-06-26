/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/SRawIO.def.  */


#if !defined (_SRawIO_H)
#   define _SRawIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_SRawIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
 Reading and writing data over default channels using raw operations, that is, with no
     conversion or interpretation. The read result is of the type IOConsts.ReadResults.
  */

EXTERN void SRawIO_Read (unsigned char *to, unsigned int _to_high);
EXTERN void SRawIO_Write (unsigned char *from_, unsigned int _from_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
