## Process this file with automake to produce Makefile.in

INCLUDES = \
	$(GNOME_CFLAGS) \
	$(PY_CFLAGS) \
	$(GTKGLEXT_CFLAGS) \
	$(PYGTK_CFLAGS)

# FIXME: Add this when migrating to gtk 2.4: -DGTK_DISABLE_DEPRECATED 

CFLAGS = \
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

bin_PROGRAMS = gwp

EXTRA_DIST =    gwp.glade		\
		gwp-py-mappings.c

gwp_SOURCES =				\
	gwp-object.h			\
	gwp-object.c			\
	gwp-flying-object.h		\
	gwp-flying-object.c		\
	gwp-ship.h			\
	gwp-ship.c			\
	gwp-starbase.h			\
	gwp-starbase.c			\
	gwp-planet.h			\
	gwp-planet.c			\
	gwp-location.h			\
	gwp-location.c			\
	gwp-hullspec.h			\
	gwp-hullspec.c			\
	gwp-beamspec.h			\
	gwp-beamspec.c			\
	gwp-torpspec.h			\
	gwp-torpspec.c			\
	gwp-engspec.h			\
	gwp-engspec.c			\
	gwp-minefield.h			\
	gwp-minefield.c			\
	gwp-ion-storm.h			\
	gwp-ion-storm.c			\
	gwp-messages.c			\
	gwp-messages.h			\
	gwp-specs.h			\
	callbacks.c			\
	callbacks.h			\
	support.c			\
	support.h			\
	main.c				\
	global.h			\
	game_state.h			\
	game_state.c			\
	starchart.c			\
	starchart.h			\
	gwp_types.c			\
	gwp_types.h			\
	vp_types.h			\
	vp_utils.c			\
	vp_utils.h			\
	game_mgr.c			\
	game_mgr.h			\
	vp_unpack.h			\
	vp_unpack.c			\
	tables.c			\
	tables.h			\
	mission.c			\
	mission.h			\
	race.c				\
	race.h				\
	message-reader.c		\
	message-reader.h		\
	vcr.c				\
	vcr.h				\
	vcr-combat.c			\
	vcr-combat.h			\
	gwp-python.h			\
	gwp-python.c			\
	gwp-utils.c			\
	gwp-utils.h

gwp_LDADD =  \
	$(GNOME_LIBS) \
	$(PY_LIB_LOC) $(PY_EXTRA_LIBS) $(PY_LIBS) \
	$(GTKGLEXT_LIBS) \
	$(PYGTK_LIBS)

gladedir = $(datadir)/gwp
glade_DATA = gwp.glade

