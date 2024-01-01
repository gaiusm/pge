SUFFIXES = .c .mod .def .o .obj .lo .a .m .mxm
DEPFLAGS=-MMD -MT $@ -MP -MF .deps/$*.d

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

ACLOCAL_AMFLAGS=-I m4

help:  force
	@echo "knows about:  all, build, clean"

noinst_LTLIBRARIES = libpgeif.la

libpgeif_la_SOURCES = macroObjects.mod Points.mod Fractions.mod PolyMatrix3D.mod \
                      Transform3D.mod delay.mod GC.mod popWorld.mod \
                      twoDsim.mod roots.mod coord.mod polar.mod history.mod \
                      deviceIf.mod rpc.mod pgeif.mod NetworkOrder.mod \
                      interpen.mod segment.mod \
                      gdbif.mod \
                      buffers.c

MY_DEPS = macroObjects.lo Points.lo Fractions.lo PolyMatrix3D.lo \
          Transform3D.lo delay.lo GC.lo popWorld.lo	\
          twoDsim.lo roots.lo coord.lo polar.lo \
          history.lo deviceIf.lo rpc.lo \
          pgeif.lo NetworkOrder.lo \
          interpen.lo segment.lo \
          gdbif.lo \
          buffers.lo

BUILT_SOURCES = springs.m circles.m rotating-line.m rotating-circles.m

GM2_LIB_DIR=$(shell gm2 -print-file-name=)
# GCC_DEFAULT_LIB=/opt/gm2/lib      # for arm
GCC_DEFAULT_LIB=$(HOME)/opt/lib64

SRC_PATH_PIM=-I$(srcdir)/pge-m2 -fm2-pathname=m2pim -I$(GM2_LIB_DIR)/m2/m2pim -fm2-pathname=m2iso -I$(GM2_LIB_DIR)/m2/m2iso -fno-m2-pathname=-

PROFILE =
CHECK = -fsoft-check-all
# CHECK =
OPT = -O0

GM2FLAGS = $(OPT) $(PROFILE) $(CHECK) -g -fm2-g -fiso -fextended-opaque -I$(srcdir)/src-m2 -g

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
	python3 $(top_srcdir)/mxmtool/max2code.py -v -o $@ $<

circles.m: $(top_srcdir)/mxm/circles.mxm
	python3 $(top_srcdir)/mxmtool/max2code.py -v -o $@ $<

rotating-circles.m: $(top_srcdir)/mxm/rotating-circles.mxm
	python3 $(top_srcdir)/mxmtool/max2code.py -v -o $@ $<

rotating-line.m: $(top_srcdir)/mxm/rotating-line.mxm
	python3 $(top_srcdir)/mxmtool/max2code.py -v -o $@ $<
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


pgeif.lo: pgeif.mod
	$(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
               --mode=compile gm2 -c $(CFLAGS_FOR_TARGET) $(LIBCFLAGS) $(libgm2_la_M2FLAGS) $(CHECK) -g -fm2-g -fno-m2-pathname=- -I$(srcdir) $(SRC_PATH_PIM) \
               -fruntime-modules=- \
               -fgen-module-list=pgeif.lst -fscaffold-main -fscaffold-static -fshared \
               $(srcdir)/pgeif.mod -o $@
	cat pgeif.lst

libpgeif.la:  $(MY_DEPS)
	swig -outdir . -o pgeif_wrap.cxx -c++ -python $(top_srcdir)/i/pgeif.i
	$(LIBTOOL) --tag=CC --mode=compile g++ -g -c pgeif_wrap.cxx -I/usr/include/python$(PYTHON_VERSION) $(CFLAGS_FOR_TARGET) -o pgeif_wrap.lo
	$(LIBTOOL) --tag=CC --mode=link gcc -g $(MY_DEPS) pgeif_wrap.lo \
           -L$(GCC_DEFAULT_LIB) \
           -rpath `pwd` -lm2iso -lm2pim -lgcc -lstdc++ -lc -lm -o libpgeif.la
	cp .libs/libpgeif.so ../_pgeif.so
	cp pgeif.py ../pgeif.py

if MAINTAINER
OBJECTS = $(SOURCES:%.mod=%.o)

bounce: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/bounce.mod

bounce2: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/bounce2.mod

bounce3: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/bounce3.mod

bounce4: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/bounce4.mod

bounce5: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/bounce5.mod

elc: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/elc.mod

elc2: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/elc2.mod

line: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/line.mod

wallh: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/wallh.mod

rboxes: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/rboxes.mod

circle: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/circle.mod

boxes: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/boxes.mod

ramps: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/ramps.mod

ramps2: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/ramps2.mod

slope: $(OBJECTS)
	$(RM) *.ms *.png
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/slope.mod

stairs: $(OBJECTS)
	$(RM) *.ms *.png
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/stairs.mod

py: $(OBJECTS)
	$(RM) *.ms *.png
	gm2 -pg -g -fiso -fextended-opaque testpy.mod

para: $(OBJECTS)
	$(RM) *.ms *.png
	gm2 -fcpp -I. $(GM2FLAGS) para.mod && ./a.out
	./produce-avi

wallv: $(OBJECTS)
	$(RM) *.ms *.png
	gm2 $(GM2FLAGS) wallv.mod

wall: $(OBJECTS)
	$(RM) *.ms *.png
	gm2 $(GM2FLAGS) wall.mod

snooker: $(OBJECTS)
	$(RM) *.ms *.png
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/snooker.mod

npn: $(OBJECTS)
	$(RM) *.ms *.png
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/npn.mod && ./a.out

test: $(OBJECTS)
	gm2 -fcpp -I. $(GM2FLAGS) $(srcdir)/test.mod && ./a.out

rotation: $(OBJECTS)
	gm2 -fiso -g -fsoft-check-all -O0 -fm2-g -I$(srcdir) $(srcdir)/rotation.mod

endif

transforms: rotating-circles.asc rotating-line.asc

if MAINTAINER
pge-c:  pge-c-clean pge-c-build

pge-maintainer: pge-c pge-push
endif

clean: force
	$(RM) *.o *.m *.cpp *~ $(EXAMPLES) *.so *.lo *.la
	$(RM) -rf .libs *_m2.cpp

clear: force
	$(RM) *.png *.ms *.cpp

force:

%.lo: %.mod .deps/%.d
	@test -z .deps || mkdir -p .deps
	$(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=compile gm2 -g -fm2-g -fiso $(DEPFLAGS) $(OPT) $(CHECK) -fextended-opaque -I. -I$(srcdir) -c $< -o $@

.c.lo:
	$(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=compile gcc -c $(DEPFLAGS) $(CFLAGS_FOR_TARGET) $(LIBCFLAGS) $(libgm2_la_M2FLAGS) $< -o $@


DEPFILES=$(libpgeif_la_SOURCES:%.mod=.deps/%.d)

$(DEPFILES):

include $(wildcard $(DEPFILES))
