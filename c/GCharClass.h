/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/CharClass.def.  */


#if !defined (_CharClass_H)
#   define _CharClass_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_CharClass_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN unsigned int CharClass_IsNumeric (char ch);
EXTERN unsigned int CharClass_IsLetter (char ch);
EXTERN unsigned int CharClass_IsUpper (char ch);
EXTERN unsigned int CharClass_IsLower (char ch);
EXTERN unsigned int CharClass_IsControl (char ch);
EXTERN unsigned int CharClass_IsWhiteSpace (char ch);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
