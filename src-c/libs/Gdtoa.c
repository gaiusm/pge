/* Copyright (C) 2016,
 *               Free Software Foundation, Inc. */
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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA */

/*
 *   dtoa.c -
 */

#define GM2

#define HAVE_STDLIB_H
#define HAVE_STRING


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#if defined(HAVE_STRINGS)
#  include <strings.h>
#endif

#if defined(HAVE_STRING)
#  include <string.h>
#endif


#if !defined(TRUE)
#  define TRUE (1==1)
#endif
#if !defined(FALSE)
#  define FALSE (1==0)
#endif

#if defined(HAVE_STDLIB_H)
#  if !defined(_ISOC99_SOURCE)
#     define _ISOC99_SOURCE
#  endif
#  include <stdlib.h>
#endif

#define MAX_FP_DIGITS 500

typedef enum Mode { maxsignicant, decimaldigits } Mode;

/*
 *  maxsignicant:  return a string containing max(1,ndigits) significant
 *                 digits.  The return string contains the string produced
 *                 by ecvt.
 *  decimaldigits: return a string produced by fcvt.  The string will
 *                 contain ndigits past the decimal point
 *                 (ndigits may be negative).
 */

double dtoa_strtod (const char *s, int *error)
{
  char *endp;
  double d;

  errno = 0;
  d = strtod (s, &endp);
  if (endp != NULL && (*endp == '\0'))
    *error = (errno != 0);
  else
    *error = TRUE;
  return d;
}

/*
 *  dtoa_calcmaxsig - calculates the position of the decimal point
 *                    it also removes the decimal point and exponent
 *                    from string, p.
 */

int dtoa_calcmaxsig (char *p, int ndigits)
{
  char *e;
  char *o;
  int x;

  e = index (p, 'E');
  if (e == NULL)
    x = 0;
  else {
    *e = (char)0;
    x = atoi(e+1);
  }

  o = index (p, '.');
  if (o == NULL)
    return strlen(p)+x;
  else {
    strncpy(o, o+1, ndigits-(o-p));
    return o-p+x;
  }
}

/*
 *  dtoa_calcdecimal - calculates the position of the decimal point
 *                     it also removes the decimal point and exponent
 *                     from string, p.  It truncates the digits in p
 *                     accordingly to ndigits.  Ie ndigits is the
 *                     number of digits after the '.'
 */

int dtoa_calcdecimal (char *p, int str_size, int ndigits)
{
  char *e;
  char *o;
  int x;
  int l;

  e = index (p, 'E');
  if (e == NULL)
    x = 0;
  else {
    *e = (char)0;
    x = atoi(e+1);
  }

  l = strlen (p);
  o = index (p, '.');
  if (o == NULL)
    x += strlen(p);
  else {
    int m = strlen(o);
    memcpy(o, o+1, l-(o-p));
    if (m>0)
      o[m-1] = '0';
    x += o-p;
  }
  if ((x+ndigits >= 0) && (x+ndigits < str_size))
    p[x+ndigits] = (char)0;
  return x;
}

int dtoa_calcsign (char *p, int str_size)
{
  if (p[0] == '-') {
    strncpy(p, p+1, str_size-1);
    return TRUE;
  } else
    return FALSE;
}

char *dtoa_dtoa (double d, int mode, int ndigits, int *decpt, int *sign)
{
  char format[50];
  char *p;
  int r;
  switch (mode) {

  case maxsignicant:
    ndigits += 20;   /* enough for exponent */
    p = malloc (ndigits);
    snprintf(format, 50, "%s%d%s", "%.", ndigits-20, "E");
    snprintf(p, ndigits, format, d);
    *sign = dtoa_calcsign(p, ndigits);
    *decpt = dtoa_calcmaxsig(p, ndigits);
    return p;
  case decimaldigits:
    p = malloc (MAX_FP_DIGITS+20);
    snprintf(format, 50, "%s%d%s", "%.", MAX_FP_DIGITS, "E");
    snprintf(p, MAX_FP_DIGITS+20, format, d);
    *sign = dtoa_calcsign(p, MAX_FP_DIGITS+20);
    *decpt = dtoa_calcdecimal(p, MAX_FP_DIGITS+20, ndigits);
    return p;
  default:
    abort();
  }
}

#if defined(GM2)
/*
 *  GNU Modula-2 hooks
 */

void _M2_dtoa_init (void) {}
void _M2_dtoa_finish (void) {}
#endif
