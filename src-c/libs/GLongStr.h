/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/LongStr.def.  */


#if !defined (_LongStr_H)
#   define _LongStr_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GConvTypes.h"

#   if defined (_LongStr_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef ConvTypes_ConvResults LongStr_ConvResults;

EXTERN void LongStr_StrToReal (char *str_, unsigned int _str_high, long double *real, LongStr_ConvResults *res);
EXTERN void LongStr_RealToFloat (long double real, unsigned int sigFigs, char *str, unsigned int _str_high);
EXTERN void LongStr_RealToEng (long double real, unsigned int sigFigs, char *str, unsigned int _str_high);
EXTERN void LongStr_RealToFixed (long double real, int place, char *str, unsigned int _str_high);
EXTERN void LongStr_RealToStr (long double real, char *str, unsigned int _str_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
