## Process this file with automake to produce Makefile.in

TESTS = \
	check-gwp

INCLUDES = \
	-I../src/ \
	$(GNOME_CFLAGS) \
	$(PY_CFLAGS) \
	$(GTKGLEXT_CFLAGS) \
	$(PYGTK_CFLAGS) \
	$(CHECK_CFLAGS)

# FIXME: Add this when migrating to gtk 2.4: -DGTK_DISABLE_DEPRECATED 

AM_CFLAGS = \
	 -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment \
	 -Wuninitialized -Wparentheses -Wpointer-arith \
	 -Wmissing-prototypes -export-dynamic \
	 -DPREFIX=\""$(prefix)"\" \
	 -DSYSCONFDIR=\""$(sysconfdir)"\" \
	 -DLIBDIR=\""$(libdir)"\" \
	 -DDATADIR=\""$(datadir)"\" \
	 -D_GNU_SOURCE \
	 -O1 \
	 -g

noinst_PROGRAMS = check-gwp

# Add here GWP's needed source files
sources =								\
	../src/support.h		../src/support.c		\
	../src/gwp-object.h		../src/gwp-object.c		\
	../src/gwp-ui.h			../src/gwp-ui.c			

# Unit test source files
check_gwp_SOURCES = $(sources) 		\
	check-gwp.c 			\
	check-gwp-object.c		\
	check-gwp-ui.c			
#	check-gwp-starchart.c

check_gwp_LDADD =  \
	$(GNOME_LIBS) \
	$(PY_LIB_LOC) $(PY_EXTRA_LIBS) $(PY_LIBS) \
	$(GTKGLEXT_LIBS) \
	$(PYGTK_LIBS) \
	$(CHECK_LIBS)
