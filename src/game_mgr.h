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

#define GTK_DISABLE_DEPRECATED
#define GNOME_DISABLE_DEPRECATED

#ifndef GAME_MGR_H
#define GAME_MGR_H

#include <gnome.h>
#include <glade/glade.h>

#include "game_types.h"

void game_mgr_init(void);
GtkWidget *game_mgr_get_properties_dlg(void);

// Specific callbacks
void game_mgr_cb_new_game(GtkWidget *widget, gpointer user_data);
void game_mgr_cb_edit_game(GtkWidget *widget, gpointer iconlist);

void game_mgr_update_race_list(char *dir);
GameSettings *game_mgr_new_settings(void);
void game_mgr_settings_free(GameSettings *s);
void game_mgr_properties_dlg_clean(void);
gboolean game_mgr_properties_dlg_fill(GameSettings *settings);
// icon_number < 0 if not editing or adding a game
gboolean game_mgr_properties_dlg_all_ok(gboolean show_warnings,
					const gint icon_number);
void game_mgr_properties_dlg_get_settings(GameSettings *settings);
void game_mgr_settings_save(const GameSettings *settings);

#endif
