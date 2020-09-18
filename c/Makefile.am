SUFFIXES = .c .mod .def .o .obj .lo .a .m .mxm

SHELL=/bin/bash

prefix= @prefix@
datarootdir= @datarootdir@
srcdir= @srcdir@
mandir= @mandir@
exec_prefix=@exec_prefix@
bindir= @bindir@
INSTALL_PROGRAM = install

TEXI2HTML=python $(srcdir)/www/tools/texi2tr/src/texi2tr.py
PYTHON_VERSION=$(strip $(shell python3 -V 2>&1 | cut -b8- | cut -f1-2 -d'.'))
# GM2GCCBASE=11.0.0
GM2GCCBASE=10.2.1

GM2=/opt/bin/gm2
G++=/opt/bin/g++
CC=/opt/bin/gcc

TARGET_SUBDIR=/opt/gm2/lib64

ACLOCAL_AMFLAGS=-I m4

help:  force
	@echo "knows about:  all, build, clean"

noinst_LTLIBRARIES = libpgeif.la

libpgeif_la_SOURCES = macroObjects.c Points.c Fractions.c PolyMatrix3D.c \
                      Transform3D.c delay.c GC.c popWorld.c \
                      twoDsim.c roots.c coord.c polar.c history.c \
                      deviceIf.c rpc.c pgeif.c NetworkOrder.c \
                      RTExceptions.c \
                      buffers.c interpen.c segment.c \
                      GFIO.c NumberIO.c RTint.c StrLib.c DynamicStrings.c \
                      StringConvert.c StrIO.c StdIO.c IO.c \
                      MathLib0.c Assertion.c Indexing.c ASCII.c \
                      RTentity.c EXCEPTIONS.c COROUTINES.c \
                      RTgenif.c Strings.c CharClass.c RawIO.c \
                      Gmcrts.c Glibc.c Gdtoa.c Gerrno.c Gldtoa.c \
                      GSelective.c GSysExceptions.c GSYSTEM.c Gtermios.c \
                      GUnixArgs.c Gwrapc.c gdbif.c network.c Glibm.c \
                      Gcbuiltin.c GBuiltins.c Gwrapsock.c


MY_DEPS = macroObjects.lo Points.lo Fractions.lo PolyMatrix3D.lo \
          Transform3D.lo delay.lo GC.lo popWorld.lo	\
          twoDsim.lo roots.lo coord.lo polar.lo \
          history.lo deviceIf.lo rpc.lo \
          pgeif.lo NetworkOrder.lo \
          RTExceptions.lo \
          buffers.lo interpen.lo segment.lo \
          FIO.lo NumberIO.lo RTint.lo StrLib.lo DynamicStrings.lo \
          StringConvert.lo StrIO.lo StdIO.lo IO.lo \
          Assertion.lo MathLib0.lo Indexing.lo ASCII.lo \
          RTentity.lo EXCEPTIONS.lo COROUTINES.lo \
          RTgenif.lo Strings.lo CharClass.lo RawIO.lo \
          Gmcrts.lo Glibc.lo Gdtoa.lo Gerrno.lo Gldtoa.lo \
          GSelective.lo GSysExceptions.lo GSYSTEM.lo Gtermios.lo \
          GUnixArgs.lo Gwrapc.lo gdbif.lo network.lo Glibm.lo \
          Gcbuiltin.lo GBuiltins.lo Gwrapsock.lo

BUILT_SOURCES = springs.m circles.m rotating-line.m rotating-circles.m

# PYTHON_VERSION=$(shell python --version 2>&1 | cut -f2 -d' ')
# PYTHON_VERSION=2.7

# GM2_LIB_DIR=/home/gaius/opt/lib/gcc/x86_64-unknown-linux-gnu/$(GM2GCCBASE)/m2
GM2_LIB_DIR=$(shell gm2 -print-file-name=)
# GCC_DEFAULT_LIB=/opt/gm2/lib      # for arm
GCC_DEFAULT_LIB=/opt/gm2/lib64    # for amd64

SRC_PATH_PIM=-I$(srcdir)/pge-m2 -I$(GM2_LIB_DIR)m2/m2pim -I$(GM2_LIB_DIR)m2/m2iso

PROFILE =
CHECK = -fsoft-check-all

GM2FLAGS = $(PROFILE) $(CHECK) -g -fiso -fextended-opaque -I$(srcdir)/src-m2 -g

EXAMPLES = elc

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

build: _pgeif.so

bagatelle: _pgeif.so
	PYTHONPATH=.:$(srcdir)/src python $(srcdir)/examples/bagatelle/bagatelle.py

matchsticks: _pgeif.so
	PYTHONPATH=.:$(srcdir)/src python $(srcdir)/examples/matchsticks/matchsticks.py

breakout: _pgeif.so
	PYTHONPATH=.:$(srcdir)/src python $(srcdir)/examples/breakout/breakout.py

trapped: _pgeif.so
	PYTHONPATH=.:$(srcdir)/src python $(srcdir)/examples/trapped/trapped.py

matchsticks2: _pgeif.so
	PYTHONPATH=.:$(srcdir)/src python $(srcdir)/testsuite/matchsticks2.py

if MAINTAINER
springs.m: $(top_srcdir)/mxm/springs.mxm
	python $(top_srcdir)/mxmtool/max2code.py -v -o $@ $<

circles.m: $(top_srcdir)/mxm/circles.mxm
	python $(top_srcdir)/mxmtool/max2code.py -v -o $@ $<

rotating-circles.m: $(top_srcdir)/mxm/rotating-circles.mxm
	python $(top_srcdir)/mxmtool/max2code.py -v -o $@ $<

rotating-line.m: $(top_srcdir)/mxm/rotating-line.mxm
	python $(top_srcdir)/mxmtool/max2code.py -v -o $@ $<
else
springs.m: $(top_srcdir)/mxm/springs.mxm
	cp $(top_srcdir)/m/springs.m $@

circles.m: $(top_srcdir)/mxm/circles.mxm
	cp $(top_srcdir)/m/circles.m $@

rotating-circles.m: $(top_srcdir)/mxm/rotating-circles.mxm
	cp $(top_srcdir)/m/rotating-circles.m $@

rotating-line.m: $(top_srcdir)/mxm/rotating-line.mxm
	cp $(top_srcdir)/m/rotating-line.m $@
endif


.mod.lo:
	$(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=compile gm2 -fcpp -g -fiso -fextended-opaque -I$(top_srcdir)/m2 -I$(srcdir) -c $< -o $@

.c.lo:
	$(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=compile gcc -c $(CFLAGS_FOR_TARGET) $(LIBCFLAGS) $(libgm2_la_M2FLAGS) $< -o $@

libpgeif.la:  $(MY_DEPS)
	swig -outdir . -o pgeif_wrap.cxx -c++ -python $(top_srcdir)/i/pgeif.i
	$(LIBTOOL) --tag=CC --mode=compile g++ -g -c pgeif_wrap.cxx -I/usr/include/python$(PYTHON_VERSION) -o pgeif_wrap.lo
	gm2 -c -g $(SRC_PATH_PIM) -fcpp -fmakelist -I$(top_srcdir)/m2 $(top_srcdir)/m2/pgeif.mod
	gm2 -c -g $(SRC_PATH_PIM) -fcpp -fmakeinit -fshared -I$(top_srcdir) $(top_srcdir)/m2/pgeif.mod
	$(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=compile gcc -c $(CFLAGS_FOR_TARGET) $(LIBCFLAGS) $(libgm2_la_M2FLAGS) $(srcdir)/pgeif.c -o pgeif.lo
	$(LIBTOOL) --tag=CC --mode=compile g++ -g -c _m2_pgeif.cpp -o _m2_pgeif.lo
	$(LIBTOOL) --tag=CC --mode=link gcc -g _m2_pgeif.lo $(MY_DEPS) \
            pgeif_wrap.lo \
           -L$(GCC_DEFAULT_LIB) \
           -rpath `pwd` -lm2pim -lm2iso -lgcc -lstdc++ -lc -lm -o libpgeif.la
	cp .libs/libpgeif.so ../_pgeif.so
	cp pgeif.py ../pgeif.py

#	$(LIBTOOL) --tag=CC --mode=compile g++ -g -c pgeif_m2.cpp -o _m2_pgeif.lo

transforms: rotating-circles.asc rotating-line.asc

clean: force
	$(RM) *.o *.m *.cpp *~ $(EXAMPLES) *.so *.lo *.la
	$(RM) -rf .libs *_m2.cpp

clear: force
	$(RM) *.png *.ms *.cpp

force:
