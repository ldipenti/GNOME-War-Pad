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

#include <gnome.h>

#include "global.h"

/************** STARCHART MINI *************/

GnomeCanvas * starchart_mini_get_canvas(void)
{
  return starchart_mini.canvas;
}

void starchart_mini_set_canvas(GnomeCanvas * canvas)
{
  starchart_mini.canvas = canvas;
}

GnomeCanvasGroup * starchart_mini_get_grp_root(void)
{
  return starchart_mini.grp_root;
}

void starchart_mini_set_grp_root(GnomeCanvasGroup * group)
{
  starchart_mini.grp_root = group;
}

GnomeCanvasItem * starchart_mini_get_zone(void)
{
  return starchart_mini.zone;
}

void starchart_mini_set_zone(GnomeCanvasItem * zone)
{
  starchart_mini.zone = zone;
}


/******** STARCHART *********/

GnomeCanvas * starchart_get_canvas(void)
{
  return starchart.canvas;
}

void starchart_set_canvas(GnomeCanvas * canvas)
{
  starchart.canvas = canvas;
}

GnomeCanvasGroup * starchart_get_grp_root(void)
{
  return starchart.grp_root;
}

void starchart_set_grp_root(GnomeCanvasGroup * group)
{
  starchart.grp_root = group;
}

GnomeCanvasGroup * starchart_get_grp_grid(void)
{
  return starchart.grp_grid;
}

void starchart_set_grp_grid(GnomeCanvasGroup * group)
{
  starchart.grp_grid = group;
}

GnomeCanvasGroup * starchart_get_grp_planets(void)
{
  return starchart.grp_planets;
}

void starchart_set_grp_planets(GnomeCanvasGroup * group)
{
  starchart.grp_planets = group;
}

GnomeCanvasGroup * starchart_get_grp_planets_mine(void)
{
  return starchart.grp_planets_mine;
}

void starchart_set_grp_planets_mine(GnomeCanvasGroup * group)
{
  starchart.grp_planets_mine = group;
}

GnomeCanvasGroup * starchart_get_grp_planets_enemy(void)
{
  return starchart.grp_planets_enemy;
}

void starchart_set_grp_planets_enemy(GnomeCanvasGroup * group)
{
  starchart.grp_planets_enemy = group;
}

GnomeCanvasGroup * starchart_get_grp_planets_allied(void)
{
  return starchart.grp_planets_allied;
}

void starchart_set_grp_planets_allied(GnomeCanvasGroup * group)
{
  starchart.grp_planets_allied = group;
}

GnomeCanvasGroup * starchart_get_grp_ships_mine(void)
{
  return starchart.grp_ships_mine;
}

void starchart_set_grp_ships_mine(GnomeCanvasGroup * group)
{
  starchart.grp_ships_mine = group;
}

GnomeCanvasGroup * starchart_get_grp_ships_enemy(void)
{
  return starchart.grp_ships_enemy;
}

void starchart_set_grp_ships_enemy(GnomeCanvasGroup * group)
{
  starchart.grp_ships_enemy = group;
}

GnomeCanvasGroup * starchart_get_grp_ships_allied(void)
{
  return starchart.grp_ships_allied;
}

void starchart_set_grp_ships_allied(GnomeCanvasGroup * group)
{
  starchart.grp_ships_allied = group;
}

void starchart_set_grid(gboolean state)
{
  starchart.grid = state;
}

gboolean starchart_get_grid(void)
{
  return starchart.grid;
}

gboolean starchart_toggle_grid(void)
{
  gboolean res;
  
  if(starchart_get_grid() == TRUE) {
    res = FALSE;
    starchart_set_grid(res);
    gnome_canvas_item_hide((GnomeCanvasItem *) starchart_get_grp_grid());
  } else {
    res = TRUE;
    starchart_set_grid(res);
    gnome_canvas_item_show((GnomeCanvasItem *) starchart_get_grp_grid());
  }
  return res;
}

/* Returns a GameSettings pointer with initializated data */
GameSettings *game_mgr_settings_new(void)
{
  GameSettings *ret;

  ret = g_malloc(sizeof(GameSettings));

  ret->game_dir = NULL;
  ret->game_name = NULL;
  ret->trn_dir = "";
  ret->rst_dir = "";
  ret->player_email = "";
  ret->host_email = "";
  ret->host_type = 0;
  ret->race = 0;

  return ret;
}

/* Free GameSettings components to release memory */
void game_mgr_settings_free(GameSettings *s) 
{
  g_assert(s != NULL);

  g_free(s->game_dir);
  /* FIXME: When this is tried to be freed, the app hangs 
     (when deleting loaded icons from gconf)
     g_free(s->game_name);
  */
  g_free(s->trn_dir);
  g_free(s->rst_dir);
  g_free(s->player_email);
  g_free(s->host_email);
  g_free(s);
}
