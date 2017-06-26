/* automatically created by mc from ../deviceGroff.mod.  */

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
#   include "GStorage.h"
#   include "Gmcrts.h"
#define _deviceGroff_H
#define _deviceGroff_C

#   include "Glibc.h"
#   include "GSYSTEM.h"
#   include "GFormatStrings.h"
#   include "GDynamicStrings.h"
#   include "GSeqFile.h"
#   include "GTextIO.h"
#   include "GRealIO.h"
#   include "GIndexing.h"
#   include "GPoints.h"
#   include "GFractions.h"
#   include "GStorage.h"
#   include "GStringConvert.h"
#   include "GGC.h"
#   include "Gdelay.h"
#   include "GAssertion.h"
#   include "GM2RTS.h"

typedef unsigned int deviceGroff_Colour;

#   define Debugging FALSE
#   define Exec TRUE
#   define Height 5
#   define Width Height
#   define Header 1
#   define Margin 1
#   define MaxName 20
#   define maxPoints 10
typedef struct circleDesc_r circleDesc;

typedef struct polygonDesc_r polygonDesc;

typedef struct gProcedure_p gProcedure;

typedef struct _T1_r _T1;

typedef _T1 *colourDesc;

typedef struct _T2_a _T2;

typedef struct _T3_r _T3;

typedef _T3 *glyphDesc;

typedef struct _T4_r _T4;

typedef _T4 *configDesc;

typedef enum {circle, polygon} typeOfGlyph;

typedef enum {leftEdge, rightEdge, topEdge, botEdge} edges;

typedef unsigned int clipCode;

struct circleDesc_r {
                      Points_Point center;
                      unsigned int filled;
                      Fractions_Fract thickness;
                      Fractions_Fract radius;
                      colourDesc colour;
                    };

typedef void (*gProcedure_t) (glyphDesc);
struct gProcedure_p { gProcedure_t proc; };

struct _T1_r {
               DynamicStrings_String name;
               Fractions_Fract r;
               Fractions_Fract g;
               Fractions_Fract b;
               unsigned int used;
             };

struct _T2_a { Points_Point array[maxPoints+1]; };
struct _T4_r {
               GC_entity centity;
               Points_Point inMax;
               Points_Point outMax;
               unsigned int same;
               unsigned int fps;
               unsigned int separateFiles;
               unsigned int mpeg;
               unsigned int ps;
               unsigned int evince;
             };

struct polygonDesc_r {
                       unsigned int filled;
                       Fractions_Fract thickness;
                       unsigned int noPoints;
                       _T2 pArray;
                       colourDesc colour;
                     };

struct _T3_r {
               typeOfGlyph type;  /* case tag */
               union {
                       circleDesc gCircle;
                       polygonDesc gPolygon;
                     };
               glyphDesc next;
             };

static unsigned int frameNo;
static DynamicStrings_String filename;
static SeqFile_ChanId file;
static Indexing_Index cArray;
static unsigned int cNum;
static configDesc config;
static unsigned int evinceRunning;
static glyphDesc gHead;
static glyphDesc gFree;
static deviceGroff_Colour cPurple;
static deviceGroff_Colour cYellow;
static deviceGroff_Colour cWhite;
static deviceGroff_Colour cBlack;
static deviceGroff_Colour cRed;
static deviceGroff_Colour cGreen;
static deviceGroff_Colour cBlue;
static GC_garbage configHeap;
static unsigned int firstFrame;

/*
   configDevice - configure the output device to have outMax resolution and whether
                  it should produce a sequence of individual troff files which
                  can be combined to make a mpeg movie.  Or alternatively whether
                  each frame should be dynamically rendered into a postscript
                  file displayed by 'gv'.
*/

void deviceGroff_configDevice (Points_Point inMax, Points_Point outMax, unsigned int fps, unsigned int separateFiles, unsigned int mpeg, unsigned int ps, unsigned int gv);

/*
   white - returns the colour, white.
*/

unsigned int deviceGroff_white (void);

/*
   black - returns the colour, black.
*/

unsigned int deviceGroff_black (void);

/*
   red - returns the colour, red.
*/

unsigned int deviceGroff_red (void);

/*
   green - returns the colour, green.
*/

unsigned int deviceGroff_green (void);

/*
   blue - returns the colour, blue.
*/

unsigned int deviceGroff_blue (void);

/*
   yellow - returns the colour, yellow.
*/

unsigned int deviceGroff_yellow (void);

/*
   purple - returns the colour, purple.
*/

unsigned int deviceGroff_purple (void);

/*
   glyphLine - draw a line between:  start and end of, thick, thickness and colour, c.
*/

void deviceGroff_glyphLine (Points_Point start, Points_Point end, Fractions_Fract thick, deviceGroff_Colour c);

/*
   glyphPolygon - draw a polygon from pos, with n points.
                  If fill then it is filled with colour, c, else it is drawn with
                  thickness in outline using colour, c.
                  Note that this procedure takes copies of all fractions and points.
*/

void deviceGroff_glyphPolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, deviceGroff_Colour c);

/*
   glyphCircle - draw a circle at point, pos.  If fill then it is filled by colour, c,
                 otherwise it is drawn in outline with a thickness, thick, in colour, c.
                 Note that this procedure takes copies of all fractions and points.
*/

void deviceGroff_glyphCircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, deviceGroff_Colour c);

/*
   flipBuffer - renders the current buffer and then sets up a new buffer to be
                populated by new glyphs.
*/

void deviceGroff_flipBuffer (void);

/*
   defineColour - defines a colour by: r, g, b.  The fracts
                  are given to the colour and a colour index
                  is returned.  Colours live for ever and are
                  never freed.  The values, r, g, b, are dup'ed
                  and root'ed.
*/

unsigned int deviceGroff_defineColour (Fractions_Fract r, Fractions_Fract g, Fractions_Fract b);

/*
   Init - initialise this module.
*/

void deviceGroff_Init (void);

/*
   flushGlyphs - draw each glyph in list, gHead, and
                 then kill each glyph.
*/

static void flushGlyphs (void);

/*
   empty - returns TRUE if the gHead list is empty.
*/

static unsigned int empty (void);

/*
   addToEnd - adds, g, to the end of, gHead.
*/

static void addToEnd (glyphDesc g);

/*
   newGlyph - returns a new glyphDesc.  It initialises next to NIL.
*/

static glyphDesc newGlyph (void);

/*
   disposeGlyph - returns, g, to the free list.
*/

static void disposeGlyph (glyphDesc *g);

/*
   killGlyph - releases any resource held by, g, and disposes of, g.
*/

static void killGlyph (glyphDesc *g);

/*
   killCircle - returns any Fracts held by circle to the free list.
                We leave colour alone.
*/

static void killCircle (glyphDesc g);

/*
   killPolygon - returns any Fracts held by polygon to the free list.
                 We leave colour alone.
*/

static void killPolygon (glyphDesc g);

/*
   foreachGlyphDo - foreach glyph do, p(g).
*/

static void foreachGlyphDo (gProcedure p);

/*
   makeTemporaryName -
*/

static DynamicStrings_String makeTemporaryName (char *a_, unsigned int _a_high);

/*
   writeColourDef - writes out the colour definition.
*/

static void writeColourDef (colourDesc c);

/*
   writeColour -
*/

static void writeColour (colourDesc c);

/*
   setColourUnused -
*/

static void setColourUnused (colourDesc c);

/*
   writeColourUsed -
*/

static void writeColourUsed (colourDesc c);

/*
   newFrame - creates a new frame.
*/

static void newFrame (void);

/*
   setColourUsed -
*/

static void setColourUsed (glyphDesc g);

/*
   debugSystem -
*/

static void debugSystem (DynamicStrings_String s);

/*
   generatePNG - generate a png file, this assumes that configDesc.separateFiles is TRUE.
*/

static void generatePNG (void);

/*
   generatePS - generate a PS file, which is dynamically re-read by 'evince'.
*/

static void generatePS (void);

/*
   drawGlyph - draws glyph, g.
*/

static void drawGlyph (glyphDesc g);

/*
   WriteLongCard - writes, c, to the output file.
*/

static void WriteLongCard (long unsigned int c);

/*
   writeUnit - writes out, u, to the output, file.
*/

static void writeUnit (Fractions_Fract u);

/*
   scaleX -
*/

static Fractions_Fract scaleX (Fractions_Fract x);

/*
   relScaleX -
*/

static Fractions_Fract relScaleX (Fractions_Fract x);

/*
   scaleY - it assumes that, y, is an absolute position on the y axis.
*/

static Fractions_Fract scaleY (Fractions_Fract y);

/*
   relScaleY - scales, y, it assumes this is a relative y movement.
*/

static Fractions_Fract relScaleY (Fractions_Fract y);

/*
   scalePoint - returns a new point after x and y have been scaled to
                fit the output resolution.  Point, p, is an absolute
                position.
*/

static Points_Point scalePoint (Points_Point p);

/*
   addOffset - adds the x, y, offsets to a point, p.  The same point, p,
               is returned.  Currently only an offset in the Y axis is added.
*/

static Points_Point addOffset (Points_Point p);

/*
   moveTo - moves to the absolute position defined by, p.
*/

static void moveTo (Points_Point p);

/*
   dumpFract -
*/

static void dumpFract (Fractions_Fract f);

/*
   dumpPoint - displays point, p.
*/

static void dumpPoint (Points_Point p);

/*
   dumpPolygon -
*/

static void dumpPolygon (glyphDesc g);

/*
   dumpColour -
*/

static void dumpColour (colourDesc c);

/*
   dumpCircle -
*/

static void dumpCircle (glyphDesc g);

/*
   dumpg - dumps, g, for debugging.
*/

static void dumpg (glyphDesc g);

/*
   drawCircle -
*/

static void drawCircle (glyphDesc g);

/*
   clipped - returns the clip set for point, p.
*/

static clipCode clipped (Points_Point p);

/*
   drawLine - draws line (if visibly on screen after clipping),
              p1, p2, given colour and thickness.
*/

static void drawLine (Points_Point p1, Points_Point p2, colourDesc colour, Fractions_Fract thickness);

/*
   clipLine - clips line: p1, p2.  It returns TRUE if any part of
              line p1, and, p2 can be placed on the screen.
              It then assigns the values o1, o2 to these coordinates.
              If FALSE is returned then o1, o2 are unassigned.
*/

static unsigned int clipLine (Points_Point p1, Points_Point p2, Points_Point *o1, Points_Point *o2);
static void stop (void);

/*
   drawPolygon -
*/

static void drawPolygon (glyphDesc g);

/*
   produceAVI - generate an AVI file from the sequence of png images.
*/

static void produceAVI (unsigned int fps, unsigned int width, unsigned int height);

/*
   markConfig -
*/

static void markConfig (GC_entity e);


/*
   flushGlyphs - draw each glyph in list, gHead, and
                 then kill each glyph.
*/

static void flushGlyphs (void)
{
  glyphDesc f;
  glyphDesc g;

  g = gHead;
  while (g != NULL)
    {
      drawGlyph (g);
      f = g;
      g = g->next;
      killGlyph (&f);
    }
  gHead = NULL;
}


/*
   empty - returns TRUE if the gHead list is empty.
*/

static unsigned int empty (void)
{
  return gHead == NULL;
}


/*
   addToEnd - adds, g, to the end of, gHead.
*/

static void addToEnd (glyphDesc g)
{
  glyphDesc f;

  if (gHead == NULL)
    gHead = g;
  else
    {
      f = gHead;
      while (f->next != NULL)
        f = f->next;
      f->next = g;
    }
}


/*
   newGlyph - returns a new glyphDesc.  It initialises next to NIL.
*/

static glyphDesc newGlyph (void)
{
  glyphDesc g;

  if (gFree == NULL)
    Storage_ALLOCATE ((void **) &g, sizeof (_T3));
  else
    {
      g = gFree;
      gFree = gFree->next;
    }
  g->next = NULL;
  return g;
}


/*
   disposeGlyph - returns, g, to the free list.
*/

static void disposeGlyph (glyphDesc *g)
{
  (*g)->next = gFree;
  gFree = (*g);
}


/*
   killGlyph - releases any resource held by, g, and disposes of, g.
*/

static void killGlyph (glyphDesc *g)
{
  switch ((*g)->type)
    {
      case circle:
        killCircle ((*g));
        break;

      case polygon:
        killPolygon ((*g));
        break;


      default:
        CaseException ("..//deviceGroff.def", 1, 15);
    }
  disposeGlyph (g);
}


/*
   killCircle - returns any Fracts held by circle to the free list.
                We leave colour alone.
*/

static void killCircle (glyphDesc g)
{
  if (g->type == circle)
    {
      g->gCircle.center = Points_unRootPoint (g->gCircle.center);
      g->gCircle.thickness = Fractions_unroot (g->gCircle.thickness);
      g->gCircle.radius = Fractions_unroot (g->gCircle.radius);
    }
  else
    M2RTS_HALT (0);
}


/*
   killPolygon - returns any Fracts held by polygon to the free list.
                 We leave colour alone.
*/

static void killPolygon (glyphDesc g)
{
  unsigned int i;

  if (g->type == polygon)
    {
      g->gPolygon.thickness = Fractions_unroot (g->gPolygon.thickness);
      for (i=0; i<=g->gPolygon.noPoints-1; i++)
        g->gPolygon.pArray.array[i] = Points_unRootPoint ((Points_Point) g->gPolygon.pArray.array[i]);
    }
  else
    M2RTS_HALT (0);
}


/*
   foreachGlyphDo - foreach glyph do, p(g).
*/

static void foreachGlyphDo (gProcedure p)
{
  glyphDesc g;

  g = gHead;
  while (g != NULL)
    {
      (*p.proc) (g);
      g = g->next;
    }
}


/*
   makeTemporaryName -
*/

static DynamicStrings_String makeTemporaryName (char *a_, unsigned int _a_high)
{
  DynamicStrings_String s;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  s = DynamicStrings_Mark (DynamicStrings_InitString ((char *) a, _a_high));
  return FormatStrings_Sprintf2 (DynamicStrings_InitString ((char *) "%s%d", 4), (unsigned char *) &s, (sizeof (s)-1), (unsigned char *) &cNum, (sizeof (cNum)-1));
}


/*
   writeColourDef - writes out the colour definition.
*/

static void writeColourDef (colourDesc c)
{
  typedef struct _T5_a _T5;

  struct _T5_a { char array[MaxName+1]; };
  _T5 a;
  double d;

  TextIO_WriteString ((IOChan_ChanId) file, (char *) ".defcolor ", 10);
  DynamicStrings_CopyOut ((char *) &a.array[0], MaxName, c->name);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) &a.array[0], MaxName);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) " rgb ", 5);
  d = Fractions_getReal (c->r);
  RealIO_WriteFixed ((IOChan_ChanId) file, d, 4, 4);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) "f ", 2);
  d = Fractions_getReal (c->g);
  RealIO_WriteFixed ((IOChan_ChanId) file, d, 4, 4);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) "f ", 2);
  d = Fractions_getReal (c->b);
  RealIO_WriteFixed ((IOChan_ChanId) file, d, 4, 4);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) "f ", 2);
  TextIO_WriteLn ((IOChan_ChanId) file);
}


/*
   writeColour -
*/

static void writeColour (colourDesc c)
{
  typedef struct _T6_a _T6;

  struct _T6_a { char array[MaxName+1]; };
  _T6 a;

  DynamicStrings_CopyOut ((char *) &a.array[0], MaxName, c->name);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) &a.array[0], MaxName);
}


/*
   setColourUnused -
*/

static void setColourUnused (colourDesc c)
{
  c->used = FALSE;
}


/*
   writeColourUsed -
*/

static void writeColourUsed (colourDesc c)
{
  if (c->used)
    writeColourDef (c);
}


/*
   newFrame - creates a new frame.
*/

static void newFrame (void)
{
  typedef struct _T7_a _T7;

  struct _T7_a { char array[MaxName+1]; };
  _T7 name;
  SeqFile_OpenResults res;

  if (! (empty ()))
    {
      frameNo += 1;
      if (frameNo == 16)
        stop ();
      filename = FormatStrings_Sprintf1 (DynamicStrings_InitString ((char *) "f%06d.ms", 8), (unsigned char *) &frameNo, (sizeof (frameNo)-1));
      DynamicStrings_CopyOut ((char *) &name.array[0], MaxName, filename);
      SeqFile_OpenWrite (&file, (char *) &name.array[0], MaxName, SeqFile_text|SeqFile_write, &res);
      Indexing_ForeachIndiceInIndexDo (cArray, (Indexing_IndexProcedure) {(Indexing_IndexProcedure_t) setColourUnused});
      foreachGlyphDo ((gProcedure) {(gProcedure_t) setColourUsed});
      Indexing_ForeachIndiceInIndexDo (cArray, (Indexing_IndexProcedure) {(Indexing_IndexProcedure_t) writeColourUsed});
      TextIO_WriteString ((IOChan_ChanId) file, (char *) ".ll 8i", 6);
      TextIO_WriteLn ((IOChan_ChanId) file);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) ".nop \\&", 7);
      TextIO_WriteLn ((IOChan_ChanId) file);
    }
}


/*
   setColourUsed -
*/

static void setColourUsed (glyphDesc g)
{
  switch (g->type)
    {
      case circle:
        g->gCircle.colour->used = TRUE;
        break;

      case polygon:
        g->gPolygon.colour->used = TRUE;
        break;


      default:
        CaseException ("..//deviceGroff.def", 1, 15);
    }
}


/*
   debugSystem -
*/

static void debugSystem (DynamicStrings_String s)
{
  int r;

  if (Debugging)
    libc_printf ((char *) "%s\\n", 4, DynamicStrings_string (s));
  r = libc_system (DynamicStrings_string (s));
  if (r != 0)
    libc_printf ((char *) "%s  -> returned %d\\n", 20, DynamicStrings_string (s), r);
}


/*
   generatePNG - generate a png file, this assumes that configDesc.separateFiles is TRUE.
*/

static void generatePNG (void)
{
  DynamicStrings_String s;

  if (config->separateFiles)
    {
      s = FormatStrings_Sprintf2 (DynamicStrings_InitString ((char *) "groff %s > f%06d.ps", 19), (unsigned char *) &filename, (sizeof (filename)-1), (unsigned char *) &frameNo, (sizeof (frameNo)-1));
      debugSystem (s);
      s = DynamicStrings_KillString (s);
      s = FormatStrings_Sprintf2 (DynamicStrings_InitString ((char *) "gs -dNOPAUSE -sDEVICE=pnmraw -sOutputFile=t%06d.pnm -dGraphicsAlphaBits=4 -q -dBATCH f%06d.ps > /dev/null 2>&1", 110), (unsigned char *) &frameNo, (sizeof (frameNo)-1), (unsigned char *) &frameNo, (sizeof (frameNo)-1));
      debugSystem (s);
      s = DynamicStrings_KillString (s);
      s = FormatStrings_Sprintf2 (DynamicStrings_InitString ((char *) "pnmcrop -quiet < t%06d.pnm | pnmtopng > e%06d.png 2> /dev/null", 62), (unsigned char *) &frameNo, (sizeof (frameNo)-1), (unsigned char *) &frameNo, (sizeof (frameNo)-1));
      debugSystem (s);
      s = DynamicStrings_KillString (s);
      s = FormatStrings_Sprintf2 (DynamicStrings_InitString ((char *) "convert e%06d.png -type truecolor f%06d.png 2> /dev/null", 56), (unsigned char *) &frameNo, (sizeof (frameNo)-1), (unsigned char *) &frameNo, (sizeof (frameNo)-1));
      debugSystem (s);
      s = DynamicStrings_KillString (s);
      s = FormatStrings_Sprintf3 (DynamicStrings_InitString ((char *) "rm t%06d.pnm f%06d.ps e%06d.png", 31), (unsigned char *) &frameNo, (sizeof (frameNo)-1), (unsigned char *) &frameNo, (sizeof (frameNo)-1), (unsigned char *) &frameNo, (sizeof (frameNo)-1));
      debugSystem (s);
      s = DynamicStrings_KillString (s);
      filename = DynamicStrings_KillString (filename);
    }
}


/*
   generatePS - generate a PS file, which is dynamically re-read by 'evince'.
*/

static void generatePS (void)
{
  DynamicStrings_String s;

  s = FormatStrings_Sprintf1 (DynamicStrings_InitString ((char *) "groff %s > PS", 13), (unsigned char *) &filename, (sizeof (filename)-1));
  debugSystem (s);
  s = DynamicStrings_KillString (s);
  if (! evinceRunning)
    {
      s = DynamicStrings_InitString ((char *) "gv --watch PS &", 15);
      debugSystem (s);
      s = DynamicStrings_KillString (s);
      evinceRunning = TRUE;
    }
}


/*
   drawGlyph - draws glyph, g.
*/

static void drawGlyph (glyphDesc g)
{
  switch (g->type)
    {
      case circle:
        drawCircle (g);
        break;

      case polygon:
        drawPolygon (g);
        break;


      default:
        CaseException ("..//deviceGroff.def", 1, 15);
    }
}


/*
   WriteLongCard - writes, c, to the output file.
*/

static void WriteLongCard (long unsigned int c)
{
  typedef struct _T8_a _T8;

  struct _T8_a { char array[20+1]; };
  DynamicStrings_String s;
  _T8 a;

  s = StringConvert_LongCardinalToString (c, 0, ' ', 10, FALSE);
  DynamicStrings_CopyOut ((char *) &a.array[0], 20, s);
  s = DynamicStrings_KillString (s);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) &a.array[0], 20);
}


/*
   writeUnit - writes out, u, to the output, file.
*/

static void writeUnit (Fractions_Fract u)
{
  long unsigned int w;
  long unsigned int n;
  long unsigned int d;

  if (Fractions_isZero (u))
    TextIO_WriteString ((IOChan_ChanId) file, (char *) "(u;0i)", 6);
  else
    {
      if (Fractions_isNegative (u))
        TextIO_WriteString ((IOChan_ChanId) file, (char *) "-", 1);
      Fractions_getFract (u, &w, &n, &d);
      if ((d == 0) || (n == 0))
        {
          TextIO_WriteString ((IOChan_ChanId) file, (char *) "(u;", 3);
          WriteLongCard (w);
          TextIO_WriteString ((IOChan_ChanId) file, (char *) "i)", 2);
        }
      else
        {
          TextIO_WriteString ((IOChan_ChanId) file, (char *) "(u;", 3);
          TextIO_WriteString ((IOChan_ChanId) file, (char *) "(", 1);
          if (w > 0)
            {
              WriteLongCard (w);
              TextIO_WriteString ((IOChan_ChanId) file, (char *) "i+(", 3);
              n = n % 10000;
              WriteLongCard (n);
              TextIO_WriteString ((IOChan_ChanId) file, (char *) "i/", 2);
              d = d % 10000;
              WriteLongCard (d);
              TextIO_WriteString ((IOChan_ChanId) file, (char *) ")", 1);
            }
          else
            {
              WriteLongCard (n);
              TextIO_WriteString ((IOChan_ChanId) file, (char *) "i/", 2);
              WriteLongCard (d);
            }
          TextIO_WriteString ((IOChan_ChanId) file, (char *) "))", 2);
        }
    }
}


/*
   scaleX -
*/

static Fractions_Fract scaleX (Fractions_Fract x)
{
  return relScaleX (x);
}


/*
   relScaleX -
*/

static Fractions_Fract relScaleX (Fractions_Fract x)
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
  Fractions_Fract r;

  r = relScaleY (y);
  return Fractions_add (config->outMax.y, r);
}


/*
   relScaleY - scales, y, it assumes this is a relative y movement.
*/

static Fractions_Fract relScaleY (Fractions_Fract y)
{
  Fractions_Fract r;

  if (config->same)
    r = Fractions_negate (y);
  else
    r = Fractions_negate (Fractions_div (Fractions_mult (config->outMax.y, y), config->inMax.y));
  return r;
}


/*
   scalePoint - returns a new point after x and y have been scaled to
                fit the output resolution.  Point, p, is an absolute
                position.
*/

static Points_Point scalePoint (Points_Point p)
{
  Points_Point p1;

  p1.x = scaleX (p.x);
  p1.y = scaleY (p.y);
  return p1;
}


/*
   addOffset - adds the x, y, offsets to a point, p.  The same point, p,
               is returned.  Currently only an offset in the Y axis is added.
*/

static Points_Point addOffset (Points_Point p)
{
  p.x = Fractions_inc (p.x, Fractions_cardinal (Margin));
  p.y = Fractions_inc (p.y, Fractions_cardinal (Header));
  return p;
}


/*
   moveTo - moves to the absolute position defined by, p.
*/

static void moveTo (Points_Point p)
{
  Points_Point p1;
  Fractions_Fract x;
  Fractions_Fract y;

  p1 = scalePoint (p);
  p1 = addOffset (p1);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) ".sp |", 5);
  writeUnit (p1.y);
  TextIO_WriteLn ((IOChan_ChanId) file);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) ".nop \\h'", 8);
  writeUnit (p1.x);
  TextIO_WriteString ((IOChan_ChanId) file, (char *) "'", 1);
  TextIO_WriteLn ((IOChan_ChanId) file);
  p1 = Points_unRootPoint (p1);
}


/*
   dumpFract -
*/

static void dumpFract (Fractions_Fract f)
{
  long unsigned int w;
  long unsigned int n;
  long unsigned int d;

  if (Fractions_isZero (f))
    libc_printf ((char *) " 0", 2);
  else
    {
      if (Fractions_isNegative (f))
        libc_printf ((char *) " -", 2);
      Fractions_getFract (f, &w, &n, &d);
      libc_printf ((char *) "%ld", 3, w);
      if (n != 0)
        libc_printf ((char *) ".%ld/%ld", 8, n, d);
    }
}


/*
   dumpPoint - displays point, p.
*/

static void dumpPoint (Points_Point p)
{
  libc_printf ((char *) " (", 2);
  dumpFract (p.x);
  libc_printf ((char *) ", ", 2);
  dumpFract (p.y);
  libc_printf ((char *) ") ", 2);
}


/*
   dumpPolygon -
*/

static void dumpPolygon (glyphDesc g)
{
  unsigned int i;

  if (g->gPolygon.filled)
    libc_printf ((char *) "polygon filled ", 15);
  else
    {
      libc_printf ((char *) "polygon outlined by thickness ", 30);
      dumpFract (g->gPolygon.thickness);
    }
  libc_printf ((char *) "in colour ", 10);
  dumpColour (g->gPolygon.colour);
  for (i=0; i<=g->gPolygon.noPoints-1; i++)
    dumpPoint ((Points_Point) g->gPolygon.pArray.array[i]);
  libc_printf ((char *) " \\n", 3);
}


/*
   dumpColour -
*/

static void dumpColour (colourDesc c)
{
  void * s;

  s = DynamicStrings_string (c->name);
  libc_printf ((char *) "%s", 2, s);
}


/*
   dumpCircle -
*/

static void dumpCircle (glyphDesc g)
{
  if (g->gCircle.filled)
    libc_printf ((char *) "circle filled ", 14);
  else
    {
      libc_printf ((char *) "circle outlined by thickness ", 29);
      dumpFract (g->gCircle.thickness);
    }
  libc_printf ((char *) "in colour ", 10);
  dumpColour (g->gCircle.colour);
  libc_printf ((char *) " at ", 4);
  dumpPoint (g->gCircle.center);
  libc_printf ((char *) " radius ", 8);
  dumpFract (g->gCircle.radius);
  libc_printf ((char *) " \\n", 3);
}


/*
   dumpg - dumps, g, for debugging.
*/

static void dumpg (glyphDesc g)
{
  switch (g->type)
    {
      case circle:
        dumpCircle (g);
        break;

      case polygon:
        dumpPolygon (g);
        break;


      default:
        CaseException ("..//deviceGroff.def", 1, 15);
    }
}


/*
   drawCircle -
*/

static void drawCircle (glyphDesc g)
{
  moveTo (Points_initPoint (Fractions_sub (g->gCircle.center.x, g->gCircle.radius), g->gCircle.center.y));
  TextIO_WriteString ((IOChan_ChanId) file, (char *) ".nop ", 5);
  if (g->gCircle.filled)
    {
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "\\M[", 3);
      writeColour (g->gCircle.colour);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "]", 1);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "\\D'C ", 5);
      writeUnit (scaleX (Fractions_mult (g->gCircle.radius, Fractions_two ())));
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\M[]", 5);
      TextIO_WriteLn ((IOChan_ChanId) file);
    }
  else
    {
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "\\D't ", 5);
      writeUnit (g->gCircle.thickness);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\h'-", 5);
      writeUnit (g->gCircle.thickness);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\c", 3);
      TextIO_WriteLn ((IOChan_ChanId) file);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) ".nop \\m[", 8);
      writeColour (g->gCircle.colour);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "]", 1);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "\\D'c ", 5);
      writeUnit (scaleX (Fractions_mult (g->gCircle.radius, Fractions_two ())));
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\m[]", 5);
      TextIO_WriteLn ((IOChan_ChanId) file);
    }
}


/*
   clipped - returns the clip set for point, p.
*/

static clipCode clipped (Points_Point p)
{
  clipCode c;

  c = (clipCode) 0;
  if (Fractions_isLess (p.x, Fractions_zero ()))
    c = (clipCode) ((1 << (leftEdge-leftEdge)));
  else if (Fractions_isGreater (p.x, Fractions_one ()))
    c = (clipCode) ((1 << (rightEdge-leftEdge)));
  if (Fractions_isLess (p.y, Fractions_zero ()))
    c = (clipCode) ((1 << (botEdge-leftEdge)));
  else if (Fractions_isGreater (p.y, Fractions_one ()))
    c = (clipCode) ((1 << (topEdge-leftEdge)));
  return c;
}


/*
   drawLine - draws line (if visibly on screen after clipping),
              p1, p2, given colour and thickness.
*/

static void drawLine (Points_Point p1, Points_Point p2, colourDesc colour, Fractions_Fract thickness)
{
  Points_Point o;
  Points_Point o1;
  Points_Point o2;

  if (clipLine (p1, p2, &o1, &o2))
    {
      moveTo (o1);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) ".nop ", 5);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "\\D't ", 5);
      writeUnit (thickness);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\h'-", 5);
      writeUnit (thickness);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\m[", 4);
      writeColour (colour);
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "]\\D'l ", 6);
      o = Points_subPoint (o2, o1);
      writeUnit (relScaleX (o.x));
      TextIO_WriteString ((IOChan_ChanId) file, (char *) " ", 1);
      writeUnit (relScaleY (o.y));
      TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\m[] ", 6);
      TextIO_WriteLn ((IOChan_ChanId) file);
    }
}


/*
   clipLine - clips line: p1, p2.  It returns TRUE if any part of
              line p1, and, p2 can be placed on the screen.
              It then assigns the values o1, o2 to these coordinates.
              If FALSE is returned then o1, o2 are unassigned.
*/

static unsigned int clipLine (Points_Point p1, Points_Point p2, Points_Point *o1, Points_Point *o2)
{
  Fractions_Fract x;
  Fractions_Fract y;
  clipCode c;
  clipCode c1;
  clipCode c2;

  p1 = Points_dupPoint (p1);
  p2 = Points_dupPoint (p2);
  c1 = clipped (p1);
  c2 = clipped (p2);
  for (;;)
  {
    if ((c1&c2) != (clipCode) 0)
      return FALSE;
    else if ((c1|c2) == (clipCode) 0)
      {
        (*o1) = p1;
        (*o2) = p2;
        return TRUE;
      }
    c = c1;
    if (c == (clipCode) 0)
      c = c2;
    if ((((1 << (leftEdge-leftEdge)) & (c)) != 0))
      {
        y = Fractions_mult (Fractions_add (p1.y, Fractions_sub (p2.y, p1.y)), Fractions_div (Fractions_negate (p1.x), Fractions_sub (p2.x, p1.x)));
        x = Fractions_zero ();
      }
    else if ((((1 << (rightEdge-leftEdge)) & (c)) != 0))
      {
        y = Fractions_mult (Fractions_add (p1.y, Fractions_sub (p2.y, p1.y)), Fractions_div (Fractions_sub (Fractions_one (), p1.x), Fractions_sub (p2.x, p1.x)));
        x = Fractions_one ();
      }
    else if ((((1 << (botEdge-leftEdge)) & (c)) != 0))
      {
        x = Fractions_mult (Fractions_add (p1.x, Fractions_sub (p2.x, p1.x)), Fractions_div (Fractions_negate (p1.y), Fractions_sub (p2.y, p1.y)));
        y = Fractions_zero ();
      }
    else if ((((1 << (topEdge-leftEdge)) & (c)) != 0))
      {
        x = Fractions_mult (Fractions_add (p1.x, Fractions_sub (p2.x, p1.x)), Fractions_div (Fractions_sub (Fractions_one (), p1.y), Fractions_sub (p2.y, p1.y)));
        y = Fractions_one ();
      }
    if (c == c1)
      {
        p1.x = x;
        p1.y = y;
        c1 = clipped (Points_initPoint (x, y));
      }
    else
      {
        p2.x = x;
        p2.y = y;
        c2 = clipped (Points_initPoint (x, y));
      }
  }
  ReturnException ("..//deviceGroff.def", 1, 15);
}

static void stop (void)
{
}


/*
   drawPolygon -
*/

static void drawPolygon (glyphDesc g)
{
  unsigned int first;
  unsigned int i;
  Points_Point p;
  Points_Point q;
  Points_Point o1;
  Points_Point o2;

  if (g->gPolygon.noPoints == 2)
    drawLine ((Points_Point) g->gPolygon.pArray.array[0], (Points_Point) g->gPolygon.pArray.array[1], g->gPolygon.colour, g->gPolygon.thickness);
  else
    {
      first = TRUE;
      p = Points_dupPoint ((Points_Point) g->gPolygon.pArray.array[0]);
      for (i=1; i<=g->gPolygon.noPoints-1; i++)
        if (clipLine (p, (Points_Point) g->gPolygon.pArray.array[i], &o1, &o2))
          {
            if (first)
              {
                moveTo (p);
                TextIO_WriteString ((IOChan_ChanId) file, (char *) ".nop ", 5);
                if (g->gPolygon.filled)
                  {
                    TextIO_WriteString ((IOChan_ChanId) file, (char *) "\\M[", 3);
                    writeColour (g->gPolygon.colour);
                    TextIO_WriteString ((IOChan_ChanId) file, (char *) "]\\D'P ", 6);
                  }
                else
                  {
                    TextIO_WriteString ((IOChan_ChanId) file, (char *) "\\D't ", 5);
                    writeUnit (g->gPolygon.thickness);
                    TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\h'-", 5);
                    writeUnit (g->gPolygon.thickness);
                    TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\m[", 4);
                    writeColour (g->gPolygon.colour);
                    TextIO_WriteString ((IOChan_ChanId) file, (char *) "]\\D'p ", 6);
                  }
                first = FALSE;
              }
            p = Points_subPoint (o2, o1);
            writeUnit (relScaleX (p.x));
            TextIO_WriteString ((IOChan_ChanId) file, (char *) " ", 1);
            writeUnit (relScaleY (p.y));
            TextIO_WriteString ((IOChan_ChanId) file, (char *) " ", 1);
            p = Points_unRootPoint (p);
            p = Points_dupPoint (o2);
          }
      if (! first)
        {
          if (g->gPolygon.filled)
            TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\M[]", 5);
          else
            TextIO_WriteString ((IOChan_ChanId) file, (char *) "'\\m[]", 5);
          TextIO_WriteLn ((IOChan_ChanId) file);
        }
      p = Points_unRootPoint (p);
    }
}


/*
   produceAVI - generate an AVI file from the sequence of png images.
*/

static void produceAVI (unsigned int fps, unsigned int width, unsigned int height)
{
  DynamicStrings_String s;

  if (Exec)
    {
      s = FormatStrings_Sprintf3 (DynamicStrings_InitString ((char *) "mencoder \"mf://f*.png\" -mf w=%d:h=%d:fps=%d:type=png -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o movie.avi", 108), (unsigned char *) &width, (sizeof (width)-1), (unsigned char *) &height, (sizeof (height)-1), (unsigned char *) &fps, (sizeof (fps)-1));
      debugSystem (s);
      s = DynamicStrings_KillString (s);
    }
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
   configDevice - configure the output device to have outMax resolution and whether
                  it should produce a sequence of individual troff files which
                  can be combined to make a mpeg movie.  Or alternatively whether
                  each frame should be dynamically rendered into a postscript
                  file displayed by 'gv'.
*/

void deviceGroff_configDevice (Points_Point inMax, Points_Point outMax, unsigned int fps, unsigned int separateFiles, unsigned int mpeg, unsigned int ps, unsigned int gv)
{
  config->inMax = Points_dupPoint (inMax);
  config->outMax = Points_dupPoint (outMax);
  config->fps = fps;
  config->mpeg = mpeg;
  config->ps = ps;
  config->evince = gv;
  config->separateFiles = separateFiles;
  config->same = (Fractions_areEqual (inMax.x, outMax.x)) && (Fractions_areEqual (inMax.y, outMax.y));
}


/*
   white - returns the colour, white.
*/

unsigned int deviceGroff_white (void)
{
  return cWhite;
}


/*
   black - returns the colour, black.
*/

unsigned int deviceGroff_black (void)
{
  return cBlack;
}


/*
   red - returns the colour, red.
*/

unsigned int deviceGroff_red (void)
{
  return cRed;
}


/*
   green - returns the colour, green.
*/

unsigned int deviceGroff_green (void)
{
  return cGreen;
}


/*
   blue - returns the colour, blue.
*/

unsigned int deviceGroff_blue (void)
{
  return cBlue;
}


/*
   yellow - returns the colour, yellow.
*/

unsigned int deviceGroff_yellow (void)
{
  return cYellow;
}


/*
   purple - returns the colour, purple.
*/

unsigned int deviceGroff_purple (void)
{
  return cPurple;
}


/*
   glyphLine - draw a line between:  start and end of, thick, thickness and colour, c.
*/

void deviceGroff_glyphLine (Points_Point start, Points_Point end, Fractions_Fract thick, deviceGroff_Colour c)
{
  typedef struct _T9_a _T9;

  struct _T9_a { Points_Point array[1+1]; };
  _T9 p;

  p.array[0] = start;
  p.array[1] = end;
  deviceGroff_glyphPolygon (2, (Points_Point *) &p.array[0], 1, FALSE, thick, c);
}


/*
   glyphPolygon - draw a polygon from pos, with n points.
                  If fill then it is filled with colour, c, else it is drawn with
                  thickness in outline using colour, c.
                  Note that this procedure takes copies of all fractions and points.
*/

void deviceGroff_glyphPolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, deviceGroff_Colour c)
{
  unsigned int i;
  glyphDesc g;
  Points_Point p[_p_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (p, p_, (_p_high+1) * sizeof (Points_Point));

  g = newGlyph ();
  g->type = polygon;
  g->gPolygon.colour = Indexing_GetIndice (cArray, (unsigned int) c);
  g->gPolygon.filled = fill;
  g->gPolygon.thickness = Fractions_dup (thick);
  g->gPolygon.noPoints = n;
  if (n > maxPoints)
    M2RTS_HALT (0);
  for (i=0; i<=n-1; i++)
    g->gPolygon.pArray.array[i] = Points_dupPoint ((Points_Point) p[i]);
  addToEnd (g);
}


/*
   glyphCircle - draw a circle at point, pos.  If fill then it is filled by colour, c,
                 otherwise it is drawn in outline with a thickness, thick, in colour, c.
                 Note that this procedure takes copies of all fractions and points.
*/

void deviceGroff_glyphCircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, deviceGroff_Colour c)
{
  glyphDesc g;

  g = newGlyph ();
  g->type = circle;
  g->gCircle.colour = Indexing_GetIndice (cArray, (unsigned int) c);
  g->gCircle.center = Points_dupPoint (pos);
  g->gCircle.filled = fill;
  g->gCircle.thickness = Fractions_dup (thick);
  g->gCircle.radius = Fractions_dup (rad);
  addToEnd (g);
}


/*
   flipBuffer - renders the current buffer and then sets up a new buffer to be
                populated by new glyphs.
*/

void deviceGroff_flipBuffer (void)
{
  if (! (empty ()))
    {
      newFrame ();
      flushGlyphs ();
      SeqFile_Close (&file);
      delay_nextFrameTime (config->fps);
      firstFrame = FALSE;
      if (config->mpeg)
        generatePNG ();
      if (config->ps)
        generatePS ();
    }
}


/*
   defineColour - defines a colour by: r, g, b.  The fracts
                  are given to the colour and a colour index
                  is returned.  Colours live for ever and are
                  never freed.  The values, r, g, b, are dup'ed
                  and root'ed.
*/

unsigned int deviceGroff_defineColour (Fractions_Fract r, Fractions_Fract g, Fractions_Fract b)
{
  colourDesc c;

  Storage_ALLOCATE ((void **) &c, sizeof (_T1));
  cNum += 1;
  c->name = makeTemporaryName ((char *) "colour", 6);
  c->r = Fractions_root (Fractions_dup (r));
  c->g = Fractions_root (Fractions_dup (g));
  c->b = Fractions_root (Fractions_dup (b));
  c->used = FALSE;
  Indexing_PutIndice (cArray, cNum, (void *) c);
  return cNum;
}


/*
   Init - initialise this module.
*/

void deviceGroff_Init (void)
{
  GC_entity e;

  frameNo = 0;
  filename = NULL;
  cNum = 0;
  cArray = Indexing_InitIndex (1);
  evinceRunning = FALSE;
  gHead = NULL;
  gFree = NULL;
  cBlack = deviceGroff_defineColour (Fractions_zero (), Fractions_zero (), Fractions_zero ());
  cWhite = deviceGroff_defineColour (Fractions_one (), Fractions_one (), Fractions_one ());
  cRed = deviceGroff_defineColour (Fractions_initFract (0, 65, 100), Fractions_initFract (0, 1, 10), Fractions_initFract (0, 2, 10));
  cGreen = deviceGroff_defineColour (Fractions_initFract (0, 1, 10), Fractions_initFract (0, 4, 10), Fractions_initFract (0, 2, 10));
  cBlue = deviceGroff_defineColour (Fractions_initFract (0, 1, 10), Fractions_initFract (0, 2, 10), Fractions_initFract (0, 6, 10));
  cYellow = deviceGroff_defineColour (Fractions_initFract (1, 0, 0), Fractions_initFract (0, 66, 100), Fractions_initFract (0, 7, 100));
  cPurple = deviceGroff_defineColour (Fractions_initFract (0, 79, 255), Fractions_initFract (0, 47, 255), Fractions_initFract (0, 70, 255));
  configHeap = GC_initGarbage ((GC_walkP) {(GC_walkP_t) markConfig}, (unsigned int) sizeof ((*config)), DynamicStrings_InitString ((char *) "config", 6));
  GC_rootAllocate (configHeap, &e, (void **) &config);
  config->centity = e;
  firstFrame = TRUE;
  deviceGroff_configDevice (Points_initPoint (Fractions_one (), Fractions_one ()), Points_initPoint (Fractions_cardinal (Width), Fractions_cardinal (Height)), 1, FALSE, FALSE, FALSE, TRUE);
}

void _M2_deviceGroff_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_deviceGroff_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
