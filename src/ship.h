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

#ifndef SHIP_H
#define SHIP_H

#include "vp_types.h"

Ship *ship_get(GHashTable *list, gint ship_id);

gint16 ship_get_id(Ship *ship);
gint16 ship_get_owner(Ship *ship);
gchar *ship_get_fcode(Ship *ship);
gint16 ship_get_warp_factor(Ship *ship);
gint16 ship_get_x_to_waypoint(Ship *ship);
gint16 ship_get_y_to_waypoint(Ship *ship);
gint16 ship_get_x_position(Ship *ship);
gint16 ship_get_y_position(Ship *ship);
gint16 ship_get_engine_type(Ship *ship);
gint16 ship_get_hull_type(Ship *ship);
gint16 ship_get_beams_type(Ship *ship);
gint16 ship_get_beams(Ship *ship);
gint16 ship_get_fighter_bays(Ship *ship);
gint16 ship_get_torpedoes_type(Ship *ship);
gint16 ship_get_torpedoes_fighters(Ship *ship);
gint16 ship_get_torpedoes_launchers(Ship *ship);
gint16 ship_get_mission(Ship *ship);
gint16 ship_get_primary_enemy(Ship *ship);
gint16 ship_get_tow_mission_ship_id(Ship *ship);
gint16 ship_get_damage(Ship *ship);
gint16 ship_get_crew(Ship *ship);
gint16 ship_get_colonists(Ship *ship);
gchar *ship_get_name(Ship *ship);
gint16 ship_get_neutronium(Ship *ship);
gint16 ship_get_tritanium(Ship *ship);
gint16 ship_get_duranium(Ship *ship);
gint16 ship_get_molybdenum(Ship *ship);
gint16 ship_get_supplies(Ship *ship);
gint16 ship_get_unload_neutronium(Ship *ship);
gint16 ship_get_unload_tritanium(Ship *ship);
gint16 ship_get_unload_duranium(Ship *ship);
gint16 ship_get_unload_molybdenum(Ship *ship);
gint16 ship_get_unload_supplies(Ship *ship);
gint16 ship_get_unload_colonists(Ship *ship);
gint16 ship_get_unload_planet_id(Ship *ship);
gint16 ship_get_transfer_neutronium(Ship *ship);
gint16 ship_get_transfer_tritanium(Ship *ship);
gint16 ship_get_transfer_duranium(Ship *ship);
gint16 ship_get_transfer_molybdenum(Ship *ship);
gint16 ship_get_transfer_supplies(Ship *ship);
gint16 ship_get_transfer_colonists(Ship *ship);
gint16 ship_get_transfer_ship_id(Ship *ship);
gint16 ship_get_intercept_mission_ship_id(Ship *ship);
gint16 ship_get_megacredits(Ship *ship);

gboolean ship_is_known(Ship *ship);
gboolean ship_is_mine(Ship *ship);
gboolean ship_valid_coords(Ship *ship);
gint ship_what_is(Ship *ship);

#endif
