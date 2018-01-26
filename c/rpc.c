/* automatically created by mc from ../git-pge/m2/rpc.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <string.h>
#include <limits.h>
#define _rpc_H
#define _rpc_C

#   include "GSYSTEM.h"
#   include "GRawIO.h"
#   include "Glibc.h"

typedef struct rpc_cc_r rpc_cc;

typedef enum {rpc_ready, rpc_problem} rpc_rpcStatus;

#if !defined (IOChan_ChanId_D)
#  define IOChan_ChanId_D
   typedef void *IOChan_ChanId;
#endif

typedef IOChan_ChanId SeqFile_ChanId;

struct rpc_cc_r {
                  unsigned int x;
                  unsigned int y;
                };


/*
   initcc - initialises a, cc, structure.
*/

rpc_cc rpc_initcc (unsigned int x, unsigned int y);

/*
   colour - registers a colour with pygame and cid is assigned with the python colour, id.
*/

rpc_rpcStatus rpc_colour (SeqFile_ChanId file, unsigned int r, unsigned int g, unsigned int b, unsigned int *cid);

/*
   polygon - writes a filled polygon to the pygame display.
             Polygon to be filled with colour, cid.
*/

rpc_rpcStatus rpc_polygon (SeqFile_ChanId file, unsigned int cid, unsigned int n, rpc_cc *p_, unsigned int _p_high);

/*
   circle - writes a filled circle to the pygame display.
            Circle to be filled with colour, cid.
*/

rpc_rpcStatus rpc_circle (SeqFile_ChanId file, unsigned int cid, rpc_cc center, unsigned int radius);

/*
   drawLine - draw a line on the pygame screen from p1 to p2 with thickness and colour, id.
*/

rpc_rpcStatus rpc_drawLine (SeqFile_ChanId file, unsigned int cid, rpc_cc p1, rpc_cc p2, unsigned int thickness);

/*
   resolution - sets the resolution of Pygame.
*/

rpc_rpcStatus rpc_resolution (SeqFile_ChanId file, rpc_cc res);

/*
   flipbuffer - flips the pygame frame buffer.
*/

rpc_rpcStatus rpc_flipbuffer (SeqFile_ChanId file);

/*
   writeString - writes a string to the socket, file.
*/

static void writeString (SeqFile_ChanId file, char *a_, unsigned int _a_high, rpc_rpcStatus *res);

/*
   writeCardinal - writes a cardinal to the socket, file.
*/

static void writeCardinal (SeqFile_ChanId file, unsigned int c, rpc_rpcStatus *res);

/*
   writeByte - writes the lowest single byte of cardinal, c.
*/

static void writeByte (SeqFile_ChanId file, unsigned int c, rpc_rpcStatus *res);

/*
   readCardinal - reads a cardinal from, file.
*/

static unsigned int readCardinal (SeqFile_ChanId file, rpc_rpcStatus *res);


/*
   writeString - writes a string to the socket, file.
*/

static void writeString (SeqFile_ChanId file, char *a_, unsigned int _a_high, rpc_rpcStatus *res)
{
  unsigned int i;
  unsigned int n;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  i = 0;
  n = _a_high;
  while ((i <= n) && ((*res) == rpc_ready))
    {
      RawIO_Write ((IOChan_ChanId) file, (unsigned char *) &a[i], (sizeof (a[i])-1));
      i += 1;
    }
}


/*
   writeCardinal - writes a cardinal to the socket, file.
*/

static void writeCardinal (SeqFile_ChanId file, unsigned int c, rpc_rpcStatus *res)
{
  if ((*res) == rpc_ready)
    RawIO_Write ((IOChan_ChanId) file, (unsigned char *) &c, (sizeof (c)-1));
}


/*
   writeByte - writes the lowest single byte of cardinal, c.
*/

static void writeByte (SeqFile_ChanId file, unsigned int c, rpc_rpcStatus *res)
{
  unsigned char b;

  if ((*res) == rpc_ready)
    {
      b = (unsigned char ) (c % 0x0100);
      RawIO_Write ((IOChan_ChanId) file, (unsigned char *) &b, (sizeof (b)-1));
    }
}


/*
   readCardinal - reads a cardinal from, file.
*/

static unsigned int readCardinal (SeqFile_ChanId file, rpc_rpcStatus *res)
{
  unsigned int cid;

  cid = 0;
  if ((*res) == rpc_ready)
    RawIO_Read ((IOChan_ChanId) file, (unsigned char *) &cid, (sizeof (cid)-1));
  return cid;
}


/*
   initcc - initialises a, cc, structure.
*/

rpc_cc rpc_initcc (unsigned int x, unsigned int y)
{
  rpc_cc c;

  c.x = x;
  c.y = y;
  return c;
}


/*
   colour - registers a colour with pygame and cid is assigned with the python colour, id.
*/

rpc_rpcStatus rpc_colour (SeqFile_ChanId file, unsigned int r, unsigned int g, unsigned int b, unsigned int *cid)
{
  rpc_rpcStatus res;

  res = rpc_ready;
  writeString (file, (char *) "o", 1, &res);
  writeByte (file, r, &res);
  writeByte (file, g, &res);
  writeByte (file, b, &res);
  (*cid) = readCardinal (file, &res);
  /* printf("colour id returned, %d
  ", cid) ;  */
  return res;
}


/*
   polygon - writes a filled polygon to the pygame display.
             Polygon to be filled with colour, cid.
*/

rpc_rpcStatus rpc_polygon (SeqFile_ChanId file, unsigned int cid, unsigned int n, rpc_cc *p_, unsigned int _p_high)
{
  unsigned int i;
  rpc_rpcStatus res;
  rpc_cc p[_p_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (p, p_, (_p_high+1) * sizeof (rpc_cc));

  res = rpc_ready;
  writeString (file, (char *) "P", 1, &res);
  writeCardinal (file, cid, &res);
  writeCardinal (file, n, &res);
  i = 0;
  while (i < n)
    {
      writeCardinal (file, p[i].x, &res);
      writeCardinal (file, p[i].y, &res);
      i += 1;
    }
  return res;
}


/*
   circle - writes a filled circle to the pygame display.
            Circle to be filled with colour, cid.
*/

rpc_rpcStatus rpc_circle (SeqFile_ChanId file, unsigned int cid, rpc_cc center, unsigned int radius)
{
  unsigned int i;
  rpc_rpcStatus res;

  res = rpc_ready;
  /* printf("circle
  ") ;  */
  writeString (file, (char *) "C", 1, &res);
  writeCardinal (file, cid, &res);
  writeCardinal (file, center.x, &res);
  writeCardinal (file, center.y, &res);
  writeCardinal (file, radius, &res);
  /* printf("done
  ") ;  */
  return res;
}


/*
   drawLine - draw a line on the pygame screen from p1 to p2 with thickness and colour, id.
*/

rpc_rpcStatus rpc_drawLine (SeqFile_ChanId file, unsigned int cid, rpc_cc p1, rpc_cc p2, unsigned int thickness)
{
  rpc_rpcStatus res;

  res = rpc_ready;
  writeString (file, (char *) "l", 1, &res);
  writeCardinal (file, cid, &res);
  writeCardinal (file, p1.x, &res);
  writeCardinal (file, p1.y, &res);
  writeCardinal (file, p2.x, &res);
  writeCardinal (file, p2.y, &res);
  return res;
}


/*
   resolution - sets the resolution of Pygame.
*/

rpc_rpcStatus rpc_resolution (SeqFile_ChanId file, rpc_cc res)
{
  rpc_rpcStatus ret;

  ret = rpc_ready;
  writeString (file, (char *) "r", 1, &ret);
  /* printf("x, y = %d, %d
  ", res.x, res.y) ;  */
  writeCardinal (file, res.x, &ret);
  writeCardinal (file, res.y, &ret);
  return ret;
}


/*
   flipbuffer - flips the pygame frame buffer.
*/

rpc_rpcStatus rpc_flipbuffer (SeqFile_ChanId file)
{
  rpc_rpcStatus res;

  res = rpc_ready;
  writeString (file, (char *) "f", 1, &res);
  return res;
}

void _M2_rpc_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_rpc_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
