/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/dtoa.def.  */


#if !defined (_dtoa_H)
#   define _dtoa_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_dtoa_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef enum {dtoa_maxsignificant, dtoa_decimaldigits} dtoa_Mode;


/*
   strtod - returns a REAL given a string, s.  It will set
            error to TRUE if the number is too large.
*/

EXTERN double dtoa_strtod (void * s, unsigned int *error);

/*
   dtoa - converts a REAL, d, into a string.  The address of the
          string is returned.
          mode       indicates the type of conversion required.
          ndigits    determines the number of digits according to mode.
          decpt      the position of the decimal point.
          sign       does the string have a sign?
*/

EXTERN void * dtoa_dtoa (double d, dtoa_Mode mode, int ndigits, int *decpt, unsigned int *sign);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
