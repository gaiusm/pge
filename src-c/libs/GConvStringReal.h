/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/ConvStringReal.def.  */


#if !defined (_ConvStringReal_H)
#   define _ConvStringReal_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GDynamicStrings.h"

#   if defined (_ConvStringReal_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   RealToFloatString - converts a real with, sigFigs, into a string
                       and returns the result as a string.
*/

EXTERN DynamicStrings_String ConvStringReal_RealToFloatString (double real, unsigned int sigFigs);

/*
   RealToEngString - converts the value of real to floating-point
                     string form, with sigFigs significant figures.
                     The number is scaled with one to three digits
                     in the whole number part and with an exponent
                     that is a multiple of three.
*/

EXTERN DynamicStrings_String ConvStringReal_RealToEngString (double real, unsigned int sigFigs);

/*
   RealToFixedString - returns the number of characters in the fixed-point
                       string representation of real rounded to the given
                       place relative to the decimal point.
*/

EXTERN DynamicStrings_String ConvStringReal_RealToFixedString (double real, int place);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
