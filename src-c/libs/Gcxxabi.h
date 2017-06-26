/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/cxxabi.def.  */


#if !defined (_cxxabi_H)
#   define _cxxabi_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_cxxabi_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void * cxxabi___cxa_begin_catch (void * a);
EXTERN void cxxabi___cxa_end_catch (void);
EXTERN void cxxabi___cxa_rethrow (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
