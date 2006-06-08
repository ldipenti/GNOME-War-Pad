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

/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.5  2005/05/31 13:17:38  ldipenti
    Feature: Added CVS metadata on source files

*/

#include "gwp-location.h"

struct _GwpLocationPrivate {
  gboolean dispose_has_run;

  /* private attributes */
  GSList *obj_list;
};

/*
 * forward definitions.
 */
static void gwp_location_init (GTypeInstance *instance, gpointer g_class);
static void gwp_location_class_init (GwpLocationClass *klass);

GType gwp_location_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpLocationClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_location_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpLocation), 
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_location_init /* instance_init */
    };
    type = g_type_register_static (GWP_TYPE_OBJECT, 
				   "GwpLocation", 
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_location_init (GTypeInstance *instance,
			       gpointer       g_class)
{
  GwpLocation *self = (GwpLocation *)instance;
  self->priv = g_new0 (GwpLocationPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* private attributes init */
  self->priv->obj_list = NULL;
}

static void gwp_location_dispose (GwpLocation *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /* 
   * Here, I have to unref all members on which I own a reference.
   */
  if (self->priv->obj_list) g_slist_free (self->priv->obj_list);
}

static void gwp_location_finalize (GwpLocation *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_location_class_init (GwpLocationClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* 
   * Register destructor methods.
   */
  gobject_class->dispose = (void *) gwp_location_dispose;
  gobject_class->finalize = (void *) gwp_location_finalize;
}

/*
 * Public method implementations.
 */

/**
 * Instantiates a new location.
 *
 * A location is a way to group several objects in one place. More
 * specifically, we are using locations to represent single starchart
 * points where may exist more than one starship, it's a way to handle
 * this cases more easy on the starchart.
 * 
 * @return The new instantiated GwpLocation.
 */
GwpLocation * gwp_location_new (void)
{
  return g_object_new (gwp_location_get_type(), NULL);
}

/**
 * Adds a GwpObject on the current GwpLocation.
 *
 * @param self the current location.
 * @param obj the object to be added.
 */
void gwp_location_add_object (GwpLocation *self, GwpObject *obj)
{
  g_assert(GWP_IS_LOCATION(self) && GWP_IS_OBJECT(obj));

  self->priv->obj_list = g_slist_append (self->priv->obj_list, obj);
}

/**
 * Returns the number of objects on the current location.
 *
 * @param self the current location.
 * @return The number of objects placed on the location.
 */
guint gwp_location_objects_nr (GwpLocation *self)
{
  g_assert (GWP_IS_LOCATION(self));

  return g_slist_length (self->priv->obj_list);
}

/**
 * Retrieve an object from the current location.
 *
 * @param self the current location.
 * @param obj_nr the object index number.
 * @return The GwpObject specified or NULL.
 */
GwpObject * gwp_location_get_object (GwpLocation *self, guint obj_nr)
{
  g_assert (GWP_IS_LOCATION(self));
  g_assert (obj_nr <= gwp_location_objects_nr(self) - 1);

  return (GwpObject *)g_slist_nth_data (self->priv->obj_list, obj_nr);
}
