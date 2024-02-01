# Note: Typing 'make' from this level will rebuild xpat2 from scratch.
#       Afterwards, type 'make install' (as root) to install the game
#	in default directories. A manual is in the doc subdirectory.
#	You may run LaTeX (2.09) on it using 'make manual'.
#
#       You may change src/Imakefile for different configurations.
#       But then, you're on your own...
#
#       Should you add / improve translations, please send a copy to
#       Michael.Bischoff@gmx.net for inclusion in future releases.
#	Please ignore any e-mail addresses ending in tu-bs.de, they are
#	no longer valid.

all:
	(cd src && xmkmf && $(MAKE) && strip xpat2)

manual:
	(cd doc && $(MAKE) xpat2.ps)

# different install targets: imake default, local, Linux FSSTND
install:
	(cd src && $(MAKE) install)

install.local:
	(cd src && $(MAKE) install.local)

install.fsstnd:
	(cd src && $(MAKE) install.fsstnd)


clean:
	(cd src && xmkmf && $(MAKE) clean)
	(cd doc && $(MAKE) clean)
	rm -f src/Makefile src/xpat2X*
	find . -name "*~" -exec rm \{\} \;

distrib:
	$(MAKE) clean
	(cd ..; tar cvfz xpat2-1.07-src.tar.gz xpat2-1.07)

bindistrib:
	(cd /; tar cvfz $(HOME)/xpat2-1.07-bin.tar.gz var/games/xpat* \
	 usr/games/bin/xpat2 usr/man/man6/xpat2.6x usr/doc/xpat2.dvi \
	 usr/doc/xpat2.lsm usr/games/lib/xpat)

allinterfaces:
# select a subset of Xlib Xaw Xview XQt Xm1 Xm2
# 'make install' will use the last one you selected
# 	mv src/Xpat.tmpl src/Xpat.tmpl.none
	for iface in Xlib Xaw XQt Xm1 Xm2;		\
	  do							\
	  rm -f src/X*.o;					\
	  sed -e "1,50s/undef use$$iface/define use$$iface/"	\
	     < src/Xpat.tmpl.none > src/Xpat.tmpl;		\
	  (cd src && xmkmf && make xpat2 && strip xpat2 &&	\
	     cp xpat2 xpat2$$iface);				\
	  cp lib/XPat.ad.$$iface src/XPat.ad;			\
	done

# targets from Makefile.Linux with preset directories for the SuSE distribution
compile.suse:
	$(MAKE) all \
		XPATLIBDIR=/usr/X11R6/lib/xpat \
		XPATMANDIR=/usr/X11R6/man/man6

install.suse:
	$(MAKE) install \
		XPATLIBDIR=/usr/X11R6/lib/xpat \
		XPATMANDIR=/usr/X11R6/man/man6
	chgrp game /usr/X11/bin/xpat2
	chmod 2755 /usr/X11/bin/xpat2
