## Process this file with automake to produce Makefile.in

INCLUDES = \
	$(FOO_CFLAGS)

CFLAGS =\
	 -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment \
	 -Wuninitialized -Wparentheses -Wpointer-arith \
	 -Wmissing-prototypes -export-dynamic \
	 -DPREFIX=\""$(prefix)"\" \
	 -DSYSCONFDIR=\""$(sysconfdir)"\" \
	 -DLIBDIR=\""$(libdir)"\" \
	 -DDATADIR=\""$(datadir)"\" \
	 -D_GNU_SOURCE \
	 -DGTK_DISABLE_DEPRECATED -DGNOME_DISABLE_DEPRECATED \
	 -O1 \
	 -g

bin_PROGRAMS = gwp

EXTRA_DIST = \
	gwp.glade

gwp_SOURCES = \
	callbacks.c\
	callbacks.h\
	support.c\
	support.h\
	main.c\
	global.h\
	game_state.h\
	game_state.c\
	planet.c\
	planet.h\
	base.c\
	base.h\
	ship.c\
	ship.h\
	starchart.c\
	starchart.h\
	gwp_types.c\
	gwp_types.h\
	vp_types.h\
	vp_utils.c\
	vp_utils.h\
	game_mgr.c\
	game_mgr.h\
	vp_unpack.h\
	vp_unpack.c\
	tables.c\
	tables.h\
	race.c\
	race.h\
	gwp-object.h\
	gwp-object.c\
	gwp-flying-object.h\
	gwp-flying-object.c\
	gwp-ship.h\
	gwp-ship.c\
	gwp-starbase.h\
	gwp-starbase.c\
	gwp-planet.h\
	gwp-planet.c

gwp_LDFLAGS = 

gwp_LDADD =  \
	$(FOO_LIBS)

gladedir = $(datadir)/gwp
glade_DATA = gwp.glade

