/* automatically created by mc.  */

#if !defined (_network_H)
#   define _network_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_network_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   htons - returns a network ordered SHORTCARD.
*/

EXTERN short unsigned int network_htons (short unsigned int s);

/*
   htonl - returns a network ordered CARDINAL.
*/

EXTERN unsigned int network_htonl (unsigned int s);

#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
