/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/StringChan.def.  */


#if !defined (_StringChan_H)
#   define _StringChan_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GDynamicStrings.h"
#   include "GIOChan.h"

#   if defined (_StringChan_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   writeString - writes a string, s, to ChanId, cid.
                 The string, s, is not destroyed.
*/

EXTERN void StringChan_writeString (IOChan_ChanId cid, DynamicStrings_String s);

/*
   writeFieldWidth - writes a string, s, to ChanId, cid.
                     The string, s, is not destroyed and it
                     is prefixed by spaces so that at least,
                     width, characters are written.  If the
                     string, s, is longer than width then
                     no spaces are prefixed to the output
                     and the entire string is written.
*/

EXTERN void StringChan_writeFieldWidth (IOChan_ChanId cid, DynamicStrings_String s, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
