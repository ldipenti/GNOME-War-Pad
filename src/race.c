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

#include <gnome.h>

#include "race.h"

gchar *race_get_name(enum races racenum)
{
  switch (racenum) {
  case RACE_FEDS:
    return _("The Federation");
    break;
  case RACE_LIZARDS:
    return _("The Lizards");
    break;
  case RACE_BIRDMEN:
    return _("The Birdmen");
    break;
  case RACE_FASCISTS:
    return _("The Fascists");
    break;
  case RACE_PRIVATEERS:
    return _("The Privateers");
    break;
  case RACE_CYBORGS:
    return _("The Cyborgs");
    break;
  case RACE_CRYSTALLINE:
    return _("The Crystalline");
    break;
  case RACE_EVILS:
    return _("The Evil Empire");
    break;
  case RACE_ROBOTS:
    return _("The Robots");
    break;
  case RACE_REBELS:
    return _("The Rebels");
    break;
  case RACE_COLONIES:
    return _("The Colonies");
    break;
  default:
    return NULL;
  }
}

gdouble race_get_tax_rate_colonists(GwpPlanet *planet)
{
  gdouble ret;

  switch(gwp_planet_get_owner(planet)) {
  case RACE_FEDS:
    ret = 2.0;
    break;
  default:
    ret = 1.0;
    break;
  }

  return ret;
}
