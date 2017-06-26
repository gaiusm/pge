/* automatically created by mc from ../deviceIf.def.  */


#if !defined (_deviceIf_H)
#   define _deviceIf_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"
#   include "GPoints.h"
#   include "GFractions.h"

#   if defined (_deviceIf_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef unsigned int deviceIf_Colour;


/*
   white - returns the colour, white.
*/

EXTERN unsigned int deviceIf_white (void);

/*
   black - returns the colour, black.
*/

EXTERN unsigned int deviceIf_black (void);

/*
   red - returns the colour, red.
*/

EXTERN unsigned int deviceIf_red (void);

/*
   green - returns the colour, green.
*/

EXTERN unsigned int deviceIf_green (void);

/*
   blue - returns the colour, blue.
*/

EXTERN unsigned int deviceIf_blue (void);

/*
   yellow - returns the colour, yellow.
*/

EXTERN unsigned int deviceIf_yellow (void);

/*
   purple - returns the colour, purple.
*/

EXTERN unsigned int deviceIf_purple (void);

/*
   glyphLine - draw a line between:  start and end of, thick, thickness and colour, c.
*/

EXTERN void deviceIf_glyphLine (Points_Point start, Points_Point end, Fractions_Fract thick, deviceIf_Colour c);

/*
   glyphPolygon - draw a polygon given n absolute points.
                  If fill then it is filled with colour, c, else it is drawn with
                  thickness in outline using colour, c.
*/

EXTERN void deviceIf_glyphPolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c);

/*
   glyphCircle - draw a circle at point, pos.  If fill then it is filled by colour, c,
                 otherwise it is drawn in outline with a thickness, thick, in colour, c.
*/

EXTERN void deviceIf_glyphCircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, deviceIf_Colour c);

/*
   flipBuffer - renders the current buffer and then sets up a new buffer to be
                populated by new glyphs.
*/

EXTERN void deviceIf_flipBuffer (void);

/*
   frameNote - emit a note to indicate a new frame has commenced.
*/

EXTERN void deviceIf_frameNote (void);

/*
   emptyCbuffer - empty the colour buffer (this only applies if the module is using
                  the buffer device).
*/

EXTERN void deviceIf_emptyCbuffer (void);

/*
   emptyFbuffer - empty the frame buffer (this only applies if the module is using
                  the buffer device).
*/

EXTERN void deviceIf_emptyFbuffer (void);

/*
   writeTime - writes the delay, t, to the frame buffer (if t > 0.0).
*/

EXTERN void deviceIf_writeTime (double t);

/*
   defineColour - defines a colour by: r, g, b.  The fracts
                  are given to the colour and a colour index
                  is returned.  Colours live for ever and are
                  never freed.
*/

EXTERN unsigned int deviceIf_defineColour (Fractions_Fract r, Fractions_Fract g, Fractions_Fract b);

/*
   useGroff - use the groff device to render frames into png images.
*/

EXTERN void deviceIf_useGroff (void);

/*
   useBuffer - place the objects into a frame buffer.
*/

EXTERN void deviceIf_useBuffer (void);

/*
   useRPC - make rpc's to the pygame display server to render frames.
*/

EXTERN void deviceIf_useRPC (void);

/*
   finish - close the device file.
*/

EXTERN void deviceIf_finish (void);

/*
   configDevice - configure the output device to have outMax resolution.
*/

EXTERN void deviceIf_configDevice (Points_Point inMax, Points_Point outMax, unsigned int fps);

/*
   getFrameBuffer - collects the frame buffer limits in the following parameters.
*/

EXTERN void deviceIf_getFrameBuffer (void * *start, unsigned int *length, unsigned int *used);

/*
   getColourBuffer - collects the colour buffer limits in the following parameters.
*/

EXTERN void deviceIf_getColourBuffer (void * *start, unsigned int *length, unsigned int *used);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
