/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/StrCase.def.  */


#if !defined (_StrCase_H)
#   define _StrCase_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_StrCase_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   StrToUpperCase - converts string, a, to uppercase returning the
                    result in, b.
*/

EXTERN void StrCase_StrToUpperCase (char *a_, unsigned int _a_high, char *b, unsigned int _b_high);

/*
   StrToLowerCase - converts string, a, to lowercase returning the
                    result in, b.
*/

EXTERN void StrCase_StrToLowerCase (char *a_, unsigned int _a_high, char *b, unsigned int _b_high);

/*
   Cap - converts a lower case character into a capital character.
         If the character is not a lower case character 'a'..'z'
         then the character is simply returned unaltered.
*/

EXTERN char StrCase_Cap (char ch);

/*
   Lower - converts an upper case character into a lower case character.
           If the character is not an upper case character 'A'..'Z'
           then the character is simply returned unaltered.
*/

EXTERN char StrCase_Lower (char ch);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
