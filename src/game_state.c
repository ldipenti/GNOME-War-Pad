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

#include "global.h"
#include "vp_types.h"
#include "game_state.h"
#include "game_mgr.h"

/*
 * Accessor functions to different members of GameState
 */

void game_set_name (const gchar *name)
{
  gchar *real_name;

  real_name = g_strdup(name);
  game_mgr_game_name_demangle(real_name);
  game_state.name = real_name;
}

const gchar *game_get_name (void)
{
  return game_state.name;
}
 
void game_set_dir(gchar *dir) {
  game_state.dir = g_string_assign(game_state.dir, dir);
  game_state.dir = g_string_append(game_state.dir, "/");
}

GString* game_get_dir(void) {
	return game_state.dir;
}

GString* game_get_full_path(GString *filename) {
    GString *tmp;
    
    tmp = g_string_new(game_get_dir()->str);
    return g_string_append(tmp, filename->str);
}

void game_init_dir(gchar *dir) {
	game_state.dir = g_string_new(dir);
}

void game_set_starchart_zoom(gdouble zoom) {
	game_state.starchart_zoom = zoom;
}
gdouble game_get_starchart_zoom(void) {
	return game_state.starchart_zoom;
}

void game_set_race(gint race_num) 
{
  if((race_num > 0) && (race_num <= 11)) {
    game_state.race = race_num;
  }
}

enum races game_get_race(void) 
{
  return game_state.race;
}

gint16 game_get_last_x_coord(void)
{
    return game_state.last_x_coord;
}

gint16 game_get_last_y_coord(void)
{
    return game_state.last_y_coord;
}

void game_set_last_coords(gint16 x, gint16 y)
{
    //g_return_if_fail(FIXME: Check coordinates!!!);
    game_state.last_x_coord = x;
    game_state.last_y_coord = y;
}

void game_set_pnames(GList *pnames)
{
  game_state.pnames = pnames;
}

GList *game_get_pnames(void)
{
  return game_state.pnames;
}

void game_set_turn_number(gint turn)
{
  game_state.turn_number = turn;
}

gint game_get_turn_number(void)
{
  return game_state.turn_number;
}
