#include <stdio.h>

#define DEBUGGING

/*
 *  buffers - wrap the event buffer contents into a binary string.
 */

extern void twoDsim_getEventBuffer (void **start, int *length, int *used);
extern void deviceIf_getFrameBuffer (void **start, int *length, int *used);
extern void deviceIf_getColourBuffer (void **start, int *length, int *used);

void get_cbuf (void **start, unsigned int *used)
{
  int length;
#if !defined (DEBUGGING)
  printf ("calling deviceIf_getColourBuffer\n");
#endif
  deviceIf_getColourBuffer (start, &length, used);
}

void get_ebuf (void **start, unsigned int *used)
{
  int length;

#if !defined (DEBUGGING)
  printf ("calling getEventBuffer\n");
#endif
  twoDsim_getEventBuffer (start, &length, used);
}


void get_fbuf (void **start, unsigned int *used)
{
  int length;
#if !defined (DEBUGGING)
  printf ("calling deviceIf_getFrameBuffer\n");
#endif
  deviceIf_getFrameBuffer (start, &length, used);
}
