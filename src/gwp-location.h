/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2004  Lucas Di Pentima <lucas@lunix.com.ar>
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
 * GwpLocation:
 * ---------
 *
 * This class represents a location on the starchart, with a list of other
 * objects that lay on that location.
 */

#ifndef GWP_LOCATION_H
#define GWP_LOCATION_H

#include <glib.h>
#include <glib-object.h>

#include "gwp-object.h"

/*
 * Type macros.
 */

typedef struct _GwpLocation GwpLocation;
typedef struct _GwpLocationClass GwpLocationClass;
typedef struct _GwpLocationPrivate GwpLocationPrivate;

struct _GwpLocation {
  GwpObject parent;

  /* instance members */

  /* private */
  GwpLocationPrivate *priv;
};

struct _GwpLocationClass {
  GwpObjectClass parent;
  /* class members */
};

/* used by GWP_LOCATION_TYPE */
GType gwp_location_get_type (void);

/*
 * Public method definitions.
 */
GwpLocation * gwp_location_new (void);

void gwp_location_add_object (GwpLocation *self, GwpObject *obj);
guint gwp_location_objects_nr (GwpLocation *self);
GwpObject * gwp_location_get_object (GwpLocation *self, guint obj_nr);



/*
 * Standard defines.
 */
#define GWP_TYPE_LOCATION (gwp_location_get_type())
#define GWP_LOCATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_LOCATION, GwpLocation))
#define GWP_LOCATION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_LOCATION, GwpLocationClass))
#define GWP_IS_LOCATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_LOCATION))
#define GWP_IS_LOCATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_LOCATION))
#define GWP_LOCATION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_LOCATION, GwpLocationClass))

#endif
