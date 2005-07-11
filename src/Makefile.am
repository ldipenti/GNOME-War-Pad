## Process this file with automake to produce Makefile.in

INCLUDES = \
	$(GNOME_CFLAGS) \
	$(PY_CFLAGS) \
	$(GTKGLEXT_CFLAGS) \
	$(PCRE_CFLAGS) \
	$(PYGTK_CFLAGS)

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

bin_PROGRAMS = gwp 

EXTRA_DIST =    gwp.glade		\
		gwp-py-mappings.c

gwp_SOURCES =						\
	main.c						\
	gwp-specs.h					\
	global.h					\
	vp_types.h					\
	gwp-object.h		gwp-object.c		\
	gwp-flying-object.h	gwp-flying-object.c	\
	gwp-ship.h		gwp-ship.c		\
	gwp-starbase.h		gwp-starbase.c		\
	gwp-planet.h		gwp-planet.c		\
	gwp-location.h		gwp-location.c		\
	gwp-hullspec.h		gwp-hullspec.c		\
	gwp-beamspec.h		gwp-beamspec.c		\
	gwp-torpspec.h		gwp-torpspec.c		\
	gwp-engspec.h		gwp-engspec.c		\
	gwp-minefield.h		gwp-minefield.c		\
	gwp-ion-storm.h		gwp-ion-storm.c		\
	gwp-starchart.h		gwp-starchart.c		\
	gwp-marker.h		gwp-marker.c		\
	gwp-ui.h		gwp-ui.c		\
	gwp-game-state.h	gwp-game-state.c	\
	gwp-messages.h		gwp-messages.c		\
	gwp-vcrfile.h		gwp-vcrfile.c		\
	gwp-py-functions.h	gwp-py-functions.c	\
	gwp-race.h		gwp-race.c		\
	callbacks.h		callbacks.c		\
	support.h		support.c		\
	starchart.h		starchart.c		\
	gwp_types.h		gwp_types.c		\
	vp_utils.h		vp_utils.c		\
	game_mgr.h		game_mgr.c		\
	vp_unpack.h		vp_unpack.c		\
	tables.h		tables.c		\
	mission.h		mission.c		\
	race.h			race.c			\
	message-reader.h	message-reader.c	\
	vcr.h			vcr.c			\
	vcr-combat.h		vcr-combat.c		\
	vcr-combat-gl.h		vcr-combat-gl.c		\
	trackball.h		trackball.c		\
	gwp-python.h		gwp-python.c		\
	gwp-utils.h		gwp-utils.c		\
	vp_maketurn.c		vp_maketurn.h		\
	vp_maketurn_global.c	vp_maketurn_global.h	\
	vp_maketurn_kmkturn.c	vp_maketurn_kmkturn.h	\
	vp_maketurn_misc.c	vp_maketurn_misc.h	\
	vp_maketurn_playerio.c	vp_maketurn_playerio.h


gwp_LDADD =  \
	$(GNOME_LIBS) \
	$(PY_LIB_LOC) $(PY_EXTRA_LIBS) $(PY_LIBS) \
	$(GTKGLEXT_LIBS) \
	$(PCRE_LIBS) \
	$(PYGTK_LIBS)

gladedir = $(datadir)/gwp
glade_DATA = gwp.glade

cacaculo:
	python setup.py build $(COMPILE) $(gwp_LDADD)
