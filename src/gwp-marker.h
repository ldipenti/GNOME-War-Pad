/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2005  Lucas Di Pentima <lucas@lunix.com.ar>
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
    Revision 1.2  2005/07/20 14:17:18  ldipenti
    Almost finished the first draft about starchart markers

    Revision 1.1  2005/07/11 11:24:48  ldipenti
    Started to work on starchart's markers

*/

#ifndef GWP_MARKER_H
#define GWP_MARKER_H

#include <glib.h>
#include <glib-object.h>
#include "gwp-object.h"
#include "gwp-starchart.h"

/*
 * Type macros.
 */
typedef struct _GwpMarker GwpMarker;
typedef struct _GwpMarkerClass GwpMarkerClass;
typedef struct _GwpMarkerPrivate GwpMarkerPrivate;

struct _GwpMarker {
  GwpObject parent;

  /* instance members */

  /* private */
  GwpMarkerPrivate *priv;
};

struct _GwpMarkerClass {
  GwpObjectClass parent;
  /* class members */
};

/* used by GWP_MARKER_TYPE */
GType gwp_marker_get_type (void);

/*
 * Public method definitions.
 */
GwpMarker * gwp_marker_new (void);

GnomeCanvasItem *gwp_marker_get_view (GwpMarker *self, GnomeCanvasGroup *layer);
void gwp_marker_draw (GwpMarker *self, GwpStarchart *sc);


/*
 * Standard defines.
 */
#define GWP_TYPE_MARKER            (gwp_marker_get_type())
#define GWP_MARKER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_MARKER, GwpMarker))
#define GWP_MARKER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_MARKER, GwpMarkerClass))
#define GWP_IS_MARKER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_MARKER))
#define GWP_IS_MARKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_MARKER))
#define GWP_MARKER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_MARKER, GwpMarkerClass))

#endif
