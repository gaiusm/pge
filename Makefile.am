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
PYTHON_VERSION=$(strip $(shell python -V 2>&1 | cut -b8- | cut -f1-2 -d'.'))

DISTFILES = Makefile.in configure.ac configure \
            README version.c COPYING examples \
            c m2 python m mxm m4 mxmtool \
            INSTALL

if MAINTAINER
help:  force
	@echo "knows about:  all, clean, install, pge-maintainer"
else
help:  force
	@echo "knows about:  all, clean, install"
endif

if LANGM2
SUBDIRS = m2
endif

if LANGC
SUBDIRS = c
endif

if MAINTAINER
springs.m: $(srcdir)/mxm/springs.mxm
	python $(srcdir)/python/max2code.py -v -o $@ $<

circles.m: $(srcdir)/mxm/circles.mxm
	python $(srcdir)/python/max2code.py -v -o $@ $<

rotating-circles.m: $(srcdir)/mxm/rotating-circles.mxm
	python $(srcdir)/python/max2code.py -v -o $@ $<

rotating-line.m: $(srcdir)/mxm/rotating-line.mxm
	python $(srcdir)/python/max2code.py -v -o $@ $<
else
springs.m: $(srcdir)/mxm/springs.mxm
	cp $(srcdir)/m/springs.m $@

circles.m: $(srcdir)/mxm/circles.mxm
	cp $(srcdir)/m/circles.m $@

rotating-circles.m: $(srcdir)/mxm/rotating-circles.mxm
	cp $(srcdir)/m/rotating-circles.m $@

rotating-line.m: $(srcdir)/mxm/rotating-line.mxm
	cp $(srcdir)/m/rotating-line.m $@
endif

build: all

springs: force
	./localrun.sh $(srcdir)/examples/springs/simple.py
	./localrun.sh $(srcdir)/examples/springs/double.py
	./localrun.sh $(srcdir)/examples/springs/swing.py
	./localrun.sh $(srcdir)/examples/springs/treble.py
	./localrun.sh $(srcdir)/examples/springs/bridge.py

trapped: force
	PYTHONPATH=.:$(srcdir)/python python $(srcdir)/examples/trapped/trapped.py

output.raw: _pgeif.so
	PYTHONPATH=.:$(srcdir)/src python $(srcdir)/examples/exampleBoxes.py

playback: force
	PYTHONPATH=.:$(srcdir)/src python $(srcdir)/src/pgeplayback.py

transforms: rotating-circles.asc rotating-line.asc

install: _pgeif.so
	cp $(srcdir)/python/pge.py .
	cp $(srcdir)/python/pgeplayback.py .
	PYTHONPATH=.:$(srcdir)/python python $(srcdir)/pgesetup.py build
	python -m py_compile pge.py
	python -m py_compile pgeif.py
	python -m py_compile pgeplayback.py
	$(INSTALL_PROGRAM) -m 755 $(srcdir)/pgeplayback $(DESTDIR)/usr/bin
	$(INSTALL_PROGRAM) -m 755 -d $(DESTDIR)/usr/lib/python$(PYTHON_VERSION)
	$(INSTALL_PROGRAM) -m 644 pge.py $(DESTDIR)/usr/lib/python$(PYTHON_VERSION)
	$(INSTALL_PROGRAM) -m 644 pge.pyc $(DESTDIR)/usr/lib/python$(PYTHON_VERSION)
	$(INSTALL_PROGRAM) -m 644 pgeif.py $(DESTDIR)/usr/lib/python$(PYTHON_VERSION)
	$(INSTALL_PROGRAM) -m 644 pgeif.pyc $(DESTDIR)/usr/lib/python$(PYTHON_VERSION)
	$(INSTALL_PROGRAM) -m 644 pgeplayback.py $(DESTDIR)/usr/lib/python$(PYTHON_VERSION)
	$(INSTALL_PROGRAM) -m 644 pgeplayback.pyc $(DESTDIR)/usr/lib/python$(PYTHON_VERSION)
	$(INSTALL_PROGRAM) -m 644 _pgeif.so $(DESTDIR)/usr/lib/python$(PYTHON_VERSION)

_pgeif.so: all

documentation: pge.pdf pge.html texi2tr.css

pge.pdf: pge.ps
	gs -q -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=$@ $<

pge.ps: pge.dvi
	dvips -o $@ $<

pge.dvi: pge-api.texi $(srcdir)/doc/pge.texi
	texi2dvi -I $(srcdir)/ $(srcdir)/doc/pge.texi

pge-api.texi:  force
	python $(srcdir)/tools/py2texi.py -f$(srcdir)/python/pge.py > pge-api.texi

texi2tr.css: $(srcdir)/www/tools/texi2tr/html/texi2tr.css
	cp $< $@

pge.html: pge-api.texi $(srcdir)/doc/pge.texi
	cp $(srcdir)/www/tools/texi2tr/html/*.html .
	cp $(srcdir)/www/tools/texi2tr/png/*png .
	$(TEXI2HTML) -T$(srcdir)/www/tools/texi2tr/html -n -I.:$(srcdir)/doc:$(srcdir) -b pge-%d.html -r pge.html pge.texi

release: force
	pwd
	echo pge-`sed -e '/version_string/!d' \
          -e 's/[^0-9.]*\([0-9.]*\).*/\1/' -e q $(srcdir)/version.c` > .fname
	-rm -rf `cat .fname`
	mkdir `cat .fname`
	dst=`cat .fname`; for f in $(DISTFILES); do \
           cp -rp $(srcdir)/$$f $$dst/$$f ; \
        done
	tar --gzip -chf `cat .fname`.tar.gz `cat .fname`
	-rm -rf `cat .fname` .fname

clean: force
	$(RM) *.o *.m *.cpp *~ $(EXAMPLES) *.so *.lo *.la
	$(RM) -rf .libs *_m2.cpp

clear: force
	$(RM) *.png *.ms *.cpp

force:

if MAINTAINER
GCCVERSION=8.2.0
MC=$(HOME)/GM2/graft-svn-trunc/build-svn-trunc/gcc/gm2/boot-bin/mc --h-file-prefix=G
PIMLIBS=$(HOME)/GM2/graft-$(GCCVERSION)/gcc-$(GCCVERSION)/gcc/gm2/gm2-libs
ISOLIBS=$(HOME)/GM2/graft-$(GCCVERSION)/gcc-$(GCCVERSION)/gcc/gm2/gm2-libs-iso
MCLIBS=$(HOME)/GM2/graft-$(GCCVERSION)/gcc-$(GCCVERSION)/gcc/gm2/mc-boot-ch

M2DEFS = coord.def delay.def deviceGroff.def \
         deviceIf.def devicePy.def Fractions.def GC.def \
         history.def interpen.def segment.def macroObjects.def network.def \
         NetworkOrder.def pgeif.def Points.def polar.def \
         popWorld.def roots.def rpc.def \
         Transform3D.def twoDsim.def PolyMatrix3D.def network.def

M2MODS = bagatelle.mod bounce2.mod bounce3.mod bounce4.mod \
         bounce5.mod bounce.mod boxes.mod circle.mod \
         delay.mod deviceGroff.mod deviceIf.mod \
         devicePy.mod elc2.mod elc.mod foo.mod Fractions.mod GC.mod \
         history.mod interpen.mod segment.mod Indexing.mod line.mod macroObjects.mod MemStream.mod \
         NetworkOrder.mod npn.mod para.mod pgeif.mod Points.mod \
         polar.mod popWorld.mod \
         ramps2.mod ramps.mod RawIO.mod rboxes.mod roots.mod \
         rotate.mod rpc.mod RTExceptions.mod slope.mod \
         snooker.mod stairs.mod Storage.mod test.mod \
         testpy.mod Transform3D.mod twoDsim.mod \
         wallh.mod wall.mod wallv.mod world.mod \
         PolyMatrix3D.mod gdbif.mod

M2EMODS = coord.mod RTgen.mod

M2PIMLIBDEFS = Storage.def Indexing.def libc.def libm.def \
               MathLib0.def StrLib.def gdbif.def \
               Assertion.def DynamicStrings.def ASCII.def \
               SYSTEM.def FormatStrings.def StringConvert.def \
               M2RTS.def StrIO.def StdIO.def Selective.def \
               SysExceptions.def FIO.def NumberIO.def RTint.def \
               StrLib.def dtoa.def ldtoa.def IO.def errno.def \
               termios.def Assertion.def MathLib0.def cbuiltin.def \
               RTExceptions.def

M2PIMLIBMODS = Storage.mod Indexing.mod \
               MathLib0.mod StrLib.mod \
               Assertion.mod DynamicStrings.mod ASCII.mod \
               FormatStrings.mod StringConvert.mod \
               M2RTS.mod StrIO.mod StdIO.mod FIO.mod NumberIO.mod \
               RTint.mod StrLib.mod IO.mod Assertion.mod \
               MathLib0.mod

M2ISOLIBDEFS = MemStream.def STextIO.def SWholeIO.def SeqFile.def \
               ClientSocket.def RawIO.def IOChan.def IOConsts.def \
               ChanConsts.def M2EXCEPTION.def pth.def COROUTINES.def \
               RTentity.def EXCEPTIONS.def \
               RTgenif.def Strings.def CharClass.def RawIO.def

M2ISOLIBMODS =               STextIO.mod SWholeIO.mod SeqFile.mod \
               ClientSocket.mod IOChan.mod IOConsts.mod \
               ChanConsts.mod M2EXCEPTION.mod \
               RTentity.mod EXCEPTIONS.mod COROUTINES.mod \
               RTgenif.mod Strings.mod CharClass.mod RawIO.mod

pge-c-clean: force
	$(RM) $(srcdir)/c/*.[ch]

pge-c-build: force
	for i in $(M2PIMLIBDEFS) ; do \
	   $(MC) -I$(PIMLIBS) -I$(ISOLIBS) -I$(srcdir)/m2 -o=$(srcdir)/c/G`basename $$i .def`.h $(PIMLIBS)/$$i ; \
        done
	for i in $(M2PIMLIBMODS) ; do \
	   $(MC) -I$(PIMLIBS) -I$(ISOLIBS) -I$(srcdir)/m2 -o=$(srcdir)/c/`basename $$i .mod`.c $(PIMLIBS)/$$i ; \
        done
	for i in $(M2ISOLIBDEFS) ; do \
	   $(MC) -I$(ISOLIBS) -I$(PIMLIBS) -I$(srcdir)/m2 -o=$(srcdir)/c/G`basename $$i .def`.h $(ISOLIBS)/$$i ; \
        done
	for i in $(M2ISOLIBMODS) ; do \
	   $(MC) -I$(ISOLIBS) -I$(PIMLIBS) -I$(srcdir)/m2 -o=$(srcdir)/c/`basename $$i .mod`.c $(ISOLIBS)/$$i ; \
        done
	for i in $(M2DEFS) ; do \
	   $(MC) -I$(PIMLIBS) -I$(ISOLIBS) -I$(srcdir)/m2 -o=$(srcdir)/c/G`basename $$i .def`.h $(srcdir)/m2/$$i ; \
        done
	for i in $(M2MODS) ; do \
	   $(MC) -I$(PIMLIBS) -I$(ISOLIBS) -I$(srcdir)/m2 -o=$(srcdir)/c/`basename $$i .mod`.c $(srcdir)/m2/$$i ; \
        done
	for i in $(M2EMODS) ; do \
	   $(MC) --extended-opaque -I$(PIMLIBS) -I$(ISOLIBS) -I$(srcdir)/m2 -o=$(srcdir)/c/`basename $$i .mod`.c $(srcdir)/m2/$$i ; \
        done
	cp $(srcdir)/m2/*.c $(srcdir)/c/
	cp $(srcdir)/src-c/Gwrapsock.c $(srcdir)/c/
	cp $(MCLIBS)/* $(srcdir)/c/
	cat $(srcdir)/c/Gpgeif.h | sed -e 's/pgeif_//g' > t ; mv t $(srcdir)/c/Gpgeif.h
	cat $(srcdir)/c/pgeif.c | sed -e 's/_pgeif/_ABCDEF/g' | sed -e 's/pgeif_//g'  | sed -e 's/_ABCDEF/_pgeif/g' > t ; mv t $(srcdir)/c/pgeif.c

pge-maintainer: pge-c-clean pge-c-build

endif
