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

#include "gwp-race.h"

/*
 * Private members.
 */
struct _GwpRacePrivate {
  gboolean dispose_has_run;
  GString *long_desc;  /**< Race name's long form (30 chars) */
  GString *short_desc; /**< Race name's short form (20 chars) */
  GString *adj;        /**< Race name's adjective (12 chars) */
};

/*
 * forward definitions.
 */
static void gwp_race_init (GTypeInstance *instance, gpointer g_class);
static void gwp_race_class_init (GwpRaceClass *klass);

GType gwp_race_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpRaceClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_race_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpRace),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_race_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpRace",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_race_init (GTypeInstance *instance,
			   gpointer       g_class)
{
  GwpRace *self = (GwpRace *)instance;
  self->priv = g_new0 (GwpRacePrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->long_desc = g_string_new ("long description");
  self->priv->short_desc = g_string_new ("short desc");
  self->priv->adj = g_string_new ("adjective");
}

static void gwp_race_dispose (GwpRace *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  g_string_free (self->priv->long_desc, TRUE);
  g_string_free (self->priv->short_desc, TRUE);
  g_string_free (self->priv->adj, TRUE);
}

static void gwp_race_finalize (GwpRace *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_race_class_init (GwpRaceClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* Register destructor methods. */
  gobject_class->dispose = (void *)gwp_race_dispose;
  gobject_class->finalize = (void *)gwp_race_finalize;
}

/*
 * Public method implementations.
 */
GwpRace * gwp_race_new (void)
{
  return g_object_new (gwp_race_get_type (), NULL);
}

/*******************/
/* Get-Set methods */
/*******************/

/**
 * Set the race name's long description.
 *
 * @param self a GwpRace object.
 * @param name the long description
 */
void
gwp_race_set_long_desc (GwpRace *self, gchar *name)
{
  g_assert (GWP_IS_RACE(self));
  self->priv->long_desc = g_string_new (g_strchomp(name));
}

/**
 * Returns the race name's long description.
 *
 * @param self a GwpRace object.
 * @return a new copy of the race name's long description.
 */
gchar *
gwp_race_get_long_desc (GwpRace *self)
{
  g_assert (GWP_IS_RACE(self));
  return g_strdup(self->priv->long_desc->str);
}

/**
 * Set the race name's long description.
 *
 * @param self a GwpRace object.
 * @param name the short description
 */
void
gwp_race_set_short_desc (GwpRace *self, gchar *name)
{
  g_assert (GWP_IS_RACE(self));
  self->priv->short_desc = g_string_new (name);
}

/**
 * Returns the race name's short description.
 *
 * @param self a GwpRace object.
 * @return a new copy of the race name's short description.
 */
gchar *
gwp_race_get_short_desc (GwpRace *self)
{
  g_assert (GWP_IS_RACE(self));
  return g_strdup(self->priv->short_desc->str);
}

/**
 * Set the race name's long description.
 *
 * @param self a GwpRace object.
 * @param name the adjective.
 */
void
gwp_race_set_adjective (GwpRace *self, gchar *name)
{
  g_assert (GWP_IS_RACE(self));
  self->priv->adj = g_string_new (name);
}

/**
 * Returns the race name's adjective.
 *
 * @param self a GwpRace object.
 * @return a new copy of the race name's adjective.
 */
gchar *
gwp_race_get_adjective (GwpRace *self)
{
  g_assert (GWP_IS_RACE(self));
  return g_strdup(self->priv->adj->str);
}

