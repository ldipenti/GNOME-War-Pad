/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002,2003 Lucas Di Pentima <lucas@lunix.com.ar>
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

/* This should be the first include, because of the Python.h */
#ifdef USE_PYTHON
#  include "gwp-python.h"
#endif

#include <gnome.h>
#include <string.h>

#include "global.h"
#include "support.h"
#include "game_mgr.h"
#include "gwp-game-state.h"
#include "vp_utils.h"
#include "starchart.h"
#include "race.h"
#include "vp_unpack.h"
#include "gwp-utils.h"

static void game_mgr_init_message_history (void);
static void destroy_gobject_ht (gpointer key, gpointer value, gpointer user_data);
static void destroy_gobject_sl (gpointer value, gpointer user_data);
static gint game_state_get_version(void);
static void game_state_set_version(gint version);

void game_mgr_init(void)
{
    GtkTreeView *race_list;
    GtkListStore *store;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GnomeAppBar *appbar;
    GSList *games = NULL;
    GwpGameState *game;
    gchar *games_path = g_strconcat(GWP_GCONF_PATH, "Games", NULL);
    gchar *name_tmp = NULL;
    GnomeIconList *iconlist =
      (GnomeIconList *) lookup_widget("game_mgr_iconlist");
    gboolean delete = FALSE;
    GtkWidget *warn;

    /* Init race list */
    race_list = (GtkTreeView*) lookup_widget("game_mgr_properties_race_list");
    store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Races", 
						      renderer,
						      "text", 0,
						      NULL);
    gtk_tree_view_set_model(race_list, GTK_TREE_MODEL(store));
    gtk_tree_view_append_column(race_list, column);

    /* Load the games data */
    appbar = (GnomeAppBar *)lookup_widget ("game_mgr_appbar");
    gwp_gconf = gconf_client_get_default();
    games = gconf_client_all_dirs(gwp_gconf, games_path, NULL);
    
    /* Check for format version */
    if (game_state_get_version() == 0) {
      /* Set current version for first GWP execution users */
      game_state_set_version (GAME_STATE_VERSION);
    } else if (game_state_get_version() < GAME_STATE_VERSION) {
      delete = TRUE;
      if(games) {
	/* Warn the user about its games being deleted */
	warn = gwp_warning_dialog_new (game_mgr,
				       _("Your game definitions will be deleted."),
				       _("The game state data format have changed. Your game definitions will be deleted because are not compatible with this version, please re-create them. Your game files won't be touched, sorry for the inconvenience."));
	gtk_dialog_run(GTK_DIALOG(warn));
	gtk_widget_destroy(warn);
      }
    }
    
    /* Additional info */
    game_mgr_update_appbar();
    
    /* Load (or delete) the games */
    while(games != NULL) {
      name_tmp = g_strdup(g_strrstr(games->data, "/"));
      name_tmp++;

      if(delete) {
	game_mgr_delete_game(name_tmp);
	game_state_set_version(GAME_STATE_VERSION);
      } else {
	/* Get the data! */
	game = game_mgr_load_game_state (games_path, name_tmp);

	/* Add icon to iconlist */
	game_mgr_add_icon(iconlist, game, -1);
      }
      /* Move forward on the list... */
      games = games->next;
    }
    g_free(games_path);
}

void game_mgr_update_race_list(char *dir_param) 
{
  GString *pdata, *ship, *rst;
  GtkTreeView *race_list;
  GtkListStore *store;
  GtkTreeIter iter;
  gchar *dir;
  gint i;

  /* Add a slash at the end */
  dir = g_strconcat(dir_param, "/", NULL);

  race_list = (GtkTreeView*) lookup_widget("game_mgr_properties_race_list");
  store = (GtkListStore*) gtk_tree_view_get_model(race_list);
  g_assert(store != NULL);
  gtk_list_store_clear(store);

  /* If dir exists, we work */
  if(g_file_test(dir, G_FILE_TEST_IS_DIR)) {

    GnomeFileEntry *trn_dir, *rst_dir;
    
    trn_dir = (GnomeFileEntry *) lookup_widget("game_mgr_trn_dir");
    rst_dir = (GnomeFileEntry *) lookup_widget("game_mgr_rst_dir");
    
    /* Set default dir to some controls */
    gnome_file_entry_set_default_path(trn_dir, dir);
    gnome_file_entry_set_default_path(rst_dir, dir);

    for (i = 1; i <= 11; i++) {
      pdata = g_string_new ("pdata");
      ship = g_string_new ("ship");
      rst = g_string_new ("player");

      pdata = g_string_append (pdata, 
			       g_strdup_printf ("%d.dis", i));
      ship = g_string_append (ship,
			      g_strdup_printf ("%d.dis", i));
      rst = g_string_append (rst,
			     g_strdup_printf ("%d.rst", i));

      pdata = g_string_prepend(pdata, dir);
      ship = g_string_prepend(ship, dir);
      rst = g_string_prepend(rst, dir);
    
      /* If one of the required files exist... */
      if((g_file_test(rst->str, G_FILE_TEST_IS_REGULAR) ||
	  g_file_test(pdata->str, G_FILE_TEST_IS_REGULAR) ||
	  g_file_test(ship->str, G_FILE_TEST_IS_REGULAR))) {
	
	/* Add available races to race list */
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 
			   0, g_strdup_printf("%s", race_get_name(i)),
			   1, i,    /* invisible column with race number */
			   -1);	
      }
    }
    g_string_free(pdata, TRUE);
    g_string_free(ship, TRUE);
    g_string_free(rst, TRUE);
  }
  g_free(dir);
}



gboolean game_mgr_properties_dlg_fill(GwpGameState *settings)
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
  gchar *game_name_str = g_strdup_printf("%s", gwp_game_state_get_name(settings));

  game_mgr_game_name_demangle(game_name_str);

  gnome_file_entry_set_filename(game_dir, gwp_game_state_get_dir(settings));
  gnome_file_entry_set_filename(trn_dir, gwp_game_state_get_trn_dir(settings));
  gnome_file_entry_set_filename(rst_dir, gwp_game_state_get_rst_dir(settings));

  gtk_entry_set_text(game_name, game_name_str);
  gtk_entry_set_text(player_email, gwp_game_state_get_player_email(settings));
  gtk_entry_set_text(host_email, gwp_game_state_get_host_email(settings));
  /* This MUST be after the game_dir changed event :-) */
  gtk_entry_set_text(race_name, race_get_name(gwp_game_state_get_race(settings)));
  /* FIXME: this sucks */
  gint *racenum = g_malloc(sizeof(gint));
  *racenum = gwp_game_state_get_race_nr (settings);
  g_object_set_data(G_OBJECT(race_name),
		    "race_number", racenum);
  g_object_set_data(G_OBJECT(game_name),
		    "old_game_name", g_strdup(gwp_game_state_get_name(settings)));

  /* FIXME: Remember host type!!! */
  
  /* Do some validations... */
  if(game_mgr_properties_dlg_all_ok(FALSE, -1)) {
    return TRUE;
  } else {
    game_mgr_properties_dlg_clean();
    return FALSE;
  }
}


/* 
 * Callback function connected to OK button on the game
 * properties dialog when using it as an edit game dialog
 */
void game_mgr_cb_edit_game(GtkWidget *widget, GtkWidget *iconlist)
{
  gint icon_idx = game_mgr_get_icon_idx_selected();
  gchar *old_game_name = (gchar *)
    g_object_get_data(G_OBJECT(lookup_widget("game_mgr_entry_game_name")),
		      "old_game_name");
  game_mgr_game_name_mangle(old_game_name);
  
  /* If validations are ok... */
  if(game_mgr_properties_dlg_all_ok(TRUE, icon_idx)) {
    GwpGameState *state = NULL;
    GtkWidget *ok_button = lookup_widget("game_mgr_button_ok");

    state = (GwpGameState *) 
      gnome_icon_list_get_icon_data(GNOME_ICON_LIST(iconlist),
				    icon_idx);
    g_assert(state != NULL);
  
    /* Assign dialog values to state structure */
    game_mgr_properties_dlg_get_settings(state);

    /* Update it on GConf */
    game_mgr_delete_game(old_game_name);
    game_mgr_save_game_state(state, FALSE);

    /* Update icon */
    gnome_icon_list_remove (GNOME_ICON_LIST(iconlist), icon_idx);
    game_mgr_add_icon (GNOME_ICON_LIST(iconlist), state, icon_idx);

    /* Disconnect signal before releasing dialog */
    g_signal_handlers_disconnect_by_func(G_OBJECT(ok_button),
					 G_CALLBACK(game_mgr_cb_edit_game),
					 iconlist);
    gtk_widget_hide(game_mgr_properties);
    game_mgr_properties_dlg_clean();
  }
}

/**
 * Callback function connected to OK button on the game 
 * properties dialog when using it as a new game dialog 
 */
void game_mgr_cb_new_game(GtkWidget *widget, gpointer iconlist)
{
  GtkWidget *ok_button = lookup_widget("game_mgr_button_ok");
  gint icon_q;

  icon_q = gnome_icon_list_get_num_icons(iconlist)+1;
  /* If validations are ok, we work... */
  if(game_mgr_properties_dlg_all_ok(TRUE, icon_q)) {
    GwpGameState *new_game = gwp_game_state_new();

    /* Get the data from the dialog */
    game_mgr_properties_dlg_get_settings(new_game);

    /* Set up initial coordinates to the middle of the echo cluster */
    gwp_game_state_set_last_coords (new_game, 1500, 1500);

    /* Save it on GConf */
    game_mgr_save_game_state(new_game, FALSE);

    /* Add icon with data */
    game_mgr_add_icon(iconlist, new_game, -1);

    /* Update appbar's info */
    game_mgr_update_appbar();
    
    /* Disconnect signal before releasing dialog */
    g_signal_handlers_disconnect_by_func(G_OBJECT(ok_button),
					 G_CALLBACK(game_mgr_cb_new_game),
					 iconlist);
    gtk_widget_hide(game_mgr_properties);
    game_mgr_properties_dlg_clean();
  }
}


void game_mgr_properties_dlg_get_settings(GwpGameState *settings)
{
  g_assert (GWP_IS_GAME_STATE(settings));

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
  
  gwp_game_state_set_dir(settings,
			 gnome_file_entry_get_full_path(game_dir, FALSE));
  
  name = g_strdup (gtk_entry_get_text(game_name));
  /* Tranform "game name" to "game_name" */
  game_mgr_game_name_mangle(name);
  gwp_game_state_set_name (settings, name);
  
  gwp_game_state_set_trn_dir (settings,
			      gnome_file_entry_get_full_path(trn_dir, FALSE));
  gwp_game_state_set_rst_dir (settings,
			      gnome_file_entry_get_full_path(rst_dir, FALSE));
  gwp_game_state_set_player_email (settings, 
				   g_strdup(gtk_entry_get_text(player_email)));
  gwp_game_state_set_host_email (settings, 
				 g_strdup(gtk_entry_get_text(host_email)));
  /* FIXME: settings->host_type = */
  race_num = (gint *) g_object_get_data(G_OBJECT(race_name),
					"race_number");
  g_assert(race_num != NULL);
  gwp_game_state_set_race (settings, *race_num);
}

/* Several dialog validations */
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

  /*
   * Check if game dir exists
   */
  if(! g_file_test(gnome_file_entry_get_full_path(game_dir, FALSE), 
		   G_FILE_TEST_IS_DIR)) {
    if(show_warnings) {
      GtkWidget *warn;
      
      warn = gwp_warning_dialog_new (game_mgr_properties,
				     g_strdup_printf(_("Game directory '%s' doesn't exist"), gnome_file_entry_get_full_path(game_dir, FALSE)),
				     NULL);

      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
    }
    return FALSE;
  }
  /*
   * Check if there is a game name
   */
  if(strlen(gtk_entry_get_text(game_name)) <= 0) {
    if(show_warnings) {
      GtkWidget *warn;
      
      warn = gwp_warning_dialog_new (game_mgr_properties,
				     _("Please provide a name for this game"),
				     NULL);

      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
    }
    return FALSE;
  }
  /* 
   * Check if game name is not duplicated 
   */
  game_name_str = g_strdup_printf("%s", gtk_entry_get_text(game_name));
  game_mgr_game_name_mangle(game_name_str);
  if(icon_number >= 0) {
    GnomeIconList *iconlist =
      (GnomeIconList *) lookup_widget("game_mgr_iconlist");
    GwpGameState *state;
    gint i, icon_q;

    /* Iterate through all games except the one being edited */
    icon_q = gnome_icon_list_get_num_icons(iconlist);
    for(i = 0; i < icon_q; i++) {
      if(i != icon_number) {
	state = (GwpGameState *) 
	  gnome_icon_list_get_icon_data(GNOME_ICON_LIST(iconlist), i);
	g_assert(state != NULL);

	/* If strings are equal... */
	if(g_ascii_strcasecmp(gwp_game_state_get_name(state), 
			      game_name_str) == 0) {
	  GtkWidget *warn;

	  warn = gwp_warning_dialog_new (game_mgr_properties,
					 g_strdup_printf(_("A game named '%s' already exist, please select another name"),
							 gtk_entry_get_text(game_name)),
					 NULL);
	  
	  gtk_dialog_run(GTK_DIALOG(warn));
	  gtk_widget_destroy(warn);
	  
	  return FALSE;
	}
      }
    }
  }
  /*
   * Check if user selected a race 
   */
  if(strlen(gtk_entry_get_text(race_name)) <= 0) {
    if(show_warnings) {
      GtkWidget *warn;
      
      warn = gwp_warning_dialog_new (game_mgr_properties,
				     _("Please select a race"),
				     NULL);
      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
    }
    return FALSE;
  }

  /* auto-validations */
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

  /* All ok!, lets continue... */
  return TRUE;
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

/**
 * Add an icon with its label to the games list.
 *
 * @param iconlist The game iconlist
 * @param state The GwpGameState object
 * @param pos The position where to add the new icon. If pos < 0, the icon will be added last.
 */
void 
game_mgr_add_icon(GnomeIconList *iconlist, 
		  GwpGameState  *state, 
		  gint           pos)
{
  gint icon_idx;
  gchar *race_logo_img = g_strdup_printf("%s%d.png",
					 GWP_RACE_ICONS_DIR"/race-logo",
					 gwp_game_state_get_race_nr (state));

  /* Setup icon caption */
  gchar *game_name = g_strdup(gwp_game_state_get_name(state));
  game_mgr_game_name_demangle(game_name);

  if (gwp_game_state_get_turn_number(state) > 0) {
    game_name = g_strconcat (game_name, "\n", 
			     "(", _("turn "), 
			     g_strdup_printf("%d", gwp_game_state_get_turn_number(state)),
			     ")", NULL);
  }

  /* Add new game icon, with data */
  if (pos < 0) {
    icon_idx = gnome_icon_list_append(GNOME_ICON_LIST(iconlist),
				      race_logo_img,
				      game_name);
    gnome_icon_list_set_icon_data(GNOME_ICON_LIST(iconlist),
				  icon_idx,
				  state);
  } else {
    gnome_icon_list_insert(GNOME_ICON_LIST(iconlist),
			   pos,
			   race_logo_img,
			   game_name);
    gnome_icon_list_set_icon_data(GNOME_ICON_LIST(iconlist),
				  pos,
				  state);
  }
  g_free(game_name);
  g_free(race_logo_img);
}

/**
 * Translates ' ' to '_' 
 */
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

/**
 * Translates '_' to ' ' 
 */
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

void game_mgr_play_game(GwpGameState *state)
{
  gchar *tmp;
  GtkLabel *race = 
    (GtkLabel *) lookup_widget("label_race_name");

  /* If none game selected, notice the user */
  if (!state) {
    GtkWidget *warn;

    warn = gwp_warning_dialog_new (game_mgr_properties,
				   _("No game selected, please select one."),
				   _("If you don't have any game on your game manager, you should add one with the \"New\" button, adding the necessary game data."));
    gtk_dialog_run(GTK_DIALOG(warn));
    gtk_widget_destroy(warn);
    return;
  }

  game_state = state;

  /* Check for new RST */
  if (vp_can_unpack(gwp_game_state_get_dir(game_state), 
		    gwp_game_state_get_race(game_state))) {
    GtkResponseType response;
    GtkWidget *warn;

    warn = gtk_message_dialog_new ((GtkWindow *) game_mgr_properties,
				   GTK_DIALOG_DESTROY_WITH_PARENT,
				   GTK_MESSAGE_QUESTION,
				   GTK_BUTTONS_YES_NO,
				   _("A new RST file was found. Do you want to unpack it?"));

    response = gtk_dialog_run(GTK_DIALOG(warn));
    gtk_widget_destroy(warn);

    if(response == GTK_RESPONSE_YES) {
      vp_unpack (gwp_game_state_get_dir(game_state), 
		 gwp_game_state_get_race(game_state));
    }
  }

  /* Show the wait notice */
  gtk_widget_show (wait_notice);
  gtk_widget_realize (wait_notice);
  while (gtk_events_pending())
    gtk_main_iteration();

  /* Read data files and init starchart */
  init_data();
  game_mgr_init_message_history(); /* This has to go after init_data()
				      because of the turn number
				      loading code. */
  init_starchart(gwp);
  init_starchart_mini();

  /* Get the widgets ready */
  gtk_label_set_text (race, 
		      race_get_name (gwp_game_state_get_race(game_state)));

  tmp = g_strconcat(gwp_game_state_get_name(game_state), " | ",
		    g_strdup_printf(_("Turn: %d"), 
				    gwp_game_state_get_turn_number(game_state)),
		    " - GNOME War Pad", NULL);
  gtk_window_set_title(GTK_WINDOW(gwp), tmp);
  g_free(tmp);
  
  /* Activate plugins */
  gwp_python_set_active_plugins ((GSList *)g_object_get_data (G_OBJECT(state),
							      "active_plugins"));
  
  /* Show the good stuff! */
  gtk_widget_hide (wait_notice);
  gtk_widget_hide(game_mgr);
  gtk_widget_show(gwp);
}

gint game_mgr_get_icon_idx_selected(void)
{
  gint icon_idx;
  GList *selections = NULL;
  GtkWidget *iconlist = lookup_widget("game_mgr_iconlist");

  selections = gnome_icon_list_get_selection(GNOME_ICON_LIST(iconlist));
  icon_idx = (gint)g_list_nth_data(selections, 0);
  
  return icon_idx;
}

static void game_mgr_init_message_history (void)
{
  GtkWidget *warn;
  GString *filenamedest = 
    g_string_new (g_strdup_printf("mdata%d_%d.dat", 
				  gwp_game_state_get_race_nr(game_state),
				  gwp_game_state_get_turn_number(game_state)));
  GString *filenameorig =
    g_string_new (g_strdup_printf("mdata%d.dat", 
				  gwp_game_state_get_race_nr(game_state)));
  gchar *dir = gwp_game_state_get_full_path (game_state, "message-history");
  gchar *filedest = gwp_game_state_get_full_path (game_state, 
					g_strdup_printf("message-history/%s",
							filenamedest->str));
  gchar *fileorig = NULL;
  FILE *dest;

  /*** Directory check & creation ***/
  if (!g_file_test(dir, G_FILE_TEST_EXISTS)) {
    mkdir (dir, S_IRWXU);
  } else if (g_file_test(dir, G_FILE_TEST_IS_REGULAR)) {
    warn = gwp_warning_dialog_new (game_mgr,
				   _("Error creating the message history directory."),
				   _("A file already exists with the name 'message-history', please remove or rename this file so that the message history feature can work correctly."));
    gtk_dialog_run(GTK_DIALOG(warn));
    gtk_widget_destroy(warn);
    return;
  }

  /*** File check & copy ***/
  if (!g_file_test(filedest, G_FILE_TEST_EXISTS)) {
    /* ... lowercase ... */
    if (g_file_test(gwp_game_state_get_full_path(game_state, 
						 filenameorig->str), 
		    G_FILE_TEST_EXISTS)) {
      fileorig = gwp_game_state_get_full_path(game_state, 
					      filenameorig->str);
    }
    /* ... uppercase ... */
    else if (g_file_test(gwp_game_state_get_full_path(game_state, 
					    g_string_up(filenameorig)->str),
			 G_FILE_TEST_EXISTS)) {
      fileorig = gwp_game_state_get_full_path(game_state, 
				    g_string_up(filenameorig)->str);
    }

    /* Copy file */
    if (fileorig) {
      gchar *contents = NULL;
      gsize length;
      GError *err = NULL;

      g_file_get_contents (fileorig, &contents, &length, &err);
      dest = fopen (filedest, "w");
      fwrite (contents, 1, (size_t)length, dest);
      fclose (dest);

      g_free (contents);
    } else {
      warn = gwp_warning_dialog_new (game_mgr,
				     _("Message data file not found."),
				     _("The MDATA file was not found, it's needed to read the game messages, please check your VGA Planets installation."));
      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
    }
  }

  /* Free Stuff!! */
  g_free (dir);
  g_free (filedest);
  g_free (fileorig);
  g_string_free (filenameorig, TRUE);
  g_string_free (filenamedest, TRUE);
}

GwpGameState * game_mgr_load_game_state (gchar *games_path, gchar *game_name)
{
  GwpGameState *game = gwp_game_state_new ();
  gchar *path = g_strconcat(games_path, "/", game_name, "/", NULL);

  gwp_game_state_set_name(game, game_name);
  
  /* GwpGameState */
  gwp_game_state_set_starchart_zoom(game, 
				    gconf_client_get_float(gwp_gconf, 
							   g_strconcat(path, "starchart_zoom", NULL),
							   NULL));
  gwp_game_state_set_turn_number(game, 
				 gconf_client_get_int(gwp_gconf, 
						      g_strconcat(path, "turn_number", NULL), 
						      NULL));
  gwp_game_state_set_last_x_coord(game, 
				  gconf_client_get_int(gwp_gconf, 
						       g_strconcat(path, "last_x_coord", NULL),
						       NULL));
  gwp_game_state_set_last_y_coord(game, 
				  gconf_client_get_int(gwp_gconf, 
						       g_strconcat(path, "last_y_coord", NULL),
						       NULL));  
  /* Game Settings */
  gwp_game_state_set_dir(game, 
			 gconf_client_get_string(gwp_gconf, 
						 g_strconcat(path, "game_dir", NULL),
						 NULL));

  gwp_game_state_set_trn_dir(game, 
			     gconf_client_get_string(gwp_gconf, 
						     g_strconcat(path, "trn_dir", NULL),
						     NULL));
  
  gwp_game_state_set_rst_dir(game, 
			     gconf_client_get_string(gwp_gconf, 
						     g_strconcat(path, "rst_dir", NULL),
						     NULL));
  
  gwp_game_state_set_player_email(game, 
				  gconf_client_get_string(gwp_gconf, 
							  g_strconcat(path, "player_email", NULL),
							  NULL));
  
  gwp_game_state_set_host_email(game, 
				gconf_client_get_string(gwp_gconf, 
							g_strconcat(path, "host_email", NULL),
							NULL));
  
  gwp_game_state_set_host_type(game, 
			       gconf_client_get_int(gwp_gconf, 
						    g_strconcat(path, "host_type", NULL),
						    NULL));
  
  gwp_game_state_set_race(game, 
			  gconf_client_get_int(gwp_gconf, 
					       g_strconcat(path, "race", NULL),
					       NULL));
  
  g_object_set (game,
		"minefields",
		gconf_client_get_bool(gwp_gconf, 
				      g_strconcat (path, 
						   "minefields", 
						   NULL),
				      NULL),
		NULL);

  g_object_set (game, 
		"ion-storms",
		gconf_client_get_bool(gwp_gconf, 
				      g_strconcat (path, 
						   "ion-storms", 
						   NULL),
				      NULL),
		NULL);
  
  g_object_set (game, 
		"planet-names", 
		gconf_client_get_bool(gwp_gconf, 
				      g_strconcat (path, 
						   "planet-names", 
						   NULL),
				      NULL),
		NULL);
  
  g_object_set (game, 
		"scanner-area", 
		gconf_client_get_bool(gwp_gconf, 
				      g_strconcat (path, 
						   "scanner-area", 
						   NULL),
				      NULL),
		NULL);

  g_object_set (game, 
		"grid", gconf_client_get_bool(gwp_gconf, 
					      g_strconcat (path, 
							   "grid", 
							   NULL),
					      NULL),
		NULL);

  g_object_set (game, 
		"constellations", 
		gconf_client_get_bool(gwp_gconf, 
				      g_strconcat (path, 
						   "constellations", 
						   NULL),
				      NULL),
		NULL);
  /* Registered plugins */
  GSList *plugins = gconf_client_get_list (gwp_gconf,
					   g_strconcat (path, "plugins", NULL),
					   GCONF_VALUE_STRING,
					   NULL);
  g_object_set_data (G_OBJECT(game),
		     "active_plugins", (gpointer)plugins);
  
  return game;
}

/**
 * Save game state data on GConf
 */
void game_mgr_save_game_state (GwpGameState *state, gboolean closing_game)
{
  g_assert (GWP_IS_GAME_STATE (state));

  gchar *name = g_strdup(gwp_game_state_get_name(state));
  gchar *path;
  gboolean tmp_bool;

  game_mgr_game_name_mangle(name);
  path = g_strconcat(GWP_GCONF_PATH"Games/",
		     name,
		     "/", NULL);

  /* GameState data */
  gconf_client_set_float(gwp_gconf, g_strconcat(path,"starchart_zoom", NULL),
			 gwp_game_state_get_starchart_zoom(state), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"turn_number",NULL),
		       gwp_game_state_get_turn_number(state), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"last_x_coord",NULL),
		       gwp_game_state_get_last_x_coord(state), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"last_y_coord",NULL),
		       gwp_game_state_get_last_y_coord(state), NULL);
  
  /* GameSettings data */
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"player_email",NULL),
			  gwp_game_state_get_player_email(state), NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"host_email",NULL),
			  gwp_game_state_get_host_email(state), NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"game_dir",NULL),
			  gwp_game_state_get_dir(state), NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"trn_dir",NULL),
			  gwp_game_state_get_trn_dir(state), NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"rst_dir",NULL),
			  gwp_game_state_get_rst_dir(state), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"host_type",NULL),
		       gwp_game_state_get_host_type(state), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"race",NULL),
		       gwp_game_state_get_race(state), NULL);

  g_object_get (G_OBJECT(state), "minefields", &tmp_bool, NULL);
  gconf_client_set_bool (gwp_gconf, g_strconcat(path, "minefields", NULL),
			 tmp_bool, NULL);
  
  g_object_get (G_OBJECT(state), "ion-storms", &tmp_bool, NULL);
  gconf_client_set_bool (gwp_gconf, g_strconcat(path, "ion-storms", NULL),
			 tmp_bool, NULL);

  g_object_get (G_OBJECT(state), "planet-names", &tmp_bool, NULL);
  gconf_client_set_bool (gwp_gconf, g_strconcat(path, "planet-names", NULL),
			 tmp_bool, NULL);

  g_object_get (G_OBJECT(state), "scanner-area", &tmp_bool, NULL);
  gconf_client_set_bool (gwp_gconf, g_strconcat(path, "scanner-area", NULL),
			 tmp_bool, NULL);

  g_object_get (G_OBJECT(state), "grid", &tmp_bool, NULL);
  gconf_client_set_bool (gwp_gconf, g_strconcat(path, "grid", NULL),
			 tmp_bool, NULL);

  g_object_get (G_OBJECT(state), "constellations", &tmp_bool, NULL);
  gconf_client_set_bool (gwp_gconf, g_strconcat(path, "constellations", NULL),
			 tmp_bool, NULL);

  if (closing_game) {
    /* Registered plugins */
    gconf_client_set_list (gwp_gconf, g_strconcat(path,"plugins", NULL),
			   GCONF_VALUE_STRING,
			   gwp_python_get_active_plugins (),
			   NULL);
  }
}


/**
 * Deletes GConf Game entry... 
 */
void game_mgr_delete_game(const gchar *name)
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

/**
 * Updates all data, call this before quitting or opening another game
 */
void game_mgr_close_game(GwpGameState *game_state)
{
  if(game_state) {
    gint x, y, i;

    /* Save game state */
    gnome_canvas_get_scroll_offsets(starchart_get_canvas(), &x, &y);
    gwp_game_state_set_last_coords(game_state, x, y);
    game_mgr_save_game_state(game_state, TRUE);

    /******************************/
    /* Clean up objects in memory */
    /******************************/
    
    /* Eliminate planets */
    g_hash_table_foreach (planet_list, (GHFunc) destroy_gobject_ht, NULL);
    g_hash_table_destroy (planet_list);
    /* Eliminate ships */
    g_hash_table_foreach (ship_list, (GHFunc) destroy_gobject_ht, NULL);
    g_hash_table_destroy (ship_list);
    /* Eliminate minefields */
    g_slist_foreach (minefield_list, (GFunc) destroy_gobject_sl, NULL);
    g_slist_free (minefield_list);
    /* Eliminate ion storms */
    g_slist_foreach (storm_list, (GFunc) destroy_gobject_sl, NULL);
    g_slist_free (storm_list);
    /* Eliminate hullspec */
    g_slist_foreach (hullspec_list, (GFunc) destroy_gobject_sl, NULL);
    g_slist_free (hullspec_list);
    /* Eliminate beamspec */
    g_slist_foreach (beamspec_list, (GFunc) destroy_gobject_sl, NULL);
    g_slist_free (beamspec_list);
    /* Eliminate torpspec */
    g_slist_foreach (torpspec_list, (GFunc) destroy_gobject_sl, NULL);
    g_slist_free (torpspec_list);
    /* Eliminate engspec */
    g_slist_foreach (engspec_list, (GFunc) destroy_gobject_sl, NULL);
    g_slist_free (engspec_list);
    /* FIXME: Dirty cleaning process? */
    for (i = 0; i < TOTAL_QUADS; i++) {
      planets_per_quad[i] = NULL;
      ships_per_quad[i] = NULL;
      locations_per_quad[i] = NULL;
    }
    /* Eliminate & recreate starchart */
    g_object_unref (G_OBJECT(starchart_get_canvas()));
    starchart_set_canvas (GNOME_CANVAS(gnome_canvas_new()));
  }
}

/**
 * Internal function to destroy GObjects from a HashTable
 */
static void destroy_gobject_ht (gpointer key, gpointer value, gpointer user_data)
{
  g_object_unref (G_OBJECT(value));
}

/**
 * Internal function to destroy GObjects from a GSList
 */
static void destroy_gobject_sl (gpointer value, gpointer user_data)
{
  g_object_unref (G_OBJECT(value));
}

/**
 * Returns the format version number
 */
static gint game_state_get_version(void)
{
  gint ret = 0;
  ret = gconf_client_get_int(gwp_gconf, 
			     g_strconcat(GWP_GCONF_PATH, "version", NULL),
			     NULL);
  return ret;
}

static void game_state_set_version(gint version)
{
  gconf_client_set_int(gwp_gconf, 
		       g_strconcat(GWP_GCONF_PATH, "version", NULL),
		       version,
		       NULL);
}

/**
 * Inform the number of games on the game manager.
 */
void
game_mgr_update_appbar (void)
{
  GnomeAppBar *appbar = (GnomeAppBar *)lookup_widget("game_mgr_appbar");
  gchar *games_path = g_strconcat(GWP_GCONF_PATH, "Games", NULL);
  GSList *games = gconf_client_all_dirs(gwp_gconf, games_path, NULL);
  gint games_nr = g_slist_length(games);

  if (games_nr == 0) {
    gnome_appbar_set_status (appbar, _("no games"));    
  } else if (games_nr == 1) {
    gnome_appbar_set_status (appbar, _("1 game"));
  } else {
    gnome_appbar_set_status (appbar, g_strdup_printf(_("%d games"), 
						     games_nr));
  }
  g_slist_free (games);
  g_free (games_path);
}
