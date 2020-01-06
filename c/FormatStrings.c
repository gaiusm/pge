/* This file is part of GNU Modula-2.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA  */

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

#include <stddef.h>
#include <string.h>
#include <limits.h>
#define _FormatStrings_H
#define _FormatStrings_C

#   include "GDynamicStrings.h"
#   include "GStringConvert.h"
#   include "GASCII.h"
#   include "GSYSTEM.h"
#   include "GM2RTS.h"


/*
   Sprintf0 - returns a String containing, s, after it has had its
              escape sequences translated.
*/

DynamicStrings_String FormatStrings_Sprintf0 (DynamicStrings_String fmt);

/*
   Sprintf1 - returns a String containing, s, together with encapsulated
              entity, w. It only formats the first %s or %d with n.
*/

DynamicStrings_String FormatStrings_Sprintf1 (DynamicStrings_String fmt, unsigned char *w_, unsigned int _w_high);

/*
   Sprintf2 - returns a string, s, which has been formatted.
*/

DynamicStrings_String FormatStrings_Sprintf2 (DynamicStrings_String fmt, unsigned char *w1_, unsigned int _w1_high, unsigned char *w2_, unsigned int _w2_high);

/*
   Sprintf3 - returns a string, s, which has been formatted.
*/

DynamicStrings_String FormatStrings_Sprintf3 (DynamicStrings_String fmt, unsigned char *w1_, unsigned int _w1_high, unsigned char *w2_, unsigned int _w2_high, unsigned char *w3_, unsigned int _w3_high);

/*
   Sprintf4 - returns a string, s, which has been formatted.
*/

DynamicStrings_String FormatStrings_Sprintf4 (DynamicStrings_String fmt, unsigned char *w1_, unsigned int _w1_high, unsigned char *w2_, unsigned int _w2_high, unsigned char *w3_, unsigned int _w3_high, unsigned char *w4_, unsigned int _w4_high);

/*
   doDSdbEnter -
*/

static void doDSdbEnter (void);

/*
   doDSdbExit -
*/

static void doDSdbExit (DynamicStrings_String s);

/*
   DSdbEnter -
*/

static void DSdbEnter (void);

/*
   DSdbExit -
*/

static void DSdbExit (DynamicStrings_String s);

/*
   IsDigit - returns TRUE if ch lies in the range: 0..9
*/

static unsigned int IsDigit (char ch);

/*
   Cast - casts a := b
*/

static void Cast (unsigned char *a, unsigned int _a_high, unsigned char *b_, unsigned int _b_high);

/*
   HandleEscape - translates 
 and \t into their respective ascii codes.
*/

static DynamicStrings_String HandleEscape (DynamicStrings_String s);

/*
   FormatString - returns a String containing, s, together with encapsulated
                  entity, w. It only formats the first %s or %d or %u with n.
                  A new string is returned.
*/

static DynamicStrings_String FormatString (DynamicStrings_String fmt, int *startpos, DynamicStrings_String in, unsigned char *w_, unsigned int _w_high);

/*
   FormatString - returns a String containing, s, together with encapsulated
                  entity, w. It only formats the first %s or %d or %u with n.
                  A new string is returned.
*/

static DynamicStrings_String PerformFormatString (DynamicStrings_String fmt, int *startpos, DynamicStrings_String in, unsigned char *w_, unsigned int _w_high);

/*
   Copy - copies, fmt[start:end] -> in and returns in.  Providing that start >= 0.
*/

static DynamicStrings_String Copy (DynamicStrings_String fmt, DynamicStrings_String in, int start, int end);

/*
   HandlePercent - pre-condition:  s, is a string.
                   Post-condition:  a new string is returned which is a copy of,
                   s, except %% is transformed into %.
*/

static DynamicStrings_String HandlePercent (DynamicStrings_String fmt, DynamicStrings_String s, int startpos);


/*
   doDSdbEnter -
*/

static void doDSdbEnter (void)
{
  DynamicStrings_PushAllocation ();
}


/*
   doDSdbExit -
*/

static void doDSdbExit (DynamicStrings_String s)
{
  s = DynamicStrings_PopAllocationExemption (TRUE, s);
}


/*
   DSdbEnter -
*/

static void DSdbEnter (void)
{
}


/*
   DSdbExit -
*/

static void DSdbExit (DynamicStrings_String s)
{
}


/*
   IsDigit - returns TRUE if ch lies in the range: 0..9
*/

static unsigned int IsDigit (char ch)
{
  return (ch >= '0') && (ch <= '9');
}


/*
   Cast - casts a := b
*/

static void Cast (unsigned char *a, unsigned int _a_high, unsigned char *b_, unsigned int _b_high)
{
  unsigned int i;
  unsigned char b[_b_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (b, b_, _b_high+1);

  if ((_a_high) == (_b_high))
    for (i=0; i<=_a_high; i++)
      a[i] = b[i];
  else
    M2RTS_HALT (-1);
}


/*
   HandleEscape - translates 
 and \t into their respective ascii codes.
*/

static DynamicStrings_String HandleEscape (DynamicStrings_String s)
{
  DynamicStrings_String d;
  int i;
  int j;
  char ch;

  DSdbEnter ();
  d = DynamicStrings_InitString ((char *) "", 0);
  i = DynamicStrings_Index (s, '\\', 0);
  j = 0;
  while (i >= 0)
    {
      if (i > 0)
        /* initially i might be zero which means the end of the string, which is not what we want  */
        d = DynamicStrings_ConCat (d, DynamicStrings_Slice (s, j, i));
      ch = DynamicStrings_char (s, i+1);
      if (ch == 'n')
        /* requires a newline  */
        d = DynamicStrings_ConCat (d, DynamicStrings_Mark (DynamicStrings_InitStringChar (ASCII_nl)));
      else if (ch == 't')
        /* requires a tab (yuck)  */
        d = DynamicStrings_ConCat (d, DynamicStrings_Mark (DynamicStrings_InitStringChar (ASCII_tab)));
      else
        /* copy escaped character  */
        d = DynamicStrings_ConCat (d, DynamicStrings_Mark (DynamicStrings_InitStringChar (ch)));
      i += 2;
      j = i;
      i = DynamicStrings_Index (s, '\\', (unsigned int ) (i));
    }
  /* s := Assign(s, Mark(ConCat(d, Mark(Slice(s, j, 0))))) ;    dont Mark(s) in the Slice as we Assign contents  */
  s = DynamicStrings_ConCat (d, DynamicStrings_Mark (DynamicStrings_Slice (DynamicStrings_Mark (s), j, 0)));
  DSdbExit (s);
  return s;
}


/*
   FormatString - returns a String containing, s, together with encapsulated
                  entity, w. It only formats the first %s or %d or %u with n.
                  A new string is returned.
*/

static DynamicStrings_String FormatString (DynamicStrings_String fmt, int *startpos, DynamicStrings_String in, unsigned char *w_, unsigned int _w_high)
{
  DynamicStrings_String s;
  unsigned char w[_w_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (w, w_, _w_high+1);

  DSdbEnter ();
  if ((*startpos) >= 0)
    s = PerformFormatString (fmt, startpos, in, (unsigned char *) w, _w_high);
  else
    s = DynamicStrings_Dup (in);
  DSdbExit (s);
  return s;
}


/*
   FormatString - returns a String containing, s, together with encapsulated
                  entity, w. It only formats the first %s or %d or %u with n.
                  A new string is returned.
*/

static DynamicStrings_String PerformFormatString (DynamicStrings_String fmt, int *startpos, DynamicStrings_String in, unsigned char *w_, unsigned int _w_high)
{
  unsigned int left;
  unsigned int u;
  int c;
  int width;
  int nextperc;
  int afterperc;
  int endpos;
  char leader;
  char ch;
  char ch2;
  DynamicStrings_String p;
  unsigned char w[_w_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (w, w_, _w_high+1);

  while ((*startpos) >= 0)
    {
      nextperc = DynamicStrings_Index (fmt, '%', (unsigned int) (*startpos));
      afterperc = nextperc;
      if (nextperc >= 0)
        {
          afterperc += 1;
          if ((DynamicStrings_char (fmt, afterperc)) == '-')
            {
              left = TRUE;
              afterperc += 1;
            }
          else
            left = FALSE;
          ch = DynamicStrings_char (fmt, afterperc);
          if (ch == '0')
            leader = '0';
          else
            leader = ' ';
          width = 0;
          while (IsDigit (ch))
            {
              width = (width*10)+((int ) (((unsigned int) (ch))-((unsigned int) ('0'))));
              afterperc += 1;
              ch = DynamicStrings_char (fmt, afterperc);
            }
          if ((ch == 'c') || (ch == 's'))
            {
              afterperc += 1;
              if (ch == 'c')
                {
                  ch2 = w[0];
                  p = DynamicStrings_ConCatChar (DynamicStrings_InitString ((char *) "", 0), ch2);
                }
              else
                {
                  Cast ((unsigned char *) &p, (sizeof (p)-1), (unsigned char *) w, _w_high);
                  p = DynamicStrings_Dup (p);
                }
              if ((width > 0) && (((int ) (DynamicStrings_Length (p))) < width))
                {
                  /* avoid gcc warning by using compound statement even if not strictly necessary.  */
                  if (left)
                    /* place trailing spaces after, p.  */
                    p = DynamicStrings_ConCat (p, DynamicStrings_Mark (DynamicStrings_Mult (DynamicStrings_Mark (DynamicStrings_InitString ((char *) " ", 1)), (unsigned int) width-((int ) (DynamicStrings_Length (p))))));
                  else
                    /* padd string, p, with leading spaces.  */
                    p = DynamicStrings_ConCat (DynamicStrings_Mult (DynamicStrings_Mark (DynamicStrings_InitString ((char *) " ", 1)), (unsigned int) width-((int ) (DynamicStrings_Length (p)))), DynamicStrings_Mark (p));
                }
              /* include string, p, into, in.  */
              if (nextperc > 0)
                in = DynamicStrings_ConCat (in, DynamicStrings_Slice (fmt, (*startpos), nextperc));
              in = DynamicStrings_ConCat (in, p);
              (*startpos) = afterperc;
              DSdbExit ((DynamicStrings_String) NULL);
              return in;
            }
          else if (ch == 'd')
            {
              afterperc += 1;
              Cast ((unsigned char *) &c, (sizeof (c)-1), (unsigned char *) w, _w_high);
              in = Copy (fmt, in, (*startpos), nextperc);
              in = DynamicStrings_ConCat (in, StringConvert_IntegerToString (c, (unsigned int) width, leader, FALSE, 10, FALSE));
              (*startpos) = afterperc;
              DSdbExit ((DynamicStrings_String) NULL);
              return in;
            }
          else if (ch == 'x')
            {
              afterperc += 1;
              Cast ((unsigned char *) &u, (sizeof (u)-1), (unsigned char *) w, _w_high);
              in = DynamicStrings_ConCat (in, DynamicStrings_Slice (fmt, (*startpos), nextperc));
              in = DynamicStrings_ConCat (in, StringConvert_CardinalToString (u, (unsigned int) width, leader, 16, TRUE));
              (*startpos) = afterperc;
              DSdbExit ((DynamicStrings_String) NULL);
              return in;
            }
          else if (ch == 'u')
            {
              afterperc += 1;
              Cast ((unsigned char *) &u, (sizeof (u)-1), (unsigned char *) w, _w_high);
              in = DynamicStrings_ConCat (in, DynamicStrings_Slice (fmt, (*startpos), nextperc));
              in = DynamicStrings_ConCat (in, StringConvert_CardinalToString (u, (unsigned int) width, leader, 10, FALSE));
              (*startpos) = afterperc;
              DSdbExit ((DynamicStrings_String) NULL);
              return in;
            }
          else
            {
              afterperc += 1;
              /* copy format string.  */
              if (nextperc > 0)
                in = DynamicStrings_ConCat (in, DynamicStrings_Slice (fmt, (*startpos), nextperc));
              /* and the character after the %.  */
              in = DynamicStrings_ConCat (in, DynamicStrings_Mark (DynamicStrings_InitStringChar (ch)));
            }
          (*startpos) = afterperc;
        }
      else
        {
          /* nothing to do.  */
          DSdbExit ((DynamicStrings_String) NULL);
          return in;
        }
    }
  DSdbExit ((DynamicStrings_String) NULL);
  return in;
}


/*
   Copy - copies, fmt[start:end] -> in and returns in.  Providing that start >= 0.
*/

static DynamicStrings_String Copy (DynamicStrings_String fmt, DynamicStrings_String in, int start, int end)
{
  if (start >= 0)
    {
      /* avoid gcc warning by using compound statement even if not strictly necessary.  */
      if (end > 0)
        in = DynamicStrings_ConCat (in, DynamicStrings_Mark (DynamicStrings_Slice (fmt, start, end)));
      else if (end < 0)
        in = DynamicStrings_ConCat (in, DynamicStrings_Mark (DynamicStrings_Slice (fmt, start, 0)));
    }
  return in;
}


/*
   HandlePercent - pre-condition:  s, is a string.
                   Post-condition:  a new string is returned which is a copy of,
                   s, except %% is transformed into %.
*/

static DynamicStrings_String HandlePercent (DynamicStrings_String fmt, DynamicStrings_String s, int startpos)
{
  int prevpos;
  DynamicStrings_String result;

  if ((startpos == (DynamicStrings_Length (fmt))) || (startpos < 0))
    return s;
  else
    {
      prevpos = startpos;
      while ((startpos >= 0) && (prevpos < ((int ) (DynamicStrings_Length (fmt)))))
        {
          startpos = DynamicStrings_Index (fmt, '%', (unsigned int) startpos);
          if (startpos >= prevpos)
            {
              if (startpos > 0)
                s = DynamicStrings_ConCat (s, DynamicStrings_Mark (DynamicStrings_Slice (fmt, prevpos, startpos)));
              startpos += 1;
              if ((DynamicStrings_char (fmt, startpos)) == '%')
                {
                  s = DynamicStrings_ConCatChar (s, '%');
                  startpos += 1;
                }
              prevpos = startpos;
            }
        }
      if (prevpos < ((int ) (DynamicStrings_Length (fmt))))
        s = DynamicStrings_ConCat (s, DynamicStrings_Mark (DynamicStrings_Slice (fmt, prevpos, 0)));
      return s;
    }
}


/*
   Sprintf0 - returns a String containing, s, after it has had its
              escape sequences translated.
*/

DynamicStrings_String FormatStrings_Sprintf0 (DynamicStrings_String fmt)
{
  DynamicStrings_String s;

  DSdbEnter ();
  fmt = HandleEscape (fmt);
  s = HandlePercent (fmt, DynamicStrings_InitString ((char *) "", 0), 0);
  DSdbExit (s);
  return s;
}


/*
   Sprintf1 - returns a String containing, s, together with encapsulated
              entity, w. It only formats the first %s or %d with n.
*/

DynamicStrings_String FormatStrings_Sprintf1 (DynamicStrings_String fmt, unsigned char *w_, unsigned int _w_high)
{
  int i;
  DynamicStrings_String s;
  unsigned char w[_w_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (w, w_, _w_high+1);

  DSdbEnter ();
  fmt = HandleEscape (fmt);
  i = 0;
  s = FormatString (fmt, &i, DynamicStrings_InitString ((char *) "", 0), (unsigned char *) w, _w_high);
  s = HandlePercent (fmt, s, i);
  DSdbExit (s);
  return s;
}


/*
   Sprintf2 - returns a string, s, which has been formatted.
*/

DynamicStrings_String FormatStrings_Sprintf2 (DynamicStrings_String fmt, unsigned char *w1_, unsigned int _w1_high, unsigned char *w2_, unsigned int _w2_high)
{
  int i;
  DynamicStrings_String s;
  unsigned char w1[_w1_high+1];
  unsigned char w2[_w2_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (w1, w1_, _w1_high+1);
  memcpy (w2, w2_, _w2_high+1);

  DSdbEnter ();
  fmt = HandleEscape (fmt);
  i = 0;
  s = FormatString (fmt, &i, DynamicStrings_InitString ((char *) "", 0), (unsigned char *) w1, _w1_high);
  s = FormatString (fmt, &i, s, (unsigned char *) w2, _w2_high);
  s = HandlePercent (fmt, s, i);
  DSdbExit (s);
  return s;
}


/*
   Sprintf3 - returns a string, s, which has been formatted.
*/

DynamicStrings_String FormatStrings_Sprintf3 (DynamicStrings_String fmt, unsigned char *w1_, unsigned int _w1_high, unsigned char *w2_, unsigned int _w2_high, unsigned char *w3_, unsigned int _w3_high)
{
  int i;
  DynamicStrings_String s;
  unsigned char w1[_w1_high+1];
  unsigned char w2[_w2_high+1];
  unsigned char w3[_w3_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (w1, w1_, _w1_high+1);
  memcpy (w2, w2_, _w2_high+1);
  memcpy (w3, w3_, _w3_high+1);

  DSdbEnter ();
  fmt = HandleEscape (fmt);
  i = 0;
  s = FormatString (fmt, &i, DynamicStrings_InitString ((char *) "", 0), (unsigned char *) w1, _w1_high);
  s = FormatString (fmt, &i, s, (unsigned char *) w2, _w2_high);
  s = FormatString (fmt, &i, s, (unsigned char *) w3, _w3_high);
  s = HandlePercent (fmt, s, i);
  DSdbExit (s);
  return s;
}


/*
   Sprintf4 - returns a string, s, which has been formatted.
*/

DynamicStrings_String FormatStrings_Sprintf4 (DynamicStrings_String fmt, unsigned char *w1_, unsigned int _w1_high, unsigned char *w2_, unsigned int _w2_high, unsigned char *w3_, unsigned int _w3_high, unsigned char *w4_, unsigned int _w4_high)
{
  int i;
  DynamicStrings_String s;
  unsigned char w1[_w1_high+1];
  unsigned char w2[_w2_high+1];
  unsigned char w3[_w3_high+1];
  unsigned char w4[_w4_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (w1, w1_, _w1_high+1);
  memcpy (w2, w2_, _w2_high+1);
  memcpy (w3, w3_, _w3_high+1);
  memcpy (w4, w4_, _w4_high+1);

  DSdbEnter ();
  fmt = HandleEscape (fmt);
  i = 0;
  s = FormatString (fmt, &i, DynamicStrings_InitString ((char *) "", 0), (unsigned char *) w1, _w1_high);
  s = FormatString (fmt, &i, s, (unsigned char *) w2, _w2_high);
  s = FormatString (fmt, &i, s, (unsigned char *) w3, _w3_high);
  s = FormatString (fmt, &i, s, (unsigned char *) w4, _w4_high);
  s = HandlePercent (fmt, s, i);
  DSdbExit (s);
  return s;
}

void _M2_FormatStrings_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_FormatStrings_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
