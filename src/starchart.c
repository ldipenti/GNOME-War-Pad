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
#include "gwp-game-state.h"
#include "support.h"
#include "vp_utils.h"
#include "starchart.h"
#include "tables.h"
#include "mission.h"

/* Private functions */
static void starchart_zoom (GnomeCanvas *starchart, gdouble zoom);
static void init_starchart_constellations(void);

static GnomeCanvasPoints *distance_p;
static GnomeCanvasLine *distance_line;

/**
 * Notifications from game_state that should be taken seriously
 */
static void
starchart_boolean_notifications (GObject *obj, gpointer data)
{
  gchar *property = (gchar *)data;
  GwpGameState *state = GWP_GAME_STATE(obj);
  gboolean flag;
  
  g_object_get (state, 
		property, &flag, 
		NULL);

  if (strcmp(property, "minefields") == 0) {
    starchart_show_minefields (flag);
  } else if (strcmp(property, "ion-storms") == 0) {
    starchart_show_ion_storms (flag);
  } else if (strcmp(property, "planet-names") == 0) {
    starchart_show_planet_names (flag);
  } else if (strcmp(property, "scanner-area") == 0) {
    starchart_show_scanner_area (flag);
  } else if (strcmp(property, "grid") == 0) {
    starchart_show_grid (flag);
  } else if (strcmp(property, "constellations") == 0) {
    starchart_show_constellations (flag);
  }
}

/*
 * Updates Planet Data on Panel
 */
void update_starbase_panel(GwpPlanet *planet)
{
  static gboolean loaded = FALSE;
  static GtkProgressBar *tech_engines = NULL;
  static GtkProgressBar *tech_hulls = NULL;
  static GtkProgressBar *tech_beams = NULL;
  static GtkProgressBar *tech_torps = NULL;
  static GtkProgressBar *base_defenses = NULL;
  static GtkProgressBar *base_fighters = NULL;
  static GtkProgressBar *base_damage = NULL;
  static GtkLabel *base_mission = NULL;
  static GtkLabel *base_repair = NULL;
  static GtkLabel *base_recycle = NULL;
  static GtkLabel *build_hull = NULL;
  static GtkLabel *build_engines = NULL;
  static GtkLabel *build_beams = NULL;
  static GtkLabel *build_torps = NULL;
  gchar *tmp;

  g_assert (GWP_IS_PLANET(planet));
  
  if (!loaded) {
    loaded = TRUE;
    
    tech_engines = (GtkProgressBar *) lookup_widget("progressbar_tech_engines");
    tech_hulls = (GtkProgressBar *) lookup_widget("progressbar_tech_hulls");
    tech_beams = (GtkProgressBar *) lookup_widget("progressbar_tech_beams");
    tech_torps = (GtkProgressBar *) lookup_widget("progressbar_tech_torps");
    
    base_defenses = (GtkProgressBar *) lookup_widget("progressbar_base_defenses");
    base_fighters = (GtkProgressBar *) lookup_widget("progressbar_base_fighters");
    base_damage = (GtkProgressBar *) lookup_widget("progressbar_base_damage");
    base_mission = (GtkLabel *) lookup_widget("label_base_mission");
    base_repair = (GtkLabel *) lookup_widget("label_base_repair");
    base_recycle = (GtkLabel *) lookup_widget("label_base_recycle");
    build_hull = (GtkLabel *) lookup_widget("sb_ship_build_hull");
    build_engines = (GtkLabel *) lookup_widget("sb_ship_build_engines");
    build_beams = (GtkLabel *) lookup_widget("sb_ship_build_beams");
    build_torps = (GtkLabel *) lookup_widget("sb_ship_build_torps");
  }

  if(gwp_planet_has_starbase(planet)) {
    GwpStarbase *base = gwp_planet_get_starbase(planet);

    gtk_progress_bar_set_fraction(tech_engines, 
				  (gdouble)gwp_starbase_get_engines_tech(base)/10);
    tmp = g_strdup_printf(_("Tech %d"), gwp_starbase_get_engines_tech(base));
    gtk_progress_bar_set_text(tech_engines, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(tech_hulls, 
				  (gdouble)gwp_starbase_get_hulls_tech(base)/10);
    tmp = g_strdup_printf(_("Tech %d"), gwp_starbase_get_hulls_tech(base));
    gtk_progress_bar_set_text(tech_hulls, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(tech_beams, 
				  (gdouble)gwp_starbase_get_beams_tech(base)/10);
    tmp = g_strdup_printf(_("Tech %d"), gwp_starbase_get_beams_tech(base));
    gtk_progress_bar_set_text(tech_beams, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(tech_torps, 
				  (gdouble)gwp_starbase_get_torps_tech(base)/10);
    tmp = g_strdup_printf(_("Tech %d"), gwp_starbase_get_torps_tech(base));
    gtk_progress_bar_set_text(tech_torps, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(base_defenses,
				  (gdouble)gwp_starbase_get_defense(base)/200);
    tmp = g_strdup_printf(_("%d"), gwp_starbase_get_defense(base));
    gtk_progress_bar_set_text(base_defenses, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(base_fighters, 
				  (gdouble)gwp_starbase_get_fighters(base)/60);
    tmp = g_strdup_printf(_("%d"), gwp_starbase_get_fighters(base));
    gtk_progress_bar_set_text(base_fighters, tmp);
    g_free(tmp);

    gtk_progress_bar_set_fraction(base_damage, 
				  (gdouble)gwp_starbase_get_damage(base)/100);
    tmp = g_strdup_printf(_("%d%%"), gwp_starbase_get_damage(base));
    gtk_progress_bar_set_text(base_damage, tmp);
    g_free(tmp);

    /*** Mission ***/
    tmp = g_strdup_printf ("%s", mission_sb_get_name(gwp_starbase_get_mission(base)));
    gtk_label_set_text (base_mission, tmp);
    g_free (tmp);

    /*** Repair / Recycle Ship ***/
    if (gwp_starbase_get_ship_action(base) != 0) {
      GwpShip *ship = gwp_ship_get(ship_list, gwp_starbase_get_id_ship(base));
      tmp = g_strdup_printf ("(#%d) %s",
			     gwp_object_get_id(GWP_OBJECT(ship)),
			     gwp_object_get_name(GWP_OBJECT(ship)));
      switch (gwp_starbase_get_ship_action(base)) {
      case 1:
	gtk_label_set_text (base_repair, tmp);
	gtk_label_set_text (base_recycle, _("--"));
	break;
      case 2:
	gtk_label_set_text (base_recycle, tmp);
	gtk_label_set_text (base_repair, _("--"));
	break;
      }      
	g_free (tmp);
    }
    /* No recycle nor repair */
    else {
      gtk_label_set_text (base_repair, _("--"));
      gtk_label_set_text (base_recycle, _("--"));
    }

    /*** Ship build ***/
    if (gwp_starbase_get_build_ship_type(base) != 0) {
      /* Hull */
      GwpHullSpec *hull = GWP_HULLSPEC(g_slist_nth_data(hullspec_list, truehull[gwp_game_state_get_race(game_state)-1][gwp_starbase_get_build_ship_type(base)-1] - 1));

      tmp = g_strdup_printf("%s", gwp_hullspec_get_name_trunc(hull, 18));
      gtk_label_set_text (build_hull, tmp);
      g_free (tmp);

      /* Engines */
      GwpEngSpec *engines = GWP_ENGSPEC(g_slist_nth_data(engspec_list, gwp_starbase_get_build_engine_type(base) - 1));
      tmp = g_strdup_printf("%d %s", 
			    gwp_hullspec_get_engines(hull),
			    gwp_engspec_get_name(engines));
      gtk_label_set_text (build_engines, tmp);
      g_free (tmp);

      /* Beams */
      if (gwp_starbase_get_build_beam_count(base) > 0) {
	GwpBeamSpec *beams = GWP_BEAMSPEC(g_slist_nth_data(beamspec_list, gwp_starbase_get_build_beam_type(base) - 1));
	tmp = g_strdup_printf("%d %s",
			      gwp_starbase_get_build_beam_count(base),
			      gwp_beamspec_get_name(beams));
	gtk_label_set_text (build_beams, tmp);
	g_free (tmp);
      } else {
	gtk_label_set_text (build_beams, _("--"));
      }

      /* Torps */
      if (gwp_starbase_get_build_torp_count(base) > 0) {
	GwpTorpSpec *torps = GWP_TORPSPEC(g_slist_nth_data(torpspec_list, gwp_starbase_get_build_torp_type(base) - 1));
	tmp = g_strdup_printf("%d %s",
			      gwp_starbase_get_build_torp_count(base),
			      gwp_torpspec_get_name(torps));
	gtk_label_set_text (build_torps, tmp);
	g_free (tmp);
      } else if (gwp_hullspec_get_fighter_bays(hull) > 0) {
	tmp = g_strdup_printf(_("0 (%d fighter bays)"),
			      gwp_hullspec_get_fighter_bays(hull));
	gtk_label_set_text (build_torps, tmp);
	g_free (tmp);
      } else {
	gtk_label_set_text (build_torps, _("--"));
      }
    }
    /* no build */
    else {
      gtk_label_set_text (build_hull, _("--"));
      gtk_label_set_text (build_engines, _("--"));
      gtk_label_set_text (build_beams, _("--"));
      gtk_label_set_text (build_torps, _("--"));
    }
  } 
  /* Planet without starbase or unknown */
  else {
    gtk_progress_bar_set_fraction(tech_engines, 0.0);
    gtk_progress_bar_set_text(tech_engines, _("--"));

    gtk_progress_bar_set_fraction(tech_hulls, 0.0);
    gtk_progress_bar_set_text(tech_hulls, _("--"));

    gtk_progress_bar_set_fraction(tech_beams, 0.0);
    gtk_progress_bar_set_text(tech_beams, _("--"));

    gtk_progress_bar_set_fraction(tech_torps, 0.0);
    gtk_progress_bar_set_text(tech_torps, _("--"));

    gtk_progress_bar_set_fraction(base_defenses, 0.0);
    gtk_progress_bar_set_text(base_defenses, _("--"));

    gtk_progress_bar_set_fraction(base_fighters, 0.0);
    gtk_progress_bar_set_text(base_fighters, _("--"));

    gtk_progress_bar_set_fraction(base_damage, 0.0);
    gtk_progress_bar_set_text(base_damage, _("--"));

    gtk_label_set_text (base_mission, _("--"));

    gtk_label_set_text (base_repair, _("--"));
    gtk_label_set_text (base_recycle, _("--"));
    
    gtk_label_set_text (build_hull, _("--"));
    gtk_label_set_text (build_engines, _("--"));
    gtk_label_set_text (build_beams, _("--"));
    gtk_label_set_text (build_torps, _("--"));
  }
}

void update_global_defense_panel(GwpPlanet *planet)
{
  static gboolean loaded = FALSE;
  static GtkLabel *beams = NULL;
  static GtkLabel *beams_type = NULL;
  static GtkLabel *fighters = NULL;
  static GtkLabel *fighter_bays = NULL;
  static GtkLabel *battle_mass = NULL;
  gchar *tmp;

  if (!loaded) {
    loaded = TRUE;

    beams = (GtkLabel *) lookup_widget("label_def_sys_beams");
    beams_type = (GtkLabel *) lookup_widget("label_def_sys_beams_type");
    fighters = (GtkLabel *) lookup_widget("label_def_sys_fighters");
    fighter_bays = (GtkLabel *) lookup_widget("label_def_sys_fighter_bays");
    battle_mass = (GtkLabel *) lookup_widget("label_def_sys_battle_mass");
  }

  if(gwp_planet_is_known(planet)) {
    tmp = g_strdup_printf("%d", gwp_planet_get_def_sys_beams_nr(planet));
    gtk_label_set_label(beams, tmp);
    g_free(tmp);

    tmp = gwp_planet_get_def_sys_beams_type_str (planet);
    gtk_label_set_label(beams_type, tmp);
    g_free (tmp);

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

void update_ship_extra_panel (GwpShip *ship)
{
  static gboolean loaded = FALSE;
  static GtkLabel *ship_name = NULL;
  static GtkLabel *spec_engines = NULL;
  static GtkLabel *spec_primary = NULL;
  static GtkLabel *spec_secondary = NULL;
  static GtkLabel *spec_secondary_extra = NULL;
  static GtkProgressBar *cargo_total = NULL;
  static GtkProgressBar *status_neu = NULL;
  static GtkProgressBar *status_damage = NULL;
  static GtkProgressBar *status_crew = NULL;
  static GtkProgressBar *cargo_tri = NULL;
  static GtkProgressBar *cargo_dur  = NULL;
  static GtkProgressBar *cargo_mol = NULL;
  static GtkProgressBar *cargo_col = NULL;
  static GtkProgressBar *cargo_sup = NULL;
  static GtkProgressBar *cargo_money = NULL;
  static GtkCombo *ship_fc = NULL;
  static GtkLabel *mission = NULL;
  static GtkLabel *mission_param = NULL;
  static GtkLabel *enemy = NULL;
  gchar *tmp = NULL;
  gchar *tmp2 = NULL;

  g_assert (GWP_IS_SHIP(ship));

  if (!loaded) {
    loaded = TRUE;

    ship_name = (GtkLabel *) lookup_widget("label_ship_extra_panel_name");
    
    spec_engines = (GtkLabel *) lookup_widget("label_ship_spec_engines");
    spec_primary = (GtkLabel *) lookup_widget("label_ship_spec_primary");
    spec_secondary = (GtkLabel *) lookup_widget("label_ship_spec_secondary");
    spec_secondary_extra = (GtkLabel *) lookup_widget("label_ship_spec_secondary_extra");

    status_neu = (GtkProgressBar *) lookup_widget("progressbar_ship_status_neu");
    status_damage = (GtkProgressBar *) lookup_widget("progressbar_ship_status_damage");
    status_crew = (GtkProgressBar *) lookup_widget("progressbar_ship_status_crew");
    
    cargo_total = (GtkProgressBar *) lookup_widget("progressbar_ship_cargo_total");
    cargo_tri = (GtkProgressBar *) lookup_widget("progressbar_ship_cargo_tri");
    cargo_dur = (GtkProgressBar *) lookup_widget("progressbar_ship_cargo_dur");
    cargo_mol = (GtkProgressBar *) lookup_widget("progressbar_ship_cargo_mol");
    cargo_col = (GtkProgressBar *) lookup_widget("progressbar_ship_cargo_col");
    cargo_sup = (GtkProgressBar *) lookup_widget("progressbar_ship_cargo_sup");
    cargo_money = (GtkProgressBar *) lookup_widget("progressbar_ship_cargo_money");

    ship_fc = (GtkCombo *) lookup_widget("combo_ship_fc");

    mission = (GtkLabel *) lookup_widget("label_ship_other_mission");
    mission_param = (GtkLabel *) lookup_widget("label_ship_other_mission_param");
    enemy = (GtkLabel *) lookup_widget("label_ship_other_enemy");
  }


  /* Ship data always available... */
  tmp = g_strdup_printf ("<b>%s</b>", gwp_object_get_name(GWP_OBJECT(ship)));
  gtk_label_set_markup (ship_name, tmp);
  g_free (tmp);

  /* Only if ship is ours... */
  if (gwp_ship_is_mine(ship)) {
    /*** Engines ***/
    tmp = g_strdup_printf("%d <i>%s</i>", gwp_ship_get_hull_engines(ship),
			  gwp_ship_get_engine_name(ship));
    gtk_label_set_markup (spec_engines, tmp);
    g_free (tmp);

    /*** Primary Weapon ***/
    if (gwp_ship_has_beam_weapons(ship)) {
      tmp = g_strdup_printf("%d <i>%s</i>", 
			    gwp_ship_get_beams(ship),
			    gwp_ship_get_beams_name(ship));
    } else {
      tmp = _("no weapon");
    }
    gtk_label_set_markup (spec_primary, tmp);
    g_free (tmp);

    /*** Secondary Weapon ***/
    /* Check for torpedo tubes */
    if (gwp_ship_has_torp_weapons(ship)) {
      tmp = g_strdup_printf(_("%d <i>%s</i>"),
			    gwp_ship_get_torps_launchers(ship),
			    gwp_ship_get_torps_name(ship));
      if (gwp_ship_get_torps(ship) == 1) {
	tmp2 = _("1 torpedo");
      } else {
	tmp2 = g_strdup_printf(_("%d torpedoes"), gwp_ship_get_torps(ship));
      }
    } 
    /* Check for fighter bays */
    else if (gwp_ship_get_fighter_bays(ship) > 0) {
      if (gwp_ship_get_fighter_bays(ship) == 1) {
	tmp = g_strdup_printf(_("1 fighter bay"));
      } else {
	tmp = g_strdup_printf(_("%d fighter bays"),
			      gwp_ship_get_fighter_bays(ship));
      }
      if (gwp_ship_get_fighters(ship) == 1) {
	tmp2 = _("1 fighter");
      } else {
	tmp2 = g_strdup_printf(_("%d fighters"), gwp_ship_get_fighters(ship));
      }
    }
    /* No fighters, no torpedoes... */
    else {
      tmp = g_strdup_printf(_("no weapon"));
      tmp2 = g_strdup_printf(_("--"));
    }
    gtk_label_set_markup (spec_secondary, tmp);
    gtk_label_set_markup (spec_secondary_extra, tmp2);
    g_free (tmp);
    g_free (tmp2);

    /*** Neutronium ***/
    if (gwp_ship_get_neutronium(ship) > 0) {
      gtk_progress_bar_set_fraction (status_neu,
				     gwp_ship_get_neutronium(ship) /
				     (gdouble)gwp_ship_get_hull_fuel_tank(ship));
    } else {
      gtk_progress_bar_set_fraction (status_neu, 0.0);
    }
    tmp = g_strdup_printf(_("%d kT"), gwp_ship_get_neutronium(ship));
    gtk_progress_bar_set_text (status_neu, tmp);
    g_free (tmp);    

    /*** Damage ***/
    if (gwp_ship_get_damage(ship) > 0) {
      gtk_progress_bar_set_fraction (status_damage,
				     gwp_ship_get_damage(ship) / 100.0);
    } else {
      gtk_progress_bar_set_fraction (status_damage, 0.0);
    }
    tmp = g_strdup_printf("%d%%", gwp_ship_get_damage(ship));
    gtk_progress_bar_set_text (status_damage, tmp);
    g_free (tmp);

    /*** Crew ***/
    if (gwp_ship_get_crew(ship) > 0) {
      gtk_progress_bar_set_fraction (status_crew,
				     gwp_ship_get_crew(ship) /
				     (gdouble)gwp_ship_get_hull_crew(ship));
    } else {
      gtk_progress_bar_set_fraction (status_crew, 0.0);
    }
    if (gwp_ship_get_crew(ship) == 1) {
      tmp = g_strdup_printf (_("1 crewman"));
    } else {
      tmp = g_strdup_printf (_("%d crewmen"), gwp_ship_get_crew(ship));
    }
    gtk_progress_bar_set_text (status_crew, tmp);
    g_free (tmp);

    /*** Total cargo ***/
    if (gwp_ship_calculate_cargo(ship) > 0) {
      gtk_progress_bar_set_fraction (cargo_total, 
				     gwp_ship_calculate_cargo(ship) /
				     (gdouble)gwp_ship_get_hull_cargo(ship));
    } else {
      gtk_progress_bar_set_fraction (cargo_total, 0.0);
    }
    tmp = g_strdup_printf(_("%d kT"), gwp_ship_calculate_cargo(ship));
    gtk_progress_bar_set_text(cargo_total, tmp);
    g_free(tmp);    

    /*** Tritanium ***/
    if (gwp_ship_get_tritanium(ship) > 0) {
      gtk_progress_bar_set_fraction (cargo_tri, 
				     gwp_ship_get_tritanium(ship) /
				     (gdouble)gwp_ship_get_hull_cargo(ship));
    } else {
      gtk_progress_bar_set_fraction (cargo_tri, 0.0);
    }
    tmp = g_strdup_printf(_("%d kT"), gwp_ship_get_tritanium(ship));
    gtk_progress_bar_set_text(cargo_tri, tmp);
    g_free(tmp);    

    /*** Duranium ***/
    if (gwp_ship_get_duranium(ship) > 0) {
      gtk_progress_bar_set_fraction (cargo_dur, 
				     gwp_ship_get_duranium(ship) /
				     (gdouble)gwp_ship_get_hull_cargo(ship));
    } else {
      gtk_progress_bar_set_fraction (cargo_dur, 0.0);
    }
    tmp = g_strdup_printf(_("%d kT"), gwp_ship_get_duranium(ship));
    gtk_progress_bar_set_text(cargo_dur, tmp);
    g_free(tmp);    

    /*** Molybdenum ***/
    if (gwp_ship_get_molybdenum(ship) > 0) {
      gtk_progress_bar_set_fraction (cargo_mol, 
				     gwp_ship_get_molybdenum(ship) /
				     (gdouble)gwp_ship_get_hull_cargo(ship));
    } else {
      gtk_progress_bar_set_fraction (cargo_mol, 0.0);
    }
    tmp = g_strdup_printf(_("%d kT"), gwp_ship_get_molybdenum(ship));
    gtk_progress_bar_set_text(cargo_mol, tmp);
    g_free(tmp);    

    /*** Supplies ***/
    if (gwp_ship_get_supplies(ship) > 0) {
      gtk_progress_bar_set_fraction (cargo_sup, 
				     gwp_ship_get_supplies(ship) /
				     (gdouble)gwp_ship_get_hull_cargo(ship));
    } else {
      gtk_progress_bar_set_fraction (cargo_sup, 0.0);
    }
    tmp = g_strdup_printf(_("%d kT"), gwp_ship_get_supplies(ship));
    gtk_progress_bar_set_text(cargo_sup, tmp);
    g_free(tmp);    

    /*** Colonists ***/
    if (gwp_ship_get_colonists(ship) > 0) {
      gtk_progress_bar_set_fraction (cargo_col, 
				     gwp_ship_get_colonists(ship) /
				     (gdouble)gwp_ship_get_hull_cargo(ship));
    } else {
      gtk_progress_bar_set_fraction (cargo_col, 0.0);
    }
    if (gwp_ship_get_colonists(ship) == 1) {
      tmp = g_strdup_printf(_("1 clan"));
    } else {
      tmp = g_strdup_printf(_("%d clans"), gwp_ship_get_colonists(ship));
    }
    gtk_progress_bar_set_text(cargo_col, tmp);
    g_free(tmp);    

    /*** Money ***/
    if (gwp_ship_get_megacredits(ship) > 0) {
      gtk_progress_bar_set_fraction (cargo_money,
				     gwp_ship_get_megacredits(ship) /
				     (gdouble)10000.0);
    } else {
      gtk_progress_bar_set_fraction (cargo_money, 0.0);
    }
    tmp = g_strdup_printf (_("%d MC"), gwp_ship_get_megacredits(ship));
    gtk_progress_bar_set_text (cargo_money, tmp);
    g_free (tmp);

    /*** Friendly Code ***/
    tmp = g_strdup_printf ("%s", gwp_ship_get_fcode(ship));
    gtk_entry_set_text (GTK_ENTRY(ship_fc->entry), tmp);
    g_free(tmp);

    /*** Mission ***/
    tmp = g_strdup_printf ("%s", gwp_ship_get_mission_name(ship));
    gtk_label_set_text (mission, tmp);
    g_free (tmp);

    /*** Mission parameter (if necessary) ***/
    if (gwp_ship_get_mission(ship) == MISSION_TOW) {
      GwpShip *obj_ship = gwp_ship_get (ship_list, 
					gwp_ship_get_tow_ship_id(ship));
      g_assert (GWP_IS_SHIP(obj_ship));
      
      /* If towed ship is there, say so... */
      if (gwp_object_get_id (GWP_OBJECT(obj_ship)) != 0) {
	tmp = g_strdup_printf ("<i>(#%d) %s</i>",
			       gwp_object_get_id(GWP_OBJECT(obj_ship)),
			       gwp_object_get_name_trunc(GWP_OBJECT(obj_ship),15));
      } else {
	tmp = _("<i>No ship</i>");
      }
      gtk_label_set_markup (mission_param, tmp);     
      g_free (tmp);
    } else if (gwp_ship_get_mission(ship) == MISSION_INTERCEPT) {
      GwpShip *obj_ship = gwp_ship_get (ship_list, 
					gwp_ship_get_intercept_ship_id(ship));
      g_assert (GWP_IS_SHIP(obj_ship));
      tmp = g_strdup_printf ("<i>(#%d) %s</i>",
			     gwp_object_get_id(GWP_OBJECT(obj_ship)),
			     gwp_object_get_name(GWP_OBJECT(obj_ship)));
      gtk_label_set_markup (mission_param, tmp);     
      g_free (tmp);      
    } else {
      gtk_label_set_text (mission_param, _("--"));
    }

    /*** Primary Enemy ***/
    tmp = g_strdup_printf ("%s", gwp_ship_get_primary_enemy_name(ship));
    gtk_label_set_text (enemy, tmp);
    g_free (tmp);
  }
  /* If ship is unknown... */
  else {
    /* Engines */
    tmp = g_strdup_printf(_("%d <i>unknown</i>"), 
			  gwp_ship_get_hull_engines(ship));
    gtk_label_set_markup (spec_engines, tmp);
    g_free (tmp);

    /* Primary weapon */
    if (gwp_ship_get_hull_beam_weapons(ship) > 0) {
      tmp = g_strdup_printf (_("%d <i>unknown</i>"),
			     gwp_ship_get_hull_beam_weapons(ship));
    } else {
      tmp = _("no weapon");
    }
    gtk_label_set_markup (spec_primary, tmp);
    g_free (tmp);

    /** Secondary Weapon **/
    /* Check for torpedo tubes */
    if (gwp_ship_get_hull_torp_launchers(ship) > 0) {
      if (gwp_ship_get_hull_torp_launchers(ship) == 1) {
	tmp = g_strdup_printf(_("1 launcher"));
      } else {
	tmp = g_strdup_printf(_("%d launchers"),
			      gwp_ship_get_hull_torp_launchers(ship));
      }
      tmp2 = g_strdup_printf(_("unknown"));
    } 
    /* Check for fighter bays */
    else if (gwp_ship_get_hull_fighter_bays(ship) > 0) {
      if (gwp_ship_get_hull_fighter_bays(ship) == 1) {
	tmp = g_strdup_printf(_("1 fighter bay"));
      } else {
	tmp = g_strdup_printf(_("%d fighter bays"),
			      gwp_ship_get_hull_fighter_bays(ship));
      }
      tmp2 = g_strdup_printf(_("unknown"));
    }
    /* No fighters, no torpedoes... */
    else {
      tmp = g_strdup_printf(_("no weapon"));
      tmp2 = g_strdup_printf(_("--"));
    }
    gtk_label_set_markup (spec_secondary, tmp);
    gtk_label_set_markup (spec_secondary_extra, tmp2);
    g_free (tmp);
    g_free (tmp2);

    /* Neutronium */
    gtk_progress_bar_set_fraction (status_neu, 0.0);
    gtk_progress_bar_set_text (status_neu, _("-- kT"));

    /* Damage */
    gtk_progress_bar_set_fraction (status_damage, 0.0);
    gtk_progress_bar_set_text (status_damage, _("-- %"));

    /* Crew */
    gtk_progress_bar_set_fraction (status_crew, 0.0);
    gtk_progress_bar_set_text (status_crew, _("-- crewmen"));

    /* Total Cargo */
    gtk_progress_bar_set_fraction (cargo_total, 0.0);
    gtk_progress_bar_set_text (cargo_total, _("-- kT"));

    /* Tritanium */
    gtk_progress_bar_set_fraction (cargo_tri, 0.0);
    gtk_progress_bar_set_text (cargo_tri, _("-- kT"));

    /* Duranium */
    gtk_progress_bar_set_fraction (cargo_dur, 0.0);
    gtk_progress_bar_set_text (cargo_dur, _("-- kT"));

    /* Molybdenum */
    gtk_progress_bar_set_fraction (cargo_mol, 0.0);
    gtk_progress_bar_set_text (cargo_mol, _("-- kT"));

    /* Supplies */
    gtk_progress_bar_set_fraction (cargo_sup, 0.0);
    gtk_progress_bar_set_text (cargo_sup, _("-- kT"));

    /* Colonists */
    gtk_progress_bar_set_fraction (cargo_col, 0.0);
    gtk_progress_bar_set_text (cargo_col, _("-- clans"));

    /* Money */
    gtk_progress_bar_set_fraction (cargo_money, 0.0);
    gtk_progress_bar_set_text (cargo_money, _("-- MC"));

    /* Friendly Code */
    gtk_entry_set_text (GTK_ENTRY(ship_fc->entry), "???");

    /* Mission */
    gtk_label_set_text (mission, _("--"));

    /* Mission param */
    gtk_label_set_text (mission_param, _("--"));

    /* Primary Enemy */
    gtk_label_set_text (enemy, _("--"));
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
  if ((planet_id >= 1) && (planet_id <= MAX_PLANETS)) {
    /* If we have data on this planet, then work */
    if ((a_planet = gwp_planet_get (planet_list, planet_id)) != NULL &&
	gwp_planet_is_known (a_planet)) {
      /*** Friendly Code ***/
      tmp = g_strdup_printf ("%s", gwp_planet_get_fcode(a_planet));
      gtk_entry_set_text (GTK_ENTRY(planet_fc->entry), tmp);
      g_free(tmp);
      
      /*** Neutronium ***/
      gtk_progress_bar_set_fraction(neu_ground, gwp_planet_get_ground_percent(gwp_planet_get_ground_neutronium(a_planet)));
      tmp = g_strdup_printf(_("%d kT"), 
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
      tmp = g_strdup_printf(_("%d kT"), 
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
      tmp = g_strdup_printf(_("%d kT"), 
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
      tmp = g_strdup_printf(_("%d kT"), 
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
	tmp = g_strdup_printf(_("%d MC"), 
			      gwp_planet_get_tax_earned_natives(a_planet));
      } else {
	tmp = g_strdup_printf(_("%d <span foreground=\"red\">(%d)</span> MC"),
			      gwp_planet_get_tax_earned_natives(a_planet),
			      gwp_planet_get_colonists(a_planet));
      }
      gtk_label_set_markup(tax_nat_earned, tmp);
      g_free(tmp);
      
      tmp = g_strdup_printf(_("%d MC"), 
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
  static GtkLabel *owner = NULL;
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
    owner = (GtkLabel *) lookup_widget ("label_owner");
    
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
			     gwp_object_get_name (GWP_OBJECT(a_planet)),
			     gwp_object_get_id (GWP_OBJECT(a_planet)));
    } else {
      tmp = g_strdup_printf ("<b>%s</b> (#%d)", 
			     gwp_object_get_name (GWP_OBJECT(a_planet)),
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

    /* Owner */
    tmp = g_strdup_printf("%s", race_get_name(gwp_planet_get_owner(a_planet)));
    gtk_label_set_text(owner, tmp);
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
			   gwp_object_get_name (GWP_OBJECT(a_planet)),
			   gwp_object_get_id (GWP_OBJECT(a_planet)));
    gtk_label_set_markup(planet_name, tmp);
    g_free(tmp);
	
    gtk_label_set_text (mines, _("--"));
    gtk_label_set_text (factories, _("--"));
    gtk_label_set_text (defenses, _("--"));
    gtk_label_set_text (temperature, _("--"));
    gtk_label_set_text(owner, _("--"));
	
    gtk_label_set_text (neutronium, _("--"));
    gtk_label_set_text (tritanium, _("--"));
    gtk_label_set_text (duranium, _("--"));
    gtk_label_set_text (molybdenum, _("--"));
    gtk_label_set_text (supplies, _("--"));
	
    gtk_label_set_text (colonists, _("--"));
    gtk_label_set_text (natives, _("--"));
    gtk_label_set_text (natives_race, _("--"));
    gtk_label_set_text (spi, _("--"));
    gtk_label_set_text (megacredits, _("--"));
    gtk_label_set_text (visibility, _("--"));

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
  static GtkLabel *owner = NULL;
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
    owner = (GtkLabel *) lookup_widget("label_ship_panel_owner");
  }

  g_assert(GWP_IS_SHIP(ship));

  if (gwp_ship_is_mine(ship)) {
    /* Update waypoint */
    gint x, y;
    gwp_ship_get_waypoint(ship, &x, &y);
    /* tmp = g_strdup_printf("(%d , %d)", x, y); */
    tmp = g_strdup_printf("%s", starchart_get_location_name(x, y)->str);
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
    if (gwp_flying_object_get_speed(GWP_FLYING_OBJECT(ship)) == 0 &&
	gwp_ship_calculate_waypoint_distance(ship) > 0) {
      tmp = _("<span foreground=\"red\">never</span>");
    } else {
      gint e = gwp_ship_calculate_eta (ship);
      if (e == 1) {
	tmp = g_strdup_printf(_("%d turn"), e);
      } else {
	tmp = g_strdup_printf(_("%d turns"), e);
      }
    }

    gtk_label_set_markup (eta, tmp);
    g_free(tmp);
  }
  /* If it's not my ship, reset all fields */
  else {
    gtk_label_set_text(waypoint, "--");
    gtk_label_set_text(distance, "--");
    gtk_label_set_text(eta, "--");

    /* Mass as appears on SHIPXY */
    tmp = g_strdup_printf ("%d KT", 
			   gwp_ship_get_mass_if_unknown(ship));
    gtk_label_set_text(mass, tmp);
    g_free (tmp);

    gtk_label_set_text(fuel_usage, "--");
    gtk_label_set_text(eta, "--");
  }

  /* 
   * These are valid for all ships.
   */
  /* Update heading */
  gint h = gwp_flying_object_get_heading(GWP_FLYING_OBJECT(ship));
  if(h != -1) {
    gchar *hstr = gwp_flying_object_get_heading_str(GWP_FLYING_OBJECT(ship));
    tmp = g_strdup_printf("%d\302\260 (%s)", h, hstr);
  } else {
    tmp = g_strdup_printf(_("not moving"));
  }
  gtk_label_set_text(heading, tmp);
  g_free(tmp);
  
  /* Update speed */
  tmp = g_strdup_printf(_("Warp %d"), 
			gwp_flying_object_get_speed(GWP_FLYING_OBJECT(ship)));
  gtk_label_set_text(speed, tmp);
  g_free(tmp);
  
  /* Update Hull Type */
  tmp = g_strdup_printf ("<i>%s</i>", 
			 gwp_ship_get_hull_name_trunc(ship, 20));
  gtk_label_set_markup (hull, tmp);
  g_free(tmp);

  /* Update owner */
  tmp = g_strdup_printf ("%s", gwp_ship_get_owner_name(ship));
  gtk_label_set_text (owner, tmp);
  g_free (tmp);

  /* Work extra only if necessary */
  if (gwp_game_state_get_extra_panel_open (game_state)) {
    /* Update ship image */
    starchart_mini_set_ship_img(ship);
    /* Update extra panel */
    update_ship_extra_panel (ship);
  }
}

/**
 * Given a GwpLocation, it shows how many ships are available.
 */
void update_ship_panel (GtkWidget * gwp, GwpLocation * location)
{
  static gboolean loaded = FALSE;
  static GtkNotebook *info_panel = NULL;
  static GtkLabel *summary = NULL;
  static GtkTreeView *panel_ship_list = NULL;
  GwpShip *ship;
  gchar *tmp = NULL, *tmp2 = NULL;
  guint ships_nr = 0;
  gint i;
  GtkListStore *store;
  GtkTreeIter iter;
  GtkTreePath *path;
  
  if (!loaded) {
    loaded = TRUE;

    info_panel = (GtkNotebook *) lookup_widget ("info_panel");
    summary = (GtkLabel *) lookup_widget ("label_ship_panel_summary");
    panel_ship_list = (GtkTreeView *) lookup_widget ("ships_list");
  }

  /* Select the ship page on panel */
  gtk_notebook_set_current_page (info_panel, PANEL_SHIP_PAGE);

  /* Set up ship list */
  store = (GtkListStore *) gtk_tree_view_get_model (panel_ship_list);
  g_assert (store != NULL);
  gtk_list_store_clear (store);

  ships_nr = gwp_location_objects_nr(location);

  /* Set up summary label */
  if (ships_nr == 1) {
    tmp2 = g_string_new ("ship")->str;
  } else {
    tmp2 = g_string_new ("ships")->str;
  }
  tmp = g_strdup_printf (_("%d %s in %s"), ships_nr, tmp2,
			 starchart_get_location_name(gwp_object_get_x_coord(GWP_OBJECT(location)), gwp_object_get_y_coord(GWP_OBJECT(location)))->str);
  gtk_label_set_text (summary, tmp);
  g_free (tmp);
  g_free (tmp2);

  /* Load GtkTreeView with ships */
  for (i = 0; i < ships_nr; i++) {
    /* Get ship from location */
    ship = GWP_SHIP(gwp_location_get_object(location, i));

    /* Check if we have the ship's ID, this is because if we don't have it,
     it means that the ship appear on SHIPXY.DAT, but not on TARGETx.DAT 
     and TARGETx.EXT doesn't exist */
    if (gwp_object_get_id (GWP_OBJECT(ship)) > 0) {

      /* Add item to ship list */
      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter,
			  0, gwp_object_get_id (GWP_OBJECT(ship)),
			  1, g_strdup_printf("%s", gwp_object_get_name(GWP_OBJECT(ship))),
			  -1);
    }
  }
  /* Select first ship on list */
  path = gtk_tree_model_get_path (GTK_TREE_MODEL(store), &iter);
  gtk_tree_view_scroll_to_cell (panel_ship_list, path, NULL, TRUE, 1.0, 0.0);
  gtk_tree_view_set_cursor (panel_ship_list, path, NULL, FALSE);
  gtk_tree_path_free (path);
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
  ships_group = starchart_get_grp_ships (); /*FIXME: only allied!!*/
  
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

	/* Add ship scanner range */
	gnome_canvas_item_new (starchart_get_grp_scanner_area (),
			       GNOME_TYPE_CANVAS_ELLIPSE,
			       "outline_color_rgba", SCANNER_RANGE_COLOR,
			       "fill_color_rgba", SCANNER_RANGE_COLOR,
			       "x1", xi - SCANNER_RANGE,
			       "y1", yi - SCANNER_RANGE,
			       "x2", xi + SCANNER_RANGE,
			       "y2", yi + SCANNER_RANGE,
			       "width_pixels", 1,
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
      /*      g_object_set_data(G_OBJECT(item), "ship_location", location); */
      g_object_set_data(G_OBJECT(ship), "ship_location", location);
      
      /* Insert item into quadrant */
      /*      load_object_per_quad (item, ships_per_quad, xi, yi); */
      load_object_per_quad (ship, ships_per_quad, xi, yi);

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
  GnomeCanvasItem *item_arrow = NULL;
  GnomeCanvasGroup *group = starchart_get_grp_ion_storms();
  GwpIonStorm *storm = GWP_ION_STORM(data);
  gdouble xi, yi;
  GnomeCanvasPoints *points;

  if (gwp_ion_storm_is_valid (storm)) {

    gchar * storm_colors[] = {
      "invalid color",
      "green",        /* Class 1 */
      "light green",  /* Class 2 */
      "yellow",       /* Class 3 */
      "indian red",   /* Class 4 */
      "red"           /* Class 5 */
    };

    /* FIXME: make a canvas group for storms!!! */
    vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(storm)),
		  gwp_object_get_y_coord(GWP_OBJECT(storm)), &xi, &yi);

    gint radius = gwp_ion_storm_get_radius (storm);
    item = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
				  "outline_color", storm_colors[gwp_ion_storm_get_class(storm)],
				  "x1", xi - radius,
				  "y1", yi - radius,
				  "x2", xi + radius,
				  "y2", yi + radius,
				  "width_pixels", 1,
				  "fill_color_rgba", UNIVERSE_COLOR_A,
				  NULL);

    points = gnome_canvas_points_new (3);
    gint storm_speed = gwp_flying_object_get_speed (GWP_FLYING_OBJECT(storm));
    g_assert (storm_speed > 0);

    /* Draw storm arrow */
    points->coords[0] = xi - (storm_speed*storm_speed / 4 / 2); /* 1st point */
    points->coords[1] = yi - radius;
    points->coords[2] = xi + (storm_speed*storm_speed / 4 / 2); /* 2nd point */
    points->coords[3] = yi - radius;
    points->coords[4] = xi;                          /* 3rd point */
    points->coords[5] = yi - radius - storm_speed*storm_speed;

    item_arrow = gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_POLYGON,
					"outline_color", storm_colors[gwp_ion_storm_get_class(storm)],
					"points", points,
					"width_pixels", 1,
					NULL);
    gnome_canvas_points_free (points);

    /* Rotate arrow */
    gdouble r[6], t[6];

    art_affine_translate (t, -xi, -yi);
    art_affine_rotate (r, (gdouble)gwp_flying_object_get_heading(GWP_FLYING_OBJECT(storm)));
    art_affine_multiply (r, t, r);
    art_affine_translate (t, xi, yi);
    art_affine_multiply (r, r, t);
    
    gnome_canvas_item_affine_absolute (item_arrow, r);
  }
}

void draw_minefield (gpointer data, gpointer user_data)
{
  GnomeCanvasItem *item = NULL;
  GnomeCanvasGroup *group = starchart_get_grp_minefields();
  GwpMinefield *minefield = GWP_MINEFIELD(data);
  gdouble xi, yi;

  if (gwp_minefield_is_valid(minefield)) {
    vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(minefield)),
		  gwp_object_get_y_coord(GWP_OBJECT(minefield)), &xi, &yi);

    /* FIXME: Make a canvas group form minefields!!! */
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
  GtkWidget *gwp;
  GnomeCanvasItem *item;
  gdouble xi, yi;
  GwpPlanet *planet;
  static GtkWidget *starchart;
  static gboolean loaded = FALSE;
  static GnomeCanvasGroup *pnames_group = NULL;
  static GnomeCanvasGroup *group;

  if (!loaded) {
    loaded = TRUE;
    pnames_group = starchart_get_grp_planet_names ();
    starchart = lookup_widget ("starchart");
    group = starchart_get_grp_planets();
  }
	
  planet = value;
  gwp = user_data;

  /* Check if planet coords aren't 0...and work */
  if (gwp_object_valid_coords(GWP_OBJECT(planet))) {
    vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(planet)), 
		  gwp_object_get_y_coord(GWP_OBJECT(planet)), &xi, &yi);
    
    /* Add planet names */
    /* FIXME: TOOOOOOO SLOOOOOOOOOOOOOOOWWWWWWWW!!!  
    gnome_canvas_item_new (pnames_group, 
			   GNOME_TYPE_CANVAS_TEXT,
			   "text", gwp_object_get_name(GWP_OBJECT(planet)),
			   "x", xi,
			   "y", yi + 10,
			   "fill_color", "white",
			   NULL);
    */

    if (gwp_planet_is_mine(planet)) {

      /* Add planet scanner range */
      gnome_canvas_item_new (starchart_get_grp_scanner_area (),
			     GNOME_TYPE_CANVAS_ELLIPSE,
			     "outline_color_rgba", SCANNER_RANGE_COLOR,
			     "fill_color_rgba", SCANNER_RANGE_COLOR,
			     "x1", xi - SCANNER_RANGE,
			     "y1", yi - SCANNER_RANGE,
			     "x2", xi + SCANNER_RANGE,
			     "y2", yi + SCANNER_RANGE,
			     "width_pixels", 1,
			     NULL);

      /* Is there's a starbase on planet, draw a special mark */
      if (gwp_planet_has_starbase(planet)) {
	gnome_canvas_item_new (group, GNOME_TYPE_CANVAS_ELLIPSE,
			       "outline_color_rgba", OWNED_STARBASE_COLOR,
			       "x1", xi - (PLANET_RADIUS+1), 
			       "y1", yi - (PLANET_RADIUS+1), 
			       "x2", xi + (PLANET_RADIUS+1), 
			       "y2", yi + (PLANET_RADIUS+1), 
			       "width_pixels", 2,
			       "fill_color_rgba", UNIVERSE_COLOR_A,
			       NULL);
      }
      
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
    load_object_per_quad (planet, planets_per_quad, xi, yi);
  }
}


void init_starchart (GtkWidget * gwp) 
{
  GnomeCanvasItem *grid_line;
  GnomeCanvasPoints *grid_points_v, *grid_points_h;
  gint i;
  
  /* Starchart struct initialization */
  starchart_set_canvas((GnomeCanvas *) lookup_widget ("starchart"));
  starchart_set_grp_root(gnome_canvas_root (starchart_get_canvas()));

  /* Set starchart on AA mode */
  starchart_get_canvas()->aa = 1;
  gnome_canvas_update_now(starchart_get_canvas());

  /* Set groups */
  starchart_set_grp_grid(GNOME_CANVAS_GROUP 
			 (gnome_canvas_item_new 
			  (starchart_get_grp_root(), 
			   GNOME_TYPE_CANVAS_GROUP, NULL)));
  
  starchart_set_grp_planet_names (GNOME_CANVAS_GROUP 
				   (gnome_canvas_item_new 
				    (starchart_get_grp_root(), 
				     GNOME_TYPE_CANVAS_GROUP, NULL)));

  /* Show our scanners reach area on starchart */
  starchart_set_grp_scanner_area (GNOME_CANVAS_GROUP 
				  (gnome_canvas_item_new 
				   (starchart_get_grp_root(), 
				    GNOME_TYPE_CANVAS_GROUP, NULL)));
  
  starchart_set_grp_planets (GNOME_CANVAS_GROUP 
			     (gnome_canvas_item_new 
			      (starchart_get_grp_root(),
			       GNOME_TYPE_CANVAS_GROUP, NULL)));

  starchart_set_grp_ships (GNOME_CANVAS_GROUP 
			   (gnome_canvas_item_new 
			    (starchart_get_grp_root(), 
			     GNOME_TYPE_CANVAS_GROUP, NULL)));

  starchart_set_grp_minefields (GNOME_CANVAS_GROUP 
				(gnome_canvas_item_new 
				 (starchart_get_grp_root(),
				  GNOME_TYPE_CANVAS_GROUP, NULL)));

  starchart_set_grp_ion_storms (GNOME_CANVAS_GROUP 
				(gnome_canvas_item_new 
				 (starchart_get_grp_root(),
				  GNOME_TYPE_CANVAS_GROUP, NULL)));

  starchart_set_grp_constellations (GNOME_CANVAS_GROUP 
				    (gnome_canvas_item_new 
				     (starchart_get_grp_root(),
				      GNOME_TYPE_CANVAS_GROUP, NULL)));

  starchart_set_default_cursor();
  
  /* Sets black background to starchart */
  gnome_canvas_item_new (starchart_get_grp_root(), 
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

  /*********** TEST ***********/
  distance_p = gnome_canvas_points_new (2);
  distance_p->coords[0] = 1500.0;
  distance_p->coords[1] = 1500.0;
  distance_p->coords[2] = 1600.0;
  distance_p->coords[3] = 1600.0;
  distance_line = gnome_canvas_item_new (starchart_get_grp_grid(),
					 GNOME_TYPE_CANVAS_LINE,
					 "fill_color", "green",
					 "width_pixels", 1, 
					 "points", distance_p, NULL);

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

  /* Set scanner range on the top */
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_scanner_area()));
  /* Set grid up in the item pile. */
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_grid()));
  /* Set Constellations on the top */
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_constellations()));
  /* Planets and ships */
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_planets()));
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_ships()));
  /* Set Minefields and storms on the top */
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_minefields()));
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_ion_storms()));
  /* Set Planet names on the top */
  gnome_canvas_item_raise_to_top(GNOME_CANVAS_ITEM(starchart_get_grp_planet_names()));

  /* Various bindings */
  g_object_set_data (G_OBJECT (starchart_get_canvas()), 
		     "grid_group", starchart_get_grp_grid());
  g_object_set_data (G_OBJECT (starchart_get_canvas()), 
		     "ships_group", starchart_get_grp_ships());

  /* Set starchart zoom */
  starchart_zoom (starchart_get_canvas(), 
		  gwp_game_state_get_starchart_zoom (game_state));

  /* Draw constellations, must be after zoom! */
  g_message ("Creating constellations...");
  init_starchart_constellations();
  g_message ("...constellations created!");

  /* Scroll to last coordinates */
  gnome_canvas_scroll_to(starchart_get_canvas(),
			 gwp_game_state_get_last_x_coord (game_state),
			 gwp_game_state_get_last_y_coord (game_state));

  /*** Set initial statuses ***/
  GtkCheckMenuItem *menu_bool = NULL;
  gboolean flag_bool = FALSE;
  /* Minefields view */
  menu_bool = (GtkCheckMenuItem *) lookup_widget ("view_mine_fields");
  g_object_get (game_state,
		"minefields", &flag_bool,
		NULL);
  gtk_check_menu_item_set_active (menu_bool, flag_bool);
  starchart_show_minefields (flag_bool);

  /* Ion Storms view */
  menu_bool = (GtkCheckMenuItem *) lookup_widget ("view_ion_storms");
  g_object_get (game_state,
		"ion-storms", &flag_bool,
		NULL);
  gtk_check_menu_item_set_active (menu_bool, flag_bool);
  starchart_show_ion_storms (flag_bool);

  /* Planet names view */
  menu_bool = (GtkCheckMenuItem *) lookup_widget ("view_pnames_menu");
  g_object_get (game_state,
		"planet-names", &flag_bool,
		NULL);
  gtk_check_menu_item_set_active (menu_bool, flag_bool);
  starchart_show_planet_names (flag_bool);

  /* Scanner area view */
  menu_bool = (GtkCheckMenuItem *) lookup_widget ("view_scanner_area");
  g_object_get (game_state,
		"scanner-area", &flag_bool,
		NULL);
  gtk_check_menu_item_set_active (menu_bool, flag_bool);
  starchart_show_scanner_area (flag_bool);

  /* Grid view */
  menu_bool = (GtkCheckMenuItem *) lookup_widget ("grid");
  g_object_get (game_state,
		"grid", &flag_bool,
		NULL);
  gtk_check_menu_item_set_active (menu_bool, flag_bool);
  starchart_show_grid (flag_bool);

  /* Constellations view */
  menu_bool = (GtkCheckMenuItem *) lookup_widget ("view_constellations");
  g_object_get (game_state,
		"constellations", &flag_bool,
		NULL);
  gtk_check_menu_item_set_active (menu_bool, flag_bool);
  starchart_show_constellations (flag_bool);

  /* Model notifications that starchart view has to respond to. */
  g_signal_connect (game_state,
		    "property-changed::minefields",
		    G_CALLBACK(starchart_boolean_notifications),
		    (gpointer)"minefields");
  g_signal_connect (game_state,
		    "property-changed::ion-storms",
		    G_CALLBACK(starchart_boolean_notifications),
		    (gpointer)"ion-storms");
  g_signal_connect (game_state,
		    "property-changed::planet-names",
		    G_CALLBACK(starchart_boolean_notifications),
		    (gpointer)"planet-names");
  g_signal_connect (game_state,
		    "property-changed::scanner-area",
		    G_CALLBACK(starchart_boolean_notifications),
		    (gpointer)"scanner-area");
  g_signal_connect (game_state,
		    "property-changed::grid",
		    G_CALLBACK(starchart_boolean_notifications),
		    (gpointer)"grid");
  g_signal_connect (game_state,
		    "property-changed::constellations",
		    G_CALLBACK(starchart_boolean_notifications),
		    (gpointer)"constellations");
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

GwpPlanet * starchart_find_planet (GSList *planets_in_quad, gint x, gint y)
{
  gint nr, i;
  GwpPlanet *planet = NULL;

  nr = g_slist_length (planets_in_quad);
  for (i = 0; i < nr; i++) {
    planet = GWP_PLANET(g_slist_nth_data (planets_in_quad, i));
    if (gwp_object_get_x_coord(GWP_OBJECT(planet)) == x &&
	gwp_object_get_y_coord(GWP_OBJECT(planet)) == y) {
      /* Planet found, return it */
      return planet;
    }
  }
  return NULL;
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

GwpObject * starchart_find_nearest_object (GSList * objects_in_quad, 
					   gdouble x, gdouble y)
{
  gint nr, i;
  gdouble min_dist, dist;
  gdouble px, py;
  GwpObject *object, *min_object;

  nr = g_slist_length (objects_in_quad);

  if (nr > 0) {
    object = (GwpObject *) g_slist_nth_data (objects_in_quad, 0);
    min_object = object;

    vp_coord_v2w(gwp_object_get_x_coord (object), 
		 gwp_object_get_y_coord (object), &px, &py);      

    min_dist = sqrt (((abs (px - x) ^ 2) + (abs (py - y) ^ 2)));

    for (i = 1; i < nr; i++) {
      object = g_slist_nth_data (objects_in_quad, i);
      
      vp_coord_v2w(gwp_object_get_x_coord (object), 
		   gwp_object_get_y_coord (object), &px, &py);      

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

GwpPlanet* starchart_select_nearest_planet (GtkWidget * gwp, 
					    GSList * planets_nearby,
					    gdouble wx, gdouble wy)
{
  /*  GnomeCanvasItem *planet; */
  GwpPlanet *planet_data;
  static gboolean loaded = FALSE;
  static GtkNotebook *extra_info_panel = NULL;
  static GtkNotebook *extra_info_panel_planet = NULL;
  static GtkNotebook *mini = NULL;

  if (!loaded) {
    loaded = TRUE;

    extra_info_panel = (GtkNotebook *) lookup_widget("extra_info_panel");
    extra_info_panel_planet = (GtkNotebook *) lookup_widget("extra_info_panel_planet");
    mini = (GtkNotebook *) lookup_widget("notebook_mini");
  }
  
  planet_data = (GwpPlanet *)starchart_find_nearest_object (planets_nearby, wx, wy);
  /*  planet_data = g_object_get_data (G_OBJECT (planet), "planet_data"); */

  if (GWP_IS_PLANET(planet_data)) {
    starchart_mark_planet(planet_data);
    update_planet_panel (gwp, planet_data);

    /* Do extra work only if needed */
    if (gwp_game_state_get_extra_panel_open(game_state)) {
      starchart_mini_set_planet_img(planet_data);
      table_population_update(planet_data);
      update_global_defense_panel(planet_data);
      update_starbase_panel(planet_data);
      gtk_notebook_set_current_page(extra_info_panel, EXTRA_PANEL_PLANET_PAGE);
      /* If planet has not starbase, select planet tab */
      if (! gwp_planet_has_starbase(planet_data)) {
	gtk_notebook_set_current_page(extra_info_panel_planet, EXTRA_PANEL_PLANET_INNER_PLANET_PAGE);
      }
      update_planet_extra_panel(gwp_object_get_id(GWP_OBJECT(planet_data)));
      gtk_notebook_set_current_page (mini, MINI_PLANET_PAGE);
      starchart_center_around(GWP_OBJECT(planet_data));
    } else {
      /* If extra panel isn't open, reset the inner notebook to planet view */
      gtk_notebook_set_current_page(extra_info_panel_planet, EXTRA_PANEL_PLANET_INNER_PLANET_PAGE);
    }

    return planet_data;
  } else {
    return NULL;
  }
}

GwpShip *starchart_select_nearest_ship (GtkWidget * gwp, 
					GSList * ships_nearby,
					gdouble wx, gdouble wy)
{
  GwpShip *ship;
  gdouble x, y;
  GwpLocation *location;
  static gboolean loaded = FALSE;
  static GtkNotebook *extra_info_panel = NULL;
  static GtkNotebook *mini = NULL;

  if (!loaded) {
    loaded = TRUE;

    extra_info_panel = (GtkNotebook *) lookup_widget("extra_info_panel");
    mini = (GtkNotebook *) lookup_widget("notebook_mini");
  }
  
  ship = (GwpShip *)starchart_find_nearest_object (ships_nearby, wx, wy);
  location = g_object_get_data (G_OBJECT (ship), "ship_location");

  if (GWP_IS_LOCATION(location)) {
    vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(location)),
		  gwp_object_get_y_coord(GWP_OBJECT(location)),
		  &x, &y);

    starchart_mark_ship (x, y);
    update_ship_panel (gwp, location);

    /* Do extra work only if needed */
    if (gwp_game_state_get_extra_panel_open(game_state)) {
      gtk_notebook_set_current_page (extra_info_panel, EXTRA_PANEL_SHIP_PAGE);
      gtk_notebook_set_current_page (mini, MINI_SHIP_PAGE);
      starchart_center_around(GWP_OBJECT(location));
    }

    return ship;
  } else {
    return NULL;
  }
}

/**
 * Centers the starchart around the given object.
 *
 * @param obj any GwpObject on the starchart.
 */
void starchart_center_around (GwpObject *obj)
{
  gint ax, ay, x, y;
  gdouble obj_x, obj_y;

  g_assert (GWP_IS_OBJECT(obj));

  vp_coord_v2w (gwp_object_get_x_coord(obj),
		gwp_object_get_y_coord(obj),
		&obj_x, &obj_y);

  ax = GTK_WIDGET (starchart_get_canvas())->allocation.width;
  ay = GTK_WIDGET (starchart_get_canvas())->allocation.height;

  gnome_canvas_w2c (starchart_get_canvas(),
		    obj_x, obj_y,
		    &x, &y);

  gnome_canvas_scroll_to (starchart_get_canvas(), 
			  (x - (ax / 2)), 
			  (y - (ay / 2)));
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

static void
starchart_zoom (GnomeCanvas *starchart,
		gdouble      zoom)
{
  gchar *zoom_status;
  GtkCheckMenuItem *pnames_menu = (GtkCheckMenuItem *) lookup_widget ("view_pnames_menu");
  
  gnome_canvas_set_pixels_per_unit (starchart, zoom);
  gwp_game_state_set_starchart_zoom (game_state, zoom);
  
  /* print status */
  zoom_status = g_strdup_printf("Zoom: %d%%", (gint)(rint(zoom*10)*10));
  starchart_set_status(zoom_status);
  g_free(zoom_status);
  
  /* show planet names if needed */
  if (gtk_check_menu_item_get_active(pnames_menu)) {
    starchart_show_planet_names (TRUE);
  } else {
    starchart_show_planet_names (FALSE);
  }
}

void starchart_zoom_in (GnomeCanvas * starchart)
{
  gdouble zoom = gwp_game_state_get_starchart_zoom (game_state);
  
  if (zoom < 2.0) {
    zoom += 0.2;
    starchart_zoom (starchart, zoom);
  }
}

void starchart_zoom_out (GnomeCanvas * starchart)
{
  gdouble zoom = gwp_game_state_get_starchart_zoom (game_state);
  
  if (zoom > 0.4) {
    zoom -= 0.2;
    starchart_zoom (starchart, zoom);
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

  distance_p->coords[2] = wx;
  distance_p->coords[3] = wy;
  g_object_set (distance_line, 
		"points", distance_p,
		NULL);
  g_message ("Moviendo a X:%f Y:%f", wx, wy);
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
  column1 = gtk_tree_view_column_new_with_attributes ("#",
						      id_renderer,
						      "text", 0,
						      NULL);
  gtk_tree_view_append_column (panel_ship_list, column1);

  column2 = gtk_tree_view_column_new_with_attributes (_("Name"), 
						      name_renderer,
						      "text", 1,
						      NULL);
  gtk_tree_view_append_column (panel_ship_list, column2);

  gtk_tree_view_set_model (panel_ship_list, GTK_TREE_MODEL(store));
}

void init_starchart_mini (void) 
{
  GnomeCanvasItem *zone;
  
  /* Starchart struct initialization */
  starchart_mini_set_canvas((GnomeCanvas *) lookup_widget ("starchart_mini"));
  starchart_mini_set_grp_root(gnome_canvas_root (starchart_mini_get_canvas()));

  /* Set starchart on "antialias" mode */
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
  starchart_mini_scroll_zone_to (gwp_game_state_get_last_x_coord(game_state),
				 gwp_game_state_get_last_y_coord(game_state));
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
  gdouble zoom = gwp_game_state_get_starchart_zoom(game_state);

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
  gnome_canvas_item_affine_absolute(planet_mark_l, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_r, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_u, matrix);
  gnome_canvas_item_affine_absolute(planet_mark_d, matrix);
}

void starchart_mark_ship (gint x, gint y)
{
  static GnomeCanvasItem *ship_mark_l = NULL;
  static GnomeCanvasItem *ship_mark_r = NULL;
  static GnomeCanvasItem *ship_mark_u = NULL;
  static GnomeCanvasItem *ship_mark_d = NULL;
  GnomeCanvasPoints *p;
  gdouble wx, wy;
  gdouble matrix[6];

  wx = (gdouble)x;
  wy = (gdouble)y;

  /* If item doesn't exist yet, lets create it. */
  if(! ship_mark_l) {
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
  gnome_canvas_item_affine_absolute(ship_mark_l, matrix);
  gnome_canvas_item_affine_absolute(ship_mark_r, matrix);
  gnome_canvas_item_affine_absolute(ship_mark_u, matrix);
  gnome_canvas_item_affine_absolute(ship_mark_d, matrix);
}

void starchart_open_extra_planet_panels (void)
{
  static GtkNotebook *extra_info_panel = NULL;

  extra_info_panel = (GtkNotebook *) lookup_widget("extra_info_panel");

  /* Select subpanels */
  gtk_notebook_set_current_page(extra_info_panel, EXTRA_PANEL_PLANET_PAGE);

  /* Show the panels!! (or not)  */
  if (! gwp_game_state_get_extra_panel_open(game_state)) {
    starchart_open_extra_panels ();
  } else {
    starchart_close_extra_panels ();
  }
}

void starchart_open_extra_ship_panels (void)
{
  static GtkNotebook *extra_info_panel = NULL;

  extra_info_panel = (GtkNotebook *) lookup_widget("extra_info_panel");

  /* Select subpanels */
  gtk_notebook_set_current_page(extra_info_panel, EXTRA_PANEL_SHIP_PAGE);

  /* Show the panels!! (or not)  */
  if (! gwp_game_state_get_extra_panel_open(game_state)) {
    starchart_open_extra_panels ();
  } else {
    starchart_close_extra_panels ();
  }
}

void starchart_open_extra_panels (void)
{
  static gboolean loaded = FALSE;
  static GtkNotebook *extra_info_panel = NULL;
  static GtkNotebook *calc_panel = NULL;
  static GtkNotebook *gds_panel = NULL;

  if (!loaded) {
    loaded = TRUE;

    extra_info_panel = (GtkNotebook *) lookup_widget("extra_info_panel");
    calc_panel = (GtkNotebook *) lookup_widget("calc_panel");
    gds_panel = (GtkNotebook *) lookup_widget("global_defense_panel");
  }

  /* Show the panels!! */
  gtk_widget_show(GTK_WIDGET(extra_info_panel));
  gtk_widget_show(GTK_WIDGET(calc_panel));
  gtk_widget_show(GTK_WIDGET(gds_panel));

  /* Register new panel state */
  gwp_game_state_set_extra_panel_open (game_state, TRUE);
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

  /* Register new panel state */
  if (game_state) {
    gwp_game_state_set_extra_panel_open (game_state, FALSE);
  }
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
  GString *img_name = g_string_new(DATADIR"/pixmaps/gwp/ships/vpl");
  gchar *ship_nr;

  /* Assemble file name and load image */
  ship_nr = g_strdup_printf ("%d.jpg", gwp_ship_get_hull_picture(ship));
  img_name = g_string_append (img_name, ship_nr);
  gtk_image_set_from_file(s_img, g_strdup(img_name->str));

  /* Free stuff */
  g_free (ship_nr);
  g_string_free(img_name, TRUE);
}

void starchart_rotate_ship (GwpShip *ship, GnomeCanvasItem *item)
{
  gdouble r[6], t[6];
  gdouble xi, yi;
 
  vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(ship)), 
		gwp_object_get_y_coord(GWP_OBJECT(ship)), 
		&xi, &yi);

  art_affine_translate (t, -xi, -yi);
  art_affine_rotate (r, (gdouble)gwp_flying_object_get_heading(GWP_FLYING_OBJECT(ship)));
  art_affine_multiply (r, t, r);
  art_affine_translate (t, xi, yi);
  art_affine_multiply (r, r, t);

  gnome_canvas_item_affine_absolute (item, r);
}

void starchart_show_planet_names (gboolean show)
{
  if (show && gwp_game_state_get_starchart_zoom(game_state) >= 1.0) {
    gnome_canvas_item_show ((GnomeCanvasItem *) 
			    starchart_get_grp_planet_names ());
  } else {
    gnome_canvas_item_hide ((GnomeCanvasItem *) 
			    starchart_get_grp_planet_names ());
  }
}

void starchart_show_scanner_area (gboolean show)
{
  if (show) {
    gnome_canvas_item_show ((GnomeCanvasItem *) 
			    starchart_get_grp_scanner_area ());
  } else {
    gnome_canvas_item_hide ((GnomeCanvasItem *) 
			    starchart_get_grp_scanner_area ());
  }
}

void starchart_show_minefields (gboolean show)
{
  if (show) {
    gnome_canvas_item_show ((GnomeCanvasItem *) 
			    starchart_get_grp_minefields ());
  } else {
    gnome_canvas_item_hide ((GnomeCanvasItem *) 
			    starchart_get_grp_minefields ());
  }
}

void starchart_show_ion_storms (gboolean show)
{
  if (show) {
    gnome_canvas_item_show ((GnomeCanvasItem *)
			    starchart_get_grp_ion_storms ());
  } else {
    gnome_canvas_item_hide ((GnomeCanvasItem *)
			    starchart_get_grp_ion_storms ());
  }
}

void starchart_show_constellations (gboolean show)
{
  if (show) {
    gnome_canvas_item_show ((GnomeCanvasItem *)
			    starchart_get_grp_constellations ());
  } else {
    gnome_canvas_item_hide ((GnomeCanvasItem *)
			    starchart_get_grp_constellations ());
  }
}

/**
 * Searches for planets on the given coords and return its name if any.
 */
GString * starchart_get_location_name (gint x, gint y)
{
  /* FIXME: Acceptable input values?? */
  g_assert (x >= 0 && x <= 5000);
  g_assert (y >= 0 && y <= 5000);

  GwpObject *obj;
  gint q;
  GString *ret;
  GSList *objects_nearby;
  gdouble dx, dy;

  vp_coord_v2w (x, y, &dx, &dy);
  q = get_quadrant(dx, dy);

  objects_nearby = starchart_get_surrounding_quads (planets_per_quad, q);

  if ((obj = (GwpObject *)starchart_find_planet(objects_nearby, x, y))) {
    ret = g_string_new(gwp_object_get_name(obj));
  } else {
    ret = g_string_new(g_strdup_printf("(%d , %d)", x, y));
  }

  return ret;
}

/* Shows/hides grid */
void
starchart_show_grid (gboolean show)
{
  if(show) {
    gnome_canvas_item_show ((GnomeCanvasItem *) starchart_get_grp_grid());
  } else {
    gnome_canvas_item_hide ((GnomeCanvasItem *) starchart_get_grp_grid());
  }
}

/**
 * Initializes starchart constellations.
 */
static void 
init_starchart_constellations (void)
{
  GSList *planets = NULL;
  GSList *ppq[TOTAL_QUADS];
  GSList *list_nearby = NULL;
  GwpPlanet *planet_a, *planet_b;
  gint i, j, quad;
  gdouble dist;
  gdouble wx, wy;
  gdouble ax, ay, bx, by, zoom;

  static void add_item (gpointer key, gpointer value, gpointer user_data) {
    /*    GSList *p_list = (GSList *)user_data; */
    planets = g_slist_append (planets, value);
  }

  g_hash_table_foreach (planet_list, (GHFunc)add_item, NULL);
  
  for (i = 0; i < TOTAL_QUADS; i++) {
    ppq[i] = g_slist_copy(planets_per_quad[i]);
  }

  for (i = 0; i < g_slist_length(planets); i++) {
    /* Get 'i' planet... */
    planet_a = GWP_PLANET (g_slist_nth_data (planets, i));
    g_assert (GWP_IS_PLANET(planet_a));
    vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(planet_a)),
		  gwp_object_get_y_coord(GWP_OBJECT(planet_a)),
		  &wx, &wy);
    quad = get_quadrant (wx, wy);

    /* ...remove it from the list per quad... */
    ppq[quad] = g_slist_remove (ppq[quad], planet_a);

    /* ...and draw the lines! (if necessary) */
    list_nearby = starchart_get_surrounding_quads (ppq, quad);
    for (j = 0; j < g_slist_length(list_nearby); j++) {
      planet_b = GWP_PLANET (g_slist_nth_data (list_nearby, j));
      g_assert (GWP_IS_PLANET(planet_b));

      vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(planet_a)),
		    gwp_object_get_y_coord(GWP_OBJECT(planet_a)),
		    &ax, &ay);
      vp_coord_v2w (gwp_object_get_x_coord(GWP_OBJECT(planet_b)),
		    gwp_object_get_y_coord(GWP_OBJECT(planet_b)),
		    &bx, &by);

      dist = sqrt (((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by)));

      /* When distance is 1 or less LY at Warp 9... */
      /* FIXME: 84 LY because of the warp well, we should
	 read this configuration from the host */
      if (dist <= 84.0) {
	GnomeCanvasPoints *points = gnome_canvas_points_new (2);
	zoom = gwp_game_state_get_starchart_zoom (game_state);

	points->coords[0] = ax;
	points->coords[1] = ay;
	points->coords[2] = bx;
	points->coords[3] = by;

	gnome_canvas_item_new (starchart_get_grp_constellations (),
			       GNOME_TYPE_CANVAS_LINE,
			       "fill_color", QUADRANT_GRID_COLOR,
			       "line_style", GDK_LINE_ON_OFF_DASH,
			       "width_pixels", 1,
			       "points", points, NULL);
      }
    }
  }
}
