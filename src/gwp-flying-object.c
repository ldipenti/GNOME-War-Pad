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
#include "gwp-flying-object.h"

struct _GwpFlyingObjectPrivate {
  gboolean dispose_has_run;
  gint heading; /* range 0..360 */
  gint speed; /* range 0..9, sometimes can be negative (set by the host) */
};

/*
 * forward definitions.
 */
static void gwp_fo_init (GTypeInstance *instance, gpointer g_class);
static void gwp_fo_class_init (GwpFlyingObjectClass *klass);

GType gwp_fo_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpFlyingObjectClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_fo_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpFlyingObject),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_fo_init /* instance_init */
    };
    type = g_type_register_static (GWP_OBJECT_TYPE,
				   "GwpFlyingObject",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_fo_init (GTypeInstance *instance,
			 gpointer       g_class)
{
  GwpFlyingObject *self = (GwpFlyingObject *)instance;
  self->priv = g_new0 (GwpFlyingObjectPrivate, 1);
  self->priv->dispose_has_run = FALSE;
  /* Attributes initialization */
  self->priv->heading = 0;
  self->priv->speed = 0;
}

static void gwp_fo_dispose (GwpFlyingObject *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a referece.
   */
  /* NOOP */
}

static void gwp_fo_finalize (GwpFlyingObject *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_fo_class_init (GwpFlyingObjectClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  /* Register destructor methods. */
  gobject_class->dispose = gwp_fo_dispose;
  gobject_class->finalize = gwp_fo_finalize;
}

/*
 * Public method implementations.
 */

GwpFlyingObject * gwp_fo_new (void)
{
  return g_object_new(gwp_fo_get_type(), NULL);
}

/**********************/
/* High-Level methods */
/**********************/
GString *gwp_fo_get_heading_str (GwpFlyingObject *self)
{
  g_assert (GWP_IS_FLYING_OBJECT(self));

  gint h = gwp_fo_get_heading(self);
  GString *hstr = NULL;

  if (h == 0 || h == 360) hstr = g_string_new(_("N"));
  else if (h > 0 && h < 90) hstr = g_string_new(_("NE"));
  else if (h == 90) hstr = g_string_new(_("E"));
  else if (h > 90 && h < 180) hstr = g_string_new(_("SE"));
  else if (h == 180) hstr = g_string_new(_("S"));
  else if (h > 180 && h < 270) hstr = g_string_new(_("SW"));
  else if (h == 270) hstr = g_string_new(_("W"));
  else hstr = g_string_new(_("NW"));

  return hstr;
}

/*******************/
/* Get/Set methods */
/*******************/
gint gwp_fo_get_heading (GwpFlyingObject *self)
{
  g_assert(GWP_IS_FLYING_OBJECT(self));
  return self->priv->heading;
}

void gwp_fo_set_heading (GwpFlyingObject *self, gint heading)
{
  g_assert(GWP_IS_FLYING_OBJECT(self));
  self->priv->heading = heading;
}

gint gwp_fo_get_speed (GwpFlyingObject *self)
{
  g_assert(GWP_IS_FLYING_OBJECT(self));
  return self->priv->speed;
}

void gwp_fo_set_speed (GwpFlyingObject *self, gint speed)
{
  g_assert(GWP_IS_FLYING_OBJECT(self));
  self->priv->speed = speed;
}

