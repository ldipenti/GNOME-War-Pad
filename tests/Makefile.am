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
	../src/gwp-specs.h						\
	../src/global.h							\
	../src/vp_types.h						\
	../src/gwp-object.h		../src/gwp-object.c		\
	../src/gwp-flying-object.h	../src/gwp-flying-object.c	\
	../src/gwp-ship.h		../src/gwp-ship.c		\
	../src/gwp-starbase.h		../src/gwp-starbase.c		\
	../src/gwp-planet.h		../src/gwp-planet.c		\
	../src/gwp-location.h		../src/gwp-location.c		\
	../src/gwp-hullspec.h		../src/gwp-hullspec.c		\
	../src/gwp-beamspec.h		../src/gwp-beamspec.c		\
	../src/gwp-torpspec.h		../src/gwp-torpspec.c		\
	../src/gwp-engspec.h		../src/gwp-engspec.c		\
	../src/gwp-minefield.h		../src/gwp-minefield.c		\
	../src/gwp-ion-storm.h		../src/gwp-ion-storm.c		\
	../src/gwp-starchart.h		../src/gwp-starchart.c		\
	../src/gwp-ui.h			../src/gwp-ui.c			\
	../src/gwp-py-functions.h	../src/gwp-py-functions.c	\
	../src/support.h		../src/support.c		\
	../src/gwp-game-state.h		../src/gwp-game-state.c		\
	../src/starchart.h		../src/starchart.c		\
	../src/gwp_types.h		../src/gwp_types.c		\
	../src/vp_utils.h		../src/vp_utils.c		\
	../src/game_mgr.h		../src/game_mgr.c		\
	../src/vp_unpack.h		../src/vp_unpack.c		\
	../src/tables.h			../src/tables.c			\
	../src/mission.h		../src/mission.c		\
	../src/race.h			../src/race.c			\
	../src/gwp-python.h		../src/gwp-python.c		\
	../src/gwp-utils.h		../src/gwp-utils.c


# Unit test source files
check_gwp_SOURCES = $(sources) 		\
	check-gwp.c 			\
	check-gwp-object.c		\
	check-gwp-ship.c

check_gwp_LDADD =  \
	$(GNOME_LIBS) \
	$(PY_LIB_LOC) $(PY_EXTRA_LIBS) $(PY_LIBS) \
	$(GTKGLEXT_LIBS) \
	$(PYGTK_LIBS) \
	$(CHECK_LIBS)
