/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2004  Lucas Di Pentima <lucas@lunix.com.ar>
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
 * GwpStarchart:
 * ------------
 * This type encapsulates the inner working mechanisms of GWP's starchart,
 * trying to separate from the frontend system (today: gnomecanvas, 
 * tomorrow: who knows!).
 */

#ifndef GWP_STARCHART_H
#define GWP_STARCHART_H

#include <glib.h>
#include <glib-object.h>
#include "gwp-object.h"
#include "gwp-planet.h"
#include "gwp-ship.h"
#include "gwp-location.h"

/*
 * Type macros.
 */
typedef struct _GwpStarchart GwpStarchart;
typedef struct _GwpStarchartClass GwpStarchartClass;
typedef struct _GwpStarchartPrivate GwpStarchartPrivate;

struct _GwpStarchart {
  GObject parent;

  /* instance members */

  /* private */
  GwpStarchartPrivate *priv;
};

struct _GwpStarchartClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_TYPE_STARCHART */
GType gwp_starchart_get_type (void);

/*
 * Public methods protos.
 */
GwpStarchart * gwp_starchart_new (void);

/************************/
/* High level functions */
/************************/
gint gwp_starchart_calculate_width (GwpStarchart *self);
gint gwp_starchart_calculate_canvas_width (GwpStarchart *self);
gint gwp_starchart_calculate_quads_per_line (GwpStarchart *self);
gint gwp_starchart_calculate_total_quads (GwpStarchart *self);
gboolean gwp_starchart_has_valid_coords (GwpStarchart *self, GwpObject *obj);
gint gwp_starchart_calculate_obj_quadrant (GwpStarchart *self, GwpObject *obj);
gint gwp_starchart_calculate_quadrant (GwpStarchart *self, gdouble x, gdouble y);


/****************************/
/* Boring get/set functions */
/****************************/
gint gwp_starchart_get_x_max (GwpStarchart *self);
void gwp_starchart_set_x_max (GwpStarchart *self, gint x);
gint gwp_starchart_get_x_min (GwpStarchart *self);
void gwp_starchart_set_x_min (GwpStarchart *self, gint x);
gint gwp_starchart_get_y_max (GwpStarchart *self);
void gwp_starchart_set_y_max (GwpStarchart *self, gint y);
gint gwp_starchart_get_y_min (GwpStarchart *self);
void gwp_starchart_set_y_min (GwpStarchart *self, gint y);
gint gwp_starchart_get_valid_margin (GwpStarchart *self);
void gwp_starchart_set_valid_margin (GwpStarchart *self, gint margin);
gint gwp_starchart_get_canvas_margin (GwpStarchart *self);
void gwp_starchart_set_canvas_margin (GwpStarchart *self, gint margin);
gint gwp_starchart_get_quad_width (GwpStarchart *self);
void gwp_starchart_set_quad_width (GwpStarchart *self, gint width);
GSList *gwp_starchart_get_planets_per_quad (GwpStarchart *self, gint quad);
void gwp_starchart_set_planets_per_quad (GwpStarchart *self, GwpPlanet *planet);
GSList *gwp_starchart_get_ships_per_quad (GwpStarchart *self, gint quad);
void gwp_starchart_set_ships_per_quad (GwpStarchart *self, GwpShip *ship);
GSList *gwp_starchart_get_locations_per_quad (GwpStarchart *self, gint quad);
void gwp_starchart_set_locations_per_quad (GwpStarchart *self, GwpLocation *loc);
GwpPlanet *gwp_starchart_select_nearest_planet (GwpStarchart *self, gint x, gint y);
GwpPlanet *gwp_starchart_select_planet (GwpStarchart *self, gint planet_id);



/* Wrapper functions to starchart.c */
void gwp_starchart_center_around (GwpStarchart *self, GwpObject *obj);


/*
 * Stardard defines.
 */
#define GWP_TYPE_STARCHART            (gwp_starchart_get_type())
#define GWP_STARCHART(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_STARCHART, GwpStarchart))
#define GWP_STARCHART_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_STARCHART, GwpStarchartClass))
#define GWP_IS_STARCHART(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_STARCHART))
#define GWP_IS_STARCHART_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_STARCHART))
#define GWP_STARCHART_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_STARCHART, GwpStarchartClass))

#endif
