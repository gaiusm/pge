/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/RTdata.def.  */


#if !defined (_RTdata_H)
#   define _RTdata_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"
#   include "GIOLink.h"

#   if defined (_RTdata_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (RTdata_ModuleId_D)
#  define RTdata_ModuleId_D
   typedef void *RTdata_ModuleId;
#endif

typedef struct RTdata_FreeProcedure_p RTdata_FreeProcedure;

typedef void (*RTdata_FreeProcedure_t) (void *);
struct RTdata_FreeProcedure_p { RTdata_FreeProcedure_t proc; };


/*
   MakeModuleId - creates a unique module Id.
*/

EXTERN void RTdata_MakeModuleId (RTdata_ModuleId *m);

/*
   InitData - adds, datum, to the device, d.  The datum
              is associated with ModuleID, m.
*/

EXTERN void RTdata_InitData (IOLink_DeviceTablePtr d, RTdata_ModuleId m, void * datum, RTdata_FreeProcedure f);

/*
   GetData - returns the datum assocated with ModuleId, m.
*/

EXTERN void * RTdata_GetData (IOLink_DeviceTablePtr d, RTdata_ModuleId m);

/*
   KillData - destroys the datum associated with ModuleId, m,
              in device, d.  It invokes the free procedure
              given during InitData.
*/

EXTERN void RTdata_KillData (IOLink_DeviceTablePtr d, RTdata_ModuleId m);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
