/* automatically created by mc from /home/gaius/GM2/graft-6.4.0/gcc-6.4.0/gcc/gm2/gm2-libs-iso/CharClass.mod.  */

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
  return (ch >= '0') && (ch <= '9');
}

unsigned int CharClass_IsLetter (char ch)
{
  return ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'));
}

unsigned int CharClass_IsUpper (char ch)
{
  return (ch >= 'A') && (ch <= 'Z');
}

unsigned int CharClass_IsLower (char ch)
{
  return (ch >= 'a') && (ch <= 'z');
}

unsigned int CharClass_IsControl (char ch)
{
  return ch < ' ';
}

unsigned int CharClass_IsWhiteSpace (char ch)
{
  return (((ch == ' ') || (ch == ASCII_cr)) || (ch == ASCII_lf)) || (ch == ASCII_tab);
}

void _M2_CharClass_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_CharClass_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
