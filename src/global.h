/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002 Lucas Di Pentima <lucas@lunix.com.ar>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <gnome.h>
#include <glade/glade.h>
#include <gconf/gconf-client.h>

#include "game_state.h"
#include "gwp_types.h"

#define GWP_GLADE_XML_DIR DATADIR"/gwp"
#define GWP_IMAGES_DIR DATADIR"/pixmaps/gwp/images"
#define GWP_ICONS_DIR DATADIR"/pixmaps/gwp/icons"

/* 
 * Defines
 */
#define MAX_PLANETS 500
#define MAX_SHIPS 500
#define XYPLAN "xyplan.dat"
#define PNAMES "PLANET.NM"
#define STARCHART_X_MIN 1000
#define STARCHART_X_MAX 3000
#define STARCHART_Y_MIN 1000
#define STARCHART_Y_MAX 3000
#define STARCHART_WIDTH_INT (STARCHART_X_MAX - STARCHART_X_MIN)
#define STARCHART_WIDTH ((gdouble) STARCHART_WIDTH_INT)
#define CANVAS_WIDTH 3000.0
#define CANVAS_WIDTH_INT 3000
#define CANVAS_OFFSET ((CANVAS_WIDTH - STARCHART_WIDTH) / 2.0)
#define CANVAS_OFFSET_INT ((CANVAS_WIDTH_INT - STARCHART_WIDTH_INT) / 2)
#define QUAD_WIDTH 100.0
#define QUAD_WIDTH_INT 100
#define QUAD_PER_LINE (CANVAS_WIDTH_INT / QUAD_WIDTH_INT)
#define TOTAL_QUADS (QUAD_PER_LINE * QUAD_PER_LINE)

#define SHIP_VALID_COORD_MARGIN 150
#define SHIP_VALID_X_MAX (3000 + SHIP_VALID_COORD_MARGIN)
#define SHIP_VALID_X_MIN (1000 - SHIP_VALID_COORD_MARGIN)
#define SHIP_VALID_Y_MAX (3000 + SHIP_VALID_COORD_MARGIN)
#define SHIP_VALID_Y_MIN (1000 - SHIP_VALID_COORD_MARGIN)

#define IS_MINE 1
#define IS_ENEMY 2
#define IS_ALLIED 3
#define IS_UNOWNED 4

#define PLANET_RADIUS 2.5
#define SHIP_RADIUS 1.0
#define HIGHLIGHTED_PLANET_RADIUS 4.0
#define HIGHLIGHTED_SHIP_RADIUS 1.0

#define HIGHLIGHTED_OWNED_PLANET_COLOR "yellow"
#define HIGHLIGHTED_OWNED_SHIP_COLOR "light sky blue"

#define OWNED_PLANET_COLOR "green"
#define PLANET_COLOR "gray60"

#define OWNED_SHIP_COLOR 0x0087ffff
#define SHIP_COLOR 0xff0000ff

#define HIGHLIGHTED_PLANET_COLOR "white"
#define HIGHLIGHTED_SHIP_COLOR "light pink"
#define QUADRANT_GRID_COLOR "gray30"
#define UNIVERSE_COLOR "black"
#define UNIVERSE_COLOR_A 0xffffff00 /* RGBA */

#define PANEL_PLANET_PAGE 0
#define PANEL_SHIP_PAGE 1
#define PANEL_MISC_PAGE 2
#define MOUSE_INTERLEAVE 5
#define SCROLL 20

#define MINI_SC_PAGE 0
#define MINI_PLANET_PAGE 1
#define MINI_SHIP_PAGE 2

#define EXTRA_PANEL_PLANET_PAGE 0
#define EXTRA_PANEL_BASE_PAGE 1
#define EXTRA_PANEL_SHIP_PAGE 2

#define GAME_STATE_VERSION 2

/* Global vars */
GHashTable *planet_list;
GHashTable *base_list;
GHashTable *ship_list;
GHashTable *target_list;
GHashTable *fleet_list;

/* Specs */
GSList *hullspec_list;
GSList *torpspec_list;
GSList *beamspec_list;
GSList *engspec_list;

/* Canvas items */
GSList *planets_per_quad[TOTAL_QUADS];
GSList *ships_per_quad[TOTAL_QUADS];
GSList *locations_per_quad[TOTAL_QUADS];

GList *xyplanet_list;
GList *shipxy_list;

/* Various widgets */
GtkWidget *gwp, *game_mgr, *game_mgr_properties;
GtkWidget *gwp_splash_screen;

/* Is needed by both main.c & support.c */
GladeXML *xml_interface; 

/* GWP structures */
Starchart starchart;
StarchartMini starchart_mini;
GameState *game_state;

/* GConf subsystem */
#define GWP_GCONF_PATH "/apps/gwp/"
GConfClient *gwp_gconf;

#endif
