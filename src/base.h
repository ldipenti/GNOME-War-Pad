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

#ifndef BASE_H
#define BASE_H

#include "vp_types.h"
#include "race.h"

Base *base_get(GHashTable *list, gint base_id);

gint16 base_get_id(Base *base);
enum races base_get_owner(Base *base);
gint16 base_get_defense(Base *base);
gint16 base_get_damage(Base *base);
gint16 base_get_engines_tech(Base *base);
gint16 base_get_hulls_tech(Base *base);
gint16 base_get_beams_tech(Base *base);
gint16 base_get_torps_tech(Base *base);

gint16* base_get_storage_engines(Base *base);
gint16* base_get_storage_hulls(Base *base);
gint16* base_get_storage_beams(Base *base);
gint16* base_get_storage_torp_launchers(Base *base);
gint16* base_get_storage_torps(Base *base);

gint16 base_get_fighters(Base *base);

gint16 base_get_id_ship(Base *base);
gint16 base_get_ship_action(Base *base);

gint16 base_get_mission(Base *base);

gint16 base_get_build_ship_type(Base *base);
gint16 base_get_build_engine_type(Base *base);
gint16 base_get_build_beam_type(Base *base);
gint16 base_get_build_beam_count(Base *base);
gint16 base_get_build_torp_type(Base *base);
gint16 base_get_build_torp_count(Base *base);

#endif
