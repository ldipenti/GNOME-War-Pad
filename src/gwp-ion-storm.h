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

#ifndef GWP_ION_STORM_H
#define GWP_ION_STORM_H

#include <glib.h>
#include <glib-object.h>

#include "gwp-flying-object.h"

/*
 * Type macros.
 */

typedef struct _GwpIonStorm GwpIonStorm;
typedef struct _GwpIonStormClass GwpIonStormClass;
typedef struct _GwpIonStormPrivate GwpIonStormPrivate;

struct _GwpIonStorm {
  GwpFlyingObject parent;

  /* instance members */

  /* private */
  GwpIonStormPrivate *priv;
};

struct _GwpIonStormClass {
  GwpFlyingObjectClass parent;
  /* class members */
};

/* used by GWP_ION_STORM_TYPE */
GType gwp_ion_storm_get_type (void);

/*
 * Public method definitions.
 */
GwpIonStorm *gwp_ion_storm_new (void);

/**********************/
/* High-level methods */
/**********************/
gint gwp_ion_storm_get_class (GwpIonStorm *self);
GString * gwp_ion_storm_get_class_str (GwpIonStorm *self);
gboolean gwp_ion_storm_is_valid (GwpIonStorm *self);

/*******************/
/* Get-Set methods */
/*******************/
gint gwp_ion_storm_get_radius (GwpIonStorm *self);
void gwp_ion_storm_set_radius (GwpIonStorm *self, gint r);
gint gwp_ion_storm_get_voltage (GwpIonStorm *self);
void gwp_ion_storm_set_voltage (GwpIonStorm *self, gint v);

/*
 * Standard defines.
 */
#define GWP_TYPE_ION_STORM            (gwp_ion_storm_get_type())
#define GWP_ION_STORM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_ION_STORM, GwpIonStorm))
#define GWP_ION_STORM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_ION_STORM, GwpIonStormClass))
#define GWP_IS_ION_STORM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_ION_STORM))
#define GWP_IS_ION_STORM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_ION_STORM))
#define GWP_ION_STORM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_ION_STORM, GwpIonStormClass))

#endif
