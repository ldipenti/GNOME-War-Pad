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

// Ship utility functions

#include "ship.h"
#include "vp_types.h"
#include "global.h"
#include "game_state.h"

/*
 * Returns the ship with id
 */
Ship *ship_get(GHashTable *list, gint ship_id) {
	return (Ship *) g_hash_table_lookup(list, (gconstpointer)ship_id);
}


// Ship data accessors

gint16 ship_get_id(Ship *ship) {
	return ship->sdata->id;
}

gint16 ship_get_owner(Ship *ship) {
	return ship->sdata->owner;
}

gchar *ship_get_fcode(Ship *ship) {
	gchar *fcode;
	fcode = g_malloc(4);
	fcode[0] = ship->sdata->fcode[0];
	fcode[1] = ship->sdata->fcode[1];
	fcode[2] = ship->sdata->fcode[2];
	fcode[3] = '\0';
	return fcode;
}

gint16 ship_get_warp_factor(Ship *ship) {
	return ship->sdata->warp_factor;
}

gint16 ship_get_x_to_waypoint(Ship *ship) {
    return ship->sdata->x_to_waypoint;
}

gint16 ship_get_y_to_waypoint(Ship *ship) {
	return ship->sdata->y_to_waypoint;
}

gint16 ship_get_x_position(Ship *ship) {
	//return ship->sdata->x_position;
    return ship->x;
}

gint16 ship_get_y_position(Ship *ship) {
	//return ship->sdata->y_position;
    return ship->y;
}

gint16 ship_get_engine_type(Ship *ship) {
	return ship->sdata->engine_type;
}

gint16 ship_get_hull_type(Ship *ship) {
	return ship->sdata->hull_type;
}

gint16 ship_get_beams_type(Ship *ship) {
	return ship->sdata->beams_type;
}

gint16 ship_get_beams(Ship *ship) {
	return ship->sdata->beams;
}

gint16 ship_get_fighter_bays(Ship *ship) {
	return ship->sdata->fighter_bays;
}

gint16 ship_get_torpedoes_type(Ship *ship) {
	return ship->sdata->torpedoes_type;
}

gint16 ship_get_torpedoes_fighters(Ship *ship) {
	return ship->sdata->torpedoes_fighters;
}

gint16 ship_get_torpedoes_launchers(Ship *ship) {
	return ship->sdata->torpedoes_launchers;
}

gint16 ship_get_mission(Ship *ship) {
	return ship->sdata->mission;
}

gint16 ship_get_primary_enemy(Ship *ship) {
	return ship->sdata->primary_enemy;
}

gint16 ship_get_tow_mission_ship_id(Ship *ship) {
	return ship->sdata->tow_mission_ship_id;
}

gint16 ship_get_damage(Ship *ship) {
	return ship->sdata->damage;
}

gint16 ship_get_crew(Ship *ship) {
	return ship->sdata->crew;
}

gint16 ship_get_colonists(Ship *ship) {
	return ship->sdata->colonists;
}

gchar *ship_get_name(Ship *ship) {
	gchar *name;
	name = g_malloc(21);
	if(ship->sdata != NULL) {
		name = g_strdup(ship->sdata->name);
	} else if(ship->tdata != NULL) {
		name = g_strdup(ship->tdata->name);
	} else {
		name = _("n/a");
	}
	return g_strchomp(name);
}

gint16 ship_get_neutronium(Ship *ship) {
	return ship->sdata->neutronium;
}

gint16 ship_get_tritanium(Ship *ship) {
	return ship->sdata->tritanium;
}

gint16 ship_get_duranium(Ship *ship) {
	return ship->sdata->duranium;
}

gint16 ship_get_molybdenum(Ship *ship) {
	return ship->sdata->molybdenum;
}

gint16 ship_get_supplies(Ship *ship) {
	return ship->sdata->supplies;
}

gint16 ship_get_unload_neutronium(Ship *ship) {
	return ship->sdata->unload_neutronium;
}

gint16 ship_get_unload_tritanium(Ship *ship) {
	return ship->sdata->unload_tritanium;
}

gint16 ship_get_unload_duranium(Ship *ship) {
	return ship->sdata->unload_duranium;
}

gint16 ship_get_unload_molybdenum(Ship *ship) {
	return ship->sdata->unload_molybdenum;
}

gint16 ship_get_unload_supplies(Ship *ship) {
	return ship->sdata->unload_supplies;
}

gint16 ship_get_unload_colonists(Ship *ship) {
	return ship->sdata->unload_colonists;
}

gint16 ship_get_unload_planet_id(Ship *ship) {
	return ship->sdata->unload_planet_id;
}

gint16 ship_get_transfer_neutronium(Ship *ship) {
	return ship->sdata->transfer_neutronium;
}

gint16 ship_get_transfer_tritanium(Ship *ship) {
	return ship->sdata->transfer_tritanium;
}

gint16 ship_get_transfer_duranium(Ship *ship) {
	return ship->sdata->transfer_duranium;
}

gint16 ship_get_transfer_molybdenum(Ship *ship) {
	return ship->sdata->transfer_molybdenum;
}

gint16 ship_get_transfer_supplies(Ship *ship) {
	return ship->sdata->transfer_supplies;
}

gint16 ship_get_transfer_colonists(Ship *ship) {
	return ship->sdata->transfer_colonists;
}

gint16 ship_get_transfer_ship_id(Ship *ship) {
	return ship->sdata->transfer_ship_id;
}

gint16 ship_get_intercept_mission_ship_id(Ship *ship) {
	return ship->sdata->intercept_mission_ship_id;
}

gint16 ship_get_megacredits(Ship *ship) {
	return ship->sdata->megacredits;
}

gboolean ship_is_known(Ship *ship) {
	if((ship != NULL) && ((ship->sdata != NULL) || 
			      (ship->tdata != NULL))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

gboolean ship_is_mine(Ship *ship)
{
    if(ship->owner == game_get_race(game_state)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

gboolean ship_valid_coords(Ship *ship)
{
	if(ship->x <= SHIP_VALID_X_MAX && ship->x >= SHIP_VALID_X_MIN &&
		ship->y <= SHIP_VALID_Y_MAX && ship->y >= SHIP_VALID_Y_MIN) {
			return TRUE;
		} else {
			return FALSE;
		}
}

gint ship_what_is(Ship *ship)
{
	if(ship_get_owner(ship) == game_get_race(game_state)) {
		return IS_MINE;
	} else {
		return IS_ENEMY; // FIXME: Check for allied ships!!!
	}
}
