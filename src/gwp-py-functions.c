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

/*
 * This file contains the functions that will be mapped to the Python
 * environment, but don't belong to any defined class.
 */

#include "gwp-py-functions.h"
#include "global.h"


/************************/
/**** Ship functions ****/
/************************/
GwpShip * ship_get_by_id (gint id) 
{
  return gwp_ship_get (ship_list, id);
}

/************************/
/*** Planet functions ***/
/************************/
GwpPlanet * planet_get_by_id (gint id)
{
  return gwp_planet_get (planet_list, id);
}

