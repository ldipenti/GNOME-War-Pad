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
#include "tables.h"
#include "planet.h"

/*
 * Updates Planet Data on Panel
 */
void update_planet_extra_panel (gint16 planet_id)
{
  GtkCombo *planet_fc;
  GtkProgressBar *neu_ground, *neu_density;
  GtkProgressBar *mol_ground, *mol_density;
  GtkProgressBar *tri_ground, *tri_density;
  GtkProgressBar *dur_ground, *dur_density;
  GtkHScale *tax_col, *tax_nat;
  GtkLabel *mol_rate, *neu_rate, *dur_rate, *tri_rate;
  GtkLabel *tax_nat_earned, *tax_col_earned;
  Planet *a_planet;
  gchar *tmp;

  planet_fc = (GtkCombo *) lookup_widget("combo_planet_fc");  

  neu_ground = (GtkProgressBar *) lookup_widget("progressbar_neu_ground");
  neu_density = (GtkProgressBar *) lookup_widget("progressbar_neu_density");
  mol_ground = (GtkProgressBar *) lookup_widget("progressbar_mol_ground");
  mol_density = (GtkProgressBar *) lookup_widget("progressbar_mol_density");
  tri_ground = (GtkProgressBar *) lookup_widget("progressbar_tri_ground");
  tri_density = (GtkProgressBar *) lookup_widget("progressbar_tri_density");
  dur_ground = (GtkProgressBar *) lookup_widget("progressbar_dur_ground");
  dur_density = (GtkProgressBar *) lookup_widget("progressbar_dur_density");

  tax_nat = (GtkHScale *) lookup_widget("hscale_tax_natives");
  tax_col = (GtkHScale *) lookup_widget("hscale_tax_colonists");

  mol_rate = (GtkLabel *) lookup_widget("label_mol_rate");
  neu_rate = (GtkLabel *) lookup_widget("label_neu_rate");
  tri_rate = (GtkLabel *) lookup_widget("label_tri_rate");
  dur_rate = (GtkLabel *) lookup_widget("label_dur_rate");

  tax_nat_earned = (GtkLabel *) lookup_widget("label_tax_nat_pay");
  tax_col_earned = (GtkLabel *) lookup_widget("label_tax_col_pay");

  /* If we received a valid planet id, we work */
  if ((planet_id >= 1) && (planet_id <= MAX_PLANETS))
    {
      /* If we have data on this planet, then work */
      if ((a_planet = planet_get (planet_list, planet_id)) != NULL &&
	  planet_is_known (a_planet))
	{
	  /*** Friendly Code ***/
	  tmp = g_strdup_printf ("%s", planet_get_fcode(a_planet));
	  gtk_entry_set_text (GTK_ENTRY(planet_fc->entry), tmp);
	  g_free(tmp);

	  /*** Neutronium ***/
	  gtk_progress_bar_set_fraction(neu_ground, planet_get_ground_percent(planet_get_ground_neutronium(a_planet)));
	  tmp = g_strdup_printf("%d kT", 
				planet_get_ground_neutronium(a_planet));
	  gtk_progress_bar_set_text(neu_ground, tmp);
	  g_free(tmp);

	  gtk_progress_bar_set_fraction(neu_density, (planet_get_dens_neutronium(a_planet)/100.0));
	  tmp = g_strdup_printf("%d%%", 
				planet_get_dens_neutronium(a_planet));
	  gtk_progress_bar_set_text(neu_density, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf(_("%d kT/turn"), planet_neutronium_extraction_rate(a_planet));
	  gtk_label_set_text(neu_rate, tmp);
	  g_free(tmp);

	  /*** Duranium ***/
	  gtk_progress_bar_set_fraction(dur_ground, planet_get_ground_percent(planet_get_ground_duranium(a_planet)));
	  tmp = g_strdup_printf("%d kT", 
				planet_get_ground_duranium(a_planet));
	  gtk_progress_bar_set_text(dur_ground, tmp);
	  g_free(tmp);
	  gtk_progress_bar_set_fraction(dur_density, (planet_get_dens_duranium(a_planet)/100.0));
	  tmp = g_strdup_printf("%d%%", 
				planet_get_dens_duranium(a_planet));
	  gtk_progress_bar_set_text(dur_density, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf(_("%d kT/turn"), planet_duranium_extraction_rate(a_planet));
	  gtk_label_set_text(dur_rate, tmp);
	  g_free(tmp);

	  /*** Molybdenum ***/
	  gtk_progress_bar_set_fraction(mol_ground, planet_get_ground_percent(planet_get_ground_molybdenum(a_planet)));
	  tmp = g_strdup_printf("%d kT", 
				planet_get_ground_molybdenum(a_planet));
	  gtk_progress_bar_set_text(mol_ground, tmp);
	  g_free(tmp);
	  gtk_progress_bar_set_fraction(mol_density, (planet_get_dens_molybdenum(a_planet)/100.0));
	  tmp = g_strdup_printf("%d%%", 
				planet_get_dens_molybdenum(a_planet));
	  gtk_progress_bar_set_text(mol_density, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf(_("%d kT/turn"), planet_molybdenum_extraction_rate(a_planet));
	  gtk_label_set_text(mol_rate, tmp);
	  g_free(tmp);

	  /*** Tritanium ***/
	  gtk_progress_bar_set_fraction(tri_ground, planet_get_ground_percent(planet_get_ground_tritanium(a_planet)));
	  tmp = g_strdup_printf("%d kT", 
				planet_get_ground_tritanium(a_planet));
	  gtk_progress_bar_set_text(tri_ground, tmp);
	  g_free(tmp);
	  gtk_progress_bar_set_fraction(tri_density, (planet_get_dens_tritanium(a_planet)/100.0));
	  tmp = g_strdup_printf("%d%%", 
				planet_get_dens_tritanium(a_planet));
	  gtk_progress_bar_set_text(tri_density, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf(_("%d kT/turn"), planet_tritanium_extraction_rate(a_planet));
	  gtk_label_set_text(tri_rate, tmp);
	  g_free(tmp);

	  /*** TAXES ***/
	  gtk_range_set_value(GTK_RANGE(tax_col), 
			      (gdouble)planet_get_tax_colonists(a_planet));
	  gtk_range_set_value(GTK_RANGE(tax_nat),
			      (gdouble)planet_get_tax_natives(a_planet));

	  /* Tax earned */
	  if(planet_get_tax_earned_natives(a_planet) <=
	     planet_get_colonists(a_planet)) {
	    tmp = g_strdup_printf("%d MC", 
				  planet_get_tax_earned_natives(a_planet));
	  } else {
	    tmp = g_strdup_printf("%d <span foreground=\"red\">(%d)</span> MC",
				  planet_get_tax_earned_natives(a_planet),
				  planet_get_colonists(a_planet));
	  }
	  gtk_label_set_markup(tax_nat_earned, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf("%d MC", 
				planet_get_tax_earned_colonists(a_planet));
	  gtk_label_set_text(tax_col_earned, tmp);
	  g_free(tmp);

	} 
      /* Reset panel */
      else {
	gtk_entry_set_text(GTK_ENTRY(planet_fc->entry), "   ");

	gtk_progress_bar_set_fraction(neu_ground, 0.0);
	gtk_progress_bar_set_text(neu_ground, _("n/a kT"));
	gtk_progress_bar_set_fraction(neu_density, 0.0);
	gtk_progress_bar_set_text(neu_density, _("n/a %"));

	gtk_progress_bar_set_fraction(mol_ground, 0.0);
	gtk_progress_bar_set_text(mol_ground, _("n/a kT"));
	gtk_progress_bar_set_fraction(mol_density, 0.0);
	gtk_progress_bar_set_text(mol_density, _("n/a %"));

	gtk_progress_bar_set_fraction(tri_ground, 0.0);
	gtk_progress_bar_set_text(tri_ground, _("n/a kT"));
	gtk_progress_bar_set_fraction(tri_density, 0.0);
	gtk_progress_bar_set_text(tri_density, _("n/a %"));

	gtk_progress_bar_set_fraction(dur_ground, 0.0);
	gtk_progress_bar_set_text(dur_ground, _("n/a kT"));
	gtk_progress_bar_set_fraction(dur_density, 0.0);
	gtk_progress_bar_set_text(dur_density, _("n/a %"));

	gtk_range_set_value(GTK_RANGE(tax_nat), 0.0);
	gtk_range_set_value(GTK_RANGE(tax_col), 0.0);

	gtk_label_set_text(neu_rate, _("n/a kT/turn"));
	gtk_label_set_text(tri_rate, _("n/a kT/turn"));
	gtk_label_set_text(mol_rate, _("n/a kT/turn"));
	gtk_label_set_text(dur_rate, _("n/a kT/turn"));
	
	gtk_label_set_text(tax_nat_earned, _("n/a MC"));
	gtk_label_set_text(tax_col_earned, _("n/a MC"));
      }
    }
}

void update_planet_panel (GtkWidget * gwp, gint16 planet_id)
{
  GtkWidget *planet_page;
  GtkNotebook *panel;
  GtkLabel *planet_name, *mines, *factories, *defenses, *temperature;
  GtkLabel *neutronium, *tritanium, *duranium, *molybdenum, *supplies;
  GtkLabel *colonists, *natives, *native_race, *spi;
  GtkLabel *megacredits, *visibility;
  gchar *tmp;
  Planet *a_planet;

  /* Select the planet page on panel */
  panel = (GtkNotebook *) lookup_widget ("info_panel");
  gtk_notebook_set_current_page (panel, PANEL_PLANET_PAGE);
  planet_page = gtk_notebook_get_nth_page (panel, PANEL_PLANET_PAGE);

  planet_name = (GtkLabel *) lookup_widget ("label_planet");
  mines = (GtkLabel *) lookup_widget ("label_mines");
  factories = (GtkLabel *) lookup_widget ("label_factories");
  defenses = (GtkLabel *) lookup_widget ("label_defenses");

  neutronium = (GtkLabel *) lookup_widget ("label_neutronium");
  tritanium = (GtkLabel *) lookup_widget ("label_tritanium");
  duranium = (GtkLabel *) lookup_widget ("label_duranium");
  molybdenum = (GtkLabel *) lookup_widget ("label_molybdenum");
  supplies = (GtkLabel *) lookup_widget ("label_supplies");
  temperature = (GtkLabel *) lookup_widget("label_temperature");

  colonists = (GtkLabel *) lookup_widget ("label_colonists");
  natives = (GtkLabel *) lookup_widget ("label_natives");
  native_race = (GtkLabel *) lookup_widget ("label_native_race");
  spi = (GtkLabel *) lookup_widget ("label_spi");
  megacredits = (GtkLabel *) lookup_widget("label_mc");
  visibility = (GtkLabel *) lookup_widget("label_visibility");


  /* If we received a valid planet id, we work */
  if ((planet_id >= 1) && (planet_id <= MAX_PLANETS))
    {
      /* If we have data on this planet, then work */
      if ((a_planet = planet_get (planet_list, planet_id)) != NULL &&
	  planet_is_known (a_planet))
	{
	  tmp = g_strdup_printf ("<b>%s</b> (#%d)", 
				 planet_get_name(a_planet),
				 planet_get_id(a_planet));
	  gtk_label_set_markup(planet_name, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf ("%d", planet_get_mines (a_planet));
	  gtk_label_set_text (mines, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf ("%d", planet_get_factories(a_planet));
	  gtk_label_set_text (factories, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf ("%d", planet_get_defense_posts(a_planet));
	  gtk_label_set_text (defenses, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf("%s (%d)", 
				planet_get_temperature_str(a_planet),
				planet_get_temperature_f(a_planet));
	  gtk_label_set_text(temperature, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf ("%d", planet_get_mined_neutronium(a_planet));
	  gtk_label_set_text (neutronium, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf ("%d", planet_get_mined_tritanium(a_planet));
	  gtk_label_set_text (tritanium, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf ("%d", planet_get_mined_duranium(a_planet));
	  gtk_label_set_text (duranium, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf ("%d", planet_get_mined_molybdenum(a_planet));
	  gtk_label_set_text (molybdenum, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf ("%d", planet_get_supplies(a_planet));
	  gtk_label_set_text (supplies, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf ("%d", planet_get_megacredits(a_planet));
	  gtk_label_set_text (megacredits, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf("%d%%", planet_get_visibility(a_planet));
	  gtk_label_set_text(visibility, tmp);
	  g_free(tmp);

	  if(planet_get_happiness_col_change(a_planet) >= 0) {
	    tmp = g_strdup_printf("%d (%d%%, +%d)", 
				  planet_get_colonists (a_planet),
				  planet_get_happiness_colonists(a_planet),
				  planet_get_happiness_col_change(a_planet));
	  } else {
	    tmp = g_strdup_printf("%d (%d%%, <span foreground=\"red\">%d</span>)", 
				  planet_get_colonists (a_planet),
				  planet_get_happiness_colonists(a_planet),
				  planet_get_happiness_col_change(a_planet));
	  }
	  gtk_label_set_markup(colonists, tmp);
	  g_free(tmp);

	  if(planet_get_happiness_nat_change(a_planet) >= 0) {
	    tmp = g_strdup_printf("%d (%d%%, +%d)", 
				  planet_get_natives (a_planet),
				  planet_get_happiness_natives(a_planet),
				  planet_get_happiness_nat_change(a_planet));
	  } else {
	    tmp = g_strdup_printf("%d (%d%%, <span foreground=\"red\">%d</span>)", 
				  planet_get_natives (a_planet),
				  planet_get_happiness_natives(a_planet),
				  planet_get_happiness_nat_change(a_planet));
	  }

	  gtk_label_set_markup(natives, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf("%s", planet_get_native_race_chars(a_planet));
	  gtk_label_set_text (native_race, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf("%s", planet_get_native_spi_chars(a_planet));
	  gtk_label_set_text (spi, tmp);
	  g_free(tmp);

	} else {
	  /** If planet is unknown... */

	  tmp = g_strdup_printf ("<b>%s</b> (#%d)", 
				 planet_get_name(a_planet),
				 planet_get_id(a_planet));
	  gtk_label_set_markup(planet_name, tmp);
	  g_free(tmp);

	  gtk_label_set_text (mines, _("n/a"));
	  gtk_label_set_text (factories, _("n/a"));
	  gtk_label_set_text (defenses, _("n/a"));
	  gtk_label_set_text (temperature, _("n/a"));

	  gtk_label_set_text (neutronium, _("n/a"));
	  gtk_label_set_text (tritanium, _("n/a"));
	  gtk_label_set_text (duranium, _("n/a"));
	  gtk_label_set_text (molybdenum, _("n/a"));
	  gtk_label_set_text (supplies, _("n/a"));

	  gtk_label_set_text (colonists, _("n/a"));
	  gtk_label_set_text (natives, _("n/a"));
	  gtk_label_set_text (native_race, _("n/a"));
	  gtk_label_set_text (spi, _("n/a"));
	  gtk_label_set_text (megacredits, _("n/a"));
	  gtk_label_set_text (visibility, _("n/a"));
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
					"fill_color_rgba", UNIVERSE_COLOR_A, 
					NULL);
	} else {
	  item = gnome_canvas_item_new (ships_group, 
					GNOME_TYPE_CANVAS_ELLIPSE,
					"outline_color", SHIP_COLOR, "x1",
					xi - SHIP_RADIUS, "y1",
					yi - SHIP_RADIUS, "x2",
					xi + SHIP_RADIUS, "y2",
					yi + SHIP_RADIUS, "width_pixels", 1,
					"fill_color_rgba", UNIVERSE_COLOR_A,
					NULL);
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
				    "fill_color_rgba", UNIVERSE_COLOR_A,
				    NULL);
    } else {
      item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				    "outline_color", PLANET_COLOR,
				    "x1", xi - PLANET_RADIUS, "y1",
				    yi - PLANET_RADIUS, "x2",
				    xi + PLANET_RADIUS, "y2",
				    yi + PLANET_RADIUS, "width_pixels", 1,
				    "fill_color_rgba", UNIVERSE_COLOR_A,
				    NULL);
    }
    
    // Bind canvas item with planet data
    g_object_set_data (G_OBJECT (item), "planet_data", planet);
    // Insert item into quadrant
    load_object_per_quad (item, planets_per_quad, xi, yi);
  }
}


void init_starchart (GtkWidget * gwp) 
{
  GnomeCanvasItem *background;
  GnomeCanvasItem *grid_line;
  GnomeCanvasPoints *grid_points_v, *grid_points_h;
  gint i;
  
  // Starchart struct initialization
  starchart_set_grid(TRUE);
  starchart_set_canvas((GnomeCanvas *) lookup_widget ("starchart"));
  starchart_set_grp_root(gnome_canvas_root (starchart_get_canvas()));

  // Set starchart on AA mode
  starchart_get_canvas()->aa = 1;
  gnome_canvas_update_now(starchart_get_canvas());

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
  starchart_set_default_cursor();
  
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
    grid_line = gnome_canvas_item_new (starchart_get_grp_grid(), 
				       GNOME_TYPE_CANVAS_LINE,
				       "fill_color", QUADRANT_GRID_COLOR,
				       "line_style", GDK_LINE_ON_OFF_DASH,
				       "width_pixels", 1,
				       "points", grid_points_v, NULL);
    // Draw Horizontal Line
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
  starchart_scroll_to (x + scroll_x, y + scroll_y);
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

GnomeCanvasItem*
starchart_select_nearest_planet (GtkWidget * gwp, 
				 GSList * planets_nearby,
				 gdouble wx, gdouble wy)
{
  GnomeCanvasItem *planet;
  Planet *planet_data;
  
  planet = starchart_find_nearest_object (planets_nearby, wx, wy);
  planet_data = g_object_get_data (G_OBJECT (planet), "planet_data");
  if (planet_data != NULL) {
    update_planet_panel (gwp, planet_get_id(planet_data));
    update_planet_extra_panel(planet_get_id(planet_data));
    table_population_update(planet_data);
    starchart_mark_planet(planet_data);
    starchart_mini_set_planet_img(planet_data);
    return planet;
  } else {
    return NULL;
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
  gdouble zoom = game_get_starchart_zoom ();
  gchar *zoom_status;
  
  if (zoom < 2.0) {
    zoom = zoom + 0.2;
    gnome_canvas_set_pixels_per_unit (starchart, zoom);
    game_set_starchart_zoom (zoom);
    zoom_status = g_strdup_printf("Zoom: %.1f", zoom);
    starchart_set_status(zoom_status);
    g_free(zoom_status);
  }
}

void starchart_zoom_out (GnomeCanvas * starchart)
{
  gdouble zoom = game_get_starchart_zoom ();
  gchar *zoom_status;
  
  if (zoom > 0.6) {
    zoom = zoom - 0.2;
    gnome_canvas_set_pixels_per_unit (starchart, zoom);
    game_set_starchart_zoom (zoom);
    zoom_status = g_strdup_printf("Zoom: %.1f", zoom);
    starchart_set_status(zoom_status);
    g_free(zoom_status);
  }
}

void starchart_update_coord_panel(GtkWidget *gwp, 
				  gdouble wx, gdouble wy)
{
  GtkLabel *x_coord, *y_coord;
  gchar *x_tmp, *y_tmp;
  gint16 x, y;
  
  x_coord = (GtkLabel *) lookup_widget("label_x_coord");
  y_coord = (GtkLabel *) lookup_widget("label_y_coord");

  /* Get VP coords */
  vp_coord_w2v(wx, wy, &x, &y);
  
  x_tmp = g_strdup_printf("%d", x);
  y_tmp = g_strdup_printf("%d", y);

  /* Update GUI */
  gtk_label_set_text(x_coord, x_tmp);
  gtk_label_set_text(y_coord, y_tmp);

  /* Free stuff */
  g_free(x_tmp);
  g_free(y_tmp);
}

void starchart_set_default_cursor(void)
{
  GdkCursor *cursor = gdk_cursor_new (GDK_TCROSS);
  
  gtk_widget_realize ((GtkWidget *) starchart_get_canvas());
  gdk_window_set_cursor (GTK_WIDGET(starchart_get_canvas())->window, cursor);
  gdk_cursor_destroy (cursor);
}

void starchart_set_pan_cursor(void)
{
  GdkCursor *cursor = gdk_cursor_new (GDK_FLEUR);
  
  gtk_widget_realize ((GtkWidget *) starchart_get_canvas());
  gdk_window_set_cursor (GTK_WIDGET(starchart_get_canvas())->window, cursor);
  gdk_cursor_destroy (cursor);
}

void init_starchart_mini (void) 
{
  GnomeCanvasItem *zone;
  
  /* Starchart struct initialization */
  starchart_mini_set_canvas((GnomeCanvas *) lookup_widget ("starchart_mini"));
  starchart_mini_set_grp_root(gnome_canvas_root (starchart_mini_get_canvas()));

  /* Set on AA mode */
  starchart_mini_get_canvas()->aa = 1;
  gnome_canvas_update_now(starchart_mini_get_canvas());

  /* Sets black background to starchart */
  gnome_canvas_item_new (starchart_mini_get_grp_root(), 
			 GNOME_TYPE_CANVAS_RECT,
			 "outline_color", "grey",
			 "x1", 0.0, "y1", 0.0, "x2", 100.0,
			 "y2", 100.0, "width_units", 1.0,
			 "fill_color", UNIVERSE_COLOR, NULL);
  
  zone = gnome_canvas_item_new (starchart_mini_get_grp_root(),
				GNOME_TYPE_CANVAS_RECT,
				"outline_color", "grey",
				"x1", 0.0, "y1", 0.0,
				"x2", 20.0, "y2", 20.0,
				"fill_color_rgba", UNIVERSE_COLOR_A, NULL);
  gnome_canvas_item_raise_to_top(zone);

  starchart_mini_set_zone(zone);
  /* End struct initialization... */
}

void starchart_scroll_to(gint cx, gint cy)
{
  gnome_canvas_scroll_to(starchart_get_canvas(), cx, cy);
}

void starchart_mini_scroll_zone_to(gint cx, gint cy)
{
  gint x, y, item_x, item_y, final_x, final_y;
  gint trans_x, trans_y;
  GnomeCanvasItem * zone = starchart_mini_get_zone();
  gdouble x1, y1, x2, y2;
  gdouble zoom = game_get_starchart_zoom();

  /* First we do some convertions */
  x = ((cx - 500) * 0.05) / zoom; /* 1/20 -> relation of the two starcharts */
  y = ((cy - 500) * 0.05) / zoom;

  gnome_canvas_item_get_bounds(zone, &x1, &y1, &x2, &y2);
  item_x = x2 - ((x2 - x1) / 2);
  item_y = y2 - ((y2 - y1) / 2);

  trans_x = x - item_x;
  trans_y = y - item_y;

  /* Bounds checks */
  if(trans_x + item_x < 10) {
    final_x = 10 - item_x;
  } else if(trans_x + item_x > 90) {
    final_x = 90 - item_x;
  } else {
    final_x = trans_x;
  }
  if(trans_y + item_y < 10) {
    final_y = 10 - item_y;
  } else if(trans_y + item_y > 90) {
    final_y = 90 - item_y;
  } else {
    final_y = trans_y;
  }

  /* Now move the darn item :-) */
  gnome_canvas_item_move(zone, final_x, final_y);
}

void starchart_set_status(gchar *msg)
{
  if (msg) {
    GnomeAppBar *appbar = (GnomeAppBar *) lookup_widget("gwp_status_bar");
    gnome_appbar_set_status(appbar, msg);
  }
}

void starchart_mark_planet(Planet *a_planet)
{
  static GnomeCanvasItem *planet_mark = NULL;
  static GnomeCanvasItem *planet_mark_l = NULL;
  static GnomeCanvasItem *planet_mark_r = NULL;
  static GnomeCanvasItem *planet_mark_u = NULL;
  static GnomeCanvasItem *planet_mark_d = NULL;
  GnomeCanvasPoints *p;
  gdouble wx, wy;
  gdouble matrix[6];

  vp_coord_v2w(a_planet->x, a_planet->y, &wx, &wy);

  /* If item doesn't exist yet, lets create it. */
  if(! planet_mark) {
    planet_mark = gnome_canvas_item_new (starchart_get_grp_root(), 
					 GNOME_TYPE_CANVAS_ELLIPSE,
					 "outline_color_rgba", 0xff0000ff,
					 "x1", -2.5, 
					 "y1", -2.5,
					 "x2", 2.5,
					 "y2", 2.5, "width_pixels", 1,
					 "fill_color_rgba", 0xdd000011, 
					 NULL);
    p = gnome_canvas_points_new(2);
    p->coords[0] = -7.5;
    p->coords[1] = 0.0;
    p->coords[2] = -2.5;
    p->coords[3] = 0.0;
    planet_mark_l = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "red",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 1,
					   NULL);

    p = gnome_canvas_points_new(2);
    p->coords[0] = 2.5;
    p->coords[1] = 0.0;
    p->coords[2] = 7.5;
    p->coords[3] = 0.0;
    planet_mark_r = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "red",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 1,
					   NULL);

    p = gnome_canvas_points_new(2);
    p->coords[0] = 0.0;
    p->coords[1] = -7.5;
    p->coords[2] = 0.0;
    p->coords[3] = -2.5;
    planet_mark_u = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "red",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 1,
					   NULL);

    p = gnome_canvas_points_new(2);
    p->coords[0] = 0.0;
    p->coords[1] = 2.5;
    p->coords[2] = 0.0;
    p->coords[3] = 7.5;
    planet_mark_d = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "red",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 1,
					   NULL);
  }
  /* Translate the mark! */
  art_affine_translate(matrix, wx, wy);
  gnome_canvas_item_affine_absolute(planet_mark, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_l, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_r, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_u, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_d, matrix);
}

void starchart_open_extra_panels(void)
{
  GtkNotebook *mini =
    (GtkNotebook *) lookup_widget("notebook_mini");

  gtk_widget_show(lookup_widget("extra_info_panel"));
  gtk_widget_show(lookup_widget("calc_panel"));
  /* Switch to planet image view */
  gtk_notebook_set_current_page(mini, 1);
}

void starchart_close_extra_panels(void)
{
  GtkNotebook *mini =
    (GtkNotebook *) lookup_widget("notebook_mini");

  gtk_widget_hide(lookup_widget("extra_info_panel"));
  gtk_widget_hide(lookup_widget("calc_panel"));
  /* Show the mini-map again */
  gtk_notebook_set_current_page(mini, 0);
}

/* Sets the planet image acording to the planet's temp */
void starchart_mini_set_planet_img(Planet *planet) 
{
  GtkImage *p_img = (GtkImage *) lookup_widget("image_planet");
  gchar *img_name = DATADIR"/pixmaps/gwp/planets/planet";

  if(!planet_is_known(planet)) {
    img_name = g_strconcat(img_name, "-unknown.png", NULL);
  } else {
    if((planet_get_temperature_f(planet) >= 0) && 
       (planet_get_temperature_f(planet) <= 9)) {
      img_name = g_strconcat(img_name, "0-9.png", NULL);
    } else if((planet_get_temperature_f(planet) >= 10) && 
	      (planet_get_temperature_f(planet) <= 19)) {
      img_name = g_strconcat(img_name, "10-19.png", NULL);
    } else if((planet_get_temperature_f(planet) >= 20) && 
	      (planet_get_temperature_f(planet) <= 29)) {
      img_name = g_strconcat(img_name, "20-29.png", NULL);
    } else if((planet_get_temperature_f(planet) >= 30) && 
	      (planet_get_temperature_f(planet) <= 39)) {
      img_name = g_strconcat(img_name, "30-39.png", NULL);
    } else if((planet_get_temperature_f(planet) >= 40) && 
	      (planet_get_temperature_f(planet) <= 49)) {
      img_name = g_strconcat(img_name, "40-49.png", NULL);
    } else if((planet_get_temperature_f(planet) >= 50) && 
	      (planet_get_temperature_f(planet) <= 59)) {
      img_name = g_strconcat(img_name, "50-59.png", NULL);
    } else if((planet_get_temperature_f(planet) >= 60) && 
	      (planet_get_temperature_f(planet) <= 69)) {
      img_name = g_strconcat(img_name, "60-69.png", NULL);
    } else if((planet_get_temperature_f(planet) >= 70) && 
	      (planet_get_temperature_f(planet) <= 79)) {
      img_name = g_strconcat(img_name, "70-79.png", NULL);
    } else if((planet_get_temperature_f(planet) >= 80) && 
	      (planet_get_temperature_f(planet) <= 89)) {
      img_name = g_strconcat(img_name, "80-89.png", NULL);
    } else if((planet_get_temperature_f(planet) >= 90) && 
	      (planet_get_temperature_f(planet) <= 100)) {
      img_name = g_strconcat(img_name, "90-100.png", NULL);
    }
  }

  gtk_image_set_from_file(p_img, img_name);

  /* Free stuff */
  g_free(img_name);
}
