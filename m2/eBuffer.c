/*
 *  eBuffer - wrap the event buffer contents into a binary string.
 */

extern void twoDsim_getEventBuffer (void **start, int *length, int *used);


void get_ebuf (void **start, unsigned int *used)
{
  int length;
  twoDsim_getEventBuffer (start, &length, used);
}
