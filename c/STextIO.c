/* automatically created by mc from /home/gaius/GM2/graft-6.4.0/gcc-6.4.0/gcc/gm2/gm2-libs-iso/STextIO.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <string.h>
#include <limits.h>
#define _STextIO_H
#define _STextIO_C

#   include "GStdChans.h"
#   include "GTextIO.h"

void STextIO_ReadChar (char *ch);
void STextIO_ReadRestLine (char *s, unsigned int _s_high);
void STextIO_ReadString (char *s, unsigned int _s_high);
void STextIO_ReadToken (char *s, unsigned int _s_high);
void STextIO_SkipLine (void);
void STextIO_WriteChar (char ch);
void STextIO_WriteLn (void);
void STextIO_WriteString (char *s_, unsigned int _s_high);

void STextIO_ReadChar (char *ch)
{
  TextIO_ReadChar ((IOChan_ChanId) StdChans_StdInChan (), ch);
}

void STextIO_ReadRestLine (char *s, unsigned int _s_high)
{
  TextIO_ReadRestLine ((IOChan_ChanId) StdChans_StdInChan (), (char *) s, _s_high);
}

void STextIO_ReadString (char *s, unsigned int _s_high)
{
  TextIO_ReadString ((IOChan_ChanId) StdChans_StdInChan (), (char *) s, _s_high);
}

void STextIO_ReadToken (char *s, unsigned int _s_high)
{
  TextIO_ReadToken ((IOChan_ChanId) StdChans_StdInChan (), (char *) s, _s_high);
}

void STextIO_SkipLine (void)
{
  TextIO_SkipLine ((IOChan_ChanId) StdChans_StdInChan ());
}

void STextIO_WriteChar (char ch)
{
  TextIO_WriteChar ((IOChan_ChanId) StdChans_StdOutChan (), ch);
}

void STextIO_WriteLn (void)
{
  TextIO_WriteLn ((IOChan_ChanId) StdChans_StdOutChan ());
}

void STextIO_WriteString (char *s_, unsigned int _s_high)
{
  char s[_s_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (s, s_, _s_high+1);

  TextIO_WriteString ((IOChan_ChanId) StdChans_StdOutChan (), (char *) s, _s_high);
}

void _M2_STextIO_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_STextIO_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
