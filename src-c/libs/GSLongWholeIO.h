/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/SLongWholeIO.def.  */


#if !defined (_SLongWholeIO_H)
#   define _SLongWholeIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_SLongWholeIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void SLongWholeIO_ReadInt (long int *int_);
EXTERN void SLongWholeIO_WriteInt (long int int_, unsigned int width);
EXTERN void SLongWholeIO_ReadCard (long unsigned int *card);
EXTERN void SLongWholeIO_WriteCard (long unsigned int card, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
