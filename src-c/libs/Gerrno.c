#include <errno.h>

int errno_geterrno (void)
{
  return errno;
}

void _M2_errno_init (int argc, char *p)
{
}

void _M2_errno_finish (int argc, char *p)
{
}
