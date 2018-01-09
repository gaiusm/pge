/* automatically created by mc from ../git-pge/m2/popWorld.def.  */


#if !defined (_popWorld_H)
#   define _popWorld_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GFractions.h"
#   include "GPoints.h"
#   include "GmacroObjects.h"

#   if defined (_popWorld_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   populate - populate the 2D world with the contents of macro, m.
*/

EXTERN void popWorld_populate (macroObjects_Macro m, unsigned int fixed, unsigned int solid);

/*
   mass - sets the default mass for a movable object.
*/

EXTERN void popWorld_mass (Fractions_Fract m);

/*
   velocity - sets the default velocity for a movable object.
*/

EXTERN void popWorld_velocity (Points_Point v);

/*
   rotate - sets the default angular velocity for a movable object.
*/

EXTERN void popWorld_rotate (Fractions_Fract r);

/*
   init - initialise the 2D world and configure the device to be groff or pygame.
*/

EXTERN void popWorld_init (unsigned int groff);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
