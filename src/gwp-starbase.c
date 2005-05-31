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

/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.12  2005/05/31 13:17:39  ldipenti
    Feature: Added CVS metadata on source files

*/

#include <string.h>
 
#include "gwp-planet.h"
#include "gwp-starbase.h"

/**
 * Private data structure for the GwpStarbase type.
 *
 * This data should be accesed directly only by the low-level get/set
 * object's methods, the high-level ones shouldn't touch them.
 */
struct _GwpStarbasePrivate {
  gboolean dispose_has_run; /**< Internal object's variable. */
  /* Private attributes */
  GwpPlanet *planet;     /**< Planet where this starbase is on. */
  gint16 defense;        /**< Starbase's defense posts. Range 0..200 */
  gint16 damage;         /**< Starbase's damage level. Range 0..100 */
  gint16 engines_tech;   /**< Engines technology level. Range 1..10 */
  gint16 hulls_tech;     /**< Hulls technology level. Range 1..10 */
  gint16 beams_tech;     /**< Beam weapons technology level. Range 1..10 */
  gint16 torps_tech;     /**< Torpedo weapongs technology level. Range 1..10 */
	
  gint16 storage_engines[9]; /**< Engines in storage. */
  gint16 storage_hulls[20]; /**< Hulls in storage. */
  gint16 storage_beams[10]; /**< Beam weapons in storage. */
  gint16 storage_torp_launchers[10]; /**< Torpedo weapons in storage. */
  gint16 storage_torps[10]; /**< Torpedoes in storage. */
	
  gint16 fighters; /**< Fighters in storage. Range 0..60 */
	
  gint16 id_ship; /**< Ship to be recycled or repaired. */

  /**
   * Ship actions.
   *   - 0 - Nothing
   *   - 1 - Fix
   *   - 2 - Recycle
   */
  gint16 ship_action;
	
  /**
   * Mission type.
   *    - 1 - Refuel
   *	- 2 - Max Defense
   *    - 3 - Load torps onto ships
   *	- 4 - Unload freighters
   *	- 5 - Repair base
   *	- 6 - Force a surrender 
   */
  gint16 mission; 
	
  /* -- Spaceship Build -- */
  gint16 build_ship_type; /**< Type of ship to build. Range 0..20, 0 =
			     no build. */ 
  gint16 build_engine_type; /**< Type of engine to build. Range 0..10 */
  gint16 build_beam_type; /**< Type of beams to build. Range 0..10 */
  gint16 build_beam_count; /**< Number of beams to build. */
  gint16 build_torp_type; /**< Type of torpedo tubes to build. Range 0..10 */
  gint16 build_torp_count; /**< Number of torp tubes to build. */
	
  /* Fighter count (?) this should always be zero */
  /* gint16 fighter_count; */
};

/*
 * forward definitions.
 */
static void gwp_starbase_init (GTypeInstance * instance, gpointer g_class);
static void gwp_starbase_class_init (GwpStarbaseClass *klass);

GType gwp_starbase_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpStarbaseClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_starbase_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpStarbase),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_starbase_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpStarbase", 
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_starbase_init (GTypeInstance *instance,
			       gpointer       g_class)
{
  int i;
  GwpStarbase *self = (GwpStarbase *)instance;
  self->priv = g_new0 (GwpStarbasePrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->planet = NULL;
  self->priv->defense = 0;
  self->priv->damage = 0;
  self->priv->engines_tech = 1;
  self->priv->hulls_tech = 1;
  self->priv->beams_tech = 1;
  self->priv->torps_tech = 1;
  for (i = 0; i < 9; i++) {
    self->priv->storage_engines[i] = 0;
  }
  for (i = 0; i < 20; i++) {
    self->priv->storage_hulls[i] = 0;
  }
  for (i = 0; i < 10; i++) {
    self->priv->storage_beams[i] = 0;
  }
  for (i = 0; i < 10; i++) {
    self->priv->storage_torp_launchers[i] = 0;
  }
  for (i = 0; i < 10; i++) {
    self->priv->storage_torps[i] = 0;
  }
  self->priv->fighters = 0;
  self->priv->id_ship = 0;
  self->priv->ship_action = 0;
  self->priv->mission = 1;
  self->priv->build_ship_type = 0;
  self->priv->build_engine_type = 0;
  self->priv->build_beam_type = 0;
  self->priv->build_beam_count = 0;
  self->priv->build_torp_type = 0;
  self->priv->build_torp_count = 0;
}

static void gwp_starbase_dispose (GwpStarbase *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  /* g_object_unref (self->priv->planet); */
}

static void gwp_starbase_finalize (GwpStarbase *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_starbase_class_init (GwpStarbaseClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  /* Register destructor methods */
  gobject_class->dispose = (void *) gwp_starbase_dispose;
  gobject_class->finalize = (void *) gwp_starbase_finalize;
}

/* 
 * Public method implementations.
 */
GwpStarbase * gwp_starbase_new (void)
{
  return g_object_new (gwp_starbase_get_type (), NULL);
}

/**********************/
/* High level methods */
/**********************/

/* Returns a copy of the original object */
GwpStarbase * gwp_starbase_copy (GwpStarbase *self)
{
  GwpStarbase *sb_copy;

  g_assert (GWP_IS_STARBASE(self));

  sb_copy = gwp_starbase_new();
  g_free(sb_copy->priv);
  sb_copy->priv = g_malloc (sizeof(GwpStarbasePrivate));
  sb_copy->priv = memcpy (sb_copy->priv, self->priv, sizeof(GwpStarbasePrivate));
  /* FIXME: should be the planet referencee be copied? */
  return sb_copy;
}

gint16 gwp_starbase_get_id (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return gwp_object_get_id (GWP_OBJECT(gwp_starbase_get_planet (self)));
}

/*******************/
/* get/set methods */
/*******************/
gint16 gwp_starbase_get_defense (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->defense;
}

void gwp_starbase_set_defense (GwpStarbase *self, gint16 def)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (def >= 0 && def <= 200);
  self->priv->defense = def;
}

gint16 gwp_starbase_get_damage (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->damage;
}

void gwp_starbase_set_damage (GwpStarbase *self, gint dam)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (dam >= 0 && dam <= 100);
  self->priv->damage = dam;
}

gint16 gwp_starbase_get_engines_tech (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->engines_tech;
}

void gwp_starbase_set_engines_tech (GwpStarbase *self, gint16 tech)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (tech >= 0 && tech <= 10);
  self->priv->engines_tech = tech;
}

gint16 gwp_starbase_get_hulls_tech (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->hulls_tech;
}

void gwp_starbase_set_hulls_tech (GwpStarbase *self, gint16 tech)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (tech >= 0 && tech <= 10);
  self->priv->hulls_tech = tech;
}

gint16 gwp_starbase_get_beams_tech (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->beams_tech;
}

void gwp_starbase_set_beams_tech (GwpStarbase *self, gint16 tech)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (tech >= 0 && tech <= 10);
  self->priv->beams_tech = tech;
}

gint16 gwp_starbase_get_torps_tech (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->torps_tech;
}

void gwp_starbase_set_torps_tech (GwpStarbase *self, gint16 tech)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (tech >= 0 && tech <= 10);
  self->priv->torps_tech = tech;
}

gint16 gwp_starbase_get_storage_engines (GwpStarbase *self, gint storage_nr)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 8);
  return self->priv->storage_engines[storage_nr];
}

void gwp_starbase_set_storage_engines (GwpStarbase *self, 
				       gint storage_nr, gint16 engine)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 8);
  g_assert (engine >= 0 && engine <= 10000);
  self->priv->storage_engines[storage_nr] = engine;
}

gint16 gwp_starbase_get_storage_hulls (GwpStarbase *self, gint storage_nr)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 19);
  return self->priv->storage_hulls[storage_nr];
}

void gwp_starbase_set_storage_hulls (GwpStarbase *self, 
				     gint storage_nr, gint16 hull)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 19); /* FIXME: check for tech level */
  g_assert (hull >= 0 && hull <= 10000);
  self->priv->storage_hulls[storage_nr] = hull;
}

gint16 gwp_starbase_get_storage_beams (GwpStarbase *self, gint storage_nr)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 9);
  return self->priv->storage_beams[storage_nr];
}

void gwp_starbase_set_storage_beams (GwpStarbase *self, 
				     gint storage_nr, gint16 beam)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 9); /* FIXME: check for tech level */
  g_assert (beam >= 0 && beam <= 10000); 
  self->priv->storage_beams[storage_nr] = beam;
}

gint16 gwp_starbase_get_storage_torp_launchers (GwpStarbase *self, 
						gint storage_nr)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 9);
  return self->priv->storage_torp_launchers[storage_nr];
}

void gwp_starbase_set_storage_torp_launchers (GwpStarbase *self, 
					      gint storage_nr, 
					      gint16 t_launcher)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 9); /* FIXME: check for tech level */
  g_assert (t_launcher >= 0 && t_launcher <= 10000);
  self->priv->storage_torp_launchers[storage_nr] = t_launcher;
}

gint16 gwp_starbase_get_storage_torps (GwpStarbase *self, gint storage_nr)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 9);
  return self->priv->storage_torps[storage_nr];
}

void gwp_starbase_set_storage_torps (GwpStarbase *self, 
				     gint storage_nr, gint16 torp)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (storage_nr >= 0 && storage_nr <= 9); /* FIXME: check for tech level */
  g_assert (torp >= 0 && torp <= 10000);
  self->priv->storage_torps[storage_nr] = torp;
}

gint16 gwp_starbase_get_fighters (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->fighters;
}

void gwp_starbase_set_fighters (GwpStarbase *self, gint16 f)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (f >= 0 && f <= 60);
  self->priv->fighters = f;
}

gint16 gwp_starbase_get_id_ship (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->id_ship;
}

void gwp_starbase_set_id_ship (GwpStarbase *self, gint16 id)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (id >= 0 && id <= 500); /* FIXME: check for Host999! */
  self->priv->id_ship = id;
}

gint16 gwp_starbase_get_ship_action (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->ship_action;
}

void gwp_starbase_set_ship_action (GwpStarbase *self, gint16 action)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (action >= 0 && action <= 2);
  self->priv->ship_action = action;
}

gint16 gwp_starbase_get_mission (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->mission;
}

void gwp_starbase_set_mission (GwpStarbase *self, gint16 mission)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (mission >= 0 && mission <= 6);
  self->priv->mission = mission;
}

gint16 gwp_starbase_get_build_ship_type (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->build_ship_type;
}

void gwp_starbase_set_build_ship_type (GwpStarbase *self, gint16 type)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (type >= 0 && type <= 20); /* FIXME: check for tech level */
  self->priv->build_ship_type = type;
}

gint16 gwp_starbase_get_build_engine_type (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->build_engine_type;
}

void gwp_starbase_set_build_engine_type (GwpStarbase *self, gint16 type)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (type >= 0 && type <= 10); /* FIXME: check for tech level */
  self->priv->build_engine_type = type;
}

gint16 gwp_starbase_get_build_beam_type (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->build_beam_type;
}

void gwp_starbase_set_build_beam_type (GwpStarbase *self, gint16 type)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (type >= 0 && type <= 10); /* FIXME: check for tech level */
  self->priv->build_beam_type = type;
}

gint16 gwp_starbase_get_build_beam_count (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->build_beam_count;
}

void gwp_starbase_set_build_beam_count (GwpStarbase *self, gint16 count)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (count >= 0);
  self->priv->build_beam_count = count;
}

gint16 gwp_starbase_get_build_torp_type (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->build_torp_type;
}

void gwp_starbase_set_build_torp_type (GwpStarbase *self, gint16 type)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (type >= 0 && type <= 10); /* FIXME: check for tech level */
  self->priv->build_torp_type = type;
}

gint16 gwp_starbase_get_build_torp_count (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  return self->priv->build_torp_count;
}

void gwp_starbase_set_build_torp_count (GwpStarbase *self, gint16 count)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (count >= 0); /* FIXME: check for limits... */
  self->priv->build_torp_count = count;
}

gint16 gwp_starbase_get_fighter_count (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  /* This field should always be zero */
  return 0;
}

void gwp_starbase_set_fighter_count (GwpStarbase *self, gint16 count)
{
  g_assert (GWP_IS_STARBASE(self));
  /* This field should always be zero */
  /* self->priv->fighter_count = 0; */
}

GwpPlanet * gwp_starbase_get_planet (GwpStarbase *self)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (GWP_IS_PLANET(self->priv->planet));
  return self->priv->planet;
}

void gwp_starbase_set_planet (GwpStarbase *self, GwpPlanet *p)
{
  g_assert (GWP_IS_STARBASE(self));
  g_assert (GWP_IS_PLANET(p));
  self->priv->planet = p;
}
