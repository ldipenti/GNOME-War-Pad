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

GnomeCanvasGroup * starchart_get_grp_planet_names(void);
void starchart_set_grp_planet_names(GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_planets_mine(void);
void starchart_set_grp_planets_mine(GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_planets_enemy(void);
void starchart_set_grp_planets_enemy(GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_planets_allied(void);
void starchart_set_grp_planets_allied(GnomeCanvasGroup * group);

GnomeCanvasGroup * starchart_get_grp_ships_mine(void);
void starchart_set_grp_ships_mine(GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_ships_enemy(void);
void starchart_set_grp_ships_enemy(GnomeCanvasGroup * group);
GnomeCanvasGroup * starchart_get_grp_ships_allied(void);
void starchart_set_grp_ships_allied(GnomeCanvasGroup * group);

void starchart_set_grid(gboolean state);
gboolean starchart_get_grid(void);
gboolean starchart_toggle_grid(void);

typedef struct _Fleet Fleet;
struct _Fleet {
  gint fleet_num; /* Fleet id */
  GSList *ships_in_fleet; /* First Ship is fleet leader */
  GString *fleet_name;
  GString *fleet_note;
};

typedef struct _Starchart Starchart;
struct _Starchart {
  gboolean grid;
  GnomeCanvas *canvas;
  
  GnomeCanvasGroup *grp_root;
  GnomeCanvasGroup *grp_grid;
  
  GnomeCanvasGroup *grp_planet_names;
  GnomeCanvasGroup *grp_planets_mine;
  GnomeCanvasGroup *grp_planets_enemy;
  GnomeCanvasGroup *grp_planets_allied;
  
  GnomeCanvasGroup *grp_ships_mine;
  GnomeCanvasGroup *grp_ships_enemy;
  GnomeCanvasGroup *grp_ships_allied;	
};

typedef struct _StarchartMini StarchartMini;
struct _StarchartMini {
  GnomeCanvas *canvas;
  GnomeCanvasGroup *grp_root;
  GnomeCanvasItem *zone;
};

#endif
