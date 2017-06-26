/* Copyright (C) 2017
   Free Software Foundation, Inc.  */
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
MA  02110-1301  USA */

int pth_pth_select (int p1, int p2, int p3, int p4, int p5)
{
  return pth_select (p1, p2, p3, p4, p5);
}

int pth_pth_uctx_create (void *p)
{
#if 0
  return pth_uctx_create (p);
#endif
}

int pth_pth_uctx_make (void *p1, void *p2, unsigned int p3,
		       void *p4, void *p5, void *p6, void *p7)
{
#if 0
  return pth_uctx_make (p1, p2, p3, p4, p5, p6, p7);
#endif
}

int pth_pth_uctx_save (void *p1)
{
#if 0
  return pth_uctx_save (p1);
#endif
}

int pth_pth_uctx_switch (void *p1, void *p2)
{
#if 0
  return pth_uctx_switch (p1, p2);
#endif
}

int pth_pth_init (void)
{
  return pth_init ();
}
