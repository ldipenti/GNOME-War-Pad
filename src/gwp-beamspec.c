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

#include "gwp-beamspec.h"

/*
 * Private members.
 */
struct _GwpBeamSpecPrivate {
  gboolean dispose_has_run;
  /* Actual data */
  gint id;
  GString *name; /* max 20 chars */
  gint cost; /* MC */
  gint tritanium;
  gint duranium;
  gint molybdenum;
  gint mass;
  gint tech_level;
  gint kill_value;
  gint damage_value;
};

/*
 * Forward definitions.
 */
static void gwp_beamspec_init (GTypeInstance *instance, gpointer g_class);
static void gwp_beamspec_class_init (GwpBeamSpecClass *klass);

GType gwp_beamspec_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpBeamSpecClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_beamspec_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpBeamSpec),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_beamspec_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpBeamSpec", 
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_beamspec_init (GTypeInstance *instance,
			       gpointer       g_class)
{
  GwpBeamSpec *self = (GwpBeamSpec *)instance;
  self->priv = g_new0 (GwpBeamSpecPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->id = 0;
  self->priv->name = g_string_new("");
  self->priv->cost = 0;
  self->priv->tritanium = 0;
  self->priv->duranium = 0;
  self->priv->molybdenum = 0;
  self->priv->mass = 0;
  self->priv->tech_level = 0;
  self->priv->kill_value = 0;
  self->priv->damage_value = 0;
}

static void gwp_beamspec_dispose (GwpBeamSpec *self)
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

static void gwp_beamspec_finalize (GwpBeamSpec *self)
{
  /* Here, complete object destruction. */
  g_free (self->priv);
}

static void gwp_beamspec_class_init (GwpBeamSpecClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* Register destructor methods. */
  gobject_class->dispose = (void *) gwp_beamspec_dispose;
  gobject_class->finalize = (void *) gwp_beamspec_finalize;
}

/* 
 * Public method implementations.
 */
GwpBeamSpec * gwp_beamspec_new (void)
{
  return g_object_new (gwp_beamspec_get_type (), NULL);
}

/**************************/
/* get/set boring methods */
/**************************/

gint gwp_beamspec_get_id (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));

  return self->priv->id;
}

void gwp_beamspec_set_id (GwpBeamSpec *self, gint id)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (id >= 1 && id <= 10);

  self->priv->id = id;
}

gchar * gwp_beamspec_get_name (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  GString *ret = g_string_new (self->priv->name->str);

  return ret->str;
}

void gwp_beamspec_set_name (GwpBeamSpec *self, gchar *name)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (name != NULL); /* FIXME: name->len <= 20 */

  self->priv->name = g_string_assign (self->priv->name, name);
}

gint gwp_beamspec_get_cost (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  
  return self->priv->cost;
}

void gwp_beamspec_set_cost (GwpBeamSpec *self, gint cost)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (cost >= 0);

  self->priv->cost = cost;
}

gint gwp_beamspec_get_tritanium (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));

  return self->priv->tritanium;
}

void gwp_beamspec_set_tritanium (GwpBeamSpec *self, gint tri)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (tri >= 0);

  self->priv->tritanium = tri;
}

gint gwp_beamspec_get_duranium (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  
  return self->priv->duranium;
}

void gwp_beamspec_set_duranium (GwpBeamSpec *self, gint dur)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (dur >= 0);

  self->priv->duranium = dur;
}

gint gwp_beamspec_get_molybdenum (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  
  return self->priv->molybdenum;
}

void gwp_beamspec_set_molybdenum (GwpBeamSpec *self, gint mol)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (mol >= 0);

  self->priv->molybdenum = mol;
}

gint gwp_beamspec_get_mass (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  
  return self->priv->mass;
}

void gwp_beamspec_set_mass (GwpBeamSpec *self, gint mass)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (mass >= 0);

  self->priv->mass = mass;
}

gint gwp_beamspec_get_tech_level (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));

  return self->priv->tech_level;
}

void gwp_beamspec_set_tech_level (GwpBeamSpec *self, gint tl)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (tl >= 1 && tl <= 10);

  self->priv->tech_level = tl;
}

gint gwp_beamspec_get_kill_value (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));

  return self->priv->kill_value;
}

void gwp_beamspec_set_kill_value (GwpBeamSpec *self, gint kv)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (kv >= 0);

  self->priv->kill_value = kv;
}

gint gwp_beamspec_get_damage_value (GwpBeamSpec *self)
{
  g_assert (GWP_IS_BEAMSPEC(self));

  return self->priv->damage_value;
}

void gwp_beamspec_set_damage_value (GwpBeamSpec *self, gint dv)
{
  g_assert (GWP_IS_BEAMSPEC(self));
  g_assert (dv >= 0);

  self->priv->damage_value = dv;
}
