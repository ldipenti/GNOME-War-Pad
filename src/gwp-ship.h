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

#ifndef GWP_SHIP_H
#define GWP_SHIP_H

#include <glib.h>
#include <glib-object.h>

#include "gwp-flying-object.h"

/*
 * Type macros.
 */

typedef struct _GwpShip GwpShip;
typedef struct _GwpShipClass GwpShipClass;
typedef struct _GwpShipPrivate GwpShipPrivate;

struct _GwpShip {
  GwpFlyingObject parent;

  /* instance members */

  /* private */
  GwpShipPrivate *priv;
};

struct _GwpShipClass {
  GwpFlyingObjectClass parent;
  /* class members */
};

/* used by GWP_SHIP_TYPE */
GType gwp_ship_get_type (void);

/*
 * Public method definitions.
 */
GwpShip *gwp_ship_new (void);

/*
 * Standard defines.
 */
#define GWP_SHIP_TYPE            (gwp_ship_get_type())
#define GWP_SHIP(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_SHIP_TYPE, GwpShip))
#define GWP_SHIP_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_SHIP_TYPE, GwpShipClass))
#define GWP_IS_SHIP(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_SHIP_TYPE))
#define GWP_IS_SHIP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_SHIP_TYPE))
#define GWP_SHIP_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_SHIP_TYPE, GwpShipClass))

#endif
