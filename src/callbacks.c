#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#define GTK_DISABLE_DEPRECATED
#define GNOME_DISABLE_DEPRECATED

#include <gnome.h>

#include "global.h"
#include "game_state.h"
#include "game_mgr.h"
#include "race_select.h"
#include "callbacks.h"
#include "support.h"
#include "starchart.h"
#include "vp_utils.h"
#include "race.h"


void
on_new_file1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_save1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_save_as1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_exit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    // Bye bye
    gtk_main_quit();
}


void
on_cut1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_copy1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_paste1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_clear1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_properties1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_preferences1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

gboolean
starchart_event_key                    (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{	
	switch(event->keyval)
	{
		// Zoom Events
		case GDK_KP_Add:
			starchart_zoom_in(starchart_get_canvas());
			return TRUE;
		case GDK_KP_Subtract:
			starchart_zoom_out(starchart_get_canvas());
			return TRUE;
		// Scrolling Events
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
        // Activate/Deactivate Grid
        case GDK_g:
            starchart_toggle_grid();
            return TRUE;
	}
	return FALSE;
}



gboolean
starchart_event_button                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         gwp_ptr)
{
  gint x, y, q;
  gdouble wx, wy;
  GSList *planets_nearby, *ships_nearby;
  
  // Get focus on starchart
  gtk_widget_grab_focus(GTK_WIDGET(starchart_get_canvas()));
  
  // First get canvas coords
  x = (gint) event->x;
  y = (gint) event->y;
  
  // Translate coords to World system
  gnome_canvas_c2w(starchart_get_canvas(), x, y, &wx, &wy);
  q = get_quadrant(wx, wy);
  
  if(event->button == 1) {
    // Search for nearest planet and select it
    planets_nearby = starchart_get_surrounding_quads(planets_per_quad, q);
    starchart_select_nearest_planet(GTK_WIDGET(gwp_ptr), planets_nearby, wx, wy);
  } else if(event->button == 3) {
    // Search for nearest ship and select it
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
  
  // First get canvas coords
  x = (gint) event->x;
  y = (gint) event->y;
  
  // Translate coords to World system
  gnome_canvas_c2w(GNOME_CANVAS(widget), x, y, &wx, &wy);
  
  // Update coord indicator
  starchart_update_coord_panel(widget, wx, wy);
  
  // Every N mouse movements, make the calculations, to avoid
  // loading the CPU too much.
  if((interleave++ % MOUSE_INTERLEAVE) == 0) {
    if ((event->x >= 0) && (event->y >= 0)) {
      // Un-highlight planet before highlighting other
      starchart_unhighlight_planet(planet);
      starchart_unhighlight_ship(ship);
      
      // Search for nearest planet and highlight it
      q = get_quadrant(wx, wy);
      planets_nearby = starchart_get_surrounding_quads(planets_per_quad, q);
      ships_nearby = starchart_get_surrounding_quads(ships_per_quad, q);
      planet = starchart_highlight_nearest_planet(planets_nearby, wx, wy);
      ship = starchart_highlight_nearest_ship(ships_nearby, wx, wy);
    }
  }
  return FALSE;
}

void
select_race_event                      (GtkButton       *button,
                                        gpointer         user_data)
{
  game_set_race((gint) user_data);
  init_data();
  init_starchart(gwp);
  gtk_widget_hide(gwp_select_race_dialog);
  gtk_widget_show(gwp);
}

void on_vp_game_dir_changed (GtkEditable *editable,
			     gpointer gwp_select_dlg) 
{
  //editable = (GtkEditable *) lookup_widget("vp_game_dir");
  game_set_dir(gtk_editable_get_chars(editable, 0, -1));
  gnome_config_set_string("General/game_dir", 
			  gtk_editable_get_chars(editable, 0, -1));
  update_select_dlg((GtkWidget *) gwp_select_dlg);  
}

void on_game_mgr_game_dir_changed (GtkEditable *editable,
				   gpointer user_data)
{
  char *dir;

  dir = gtk_editable_get_chars(editable, 0, -1);
  game_mgr_update_race_list(dir);
}

void on_game_mgr_new_game (GtkWidget *widget,
			   gpointer user_data)
{
  GtkWidget *iconlist;
  GtkWidget *mgr = lookup_widget("game_mgr");
  GtkWidget *ok_button = lookup_widget("game_mgr_button_ok");

  iconlist = lookup_widget("game_mgr_iconlist");

  // Connect callback to OK button, so that works as a "new game" dialog.
  g_signal_connect(G_OBJECT(ok_button), 
		   "clicked", 
		   G_CALLBACK(game_mgr_cb_new_game), iconlist);
  gtk_window_set_transient_for(GTK_WINDOW(game_mgr_properties), 
			       GTK_WINDOW(mgr));
  gtk_window_set_title(GTK_WINDOW(game_mgr_properties), 
		       _("New Game Properties"));
  gtk_widget_show(game_mgr_properties);
}

// Displays pop-up menu on selected game icon
void on_game_mgr_iconlist_select_icon (GtkWidget *widget,
				       gpointer user_data)
{
  GtkWidget *popup;

  popup = lookup_widget("game_mgr_popup_menu");
  gtk_menu_popup (GTK_MENU(popup), NULL, NULL, NULL, NULL, 1, 
		  gtk_get_current_event_time());
}

void on_game_mgr_button_cancel_clicked (GtkWidget *widget,
					gpointer user_data)
{
  gtk_widget_hide(game_mgr_properties);
  game_mgr_properties_dlg_clean();
}

// Get the race number and assign it to the race name field
void on_game_mgr_properties_race_list_row_activated (GtkWidget *widget,
						     gpointer user_data)
{
  GtkTreeView *race_l;
  GtkTreeSelection *sel;
  GtkTreeModel *model;
  GtkEntry *race_name_entry;
  GtkTreeIter iter;
  gint race;

  race_l = (GtkTreeView *) lookup_widget("game_mgr_properties_race_list");
  model = gtk_tree_view_get_model(race_l);
  sel = gtk_tree_view_get_selection(race_l);
  race = (gint) gtk_tree_selection_get_user_data(sel);

  // get the iterator at the selection
  gtk_tree_selection_get_selected(sel, NULL, &iter);

  // get the "hidden" data from the second column
  gtk_tree_model_get(model, &iter, 
		     1, &race, -1);

  // Copy the race name on the entry
  race_name_entry = (GtkEntry *) lookup_widget("game_mgr_entry_race_name");
  gtk_entry_set_text(race_name_entry, race_get_name(race));

  // Bind its number (the really important data)
  g_object_set_data(G_OBJECT(race_name_entry),
		      "race_number", &race);
}
