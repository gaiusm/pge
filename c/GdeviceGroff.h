/* automatically created by mc from ../git-pge/m2/deviceGroff.def.  */


#if !defined (_deviceGroff_H)
#   define _deviceGroff_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GPoints.h"
#   include "GFractions.h"

#   if defined (_deviceGroff_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef unsigned int deviceGroff_Colour;


/*
   configDevice - configure the output device to have outMax resolution and whether
                  it should produce a sequence of individual troff files which
                  can be combined to make a mpeg movie.  Or alternatively whether
                  each frame should be dynamically rendered into a postscript
                  file displayed by 'gv'.
*/

EXTERN void deviceGroff_configDevice (Points_Point inMax, Points_Point outMax, unsigned int fps, unsigned int separateFiles, unsigned int mpeg, unsigned int ps, unsigned int gv);

/*
   white - returns the colour, white.
*/

EXTERN unsigned int deviceGroff_white (void);

/*
   black - returns the colour, black.
*/

EXTERN unsigned int deviceGroff_black (void);

/*
   red - returns the colour, red.
*/

EXTERN unsigned int deviceGroff_red (void);

/*
   green - returns the colour, green.
*/

EXTERN unsigned int deviceGroff_green (void);

/*
   blue - returns the colour, blue.
*/

EXTERN unsigned int deviceGroff_blue (void);

/*
   yellow - returns the colour, yellow.
*/

EXTERN unsigned int deviceGroff_yellow (void);

/*
   purple - returns the colour, purple.
*/

EXTERN unsigned int deviceGroff_purple (void);

/*
   glyphLine - draw a line between:  start and end of, thick, thickness and colour, c.
*/

EXTERN void deviceGroff_glyphLine (Points_Point start, Points_Point end, Fractions_Fract thick, deviceGroff_Colour c);

/*
   glyphPolygon - draw a polygon given n absolute points.
                  If fill then it is filled with colour, c, else it is drawn with
                  thickness in outline using colour, c.
*/

EXTERN void deviceGroff_glyphPolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, deviceGroff_Colour c);

/*
   glyphCircle - draw a circle at point, pos.  If fill then it is filled by colour, c,
                 otherwise it is drawn in outline with a thickness, thick, in colour, c.
*/

EXTERN void deviceGroff_glyphCircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, deviceGroff_Colour c);

/*
   flipBuffer - renders the current buffer and then sets up a new buffer to be
                populated by new glyphs.
*/

EXTERN void deviceGroff_flipBuffer (void);

/*
   defineColour - defines a colour by: r, g, b.  The fracts
                  are given to the colour and a colour index
                  is returned.  Colours live for ever and are
                  never freed.
*/

EXTERN unsigned int deviceGroff_defineColour (Fractions_Fract r, Fractions_Fract g, Fractions_Fract b);

/*
   Init - initialise this module.
*/

EXTERN void deviceGroff_Init (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
