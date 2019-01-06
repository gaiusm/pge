/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/SWholeIO.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _SWholeIO_H
#define _SWholeIO_C

#   include "GStdChans.h"
#   include "GWholeIO.h"

void SWholeIO_ReadInt (int *int_);
void SWholeIO_WriteInt (int int_, unsigned int width);
void SWholeIO_ReadCard (unsigned int *card);
void SWholeIO_WriteCard (unsigned int card, unsigned int width);

void SWholeIO_ReadInt (int *int_)
{
  /* Skips leading spaces, and removes any remaining characters
     from the default input stream that form part of a signed
     whole number.  The value of this number is assigned to int.
     The read result is set to the value allRight, outOfRange,
     wrongFormat, endOfLine, or endOfInput.
  */
  WholeIO_ReadInt ((IOChan_ChanId) StdChans_StdInChan (), int);
}

void SWholeIO_WriteInt (int int_, unsigned int width)
{
  /* Writes the value of int to the default output stream in
     text form, in a field of the given minimum width.  */
  WholeIO_WriteInt ((IOChan_ChanId) StdChans_StdOutChan (), int_, width);
}

void SWholeIO_ReadCard (unsigned int *card)
{
  /* Skips leading spaces, and removes any remaining characters
     from the default input stream that form part of an unsigned
     whole number.  The value of this number is assigned to card.
     The read result is set to the value allRight, outOfRange,
     wrongFormat, endOfLine, or endOfInput.
  */
  WholeIO_ReadCard ((IOChan_ChanId) StdChans_StdInChan (), card);
}

void SWholeIO_WriteCard (unsigned int card, unsigned int width)
{
  /* Writes the value of card to the default output stream in
     text form, in a field of the given minimum width.  */
  WholeIO_WriteCard ((IOChan_ChanId) StdChans_StdOutChan (), card, width);
}

void _M2_SWholeIO_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_SWholeIO_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
