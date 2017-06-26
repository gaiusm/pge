/* automatically created by mc from ../delay.mod.  */

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

#define _delay_H
#define _delay_C

#   include "GSelective.h"
#   include "GM2RTS.h"

#   define M 1000000
#   define debugDelay 0
static unsigned int noDelay;
static Selective_Timeval delayT;
static unsigned int sec;
static unsigned int usec;
static unsigned int firstSec;
static unsigned int actualFps;
static unsigned int totalFrames;

/*
   nextFrameTime - calculates the time of the next frame, given the frames
                   per second.  This should be called once for every frame.
*/

void delay_nextFrameTime (unsigned int fps);

/*
   wait - waits until 
*/

void delay_wait (void);

/*
   getActualFPS - return the actual frames per second.
*/

unsigned int delay_getActualFPS (void);

/*
   isEarlier - 
*/

static unsigned int isEarlier (unsigned int s1, unsigned int u1, unsigned int s2, unsigned int u2);


/*
   isEarlier - 
*/

static unsigned int isEarlier (unsigned int s1, unsigned int u1, unsigned int s2, unsigned int u2)
{
  if (s1 < s2)
    return TRUE;
  else if (s1 > s2)
    return FALSE;
  else
    return u1 < u2;
}


/*
   nextFrameTime - calculates the time of the next frame, given the frames
                   per second.  This should be called once for every frame.
*/

void delay_nextFrameTime (unsigned int fps)
{
  unsigned int dt;

  totalFrames += 1;
  if (fps == 0)
    noDelay = TRUE;
  else
    {
      if ((Selective_GetTimeOfDay (delayT)) == 0)
        {}  /* empty.  */
      Selective_GetTime (delayT, &sec, &usec);
      if (firstSec == 0)
        {
          firstSec = sec;
          actualFps = fps;
        }
      else if (firstSec < sec)
        actualFps = totalFrames / (sec-firstSec);
      dt = M / fps;
      usec += dt;
      if (usec > M)
        {
          usec -= M;
          sec += 1;
        }
      sec += debugDelay;
    }
}


/*
   wait - waits until 
*/

void delay_wait (void)
{
  Selective_SetOfFd r;
  Selective_SetOfFd w;
  Selective_SetOfFd e;
  unsigned int u;
  unsigned int s;

  if (! noDelay)
    {
      if ((Selective_GetTimeOfDay (delayT)) == 0)
        {}  /* empty.  */
      Selective_GetTime (delayT, &s, &u);
      if (isEarlier (s, u, sec, usec))
        {
          sec -= s;
          if (usec < u)
            {
              usec = (M+usec)-u;
              if (sec > 0)
                sec -= 1;
              else
                M2RTS_HALT (0);
            }
          else
            usec -= u;
          Selective_SetTime (delayT, sec, usec);
          r = Selective_InitSet ();
          w = Selective_InitSet ();
          e = Selective_InitSet ();
          Selective_FdZero (r);
          if ((Selective_Select (0, r, w, e, delayT)) == 0)
            {}  /* empty.  */
          r = Selective_KillSet (r);
          w = Selective_KillSet (w);
          e = Selective_KillSet (e);
        }
    }
}


/*
   getActualFPS - return the actual frames per second.
*/

unsigned int delay_getActualFPS (void)
{
  return actualFps;
}

void _M2_delay_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  delayT = Selective_InitTime (0, 0);
  firstSec = 0;
  totalFrames = 0;
}

void _M2_delay_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
