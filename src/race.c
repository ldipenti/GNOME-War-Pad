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

gchar *race_get_name(gint racenum)
{
  switch (racenum) {
  case 1:
    return "The Federation";
    break;
  case 2:
    return "The Lizards";
    break;
  case 3:
    return "The Birdmen";
    break;
  case 4:
    return "The Fascists";
    break;
  case 5:
    return "The Privateers";
    break;
  case 6:
    return "The Cyborgs";
    break;
  case 7:
    return "The Crystalline";
    break;
  case 8:
    return "The Evil Empire";
    break;
  case 9:
    return "The Robots";
    break;
  case 10:
    return "The Rebels";
    break;
  case 11:
    return "The Colonies";
    break;
  default:
    return NULL;
  }
}
