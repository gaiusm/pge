/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/RawIO.def.  */


#if !defined (_RawIO_H)
#   define _RawIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"
#   include "GSYSTEM.h"

#   if defined (_RawIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
 Reading and writing data over specified channels using raw
     operations, that is, with no conversion or interpretation.
     The read result is of the type IOConsts.ReadResults.
  */

EXTERN void RawIO_Read (IOChan_ChanId cid, unsigned char *to, unsigned int _to_high);
EXTERN void RawIO_Write (IOChan_ChanId cid, unsigned char *from_, unsigned int _from_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
