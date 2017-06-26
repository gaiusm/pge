/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RealConv.def.  */


#if !defined (_RealConv_H)
#   define _RealConv_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GConvTypes.h"

#   if defined (_RealConv_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef ConvTypes_ConvResults RealConv_ConvResults;

EXTERN void RealConv_ScanReal (char inputCh, ConvTypes_ScanClass *chClass, ConvTypes_ScanState *nextState);
EXTERN RealConv_ConvResults RealConv_FormatReal (char *str_, unsigned int _str_high);
EXTERN double RealConv_ValueReal (char *str_, unsigned int _str_high);
EXTERN unsigned int RealConv_LengthFloatReal (double real, unsigned int sigFigs);
EXTERN unsigned int RealConv_LengthEngReal (double real, unsigned int sigFigs);
EXTERN unsigned int RealConv_LengthFixedReal (double real, int place);
EXTERN unsigned int RealConv_IsRConvException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
