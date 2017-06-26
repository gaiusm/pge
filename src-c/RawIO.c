/* automatically created by mc from ../RawIO.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <string.h>
#include <limits.h>
#define _RawIO_H
#define _RawIO_C

#   include "GIOChan.h"
#   include "GIOConsts.h"
#   include "Glibc.h"


/*
   Read - storage units from cid, and assigns them to successive
          components of to.  The read result is set to the value
          allRight, wrongFormat, or endOfInput.
*/

void RawIO_Read (IOChan_ChanId cid, unsigned char *to, unsigned int _to_high);

/*
   Write - storage units to cid from successive components of from.
*/

void RawIO_Write (IOChan_ChanId cid, unsigned char *from_, unsigned int _from_high);

/*
   memDump -
*/

static void memDump (void * a, unsigned int len);


/*
   memDump -
*/

static void memDump (void * a, unsigned int len)
{
  unsigned int i;
  unsigned int j;
  unsigned char * p;

  p = a;
  j = 0;
  for (i=0; i<=len; i++)
    {
      if ((j % 16) == 0)
        libc_printf ((char *) "\\n%p  %02x", 10, p, (unsigned int ) ((*p)));
      else
        libc_printf ((char *) " %02x", 5, (unsigned int ) ((*p)));
      p += 1;
      j += 1;
    }
  libc_printf ((char *) "\\n", 2);
}


/*
   Read - storage units from cid, and assigns them to successive
          components of to.  The read result is set to the value
          allRight, wrongFormat, or endOfInput.
*/

void RawIO_Read (IOChan_ChanId cid, unsigned char *to, unsigned int _to_high)
{
  unsigned int i;
  unsigned int n;
  void * a;

  a = to;
  n = (_to_high)+1;
  for (;;)
  {
    IOChan_RawRead (cid, a, n, &i);
    if (((n == 0) || ((IOChan_ReadResult (cid)) == IOConsts_wrongFormat)) || ((IOChan_ReadResult (cid)) == IOConsts_endOfInput))
      return;
    else
      {
        a += i;
        n -= i;
      }
  }
}


/*
   Write - storage units to cid from successive components of from.
*/

void RawIO_Write (IOChan_ChanId cid, unsigned char *from_, unsigned int _from_high)
{
  unsigned char from[_from_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (from, from_, _from_high+1);

  IOChan_RawWrite (cid, &from, (_from_high)+1);
}

void _M2_RawIO_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_RawIO_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
