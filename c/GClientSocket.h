/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/ClientSocket.def.  */


#if !defined (_ClientSocket_H)
#   define _ClientSocket_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GIOChan.h"
#   include "GChanConsts.h"

#   if defined (_ClientSocket_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   OpenSocket - opens a TCP client connection to host:port.
*/

EXTERN void ClientSocket_OpenSocket (IOChan_ChanId *cid, char *host_, unsigned int _host_high, unsigned int port, ChanConsts_FlagSet f, ChanConsts_OpenResults *res);

/*
   Close - if the channel identified by cid is not open to
           a socket stream, the exception wrongDevice is
           raised; otherwise closes the channel, and assigns
           the value identifying the invalid channel to cid.
*/

EXTERN void ClientSocket_Close (IOChan_ChanId *cid);

/*
   IsSocket - tests if the channel identified by cid is open as
              a client socket stream.
*/

EXTERN unsigned int ClientSocket_IsSocket (IOChan_ChanId cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
