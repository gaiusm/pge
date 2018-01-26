/* automatically created by mc from ../git-pge/m2/testpy.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   include "GdevicePy.h"
#   include "GFractions.h"
#   include "GPoints.h"

typedef struct _T1_a _T1;

struct _T1_a { Points_Point array[3+1]; };
static _T1 p;

void _M2_testpy_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  /* This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GNU Modula-2 is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with gm2; see the file COPYING.  If not, write to the Free Software
Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */
  devicePy_configDevice (Points_initPoint (Fractions_one (), Fractions_one ()), Points_initPoint (Fractions_cardinal (1024), Fractions_cardinal (1024)), 1);
  devicePy_glyphCircle (Points_initPoint (Fractions_half (), Fractions_half ()), TRUE, Fractions_zero (), Fractions_initFract (0, 1, 50), (devicePy_Colour) devicePy_green ());
  p.array[0] = Points_initPoint (Fractions_zero (), Fractions_zero ());
  p.array[1] = Points_initPoint (Fractions_half (), Fractions_zero ());
  p.array[2] = Points_initPoint (Fractions_half (), Fractions_initFract (0, 1, 5));
  p.array[3] = Points_initPoint (Fractions_zero (), Fractions_initFract (0, 1, 5));
  devicePy_glyphPolygon (4, (Points_Point *) &p.array[0], 3, TRUE, Fractions_zero (), (devicePy_Colour) devicePy_red ());
  devicePy_flipBuffer ();
}

void _M2_testpy_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
