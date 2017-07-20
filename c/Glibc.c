#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int libc_read (int fd, void *a, int nbytes)
{
  return read (fd, a, nbytes);
}

int libc_write (int fd, void *a, int nbytes)
{
  return write (fd, a, nbytes);
}

int libc_close (int fd)
{
  return close (fd);
}

int libc_exit (int code)
{
  exit (code);
}

int libc_perror (char *s)
{
  perror (s);
}

int libc_abort ()
{
  abort ();
}

int libc_strlen (char *s)
{
  return strlen (s);
}

int libc_printf (char *_format, unsigned int _format_high, ...)
{
  va_list arg;
  int done;
  char format[_format_high+1];
  unsigned int i = 0;
  unsigned int j = 0;
  char *c;

  do {
    c = index (&_format[i], '\\');
    if (c == NULL)
      strcpy (&format[j], &_format[i]);
    else {
      memcpy (&format[j], &_format[i], (c - _format) - i);
      i = c - _format;
      j += c - _format;
      if (_format[i+1] == 'n')
	format[j] = '\n';
      else
	format[j] = _format[i+1];
      j++;
      i += 2;
    }
  } while (c != NULL);

  va_start (arg, _format_high);
  done = vfprintf (stdout, format, arg);
  va_end (arg);

  return done;
}

void *libc_malloc (unsigned int size)
{
  return malloc (size);
}

void libc_free (void *p)
{
  free (p);
}

char *libc_strcpy (char *dest, char *src)
{
  return strcpy (dest, src);
}

char *libc_strncpy (char *dest, char *src, int n)
{
  return strncpy (dest, src, n);
}

int libc_unlink (char *p)
{
  return unlink (p);
}

int libc_system (char *command)
{
  return system (command);
}

void *libc_memcpy (void *dest, void *src, int n)
{
  return memcpy (dest, src, n);
}

char *libc_getenv (char *name)
{
  return getenv (name);
}

int libc_creat (char *p, mode_t mode)
{
  return creat (p, mode);
}

int libc_open (char *p, int flags, mode_t mode)
{
  return open (p, flags, mode);
}

off_t libc_lseek (int fd, off_t offset, int whence)
{
  return lseek (fd, offset, whence);
}

void *libc_realloc (void *ptr, size_t size)
{
  return realloc (ptr, size);
}

void *libc_memset (void *s, int c, size_t n)
{
  return memset (s, c, n);
}

void *libc_memmove (void *dest, void *src, size_t n)
{
  return memmove (dest, src, n);
}

int libc_getpid (void)
{
  return getpid ();
}

unsigned int libc_sleep (unsigned int s)
{
  return sleep (s);
}
