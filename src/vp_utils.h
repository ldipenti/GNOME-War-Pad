/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002 Lucas Di Pentima <lucas@lunix.com.ar>
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
 * Misc VP utilities functions
 */

#ifndef VP_UTILS_H
#define VP_UTILS_H

#include <gnome.h>

#include "global.h"
#include "vp_types.h"

void vp_coord_v2w(gint16 x1, gint16 y1, gdouble *x2, gdouble *y2);
void vp_coord_w2v(gdouble x1, gdouble y1, gint16 *x2, gint16 *y2);

GList *load_xyplan(gchar *xyplan_file);
GList *load_shipxy(gint race);
GHashTable *load_pdata(void);
GHashTable *load_sdata(void);
GHashTable *load_target(gint race);
GList *load_pnames_file(gchar *pnames_file);
void load_object_per_quad (gpointer obj, GSList * obj_per_quad[TOTAL_QUADS], double wx, gdouble wy);
//void load_ships_per_quad(GnomeCanvasItem *ship, GSList *ships_per_quad[TOTAL_QUADS]);

gint16 getWord(guchar* p);
gint32 getDWord(guchar* p);

void init_data(void);

gboolean vp_can_unpack(gchar *game_dir, gint race);

#endif
