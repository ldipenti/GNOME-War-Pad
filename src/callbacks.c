#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#define GTK_DISABLE_DEPRECATED
#define GNOME_DISABLE_DEPRECATED

#include <gnome.h>

#include "global.h"
#include "game_state.h"
#include "game_mgr.h"
#include "callbacks.h"
#include "support.h"
#include "starchart.h"
#include "vp_utils.h"
#include "vp_unpack.h"
#include "race.h"


gboolean
starchart_event_key                    (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{	
  switch(event->keyval)
    {
      /* Zoom Events */
    case GDK_KP_Add:
      starchart_zoom_in(starchart_get_canvas());
      return TRUE;
    case GDK_KP_Subtract:
      starchart_zoom_out(starchart_get_canvas());
      return TRUE;
      /* Scrolling Events */
    case GDK_w:
      starchart_scroll(0, -SCROLL);
      return TRUE;
    case GDK_s:
      starchart_scroll(0, SCROLL);
      return TRUE;
    case GDK_a:
      starchart_scroll(-SCROLL, 0);
      return TRUE;
    case GDK_d:
      starchart_scroll(SCROLL, 0);
      return TRUE;
      /* Activate/Deactivate Grid */
    case GDK_g:
      starchart_toggle_grid();
      return TRUE;
    }
  return FALSE;
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
  
  /* Get focus on starchart */
  gtk_widget_grab_focus(GTK_WIDGET(starchart_get_canvas()));
  
  /* First get canvas coords */
  x = (gint) event->x;
  y = (gint) event->y;
  
  /* Translate coords to World system */
  gnome_canvas_c2w(starchart_get_canvas(), x, y, &wx, &wy);
  q = get_quadrant(wx, wy);
  
  if((event->button == 1) && (!(event->state & GDK_SHIFT_MASK))) {
    /* Search for nearest planet and select it */
    planets_nearby = starchart_get_surrounding_quads(planets_per_quad, q);
    starchart_select_nearest_planet(GTK_WIDGET(gwp_ptr), 
				    planets_nearby, wx, wy);
  } else if((event->button == 3) && (!(event->state & GDK_SHIFT_MASK))) {
    /* Search for nearest ship and select it */
    ships_nearby = starchart_get_surrounding_quads(ships_per_quad, q);
    starchart_select_nearest_ship(GTK_WIDGET(gwp_ptr), ships_nearby, wx, wy);
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
  gint q;
  GSList *planets_nearby, *ships_nearby;
  static GnomeCanvasItem *planet, *ship;
  static guint interleave;
  static gint pointer_x = 0, pointer_y = 0;
  static gboolean panning = FALSE;
  
  /* First get canvas coords */
  x = (gint) event->x;
  y = (gint) event->y;

  /* If we are dragging the starchart to pan... */
  if((event->state & (GDK_BUTTON1_MASK | GDK_SHIFT_MASK)) 
     == (GDK_BUTTON1_MASK | GDK_SHIFT_MASK)) {
    gint offset_x, offset_y;

    /* Set hand cursor */
    if(!panning) {
      starchart_set_pan_cursor();
      panning = TRUE;
    }

    if((interleave++ % MOUSE_INTERLEAVE) == 0) {
      gnome_canvas_get_scroll_offsets(starchart_get_canvas(), 
				      &offset_x, 
				      &offset_y);
      starchart_scroll_to(offset_x + (pointer_x - x) * (MOUSE_INTERLEAVE+1), 
			  offset_y + (pointer_y - y) * (MOUSE_INTERLEAVE+1));
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
    
    /*
      Every N mouse movements, make the calculations, to avoid
      loading the CPU too much.
    */
    if((interleave++ % MOUSE_INTERLEAVE) == 0) {
      if ((event->x >= 0) && (event->y >= 0)) {
	/* Un-highlight planet before highlighting other */
	starchart_unhighlight_planet(planet);
	starchart_unhighlight_ship(ship);
	
	/* Search for nearest planet and highlight it */
	q = get_quadrant(wx, wy);
	planets_nearby = starchart_get_surrounding_quads(planets_per_quad, q);
	ships_nearby = starchart_get_surrounding_quads(ships_per_quad, q);
	planet = starchart_highlight_nearest_planet(planets_nearby, wx, wy);
	ship = starchart_highlight_nearest_ship(ships_nearby, wx, wy);
      }
    }
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
  GameSettings *settings = (GameSettings *) 
    gnome_icon_list_get_icon_data(iconlist,
				  game_mgr_get_icon_idx_selected());
  game_mgr_play_game(settings);
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

/* Button events on iconlist */
void on_game_mgr_iconlist_select_icon (GnomeIconList *iconlist,
				       gint icon_idx,
				       GdkEventButton *event,
				       gpointer user_data)
{
  /* Displays a pop-up menu */
  if((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
    GtkWidget *popup = NULL;
    
    popup = lookup_widget("game_mgr_popup_menu");
    gtk_menu_popup (GTK_MENU(popup), NULL, NULL, NULL, NULL, 1, 
		    gtk_get_current_event_time());
    return;
  }

  /* Double-click enters the game */
  if((event->type == GDK_2BUTTON_PRESS) && (event->button == 1)) {
    game_mgr_play_game((GameSettings *)
		       gnome_icon_list_get_icon_data(iconlist, 
						     icon_idx));
    return;
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

void on_game_mgr_edit_game(GtkWidget *widget,
			   gpointer user_data)
{
  GtkWidget *iconlist = NULL;
  GtkWidget *ok_button = lookup_widget("game_mgr_button_ok");
  GameSettings *settings = NULL;
  GList *selections = NULL;

  iconlist = lookup_widget("game_mgr_iconlist");
  selections = gnome_icon_list_get_selection(GNOME_ICON_LIST(iconlist));
  if(selections) {
    settings = (GameSettings *) 
      gnome_icon_list_get_icon_data(GNOME_ICON_LIST(iconlist),
				  (gint)g_list_nth_data(selections, 0));
    g_assert(settings != NULL);

    if(game_mgr_properties_dlg_fill(settings)) {

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

      // Update 'Unpack' button status
      if(vp_can_unpack(settings->game_dir, settings->race)) {
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
  GameSettings *settings = NULL;
  GList *selections = NULL;
  
  selections = gnome_icon_list_get_selection(GNOME_ICON_LIST(iconlist));

  if(selections) {
    gint icon_idx = (gint)g_list_nth_data(selections, 0);
    GtkResponseType response;
    GtkWidget *warn;
    gchar *game_name;

    settings = (GameSettings *) 
      gnome_icon_list_get_icon_data(GNOME_ICON_LIST(iconlist),
				    icon_idx);
    g_assert(settings != NULL);
    game_name = g_strdup_printf("%s", settings->game_name);
    game_mgr_game_name_demangle(game_name);

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
      game_mgr_settings_delete(settings->game_name);
      gconf_client_suggest_sync(gwp_gconf, NULL);

      /* Free memory from GameSettings struct */
      game_mgr_settings_free(settings);
      /* Remove icon */
      gnome_icon_list_remove(GNOME_ICON_LIST(iconlist),
			     icon_idx);
    }
  } 
}

void gwp_quit(void)
{
  /* Disconnect from GConf server */
  gconf_client_suggest_sync(gwp_gconf, NULL);
  g_object_unref(gwp_gconf);
  
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
      NULL
    };
    const gchar *documenters[] = {
      "Lucas Di Pentima <lucas@lunix.com.ar>",
      NULL
    };

    about_gwp = gnome_about_new(PACKAGE_NAME,
				PACKAGE_VERSION,
				_("(c) 2002,2003 Lucas Di Pentima\nThis software is released under the GNU GPL License"),
				_("A VGA Planets client for the GNOME platform.\nhttp://www.lunix.com.ar/~ldipenti/gwp/"),
				(const gchar **)authors,
				(const gchar **)documenters,
				NULL,
				gdk_pixbuf_new_from_file(DATA_DIR"/gwp/logo.png",
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

  // Disable button if all ok
  if(! vp_can_unpack(game_dir, *race)) {
    GtkWidget *btn_unpack =
      lookup_widget("game_mgr_btn_unpack");
    gtk_widget_set_sensitive(btn_unpack, FALSE);    
  }
}
