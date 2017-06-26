/* Copyright (C) 2016
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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.  */

int	UnixArgs_ArgC;
char	**UnixArgs_ArgV;

void _M2_UnixArgs_init (int argc, char *argv[])
{
  UnixArgs_ArgC = argc;
  UnixArgs_ArgV = argv;
}

void _M2_UnixArgs_finish (int argc, char *argv[])
{
}
