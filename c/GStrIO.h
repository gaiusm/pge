

#if !defined (_StrIO_H)
#   define _StrIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_StrIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   WriteLn - writes a carriage return and a newline
             character.
*/

EXTERN void StrIO_WriteLn (void);

/*
   ReadString - reads a sequence of characters into a string.
                Line editing accepts Del, Ctrl H, Ctrl W and
                Ctrl U.
*/

EXTERN void StrIO_ReadString (char *a, unsigned int _a_high);

/*
   WriteString - writes a string to the default output.
*/

EXTERN void StrIO_WriteString (char *a_, unsigned int _a_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
