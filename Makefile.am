## Process this file with automake to produce Makefile.in

SUBDIRS = po pixmaps help scripts src

gwpdocdir = ${prefix}/share/doc/gwp
gwpdoc_DATA = 		\
	README		\
	AUTHORS		\
	CHANGES		\
	NEWS		\
	TODO

EXTRA_DIST = $(gwpdoc_DATA)	\
        intltool-extract.in	\
        intltool-merge.in	\
        intltool-update.in	\
	COPYING			\
	INSTALL			\
	COPYING-DOCS		\
	ABOUT_NLS

gnomemenudir = $(prefix)/@NO_PREFIX_PACKAGE_MENU_DIR@/Games
gnomemenu_DATA = gwp.desktop

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

