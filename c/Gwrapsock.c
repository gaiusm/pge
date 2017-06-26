/* Copyright (C) 2017
 *               Free Software Foundation, Inc. */
/* This file is part of GNU Modula-2.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA */

#define HAVE_SYS_TYPES_H
#define HAVE_SYS_SOCKET_H
#define HAVE_UNISTD_H
#define HAVE_SIGNAL_H
#define HAVE_SYS_ERRNO_H
#define HAVE_ERRNO_H
#define HAVE_MALLOC_H
#define HAVE_STRING_H
#define HAVE_STDLIB_H


#if defined(HAVE_SYS_TYPES_H)
#   include <sys/types.h>
#endif

#if defined(HAVE_SYS_SOCKET_H)
#   include <sys/socket.h>
#endif

#include <netinet/in.h>
#include <netdb.h>

#if defined(HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#if defined(HAVE_SIGNAL_H)
#  include <signal.h>
#endif

#if defined(HAVE_SYS_ERRNO_H)
#  include <sys/errno.h>
#endif

#if defined(HAVE_ERRNO_H)
#  include <errno.h>
#endif

#if defined(HAVE_MALLOC_H)
#  include <malloc.h>
#endif

#if defined(HAVE_SIGNAL_H)
#  include <signal.h>
#endif

#if defined(HAVE_STRING_H)
#  include <string.h>
#endif

#if defined(HAVE_STDLIB_H)
#  include <stdlib.h>
#endif

#if !defined(TRUE)
#  define TRUE  (1==1)
#endif
#if !defined(FALSE)
#  define FALSE (1==0)
#endif

#include "GChanConsts.h"

#define MAXHOSTNAME 1024
#define MAXPBBUF    1024


typedef struct {
  char                hostname[MAXHOSTNAME];
  struct hostent     *hp;
  struct sockaddr_in  sa;
  int                 sockFd;
  int                 portNo;
  int                 hasChar;
  char                pbChar[MAXPBBUF];
} clientInfo;

static ChanConsts_OpenResults clientConnect (clientInfo *c);


/*
 *  clientOpen - returns an ISO Modula-2 OpenResult.
 *               It attempts to connect to:  hostname:portNo.
 *               If successful then the data structure, c,
 *               will have its fields initialized.
 */

ChanConsts_OpenResults wrapsock_clientOpen (clientInfo *c, char *hostname,
					    unsigned int length, int portNo)
{
  /* remove SIGPIPE which is raised on the server if the client is killed */
  signal(SIGPIPE, SIG_IGN);

  c->hp = gethostbyname(hostname);
  if (c->hp == NULL)
    return ChanConsts_noSuchFile;

  memset((void *)&c->sa, 0, sizeof(c->sa));
  c->sa.sin_family = AF_INET;
  memcpy((void *)&c->sa.sin_addr, (void *)c->hp->h_addr, c->hp->h_length);
  c->portNo        = portNo;
  c->sa.sin_port   = htons(portNo);
  c->hasChar       = 0;
  /*
   *  Open a TCP socket (an Internet stream socket)
   */

  c->sockFd = socket(c->hp->h_addrtype, SOCK_STREAM, 0);
  return clientConnect(c);
}

/*
 *  clientOpenIP - returns an ISO Modula-2 OpenResult.
 *                 It attempts to connect to:  ipaddress:portNo.
 *                 If successful then the data structure, c,
 *                 will have its fields initialized.
 */

ChanConsts_OpenResults wrapsock_clientOpenIP (clientInfo *c, unsigned int ip, int portNo)
{
  /* remove SIGPIPE which is raised on the server if the client is killed */
  signal(SIGPIPE, SIG_IGN);

  memset((void *)&c->sa, 0, sizeof(c->sa));
  c->sa.sin_family = AF_INET;
  memcpy((void *)&c->sa.sin_addr, (void *)&ip, sizeof(ip));
  c->portNo        = portNo;
  c->sa.sin_port   = htons(portNo);

  /*
   * Open a TCP socket (an Internet stream socket)
   */

  c->sockFd = socket(PF_INET, SOCK_STREAM, 0);
  return clientConnect(c);
}

/*
 *  clientConnect - returns an ISO Modula-2 OpenResult
 *                  once a connect has been performed.
 *                  If successful the clientInfo will
 *                  include the file descriptor ready
 *                  for read/write operations.
 */

static ChanConsts_OpenResults clientConnect (clientInfo *c)
{
  if (connect(c->sockFd, (struct sockaddr *)&c->sa, sizeof(c->sa)) < 0)
    return ChanConsts_noSuchFile;

  return ChanConsts_opened;
}

/*
 *  getClientPortNo - returns the portNo from structure, c.
 */

int wrapsock_getClientPortNo (clientInfo *c)
{
  return c->portNo;
}

/*
 *  getClientHostname - fills in the hostname of the server
 *                      the to which the client is connecting.
 */

void wrapsock_getClientHostname (clientInfo *c,
				 char *hostname, unsigned int high)
{
  strncpy(hostname, c->hostname, high+1);
}

/*
 *  getClientSocketFd - returns the sockFd from structure, c.
 */

int wrapsock_getClientSocketFd (clientInfo *c)
{
  return c->sockFd;
}

/*
 *  getClientIP - returns the sockFd from structure, s.
 */

unsigned int wrapsock_getClientIP (clientInfo *c)
{
#if 0
  printf("client ip = %s\n", inet_ntoa (c->sa.sin_addr.s_addr));
#endif
  return c->sa.sin_addr.s_addr;
}

/*
 *  getPushBackChar - returns TRUE if a pushed back character
 *                    is available.
 */

unsigned int wrapsock_getPushBackChar (clientInfo *c, char *ch)
{
  if (c->hasChar > 0) {
    c->hasChar--;
    *ch = c->pbChar[c->hasChar];
    return TRUE;
  }
  return FALSE;
}

/*
 *  setPushBackChar - returns TRUE if it is able to push back a
 *                    character.
 */

unsigned int wrapsock_setPushBackChar (clientInfo *c, char ch)
{
  if (c->hasChar == MAXPBBUF)
    return FALSE;
  c->pbChar[c->hasChar] = ch;
  c->hasChar++;
  return TRUE;
}

/*
 *  getSizeOfClientInfo - returns the sizeof (opaque data type).
 */

unsigned int wrapsock_getSizeOfClientInfo (void)
{
  return sizeof (clientInfo);
}

/*
 *  GNU Modula-2 link fodder.
 */

void _M2_wrapsock_init (void)
{
}

void _M2_wrapsock_finish (void)
{
}
