/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/SFIO.def.  */


#if !defined (_SFIO_H)
#   define _SFIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GDynamicStrings.h"
#   include "GFIO.h"

#   if defined (_SFIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   Exists - returns TRUE if a file named, fname exists for reading.
*/

EXTERN unsigned int SFIO_Exists (DynamicStrings_String fname);

/*
   OpenToRead - attempts to open a file, fname, for reading and
                it returns this file.
                The success of this operation can be checked by
                calling IsNoError.
*/

EXTERN FIO_File SFIO_OpenToRead (DynamicStrings_String fname);

/*
   OpenToWrite - attempts to open a file, fname, for write and
                 it returns this file.
                 The success of this operation can be checked by
                 calling IsNoError.
*/

EXTERN FIO_File SFIO_OpenToWrite (DynamicStrings_String fname);

/*
   OpenForRandom - attempts to open a file, fname, for random access
                   read or write and it returns this file.
                   The success of this operation can be checked by
                   calling IsNoError.
                   towrite, determines whether the file should be
                   opened for writing or reading.
                   if towrite is TRUE or whether the previous file should
                   be left alone, allowing this descriptor to seek
                   and modify an existing file.
*/

EXTERN FIO_File SFIO_OpenForRandom (DynamicStrings_String fname, unsigned int towrite, unsigned int newfile);

/*
   WriteS - writes a string, s, to, file. It returns the String, s.
*/

EXTERN DynamicStrings_String SFIO_WriteS (FIO_File file, DynamicStrings_String s);

/*
   ReadS - reads a string, s, from, file. It returns the String, s.
           It stops reading the string at the end of line or end of file.
           It consumes the newline at the end of line but does not place
           this into the returned string.
*/

EXTERN DynamicStrings_String SFIO_ReadS (FIO_File file);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
