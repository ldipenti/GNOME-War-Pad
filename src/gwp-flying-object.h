/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002, 2003  Lucas Di Pentima <lucas@lunix.com.ar>
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

/*
 * GwpFlyingObject:
 * ---------------
 *
 * This is the abstract class for all moving targets on the starchart, ie:
 * ships, storms, meteors, anything that moves.
 */

#ifndef GWP_FLYING_OBJECT_H
#define GWP_FLYING_OBJECT_H

#include <glib.h>
#include <glib-object.h>
#include <gnome.h>

#include "gwp-object.h"

/*
 * Type macros.
 */

typedef struct _GwpFlyingObject GwpFlyingObject;
typedef struct _GwpFlyingObjectClass GwpFlyingObjectClass;
typedef struct _GwpFlyingObjectPrivate GwpFlyingObjectPrivate;

struct _GwpFlyingObject {
  GwpObject parent;

  /* instance members */

  /* private */
  GwpFlyingObjectPrivate *priv;
};

struct _GwpFlyingObjectClass {
  GwpObjectClass parent;
  /* class members */
};

/* used by GWP_FLYING_OBJECT_TYPE */
GType gwp_flying_object_get_type (void);

/*
 * Public method definitions.
 */
GwpFlyingObject * gwp_flying_object_new (void);

/* high-level methods */
GString *gwp_flying_object_get_heading_str (GwpFlyingObject *self);

/* get-set methods */
gint gwp_flying_object_get_heading (GwpFlyingObject *self);
void gwp_flying_object_set_heading (GwpFlyingObject *self, gint heading);
gint gwp_flying_object_get_speed (GwpFlyingObject *self);
void gwp_flying_object_set_speed (GwpFlyingObject *self, gint speed);

/*
 * Standard defines.
 */
#define GWP_FLYING_OBJECT_TYPE            (gwp_flying_object_get_type())
#define GWP_TYPE_FLYING_OBJECT            (gwp_flying_object_get_type())
#define GWP_FLYING_OBJECT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_FLYING_OBJECT_TYPE, GwpFlyingObject))
#define GWP_FLYING_OBJECT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_FLYING_OBJECT_TYPE, GwpFlyingObjectClass))
#define GWP_IS_FLYING_OBJECT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_FLYING_OBJECT_TYPE))
#define GWP_IS_FLYING_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_FLYING_OBJECT_TYPE))
#define GWP_FLYING_OBJECT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_FLYING_OBJECT_TYPE, GwpFlyingObjectClass))

#endif
