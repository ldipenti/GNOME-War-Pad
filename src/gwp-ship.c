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

#include <math.h>

#include "gwp-flying-object.h"
#include "gwp-ship.h"
#include "race.h"
#include "mission.h"
#include "game_state.h"

GwpHullSpec * gwp_ship_get_hullspec (GwpShip *self);
GwpEngSpec * gwp_ship_get_engspec (GwpShip *self);
GwpBeamSpec * gwp_ship_get_beamspec (GwpShip *self);
GwpTorpSpec * gwp_ship_get_torpspec (GwpShip *self);

/**
 * Private data structure for the GwpShip type.
 *
 * This data should be accesed directly only by the low-level get/set
 * object's methods, the high-level ones shouldn't touch them.
 */
struct _GwpShipPrivate {
  gboolean dispose_has_run; /**< GType's internal control variable. */

  gboolean known; /**< TRUE if the current ship is owned by the player. */
  gint mass_if_unknown; /**< The ship's mass if it's unknown, 0 otherwise. */
  gint owner;     /**< Owner race number. Range 1..11 */
  GString *fcode; /**< Friendly Code. Max 3 chars */
  
  gint16 x_to_waypoint; /**< Distance left to waypoint's X coordinate.
			   Range -3000..3000. */
  gint16 y_to_waypoint; /**< Distance left to waypoint's Y coordinate.
			   Range -3000..3000. */

  gint16 engines_type;     /**< Ship's engine type. Range 1..9, index
			      into ENGSPEC.DAT. */
  gint16 hull_type;        /**< Ship's hull type. Range 1..105, index
			      into HULLSPEC.DAT. */
  gint16 beams_type;       /**< Ship's beam weapons type. Range 1..10
			      (0 = none), BEAMSPEC.DAT. */
  gint16 beams;            /**< Number of beam weapons. */
  gint16 fighter_bays;     /**< Number of fighter bays. */
  gint16 torps_type;       /**< Ship's torpedo weapons type. Range
			      1..10 (0 = none), index into TORPSPEC.DAT. */
  gint16 torps_nr;         /**< Number of torpedoes. */
  gint16 fighters_nr;      /**< Number of fighters. */
  gint16 torps_launchers;  /**< Number of torpedo launchers. */

  /**
   * Ship's current mission number.
   *
   * Standard Missions:
   *    - 0   none
   *    - 1   Explore
   *    - 2   Mine sweep
   *    - 3   Lay mines
   *    - 4   Kill
   *    - 5   Sensor sweep
   *    - 6   Colonize, Land & Disassemble
   *    - 7   Tow, tow arg = ship id (must be in the same spot)
   *    - 8   Intercept, Intercept arg = ship id (must be visible and within 200 ly)
   *    - 9   Race specific missions
   *       - 1 = Federation                  Super Refit
   *       - 2 = Lizard                      Hissssss!
   *       - 3 = Bird Man                    Super Spy
   *       - 4 = Fascist                     Pillage Planet
   *       - 5 = Privateer                   Rob Ship
   *       - 6 = Cyborg                      Self Repair
   *       - 7 = Crystal                     Lay Web Mines
   *       - 8 = Evil Empire                 Dark Sense
   *       - 9 = Robots                      Build Fighters
   *       - 10 = Rebel                       Rebel Ground Attack
   *       - 11 = Colonies                    Build Fighters
   *
   *    - 10  Cloak. Only possible on appropiate ships
   *    - 11  Beam up Neutronium
   *    - 12  Beam up Duranium
   *    - 13  Beam up Tritanium
   *    - 14  Beam uo Molybdenum
   *    - 15  Beam up Supplies
   * ...
   * ... 37 (check filefmt for PHost extended missions!
   */
  gint16 mission;

  gint16 primary_enemy; /**< Primary enemy race number. Can be 0 or
			   race id 1..11 */
  gint16 tow_ship_id; /**< Ship to tow. Ship ID to tow or first
			 mission argument) */
  gint16 damage; /**< Ship's damage. In percent - range 0..149 */
  gint16 crew; /**< Number of crew men on ship. If this number reach
		  0, the ship can be captured. */
  gint16 colonists; /**< Colonists on board. Specified in clans (100
		       people each) */
  
  gint16 neutronium;  /**< Neutronium on board. Specified in KT. */
  gint16 tritanium;  /**< Tritanium on board. Specified in KT. */
  gint16 duranium;  /**< Duranium on board. Specified in KT. */
  gint16 molybdenum;  /**< Molybdenum on board. Specified in KT. */
  gint16 supplies;  /**< Supplies on board. Specified in KT. */
	
  gint16 unload_neutronium; /**< Unload neutronium on
			       planet. Specified in KT. */
  gint16 unload_tritanium; /**< Unload tritanium on planet. Specified
			      in KT. */
  gint16 unload_duranium; /**< Unload duranium on planet. Specified in
			     KT. */
  gint16 unload_molybdenum; /**< Unload molybdenum on
			       planet. Specified in KT. */
  gint16 unload_colonists; /**< Unload colonists on planet. Specified
			      in KT. */
  gint16 unload_supplies; /**< Unload supplies on planet. Specified in
			     KT. */
  gint16 unload_planet_id; /**< Planet to unload cargo. Planet's ID,
			      or 0 to jettison. The ship must be on
			       planet's orbit. */
	

  gint16 transfer_neutronium; /**< Transfer neutronium to other
				 ship. Specified in KT. */
  gint16 transfer_tritanium; /**< Transfer tritanium to other
				ship. Specified in KT. */
  gint16 transfer_duranium; /**< Transfer duranium to other
			       ship. Specified in KT. */
  gint16 transfer_molybdenum; /**< Transfer molybdenum to other
				 ship. Specified in KT. */
  gint16 transfer_colonists; /**< Transfer colonists to other
				ship. Specified in KT. */
  gint16 transfer_supplies; /**< Transfer supplies to other
			       ship. Specified in KT. */
  gint16 transfer_ship_id; /**< Ship to transfer cargo. Ship's ID or 0
			      to jettison. Ship must be on the same
			      spot to transfer. */
	
  gint16 intercept_ship_id;  /**< Intercept ship, or second mission
				argument. Valid ship ID or 0. */
	
  gint16 megacredits;  /* Amount of cash on board. Range 0..10000 */
};

/*
 * forward definitions.
 */
static void gwp_ship_init (GTypeInstance  *instance,  gpointer g_class);
static void gwp_ship_class_init (GwpShipClass *klass);

GType gwp_ship_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpShipClass),
      NULL,            /* base_init */
      NULL,            /* base_finalize */
      (GClassInitFunc) gwp_ship_class_init,            /* class_init */
      NULL,            /* class_finalize */
      NULL,            /* class_data */
      sizeof (GwpShip),
      0,               /* n_preallocs */
      (GInstanceInitFunc) gwp_ship_init    /* instance_init */
    };
    type = g_type_register_static (GWP_TYPE_FLYING_OBJECT,
				   "GwpShip",
				   &info, 0);
  }
  return type;
}

/**
 * Instance constructor (internal)
 */
static void gwp_ship_init (GTypeInstance  *instance,
			   gpointer        g_class)
{
  GwpShip *self = (GwpShip *)instance;
  self->priv = g_new0 (GwpShipPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->owner = 0;
  self->priv->mass_if_unknown = 0;
  self->priv->known = FALSE;
  self->priv->fcode = g_string_new("GWP");

  self->priv->x_to_waypoint = 0;
  self->priv->y_to_waypoint = 0;

  self->priv->engines_type = 0;
  self->priv->hull_type = 0;
  self->priv->beams_type = 0;
  self->priv->beams = 0;
  self->priv->fighter_bays = 0;
  self->priv->torps_type = 0;
  self->priv->torps_nr = 0;
  self->priv->fighters_nr = 0;
  self->priv->torps_launchers = 0;

  self->priv->mission = 0;
  self->priv->primary_enemy = 0;
  self->priv->tow_ship_id = 0;

  self->priv->damage = 0;
  self->priv->crew = 0;
  self->priv->colonists = 0;

  self->priv->neutronium = 0;
  self->priv->tritanium = 0;
  self->priv->duranium = 0;
  self->priv->molybdenum = 0;
  self->priv->supplies = 0;

  self->priv->unload_neutronium = 0;
  self->priv->unload_tritanium = 0;
  self->priv->unload_duranium = 0;
  self->priv->unload_molybdenum = 0;
  self->priv->unload_colonists = 0;
  self->priv->unload_supplies = 0;
  self->priv->unload_planet_id = 0;

  self->priv->intercept_ship_id = 0;
  self->priv->megacredits = 0;

}

static void gwp_ship_dispose (GwpShip *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

/*  g_message ("Destroying ship #%d: %s", gwp_object_get_id(GWP_OBJECT(self)),
	     gwp_object_get_name(GWP_OBJECT(self))->str);
*/

  /*
   * Here I have to unref all members on which I own a reference.
   */
  g_string_free(self->priv->fcode, TRUE);
}

static void gwp_ship_finalize (GwpShip *self)
{
  /* 
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_ship_class_init (GwpShipClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /*
   * Register destructor methods.
   */
  gobject_class->dispose = (void *) gwp_ship_dispose;
  gobject_class->finalize = (void *) gwp_ship_finalize;
}

/*
 * Public method implementations.
 */

/**
 * Instantiates a new ship.
 *
 * @return The new instantiated GwpShip.
 */
GwpShip * gwp_ship_new (void)
{
  return g_object_new (gwp_ship_get_type(), NULL);
}

/*******************/
/* Private methods */
/*******************/

/**
 * Gets the correct hull specs for the ship.
 *
 * Search on the global hullspec list the correct hull spec for the
 * current ship. This is a private method, just for use
 * by the other ship's methods.
 *
 * @param self a GwpShip.
 * @return The hull spec for the current ship.
 */
GwpHullSpec * gwp_ship_get_hullspec (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  return (GwpHullSpec *)g_slist_nth_data (hullspec_list, gwp_ship_get_hull_type(self) - 1);
}

/**
 * Gets the correct engine specs for the ship.
 *
 * Search on the global engspec list the correct engine spec for the
 * current ship. This is a private method.
 *
 * @param self a GwpShip.
 * @return The engine spec for the current ship.
 */
GwpEngSpec * gwp_ship_get_engspec (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  return (GwpEngSpec *)g_slist_nth_data (engspec_list, gwp_ship_get_engines_type(self) - 1);
}

/**
 * Gets the beam weapons specs for the ship.
 *
 * Search on the global beamspec list the correct beam weapon spec for
 * the current ship. This is a private method.
 * 
 * @param self a GwpShip.
 * @return The beam weapon spec for the current ship or NULL if it
 * doesn't have.
 */
GwpBeamSpec * gwp_ship_get_beamspec (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  gint beams_type = gwp_ship_get_beams_type (self);

  if (gwp_ship_has_beam_weapons(self)) {
    return (GwpBeamSpec *)g_slist_nth_data (beamspec_list, beams_type - 1);
  } else {
    return NULL;
  }
}

/**
 * Gets the torpedoes weapons specs.
 *
 * Search on the global torpspec list the correct beam weapon spec for
 * the current ship. This is a private method.
 *
 * @param self a GwpShip.
 * @return The torpedoes weapon spec for the current ship or NULL if
 * it doesn't have.
 */
GwpTorpSpec * gwp_ship_get_torpspec (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  gint torps_type = gwp_ship_get_torps_type (self);

  if (gwp_ship_has_torp_weapons(self)) {
    return (GwpTorpSpec *)g_slist_nth_data (torpspec_list, torps_type - 1);
  } else {
    return NULL;
  }
}


/**********************/
/* High level methods */
/**********************/

/**
 * Checks if the current ship hash beam weapons.
 *
 * @param self a GwpShip
 * @return True if current ship has beam weapons.
 */
gboolean gwp_ship_has_beam_weapons (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  if (gwp_ship_get_beams(self) > 0 && gwp_ship_get_beams_type(self) > 0) {
    return TRUE;
  } else {
    return FALSE;
  }
} 

/**
 * Checks if the current ship has torpedo weapons.
 *
 * @param self a GwpShip.
 * @return True if the ship has torpedo tubes.
 */
gboolean gwp_ship_has_torp_weapons (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  if (gwp_ship_get_torps_launchers(self) > 0 &&
      gwp_ship_get_torps_type(self) > 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
 * Returns the enemy race's name for the current ship.
 *
 * This function checks if the current ship has a primary enemy, and
 * if that is the case, returns the race's name.
 *
 * @param self a GwpShip.
 * @return A string with the primary enemy race name.
 */
gchar * gwp_ship_get_primary_enemy_name (GwpShip *self)  /* TESTME */
{
  g_assert (GWP_IS_SHIP(self));

  GString *ret = NULL;

  if (gwp_ship_get_primary_enemy(self) == 0) {
    ret = g_string_new (_("No enemy"));
  } else {
    ret = g_string_new (race_get_name(gwp_ship_get_primary_enemy(self)));
  }

  return ret->str;
}

/**
 * Returns the current mission's name for the current ship.
 *
 * This function checks if the ship is doing the special mission, in
 * that case it looks up and return that.
 *
 * @param self a GwpShip.
 * @return A string with the mission's name.
 */
gchar * gwp_ship_get_mission_name (GwpShip *self) /* TESTME */
{
  g_assert (GWP_IS_SHIP(self));
  
  GString *ret = NULL;

  if (gwp_ship_get_mission(self) != MISSION_SPECIAL) {
    ret = g_string_new (mission_get_name(gwp_ship_get_mission(self)));
  } else {
    ret = g_string_new (mission_special_get_name(game_get_race(game_state)));
  }

  return ret->str;
}

/**
 * Returns the owner race's name for the current ship.
 *
 * @param self a GwpShip.
 * @return A string with the owner race name.
 */
gchar * gwp_ship_get_owner_name (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  GString *ret = g_string_new (race_get_name(gwp_ship_get_owner(self)));

  return ret->str;
}

/**
 * Returns the ship's hull name truncated.
 *
 * This is a mapping function to access the ship's hullspec data.
 *
 * @param self a GwpShip.
 * @param len the maximum name length accepted.
 * @return A string containing the hull name truncated if necessary.
 * @see gwp_hullspec_get_name_trunc
 */
gchar * gwp_ship_get_hull_name_trunc (GwpShip *self, gint len)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_hullspec_get_name_trunc (gwp_ship_get_hullspec(self), len);
}

/**
 * Returns the max cargo capacity of the current ship.
 *
 * @param self a GwpShip.
 * @return The ship's maximum cargo capacity.
 * @see gwp_hullspec_get_cargo
 */
gint gwp_ship_get_hull_cargo (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_hullspec_get_cargo (gwp_ship_get_hullspec(self));
}

/**
 * Returns the fuel tank capacity of the current ship.
 *
 * @param self a GwpShip.
 * @return The ship's maximum fuel capacity.
 * @see gwp_hullspec_get_fuel_tank
 */
gint gwp_ship_get_hull_fuel_tank (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_hullspec_get_fuel_tank (gwp_ship_get_hullspec(self));
}

/**
 * Returns the maximum crew capacity of the current ship.
 *
 * @param self a GwpShip.
 * @return The ship's maximum crew capacity.
 * @see gwp_hullspec_get_crew
 */
gint gwp_ship_get_hull_crew (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_hullspec_get_crew (gwp_ship_get_hullspec(self));
}

/**
 * Returns the number of engines the current ship uses.
 *
 * @param self a GwpShip.
 * @return The engine's number used.
 * @see gwp_hullspec_get_engines
 */
gint gwp_ship_get_hull_engines (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_hullspec_get_engines (gwp_ship_get_hullspec(self));
}

/**
 * Returns the max number of beam weapons the current ship can carry.
 *
 * @param self a GwpShip.
 * @return The maximum number of beam weapons.
 * @see gwp_hullspec_get_beam_weapons
 */
gint gwp_ship_get_hull_beam_weapons (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_hullspec_get_beam_weapons (gwp_ship_get_hullspec(self));
}

/**
 * Returns the max number of torpedo launchers the current ship can carry.
 *
 * @param self a GwpShip.
 * @return The maximum number of torp launchers.
 * @see gwp_hullspec_get_torp_launchers
 */
gint gwp_ship_get_hull_torp_launchers (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_hullspec_get_torp_launchers (gwp_ship_get_hullspec(self));
}

/**
 * Returns the max number of fighter bays the current ship can carry.
 *
 * @param self a GwpShip.
 * @return The maximum number of fighter bays.
 * @see gwp_hullspec_get_fighter_bays
 */
gint gwp_ship_get_hull_fighter_bays (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_hullspec_get_fighter_bays (gwp_ship_get_hullspec(self));
}

/**
 * Returns the picture number for the current ship's hull
 *
 * @param self a GwpShip.
 * @return The hull picture's number.
 * @see gwp_hullspec_get_picture
 */
gint gwp_ship_get_hull_picture (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_hullspec_get_picture (gwp_ship_get_hullspec(self));
}


/**
 * Returns the engine's name for the current ship.
 *
 * @param self a GwpShip.
 * @return The engine's name.
 * @see gwp_engspec_get_name
 */
gchar * gwp_ship_get_engine_name (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_engspec_get_name(gwp_ship_get_engspec(self));
}

/**
 * Returns the beam weapons' name for the current ship.
 *
 * @param self a GwpShip.
 * @return The beam's name.
 * @see gwp_beamspec_get_name
 */
gchar * gwp_ship_get_beams_name (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_beamspec_get_name(gwp_ship_get_beamspec(self));
}

/**
 * Returns the torpedoes' name for the current ship.
 *
 * @param self a GwpShip.
 * @return The torps' name.
 * @see gwp_torpspec_get_name
 */
gchar * gwp_ship_get_torps_name (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return gwp_torpspec_get_name(gwp_ship_get_torpspec(self));
}

/**
 * Calculates the ship's heading.
 *
 * Using the ship's own data calculates the heading in degress.
 *
 * @param self a GwpShip
 * @return The heading in degress, from 0 to 360.
 */
gint gwp_ship_calculate_heading (GwpShip *self)
{
  gdouble dx, dy;
  gdouble hyp;
  gdouble heading;
  gint h;

  g_assert (GWP_IS_SHIP(self));
  
  dx = gwp_ship_get_x_to_waypoint(self);
  dy = gwp_ship_get_y_to_waypoint(self);
  
  
  if(dx == 0.0 && dy == 0.0) {

    h = -1; /* -1 = ship not moving */

  } else {

    hyp = rint(sqrt((dx*dx) + (dy*dy)));
    
    if (hyp != 0) {
      heading = asin(dy/hyp);
      
      h = rint(heading * (360 / (2 * 3.14159)));
      
      if (dx >= 0) {
	h = 90 + (h * -1);
      } else {
	h = h + 270;
      }
      
    } else {
      h = 0;
    }
  }
  return h;
}

/**
 * Search a ship by its ID.
 *
 * @param list the ship hash table.
 * @param ship_id the ship's ID.
 * @return The GwpShip found, or NULL if not found.
 */
GwpShip * gwp_ship_get (GHashTable *list, gint ship_id) 
{
  return (GwpShip *) g_hash_table_lookup(list, (gconstpointer)ship_id);
}

/**
 * Checks if the current ship's coordinates are valid.
 *
 * @param self a GwpShip.
 * @return TRUE if coordinates are valid, FALSE otherwise.
 */
gboolean gwp_ship_valid_coords(GwpShip *self)
{
  g_assert(GWP_IS_SHIP(self));

  if(gwp_object_get_x_coord(GWP_OBJECT(self)) <= SHIP_VALID_X_MAX && 
     gwp_object_get_x_coord(GWP_OBJECT(self)) >= SHIP_VALID_X_MIN &&
     gwp_object_get_y_coord(GWP_OBJECT(self)) <= SHIP_VALID_Y_MAX && 
     gwp_object_get_y_coord(GWP_OBJECT(self)) >= SHIP_VALID_Y_MIN) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
 * Checks if current ship is owned by player.
 *
 * @param self a GwpShip.
 * @return TRUE if ship's owned by player, FALSE otherwise.
 */
gboolean gwp_ship_is_mine(GwpShip *self)
{
  g_assert(GWP_IS_SHIP(self));

  if(gwp_ship_get_owner(self) == game_get_race(game_state)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
 * Returns waypoint coordinates of current ship.
 *
 * @param self a GwpShip.
 * @param wp_x a reference to assign waypoint's x coordinate.
 * @param wp_y a reference to assign waypoint's y coordinate.
 */
void gwp_ship_get_waypoint(GwpShip *self, gint *wp_x, gint *wp_y)
{
  g_assert(GWP_IS_SHIP(self) && wp_x != NULL && wp_y != NULL);

  *wp_x = gwp_object_get_x_coord(GWP_OBJECT(self)) + 
    gwp_ship_get_x_to_waypoint (self);
  *wp_y = gwp_object_get_y_coord(GWP_OBJECT(self)) + 
    gwp_ship_get_y_to_waypoint (self);
}

/**
 * Calculates the distance left to reach the waypoint.
 *
 * @param self a GwpShip
 * @return The distance in light-years.
 */
gdouble gwp_ship_calculate_waypoint_distance (GwpShip *self)
{
  g_assert(GWP_IS_SHIP(self));

  gdouble x, y;

  x = gwp_ship_get_x_to_waypoint(self);
  y = gwp_ship_get_y_to_waypoint(self);

  return sqrt((x*x) + (y*y));  
}

/**
 * Calculate the Estimated Time of Arrival.
 *
 * @param self a GwpShip.
 * @return The number of turns (months) needed to arrive to current waypoint.
 */
gint gwp_ship_calculate_eta (GwpShip *self)
{
  g_assert(GWP_IS_SHIP(self));

  gdouble dist = gwp_ship_calculate_waypoint_distance (self);
  gdouble speed = gwp_flying_object_get_speed (GWP_FLYING_OBJECT(self));

  gint eta = 0;
  if (dist > 0.0) {
    eta = ceil(dist / (speed*speed));
  }
  
  return eta;
}

/**
 * Calculate the fuel usage.
 *
 * Based on the current ship's information, it calculates the fuel
 * needed to arrive to destination depending on the engines type,
 * speed, total mass, and cargo to be loaded, unloaded or
 * transfered. This function is a wrapper to the corresponding
 * function on GwpEngSpec.
 *
 * @see gwp_engspec_get_fuel_usage_full
 * @param self a GwpShip.
 * @return The number of KT of neutronium needed to travel.
 */
gint gwp_ship_calculate_fuel_usage (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  /* Calculate only if ship is moving */
  if (gwp_flying_object_get_speed(GWP_FLYING_OBJECT(self)) > 0 && 
      gwp_ship_calculate_waypoint_distance(self) > 0.0) {

    /* Get this ship's engines specs */
    GwpEngSpec *eng = gwp_ship_get_engspec (self);
    g_assert (GWP_IS_ENGSPEC(eng));
    
    return gwp_engspec_get_fuel_usage_full (eng, 
					    gwp_ship_calculate_waypoint_distance(self),
					    gwp_flying_object_get_speed(GWP_FLYING_OBJECT(self)),
					    gwp_ship_calculate_mass(self));
  } else {
    return 0;
  }
}

/**
 * Calculates total cargo mass.
 *
 * @param self a GwpShip
 * @return The total cargo mass in kT.
 */
gint gwp_ship_calculate_cargo (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  return gwp_ship_get_colonists (self) + gwp_ship_get_tritanium (self) + 
    gwp_ship_get_duranium (self) + gwp_ship_get_molybdenum (self) + 
    gwp_ship_get_supplies (self) + gwp_ship_get_torps(self) +
    gwp_ship_get_fighters(self);
}

/**
 * Calculates total mass based on cargo, equipment, etc.
 *
 * This method take in account all items that the ship has on board,
 * including the hull itself, to calculate the amount of load that the
 * engines have to cope with. It also check if the ship is unloading
 * cargo or transfering it to another ship.
 *
 * @param self a GwpShip.
 * @return The total ship's mass in KT.
 */
gint gwp_ship_calculate_mass (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  GwpBeamSpec *beam = gwp_ship_get_beamspec (self);
  GwpTorpSpec *torp = gwp_ship_get_torpspec (self);
  GwpHullSpec *hull = gwp_ship_get_hullspec (self);

  gint total_mass = 0;

  total_mass += gwp_ship_calculate_cargo (self) + 
    gwp_ship_get_neutronium (self);
  
  /* Planet unload actions */
  if (gwp_ship_get_unload_planet_id(self) != 0) {
    total_mass -= gwp_ship_get_unload_colonists (self) +
      gwp_ship_get_unload_neutronium (self) + 
      gwp_ship_get_unload_tritanium (self) +
      gwp_ship_get_unload_duranium (self) + 
      gwp_ship_get_unload_molybdenum (self) +
      gwp_ship_get_unload_supplies (self);
  }

  /* Ship transfer actions */
  if (gwp_ship_get_transfer_ship_id(self) != 0) {
    total_mass -= gwp_ship_get_transfer_colonists (self) +
      gwp_ship_get_transfer_neutronium (self) +
      gwp_ship_get_transfer_tritanium (self) +
      gwp_ship_get_transfer_duranium (self) +
      gwp_ship_get_transfer_molybdenum (self) +
      gwp_ship_get_transfer_supplies (self);
  }
  
  total_mass += gwp_hullspec_get_mass (hull);
  
  if (GWP_IS_TORPSPEC(torp)) {
    total_mass += gwp_torpspec_get_mass (torp) * 
      gwp_ship_get_torps_launchers (self);
    total_mass += gwp_ship_get_torps (self);

    /* If ship is laying mines, substract the torps used */
    total_mass -= gwp_ship_calculate_lay_mines_torps (self);
  }
  
  
  if (GWP_IS_BEAMSPEC(beam)) {
    total_mass += gwp_beamspec_get_mass (beam) * gwp_ship_get_beams (self);
  }

  return total_mass;
}

/**
 * Calculates the number of torpedoes to be used by lay mines mission.
 */
gint gwp_ship_calculate_lay_mines_torps (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));

  gchar *fc = gwp_ship_get_fcode (self);
  gint torps = gwp_ship_get_torps (self);
  gint torps_burned = 0;
  
  if (gwp_ship_get_mission(self) == MISSION_LAY_MINES &&
      gwp_ship_get_torps (self) > 0) {
    
    if (fc == "md1") {
      torps_burned = (torps >= 10)?10:torps;
    } else if (fc == "md2") {
      torps_burned = (torps >= 20)?20:torps;
    } else if (fc == "md3") {
      torps_burned = (torps >= 30)?30:torps;
    } else if (fc == "md4") {
      torps_burned = (torps >= 40)?40:torps;
    } else if (fc == "md5") {
      torps_burned = (torps >= 50)?50:torps;
    } else if (fc == "md6") {
      torps_burned = (torps >= 60)?60:torps;
    } else if (fc == "md7") {
      torps_burned = (torps >= 70)?70:torps;
    } else if (fc == "md8") {
      torps_burned = (torps >= 80)?80:torps;
    } else if (fc == "md9") {
      torps_burned = (torps >= 90)?90:torps;
    } else if (fc == "md0") {
      torps_burned = (torps >= 100)?100:torps;
    } else if (fc == "mdq") {
      torps_burned = torps / 0.25;
    } else if (fc == "mdh") {
      torps_burned = torps / 0.5;
    } else {
      torps_burned = torps;
    }
  }
  
  return torps_burned;
}

/****************************/
/* Get/Set (boring) methods */
/****************************/

/**
 * Checks if the current ship is owned by the player.
 *
 * @return TRUE if it's owned by the player.
 */
gboolean gwp_ship_is_known (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->known;
}

void gwp_ship_set_known (GwpShip *self, gboolean is_known)
{
  g_assert (GWP_IS_SHIP(self));
  self->priv->known = is_known;
}

gint gwp_ship_get_owner (GwpShip *self)
{
  g_assert(GWP_IS_SHIP(self));
  return self->priv->owner;
}

void gwp_ship_set_owner (GwpShip *self, gint owner)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (owner >= 0 && owner <= 12);
  self->priv->owner = owner;
}

gint gwp_ship_get_mass_if_unknown (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->mass_if_unknown;
}

void gwp_ship_set_mass_if_unknown (GwpShip *self, gint mass)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (mass >= 0);
  self->priv->mass_if_unknown = mass;
}

gchar *gwp_ship_get_fcode (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  GString *ret = g_string_new (self->priv->fcode->str);

  return ret->str;
}

void gwp_ship_set_fcode (GwpShip *self, gchar *fcode)
{
  g_assert (GWP_IS_SHIP(self));

  if (strlen(fcode) <= 3) {
    g_string_free (self->priv->fcode, TRUE);
    self->priv->fcode = g_string_new (fcode);
  }
}

gint16 gwp_ship_get_x_to_waypoint (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->x_to_waypoint;
}

void gwp_ship_set_x_to_waypoint (GwpShip *self, gint16 xw)
{
  g_assert (GWP_IS_SHIP(self));
  self->priv->x_to_waypoint = xw;
}

gint16 gwp_ship_get_y_to_waypoint (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->y_to_waypoint;
}

void gwp_ship_set_y_to_waypoint (GwpShip *self, gint16 yw)
{
  g_assert (GWP_IS_SHIP(self));
  self->priv->y_to_waypoint = yw;
}

gint16 gwp_ship_get_engines_type (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->engines_type;
}

void gwp_ship_set_engines_type (GwpShip *self, gint16 et)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (et >= 1 && et <= 9);
  self->priv->engines_type = et;
}

gint16 gwp_ship_get_hull_type (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->hull_type;
}

void gwp_ship_set_hull_type (GwpShip *self, gint16 ht)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (ht >= 1 && ht <= 105);
  self->priv->hull_type = ht;
}

gint16 gwp_ship_get_beams_type (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->beams_type;
}

void gwp_ship_set_beams_type (GwpShip *self, gint16 bt)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (bt >= 0 && bt <= 10);
  self->priv->beams_type = bt;
}

gint16 gwp_ship_get_beams (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->beams;
}

void gwp_ship_set_beams (GwpShip *self, gint16 beams)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (beams >= 0);
  self->priv->beams = beams;
}

gint16 gwp_ship_get_fighter_bays (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->fighter_bays;
}

void gwp_ship_set_fighter_bays (GwpShip *self, gint16 f_bays)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (f_bays >= 0);
  self->priv->fighter_bays = f_bays;
}

gint16 gwp_ship_get_torps_type (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->torps_type;
}

void gwp_ship_set_torps_type (GwpShip *self, gint16 tt)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (tt >= 0 && tt <= 10);
  self->priv->torps_type = tt;
}

gint16 gwp_ship_get_torps (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->torps_nr;
}

void gwp_ship_set_torps (GwpShip *self, gint16 torps)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (torps >= 0);
  self->priv->torps_nr = torps;
}

gint16 gwp_ship_get_fighters (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->fighters_nr;
}

void gwp_ship_set_fighters (GwpShip *self, gint16 fighters)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (fighters >= 0);
  self->priv->fighters_nr = fighters;
}

gint16 gwp_ship_get_torps_launchers (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->torps_launchers;
}

void gwp_ship_set_torps_launchers (GwpShip *self, gint16 tl)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (tl >= 0);
  self->priv->torps_launchers = tl;
}

gint16 gwp_ship_get_mission (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->mission;
}

void gwp_ship_set_mission (GwpShip *self, gint16 mission)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (mission >= 0 && mission <= 37); /* FIXME: check for Thost or Phost! */
  self->priv->mission = mission;
}

gint16 gwp_ship_get_primary_enemy (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->primary_enemy;
}

void gwp_ship_set_primary_enemy (GwpShip *self, gint16 pe)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (pe >= 0 && pe <= 11);
  self->priv->primary_enemy = pe;
}

gint16 gwp_ship_get_tow_ship_id (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->tow_ship_id;
}

void gwp_ship_set_tow_ship_id (GwpShip *self, gint16 id)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (id >= 0 && id <= 500); /* FIXME: check for Host999! */
  self->priv->tow_ship_id = id;
}

gint16 gwp_ship_get_damage (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->damage;
}

void gwp_ship_set_damage (GwpShip *self, gint16 dmg)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (dmg >= 0 && dmg <= 149); /* FIXME: check for lizard ships! */
  self->priv->damage = dmg;
}

gint16 gwp_ship_get_crew (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->crew;
}

void gwp_ship_set_crew (GwpShip *self, gint16 crew)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (crew >= 0); /* FIXME: check for crew capacity! */
  self->priv->crew = crew;
}

gint16 gwp_ship_get_colonists (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->colonists;
}

void gwp_ship_set_colonists (GwpShip *self, gint16 col)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (col >= 0); /* FIXME: check cargo capacity! */
  self->priv->colonists = col;
}

gint16 gwp_ship_get_neutronium (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->neutronium;
}

void gwp_ship_set_neutronium (GwpShip *self, gint16 neu)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (neu >= 0); /* FIXME: check cargo capacity! */
  self->priv->neutronium = neu;
}

gint16 gwp_ship_get_tritanium (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->tritanium;
}

void gwp_ship_set_tritanium (GwpShip *self, gint16 tri)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (tri >= 0); /* FIXME: check cargo capacity! */
  self->priv->tritanium = tri;
}

gint16 gwp_ship_get_duranium (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->duranium;
}

void gwp_ship_set_duranium (GwpShip *self, gint16 dur)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (dur >= 0); /* FIXME: check cargo capacity! */
  self->priv->duranium = dur;
}

gint16 gwp_ship_get_molybdenum (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->molybdenum;
}

void gwp_ship_set_molybdenum (GwpShip *self, gint16 mol)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (mol >= 0); /* FIXME: check cargo capacity */
  self->priv->molybdenum = mol;
}

gint16 gwp_ship_get_supplies (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->supplies;
}

void gwp_ship_set_supplies (GwpShip *self, gint16 sup)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (sup >= 0); /* FIXME: check cargo capacity */
  self->priv->supplies = sup;
}

/* Unload cargo to planet */
gint16 gwp_ship_get_unload_neutronium (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->unload_neutronium;
}

void gwp_ship_set_unload_neutronium (GwpShip *self, gint16 neu)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (neu >= 0);
  self->priv->unload_neutronium = neu;
}

gint16 gwp_ship_get_unload_tritanium (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->unload_tritanium;
}

void gwp_ship_set_unload_tritanium (GwpShip *self, gint16 tri)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (tri >= 0);
  self->priv->unload_tritanium = tri;
}

gint16 gwp_ship_get_unload_duranium (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->unload_duranium;
}

void gwp_ship_set_unload_duranium (GwpShip *self, gint16 dur)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (dur >= 0);
  self->priv->unload_duranium = dur;
}

gint16 gwp_ship_get_unload_molybdenum (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->unload_molybdenum;
}

void gwp_ship_set_unload_molybdenum (GwpShip *self, gint16 mol)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (mol >= 0);
  self->priv->unload_molybdenum = mol;
}

gint16 gwp_ship_get_unload_supplies (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->unload_supplies;
}

void gwp_ship_set_unload_supplies (GwpShip *self, gint16 sup)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (sup >= 0);
  self->priv->unload_supplies = sup;
}

void gwp_ship_set_unload_colonists (GwpShip *self, gint16 col)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (col >= 0);
  self->priv->unload_colonists = col;
}

gint16 gwp_ship_get_unload_colonists (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->unload_colonists;
}

gint16 gwp_ship_get_unload_planet_id (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->unload_planet_id;
}

void gwp_ship_set_unload_planet_id (GwpShip *self, gint16 pid)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (pid >= 0 && pid <= 500); /* FIXME: if not 0, check for planet to be on the same place as ship */
  self->priv->unload_planet_id = pid;
}

/* Transfer cargo to ship */
gint16 gwp_ship_get_transfer_neutronium (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->transfer_neutronium;
}

void gwp_ship_set_transfer_neutronium (GwpShip *self, gint16 neu)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (neu >= 0);
  self->priv->transfer_neutronium = neu;
}

gint16 gwp_ship_get_transfer_tritanium (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->transfer_tritanium;
}

void gwp_ship_set_transfer_tritanium (GwpShip *self, gint16 tri)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (tri >= 0);
  self->priv->transfer_tritanium = tri;
}

gint16 gwp_ship_get_transfer_duranium (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->transfer_duranium;
}

void gwp_ship_set_transfer_duranium (GwpShip *self, gint16 dur)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (dur >= 0);
  self->priv->transfer_duranium = dur;
}

gint16 gwp_ship_get_transfer_molybdenum (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->molybdenum;
}

void gwp_ship_set_transfer_molybdenum (GwpShip *self, gint16 mol)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (mol >= 0);
  self->priv->transfer_molybdenum = mol;
}

gint16 gwp_ship_get_transfer_supplies (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->transfer_supplies;
}

void gwp_ship_set_transfer_colonists (GwpShip *self, gint16 col)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (col >= 0);
  self->priv->transfer_colonists = col;
}

gint16 gwp_ship_get_transfer_colonists (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->transfer_colonists;
}

void gwp_ship_set_transfer_supplies (GwpShip *self, gint16 sup)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (sup >= 0);
  self->priv->transfer_supplies = sup;
}

gint16 gwp_ship_get_transfer_ship_id (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->transfer_ship_id;
}

void gwp_ship_set_transfer_ship_id (GwpShip *self, gint16 sid)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (sid >= 0 && sid <= 500); /* FIXME: check for Host999 and if not 0, the ship is on the same spot */
  self->priv->transfer_ship_id = sid;
}

gint16 gwp_ship_get_intercept_ship_id (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->intercept_ship_id;
}

void gwp_ship_set_intercept_ship_id (GwpShip *self, gint16 sid)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (sid >= 0 && sid <= 500); /* FIXME: check for Host999 and if not 0, the ship should be on the same spot */
  self->priv->intercept_ship_id = sid;
}

gint16 gwp_ship_get_megacredits (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->megacredits;
}

void gwp_ship_set_megacredits (GwpShip *self, gint16 m)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (m >= 0 && m <= 10000);
  self->priv->megacredits = m;
}
