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

/*
 * StarChart Helper Functions
 */
#include <gnome.h>
#include <math.h>

#include "vp_types.h"
#include "gwp_types.h"
#include "global.h"
#include "game_state.h"
#include "support.h"
#include "vp_utils.h"
#include "starchart.h"
#include "planet.h"
#include "ship.h"


/*
 * Updates Planet Data on Panel
 */
void update_planet_panel (GtkWidget * gwp, gint16 planet_id)
{
  GList *pnames;
  GtkWidget *planet_page;
  GtkNotebook *panel;
  GtkLabel *planet_name, *mines, *factories, *defenses;
  GtkLabel *neutronium, *tritanium, *duranium, *molybdenum, *supplies;
  GtkLabel *colonists, *natives, *native_race, *spi;
  Planet *a_planet;

  // Select the planet page on panel
  panel = (GtkNotebook *) lookup_widget ("info_panel");
  gtk_notebook_set_current_page (panel, PANEL_PLANET_PAGE);
  planet_page = gtk_notebook_get_nth_page (panel, PANEL_PLANET_PAGE);

  pnames = load_pnames (PNAMES);
  planet_name = (GtkLabel *) lookup_widget ("label_planet");
  mines = (GtkLabel *) lookup_widget ("label_mines");
  factories = (GtkLabel *) lookup_widget ("label_factories");
  defenses = (GtkLabel *) lookup_widget ("label_defenses");

  neutronium = (GtkLabel *) lookup_widget ("label_neutronium");
  tritanium = (GtkLabel *) lookup_widget ("label_tritanium");
  duranium = (GtkLabel *) lookup_widget ("label_duranium");
  molybdenum = (GtkLabel *) lookup_widget ("label_molybdenum");
  supplies = (GtkLabel *) lookup_widget ("label_supplies");

  colonists = (GtkLabel *) lookup_widget ("label_colonists");
  natives = (GtkLabel *) lookup_widget ("label_natives");
  native_race = (GtkLabel *) lookup_widget ("label_native_race");
  spi = (GtkLabel *) lookup_widget ("label_spi");

  // If we received a valid planet id, we work
  if ((planet_id >= 1) && (planet_id <= MAX_PLANETS))
    {
      // If we have data on this planet, then work
      if ((a_planet = planet_get (planet_list, planet_id)) != NULL &&
	  planet_is_known (a_planet))
	{
	  gtk_label_set_text (planet_name,
			      g_strdup_printf ("%s",
					       planet_get_name (a_planet)));
	  gtk_label_set_text (mines,
			      g_strdup_printf ("%d",
					       planet_get_mines (a_planet)));
	  gtk_label_set_text (factories,
			      g_strdup_printf ("%d",
					       planet_get_factories
					       (a_planet)));
	  gtk_label_set_text (defenses,
			      g_strdup_printf ("%d",
					       planet_get_defense_posts
					       (a_planet)));

	  gtk_label_set_text (neutronium,
			      g_strdup_printf ("%d",
					       planet_get_mined_neutronium
					       (a_planet)));
	  gtk_label_set_text (tritanium,
			      g_strdup_printf ("%d",
					       planet_get_mined_tritanium
					       (a_planet)));
	  gtk_label_set_text (duranium,
			      g_strdup_printf ("%d",
					       planet_get_mined_duranium
					       (a_planet)));
	  gtk_label_set_text (molybdenum,
			      g_strdup_printf ("%d",
					       planet_get_mined_molybdenum
					       (a_planet)));
	  gtk_label_set_text (supplies,
			      g_strdup_printf ("%d",
					       planet_get_supplies
					       (a_planet)));

	  gtk_label_set_text (colonists,
			      g_strdup_printf ("%d",
					       planet_get_colonists (a_planet)
					       * 100));
	  gtk_label_set_text (natives,
			      g_strdup_printf ("%d",
					       planet_get_natives (a_planet) *
					       100));
	  gtk_label_set_text (native_race,
			      g_strdup_printf ("%s",
					       planet_get_native_race
					       (a_planet)));
	  gtk_label_set_text (spi,
			      g_strdup_printf ("%s",
					       planet_get_native_spi
					       (a_planet)));
	}
      else
	{
	  gtk_label_set_text (planet_name,
			      g_strdup_printf ("%s",
					       planet_get_name (a_planet)));
	  gtk_label_set_text (mines, "n/a");
	  gtk_label_set_text (factories, "n/a");
	  gtk_label_set_text (defenses, "n/a");

	  gtk_label_set_text (neutronium, "n/a");
	  gtk_label_set_text (tritanium, "n/a");
	  gtk_label_set_text (duranium, "n/a");
	  gtk_label_set_text (molybdenum, "n/a");
	  gtk_label_set_text (supplies, "n/a");

	  gtk_label_set_text (colonists, "n/a");
	  gtk_label_set_text (natives, "n/a");
	  gtk_label_set_text (native_race, "n/a");
	  gtk_label_set_text (spi, "n/a");
	}
    }
}

void update_ship_panel (GtkWidget * gwp, GSList * ship_l)
{
  GtkWidget *ship_page;
  GtkNotebook *panel;

  // FIXME: Deprecated!
  //  GtkList *panel_ship_list;
  //  GtkListItem *panel_ship_list_item;
  // END-FIXME

  GtkLabel *ship_name;
  GList *item_list = NULL;
  Ship *a_ship;
  gint i, ship_id;

  // Select the planet page on panel
  panel = (GtkNotebook *) lookup_widget ("info_panel");
  gtk_notebook_set_current_page (panel, PANEL_SHIP_PAGE);
  ship_page = gtk_notebook_get_nth_page (panel, PANEL_SHIP_PAGE);

  ship_name = (GtkLabel *) lookup_widget ("label_name");

  // FIXME: Revisar esta bosta
  //-->panel_ship_list = (GtkList *) lookup_widget ("ships_list");

  // Load GtkList with ships
  /*
  for (i = 0; i < g_slist_length (ship_l); i++)
    {
      ship_id = (gint) g_slist_nth_data (ship_l, i);
      // If we received a valid planet id, we work
      if ((ship_id >= 1) && (ship_id <= MAX_SHIPS))
	{
	  a_ship = ship_get (ship_list, ship_id);
	  panel_ship_list_item =
	    (GtkListItem *)
	    gtk_list_item_new_with_label (ship_get_name (a_ship));
	  item_list =
	    g_list_append (item_list, (gpointer) panel_ship_list_item);
	}
    }
  gtk_list_append_items (panel_ship_list, item_list);
  */
}

gint get_planet_from_coords (gdouble x_wc, gdouble y_wc)
{
  VpXYPlanReg *planet;
  gint16 x, y;
  gint i;

  // Convert World Coords to VP System
  vp_coord_w2v (x_wc, y_wc, &x, &y);

  for (i = 0; i < g_list_length (xyplanet_list); i++)
    {
      planet = g_list_nth_data (xyplanet_list, i);

      // Check if this is the clicked planet
      if ((x == planet->x) && (y == planet->y))
	{
	  return i + 1;
	}
    }

  // If we don't find the planet...
  return 0;
}

GSList * get_ships_from_coords (gdouble x_wc, gdouble y_wc)
{
  VpShipXYReg *ship;
  GSList *ship_list = NULL;
  gint16 x, y;
  gint i;

  // Convert World Coords to VP System
  vp_coord_w2v (x_wc, y_wc, &x, &y);

  for (i = 0; i < g_list_length (shipxy_list); i++)
    {
      ship = g_list_nth_data (shipxy_list, i);
        
        // Check if this is the clicked ship
      if ((x == ship->x) && (y == ship->y))
	{
	  ship_list = g_slist_append (ship_list, (gpointer) (i + 1));
	}
    }
  return ship_list;
}

void draw_ship (gpointer key, gpointer value, gpointer user_data)
{
    GnomeCanvasItem *item = NULL;
    GnomeCanvasGroup *ships_group;
    gdouble xi, yi;
    GSList *ship_data_list;
    Ship *ship;
    ship = value;
    ships_group = starchart_get_grp_ships_allied();

    // Check if ship coords aren't invalid...and work
    if (ship_valid_coords(ship)) {
      vp_coord_v2w (ship_get_x_position(ship), ship_get_y_position(ship), 
		    &xi, &yi);
      // Check if we don't have a ship in the same place
      if ((item = gnome_canvas_get_item_at (starchart_get_canvas(), 
					    xi, yi)) == NULL) {
	if (ship_is_mine(ship)) {
	  item = gnome_canvas_item_new (ships_group, 
					GNOME_TYPE_CANVAS_ELLIPSE,
					"outline_color", OWNED_SHIP_COLOR,
					"x1", xi - SHIP_RADIUS, "y1",
					yi - SHIP_RADIUS, "x2",
					xi + SHIP_RADIUS, "y2",
					yi + SHIP_RADIUS, "width_pixels", 1,
					"fill_color", UNIVERSE_COLOR, NULL);
	} else {
	  item = gnome_canvas_item_new (ships_group, 
					GNOME_TYPE_CANVAS_ELLIPSE,
					"outline_color", SHIP_COLOR, "x1",
					xi - SHIP_RADIUS, "y1",
					yi - SHIP_RADIUS, "x2",
					xi + SHIP_RADIUS, "y2",
					yi + SHIP_RADIUS, "width_pixels", 1,
					"fill_color", UNIVERSE_COLOR, NULL);
	}
        // Bind canvas item to ship data
        // FIXME!!!
        //ship_data_list = g_malloc(sizeof(GSList));
        //ship_data_list = g_slist_append(ship_data_list, ship);
        //gtk_object_set_data(GTK_OBJECT(item), "ship_data_list", ship_data_list);
        
        // Insert item into quadrant
        load_object_per_quad (item, ships_per_quad, xi, yi);
      } else {
	// Get data list and add this ship data
        //ship_data_list = gtk_object_get_data (GTK_OBJECT (item), "ship_data_list");
        ship_data_list = g_object_get_data (G_OBJECT (item), "ship_data_list");
        ship_data_list = g_slist_append (ship_data_list, ship);
      }
    }
}

void draw_planet (gpointer key, gpointer value, gpointer user_data)
{
  GtkWidget *starchart, *gwp;
  GnomeCanvasItem *item;
  GnomeCanvasGroup *group;
  gdouble xi, yi;
  Planet *planet;

  planet = value;
  gwp = user_data;
  starchart = lookup_widget ("starchart");
  group = gnome_canvas_root (GNOME_CANVAS (starchart));

  // Check if planet coords aren't 0...and work
  if (planet_valid_coords(planet)) {
    vp_coord_v2w (planet->x, planet->y, &xi, &yi);
    
    if (planet_is_mine(planet)) {
      item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				    "outline_color", OWNED_PLANET_COLOR,
				    "x1", xi - PLANET_RADIUS, "y1",
				    yi - PLANET_RADIUS, "x2",
				    xi + PLANET_RADIUS, "y2",
				    yi + PLANET_RADIUS, "width_pixels", 1,
				    "fill_color", UNIVERSE_COLOR, NULL);
    } else {
      item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				    "outline_color", PLANET_COLOR,
				    "x1", xi - PLANET_RADIUS, "y1",
				    yi - PLANET_RADIUS, "x2",
				    xi + PLANET_RADIUS, "y2",
				    yi + PLANET_RADIUS, "width_pixels", 1,
				    "fill_color", "black", NULL);
    }
    
    // Bind canvas item with planet data
    g_object_set_data (G_OBJECT (item), "planet_data", planet);
    // Insert item into quadrant
    load_object_per_quad (item, planets_per_quad, xi, yi);
  }
}


void init_starchart (GtkWidget * gwp) 
{
  GdkCursor *cursor;
  GnomeCanvasItem *background;
  GnomeCanvasItem *grid_line;
  GnomeCanvasPoints *grid_points_v, *grid_points_h;
  gint i;
  
  // Starchart struct initialization
  starchart_set_grid(TRUE);
  starchart_set_canvas((GnomeCanvas *) lookup_widget ("starchart"));
  starchart_set_grp_root(gnome_canvas_root (starchart_get_canvas()));
  
  starchart_set_grp_grid(GNOME_CANVAS_GROUP (gnome_canvas_item_new 
					     (starchart_get_grp_root(), 
					      GNOME_TYPE_CANVAS_GROUP, NULL)));
  
  starchart_set_grp_planets(GNOME_CANVAS_GROUP (gnome_canvas_item_new 
						(starchart_get_grp_root(), 
						 GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_planets_mine(GNOME_CANVAS_GROUP (gnome_canvas_item_new 
						     (starchart_get_grp_root(),
						      GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_planets_enemy(GNOME_CANVAS_GROUP (gnome_canvas_item_new 
						      (starchart_get_grp_root(), 
						       GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_planets_allied(GNOME_CANVAS_GROUP (gnome_canvas_item_new 
						       (starchart_get_grp_root(), 
							GNOME_TYPE_CANVAS_GROUP, NULL)));
  
  starchart_set_grp_ships_mine(GNOME_CANVAS_GROUP (gnome_canvas_item_new 
						   (starchart_get_grp_root(), 
						    GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_ships_enemy(GNOME_CANVAS_GROUP (gnome_canvas_item_new 
						    (starchart_get_grp_root(), 
						     GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_ships_allied(GNOME_CANVAS_GROUP (gnome_canvas_item_new 
						     (starchart_get_grp_root(),
						      GNOME_TYPE_CANVAS_GROUP, NULL)));
  // End struct initialization...
  
  // Initialize mouse cursor
  cursor = gdk_cursor_new (GDK_TCROSS);
  gtk_widget_realize ((GtkWidget *) starchart_get_canvas());
  gdk_window_set_cursor (GTK_WIDGET(starchart_get_canvas())->window, cursor);
  gdk_cursor_destroy (cursor);
  
  // Loads Ships on Starchart
  g_message ("Cargando naves...");
  g_hash_table_foreach (ship_list, (GHFunc) draw_ship, NULL);
  g_message ("Naves cargadas...");
  
  // Sets black background to starchart
  background = gnome_canvas_item_new (starchart_get_grp_root(), 
				      GNOME_TYPE_CANVAS_RECT,
				      "outline_color", "grey",
				      "x1", 0.0, "y1", 0.0, "x2", CANVAS_WIDTH,
				      "y2", CANVAS_WIDTH, "width_units", 1.0,
				      "fill_color", UNIVERSE_COLOR, NULL);
  
  // Sets starchart grid
  grid_points_v = gnome_canvas_points_new (2);
  grid_points_h = gnome_canvas_points_new (2);
  for (i = 0; i < (STARCHART_WIDTH_INT / QUAD_WIDTH_INT) + 1 ; i++) {
    // Vertical lines
    grid_points_v->coords[0] = CANVAS_OFFSET + i * QUAD_WIDTH;
    grid_points_v->coords[1] = CANVAS_OFFSET;
    grid_points_v->coords[2] = CANVAS_OFFSET + i * QUAD_WIDTH;
    grid_points_v->coords[3] = CANVAS_OFFSET + STARCHART_WIDTH;
    // Horizontal lines
    grid_points_h->coords[0] = CANVAS_OFFSET;
    grid_points_h->coords[1] = CANVAS_OFFSET + i * QUAD_WIDTH;
    grid_points_h->coords[2] = CANVAS_OFFSET + STARCHART_WIDTH;
    grid_points_h->coords[3] = CANVAS_OFFSET + i * QUAD_WIDTH;
    // Draw Vertical Line
    grid_line = g_malloc (sizeof (GnomeCanvasItem));
    grid_line = gnome_canvas_item_new (starchart_get_grp_grid(), 
				       GNOME_TYPE_CANVAS_LINE,
				       "fill_color", QUADRANT_GRID_COLOR,
				       "line_style", GDK_LINE_ON_OFF_DASH,
				       "width_pixels", 1,
				       "points", grid_points_v, NULL);
    // Draw Horizontal Line
    grid_line = g_malloc (sizeof (GnomeCanvasItem));
    grid_line = gnome_canvas_item_new (starchart_get_grp_grid(), 
				       GNOME_TYPE_CANVAS_LINE,
				       "fill_color", QUADRANT_GRID_COLOR,
				       "line_style", GDK_LINE_ON_OFF_DASH,
				       "width_pixels", 1,
				       "points", grid_points_h, NULL);
  }
  
  // Loads Planets on Starchart
  g_message("Cargando planetas...");
  g_hash_table_foreach (planet_list, (GHFunc) draw_planet, gwp);
  g_message("Planetas cargados...");
  
  // Set grid up in the item pile.
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_grid()));
  // Put ships above all other objects
  gnome_canvas_item_raise_to_top (GNOME_CANVAS_ITEM (starchart_get_grp_ships_allied()));
  
  // Various bindings
  g_object_set_data (G_OBJECT (starchart_get_canvas()), 
		     "grid_group", starchart_get_grp_grid());
  g_object_set_data (G_OBJECT (starchart_get_canvas()), 
		     "ships_group", starchart_get_grp_ships_allied());
}

void starchart_scroll (gint scroll_x, gint scroll_y)
{
  gint x, y;
  
  gnome_canvas_get_scroll_offsets (starchart_get_canvas(), &x, &y);
  gnome_canvas_scroll_to (starchart_get_canvas(), x + scroll_x, y + scroll_y);
}


GSList * starchart_get_surrounding_quads (GSList * objects_per_quad[TOTAL_QUADS],
					  gint center_quad)
{
  GSList *objects = NULL;
  gint north, east, south, west;
  gint north_east, north_west;
  gint south_east, south_west;

  north = center_quad - QUAD_PER_LINE;
  south = center_quad + QUAD_PER_LINE;
  east = center_quad + 1;
  west = center_quad - 1;
  north_east = north + 1;
  north_west = north - 1;
  south_east = south + 1;
  south_west = south - 1;

  // Depending on the position, add different quads to list
  if ((center_quad >= 0) && (center_quad < TOTAL_QUADS))
    objects =
      g_slist_concat (objects, g_slist_copy (objects_per_quad[center_quad]));
  if ((north >= 0) && (north < TOTAL_QUADS))
    objects =
      g_slist_concat (objects, g_slist_copy (objects_per_quad[north]));
  if ((south >= 0) && (south < TOTAL_QUADS))
    objects =
      g_slist_concat (objects, g_slist_copy (objects_per_quad[south]));
  if ((east >= 0) && (east < TOTAL_QUADS))
    objects = g_slist_concat (objects, g_slist_copy (objects_per_quad[east]));
  if ((west >= 0) && (west < TOTAL_QUADS))
    objects = g_slist_concat (objects, g_slist_copy (objects_per_quad[west]));
  if ((north_west >= 0) && (north_west < TOTAL_QUADS))
    objects =
      g_slist_concat (objects, g_slist_copy (objects_per_quad[north_west]));
  if ((south_west >= 0) && (south_west < TOTAL_QUADS))
    objects =
      g_slist_concat (objects, g_slist_copy (objects_per_quad[south_west]));
  if ((north_east >= 0) && (north_east < TOTAL_QUADS))
    objects =
      g_slist_concat (objects, g_slist_copy (objects_per_quad[north_east]));
  if ((south_east >= 0) && (south_east < TOTAL_QUADS))
    objects =
      g_slist_concat (objects, g_slist_copy (objects_per_quad[south_east]));

  return objects;
}

GnomeCanvasItem * starchart_find_nearest_object (GSList * objects_in_quad, 
						 gdouble x, gdouble y)
{
  gint nr, i;
  gdouble min_dist, dist;
  gdouble px, py;
  GnomeCanvasItem *object, *min_object;

  nr = g_slist_length (objects_in_quad);
  if (nr > 0)
    {
      object = (GnomeCanvasItem *) g_slist_nth_data (objects_in_quad, 0);
      min_object = object;
      starchart_get_object_center_coord (object, &px, &py);
      min_dist = sqrt (((abs (px - x) ^ 2) + (abs (py - y) ^ 2)));
      for (i = 1; i < nr; i++)
	{
	  object = g_slist_nth_data (objects_in_quad, i);
	  starchart_get_object_center_coord (object, &px, &py);
	  dist = sqrt (((abs (px - x) ^ 2) + (abs (py - y) ^ 2)));
	  if (dist < min_dist)
	    {
	      min_dist = dist;
	      min_object = object;
	    }
	}
      return min_object;
    }
  return NULL;
}

void starchart_unhighlight_planet (GnomeCanvasItem * planet)
{
  gdouble x, y;
  
  if (planet != NULL) {
    starchart_get_object_center_coord (planet, &x, &y);
    
    if (starchart_is_my_planet(planet))	{
      gnome_canvas_item_set (planet, "outline_color", OWNED_PLANET_COLOR,
			     "x1", x - PLANET_RADIUS, "y1",
			     y - PLANET_RADIUS, "x2", x + PLANET_RADIUS,
			     "y2", y + PLANET_RADIUS, NULL);
    } else {
      gnome_canvas_item_set (planet, "outline_color", PLANET_COLOR,
			     "x1", x - PLANET_RADIUS, "y1",
			     y - PLANET_RADIUS, "x2", x + PLANET_RADIUS,
			     "y2", y + PLANET_RADIUS, NULL);
    }
  }
}

void starchart_unhighlight_ship (GnomeCanvasItem * ship)
{
  gdouble x, y;
  
  if (ship != NULL) {
    starchart_get_object_center_coord (ship, &x, &y);
    
    if (starchart_is_my_ship(ship)) {
      gnome_canvas_item_set (ship, "outline_color", OWNED_SHIP_COLOR,
			     "x1", x - SHIP_RADIUS, "y1", y - SHIP_RADIUS,
			     "x2", x + SHIP_RADIUS, "y2", y + SHIP_RADIUS,
			     NULL);
    } else {
      gnome_canvas_item_set (ship, "outline_color", SHIP_COLOR,
			     "x1", x - SHIP_RADIUS, "y1", y - SHIP_RADIUS,
			     "x2", x + SHIP_RADIUS, "y2", y + SHIP_RADIUS,
			     NULL);
    }
  }
}

GnomeCanvasItem * starchart_highlight_nearest_planet (GSList * planets_in_quad,
						      gdouble wx, gdouble wy)
{
  GnomeCanvasItem *planet = NULL;
  gdouble x, y;
  
  planet = starchart_find_nearest_object (planets_in_quad, wx, wy);
  if ((planet != NULL) && starchart_is_my_planet (planet)) {
    starchart_get_object_center_coord (planet, &x, &y);
    gnome_canvas_item_set (planet, "outline_color",
			   HIGHLIGHTED_OWNED_PLANET_COLOR, "x1",
			   x - HIGHLIGHTED_PLANET_RADIUS, "y1",
			   y - HIGHLIGHTED_PLANET_RADIUS, "x2",
			   x + HIGHLIGHTED_PLANET_RADIUS, "y2",
			   y + HIGHLIGHTED_PLANET_RADIUS, NULL);
  } else if (planet != NULL) {
    starchart_get_object_center_coord (planet, &x, &y);
    gnome_canvas_item_set (planet, "outline_color",
			   HIGHLIGHTED_PLANET_COLOR, "x1",
			   x - HIGHLIGHTED_PLANET_RADIUS, "y1",
			   y - HIGHLIGHTED_PLANET_RADIUS, "x2",
			   x + HIGHLIGHTED_PLANET_RADIUS, "y2",
			   y + HIGHLIGHTED_PLANET_RADIUS, NULL);
  }
  return planet;
}

GnomeCanvasItem * starchart_highlight_nearest_ship (GSList * ships_in_quad,
						    gdouble wx, gdouble wy)
{
  GnomeCanvasItem *ship = NULL;
  gdouble x, y;
  
  ship = starchart_find_nearest_object (ships_in_quad, wx, wy);
  if ((ship != NULL) && starchart_is_my_ship (ship)) {
    starchart_get_object_center_coord (ship, &x, &y);

    gnome_canvas_item_set (ship, "outline_color",
			   HIGHLIGHTED_OWNED_SHIP_COLOR, "x1",
			   x - HIGHLIGHTED_SHIP_RADIUS, "y1",
			   y - HIGHLIGHTED_SHIP_RADIUS, "x2",
			   x + HIGHLIGHTED_SHIP_RADIUS, "y2",
			   y + HIGHLIGHTED_SHIP_RADIUS, NULL);
  } else if (ship != NULL) {
    starchart_get_object_center_coord (ship, &x, &y);
    gnome_canvas_item_set (ship, "outline_color", HIGHLIGHTED_SHIP_COLOR,
			   "x1", x - HIGHLIGHTED_SHIP_RADIUS, "y1",
			   y - HIGHLIGHTED_SHIP_RADIUS, "x2",
			   x + HIGHLIGHTED_SHIP_RADIUS, "y2",
			   y + HIGHLIGHTED_SHIP_RADIUS, NULL);
  }
  return ship;
}

gboolean starchart_is_my_planet (GnomeCanvasItem * planet_item)
{
  gdouble x, y;
  Planet *planet = NULL;
  
  starchart_get_object_center_coord (planet_item, &x, &y);
  //planet = gtk_object_get_data (GTK_OBJECT (planet_item), "planet_data");
  planet = g_object_get_data (G_OBJECT (planet_item), "planet_data");
  if (planet_what_is (planet) == IS_MINE) {
    return TRUE;
  } else {
    return FALSE;
  }
}

gboolean starchart_is_my_ship (GnomeCanvasItem * ship_item)
{
  /* FIXME: Check this out! *too slow!*
     
  gdouble x, y;
  GSList *ship_l;
  Ship *ship = NULL;
  gint i;
  gboolean answer;
  
  answer = TRUE;
  
  starchart_get_object_center_coord(ship_item, &x, &y);
  ship_l = get_ships_from_coords(x, y);
  for(i = 0; i < g_slist_length(ship_l); i++) {
  ship = g_hash_table_lookup(ship_list, (gconstpointer)g_slist_nth_data(ship_l, i));
  if(ship->owner != game_get_race()) {
  answer = FALSE;
  }
  }
  return answer;
  */
  return TRUE;
}

void
starchart_select_nearest_planet (GtkWidget * gwp, 
				 GSList * planets_nearby,
				 gdouble wx, gdouble wy)
{
  GnomeCanvasItem *planet;
  Planet *planet_data;
  
  planet = starchart_find_nearest_object (planets_nearby, wx, wy);
  //planet_data = gtk_object_get_data (GTK_OBJECT (planet), "planet_data");
  planet_data = g_object_get_data (G_OBJECT (planet), "planet_data");
  if (planet_data != NULL) {
    update_planet_panel (gwp, planet_get_id (planet_data));
  }
}

void starchart_select_nearest_ship (GtkWidget * gwp, 
				    GSList * ships_nearby,
				    gdouble wx, gdouble wy)
{
  GnomeCanvasItem *ship;
  gdouble x, y;
  GSList *ship_list;
  
  ship = starchart_find_nearest_object (ships_nearby, wx, wy);
  starchart_get_object_center_coord (ship, &x, &y);
  ship_list = get_ships_from_coords (x, y);
  update_ship_panel (gwp, ship_list);
}

// (x, y) in world coords
gint get_quadrant (gdouble x, gdouble y)
{
  gint xi, yi;
  xi = (gint) x;
  yi = (gint) y;
  
  return ((xi / QUAD_WIDTH_INT) + ((yi / QUAD_WIDTH_INT) * QUAD_PER_LINE));
}

void starchart_get_object_center_coord (GnomeCanvasItem * item, 
					gdouble * x,
					gdouble * y)
{
  gdouble x1, y1, x2, y2;
  
  gnome_canvas_item_get_bounds (item, &x1, &y1, &x2, &y2);
  
  *x = x1 + ((x2 - x1) / 2);
  *y = y1 + ((y2 - y1) / 2);
}

void starchart_zoom_in (GnomeCanvas * starchart)
{
  gdouble zoom;
  zoom = game_get_starchart_zoom ();
  
  if (zoom < 2.0) {
    zoom = zoom + 0.2;
    gnome_canvas_set_pixels_per_unit (starchart, zoom);
    game_set_starchart_zoom (zoom);
  }
}

void starchart_zoom_out (GnomeCanvas * starchart)
{
  gdouble zoom;
  zoom = game_get_starchart_zoom ();
  
  if (zoom > 0.6) {
    zoom = zoom - 0.2;
    gnome_canvas_set_pixels_per_unit (starchart, zoom);
    game_set_starchart_zoom (zoom);
  }
}

void starchart_update_coord_panel(GtkWidget *gwp, 
				  gdouble wx, gdouble wy)
{
  GtkLabel *x_coord, *y_coord;
  gint16 x, y;
  
  x_coord = (GtkLabel *) lookup_widget("label_x_coord");
  y_coord = (GtkLabel *) lookup_widget("label_y_coord");
  
  // Get VP coords
  vp_coord_w2v(wx, wy, &x, &y);
  
  // Update GUI
  gtk_label_set_text(x_coord, g_strdup_printf("%d", x));
  gtk_label_set_text(y_coord, g_strdup_printf("%d", y));
}
