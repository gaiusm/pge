/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/Selective.def.  */


#if !defined (_Selective_H)
#   define _Selective_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_Selective_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef void *Selective_SetOfFd;

typedef void *Selective_Timeval;

EXTERN int Selective_Select (unsigned int nooffds, Selective_SetOfFd readfds, Selective_SetOfFd writefds, Selective_SetOfFd exceptfds, Selective_Timeval timeout);
EXTERN Selective_Timeval Selective_InitTime (unsigned int sec, unsigned int usec);
EXTERN Selective_Timeval Selective_KillTime (Selective_Timeval t);
EXTERN void Selective_GetTime (Selective_Timeval t, unsigned int *sec, unsigned int *usec);
EXTERN void Selective_SetTime (Selective_Timeval t, unsigned int sec, unsigned int usec);
EXTERN Selective_SetOfFd Selective_InitSet (void);
EXTERN Selective_SetOfFd Selective_KillSet (Selective_SetOfFd s);
EXTERN void Selective_FdZero (Selective_SetOfFd s);
EXTERN void Selective_FdSet (int fd, Selective_SetOfFd s);
EXTERN void Selective_FdClr (int fd, Selective_SetOfFd s);
EXTERN unsigned int Selective_FdIsSet (int fd, Selective_SetOfFd s);
EXTERN int Selective_MaxFdsPlusOne (int a, int b);
EXTERN void Selective_WriteCharRaw (int fd, char ch);
EXTERN char Selective_ReadCharRaw (int fd);

/*
   GetTimeOfDay - fills in a record, Timeval, filled in with the
                  current system time in seconds and microseconds.
                  It returns zero (see man 3p gettimeofday)
*/

EXTERN int Selective_GetTimeOfDay (Selective_Timeval tv);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
