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

/* Planet utility functions */

#ifndef PLANET_H
#define PLANET_H

#include "vp_types.h"
#include "race.h"

Planet *planet_get(GHashTable *list, gint planet_id);
Planet *planet_copy(Planet *planet);
Base *planet_get_base(Planet *planet);

/* Planet check functions */
gboolean planet_has_starbase(Planet *planet);
gint planet_is_known(Planet *planet);
gboolean planet_is_mine(Planet *planet);
gboolean planet_valid_coords(Planet *planet);
gint planet_what_is(Planet *planet);

/* Planet "GET" functions */
gint16 planet_get_id(Planet *planet);
gchar *planet_get_name(Planet *planet);
enum races planet_get_owner(Planet *planet);
gchar *planet_get_fcode(Planet *planet);
gint16 planet_get_mines(Planet *planet);
gint16 planet_get_factories(Planet *planet);
gint16 planet_get_defense_posts(Planet *planet);
gint32 planet_get_mined_neutronium(Planet *planet);
gint32 planet_get_mined_tritanium(Planet *planet);
gint32 planet_get_mined_duranium(Planet *planet);
gint32 planet_get_mined_molybdenum(Planet *planet);
gint32 planet_get_colonists(Planet *planet);
gint32 planet_get_supplies(Planet *planet);
gint32 planet_get_megacredits(Planet *planet);
gint32 planet_get_ground_neutronium(Planet *planet);
gint32 planet_get_ground_tritanium(Planet *planet);
gint32 planet_get_ground_duranium(Planet *planet);
gint32 planet_get_ground_molybdenum(Planet *planet);
gint16 planet_get_dens_neutronium(Planet *planet);
gint16 planet_get_dens_tritanium(Planet *planet);
gint16 planet_get_dens_duranium(Planet *planet);
gint16 planet_get_dens_molybdenum(Planet *planet);
gint16 planet_get_tax_colonists(Planet *planet);
gint16 planet_get_tax_natives(Planet *planet);
gint16 planet_get_happiness_colonists(Planet *planet);
gint16 planet_get_happiness_natives(Planet *planet);
void planet_set_happiness_natives(Planet *planet, gint happ);
void planet_set_happiness_colonists(Planet *planet, gint happ);
gchar *planet_get_native_spi_chars(Planet *planet);
gint planet_get_native_spi(Planet *planet);
gint32 planet_get_natives(Planet *planet);
enum natives planet_get_native_race(Planet *planet);
gchar *planet_get_native_race_chars(Planet *planet);
gint16 planet_get_temperature(Planet *planet);
gint16 planet_get_temperature_f(Planet *planet);
gchar *planet_get_temperature_str(Planet *planet);
gint16 planet_get_build_base(Planet *planet);
gint planet_get_visibility(Planet *planet);

gint planet_neutronium_extraction_rate(Planet *planet);
gint planet_neutronium_turns_left(Planet *planet);
gint planet_molybdenum_extraction_rate(Planet *planet);
gint planet_molybdenum_turns_left(Planet *planet);
gint planet_tritanium_extraction_rate(Planet *planet);
gint planet_tritanium_turns_left(Planet *planet);
gint planet_duranium_extraction_rate(Planet *planet);
gint planet_duranium_turns_left(Planet *planet);
gint planet_mineral_extraction_rate(gint mines, gint density, gint mineral);
gint planet_mineral_turns_left(gint mineral, gint extraction_rate);
gdouble planet_get_ground_percent(gint mineral);

gint planet_get_tax_earned_natives(Planet *planet);
gint planet_get_tax_earned_colonists(Planet *planet);
gint planet_get_happiness_col_change(Planet *planet);
gint planet_get_happiness_nat_change(Planet *planet);

gint planet_get_nat_growth_limit(Planet *planet);
gint planet_get_col_growth_limit(Planet *planet);

/* Planet Defense Systems funcs */
gint planet_get_def_sys_beams_nr(Planet *planet);
gint planet_get_def_sys_fighters_nr(Planet *planet);
gint planet_get_def_sys_fighter_bays(Planet *planet);
gint planet_get_def_sys_battle_mass(Planet *planet);

#endif
