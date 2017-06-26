/* automatically created by mc from ../devicePy.def.  */


#if !defined (_devicePy_H)
#   define _devicePy_H

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

#   if defined (_devicePy_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef unsigned int devicePy_Colour;


/*
   configDevice - configure the output device to have outMax resolution and
                  a frame rate.
*/

EXTERN void devicePy_configDevice (Points_Point inMax, Points_Point outMax, unsigned int fps);

/*
   white - returns the colour, white.
*/

EXTERN unsigned int devicePy_white (void);

/*
   black - returns the colour, black.
*/

EXTERN unsigned int devicePy_black (void);

/*
   red - returns the colour, red.
*/

EXTERN unsigned int devicePy_red (void);

/*
   green - returns the colour, green.
*/

EXTERN unsigned int devicePy_green (void);

/*
   blue - returns the colour, blue.
*/

EXTERN unsigned int devicePy_blue (void);

/*
   yellow - returns the colour, yellow.
*/

EXTERN unsigned int devicePy_yellow (void);

/*
   purple - returns the colour, purple.
*/

EXTERN unsigned int devicePy_purple (void);

/*
   glyphLine - draw a line between:  start and end of, thick, thickness and colour, c.
*/

EXTERN void devicePy_glyphLine (Points_Point start, Points_Point end, Fractions_Fract thick, devicePy_Colour c);

/*
   glyphPolygon - draw a polygon given n absolute points.
                  If fill then it is filled with colour, c, else it is drawn with
                  thickness in outline using colour, c.
*/

EXTERN void devicePy_glyphPolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, devicePy_Colour c);

/*
   glyphCircle - draw a circle at point, pos.  If fill then it is filled by colour, c,
                 otherwise it is drawn in outline with a thickness, thick, in colour, c.
*/

EXTERN void devicePy_glyphCircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, devicePy_Colour c);

/*
   flipBuffer - renders the current buffer and then sets up a new buffer to be
                populated by new glyphs.
*/

EXTERN void devicePy_flipBuffer (void);

/*
   defineColour - defines a colour by: r, g, b.  The fracts
                  are given to the colour and a colour index
                  is returned.  Colours live for ever and are
                  never freed.
*/

EXTERN unsigned int devicePy_defineColour (Fractions_Fract r, Fractions_Fract g, Fractions_Fract b);

/*
   Init - initialise this module.
*/

EXTERN void devicePy_Init (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
