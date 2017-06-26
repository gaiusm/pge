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
 *   ldtoa.c -
 */

#define GM2

#define HAVE_STDLIB_H
#define HAVE_STRING

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#if defined(HAVE_STDLIB_H)
#  if !defined(_ISOC99_SOURCE)
#     define _ISOC99_SOURCE
#  endif
#  include <stdlib.h>
#endif

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

#define MAX_FP_DIGITS 500

typedef enum Mode { maxsignicant, decimaldigits } Mode;

extern int dtoa_calcmaxsig (char *p, int ndigits);
extern int dtoa_calcdecimal (char *p, int str_size, int ndigits);
extern int dtoa_calcsign (char *p, int str_size);

/*
 *  maxsignicant:  return a string containing max(1,ndigits) significant
 *                 digits.  The return string contains the string produced
 *                 by snprintf.
 *  decimaldigits: return a string produced by fcvt.  The string will
 *                 contain ndigits past the decimal point
 *                 (ndigits may be negative).
 */

long double ldtoa_strtold (const char *s, int *error)
{
  char *endp;
  long double d;

  errno = 0;
#if defined(HAVE_STRTOLD)
  d = strtold (s, &endp);
#else
  /* fall back to using strtod */
  d = (long double)strtod (s, &endp);
#endif
  if (endp != NULL && (*endp == '\0'))
    *error = (errno != 0);
  else
    *error = TRUE;
  return d;
}

char *ldtoa_ldtoa (long double d, int mode, int ndigits, int *decpt, int *sign)
{
  char format[50];
  char *p;
  int r;
  switch (mode) {

  case maxsignicant:
    ndigits += 20;   /* enough for exponent */
    p = malloc (ndigits);
    snprintf(format, 50, "%s%d%s", "%.", ndigits-20, "LE");
    snprintf(p, ndigits, format, d);
    *sign = dtoa_calcsign(p, ndigits);
    *decpt = dtoa_calcmaxsig(p, ndigits);
    return p;
  case decimaldigits:
    p = malloc (MAX_FP_DIGITS+20);
    snprintf(format, 50, "%s%d%s", "%.", MAX_FP_DIGITS, "LE");
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

void _M2_ldtoa_init (void) {}
void _M2_ldtoa_finish (void) {}
#endif
