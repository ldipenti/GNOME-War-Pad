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
 * NOTE:
 * ----
 * This file implements GwpStarchart class, intended to represent the
 * starchart's data model within GWP. This class should be graphic
 * independent, so any concrete actions on some graphic technology
 * should be coded on gwp-starchart-ui.[ch] files, and those functions
 * should be called from abstract wrappers declared here.
 */

#include <math.h>
#include "global.h"
#include "gwp-starchart.h"
#include "starchart.h"
#include "vp_utils.h"


/* Private methods prototypes. */
static void gwp_starchart_set_object_per_quad (GwpStarchart *self,
					       GHashTable *list, 
					       GwpObject *obj);

/*
 * Private members.
 */
struct _GwpStarchartPrivate {
  gboolean dispose_has_run; /**< Control variable. */
  gint x_min; /**< Minimum X value. */
  gint x_max; /**< Maximum X value. */
  gint y_min; /**< Minimum Y value. */
  gint y_max; /**< Maximum Y value. */
  gint valid_margin; /**< Starchart valid coords margin in LY. */
  gint canvas_margin; /**< Canvas margin in LY. */
  gint quad_width; /**< Quadrant with in LY. */
  GHashTable *planets_per_quad; /**< Planet list per quadrant. */
  GHashTable *ships_per_quad; /**< Ship list per quadrant. */
  GHashTable *locations_per_quad; /**< Location list per quadrant. */
};

/*
 * forward definitions.
 */
static void gwp_starchart_init (GTypeInstance *instance, gpointer g_class);
static void gwp_starchart_class_init (GwpStarchartClass *klass);

GType gwp_starchart_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpStarchartClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_starchart_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpStarchart),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_starchart_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpStarchart",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_starchart_init (GTypeInstance *instance,
				gpointer       g_class)
{
  GwpStarchart *self = (GwpStarchart *)instance;
  self->priv = g_new0 (GwpStarchartPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->x_min = 1000;
  self->priv->x_max = 3000;
  self->priv->y_min = 1000;
  self->priv->y_max = 3000;
  self->priv->valid_margin = 150;
  self->priv->canvas_margin = 500;
  self->priv->quad_width = 100;
  self->priv->planets_per_quad = g_hash_table_new (NULL, NULL);
  self->priv->ships_per_quad = g_hash_table_new (NULL, NULL);
  self->priv->locations_per_quad = g_hash_table_new (NULL, NULL);
}

static void gwp_starchart_dispose (GwpStarchart *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  /* ... FIXME: complete this! 
     
  We have to unref all the hash tables and lists!!
  
  */
}

static void gwp_starchart_finalize (GwpStarchart *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_starchart_class_init (GwpStarchartClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* Register destructor methods. */
  gobject_class->dispose = (void *)gwp_starchart_dispose;
  gobject_class->finalize = (void *)gwp_starchart_finalize;
}

/*
 * Public method implementations.
 */
GwpStarchart * gwp_starchart_new (void)
{
  return g_object_new (gwp_starchart_get_type (), NULL);
}

/************************/
/* High level functions */
/************************/

/**
 * Calculates the starchart's width in LY.
 *
 * @param self a GwpStarchart.
 * @return Starchart's width in LY.
 */
gint gwp_starchart_calculate_width (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return (gwp_starchart_get_x_max(self) - gwp_starchart_get_x_min(self));
}

/**
 * Calculates the canvas width in pixels.
 *
 * @param self a GwpStarchart.
 * @return The canvas width in pixels.
 */
gint gwp_starchart_calculate_canvas_width (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return (gwp_starchart_calculate_width(self) + 
	  (gwp_starchart_get_canvas_margin(self) * 2));
}

gint gwp_starchart_calculate_quads_per_line (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return (gwp_starchart_calculate_canvas_width(self) /
	  gwp_starchart_get_quad_width(self));
}

gint gwp_starchart_calculate_total_quads (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return (pow(gwp_starchart_calculate_quads_per_line(self), 2));
}

gboolean gwp_starchart_has_valid_coords (GwpStarchart *self, GwpObject *obj)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (GWP_IS_OBJECT(obj));

  gboolean ret = FALSE;
  gint margin = gwp_starchart_get_valid_margin (self);
  gint x, y;
  gint valid_x_max, valid_x_min;
  gint valid_y_max, valid_y_min;

  x = gwp_object_get_x_coord (obj);
  y = gwp_object_get_y_coord (obj);
  valid_x_max = gwp_starchart_get_x_max (self) + margin;
  valid_x_min = gwp_starchart_get_x_min (self) - margin;
  valid_y_max = gwp_starchart_get_y_max (self) + margin;
  valid_y_min = gwp_starchart_get_y_min (self) - margin;
  
  if ( (x <= valid_x_max) && (x >= valid_x_min) &&
       (y <= valid_y_max) && (y >= valid_y_min) ) {
    ret = TRUE;
  }

  return ret;
}

/**
 * Calculates the quadrant number where obj is on.
 *
 * @param obj the GwpObject on the starchart.
 * @return The quadrant number.
 */
gint gwp_starchart_calculate_obj_quadrant (GwpStarchart *self, GwpObject *obj)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (GWP_IS_OBJECT(obj));

  gdouble x, y;

  vp_coord_v2w (gwp_object_get_x_coord(obj), gwp_object_get_y_coord(obj),
		 &x, &y);

  return gwp_starchart_calculate_quadrant (self, x, y);
}

/**
 * Calculates the quadrant number from x,y world coords
 *
 * @param x the x coordinate (world coord).
 * @param y the y coordinate (world coord).
 */
gint gwp_starchart_calculate_quadrant (GwpStarchart *self, 
				       gdouble x, gdouble y)
{
  g_assert (GWP_IS_STARCHART(self));

  gint xi, yi;
  xi = (gint) x;
  yi = (gint) y;
  
  return ((xi / gwp_starchart_get_quad_width(self)) + 
	  ((yi / gwp_starchart_get_quad_width(self)) *
	   gwp_starchart_calculate_quads_per_line(self)));
}


/****************************/
/* Boring get/set functions */
/****************************/
gint gwp_starchart_get_x_max (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return self->priv->x_max;
}

void gwp_starchart_set_x_max (GwpStarchart *self, gint x)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (x >= 0);
  self->priv->x_max = x;
}

gint gwp_starchart_get_x_min (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return self->priv->x_min;
}

void gwp_starchart_set_x_min (GwpStarchart *self, gint x)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (x >= 0);
  self->priv->x_min = x;
}

gint gwp_starchart_get_y_max (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return self->priv->y_max;
}

void gwp_starchart_set_y_max (GwpStarchart *self, gint y)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (y >= 0);
  self->priv->y_max = y;
}

gint gwp_starchart_get_y_min (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return self->priv->y_min;
}

void gwp_starchart_set_y_min (GwpStarchart *self, gint y)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (y >= 0);
  self->priv->y_min = y;
}

gint gwp_starchart_get_valid_margin (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return self->priv->valid_margin;
}

void gwp_starchart_set_valid_margin (GwpStarchart *self, gint margin)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (margin >= 0);
  self->priv->valid_margin = margin;
}

gint gwp_starchart_get_canvas_margin (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return self->priv->canvas_margin;
}

void gwp_starchart_set_canvas_margin (GwpStarchart *self, gint margin)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (margin >= 0);
  self->priv->canvas_margin = margin;
}

gint gwp_starchart_get_quad_width (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return self->priv->quad_width;
}

void gwp_starchart_set_quad_width (GwpStarchart *self, gint width)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (width > 0); /* FIXME: check for quad not being wider than
			   starchart. */
  self->priv->quad_width = width;
}

/**
 * Get the planets list from a given quadrant.
 *
 * @param self the GwpStarchart object.
 * @param quad the quadrant number.
 * @return A list containing planets from the quadrant.
 */
GSList *gwp_starchart_get_planets_per_quad (GwpStarchart *self, gint quad)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (quad >= 0);

  return (GSList *)g_hash_table_lookup (self->priv->planets_per_quad, 
					(gpointer)quad);
}

/**
 * Add a GwpPlanet to the quadrant list.
 *
 * @param self the GwpStarchart object.
 * @param planet the GwpPlanet to be added.
 */
void gwp_starchart_set_planets_per_quad (GwpStarchart *self, GwpPlanet *planet)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (GWP_IS_PLANET(planet));

  gwp_starchart_set_object_per_quad (self, self->priv->planets_per_quad,
				     GWP_OBJECT(planet));
}

/**
 * Get the ships list from a given quadrant.
 *
 * @param self the GwpStarchart object.
 * @param quad the quadrant number.
 * @return A list containing ships from the quadrant.
 */
GSList *gwp_starchart_get_ships_per_quad (GwpStarchart *self, gint quad)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (quad >= 0);

  return (GSList *)g_hash_table_lookup (self->priv->ships_per_quad, 
					(gpointer)quad);
}

/**
 * Add a GwpShip to the quadrant list.
 *
 * @param self the GwpStarchart object.
 * @param ship the GwpShip to be added.
 */
void gwp_starchart_set_ships_per_quad (GwpStarchart *self, GwpShip *ship)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (GWP_IS_SHIP(ship));

  gwp_starchart_set_object_per_quad (self, self->priv->ships_per_quad,
				     GWP_OBJECT(ship));
}

/**
 * Get the locations list from a given quadrant.
 *
 * @param self the GwpStarchart object.
 * @param quad the quadrant number.
 * @return A list containing locations from the quadrant.
 */
GSList *gwp_starchart_get_locations_per_quad (GwpStarchart *self, gint quad)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (quad >= 0);

  return (GSList *)g_hash_table_lookup (self->priv->locations_per_quad, 
					(gpointer)quad);
}

/**
 * Add a GwpLocation to the quadrant list.
 *
 * @param self the GwpStarchart object.
 * @param loc the GwpLocation to be added.
 */
void gwp_starchart_set_locations_per_quad (GwpStarchart *self, 
					   GwpLocation *loc)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (GWP_IS_LOCATION(loc));

  gwp_starchart_set_object_per_quad (self, self->priv->locations_per_quad,
				     GWP_OBJECT(loc));
}



/*****************************************/
/************ Private methods ************/
/*****************************************/

/**
 * Add a GwpObject to the quadrant list (private method).
 *
 * This is a private method, it's used internally by similar public
 * methods handling ship, planet, locations, etc...
 *
 * @param self the GwpStarchart object.
 * @param list the object's lists.
 * @param obj the object to be added.
 */
static void gwp_starchart_set_object_per_quad (GwpStarchart *self,
					       GHashTable *list, 
					       GwpObject *obj)
{
  g_assert (GWP_IS_STARCHART(self));
  g_assert (GWP_IS_OBJECT(obj));
  g_assert (list != NULL);

  gint quad = gwp_starchart_calculate_obj_quadrant (self, obj);

  GSList *obj_list = g_hash_table_lookup(list, (gpointer)quad);

  if (obj_list != NULL) {
    obj_list = g_slist_append (obj_list, obj);
  } else {
    obj_list = g_slist_append (obj_list, obj);
    g_hash_table_insert (list, (gpointer)quad, obj_list);
  } 
}

/**************************************************************/
/* Wrapper functions to be used until this object is complete */
/**************************************************************/
void
gwp_starchart_center_around (GwpStarchart *self, GwpObject *obj)
{
  starchart_center_around (obj);
}

GwpPlanet *
gwp_starchart_select_nearest_planet (GwpStarchart *self,
				     gint x, gint y)
{
  gdouble wx, wy;
  gint q;
  GSList *planets_nearby;
  GwpPlanet *s_planet;

  g_assert (GWP_IS_STARCHART(self));

  /* Translate coords to World system */
  vp_coord_v2w (x, y, &wx, &wy);
  q = get_quadrant(wx, wy);

  /* Search for nearest planet and select it */
  planets_nearby = starchart_get_surrounding_quads(planets_per_quad, q);

  s_planet = starchart_select_nearest_planet(gwp, planets_nearby, wx, wy);
  g_signal_emit_by_name (s_planet, "selected");

  return s_planet;
}

GwpPlanet *
gwp_starchart_select_planet (GwpStarchart *self,
			     gint planet_id)
{
  GwpPlanet *planet = NULL;

  g_assert (GWP_IS_STARCHART(self));
  g_return_val_if_fail ((planet_id >= 1 && planet_id <= 500), NULL);

  planet = gwp_planet_get (planet_list, planet_id);
  
  if (planet) {
    gwp_starchart_select_nearest_planet (self, 
					 gwp_object_get_x_coord (GWP_OBJECT(planet)),
					 gwp_object_get_y_coord (GWP_OBJECT(planet)));
    gwp_starchart_center_around (self, GWP_OBJECT(planet));

    return planet;
  } else {
    return NULL;
  }
}
