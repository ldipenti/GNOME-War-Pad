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

#ifndef GWP_PLANET_H
#define GWP_PLANET_H

#include <glib.h>
#include <glib-object.h>

#include "gwp-object.h"

/*
 * Type macros.
 */

typedef struct _GwpPlanet GwpPlanet;
typedef struct _GwpPlanetClass GwpPlanetClass;
typedef struct _GwpPlanetPrivate GwpPlanetPrivate;

struct _GwpPlanet {
  GwpObject parent;

  /* instance members */

  /* private */
  GwpPlanetPrivate *priv;
};

struct _GwpPlanetClass {
  GwpObjectClass parent;
  /* class members */
};

/* used by GWP_PLANET_TYPE */
GType gwp_planet_get_type (void);

/*
 * Public method definitions.
 */
GwpPlanet *gwp_planet_new (void);

/*
 * Standard defines.
 */
#define GWP_PLANET_TYPE (gwp_planet_get_type())
#define GWP_PLANET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_PLANET_TYPE, GwpPlanet))
#define GWP_PLANET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_PLANET_TYPE, GwpPlanetClass))
#define GWP_IS_PLANET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_PLANET_TYPE))
#define GWP_IS_PLANET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_PLANET_TYPE))
#define GWP_PLANET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_PLANET_TYPE, GwpPlanetClass))

#endif
