/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/Environment.def.  */


#if !defined (_Environment_H)
#   define _Environment_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_Environment_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   GetEnvironment - gets the environment variable, Env, and places
      	       	    a copy of its value into string, a.
*/

EXTERN unsigned int Environment_GetEnvironment (char *Env_, unsigned int _Env_high, char *a, unsigned int _a_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
