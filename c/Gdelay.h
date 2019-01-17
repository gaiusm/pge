/* automatically created by mc from ../git-pge/m2/delay.def.  */


#if !defined (_delay_H)
#   define _delay_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_delay_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   nextFrameTime - calculates the time of the next frame, given the frames
                   per second.  This should be called once for every frame.
*/

EXTERN void delay_nextFrameTime (unsigned int fps);

/*
   wait - waits until 
*/

EXTERN void delay_wait (void);

/*
   getActualFPS - return the actual frames per second.
*/

EXTERN unsigned int delay_getActualFPS (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
