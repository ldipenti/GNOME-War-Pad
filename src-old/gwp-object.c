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
    Revision 1.17  2005/07/27 03:56:10  ldipenti
    Feature: GwpObject migrated to GObject's properties, GwpMarker cleaned up a little...property-changed signal is inherited from GwpObject

    Revision 1.16  2005/05/31 13:17:38  ldipenti
    Feature: Added CVS metadata on source files

*/

#include <string.h>

#include "global.h"
#include "gwp-object.h"

enum {
  PROP_0,
  PROP_X_COORD,
  PROP_Y_COORD,
  PROP_ID,
  PROP_NAME,
};

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
  self->priv->name = g_string_new(_("Unknown name")); 
}

/**
 * Property setters
 */
static void
gwp_object_set_property (GObject      *object,
			 guint         property_id,
			 const GValue *value,
			 GParamSpec   *pspec)
{
  GwpObject *self = (GwpObject *) object;
  gboolean changed = TRUE;

  switch (property_id) {
  case PROP_X_COORD:
    self->priv->x_coord = g_value_get_int (value);
    break;
  case PROP_Y_COORD:
    self->priv->y_coord = g_value_get_int (value);
    break;
  case PROP_NAME:
    if (strlen(g_value_get_string(value)) >= 1 &&
	strlen(g_value_get_string(value)) <= 21) {
      g_string_free (self->priv->name, TRUE);
      self->priv->name = g_string_new (g_value_get_string(value));
    } else {
      changed = FALSE;
    }
    break;
  case PROP_ID:
    self->priv->id = g_value_get_int (value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
  }
  /* Emit a notify signal with the changed property name */
  if (changed)
    g_signal_emit_by_name (self, g_strconcat ("property-changed::",
					      pspec->name, NULL));
}

/**
 * Property getters
 */
static void
gwp_object_get_property (GObject    *object,
			 guint       property_id,
			 GValue     *value,
			 GParamSpec *pspec)
{
  GwpObject *self = (GwpObject *) object;

  switch (property_id) {
  case PROP_X_COORD:
    g_value_set_int (value, self->priv->x_coord);
    break;
  case PROP_Y_COORD:
    g_value_set_int (value, self->priv->y_coord);
    break;
  case PROP_NAME:
    g_value_set_string (value, self->priv->name->str);
    break;
  case PROP_ID:
    g_value_set_int (value, self->priv->id);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;    
  }
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
  g_free (self->priv);
}

static void gwp_object_class_init (GwpObjectClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* Register destructor methods. */
  gobject_class->dispose = (void *)gwp_object_dispose;
  gobject_class->finalize = (void *)gwp_object_finalize;

  /*
   * Signals
   */
  g_signal_newv ("property-changed",
		 G_TYPE_FROM_CLASS (klass),
		 G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
		 NULL /* class closure */,
		 NULL /* accumulator */,
		 NULL /* accu_data */,
		 g_cclosure_marshal_VOID__VOID,
		 G_TYPE_NONE /* return_type */,
		 0     /* n_params */,
		 NULL  /* param_types */);

  /* Property get/set methods */
  gobject_class->set_property = gwp_object_set_property;
  gobject_class->get_property = gwp_object_get_property;

  /* Properties registrations */
  g_object_class_install_property (gobject_class, PROP_X_COORD,
				   g_param_spec_int ("x-coord",
						     "X-Coord",
						     "X coordinate in the starchart",
						     0, 4000, /* min/max */
						     0, /* default */
						     G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_Y_COORD,
				   g_param_spec_int ("y-coord",
						     "Y-Coord",
						     "Y coordinate in the starchart",
						     0, 4000, /* min/max */
						     0, /* default */
						     G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_NAME,
				   g_param_spec_string ("name",
							"Name",
							"Object's Name",
							"Unkown name", /* default */
							G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_ID,
				   g_param_spec_int ("id",
						     "ID",
						     "Object's ID number",
						     0, 65535, /* min/max */
						     0, /* default */
						     G_PARAM_READWRITE));
}

/* 
 * Public method implementations.
 */
GwpObject * gwp_object_new (void)
{
  return g_object_new (gwp_object_get_type (), NULL);
}

/**********************/
/* High-level methods */
/**********************/

/**
 * Check if the given object has valid coordinates
 *
 * @param self a GwpObject
 * @return TRUE if the current object has valid coordinates, FALSE
 * otherwise.
 */
gboolean gwp_object_valid_coords (GwpObject *self) 
{
  g_assert(GWP_IS_OBJECT(self));

  if (gwp_object_get_x_coord(self) <= STARCHART_X_MAX && 
      gwp_object_get_x_coord(self) >= STARCHART_X_MIN &&
      gwp_object_get_y_coord(self) <= STARCHART_Y_MAX && 
      gwp_object_get_y_coord(self) >= STARCHART_Y_MIN) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
 * Returns the object's name truncated.
 *
 * Object names can be very long, so with this function you can truncate
 * it to a given number of characters.
 *
 * @param self a GwpObject.
 * @param len the maximum name length accepted.
 * @return A string containing the truncated name.
 */
gchar * gwp_object_get_name_trunc (GwpObject *self, gint len)
{
  g_assert (GWP_IS_OBJECT(self)); 
  g_assert (len > 0);

  /* ...truncate object name if it's too long */
  GString *tmp_str = g_string_new(gwp_object_get_name(self));
  if (tmp_str->len > len) {
    tmp_str = g_string_truncate (tmp_str, len);
    tmp_str = g_string_append (tmp_str, "...");
  }

  return tmp_str->str;
}

/*******************/
/* Get-Set methods */
/*******************/

gint gwp_object_get_x_coord (GwpObject *self)
{
  g_assert (GWP_IS_OBJECT(self));
  return self->priv->x_coord;
}

void gwp_object_set_x_coord (GwpObject *self, gint x)
{
  g_assert (GWP_IS_OBJECT(self));
  g_object_set (self,
		"x_coord", x,
		NULL);
}

gint gwp_object_get_y_coord (GwpObject *self)
{
  g_assert (GWP_IS_OBJECT(self));
  return self->priv->y_coord;
}

void gwp_object_set_y_coord (GwpObject *self, gint y)
{
  g_assert (GWP_IS_OBJECT(self));
  g_object_set (self,
		"y_coord", y,
		NULL);
}

gint gwp_object_get_id (GwpObject *self)
{
  g_assert(GWP_IS_OBJECT(self));
  return self->priv->id;
}

void gwp_object_set_id (GwpObject *self, gint id)
{
  g_assert(GWP_IS_OBJECT(self));
  g_object_set (self,
		"id", id, 
		NULL);
}

gchar * gwp_object_get_name (GwpObject *self)
{
  g_assert (GWP_IS_OBJECT(self));
  GString *ret;

  /* CP437 (DOS format) to UTF-8 conversion is done */
  ret = g_string_new (g_convert(self->priv->name->str, 
				strlen(self->priv->name->str), 
				"UTF-8", "CP437", NULL, NULL, NULL));
  return ret->str;
}

void gwp_object_set_name (GwpObject *self, gchar *name)
{
  g_assert (GWP_IS_OBJECT(self));
  g_object_set(self,
	       "name", g_strdup(name),
	       NULL);
}
