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

#include <math.h>
#include "gwp-starchart.h"

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
  /* ... FIXME: complete this! */
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
gint gwp_starchart_calculate_width (GwpStarchart *self)
{
  g_assert (GWP_IS_STARCHART(self));
  return (gwp_starchart_get_x_max(self) - gwp_starchart_get_x_min(self));
}

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
