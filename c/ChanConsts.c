/* This file is part of GNU Modula-2.
Contributed by Gaius Mulley <gaius@glam.ac.uk>.

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
Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _ChanConsts_H
#define _ChanConsts_C


typedef enum {ChanConsts_readFlag, ChanConsts_writeFlag, ChanConsts_oldFlag, ChanConsts_textFlag, ChanConsts_rawFlag, ChanConsts_interactiveFlag, ChanConsts_echoFlag} ChanConsts_ChanFlags;

typedef enum {ChanConsts_opened, ChanConsts_wrongNameFormat, ChanConsts_wrongFlags, ChanConsts_tooManyOpen, ChanConsts_outOfChans, ChanConsts_wrongPermissions, ChanConsts_noRoomOnDevice, ChanConsts_noSuchFile, ChanConsts_fileExists, ChanConsts_wrongFileType, ChanConsts_noTextOperations, ChanConsts_noRawOperations, ChanConsts_noMixedOperations, ChanConsts_alreadyOpen, ChanConsts_otherProblem} ChanConsts_OpenResults;

#   define ChanConsts_read (ChanConsts_FlagSet) ((1 << (ChanConsts_readFlag-ChanConsts_readFlag)))
#   define ChanConsts_write (ChanConsts_FlagSet) ((1 << (ChanConsts_writeFlag-ChanConsts_readFlag)))
#   define ChanConsts_old (ChanConsts_FlagSet) ((1 << (ChanConsts_oldFlag-ChanConsts_readFlag)))
#   define ChanConsts_text (ChanConsts_FlagSet) ((1 << (ChanConsts_textFlag-ChanConsts_readFlag)))
#   define ChanConsts_raw (ChanConsts_FlagSet) ((1 << (ChanConsts_rawFlag-ChanConsts_readFlag)))
#   define ChanConsts_interactive (ChanConsts_FlagSet) ((1 << (ChanConsts_interactiveFlag-ChanConsts_readFlag)))
#   define ChanConsts_echo (ChanConsts_FlagSet) ((1 << (ChanConsts_echoFlag-ChanConsts_readFlag)))
typedef unsigned int ChanConsts_FlagSet;


void _M2_ChanConsts_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_ChanConsts_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
