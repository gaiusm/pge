/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/SShortIO.def.  */


#if !defined (_SShortIO_H)
#   define _SShortIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_SShortIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void SShortIO_ReadReal (float *real);
EXTERN void SShortIO_WriteFloat (float real, unsigned int sigFigs, unsigned int width);
EXTERN void SShortIO_WriteEng (float real, unsigned int sigFigs, unsigned int width);
EXTERN void SShortIO_WriteFixed (float real, int place, unsigned int width);
EXTERN void SShortIO_WriteReal (float real, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
