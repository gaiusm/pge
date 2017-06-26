/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/SWholeIO.mod.  */

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
  WholeIO_ReadInt ((IOChan_ChanId) StdChans_StdInChan (), int);
}

void SWholeIO_WriteInt (int int_, unsigned int width)
{
  WholeIO_WriteInt ((IOChan_ChanId) StdChans_StdOutChan (), int_, width);
}

void SWholeIO_ReadCard (unsigned int *card)
{
  WholeIO_ReadCard ((IOChan_ChanId) StdChans_StdInChan (), card);
}

void SWholeIO_WriteCard (unsigned int card, unsigned int width)
{
  WholeIO_WriteCard ((IOChan_ChanId) StdChans_StdOutChan (), card, width);
}

void _M2_SWholeIO_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_SWholeIO_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
