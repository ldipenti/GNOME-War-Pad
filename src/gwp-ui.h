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
 * GwpUi :
 * ---------
 *
 * This class represents GWP's user interface, it provides a
 * controlled way to access the widgets.
 */

#ifndef GWP_UI_H
#define GWP_UI_H

#include <glib.h>
#include <glib-object.h>

/*
 * Type macros.
 */

typedef struct _GwpUi GwpUi;
typedef struct _GwpUiClass GwpUiClass;
typedef struct _GwpUiPrivate GwpUiPrivate;

struct _GwpUi {
  GObject parent;

  /* instance members */

  /* private */
  GwpUiPrivate *priv;
};

struct _GwpUiClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_UI_TYPE */
GType gwp_ui_get_type (void);

/*
 * Public method definitions.
 */
GwpUi *gwp_ui_new (void);

/**********************/
/* High-Level methods */
/**********************/
void gwp_ui_set_notification (GwpUi *self, gchar *msg);


/*******************/
/* Get-Set methods */
/*******************/


/*
 * Standard defines.
 */
#define GWP_TYPE_UI            (gwp_ui_get_type())
#define GWP_UI(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_UI, GwpUi))
#define GWP_UI_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_UI, GwpUiClass))
#define GWP_IS_UI(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_UI))
#define GWP_IS_UI_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_UI))
#define GWP_UI_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_UI, GwpUiClass))

#endif
