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

#include "gwp-hullspec.h"

/*
 * Private members.
 */
struct _GwpHullSpecPrivate {
  gboolean dispose_has_run;
  /* Actual data */
  gint id;
  GString *name; /* max 30 chars */
  gint picture;
  gint tritanium;
  gint duranium;
  gint molybdenum;
  gint fuel_tank;
  gint crew_size;
  gint engines;
  gint mass; /* when empty */
  gint tech_level;
  gint cargo;
  gint fighter_bays;
  gint torp_launchers; /* max value */
  gint beam_weapons; /* max value */
  gint cost; /* MC */
};

/*
 * Forward definitions.
 */
static void gwp_hullspec_init (GTypeInstance *instance, gpointer g_class);
static void gwp_hullspec_class_init (GwpHullSpecClass *klass);

GType gwp_hullspec_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpHullSpecClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_hullspec_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpHullSpec), 
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_hullspec_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpHullSpec",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_hullspec_init (GTypeInstance *instance,
			       gpointer       g_class)
{
  GwpHullSpec *self = (GwpHullSpec *)instance;
  self->priv = g_new0 (GwpHullSpecPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->id = 0;
  self->priv->name = g_string_new("");
  self->priv->picture = 0;
  self->priv->tritanium = 0;
  self->priv->duranium = 0;
  self->priv->molybdenum = 0;
  self->priv->fuel_tank = 0;
  self->priv->crew_size = 0;
  self->priv->engines = 0;
  self->priv->mass = 0;
  self->priv->tech_level = 0;
  self->priv->cargo = 0;
  self->priv->fighter_bays = 0;
  self->priv->torp_launchers = 0;
  self->priv->beam_weapons = 0;
  self->priv->cost = 0;
}

static void gwp_hullspec_dispose (GwpHullSpec *self)
{
  if(self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  g_string_free (self->priv->name, TRUE);
}

static void gwp_hullspec_finalize (GwpHullSpec *self)
{
  /* Here, complete object destruction. */
  g_free (self->priv);
}

static void gwp_hullspec_class_init (GwpHullSpecClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* Register destructor methods. */
  gobject_class->dispose = (void *) gwp_hullspec_dispose;
  gobject_class->finalize = (void *) gwp_hullspec_finalize;
}

/* 
 * Public method implementations.
 */
GwpHullSpec * gwp_hullspec_new (void)
{
  return g_object_new (gwp_hullspec_get_type (), NULL);
}

/**********************/
/* High Level methods */
/**********************/

/**
 * Returns the hull name truncated.
 *
 * Hull names can be very long, so with this function you can truncate
 * it to a given number of characters.
 *
 * @param self a GwpHullSpec.
 * @param len the maximum name length accepted.
 * @return A string containing the truncated name.
 */
gchar * gwp_hullspec_get_name_trunc (GwpHullSpec *self, gint len)
{
  g_return_val_if_fail ((GWP_IS_HULLSPEC(self) && len > 0), NULL);

  /* ...truncate hull name if it's too long */
  GString *tmp_str = g_string_new(gwp_hullspec_get_name(self));
  if (tmp_str->len > len) {
    tmp_str = g_string_truncate (tmp_str, len);
    tmp_str = g_string_append (tmp_str, "...");
  }

  return tmp_str->str;
}

/***************************/
/*  get/set boring methods */
/***************************/

gint gwp_hullspec_get_id (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));

  return self->priv->id;
}

void gwp_hullspec_set_id (GwpHullSpec *self, gint id)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (id >= 1 && id <= 105);

  self->priv->id = id;
}

gchar * gwp_hullspec_get_name (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  GString *ret = g_string_new (self->priv->name->str);

  return ret->str;
}

void gwp_hullspec_set_name (GwpHullSpec *self, gchar *name)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (name != NULL); /* FIXME: name->len <= 30 */

  self->priv->name = g_string_assign (self->priv->name, name);
}

gint gwp_hullspec_get_picture (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->picture;
}

void gwp_hullspec_set_picture (GwpHullSpec *self, gint pic)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (pic >= 0);
  self->priv->picture = pic;
}

gint gwp_hullspec_get_tritanium (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->tritanium;
}

void gwp_hullspec_set_tritanium (GwpHullSpec *self, gint m)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (m >= 0);
  self->priv->tritanium = m;
}

gint gwp_hullspec_get_duranium (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->duranium;
}

void gwp_hullspec_set_duranium (GwpHullSpec *self, gint m)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (m >= 0);
  self->priv->duranium = m;
}

gint gwp_hullspec_get_molybdenum (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->molybdenum;
}

void gwp_hullspec_set_molybdenum (GwpHullSpec *self, gint m)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (m >= 0);
  self->priv->molybdenum = m;
}

gint gwp_hullspec_get_fuel_tank (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->fuel_tank;
}

void gwp_hullspec_set_fuel_tank (GwpHullSpec *self, gint ft)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (ft > 0);
  self->priv->fuel_tank = ft;
}

gint gwp_hullspec_get_crew (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->crew_size;
}

void gwp_hullspec_set_crew (GwpHullSpec *self, gint crew)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (crew > 0);
  self->priv->crew_size = crew;
}

gint gwp_hullspec_get_engines (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->engines;
}

void gwp_hullspec_set_engines (GwpHullSpec *self, gint eng)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (eng > 0);
  self->priv->engines = eng;
}

gint gwp_hullspec_get_mass (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->mass;
}

void gwp_hullspec_set_mass (GwpHullSpec *self, gint mass)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (mass > 0);
  self->priv->mass = mass;
}

gint gwp_hullspec_get_tech_level (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->tech_level;
}

void gwp_hullspec_set_tech_level (GwpHullSpec *self, gint tl)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (tl > 0);
  self->priv->tech_level = tl;
}

gint gwp_hullspec_get_cargo (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->cargo;
}

void gwp_hullspec_set_cargo (GwpHullSpec *self, gint cargo)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (cargo >= 0);
  self->priv->cargo = cargo;
}

gint gwp_hullspec_get_fighter_bays (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->fighter_bays;
}

void gwp_hullspec_set_fighter_bays (GwpHullSpec *self, gint fb)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (fb >= 0);
  self->priv->fighter_bays = fb;
}

gint gwp_hullspec_get_torp_launchers (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->torp_launchers;
}

void gwp_hullspec_set_torp_launchers (GwpHullSpec *self, gint tl)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (tl >= 0);
  self->priv->torp_launchers = tl;
}

gint gwp_hullspec_get_beam_weapons (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->beam_weapons;
}

void gwp_hullspec_set_beam_weapons (GwpHullSpec *self, gint bw)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (bw >= 0);
  self->priv->beam_weapons = bw;
}

gint gwp_hullspec_get_cost (GwpHullSpec *self)
{
  g_assert (GWP_IS_HULLSPEC(self));
  return self->priv->cost;
}

void gwp_hullspec_set_cost (GwpHullSpec *self, gint cost)
{
  g_assert (GWP_IS_HULLSPEC(self));
  g_assert (cost > 0);
  self->priv->cost = cost;
}
