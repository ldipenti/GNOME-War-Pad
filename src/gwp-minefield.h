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
 * GwpMinefield:
 * ---------------
 *
 * This class describes all minefields on the echo cluster.
 */

#ifndef GWP_MINEFIELD_H
#define GWP_MINEFIELD_H

#include <glib.h>
#include <glib-object.h>

#include "global.h"
#include "gwp-object.h"

/* 
 * Type macros.
 */

typedef struct _GwpMinefield GwpMinefield;
typedef struct _GwpMinefieldClass GwpMinefieldClass;
typedef struct _GwpMinefieldPrivate GwpMinefieldPrivate;

struct _GwpMinefield {
  GwpObject parent;

  /* instance members */

  /* private */
  GwpMinefieldPrivate *priv;
};

struct _GwpMinefieldClass {
  GwpObjectClass parent;
  /* class members */
};

/* used by GWP_MINEFIELD_TYPE */
GType gwp_minefield_get_type (void);

/*
 * Public method definitions.
 */
GwpMinefield * gwp_minefield_new (void);

/* high-level methods */
gboolean gwp_minefield_is_valid (GwpMinefield *self);
gboolean gwp_minefield_is_mine(GwpMinefield *self);
gboolean gwp_minefield_is_web (GwpMinefield *self);

/* get-set methods */
gint gwp_minefield_get_radius (GwpMinefield *self);
void gwp_minefield_set_radius (GwpMinefield *self, gint r);
gint gwp_minefield_get_owner (GwpMinefield *self);
void gwp_minefield_set_owner (GwpMinefield *self, gint owner);


/*
 * Standard defines.
 */
#define GWP_TYPE_MINEFIELD (gwp_minefield_get_type())
#define GWP_MINEFIELD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_MINEFIELD, GwpMinefield))
#define GWP_MINEFIELD_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_MINEFIELD, GwpMinefieldClass))
#define GWP_IS_MINEFIELD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_MINEFIELD))
#define GWP_IS_MINEFIELD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_MINEFIELD))
#define GWP_MINEFIELD_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_MINEFIELD, GwpMinefieldClass))

#endif
