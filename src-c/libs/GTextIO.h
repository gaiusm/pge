/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/TextIO.def.  */


#if !defined (_TextIO_H)
#   define _TextIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"

#   if defined (_TextIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void TextIO_ReadChar (IOChan_ChanId cid, char *ch);
EXTERN void TextIO_ReadRestLine (IOChan_ChanId cid, char *s, unsigned int _s_high);
EXTERN void TextIO_ReadString (IOChan_ChanId cid, char *s, unsigned int _s_high);
EXTERN void TextIO_ReadToken (IOChan_ChanId cid, char *s, unsigned int _s_high);
EXTERN void TextIO_SkipLine (IOChan_ChanId cid);
EXTERN void TextIO_WriteChar (IOChan_ChanId cid, char ch);
EXTERN void TextIO_WriteLn (IOChan_ChanId cid);
EXTERN void TextIO_WriteString (IOChan_ChanId cid, char *s_, unsigned int _s_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
