/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs-iso/IOConsts.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _IOConsts_H
#define _IOConsts_C


typedef enum {IOConsts_notKnown, IOConsts_allRight, IOConsts_outOfRange, IOConsts_wrongFormat, IOConsts_endOfLine, IOConsts_endOfInput} IOConsts_ReadResults;


void _M2_IOConsts_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_IOConsts_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
