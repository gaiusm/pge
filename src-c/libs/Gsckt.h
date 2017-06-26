/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/sckt.def.  */


#if !defined (_sckt_H)
#   define _sckt_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_sckt_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef void *sckt_tcpServerState;

typedef void *sckt_tcpClientState;


/*
   tcpServerEstablish - returns a tcpState containing the relevant
                        information about a socket declared to receive
                        tcp connections.
*/

EXTERN sckt_tcpServerState sckt_tcpServerEstablish (void);

/*
   tcpServerEstablishPort - returns a tcpState containing the relevant
                            information about a socket declared to recieve
                            tcp connections. This method attempts to use
                            the port specified by the parameter.
*/

EXTERN sckt_tcpServerState sckt_tcpServerEstablishPort (unsigned int port);

/*
   tcpServerAccept - returns a file descriptor once a client has connected and
                     been accepted.
*/

EXTERN int sckt_tcpServerAccept (sckt_tcpServerState s);

/*
   tcpServerPortNo - returns the portNo from structure, s.
*/

EXTERN unsigned int sckt_tcpServerPortNo (sckt_tcpServerState s);
EXTERN int sckt_tcpServerSocketFd (sckt_tcpServerState s);

/*
   getLocalIP - returns the IP address of this machine.
*/

EXTERN unsigned int sckt_getLocalIP (sckt_tcpServerState s);

/*
   tcpServerIP - returns the IP address from structure, s.
*/

EXTERN unsigned int sckt_tcpServerIP (sckt_tcpServerState s);

/*
   tcpServerClientIP - returns the IP address of the client who
                       has connected to server, s.
*/

EXTERN unsigned int sckt_tcpServerClientIP (sckt_tcpServerState s);

/*
   tcpServerClientPortNo - returns the port number of the client who
                           has connected to server, s.
*/

EXTERN unsigned int sckt_tcpServerClientPortNo (sckt_tcpServerState s);

/*
   tcpClientSocket - returns a file descriptor (socket) which has
                     connected to, serverName:portNo.
*/

EXTERN sckt_tcpClientState sckt_tcpClientSocket (void * serverName, unsigned int portNo);

/*
   tcpClientSocketIP - returns a file descriptor (socket) which has
                       connected to, ip:portNo.
*/

EXTERN sckt_tcpClientState sckt_tcpClientSocketIP (unsigned int ip, unsigned int portNo);

/*
   tcpClientConnect - returns the file descriptor associated with, s,
                      once a connect has been performed.
*/

EXTERN int sckt_tcpClientConnect (sckt_tcpClientState s);

/*
   tcpClientPortNo - returns the portNo from structure, s.
*/

EXTERN int sckt_tcpClientPortNo (sckt_tcpClientState s);

/*
   tcpClientSocketFd - returns the sockFd from structure, s.
*/

EXTERN int sckt_tcpClientSocketFd (sckt_tcpClientState s);

/*
   tcpClientIP - returns the IP address from structure, s.
*/

EXTERN unsigned int sckt_tcpClientIP (sckt_tcpClientState s);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
