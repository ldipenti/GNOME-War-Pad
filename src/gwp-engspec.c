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
#include "gwp-engspec.h"

/*
 * Private members.
 */
struct _GwpEngSpecPrivate {
  gboolean dispose_has_run;
  /* Actual data */
  gint id;
  GString *name; /* max 20 chars */
  gint cost; /* MC */
  gint tritanium;
  gint duranium;
  gint molybdenum;
  gint tech_level;
  gint32 fuel_usage[9]; /* fuel used to travel 1 month at the given speed,
			   for each warp factor, for a 100000 kt ship */
};

/*
 * Forward definitions.
 */
static void gwp_engspec_init (GTypeInstance *instance, gpointer g_class);
static void gwp_engspec_class_init (GwpEngSpecClass *klass);

GType gwp_engspec_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpEngSpecClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_engspec_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpEngSpec),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_engspec_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpEngSpec",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_engspec_init (GTypeInstance *instance,
			      gpointer       g_class)
{
  gint i;
  GwpEngSpec *self = (GwpEngSpec *)instance;
  self->priv = g_new0 (GwpEngSpecPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->id = 0;
  self->priv->name = g_string_new ("");
  self->priv->cost = 0;
  self->priv->tritanium = 0;
  self->priv->duranium = 0;
  self->priv->molybdenum = 0;
  self->priv->tech_level = 0;
  for (i = 0; i < 9; i++) {
    self->priv->fuel_usage[i] = 0;
  }
}

static void gwp_engspec_dispose (GwpEngSpec *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  g_string_free (self->priv->name, TRUE);
}

static void gwp_engspec_finalize (GwpEngSpec *self)
{
  /* Here, complete object destruction. */
  g_free (self->priv);
}

static void gwp_engspec_class_init (GwpEngSpecClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* Register destructor methods. */
  gobject_class->dispose = gwp_engspec_dispose;
  gobject_class->finalize = gwp_engspec_finalize;
}

/*
 * Public method implementations.
 */
GwpEngSpec * gwp_engspec_new (void)
{
  return g_object_new (gwp_engspec_get_type (), NULL);
}

/**********************/
/* high level methods */
/**********************/

/* 
   Fuel used to travel "d" LY with a ship of "m" kt at speed "v":

         d * m * X(v)             d
   N = ----------------    t = -------
        v * v * 100000          v * v

   N is the fuel required, t the time required and X(v) is the value loaded.
   When travelling more that 1 month, the fuel usage must be recalculated for
   every month because as the fuel runs out, the total ship's mass changes.
*/

/** 
 * Calculates the fuel used by engines depending of certain data.
 * This function is intended to be used by the GwpShip class, all data
 * needed must come from an existing or theoretical ship.
 * @param self a GwpEngSpec
 * @param dist the distance needed to travel.
 * @param speed the warp factor set on the current engine.
 * @param mass the total mass the engine must move.
 * @return The amount of neutronium needed for the travel.
 */
gint gwp_engspec_get_fuel_usage_full (GwpEngSpec *self, gdouble dist,
				      gint speed, gint mass)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (dist >= 0.0);
  g_assert (speed >= 0 && speed <= 9);
  g_assert (mass > 0);

  gint ret = 0;

  /* Avoid division by zero problem...*/
  if (speed == 0) {
    ret = 0;
  } else {
    gint eta = ceil(dist / (speed * speed));
    
    /* If is one month journey, do simple calculation */
    if (eta <= 1) {
      ret = (mass * gwp_engspec_get_fuel_usage(self, speed)) / 100000;
    }
    /* If the journey is long, recalculate mass */
    else {
      gint i;
      gint usage = 0;
      for (i = eta; i > 0; i--) {
	usage = (mass * gwp_engspec_get_fuel_usage(self, speed)) / 100000;
	mass -= usage;
	ret += usage;
      }
    }
  }
  return ret;
}

/**************************/
/* get/set boring methods */
/**************************/

gint gwp_engspec_get_id (GwpEngSpec *self)
{
  g_assert (GWP_IS_ENGSPEC(self));

  return self->priv->id;
}

void gwp_engspec_set_id (GwpEngSpec *self, gint id)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (id >= 1 && id <= 9);

  self->priv->id = id;
}

GString * gwp_engspec_get_name (GwpEngSpec *self)
{
  g_assert (GWP_IS_ENGSPEC(self));

  return g_string_new (self->priv->name->str);
}

void gwp_engspec_set_name (GwpEngSpec *self, GString *name)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (name != NULL && name->len <= 20);

  self->priv->name = g_string_assign (self->priv->name, name->str);
}

gint gwp_engspec_get_cost (GwpEngSpec *self)
{
  g_assert (GWP_IS_ENGSPEC(self));

  return self->priv->cost;
}

void gwp_engspec_set_cost (GwpEngSpec *self, gint cost)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (cost >= 0);

  self->priv->cost = cost;
}

gint gwp_engspec_get_tritanium (GwpEngSpec *self)
{
  g_assert (GWP_IS_ENGSPEC(self));

  return self->priv->tritanium;
}

void gwp_engspec_set_tritanium (GwpEngSpec *self, gint tri)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (tri >= 0);

  self->priv->tritanium = tri;
}

gint gwp_engspec_get_duranium (GwpEngSpec *self)
{
  g_assert (GWP_IS_ENGSPEC(self));

  return self->priv->duranium;
}

void gwp_engspec_set_duranium (GwpEngSpec *self, gint dur)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (dur >= 0);

  self->priv->duranium = dur;
}

gint gwp_engspec_get_molybdenum (GwpEngSpec *self)
{
  g_assert (GWP_IS_ENGSPEC(self));

  return self->priv->molybdenum;
}

void gwp_engspec_set_molybdenum (GwpEngSpec *self, gint mol)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (mol >= 0);

  self->priv->molybdenum = mol;
}

gint gwp_engspec_get_tech_level (GwpEngSpec *self)
{
  g_assert (GWP_IS_ENGSPEC(self));

  return self->priv->tech_level;
}

void gwp_engspec_set_tech_level (GwpEngSpec *self, gint tl)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (tl >= 1 && tl <= 10);

  self->priv->tech_level = tl;
}

gint gwp_engspec_get_fuel_usage (GwpEngSpec *self, gint warp)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (warp >= 0 && warp <= 9);

  if (warp > 0) {
    return self->priv->fuel_usage[warp-1];
  } else {
    return 0;
  }
}

void gwp_engspec_set_fuel_usage (GwpEngSpec *self, gint warp, gint fuel)
{
  g_assert (GWP_IS_ENGSPEC(self));
  g_assert (warp >= 1 && warp <= 9);
  g_assert (fuel >= 0);

  self->priv->fuel_usage[warp-1] = fuel;
}
