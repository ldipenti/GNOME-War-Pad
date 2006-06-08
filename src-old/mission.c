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

#include <gnome.h>

#include "mission.h"

gchar * mission_special_get_name (enum specials mission)
{
  switch (mission) {
  case SPECIAL_NONE:
    return _("No mission");
    break;
  case SPECIAL_SUPER_REFIT:
    return _("Super Refit");
    break;
  case SPECIAL_HISS:
    return _("Hisssssss!");
    break;
  case SPECIAL_SUPER_SPY:
    return _("Super Spy");
    break;
  case SPECIAL_PILLAGE:
    return _("Pillage Planet");
    break;
  case SPECIAL_ROB_SHIP:
    return _("Rob Ship");
    break;
  case SPECIAL_SELF_REPAIR:
    return _("Self Repair");
    break;
  case SPECIAL_LAY_WEB_MINES:
    return _("Lay Web Mines");
    break;
  case SPECIAL_DARK_SENSE:
    return _("Dark Sense");
    break;
  case SPECIAL_ROBOT_BUILD_FIGHTERS:
    return _("Build Fighters");
    break;
  case SPECIAL_GROUND_ATTACK:
    return _("Ground Attack");
    break;
  case SPECIAL_COLONIES_BUILD_FIGHTERS:
    return _("Build Fighters");
    break;
  default:
    return NULL;
  }
}

gchar * mission_get_name (enum missions mission)
{
  switch (mission) {
  case MISSION_NONE:
    return _("No mission");
    break;
  case MISSION_EXPLORE:
    return _("Explore");
    break;
  case MISSION_MINE_SWEEP:
    return _("Mine sweep");
    break;
  case MISSION_LAY_MINES:
    return _("Lay mines");
    break;
  case MISSION_KILL:
    return _("Kill");
    break;
  case MISSION_SENSOR_SWEEP:
    return _("Sensor sweep");
    break;
  case MISSION_COLONIZE:
    return _("Colonize");
    break;
  case MISSION_TOW:
    return _("Tow");
    break;
  case MISSION_INTERCEPT:
    return _("Intercept");
    break;
  case MISSION_SPECIAL:
    return _("Special");
    break;
  case MISSION_CLOAK:
    return _("Cloak");
    break;
  case MISSION_BEAM_UP_NEU:
    return _("Beam up fuel");
    break;
  case MISSION_BEAM_UP_DUR:
    return _("Beam up duranium");
    break;
  case MISSION_BEAM_UP_TRI:
    return _("Beam up tritanium");
    break;
  case MISSION_BEAM_UP_MOL:
    return _("Beam up molybdenum");
    break;
  case MISSION_BEAM_UP_SUP:
    return _("Beam up supplies");
    break;
  default:
    return NULL;
  }
}

gchar * mission_sb_get_name (enum sb_missions mission)
{
  switch (mission) {
  case SB_MISSION_NONE:
    return _("No mission");
    break;
  case SB_MISSION_REFUEL:
    return _("Refuel ships");
    break;
  case SB_MISSION_MAX_DEFENSE:
    return _("Maximize defense");
    break;
  case SB_MISSION_LOAD_TORPS:
    return _("Load torpedoes on ships");
    break;
  case SB_MISSION_UNLOAD_SHIPS:
    return _("Unload ships");
    break;
  case SB_MISSION_REPAIR_BASE:
    return _("Repair starbase");
    break;
  case SB_MISSION_FORCE_SURRENDER:
    return _("Force a surrender");
    break;
  default:
    return NULL;
  }
}
