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
    Revision 1.3  2005/05/31 13:17:39  ldipenti
    Feature: Added CVS metadata on source files

*/

#ifndef MISSION_H
#define MISSION_H

#include <gnome.h>

enum missions {
  MISSION_NONE,
  MISSION_EXPLORE,
  MISSION_MINE_SWEEP,
  MISSION_LAY_MINES,
  MISSION_KILL,
  MISSION_SENSOR_SWEEP,
  MISSION_COLONIZE,
  MISSION_TOW,
  MISSION_INTERCEPT,
  MISSION_SPECIAL,
  MISSION_CLOAK,
  MISSION_BEAM_UP_NEU,
  MISSION_BEAM_UP_DUR,
  MISSION_BEAM_UP_TRI,
  MISSION_BEAM_UP_MOL,
  MISSION_BEAM_UP_SUP
};

enum specials {
  SPECIAL_NONE,
  SPECIAL_SUPER_REFIT,
  SPECIAL_HISS,
  SPECIAL_SUPER_SPY,
  SPECIAL_PILLAGE,
  SPECIAL_ROB_SHIP,
  SPECIAL_SELF_REPAIR,
  SPECIAL_LAY_WEB_MINES,
  SPECIAL_DARK_SENSE,
  SPECIAL_ROBOT_BUILD_FIGHTERS,
  SPECIAL_GROUND_ATTACK,
  SPECIAL_COLONIES_BUILD_FIGHTERS
};

enum sb_missions {
  SB_MISSION_NONE,
  SB_MISSION_REFUEL,
  SB_MISSION_MAX_DEFENSE,
  SB_MISSION_LOAD_TORPS,
  SB_MISSION_UNLOAD_SHIPS,
  SB_MISSION_REPAIR_BASE,
  SB_MISSION_FORCE_SURRENDER
};

gchar * mission_special_get_name (enum specials mission);
gchar * mission_get_name (enum missions mission);
gchar * mission_sb_get_name (enum sb_missions mission);

#endif
