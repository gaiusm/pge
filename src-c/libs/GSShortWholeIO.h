/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/SShortWholeIO.def.  */


#if !defined (_SShortWholeIO_H)
#   define _SShortWholeIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_SShortWholeIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void SShortWholeIO_ReadInt (short int *int_);
EXTERN void SShortWholeIO_WriteInt (short int int_, unsigned int width);
EXTERN void SShortWholeIO_ReadCard (short unsigned int *card);
EXTERN void SShortWholeIO_WriteCard (short unsigned int card, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
