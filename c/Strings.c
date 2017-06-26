/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/Strings.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#include <string.h>
#include <limits.h>
#include <ctype.h>
#   include "GM2RTS.h"
#define _Strings_H
#define _Strings_C

#   include "GASCII.h"
#   include "Glibc.h"

typedef struct Strings_String1_a Strings_String1;

#   define Debugging FALSE
typedef enum {Strings_less, Strings_equal, Strings_greater} Strings_CompareResults;

struct Strings_String1_a { char array[0+1]; };

/*
   Length - Returns the length of stringVal (the same value as would be returned by the
            pervasive function LENGTH).
*/

unsigned int Strings_Length (char *stringVal_, unsigned int _stringVal_high);

/*
   Assign - Copies source to destination.
*/

void Strings_Assign (char *source_, unsigned int _source_high, char *destination, unsigned int _destination_high);
void Strings_Extract (char *source_, unsigned int _source_high, unsigned int startIndex, unsigned int numberToExtract, char *destination, unsigned int _destination_high);

/*
 Deletes at most numberToDelete characters from stringVar, starting at position
   startIndex.
*/

void Strings_Delete (char *stringVar, unsigned int _stringVar_high, unsigned int startIndex, unsigned int numberToDelete);

/*
 Inserts source into destination at position startIndex */

void Strings_Insert (char *source_, unsigned int _source_high, unsigned int startIndex, char *destination, unsigned int _destination_high);
void Strings_Replace (char *source_, unsigned int _source_high, unsigned int startIndex, char *destination, unsigned int _destination_high);
void Strings_Append (char *source_, unsigned int _source_high, char *destination, unsigned int _destination_high);
void Strings_Concat (char *source1_, unsigned int _source1_high, char *source2_, unsigned int _source2_high, char *destination, unsigned int _destination_high);
unsigned int Strings_CanAssignAll (unsigned int sourceLength, char *destination, unsigned int _destination_high);
unsigned int Strings_CanExtractAll (unsigned int sourceLength, unsigned int startIndex, unsigned int numberToExtract, char *destination, unsigned int _destination_high);
unsigned int Strings_CanDeleteAll (unsigned int stringLength, unsigned int startIndex, unsigned int numberToDelete);
unsigned int Strings_CanInsertAll (unsigned int sourceLength, unsigned int startIndex, char *destination, unsigned int _destination_high);
unsigned int Strings_CanReplaceAll (unsigned int sourceLength, unsigned int startIndex, char *destination, unsigned int _destination_high);
unsigned int Strings_CanAppendAll (unsigned int sourceLength, char *destination, unsigned int _destination_high);
unsigned int Strings_CanConcatAll (unsigned int source1Length, unsigned int source2Length, char *destination, unsigned int _destination_high);
Strings_CompareResults Strings_Compare (char *stringVal1_, unsigned int _stringVal1_high, char *stringVal2_, unsigned int _stringVal2_high);
unsigned int Strings_Equal (char *stringVal1_, unsigned int _stringVal1_high, char *stringVal2_, unsigned int _stringVal2_high);
void Strings_FindNext (char *pattern_, unsigned int _pattern_high, char *stringToSearch_, unsigned int _stringToSearch_high, unsigned int startIndex, unsigned int *patternFound, unsigned int *posOfPattern);
void Strings_FindPrev (char *pattern_, unsigned int _pattern_high, char *stringToSearch_, unsigned int _stringToSearch_high, unsigned int startIndex, unsigned int *patternFound, unsigned int *posOfPattern);
void Strings_FindDiff (char *stringVal1_, unsigned int _stringVal1_high, char *stringVal2_, unsigned int _stringVal2_high, unsigned int *differenceFound, unsigned int *posOfDifference);
void Strings_Capitalize (char *stringVar, unsigned int _stringVar_high);


/*
   Length - Returns the length of stringVal (the same value as would be returned by the
            pervasive function LENGTH).
*/

unsigned int Strings_Length (char *stringVal_, unsigned int _stringVal_high)
{
  char stringVal[_stringVal_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (stringVal, stringVal_, _stringVal_high+1);

  return M2RTS_Length (stringVal, _stringVal_high);
}


/*
   Assign - Copies source to destination.
*/

void Strings_Assign (char *source_, unsigned int _source_high, char *destination, unsigned int _destination_high)
{
  unsigned int i;
  unsigned int sh;
  unsigned int dh;
  char source[_source_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (source, source_, _source_high+1);

  sh = Strings_Length ((char *) source, _source_high);
  dh = _destination_high;
  i = 0;
  while ((i < sh) && (i <= dh))
    {
      destination[i] = source[i];
      i += 1;
    }
  if (i <= dh)
    destination[i] = ASCII_nul;
}

void Strings_Extract (char *source_, unsigned int _source_high, unsigned int startIndex, unsigned int numberToExtract, char *destination, unsigned int _destination_high)
{
  unsigned int sh;
  unsigned int dh;
  unsigned int i;
  char source[_source_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (source, source_, _source_high+1);

  sh = Strings_Length ((char *) source, _source_high);
  dh = _destination_high;
  i = 0;
  while (((i < numberToExtract) && (startIndex < sh)) && (i <= dh))
    {
      destination[i] = source[startIndex];
      i += 1;
      startIndex += 1;
    }
  if (i <= dh)
    destination[i] = ASCII_nul;
}


/*
 Deletes at most numberToDelete characters from stringVar, starting at position
   startIndex.
*/

void Strings_Delete (char *stringVar, unsigned int _stringVar_high, unsigned int startIndex, unsigned int numberToDelete)
{
  unsigned int h;

  if (numberToDelete > 0)
    {
      h = Strings_Length ((char *) stringVar, _stringVar_high);
      while ((startIndex+numberToDelete) < h)
        {
          stringVar[startIndex] = stringVar[startIndex+numberToDelete];
          startIndex += 1;
        }
      if (startIndex < (_stringVar_high))
        stringVar[startIndex] = ASCII_nul;
    }
}


/*
 Inserts source into destination at position startIndex */

void Strings_Insert (char *source_, unsigned int _source_high, unsigned int startIndex, char *destination, unsigned int _destination_high)
{
  unsigned int newEnd;
  unsigned int endCopy;
  unsigned int i;
  unsigned int j;
  unsigned int sh;
  unsigned int dh;
  unsigned int dl;
  char source[_source_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (source, source_, _source_high+1);

  sh = Strings_Length ((char *) source, _source_high);
  dh = _destination_high;
  dl = Strings_Length ((char *) destination, _destination_high);
  if (Debugging)
    libc_printf ((char *) "sh = %d   dh = %d   dl = %d\\n", 29, sh, dh, dl);
  newEnd = dl+sh;
  if (newEnd > dh)
    newEnd = dh;
  if (newEnd > sh)
    endCopy = newEnd-sh;
  else
    endCopy = 0;
  if (Debugging)
    {
      libc_printf ((char *) "\\ndestination contains\\n%s\\nnewEnd = %d   endCopy = %d\\n", 56, (*destination), newEnd, endCopy);
      libc_printf ((char *) "newEnd = %d\\n", 13, newEnd);
      libc_printf ((char *) "endCopy = %d\\n", 14, endCopy);
    }
  newEnd += 1;
  endCopy += 1;
  while (endCopy > startIndex)
    {
      newEnd -= 1;
      endCopy -= 1;
      if (Debugging)
        libc_printf ((char *) "copying dest %d to %d (%c) (startIndex=%d)\\n", 44, endCopy, newEnd, destination[newEnd], startIndex);
      destination[newEnd] = destination[endCopy];
    }
  if (Debugging)
    libc_printf ((char *) "destination now contains %s\\n", 29, (*destination));
  j = startIndex;
  i = 0;
  while ((i < sh) && (j <= dh))
    {
      destination[j] = source[i];
      i += 1;
      j += 1;
    }
}

void Strings_Replace (char *source_, unsigned int _source_high, unsigned int startIndex, char *destination, unsigned int _destination_high)
{
  unsigned int i;
  unsigned int sh;
  unsigned int dh;
  char source[_source_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (source, source_, _source_high+1);

  i = 0;
  sh = Strings_Length ((char *) source, _source_high);
  dh = Strings_Length ((char *) destination, _destination_high);
  while ((i < sh) && (startIndex < dh))
    {
      destination[startIndex] = source[i];
      i += 1;
      startIndex += 1;
    }
  if (startIndex < (_destination_high))
    destination[startIndex] = ASCII_nul;
}

void Strings_Append (char *source_, unsigned int _source_high, char *destination, unsigned int _destination_high)
{
  unsigned int i;
  unsigned int j;
  unsigned int sh;
  unsigned int dh;
  char source[_source_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (source, source_, _source_high+1);

  j = Strings_Length ((char *) destination, _destination_high);
  dh = _destination_high;
  sh = Strings_Length ((char *) source, _source_high);
  i = 0;
  while ((i < sh) && (j <= dh))
    {
      destination[j] = source[i];
      i += 1;
      j += 1;
    }
  if (j <= dh)
    destination[j] = ASCII_nul;
}

void Strings_Concat (char *source1_, unsigned int _source1_high, char *source2_, unsigned int _source2_high, char *destination, unsigned int _destination_high)
{
  char source1[_source1_high+1];
  char source2[_source2_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (source1, source1_, _source1_high+1);
  memcpy (source2, source2_, _source2_high+1);

  Strings_Assign ((char *) source1, _source1_high, (char *) destination, _destination_high);
  Strings_Append ((char *) source2, _source2_high, (char *) destination, _destination_high);
}

unsigned int Strings_CanAssignAll (unsigned int sourceLength, char *destination, unsigned int _destination_high)
{
  return sourceLength <= (_destination_high);
}

unsigned int Strings_CanExtractAll (unsigned int sourceLength, unsigned int startIndex, unsigned int numberToExtract, char *destination, unsigned int _destination_high)
{
  return ((numberToExtract+startIndex) <= sourceLength) && ((_destination_high) >= numberToExtract);
}

unsigned int Strings_CanDeleteAll (unsigned int stringLength, unsigned int startIndex, unsigned int numberToDelete)
{
  return (startIndex+numberToDelete) <= stringLength;
}

unsigned int Strings_CanInsertAll (unsigned int sourceLength, unsigned int startIndex, char *destination, unsigned int _destination_high)
{
  return (((_destination_high)-(Strings_Length ((char *) destination, _destination_high))) < sourceLength) && (((_destination_high)-startIndex) < sourceLength);
}

unsigned int Strings_CanReplaceAll (unsigned int sourceLength, unsigned int startIndex, char *destination, unsigned int _destination_high)
{
  return sourceLength <= ((Strings_Length ((char *) destination, _destination_high))-startIndex);
}

unsigned int Strings_CanAppendAll (unsigned int sourceLength, char *destination, unsigned int _destination_high)
{
  return ((_destination_high)-(Strings_Length ((char *) destination, _destination_high))) >= sourceLength;
}

unsigned int Strings_CanConcatAll (unsigned int source1Length, unsigned int source2Length, char *destination, unsigned int _destination_high)
{
  return ((_destination_high)-(Strings_Length ((char *) destination, _destination_high))) >= (source1Length+source2Length);
}

Strings_CompareResults Strings_Compare (char *stringVal1_, unsigned int _stringVal1_high, char *stringVal2_, unsigned int _stringVal2_high)
{
  unsigned int i;
  unsigned int l1;
  unsigned int l2;
  char stringVal1[_stringVal1_high+1];
  char stringVal2[_stringVal2_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (stringVal1, stringVal1_, _stringVal1_high+1);
  memcpy (stringVal2, stringVal2_, _stringVal2_high+1);

  l1 = Strings_Length ((char *) stringVal1, _stringVal1_high);
  l2 = Strings_Length ((char *) stringVal2, _stringVal2_high);
  i = 0;
  while ((i < l1) && (i < l2))
    if (stringVal1[i] < stringVal2[i])
      return Strings_less;
    else if (stringVal1[i] > stringVal2[i])
      return Strings_greater;
    else
      i += 1;
  if (l1 < l2)
    return Strings_less;
  else if (l1 > l2)
    return Strings_greater;
  else
    return Strings_equal;
}

unsigned int Strings_Equal (char *stringVal1_, unsigned int _stringVal1_high, char *stringVal2_, unsigned int _stringVal2_high)
{
  unsigned int h1;
  unsigned int h2;
  unsigned int i;
  char c1;
  char c2;
  char stringVal1[_stringVal1_high+1];
  char stringVal2[_stringVal2_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (stringVal1, stringVal1_, _stringVal1_high+1);
  memcpy (stringVal2, stringVal2_, _stringVal2_high+1);

  i = 0;
  h1 = _stringVal1_high;
  h2 = _stringVal2_high;
  if (h1 == h2)
    {
      do {
        c1 = stringVal1[i];
        c2 = stringVal2[i];
        if (c1 != c2)
          return FALSE;
        if (c1 == ASCII_nul)
          return TRUE;
        i += 1;
      } while (! (i > h1));
      return TRUE;
    }
  else
    {
      c1 = stringVal1[0];
      c2 = stringVal2[0];
      while (c1 == c2)
        {
          if (c1 == ASCII_nul)
            return TRUE;
          i += 1;
          if (i <= h1)
            {
              c1 = stringVal1[i];
              if (i <= h2)
                c2 = stringVal2[i];
              else
                return c1 == ASCII_nul;
            }
          else if (i <= h2)
            {
              c2 = stringVal2[i];
              return c2 == ASCII_nul;
            }
        }
      return FALSE;
    }
}

void Strings_FindNext (char *pattern_, unsigned int _pattern_high, char *stringToSearch_, unsigned int _stringToSearch_high, unsigned int startIndex, unsigned int *patternFound, unsigned int *posOfPattern)
{
  unsigned int i;
  unsigned int j;
  unsigned int hp;
  unsigned int hs;
  char pattern[_pattern_high+1];
  char stringToSearch[_stringToSearch_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (pattern, pattern_, _pattern_high+1);
  memcpy (stringToSearch, stringToSearch_, _stringToSearch_high+1);

  i = startIndex;
  hp = Strings_Length ((char *) pattern, _pattern_high);
  hs = Strings_Length ((char *) stringToSearch, _stringToSearch_high);
  if (hp <= hs)
    while (i <= (hs-hp))
      {
        j = 0;
        while ((j < hp) && (pattern[j] == stringToSearch[i+j]))
          {
            j += 1;
            if (j == hp)
              {
                (*posOfPattern) = i;
                (*patternFound) = TRUE;
                return;
              }
          }
        i += 1;
      }
  (*patternFound) = FALSE;
}

void Strings_FindPrev (char *pattern_, unsigned int _pattern_high, char *stringToSearch_, unsigned int _stringToSearch_high, unsigned int startIndex, unsigned int *patternFound, unsigned int *posOfPattern)
{
  unsigned int i;
  unsigned int j;
  unsigned int hp;
  unsigned int hs;
  char pattern[_pattern_high+1];
  char stringToSearch[_stringToSearch_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (pattern, pattern_, _pattern_high+1);
  memcpy (stringToSearch, stringToSearch_, _stringToSearch_high+1);

  hp = Strings_Length ((char *) pattern, _pattern_high);
  hs = Strings_Length ((char *) stringToSearch, _stringToSearch_high);
  if (hp <= hs)
    {
      i = (hs-hp)+1;
      while (i > 0)
        {
          i -= 1;
          j = 0;
          while ((j < hp) && (pattern[j] == stringToSearch[i+j]))
            {
              j += 1;
              if (j == hp)
                {
                  (*posOfPattern) = i;
                  (*patternFound) = TRUE;
                  return;
                }
            }
        }
    }
  (*patternFound) = FALSE;
}

void Strings_FindDiff (char *stringVal1_, unsigned int _stringVal1_high, char *stringVal2_, unsigned int _stringVal2_high, unsigned int *differenceFound, unsigned int *posOfDifference)
{
  unsigned int i;
  unsigned int s1h;
  unsigned int s2h;
  char stringVal1[_stringVal1_high+1];
  char stringVal2[_stringVal2_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (stringVal1, stringVal1_, _stringVal1_high+1);
  memcpy (stringVal2, stringVal2_, _stringVal2_high+1);

  s1h = Strings_Length ((char *) stringVal1, _stringVal1_high);
  s2h = Strings_Length ((char *) stringVal2, _stringVal2_high);
  i = 0;
  while ((i < s1h) && (i < s2h))
    if (stringVal1[i] == stringVal2[i])
      i += 1;
    else
      {
        (*differenceFound) = TRUE;
        (*posOfDifference) = i;
        return;
      }
  if (s1h == s2h)
    (*differenceFound) = FALSE;
  else
    {
      (*differenceFound) = TRUE;
      (*posOfDifference) = i;
    }
}

void Strings_Capitalize (char *stringVar, unsigned int _stringVar_high)
{
  unsigned int i;
  unsigned int h;

  i = 0;
  h = Strings_Length ((char *) stringVar, _stringVar_high);
  while (i < h)
    {
      stringVar[i] = toupper (stringVar[i]);
      i += 1;
    }
}

void _M2_Strings_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_Strings_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
