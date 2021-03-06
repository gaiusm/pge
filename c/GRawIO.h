/* do not edit automatically generated by mc from RawIO.  */
/* Library module defined by the International Standard
   Information technology - programming languages
   BS ISO/IEC 10514-1:1996E Part 1: Modula-2, Base Language.

   Copyright ISO/IEC (International Organization for Standardization
   and International Electrotechnical Commission) 1996-2020.

   It may be freely copied for the purpose of implementation (see page
   707 of the Information technology - Programming languages Part 1:
   Modula-2, Base Language.  BS ISO/IEC 10514-1:1996).  */


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
