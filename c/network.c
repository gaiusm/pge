

#define _network_C
#include "Gnetwork.h"
#include <netinet/in.h>


short unsigned int network_htons (short unsigned int s)
{
  return htons (s);
}

unsigned int network_htonl (unsigned int s)
{
  return htonl (s);
}
