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

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <gnome.h>

#include "race.h"

/*******************************************/
/************** GAME SETTINGS **************/
/*******************************************/

/*
 * This structure is for the game manager to store
 * every game's information that later will save on
 * GConf.
 */
typedef struct _GameSettings GameSettings;
struct _GameSettings {
  gchar *game_dir, *game_name, *trn_dir, *rst_dir;
  gchar *player_email, *host_email;
  gint host_type; // 1=THost ; 2=PHost
  gint race;
};

GameSettings *game_settings_new(void);
void game_settings_free(GameSettings *s);
void game_settings_save(const GameSettings *settings);

/*******************************************/
/**************** GAME STATE ***************/
/*******************************************/

/*
 * Game state data type, this will be used to store all 
 * the global info that will be needed during the game.
 */
typedef struct _GameState GameState;
struct _GameState
{
  gdouble starchart_zoom;
  gint turn_number;
  gint16 last_x_coord;
  gint16 last_y_coord;
  GList *pnames;
  gboolean toolbar;
  gboolean extra_panel_open;
  gboolean planet_names;
  GameSettings *settings;
};

GameState *game_state_new(void);
void game_state_free(GameState *gstate);

/* Accesors */
void game_set_dir (GameState *game_state, gchar * dir);
gchar *game_get_dir(const GameState *game_state);
gchar *game_get_full_path(const GameState *game_state, gchar *filename);

void game_set_starchart_zoom (GameState *game_state, gdouble zoom);
gdouble game_get_starchart_zoom (const GameState *game_state);

void game_set_race (GameState *game_state, gint race_num);
enum races game_get_race (const GameState *game_state);

gint16 game_get_last_x_coord(const GameState *game_state);
void game_set_last_x_coord(GameState *game_state, gint y);
gint16 game_get_last_y_coord(const GameState *game_state);
void game_set_last_y_coord(GameState *game_state, gint y);
void game_set_last_coords(GameState *game_state, gint16 x, gint16 y);

void game_set_name (GameState *game_state, const gchar *name);
const gchar *game_get_name (const GameState *game_state);

GList *game_get_pnames(GameState *game_state);
void game_set_pnames(GameState *game_state, GList *pnames);

void game_set_turn_number(GameState *game_state, gint turn);
gint game_get_turn_number(const GameState *game_state);

void game_state_save(const GameState *state);
void game_state_delete(const gchar *name);

void game_set_player_email(GameState *game_state, gchar *pe);
gchar *game_get_player_email(const GameState *game_state);
void game_set_host_email(GameState *game_state, gchar *he);
gchar *game_get_host_email(const GameState *game_state);
void game_set_trn_dir(GameState *game_state, gchar *td);
gchar *game_get_trn_dir(const GameState *game_state);
void game_set_rst_dir(GameState *game_state, gchar *rt);
gchar *game_get_rst_dir(const GameState *game_state);
gint game_get_host_type(const GameState *game_state);
void game_set_host_type(GameState *game_state, gint ht);
gboolean game_get_toolbar(const GameState *game_state);
void game_set_toolbar(GameState *game_state, gboolean tb);
gboolean game_is_extra_panel_open (const GameState *game_state);
void game_set_extra_panel_open (GameState *game_state, gboolean is_open);
void game_state_set_planet_names (GameState *game_state, gboolean show);
gboolean game_state_get_planet_names (const GameState *game_state);

void game_close(GameState *game_state);
gint game_state_get_version(void);
void game_state_set_version(gint version);

#endif
