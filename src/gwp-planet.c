/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002, 2003 Lucas Di Pentima <lucas@lunix.com.ar>
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

#include "gwp-object.h"
#include "gwp-planet.h"

struct _GwpPlanetPrivate {
  gboolean dispose_has_run;
};

/*
 * forward definitions.
 */
static void gwp_planet_init (GTypeInstance *instance, gpointer g_class);
static void gwp_planet_class_init (GwpPlanetClass *klass);

GType gwp_planet_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpPlanetClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_planet_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpPlanet),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_planet_init /* instance_init */
    };
    type = g_type_register_static (GWP_OBJECT_TYPE,
				   "GwpPlanet",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_planet_init (GTypeInstance *instance,
			     gpointer       g_class)
{
  GwpPlanet *self = (GwpPlanet *)instance;
  self->priv = g_new0 (GwpPlanetPrivate, 1);
  self->priv->dispose_has_run = FALSE;
  g_message("GwpPlanet init");
}

static void gwp_planet_dispose (GwpPlanet *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here, I have to unref all members on which I own a reference.
   */
}

static void gwp_planet_finalize (GwpPlanet *self)
{
  /*
   * Here, complete object destruction.
   */
  g_message ("GwpPlanet finalize");
  g_free (self->priv);
}

static void gwp_planet_class_init (GwpPlanetClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  g_message ("GwpPlanetClass init");
  /*
   * Register destructor methods.
   */
  gobject_class->dispose = gwp_planet_dispose;
  gobject_class->finalize = gwp_planet_finalize;
}

/*
 * Public method implementations.
 */
GwpPlanet * gwp_planet_new (void)
{
  return g_object_new (gwp_planet_get_type(), NULL);
}
