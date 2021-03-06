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

/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.9  2005/05/31 13:17:38  ldipenti
    Feature: Added CVS metadata on source files

*/

/*
 * GwpObject:
 * ---------
 *
 * This is the base class for all the objects on GWP that must be showed 
 * on the starchart: ships, planets, storms, meteors, UFOs, notes, etc.
 */

#ifndef GWP_OBJECT_H
#define GWP_OBJECT_H

#include <glib.h>
#include <glib-object.h>

/*
 * Type macros.
 */

typedef struct _GwpObject GwpObject;
typedef struct _GwpObjectClass GwpObjectClass;
typedef struct _GwpObjectPrivate GwpObjectPrivate;

struct _GwpObject {
  GObject parent;

  /* instance members */

  /* private */
  GwpObjectPrivate *priv;
};

struct _GwpObjectClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_OBJECT_TYPE */
GType gwp_object_get_type (void);

/*
 * Public method definitions.
 */
GwpObject *gwp_object_new (void);

/**********************/
/* High-Level methods */
/**********************/
gboolean gwp_object_valid_coords (GwpObject *self);
gchar * gwp_object_get_name_trunc (GwpObject *self, gint len);

/*******************/
/* Get-Set methods */
/*******************/
gint gwp_object_get_x_coord (GwpObject *self);
void gwp_object_set_x_coord (GwpObject *self, gint x);
gint gwp_object_get_y_coord (GwpObject *self);
void gwp_object_set_y_coord (GwpObject *self, gint y);
gint gwp_object_get_id (GwpObject *self);
void gwp_object_set_id (GwpObject *self, gint id);
gchar * gwp_object_get_name (GwpObject *self);
void gwp_object_set_name (GwpObject *self, gchar *name);

/*
 * Standard defines.
 */
#define GWP_TYPE_OBJECT            (gwp_object_get_type())
#define GWP_OBJECT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_OBJECT, GwpObject))
#define GWP_OBJECT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_OBJECT, GwpObjectClass))
#define GWP_IS_OBJECT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_OBJECT))
#define GWP_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_OBJECT))
#define GWP_OBJECT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_OBJECT, GwpObjectClass))

#endif
