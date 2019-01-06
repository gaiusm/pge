/* Gmcrts.c implements case and return exceptions.

Copyright (C) 2016-2018 Free Software Foundation, Inc.
Contributed by Gaius Mulley <gaius@glam.ac.uk>.

This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GNU Modula-2 is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Modula-2; see the file COPYING.  If not, write to the
Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA.  */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void
CaseException (const char *s, unsigned int high, unsigned int lineno)
{
  fprintf (stderr, "%s:%d:case statement has no matching selection\n", s,
           lineno);
  _exit (1);
}

void
ReturnException (const char *s, unsigned int high, unsigned int lineno)
{
  fprintf (stderr, "%s:%d:procedure function is about to finish and no return "
                   "statement has been executed\n",
           s, lineno);
  _exit (1);
}

void throw (int n)
{
  fprintf (stderr, "throw called (%d)\n", n);
  _exit (1);
}
