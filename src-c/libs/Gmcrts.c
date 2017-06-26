#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void CaseException (const char *s, unsigned int high, unsigned int lineno)
{
  fprintf (stderr, "%s:%d:case statement has no matching selection\n", s, lineno);
  _exit (1);
}

void ReturnException (const char *s, unsigned int high, unsigned int lineno)
{
  fprintf (stderr, "%s:%d:procedure function is about to finish and no return statement has been executed\n", s, lineno);
  _exit (1);
}

void throw (int n)
{
  fprintf (stderr, "throw called (%d)\n", n);
  _exit (1);
}
