/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RealStr.def.  */


#if !defined (_RealStr_H)
#   define _RealStr_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GConvTypes.h"

#   if defined (_RealStr_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef ConvTypes_ConvResults RealStr_ConvResults;

EXTERN void RealStr_StrToReal (char *str_, unsigned int _str_high, double *real, RealStr_ConvResults *res);
EXTERN void RealStr_RealToFloat (double real, unsigned int sigFigs, char *str, unsigned int _str_high);
EXTERN void RealStr_RealToEng (double real, unsigned int sigFigs, char *str, unsigned int _str_high);
EXTERN void RealStr_RealToFixed (double real, int place, char *str, unsigned int _str_high);
EXTERN void RealStr_RealToStr (double real, char *str, unsigned int _str_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
