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
    Revision 1.18  2005/05/31 13:17:38  ldipenti
    Feature: Added CVS metadata on source files

*/

/*
 * GwpPlanet:
 * ---------
 *
 * This class represents the different planets on the game.
 */

#ifndef GWP_PLANET_H
#define GWP_PLANET_H

#include <glib.h>
#include <glib-object.h>

#include "gwp-object.h"

/*
 * Type macros.
 */
typedef struct _GwpPlanet GwpPlanet;
typedef struct _GwpPlanetClass GwpPlanetClass;
typedef struct _GwpPlanetPrivate GwpPlanetPrivate;

struct _GwpPlanet {
  GwpObject parent;

  /* instance members */

  /* private */
  GwpPlanetPrivate *priv;
};

struct _GwpPlanetClass {
  GwpObjectClass parent;
  /* class members */
};

/* This is included here because of the cyclic needs of types between
   GwpStarbase and GwpPlanet */
#include "gwp-starbase.h"

/* used by GWP_PLANET_TYPE */
GType gwp_planet_get_type (void);

/*
 * Public method definitions.
 */
GwpPlanet * gwp_planet_new (void);

/**********************/
/* High-level methods */
/**********************/
gchar * gwp_planet_get_def_sys_beams_type_str (GwpPlanet *self);
gint gwp_planet_get_def_sys_beams_type (GwpPlanet *self);
gint gwp_planet_get_def_sys_beams_nr(GwpPlanet *self);
gint gwp_planet_get_def_sys_fighters_nr(GwpPlanet *self);
gint gwp_planet_get_def_sys_fighter_bays(GwpPlanet *self);
gint gwp_planet_get_def_sys_battle_mass(GwpPlanet *self);

gint gwp_planet_get_col_growth_limit(GwpPlanet *self);
gint gwp_planet_get_nat_growth_limit(GwpPlanet *self);
GwpPlanet * gwp_planet_copy (GwpPlanet *self);
GwpPlanet * gwp_planet_get(GHashTable *list, gint planet_id);
gboolean gwp_planet_is_mine (GwpPlanet *self);
gboolean gwp_planet_is_unowned (GwpPlanet *self);
gint gwp_planet_what_is (GwpPlanet *self);
gint16 gwp_planet_get_temperature_f (GwpPlanet *self);
gchar * gwp_planet_get_temperature_str(GwpPlanet *self);
gint gwp_planet_get_visibility(GwpPlanet *self);
gint gwp_planet_get_happiness_col_change(GwpPlanet *self);
gint gwp_planet_get_happiness_nat_change (GwpPlanet *self);
gchar * gwp_planet_get_natives_race_chars (GwpPlanet *self);
gchar * gwp_planet_get_natives_spi_chars (GwpPlanet *self);
gboolean gwp_planet_has_starbase (GwpPlanet *self);
gdouble gwp_planet_get_ground_percent(gint mineral);
gint gwp_planet_neutronium_extraction_rate(GwpPlanet *self);
gint gwp_planet_neutronium_turns_left(GwpPlanet *self);
gint gwp_planet_tritanium_extraction_rate(GwpPlanet *self);
gint gwp_planet_tritanium_turns_left(GwpPlanet *self);
gint gwp_planet_molybdenum_extraction_rate(GwpPlanet *self);
gint gwp_planet_molybdenum_turns_left(GwpPlanet *self);
gint gwp_planet_duranium_extraction_rate(GwpPlanet *self);
gint gwp_planet_duranium_turns_left(GwpPlanet *self);
gint gwp_planet_get_tax_collected_colonists(GwpPlanet *self);
gint gwp_planet_get_tax_collected_natives(GwpPlanet *self);
gint gwp_planet_get_tax_collected_natives_max(GwpPlanet *self);
gint gwp_planet_calculate_allowed_factories (GwpPlanet *self);
gint gwp_planet_calculate_allowed_mines (GwpPlanet *self);
gint gwp_planet_calculate_allowed_defenses (GwpPlanet *self);

/*******************/
/* Get/Set methods */
/*******************/
gboolean gwp_planet_is_known (GwpPlanet *self);
void gwp_planet_set_is_known (GwpPlanet *self, gboolean is_known);
void gwp_planet_set_starbase (GwpPlanet *self, GwpStarbase *sb);
GwpStarbase * gwp_planet_get_starbase (GwpPlanet *self);

gint16 gwp_planet_get_owner (GwpPlanet *self);
void gwp_planet_set_owner (GwpPlanet *self, gint16 o);
gchar * gwp_planet_get_fcode (GwpPlanet *self);
void gwp_planet_set_fcode (GwpPlanet *self, gchar *fcode);
gint16 gwp_planet_get_mines (GwpPlanet *self);
void gwp_planet_set_mines (GwpPlanet *self, gint16 m);
gint16 gwp_planet_get_factories (GwpPlanet *self);
void gwp_planet_set_factories (GwpPlanet *self, gint16 f);
gint16 gwp_planet_get_defense_posts (GwpPlanet *self);
void gwp_planet_set_defense_posts (GwpPlanet *self, gint16 d);
gint32 gwp_planet_get_mined_neutronium (GwpPlanet *self);
void gwp_planet_set_mined_neutronium (GwpPlanet *self, gint32 mn);
gint32 gwp_planet_get_mined_tritanium (GwpPlanet *self);
void gwp_planet_set_mined_tritanium (GwpPlanet *self, gint32 mt);
gint32 gwp_planet_get_mined_duranium (GwpPlanet *self);
void gwp_planet_set_mined_duranium (GwpPlanet *self, gint32 md);
gint32 gwp_planet_get_mined_molybdenum (GwpPlanet *self);
void gwp_planet_set_mined_molybdenum (GwpPlanet *self, gint32 mm);
gint32 gwp_planet_get_colonists (GwpPlanet *self);
void gwp_planet_set_colonists (GwpPlanet *self, gint32 col);
gint32 gwp_planet_get_supplies (GwpPlanet *self);
void gwp_planet_set_supplies (GwpPlanet *self, gint32 sup);
gint32 gwp_planet_get_megacredits (GwpPlanet *self);
void gwp_planet_set_megacredits (GwpPlanet *self, gint32 mc);
gint32 gwp_planet_get_ground_neutronium (GwpPlanet *self);
void gwp_planet_set_ground_neutronium (GwpPlanet *self, gint32 gn);
gint32 gwp_planet_get_ground_tritanium (GwpPlanet *self);
void gwp_planet_set_ground_tritanium (GwpPlanet *self, gint32 gt);
gint32 gwp_planet_get_ground_duranium (GwpPlanet *self);
void gwp_planet_set_ground_duranium (GwpPlanet *self, gint32 gd);
gint32 gwp_planet_get_ground_molybdenum (GwpPlanet *self);
void gwp_planet_set_ground_molybdenum (GwpPlanet *self, gint32 gm);
gint16 gwp_planet_get_dens_neutronium (GwpPlanet *self);
void gwp_planet_set_dens_neutronium (GwpPlanet *self, gint16 dn);
gint16 gwp_planet_get_dens_tritanium (GwpPlanet *self);
void gwp_planet_set_dens_tritanium (GwpPlanet *self, gint16 dt);
gint16 gwp_planet_get_dens_duranium (GwpPlanet *self);
void gwp_planet_set_dens_duranium (GwpPlanet *self, gint16 dd);
gint16 gwp_planet_get_dens_molybdenum (GwpPlanet *self);
void gwp_planet_set_dens_molybdenum (GwpPlanet *self, gint16 dm);
gint16 gwp_planet_get_tax_colonists (GwpPlanet *self);
void gwp_planet_set_tax_colonists (GwpPlanet *self, gint16 tc);
gint16 gwp_planet_get_tax_natives (GwpPlanet *self);
void gwp_planet_set_tax_natives (GwpPlanet *self, gint16 tn);
gint16 gwp_planet_get_happiness_colonists (GwpPlanet *self);
void gwp_planet_set_happiness_colonists (GwpPlanet *self, gint16 tc);
gint16 gwp_planet_get_happiness_natives (GwpPlanet *self);
void gwp_planet_set_happiness_natives (GwpPlanet *self, gint16 tn);
gint16 gwp_planet_get_natives_spi (GwpPlanet *self);
void gwp_planet_set_natives_spi (GwpPlanet *self, gint16 spi);
gint32 gwp_planet_get_natives (GwpPlanet *self);
void gwp_planet_set_natives (GwpPlanet *self, gint32 nat);
gint16 gwp_planet_get_natives_race (GwpPlanet *self);
void gwp_planet_set_natives_race (GwpPlanet *self, gint16 nr);
gint16 gwp_planet_get_temperature (GwpPlanet *self);
void gwp_planet_set_temperature (GwpPlanet *self, gint16 temp);
gint16 gwp_planet_get_build_base (GwpPlanet *self);
void gwp_planet_set_build_base (GwpPlanet *self, gint16 bb);
gint gwp_planet_get_mining_rate (GwpPlanet *self);
gint gwp_planet_get_tax_rate_colonists (GwpPlanet *self);
gint gwp_planet_get_tax_rate_natives (GwpPlanet *self);

/*
 * Standard defines.
 */
#define GWP_TYPE_PLANET (gwp_planet_get_type())
#define GWP_PLANET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_TYPE_PLANET, GwpPlanet))
#define GWP_PLANET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_TYPE_PLANET, GwpPlanetClass))
#define GWP_IS_PLANET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_TYPE_PLANET))
#define GWP_IS_PLANET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_TYPE_PLANET))
#define GWP_PLANET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_TYPE_PLANET, GwpPlanetClass))

#endif
