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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef USE_PYTHON
/* Must be the first!! */
#include "gwp-python.h"
#endif

#include <gnome.h>

#include "global.h"
#include "gwp-game-state.h"
#include "game_mgr.h"
#include "callbacks.h"
#include "support.h"
#include "starchart.h"
#include "vp_utils.h"
#include "vp_unpack.h"
#include "race.h"
#include "gwp-messages.h"
#include "gwp-utils.h"
#include "message-reader.h"
#include "gwp-py-functions.h"
#include "vcr.h"


gboolean
starchart_event_key                    (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{	
  gboolean handled = FALSE;

  switch(event->keyval)
    {
      /* Scrolling Events */
    case GDK_w:
      if (!gwp_game_state_get_extra_panel_open(game_state))
	starchart_scroll(0, -SCROLL);
      handled = TRUE;
      break;
    case GDK_s:
      if (!gwp_game_state_get_extra_panel_open(game_state))
	starchart_scroll(0, SCROLL);
      handled = TRUE;
      break;
    case GDK_a:
      if (!gwp_game_state_get_extra_panel_open(game_state))
	starchart_scroll(-SCROLL, 0);
      handled = TRUE;
      break;
    case GDK_d:
      if (!gwp_game_state_get_extra_panel_open(game_state))
	starchart_scroll(SCROLL, 0);
      handled = TRUE;
      break;
      /* Hide panels */
    case GDK_Escape:
      starchart_close_extra_panels();
      handled = TRUE;
      break;
    }

#ifdef USE_PYTHON
  gwp_python_event_key (event);
  handled = TRUE;
#endif

  return handled;
}

gboolean
starchart_event_button_release         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  gint x, y;

  starchart_set_default_cursor();

  x = (gint) event->x;
  y = (gint) event->y;

  starchart_mini_scroll_zone_to(x, y);

  return TRUE;
}

gboolean
starchart_event_button                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         gwp_ptr)
{
  gint x, y, q;
  gdouble wx, wy;
  GSList *planets_nearby, *ships_nearby;
/*   static GnomeCanvasItem *ps_planet = NULL, *s_planet = NULL; */
/*   static GnomeCanvasItem *ps_ship = NULL, *s_ship = NULL; */
  static GwpPlanet *ps_planet = NULL, *s_planet = NULL;
  static GwpShip *ps_ship = NULL, *s_ship = NULL;
  static gboolean loaded = FALSE;
  static GtkNotebook *mini = NULL;

  if (!loaded) {
    loaded = TRUE;

    mini = (GtkNotebook *) lookup_widget("notebook_mini");
  }
  
  /* Get focus on starchart */
  gtk_widget_grab_focus(GTK_WIDGET(starchart_get_canvas()));
  
  /* First get canvas coords */
  x = (gint) event->x;
  y = (gint) event->y;
  
  /* Translate coords to World system */
  gnome_canvas_c2w(starchart_get_canvas(), x, y, &wx, &wy);
  q = get_quadrant(wx, wy);
  
  /* Select a planet */
  if((event->type == GDK_BUTTON_PRESS) && (event->button == 1)) {
    /* Search for nearest planet and select it */
    planets_nearby = starchart_get_surrounding_quads(planets_per_quad, q);

    /* Keep record of previously selected planet */
    ps_planet = s_planet;
    s_planet = starchart_select_nearest_planet(GTK_WIDGET(gwp_ptr), 
					       planets_nearby, wx, wy);

    /* When a planet is selected, emit the corresponding signal */
    g_signal_emit_by_name (s_planet, "selected");
  } 
  /* Open Planet panel (double-click) */
  else if((event->type == GDK_2BUTTON_PRESS) && (event->button == 1)) {
    /* If the d-click was on the same planet, show the panels! */
    if(ps_planet == s_planet) {
      starchart_open_extra_planet_panels();
      while (gtk_events_pending())
	gtk_main_iteration();

      /* Re-select planet to update extra panels */
      planets_nearby = starchart_get_surrounding_quads(planets_per_quad, q);
      starchart_select_nearest_planet(GTK_WIDGET(gwp_ptr), planets_nearby, wx, wy);
    }
  } 
  /* Select a ship */
  else if((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
    /* Search for nearest ship and select it */
    ships_nearby = starchart_get_surrounding_quads(ships_per_quad, q);

    /* Keep record of previously selected ship */
    ps_ship = s_ship;
    s_ship = starchart_select_nearest_ship(GTK_WIDGET(gwp_ptr),
					   ships_nearby, wx, wy);

    /* When a ship is selected, emit the corresponding signal */
    g_signal_emit_by_name (s_ship, "selected");
  }
  /* Open Ship panel (double-click) */
  else if((event->type == GDK_2BUTTON_PRESS) && (event->button == 3)) {
    /* If the d-click was on the same planet, show the panels! */
    if(ps_ship == s_ship) {
      starchart_open_extra_ship_panels();
      while (gtk_events_pending())
	gtk_main_iteration();

      /* Re-select ship to update extra panels */
      ships_nearby = starchart_get_surrounding_quads(ships_per_quad, q);
      starchart_select_nearest_ship(GTK_WIDGET(gwp_ptr), ships_nearby, wx, wy);
    }
  } 
  return TRUE;
}


gboolean
starchart_event_pointer_motion         (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data)
{
  gint x, y;
  gdouble wx, wy;
  static guint interleave;
  static gint pointer_x = 0, pointer_y = 0;
  static gboolean panning = FALSE;
  
  /* First get canvas coords */
  x = (gint) event->x;
  y = (gint) event->y;

  /* If we are dragging the starchart to pan... */
  if((event->state & (GDK_BUTTON1_MASK)) == (GDK_BUTTON1_MASK)) {
    gint offset_x, offset_y;

    /* Check if extra panels are closed, panning is deactivated when open */
    if (!gwp_game_state_get_extra_panel_open(game_state)) {
      
      /* Set drag cursor */
      if(!panning) {
	starchart_set_pan_cursor();
	panning = TRUE;
      }

      /* Do panning */       
      if((interleave++ % MOUSE_INTERLEAVE) == 0) {
	gnome_canvas_get_scroll_offsets(starchart_get_canvas(), 
					&offset_x, 
					&offset_y);
	starchart_scroll_to(offset_x + (pointer_x - x) * (MOUSE_INTERLEAVE+1), 
			    offset_y + (pointer_y - y) * (MOUSE_INTERLEAVE+1));
      }
    } 
  }
  /* If not panning... */
  else {

    /* Reset cursor */
    if(panning) {
      starchart_set_default_cursor();
      panning = FALSE;
    }

    /* Translate coords to World system */
    gnome_canvas_c2w(GNOME_CANVAS(widget), x, y, &wx, &wy);
    
    /* Update coord indicator */
    starchart_update_coord_panel(widget, wx, wy);  
  }

  pointer_x = (gint) event->x;
  pointer_y = (gint) event->y;

  return FALSE;
}

void on_game_mgr_game_dir_changed (GtkEditable *editable,
				   gpointer user_data)
{
  GtkEntry *race_name_entry;
  char *dir;
  GtkWidget *btn_unpack = lookup_widget("game_mgr_btn_unpack");

  dir = gtk_editable_get_chars(editable, 0, -1);
  game_mgr_update_race_list(dir);

  /* Clear the race name on the entry */
  race_name_entry = (GtkEntry *) lookup_widget("game_mgr_entry_race_name");
  gtk_entry_set_text(race_name_entry, "");

  /* Disable 'Unpack' Button */
  gtk_widget_set_sensitive(btn_unpack, FALSE);
}

/* Lets play, dude! */
void on_game_mgr_play_game (GtkWidget *widget,
			    gpointer user_data)
{
  GnomeIconList *iconlist =
    (GnomeIconList *)lookup_widget("game_mgr_iconlist");
  GwpGameState *state = (GwpGameState *) 
    gnome_icon_list_get_icon_data(iconlist,
				  game_mgr_get_icon_idx_selected());

  game_mgr_play_game (state);
}

void on_game_mgr_new_game (GtkWidget *widget,
			   gpointer user_data)
{
  GtkWidget *iconlist = NULL;
  GtkWidget *ok_button = lookup_widget("game_mgr_button_ok");

  iconlist = lookup_widget("game_mgr_iconlist");

  /* Connect callback to OK button, so that works as a "new game" dialog. */
  g_signal_connect(G_OBJECT(ok_button), 
		   "clicked", 
		   G_CALLBACK(game_mgr_cb_new_game), iconlist);
  gtk_window_set_transient_for(GTK_WINDOW(game_mgr_properties), 
			       GTK_WINDOW(game_mgr));
  gtk_window_set_title(GTK_WINDOW(game_mgr_properties), 
		       _("New Game Properties"));
  gtk_widget_show(game_mgr_properties);
}

/* Key press event on iconlist */
gboolean 
on_game_mgr_iconlist_select_icon_keyboard (GnomeIconList *iconlist,
					   GdkEventKey   *event,
					   gpointer       user_data)
{
  if (event == NULL)
    return FALSE;

  if ((event->type == GDK_KEY_PRESS) && (event->keyval == GDK_Return)) {
    GList *selection = gnome_icon_list_get_selection (iconlist);
    /* First icon on the selection, we don't support multiple selection */
    gint icon_selected = (gint)g_list_nth_data (selection, 0);
    /* Play game! */
    game_mgr_play_game((GwpGameState *)
		       gnome_icon_list_get_icon_data(iconlist, 
						     icon_selected));
    return TRUE;
  }
  return FALSE;
}

/* Button events on iconlist */
void on_game_mgr_iconlist_select_icon (GnomeIconList *iconlist,
				       gint icon_idx,
				       GdkEventButton *event,
				       gpointer user_data)
{
  /* If user press the arrow keys, do nothing. */
  if (event == NULL) 
    return;
  
  /* Displays a pop-up menu */
  if((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
    GtkWidget *popup = NULL;
    
    popup = lookup_widget("game_mgr_popup_menu");
    gtk_menu_popup (GTK_MENU(popup), NULL, NULL, NULL, NULL, 1, 
		    gtk_get_current_event_time());
  }
  /* Double-click enters the game */
  else if((event->type == GDK_2BUTTON_PRESS) && (event->button == 1)) {
    game_mgr_play_game((GwpGameState *)
		       gnome_icon_list_get_icon_data(iconlist, 
						     icon_idx));
  }
}

void on_game_mgr_button_cancel_clicked (GtkWidget *widget,
					gpointer user_data)
{
  GtkButton *ok_button =
    (GtkButton *) lookup_widget("game_mgr_button_ok");
  GtkWidget *iconlist = lookup_widget("game_mgr_iconlist");

  /* Disconnect signal before releasing dialog */
  g_signal_handlers_disconnect_by_func(G_OBJECT(ok_button),
				       G_CALLBACK(game_mgr_cb_new_game),
				       iconlist);
  g_signal_handlers_disconnect_by_func(G_OBJECT(ok_button),
				       G_CALLBACK(game_mgr_cb_edit_game),
				       iconlist);

  gtk_widget_hide(game_mgr_properties);
  game_mgr_properties_dlg_clean();
}

/* Get the race number and assign it to the race name field */
void on_game_mgr_properties_race_list_row_activated (GtkWidget *widget,
						     gpointer user_data)
{
  GtkTreeView *race_l = NULL;
  GtkTreeSelection *sel = NULL;
  GtkTreeModel *model = NULL;
  GtkEntry *race_name_entry = NULL;
  GtkTreeIter iter;
  gint *race = NULL;
  gchar *dir = NULL;

  race_l = (GtkTreeView *) lookup_widget("game_mgr_properties_race_list");
  model = gtk_tree_view_get_model(race_l);
  sel = gtk_tree_view_get_selection(race_l);

  /* get the iterator at the selection */
  gtk_tree_selection_get_selected(sel, NULL, &iter);

  /* get the "hidden" data from the second column */
  race = g_malloc(sizeof(gint));
  gtk_tree_model_get(model, &iter, 1, race, -1);

  /* Copy the race name on the entry */
  race_name_entry = (GtkEntry *) lookup_widget("game_mgr_entry_race_name");
  gtk_entry_set_text(race_name_entry, race_get_name(*race));

  /* Bind its number (the really important data) */
  g_object_set_data(G_OBJECT(race_name_entry),
		      "race_number", race);

  /* Check if it's neccesary to activate the 'unpack' button */
  dir = gnome_file_entry_get_full_path((GnomeFileEntry *)
				       lookup_widget("game_mgr_game_dir"),
				       FALSE);
  if(vp_can_unpack(dir, *race)) {
    GtkWidget *btn_unpack =
      lookup_widget("game_mgr_btn_unpack");
    gtk_widget_set_sensitive(btn_unpack, TRUE);
  } else {
    GtkWidget *btn_unpack =
      lookup_widget("game_mgr_btn_unpack");
    gtk_widget_set_sensitive(btn_unpack, FALSE);
  }
}

void on_ships_list_cursor_changed (GtkWidget *widget,
				   gpointer user_data)
{
  GtkTreeView *ship_l = NULL;
  GtkTreeSelection *sel = NULL;
  GtkTreeModel *model = NULL;
  GtkTreeIter iter;
  gint ship_id;
  
  ship_l = (GtkTreeView *) lookup_widget ("ships_list");
  model = gtk_tree_view_get_model (ship_l);
  sel = gtk_tree_view_get_selection (ship_l);

  /* get the iterator at the selection */
  gtk_tree_selection_get_selected (sel, NULL, &iter);

  /* get the ship ID from the first column */
  gtk_tree_model_get (model, &iter, 0, &ship_id, -1);

  /* Update panel with new data */
  update_ship_panel_with (gwp_ship_get(ship_list, ship_id));
}

void on_game_mgr_edit_game(GtkWidget *widget,
			   gpointer user_data)
{
  GtkWidget *iconlist = NULL;
  GtkWidget *ok_button = lookup_widget("game_mgr_button_ok");
  GwpGameState *state = NULL;
  GList *selections = NULL;

  iconlist = lookup_widget("game_mgr_iconlist");
  selections = gnome_icon_list_get_selection(GNOME_ICON_LIST(iconlist));
  if(selections) {
    state = (GwpGameState *) 
      gnome_icon_list_get_icon_data(GNOME_ICON_LIST(iconlist),
				  (gint)g_list_nth_data(selections, 0));
    g_assert(state != NULL);

    if(game_mgr_properties_dlg_fill(state)) {

      /* 
	 Connect callback to OK button, so that works as 
	 an "edit game" dialog. 
      */
      g_signal_connect(G_OBJECT(ok_button), 
		       "clicked", 
		       G_CALLBACK(game_mgr_cb_edit_game), 
		       iconlist);
      gtk_window_set_transient_for(GTK_WINDOW(game_mgr_properties), 
				   GTK_WINDOW(game_mgr));
      gtk_window_set_title(GTK_WINDOW(game_mgr_properties), 
			   _("Edit Game Properties"));

      /* Update 'Unpack' button status */
      if(vp_can_unpack(gwp_game_state_get_dir(state), 
		       gwp_game_state_get_race(state))) {
	GtkWidget *btn_unpack =
	  lookup_widget("game_mgr_btn_unpack");
	gtk_widget_set_sensitive(btn_unpack, TRUE);
      } else {
	GtkWidget *btn_unpack =
	  lookup_widget("game_mgr_btn_unpack");
	gtk_widget_set_sensitive(btn_unpack, FALSE);
      }

      gtk_widget_show(game_mgr_properties);
    } else {
      GtkWidget *warn;
      
      warn = gtk_message_dialog_new((GtkWindow*) game_mgr,
				    GTK_DIALOG_DESTROY_WITH_PARENT,
				    GTK_MESSAGE_WARNING,
				    GTK_BUTTONS_CLOSE,
				    _("Oops! there is some problem with this game"));
      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
    }
  }
}

void on_game_mgr_delete_game (GtkWidget *widget,
			      gpointer user_data)
{
  GtkWidget *iconlist = lookup_widget("game_mgr_iconlist");
  GwpGameState *state = NULL;
  GList *selections = NULL;
  
  selections = gnome_icon_list_get_selection(GNOME_ICON_LIST(iconlist));

  if(selections) {
    gint icon_idx = (gint)g_list_nth_data(selections, 0);
    GtkResponseType response;
    GtkWidget *warn;
    gchar *game_name;

    state = (GwpGameState *) 
      gnome_icon_list_get_icon_data(GNOME_ICON_LIST(iconlist),
				    icon_idx);
    g_assert(state != NULL);
    game_name = g_strdup(gwp_game_state_get_name(state));
    game_mgr_game_name_mangle(game_name);

    /* Are you sureeee? */
    warn = gtk_message_dialog_new((GtkWindow*) game_mgr_properties,
				  GTK_DIALOG_DESTROY_WITH_PARENT,
				  GTK_MESSAGE_QUESTION,
				  GTK_BUTTONS_YES_NO,
				  _("Are you sure you want to delete '%s'?"),
				  game_name);
    response = gtk_dialog_run(GTK_DIALOG(warn));
    gtk_widget_destroy(warn);

    /* Oh well... */
    if(response == GTK_RESPONSE_YES) {
    
      /* Remove it from GConf */
      game_mgr_delete_game(game_name);
      gconf_client_suggest_sync(gwp_gconf, NULL);

      /* Free memory from GameState struct */
      /* FIXME!!: Destroy current GwpGameState object */
      /*game_state_free(state);*/

      /* Remove icon */
      gnome_icon_list_remove(GNOME_ICON_LIST(iconlist),
			     icon_idx);
    }
  } 
}

void gwp_quit(void)
{
  /* Save game state */
  game_mgr_close_game(game_state);

  /* Disconnect from GConf server */
  gconf_client_suggest_sync(gwp_gconf, NULL);
  g_object_unref(gwp_gconf);

#ifdef USE_PYTHON
  /* Stop Python interpreter */
  gwp_python_quit();
#endif

  /* bye bye... */
  gtk_main_quit();
}

/* Proxy funcs to show about... dialog */
void on_game_mgr_about_activate(GtkWidget *widget,
				gpointer data)
{
  on_about_activate(game_mgr);
}
void on_starchart_about_activate(GtkWidget *widget,
				 gpointer data)
{
  on_about_activate(gwp);
}
/* 
 * The real About show func: It appears that the GnomeAbout widget
 * is always destroyed when closed, so I have to create it every
 * time...that sucks!
 */
void on_about_activate(GtkWidget *widget)
{
  if(GTK_IS_WIDGET(widget)) {
    GtkWidget *about_gwp;
    const gchar *authors[] = {
      "Lucas Di Pentima <lucas@lunix.com.ar>",
      "Sven Wergandt <summ@gmx.de>",
      NULL
    };
    const gchar *documenters[] = {
      "Lucas Di Pentima <lucas@lunix.com.ar>",
      NULL
    };
    const gchar *translators = "Lucas Di Pentima <lucas@lunix.com.ar> (Spanish)\nStefan Reuther <streu@gmx.de> (German)";

    about_gwp = gnome_about_new(PACKAGE_NAME,
				PACKAGE_VERSION,
				_("(C) 2002-2004 Lucas Di Pentima\nThis software is released under the GNU GPL License"),
				_("A VGA Planets client for the GNOME platform.\nhttp://www.lunix.com.ar/~ldipenti/gwp/"),
				(const gchar **)authors,
				(const gchar **)documenters,
				(const gchar *)translators,
				gdk_pixbuf_new_from_file(DATADIR"/gwp/logo.png",
							 NULL));

    gtk_window_set_transient_for(GTK_WINDOW(about_gwp), 
				 GTK_WINDOW(widget));
    gtk_widget_show(about_gwp);
  }
}

/*
 * This cb is used to catch the "close window" clicks of those
 * pop-up windows we don't want to be destroyed.
 */
gboolean delete_event (GtkWidget *widget,
		       GdkEvent *event,
		       gpointer data)
{
  /* Return true, so that the window is not destroyed. */
  gtk_widget_hide(widget);
  return TRUE;
}

/*
 * Close current game and return to game manager.
 * FIXME: Here we'll have to clean all the data, including
 * the actions done and everything...
 */
void on_game_close_activate (GtkWidget *widget,
			     gpointer user_data)
{
  gtk_widget_hide(gwp);
  game_mgr_close_game(game_state);
  gtk_widget_show(game_mgr);
}

void on_game_mgr_btn_unpack_clicked (GtkWidget *widget,
				     gpointer user_data)
{
  GtkEntry *race_name_entry = 
    (GtkEntry *) lookup_widget("game_mgr_entry_race_name");
  gint *race;
  gchar *game_dir;

  race = (gint *) g_object_get_data(G_OBJECT(race_name_entry),
				    "race_number");

  game_dir = 
    gnome_file_entry_get_full_path((GnomeFileEntry *)
				   lookup_widget("game_mgr_game_dir"),
				   FALSE);
  // Unpack this game
  vp_unpack(game_dir, *race);

  /* Disable button if all ok */
  if(! vp_can_unpack(game_dir, *race)) {
    GtkWidget *btn_unpack =
      lookup_widget("game_mgr_btn_unpack");
    gtk_widget_set_sensitive(btn_unpack, FALSE);    
  }
}

/* CB to format the hscale widgets value */
gchar* on_hscale_tax_format_value(GtkScale *scale, gdouble value)
{
  return g_strdup_printf("%0.*f%%", gtk_scale_get_digits(scale), value);
}

/* Show online help */
void on_online_help_activate (GtkWidget *widget,
			      gpointer user_data)
{
  GError* error = NULL;
  
  if (!gnome_help_display ("gwp.xml", NULL, &error)) {
    /* report error */
    g_error_free (error);
  }
}

void on_button_zoom_in_clicked (GtkWidget *widget,
				gpointer user_data)
{
  starchart_zoom_in(starchart_get_canvas());
}

void on_button_zoom_out_clicked (GtkWidget *wodget,
				 gpointer user_data)
{
  starchart_zoom_out(starchart_get_canvas());
}

/* Zoom in */
void 
on_zoom_in (GtkWidget *widget,
	    gpointer user_data)
{
  starchart_zoom_in (starchart_get_canvas());
}

/* Zoom out */
void 
on_zoom_out (GtkWidget *widget,
	    gpointer user_data)
{
  starchart_zoom_out (starchart_get_canvas());
}

/**
 * Toggle grid visualization
 */
void
on_view_grid_toggle (GtkCheckMenuItem *menuitem,
		     gpointer          user_data)
{
  starchart_show_grid (gtk_check_menu_item_get_active(menuitem));
}

/* Hides/Shows the planet names on starchart */
void on_view_pnames_activate (GtkCheckMenuItem *menuitem,
			      gpointer user_data)
{
  gboolean show = gtk_check_menu_item_get_active(menuitem);

  if (gwp_game_state_get_starchart_zoom(game_state) >= 1.0) {
    starchart_show_planet_names (show);
  }
}

/* Hides/Shows the scanner area on starchart */
void on_view_scanner_area_activate (GtkCheckMenuItem *menuitem,
				    gpointer user_data)
{
  starchart_show_scanner_area (gtk_check_menu_item_get_active(menuitem));
}

/* Hides/Shows the minefields on starchart */
void on_view_minefields_activate (GtkCheckMenuItem *menuitem,
				  gpointer user_data)
{
  /* GameToggleMinefieldsRequest ... or something*/
  g_object_set (game_state, 
		"minefields", gtk_check_menu_item_get_active(menuitem),
		NULL);
}

/* Hides/Shows the ion storms on starchart */
void on_view_ion_storms_activate (GtkCheckMenuItem *menuitem,
				  gpointer user_data)
{
  starchart_show_ion_storms (gtk_check_menu_item_get_active(menuitem));
}

void on_view_message_reader_activate (GtkWidget *widget,
				      gpointer  user_data)
{
  message_reader_all_init( widget, user_data );
}

void on_reader_delete_event( GtkWidget *widget,
				      gpointer  user_data )
{
  message_reader_delete_event( widget, user_data );
}

void on_reader_firstmess_btn_clicked (GtkWidget *widget,
				      gpointer  user_data)
{
  message_reader_show_first_body( widget, user_data );
}

void on_reader_prev_btn_clicked (GtkWidget *widget,
				 gpointer  user_data)
{
  message_reader_show_prev_body( widget, user_data );
}

void on_reader_next_btn_clicked (GtkWidget *widget,
				 gpointer  user_data)
{
  message_reader_show_next_body( widget, user_data );
}

void on_reader_lastmess_btn_clicked (GtkWidget *widget,
				     gpointer  user_data)
{
  message_reader_show_last_body( widget, user_data );
}

void on_combox_turnnmb_changed( GtkWidget *widget,
				     gpointer  user_data)
{
  message_reader_change_messagefile( widget, user_data );
}

void on_message_treeview_select_cursor_row( GtkWidget *widget,
				     gpointer user_data)
{
  g_message( "on_message_treeview_select_cursor_row: NOTHING IMPLEMENTED YET" );
}

void on_message_treeview_row_activated( GtkWidget *widget,
				     gpointer user_data)
{
  g_message( "on_message_treeview_row_activated: NOTHING IMPLEMENTED YET" );
}


void on_message_treeview_cursor_changed( GtkWidget *widget,
				     gpointer user_data)
{
  GtkTreeView *message_tree = (GtkTreeView *)lookup_widget( "message_treeview" );
  GtkTreeModel *model = gtk_tree_view_get_model( message_tree );

/* TODO - question: no gtk_tree_iter_new() ??? */
  GtkTreeIter iter;

  GtkTreeSelection *selection = gtk_tree_view_get_selection( message_tree );
  gtk_tree_selection_get_selected( selection, NULL, &iter );

  gint ident;

  gtk_tree_model_get(model, &iter, COL_IDENT, &ident, -1);
  if( ident >= 0 )
    message_reader_show_body( widget, user_data, ident-1 );



/*

  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  GtkTreeView *message_tree = (GtkTreeView *)lookup_widget( "message_treeview" );
  GtkTreeModel *model = gtk_tree_view_get_model( message_tree );
  GtkTreeIter iter;

  GtkTreeSelection *selection = gtk_tree_view_get_selection( message_tree );
  gtk_tree_selection_get_selected( selection, NULL, &iter );

//  gtk_tree_model_iter_next( model, &iter );
//  gtk_tree_model_
//  gtk_
g_message( "### 1: '%s'", gtk_tree_model_get_string_from_iter( model, &iter ) );
gtk_tree_model_iter_next( model, &iter );
g_message( "### 2: '%s'", gtk_tree_model_get_string_from_iter( model, &iter ) );

//  gint ident;

//  gtk_tree_model_get(model, &iter, COL_IDENT, &ident, -1);
//  if( ident >= 0 )
//    message_reader_show_body( widget, user_data, ident-1 );




*/
}


/* Ship list double-click to open extra panels */
void on_ships_list_row_activated (GtkTreeView *ships_l,
				  GtkTreePath *path,
				  GtkTreeViewColumn *col,
				  gpointer user_data)
{
  GtkTreeModel *model = NULL;
  GtkTreeIter iter;
  static gboolean loaded = FALSE;
  static GtkNotebook *extra_info_panel = NULL;
  static GtkNotebook *mini = NULL;

  if (!loaded) {
    loaded = TRUE;

    extra_info_panel = (GtkNotebook *) lookup_widget("extra_info_panel");
    mini = (GtkNotebook *) lookup_widget("notebook_mini");
  }

  /* Open extra panels */
  starchart_open_extra_ship_panels();  
  
  /* Select ship */
  model = gtk_tree_view_get_model (ships_l);
  if (gtk_tree_model_get_iter(model, &iter, path)) {
    gint ship_id;
    /* get the ship ID from the first column */
    gtk_tree_model_get (model, &iter, 0, &ship_id, -1);

    /* Update panel with new data */
    GwpShip *ship = gwp_ship_get (ship_list, ship_id);
    update_ship_panel_with (ship);

    /* Do extra work only if needed */
    if (gwp_game_state_get_extra_panel_open(game_state)) {
      gtk_notebook_set_current_page (extra_info_panel, EXTRA_PANEL_SHIP_PAGE);
      gtk_notebook_set_current_page (mini, MINI_SHIP_PAGE);

      /* Wait until widgets are in place */
      while (gtk_events_pending())
	gtk_main_iteration();

      /* Center starchart around ship */ 
      starchart_center_around (GWP_OBJECT(ship));
    }
  }  
}


void on_vcr_activate (GtkWidget *widget,
				      gpointer  user_data)
{
  vcr_all_init( widget, user_data );
}


void on_vcr_delete_event( GtkWidget *widget,
                          gpointer  user_data )
{
  vcr_delete_event( widget, user_data );
}


void on_vcr_button_start_combat_pressed( GtkWidget *widget,
                                         gpointer  user_data )
{
  vcr_start_combat( widget, user_data );
}


void on_vcr_checkbutton_base_toggled( GtkWidget *widget,
                                      gpointer  user_data )
{
  vcr_toggle_starbase( widget, user_data );
}



void on_vcr_comboboxentry_sel_ext_shp_a_changed( GtkWidget *widget,
                                                 gpointer  user_data )
{
  vcr_ship_a_selected( widget, user_data );
}


void on_vcr_comboboxentry_sel_race_a_changed( GtkWidget *widget,
                                              gpointer  user_data )
{
  vcr_ship_a_race_selected( widget, user_data );
}


void on_vcr_comboboxentry_sel_race_b_changed( GtkWidget *widget,
                                              gpointer  user_data )
{
  vcr_ship_b_race_selected( widget, user_data );
}


void on_vcr_comboboxentry_sel_type_a_changed( GtkWidget *widget,
                                              gpointer  user_data )
{
  vcr_ship_a_hull_selected( widget, user_data );
}


void on_vcr_comboboxentry_sel_type_b_changed( GtkWidget *widget,
                                              gpointer  user_data )
{
  vcr_ship_b_hull_selected( widget, user_data );
}


void on_vcr_comboboxentry_sel_vcr_changed( GtkWidget *widget,
                                           gpointer  user_data )
{
  vcr_record_selected( widget, user_data );
}


void on_TESTBUTTON_pressed( GtkWidget *widget, gpointer user_data )
{
  vcr_set( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_CUR, 1 );
  vcr_set( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_MAX, 3 );
  vcr_set( widget, user_data, SHIP_B, NMB_TUBEBAY, VAL_CUR, 2 );
  vcr_set( widget, user_data, SHIP_B, NMB_TUBEBAY, VAL_MAX, 4 );
  vcr_set( widget, user_data, SHIP_A, NMB_BEAMS, VAL_CUR, 3 );
  vcr_set( widget, user_data, SHIP_A, NMB_BEAMS, VAL_MAX, 5 );
  vcr_set( widget, user_data, SHIP_B, NMB_BEAMS, VAL_CUR, 4 );
  vcr_set( widget, user_data, SHIP_B, NMB_BEAMS, VAL_MAX, 6 );
}

/* Show python console */
void on_view_python_console_activate (GtkWidget *widget,
				      gpointer user_data)
{
#ifdef USE_PYTHON
  
  FILE *console = fopen (GWP_SCRIPTS_DIR"/gtkcons.py", "r");
  PyRun_SimpleFile(console, "gtkcons.py");
  fclose (console);

#else /* No Python support, warn the user */

  GtkWidget *warn = gwp_warning_dialog_new (gwp,
					    _("No Python support enabled."),
					    _("If you need the Python scripting feature, you should recompile the program after installing Python development packages on your distribution."));
  gtk_dialog_run(GTK_DIALOG(warn));
  gtk_widget_destroy(warn);

#endif
}
