/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2004  Lucas Di Pentima <lucas@lunix.com.ar>
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

/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.13  2005/05/31 13:17:38  ldipenti
    Feature: Added CVS metadata on source files

*/

/*
 * GwpGameState:
 * -------------
 *
 * This class encapsulates a running game session' state. It contains
 * data that describe the actual state of the interface, user settings, etc.
 * Some of this data will be saved for a future run, some won't.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifndef GWP_GAME_STATE_H
#define GWP_GAME_STATE_H

#include <glib.h>
#include <glib-object.h>

#include "race.h"
#include "gwp-planet.h"
#include "gwp-ship.h"

/*
 * Type macros.
 */
typedef struct _GwpGameState GwpGameState;
typedef struct _GwpGameStateClass GwpGameStateClass;
typedef struct _GwpGameStatePrivate GwpGameStatePrivate;

struct _GwpGameState {
  GObject parent;

  /* instance members */

  /* private */
  GwpGameStatePrivate *priv;
};

struct _GwpGameStateClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_TYPE_GAME_STATE */
GType gwp_game_state_get_type (void);

/*
 * Public method definitions.
 */
GwpGameState *gwp_game_state_new (void);
void gwp_game_state_postinit (GwpGameState *self);

/**********************/
/* High level methods */
/**********************/
gchar * gwp_game_state_get_full_path (GwpGameState *self, gchar *filename);
void gwp_game_state_set_last_coords (GwpGameState *self, gint16 x, gint16 y);
gchar * gwp_game_state_get_dat_filename (GwpGameState *self,  gchar *prefix, gchar *suffix);


/*******************/
/* Get/Set methods */
/*******************/
void gwp_game_state_set_name (GwpGameState *self, const gchar *name);
const gchar * gwp_game_state_get_name (const GwpGameState *self);
void gwp_game_state_set_dir (GwpGameState *self, gchar *dir);
gchar * gwp_game_state_get_dir (const GwpGameState *self);
void gwp_game_state_set_starchart_zoom (GwpGameState *self, gdouble zoom);
gdouble gwp_game_state_get_starchart_zoom (GwpGameState *self);
void gwp_game_state_set_race (GwpGameState *self, gint race_num);
enum races gwp_game_state_get_race (GwpGameState *self);
gint gwp_game_state_get_race_nr (GwpGameState *self);
void gwp_game_state_set_last_x_coord (GwpGameState *self, gint x);
gint16 gwp_game_state_get_last_x_coord (GwpGameState *self);
void gwp_game_state_set_last_y_coord (GwpGameState *self, gint y);
gint16 gwp_game_state_get_last_y_coord (GwpGameState *self);
void gwp_game_state_set_pnames (GwpGameState *self, GList *pnames);
GList * gwp_game_state_get_pnames (GwpGameState *self);
void gwp_game_state_set_turn_number (GwpGameState *self, gint turn);
gint gwp_game_state_get_turn_number (GwpGameState *self);
void gwp_game_state_set_player_email (GwpGameState *self, gchar *pe);
gchar * gwp_game_state_get_player_email (GwpGameState *self);
void gwp_game_state_set_host_email (GwpGameState *self, gchar *he);
gchar * gwp_game_state_get_host_email (GwpGameState *self);
void gwp_game_state_set_trn_dir (GwpGameState *self, gchar *dir);
gchar * gwp_game_state_get_trn_dir (GwpGameState *self);
void gwp_game_state_set_rst_dir (GwpGameState *self, gchar *dir);
gchar * gwp_game_state_get_rst_dir (GwpGameState *self);
void gwp_game_state_set_host_type (GwpGameState *self, gint type);
gint gwp_game_state_get_host_type (GwpGameState *self);
void gwp_game_state_set_planet_names (GwpGameState *self, gboolean show);
gboolean gwp_game_state_get_planet_names (GwpGameState *self);
void gwp_game_state_set_scanner_area (GwpGameState *self, gboolean show);
gboolean gwp_game_state_get_scanner_area (GwpGameState *self);
void gwp_game_state_set_minefields (GwpGameState *self, gboolean show);
gboolean gwp_game_state_get_minefields (GwpGameState *self);
void gwp_game_state_set_ion_storms (GwpGameState *self, gboolean show);
gboolean gwp_game_state_get_ion_storms (GwpGameState *self);
void gwp_game_state_set_extra_panel_open (GwpGameState *self, gboolean show);
gboolean gwp_game_state_get_extra_panel_open (GwpGameState *self);
#ifdef USE_PYTHON
void gwp_game_state_set_plugin_mgr (GwpGameState *self, void *obj);
void * gwp_game_state_get_plugin_mgr (GwpGameState *self);
#endif
GwpShip * gwp_game_state_get_selected_ship (GwpGameState *self);
GwpPlanet * gwp_game_state_get_selected_planet (GwpGameState *self);


/*************************************/
/******* Host Settings Methods *******/
/*************************************/

gint gwp_game_state_get_host_recycle_col_ship (GwpGameState *self);
void gwp_game_state_set_host_recycle_col_ship (GwpGameState *self, gint percent);
void gwp_game_state_set_host_large_meteor_impact (GwpGameState *self, gint percent);
gint gwp_game_state_get_host_large_meteor_impact (GwpGameState *self);
void gwp_game_state_set_host_space_mines (GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_space_mines (GwpGameState *self);
gboolean gwp_game_state_get_host_alchemy_ships (GwpGameState *self);
void gwp_game_state_set_host_alchemy_ships (GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_delete_old_msgs (GwpGameState *self);
void gwp_game_state_set_host_delete_old_msgs (GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_disable_pwd (GwpGameState *self);
void gwp_game_state_set_host_disable_pwd (GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_rebel_build_fighters (GwpGameState *self);
void gwp_game_state_set_host_rebel_build_fighters (GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_colonial_build_fighters (GwpGameState *self);
void gwp_game_state_set_host_colonial_build_fighters (GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_robots_build_fighters (GwpGameState *self);
void gwp_game_state_set_host_robots_build_fighters (GwpGameState *self, gboolean bool);
gint gwp_game_state_get_host_cloak_failure (GwpGameState *self);
void gwp_game_state_set_host_cloak_failure (GwpGameState *self, gint percent);
gboolean gwp_game_state_get_host_priv_rob_cloak (GwpGameState *self);
void gwp_game_state_set_host_priv_rob_cloak (GwpGameState *self, gboolean bool);
gint gwp_game_state_get_host_dark_sense_range (GwpGameState *self);
void gwp_game_state_set_host_dark_sense_range (GwpGameState *self, gint percent);

gint gwp_game_state_get_host_ground_attack_ratio (GwpGameState *self, gint race);
void gwp_game_state_set_host_ground_attack_ratio (GwpGameState *self, gint race, gint ratio);
gint gwp_game_state_get_host_ships_visible_range (GwpGameState *self);
void gwp_game_state_set_host_ships_visible_range (GwpGameState *self, gint range);
gboolean gwp_game_state_get_host_lizard_hiss_mission (GwpGameState *self);
void gwp_game_state_set_host_lizard_hiss_mission (GwpGameState *self, gboolean hiss);
gboolean gwp_game_state_get_host_rebel_ground_attack(GwpGameState *self);
void gwp_game_state_set_host_rebel_ground_attack(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_fed_super_refit(GwpGameState *self);
void gwp_game_state_set_host_fed_super_refit(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_crystal_web_mines(GwpGameState *self);
void gwp_game_state_set_host_crystal_web_mines(GwpGameState *self, gboolean bool);

gint gwp_game_state_get_host_ground_defense_ratio(GwpGameState *self, gint race);
void gwp_game_state_set_host_ground_defense_ratio(GwpGameState *self, gint race, gint ration);
gint gwp_game_state_get_host_cloak_fuel_use(GwpGameState *self);
void gwp_game_state_set_host_cloak_fuel_use(GwpGameState *self, gint use);
gint gwp_game_state_get_host_sensors_range (GwpGameState *self);
void gwp_game_state_set_host_sensors_range (GwpGameState *self, gint range);
gboolean gwp_game_state_get_host_new_natives(GwpGameState *self);
void gwp_game_state_set_host_new_natives(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_planets_attack_ships(GwpGameState *self);
void gwp_game_state_set_host_planets_attack_ships(GwpGameState *self, gboolean bool);
gint gwp_game_state_get_host_borg_assimilation_rate(GwpGameState *self);
void gwp_game_state_set_host_borg_assimilation_rate(GwpGameState *self, gint rate);

gint gwp_game_state_get_host_starbase_free_fighters(GwpGameState *self, gint race);
void gwp_game_state_set_host_starbase_free_fighters(GwpGameState *self, gint race, gint free);
gint gwp_game_state_get_host_webmine_decay(GwpGameState *self);
void gwp_game_state_set_host_webmine_decay(GwpGameState *self, gint decay);
gint gwp_game_state_get_host_mine_decay(GwpGameState *self);
void gwp_game_state_set_host_mine_decay(GwpGameState *self, gint decay);
gint gwp_game_state_get_host_max_mine_radius(GwpGameState *self);
void gwp_game_state_set_host_max_mine_radius(GwpGameState *self, gint radius);
gint gwp_game_state_get_host_isotope_tudr(GwpGameState *self);
void gwp_game_state_set_host_isotope_tudr(GwpGameState *self, gint tudr);
gint gwp_game_state_get_host_structure_decay(GwpGameState *self);
void gwp_game_state_set_host_structure_decay(GwpGameState *self, gint decay);

gint gwp_game_state_get_host_mining_rate (GwpGameState *self, gint race);
void gwp_game_state_set_host_mining_rate (GwpGameState *self, gint race, gint rate);
gboolean gwp_game_state_get_host_colonists_eat_supplies (GwpGameState *self);
void gwp_game_state_set_host_colonists_eat_supplies (GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_zero_fuel_ships_move (GwpGameState *self);
void gwp_game_state_set_host_zero_fuel_ships_move (GwpGameState *self, gboolean bool);
gint gwp_game_state_get_host_mine_hit_odds (GwpGameState *self);
void gwp_game_state_set_host_mine_hit_odds (GwpGameState *self, gint ratio);
gint gwp_game_state_get_host_webmine_hit_odds (GwpGameState *self);
void gwp_game_state_set_host_webmine_hit_odds (GwpGameState *self, gint ratio);
gint gwp_game_state_get_host_mine_detect_range (GwpGameState *self);
void gwp_game_state_set_host_mine_detect_range (GwpGameState *self, gint range);

gint gwp_game_state_get_host_tax_rate (GwpGameState *self, gint race);
void gwp_game_state_set_host_tax_rate (GwpGameState *self, gint race, gint rate);
gboolean gwp_game_state_get_host_mines_destroy_mines(GwpGameState *self);
void gwp_game_state_set_host_mines_destroy_mines(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_es_bonus(GwpGameState *self);
void gwp_game_state_set_host_es_bonus(GwpGameState *self, gboolean bool);
gint gwp_game_state_get_host_es_bonus_rate(GwpGameState *self);
void gwp_game_state_set_host_es_bonus_rate(GwpGameState *self, gint rate);

gint gwp_game_state_get_host_colonial_sweep_rate(GwpGameState *self);
void gwp_game_state_set_host_colonial_sweep_rate(GwpGameState *self, gint rate);
gboolean gwp_game_state_get_host_colonial_sweep_webs(GwpGameState *self);
void gwp_game_state_set_host_colonial_sweep_webs(GwpGameState *self, gboolean bool);
gint gwp_game_state_get_host_mine_sweep_rate(GwpGameState *self);
void gwp_game_state_set_host_mine_sweep_rate(GwpGameState *self, gint rate);
gint gwp_game_state_get_host_webmine_sweep_rate(GwpGameState *self);
void gwp_game_state_set_host_webmine_sweep_rate(GwpGameState *self, gint rate);
gint gwp_game_state_get_host_hiss_mission_effect(GwpGameState *self);
void gwp_game_state_set_host_hiss_mission_effect(GwpGameState *self, gint effect);
gint gwp_game_state_get_host_rob_mission_failure(GwpGameState *self);
void gwp_game_state_set_host_rob_mission_failure(GwpGameState *self, gint failure);
gboolean gwp_game_state_get_host_planet_attack_rebel(GwpGameState *self);
void gwp_game_state_set_host_planet_attack_rebel(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_planet_attack_fascist(GwpGameState *self);
void gwp_game_state_set_host_planet_attack_fascist(GwpGameState *self, gboolean bool);
gint gwp_game_state_get_host_mine_sweep_range(GwpGameState *self);
void gwp_game_state_set_host_mine_sweep_range(GwpGameState *self, gint range);
gint gwp_game_state_get_host_webmine_sweep_range(GwpGameState *self);
void gwp_game_state_set_host_webmine_sweep_range(GwpGameState *self, gint range);
gboolean gwp_game_state_get_host_science_missions(GwpGameState *self);
void gwp_game_state_set_host_science_missions(GwpGameState *self, gboolean bool);
gdouble gwp_game_state_get_host_cloaked_mine_hit(GwpGameState *self);
void gwp_game_state_set_host_cloaked_mine_hit(GwpGameState *self, gdouble rate);
gint gwp_game_state_get_host_cloak_prevent_damage(GwpGameState *self);
void gwp_game_state_set_host_cloak_prevent_damage(GwpGameState *self, gint rate);
gboolean gwp_game_state_get_host_fed_crew_bonus(GwpGameState *self);
void gwp_game_state_set_host_fed_crew_bonus(GwpGameState *self, gboolean bool);

gboolean gwp_game_state_get_host_one_engine_tow(GwpGameState *self);
void gwp_game_state_set_host_one_engine_tow(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_hyperdrive_ships(GwpGameState *self);
void gwp_game_state_set_host_hyperdrive_ships(GwpGameState *self, gboolean bool);
gint gwp_game_state_get_host_climate_death_rate (GwpGameState *self);
void gwp_game_state_set_host_climate_death_rate (GwpGameState *self, gint rate);
gboolean gwp_game_state_get_host_gravity_well(GwpGameState *self);
void gwp_game_state_set_host_gravity_well(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_crystal_desert_adv (GwpGameState *self);
void gwp_game_state_set_host_crystal_desert_adv (GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_mines_destroy_webs(GwpGameState *self);
void gwp_game_state_set_host_mines_destroy_webs(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_climate_limit_pop(GwpGameState *self);
void gwp_game_state_set_host_climate_limit_pop(GwpGameState *self, gboolean bool);

gint gwp_game_state_get_host_max_planet_income(GwpGameState *self);
void gwp_game_state_set_host_max_planet_income(GwpGameState *self, gint max);
gint gwp_game_state_get_host_ion_storms(GwpGameState *self);
void gwp_game_state_set_host_ion_storms(GwpGameState *self, gint storm);
gboolean gwp_game_state_get_host_firecloud_chunnel(GwpGameState *self);
void gwp_game_state_set_host_firecloud_chunnel(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_superspy_deluxe(GwpGameState *self);
void gwp_game_state_set_host_superspy_deluxe(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_storms_hide_mines(GwpGameState *self);
void gwp_game_state_set_host_storms_hide_mines(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_fascist_glory_device(GwpGameState *self);
void gwp_game_state_set_host_fascist_glory_device(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_loki_anticloak(GwpGameState *self);
void gwp_game_state_set_host_loki_anticloak(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_ladyroyale_gambling(GwpGameState *self);
void gwp_game_state_set_host_ladyroyale_gambling(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_cloaked_ships_attack(GwpGameState *self);
void gwp_game_state_set_host_cloaked_ships_attack(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_ship_cloning(GwpGameState *self);
void gwp_game_state_set_host_ship_cloning(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_boarding_party(GwpGameState *self);
void gwp_game_state_set_host_boarding_party(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_imperial_assault(GwpGameState *self);
void gwp_game_state_set_host_imperial_assault(GwpGameState *self, gboolean bool);

gint gwp_game_state_get_host_cobol_fuel(GwpGameState *self);
void gwp_game_state_set_host_cobol_fuel(GwpGameState *self, gint rate);
gint gwp_game_state_get_host_hulltech_slowed_minehits(GwpGameState *self);
void gwp_game_state_set_host_hulltech_slowed_minehits(GwpGameState *self, gint tech);
gboolean gwp_game_state_get_host_aries_makes_fuel(GwpGameState *self);
void gwp_game_state_set_host_aries_makes_fuel(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_bioscanners(GwpGameState *self);
void gwp_game_state_set_host_bioscanners(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_loki_decloak_birds(GwpGameState *self);
void gwp_game_state_set_host_loki_decloak_birds(GwpGameState *self, gboolean bool);
gboolean gwp_game_state_get_host_vpa_extras(GwpGameState *self);
void gwp_game_state_set_host_vpa_extras(GwpGameState *self, gboolean bool);

/*
 * Standard defines.
 */
#define GWP_TYPE_GAME_STATE            (gwp_game_state_get_type())
#define GWP_GAME_STATE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_GAME_STATE, GwpGameState))
#define GWP_GAME_STATE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_GAME_STATE, GwpGameStateClass))
#define GWP_IS_GAME_STATE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_GAME_STATE))
#define GWP_IS_GAME_STATE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_GAME_STATE))
#define GWP_GAME_STATE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_GAME_STATE, GwpGameStateClass))

/**
 * Host type enumeration
 */
enum {
  GWP_GAME_STATE_HOST_TYPE_0,
  GWP_GAME_STATE_HOST_TYPE_THOST,
  GWP_GAME_STATE_HOST_TYPE_PHOST,
};

#endif
