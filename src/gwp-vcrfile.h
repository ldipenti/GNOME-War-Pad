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
 * GwpVCRFile:
 * ---------
 *
 * Read the Visual Combat Recordings Results File
 */

#ifndef GWP_VCRFILE_H
#define GWP_VCRFILE_H

#include <glib.h>
#include <glib-object.h>

#include "vcr-combat.h"

#define bool int
#define true !0
#define false 0

#define VCRFILE_MAX_SHIPNAME_LENGTH 20

/*
 * Type macros.
 */

typedef struct _GwpVCRFile GwpVCRFile;
typedef struct _GwpVCRFileClass GwpVCRFileClass;
typedef struct _GwpVCRFilePrivate GwpVCRFilePrivate;
typedef struct _GwpVCRFilePublic {
  gint *msgindex;
  gboolean *msgexists;
  gint *msgnmb;
} GwpVCRFilePublic;

struct _GwpVCRFile {
  GObject parent;

  /* instance members */

  /* private */
  GwpVCRFilePrivate *priv;
  GwpVCRFilePublic *pub;
};

struct _GwpVCRFileClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_VCRFILE_TYPE */
GType gwp_vcrfile_get_type (void);

/*
 * Public method definitions.
 */
GwpVCRFile *gwp_vcrfile_new (void);

/**********************/
/* High-Level methods */
/**********************/
gboolean gwp_vcrfile_valid_coords (GwpVCRFile *self);

/*******************/
/* Get-Set methods */
/*******************/
gint gwp_vcrfile_get_x_coord (GwpVCRFile *self);
void gwp_vcrfile_set_x_coord (GwpVCRFile *self, gint x);
gint gwp_vcrfile_get_y_coord (GwpVCRFile *self);
void gwp_vcrfile_set_y_coord (GwpVCRFile *self, gint y);
gint gwp_vcrfile_get_id (GwpVCRFile *self);
void gwp_vcrfile_set_id (GwpVCRFile *self, gint id);
GString * gwp_vcrfile_get_name (GwpVCRFile *self);
void gwp_vcrfile_set_name (GwpVCRFile *self, GString *name);

gint gwp_vcrfile_read( GwpVCRFile *self );
gint gwp_vcrfile_get_number_of_combats( GwpVCRFile *self );
void gwp_vcrfile_set_current_combat( GwpVCRFile *self, gint n );

gint gwp_vcrfile_read_combat_record( GwpVCRFile *self, gint n );
gint gwp_vcrfile_get_random_seed( GwpVCRFile *self );
gboolean gwp_vcrfile_2nd_side_is_planet( GwpVCRFile *self );
gint gwp_vcrfile_get_mass( GwpVCRFile *self, gint side );
gchar* gwp_vcrfile_get_shipname( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_damage( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_shields( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_crew( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_shipid( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_owner( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_type_of_beams( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_beams( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_bays( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_type_of_torpedos( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_torpedos( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_fighters( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_tubes( GwpVCRFile *self, gint side );

gint gwp_vcrfile_get_word( FILE *from );
gint gwp_vcrfile_get_byte( FILE *from );
gint gwp_vcrfile_get_gchars( FILE *from, gchar *to, gint len );
/*
 * Standard defines.
 */
#define GWP_VCRFILE_TYPE            (gwp_vcrfile_get_type())
#define GWP_VCRFILE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_VCRFILE_TYPE, GwpVCRFile))
#define GWP_VCRFILE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_VCRFILE_TYPE, GwpVCRFileClass))
#define GWP_IS_VCRFILE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_VCRFILE_TYPE))
#define GWP_IS_VCRFILE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_VCRFILE_TYPE))
#define GWP_VCRFILE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_VCRFILE_TYPE, GwpVCRFileClass))

#endif
