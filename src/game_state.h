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

/*
 * Game state data type, this will be used to store all 
 * the global info that will be needed during the game.
 */
typedef struct _GameState GameState;
struct _GameState
{
  gdouble starchart_zoom;
  gint16 last_x_coord;
  gint16 last_y_coord;
  GString * dir;
  gint race;
  gchar *name;
};

void game_set_dir (gchar * dir);
GString *game_get_dir (void);
GString *game_get_full_path (GString * filename);
void game_init_dir (gchar * dir);

void game_set_starchart_zoom (gdouble zoom);
gdouble game_get_starchart_zoom (void);

void game_set_race (gint race_num);
gint game_get_race (void);

gint16 game_get_last_x_coord(void);
gint16 game_get_last_y_coord(void);
void game_set_last_coords(gint16 x, gint16 y);

void game_set_name (const gchar *name);
const gchar *game_get_name (void);

#endif
