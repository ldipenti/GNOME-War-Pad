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
#include <string.h>

#include "gwp-starbase.h"
#include "race.h"
#include "global.h"
#include "gwp-game-state.h"
#include "gwp-planet.h"
#include "gwp-beamspec.h"

gint gwp_planet_mineral_extraction_rate(GwpPlanet *self, gint density, gint mineral);
gint gwp_planet_mineral_turns_left(gint mineral, gint extraction_rate);


/**
 * Private data structure for the GwpPlanet type.
 *
 * This data should be accesed directly only by the low-level get/set
 * object's methods, the high-level ones shouldn't touch them.
 */
struct _GwpPlanetPrivate {
  gboolean dispose_has_run; /**< Internal object's variable. */
  /* private attributes */
  gboolean is_known; /**< TRUE if we know the planet in any way. */
  GwpStarbase *starbase; /**< Pointer to a starbase orbiting the
			    planet. NULL if the planet doesn't have one. */
  gint16 owner; /**< Owner's race number. Range 1..11. 0 = unowned, -1
		   = unknown */
  GString *fcode; /**< Planet's friendly Code. Max 3 chars. */
  gint16 mines; /**< Mineral mines on planet. */
  gint16 factories; /**< Supplies factories on planet. */
  gint16 defense_posts; /**< Defense posts on planet. If 15 or more,
			   planet activity's visibility goes to 0% */
  gint32 mined_neutronium; /**< Neutronium on surface. Specified in KT. */
  gint32 mined_tritanium; /**< Tritanium on surface. Specified in KT. */
  gint32 mined_duranium; /**< Duranium on surface. Specified in KT. */
  gint32 mined_molybdenum; /**< Molybdenum on surface, Specified in KT. */
  gint32 colonists; /**< Number of colonists on planet. Specified in
		       clans (100 people each). */
  gint32 supplies; /**< Supplies available on planet. Specified in KT. */
  gint32 megacredits; /**< Megacredits available on planet. */
  gint32 ground_neutronium; /**< Neutronium below surface. Specified
			       in KT. */
  gint32 ground_tritanium; /**< Tritanium below surface. Specified in KT. */
  gint32 ground_duranium; /**< Duranium below surface. Specified in KT. */
  gint32 ground_molybdenum; /**< Molybdenum below surface. Specified
			       in KT. */
  gint16 dens_neutronium; /**< Neutroium below surface. Specified in KT. */
  gint16 dens_tritanium; /**< Tritanium below surface. Specified in KT. */
  gint16 dens_duranium; /**< Duranium below surface. Specified in KT. */
  gint16 dens_molybdenum; /**< Molybdenum below surface. Specified in KT. */
  gint16 tax_colonists; /**< Tax charged to colonists. Specified in %. */
  gint16 tax_natives; /**< Tax charged to natives. Specified in %. */
  gint16 happiness_colonists; /**< Colonists's happines
				 level. Specified in %. */
  gint16 happiness_natives; /**< Natives's happiness level. Specified
			       in % */
  /**
   *  Socio Political Index.
   *
   * This defines the type of government that the natives have on the
   * current planet and the quantity of taxes that they pay. Options
   * can be:
   *
   *    - 0 none (0%)
   *    - 1 Anarchy (20%)
   *    - 2 Pre-Tribal (40%)
   *    - 3 Early-Tribal (60%)
   *    - 4 Tribal (80%)
   *    - 5 Feudal (100%)
   *    - 6 Monarchy (120%)
   *    - 7 Representative (140%)
   *    - 8 Participatory (160%)
   *    - 9 Unity (180%)
   */
  gint16 natives_spi; 
  gint32 natives; /**< Number of natives on planet. Specified in clans
		     (100 people each). */

  /**
   * Native race on planet.
   *
   *    - 0 none
   *    - 1 Humanoid
   *    - 2 Bovinoid
   *    - 3 Reptilian
   *    - 4 Avian
   *    - 5 Amorphous
   *    - 6 Insectoid
   *    - 7 Amphibian
   *    - 8 Ghipsoldal
   *    - 9 Siliconoid   
   */
  gint16 natives_race;

  /**
   * Planet's temperature.
   *
   * Defines the habitability, the maximum number of colonists that
   * can live on the current planet, and the growth rate.
   *
   *    - 0..15 desert (85..100 ºF)
   *    - 16..35 tropical (65..84 ºF)
   *    - 36..60 warm (40..64 ºF)
   *    - 61..85 cool (15..39 ºF)
   *    - 86..100 arctic (0..14 ºF)
   */
  gint16 temperature;
  gint16 build_base; /**< 1=Build base, 0 otherwise. */
};

/*
 * forward definitions.
 */
static void gwp_planet_init (GTypeInstance *instance, gpointer g_class);
static void gwp_planet_class_init (GwpPlanetClass *klass);

GType gwp_planet_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpPlanetClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_planet_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpPlanet),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_planet_init /* instance_init */
    };
    type = g_type_register_static (GWP_TYPE_OBJECT,
				   "GwpPlanet",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_planet_init (GTypeInstance *instance,
			     gpointer       g_class)
{
  GwpPlanet *self = (GwpPlanet *)instance;
  self->priv = g_new0 (GwpPlanetPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* private attributes init */
  self->priv->is_known = FALSE;
  self->priv->starbase = NULL;
  self->priv->owner = -1;
  self->priv->fcode = g_string_new ("GWP");
  self->priv->mines = 0;
  self->priv->factories = 0;
  self->priv->defense_posts = 0;
  self->priv->mined_neutronium = 0;
  self->priv->mined_tritanium = 0;
  self->priv->mined_duranium = 0;
  self->priv->mined_molybdenum = 0;
  self->priv->colonists = -1;
  self->priv->supplies = 0;
  self->priv->megacredits = 0;
  self->priv->ground_neutronium = 0;
  self->priv->ground_tritanium = 0;
  self->priv->ground_duranium = 0;
  self->priv->ground_molybdenum = 0;
  self->priv->dens_neutronium = 0;
  self->priv->dens_tritanium = 0;
  self->priv->dens_duranium = 0;
  self->priv->dens_molybdenum = 0;
  self->priv->tax_colonists = 0;
  self->priv->tax_natives = 0;
  self->priv->happiness_colonists = 0;
  self->priv->happiness_natives = 0;
  self->priv->natives_spi = 0;
  self->priv->natives = 0;
  self->priv->natives_race = 0;
  self->priv->temperature = -1;
  self->priv->build_base = 0;
}

static void gwp_planet_dispose (GwpPlanet *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here, I have to unref all members on which I own a reference.
   */
  if (GWP_IS_STARBASE(self->priv->starbase)) {
    g_object_unref(self->priv->starbase);
  }
}

static void gwp_planet_finalize (GwpPlanet *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_planet_class_init (GwpPlanetClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /*
   * Register destructor methods.
   */
  gobject_class->dispose = (void *) gwp_planet_dispose;
  gobject_class->finalize = (void *) gwp_planet_finalize;

  /*
   * Signals
   */
  g_signal_newv ("selected",
		 G_TYPE_FROM_CLASS (klass),
		 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
		 NULL /* class closure */,
		 NULL /* accumulator */,
		 NULL /* accu_data */,
		 g_cclosure_marshal_VOID__VOID,
		 G_TYPE_NONE /* return_type */,
		 0     /* n_params */,
		 NULL  /* param_types */);
}

/**
 * Instantiates a new planet.
 *
 * @return The new GwpPlanet object.
 */
GwpPlanet * gwp_planet_new (void)
{
  return g_object_new (gwp_planet_get_type(), NULL);
}

/**********************/
/* High-level methods */
/**********************/

/*
 * Global Defense Systems calculations. (GDS)
 */

/**
 * Type of beam weapons on defense systems - GDS
 *
 * This calculates the equivalent type of beams weapons a planet
 * has to defend itself from attacks. It depend on the defense
 * posts and if wether a starbase is orbiting around it.
 *
 * @param self a GwpPlanet.
 * @return The name of the beam weapon type.
 */
gchar * gwp_planet_get_def_sys_beams_type_str (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  GString *ret = NULL;
  GwpBeamSpec *beam = NULL;
  gint beam_type = gwp_planet_get_def_sys_beams_type (self);

  if (beam_type != 0) {
    beam = g_slist_nth_data (beamspec_list, beam_type - 1);
    g_assert (GWP_IS_BEAMSPEC(beam));

    ret = g_string_new (gwp_beamspec_get_name(beam));
  } else {
    ret = g_string_new (_("No beam weapon"));
  }

  return ret->str;
}

/**
 * Type of beam weapons on defense systems - GDS
 *
 * This calculates the equivalent type of beams weapons a planet
 * has to defend itself from attacks. It depend on the defense
 * posts and if wether a starbase is orbiting around it.
 *
 * @param self a GwpPlanet.
 * @return The beam weapon type.
 */
gint gwp_planet_get_def_sys_beams_type (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret;

  ret = round (sqrt(gwp_planet_get_defense_posts(self) * 0.5));

  /* 
     FIXME: I don't understand what Donovan says here:
     http://www.xs4all.nl/~donovan/help/details.htm#combat3
     ...about the planet beam weapons type.
  */
/*   if (gwp_planet_has_starbase(self)) { */
/*     if (ret < */
/*   } */

  /* Check for type "overrun" */
  if (ret > 10) { ret = 10; };
  
  return ret;
}

/**
 * Number of beam weapons on defense systems - GDS.
 *
 * This calculates the equivalent number of beams a planet has to
 * defend itself from attacks.
 *
 * @param self a GwpPlanet.
 * @return The number of beam weapons.
 */
gint gwp_planet_get_def_sys_beams_nr(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret;

  if(gwp_planet_has_starbase(self)) {
    ret = round(sqrt(((gdouble)gwp_planet_get_defense_posts(self) +
		      (gdouble)gwp_starbase_get_defense(gwp_planet_get_starbase(self)))
		     / 3));
  } else {
    ret = round(sqrt((gdouble)gwp_planet_get_defense_posts(self) / 3));
  }

  return ret;
}

/**
 * Number of fighters on defense systems - GDS.
 *
 * This calculates the equivalent number of fighters a planet has to
 * defend itself from attacks.
 *
 * @param self a GwpPlanet.
 * @return The number of fighters.
 */
gint gwp_planet_get_def_sys_fighters_nr(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret;

  if(gwp_planet_get_defense_posts(self) >= 1) {
    ret = round(sqrt((gdouble)gwp_planet_get_defense_posts(self) - 0.75));
  } else {
    /* Avoid a negative square root */
    ret = 0;
  }

  /* Add starbase fighters */
  if(gwp_planet_has_starbase(self)) {
    ret += gwp_starbase_get_fighters(gwp_planet_get_starbase(self));
  }

  return ret;
}

/**
 * Number of fighter bays on defense systems - GDS.
 *
 * @param self a GwpPlanet.
 * @return The number of fighter bays
 */
gint gwp_planet_get_def_sys_fighter_bays(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret;

  ret = trunc(sqrt(gwp_planet_get_defense_posts(self)));

  if (gwp_planet_has_starbase(self)) {
    ret += 5;    
  } 
  return ret;
}

/**
 * Planet's Battle mass on defense systems - GDS.
 *
 * This is the equivalent mass that defense systems generate on the
 * planet, the planet's battle endurance.
 *
 * @param self a GwpPlanet.
 * @return The ballte mass in KT.
 */
gint gwp_planet_get_def_sys_battle_mass(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret;

  if(gwp_planet_has_starbase(self)) {
    ret = (100 + gwp_planet_get_defense_posts(self) 
	   + gwp_starbase_get_defense(gwp_planet_get_starbase(self)));
  } else {
    ret = (100 + gwp_planet_get_defense_posts(self));
  }

  return ret;
}

/**
 * Calculates the colonists population limit.
 *
 * @param self a GwpPlanet
 * @return The maximum number of colonist clans that can live without
 * dying on the planet.
 */
gint gwp_planet_get_col_growth_limit(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret = 0;

  g_assert(GWP_IS_PLANET(self));

  if(gwp_planet_is_known(self) && gwp_planet_is_mine(self)) {

    /* If planet conditions are good for life... */
    if((gwp_planet_get_temperature(self) <= 84) &&
       (gwp_planet_get_temperature(self) >= 15)) {
      if(gwp_game_state_get_race(game_state) != RACE_CRYSTALLINE) {
	ret = sin(3.14 * ((100.0 - (gdouble)gwp_planet_get_temperature(self))
			  / 100.0)) * 100000;
      } else {
	/* If we are Crystalline... */
	ret = gwp_planet_get_temperature(self) * 1000;
      }
    } else {
      /* If planet conditions are extreme... */

      /* FIXME!!!: We need to know host configuration for this... */
    }
  } 

  return ret; 
}

/**
 * Calculates the native population limit.
 *
 * @param self a GwpPlanet
 * @return The maximum number of native clans that can live on the
 * planet.
 */
gint gwp_planet_get_nat_growth_limit(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret = 0;

  if(gwp_planet_is_known(self) && gwp_planet_is_mine(self)) {
    if(gwp_planet_get_natives_race(self) != NATIVE_NONE) {
      /* If the planet is ours and the natives aren't Siliconoid */
      if(gwp_planet_get_natives_race(self) != NATIVE_SILICONOID) {
	ret = sin(3.14 * ((100.0 - (gdouble)gwp_planet_get_temperature(self))
			  / 100.0)) * 150000;
      } else {
	/* If they are Siliconoid, it's easier */
	ret = gwp_planet_get_temperature(self) * 1000;
      }
    }
  }
  
  return ret;
}

/**
 * Copies the planet object.
 *
 * @param self the GwpPlanet to be copied.
 * @return An exact copy of the original GwpPlanet.
 */
GwpPlanet * gwp_planet_copy (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  GwpPlanet *p_copy;

  p_copy  = gwp_planet_new();
  g_free (p_copy->priv);
  p_copy->priv = g_malloc (sizeof(GwpPlanetPrivate));
  p_copy->priv = memcpy (p_copy->priv, self->priv, sizeof(GwpPlanetPrivate));

  /* Now copy starbase if exists */
  if (gwp_planet_has_starbase(self)) {
    GwpStarbase *sb;
    sb = gwp_starbase_copy (gwp_planet_get_starbase(self));
    gwp_planet_set_starbase (p_copy, sb);
    gwp_starbase_set_planet (sb, p_copy);
  }

  return p_copy;
}

/**
 * Search and retrieve a planet.
 *
 * @param list a hast table with all the planets on the game.
 * @param planet_id the planet ID.
 * @return The GwpPlanet or NULL if doesn't exist.
 */
GwpPlanet * gwp_planet_get(GHashTable *list, gint planet_id)
{
  return (GwpPlanet *) g_hash_table_lookup(list, (gconstpointer)planet_id);
}

gboolean gwp_planet_is_mine (GwpPlanet *self)
{
  g_assert(GWP_IS_PLANET(self));

  return (gwp_planet_what_is(self) == IS_MINE);
}

/**
 * Returns TRUE if planet is unowned.
 */
gboolean
gwp_planet_is_unowned (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  return (gwp_planet_what_is(self) == IS_UNOWNED);
}

gint gwp_planet_what_is (GwpPlanet *self)
{
  g_assert(GWP_IS_PLANET(self));

  if(gwp_planet_get_owner(self) == gwp_game_state_get_race(game_state)) {
    return IS_MINE;
  } else if (gwp_planet_get_owner(self) == 0) {
    return IS_UNOWNED;
  } else {
    return IS_ENEMY; // FIXME: Check for allied planets!!!
  }
}

/**
 * Returns planet's temperature in ºF.
 *
 * @param self a GwpPlanet.
 * @return the temperature value.
 */
gint16 gwp_planet_get_temperature_f (GwpPlanet *self) 
{
  g_assert (GWP_IS_PLANET(self));

  return 100 - gwp_planet_get_temperature(self);
}

/**
 * Returns planet's temperature label in a string.
 *
 * @param self a GwpPlanet.
 * @return The character string representing the planet's
 * temperature.
 * @see _GwpPlanetPrivate::temperature
 */
gchar * gwp_planet_get_temperature_str(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint16 temp;

  temp = gwp_planet_get_temperature (self);
	
  if((temp >= 0) && (temp <= 15)) {
    return _("desert");
  } else if((temp >= 16) && (temp <= 35)) {
    return _("tropical");
  } else if((temp >= 36) && (temp <= 60)) {
    return _("warm");
  } else if((temp >= 61) && (temp <= 85)) {
    return _("cool");
  } else if((temp >= 86) && (temp <= 100)) {
    return _("arctic");
  } else {
    return _("n/a");
  }
}

/**
 * Calculates the planet visibility.
 *
 * Based on the amount of mineral mines, supplies factories and
 * defense posts, calculate the percentaje of being spotted as an
 * habited planet.
 *
 * @param self a GwpPlanet.
 * @return The % of being spotted.
 */
gint gwp_planet_get_visibility(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret;

  if(((gwp_planet_get_mines (self) > 20) || 
      (gwp_planet_get_factories (self) > 15)) &&
     (gwp_planet_get_defense_posts (self) < 15)) {
    ret = (100 - (gwp_planet_get_defense_posts (self) * 6.66));
  } else {
    ret = 0;
  }

  return ret;
}

/**
 * Calculates the happiness change on colonists.
 *
 * Based on several planet's characteristics and taxes, calculates how
 * much more or less happy will be the colonists next turn.
 *
 * @param self a GwpPlanet.
 * @return The happiness change.
 */
gint gwp_planet_get_happiness_col_change (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret;

  if(gwp_game_state_get_race(game_state) != RACE_CRYSTALLINE) {
    ret = trunc((1000 - sqrt(gwp_planet_get_colonists (self)) -
		 80 * gwp_planet_get_tax_colonists (self) -
		 abs(50 - gwp_planet_get_temperature (self)) * 3 -
		 (gwp_planet_get_factories (self) + 
		  gwp_planet_get_mines (self)) / 3)
		/ 100);
  } else {
    ret = trunc((1000.0 - sqrt(gwp_planet_get_colonists (self)) -
		 80.0 * gwp_planet_get_tax_colonists (self) -
		 abs(100 - gwp_planet_get_temperature (self)) * 3.0 -
		 (gwp_planet_get_factories (self) + 
		  gwp_planet_get_mines (self)) / 3)
		/ 100);
  }
  return ret;
}

/**
 * Calculates the happiness change on natives.
 *
 * Based on several planet's characteristics and taxes, calculates how
 * much more or less happy will be the natives next turn.
 *
 * @param self a GwpPlanet.
 * @return The happiness change.
 */
gint gwp_planet_get_happiness_nat_change (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint ret = 0;

  if(gwp_planet_get_natives_race (self) != NATIVE_NONE) {
    ret = trunc((1000 - sqrt(gwp_planet_get_natives (self)) -
		 85.0 * gwp_planet_get_tax_natives (self) -
		 trunc((gwp_planet_get_factories (self) + 
			gwp_planet_get_mines (self)) / 2)
		 - 50.0 * (10 - gwp_planet_get_natives_spi (self))) / 100);
  } 

  /* If natives are Avian, they get happy faster ;-) */
  if(gwp_planet_get_natives_race (self) == NATIVE_AVIAN) {
    ret += 10;
  }
  return ret;
}

/**
 * Returns the name of the native race that live on the planet.
 *
 * @param self a GwpPlanet.
 * @return The native race's name.
 * @see _GwpPlanetPrivate::natives
 */
gchar * gwp_planet_get_natives_race_chars (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gchar * race[] = {
    _("none"), 
    _("Humanoid"),
    _("Bovinoid"), 
    _("Reptilian"),
    _("Avian"), 
    _("Amorphous"),
    _("Insectoid"), 
    _("Amphibian"),
    _("Ghipsoldal"), 
    _("Siliconoid")
  };
	
  return g_strdup(race[gwp_planet_get_natives_race (self)]);
}

/**
 * Returns the native's government type on the current planet.
 *
 * @param self a GwpPlanet.
 * @return The native government type name.
 * @see _GwpPlanetPrivate::spi
 */
gchar * gwp_planet_get_natives_spi_chars (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gchar * spi[] = {
    _("none"),
    _("Anarchy"),
    _("Pre-Tribal"),
    _("Early-Tribal"),
    _("Tribal"),
    _("Feudal"),
    _("Monarchy"),
    _("Representative"),
    _("Participatory"),
    _("Unity")
  };
	
  return g_strdup(spi[gwp_planet_get_natives_spi (self)]);
}

/**
 * TRUE if the current planet has an orbiting starbase.
 *
 * @param self a GwpPlanet.
 * @return TRUE if planet has a starbase.
 */
gboolean gwp_planet_has_starbase (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gboolean ret = FALSE;

  if (GWP_IS_STARBASE(self->priv->starbase)) {
    ret = TRUE;
  }
  return ret;
}

/**
 * This function returns a number between 0.0 and 1.0, to be
 * fed on a progress bar.
 */
gdouble gwp_planet_get_ground_percent(gint mineral)
{
  gdouble ret = mineral / 10000.0;

  if(ret > 1.0) {
    return 1.0;
  } else {
    return ret;
  }
}

gint gwp_planet_neutronium_extraction_rate(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  return gwp_planet_mineral_extraction_rate(self,
					    gwp_planet_get_dens_neutronium(self),
					    gwp_planet_get_ground_neutronium(self));
}

gint gwp_planet_neutronium_turns_left(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  return gwp_planet_mineral_turns_left(gwp_planet_get_ground_neutronium(self),
				       gwp_planet_neutronium_extraction_rate(self));
}

gint gwp_planet_tritanium_extraction_rate(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  return gwp_planet_mineral_extraction_rate(self,
					    gwp_planet_get_dens_tritanium(self),
					    gwp_planet_get_ground_tritanium(self));
}

gint gwp_planet_tritanium_turns_left(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  return gwp_planet_mineral_turns_left(gwp_planet_get_ground_tritanium(self),
				       gwp_planet_tritanium_extraction_rate(self));
}

gint gwp_planet_molybdenum_extraction_rate(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  return gwp_planet_mineral_extraction_rate(self,
					    gwp_planet_get_dens_molybdenum(self),
					    gwp_planet_get_ground_molybdenum(self));
}

gint gwp_planet_molybdenum_turns_left(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  return gwp_planet_mineral_turns_left(gwp_planet_get_ground_molybdenum(self),
				       gwp_planet_molybdenum_extraction_rate(self));
}

gint gwp_planet_duranium_extraction_rate(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  return gwp_planet_mineral_extraction_rate(self,
					    gwp_planet_get_dens_duranium(self),
					    gwp_planet_get_ground_duranium(self));
}

gint gwp_planet_duranium_turns_left(GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  return gwp_planet_mineral_turns_left(gwp_planet_get_ground_duranium(self),
				       gwp_planet_duranium_extraction_rate(self));
}

/**
 * Calculates how many MC will collect a planet from colonists taxes.
 *
 * @param self a GwpPlanet.
 * @return The amount of MC collected from colonists.
 */
gint gwp_planet_get_tax_collected_colonists(GwpPlanet *self)
{
  gint ret;

  if (gwp_planet_get_happiness_colonists(self) > 30) {
    ret = ((gdouble)gwp_planet_get_colonists(self)/100) * 
      ((gdouble)gwp_planet_get_tax_colonists(self)/10) * 
      (gdouble)(gwp_planet_get_tax_rate_colonists(self)/100);
  } else {
    ret = 0;
  }

  return ret;
}


/**
 * Calculates how many MC will collect a planet from native taxes.
 *
 * @param self a GwpPlanet.
 * @return The amount of MC collected from natives.
 */
gint gwp_planet_get_tax_collected_natives_max (GwpPlanet *self)
{
  gint ret;

  if (gwp_planet_get_happiness_natives(self) > 30) {
    ret = ((gdouble)gwp_planet_get_natives(self)/100.0) * 
      ((gdouble)gwp_planet_get_tax_rate_colonists(self) / 100.0) *
      ((gdouble)gwp_planet_get_tax_natives(self)/10.0) * 
      ((gdouble)gwp_planet_get_natives_spi(self)/5.0) * 
      ((gdouble)gwp_planet_get_tax_rate_natives(self)/100.0);
  } else {
    ret = 0;
  }
  return ret;
}

/**
 * Calculates how many MC will collect a planet from native taxes.
 *
 * This value is limited by the kind and amount of colonists and natives.
 *
 * @param self a GwpPlanet.
 * @return The amount of MC collected from natives.
 */
gint gwp_planet_get_tax_collected_natives(GwpPlanet *self)
{
  /* Max amount of MC that can be collected */
  gint max = gwp_planet_get_tax_collected_natives_max (self);
  /* Real max possible amount of MC collected */
  gint ret = gwp_planet_get_colonists(self) * 
    ((gdouble)gwp_planet_get_tax_rate_colonists(self)/100.0) *
    ((gdouble)gwp_planet_get_tax_rate_natives(self)/100.0);
  
  /* If colonists are too few...we cannot collect all the money */
  if (max > ret) {
    return ret;
  } else {
    return max;
  }
}

/**
 * Calculates the maximum factories allowed for construction.
 *
 * @param self a GwpPlanet
 * @return The number of factories
 */
gint 
gwp_planet_calculate_allowed_factories (GwpPlanet *self)
{
  gint clans = gwp_planet_get_colonists (self);
  gint ret;

  if (clans <= 100) {
    ret = clans;
  } else {
    ret = 100 + sqrt (clans - 100);
  }
  return ret;
}

/**
 * Calculates the maximum mineral mines allowed for construction.
 *
 * @param self a GwpPlanet
 * @return The number of mines
 */
gint 
gwp_planet_calculate_allowed_mines (GwpPlanet *self)
{
  gint clans = gwp_planet_get_colonists (self);
  gint ret;

  if (clans <= 200) {
    ret = clans;
  } else {
    ret = 200 + sqrt (clans - 200);
  }
  return ret;
}

/**
 * Calculates the maximum defense posts allowed for construction.
 *
 * @param self a GwpPlanet
 * @return The number of defenses
 */
gint 
gwp_planet_calculate_allowed_defenses (GwpPlanet *self)
{
  gint clans = gwp_planet_get_colonists (self);
  gint ret;

  if (clans <= 50) {
    ret = clans;
  } else {
    ret = 50 + sqrt (clans - 50);
  }
  return ret;
}

/**********************************/
/* Get/Set method implementations */
/**********************************/
gboolean gwp_planet_is_known (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->is_known;
}

void gwp_planet_set_is_known (GwpPlanet *self, gboolean is_known)
{
  g_assert (GWP_IS_PLANET(self));
  self->priv->is_known = is_known;
}

GwpStarbase * gwp_planet_get_starbase (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (GWP_IS_STARBASE(self->priv->starbase));
  return self->priv->starbase;
}

void gwp_planet_set_starbase (GwpPlanet *self, GwpStarbase *sb)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (GWP_IS_STARBASE(sb));
  self->priv->starbase = sb;
}

gint16 gwp_planet_get_owner (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->owner;
}

void gwp_planet_set_owner (GwpPlanet *self, gint16 o)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (o >= -1 && o <= 11); /* -1 = unknown, 0 = unowned */
  self->priv->owner = o;
}

gchar * gwp_planet_get_fcode (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  GString *ret = g_string_new(self->priv->fcode->str);

  return ret->str;
}

void gwp_planet_set_fcode (GwpPlanet *self, gchar *fcode)
{
  g_assert (GWP_IS_PLANET(self));
  
  if (strlen(fcode) <= 3) {
    self->priv->fcode = g_string_new (fcode);
  }
}

gint16 gwp_planet_get_mines (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->mines;
}

void gwp_planet_set_mines (GwpPlanet *self, gint16 m)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (m >= 0 && m <= 516);
  self->priv->mines = m;
}

gint16 gwp_planet_get_factories (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->factories;
}

void gwp_planet_set_factories (GwpPlanet *self, gint16 f)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (f >= 0 && f <= 416);
  self->priv->factories = f;
}

gint16 gwp_planet_get_defense_posts (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->defense_posts;
}

void gwp_planet_set_defense_posts (GwpPlanet *self, gint16 d)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (d >= 0 && d <= 366);
  self->priv->defense_posts = d;
}

gint32 gwp_planet_get_mined_neutronium (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->mined_neutronium;
}

void gwp_planet_set_mined_neutronium (GwpPlanet *self, gint32 mn)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (mn >= 0);
  self->priv->mined_neutronium = mn;
}

gint32 gwp_planet_get_mined_tritanium (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->mined_tritanium;
}

void gwp_planet_set_mined_tritanium (GwpPlanet *self, gint32 mt)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (mt >= 0);
  self->priv->mined_tritanium = mt;
}

gint32 gwp_planet_get_mined_duranium (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->mined_duranium;
}

void gwp_planet_set_mined_duranium (GwpPlanet *self, gint32 md)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (md >= 0);
  self->priv->mined_duranium = md;
}

gint32 gwp_planet_get_mined_molybdenum (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->mined_molybdenum;
}

void gwp_planet_set_mined_molybdenum (GwpPlanet *self, gint32 mm)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (mm >= 0);
  self->priv->mined_molybdenum = mm;
}

gint32 gwp_planet_get_colonists (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->colonists;
}

void gwp_planet_set_colonists (GwpPlanet *self, gint32 col)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (col >= 0 && col <= 250000); /* FIXME: THost limit 100000, PHost limit 250000 */
  self->priv->colonists = col;
}

gint32 gwp_planet_get_supplies (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->supplies;
}

void gwp_planet_set_supplies (GwpPlanet *self, gint32 sup)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (sup >= 0 );
  self->priv->supplies = sup;
}

gint32 gwp_planet_get_megacredits (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->megacredits;
}

void gwp_planet_set_megacredits (GwpPlanet *self, gint32 mc)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (mc >= 0); /* FIXME: check for MC limits! */
  self->priv->megacredits = mc;
}

gint32 gwp_planet_get_ground_neutronium (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->ground_neutronium;
}

void gwp_planet_set_ground_neutronium (GwpPlanet *self, gint32 gn)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (gn >= 0);
  self->priv->ground_neutronium = gn;
}

gint32 gwp_planet_get_ground_tritanium (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->ground_tritanium;
}

void gwp_planet_set_ground_tritanium (GwpPlanet *self, gint32 gt)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (gt >= 0);
  self->priv->ground_tritanium = gt;
}

gint32 gwp_planet_get_ground_duranium (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->ground_duranium;
}

void gwp_planet_set_ground_duranium (GwpPlanet *self, gint32 gd)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (gd >= 0);
  self->priv->ground_duranium = gd;
}

gint32 gwp_planet_get_ground_molybdenum (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->ground_molybdenum;
}

void gwp_planet_set_ground_molybdenum (GwpPlanet *self, gint32 gm)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (gm >= 0);
  self->priv->ground_molybdenum = gm;
}

gint16 gwp_planet_get_dens_neutronium (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->dens_neutronium;
}

void gwp_planet_set_dens_neutronium (GwpPlanet *self, gint16 dn)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (dn >= 0);
  self->priv->dens_neutronium = dn;
}

gint16 gwp_planet_get_dens_tritanium (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->dens_tritanium;
}

void gwp_planet_set_dens_tritanium (GwpPlanet *self, gint16 dt)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (dt >= 0);
  self->priv->dens_tritanium = dt;
}

gint16 gwp_planet_get_dens_duranium (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->dens_duranium;
}

void gwp_planet_set_dens_duranium (GwpPlanet *self, gint16 dd)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (dd >= 0);
  self->priv->dens_duranium = dd;
}

gint16 gwp_planet_get_dens_molybdenum (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->dens_molybdenum;
}

void gwp_planet_set_dens_molybdenum (GwpPlanet *self, gint16 dm)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (dm >= 0);
  self->priv->dens_molybdenum = dm;
}

gint16 gwp_planet_get_tax_colonists (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->tax_colonists;
}

void gwp_planet_set_tax_colonists (GwpPlanet *self, gint16 tc)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (tc >= 0);
  self->priv->tax_colonists = tc;
}

gint16 gwp_planet_get_tax_natives (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->tax_natives;
}

void gwp_planet_set_tax_natives (GwpPlanet *self, gint16 tn)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (tn >= 0);
  self->priv->tax_natives = tn;
}

gint16 gwp_planet_get_happiness_colonists (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->happiness_colonists;
}

void gwp_planet_set_happiness_colonists (GwpPlanet *self, gint16 tc)
{
  g_assert (GWP_IS_PLANET(self));

  /* Boundary checks */
  if (tc > 100) tc = 100;
  if (tc < 0) tc = 0;

  self->priv->happiness_colonists = tc;
}

gint16 gwp_planet_get_happiness_natives (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->happiness_natives;
}

void gwp_planet_set_happiness_natives (GwpPlanet *self, gint16 tn)
{
  g_assert (GWP_IS_PLANET(self));

  /* Boundary checks */
  if (tn > 100) tn = 100;
  if (tn < 0) tn = 0;

  self->priv->happiness_natives = tn;
}

gint16 gwp_planet_get_natives_spi (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->natives_spi;
}

void gwp_planet_set_natives_spi (GwpPlanet *self, gint16 spi)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (spi >= 0 && spi <= 9);
  self->priv->natives_spi = spi;
}

gint32 gwp_planet_get_natives (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->natives;
}

void gwp_planet_set_natives (GwpPlanet *self, gint32 nat)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (nat >= 0);
  self->priv->natives = nat;
}

gint16 gwp_planet_get_natives_race (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->natives_race;
}

void gwp_planet_set_natives_race (GwpPlanet *self, gint16 nr)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (nr >= 0 && nr <= 9);
  self->priv->natives_race = nr;
}

gint16 gwp_planet_get_temperature (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->temperature;
}

void gwp_planet_set_temperature (GwpPlanet *self, gint16 temp)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (temp >= 0 && temp <= 100);
  self->priv->temperature = temp;
}

gint16 gwp_planet_get_build_base (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return self->priv->build_base;
}

void gwp_planet_set_build_base (GwpPlanet *self, gint16 bb)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (bb >= 0 && bb <= 1);
  self->priv->build_base = bb;
}

/**
 * Returns the planet's mining rate depending on its owner and natives.
 */
gint
gwp_planet_get_mining_rate (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  enum natives natives = gwp_planet_get_natives_race (self);
  gint owner = gwp_planet_get_owner (self);
  gint miningrate = gwp_game_state_get_host_mining_rate (game_state, owner);
  
  if (natives == NATIVE_REPTILIAN)
    miningrate *= 2;

  return miningrate;
}

/**
 * Returns the planet's tax rate for colonists
 *
 * @return the planet's tax rate in percentage.
 */
gint
gwp_planet_get_tax_rate_colonists (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  gint owner = gwp_planet_get_owner (self);
  gint taxrate = gwp_game_state_get_host_tax_rate (game_state, owner);
  
  return taxrate;
}

/**
 * Returns the planet's tax rate for natives
 *
 * @return the planet's tax rate in percentage.
 */
gint
gwp_planet_get_tax_rate_natives (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));

  enum natives natives = gwp_planet_get_natives_race (self);
  gint taxrate = gwp_planet_get_tax_rate_colonists (self);
  
  if (natives == NATIVE_INSECTOID)
    taxrate *= 2;
  else if (natives == NATIVE_AMORPHOUS)
    taxrate *= 0;

  return taxrate;
}

/*******************/
/* Private methods */
/*******************/

gint 
gwp_planet_mineral_extraction_rate(GwpPlanet   *self,
				   gint         density, 
				   gint         mineral)
{
  g_assert (GWP_IS_PLANET (self));

  gint ret;
  gdouble miningrate;
  gint mines = gwp_planet_get_mines (self);

  /* Race & natives corrections */
  miningrate = gwp_planet_get_mining_rate (self);

  /* WARNING: This calculus is the good one, check filefmt.txt, not Donovan! */
  ret = rint (rint((gdouble)mines * (gdouble)density / 100.0) * 
	      miningrate / 100.0);

  if(ret <= mineral) {
    return ret;
  } else {
    return mineral;
  }
}

gint gwp_planet_mineral_turns_left(gint mineral, gint extraction_rate)
{
  gint ret;

  if(extraction_rate > 0) {
    ret = mineral / extraction_rate;
  } else {
    ret = 0;
  }

  return ret;
}
