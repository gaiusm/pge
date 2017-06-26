
AC_INIT([pge], [2.0])

AC_PREREQ(2.69)

AM_INIT_AUTOMAKE([subdir-objects])

AC_PROG_AWK
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AC_CONFIG_SRCDIR([version.c])
AC_CONFIG_MACRO_DIR([m4])

AS_MKDIR_P(c)
AS_MKDIR_P(m2)
AS_MKDIR_P(python)

LT_INIT
LT_PREREQ([])
AC_SUBST([LIBTOOL_DEPS])

AC_ARG_ENABLE([maintainer],
[  --enable-maintainer    Turn on maintainer],
[case "${enableval}" in
  yes) maintainer=true ;;
    no)  maintainer=false ;;
      *) AC_MSG_ERROR([bad value ${enableval} for --enable-maintainer]) ;;
      esac],[maintainer=false])
      AM_CONDITIONAL([MAINTAINER], [test x$maintainer = xtrue])

AC_ARG_ENABLE([langm2],
[  --enable-langm2    Turn on building the implementation from Modula-2 sources],
[case "${enableval}" in
  yes) langm2=true ;;
    no)  langm2=false ;;
      *) AC_MSG_ERROR([bad value ${enableval} for --enable-langm2]) ;;
      esac],[langm2=false])
      AM_CONDITIONAL([LANGM2], [test x$langm2 = xtrue])

AC_ARG_ENABLE([langc],
[  --enable-langc    Turn on building the implementation from C sources],
[case "${enableval}" in
  yes) langc=true ;;
    no)  langc=false ;;
      *) AC_MSG_ERROR([bad value ${enableval} for --enable-langc]) ;;
      esac],[langc=false])
      AM_CONDITIONAL([LANGC], [test x$langc = xtrue])

AC_MSG_CHECKING([checking to see that you have set a source language])
if test x$langc = xtrue; then
   AC_MSG_RESULT([(C)... yes])
elif test x$langm2 = xtrue; then
   AC_MSG_RESULT([(Modula-2)... yes])
else
   AC_MSG_ERROR([you must specify either --enable-langc or --enable-langm2])
fi

AC_HAVE_LIBRARY(-lpth)
AC_SUBST([langm2])
AC_SUBST([langc])
AC_SUBST([maintainer])

dnl create these files
AC_CONFIG_FILES([Makefile m2/Makefile c/Makefile localrun.sh],
                [chmod +x localrun.sh])

AC_OUTPUT
