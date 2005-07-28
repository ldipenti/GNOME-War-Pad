/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2005 Lucas Di Pentima <lucas@lunix.com.ar>
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
    Revision 1.5  2005/07/28 03:16:21  ldipenti
    Feature: update() method implemented, when coords change, the draw get updated

    Revision 1.4  2005/07/27 03:56:10  ldipenti
    Feature: GwpObject migrated to GObject's properties, GwpMarker cleaned up a little...property-changed signal is inherited from GwpObject

    Revision 1.3  2005/07/20 16:11:05  ldipenti
    Feature: First working prototype with starchart markers (cool!)

    Revision 1.2  2005/07/20 14:17:18  ldipenti
    Almost finished the first draft about starchart markers

    Revision 1.1  2005/07/11 11:24:48  ldipenti
    Started to work on starchart's markers

*/

#include <gnome.h>
#include "gwp-object.h"
#include "gwp-marker.h"
#include "vp_utils.h"

enum {
  PROP_0,
  PROP_VISIBLE,
  PROP_COMMENT,
  PROP_COLOR,
  PROP_COMMENT_VISIBLE,
};

struct _GwpMarkerPrivate {
  gboolean dispose_has_run;
  gboolean visible; /**< Whether the marker is visible or not. TRUE by default */
  GString *comment; /**< An optional comment on the marker. */
  GString *color; /**< The marker's color. White by default */
  gboolean comment_visible; /**< TRUE if the comment should be showed. FALSE by default. */
  GwpStarchart *starchart; /**< The starchart related to this marker, it's passed at instantiation time. */
};

/*
 * forward definitions.
 */
static void gwp_marker_init (GTypeInstance *instance, gpointer g_class);
static void gwp_marker_class_init (GwpMarkerClass *klass);

GType gwp_marker_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpMarkerClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_marker_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpMarker), 
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_marker_init /* instance_init */
    };
    type = g_type_register_static (GWP_TYPE_OBJECT,
				   "GwpMarker",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_marker_init (GTypeInstance *instance,
			     gpointer g_class)
{
  GwpMarker *self = (GwpMarker *)instance;
  self->priv = g_new0 (GwpMarkerPrivate, 1);
  self->priv->dispose_has_run = FALSE;
  /* Attributes initializacion */
  self->priv->visible = FALSE;
  self->priv->comment = g_string_new ("");
  self->priv->color = g_string_new ("white");
  self->priv->comment_visible = FALSE;
  self->priv->starchart = NULL;
}

/**
 * Property setters
 */
static void
gwp_marker_set_property (GObject      *object,
			 guint         property_id,
			 const GValue *value,
			 GParamSpec   *pspec)
{
  GwpMarker *self = (GwpMarker *) object;

  switch (property_id) {
  case PROP_VISIBLE:
    self->priv->visible = g_value_get_boolean (value);
    break;
  case PROP_COMMENT:
    self->priv->comment = g_string_new (g_value_get_string(value));
    break;
  case PROP_COLOR:
    self->priv->color = g_string_new (g_value_get_string(value));
    break;
  case PROP_COMMENT_VISIBLE:
    self->priv->comment_visible = g_value_get_boolean (value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
  }
  /* Emit a notify signal with the changed property name */
  g_signal_emit_by_name (self, g_strconcat ("property-changed::",
					    pspec->name, NULL));
}

/**
 * Property getters
 */
static void
gwp_marker_get_property (GObject    *object,
			 guint       property_id,
			 GValue     *value,
			 GParamSpec *pspec)
{
  GwpMarker *self = (GwpMarker *) object;

  switch (property_id) {
  case PROP_VISIBLE:
    g_value_set_boolean (value, self->priv->visible);
    break;
  case PROP_COMMENT:
    g_value_set_string (value, self->priv->comment->str);
    break;
  case PROP_COLOR:
    g_value_set_string (value, self->priv->color->str);
    break;
  case PROP_COMMENT_VISIBLE:
    g_value_set_boolean (value, self->priv->comment_visible);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;    
  }
}

static void gwp_marker_dispose (GwpMarker *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  gwp_starchart_delete_draw (self->priv->starchart,
			     gwp_object_get_id(GWP_OBJECT(self)));
  g_string_free (self->priv->comment, TRUE);
  g_string_free (self->priv->color, TRUE);
}

static void gwp_marker_finalize (GwpMarker *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_marker_class_init (GwpMarkerClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  /* Register destructor methods. */
  gobject_class->dispose = (void *) gwp_marker_dispose;
  gobject_class->finalize = (void *) gwp_marker_finalize;

  /* 
     NOTE on signal registration: we don't need to register the 
     'property-changed' signal because it's already registered
     in GwpObject class.
  */

  /* Property get/set methods */
  gobject_class->set_property = gwp_marker_set_property;
  gobject_class->get_property = gwp_marker_get_property;

  /* Properties registrations */
  g_object_class_install_property (gobject_class, PROP_VISIBLE,
				   g_param_spec_boolean ("visible",
							 "Visible",
							 "Whether show the marker or not",
							 FALSE, /* default */
							 G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_COMMENT_VISIBLE,
				   g_param_spec_boolean ("comment-visible",
							 "Comment-Visible",
							 "Whether show the marker's comment or not",
							 FALSE, /* default */
							 G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_COMMENT,
				   g_param_spec_string ("comment",
							"Comment",
							"Marker's comment",
							"", /* default */
							G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_COLOR,
				   g_param_spec_string ("color",
							"Color",
							"Marker's color",
							"white", /* default */
							G_PARAM_READWRITE));
}

/*
 * Public methods implementations.
 */

GwpMarker *
gwp_marker_new (GwpStarchart *starchart)
{
  g_return_val_if_fail (GWP_IS_STARCHART(starchart), NULL);

  GwpMarker *new_marker = g_object_new (gwp_marker_get_type(), NULL);
  new_marker->priv->starchart = starchart;

  /* Auto-connect to update signal */
  g_signal_connect (new_marker,
		    "property-changed::x-coord",
		    G_CALLBACK(gwp_marker_update),
		    NULL);
  g_signal_connect (new_marker,
		    "property-changed::y-coord",
		    G_CALLBACK(gwp_marker_update),
		    NULL);

  return new_marker;
}

/**
 * Draws the marker's representation on the related starchart
 *
 * @param self a GwpMarker
 */
void
gwp_marker_draw (GwpMarker *self)
{
  g_return_if_fail (GWP_IS_MARKER(self));


  /* Do nothing if this marker had been already been drawn */
  if (gwp_object_get_id(GWP_OBJECT(self)) != 0) return;

  gint marker_id = 0;

  marker_id = 
    gwp_starchart_draw_group (self->priv->starchart, 
			      gwp_object_get_x_coord(GWP_OBJECT(self)),
			      gwp_object_get_y_coord(GWP_OBJECT(self)));
  gwp_object_set_id (GWP_OBJECT(self), marker_id);

  gwp_starchart_draw_line_on_marker(self->priv->starchart, 
				    marker_id,
				    0, 0, 
				    10, 10,
				    "red");
  gwp_starchart_draw_line_on_marker(self->priv->starchart, 
				    marker_id,
				    0, 10, 
				    10, 0,
				    "red");
  g_object_set (self,
		"visible", TRUE,
		NULL);
}

/**
 * Delete the marker's representation from the related starchart.
 *
 * @param self a GwpMarker
 */
void
gwp_marker_delete (GwpMarker *self)
{
  g_return_if_fail (GWP_IS_MARKER(self));

  /* Do nothing if this marker had been already deleted */
  if (gwp_object_get_id(GWP_OBJECT(self)) == 0) return;
  
  gwp_starchart_delete_draw (self->priv->starchart,
			     gwp_object_get_id(GWP_OBJECT(self)));
  /* Reset the ID */
  gwp_object_set_id (GWP_OBJECT(self), 0);

  g_object_set (self,
		"visible", FALSE,
		NULL);
}

/**
 * Updates marker's drawing
 *
 * @param self a GwpMarker
 */
void
gwp_marker_update (GwpMarker *self)
{
  g_return_if_fail (GWP_IS_MARKER(self));

  gboolean visible;
  g_object_get (self,
		"visible", &visible,
		NULL);

  if (visible) {
    gwp_marker_delete (self);
    gwp_marker_draw (self);
  }
}
