/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002,2003 Lucas Di Pentima <lucas@lunix.com.ar>
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

/* Base utility functions */

#include <gnome.h>

#include "base.h"
#include "vp_types.h"
#include "global.h"
#include "race.h"

/* Returns the base with id */
Base *base_get(GHashTable *list, gint base_id)
{
  return (Base *) g_hash_table_lookup(list, (gconstpointer)base_id);
}


/* Base GET functions */
gint16 base_get_id(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->id;
}

enum races base_get_owner(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->owner;
}

gint16 base_get_defense(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->defense;
}

gint16 base_get_damage(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->damage;
}

gint16 base_get_engines_tech(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->engines_tech;
}

gint16 base_get_hulls_tech(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->hulls_tech;
}

gint16 base_get_beams_tech(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->beams_tech;
}

gint16 base_get_torps_tech(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->torps_tech;
}

gint16* base_get_storage_engines(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->storage_engines;
}

gint16* base_get_storage_hulls(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->storage_hulls;
}

gint16* base_get_storage_beams(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->storage_beams;
}

gint16* base_get_storage_torp_launchers(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->storage_torp_launchers;
}

gint16* base_get_storage_torps(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->storage_torps;
}

gint16 base_get_fighters(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->fighters;
}

gint16 base_get_id_ship(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->id_ship;
}

gint16 base_get_ship_action(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->ship_action;
}

gint16 base_get_mission(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->mission;
}

gint16 base_get_build_ship_type(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->build_ship_type;
}

gint16 base_get_build_engine_type(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->build_engine_type;
}

gint16 base_get_build_beam_type(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->build_beam_type;
}

gint16 base_get_build_beam_count(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->build_beam_count;
}

gint16 base_get_build_torp_type(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->build_torp_type;
}

gint16 base_get_build_torp_count(Base *base)
{
  g_assert(base != NULL);
  return base->bdata->build_torp_count;
}
