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

// Planet utility functions

#ifndef PLANET_H
#define PLANET_H

#include "vp_types.h"


Planet *planet_get(GHashTable *list, gint planet_id);

// Planet check functions
gint planet_is_known(Planet *planet);

// Planet "GET" functions
gint16 planet_get_id(Planet *planet);
gchar *planet_get_name(Planet *planet);
gint16 planet_get_owner(Planet *planet);
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
gchar *planet_get_native_spi(Planet *planet);
gint32 planet_get_natives(Planet *planet);
gchar *planet_get_native_race(Planet *planet);
gint16 planet_get_temperature(Planet *planet);
gchar *planet_get_temperature_str(Planet *planet);
gint16 planet_get_build_base(Planet *planet);

gboolean planet_is_mine(Planet *planet);
gboolean planet_valid_coords(Planet *planet);
gint planet_what_is(Planet *planet);

#endif
