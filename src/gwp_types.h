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

/*
 * This file contains structures and datatypes that GWP uses to provide 
 * more functionality to VGA Planets. This datatypes are not provided
 * from VP, so it's probably that other clients won't be able to use them.
 */

#ifndef GWP_TYPES_H
#define GWP_TYPES_H

#include <gnome.h>

#include "vp_types.h"

GnomeCanvas * starchart_mini_get_canvas(void);
void starchart_mini_set_canvas(GnomeCanvas * canvas);
GnomeCanvasGroup * starchart_mini_get_grp_root(void);
void starchart_mini_set_grp_root(GnomeCanvasGroup * group);
GnomeCanvasItem * starchart_mini_get_zone(void);
void starchart_mini_set_zone(GnomeCanvasItem * zone);

GnomeCanvas * starchart_get_canvas(void);
void starchart_set_canvas(GnomeCanvas * canvas);
GnomeCanvasGroup * starchart_get_grp_root(void);
void starchart_set_grp_root(GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_grid(void);
void starchart_set_grp_grid(GnomeCanvasGroup * group);

GnomeCanvasGroup * starchart_get_grp_planet_names (void);
void starchart_set_grp_planet_names (GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_scanner_area (void);
void starchart_set_grp_scanner_area (GnomeCanvasGroup * group);

GnomeCanvasGroup * starchart_get_grp_planets (void);
void starchart_set_grp_planets (GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_ships (void);
void starchart_set_grp_ships (GnomeCanvasGroup * group);

GnomeCanvasGroup * starchart_get_grp_minefields (void);
void starchart_set_grp_minefields (GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_ion_storms (void);
void starchart_set_grp_ion_storms (GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_constellations (void);
void starchart_set_grp_constellations (GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_misc (void);
void starchart_set_grp_misc (GnomeCanvasGroup * group);

typedef struct _Fleet Fleet;
struct _Fleet {
  gint fleet_num; /* Fleet id */
  GSList *ships_in_fleet; /* First Ship is fleet leader */
  GString *fleet_name;
  GString *fleet_note;
};

typedef struct _Starchart Starchart;
struct _Starchart {
  GnomeCanvas *canvas;
  
  GnomeCanvasGroup *grp_root;
  GnomeCanvasGroup *grp_grid;
  
  GnomeCanvasGroup *grp_planet_names;
  GnomeCanvasGroup *grp_scanner_area;

  GnomeCanvasGroup *grp_planets;
  GnomeCanvasGroup *grp_ships;

  GnomeCanvasGroup *grp_minefields;
  GnomeCanvasGroup *grp_ion_storms;
  GnomeCanvasGroup *grp_constellations;
  GnomeCanvasGroup *grp_misc; /**< For misc things like the distance calc */
};

typedef struct _StarchartMini StarchartMini;
struct _StarchartMini {
  GnomeCanvas *canvas;
  GnomeCanvasGroup *grp_root;
  GnomeCanvasItem *zone;
};

#endif
