/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/ldtoa.def.  */


#if !defined (_ldtoa_H)
#   define _ldtoa_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_ldtoa_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef enum {ldtoa_maxsignificant, ldtoa_decimaldigits} ldtoa_Mode;


/*
   strtold - returns a LONGREAL given a C string, s.  It will set
             error to TRUE if the number is too large or badly formed.
*/

EXTERN long double ldtoa_strtold (void * s, unsigned int *error);

/*
   ldtoa - converts a LONGREAL, d, into a string.  The address of the
           string is returned.
           mode       indicates the type of conversion required.
           ndigits    determines the number of digits according to mode.
           decpt      the position of the decimal point.
           sign       does the string have a sign?
*/

EXTERN void * ldtoa_ldtoa (long double d, ldtoa_Mode mode, int ndigits, int *decpt, unsigned int *sign);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
