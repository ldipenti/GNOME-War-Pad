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
 * GwpHullSpec:
 * -----------
 *
 * Starship's Hull Specification Type - it describes all the hulls 
 * on the game, the data is loaded from the HULLSPEC.DAT file.
 */

#ifndef GWP_HULLSPEC_H
#define GWP_HULLSPEC_H

#include <glib.h>
#include <glib-object.h>

/*
 * Type macros.
 */

typedef struct _GwpHullSpec GwpHullSpec;
typedef struct _GwpHullSpecClass GwpHullSpecClass;
typedef struct _GwpHullSpecPrivate GwpHullSpecPrivate;

struct _GwpHullSpec {
  GObject parent;

  /* instance members */

  /* private */
  GwpHullSpecPrivate *priv;
};

struct _GwpHullSpecClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_HULLSPEC_TYPE */
GType gwp_hullspec_get_type (void);

/*
 * Public method definitions. 
 */
GwpHullSpec *gwp_hullspec_new (void);

/**********************/
/* high level methods */
/**********************/
GString * gwp_hullspec_get_name_trunc (GwpHullSpec *self, gint len);


/*******************/
/* get/set methods */
/*******************/
gint gwp_hullspec_get_id (GwpHullSpec *self);
void gwp_hullspec_set_id (GwpHullSpec *self, gint id);
GString * gwp_hullspec_get_name (GwpHullSpec *self);
void gwp_hullspec_set_name (GwpHullSpec *self, GString *name);
gint gwp_hullspec_get_picture (GwpHullSpec *self);
void gwp_hullspec_set_picture (GwpHullSpec *self, gint pic);
gint gwp_hullspec_get_tritanium (GwpHullSpec *self);
void gwp_hullspec_set_tritanium (GwpHullSpec *self, gint m);
gint gwp_hullspec_get_duranium (GwpHullSpec *self);
void gwp_hullspec_set_duranium (GwpHullSpec *self, gint m);
gint gwp_hullspec_get_molybdenum (GwpHullSpec *self);
void gwp_hullspec_set_molybdenum (GwpHullSpec *self, gint m);
gint gwp_hullspec_get_fuel_tank (GwpHullSpec *self);
void gwp_hullspec_set_fuel_tank (GwpHullSpec *self, gint ft);
gint gwp_hullspec_get_crew (GwpHullSpec *self);
void gwp_hullspec_set_crew (GwpHullSpec *self, gint crew);
gint gwp_hullspec_get_engines (GwpHullSpec *self);
void gwp_hullspec_set_engines (GwpHullSpec *self, gint eng);
gint gwp_hullspec_get_mass (GwpHullSpec *self);
void gwp_hullspec_set_mass (GwpHullSpec *self, gint mass);
gint gwp_hullspec_get_tech_level (GwpHullSpec *self);
void gwp_hullspec_set_tech_level (GwpHullSpec *self, gint tl);
gint gwp_hullspec_get_cargo (GwpHullSpec *self);
void gwp_hullspec_set_cargo (GwpHullSpec *self, gint cargo);
gint gwp_hullspec_get_fighter_bays (GwpHullSpec *self);
void gwp_hullspec_set_fighter_bays (GwpHullSpec *self, gint fb);
gint gwp_hullspec_get_torp_launchers (GwpHullSpec *self);
void gwp_hullspec_set_torp_launchers (GwpHullSpec *self, gint tl);
gint gwp_hullspec_get_beam_weapons (GwpHullSpec *self);
void gwp_hullspec_set_beam_weapons (GwpHullSpec *self, gint bw);
gint gwp_hullspec_get_cost (GwpHullSpec *self);
void gwp_hullspec_set_cost (GwpHullSpec *self, gint cost);


/*
 * Standard defines.
 */
#define GWP_TYPE_HULL_SPEC            (gwp_hullspec_get_type())
#define GWP_HULLSPEC(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_HULL_SPEC, GwpHullSpec))
#define GWP_HULL_SPEC(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_HULL_SPEC, GwpHullSpec))
#define GWP_HULLSPEC_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_HULL_SPEC, GwpHullSpecClass))
#define GWP_IS_HULLSPEC(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_HULL_SPEC))
#define GWP_IS_HULLSPEC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_HULL_SPEC))
#define GWP_HULLSPEC_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_HULL_SPEC, GwpHullSpecClass))

#endif
