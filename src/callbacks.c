#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#define GTK_DISABLE_DEPRECATED
#define GNOME_DISABLE_DEPRECATED

#include <gnome.h>

#include "global.h"
#include "game_state.h"
#include "race_select.h"
#include "callbacks.h"
#include "support.h"
#include "starchart.h"
#include "vp_utils.h"


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

void select_race1_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)1);
}
void select_race2_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)2);
}
void select_race3_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)3);
}
void select_race4_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)4);
}
void select_race5_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)5);
}
void select_race6_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)6);
}
void select_race7_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)7);
}
void select_race8_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)8);
}
void select_race9_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)9);
}
void select_race10_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)10);
}
void select_race11_event(GtkButton *button, gpointer user_data)
{
  select_race_event(button, (gpointer)11);
}

void
on_vp_game_dir_changed                 (GtkEditable     *editable,
                                        gpointer         gwp_select_dlg)
{
  editable = (GtkEditable *) lookup_widget("vp_game_dir");
  game_set_dir(gtk_editable_get_chars(editable, 0, -1));
  gnome_config_set_string("General/game_dir", 
			  gtk_editable_get_chars(editable, 0, -1));
  update_select_dlg((GtkWidget *) gwp_select_dlg);
  
}

