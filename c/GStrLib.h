/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/StrLib.def.  */


#if !defined (_StrLib_H)
#   define _StrLib_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_StrLib_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   StrConCat - combines a and b into c.
*/

EXTERN void StrLib_StrConCat (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high, char *c, unsigned int _c_high);

/*
   StrLess - returns TRUE if string, a, alphabetically occurs before
             string, b.
*/

EXTERN unsigned int StrLib_StrLess (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high);

/*
   StrEqual - performs a = b on two strings.
*/

EXTERN unsigned int StrLib_StrEqual (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high);

/*
   StrLen - returns the length of string, a.
*/

EXTERN unsigned int StrLib_StrLen (char *a_, unsigned int _a_high);

/*
   StrCopy - effectively performs b := a with two strings.
*/

EXTERN void StrLib_StrCopy (char *a_, unsigned int _a_high, char *b, unsigned int _b_high);

/*
   IsSubString - returns true if b is a subcomponent of a.
*/

EXTERN unsigned int StrLib_IsSubString (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high);

/*
   StrRemoveWhitePrefix - copies string, into string, b, excluding any white
                          space infront of a.
*/

EXTERN void StrLib_StrRemoveWhitePrefix (char *a_, unsigned int _a_high, char *b, unsigned int _b_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
