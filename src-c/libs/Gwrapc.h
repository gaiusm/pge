/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/wrapc.def.  */


#if !defined (_wrapc_H)
#   define _wrapc_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_wrapc_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   strtime - returns the C string for the equivalent C asctime
             function.
*/

EXTERN void * wrapc_strtime (void);

/*
   filesize - assigns the size of a file, f, into low, high and
              returns zero if successful.
*/

EXTERN int wrapc_filesize (int f, unsigned int *low, unsigned int *high);

/*
   filemtime - returns the mtime of a file, f.
*/

EXTERN int wrapc_filemtime (int f);

/*
   getrand - returns a random number between 0..n-1
*/

EXTERN int wrapc_getrand (int n);

/*
   getusername - returns a C string describing the current user.
*/

EXTERN void * wrapc_getusername (void);

/*
   getnameuidgid - fills in the, uid, and, gid, which represents
                   user, name.
*/

EXTERN void wrapc_getnameuidgid (void * name, int *uid, int *gid);
EXTERN int wrapc_signbit (double r);
EXTERN int wrapc_signbitf (float s);
EXTERN int wrapc_signbitl (long double l);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
