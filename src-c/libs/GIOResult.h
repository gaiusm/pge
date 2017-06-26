/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/IOResult.def.  */


#if !defined (_IOResult_H)
#   define _IOResult_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOConsts.h"
#   include "GIOChan.h"

#   if defined (_IOResult_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef IOConsts_ReadResults IOResult_ReadResults;


/*
    ReadResults =   This type is used to classify the result of an input operation 
    (
      notKnown,     no read result is set 
      allRight,     data is as expected or as required 
      outOfRange,   data cannot be represented 
      wrongFormat,  data not in expected format 
      endOfLine,    end of line seen before expected data 
      endOfInput    end of input seen before expected data 
    );
  */

EXTERN IOResult_ReadResults IOResult_ReadResult (IOChan_ChanId cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
