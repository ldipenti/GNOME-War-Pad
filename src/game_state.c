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

/*
 * This encapsulate game state values that need to be accesible
 * during the execution of the program
 */
 
#include <gnome.h>
#include <string.h>

#include "global.h"
#include "vp_types.h"
#include "gwp_types.h"
#include "game_state.h"
#include "game_mgr.h"

void destroy_gobject (gpointer key, gpointer value, gpointer user_data);


/*******************************************/
/************** GAME SETTINGS **************/
/*******************************************/

/* Returns a GameSettings pointer with initialized data */
GameSettings *game_settings_new(void)
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
void game_settings_free(GameSettings *s) 
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

/*
 * Accessor functions to different members of GameSettings
 */

/*******************************************/
/**************** GAME STATE ***************/
/*******************************************/

/* Returns a GameState pointer with initialized data */
GameState *game_state_new(void)
{
  GameState *ret;

  ret = g_malloc(sizeof(GameState));

  ret->starchart_zoom = 1.0;
  ret->last_x_coord = 0;
  ret->last_y_coord = 0;
  ret->turn_number = 0;
  ret->pnames = NULL;
  ret->toolbar = TRUE;
  ret->extra_panel_open = FALSE;
  ret->planet_names = TRUE;
  ret->minefields = TRUE;
  ret->ion_storms = TRUE;
  ret->settings = game_settings_new();
  
  return ret;
}

/* Free GameState components to release memory */
void game_state_free(GameState *gstate)
{
  g_assert(gstate != NULL);

  g_list_free(gstate->pnames);
  game_settings_free(gstate->settings);
  g_free(gstate);
}

/*
 * Accessor functions to different members of GameState
 */

void game_set_name (GameState *game_state, const gchar *name)
{
  gchar *real_name;

  g_assert(game_state != NULL);
  real_name = g_strdup(name);
  game_mgr_game_name_demangle(real_name);
  game_state->settings->game_name = real_name;
}

const gchar *game_get_name (const GameState *game_state)
{
  g_assert(game_state != NULL);

  return game_state->settings->game_name;
}
 
void game_set_dir(GameState *game_state, gchar *dir) {
  g_assert(game_state != NULL);

  game_state->settings->game_dir = g_strdup(dir);
}

gchar* game_get_dir(const GameState *game_state) 
{
  g_assert(game_state != NULL);

  return game_state->settings->game_dir;
}

gchar* game_get_full_path(const GameState *game_state, gchar *filename) 
{
  g_assert(game_state != NULL);
  
  return g_strconcat(game_get_dir(game_state), "/", filename, NULL);
}

void game_set_starchart_zoom(GameState *game_state, gdouble zoom) 
{
  g_assert(game_state != NULL);

  game_state->starchart_zoom = zoom;
}

gdouble game_get_starchart_zoom(const GameState *game_state) 
{
  g_assert(game_state != NULL);

  return game_state->starchart_zoom;
}

void game_set_race(GameState *game_state, gint race_num) 
{
  g_assert(game_state != NULL);

  if((race_num > 0) && (race_num <= 11)) {
    game_state->settings->race = race_num;
  }
}

enum races game_get_race(const GameState *game_state) 
{
  g_assert(game_state != NULL);
  return game_state->settings->race;
}

gint game_get_race_nr (const GameState *game_state) 
{
  g_assert(game_state != NULL);
  return game_state->settings->race;
}

void game_set_last_x_coord(GameState *game_state, gint x)
{
  g_assert(game_state != NULL);

  game_state->last_x_coord = x;
}

gint16 game_get_last_x_coord(const GameState *game_state)
{
  g_assert(game_state != NULL);

  return game_state->last_x_coord;
}

void game_set_last_y_coord(GameState *game_state, gint y)
{
  g_assert(game_state != NULL);

  game_state->last_y_coord = y;
}

gint16 game_get_last_y_coord(const GameState *game_state)
{
  g_assert(game_state != NULL);

  return game_state->last_y_coord;
}

void game_set_last_coords(GameState *game_state, gint16 x, gint16 y)
{
  g_assert(game_state != NULL);

  //g_return_if_fail(FIXME: Check coordinates!!!);
  game_state->last_x_coord = x;
  game_state->last_y_coord = y;
}

void game_set_pnames(GameState *game_state, GList *pnames)
{
  g_assert(game_state != NULL);

  game_state->pnames = pnames;
}

GList *game_get_pnames(GameState *game_state)
{
  g_assert(game_state != NULL);

  return game_state->pnames;
}

void game_set_turn_number(GameState *game_state, gint turn)
{
  g_assert(game_state != NULL);

  game_state->turn_number = turn;
}

gint game_get_turn_number(const GameState *game_state)
{
  g_assert(game_state != NULL);

  return game_state->turn_number;
}

void game_set_player_email(GameState *game_state, gchar *pe)
{
  g_assert(game_state != NULL);

  game_state->settings->player_email = g_strdup(pe);
}

gchar *game_get_player_email(const GameState *game_state)
{
  g_assert(game_state != NULL);
  
  return game_state->settings->player_email;
}

void game_set_host_email(GameState *game_state, gchar *he)
{
  g_assert(game_state != NULL);

  game_state->settings->host_email = g_strdup(he);
}

gchar *game_get_host_email(const GameState *game_state)
{
  g_assert(game_state != NULL);
  
  return game_state->settings->host_email;
}

void game_set_trn_dir(GameState *game_state, gchar *td)
{
  g_assert(game_state != NULL);

  game_state->settings->trn_dir = g_strdup(td);
}

gchar *game_get_trn_dir(const GameState *game_state)
{
  g_assert(game_state != NULL);

  return game_state->settings->trn_dir;
}

void game_set_rst_dir(GameState *game_state, gchar *rt)
{
  g_assert(game_state != NULL);

  game_state->settings->rst_dir = g_strdup(rt);
}

gchar *game_get_rst_dir(const GameState *game_state)
{
  g_assert(game_state != NULL);

  return game_state->settings->rst_dir;
}

void game_set_host_type(GameState *game_state, gint ht)
{
  g_assert(game_state != NULL);

  game_state->settings->host_type = ht;
}

gint game_get_host_type(const GameState *game_state)
{
  g_assert(game_state != NULL);
  
  return game_state->settings->host_type;
}

gboolean game_get_planet_names (const GameState *game_state)
{
  g_assert (game_state != NULL);
  return game_state->planet_names;
}

void game_set_planet_names (GameState *game_state, gboolean show)
{
  g_assert (game_state != NULL);
  game_state->planet_names = show;
}

gboolean game_get_scanner_area (const GameState *game_state)
{
  g_assert (game_state != NULL);
  return game_state->scanner_area;
}

void game_set_scanner_area (GameState *game_state, gboolean show)
{
  g_assert (game_state != NULL);
  game_state->scanner_area = show;
}

gboolean game_get_minefields (const GameState *game_state)
{
  g_assert (game_state != NULL);
  return game_state->minefields;
}

void game_set_minefields (GameState *game_state, gboolean show)
{
  g_assert (game_state != NULL);
  game_state->minefields = show;
}

gboolean game_get_ion_storms (const GameState *game_state)
{
  g_assert (game_state != NULL);
  return game_state->ion_storms;
}

void game_set_ion_storms (GameState *game_state, gboolean show)
{
  g_assert (game_state != NULL);
  game_state->ion_storms = show;
}

gboolean game_is_extra_panel_open (const GameState *game_state)
{
  g_assert (game_state != NULL);

  return game_state->extra_panel_open;
}

void game_set_extra_panel_open (GameState *game_state, gboolean is_open)
{
  g_assert (game_state != NULL);

  game_state->extra_panel_open = is_open;
}

gboolean game_get_toolbar(const GameState *game_state)
{
  g_assert(game_state != NULL);

  return game_state->toolbar;
}

void game_set_toolbar(GameState *game_state, gboolean tb)
{
  g_assert(game_state != NULL);

  game_state->toolbar = tb;
}

/* FIXME: delete this */
void game_set_f_key (GameState *self, PyObject *fun)
{
  g_assert(self != NULL);
  g_assert(fun != NULL);

  self->f_key = fun;
}
PyObject *game_get_f_key (GameState *self)
{
  g_assert(self);

  return self->f_key;
}
/*******delete!!!******/

/* Save game state on GConf */
void game_state_save(const GameState *state)
{
  g_assert(state != NULL);

  {
    gchar *name = g_strdup(game_get_name(state));
    gchar *path;

    game_mgr_game_name_mangle(name);
    path = g_strconcat(GWP_GCONF_PATH"Games/",
			      name,
			      "/", NULL);

    /* GameState data */
    gconf_client_set_float(gwp_gconf, g_strconcat(path,"starchart_zoom", NULL),
			   game_get_starchart_zoom(state), NULL);
    gconf_client_set_int(gwp_gconf, g_strconcat(path,"turn_number",NULL),
			 game_get_turn_number(state), NULL);
    gconf_client_set_int(gwp_gconf, g_strconcat(path,"last_x_coord",NULL),
			 game_get_last_x_coord(state), NULL);
    gconf_client_set_int(gwp_gconf, g_strconcat(path,"last_y_coord",NULL),
			 game_get_last_y_coord(state), NULL);

    /* GameSettings data */
    gconf_client_set_string(gwp_gconf, g_strconcat(path,"player_email",NULL),
			    game_get_player_email(state), NULL);
    gconf_client_set_string(gwp_gconf, g_strconcat(path,"host_email",NULL),
			    game_get_host_email(state), NULL);
    gconf_client_set_string(gwp_gconf, g_strconcat(path,"game_dir",NULL),
			    game_get_dir(state), NULL);
    gconf_client_set_string(gwp_gconf, g_strconcat(path,"trn_dir",NULL),
			    game_get_trn_dir(state), NULL);
    gconf_client_set_string(gwp_gconf, g_strconcat(path,"rst_dir",NULL),
			    game_get_rst_dir(state), NULL);
    gconf_client_set_int(gwp_gconf, g_strconcat(path,"host_type",NULL),
			 game_get_host_type(state), NULL);
    gconf_client_set_int(gwp_gconf, g_strconcat(path,"race",NULL),
			 game_get_race(state), NULL);
    gconf_client_set_bool(gwp_gconf, g_strconcat(path,"toolbar",NULL),
			  game_get_toolbar(state), NULL);
  }
}

/* Deletes GConf Game entry... */
void game_state_delete(const gchar *name)
{
  GSList *games, *entries, *p;
  gchar *tmp, *tmp_path;
  gchar *games_path = g_strconcat(GWP_GCONF_PATH, "Games", NULL);
 
  games = gconf_client_all_dirs(gwp_gconf, games_path, NULL);

  /* Search within the games */
  while(games != NULL) {
    tmp = g_strdup(g_strrstr(games->data, "/"));
    tmp++;

    /* If this is the entry we are looking for... */
    if(g_ascii_strncasecmp(tmp, name,strlen(name)) == 0) {
      tmp_path = g_strconcat(games_path, "/", tmp, NULL);

      /********************/
      /* bye bye entries! */
      /********************/
      entries = gconf_client_all_entries(gwp_gconf, tmp_path, NULL);

      for(p=entries; p; p=p->next) {
	GConfEntry *ent = (GConfEntry *)p->data;
	gconf_client_unset(gwp_gconf, ent->key, NULL);
      }
      g_slist_free(entries);

      return;
    }
    games = games->next;
  }
}

/* Updates all data, call this before quitting or opening another game */
void game_close(GameState *game_state)
{
  if(game_state) {
    gint x, y;

    /* Save game state */
    gnome_canvas_get_scroll_offsets(starchart_get_canvas(), &x, &y);
    game_set_last_coords(game_state, x, y);
    game_state_save(game_state);

    /******************************/
    /* Clean up objects in memory */
    /******************************/
    
    /* Eliminate planets and ships from memory*/
    g_hash_table_foreach (planet_list, (GHFunc) destroy_gobject, NULL);
    g_hash_table_destroy (planet_list);

    g_hash_table_foreach (ship_list, (GHFunc) destroy_gobject, NULL);
    g_hash_table_destroy (ship_list);

    /* FIXME!!! cleanup code is buggy! */
  }
}

/* Internal function to destroy GObjects from a HashTable */
void destroy_gobject (gpointer key, gpointer value, gpointer user_data)
{
  g_object_unref (G_OBJECT(value));
}

/* Returns the format version number */
gint game_state_get_version(void)
{
  gint ret = 0;
  ret = gconf_client_get_int(gwp_gconf, 
			     g_strconcat(GWP_GCONF_PATH, "version", NULL),
			     NULL);
  return ret;
}

void game_state_set_version(gint version)
{
  gconf_client_set_int(gwp_gconf, 
		       g_strconcat(GWP_GCONF_PATH, "version", NULL),
		       version,
		       NULL);
}
