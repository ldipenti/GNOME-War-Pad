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

#include "global.h"

/*******************************************/
/************** STARCHART MINI *************/
/*******************************************/

GnomeCanvas * starchart_mini_get_canvas(void)
{
  return starchart_mini.canvas;
}

void starchart_mini_set_canvas(GnomeCanvas * canvas)
{
  starchart_mini.canvas = canvas;
}

GnomeCanvasGroup * starchart_mini_get_grp_root(void)
{
  return starchart_mini.grp_root;
}

void starchart_mini_set_grp_root(GnomeCanvasGroup * group)
{
  starchart_mini.grp_root = group;
}

GnomeCanvasItem * starchart_mini_get_zone(void)
{
  return starchart_mini.zone;
}

void starchart_mini_set_zone(GnomeCanvasItem * zone)
{
  starchart_mini.zone = zone;
}


/*******************************************/
/**************** STARCHART ****************/
/*******************************************/

GnomeCanvas * starchart_get_canvas(void)
{
  return starchart.canvas;
}

void starchart_set_canvas(GnomeCanvas * canvas)
{
  starchart.canvas = canvas;
}

GnomeCanvasGroup * starchart_get_grp_root(void)
{
  return starchart.grp_root;
}

void starchart_set_grp_root(GnomeCanvasGroup * group)
{
  starchart.grp_root = group;
}

GnomeCanvasGroup * starchart_get_grp_grid(void)
{
  return starchart.grp_grid;
}

void starchart_set_grp_grid(GnomeCanvasGroup * group)
{
  starchart.grp_grid = group;
}

GnomeCanvasGroup * starchart_get_grp_planet_names(void)
{
  return starchart.grp_planet_names;
}

void starchart_set_grp_planet_names(GnomeCanvasGroup * group)
{
  starchart.grp_planet_names = group;
}

GnomeCanvasGroup * starchart_get_grp_scanner_area(void)
{
  return starchart.grp_scanner_area;
}

void starchart_set_grp_scanner_area(GnomeCanvasGroup * group)
{
  starchart.grp_scanner_area = group;
}

GnomeCanvasGroup * starchart_get_grp_scanner_area_sensor(void)
{
  return starchart.grp_scanner_area_sensor;
}

void starchart_set_grp_scanner_area_sensor(GnomeCanvasGroup * group)
{
  starchart.grp_scanner_area_sensor = group;
}

GnomeCanvasGroup * starchart_get_grp_planets(void)
{
  return starchart.grp_planets;
}

void starchart_set_grp_planets(GnomeCanvasGroup * group)
{
  starchart.grp_planets = group;
}

GnomeCanvasGroup * starchart_get_grp_ships(void)
{
  return starchart.grp_ships;
}

void starchart_set_grp_ships(GnomeCanvasGroup * group)
{
  starchart.grp_ships = group;
}

GnomeCanvasGroup * starchart_get_grp_minefields (void)
{
  return starchart.grp_minefields;
}

void starchart_set_grp_minefields (GnomeCanvasGroup * group)
{
  starchart.grp_minefields = group;
}

GnomeCanvasGroup * starchart_get_grp_ion_storms (void)
{
  return starchart.grp_ion_storms;
}

void starchart_set_grp_ion_storms (GnomeCanvasGroup * group)
{
  starchart.grp_ion_storms = group;
}

GnomeCanvasGroup * starchart_get_grp_constellations (void)
{
  return starchart.grp_constellations;
}

void starchart_set_grp_constellations (GnomeCanvasGroup * group)
{
  starchart.grp_constellations = group;
}

GnomeCanvasGroup * starchart_get_grp_misc (void)
{
  return starchart.grp_misc;
}

void starchart_set_grp_misc (GnomeCanvasGroup * group)
{
  starchart.grp_misc = group;
}
