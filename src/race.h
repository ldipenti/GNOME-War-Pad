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

#ifndef RACE_H
#define RACE_H

#include <gnome.h>

#include "planet.h"

enum spi {
  SPI_NONE,
  SPI_ANARCHY,
  SPI_PRE_TRIBAL,
  SPI_EARLY_TRIBAL,
  SPI_TRIBAL,
  SPI_FEUDAL,
  SPI_MONARCHY,
  SPI_REPRESENTATIVE,
  SPI_PARTICIPATORY,
  SPI_UNITY
};

enum natives {
  NATIVE_NONE,
  NATIVE_HUMANOID,
  NATIVE_BOVINOID,
  NATIVE_REPTILIAN,
  NATIVE_AVIAN,
  NATIVE_AMORPHOUS,
  NATIVE_INSECTOID,
  NATIVE_AMPHIBIAN,
  NATIVE_GHIPSOLDAL,
  NATIVE_SILICONOID
};

enum races {
  RACE_NONE,
  RACE_FEDS,
  RACE_LIZARDS,
  RACE_BIRDMEN,
  RACE_FASCISTS,
  RACE_PRIVATEERS,
  RACE_CYBORGS,
  RACE_CRYSTALLINE,
  RACE_EVILS,
  RACE_ROBOTS,
  RACE_REBELS,
  RACE_COLONIES
};

gchar *race_get_name(enum races racenum);
gdouble race_get_tax_rate_colonists(Planet *planet);

#endif
