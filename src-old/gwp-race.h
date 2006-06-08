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
    Revision 1.2  2005/05/31 13:17:39  ldipenti
    Feature: Added CVS metadata on source files

*/

/*
 * GwpRace:
 * ---------
 *
 * This class provides information about the different player races, their
 * names and possibly their configuration data.
 */

#ifndef GWP_RACE_H
#define GWP_RACE_H

#include <glib.h>
#include <glib-object.h>

/*
 * Type macros.
 */

typedef struct _GwpRace GwpRace;
typedef struct _GwpRaceClass GwpRaceClass;
typedef struct _GwpRacePrivate GwpRacePrivate;

struct _GwpRace {
  GObject parent;

  /* instance members */

  /* private */
  GwpRacePrivate *priv;
};

struct _GwpRaceClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_RACE_TYPE */
GType gwp_race_get_type (void);

/*
 * Public method definitions.
 */
GwpRace *gwp_race_new (void);


/*******************/
/* Get-Set methods */
/*******************/
void gwp_race_set_long_desc (GwpRace *self, gchar *name);
gchar * gwp_race_get_long_desc (GwpRace *self);
void gwp_race_set_short_desc (GwpRace *self, gchar *name);
gchar * gwp_race_get_short_desc (GwpRace *self);
void gwp_race_set_adjective (GwpRace *self, gchar *name);
gchar * gwp_race_get_adjective (GwpRace *self);


/*
 * Standard defines.
 */
#define GWP_TYPE_RACE            (gwp_race_get_type())
#define GWP_RACE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_RACE, GwpRace))
#define GWP_RACE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_RACE, GwpRaceClass))
#define GWP_IS_RACE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_RACE))
#define GWP_IS_RACE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_RACE))
#define GWP_RACE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_RACE, GwpRaceClass))

#endif
