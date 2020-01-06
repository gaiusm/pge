/* This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GNU Modula-2 is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with gm2; see the file COPYING.  If not, write to the Free Software
Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _CharClass_H
#define _CharClass_C

#   include "GASCII.h"

unsigned int CharClass_IsNumeric (char ch);
unsigned int CharClass_IsLetter (char ch);
unsigned int CharClass_IsUpper (char ch);
unsigned int CharClass_IsLower (char ch);
unsigned int CharClass_IsControl (char ch);
unsigned int CharClass_IsWhiteSpace (char ch);

unsigned int CharClass_IsNumeric (char ch)
{
  /* Returns TRUE if and only if ch is classified as a numeric character  */
  return (ch >= '0') && (ch <= '9');
}

unsigned int CharClass_IsLetter (char ch)
{
  /* Returns TRUE if and only if ch is classified as a letter  */
  return ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'));
}

unsigned int CharClass_IsUpper (char ch)
{
  /* Returns TRUE if and only if ch is classified as an upper case letter  */
  return (ch >= 'A') && (ch <= 'Z');
}

unsigned int CharClass_IsLower (char ch)
{
  /* Returns TRUE if and only if ch is classified as a lower case letter  */
  return (ch >= 'a') && (ch <= 'z');
}

unsigned int CharClass_IsControl (char ch)
{
  /* Returns TRUE if and only if ch represents a control function  */
  return ch < ' ';
}

unsigned int CharClass_IsWhiteSpace (char ch)
{
  /* Returns TRUE if and only if ch represents a space character or a format effector  */
  return (((ch == ' ') || (ch == ASCII_cr)) || (ch == ASCII_lf)) || (ch == ASCII_tab);
}

void _M2_CharClass_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_CharClass_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
