/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2004 Lucas Di Pentima <lucas@lunix.com.ar>
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
 * GwpEngSpec:
 * -----------
 *
 * Starship's Engines Specification Type - it describes all the engine types
 * on the game, the data is loaded from the ENGSPEC.DAT file.
 */

#ifndef GWP_ENGSPEC_H
#define GWP_ENGSPEC_H

#include <glib.h>
#include <glib-object.h>

/*
 * Type macros.
 */

typedef struct _GwpEngSpec GwpEngSpec;
typedef struct _GwpEngSpecClass GwpEngSpecClass;
typedef struct _GwpEngSpecPrivate GwpEngSpecPrivate;

struct _GwpEngSpec {
  GObject parent;

  /* instance members */

  /* private */
  GwpEngSpecPrivate *priv;
};

struct _GwpEngSpecClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_ENGSPEC_TYPE */
GType gwp_engspec_get_type (void);

/*
 * Public method definitions.
 */
GwpEngSpec *gwp_engspec_new (void);

/**********************/
/* high level methods */
/**********************/
gint gwp_engspec_get_fuel_usage_full (GwpEngSpec *self, gdouble dist,
				      gint speed, gint mass);

/**************************/
/* get/set boring methods */
/**************************/
gint gwp_engspec_get_id (GwpEngSpec *self);
void gwp_engspec_set_id (GwpEngSpec *self, gint id);
GString * gwp_engspec_get_name (GwpEngSpec *self);
void gwp_engspec_set_name (GwpEngSpec *self, GString *name);
gint gwp_engspec_get_cost (GwpEngSpec *self);
void gwp_engspec_set_cost (GwpEngSpec *self, gint cost);
gint gwp_engspec_get_tritanium (GwpEngSpec *self);
void gwp_engspec_set_tritanium (GwpEngSpec *self, gint tri);
gint gwp_engspec_get_duranium (GwpEngSpec *self);
void gwp_engspec_set_duranium (GwpEngSpec *self, gint dur);
gint gwp_engspec_get_molybdenum (GwpEngSpec *self);
void gwp_engspec_set_molybdenum (GwpEngSpec *self, gint mol);
gint gwp_engspec_get_tech_level (GwpEngSpec *self);
void gwp_engspec_set_tech_level (GwpEngSpec *self, gint tl);
gint gwp_engspec_get_fuel_usage (GwpEngSpec *self, gint warp);
void gwp_engspec_set_fuel_usage (GwpEngSpec *self, gint warp, gint fuel);


/*
 * Standard defines.
 */
#define GWP_ENGSPEC_TYPE (gwp_engspec_get_type())
#define GWP_ENGSPEC(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_ENGSPEC_TYPE, GwpEngSpec))
#define GWP_ENGSPEC_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_ENGSPEC_TYPE, GwpEngSpecClass))
#define GWP_IS_ENGSPEC(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_ENGSPEC_TYPE))
#define GWP_IS_ENGSPEC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_ENGSPEC_TYPE))
#define GWP_ENGSPEC_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_ENGSPEC_TYPE, GwpEngSpecClass))

#endif
