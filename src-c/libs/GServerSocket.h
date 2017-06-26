/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/ServerSocket.def.  */


#if !defined (_ServerSocket_H)
#   define _ServerSocket_H

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

#   if defined (_ServerSocket_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   OpenSocketBindListen - opens a TCP server socket.  The socket
                          is bound to, port, and will allow, listen,
                          pending connections.  The result of these
                          combined operations is returned in, res.
*/

EXTERN void ServerSocket_OpenSocketBindListen (IOChan_ChanId *socketid, unsigned int port, unsigned int listen, ChanConsts_OpenResults *res);

/*
   OpenAccept - attempts to open a new channel whose
                input/output capability is determined by,
                flags.  The result of this attempt is returned
                in res.
*/

EXTERN void ServerSocket_OpenAccept (IOChan_ChanId *cid, IOChan_ChanId socketid, ChanConsts_FlagSet flags, ChanConsts_OpenResults *res);

/*
   Close - if the channel identified by cid was not opened as
           a server socket stream, the exception wrongDevice is
           raised; otherwise closes the channel, and assigns
           the value identifying the invalid channel to cid.
*/

EXTERN void ServerSocket_Close (IOChan_ChanId *cid);

/*
   IsSocket - tests if the channel identified by cid is open as
              a server socket stream.
*/

EXTERN unsigned int ServerSocket_IsSocket (IOChan_ChanId cid);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
