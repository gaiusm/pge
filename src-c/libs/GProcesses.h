/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/Processes.def.  */


#if !defined (_Processes_H)
#   define _Processes_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_Processes_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (Processes_ProcessId_D)
#  define Processes_ProcessId_D
   typedef void *Processes_ProcessId;
#endif

typedef void *Processes_Parameter;

typedef PROC Processes_Body;

typedef int Processes_Urgency;

typedef unsigned int Processes_Sources;

typedef enum {Processes_passiveProgram, Processes_processError} Processes_ProcessesExceptions;

EXTERN void Processes_Create (Processes_Body procBody, unsigned int extraSpace, Processes_Urgency procUrg, Processes_Parameter procParams, Processes_ProcessId *procId);
EXTERN void Processes_Start (Processes_Body procBody, unsigned int extraSpace, Processes_Urgency procUrg, Processes_Parameter procParams, Processes_ProcessId *procId);
EXTERN void Processes_StopMe (void);
EXTERN void Processes_SuspendMe (void);
EXTERN void Processes_Activate (Processes_ProcessId procId);
EXTERN void Processes_SuspendMeAndActivate (Processes_ProcessId procId);
EXTERN void Processes_Switch (Processes_ProcessId procId, Processes_Parameter *info);
EXTERN void Processes_Wait (void);
EXTERN void Processes_Attach (Processes_Sources eventSource);
EXTERN void Processes_Detach (Processes_Sources eventSource);
EXTERN unsigned int Processes_IsAttached (Processes_Sources eventSource);
EXTERN Processes_ProcessId Processes_Handler (Processes_Sources eventSource);
EXTERN Processes_ProcessId Processes_Me (void);
EXTERN Processes_Parameter Processes_MyParam (void);
EXTERN Processes_Urgency Processes_UrgencyOf (Processes_ProcessId procId);
EXTERN Processes_ProcessesExceptions Processes_ProcessesException (void);
EXTERN unsigned int Processes_IsProcessesException (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
