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
 * GwpTorpSpec:
 * -----------
 *
 * Starship's Torpedoes Specification Type - it describes all the torpedo
 * weapons on the game, the data is loaded from the TORPSPEC.DAT file.
 */

#ifndef GWP_TORPSPEC_H
#define GWP_TORPSPEC_H

#include <glib.h>
#include <glib-object.h>

/*
 * Type macros.
 */

typedef struct _GwpTorpSpec GwpTorpSpec;
typedef struct _GwpTorpSpecClass GwpTorpSpecClass;
typedef struct _GwpTorpSpecPrivate GwpTorpSpecPrivate;

struct _GwpTorpSpec {
  GObject parent;

  /* instance members */

  /* private */
  GwpTorpSpecPrivate *priv;
};

struct _GwpTorpSpecClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_TORPSPEC_TYPE */
GType gwp_torpspec_get_type (void);

/*
 * Public method definitions.
 */
GwpTorpSpec *gwp_torpspec_new (void);



/**************************/
/* get/set boring methods */
/**************************/
gint gwp_torpspec_get_id (GwpTorpSpec *self);
void gwp_torpspec_set_id (GwpTorpSpec *self, gint id);
GString * gwp_torpspec_get_name (GwpTorpSpec *self);
void gwp_torpspec_set_name (GwpTorpSpec *self, GString *name);
gint gwp_torpspec_get_torpedo_cost (GwpTorpSpec *self);
void gwp_torpspec_set_torpedo_cost (GwpTorpSpec *self, gint tc);
gint gwp_torpspec_get_launcher_cost (GwpTorpSpec *self);
void gwp_torpspec_set_launcher_cost (GwpTorpSpec *self, gint lc);
gint gwp_torpspec_get_tritanium (GwpTorpSpec *self);
void gwp_torpspec_set_tritanium (GwpTorpSpec *self, gint tri);
gint gwp_torpspec_get_duranium (GwpTorpSpec *self);
void gwp_torpspec_set_duranium (GwpTorpSpec *self, gint dur);
gint gwp_torpspec_get_molybdenum (GwpTorpSpec *self);
void gwp_torpspec_set_molybdenum (GwpTorpSpec *self, gint mol);
gint gwp_torpspec_get_mass (GwpTorpSpec *self);
void gwp_torpspec_set_mass (GwpTorpSpec *self, gint mass);
gint gwp_torpspec_get_tech_level (GwpTorpSpec *self);
void gwp_torpspec_set_tech_level (GwpTorpSpec *self, gint tl);
gint gwp_torpspec_get_kill_value (GwpTorpSpec *self);
void gwp_torpspec_set_kill_value (GwpTorpSpec *self, gint kv);
gint gwp_torpspec_get_damage_value (GwpTorpSpec *self);
void gwp_torpspec_set_damage_value (GwpTorpSpec *self, gint dv);


/*
 * Standard defines.
 */
#define GWP_TORPSPEC_TYPE (gwp_torpspec_get_type())
#define GWP_TORPSPEC(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TORPSPEC_TYPE, GwpTorpSpec))
#define GWP_TORPSPEC_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TORPSPEC_TYPE, GwpTorpSpecClass))
#define GWP_IS_TORPSPEC(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TORPSPEC_TYPE))
#define GWP_IS_TORPSPEC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TORPSPEC_TYPE
#define GWP_TORPSPEC_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TORPSPEC_TYPE, GwpTorpSpecClass)) 

#endif
