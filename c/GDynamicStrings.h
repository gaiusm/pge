/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/DynamicStrings.def.  */


#if !defined (_DynamicStrings_H)
#   define _DynamicStrings_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_DynamicStrings_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (DynamicStrings_String_D)
#  define DynamicStrings_String_D
   typedef void *DynamicStrings_String;
#endif


/*
   InitString - creates and returns a String type object.
                Initial contents are, a.
*/

EXTERN DynamicStrings_String DynamicStrings_InitString (char *a_, unsigned int _a_high);

/*
   KillString - frees String, s, and its contents.
                NIL is returned.
*/

EXTERN DynamicStrings_String DynamicStrings_KillString (DynamicStrings_String s);

/*
   Fin - finishes with a string, it calls KillString with, s.
         The purpose of the procedure is to provide a short cut
         to calling KillString and then testing the return result.
*/

EXTERN void DynamicStrings_Fin (DynamicStrings_String s);

/*
   InitStringCharStar - initializes and returns a String to contain the C string.
*/

EXTERN DynamicStrings_String DynamicStrings_InitStringCharStar (void * a);

/*
   InitStringChar - initializes and returns a String to contain the single character, ch.
*/

EXTERN DynamicStrings_String DynamicStrings_InitStringChar (char ch);

/*
   Mark - marks String, s, ready for garbage collection.
*/

EXTERN DynamicStrings_String DynamicStrings_Mark (DynamicStrings_String s);

/*
   Length - returns the length of the String, s.
*/

EXTERN unsigned int DynamicStrings_Length (DynamicStrings_String s);

/*
   ConCat - returns String, a, after the contents of, b, have been appended.
*/

EXTERN DynamicStrings_String DynamicStrings_ConCat (DynamicStrings_String a, DynamicStrings_String b);

/*
   ConCatChar - returns String, a, after character, ch, has been appended.
*/

EXTERN DynamicStrings_String DynamicStrings_ConCatChar (DynamicStrings_String a, char ch);

/*
   Assign - assigns the contents of, b, into, a.
            String, a, is returned.
*/

EXTERN DynamicStrings_String DynamicStrings_Assign (DynamicStrings_String a, DynamicStrings_String b);

/*
   Dup - duplicate a String, s, returning the copy of s.
*/

EXTERN DynamicStrings_String DynamicStrings_Dup (DynamicStrings_String s);

/*
   Add - returns a new String which contains the contents of a and b.
*/

EXTERN DynamicStrings_String DynamicStrings_Add (DynamicStrings_String a, DynamicStrings_String b);

/*
   Equal - returns TRUE if String, a, and, b, are equal.
*/

EXTERN unsigned int DynamicStrings_Equal (DynamicStrings_String a, DynamicStrings_String b);

/*
   EqualCharStar - returns TRUE if contents of String, s, is the same as the
                   string, a.
*/

EXTERN unsigned int DynamicStrings_EqualCharStar (DynamicStrings_String s, void * a);

/*
   EqualArray - returns TRUE if contents of String, s, is the same as the
                string, a.
*/

EXTERN unsigned int DynamicStrings_EqualArray (DynamicStrings_String s, char *a_, unsigned int _a_high);

/*
   Mult - returns a new string which is n concatenations of String, s.
          If n<=0 then an empty string is returned.
*/

EXTERN DynamicStrings_String DynamicStrings_Mult (DynamicStrings_String s, unsigned int n);

/*
   Slice - returns a new string which contains the elements
           low..high-1

           strings start at element 0
           Slice(s, 0, 2)  will return elements 0, 1 but not 2
           Slice(s, 1, 3)  will return elements 1, 2 but not 3
           Slice(s, 2, 0)  will return elements 2..max
           Slice(s, 3, -1) will return elements 3..max-1
           Slice(s, 4, -2) will return elements 4..max-2
*/

EXTERN DynamicStrings_String DynamicStrings_Slice (DynamicStrings_String s, int low, int high);

/*
   Index - returns the indice of the first occurance of, ch, in
           String, s. -1 is returned if, ch, does not exist.
           The search starts at position, o.
*/

EXTERN int DynamicStrings_Index (DynamicStrings_String s, char ch, unsigned int o);

/*
   RIndex - returns the indice of the last occurance of, ch,
            in String, s. The search starts at position, o.
            -1 is returned if, ch, is not found.
*/

EXTERN int DynamicStrings_RIndex (DynamicStrings_String s, char ch, unsigned int o);

/*
   RemoveComment - assuming that, comment, is a comment delimiter
                   which indicates anything to its right is a comment
                   then strip off the comment and also any white space
                   on the remaining right hand side.
                   It leaves any white space on the left hand side alone.
*/

EXTERN DynamicStrings_String DynamicStrings_RemoveComment (DynamicStrings_String s, char comment);

/*
   RemoveWhitePrefix - removes any leading white space from String, s.
                       A new string is returned.
*/

EXTERN DynamicStrings_String DynamicStrings_RemoveWhitePrefix (DynamicStrings_String s);

/*
   RemoveWhitePostfix - removes any leading white space from String, s.
                        A new string is returned.
*/

EXTERN DynamicStrings_String DynamicStrings_RemoveWhitePostfix (DynamicStrings_String s);

/*
   ToUpper - returns string, s, after it has had its lower case characters
             replaced by upper case characters.
             The string, s, is not duplicated.
*/

EXTERN DynamicStrings_String DynamicStrings_ToUpper (DynamicStrings_String s);

/*
   ToLower - returns string, s, after it has had its upper case characters
             replaced by lower case characters.
             The string, s, is not duplicated.
*/

EXTERN DynamicStrings_String DynamicStrings_ToLower (DynamicStrings_String s);

/*
   CopyOut - copies string, s, to a.
*/

EXTERN void DynamicStrings_CopyOut (char *a, unsigned int _a_high, DynamicStrings_String s);

/*
   char - returns the character, ch, at position, i, in String, s.
          As Slice the index can be negative so:

          char(s, 0) will return the first character
          char(s, 1) will return the second character
          char(s, -1) will return the last character
          char(s, -2) will return the penultimate character

          a nul character is returned if the index is out of range.
*/

EXTERN char DynamicStrings_char (DynamicStrings_String s, int i);

/*
   string - returns the C style char * of String, s.
*/

EXTERN void * DynamicStrings_string (DynamicStrings_String s);

/*
   InitStringDB - the debug version of InitString.
*/

EXTERN DynamicStrings_String DynamicStrings_InitStringDB (char *a_, unsigned int _a_high, char *file_, unsigned int _file_high, unsigned int line);

/*
   InitStringCharStarDB - the debug version of InitStringCharStar.
*/

EXTERN DynamicStrings_String DynamicStrings_InitStringCharStarDB (void * a, char *file_, unsigned int _file_high, unsigned int line);

/*
   InitStringCharDB - the debug version of InitStringChar.
*/

EXTERN DynamicStrings_String DynamicStrings_InitStringCharDB (char ch, char *file_, unsigned int _file_high, unsigned int line);

/*
   MultDB - the debug version of MultDB.
*/

EXTERN DynamicStrings_String DynamicStrings_MultDB (DynamicStrings_String s, unsigned int n, char *file_, unsigned int _file_high, unsigned int line);

/*
   DupDB - the debug version of Dup.
*/

EXTERN DynamicStrings_String DynamicStrings_DupDB (DynamicStrings_String s, char *file_, unsigned int _file_high, unsigned int line);

/*
   SliceDB - debug version of Slice.
*/

EXTERN DynamicStrings_String DynamicStrings_SliceDB (DynamicStrings_String s, int low, int high, char *file_, unsigned int _file_high, unsigned int line);

/*
   PushAllocation - pushes the current allocation/deallocation lists.
*/

EXTERN void DynamicStrings_PushAllocation (void);

/*
   PopAllocation - test to see that all strings are deallocated since
                   the last push.  Then it pops to the previous
                   allocation/deallocation lists.

                   If halt is true then the application terminates
                   with an exit code of 1.
*/

EXTERN void DynamicStrings_PopAllocation (unsigned int halt);

/*
   PopAllocationExemption - test to see that all strings are deallocated, except
                            string, e, since the last push.
                            Then it pops to the previous allocation/deallocation
                            lists.

                            If halt is true then the application terminates
                            with an exit code of 1.

                            The string, e, is returned unmodified,
*/

EXTERN DynamicStrings_String DynamicStrings_PopAllocationExemption (unsigned int halt, DynamicStrings_String e);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
