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

#include "gwp-flying-object.h"
#include "gwp-object.h"
#include "gwp-ship.h"

struct _GwpShipPrivate {
  gboolean dispose_has_run;
};

/*
 * forward definitions.
 */
static void gwp_ship_init (GTypeInstance  *instance,  gpointer g_class);
static void gwp_ship_class_init (GwpShipClass *klass);

GType gwp_ship_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpShipClass),
      NULL,            /* base_init */
      NULL,            /* base_finalize */
      (GClassInitFunc) gwp_ship_class_init,            /* class_init */
      NULL,            /* class_finalize */
      NULL,            /* class_data */
      sizeof (GwpShip),
      0,               /* n_preallocs */
      (GInstanceInitFunc) gwp_ship_init    /* instance_init */
    };
    type = g_type_register_static (GWP_FLYING_OBJECT_TYPE,
				   "GwpShip",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_ship_init (GTypeInstance  *instance,
			   gpointer        g_class)
{
  GwpShip *self = (GwpShip *)instance;
  self->priv = g_new0 (GwpShipPrivate, 1);
  self->priv->dispose_has_run = FALSE;
  g_message("GwpShip initialized");
}

static void gwp_ship_dispose (GwpShip *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
}

static void gwp_ship_finalize (GwpShip *self)
{
  /* 
   * Here, complete object destruction.
   */
  g_message("GwpShip finalize");
  g_free (self->priv);
}

static void gwp_ship_class_init (GwpShipClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  g_message("GwpShipClass init");
  /*
   * Register destructor methods.
   */
  gobject_class->dispose = gwp_ship_dispose;
  gobject_class->finalize = gwp_ship_finalize;
}

/*
 * Public method implementations.
 */
GwpShip * gwp_ship_new (void)
{
  return g_object_new(gwp_ship_get_type(), NULL);
}
