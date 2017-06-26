/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/errno.def.  */


#if !defined (_errno_H)
#   define _errno_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_errno_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define errno_EINTR 4
#   define errno_ERANGE 34
#   define errno_EAGAIN 11
EXTERN int errno_geterrno (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
