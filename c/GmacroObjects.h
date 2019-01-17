/* automatically created by mc from ../git-pge/m2/macroObjects.def.  */


#if !defined (_macroObjects_H)
#   define _macroObjects_H

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
#   include "GdeviceIf.h"

#   if defined (_macroObjects_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (macroObjects_Macro_D)
#  define macroObjects_Macro_D
   typedef void *macroObjects_Macro;
#endif

typedef struct macroObjects_pProc_p macroObjects_pProc;

typedef struct macroObjects_cProc_p macroObjects_cProc;

typedef void (*macroObjects_pProc_t) (unsigned int, Points_Point *, unsigned int, unsigned int, Fractions_Fract, deviceIf_Colour);
struct macroObjects_pProc_p { macroObjects_pProc_t proc; };

typedef void (*macroObjects_cProc_t) (Points_Point, unsigned int, Fractions_Fract, Fractions_Fract, deviceIf_Colour);
struct macroObjects_cProc_p { macroObjects_cProc_t proc; };


/*
   initMacro - creates and returns a macro.
*/

EXTERN macroObjects_Macro macroObjects_initMacro (void);

/*
   moveTo - assign the internal position in macro, m, to, p.
*/

EXTERN macroObjects_Macro macroObjects_moveTo (macroObjects_Macro m, Points_Point p);

/*
   right - move right relatively by, f, units.
*/

EXTERN macroObjects_Macro macroObjects_right (macroObjects_Macro m, Fractions_Fract f);

/*
   left - move left relatively by, f, units.
*/

EXTERN macroObjects_Macro macroObjects_left (macroObjects_Macro m, Fractions_Fract f);

/*
   up - move up relatively by, f, units.
*/

EXTERN macroObjects_Macro macroObjects_up (macroObjects_Macro m, Fractions_Fract f);

/*
   down - move down relatively by, f, units.
*/

EXTERN macroObjects_Macro macroObjects_down (macroObjects_Macro m, Fractions_Fract f);

/*
   rectangle - draw a rectangle at current position which is length, height, units, and is
               filled and has colour, c.
*/

EXTERN macroObjects_Macro macroObjects_rectangle (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Fractions_Fract length, Fractions_Fract height);

/*
   circle - draw a circle at current position of, colour, and radius.
*/

EXTERN macroObjects_Macro macroObjects_circle (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Fractions_Fract rad);

/*
   angledRect - add angled rectangle to macro, m.  The angled rectangle four points are defined
                by the current position, cp, cp+v1, cp+v1+v2, cp+v2.
*/

EXTERN macroObjects_Macro macroObjects_angledRect (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Points_Point v1, Points_Point v2);

/*
   triangle - the triangle is defined by the current position:  cp, cp+v1, cp+v1+v2.
*/

EXTERN macroObjects_Macro macroObjects_triangle (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Points_Point v1, Points_Point v2);

/*
   append - returns a new macro which is the result of appending, b, onto the end of, a.
*/

EXTERN macroObjects_Macro macroObjects_append (macroObjects_Macro a, macroObjects_Macro b);

/*
   rotate - rotate macro, m, about point, p, with angle, r.
            It returns a new macro.
*/

EXTERN macroObjects_Macro macroObjects_rotate (macroObjects_Macro m, Points_Point p, Fractions_Fract r);

/*
   translate - translates macro, m, along, vector.
               It returns a new macro.
*/

EXTERN macroObjects_Macro macroObjects_translate (macroObjects_Macro m, Points_Point vector);

/*
   scale - scale macro, m, in the x and y axis.  A new
           macro is returned.
*/

EXTERN macroObjects_Macro macroObjects_scale (macroObjects_Macro m, Points_Point s);

/*
   dup - duplicates and returns a new macro.
*/

EXTERN macroObjects_Macro macroObjects_dup (macroObjects_Macro m);

/*
   runCallBacks - for each
                           polygon call p 
                           circle call c
                                         in macro, m.
*/

EXTERN void macroObjects_runCallBacks (macroObjects_Macro m, macroObjects_pProc p, macroObjects_cProc c);

/*
   rootMacro - register macro, m, with the roots of the garbage collector.
*/

EXTERN macroObjects_Macro macroObjects_rootMacro (macroObjects_Macro m);

/*
   unRootMacro - unroots macro, m, from the garbage collector.
                 Macro, m, can still be used until the garbage collector is called.
*/

EXTERN macroObjects_Macro macroObjects_unRootMacro (macroObjects_Macro m);

/*
   markMacro - marks macro, m, and marks everything.
*/

EXTERN void macroObjects_markMacro (macroObjects_Macro m);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
