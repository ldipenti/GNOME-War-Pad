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

#ifndef GWP_SHIP_H
#define GWP_SHIP_H

#include <glib.h>
#include <glib-object.h>

#include "global.h"
#include "gwp-flying-object.h"
#include "gwp-specs.h"

/*
 * Type macros.
 */

typedef struct _GwpShip GwpShip;
typedef struct _GwpShipClass GwpShipClass;
typedef struct _GwpShipPrivate GwpShipPrivate;

struct _GwpShip {
  GwpFlyingObject parent;

  /* instance members */

  /* private */
  GwpShipPrivate *priv;
};

struct _GwpShipClass {
  GwpFlyingObjectClass parent;
  /* class members */
};

/* used by GWP_SHIP_TYPE */
GType gwp_ship_get_type (void);

/*
 * Public method definitions.
 */
GwpShip *gwp_ship_new (void);


/**********************/
/* High level methods */
/**********************/
gboolean gwp_ship_has_beam_weapons (GwpShip *self);
gboolean gwp_ship_has_torp_weapons (GwpShip *self);

GString * gwp_ship_get_primary_enemy_name (GwpShip *self);
GString * gwp_ship_get_mission_name (GwpShip *self);
GString * gwp_ship_get_owner_name (GwpShip *self);

GString * gwp_ship_get_hull_name_trunc (GwpShip *self, gint len);
gint gwp_ship_get_hull_cargo (GwpShip *self);
gint gwp_ship_get_hull_fuel_tank (GwpShip *self);
gint gwp_ship_get_hull_crew (GwpShip *self);
gint gwp_ship_get_hull_engines (GwpShip *self);
gint gwp_ship_get_hull_beam_weapons (GwpShip *self);
gint gwp_ship_get_hull_torp_launchers (GwpShip *self);
gint gwp_ship_get_hull_fighter_bays (GwpShip *self);
gint gwp_ship_get_hull_picture (GwpShip *self);

GString * gwp_ship_get_engine_name (GwpShip *self);
GString * gwp_ship_get_beams_name (GwpShip *self);
GString * gwp_ship_get_torps_name (GwpShip *self);

gint gwp_ship_calculate_heading (GwpShip *self);
GwpShip * gwp_ship_get (GHashTable *list, gint ship_id);
gboolean gwp_ship_valid_coords(GwpShip *self);
gboolean gwp_ship_is_mine(GwpShip *self);
void gwp_ship_get_waypoint(GwpShip *self, gint *wp_x, gint *wp_y);
gdouble gwp_ship_calculate_waypoint_distance (GwpShip *self);
gint gwp_ship_calculate_eta (GwpShip *self);

gint gwp_ship_calculate_fuel_usage (GwpShip *self);
gint gwp_ship_calculate_cargo (GwpShip *self);
gint gwp_ship_calculate_mass (GwpShip *self);
gint gwp_ship_calculate_lay_mines_torps (GwpShip *self);


/****************************/
/* Get/Set (boring) methods */
/****************************/
gboolean gwp_ship_is_known (GwpShip *self);
void gwp_ship_set_known (GwpShip *self, gboolean is_known);

gint gwp_ship_get_owner (GwpShip *self);
void gwp_ship_set_owner (GwpShip *self, gint owner);

gint gwp_ship_get_mass_if_unknown (GwpShip *self);
void gwp_ship_set_mass_if_unknown (GwpShip *self, gint mass);

GString *gwp_ship_get_fcode (GwpShip *self);
void gwp_ship_set_fcode (GwpShip *self, GString *fcode);

gint16 gwp_ship_get_x_to_waypoint (GwpShip *self);
void gwp_ship_set_x_to_waypoint (GwpShip *self, gint16 xw);
gint16 gwp_ship_get_y_to_waypoint (GwpShip *self);
void gwp_ship_set_y_to_waypoint (GwpShip *self, gint16 yw);

gint16 gwp_ship_get_engines_type (GwpShip *self);
void gwp_ship_set_engines_type (GwpShip *self, gint16 et);
gint16 gwp_ship_get_hull_type (GwpShip *self);
void gwp_ship_set_hull_type (GwpShip *self, gint16 ht);
gint16 gwp_ship_get_beams_type (GwpShip *self);
void gwp_ship_set_beams_type (GwpShip *self, gint16 bt);
gint16 gwp_ship_get_beams (GwpShip *self);
void gwp_ship_set_beams (GwpShip *self, gint16 beams);
gint16 gwp_ship_get_fighter_bays (GwpShip *self);
void gwp_ship_set_fighter_bays (GwpShip *self, gint16 f_bays);
gint16 gwp_ship_get_torps_type (GwpShip *self);
void gwp_ship_set_torps_type (GwpShip *self, gint16 tt);
gint16 gwp_ship_get_torps (GwpShip *self);
void gwp_ship_set_torps (GwpShip *self, gint16 torps);
gint16 gwp_ship_get_fighters (GwpShip *self);
void gwp_ship_set_fighters (GwpShip *self, gint16 fighters);
gint16 gwp_ship_get_torps_launchers (GwpShip *self);
void gwp_ship_set_torps_launchers (GwpShip *self, gint16 tl);

gint16 gwp_ship_get_mission (GwpShip *self);
void gwp_ship_set_mission (GwpShip *self, gint16 mission);

gint16 gwp_ship_get_primary_enemy (GwpShip *self);
void gwp_ship_set_primary_enemy (GwpShip *self, gint16 pe);

gint16 gwp_ship_get_tow_ship_id (GwpShip *self);
void gwp_ship_set_tow_ship_id (GwpShip *self, gint16 id);

gint16 gwp_ship_get_damage (GwpShip *self);
void gwp_ship_set_damage (GwpShip *self, gint16 dmg);
gint16 gwp_ship_get_crew (GwpShip *self);
void gwp_ship_set_crew (GwpShip *self, gint16 crew);
gint16 gwp_ship_get_colonists (GwpShip *self);
void gwp_ship_set_colonists (GwpShip *self, gint16 col);

gint16 gwp_ship_get_neutronium (GwpShip *self);
void gwp_ship_set_neutronium (GwpShip *self, gint16 neu);
gint16 gwp_ship_get_tritanium (GwpShip *self);
void gwp_ship_set_tritanium (GwpShip *self, gint16 tri);
gint16 gwp_ship_get_duranium (GwpShip *self);
void gwp_ship_set_duranium (GwpShip *self, gint16 dur);
gint16 gwp_ship_get_molybdenum (GwpShip *self);
void gwp_ship_set_molybdenum (GwpShip *self, gint16 mol);
gint16 gwp_ship_get_supplies (GwpShip *self);
void gwp_ship_set_supplies (GwpShip *self, gint16 sup);

/* Unload cargo to planet */
gint16 gwp_ship_get_unload_neutronium (GwpShip *self);
void gwp_ship_set_unload_neutronium (GwpShip *self, gint16 neu);
gint16 gwp_ship_get_unload_tritanium (GwpShip *self);
void gwp_ship_set_unload_tritanium (GwpShip *self, gint16 tri);
gint16 gwp_ship_get_unload_duranium (GwpShip *self);
void gwp_ship_set_unload_duranium (GwpShip *self, gint16 dur);
gint16 gwp_ship_get_unload_molybdenum (GwpShip *self);
void gwp_ship_set_unload_molybdenum (GwpShip *self, gint16 mol);
gint16 gwp_ship_get_unload_supplies (GwpShip *self);
void gwp_ship_set_unload_supplies (GwpShip *self, gint16 sup);
void gwp_ship_set_unload_colonists (GwpShip *self, gint16 col);
gint16 gwp_ship_get_unload_colonists (GwpShip *self);
gint16 gwp_ship_get_unload_planet_id (GwpShip *self);
void gwp_ship_set_unload_planet_id (GwpShip *self, gint16 pid);

/* Transfer cargo to ship */
gint16 gwp_ship_get_transfer_neutronium (GwpShip *self);
void gwp_ship_set_transfer_neutronium (GwpShip *self, gint16 neu);
gint16 gwp_ship_get_transfer_tritanium (GwpShip *self);
void gwp_ship_set_transfer_tritanium (GwpShip *self, gint16 tri);
gint16 gwp_ship_get_transfer_duranium (GwpShip *self);
void gwp_ship_set_transfer_duranium (GwpShip *self, gint16 dur);
gint16 gwp_ship_get_transfer_molybdenum (GwpShip *self);
void gwp_ship_set_transfer_molybdenum (GwpShip *self, gint16 mol);
gint16 gwp_ship_get_transfer_supplies (GwpShip *self);
void gwp_ship_set_transfer_supplies (GwpShip *self, gint16 sup);
void gwp_ship_set_transfer_colonists (GwpShip *self, gint16 col);
gint16 gwp_ship_get_transfer_colonists (GwpShip *self);
gint16 gwp_ship_get_transfer_ship_id (GwpShip *self);
void gwp_ship_set_transfer_ship_id (GwpShip *self, gint16 sid);

gint16 gwp_ship_get_intercept_ship_id (GwpShip *self);
void gwp_ship_set_intercept_ship_id (GwpShip *self, gint16 sid);

gint16 gwp_ship_get_megacredits (GwpShip *self);
void gwp_ship_set_megacredits (GwpShip *self, gint16 m);


/*
 * Standard defines.
 */
#define GWP_SHIP_TYPE            (gwp_ship_get_type())
#define GWP_TYPE_SHIP            (gwp_ship_get_type())
#define GWP_SHIP(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_SHIP_TYPE, GwpShip))
#define GWP_SHIP_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_SHIP_TYPE, GwpShipClass))
#define GWP_IS_SHIP(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_SHIP_TYPE))
#define GWP_IS_SHIP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_SHIP_TYPE))
#define GWP_SHIP_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_SHIP_TYPE, GwpShipClass))

#endif
