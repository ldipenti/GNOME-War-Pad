## Process this file with automake to produce Makefile.in

SUBDIRS = po pixmaps help scripts src tests

gwpdocdir = ${prefix}/doc/gwp
gwpdoc_DATA = \
	README\
	COPYING\
	COPYING-DOCS\
	BUGS\
	AUTHORS\
	INSTALL\
	CHANGES\
	NEWS\
	TODO\
	ABOUT-NLS

EXTRA_DIST = $(gwpdoc_DATA)	\
        intltool-extract.in	\
        intltool-merge.in	\
        intltool-update.in

gnomemenudir = $(prefix)/@NO_PREFIX_PACKAGE_MENU_DIR@/Games
gnomemenu_DATA = gwp.desktop



# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

