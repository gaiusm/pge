/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/SLongIO.def.  */


#if !defined (_SLongIO_H)
#   define _SLongIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_SLongIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void SLongIO_ReadReal (long double *real);
EXTERN void SLongIO_WriteFloat (long double real, unsigned int sigFigs, unsigned int width);
EXTERN void SLongIO_WriteEng (long double real, unsigned int sigFigs, unsigned int width);
EXTERN void SLongIO_WriteFixed (long double real, int place, unsigned int width);
EXTERN void SLongIO_WriteReal (long double real, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
