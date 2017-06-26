/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/SimpleCipher.def.  */


#if !defined (_SimpleCipher_H)
#   define _SimpleCipher_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_SimpleCipher_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   InsertCipherLayer - inserts a caesar cipher below channel, cid.
                       The encryption, key, is specified.
*/

EXTERN void SimpleCipher_InsertCipherLayer (IOChan_ChanId cid, int key);

/*
   RemoveCipherLayer - removes a Caesar cipher below channel, cid.
*/

EXTERN void SimpleCipher_RemoveCipherLayer (IOChan_ChanId cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
