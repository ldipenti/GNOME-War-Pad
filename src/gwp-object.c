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

#include "gwp-object.h"

/*
 * Private members.
 */
struct _GwpObjectPrivate {
  gboolean dispose_has_run;
  gint x_coord;
  gint y_coord;
  gint id;
  GString *name;
};

/*
 * forward definitions.
 */
static void gwp_object_init (GTypeInstance *instance, gpointer g_class);
static void gwp_object_class_init (GwpObjectClass *klass);

GType gwp_object_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpObjectClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_object_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpObject),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_object_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpObject",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_object_init (GTypeInstance *instance,
			     gpointer       g_class)
{
  GwpObject *self = (GwpObject *)instance;
  self->priv = g_new0 (GwpObjectPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->x_coord = 0;
  self->priv->y_coord = 0;
  self->priv->id = 0;
  self->priv->name = g_string_new("");
  g_message("GwpObject init");
}

static void gwp_object_dispose (GwpObject *self)
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

static void gwp_object_finalize (GwpObject *self)
{
  /*
   * Here, complete object destruction.
   */
  g_message("GwpObject finalize");
  g_free (self->priv);
}

static void gwp_object_class_init (GwpObjectClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  g_message("GwpObjectClass init");
  /* Register destructor methods. */
  gobject_class->dispose = gwp_object_dispose;
  gobject_class->finalize = gwp_object_finalize;
}

/* 
 * Public method implementations.
 */
GwpObject * gwp_object_new (void)
{
  return g_object_new (gwp_object_get_type (), NULL);
}

gint gwp_object_get_x_coord (GwpObject *self)
{
  g_assert (GWP_IS_OBJECT(self));
  return self->priv->x_coord;
}

void gwp_object_set_x_coord (GwpObject *self, gint x)
{
  g_assert (GWP_IS_OBJECT(self));
  g_assert (x >= 0 && x <= 4000);
  self->priv->x_coord = x;
}

gint gwp_object_get_y_coord (GwpObject *self)
{
  g_assert (GWP_IS_OBJECT(self));
  return self->priv->y_coord;
}

void gwp_object_set_y_coord (GwpObject *self, gint y)
{
  g_assert (GWP_IS_OBJECT(self));
  g_assert (y >= 0 && y <= 4000);
  self->priv->y_coord = y;
}

gint gwp_object_get_id (GwpObject *self)
{
  g_assert(GWP_IS_OBJECT(self));
  return self->priv->id;
}

void gwp_object_set_id (GwpObject *self, gint id)
{
  g_assert(GWP_IS_OBJECT(self));
  self->priv->id = id;
}

GString * gwp_object_get_name (GwpObject *self)
{
  g_assert (GWP_IS_OBJECT(self));
  return g_string_new (self->priv->name->str);
}

void gwp_object_set_name (GwpObject *self, GString *name)
{
  g_assert (GWP_IS_OBJECT(self));
  g_assert (name != NULL);
  g_string_free (self->priv->name, TRUE);
  self->priv->name = g_string_new(name->str);
}
