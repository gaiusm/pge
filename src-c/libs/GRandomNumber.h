/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RandomNumber.def.  */


#if !defined (_RandomNumber_H)
#   define _RandomNumber_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_RandomNumber_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   Randomize - initialize the random number generator with a seed
               based on the microseconds.
*/

EXTERN void RandomNumber_Randomize (void);

/*
   RandomInit - initialize the random number generator with value, seed.
*/

EXTERN void RandomNumber_RandomInit (unsigned int seed);

/*
   RandomBytes - fills in an array with random values.
*/

EXTERN void RandomNumber_RandomBytes (unsigned char *a, unsigned int _a_high);

/*
   RandomInt - return an INTEGER in the range [low .. high].
*/

EXTERN int RandomNumber_RandomInt (int low, int high);

/*
   RandomShortInt - return an SHORTINT in the range [low..high].
*/

EXTERN short int RandomNumber_RandomShortInt (short int low, short int high);

/*
   RandomLongInt - return an LONGINT in the range [low..high].
*/

EXTERN long int RandomNumber_RandomLongInt (long int low, long int high);

/*
   RandomShortCard - return a SHORTCARD in the range [low..high].
*/

EXTERN unsigned int RandomNumber_RandomShortCard (unsigned int low, unsigned int high);

/*
   RandomCard - return a CARDINAL in the range [low..high].
*/

EXTERN unsigned int RandomNumber_RandomCard (unsigned int low, unsigned int high);

/*
   RandomLongCard - return an LONGCARD in the range [low..high].
*/

EXTERN long unsigned int RandomNumber_RandomLongCard (long unsigned int low, long unsigned int high);

/*
   RandomReal - return a REAL number in the range 0.0..1.0
*/

EXTERN double RandomNumber_RandomReal (void);

/*
   RandomShortReal - return a SHORTREAL number in the range 0.0..1.0
*/

EXTERN float RandomNumber_RandomShortReal (void);

/*
   RandomLongReal - return a LONGREAL number in the range 0.0..1.0
*/

EXTERN long double RandomNumber_RandomLongReal (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
