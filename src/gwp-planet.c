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

#include <math.h>

#include "gwp-starbase.h"
#include "race.h"
#include "global.h"
#include "game_state.h"
#include "gwp-planet.h"

gint gwp_planet_mineral_extraction_rate(gint mines, gint density, gint mineral);
gint gwp_planet_mineral_turns_left(gint mineral, gint extraction_rate);


struct _GwpPlanetPrivate {
  gboolean dispose_has_run;
  /* private attributes */
  gboolean is_known;
  GwpStarbase *starbase;
  gint16 owner;
  GString *fcode;
  gint16 mines;
  gint16 factories;
  gint16 defense_posts;
  gint32 mined_neutronium;
  gint32 mined_tritanium;
  gint32 mined_duranium;
  gint32 mined_molybdenum;
  gint32 colonists;
  gint32 supplies;
  gint32 megacredits;
  gint32 ground_neutronium;
  gint32 ground_tritanium;
  gint32 ground_duranium;
  gint32 ground_molybdenum;
  gint16 dens_neutronium;
  gint16 dens_tritanium;
  gint16 dens_duranium;
  gint16 dens_molybdenum;
  gint16 tax_colonists;
  gint16 tax_natives;
  gint16 happiness_colonists;
  gint16 happiness_natives;
  gint16 natives_spi;
  gint32 natives;
  gint16 natives_race;
  gint16 temperature;
  gint16 build_base;
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
    type = g_type_register_static (GWP_OBJECT_TYPE,
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
  self->priv->owner = 0;
  self->priv->fcode = g_string_new ("GWP");
  self->priv->mines = 0;
  self->priv->factories = 0;
  self->priv->defense_posts = 0;
  self->priv->mined_neutronium = 0;
  self->priv->mined_tritanium = 0;
  self->priv->mined_duranium = 0;
  self->priv->mined_molybdenum = 0;
  self->priv->colonists = 0;
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
  self->priv->temperature = 0;
  self->priv->build_base = 0;
  /* g_message("GwpPlanet init"); */
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
  /* g_message ("GwpPlanet finalize"); */
  g_free (self->priv);
}

static void gwp_planet_class_init (GwpPlanetClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* g_message ("GwpPlanetClass init"); */
  /*
   * Register destructor methods.
   */
  gobject_class->dispose = gwp_planet_dispose;
  gobject_class->finalize = gwp_planet_finalize;
}

/*
 * Public method implementations.
 */
GwpPlanet * gwp_planet_new (void)
{
  return g_object_new (gwp_planet_get_type(), NULL);
}

/**********************/
/* High-level methods */
/**********************/

/* Global Defense Systems calculations */
gint gwp_planet_get_def_sys_beams_nr(GwpPlanet *self)
{
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

/* Global Defense Systems calculations */
gint gwp_planet_get_def_sys_fighters_nr(GwpPlanet *self)
{
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

/* Global Defense Systems calculations */
gint gwp_planet_get_def_sys_fighter_bays(GwpPlanet *self)
{
  return trunc(sqrt(gwp_planet_get_defense_posts(self)));
}

/* Global Defense Systems calculations */
gint gwp_planet_get_def_sys_battle_mass(GwpPlanet *self)
{
  gint ret;

  if(gwp_planet_has_starbase(self)) {
    ret = (100 + gwp_planet_get_defense_posts(self) 
	   + gwp_starbase_get_defense(gwp_planet_get_starbase(self)));
  } else {
    ret = (100 + gwp_planet_get_defense_posts(self));
  }

  return ret;
}

/* Calculates the colonists population limit */
gint gwp_planet_get_col_growth_limit(GwpPlanet *self)
{
  gint ret = 0;

  g_assert(GWP_IS_PLANET(self));

  if(gwp_planet_is_known(self) && gwp_planet_is_mine(self)) {

    /* If planet conditions are good for life... */
    if((gwp_planet_get_temperature(self) <= 84) &&
       (gwp_planet_get_temperature(self) >= 15)) {
      if(game_get_race(game_state) != RACE_CRYSTALLINE) {
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

/* Calculates the native population limit */
gint gwp_planet_get_nat_growth_limit(GwpPlanet *self)
{
  gint ret = 0;

  g_assert(GWP_IS_PLANET(self));

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

GwpPlanet * gwp_planet_copy (GwpPlanet *self)
{
  GwpPlanet *p_copy;

  g_assert (GWP_IS_PLANET(self));

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

GwpPlanet * gwp_planet_get(GHashTable *list, gint planet_id)
{
  return (GwpPlanet *) g_hash_table_lookup(list, (gconstpointer)planet_id);
}

gboolean gwp_planet_valid_coords (GwpPlanet *self) 
{
  g_assert(GWP_IS_PLANET(self));

  if (gwp_object_get_x_coord(GWP_OBJECT(self)) <= STARCHART_X_MAX && 
      gwp_object_get_x_coord(GWP_OBJECT(self)) >= STARCHART_X_MIN &&
      gwp_object_get_y_coord(GWP_OBJECT(self)) <= STARCHART_Y_MAX && 
      gwp_object_get_y_coord(GWP_OBJECT(self)) >= STARCHART_Y_MIN) {
    return TRUE;
  } else {
    return FALSE;
  }
}

gboolean gwp_planet_is_mine (GwpPlanet *self)
{
  g_assert(GWP_IS_PLANET(self));
  if(gwp_planet_what_is(self) == IS_MINE) {
    return TRUE;
  } else {
    return FALSE;
  }
}

gint gwp_planet_what_is (GwpPlanet *self)
{
  g_assert(GWP_IS_PLANET(self));
  if(gwp_planet_get_owner(self) == game_get_race(game_state)) {
    return IS_MINE;
  } else {
    return IS_ENEMY; // FIXME: Check for allied planets!!!
  }
}

/* Returns temp in ºF */
gint16 gwp_planet_get_temperature_f (GwpPlanet *self) 
{
  return 100 - gwp_planet_get_temperature(self);
}

/* Returns temp in string */
gchar * gwp_planet_get_temperature_str(GwpPlanet *self)
{
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

gint gwp_planet_get_visibility(GwpPlanet *self)
{
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

gint gwp_planet_get_happiness_col_change (GwpPlanet *self)
{
  gint ret;

  if(game_get_race(game_state) != RACE_CRYSTALLINE) {
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

gint gwp_planet_get_happiness_nat_change (GwpPlanet *self)
{
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

gchar * gwp_planet_get_natives_race_chars (GwpPlanet *self)
{
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
	
  return race[gwp_planet_get_natives_race (self)];
}

gchar * gwp_planet_get_natives_spi_chars (GwpPlanet *self)
{
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
	
  return spi[gwp_planet_get_natives_spi (self)];
}

gboolean gwp_planet_has_starbase (GwpPlanet *self)
{
  gboolean ret = FALSE;

  g_assert (GWP_IS_PLANET(self));

  if (GWP_IS_STARBASE(self->priv->starbase)) {
    ret = TRUE;
  }
  return ret;
}

/* This function returns a number between 0.0 and 1.0, to be
   fed on a progress bar */
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
  return gwp_planet_mineral_extraction_rate(gwp_planet_get_mines(self), 
					    gwp_planet_get_dens_neutronium(self),
					    gwp_planet_get_ground_neutronium(self));
}

gint gwp_planet_neutronium_turns_left(GwpPlanet *self)
{
  return gwp_planet_mineral_turns_left(gwp_planet_get_ground_neutronium(self),
				       gwp_planet_neutronium_extraction_rate(self));
}

gint gwp_planet_tritanium_extraction_rate(GwpPlanet *self)
{
  return gwp_planet_mineral_extraction_rate(gwp_planet_get_mines(self), 
					    gwp_planet_get_dens_tritanium(self),
					    gwp_planet_get_ground_tritanium(self));
}

gint gwp_planet_tritanium_turns_left(GwpPlanet *self)
{
  return gwp_planet_mineral_turns_left(gwp_planet_get_ground_tritanium(self),
				       gwp_planet_tritanium_extraction_rate(self));
}

gint gwp_planet_molybdenum_extraction_rate(GwpPlanet *self)
{
  return gwp_planet_mineral_extraction_rate(gwp_planet_get_mines(self), 
					    gwp_planet_get_dens_molybdenum(self),
					    gwp_planet_get_ground_molybdenum(self));
}

gint gwp_planet_molybdenum_turns_left(GwpPlanet *self)
{
  return gwp_planet_mineral_turns_left(gwp_planet_get_ground_molybdenum(self),
				       gwp_planet_molybdenum_extraction_rate(self));
}

gint gwp_planet_duranium_extraction_rate(GwpPlanet *self)
{
  return gwp_planet_mineral_extraction_rate(gwp_planet_get_mines(self), 
					    gwp_planet_get_dens_duranium(self),
					    gwp_planet_get_ground_duranium(self));
}

gint gwp_planet_duranium_turns_left(GwpPlanet *self)
{
  return gwp_planet_mineral_turns_left(gwp_planet_get_ground_duranium(self),
				       gwp_planet_duranium_extraction_rate(self));
}

/* Calculates how many MC will collect a planet from colonists taxes */
gint gwp_planet_get_tax_earned_colonists(GwpPlanet *self)
{
  gint ret;

  if(gwp_planet_get_happiness_colonists(self) > 30) {
    ret = ((gdouble)gwp_planet_get_colonists(self)/100) * ((gdouble)gwp_planet_get_tax_colonists(self)/10) * race_get_tax_rate_colonists(self);
  } else {
    ret = 0;
  }

  return ret;
}


/* Calculates how many MC will collect a planet from native taxes */
gint gwp_planet_get_tax_earned_natives(GwpPlanet *self)
{
  gint ret;
  
  if(gwp_planet_get_happiness_natives(self) > 30) {
    ret = ((gdouble)gwp_planet_get_natives(self)/100) * ((gdouble)gwp_planet_get_tax_natives(self)/10) * ((gdouble)gwp_planet_get_natives_spi(self)/5);
  } else {
    ret = 0;
  }
  /* FIXME: Complete this calculation correctly!! */

  switch(gwp_planet_get_natives_race(self)) {
  case NATIVE_INSECTOID:
    ret = ret * 2;
    break;
  case NATIVE_AMORPHOUS:
    ret = ret * 0;
    break;
  default:
    break;
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
  g_assert (o >= 0 && o <= 11);
  self->priv->owner = o;
}

GString * gwp_planet_get_fcode (GwpPlanet *self)
{
  g_assert (GWP_IS_PLANET(self));
  return g_string_new(self->priv->fcode->str);
}

void gwp_planet_set_fcode (GwpPlanet *self, GString *fcode)
{
  g_assert (GWP_IS_PLANET(self));
  g_assert (fcode->len <= 3);
  self->priv->fcode = g_string_new (fcode->str);
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
  self->priv->mined_neutronium = mt;
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

/*******************/
/* Private methods */
/*******************/

gint gwp_planet_mineral_extraction_rate(gint mines, gint density, gint mineral)
{
  gint ret;

  /* FIXME: Check out the player's race mining rate!!! */
  if(density < 10) {
    ret = mines / 10;
  } else if((density >= 10) && (density < 30)) {
    ret = mines / 5;
  } else if((density >= 30) && (density < 40)) {
    ret = mines / 3;
  } else if((density >= 40) && (density < 70)) {
    ret = mines / 2;
  } else {
    ret = mines;
  }

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
