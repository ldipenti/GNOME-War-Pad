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
 * GwpStarbase:
 * -----------
 *
 * This object is contained within GwpPlanet when the starbase is actually
 * built on the planet. By itself, this object has no graphical 
 * representation on the starchart, that's why it doesn't derivate from
 * GwpObject.
 */

#ifndef GWP_STARBASE_H
#define GWP_STARBASE_H

#include <glib.h>
#include <glib-object.h>

/*
 * Type macros.
 */

typedef struct _GwpStarbase GwpStarbase;
typedef struct _GwpStarbaseClass GwpStarbaseClass;
typedef struct _GwpStarbasePrivate GwpStarbasePrivate;

struct _GwpStarbase {
  GObject parent;

  /* instance members */

  /* private */
  GwpStarbasePrivate *priv;
};

/* used by GWP_STARBASE_TYPE */
GType gwp_starbase_get_type (void);

/*
 * Public method definitions.
 */
GwpStarbase * gwp_starbase_new (void);

/*
 * Standard defines.
 */
#define GWP_STARBASE_TYPE (gwp_starbase_get_type())
#define GWP_STARBASE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_STARBASE_TYPE, GwpStarbase))
#define GWP_STARBASE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_STARBASE_TYPE, GwpStarbaseClass))
#define GWP_IS_STARBASE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_STARBASE_TYPE))
#define GWP_IS_STARBASE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_STARBASE_TYPE))
#define GWP_STARBASE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_STARBASE_TYPE, GwpStarbaseClass))

#endif
