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

struct _GwpStarbaseClass {
  GObjectClass parent;
  /* class members */
};

/* This is included here because of the cyclic needs of types between
   GwpStarbase and GwpPlanet */
#include "gwp-planet.h"

/* used by GWP_STARBASE_TYPE */
GType gwp_starbase_get_type (void);

/*
 * Public method definitions.
 */
GwpStarbase * gwp_starbase_new (void);

/**********************/
/* High level methods */
/**********************/
GwpStarbase * gwp_starbase_copy (GwpStarbase *self);
gint16 gwp_starbase_get_id (GwpStarbase *self);

/*******************/
/* get/set methods */
/*******************/
gint16 gwp_starbase_get_defense (GwpStarbase *self);
void gwp_starbase_set_defense (GwpStarbase *self, gint16 def);
gint16 gwp_starbase_get_damage (GwpStarbase *self);
void gwp_starbase_set_damage (GwpStarbase *self, gint dam);
gint16 gwp_starbase_get_engines_tech (GwpStarbase *self);
void gwp_starbase_set_engines_tech (GwpStarbase *self, gint16 tech);
gint16 gwp_starbase_get_hulls_tech (GwpStarbase *self);
void gwp_starbase_set_hulls_tech (GwpStarbase *self, gint16 tech);
gint16 gwp_starbase_get_beams_tech (GwpStarbase *self);
void gwp_starbase_set_beams_tech (GwpStarbase *self, gint16 tech);
gint16 gwp_starbase_get_torps_tech (GwpStarbase *self);
void gwp_starbase_set_torps_tech (GwpStarbase *self, gint16 tech);
gint16 gwp_starbase_get_storage_engines (GwpStarbase *self, gint storage_nr);
void gwp_starbase_set_storage_engines (GwpStarbase *self, gint storage_nr, gint16 engine);
gint16 gwp_starbase_get_storage_hulls (GwpStarbase *self, gint storage_nr);
void gwp_starbase_set_storage_hulls (GwpStarbase *self, gint storage_nr, gint16 hull);
gint16 gwp_starbase_get_storage_beams (GwpStarbase *self, gint storage_nr);
void gwp_starbase_set_storage_beams (GwpStarbase *self, gint storage_nr, gint16 beam);
gint16 gwp_starbase_get_storage_torp_launchers (GwpStarbase *self, gint storage_nr);
void gwp_starbase_set_storage_torp_launchers (GwpStarbase *self, gint storage_nr, gint16 t_launcher);
gint16 gwp_starbase_get_storage_torps (GwpStarbase *self, gint storage_nr);
void gwp_starbase_set_storage_torps (GwpStarbase *self, gint storage_nr, gint16 torp);
gint16 gwp_starbase_get_fighters (GwpStarbase *self);
void gwp_starbase_set_fighters (GwpStarbase *self, gint16 f);
gint16 gwp_starbase_get_id_ship (GwpStarbase *self);
void gwp_starbase_set_id_ship (GwpStarbase *self, gint16 id);
gint16 gwp_starbase_get_ship_action (GwpStarbase *self);
void gwp_starbase_set_ship_action (GwpStarbase *self, gint16 action);
gint16 gwp_starbase_get_mission (GwpStarbase *self);
void gwp_starbase_set_mission (GwpStarbase *self, gint16 mission);
gint16 gwp_starbase_get_build_ship_type (GwpStarbase *self);
void gwp_starbase_set_build_ship_type (GwpStarbase *self, gint16 type);
gint16 gwp_starbase_get_build_engine_type (GwpStarbase *self);
void gwp_starbase_set_build_engine_type (GwpStarbase *self, gint16 type);
gint16 gwp_starbase_get_build_beam_type (GwpStarbase *self);
void gwp_starbase_set_build_beam_type (GwpStarbase *self, gint16 type);
gint16 gwp_starbase_get_build_beam_count (GwpStarbase *self);
void gwp_starbase_set_build_beam_count (GwpStarbase *self, gint16 count);
gint16 gwp_starbase_get_build_torp_type (GwpStarbase *self);
void gwp_starbase_set_build_torp_type (GwpStarbase *self, gint16 type);
gint16 gwp_starbase_get_build_torp_count (GwpStarbase *self);
void gwp_starbase_set_build_torp_count (GwpStarbase *self, gint16 count);
gint16 gwp_starbase_get_fighter_count (GwpStarbase *self);
void gwp_starbase_set_fighter_count (GwpStarbase *self, gint16 count);

/* FIXME: If I include this headers, I get parser errors from gcc (?)
*/
void gwp_starbase_set_planet (GwpStarbase *self, GwpPlanet *p);
GwpPlanet * gwp_starbase_get_planet (GwpStarbase *self);

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
