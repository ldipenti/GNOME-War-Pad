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

#include <gnome.h>
#include <math.h>

#include "vp_types.h"
#include "gwp_types.h"
#include "global.h"
#include "game_state.h"
#include "support.h"
#include "vp_utils.h"
#include "starchart.h"
#include "tables.h"

/*
 * Updates Planet Data on Panel
 */
void update_starbase_panel(GwpPlanet *planet)
{
  GtkProgressBar *tech_engines, *tech_hulls, *tech_beams, *tech_torps;
  GtkProgressBar *base_defenses, *base_fighters, *base_damage;
  gchar *tmp;

  g_assert (GWP_IS_PLANET(planet));
  
  tech_engines = (GtkProgressBar *) lookup_widget("progressbar_tech_engines");
  tech_hulls = (GtkProgressBar *) lookup_widget("progressbar_tech_hulls");
  tech_beams = (GtkProgressBar *) lookup_widget("progressbar_tech_beams");
  tech_torps = (GtkProgressBar *) lookup_widget("progressbar_tech_torps");

  base_defenses = (GtkProgressBar *) 
    lookup_widget("progressbar_base_defenses");
  base_fighters = (GtkProgressBar *) 
    lookup_widget("progressbar_base_fighters");
  base_damage = (GtkProgressBar *) 
    lookup_widget("progressbar_base_damage");

  if(gwp_planet_has_starbase(planet)) {
    GwpStarbase *base = gwp_planet_get_starbase(planet);

    gtk_progress_bar_set_fraction(tech_engines, 
				  (gdouble)gwp_starbase_get_engines_tech(base)/10);
    tmp = g_strdup_printf(_("Engines: %d"), gwp_starbase_get_engines_tech(base));
    gtk_progress_bar_set_text(tech_engines, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(tech_hulls, 
				  (gdouble)gwp_starbase_get_hulls_tech(base)/10);
    tmp = g_strdup_printf(_("Hulls: %d"), gwp_starbase_get_hulls_tech(base));
    gtk_progress_bar_set_text(tech_hulls, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(tech_beams, 
				  (gdouble)gwp_starbase_get_beams_tech(base)/10);
    tmp = g_strdup_printf(_("Beams: %d"), gwp_starbase_get_beams_tech(base));
    gtk_progress_bar_set_text(tech_beams, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(tech_torps, 
				  (gdouble)gwp_starbase_get_torps_tech(base)/10);
    tmp = g_strdup_printf(_("Torpedoes: %d"), gwp_starbase_get_torps_tech(base));
    gtk_progress_bar_set_text(tech_torps, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(base_defenses,
				  (gdouble)gwp_starbase_get_defense(base)/200);
    tmp = g_strdup_printf(_("Defenses: %d"), gwp_starbase_get_defense(base));
    gtk_progress_bar_set_text(base_defenses, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(base_fighters, 
				  (gdouble)gwp_starbase_get_fighters(base)/60);
    tmp = g_strdup_printf(_("Fighters: %d"), gwp_starbase_get_fighters(base));
    gtk_progress_bar_set_text(base_fighters, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(base_damage, 
				  (gdouble)gwp_starbase_get_damage(base)/100);
    tmp = g_strdup_printf(_("Damage: %d%%"), gwp_starbase_get_damage(base));
    gtk_progress_bar_set_text(base_damage, tmp);
    g_free(tmp);

  } else {
    gtk_progress_bar_set_fraction(tech_engines, 0.0);
    gtk_progress_bar_set_text(tech_engines, _("Engines: --"));

    gtk_progress_bar_set_fraction(tech_hulls, 0.0);
    gtk_progress_bar_set_text(tech_hulls, _("Hulls: --"));

    gtk_progress_bar_set_fraction(tech_beams, 0.0);
    gtk_progress_bar_set_text(tech_beams, _("Beams: --"));

    gtk_progress_bar_set_fraction(tech_torps, 0.0);
    gtk_progress_bar_set_text(tech_torps, _("Torpedoes: --"));

    gtk_progress_bar_set_fraction(base_defenses, 0.0);
    gtk_progress_bar_set_text(base_defenses, _("Defenses: --"));

    gtk_progress_bar_set_fraction(base_fighters, 0.0);
    gtk_progress_bar_set_text(base_fighters, _("Fighters: --"));

    gtk_progress_bar_set_fraction(base_damage, 0.0);
    gtk_progress_bar_set_text(base_damage, _("Damage: --"));
  }
}

void update_global_defense_panel(GwpPlanet *planet)
{
  GtkLabel *beams, *beams_type;
  GtkLabel *fighters, *fighter_bays;
  GtkLabel *battle_mass;
  gchar *tmp;

  beams = (GtkLabel *)lookup_widget("label_def_sys_beams");
  beams_type = (GtkLabel *)lookup_widget("label_def_sys_beams_type");
  fighters = (GtkLabel *)lookup_widget("label_def_sys_fighters");
  fighter_bays = (GtkLabel *)lookup_widget("label_def_sys_fighter_bays");
  battle_mass = (GtkLabel *)lookup_widget("label_def_sys_battle_mass");

  if(gwp_planet_is_known(planet)) {
    tmp = g_strdup_printf("%d", gwp_planet_get_def_sys_beams_nr(planet));
    gtk_label_set_label(beams, tmp);
    g_free(tmp);

    gtk_label_set_label(beams_type, "FIXME!!");

    tmp = g_strdup_printf("%d", gwp_planet_get_def_sys_fighters_nr(planet));
    gtk_label_set_label(fighters, tmp);
    g_free(tmp);

    tmp = g_strdup_printf("%d", gwp_planet_get_def_sys_fighter_bays(planet));
    gtk_label_set_label(fighter_bays, tmp);
    g_free(tmp);

    tmp = g_strdup_printf("%d", gwp_planet_get_def_sys_battle_mass(planet));
    gtk_label_set_label(battle_mass, tmp);
    g_free(tmp);
  } else {
    gtk_label_set_label(beams, "--");
    gtk_label_set_label(beams_type, "--");
    gtk_label_set_label(fighters, "--");
    gtk_label_set_label(fighter_bays, "--");
    gtk_label_set_label(battle_mass, "--");
  }
}

void update_planet_extra_panel(gint16 planet_id)
{
  static gboolean loaded = FALSE;
  static GtkCombo *planet_fc = NULL;
  static GtkProgressBar *neu_ground = NULL;
  static GtkProgressBar *neu_density = NULL;
  static GtkProgressBar *mol_ground = NULL;
  static GtkProgressBar *mol_density = NULL;
  static GtkProgressBar *tri_ground = NULL;
  static GtkProgressBar *tri_density = NULL;
  static GtkProgressBar *dur_ground = NULL;
  static GtkProgressBar *dur_density = NULL;
  static GtkHScale *tax_col = NULL;
  static GtkHScale *tax_nat = NULL;
  static GtkLabel *mol_rate = NULL;
  static GtkLabel *neu_rate = NULL;
  static GtkLabel *dur_rate = NULL;
  static GtkLabel *tri_rate = NULL;
  static GtkLabel *tax_nat_earned = NULL;
  static GtkLabel *tax_col_earned = NULL;
  GwpPlanet *a_planet;
  gchar *tmp;

  if (!loaded) {
    loaded = TRUE;
    
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
  }

  /* If we received a valid planet id, we work */
  if ((planet_id >= 1) && (planet_id <= MAX_PLANETS))
    {
      /* If we have data on this planet, then work */
      if ((a_planet = gwp_planet_get (planet_list, planet_id)) != NULL &&
	  gwp_planet_is_known (a_planet))
	{
	  /*** Friendly Code ***/
	  tmp = g_strdup_printf ("%s", gwp_planet_get_fcode(a_planet)->str);
	  gtk_entry_set_text (GTK_ENTRY(planet_fc->entry), tmp);
	  g_free(tmp);

	  /*** Neutronium ***/
	  gtk_progress_bar_set_fraction(neu_ground, gwp_planet_get_ground_percent(gwp_planet_get_ground_neutronium(a_planet)));
	  tmp = g_strdup_printf("%d kT", 
				gwp_planet_get_ground_neutronium(a_planet));
	  gtk_progress_bar_set_text(neu_ground, tmp);
	  g_free(tmp);

	  gtk_progress_bar_set_fraction(neu_density, (gwp_planet_get_dens_neutronium(a_planet)/100.0));
	  tmp = g_strdup_printf("%d%%", 
				gwp_planet_get_dens_neutronium(a_planet));
	  gtk_progress_bar_set_text(neu_density, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf(_("%d kT/turn (%d turns)"), 
				gwp_planet_neutronium_extraction_rate(a_planet),
				gwp_planet_neutronium_turns_left(a_planet));
	  gtk_label_set_text(neu_rate, tmp);
	  g_free(tmp);

	  /*** Duranium ***/
	  gtk_progress_bar_set_fraction(dur_ground, gwp_planet_get_ground_percent(gwp_planet_get_ground_duranium(a_planet)));
	  tmp = g_strdup_printf("%d kT", 
				gwp_planet_get_ground_duranium(a_planet));
	  gtk_progress_bar_set_text(dur_ground, tmp);
	  g_free(tmp);
	  gtk_progress_bar_set_fraction(dur_density, (gwp_planet_get_dens_duranium(a_planet)/100.0));
	  tmp = g_strdup_printf("%d%%", 
				gwp_planet_get_dens_duranium(a_planet));
	  gtk_progress_bar_set_text(dur_density, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf(_("%d kT/turn (%d turns)"), 
				gwp_planet_duranium_extraction_rate(a_planet),
				gwp_planet_duranium_turns_left(a_planet));
	  gtk_label_set_text(dur_rate, tmp);
	  g_free(tmp);

	  /*** Molybdenum ***/
	  gtk_progress_bar_set_fraction(mol_ground, gwp_planet_get_ground_percent(gwp_planet_get_ground_molybdenum(a_planet)));
	  tmp = g_strdup_printf("%d kT", 
				gwp_planet_get_ground_molybdenum(a_planet));
	  gtk_progress_bar_set_text(mol_ground, tmp);
	  g_free(tmp);
	  gtk_progress_bar_set_fraction(mol_density, (gwp_planet_get_dens_molybdenum(a_planet)/100.0));
	  tmp = g_strdup_printf("%d%%", 
				gwp_planet_get_dens_molybdenum(a_planet));
	  gtk_progress_bar_set_text(mol_density, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf(_("%d kT/turn (%d turns)"), 
				gwp_planet_molybdenum_extraction_rate(a_planet),
				gwp_planet_molybdenum_turns_left(a_planet));
	  gtk_label_set_text(mol_rate, tmp);
	  g_free(tmp);

	  /*** Tritanium ***/
	  gtk_progress_bar_set_fraction(tri_ground, gwp_planet_get_ground_percent(gwp_planet_get_ground_tritanium(a_planet)));
	  tmp = g_strdup_printf("%d kT", 
				gwp_planet_get_ground_tritanium(a_planet));
	  gtk_progress_bar_set_text(tri_ground, tmp);
	  g_free(tmp);
	  gtk_progress_bar_set_fraction(tri_density, (gwp_planet_get_dens_tritanium(a_planet)/100.0));
	  tmp = g_strdup_printf("%d%%", 
				gwp_planet_get_dens_tritanium(a_planet));
	  gtk_progress_bar_set_text(tri_density, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf(_("%d kT/turn (%d turns)"), 
				gwp_planet_tritanium_extraction_rate(a_planet),
				gwp_planet_tritanium_turns_left(a_planet));
	  gtk_label_set_text(tri_rate, tmp);
	  g_free(tmp);

	  /*** TAXES ***/
	  gtk_range_set_value(GTK_RANGE(tax_col), 
			      (gdouble)gwp_planet_get_tax_colonists(a_planet));
	  gtk_range_set_value(GTK_RANGE(tax_nat),
			      (gdouble)gwp_planet_get_tax_natives(a_planet));

	  /* Tax earned */
	  if(gwp_planet_get_tax_earned_natives(a_planet) <=
	     gwp_planet_get_colonists(a_planet)) {
	    tmp = g_strdup_printf("%d MC", 
				  gwp_planet_get_tax_earned_natives(a_planet));
	  } else {
	    tmp = g_strdup_printf("%d <span foreground=\"red\">(%d)</span> MC",
				  gwp_planet_get_tax_earned_natives(a_planet),
				  gwp_planet_get_colonists(a_planet));
	  }
	  gtk_label_set_markup(tax_nat_earned, tmp);
	  g_free(tmp);

	  tmp = g_strdup_printf("%d MC", 
				gwp_planet_get_tax_earned_colonists(a_planet));
	  gtk_label_set_text(tax_col_earned, tmp);
	  g_free(tmp);

	} 
      /* Reset panel */
      else {
	gtk_entry_set_text(GTK_ENTRY(planet_fc->entry), "   ");

	gtk_progress_bar_set_fraction(neu_ground, 0.0);
	gtk_progress_bar_set_text(neu_ground, _("-- kT"));
	gtk_progress_bar_set_fraction(neu_density, 0.0);
	gtk_progress_bar_set_text(neu_density, _("-- %"));

	gtk_progress_bar_set_fraction(mol_ground, 0.0);
	gtk_progress_bar_set_text(mol_ground, _("-- kT"));
	gtk_progress_bar_set_fraction(mol_density, 0.0);
	gtk_progress_bar_set_text(mol_density, _("-- %"));

	gtk_progress_bar_set_fraction(tri_ground, 0.0);
	gtk_progress_bar_set_text(tri_ground, _("-- kT"));
	gtk_progress_bar_set_fraction(tri_density, 0.0);
	gtk_progress_bar_set_text(tri_density, _("-- %"));

	gtk_progress_bar_set_fraction(dur_ground, 0.0);
	gtk_progress_bar_set_text(dur_ground, _("-- kT"));
	gtk_progress_bar_set_fraction(dur_density, 0.0);
	gtk_progress_bar_set_text(dur_density, _("-- %"));

	gtk_range_set_value(GTK_RANGE(tax_nat), 0.0);
	gtk_range_set_value(GTK_RANGE(tax_col), 0.0);

	gtk_label_set_text(neu_rate, _("-- kT/turn"));
	gtk_label_set_text(tri_rate, _("-- kT/turn"));
	gtk_label_set_text(mol_rate, _("-- kT/turn"));
	gtk_label_set_text(dur_rate, _("-- kT/turn"));
	
	gtk_label_set_text(tax_nat_earned, _("-- MC"));
	gtk_label_set_text(tax_col_earned, _("-- MC"));
      }
    }
}

void update_planet_panel (GtkWidget * gwp, GwpPlanet *a_planet)
{
  static gboolean loaded = FALSE;
  static GtkNotebook *panel = NULL;
  static GtkLabel *planet_name = NULL;
  static GtkLabel *mines = NULL;
  static GtkLabel *factories = NULL;
  static GtkLabel *defenses = NULL;
  static GtkLabel *temperature = NULL;
  static GtkLabel *neutronium = NULL;
  static GtkLabel *tritanium = NULL;
  static GtkLabel *duranium = NULL;
  static GtkLabel *molybdenum = NULL;
  static GtkLabel *supplies = NULL;
  static GtkLabel *colonists = NULL;
  static GtkLabel *natives = NULL;
  static GtkLabel *natives_race = NULL;
  static GtkLabel *spi = NULL;
  static GtkLabel *megacredits = NULL;
  static GtkLabel *visibility = NULL;
  static GtkLabel *coords = NULL;
  gchar *tmp = NULL;

  g_assert (GWP_IS_PLANET(a_planet));

  if (!loaded) {
    loaded = TRUE;

    panel = (GtkNotebook *) lookup_widget ("info_panel");

    planet_name = (GtkLabel *) lookup_widget ("label_planet");
    mines = (GtkLabel *) lookup_widget ("label_mines");
    factories = (GtkLabel *) lookup_widget ("label_factories");
    defenses = (GtkLabel *) lookup_widget ("label_defenses");
    coords = (GtkLabel *) lookup_widget ("label_coords");
    
    neutronium = (GtkLabel *) lookup_widget ("label_neutronium");
    tritanium = (GtkLabel *) lookup_widget ("label_tritanium");
    duranium = (GtkLabel *) lookup_widget ("label_duranium");
    molybdenum = (GtkLabel *) lookup_widget ("label_molybdenum");
    supplies = (GtkLabel *) lookup_widget ("label_supplies");
    temperature = (GtkLabel *) lookup_widget("label_temperature");
    
    colonists = (GtkLabel *) lookup_widget ("label_colonists");
    natives = (GtkLabel *) lookup_widget ("label_natives");
    natives_race = (GtkLabel *) lookup_widget ("label_native_race");
    spi = (GtkLabel *) lookup_widget ("label_spi");
    megacredits = (GtkLabel *) lookup_widget("label_mc");
    visibility = (GtkLabel *) lookup_widget("label_visibility");
  }

  /* Select the planet page on panel */
  gtk_notebook_set_current_page (panel, PANEL_PLANET_PAGE);

  /* If we have data on this planet, then work */
  if (gwp_planet_is_known (a_planet)) {

    /* Underline planet name if it has starbase */
    if(gwp_planet_has_starbase (a_planet)) {
      tmp = g_strdup_printf ("<u><b>%s</b></u> (#%d)", 
			     gwp_object_get_name (GWP_OBJECT(a_planet))->str,
			     gwp_object_get_id (GWP_OBJECT(a_planet)));
    } else {
      tmp = g_strdup_printf ("<b>%s</b> (#%d)", 
			     gwp_object_get_name (GWP_OBJECT(a_planet))->str,
			     gwp_object_get_id (GWP_OBJECT(a_planet)));
    }
    gtk_label_set_markup(planet_name, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf ("%d", gwp_planet_get_mines (a_planet));
    gtk_label_set_text (mines, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf ("%d", gwp_planet_get_factories (a_planet));
    gtk_label_set_text (factories, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf ("%d", gwp_planet_get_defense_posts (a_planet));
    gtk_label_set_text (defenses, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf("%s (%d)", 
			  gwp_planet_get_temperature_str (a_planet),
			  gwp_planet_get_temperature_f (a_planet));
    gtk_label_set_text(temperature, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf ("%d", gwp_planet_get_mined_neutronium (a_planet));
    gtk_label_set_text (neutronium, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf ("%d", gwp_planet_get_mined_tritanium (a_planet));
    gtk_label_set_text (tritanium, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf ("%d", gwp_planet_get_mined_duranium (a_planet));
    gtk_label_set_text (duranium, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf ("%d", gwp_planet_get_mined_molybdenum (a_planet));
    gtk_label_set_text (molybdenum, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf ("%d", gwp_planet_get_supplies (a_planet));
    gtk_label_set_text (supplies, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf ("%d", gwp_planet_get_megacredits (a_planet));
    gtk_label_set_text (megacredits, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf("%d%%", gwp_planet_get_visibility (a_planet));
    gtk_label_set_text(visibility, tmp);
    g_free(tmp);

    tmp = g_strdup_printf("%d , %d", 
			  gwp_object_get_x_coord (GWP_OBJECT(a_planet)),
			  gwp_object_get_y_coord (GWP_OBJECT(a_planet)));
    gtk_label_set_text(coords, tmp);
    g_free(tmp);
	
    if(gwp_planet_get_happiness_col_change (a_planet) >= 0) {
      tmp = g_strdup_printf ("%d (%d%%, +%d)", 
			     gwp_planet_get_colonists (a_planet),
			     gwp_planet_get_happiness_colonists (a_planet),
			     gwp_planet_get_happiness_col_change (a_planet));
    } else {
      tmp = g_strdup_printf ("%d (%d%%, <span foreground=\"red\">%d</span>)", 
			     gwp_planet_get_colonists (a_planet),
			     gwp_planet_get_happiness_colonists (a_planet),
			     gwp_planet_get_happiness_col_change (a_planet));
    }
    gtk_label_set_markup (colonists, tmp);
    g_free (tmp);
	
    if(gwp_planet_get_happiness_nat_change (a_planet) >= 0) {
      tmp = g_strdup_printf ("%d (%d%%, +%d)", 
			     gwp_planet_get_natives (a_planet),
			     gwp_planet_get_happiness_natives (a_planet),
			     gwp_planet_get_happiness_nat_change (a_planet));
    } else {
      tmp = g_strdup_printf ("%d (%d%%, <span foreground=\"red\">%d</span>)", 
			     gwp_planet_get_natives (a_planet),
			     gwp_planet_get_happiness_natives (a_planet),
			     gwp_planet_get_happiness_nat_change (a_planet));
    }
	
    gtk_label_set_markup (natives, tmp);
    g_free (tmp);
	
    tmp = g_strdup_printf("%s", gwp_planet_get_natives_race_chars (a_planet));
    gtk_label_set_text (natives_race, tmp);
    g_free(tmp);
	
    tmp = g_strdup_printf("%s", gwp_planet_get_natives_spi_chars (a_planet));
    gtk_label_set_text (spi, tmp);
    g_free(tmp);
	
  } else {
    /** If planet is unknown... */
	
    tmp = g_strdup_printf ("<b>%s</b> (#%d)", 
			   gwp_object_get_name (GWP_OBJECT(a_planet))->str,
			   gwp_object_get_id (GWP_OBJECT(a_planet)));
    gtk_label_set_markup(planet_name, tmp);
    g_free(tmp);
	
    gtk_label_set_text (mines, "--");
    gtk_label_set_text (factories, "--");
    gtk_label_set_text (defenses, "--");
    gtk_label_set_text (temperature, "--");
	
    gtk_label_set_text (neutronium, "--");
    gtk_label_set_text (tritanium, "--");
    gtk_label_set_text (duranium, "--");
    gtk_label_set_text (molybdenum, "--");
    gtk_label_set_text (supplies, "--");
	
    gtk_label_set_text (colonists, "--");
    gtk_label_set_text (natives, "--");
    gtk_label_set_text (natives_race, "--");
    gtk_label_set_text (spi, "--");
    gtk_label_set_text (megacredits, "--");
    gtk_label_set_text (visibility, "--");

    /* Planet coords are always known */
    tmp = g_strdup_printf("%d , %d", 
			  gwp_object_get_x_coord (GWP_OBJECT(a_planet)),
			  gwp_object_get_y_coord (GWP_OBJECT(a_planet)));
    gtk_label_set_text(coords, tmp);
    g_free(tmp);
  }
}

/* Completes the ship panel with the selected ship's data */
void update_ship_panel_with (GwpShip *ship)
{
  static gboolean loaded = FALSE;
  static GtkLabel *waypoint = NULL;
  static GtkLabel *distance = NULL;
  static GtkLabel *speed = NULL;
  static GtkLabel *eta = NULL;
  static GtkLabel *mass = NULL;
  static GtkLabel *fuel_usage = NULL;
  static GtkLabel *heading = NULL;
  static GtkLabel *hull = NULL;
  gchar *tmp = NULL;

  if (! loaded) {
    loaded = TRUE;

    waypoint = (GtkLabel *) lookup_widget("label_ship_panel_waypoint");
    distance = (GtkLabel *) lookup_widget("label_ship_panel_distance");
    heading = (GtkLabel *) lookup_widget("label_ship_panel_heading");
    speed = (GtkLabel *) lookup_widget("label_ship_panel_speed");
    eta = (GtkLabel *) lookup_widget("label_ship_panel_eta");
    mass = (GtkLabel *) lookup_widget("label_ship_panel_mass");
    fuel_usage = (GtkLabel *) lookup_widget("label_ship_panel_fuel");
    hull = (GtkLabel *) lookup_widget("label_ship_panel_hull_type");
  }

  g_assert(GWP_IS_SHIP(ship));

  if (gwp_ship_is_mine(ship)) {
    /* Update waypoint */
    gint x, y;
    gwp_ship_get_waypoint(ship, &x, &y);
    tmp = g_strdup_printf("(%d , %d)", x, y);
    gtk_label_set_text(waypoint, tmp);
    g_free(tmp);

    /* Update distance */
    tmp = g_strdup_printf(_("%.2f LY"), gwp_ship_calculate_waypoint_distance(ship));
    gtk_label_set_text(distance, tmp);
    g_free(tmp);

    /* Update fuel usage */
    tmp = g_strdup_printf (_("%d KT"), gwp_ship_calculate_fuel_usage(ship));
    gtk_label_set_text (fuel_usage, tmp);
    g_free (tmp);

    /* Update mass */
    tmp = g_strdup_printf (_("%d KT"), gwp_ship_calculate_mass(ship));
    gtk_label_set_text (mass, tmp);
    g_free (tmp);

    /* Update ETA */
    gint e = gwp_ship_calculate_eta (ship);
    if (e == 1) {
      tmp = g_strdup_printf(_("%d turn"), e);
    } else {
      tmp = g_strdup_printf(_("%d turns"), e);
    }
    gtk_label_set_text (eta, tmp);
    g_free(tmp);
  }
  /* If it's not a ship, reset all fields */
  else {
    gtk_label_set_text(waypoint, "--");
    gtk_label_set_text(distance, "--");
    gtk_label_set_text(eta, "--");
    gtk_label_set_text(mass, "--");
    gtk_label_set_text(fuel_usage, "--");
    gtk_label_set_text(eta, "--");
  }

  /* 
   * These are valid for all ships.
   */
  /* Update heading */
  gint h = gwp_fo_get_heading(GWP_FLYING_OBJECT(ship));
  if(h != -1) {
    gchar *hstr = gwp_fo_get_heading_str(GWP_FLYING_OBJECT(ship))->str;
    tmp = g_strdup_printf("%d\302\260 (%s)", h, hstr);
  } else {
    tmp = g_strdup_printf(_("not moving"));
  }
  gtk_label_set_text(heading, tmp);
  g_free(tmp);
  
  /* Update speed */
  tmp = g_strdup_printf("%d", gwp_fo_get_speed(GWP_FLYING_OBJECT(ship)));
  gtk_label_set_text(speed, tmp);
  g_free(tmp);
  
  /* Update Hull Type */
  GwpHullSpec *hspec = gwp_ship_get_hullspec (ship);
  tmp = g_strdup_printf ("<i>%s</i>", 
			 gwp_hullspec_get_name_trunc(hspec, 20)->str);
  gtk_label_set_markup (hull, tmp);
  g_free(tmp);

  /* Update ship image */
  starchart_mini_set_ship_img(ship);
}

/* Given a GwpLocation, is shows how many ships are available */
void update_ship_panel (GtkWidget * gwp, GwpLocation * location)
{
  GtkLabel *summary = NULL;
  GwpShip *ship;
  gchar *tmp;
  guint ships_nr = 0;
  gint i;
  GtkTreeView *panel_ship_list = NULL;
  GtkListStore *store;
  GtkTreeIter iter;
  GtkTreePath *path;
  
  /* Select the ship page on panel */
  gtk_notebook_set_current_page (lookup_widget ("info_panel"),
				 PANEL_SHIP_PAGE);

  /* Select the ship page on mini panel */
  gtk_notebook_set_current_page (lookup_widget ("extra_info_panel"), 
				 EXTRA_PANEL_SHIP_PAGE);

  /* Retrieve all info widgets */
  summary = (GtkLabel *) lookup_widget ("label_ship_panel_summary");
  
  /* Set up ship list */
  panel_ship_list = (GtkTreeView *) lookup_widget ("ships_list");
  store = (GtkListStore *) gtk_tree_view_get_model (panel_ship_list);
  g_assert (store != NULL);
  gtk_list_store_clear (store);

  ships_nr = gwp_location_objects_nr(location);

  /* Set up summary label */
  if (ships_nr == 1) {
    tmp = g_strdup_printf (_("%d ship in (%d , %d)"), 
			   ships_nr,
			   gwp_object_get_x_coord(GWP_OBJECT(location)),
			   gwp_object_get_y_coord(GWP_OBJECT(location)));
    gtk_label_set_text (summary, tmp);
    g_free (tmp);
  } else {
    tmp = g_strdup_printf (_("%d ships in (%d , %d)"), 
			   ships_nr,
			   gwp_object_get_x_coord(GWP_OBJECT(location)),
			   gwp_object_get_y_coord(GWP_OBJECT(location)));
    gtk_label_set_text (summary, tmp);
    g_free (tmp);
  }

  /* Load GtkTreeView with ships */
  for (i = 0; i < ships_nr; i++) {
    /* Get ship from location */
    ship = gwp_location_get_object(location, i);

    /* Check if we have the ship's ID, this is because if we don't have it,
     it means that the ship appear on SHIPXY.DAT, but not on TARGETx.DAT 
     and TARGETx.EXT doesn't exist */
    if (gwp_object_get_id (GWP_OBJECT(ship)) > 0) {

      /* Add item to ship list */
      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter,
			  0, gwp_object_get_id (GWP_OBJECT(ship)),
			  1, g_strdup_printf("%s", gwp_object_get_name(GWP_OBJECT(ship))->str),
			  -1);
      
      /* Select first ship on list */
      path = gtk_tree_model_get_path (GTK_TREE_MODEL(store), &iter);
      gtk_tree_view_scroll_to_cell (panel_ship_list, path, NULL, TRUE, 1.0, 0.0);
      gtk_tree_view_set_cursor (panel_ship_list, path, NULL, FALSE);
      gtk_tree_path_free (path);
    }
  }
}

gint get_planet_from_coords (gdouble x_wc, gdouble y_wc)
{
  VpXYPlanReg *planet;
  gint16 x, y;
  gint i;

  /* Convert World Coords to VP System */
  vp_coord_w2v (x_wc, y_wc, &x, &y);

  for (i = 0; i < g_list_length (xyplanet_list); i++) {
    planet = g_list_nth_data (xyplanet_list, i);
    
    /* Check if this is the clicked planet */
    if ((x == planet->x) && (y == planet->y))	{
      return i + 1;
    }
  }
  
  /* If we don't find the planet... */
  return 0;
}

GSList * get_ships_from_coords (gdouble x_wc, gdouble y_wc)
{
  VpShipXYReg *ship;
  GSList *ship_list = NULL;
  gint16 x, y;
  gint i;

  /* Convert World Coords to VP System */
  vp_coord_w2v (x_wc, y_wc, &x, &y);

  for (i = 0; i < g_list_length (shipxy_list); i++) {
    ship = g_list_nth_data (shipxy_list, i);
    
    /* Check if this is the clicked ship */
    if ((x == ship->x) && (y == ship->y)) {
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
  gint xv, yv, q;
  GwpShip *ship;
  GSList *locations_nearby = NULL;
  GwpLocation *location;
  
  ship = value;
  ships_group = starchart_get_grp_ships_allied(); /*FIXME: only allied!!*/
  
  /* Check if ship coords aren't invalid...and work */
  if (gwp_ship_valid_coords (ship)) {
    xv = gwp_object_get_x_coord (GWP_OBJECT(ship));
    yv = gwp_object_get_y_coord (GWP_OBJECT(ship));
    vp_coord_v2w (xv, yv, &xi, &yi);

    /* Check if we don't have a ship in the same place */
    q = get_quadrant(xi, yi);
    locations_nearby = starchart_get_surrounding_quads (locations_per_quad, q);
    location = starchart_find_location (locations_nearby, xv, yv);
    
    if (! GWP_IS_LOCATION (location)) {
      GnomeCanvasPoints *points;
      
      /* Generate polygon points for triangle */
      points = gnome_canvas_points_new(3);
      points->coords[0] = xi - 1.5; /* 1st point */
      points->coords[1] = yi + 1.5;
      points->coords[2] = xi + 1.5; /* 2nd point */
      points->coords[3] = yi + 1.5;
      points->coords[4] = xi; /* 3rd point */
      points->coords[5] = yi - 3.0;

      if (gwp_ship_is_mine(ship)) {
	item = gnome_canvas_item_new (ships_group, 
				      GNOME_TYPE_CANVAS_POLYGON,
				      "outline_color_rgba", OWNED_SHIP_COLOR,
				      "points", points,
				      "width_pixels", 1,
				      "fill_color_rgba", OWNED_SHIP_COLOR, 
				      NULL);
      } else {
	item = gnome_canvas_item_new (ships_group, 
				      GNOME_TYPE_CANVAS_POLYGON,
				      "outline_color_rgba", SHIP_COLOR, 
				      "points", points,
				      "width_pixels", 1,
				      "fill_color_rgba", SHIP_COLOR,
				      NULL);
      }
      starchart_rotate_ship (ship, item);
      gnome_canvas_item_raise_to_top(item);
      gnome_canvas_points_free(points);
      
      /* Instantiate a new location and add the ship to it */
      location = gwp_location_new();
      gwp_object_set_x_coord (GWP_OBJECT(location), xv);
      gwp_object_set_y_coord (GWP_OBJECT(location), yv);
      gwp_location_add_object (location, GWP_OBJECT(ship));
      load_object_per_quad (location, locations_per_quad, xi, yi);
      
      /* Bind new location to item */
      g_object_set_data(G_OBJECT(item), "ship_location", location);
      
      /* Insert item into quadrant */
      load_object_per_quad (item, ships_per_quad, xi, yi);

    } 
    /* A location is here already, lets add the ship to it */
    else {
      /* Get location and add the new ship */
      gwp_location_add_object (location, GWP_OBJECT(ship));
    }
  }
}

void draw_ion_storm (gpointer data, gpointer user_data)
{
  GnomeCanvasItem *item = NULL;
  GtkWidget *starchart = (GtkWidget *)starchart_get_canvas();
  GnomeCanvasGroup *group = gnome_canvas_root(GNOME_CANVAS(starchart));
  GwpIonStorm *storm = GWP_ION_STORM(data);
  gdouble xi, yi;

  if (gwp_ion_storm_is_valid (storm)) {
    vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(storm)),
		  gwp_object_get_y_coord(GWP_OBJECT(storm)), &xi, &yi);

    gint radius = gwp_ion_storm_get_radius (storm);
    item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				  "outline_color", "red",
				  "x1", xi - radius,
				  "y1", yi - radius,
				  "x2", xi + radius,
				  "y2", yi + radius,
				  "width_pixels", 1,
				  "fill_color_rgba", UNIVERSE_COLOR_A,
				  NULL);
  }
}

void draw_minefield (gpointer data, gpointer user_data)
{
  GnomeCanvasItem *item = NULL;
  GtkWidget *starchart = (GtkWidget *)starchart_get_canvas();
  GnomeCanvasGroup *group = gnome_canvas_root(GNOME_CANVAS(starchart));
  GwpMinefield *minefield = GWP_MINEFIELD(data);
  gdouble xi, yi;

  if (gwp_minefield_is_valid(minefield)) {
    vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(minefield)),
		  gwp_object_get_y_coord(GWP_OBJECT(minefield)), &xi, &yi);

    if (gwp_minefield_is_web (minefield)) {
      item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				    "outline_color", "dark khaki",
				    "x1", xi - gwp_minefield_get_radius(minefield),
				    "y1", yi - gwp_minefield_get_radius(minefield),
				    "x2", xi + gwp_minefield_get_radius(minefield),
				    "y2", yi + gwp_minefield_get_radius(minefield),
				    "width_pixels", 1,
				    "fill_color_rgba", UNIVERSE_COLOR_A,
				    NULL);		        
    } else if (gwp_minefield_is_mine(minefield)) {
      item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				    "outline_color", "dark olive green",
				    "x1", xi - gwp_minefield_get_radius(minefield),
				    "y1", yi - gwp_minefield_get_radius(minefield),
				    "x2", xi + gwp_minefield_get_radius(minefield),
				    "y2", yi + gwp_minefield_get_radius(minefield),
				    "width_pixels", 1,
				    "fill_color_rgba", UNIVERSE_COLOR_A,
				    NULL);		  
    } else {
      item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				    "outline_color", "gray50",
				    "x1", xi - gwp_minefield_get_radius(minefield),
				    "y1", yi - gwp_minefield_get_radius(minefield),
				    "x2", xi + gwp_minefield_get_radius(minefield),
				    "y2", yi + gwp_minefield_get_radius(minefield),
				    "width_pixels", 1,
				    "fill_color_rgba", UNIVERSE_COLOR_A,
				    NULL);		  
    }
  }
}

void draw_planet (gpointer key, gpointer value, gpointer user_data)
{
  GtkWidget *starchart, *gwp;
  GnomeCanvasItem *item;
  GnomeCanvasGroup *group;
  gdouble xi, yi;
  GwpPlanet *planet;

  planet = value;
  gwp = user_data;
  starchart = lookup_widget ("starchart");
  group = gnome_canvas_root (GNOME_CANVAS (starchart));

  /* Check if planet coords aren't 0...and work */
  if (gwp_object_valid_coords(GWP_OBJECT(planet))) {
    vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(planet)), 
		  gwp_object_get_y_coord(GWP_OBJECT(planet)), &xi, &yi);
    
    if (gwp_planet_is_mine(planet)) {
      item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				    "outline_color", OWNED_PLANET_COLOR,
				    "x1", xi - PLANET_RADIUS, 
				    "y1", yi - PLANET_RADIUS, 
				    "x2", xi + PLANET_RADIUS, 
				    "y2", yi + PLANET_RADIUS, 
				    "width_pixels", 1,
				    "fill_color_rgba", UNIVERSE_COLOR_A,
				    NULL);
    } else {
      item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				    "outline_color", PLANET_COLOR,
				    "x1", xi - PLANET_RADIUS, 
				    "y1", yi - PLANET_RADIUS, 
				    "x2", xi + PLANET_RADIUS, 
				    "y2", yi + PLANET_RADIUS, 
				    "width_pixels", 1,
				    "fill_color_rgba", UNIVERSE_COLOR_A,
				    NULL);
    }
    
    /* Bind canvas item with planet data */
    g_object_set_data (G_OBJECT (item), "planet_data", planet);
    /* Insert item into quadrant */
    load_object_per_quad (item, planets_per_quad, xi, yi);
  }
}


void init_starchart (GtkWidget * gwp) 
{
  GnomeCanvasItem *background;
  GnomeCanvasItem *grid_line;
  GnomeCanvasPoints *grid_points_v, *grid_points_h;
  gint i;
  
  /* Starchart struct initialization */
  starchart_set_grid(TRUE);
  starchart_set_canvas((GnomeCanvas *) lookup_widget ("starchart"));
  starchart_set_grp_root(gnome_canvas_root (starchart_get_canvas()));

  /* Set starchart on AA mode */
  starchart_get_canvas()->aa = 1;
  gnome_canvas_update_now(starchart_get_canvas());

  /* Scroll to last coordinates */
  gnome_canvas_scroll_to(starchart_get_canvas(),
			 game_get_last_x_coord(game_state),
			 game_get_last_y_coord(game_state));

  /* Set up toolbar view & menu entry */
  /* FIXME: Does not work toolbar hiding...why??
  if(game_get_toolbar(game_state)) {
    gtk_check_menu_item_set_active((GtkCheckMenuItem*)
				   lookup_widget("toolbar_menu"),
				   TRUE);
    gtk_widget_show(lookup_widget("bonobodock_btn_bar"));
  } else {
    gtk_check_menu_item_set_active((GtkCheckMenuItem*)
				   lookup_widget("toolbar_menu"),
				   FALSE);
    gtk_widget_hide(lookup_widget("bonobodock_btn_bar"));
  }
  */

  starchart_set_grp_grid(GNOME_CANVAS_GROUP 
			 (gnome_canvas_item_new 
			  (starchart_get_grp_root(), 
			   GNOME_TYPE_CANVAS_GROUP, NULL)));
  
  starchart_set_grp_planets(GNOME_CANVAS_GROUP 
			    (gnome_canvas_item_new 
			     (starchart_get_grp_root(), 
			      GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_planets_mine(GNOME_CANVAS_GROUP 
				 (gnome_canvas_item_new 
				  (starchart_get_grp_root(),
				   GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_planets_enemy(GNOME_CANVAS_GROUP 
				  (gnome_canvas_item_new 
				   (starchart_get_grp_root(), 
				    GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_planets_allied(GNOME_CANVAS_GROUP 
				   (gnome_canvas_item_new 
				    (starchart_get_grp_root(), 
				     GNOME_TYPE_CANVAS_GROUP, NULL)));
  
  starchart_set_grp_ships_mine(GNOME_CANVAS_GROUP 
			       (gnome_canvas_item_new 
				(starchart_get_grp_root(), 
				 GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_ships_enemy(GNOME_CANVAS_GROUP 
				(gnome_canvas_item_new 
				 (starchart_get_grp_root(), 
				  GNOME_TYPE_CANVAS_GROUP, NULL)));
  starchart_set_grp_ships_allied(GNOME_CANVAS_GROUP 
				 (gnome_canvas_item_new 
				  (starchart_get_grp_root(),
				   GNOME_TYPE_CANVAS_GROUP, NULL)));
  /* End struct initialization... */

  /* Initialize mouse cursor */
  starchart_set_default_cursor();
  
  /* Sets black background to starchart */
  background = gnome_canvas_item_new (starchart_get_grp_root(), 
				      GNOME_TYPE_CANVAS_RECT,
				      "outline_color", "grey",
				      "x1", 0.0, "y1", 0.0, "x2", CANVAS_WIDTH,
				      "y2", CANVAS_WIDTH, "width_units", 1.0,
				      "fill_color", UNIVERSE_COLOR, NULL);
  
  /* Sets starchart grid */
  grid_points_v = gnome_canvas_points_new (2);
  grid_points_h = gnome_canvas_points_new (2);
  for (i = 0; i < (STARCHART_WIDTH_INT / QUAD_WIDTH_INT) + 1 ; i++) {
    /* Vertical lines */
    grid_points_v->coords[0] = CANVAS_OFFSET + i * QUAD_WIDTH;
    grid_points_v->coords[1] = CANVAS_OFFSET;
    grid_points_v->coords[2] = CANVAS_OFFSET + i * QUAD_WIDTH;
    grid_points_v->coords[3] = CANVAS_OFFSET + STARCHART_WIDTH;
    /* Horizontal lines */
    grid_points_h->coords[0] = CANVAS_OFFSET;
    grid_points_h->coords[1] = CANVAS_OFFSET + i * QUAD_WIDTH;
    grid_points_h->coords[2] = CANVAS_OFFSET + STARCHART_WIDTH;
    grid_points_h->coords[3] = CANVAS_OFFSET + i * QUAD_WIDTH;
    /* Draw Vertical Line */
    grid_line = gnome_canvas_item_new (starchart_get_grp_grid(), 
				       GNOME_TYPE_CANVAS_LINE,
				       "fill_color", QUADRANT_GRID_COLOR,
				       "line_style", GDK_LINE_ON_OFF_DASH,
				       "width_pixels", 1,
				       "points", grid_points_v, NULL);
    /* Draw Horizontal Line */
    grid_line = gnome_canvas_item_new (starchart_get_grp_grid(), 
				       GNOME_TYPE_CANVAS_LINE,
				       "fill_color", QUADRANT_GRID_COLOR,
				       "line_style", GDK_LINE_ON_OFF_DASH,
				       "width_pixels", 1,
				       "points", grid_points_h, NULL);
  }
  
  /* Loads Planets on Starchart */
  g_message("Loading planets...");
  g_hash_table_foreach (planet_list, (GHFunc) draw_planet, gwp);
  g_message("...planets loaded!");
  
  /* Loads Ships on Starchart */
  g_message ("Loading ships...");
  g_hash_table_foreach (ship_list, (GHFunc) draw_ship, NULL);
  g_message ("...ships loaded!");

  /* Loads Minefields on Starchart */
  g_message ("Loading minefields...");
  g_slist_foreach (minefield_list, (GFunc) draw_minefield, NULL);
  g_message ("...minefields loaded!");

  /* Loads Ion Storm on Starchart */
  g_message ("Loading ion storms...");
  g_slist_foreach (storm_list, (GFunc) draw_ion_storm, NULL);
  g_message ("...ion storms loaded!");

  /* Set grid up in the item pile. */
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_grid()));
  /* Put ships above all other objects */
  gnome_canvas_item_raise_to_top (GNOME_CANVAS_ITEM (starchart_get_grp_ships_allied()));
  
  /* Various bindings */
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

  /* Depending on the position, add different quads to list */
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

GwpLocation * starchart_find_location (GSList *locations_in_quad,
				       gint x, gint y)
{
  gint nr, i;
  GwpLocation *loc = NULL;

  nr = g_slist_length (locations_in_quad);
  for (i = 0; i < nr; i++) {
    loc = (GwpLocation *) g_slist_nth_data (locations_in_quad, i);
    if (gwp_object_get_x_coord(GWP_OBJECT(loc)) == x &&
	gwp_object_get_y_coord(GWP_OBJECT(loc)) == y) {
      /* Location found! return it */
      return loc;
    }
  }
  return NULL;
}

GnomeCanvasItem * starchart_find_nearest_object (GSList * objects_in_quad, 
						 gdouble x, gdouble y)
{
  gint nr, i;
  gdouble min_dist, dist;
  gdouble px, py;
  GnomeCanvasItem *object, *min_object;

  nr = g_slist_length (objects_in_quad);

  if (nr > 0) {
    object = (GnomeCanvasItem *) g_slist_nth_data (objects_in_quad, 0);
    min_object = object;
    starchart_get_object_center_coord (object, &px, &py);
    min_dist = sqrt (((abs (px - x) ^ 2) + (abs (py - y) ^ 2)));

    for (i = 1; i < nr; i++) {
      object = g_slist_nth_data (objects_in_quad, i);
      starchart_get_object_center_coord (object, &px, &py);
      dist = sqrt (((abs (px - x) ^ 2) + (abs (py - y) ^ 2)));

      if (dist < min_dist) {
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
  GwpPlanet *planet = NULL;
  
  starchart_get_object_center_coord (planet_item, &x, &y);
  planet = g_object_get_data (G_OBJECT (planet_item), "planet_data");
  if (gwp_planet_what_is (planet) == IS_MINE) {
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

GnomeCanvasItem* starchart_select_nearest_planet (GtkWidget * gwp, 
						  GSList * planets_nearby,
						  gdouble wx, gdouble wy)
{
  GnomeCanvasItem *planet;
  GwpPlanet *planet_data;
  
  planet = starchart_find_nearest_object (planets_nearby, wx, wy);
  planet_data = g_object_get_data (G_OBJECT (planet), "planet_data");

  if (GWP_IS_PLANET(planet_data)) {
    starchart_mark_planet(planet_data);
    update_planet_panel (gwp, planet_data);
    update_planet_extra_panel(gwp_object_get_id(GWP_OBJECT(planet_data)));
    starchart_mini_set_planet_img(planet_data);
    table_population_update(planet_data);
    update_global_defense_panel(planet_data);
    update_starbase_panel(planet_data);

    return planet;
  } else {
    return NULL;
  }
}

GnomeCanvasItem *starchart_select_nearest_ship (GtkWidget * gwp, 
						GSList * ships_nearby,
						gdouble wx, gdouble wy)
{
  GnomeCanvasItem *ship;
  gdouble x, y;
  GSList *ship_list;
  GwpShip *ship_data;
  GwpLocation *location;
  
  ship = starchart_find_nearest_object (ships_nearby, wx, wy);
  location = g_object_get_data (G_OBJECT (ship), "ship_location");

  if (GWP_IS_LOCATION(location)) {
    vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(location)),
		  gwp_object_get_y_coord(GWP_OBJECT(location)),
		  &x, &y);

    starchart_mark_ship (x, y);
    update_ship_panel (gwp, location);

    return ship;
  } else {
    return NULL;
  }
}

/* (x, y) in world coords */
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
  gdouble zoom = game_get_starchart_zoom(game_state);
  gchar *zoom_status;
  
  if (zoom < 2.0) {
    zoom = zoom + 0.2;
    gnome_canvas_set_pixels_per_unit (starchart, zoom);
    game_set_starchart_zoom(game_state, zoom);
    zoom_status = g_strdup_printf("Zoom: %.1f", zoom);
    starchart_set_status(zoom_status);
    g_free(zoom_status);
  }
}

void starchart_zoom_out (GnomeCanvas * starchart)
{
  gdouble zoom = game_get_starchart_zoom(game_state);
  gchar *zoom_status;
  
  if (zoom > 0.6) {
    zoom = zoom - 0.2;
    gnome_canvas_set_pixels_per_unit (starchart, zoom);
    game_set_starchart_zoom(game_state, zoom);
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

/* Initializes the ship list */
void init_ship_panel (void)
{
  GtkTreeView *panel_ship_list;
  GtkCellRenderer *name_renderer, *id_renderer;
  GtkListStore *store;
  GtkTreeViewColumn *column1, *column2;

  panel_ship_list = (GtkTreeView *) lookup_widget ("ships_list");
  store = gtk_list_store_new (2, G_TYPE_INT, G_TYPE_STRING);
  name_renderer = gtk_cell_renderer_text_new();
  id_renderer = gtk_cell_renderer_text_new();
  column1 = gtk_tree_view_insert_column_with_attributes (panel_ship_list,
							 0,
							 "#", id_renderer,
							 "text", 0,
							 NULL);
  column2 = gtk_tree_view_insert_column_with_attributes (panel_ship_list,
							 1, _("Name"), 
							 name_renderer,
							 "text", 1,
							 NULL);
  gtk_tree_view_set_model (panel_ship_list, GTK_TREE_MODEL(store));
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

  /* Scroll to last known coords */
  starchart_mini_scroll_zone_to(game_get_last_x_coord(game_state),
				game_get_last_y_coord(game_state));
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
  gdouble zoom = game_get_starchart_zoom(game_state);

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

void starchart_mark_planet(GwpPlanet *a_planet)
{
  /*  static GnomeCanvasItem *planet_mark = NULL; */
  static GnomeCanvasItem *planet_mark_l = NULL;
  static GnomeCanvasItem *planet_mark_r = NULL;
  static GnomeCanvasItem *planet_mark_u = NULL;
  static GnomeCanvasItem *planet_mark_d = NULL;
  GnomeCanvasPoints *p;
  gdouble wx, wy;
  gdouble matrix[6];

  vp_coord_v2w(gwp_object_get_x_coord(GWP_OBJECT(a_planet)), 
	       gwp_object_get_y_coord(GWP_OBJECT(a_planet)), &wx, &wy);

  /* If item doesn't exist yet, lets create it. */
  if(! planet_mark_l) {
/*     planet_mark = gnome_canvas_item_new (starchart_get_grp_root(),  */
/* 					 GNOME_TYPE_CANVAS_ELLIPSE, */
/* 					 "outline_color_rgba", 0x00000000, */
/* 					 "x1", -2.5,  */
/* 					 "y1", -2.5, */
/* 					 "x2", 2.5, */
/* 					 "y2", 2.5, "width_pixels", 1, */
/* 					 "fill_color_rgba", 0x00000000,  */
/* 					 NULL); */
    p = gnome_canvas_points_new(2);
    p->coords[0] = -7.5;
    p->coords[1] = 0.0;
    p->coords[2] = -3.5;
    p->coords[3] = 0.0;
    planet_mark_l = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "red",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 2,
					   NULL);

    p = gnome_canvas_points_new(2);
    p->coords[0] = 3.5;
    p->coords[1] = 0.0;
    p->coords[2] = 7.5;
    p->coords[3] = 0.0;
    planet_mark_r = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "red",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 2,
					   NULL);

    p = gnome_canvas_points_new(2);
    p->coords[0] = 0.0;
    p->coords[1] = -7.5;
    p->coords[2] = 0.0;
    p->coords[3] = -3.5;
    planet_mark_u = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "red",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 2,
					   NULL);

    p = gnome_canvas_points_new(2);
    p->coords[0] = 0.0;
    p->coords[1] = 3.5;
    p->coords[2] = 0.0;
    p->coords[3] = 7.5;
    planet_mark_d = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "red",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 2,
					   NULL);
  }
  /* Translate the mark! */
  art_affine_translate(matrix, wx, wy);
  /*  gnome_canvas_item_affine_absolute(planet_mark, matrix); */
  gnome_canvas_item_affine_absolute(planet_mark_l, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_r, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_u, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_d, matrix);
}

void starchart_mark_ship (gint x, gint y)
{
  /*  static GnomeCanvasItem *ship_mark = NULL; */
  static GnomeCanvasItem *ship_mark_l = NULL;
  static GnomeCanvasItem *ship_mark_r = NULL;
  static GnomeCanvasItem *ship_mark_u = NULL;
  static GnomeCanvasItem *ship_mark_d = NULL;
  GnomeCanvasPoints *p;
  gdouble wx, wy;
  gdouble matrix[6];

  /*
  vp_coord_v2w(gwp_object_get_x_coord(GWP_OBJECT(a_ship)), 
	       gwp_object_get_y_coord(GWP_OBJECT(a_ship)), &wx, &wy);
  */

  wx = (gdouble)x;
  wy = (gdouble)y;

  /* If item doesn't exist yet, lets create it. */
  if(! ship_mark_l) {
/*     ship_mark = gnome_canvas_item_new (starchart_get_grp_root(),  */
/* 					 GNOME_TYPE_CANVAS_ELLIPSE, */
/* 					 "outline_color_rgba", 0x00000000, */
/* 					 "x1", -2.5,  */
/* 					 "y1", -2.5, */
/* 					 "x2", 2.5, */
/* 					 "y2", 2.5, "width_pixels", 1, */
/* 					 "fill_color_rgba", 0xdd000011,  */
/* 					 NULL); */
    p = gnome_canvas_points_new(2);
    p->coords[0] = -6.0;
    p->coords[1] = 6.0;
    p->coords[2] = -3.0;
    p->coords[3] = 3.0;
    ship_mark_l = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "green",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 2,
					   NULL);

    p = gnome_canvas_points_new(2);
    p->coords[0] = 3.0;
    p->coords[1] = -3.0;
    p->coords[2] = 6.;
    p->coords[3] = -6.0;
    ship_mark_r = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "green",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 2,
					   NULL);

    p = gnome_canvas_points_new(2);
    p->coords[0] = -6.0;
    p->coords[1] = -6.0;
    p->coords[2] = -3.0;
    p->coords[3] = -3.0;
    ship_mark_u = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "green",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 2,
					   NULL);

    p = gnome_canvas_points_new(2);
    p->coords[0] = 3.0;
    p->coords[1] = 3.0;
    p->coords[2] = 6.0;
    p->coords[3] = 6.0;
    ship_mark_d = gnome_canvas_item_new (starchart_get_grp_root(), 
					   GNOME_TYPE_CANVAS_LINE,
					   "fill_color", "green",
					   "points", p,
					   "line_style", GDK_LINE_SOLID,
					   "width_pixels", 2,
					   NULL);
  }
  /* Translate the mark! */
  art_affine_translate(matrix, wx, wy);
  /*  gnome_canvas_item_affine_absolute(ship_mark, matrix); */
  gnome_canvas_item_affine_absolute(ship_mark_l, matrix);
  gnome_canvas_item_affine_absolute(ship_mark_r, matrix);
  gnome_canvas_item_affine_absolute(ship_mark_u, matrix);
  gnome_canvas_item_affine_absolute(ship_mark_d, matrix);
}


void starchart_open_extra_panels(void)
{
  gtk_widget_show(lookup_widget("extra_info_panel"));
  gtk_widget_show(lookup_widget("calc_panel"));
  gtk_widget_show(lookup_widget("global_defense_panel"));
}

void starchart_close_extra_panels(void)
{
  GtkNotebook *mini =
    (GtkNotebook *) lookup_widget("notebook_mini");

  gtk_widget_hide(lookup_widget("extra_info_panel"));
  gtk_widget_hide(lookup_widget("calc_panel"));
  gtk_widget_hide(lookup_widget("global_defense_panel"));
  /* Show the mini-map again */
  gtk_notebook_set_current_page(mini, MINI_SC_PAGE);
}

/* Sets the planet image acording to the planet's temp */
void starchart_mini_set_planet_img(GwpPlanet *planet) 
{
  GtkImage *p_img = (GtkImage *) lookup_widget("image_planet");
  GtkImage *sb, *img;
  GdkPixbuf *pixbuf1, *pixbuf2;
  GdkPixmap *pixmap;
  gchar *img_name = DATADIR"/pixmaps/gwp/planets/planet";

  if(!gwp_planet_is_known(planet)) {
    img_name = g_strconcat(img_name, "-unknown.png", NULL);
  } else {
    if((gwp_planet_get_temperature_f(planet) >= 0) && 
       (gwp_planet_get_temperature_f(planet) <= 9)) {
      img_name = g_strconcat(img_name, "0-9.png", NULL);
    } else if((gwp_planet_get_temperature_f(planet) >= 10) && 
	      (gwp_planet_get_temperature_f(planet) <= 19)) {
      img_name = g_strconcat(img_name, "10-19.png", NULL);
    } else if((gwp_planet_get_temperature_f(planet) >= 20) && 
	      (gwp_planet_get_temperature_f(planet) <= 29)) {
      img_name = g_strconcat(img_name, "20-29.png", NULL);
    } else if((gwp_planet_get_temperature_f(planet) >= 30) && 
	      (gwp_planet_get_temperature_f(planet) <= 39)) {
      img_name = g_strconcat(img_name, "30-39.png", NULL);
    } else if((gwp_planet_get_temperature_f(planet) >= 40) && 
	      (gwp_planet_get_temperature_f(planet) <= 49)) {
      img_name = g_strconcat(img_name, "40-49.png", NULL);
    } else if((gwp_planet_get_temperature_f(planet) >= 50) && 
	      (gwp_planet_get_temperature_f(planet) <= 59)) {
      img_name = g_strconcat(img_name, "50-59.png", NULL);
    } else if((gwp_planet_get_temperature_f(planet) >= 60) && 
	      (gwp_planet_get_temperature_f(planet) <= 69)) {
      img_name = g_strconcat(img_name, "60-69.png", NULL);
    } else if((gwp_planet_get_temperature_f(planet) >= 70) && 
	      (gwp_planet_get_temperature_f(planet) <= 79)) {
      img_name = g_strconcat(img_name, "70-79.png", NULL);
    } else if((gwp_planet_get_temperature_f(planet) >= 80) && 
	      (gwp_planet_get_temperature_f(planet) <= 89)) {
      img_name = g_strconcat(img_name, "80-89.png", NULL);
    } else if((gwp_planet_get_temperature_f(planet) >= 90) && 
	      (gwp_planet_get_temperature_f(planet) <= 100)) {
      img_name = g_strconcat(img_name, "90-100.png", NULL);
    }
  }

  img = (GtkImage *) gtk_image_new_from_file(img_name);
  pixbuf1 = gtk_image_get_pixbuf(img);
  pixmap = gdk_pixmap_new(gwp->window, 100, 100, -1);
  gdk_draw_pixbuf(pixmap, NULL, pixbuf1,
		  0,0,
		  0,0,
		  -1, -1,
		  GDK_RGB_DITHER_NONE,
		  0,0);
    
  /* Add starbase image if one exists on planet */
  if(gwp_planet_has_starbase(planet)) {
    sb = (GtkImage *) gtk_image_new_from_file(DATADIR"/pixmaps/gwp/planets/sbase1.png");
    pixbuf2 = gtk_image_get_pixbuf(sb);
    
    gdk_draw_pixbuf(pixmap, NULL, pixbuf2,
		    0,0,
		    0,0,
		    -1,-1,
		    GDK_RGB_DITHER_NONE,
		    0,0);    
  }
  gtk_image_set_from_pixmap(p_img, pixmap, NULL);

  /* Free stuff */
  g_free(img_name);
}

/* Sets the ship image */
void starchart_mini_set_ship_img(GwpShip *ship) 
{
  g_assert (GWP_IS_SHIP(ship));

  GtkImage *s_img = (GtkImage *) lookup_widget("image_ship");
  GString *img_name = g_string_new(DATADIR"/pixmaps/gwp/ships/ship");
  gchar *ship_nr;

  /* Assemble file name and load image */
  ship_nr = g_strdup_printf ("%d.jpg", gwp_ship_get_hull_type(ship));
  img_name = g_string_append (img_name, ship_nr);
  gtk_image_set_from_file(s_img, g_strdup(img_name->str));

  /* Free stuff */
  g_free (ship_nr);
  g_string_free(img_name, TRUE);
}

void toggle_global_defense_panel(gboolean show)
{
  GtkWidget *def_panel = lookup_widget("global_defense_panel");

  if(show) {
    gtk_widget_show(def_panel);
  } else {
    gtk_widget_hide(def_panel);
  }
}

void toggle_starbase_panel(gboolean show)
{
  GtkNotebook *base_panel = 
    (GtkNotebook *) lookup_widget("extra_info_panel");

  if(show) {
    gtk_notebook_set_current_page(base_panel, EXTRA_PANEL_BASE_PAGE);
  } else {
    gtk_notebook_set_current_page(base_panel, EXTRA_PANEL_PLANET_PAGE);
  }
}

void starchart_rotate_ship (GwpShip *ship, GnomeCanvasItem *item)
{
  gdouble r[6], t[6];
  gdouble xi, yi;
 
  vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(ship)), 
		gwp_object_get_y_coord(GWP_OBJECT(ship)), 
		&xi, &yi);

  art_affine_translate (t, -xi, -yi);
  art_affine_rotate (r, (gdouble)gwp_fo_get_heading(GWP_FLYING_OBJECT(ship)));
  art_affine_multiply (r, t, r);
  art_affine_translate (t, xi, yi);
  art_affine_multiply (r, r, t);

  gnome_canvas_item_affine_absolute (item, r);
}
