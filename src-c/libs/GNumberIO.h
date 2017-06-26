/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/NumberIO.def.  */


#if !defined (_NumberIO_H)
#   define _NumberIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_NumberIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void NumberIO_ReadCard (unsigned int *x);
EXTERN void NumberIO_WriteCard (unsigned int x, unsigned int n);
EXTERN void NumberIO_ReadHex (unsigned int *x);
EXTERN void NumberIO_WriteHex (unsigned int x, unsigned int n);
EXTERN void NumberIO_ReadInt (int *x);
EXTERN void NumberIO_WriteInt (int x, unsigned int n);
EXTERN void NumberIO_CardToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high);
EXTERN void NumberIO_StrToCard (char *a_, unsigned int _a_high, unsigned int *x);
EXTERN void NumberIO_HexToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high);
EXTERN void NumberIO_StrToHex (char *a_, unsigned int _a_high, unsigned int *x);
EXTERN void NumberIO_IntToStr (int x, unsigned int n, char *a, unsigned int _a_high);
EXTERN void NumberIO_StrToInt (char *a_, unsigned int _a_high, int *x);
EXTERN void NumberIO_ReadOct (unsigned int *x);
EXTERN void NumberIO_WriteOct (unsigned int x, unsigned int n);
EXTERN void NumberIO_OctToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high);
EXTERN void NumberIO_StrToOct (char *a_, unsigned int _a_high, unsigned int *x);
EXTERN void NumberIO_ReadBin (unsigned int *x);
EXTERN void NumberIO_WriteBin (unsigned int x, unsigned int n);
EXTERN void NumberIO_BinToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high);
EXTERN void NumberIO_StrToBin (char *a_, unsigned int _a_high, unsigned int *x);
EXTERN void NumberIO_StrToBinInt (char *a_, unsigned int _a_high, int *x);
EXTERN void NumberIO_StrToHexInt (char *a_, unsigned int _a_high, int *x);
EXTERN void NumberIO_StrToOctInt (char *a_, unsigned int _a_high, int *x);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
