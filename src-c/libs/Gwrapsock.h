/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/wrapsock.def.  */


#if !defined (_wrapsock_H)
#   define _wrapsock_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"
#   include "GChanConsts.h"

#   if defined (_wrapsock_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef void *wrapsock_clientInfo;


/*
   clientOpen - returns an ISO Modula-2 OpenResult.
                It attempts to connect to:  hostname:portNo.
                If successful then the data structure, c,
                will have its fields initialized.
*/

EXTERN ChanConsts_OpenResults wrapsock_clientOpen (wrapsock_clientInfo c, void * hostname, unsigned int length, unsigned int portNo);

/*
   clientOpenIP - returns an ISO Modula-2 OpenResult.
                  It attempts to connect to:  ipaddress:portNo.
                  If successful then the data structure, c,
                  will have its fields initialized.
*/

EXTERN ChanConsts_OpenResults wrapsock_clientOpenIP (wrapsock_clientInfo c, unsigned int ip, unsigned int portNo);

/*
   getClientPortNo - returns the portNo from structure, c.
*/

EXTERN unsigned int wrapsock_getClientPortNo (wrapsock_clientInfo c);

/*
   getClientHostname - fills in the hostname of the server
                       the to which the client is connecting.
*/

EXTERN void wrapsock_getClientHostname (wrapsock_clientInfo c, void * hostname, unsigned int high);

/*
   getClientSocketFd - returns the sockFd from structure, c.
*/

EXTERN int wrapsock_getClientSocketFd (wrapsock_clientInfo c);

/*
   getClientIP - returns the sockFd from structure, s.
*/

EXTERN unsigned int wrapsock_getClientIP (wrapsock_clientInfo c);

/*
   getPushBackChar - returns TRUE if a pushed back character
                     is available.
*/

EXTERN unsigned int wrapsock_getPushBackChar (wrapsock_clientInfo c, char *ch);

/*
   setPushBackChar - returns TRUE if it is able to push back a
                     character.
*/

EXTERN unsigned int wrapsock_setPushBackChar (wrapsock_clientInfo c, char ch);

/*
   getSizeOfClientInfo - returns the sizeof (opaque data type).
*/

EXTERN unsigned int wrapsock_getSizeOfClientInfo (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
