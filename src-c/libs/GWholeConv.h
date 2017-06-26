/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/WholeConv.def.  */


#if !defined (_WholeConv_H)
#   define _WholeConv_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GConvTypes.h"

#   if defined (_WholeConv_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef ConvTypes_ConvResults WholeConv_ConvResults;

EXTERN void WholeConv_ScanInt (char inputCh, ConvTypes_ScanClass *chClass, ConvTypes_ScanState *nextState);
EXTERN WholeConv_ConvResults WholeConv_FormatInt (char *str_, unsigned int _str_high);
EXTERN int WholeConv_ValueInt (char *str_, unsigned int _str_high);
EXTERN unsigned int WholeConv_LengthInt (int int_);
EXTERN void WholeConv_ScanCard (char inputCh, ConvTypes_ScanClass *chClass, ConvTypes_ScanState *nextState);
EXTERN WholeConv_ConvResults WholeConv_FormatCard (char *str_, unsigned int _str_high);
EXTERN unsigned int WholeConv_ValueCard (char *str_, unsigned int _str_high);
EXTERN unsigned int WholeConv_LengthCard (unsigned int card);
EXTERN unsigned int WholeConv_IsWholeConvException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
