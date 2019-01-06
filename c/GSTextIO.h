/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/STextIO.def.  */


#if !defined (_STextIO_H)
#   define _STextIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_STextIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void STextIO_ReadChar (char *ch);
EXTERN void STextIO_ReadRestLine (char *s, unsigned int _s_high);
EXTERN void STextIO_ReadString (char *s, unsigned int _s_high);
EXTERN void STextIO_ReadToken (char *s, unsigned int _s_high);
EXTERN void STextIO_SkipLine (void);
EXTERN void STextIO_WriteChar (char ch);
EXTERN void STextIO_WriteLn (void);
EXTERN void STextIO_WriteString (char *s_, unsigned int _s_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
