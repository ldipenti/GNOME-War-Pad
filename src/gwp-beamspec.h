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
 * GwpBeamSpec:
 * -----------
 *
 * Starship's Beam Specification Type - it describes all the beam weapons 
 * on the game, the data is loaded from the BEAMSPEC.DAT file.
 */

#ifndef GWP_BEAMSPEC_H
#define GWP_BEAMSPEC_H

#include <glib.h>
#include <glib-object.h>

/*
 * Type macros.
 */

typedef struct _GwpBeamSpec GwpBeamSpec;
typedef struct _GwpBeamSpecClass GwpBeamSpecClass;
typedef struct _GwpBeamSpecPrivate GwpBeamSpecPrivate;

struct _GwpBeamSpec {
  GObject parent;

  /* instance members */

  /* private */
  GwpBeamSpecPrivate *priv;
};

struct _GwpBeamSpecClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_BEAMSPEC_TYPE */
GType gwp_beamspec_get_type (void);

/*
 * Public method definitions.
 */
GwpBeamSpec *gwp_beamspec_new (void);


/**************************/
/* get/set boring methods */
/**************************/

gint gwp_beamspec_get_id (GwpBeamSpec *self);
void gwp_beamspec_set_id (GwpBeamSpec *self, gint id);
GString * gwp_beamspec_get_name (GwpBeamSpec *self);
void gwp_beamspec_set_name (GwpBeamSpec *self, GString *name);
gint gwp_beamspec_get_cost (GwpBeamSpec *self);
void gwp_beamspec_set_cost (GwpBeamSpec *self, gint cost);
gint gwp_beamspec_get_tritanium (GwpBeamSpec *self);
void gwp_beamspec_set_tritanium (GwpBeamSpec *self, gint tri);
gint gwp_beamspec_get_duranium (GwpBeamSpec *self);
void gwp_beamspec_set_duranium (GwpBeamSpec *self, gint dur);
gint gwp_beamspec_get_molybdenum (GwpBeamSpec *self);
void gwp_beamspec_set_molybdenum (GwpBeamSpec *self, gint mol);
gint gwp_beamspec_get_mass (GwpBeamSpec *self);
void gwp_beamspec_set_mass (GwpBeamSpec *self, gint mass);
gint gwp_beamspec_get_tech_level (GwpBeamSpec *self);
void gwp_beamspec_set_tech_level (GwpBeamSpec *self, gint tl);
gint gwp_beamspec_get_kill_value (GwpBeamSpec *self);
void gwp_beamspec_set_kill_value (GwpBeamSpec *self, gint kv);
gint gwp_beamspec_get_damage_value (GwpBeamSpec *self);
void gwp_beamspec_set_damage_value (GwpBeamSpec *self, gint dv);


/*
 * Standard defines.
 */
#define GWP_TYPE_BEAM_SPEC            (gwp_beamspec_get_type())
#define GWP_BEAMSPEC(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_BEAM_SPEC, GwpBeamSpec))
#define GWP_BEAM_SPEC(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_BEAM_SPEC, GwpBeamSpec))
#define GWP_BEAMSPEC_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_BEAM_SPEC, GwpBeamSpecClass))
#define GWP_IS_BEAMSPEC(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_BEAM_SPEC))
#define GWP_IS_BEAMSPEC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_BEAM_SPEC))
#define GWP_BEAMSPEC_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_BEAM_SPEC, GwpBeamSpecClass))

#endif
