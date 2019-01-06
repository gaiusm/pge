/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/Strings.def.  */


#if !defined (_Strings_H)
#   define _Strings_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_Strings_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct Strings_String1_a Strings_String1;

typedef enum {Strings_less, Strings_equal, Strings_greater} Strings_CompareResults;

struct Strings_String1_a { char array[0+1]; };
EXTERN unsigned int Strings_Length (char *stringVal_, unsigned int _stringVal_high);
EXTERN void Strings_Assign (char *source_, unsigned int _source_high, char *destination, unsigned int _destination_high);
EXTERN void Strings_Extract (char *source_, unsigned int _source_high, unsigned int startIndex, unsigned int numberToExtract, char *destination, unsigned int _destination_high);
EXTERN void Strings_Delete (char *stringVar, unsigned int _stringVar_high, unsigned int startIndex, unsigned int numberToDelete);
EXTERN void Strings_Insert (char *source_, unsigned int _source_high, unsigned int startIndex, char *destination, unsigned int _destination_high);
EXTERN void Strings_Replace (char *source_, unsigned int _source_high, unsigned int startIndex, char *destination, unsigned int _destination_high);
EXTERN void Strings_Append (char *source_, unsigned int _source_high, char *destination, unsigned int _destination_high);
EXTERN void Strings_Concat (char *source1_, unsigned int _source1_high, char *source2_, unsigned int _source2_high, char *destination, unsigned int _destination_high);
EXTERN unsigned int Strings_CanAssignAll (unsigned int sourceLength, char *destination, unsigned int _destination_high);
EXTERN unsigned int Strings_CanExtractAll (unsigned int sourceLength, unsigned int startIndex, unsigned int numberToExtract, char *destination, unsigned int _destination_high);
EXTERN unsigned int Strings_CanDeleteAll (unsigned int stringLength, unsigned int startIndex, unsigned int numberToDelete);
EXTERN unsigned int Strings_CanInsertAll (unsigned int sourceLength, unsigned int startIndex, char *destination, unsigned int _destination_high);
EXTERN unsigned int Strings_CanReplaceAll (unsigned int sourceLength, unsigned int startIndex, char *destination, unsigned int _destination_high);
EXTERN unsigned int Strings_CanAppendAll (unsigned int sourceLength, char *destination, unsigned int _destination_high);
EXTERN unsigned int Strings_CanConcatAll (unsigned int source1Length, unsigned int source2Length, char *destination, unsigned int _destination_high);
EXTERN Strings_CompareResults Strings_Compare (char *stringVal1_, unsigned int _stringVal1_high, char *stringVal2_, unsigned int _stringVal2_high);
EXTERN unsigned int Strings_Equal (char *stringVal1_, unsigned int _stringVal1_high, char *stringVal2_, unsigned int _stringVal2_high);
EXTERN void Strings_FindNext (char *pattern_, unsigned int _pattern_high, char *stringToSearch_, unsigned int _stringToSearch_high, unsigned int startIndex, unsigned int *patternFound, unsigned int *posOfPattern);
EXTERN void Strings_FindPrev (char *pattern_, unsigned int _pattern_high, char *stringToSearch_, unsigned int _stringToSearch_high, unsigned int startIndex, unsigned int *patternFound, unsigned int *posOfPattern);
EXTERN void Strings_FindDiff (char *stringVal1_, unsigned int _stringVal1_high, char *stringVal2_, unsigned int _stringVal2_high, unsigned int *differenceFound, unsigned int *posOfDifference);
EXTERN void Strings_Capitalize (char *stringVar, unsigned int _stringVar_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
