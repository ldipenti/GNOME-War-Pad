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

void game_mgr_init(void)
{
    GtkTreeView *race_list;
    GtkListStore *store;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GSList *games = NULL;
    GameSettings *game;
    gchar *games_path = g_strconcat(GWP_GCONF_PATH, "Games", NULL);
    GnomeIconList *iconlist =
      (GnomeIconList *) lookup_widget("game_mgr_iconlist");
    
    race_list = (GtkTreeView*) lookup_widget("game_mgr_properties_race_list");
    store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Races", 
						      renderer,
						      "text", 0,
						      NULL);
    gtk_tree_view_set_model(race_list, GTK_TREE_MODEL(store));
    gtk_tree_view_append_column(race_list, column);
    // Clear the dialog
    //game_mgr_properties_dlg_clean();

    // Load the games data
    gwp_gconf = gconf_client_get_default();
    games = gconf_client_all_dirs(gwp_gconf, 
				  games_path,
				  NULL);
    // Load the games
    while(games != NULL) {
      game = game_mgr_settings_new();

      // Get the data!
      game->game_name = g_strdup(g_strrstr(games->data, "/"));
      game->game_name++;
      game->game_dir = gconf_client_get_string(gwp_gconf, 
					       g_strconcat(games_path,
							   "/",
							   game->game_name,
							   "/game_dir",
							   NULL),
					       NULL);
      game->trn_dir = gconf_client_get_string(gwp_gconf, 
					      g_strconcat(games_path,
							   "/",
							   game->game_name,
							  "/trn_dir",
							  NULL),
					      NULL);
      game->rst_dir = gconf_client_get_string(gwp_gconf, 
					      g_strconcat(games_path,
							   "/",
							   game->game_name,
							  "/rst_dir",
							  NULL),
					      NULL);
      game->player_email = gconf_client_get_string(gwp_gconf, 
						   g_strconcat(games_path,
							       "/",
							       game->game_name,
							       "/player_email",
							       NULL),
						   NULL);
      game->host_email = gconf_client_get_string(gwp_gconf, 
						 g_strconcat(games_path,
							     "/",
							     game->game_name,
							     "/host_email",
							     NULL),
						 NULL);
      game->host_type = gconf_client_get_int(gwp_gconf,
					     g_strconcat(games_path,
							 "/",
							 game->game_name,
							 "/host_type",
							 NULL),
					     NULL);
      game->race = gconf_client_get_int(gwp_gconf,
					g_strconcat(games_path,
						    "/",
						    game->game_name,
						    "/race",
						    NULL),
					NULL);

      // Add icon to iconlist
      game_mgr_add_icon(iconlist, game);
      
      // Move forward on the list...
      games = games->next;
    }
}

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

    GnomeFileEntry *trn_dir, *rst_dir;
    
    trn_dir = (GnomeFileEntry *) lookup_widget("game_mgr_trn_dir");
    rst_dir = (GnomeFileEntry *) lookup_widget("game_mgr_rst_dir");
    
    // Set default dir to some controls
    gnome_file_entry_set_default_path(trn_dir, dir);
    gnome_file_entry_set_default_path(rst_dir, dir);

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


gboolean game_mgr_properties_dlg_fill(GameSettings *settings)
{
  GtkEntry *game_name = (GtkEntry *)
    lookup_widget("game_mgr_entry_game_name");
  GtkEntry *race_name = (GtkEntry *)
    lookup_widget("game_mgr_entry_race_name");
  GtkEntry *player_email = (GtkEntry *)
    lookup_widget("game_mgr_entry_player_email");
  GtkEntry *host_email = (GtkEntry *)
    lookup_widget("game_mgr_entry_host_email");
  GnomeFileEntry *game_dir = (GnomeFileEntry *)
    lookup_widget("game_mgr_game_dir");
  GnomeFileEntry *trn_dir = (GnomeFileEntry *)
    lookup_widget("game_mgr_trn_dir");
  GnomeFileEntry *rst_dir = (GnomeFileEntry *)
    lookup_widget("game_mgr_rst_dir");
  gchar *game_name_str = g_strdup_printf("%s", settings->game_name);

  game_mgr_game_name_demangle(game_name_str);

  gnome_file_entry_set_filename(game_dir, settings->game_dir);
  gnome_file_entry_set_filename(trn_dir, settings->trn_dir);
  gnome_file_entry_set_filename(rst_dir, settings->rst_dir);

  gtk_entry_set_text(game_name, game_name_str);
  gtk_entry_set_text(player_email, settings->player_email);
  gtk_entry_set_text(host_email, settings->host_email);
  // This MUST be after the game_dir changed event :-)
  gtk_entry_set_text(race_name, race_get_name(settings->race));
  g_object_set_data(G_OBJECT(race_name),
		      "race_number", &settings->race);

  //FIXME: Remember host type!!!
  
  // Do some validations...
  if(game_mgr_properties_dlg_all_ok(FALSE, -1)) {
    return TRUE;
  } else {
    game_mgr_properties_dlg_clean();
    return FALSE;
  }
}


/* Callback function connected to OK button on the game
   properties dialog when using it as an edit game dialog */
void game_mgr_cb_edit_game(GtkWidget *widget, gchar *old_game_name)
{
  GList *selections = NULL;
  GtkWidget *iconlist = lookup_widget("game_mgr_iconlist");
  gint icon_idx;

  g_assert(iconlist != NULL);

  selections = gnome_icon_list_get_selection(GNOME_ICON_LIST(iconlist));
  icon_idx = (gint)g_list_nth_data(selections, 0);
  
  // If validations are ok...
  if(game_mgr_properties_dlg_all_ok(TRUE, icon_idx)) {
    GameSettings *settings = NULL;
    GtkWidget *ok_button = lookup_widget("game_mgr_button_ok");
    GnomeIconTextItem *icon_text = NULL;

    settings = (GameSettings *) 
      gnome_icon_list_get_icon_data(GNOME_ICON_LIST(iconlist),
				    icon_idx);
    g_assert(settings != NULL);
  
    // Assign dialog values to settings structure
    game_mgr_properties_dlg_get_settings(settings);

    // Update it on GConf
    game_mgr_settings_delete(old_game_name);
    game_mgr_settings_save(settings);

    // Update icon name
    icon_text = gnome_icon_list_get_icon_text_item(GNOME_ICON_LIST(iconlist),
						   icon_idx);
    g_assert(GNOME_IS_ICON_TEXT_ITEM(icon_text));
    gnome_icon_text_item_start_editing(icon_text);
    icon_text->text = g_strdup_printf("%s", settings->game_name);
    game_mgr_game_name_demangle(icon_text->text);
    gnome_icon_text_item_stop_editing(icon_text, TRUE);

    // Disconnect signal before releasing dialog
    g_signal_handlers_disconnect_by_func(G_OBJECT(ok_button),
					 G_CALLBACK(game_mgr_cb_edit_game),
					 iconlist);
    gtk_widget_hide(game_mgr_properties);
    game_mgr_properties_dlg_clean();
  }
}

/* Callback function connected to OK button on the game 
   properties dialog when using it as a new game dialog */
void game_mgr_cb_new_game(GtkWidget *widget, gpointer iconlist)
{
  GtkWidget *ok_button = lookup_widget("game_mgr_button_ok");
  gint icon_q;

  icon_q = gnome_icon_list_get_num_icons(iconlist)+1;
  // If validations are ok, we work...
  if(game_mgr_properties_dlg_all_ok(TRUE, icon_q)) {
    GameSettings *new_game = game_mgr_settings_new();

    // Get the data from the dialog
    game_mgr_properties_dlg_get_settings(new_game);

    // Save it on GConf
    game_mgr_settings_save(new_game);

    // Add icon with data
    game_mgr_add_icon(iconlist, new_game);

    // Disconnect signal before releasing dialog
    g_signal_handlers_disconnect_by_func(G_OBJECT(ok_button),
					 G_CALLBACK(game_mgr_cb_new_game),
					 iconlist);
    gtk_widget_hide(game_mgr_properties);
    game_mgr_properties_dlg_clean();
  }
}

void game_mgr_properties_dlg_get_settings(GameSettings *settings)
{
  g_assert(settings != NULL);

  {
    GnomeFileEntry *game_dir = 
      (GnomeFileEntry *) lookup_widget("game_mgr_game_dir");
    GnomeFileEntry *trn_dir = 
      (GnomeFileEntry *) lookup_widget("game_mgr_trn_dir");
    GnomeFileEntry *rst_dir =
      (GnomeFileEntry *) lookup_widget("game_mgr_rst_dir");
    GtkEntry *game_name = 
      (GtkEntry *) lookup_widget("game_mgr_entry_game_name");
    GtkEntry *player_email =
      (GtkEntry *) lookup_widget("game_mgr_entry_player_email");
    GtkEntry *host_email =
      (GtkEntry *) lookup_widget("game_mgr_entry_host_email");
    GtkEntry *race_name =
      (GtkEntry *) lookup_widget("game_mgr_entry_race_name");
    gint *race_num = NULL;
    gchar *name;

    settings->game_dir = gnome_file_entry_get_full_path(game_dir, FALSE);

    name = g_strdup_printf("%s", gtk_entry_get_text(game_name));
    // Tranform "game name" to "game_name"
    game_mgr_game_name_mangle(name);
    settings->game_name = g_strdup_printf("%s", name);

    settings->trn_dir = gnome_file_entry_get_full_path(trn_dir, FALSE);
    settings->rst_dir = gnome_file_entry_get_full_path(rst_dir, FALSE);
    settings->player_email = 
      g_strdup_printf("%s", gtk_entry_get_text(player_email));
    settings->host_email = 
      g_strdup_printf("%s", gtk_entry_get_text(host_email));
    // FIXME: settings->host_type =
    race_num = (gint *) g_object_get_data(G_OBJECT(race_name),
					  "race_number");
    g_assert(race_num != NULL);
    settings->race = *race_num;
  }
}

// Several dialog validations
gboolean game_mgr_properties_dlg_all_ok(gboolean show_warnings,
					const gint icon_number)
{
  GnomeFileEntry *game_dir = 
    (GnomeFileEntry *) lookup_widget("game_mgr_game_dir");
  GtkEntry *game_name = 
    (GtkEntry *) lookup_widget("game_mgr_entry_game_name");
  GtkEntry *race_name =
    (GtkEntry *) lookup_widget("game_mgr_entry_race_name");
  GnomeFileEntry *trn_dir =
    (GnomeFileEntry *) lookup_widget("game_mgr_trn_dir");
  GnomeFileEntry *rst_dir =
    (GnomeFileEntry *) lookup_widget("game_mgr_rst_dir");
  gchar *game_name_str;

  // check if game dir exists
  if(! g_file_test(gnome_file_entry_get_full_path(game_dir, FALSE), 
		   G_FILE_TEST_IS_DIR)) {
    if(show_warnings) {
      GtkWidget *warn;
      
      warn = gtk_message_dialog_new((GtkWindow*) game_mgr_properties,
				    GTK_DIALOG_DESTROY_WITH_PARENT,
				    GTK_MESSAGE_WARNING,
				    GTK_BUTTONS_CLOSE,
				    _("Game directory '%s' doesn't exist"), 
				    gnome_file_entry_get_full_path(game_dir, 
								   FALSE));
      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
    }
    return FALSE;
  }
  // check if there is a game name
  if(strlen(gtk_entry_get_text(game_name)) <= 0) {
    if(show_warnings) {
      GtkWidget *warn;
      
      warn = gtk_message_dialog_new((GtkWindow*) game_mgr_properties,
				    GTK_DIALOG_DESTROY_WITH_PARENT,
				    GTK_MESSAGE_WARNING,
				    GTK_BUTTONS_CLOSE,
				    _("Please provide a name for this game"));
      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
    }
    return FALSE;
  }
  // check if game name is not duplicated
  game_name_str = g_strdup_printf("%s", gtk_entry_get_text(game_name));
  game_mgr_game_name_mangle(game_name_str);
  if(icon_number >= 0) {
    GnomeIconList *iconlist =
      (GnomeIconList *) lookup_widget("game_mgr_iconlist");
    GameSettings *sett;
    gint i, icon_q;

    // Iterate through all games except the one being edited
    icon_q = gnome_icon_list_get_num_icons(iconlist);
    for(i = 0; i < icon_q; i++) {
      if(i != icon_number) {
	sett = (GameSettings *) 
	  gnome_icon_list_get_icon_data(GNOME_ICON_LIST(iconlist),
					i);
	g_assert(sett != NULL);

	// If strings are equal...
	if(g_ascii_strncasecmp(sett->game_name, 
			       game_name_str,
			       strlen(game_name_str)) == 0) {
	  GtkWidget *warn;
	  
	  warn = gtk_message_dialog_new((GtkWindow*) game_mgr_properties,
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_WARNING,
					GTK_BUTTONS_CLOSE,
					_("A game named '%s' already exist, please select another name"),
					gtk_entry_get_text(game_name));
	  gtk_dialog_run(GTK_DIALOG(warn));
	  gtk_widget_destroy(warn);
	  
	  return FALSE;
	}
      }
    }
  }
  // check if user selected a race
  if(strlen(gtk_entry_get_text(race_name)) <= 0) {
    if(show_warnings) {
      GtkWidget *warn;
      
      warn = gtk_message_dialog_new((GtkWindow*) game_mgr_properties,
				    GTK_DIALOG_DESTROY_WITH_PARENT,
				    GTK_MESSAGE_WARNING,
				    GTK_BUTTONS_CLOSE,
				    _("Please select a race"));
      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
    }
    return FALSE;
  }

  // auto-validations
  if(! gnome_file_entry_get_full_path(trn_dir, FALSE)) {
    gnome_file_entry_set_filename(trn_dir,
				  gnome_file_entry_get_full_path(game_dir,
								 FALSE));
  }

  if(! gnome_file_entry_get_full_path(rst_dir, FALSE)) {
    gnome_file_entry_set_filename(rst_dir,
				  gnome_file_entry_get_full_path(game_dir,
								 FALSE));
  }

  // All ok!, lets continue...
  return TRUE;
}

// Returns a GameSettings pointer with initializated data
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

void game_mgr_settings_save(const GameSettings *settings)
{
  gchar *path = g_strconcat(GWP_GCONF_PATH"Games/",
			    settings->game_name,
			    "/", NULL);

  g_assert(settings != NULL);

  gconf_client_set_string(gwp_gconf, g_strconcat(path,"player_email",NULL),
			  settings->player_email, NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"host_email",NULL),
			  settings->host_email, NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"game_dir",NULL),
			  settings->game_dir, NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"trn_dir",NULL),
			  settings->trn_dir, NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"rst_dir",NULL),
			  settings->rst_dir, NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"host_type",NULL),
		       settings->host_type, NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"race",NULL),
		       settings->race, NULL);
}

void game_mgr_add_icon(GnomeIconList *iconlist, GameSettings *sett)
{
  gint icon_idx;
  gchar *game_name = g_strdup_printf("%s", sett->game_name);

  game_mgr_game_name_demangle(game_name);

  // Add new game icon, with data
  icon_idx = gnome_icon_list_append(GNOME_ICON_LIST(iconlist),
				    GWP_ICONS_DIR"/game_icon.png",
				    game_name);
  gnome_icon_list_set_icon_data(GNOME_ICON_LIST(iconlist),
				icon_idx,
				sett);
}

// For debugging purposes
void game_mgr_settings_print_data (GameSettings *s)
{
  g_assert(s != NULL);

  g_message("Game Name: '%s'", s->game_name);
  g_message("Game Dir: '%s'", s->game_dir);
  g_message("TRN Dir: '%s'", s->trn_dir);
  g_message("RST DIR: '%s'", s->rst_dir);
  g_message("Player Email: '%s'", s->player_email);
  g_message("Host Email: '%s'", s->host_email);
  g_message("Host Type: '%d' - Race: '%d'", s->host_type, s->race);
}

// Deletes GConf Game entry...
void game_mgr_settings_delete(const gchar *name)
{
  GSList *games;
  gchar *tmp, *tmp_path;
  gchar *games_path = g_strconcat(GWP_GCONF_PATH, "Games", NULL);
 
  games = gconf_client_all_dirs(gwp_gconf, 
				games_path,
				NULL);
  // Search within the games
  while(games != NULL) {
    tmp = g_strdup(g_strrstr(games->data, "/"));
    tmp++;

    // If this is the entry we are looking for...
    if(g_ascii_strncasecmp(tmp, name,strlen(name)) == 0) {
      tmp_path = g_strconcat(games_path, "/", tmp, "/", NULL);

      // bye bye entries!
      gconf_client_unset(gwp_gconf, 
			 g_strconcat(tmp_path, "game_name", NULL),
			 NULL);
      gconf_client_unset(gwp_gconf, 
			 g_strconcat(tmp_path, "game_dir", NULL),
			 NULL);
      gconf_client_unset(gwp_gconf, 
			 g_strconcat(tmp_path, "trn_dir", NULL),
			 NULL);
      gconf_client_unset(gwp_gconf, 
			 g_strconcat(tmp_path, "rst_dir", NULL),
			 NULL);
      gconf_client_unset(gwp_gconf, 
			 g_strconcat(tmp_path, "player_email", NULL),
			 NULL);
      gconf_client_unset(gwp_gconf, 
			 g_strconcat(tmp_path, "host_email", NULL),
			 NULL);
      gconf_client_unset(gwp_gconf, 
			 g_strconcat(tmp_path, "host_type", NULL),
			 NULL);
      gconf_client_unset(gwp_gconf, 
			 g_strconcat(tmp_path, "race", NULL),
			 NULL);
      return;
    }
    games = games->next;
  }
}

// Translates ' ' to '_'
void game_mgr_game_name_mangle(gchar *name)
{
  gchar *ptr;

  if(!name) return;
  ptr = name;

  while(*ptr) {
    if(g_ascii_isspace(*ptr)) *ptr = '_';
    ptr++;
  }
}

// Translates '_' to ' '
void game_mgr_game_name_demangle(gchar *name)
{
  gchar *ptr;

  if(!name) return;
  ptr = name;

  while(*ptr) {
    if(*ptr == '_') *ptr = ' ';
    ptr++;
  }
}
