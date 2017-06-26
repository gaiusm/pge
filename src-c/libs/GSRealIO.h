/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/SRealIO.def.  */


#if !defined (_SRealIO_H)
#   define _SRealIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_SRealIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void SRealIO_ReadReal (double *real);
EXTERN void SRealIO_WriteFloat (double real, unsigned int sigFigs, unsigned int width);
EXTERN void SRealIO_WriteEng (double real, unsigned int sigFigs, unsigned int width);
EXTERN void SRealIO_WriteFixed (double real, int place, unsigned int width);
EXTERN void SRealIO_WriteReal (double real, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
