/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2004 Lucas Di Pentima <lucas@lunix.com.ar>
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

#ifndef GWP_PY_FUNCTIONS_H
#define GWP_PY_FUNCTIONS_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef USE_PYTHON

#include <gnome.h>
#include "gwp-ship.h"
#include "gwp-planet.h"
#include "gwp-game-state.h"

GwpShip * ship_get_by_id (gint id);
GwpPlanet * planet_get_by_id (gint id);
GwpGameState * get_game_state (void);

/************************/
/* Overridden functions */
/************************/
GSList * ship_get_list (void);
GSList * planet_get_list (void);
GSList * hullspec_get_list (void);
GSList * engspec_get_list (void);
GSList * beamspec_get_list (void);
GSList * torpspec_get_list (void);

void set_plugin_mgr(void *);
void * get_plugin_mgr(void);
gchar * get_path_pic_hull(gint nr);

/* FIXME: Does really need to return a void pointer??? */
void * get_truehull(void);
gchar * get_race_name(gint nr);
gchar * get_system_plugins_dir(void);


#endif /* USE_PYTHON */

#endif 
