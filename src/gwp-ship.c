/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002, 2003 Lucas Di Pentima <lucas@lunix.com.ar>
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

#include "gwp-flying-object.h"
#include "gwp-ship.h"

struct _GwpShipPrivate {
  gboolean dispose_has_run;

  gboolean known;
  gint owner; /* range 1..11 */
  GString *fcode; /* max 3 chars */
  
  gint16 x_to_waypoint; /* distance to x, y waypoints */
  gint16 y_to_waypoint; /* range -3000..3000          */

  gint16 engines_type;        /* range 1..9, index into ENGSPEC.DAT */
  gint16 hull_type;           /* range 1..105, index into HULLSPEC.DAT */
  gint16 beams_type;          /* range 1..10 (0 = none), BEAMSPEC.DAT */
  gint16 beams;               /* Number of beam weapons */
  gint16 fighter_bays;        /* Number of fighter bays */
  gint16 torps_type;          /* range 1..10 (0 = none). TORPSPEC.DAT */
  gint16 torps_nr;            /* Number of torpedoes */
  gint16 fighters_nr;         /* Number of fighters */
  gint16 torps_launchers;     /* Number of torps launchers */

  /*
   * Standard Missions:
   * 0   none
   * 1   Explore
   * 2   Mine sweep
   * 3   Lay mines
   * 4   Kill
   * 5   Sensor sweep
   * 6   Colonize, Land & Disassemble
   * 7   Tow, tow arg = ship id (must be in the same spot)
   * 8   Intercept, Intercept arg = ship id (must be visible and within 200 ly)
   * 9   Race specific missions
   *       1 = Federation                  Super Refit
   *       2 = Lizard                      Hissssss!
   *       3 = Bird Man                    Super Spy
   *       4 = Fascist                     Pillage Planet
   *       5 = Privateer                   Rob Ship
   *       6 = Cyborg                      Self Repair
   *       7 = Crystal                     Lay Web Mines
   *       8 = Evil Empire                 Dark Sense
   *       9 = Robots                      Build Fighters
   *      10 = Rebel                       Rebel Ground Attack
   *      11 = Colonies                    Build Fighters
   *
   * 10  Cloak. Only possible on appropiate ships
   * 11  Beam up Neutronium
   * 12  Beam up Duranium
   * 13  Beam up Tritanium
   * 14  Beam uo Molybdenum
   * 15  Beam up Supplies
   * ...
   * ... 37 (check filefmt for PHost extended missions!
   */
  gint16 mission;

  gint16 primary_enemy; /* 0 or race id 1..11 */

  /* Ship to tow (or first mission argument) */
  gint16 tow_ship_id;

  gint16 damage;                /* % - range 1..149 */
  gint16 crew;
  gint16 colonists;             /* Clans (100 people each) */
  
  /* Cargo */
  gint16 neutronium;
  gint16 tritanium;
  gint16 duranium;
  gint16 molybdenum;
  gint16 supplies;
	
  /* Unload cargo to planet */
  gint16 unload_neutronium;
  gint16 unload_tritanium;
  gint16 unload_duranium;
  gint16 unload_molybdenum;
  gint16 unload_colonists;
  gint16 unload_supplies;
  gint16 unload_planet_id;      /* 0 = Jettison */
	
  /* Transfer to enemy ship */
  gint16 transfer_neutronium;
  gint16 transfer_tritanium;
  gint16 transfer_duranium;
  gint16 transfer_molybdenum;
  gint16 transfer_colonists;
  gint16 transfer_supplies;
  gint16 transfer_ship_id;      /* 0 or ship id */
	
  /* Intercept Mission arg (or second mission arg) */
  gint16 intercept_ship_id;     /* Valid ship ID or zero. */
	
  gint16 megacredits;           /* range 0..10000 */
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
    type = g_type_register_static (GWP_FLYING_OBJECT_TYPE,
				   "GwpShip",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_ship_init (GTypeInstance  *instance,
			   gpointer        g_class)
{
  GwpShip *self = (GwpShip *)instance;
  self->priv = g_new0 (GwpShipPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->owner = 0;
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

  g_message("GwpShip init");
}

static void gwp_ship_dispose (GwpShip *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

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
  g_message("GwpShip finalize");
  g_free (self->priv);
}

static void gwp_ship_class_init (GwpShipClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  g_message("GwpShipClass init");
  /*
   * Register destructor methods.
   */
  gobject_class->dispose = gwp_ship_dispose;
  gobject_class->finalize = gwp_ship_finalize;
}

/*
 * Public method implementations.
 */
GwpShip * gwp_ship_new (void)
{
  return g_object_new (gwp_ship_get_type(), NULL);
}

/* Get/Set (boring) methods */
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

GString *gwp_ship_get_fcode (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return g_string_new (self->priv->fcode->str);
}

void gwp_ship_set_fcode (GwpShip *self, GString *fcode)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (fcode->len <= 3);
  g_string_free (self->priv->fcode, TRUE);
  self->priv->fcode = g_string_new (fcode->str);
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
  g_assert (neu >= 0 && neu <= self->priv->neutronium);
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
  g_assert (tri >= 0 && tri <= self->priv->tritanium);
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
  g_assert (dur >= 0 && dur <= self->priv->duranium);
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
  g_assert (mol >= 0 && mol <= self->priv->molybdenum);
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
  g_assert (sup >= 0 && sup <= self->priv->supplies);
  self->priv->unload_supplies = sup;
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
  g_assert (neu >= 0 && neu <= self->priv->neutronium);
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
  g_assert (tri >= 0 && tri <= self->priv->tritanium);
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
  g_assert (dur >= 0 && dur <= self->priv->duranium);
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
  g_assert (mol >= 0 && mol <= self->priv->molybdenum);
  self->priv->transfer_molybdenum = mol;
}

gint16 gwp_ship_get_transfer_supplies (GwpShip *self)
{
  g_assert (GWP_IS_SHIP(self));
  return self->priv->transfer_supplies;
}

void gwp_ship_set_transfer_supplies (GwpShip *self, gint16 sup)
{
  g_assert (GWP_IS_SHIP(self));
  g_assert (sup >= 0 && sup <= self->priv->supplies);
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