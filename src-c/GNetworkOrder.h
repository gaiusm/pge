/* automatically created by mc from ../NetworkOrder.def.  */


#if !defined (_NetworkOrder_H)
#   define _NetworkOrder_H

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
#   include "Gcoord.h"
#   include "GIOChan.h"

#   if defined (_NetworkOrder_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   writeReal - 
*/

EXTERN void NetworkOrder_writeReal (IOChan_ChanId file, double r);

/*
   writeCard - 
*/

EXTERN void NetworkOrder_writeCard (IOChan_ChanId file, unsigned int c);

/*
   writeFract - 
*/

EXTERN void NetworkOrder_writeFract (IOChan_ChanId file, Fractions_Fract f);

/*
   writePoint - 
*/

EXTERN void NetworkOrder_writePoint (IOChan_ChanId file, Points_Point p);

/*
   writeCoord - 
*/

EXTERN void NetworkOrder_writeCoord (IOChan_ChanId file, coord_Coord c);

/*
   writeLongCard - 
*/

EXTERN void NetworkOrder_writeLongCard (IOChan_ChanId file, long unsigned int l);

/*
   writeShort - 
*/

EXTERN void NetworkOrder_writeShort (IOChan_ChanId file, short unsigned int s);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
