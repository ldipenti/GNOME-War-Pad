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

#define GTK_DISABLE_DEPRECATED
#define GNOME_DISABLE_DEPRECATED

// Planet utility functions

#include <gnome.h>

#include "planet.h"
#include "vp_types.h"
#include "global.h"
#include "game_state.h"

/*
 * Returns the planet with id
 */
Planet *planet_get(GHashTable *list, gint planet_id) {
  return (Planet *) g_hash_table_lookup(list, (gconstpointer)planet_id);
}

/*
 * Planet check functions
 */
gboolean planet_is_known(Planet *planet) {
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
  return planet->name;
}
 
gint16 planet_get_id(Planet *planet) {
  return planet->id;
}

gint16 planet_get_owner(Planet *planet) {
  return planet->owner;
}

gchar *planet_get_fcode(Planet *planet) {
  gchar *fcode;
  fcode = g_malloc(4);
  fcode[0] = planet->pdata->fcode[0];
  fcode[1] = planet->pdata->fcode[1];
  fcode[2] = planet->pdata->fcode[2];
  fcode[3] = '\0';
  return fcode;
}

gint16 planet_get_mines(Planet *planet) {
  return planet->pdata->mines;
}

gint16 planet_get_factories(Planet *planet) {
  return planet->pdata->factories;
}

gint16 planet_get_defense_posts(Planet *planet) {
  return planet->pdata->defense_posts;
}

gint32 planet_get_mined_neutronium(Planet *planet) {
  return planet->pdata->mined_neutronium;
}

gint32 planet_get_mined_tritanium(Planet *planet) {
  return planet->pdata->mined_tritanium;
}

gint32 planet_get_mined_duranium(Planet *planet) {
  return planet->pdata->mined_duranium;
}

gint32 planet_get_mined_molybdenum(Planet *planet) {
  return planet->pdata->mined_molybdenum;
}

gint32 planet_get_colonists(Planet *planet) {
  return planet->pdata->colonists;
}

gint32 planet_get_supplies(Planet *planet) {
  return planet->pdata->supplies;
}

gint32 planet_get_megacredits(Planet *planet) {
  return planet->pdata->megacredits;
}

gint32 planet_get_ground_neutronium(Planet *planet) {
  return planet->pdata->ground_neutronium;
}

gint32 planet_get_ground_tritanium(Planet *planet) {
  return planet->pdata->ground_tritanium;
}

gint32 planet_get_ground_duranium(Planet *planet) {
  return planet->pdata->ground_duranium;
}

gint32 planet_get_ground_molybdenum(Planet *planet) {
  return planet->pdata->ground_molybdenum;
}

gint16 planet_get_dens_neutronium(Planet *planet) {
  return planet->pdata->dens_neutronium;
}

gint16 planet_get_dens_tritanium(Planet *planet) {
  return planet->pdata->dens_tritanium;
}

gint16 planet_get_dens_duranium(Planet *planet) {
  return planet->pdata->dens_duranium;
}

gint16 planet_get_dens_molybdenum(Planet *planet) {
  return planet->pdata->dens_molybdenum;
}

gint16 planet_get_tax_colonists(Planet *planet) {
  return planet->pdata->tax_colonists;
}

gint16 planet_get_tax_natives(Planet *planet) {
  return planet->pdata->tax_natives;
}

gint16 planet_get_happiness_colonists(Planet *planet) {
  return planet->pdata->happiness_colonists;
}

gint16 planet_get_happiness_natives(Planet *planet) {
  return planet->pdata->happiness_natives;
}

gchar *planet_get_native_spi(Planet *planet) {
  gchar *spi[10];
	
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
  return planet->pdata->natives;
}

gchar *planet_get_native_race(Planet *planet) {
  gchar *race[10];

  race[0] = _("none");
  race[1] = _("Humanoid");
  race[2] = _("Bovinoid");
  race[3] = _("Reptilian");
  race[4] = _("Avian");
  race[5] = _("Amorphous");
  race[6] = _("Insectoid");
  race[7] = _("Amphibian");
  race[8] = _("Ghipsoldal");
  race[9] = _("Siliconoid");
	
  return race[planet->pdata->native_race];
}

gint16 planet_get_temperature(Planet *planet) 
{
  return planet->pdata->temperature;
}

gint16 planet_get_temperature_f(Planet *planet) 
{
  return 100 - planet_get_temperature(planet);
}

gchar *planet_get_temperature_str(Planet *planet) {
  gint16 temp = planet_get_temperature(planet);
	
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
  return planet->pdata->build_base;
}

gboolean planet_is_mine(Planet *planet)
{
  if(planet->owner == game_get_race()) {
    return TRUE;
  } else {
    return FALSE;
  }
}

gboolean planet_valid_coords(Planet *planet) 
{
  if (planet->x <= STARCHART_X_MAX && planet->x >= STARCHART_X_MIN &&
      planet->y <= STARCHART_Y_MAX && planet->y >= STARCHART_Y_MIN) {
    return TRUE;
  } else {
    return FALSE;
  }
}

gint planet_what_is(Planet *planet)
{
  if(planet_get_owner(planet) == game_get_race())
    {
      return IS_MINE;
    } else {
      return IS_ENEMY; // FIXME: Check for allied planets!!!
    }
}
