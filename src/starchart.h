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

#ifndef STARCHART_H
#define STARCHART_H

#include "vp_types.h"

// Starchart init function
void init_starchart(GtkWidget *gwp);
void init_starchart_mini(void);

// Starchart Object Event Handlers
gint handle_planet_event(GnomeCanvasItem *item, GdkEvent *event, gpointer data);
gint handle_starchart_event(GnomeCanvas *item, GdkEvent *event, gpointer data);

// Updates Planet Data on Panel
void update_planet_panel(GtkWidget *gwp, gint16 planet_id);
void update_planet_extra_panel (gint16 planet_id);
void update_ship_panel(GtkWidget *gwp, GSList *ship_list);
void starchart_update_coord_panel(GtkWidget *gwp, gdouble wx, gdouble wy);

// Show/Hide Functions
void starchart_show_grid(GnomeCanvas *starchart);
void starchart_hide_grid(GnomeCanvas *starchart);
void starchart_open_extra_panels(void);
void starchart_close_extra_panels(void);

// Drawing functions
void draw_planet(gpointer key, gpointer value, gpointer user_data);
void draw_ship(gpointer key, gpointer value, gpointer user_data);
GnomeCanvasItem *starchart_highlight_nearest_planet(GSList *planets_in_quad, gdouble wx, gdouble wy);
GnomeCanvasItem *starchart_highlight_nearest_ship(GSList *ships_in_quad, gdouble wx, gdouble wy);
GnomeCanvasItem* starchart_select_nearest_planet(GtkWidget *gwp, GSList *planets_nearby, gdouble wx, gdouble wy);
void starchart_select_nearest_ship(GtkWidget* gwp, GSList *ships_nearby, gdouble wx, gdouble wy);
void starchart_unhighlight_planet(GnomeCanvasItem *planet);
void starchart_unhighlight_ship(GnomeCanvasItem *ship);
void starchart_zoom_in(GnomeCanvas *starchart);
void starchart_zoom_out(GnomeCanvas *starchart);
void starchart_mark_planet(Planet *a_planet);

// Moving functions
void starchart_scroll (gint scroll_x, gint scroll_y);

// Find functions
GnomeCanvasItem *starchart_find_nearest_object(GSList *objects_in_quad, gdouble x, gdouble y);
GSList *starchart_get_surrounding_quads(GSList *objects_per_quad[TOTAL_QUADS], gint center_quad);
gint get_quadrant(gdouble x, gdouble y);

gboolean starchart_is_my_planet(GnomeCanvasItem *planet_item);
gboolean starchart_is_my_ship(GnomeCanvasItem *ship_item);
gint get_planet_from_coords(gdouble x_wc, gdouble y_wc);
GSList *get_ships_from_coords(gdouble x_wc, gdouble y_wc);
void starchart_get_object_center_coord(GnomeCanvasItem *item, gdouble *x, gdouble *y);
void starchart_set_default_cursor(void);
void starchart_set_pan_cursor(void);
void starchart_scroll_to(gint cx, gint cy);
void starchart_mini_scroll_zone_to(gint cx, gint cy);
void starchart_set_status(gchar *msg);
void starchart_mini_set_planet_img(Planet *planet);

#endif