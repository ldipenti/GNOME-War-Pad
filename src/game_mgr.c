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

#include <gnome.h>
#include "global.h"
#include "support.h"
#include "game_mgr.h"
#include "game_state.h"
#include "game_types.h"
#include "race.h"

void game_mgr_update_race_list(char *dir) 
{
  GString *pdata, *ship;
  GtkTreeView *race_list;
  GtkListStore *store;
  GtkTreeIter iter;
  gint i;

  race_list = (GtkTreeView*) lookup_widget("game_mgr_properties_race_list");
  store = (GtkListStore*) gtk_tree_view_get_model(race_list);
  g_assert(store != NULL);
  gtk_list_store_clear(store);

  // If dir exists, we work
  if(g_file_test(dir, G_FILE_TEST_IS_DIR)) {

    for (i = 1; i <= 11; i++) {
      pdata = g_string_new ("pdata");
      ship = g_string_new ("ship");

      pdata = g_string_append (pdata, 
			       g_strdup_printf ("%d.dis", i));
      ship = g_string_append (ship,
			      g_strdup_printf ("%d.dis", i));

      pdata = g_string_prepend(pdata, dir);
      ship = g_string_prepend(ship, dir);
    
      // shipN.dis or pdataN.dis should exist...
      if (g_file_test(pdata->str, G_FILE_TEST_IS_REGULAR) || 
	  g_file_test(ship->str, G_FILE_TEST_IS_REGULAR)) {
	
	// Add available races to race list
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 
			   0, g_strdup_printf("%s", race_get_name(i)),
			   1, i,    // invisible column with race number
			   -1);	
      }
      g_string_free(pdata, TRUE);
      g_string_free(ship, TRUE);
    }    
  }
}

/* Callback function connected to OK button on the game 
   properties dialog when using it as a new game dialog */
void game_mgr_cb_new_game(GtkWidget *widget, gpointer iconlist)
{
  GameSettings *new_game = game_mgr_new_settings();
  GnomeFileEntry *game_dir = 
    (GnomeFileEntry *) lookup_widget("game_mgr_game_dir");
  GtkEntry *entry;
  GtkWidget *ok_button = lookup_widget("game_mgr_button_ok");
  gint icon_idx;

  g_assert(game_dir != NULL);
  new_game->game_dir = gnome_file_entry_get_full_path(game_dir, FALSE);

  // If that dir exists...
  if(g_file_test(new_game->game_dir, G_FILE_TEST_IS_DIR)) {
    entry = (GtkEntry *) lookup_widget("game_mgr_entry_game_name");
    new_game->game_name = g_strdup_printf("%s", gtk_entry_get_text(entry));

    /* FIXME: completeeee
      new_game->trn_dir =
      new_game->rst_dir =
      new_game->player_email =
      new_game->host_email =
      new_game->host_type =
      new_game->race =
    */

    // Add new game icon, with data
    icon_idx = gnome_icon_list_append(GNOME_ICON_LIST(iconlist),
				      GWP_ICONS_DIR"/game_icon.png",
				      new_game->game_name);
    gnome_icon_list_set_icon_data(GNOME_ICON_LIST(iconlist),
				  icon_idx,
				  new_game);

    
    // Disconnect signal before releasing dialog
    g_signal_handlers_disconnect_by_func(G_OBJECT(ok_button),
					 G_CALLBACK(game_mgr_cb_new_game),
					 iconlist);
    gtk_widget_hide(game_mgr_properties);
    game_mgr_properties_dlg_clean();
  } else {
    {
      GtkWidget *warn;

      warn = gtk_message_dialog_new((GtkWindow*) game_mgr_properties,
				    GTK_DIALOG_DESTROY_WITH_PARENT,
				    GTK_MESSAGE_WARNING,
				    GTK_BUTTONS_CLOSE,
				    "Game directory '%s' doesn't exist", 
				    new_game->game_dir);
      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
    }
  }
}

// Returns a GameSettings pointer with initializated data
GameSettings *game_mgr_new_settings(void)
{
  GameSettings *ret;

  ret = g_malloc(sizeof(GameSettings));

  ret->game_dir = NULL;
  ret->game_name = NULL;
  ret->trn_dir = NULL;
  ret->rst_dir = NULL;
  ret->player_email = NULL;
  ret->host_email = NULL;
  ret->host_type = 0;
  ret->race = 0;

  return ret;
}

void game_mgr_properties_dlg_clean(void)
{
  GtkEntry *entry;
  GnomeFileEntry *fentry;
  GtkTreeView *race_list;
  GtkListStore *store;

  race_list = (GtkTreeView*) lookup_widget("game_mgr_properties_race_list");
  store = (GtkListStore*) gtk_tree_view_get_model(race_list);
  g_assert(store != NULL);
  gtk_list_store_clear(store);
  
  entry = (GtkEntry *) lookup_widget("game_mgr_entry_game_name");
  gtk_entry_set_text(entry, "");

  entry = (GtkEntry *) lookup_widget("game_mgr_entry_race_name");
  gtk_entry_set_text(entry, "");

  entry = (GtkEntry *) lookup_widget("game_mgr_entry_player_email");
  gtk_entry_set_text(entry, "");

  entry = (GtkEntry *) lookup_widget("game_mgr_entry_host_email");
  gtk_entry_set_text(entry, "");

  fentry = (GnomeFileEntry *) lookup_widget("game_mgr_trn_dir");
  gnome_file_entry_set_filename(fentry, "");

  fentry = (GnomeFileEntry *) lookup_widget("game_mgr_rst_dir");
  gnome_file_entry_set_filename(fentry, "");

  fentry = (GnomeFileEntry *) lookup_widget("game_mgr_game_dir");
  gnome_file_entry_set_filename(fentry, "");
}
