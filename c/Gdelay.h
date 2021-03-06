/* do not edit automatically generated by mc from delay.  */
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


#if !defined (_delay_H)
#   define _delay_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_delay_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   nextFrameTime - calculates the time of the next frame, given the frames
                   per second.  This should be called once for every frame.
*/

EXTERN void delay_nextFrameTime (unsigned int fps);

/*
   wait - waits until 
*/

EXTERN void delay_wait (void);

/*
   getActualFPS - return the actual frames per second.
*/

EXTERN unsigned int delay_getActualFPS (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
