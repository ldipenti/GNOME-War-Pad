## Process this file with automake to produce Makefile.in

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

INCLUDES = \
	$(FOO_CFLAGS)

CFLAGS =\
	 -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment \
	 -Wuninitialized -Wparentheses -Wpointer-arith \
	 -Wmissing-prototypes -export-dynamic \
	 -DGWP_GLADE_XML_DIR=\""$(gladedir)"\" \
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
	vp_utils.h

gwp_LDFLAGS = 

gwp_LDADD =  \
	$(FOO_LIBS)

gladedir = $(datadir)/gwp
glade_DATA = gwp.glade
