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

#include "gwp-torpspec.h"

/*
 * Private members.
 */
struct _GwpTorpSpecPrivate {
  gboolean dispose_has_run;
  /* Actual data */
  gint id;
  GString *name; /* max 20 chars */
  gint torpedo_cost;
  gint launcher_cost;
  gint tritanium; /* mineral cost for launcher, torps take 1kt of */
  gint duranium;  /* every mineral */
  gint molybdenum;
  gint mass; /* launcher mass, torp mas is always 1 */
  gint tech_level;
  gint kill_value;
  gint damage_value;
};

/*
 * Forward definitions.
 */
static void gwp_torpspec_init (GTypeInstance *instance, gpointer g_class);
static void gwp_torpspec_class_init (GwpTorpSpecClass *klass);

GType gwp_torpspec_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpTorpSpecClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_torpspec_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpTorpSpec),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_torpspec_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpTorpSpec",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_torpspec_init (GTypeInstance *instance,
			       gpointer       g_class)
{
  GwpTorpSpec *self = (GwpTorpSpec *)instance;
  self->priv = g_new0 (GwpTorpSpecPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->id = 0;
  self->priv->name = g_string_new("");
  self->priv->torpedo_cost = 0;
  self->priv->launcher_cost = 0;
  self->priv->tritanium = 0;
  self->priv->duranium = 0;
  self->priv->molybdenum = 0;
  self->priv->mass = 0;
  self->priv->tech_level = 0;
  self->priv->kill_value = 0;
  self->priv->damage_value = 0;
}

static void gwp_torpspec_dispose (GwpTorpSpec *self)
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

static void gwp_torpspec_finalize (GwpTorpSpec *self)
{
  /* Here, complete object destruction. */
  g_free (self->priv);
}

static void gwp_torpspec_class_init (GwpTorpSpecClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* Register destructor methods. */
  gobject_class->dispose = gwp_torpspec_dispose;
  gobject_class->finalize = gwp_torpspec_finalize;
}

/*
 * Public method implementations.
 */
GwpTorpSpec * gwp_torpspec_new (void)
{
  return g_object_new (gwp_torpspec_get_type (), NULL);
}

/**************************/
/* get/set boring methods */
/**************************/

gint gwp_torpspec_get_id (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->id;
}

void gwp_torpspec_set_id (GwpTorpSpec *self, gint id)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (id >= 1 && id <= 10);

  self->priv->id = id;
}

GString * gwp_torpspec_get_name (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return g_string_new (self->priv->name->str);
}

void gwp_torpspec_set_name (GwpTorpSpec *self, GString *name)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (name != NULL && name->len <= 20);

  self->priv->name = g_string_assign (self->priv->name, name->str);
}

gint gwp_torpspec_get_torpedo_cost (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->torpedo_cost;
}

void gwp_torpspec_set_torpedo_cost (GwpTorpSpec *self, gint tc)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (tc >= 0);

  self->priv->torpedo_cost = tc;
}

gint gwp_torpspec_get_launcher_cost (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->launcher_cost;
}

void gwp_torpspec_set_launcher_cost (GwpTorpSpec *self, gint lc)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (lc >= 0);

  self->priv->launcher_cost = lc;
}

gint gwp_torpspec_get_tritanium (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->tritanium;
}

void gwp_torpspec_set_tritanium (GwpTorpSpec *self, gint tri)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (tri >= 0);

  self->priv->tritanium = tri;
}

gint gwp_torpspec_get_duranium (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->duranium;
}

void gwp_torpspec_set_duranium (GwpTorpSpec *self, gint dur)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (dur >= 0);

  self->priv->duranium = dur;
}

gint gwp_torpspec_get_molybdenum (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->molybdenum;
}

void gwp_torpspec_set_molybdenum (GwpTorpSpec *self, gint mol)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (mol >= 0);

  self->priv->molybdenum = mol;
}

gint gwp_torpspec_get_mass (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->mass;
}

void gwp_torpspec_set_mass (GwpTorpSpec *self, gint mass)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (mass >= 0);

  self->priv->mass = mass;
}

gint gwp_torpspec_get_tech_level (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->tech_level;
}

void gwp_torpspec_set_tech_level (GwpTorpSpec *self, gint tl)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (tl >= 1 && tl <= 10);

  self->priv->tech_level = tl;
}

gint gwp_torpspec_get_kill_value (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->kill_value;
}

void gwp_torpspec_set_kill_value (GwpTorpSpec *self, gint kv)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (kv >= 0);

  self->priv->kill_value = kv;
}

gint gwp_torpspec_get_damage_value (GwpTorpSpec *self)
{
  g_assert (GWP_IS_TORPSPEC(self));

  return self->priv->damage_value;
}

void gwp_torpspec_set_damage_value (GwpTorpSpec *self, gint dv)
{
  g_assert (GWP_IS_TORPSPEC(self));
  g_assert (dv >= 0);

  self->priv->damage_value = dv;
}
