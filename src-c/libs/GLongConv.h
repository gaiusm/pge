/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/LongConv.def.  */


#if !defined (_LongConv_H)
#   define _LongConv_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GConvTypes.h"

#   if defined (_LongConv_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef ConvTypes_ConvResults LongConv_ConvResults;

EXTERN void LongConv_ScanReal (char inputCh, ConvTypes_ScanClass *chClass, ConvTypes_ScanState *nextState);
EXTERN LongConv_ConvResults LongConv_FormatReal (char *str_, unsigned int _str_high);
EXTERN long double LongConv_ValueReal (char *str_, unsigned int _str_high);
EXTERN unsigned int LongConv_LengthFloatReal (long double real, unsigned int sigFigs);
EXTERN unsigned int LongConv_LengthEngReal (long double real, unsigned int sigFigs);
EXTERN unsigned int LongConv_LengthFixedReal (long double real, int place);
EXTERN unsigned int LongConv_IsRConvException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
