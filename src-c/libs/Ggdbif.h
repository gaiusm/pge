/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/gdbif.def.  */


#if !defined (_gdbif_H)
#   define _gdbif_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_gdbif_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   finishSpin - sets boolean mustWait to FALSE.
*/

EXTERN void gdbif_finishSpin (void);

/*
   sleepSpin - waits for the boolean variable mustWait to become FALSE.
               It sleeps for a second between each test of the variable.
*/

EXTERN void gdbif_sleepSpin (void);

/*
   connectSpin - breakpoint placeholder.  Its only purpose is to allow users
                 to set a breakpoint.  This procedure is called once
                 sleepSpin is released from its spin (via a call from
                 finishSpin).
*/

EXTERN void gdbif_connectSpin (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
