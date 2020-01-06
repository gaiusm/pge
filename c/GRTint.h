

#if !defined (_RTint_H)
#   define _RTint_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_RTint_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct RTint_DespatchVector_p RTint_DespatchVector;

typedef void (*RTint_DespatchVector_t) (unsigned int, unsigned int, void *);
struct RTint_DespatchVector_p { RTint_DespatchVector_t proc; };


/*
   InitInputVector - returns an interrupt vector which is associated
                     with the file descriptor, fd.
*/

EXTERN unsigned int RTint_InitInputVector (int fd, unsigned int pri);

/*
   InitOutputVector - returns an interrupt vector which is associated
                      with the file descriptor, fd.
*/

EXTERN unsigned int RTint_InitOutputVector (int fd, unsigned int pri);

/*
   InitTimeVector - returns an interrupt vector associated with
                    the relative time.
*/

EXTERN unsigned int RTint_InitTimeVector (unsigned int micro, unsigned int secs, unsigned int pri);

/*
   ReArmTimeVector - reprimes the vector, vec, to deliver an interrupt
                     at the new relative time.
*/

EXTERN void RTint_ReArmTimeVector (unsigned int vec, unsigned int micro, unsigned int secs);

/*
   GetTimeVector - assigns, micro, and, secs, with the remaining
                   time before this interrupt will expire.
                   This value is only updated when a Listen
                   occurs.
*/

EXTERN void RTint_GetTimeVector (unsigned int vec, unsigned int *micro, unsigned int *secs);

/*
   AttachVector - adds the pointer, p, to be associated with the interrupt
                  vector. It returns the previous value attached to this
                  vector.
*/

EXTERN void * RTint_AttachVector (unsigned int vec, void * p);

/*
   IncludeVector - includes, vec, into the despatcher list of
                   possible interrupt causes.
*/

EXTERN void RTint_IncludeVector (unsigned int vec);

/*
   ExcludeVector - excludes, vec, from the despatcher list of
                   possible interrupt causes.
*/

EXTERN void RTint_ExcludeVector (unsigned int vec);

/*
   Listen - will either block indefinitely (until an interrupt)
            or alteratively will test to see whether any interrupts
            are pending.
            If a pending interrupt was found then, call, is called
            and then this procedure returns.
            It only listens for interrupts > pri.
*/

EXTERN void RTint_Listen (unsigned int untilInterrupt, RTint_DespatchVector call, unsigned int pri);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
