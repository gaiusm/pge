/* automatically created by mc from ../git-pge/m2/gdbif.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#define _gdbif_H
#define _gdbif_C

#   include "Glibc.h"
#   include "GFIO.h"
#   include "GNumberIO.h"

static unsigned int invoked;
static unsigned int mustWait;

/*
   finishSpin - sets boolean mustWait to FALSE.
*/

void gdbif_finishSpin (void);

/*
   sleepSpin - waits for the boolean variable mustWait to become FALSE.
               It sleeps for a second between each test of the variable.
*/

void gdbif_sleepSpin (void);

/*
   connectSpin - breakpoint placeholder.
*/

void gdbif_connectSpin (void);

/*
   gdbinit - create a ".gdbinit" file in the current directory.
*/

static void gdbinit (void);


/*
   gdbinit - create a ".gdbinit" file in the current directory.
*/

static void gdbinit (void)
{
  typedef struct _T1_a _T1;

  struct _T1_a { char array[7+1]; };
  FIO_File file;
  _T1 pidstr;

  file = FIO_OpenToWrite ((char *) ".gdbinit", 8);
  if (FIO_IsNoError (file))
    {
      FIO_WriteString (file, (char *) "attach ", 7);
      NumberIO_IntToStr (libc_getpid (), 0, (char *) &pidstr.array[0], 7);
      FIO_WriteString (file, (char *) &pidstr.array[0], 7);
      FIO_WriteLine (file);
      FIO_WriteString (file, (char *) "set mustWait=0", 14);
      FIO_WriteLine (file);
      FIO_WriteString (file, (char *) "fin", 3);
      FIO_WriteLine (file);
      FIO_Close (file);
    }
}


/*
   finishSpin - sets boolean mustWait to FALSE.
*/

void gdbif_finishSpin (void)
{
  mustWait = FALSE;
}


/*
   sleepSpin - waits for the boolean variable mustWait to become FALSE.
               It sleeps for a second between each test of the variable.
*/

void gdbif_sleepSpin (void)
{
  if (mustWait)
    {
      gdbinit ();
      libc_printf ((char *) "process %d is waiting for you to:\\n", 35, libc_getpid ());
      libc_printf ((char *) "(gdb) attach %d\\n", 17, libc_getpid ());
      libc_printf ((char *) "(gdb) break connectSpin\\n", 25);
      libc_printf ((char *) "(gdb) print finishSpin()\\n", 26);
      do {
        libc_sleep (1);
        libc_printf ((char *) ".", 1);
      } while (! (! mustWait));
      libc_printf ((char *) "ok continuing\\n", 15);
      gdbif_connectSpin ();
    }
}


/*
   connectSpin - breakpoint placeholder.
*/

void gdbif_connectSpin (void)
{
}

void _M2_gdbif_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  mustWait = TRUE;
}

void _M2_gdbif_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
