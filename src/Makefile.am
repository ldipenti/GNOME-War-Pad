## Process this file with automake to produce Makefile.in

INCLUDES = \
	$(FOO_CFLAGS)

CFLAGS =\
	 -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment \
	 -Wuninitialized -Wparentheses -Wpointer-arith \
	 -Wmissing-prototypes -export-dynamic \
	 -DDATA_DIR=\""$(datadir)"\" \
	 -O1\
	 -g

bin_PROGRAMS = gwp

gwp_SOURCES = \
	callbacks.c\
	callbacks.h\
	support.c\
	support.h\
	main.c\
	global.h\
	race_select.c\
	race_select.h\
	game_state.h\
	game_state.c\
	planet.c\
	planet.h\
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
	game_types.h

gwp_LDFLAGS = 

gwp_LDADD =  \
	$(FOO_LIBS)

gladedir = $(datadir)/gwp
glade_DATA = gwp.glade

