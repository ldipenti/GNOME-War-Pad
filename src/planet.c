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

#include <gnome.h>
#include <math.h>

#include "planet.h"
#include "vp_types.h"
#include "global.h"
#include "game_state.h"
#include "race.h"
#include "base.h"

/*
 * Returns the planet with id
 */
/*
GwpPlanet *planet_get(GHashTable *list, gint planet_id)
{
  return (GwpPlanet *) g_hash_table_lookup(list, (gconstpointer)planet_id);
}
*/
/* Returns the planet's corresponding base (if exists) */
Base *planet_get_base(Planet *planet)
{
  g_assert(planet != NULL);
  if(planet_has_starbase(planet)) {
    return base_get(base_list, planet_get_id(planet));
  } else {
    return NULL;
  }
}

/*
 * Planet check functions
 */
gboolean planet_has_starbase(Planet *planet)
{
  g_assert(planet != NULL);

  if(g_hash_table_lookup(base_list, 
			 (gconstpointer)(gint)planet_get_id(planet))) {
    return TRUE;
  } else {
    return FALSE;
  }
}

gboolean planet_is_known(Planet *planet) 
{
  g_assert(planet != NULL);

  if(planet->pdata != NULL) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*
 * Planet Data Access Functions
 */
gchar *planet_get_name(Planet *planet) {
  g_assert(planet != NULL);
  return planet->name;
}
 
gint16 planet_get_id(Planet *planet) {
  g_assert(planet != NULL);
  return planet->id;
}

enum races planet_get_owner(Planet *planet) {
  g_assert(planet != NULL);
  return planet->owner;
}

gchar *planet_get_fcode(Planet *planet) {
  gchar *fcode;

  g_assert(planet != NULL);

  fcode = g_malloc(4);
  fcode[0] = planet->pdata->fcode[0];
  fcode[1] = planet->pdata->fcode[1];
  fcode[2] = planet->pdata->fcode[2];
  fcode[3] = '\0';
  return fcode;
}

gint16 planet_get_mines(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->mines;
}

gint16 planet_get_factories(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->factories;
}

gint16 planet_get_defense_posts(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->defense_posts;
}

gint32 planet_get_mined_neutronium(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->mined_neutronium;
}

gint32 planet_get_mined_tritanium(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->mined_tritanium;
}

gint32 planet_get_mined_duranium(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->mined_duranium;
}

gint32 planet_get_mined_molybdenum(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->mined_molybdenum;
}

gint32 planet_get_colonists(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->colonists;
}

gint32 planet_get_supplies(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->supplies;
}

gint32 planet_get_megacredits(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->megacredits;
}

gint32 planet_get_ground_neutronium(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->ground_neutronium;
}

gint32 planet_get_ground_tritanium(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->ground_tritanium;
}

gint32 planet_get_ground_duranium(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->ground_duranium;
}

gint32 planet_get_ground_molybdenum(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->ground_molybdenum;
}

gint16 planet_get_dens_neutronium(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->dens_neutronium;
}

gint16 planet_get_dens_tritanium(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->dens_tritanium;
}

gint16 planet_get_dens_duranium(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->dens_duranium;
}

gint16 planet_get_dens_molybdenum(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->dens_molybdenum;
}

gint16 planet_get_tax_colonists(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->tax_colonists;
}

gint16 planet_get_tax_natives(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->tax_natives;
}

gint16 planet_get_happiness_colonists(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->happiness_colonists;
}

void planet_set_happiness_colonists(Planet *planet, gint happ) 
{
  g_assert(planet != NULL);
  planet->pdata->happiness_colonists = happ;
}

gint16 planet_get_happiness_natives(Planet *planet) {
  g_assert(planet != NULL);

  if(planet_get_native_race(planet) != NATIVE_NONE) {
    return planet->pdata->happiness_natives;
  } else {
    return 0;
  }
}

void planet_set_happiness_natives(Planet *planet, gint happ) 
{
  g_assert(planet != NULL);

  if(planet_get_native_race(planet) != NATIVE_NONE) {
    planet->pdata->happiness_natives = happ;
  } 
}

gint planet_get_native_spi(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->native_spi;
}

gchar *planet_get_native_spi_chars(Planet *planet) {
  gchar *spi[10];

  g_assert(planet != NULL);
	
  spi[0] = _("none");
  spi[1] = _("Anarchy");
  spi[2] = _("Pre-Tribal");
  spi[3] = _("Early-Tribal");
  spi[4] = _("Tribal");
  spi[5] = _("Feudal");
  spi[6] = _("Monarchy");
  spi[7] = _("Representative");
  spi[8] = _("Participatory");
  spi[9] = _("Unity");
	
  return spi[planet->pdata->native_spi];
}

gint32 planet_get_natives(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->natives;
}

enum natives planet_get_native_race(Planet *planet) 
{
  g_assert(planet != NULL);
  return planet->pdata->native_race;
}

gchar *planet_get_native_race_chars(Planet *planet) {
  gchar *race[] = {
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
	
  g_assert(planet != NULL);

  return race[planet_get_native_race(planet)];
}

gint16 planet_get_temperature(Planet *planet) 
{
  g_assert(planet != NULL);
  return planet->pdata->temperature;
}

/* Returns temp in ºF */
gint16 planet_get_temperature_f(Planet *planet) 
{
  g_assert(planet != NULL);
  return 100 - planet_get_temperature(planet);
}

gchar *planet_get_temperature_str(Planet *planet) {
  gint16 temp;

  g_assert(planet != NULL);
  temp = planet_get_temperature(planet);
	
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

gint16 planet_get_build_base(Planet *planet) {
  g_assert(planet != NULL);
  return planet->pdata->build_base;
}

gboolean planet_is_mine(Planet *planet)
{
  g_assert(planet != NULL);
  if(planet_what_is(planet) == IS_MINE) {
    return TRUE;
  } else {
    return FALSE;
  }
}

gboolean planet_valid_coords(Planet *planet) 
{
  g_assert(planet != NULL);
  if (planet->x <= STARCHART_X_MAX && planet->x >= STARCHART_X_MIN &&
      planet->y <= STARCHART_Y_MAX && planet->y >= STARCHART_Y_MIN) {
    return TRUE;
  } else {
    return FALSE;
  }
}

gint planet_what_is(Planet *planet)
{
  g_assert(planet != NULL);

  if(planet_get_owner(planet) == game_get_race(game_state)) {
    return IS_MINE;
  } else {
    return IS_ENEMY; // FIXME: Check for allied planets!!!
  }
}

gint planet_get_visibility(Planet *planet)
{
  gint ret;

  g_assert(planet != NULL);

  if(((planet_get_mines(planet)>20) || (planet_get_factories(planet)>15)) &&
     (planet_get_defense_posts(planet) < 15)) {
    ret = (100 - (planet_get_defense_posts(planet) * 6.66));
  } else {
    ret = 0;
  }

  return ret;
}

gint planet_neutronium_extraction_rate(Planet *planet)
{
  g_assert(planet != NULL);
  return planet_mineral_extraction_rate(planet_get_mines(planet), 
					planet_get_dens_neutronium(planet),
					planet_get_ground_neutronium(planet));
}

gint planet_neutronium_turns_left(Planet *planet)
{
  g_assert(planet != NULL);
  return planet_mineral_turns_left(planet_get_ground_neutronium(planet),
				   planet_neutronium_extraction_rate(planet));
}

gint planet_tritanium_extraction_rate(Planet *planet)
{
  g_assert(planet != NULL);
  return planet_mineral_extraction_rate(planet_get_mines(planet), 
					planet_get_dens_tritanium(planet),
					planet_get_ground_tritanium(planet));
}

gint planet_tritanium_turns_left(Planet *planet)
{
  g_assert(planet != NULL);
  return planet_mineral_turns_left(planet_get_ground_tritanium(planet),
				   planet_tritanium_extraction_rate(planet));
}

gint planet_molybdenum_extraction_rate(Planet *planet)
{
  g_assert(planet != NULL);
  return planet_mineral_extraction_rate(planet_get_mines(planet), 
					planet_get_dens_molybdenum(planet),
					planet_get_ground_molybdenum(planet));
}

gint planet_molybdenum_turns_left(Planet *planet)
{
  g_assert(planet != NULL);
  return planet_mineral_turns_left(planet_get_ground_molybdenum(planet),
				   planet_molybdenum_extraction_rate(planet));
}

gint planet_duranium_extraction_rate(Planet *planet)
{
  g_assert(planet != NULL);
  return planet_mineral_extraction_rate(planet_get_mines(planet), 
					planet_get_dens_duranium(planet),
					planet_get_ground_duranium(planet));
}

gint planet_duranium_turns_left(Planet *planet)
{
  g_assert(planet != NULL);
  return planet_mineral_turns_left(planet_get_ground_duranium(planet),
				   planet_duranium_extraction_rate(planet));
}

gint planet_mineral_extraction_rate(gint mines, gint density, gint mineral)
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

gint planet_mineral_turns_left(gint mineral, gint extraction_rate)
{
  gint ret;

  if(extraction_rate > 0) {
    ret = mineral / extraction_rate;
  } else {
    ret = 0;
  }

  return ret;
}

/* This function returns a number between 0.0 and 1.0, to be
   fed on a progress bar */
/*
gdouble planet_get_ground_percent(gint mineral)
{
  gdouble ret = mineral / 10000.0;

  if(ret > 1.0) {
    return 1.0;
  } else {
    return ret;
  }
}
*/

/* Calculates how many MC will collect a planet from colonists taxes */
/*
gint planet_get_tax_earned_colonists(Planet *planet)
{
  gint ret;

  g_assert(planet != NULL);

  if(planet_get_happiness_colonists(planet) > 30) {
    ret = ((gdouble)planet_get_colonists(planet)/100) * ((gdouble)planet_get_tax_colonists(planet)/10) * race_get_tax_rate_colonists(planet);
  } else {
    ret = 0;
  }

  return ret;
}
*/

/* Calculates how many MC will collect a planet from native taxes */
/*
gint planet_get_tax_earned_natives(Planet *planet)
{
  gint ret;
  
  g_assert(planet != NULL);

  if(planet_get_happiness_natives(planet) > 30) {
    ret = ((gdouble)planet_get_natives(planet)/100) * ((gdouble)planet_get_tax_natives(planet)/10) * ((gdouble)planet_get_native_spi(planet)/5);
  } else {
    ret = 0;
  }
*/
  /* FIXME: Complete this calculation correctly!! */
/*
  switch(planet_get_native_race(planet)) {
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
*/

gint planet_get_happiness_col_change(Planet *planet)
{
  gint ret;

  g_assert(planet != NULL);
  
  if(game_get_race(game_state) != RACE_CRYSTALLINE) {
    ret = trunc((1000 - sqrt(planet_get_colonists(planet)) -
		 80 * planet_get_tax_colonists(planet) -
		 abs(50 - planet_get_temperature(planet)) * 3 -
		 (planet_get_factories(planet)+planet_get_mines(planet)) / 3)
		/ 100);
  } else {
    ret = trunc((1000.0 - sqrt(planet_get_colonists(planet)) -
		 80.0 * planet_get_tax_colonists(planet) -
		 abs(100 - planet_get_temperature(planet)) * 3.0 -
		 (planet_get_factories(planet)+planet_get_mines(planet)) / 3)
		/ 100);
  }
  return ret;
}

gint planet_get_happiness_nat_change(Planet *planet)
{
  gint ret = 0;

  g_assert(planet != NULL);
  if(planet_get_native_race(planet) != NATIVE_NONE) {
    ret = trunc((1000 - sqrt(planet_get_natives(planet)) -
		 85.0 * planet_get_tax_natives(planet) -
		 trunc((planet_get_factories(planet) + 
			planet_get_mines(planet)) / 2)
		 - 50.0 * (10 - planet_get_native_spi(planet))) / 100);
  } 

  /* If natives are Avian, they get happy faster ;-) */
  if(planet_get_native_race(planet) == NATIVE_AVIAN) {
    ret += 10;
  }

  return ret;
}

/* Calculates the native population limit */
gint planet_get_nat_growth_limit(Planet *planet)
{
  gint ret = 0;
  g_assert(planet != NULL);

  if(planet_is_known(planet) && planet_is_mine(planet)) {
    if(planet_get_native_race(planet) != NATIVE_NONE) {
      /* If the planet is ours and the natives aren't Siliconoid */
      if(planet_get_native_race(planet) != NATIVE_SILICONOID) {
	ret = sin(3.14 * ((100.0 - (gdouble)planet_get_temperature(planet))
			  / 100.0)) * 150000;
      } else {
	/* If they are Siliconoid, it's easier */
	ret = planet_get_temperature(planet) * 1000;
      }
    }
  }
  
  return ret;
}

gint planet_get_col_growth_limit(Planet *planet)
{
  gint ret = 0;
  g_assert(planet != NULL);

  if(planet_is_known(planet) && planet_is_mine(planet)) {

    /* If planet conditions are good for life... */
    if((planet_get_temperature(planet) <= 84) &&
       (planet_get_temperature(planet) >= 15)) {
      if(game_get_race(game_state) != RACE_CRYSTALLINE) {
	ret = sin(3.14 * ((100.0 - (gdouble)planet_get_temperature(planet))
			  / 100.0)) * 100000;
      } else {
	/* If we are Crystalline... */
	ret = planet_get_temperature(planet) * 1000;
      }
    } else {
      /* If planet conditions are extreme... */

      /* FIXME!!!: We need to know host configuration for this... */
    }
  } 

  return ret; 
}

/* Copies entire planet data structure */
Planet *planet_copy(Planet *planet)
{
  Planet *planet_copy;

  g_assert(planet != NULL);

  planet_copy = g_malloc(sizeof(Planet));
  planet_copy = memcpy(planet_copy, planet, sizeof(Planet));

  /* Only if planet is known */
  if(planet->pdata != NULL) {
    planet_copy->pdata = g_malloc(sizeof(VpPlanetReg));
    planet_copy->pdata = memcpy(planet_copy->pdata, planet->pdata, 
				sizeof(VpPlanetReg));
  }

  return planet_copy;
}

/***************************************/
/* Global Defense Systems calculations */
/***************************************/
gint planet_get_def_sys_beams_nr(Planet *planet)
{
  gint ret;
  g_assert(planet != NULL);

  if(planet_has_starbase(planet)) {
    ret = round(sqrt(((gdouble)planet_get_defense_posts(planet) +
		      (gdouble)base_get_defense(planet_get_base(planet)))
		     / 3));
  } else {
    ret = round(sqrt((gdouble)planet_get_defense_posts(planet) / 3));
  }

  return ret;
}

gint planet_get_def_sys_fighters_nr(Planet *planet)
{
  gint ret;
  g_assert(planet != NULL);

  if(planet_get_defense_posts(planet) >= 1) {
    ret = round(sqrt((gdouble)planet_get_defense_posts(planet) - 0.75));
  } else {
    /* Avoid a negative square root */
    ret = 0;
  }

  /* Add starbase fighters */
  if(planet_has_starbase(planet)) {
    ret += base_get_fighters(planet_get_base(planet));
  }

  return ret;
}

gint planet_get_def_sys_fighter_bays(Planet *planet)
{
  g_assert(planet != NULL);

  return trunc(sqrt(planet_get_defense_posts(planet)));
}

gint planet_get_def_sys_battle_mass(Planet *planet)
{
  gint ret;
  g_assert(planet != NULL);

  if(planet_has_starbase(planet)) {
    ret = (100 + planet_get_defense_posts(planet) 
	   + base_get_defense(planet_get_base(planet)));
  } else {
    ret = (100 + planet_get_defense_posts(planet));
  }

  return ret;
}
