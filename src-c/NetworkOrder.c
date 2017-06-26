/* automatically created by mc from ../NetworkOrder.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#include <string.h>
#include <limits.h>
#define _NetworkOrder_H
#define _NetworkOrder_C

#   include "GSYSTEM.h"
#   include "Gnetwork.h"
#   include "GRawIO.h"
#   include "GFractions.h"
#   include "GPoints.h"
#   include "Glibc.h"
#   include "GM2RTS.h"

#if !defined (IOChan_ChanId_D)
#  define IOChan_ChanId_D
   typedef void *IOChan_ChanId;
#endif

typedef struct {
                   double x;
                   double y;
               } coord_Coord;

#   define debugging FALSE

/*
   writeReal -
*/

void NetworkOrder_writeReal (IOChan_ChanId file, double r);

/*
   writeCard -
*/

void NetworkOrder_writeCard (IOChan_ChanId file, unsigned int c);

/*
   writeFract -
*/

void NetworkOrder_writeFract (IOChan_ChanId file, Fractions_Fract f);

/*
   writePoint -
*/

void NetworkOrder_writePoint (IOChan_ChanId file, Points_Point p);

/*
   writeCoord -
*/

void NetworkOrder_writeCoord (IOChan_ChanId file, coord_Coord c);
void NetworkOrder_writeLongCard (IOChan_ChanId file, long unsigned int l);

/*
   writeShort -
*/

void NetworkOrder_writeShort (IOChan_ChanId file, short unsigned int s);

/*
   get2x32 -
*/

static void get2x32 (unsigned char *l_, unsigned int _l_high, unsigned char *lo, unsigned int _lo_high, unsigned char *hi, unsigned int _hi_high);

/*
   set2x32 -
*/

static void set2x32 (unsigned char *l_, unsigned int _l_high, unsigned char *lo_, unsigned int _lo_high, unsigned char *hi_, unsigned int _hi_high);

/*
   htonl64 - implements a 64 bit long unsigned network order transformation.
*/

static long unsigned int htonl64 (long unsigned int l);


/*
   get2x32 -
*/

static void get2x32 (unsigned char *l_, unsigned int _l_high, unsigned char *lo, unsigned int _lo_high, unsigned char *hi, unsigned int _hi_high)
{
  unsigned int i;
  unsigned char l[_l_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (l, l_, _l_high+1);

  if ((_l_high) == ((_lo_high)+(_hi_high)))
    {
      i = 0;
      while (i < (_lo_high))
        {
          lo[i] = l[i];
          i += 1;
        }
      while (i < (_l_high))
        {
          hi[i-(_lo_high)] = l[i];
          i += 1;
        }
    }
  else
    M2RTS_HALT (0);
}


/*
   set2x32 -
*/

static void set2x32 (unsigned char *l_, unsigned int _l_high, unsigned char *lo_, unsigned int _lo_high, unsigned char *hi_, unsigned int _hi_high)
{
  unsigned int i;
  unsigned char l[_l_high+1];
  unsigned char lo[_lo_high+1];
  unsigned char hi[_hi_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (l, l_, _l_high+1);
  memcpy (lo, lo_, _lo_high+1);
  memcpy (hi, hi_, _hi_high+1);

  if ((_l_high) == ((_lo_high)+(_hi_high)))
    {
      i = 0;
      while (i < (_lo_high))
        {
          l[i] = lo[i];
          i += 1;
        }
      while (i < (_l_high))
        {
          l[i] = hi[i-(_lo_high)];
          i += 1;
        }
    }
  else
    M2RTS_HALT (0);
}


/*
   htonl64 - implements a 64 bit long unsigned network order transformation.
*/

static long unsigned int htonl64 (long unsigned int l)
{
  short unsigned int s;
  unsigned int lo;
  unsigned int hi;

  s = 1;
  if (s == (network_htons (s)))
    return l;
  get2x32 ((unsigned char *) &l, (sizeof (l)-1), (unsigned char *) &lo, (sizeof (lo)-1), (unsigned char *) &hi, (sizeof (hi)-1));
  lo = network_htonl (lo);
  hi = network_htonl (hi);
  set2x32 ((unsigned char *) &l, (sizeof (l)-1), (unsigned char *) &hi, (sizeof (hi)-1), (unsigned char *) &lo, (sizeof (lo)-1));
  return l;
}


/*
   writeReal -
*/

void NetworkOrder_writeReal (IOChan_ChanId file, double r)
{
  if (debugging)
    libc_printf ((char *) "about to write real %g\\n", 24, r);
  RawIO_Write (file, (unsigned char *) &r, (sizeof (r)-1));
}


/*
   writeCard -
*/

void NetworkOrder_writeCard (IOChan_ChanId file, unsigned int c)
{
  c = network_htonl (c);
  RawIO_Write (file, (unsigned char *) &c, (sizeof (c)-1));
}


/*
   writeFract -
*/

void NetworkOrder_writeFract (IOChan_ChanId file, Fractions_Fract f)
{
  long unsigned int w;
  long unsigned int n;
  long unsigned int d;
  unsigned char l;

  if (Fractions_isZero (f))
    {
      l = (unsigned char ) (0);
      RawIO_Write (file, (unsigned char *) &l, (sizeof (l)-1));
    }
  else if (Fractions_isOne (f))
    {
      l = (unsigned char ) (1);
      RawIO_Write (file, (unsigned char *) &l, (sizeof (l)-1));
    }
  else
    {
      Fractions_getFract (f, &w, &n, &d);
      if (w == 0)
        {
          l = (unsigned char ) (2);
          RawIO_Write (file, (unsigned char *) &l, (sizeof (l)-1));
          NetworkOrder_writeLongCard (file, n);
          NetworkOrder_writeLongCard (file, d);
        }
      else
        {
          l = (unsigned char ) (3);
          RawIO_Write (file, (unsigned char *) &l, (sizeof (l)-1));
          NetworkOrder_writeLongCard (file, w);
          NetworkOrder_writeLongCard (file, n);
          NetworkOrder_writeLongCard (file, d);
        }
    }
}


/*
   writePoint -
*/

void NetworkOrder_writePoint (IOChan_ChanId file, Points_Point p)
{
  NetworkOrder_writeFract (file, p.x);
  NetworkOrder_writeFract (file, p.y);
}


/*
   writeCoord -
*/

void NetworkOrder_writeCoord (IOChan_ChanId file, coord_Coord c)
{
  NetworkOrder_writeReal (file, c.x);
  NetworkOrder_writeReal (file, c.y);
}

void NetworkOrder_writeLongCard (IOChan_ChanId file, long unsigned int l)
{
  typedef struct _T1_a _T1;

  struct _T1_a { unsigned int array[1+1]; };
  unsigned int lo;
  unsigned int hi;
  _T1 * p;

  p = &l;
  lo = (*p).array[0];
  hi = (*p).array[1];
  NetworkOrder_writeCard (file, hi);
  NetworkOrder_writeCard (file, lo);
}


/*
   writeShort -
*/

void NetworkOrder_writeShort (IOChan_ChanId file, short unsigned int s)
{
  s = network_htons (s);
  RawIO_Write (file, (unsigned char *) &s, (sizeof (s)-1));
}

void _M2_NetworkOrder_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_NetworkOrder_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
