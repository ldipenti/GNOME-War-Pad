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

/*
 * Here we will manage the different projection tables and graphics
 */

#include <gnome.h>
#include <math.h>
#include <string.h>

#include "tables.h"
#include "global.h"
#include "support.h"

void table_all_init(void)
{
  table_population_init();
}

void table_population_init(void)
{
  GtkTreeView *table_pop;
  GtkListStore *store;
  GtkTreeViewColumn *column;
  GtkCellRenderer *renderer;

  enum {
    TURN_COLUMN,
    COLONISTS_COLUMN,
    COL_HAPP_COLUMN,
    COL_GROWTH_COLUMN,
    NATIVES_COLUMN,
    NAT_HAPP_COLUMN,
    NAT_GROWTH_COLUMN,
    N_COLUMNS
  };

  table_pop = (GtkTreeView *) lookup_widget("treeview_population");
  store = gtk_list_store_new(N_COLUMNS,   /* Nr. of columns */
			     G_TYPE_INT,  /* Turn number    */
			     G_TYPE_INT,  /* Colonists      */
			     G_TYPE_INT,  /* Col happiness  */
			     G_TYPE_INT,  /* Col growth     */
			     G_TYPE_INT,  /* Natives        */
			     G_TYPE_INT,  /* Nat happiness  */
			     G_TYPE_INT); /* Nat growth     */
  gtk_tree_view_set_model(table_pop, GTK_TREE_MODEL(store));
  renderer = gtk_cell_renderer_text_new();

  column = gtk_tree_view_column_new_with_attributes(_("Turn"), 
						    renderer,
						    "text", TURN_COLUMN,
						    NULL);
  gtk_tree_view_append_column(table_pop, column);

  column = gtk_tree_view_column_new_with_attributes(_("Colonists"), 
						    renderer,
						    "text", COLONISTS_COLUMN,
						    NULL);
  gtk_tree_view_append_column(table_pop, column);

  column = gtk_tree_view_column_new_with_attributes(_("C Happ"),
						    renderer,
						    "text", COL_HAPP_COLUMN,
						    NULL);
  gtk_tree_view_append_column(table_pop, column);

  column = gtk_tree_view_column_new_with_attributes(_("C Growth"), 
						    renderer,
						    "text", COL_GROWTH_COLUMN,
						    NULL);
  gtk_tree_view_append_column(table_pop, column);

  column = gtk_tree_view_column_new_with_attributes(_("Natives"), 
						    renderer,
						    "text", NATIVES_COLUMN,
						    NULL);
  gtk_tree_view_append_column(table_pop, column);

  column = gtk_tree_view_column_new_with_attributes(_("N Happ"), 
						    renderer,
						    "text", NAT_HAPP_COLUMN,
						    NULL);
  gtk_tree_view_append_column(table_pop, column);

  column = gtk_tree_view_column_new_with_attributes(_("N Growth"), 
						    renderer,
						    "text", NAT_GROWTH_COLUMN,
						    NULL);
  gtk_tree_view_append_column(table_pop, column);
}

/* Updates estimation table */
/* FIXME: Checks for mine & factory decay rates aren't being done!!! */
void table_population_update(GwpPlanet *a_planet)
{
  GwpPlanet *planet;
  GtkTreeView *table_pop;
  GtkListStore *store;
  GtkTreeIter iter;
  gint turn = 0;
  gint colonists_before = 0, colonists_growth = 0;
  gint natives_before = 0,  natives_growth = 0;
  gint nat_growth_limit = 0, col_growth_limit = 0;

  enum {
    TURN_COLUMN,
    COLONISTS_COLUMN,
    COL_HAPP_COLUMN,
    COL_GROWTH_COLUMN,
    NATIVES_COLUMN,
    NAT_HAPP_COLUMN,
    NAT_GROWTH_COLUMN,
    N_COLUMNS
  };

  g_assert(GWP_IS_PLANET(a_planet));

  /* Copy planet struct to fake future planet's state */
  planet = gwp_planet_copy(a_planet);

  table_pop = (GtkTreeView *) lookup_widget("treeview_population");
  store = (GtkListStore *) gtk_tree_view_get_model(table_pop);
  g_assert(store != NULL);
  gtk_list_store_clear(store);

  /* Do math if planet is well known */
  if(gwp_planet_is_known(planet) && gwp_planet_is_mine(planet)) {
    natives_before = gwp_planet_get_natives(planet);
    colonists_before = gwp_planet_get_colonists(planet);

    nat_growth_limit = gwp_planet_get_nat_growth_limit(planet);
    col_growth_limit = gwp_planet_get_col_growth_limit(planet);

    for(turn = game_get_turn_number(game_state)+1; 
	turn <= game_get_turn_number(game_state)+11; turn++) {

      /****************************/
      /* Calculate natives growth */
      /****************************/
      if(gwp_planet_get_natives_race(planet) != NATIVE_NONE) {
	/* If they are not siliconoid... */
	if(gwp_planet_get_natives_race(planet) != NATIVE_SILICONOID) {

	  if((gwp_planet_get_natives(planet) < nat_growth_limit) &&
	     (gwp_planet_get_happiness_natives(planet) >= 70)) {

	    natives_growth = round(sin(3.14 * (gdouble)((100 - (gdouble)gwp_planet_get_temperature(planet)) / 100))
				   * ((gdouble)natives_before / 25)
				   * (5.0/(gwp_planet_get_tax_natives(planet) 
					   + 5)));
	    /* Check if next turn will pass the limit */
	    if((natives_before + natives_growth) > nat_growth_limit) {
	      natives_growth = nat_growth_limit - natives_before;
	    }
	  } else {
	    /* No more space! overpopulation! */
	    natives_growth = 0;
	  }

	} /* If they are Siliconoid, treat them specially */
	else {
	  if(gwp_planet_get_natives(planet) < nat_growth_limit) {
	    natives_growth = round(((gdouble)gwp_planet_get_temperature(planet)
				    / 100)
				   * ((gdouble)natives_before / 25)
				   * (5.0/(gwp_planet_get_tax_natives(planet) 
					   + 5)));
	    /* Check if next turn will pass the limit */
	    if((natives_before + natives_growth) > nat_growth_limit) {
	      natives_growth = nat_growth_limit - natives_before;
	    }
	  } else {
	    /* No more space! overpopulation! */
	    natives_growth = 0;
	  }
	}
      } else {
	/* There aren't any natives */
	natives_growth = 0;
      }
      
      /**********************************/
      /*** Calculate colonists growth ***/
      /**********************************/
      if(game_get_race(game_state) != RACE_CRYSTALLINE) {

	if((gwp_planet_get_colonists(planet) < col_growth_limit) &&
	   (gwp_planet_get_happiness_colonists(planet) >= 70)) {

	  colonists_growth = round(sin(3.14 * (gdouble)((100 - (gdouble)gwp_planet_get_temperature(planet)) / 100))
				   * ((gdouble)colonists_before / 20)
				   * (5.0/(gwp_planet_get_tax_colonists(planet)+5)));
	  /* Check if next turn will pass the limit */
	  if((colonists_before + colonists_growth) > col_growth_limit) {
	    colonists_growth = col_growth_limit - colonists_before;
	  }
	} else {
	  /* No more space! overpopulation! */
	  colonists_growth = 0;
	}
      } /* Cystalline calculations */
      else {
	if(gwp_planet_get_colonists(planet) < col_growth_limit) {
	  colonists_growth = round(((gdouble)gwp_planet_get_temperature(planet)/100)
				   * ((gdouble)natives_before / 25)
				   * (5.0/(gwp_planet_get_tax_natives(planet) + 5)));
	  /* Check if next turn will pass the limit */
	  if((colonists_before + colonists_growth) > col_growth_limit) {
	    colonists_growth = col_growth_limit - colonists_before;
	  }
	} else {
	  /* No more space! overpopulation! */
	  colonists_growth = 0;
	}
      }

      gtk_list_store_append(store, &iter); /* Get iterator */
      gtk_list_store_set(store, &iter,
			 TURN_COLUMN, turn,
			 COLONISTS_COLUMN, (colonists_before+colonists_growth),
			 COL_HAPP_COLUMN, gwp_planet_get_happiness_colonists(planet) + gwp_planet_get_happiness_col_change(planet),
			 COL_GROWTH_COLUMN, colonists_growth,
			 NATIVES_COLUMN, (natives_before + natives_growth),
			 NAT_HAPP_COLUMN, gwp_planet_get_happiness_natives(planet) + gwp_planet_get_happiness_nat_change(planet),
			 NAT_GROWTH_COLUMN, natives_growth,
			 -1);

      natives_before += natives_growth;
      colonists_before += colonists_growth;
      gwp_planet_set_happiness_natives(planet, 
				   gwp_planet_get_happiness_natives(planet) 
				   + gwp_planet_get_happiness_nat_change(planet));
      gwp_planet_set_happiness_colonists(planet, 
				     gwp_planet_get_happiness_colonists(planet) 
				     + gwp_planet_get_happiness_col_change(planet));
    }
  }
  g_object_unref(planet);
}
