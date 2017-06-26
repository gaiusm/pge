/* automatically created by mc from ../deviceIf.mod.  */

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
#   include "Gmcrts.h"
#define _deviceIf_H
#define _deviceIf_C

#   include "GMemStream.h"
#   include "GClientSocket.h"
#   include "GSeqFile.h"
#   include "GRawIO.h"
#   include "GFractions.h"
#   include "GIOChan.h"
#   include "GChanConsts.h"
#   include "GSYSTEM.h"
#   include "Glibc.h"
#   include "GGC.h"
#   include "GPoints.h"
#   include "GDynamicStrings.h"
#   include "GNetworkOrder.h"
#   include "GM2RTS.h"

typedef unsigned int deviceIf_Colour;

#   define whiteCID 1
#   define blackCID 2
#   define redCID 3
#   define greenCID 4
#   define blueCID 5
#   define yellowCID 6
#   define purpleCID 7
#   define nextCID 8
#   define MaxColours 4096
#   define FPS 30
#   define DebugTrace FALSE
typedef struct _T1_r _T1;

typedef unsigned int SetOfColours;

typedef _T1 *configDesc;

struct _T1_r {
               GC_entity centity;
               Points_Point inMax;
               Points_Point outMax;
               unsigned int same;
               unsigned int fps;
             };

static enum {none, groff, rpc, buffer} device;
static IOChan_ChanId ffile;
static IOChan_ChanId cfile;
static SetOfColours registered;
static unsigned int nextColour;
static unsigned int nextFrame;
static void * fbufferStart;
static unsigned int fbufferLength;
static unsigned int fbufferUsed;
static void * cbufferStart;
static unsigned int cbufferLength;
static unsigned int cbufferUsed;
static GC_garbage configHeap;
static configDesc config;

/*
   white - returns the colour, white.
*/

deviceIf_Colour deviceIf_white (void);

/*
   black - returns the colour, black.
*/

deviceIf_Colour deviceIf_black (void);

/*
   red - returns the colour, red.
*/

deviceIf_Colour deviceIf_red (void);

/*
   green - returns the colour, green.
*/

deviceIf_Colour deviceIf_green (void);

/*
   blue - returns the colour, blue.
*/

deviceIf_Colour deviceIf_blue (void);

/*
   yellow - returns the colour, yellow.
*/

deviceIf_Colour deviceIf_yellow (void);

/*
   purple - returns the colour, purple.
*/

deviceIf_Colour deviceIf_purple (void);

/*
   glyphLine - draw a line between:  start and end of, thick, thickness and colour, c.
*/

void deviceIf_glyphLine (Points_Point start, Points_Point end, Fractions_Fract thick, deviceIf_Colour c);

/*
   glyphPolygon - draw a polygon given n absolute points.
                  If fill then it is filled with colour, c, else it is drawn with
                  thickness in outline using colour, c.
*/

void deviceIf_glyphPolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c);

/*
   glyphCircle - draw a circle at point, pos.  If fill then it is filled by colour, c,
                 otherwise it is drawn in outline with a thickness, thick, in colour, c.
*/

void deviceIf_glyphCircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, deviceIf_Colour c);

/*
   flipBuffer - renders the current buffer and then sets up a new buffer to be
                populated by new glyphs.
*/

void deviceIf_flipBuffer (void);

/*
   frameNote - emit a note to indicate a new frame has commenced.
*/

void deviceIf_frameNote (void);

/*
   emptyCbuffer - empty the colour buffer (this only applies if the module is using
                  the buffer device).
*/

void deviceIf_emptyCbuffer (void);

/*
   emptyFbuffer - empty the frame buffer (this only applies if the module is using
                  the buffer device).
*/

void deviceIf_emptyFbuffer (void);

/*
   writeTime - writes the delay, t, to the frame buffer (if t > 0.0).
*/

void deviceIf_writeTime (double t);

/*
   defineColour - defines a colour by: r, g, b.  The fracts
                  are given to the colour and a colour index
                  is returned.  Colours live for ever and are
                  never freed.
*/

unsigned int deviceIf_defineColour (Fractions_Fract r, Fractions_Fract g, Fractions_Fract b);

/*
   useGroff - use the groff device to render frames into png images.
*/

void deviceIf_useGroff (void);

/*
   useBuffer - place the objects into a frame buffer.
*/

void deviceIf_useBuffer (void);

/*
   useRPC - use the rpc device connect to a server to render frames.
*/

void deviceIf_useRPC (void);

/*
   finish - close the device file.
*/

void deviceIf_finish (void);

/*
   configDevice - configure the output device to have outMax resolution.
*/

void deviceIf_configDevice (Points_Point inMax, Points_Point outMax, unsigned int fps);

/*
   getFrameBuffer - collects the frame buffer limits in the following parameters.
*/

void deviceIf_getFrameBuffer (void * *start, unsigned int *length, unsigned int *used);

/*
   getColourBuffer - collects the colour buffer limits in the following parameters.
*/

void deviceIf_getColourBuffer (void * *start, unsigned int *length, unsigned int *used);

/*
   checkOpened -
*/

static void checkOpened (void);

/*
   registerColour -
*/

static deviceIf_Colour registerColour (deviceIf_Colour cid, Fractions_Fract r, Fractions_Fract g, Fractions_Fract b);

/*
   writeColour -
*/

static void writeColour (deviceIf_Colour c);

/*
   scaleX -
*/

static Fractions_Fract scaleX (Fractions_Fract x);

/*
   scaleY - it assumes that, y, is an absolute position on the y axis.
*/

static Fractions_Fract scaleY (Fractions_Fract y);

/*
   markConfig -
*/

static void markConfig (GC_entity e);

/*
   Init -
*/

static void Init (void);


/*
   checkOpened -
*/

static void checkOpened (void)
{
  if (device == none)
    {
      libc_printf ((char *) "device must be configured before anything can be displayed\\n", 60);
      libc_exit (1);
    }
}


/*
   registerColour -
*/

static deviceIf_Colour registerColour (deviceIf_Colour cid, Fractions_Fract r, Fractions_Fract g, Fractions_Fract b)
{
  if ((((1 << (cid)) & (registered)) != 0))
    {
      /* avoid dangling else.  */
      if (DebugTrace)
        libc_printf ((char *) "colour %d already registered\\n", 30, cid);
    }
  else
    {
      checkOpened ();
      if (DebugTrace)
        libc_printf ((char *) "register colour %d\\n", 20, cid);
      registered |= (1 << (cid ));
      if (DebugTrace)
        libc_printf ((char *) "  output rc command\\n", 21);
      RawIO_Write (cfile, (unsigned char *) "rc", 2);
      NetworkOrder_writeShort (cfile, (short unsigned int) cid);
      NetworkOrder_writeFract (cfile, r);
      NetworkOrder_writeFract (cfile, g);
      NetworkOrder_writeFract (cfile, b);
    }
  return cid;
}


/*
   writeColour -
*/

static void writeColour (deviceIf_Colour c)
{
  NetworkOrder_writeShort (ffile, (short unsigned int) c);
}


/*
   scaleX -
*/

static Fractions_Fract scaleX (Fractions_Fract x)
{
  if (config->same)
    return Fractions_dup (x);
  else
    return Fractions_div (Fractions_mult (config->outMax.x, x), config->inMax.x);
}


/*
   scaleY - it assumes that, y, is an absolute position on the y axis.
*/

static Fractions_Fract scaleY (Fractions_Fract y)
{
  if (config->same)
    return Fractions_dup (y);
  else
    return Fractions_div (Fractions_mult (config->outMax.y, y), config->inMax.y);
}


/*
   markConfig -
*/

static void markConfig (GC_entity e)
{
  configDesc c;

  c = GC_getData (e);
  if (c == config)
    {
      GC_markEntity (config->centity);
      Points_markPoint (config->inMax);
      Points_markPoint (config->outMax);
    }
  else
    M2RTS_HALT (0);
}


/*
   Init -
*/

static void Init (void)
{
  GC_entity e;

  nextColour = nextCID;
  registered = (SetOfColours) 0;
  nextFrame = 1;
  fbufferStart = NULL;
  fbufferLength = 0;
  fbufferUsed = 0;
  cbufferStart = NULL;
  cbufferLength = 0;
  cbufferUsed = 0;
  device = none;
  configHeap = GC_initGarbage ((GC_walkP) {(GC_walkP_t) markConfig}, (unsigned int) sizeof ((*config)), DynamicStrings_InitString ((char *) "config", 6));
  GC_rootAllocate (configHeap, &e, (void **) &config);
  config->centity = e;
  deviceIf_configDevice (Points_initPoint (Fractions_one (), Fractions_one ()), Points_initPoint (Fractions_one (), Fractions_one ()), FPS);
}


/*
   white - returns the colour, white.
*/

deviceIf_Colour deviceIf_white (void)
{
  return registerColour ((deviceIf_Colour) whiteCID, Fractions_one (), Fractions_one (), Fractions_one ());
}


/*
   black - returns the colour, black.
*/

deviceIf_Colour deviceIf_black (void)
{
  return registerColour ((deviceIf_Colour) blackCID, Fractions_zero (), Fractions_zero (), Fractions_zero ());
}


/*
   red - returns the colour, red.
*/

deviceIf_Colour deviceIf_red (void)
{
  return registerColour ((deviceIf_Colour) redCID, Fractions_one (), Fractions_zero (), Fractions_zero ());
}


/*
   green - returns the colour, green.
*/

deviceIf_Colour deviceIf_green (void)
{
  return registerColour ((deviceIf_Colour) greenCID, Fractions_zero (), Fractions_one (), Fractions_zero ());
}


/*
   blue - returns the colour, blue.
*/

deviceIf_Colour deviceIf_blue (void)
{
  return registerColour ((deviceIf_Colour) blueCID, Fractions_zero (), Fractions_zero (), Fractions_one ());
}


/*
   yellow - returns the colour, yellow.
*/

deviceIf_Colour deviceIf_yellow (void)
{
  return registerColour ((deviceIf_Colour) yellowCID, Fractions_one (), Fractions_one (), Fractions_zero ());
}


/*
   purple - returns the colour, purple.
*/

deviceIf_Colour deviceIf_purple (void)
{
  return registerColour ((deviceIf_Colour) purpleCID, Fractions_one (), Fractions_zero (), Fractions_one ());
}


/*
   glyphLine - draw a line between:  start and end of, thick, thickness and colour, c.
*/

void deviceIf_glyphLine (Points_Point start, Points_Point end, Fractions_Fract thick, deviceIf_Colour c)
{
  checkOpened ();
  RawIO_Write (ffile, (unsigned char *) "dl", 2);
  NetworkOrder_writePoint (ffile, start);
  NetworkOrder_writePoint (ffile, end);
  NetworkOrder_writeFract (ffile, thick);
  writeColour (c);
}


/*
   glyphPolygon - draw a polygon given n absolute points.
                  If fill then it is filled with colour, c, else it is drawn with
                  thickness in outline using colour, c.
*/

void deviceIf_glyphPolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c)
{
  unsigned int i;
  Points_Point p[_p_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (p, p_, (_p_high+1) * sizeof (Points_Point));

  checkOpened ();
  if (fill)
    RawIO_Write (ffile, (unsigned char *) "dP", 2);
  else
    RawIO_Write (ffile, (unsigned char *) "dp", 2);
  NetworkOrder_writeShort (ffile, (short unsigned int) n);
  for (i=0; i<=n-1; i++)
    NetworkOrder_writePoint (ffile, (Points_Point) p[i]);
  if (fill)
    writeColour (c);
  else
    NetworkOrder_writeFract (ffile, thick);
}


/*
   glyphCircle - draw a circle at point, pos.  If fill then it is filled by colour, c,
                 otherwise it is drawn in outline with a thickness, thick, in colour, c.
*/

void deviceIf_glyphCircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, deviceIf_Colour c)
{
  checkOpened ();
  if (fill)
    RawIO_Write (ffile, (unsigned char *) "dC", 2);
  else
    RawIO_Write (ffile, (unsigned char *) "dc", 2);
  NetworkOrder_writePoint (ffile, pos);
  NetworkOrder_writeFract (ffile, rad);
  if (fill)
    writeColour (c);
  else
    NetworkOrder_writeFract (ffile, thick);
}


/*
   flipBuffer - renders the current buffer and then sets up a new buffer to be
                populated by new glyphs.
*/

void deviceIf_flipBuffer (void)
{
  if (DebugTrace)
    libc_printf ((char *) "deviceIf: flipBuffer \\n", 23);
  if (device == none)
    deviceIf_useBuffer ();
  RawIO_Write (ffile, (unsigned char *) "fb", 2);
}


/*
   frameNote - emit a note to indicate a new frame has commenced.
*/

void deviceIf_frameNote (void)
{
  checkOpened ();
  if (device == groff)
    {
      RawIO_Write (ffile, (unsigned char *) "fn", 2);
      NetworkOrder_writeCard (ffile, nextFrame);
    }
  nextFrame += 1;
}


/*
   emptyCbuffer - empty the colour buffer (this only applies if the module is using
                  the buffer device).
*/

void deviceIf_emptyCbuffer (void)
{
  if (device == buffer)
    {
      if (DebugTrace)
        libc_printf ((char *) "rewrite\\n", 9);
      MemStream_Rewrite (cfile);
    }
}


/*
   emptyFbuffer - empty the frame buffer (this only applies if the module is using
                  the buffer device).
*/

void deviceIf_emptyFbuffer (void)
{
  if (device == buffer)
    {
      if (DebugTrace)
        libc_printf ((char *) "rewrite\\n", 9);
      MemStream_Rewrite (ffile);
    }
}


/*
   writeTime - writes the delay, t, to the frame buffer (if t > 0.0).
*/

void deviceIf_writeTime (double t)
{
  if (t > 0.0)
    {
      checkOpened ();
      RawIO_Write (ffile, (unsigned char *) "sl", 2);
      RawIO_Write (ffile, (unsigned char *) &t, (sizeof (t)-1));
    }
}


/*
   defineColour - defines a colour by: r, g, b.  The fracts
                  are given to the colour and a colour index
                  is returned.  Colours live for ever and are
                  never freed.
*/

unsigned int deviceIf_defineColour (Fractions_Fract r, Fractions_Fract g, Fractions_Fract b)
{
  unsigned int col;

  col = nextColour;
  nextColour += 1;
  return registerColour ((deviceIf_Colour) col, r, g, b);
}


/*
   useGroff - use the groff device to render frames into png images.
*/

void deviceIf_useGroff (void)
{
  ChanConsts_OpenResults res;

  device = groff;
  SeqFile_OpenWrite ((SeqFile_ChanId*) &ffile, (char *) "output.raw", 10, (SeqFile_FlagSet) ChanConsts_write|ChanConsts_raw, (SeqFile_OpenResults*) &res);
  if (res != ChanConsts_opened)
    {
      libc_printf ((char *) "something went wrong when trying to open the raw output file\\n", 62);
      libc_exit (1);
    }
  cfile = ffile;
}


/*
   useBuffer - place the objects into a frame buffer.
*/

void deviceIf_useBuffer (void)
{
  ChanConsts_OpenResults res;

  device = buffer;
  MemStream_OpenWrite (&ffile, ChanConsts_write|ChanConsts_raw, &res, &fbufferStart, &fbufferLength, &fbufferUsed, TRUE);
  if (res != ChanConsts_opened)
    {
      libc_printf ((char *) "deviceIf.useBuffer: something went wrong when trying to open the frame memstream file\\n", 87);
      libc_exit (1);
    }
  MemStream_OpenWrite (&cfile, ChanConsts_write|ChanConsts_raw, &res, &cbufferStart, &cbufferLength, &cbufferUsed, TRUE);
  if (res != ChanConsts_opened)
    {
      libc_printf ((char *) "deviceIf.useBuffer: something went wrong when trying to open the colour memstream file\\n", 88);
      libc_exit (1);
    }
}


/*
   useRPC - use the rpc device connect to a server to render frames.
*/

void deviceIf_useRPC (void)
{
  ChanConsts_OpenResults res;
  int r;

  device = rpc;
  do {
    ClientSocket_OpenSocket (&ffile, (char *) "localhost", 9, 6000, ((ChanConsts_read|ChanConsts_write)|ChanConsts_raw)|ChanConsts_text, &res);
    if (res != ChanConsts_opened)
      {
        libc_printf ((char *) "unable to connect to localhost:6000\\n", 37);
        r = libc_system ("sleep 1");
      }
  } while (! (res == ChanConsts_opened));
}


/*
   finish - close the device file.
*/

void deviceIf_finish (void)
{
  checkOpened ();
  RawIO_Write (ffile, (unsigned char *) "ex", 2);
  RawIO_Write (ffile, (unsigned char *) "\00", 0);
  switch (device)
    {
      case groff:
        SeqFile_Close ((SeqFile_ChanId*) &ffile);
        break;

      case rpc:
        ClientSocket_Close (&ffile);
        break;

      case buffer:
        MemStream_Close (&ffile);
        MemStream_Close (&cfile);
        break;


      default:
        CaseException ("..//deviceIf.def", 2, 1);
    }
}


/*
   configDevice - configure the output device to have outMax resolution.
*/

void deviceIf_configDevice (Points_Point inMax, Points_Point outMax, unsigned int fps)
{
  config->inMax = Points_dupPoint (inMax);
  config->outMax = Points_dupPoint (outMax);
  config->same = (Fractions_areEqual (inMax.x, outMax.x)) && (Fractions_areEqual (inMax.y, outMax.y));
  config->fps = fps;
}


/*
   getFrameBuffer - collects the frame buffer limits in the following parameters.
*/

void deviceIf_getFrameBuffer (void * *start, unsigned int *length, unsigned int *used)
{
  (*start) = fbufferStart;
  (*length) = fbufferLength;
  (*used) = fbufferUsed;
  if (DebugTrace)
    libc_printf ((char *) "getFrameBuffer (addr = 0x%p, length = %d, used = %d)\\n", 54, (*start), (*length), (*used));
}


/*
   getColourBuffer - collects the colour buffer limits in the following parameters.
*/

void deviceIf_getColourBuffer (void * *start, unsigned int *length, unsigned int *used)
{
  (*start) = cbufferStart;
  (*length) = cbufferLength;
  (*used) = cbufferUsed;
  if (DebugTrace)
    libc_printf ((char *) "getColourBuffer (addr = 0x%p, length = %d, used = %d)\\n", 55, (*start), (*length), (*used));
}

void _M2_deviceIf_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_deviceIf_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
