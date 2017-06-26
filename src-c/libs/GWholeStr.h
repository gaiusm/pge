/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/WholeStr.def.  */


#if !defined (_WholeStr_H)
#   define _WholeStr_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GConvTypes.h"

#   if defined (_WholeStr_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef ConvTypes_ConvResults WholeStr_ConvResults;

EXTERN void WholeStr_StrToInt (char *str_, unsigned int _str_high, int *int_, WholeStr_ConvResults *res);
EXTERN void WholeStr_IntToStr (int int_, char *str, unsigned int _str_high);
EXTERN void WholeStr_StrToCard (char *str_, unsigned int _str_high, unsigned int *card, WholeStr_ConvResults *res);
EXTERN void WholeStr_CardToStr (unsigned int card, char *str, unsigned int _str_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
