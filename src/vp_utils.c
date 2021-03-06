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

/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.79  2005/09/26 18:03:14  ldipenti
    Typo: some g_message() left behind... :-)

    Revision 1.78  2005/09/26 17:53:09  ldipenti
    Bugfix: when some regexp don't match when scanning messages, some empty glists were tried to be freed, this wasn't necessary.

    Revision 1.77  2005/07/11 15:19:48  ldipenti
    Bugfix: gcc-4 compile errors fixed

    Revision 1.76  2005/06/02 14:36:05  ldipenti
    Feature: patched applied to parse host configuration messages, thanks François!!!

    Revision 1.75  2005/05/31 13:17:39  ldipenti
    Feature: Added CVS metadata on source files

*/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef USE_PYTHON
#  include "gwp-python.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gnome.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pcre.h>

#include "global.h"
#include "gwp-game-state.h"
#include "vp_utils.h"
#include "vp_types.h"
#include "starchart.h"
#include "gwp-planet.h"
#include "gwp-starbase.h"
#include "gwp-ship.h"
#include "gwp-minefield.h"
#include "gwp-ion-storm.h"
#include "gwp-specs.h"
#include "gwp-utils.h"
#include "gwp-messages.h"
#include "gwp-race.h"
#include "gwp-messages.h"

/* Macro use to type conversion :/. string to boolean */
#define YES_OR_NO(x) (x == "YES" ? TRUE : FALSE)

void load_target_dat_ext (GHashTable *target_list, gint race, char *e);

void scan_messages (void);
void scan_messages_planet_orbit (const gchar *msg_body);
void scan_messages_planet_scanned (const gchar *msg_body);
void scan_messages_recycle_rate(const gchar *msg_body);
void scan_messages_att_rat(const gchar *msg_body);
void scan_messages_def_rat(const gchar *msg_body);
void scan_messages_fig_starb(const gchar *msg_body);
void scan_messages_min_rat(const gchar *msg_body);
void scan_messages_tax_rat(const gchar *msg_body);
void scan_messages_min_sweep(const gchar *msg_body);
void scan_messages_shipt_tow(const gchar *msg_body);
void scan_messages_in_pla(const gchar *msg_body);
void scan_messages_fuel_ly(const gchar *msg_body);
void scan_messages_allies(const gchar *msg_body);

int extract_from_message (const gchar *msg_body, const gchar *pattern, GList *info);
void free_substring(GList *substring);


static void dump_to_ship_dat_file (void);
static void dump_to_pdata_dat_file (void);
static void dump_to_bdata_dat_file (void);

static void ghfunc_dump_ship_data (gpointer key, gpointer value, gpointer user_data);
static void ghfunc_dump_planet_data (gpointer key, gpointer value, gpointer user_data);
static void ghfunc_dump_starbase_data (gpointer key, gpointer value, gpointer user_data);

static gint16 getWord(guchar* p);
static void setWord (gchar * buf, gint16 p);
static void setDWord (gchar * buf, gint32 p);
static gint32 getDWord(guchar* p);
static GHashTable *target_list;
static gchar *padstr(gchar *str, gint qty);

#ifdef USE_PYTHON
static gboolean python_loaded = FALSE;
#endif

/*
 * Data Loading Init Function
 */
void init_data (void)
{
  /* Game state initializations */

  race_list = load_race();
  g_message ("RACE.NM loaded...");
  target_list = load_target (gwp_game_state_get_race(game_state));
  g_message ("TARGET loaded...");
  load_kore_data();
  g_message("KOREx loaded...");
  planet_list = load_pdata();
  g_message ("PDATA loaded...");
  ship_list = load_sdata();
  g_message ("SDATA loaded...");
  load_gen_data();
  g_message("GENx loaded...");
  load_bdata();
  g_message("BDATA loaded...");
  hullspec_list = load_hullspec();
  g_message("HULLSPEC.DAT loaded...");
  engspec_list = load_engspec();
  g_message("ENGSPEC.DAT loaded...");
  torpspec_list = load_torpspec();
  g_message("TORPSPEC.DAT loaded...");
  beamspec_list = load_beamspec();
  g_message("BEAMSPEC.DAT loaded...");
  load_truehull_data();
  g_message("TRUEHULL loaded...");
  g_message("Scanning Messages...");
  scan_messages();
  g_message("Messages Scanned!");
  g_message("Running Game State post-initialization");
  gwp_game_state_postinit(game_state);
  g_message("Post-init done!");

#ifdef USE_PYTHON
  if (! python_loaded)
    gwp_python_inittab();
  python_loaded = TRUE;
#endif

}

/*
 * Helper Loading functions
 */
static gint16 getWord (guchar * p)
{
  return 256 * p[1] + p[0];
}

static void setWord (gchar * buf, gint16 p)
{ 
  if (p < 0) {
    p = (65536 + p);
  }

  buf[1] = (gchar)(p >> 8);
  buf[0] = (gchar)(p % 256);
}

static void setDWord (gchar * buf, gint32 p)
{ 
  if (p < 0) {
    p = (16777216 + p);
  }

  buf[3] = (gchar)(p >> 24) & 0x000000ff;
  buf[2] = (gchar)(p >> 16) & 0x000000ff;
  buf[1] = (gchar)(p >> 8) & 0x000000ff;
  buf[0] = (gchar)(p % 256);
}

static gint32 getDWord (guchar * p)
{
  return 16777216 * p[3] + 65536 * p[2] + 256 * p[1] + p[0];
}

/**
 * Converts VP coords to Canvas World Coord system
 */
void vp_coord_v2w (gint16 x1, gint16 y1, gdouble * x2, gdouble * y2)
{
  if(x1 >= 1000 && x1 <= 3000 && y1 >= 1000 && y1 <= 3000) {
    /* Convert X coordinate */
    *x2 = (gdouble) x1 - 1000 + CANVAS_OFFSET_INT;
    
    /* Convert Y coordinate */
    *y2 = (gdouble) abs (y1 - 3000) + CANVAS_OFFSET_INT;
  } else {      
    /* Assign "dummy" values */
    *x2 = 0.0;
    *y2 = 0.0;
  }
}

/**
 * Converts Canvas World Coord system to VP coords
 */
void vp_coord_w2v (gdouble x1, gdouble y1, gint16 * x2, gint16 * y2)
{
  /* Convert X coordinate */
  *x2 = (gint16) x1 + 1000 - CANVAS_OFFSET_INT;
  *y2 = (gint16) abs (y1 - 3000) + CANVAS_OFFSET_INT;
}

/**
 * Loads planets names into a list
 */
GList * load_pnames_file (gchar * pnames_file)
{
  gchar *tmp = NULL;
  FILE *pname = NULL;
  GList *pname_list = NULL;
  GString *pnames_str;

  /* Initialize filename string */
  pnames_str = g_string_new (pnames_file);
  pnames_str = g_string_up (pnames_str);

  /* Check file and try to open it */
  if ((pname = fopen (gwp_game_state_get_full_path(game_state, pnames_str->str), "r")) == NULL) {
    pnames_str = g_string_down (pnames_str);
    if ((pname = fopen (gwp_game_state_get_full_path(game_state, pnames_str->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, pnames_str->str));
      g_string_free(pnames_str, TRUE);
      exit (-1);
    }
  }
  rewind (pname);

  while (!feof(pname)) {
    tmp = (gchar *) g_malloc(sizeof(gchar[21]));
    fread (tmp, sizeof(gchar[20]), 1, pname);
    tmp[20] = (gchar) NULL;
    pname_list = g_list_append(pname_list, g_strchomp(tmp));
  }
  fclose (pname);
  g_string_free(pnames_str, TRUE);

  return pname_list;
}

/**
 * Loads planets coordinates into a list
 */
GList * load_xyplan (gchar * xyplan_file)
{
  FILE *xyplan;
  GList *coords_list = NULL;
  VpXYPlanReg coords, *tmp;
  GString *xyplan_str;
  size_t result;
  
  xyplan_str = g_string_new (xyplan_file);
  xyplan_str = g_string_up (xyplan_str);
  
  if ((xyplan = fopen (gwp_game_state_get_full_path(game_state, xyplan_str->str), "r")) == NULL) {
    xyplan_str = g_string_down (xyplan_str);
    if ((xyplan =
	 fopen (gwp_game_state_get_full_path(game_state, xyplan_str->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, xyplan_str->str));
      exit (-1);
    }
  }
  
  rewind (xyplan);
  while (!feof (xyplan)) {
    result = fread (&coords, sizeof (VpXYPlanReg), 1, xyplan);
    if (result == 1) {

      /* Copy planet to tmp variable to assign it in GList */
      tmp = g_malloc (sizeof (VpXYPlanReg));
      *tmp = coords;
      
      /* Append object to list */
      coords_list = g_list_append (coords_list, tmp);
    } else {
      if (result != 0)
	g_message ("WARNING: Maybe XYPLAN.DAT file is corrupted? Some unknown trailing data was found. Number of registers read: %d", result);
    }
  }
  fclose (xyplan);

  return coords_list;
}

/* 
 * Dummy function that loads TARGETx.DAT and TARGETx.EXT on a hash table
 * FIXME: This could be wrong, but I'm using it for now because I use
 * PCC and CCUnpack leaves the rest of the targets on *.EXT
 * NOTE: Make our unpacker do that too!
 */
GHashTable * load_target (gint race)
{
  GHashTable *target_list = g_hash_table_new (NULL, NULL);
  GString *target_file = NULL;

  load_target_dat_ext (target_list, race, "DAT");

  /* Initialize file name */
  target_file = g_string_new ("TARGET");
  target_file =
    g_string_append (target_file, g_strdup_printf ("%d.EXT", race));

  /* FIXME: this sucks! */
  /* Test if targetx.ext exists, and load its data */
  if (g_file_test (gwp_game_state_get_full_path(game_state, target_file->str), 
		   G_FILE_TEST_IS_REGULAR) ||
      g_file_test (gwp_game_state_get_full_path(game_state, 
				      g_string_down(target_file)->str), 
		   G_FILE_TEST_IS_REGULAR)) {
    load_target_dat_ext (target_list, race, "EXT");
  }

  return target_list;
}

/* This loads data to passed hash table from targetx.? file */
void load_target_dat_ext (GHashTable *target_list, gint race, char *e)
{
  FILE *target;
  GString *target_file;
  VpTargetReg target_reg, *tmp;
  gint16 i, target_nr;
  gchar buffer[34];
  
  /* Initialize file name */
  target_file = g_string_new ("TARGET");
  target_file =
    g_string_append (target_file, g_strdup_printf ("%d.%s", race, e));
  
  if ((target = fopen(gwp_game_state_get_full_path(game_state, target_file->str), "r")) == NULL) {
    target_file = g_string_down (target_file);
    if ((target =
	 fopen (gwp_game_state_get_full_path(game_state, target_file->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, target_file->str));
      exit (-1);
    }
  }
  
  rewind (target);
  fread (&target_nr, sizeof (gint16), 1, target);

  /* read registers */
  for (i = 0; i < target_nr; i++) {
    fread (buffer, 34, 1, target);
    
    target_reg.id = getWord (buffer);
    target_reg.owner = getWord (buffer + 2);
    target_reg.warp_factor = getWord (buffer + 4);
    target_reg.x = getWord (buffer + 6);
    target_reg.y = getWord (buffer + 8);
    target_reg.hull_type = getWord (buffer + 10);
    target_reg.heading = getWord (buffer + 12);
    target_reg.name[0] = buffer[14];
    target_reg.name[1] = buffer[15];
    target_reg.name[2] = buffer[16];
    target_reg.name[3] = buffer[17];
    target_reg.name[4] = buffer[18];
    target_reg.name[5] = buffer[19];
    target_reg.name[6] = buffer[20];
    target_reg.name[7] = buffer[21];
    target_reg.name[8] = buffer[22];
    target_reg.name[9] = buffer[23];
    target_reg.name[10] = buffer[24];
    target_reg.name[11] = buffer[25];
    target_reg.name[12] = buffer[26];
    target_reg.name[13] = buffer[27];
    target_reg.name[14] = buffer[28];
    target_reg.name[15] = buffer[29];
    target_reg.name[16] = buffer[30];
    target_reg.name[17] = buffer[31];
    target_reg.name[18] = buffer[32];
    target_reg.name[19] = buffer[33];
    target_reg.name[20] = '\0';
    
    /* Assign new memory for new target */
    tmp = g_malloc (sizeof (VpTargetReg));
    *tmp = target_reg;
    /* Add new target */
    g_hash_table_insert (target_list, (gpointer)(gint)tmp->id, tmp);
  }
  fclose (target);
}

/*
 * Loads ships coordinates into a list
 */
GList * load_shipxy (gint race)
{
  FILE *shipxy;
  GList *coords_list = NULL;
  GString *shipxy_file;
  VpShipXYReg coords, *tmp;
  gint i;
  
  shipxy_file = g_string_new ("SHIPXY");
  shipxy_file =
    g_string_append (shipxy_file, g_strdup_printf ("%d.DAT", race));
  
  if ((shipxy = fopen(gwp_game_state_get_full_path(game_state, shipxy_file->str), "r")) == NULL) {
    shipxy_file = g_string_down (shipxy_file);
    if ((shipxy =
	 fopen (gwp_game_state_get_full_path(game_state, shipxy_file->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, shipxy_file->str));
      exit (-1);
    }
  }
  
  rewind (shipxy);

  for (i = 0; i < MAX_SHIPS; i++) {
    fread (&coords, sizeof (VpShipXYReg), 1, shipxy);
    
    /* Copy ship to tmp variable to assign it in GList */
    tmp = g_malloc (sizeof (VpShipXYReg));
    *tmp = coords;
    
    /* Append object to list */
    coords_list = g_list_append (coords_list, tmp);
  }
  fclose (shipxy);
  
  return coords_list;
}

/*
 * Loads Ship Data on GHashTable
 */
GHashTable * load_sdata (void)
{
  GList *shipxy_list;
  GString *sdata_dat_file;
  FILE *sdata = NULL;
  VpShipXYReg *coords = NULL;
  GwpShip *s;
  GHashTable *ship_list = NULL;
  VpTargetReg *target_reg;
  gint i, idx;
  gint16 ships_nr;
  gchar buffer[107];
  gchar *fc_tmp, *name_tmp;
  
  /* Load temp SHIPXY data */
  shipxy_list = load_shipxy (gwp_game_state_get_race(game_state));
  g_message ("SHIPXY loaded...");

  sdata_dat_file =
    g_string_new (g_strdup_printf ("SHIP%d.DAT", 
				   gwp_game_state_get_race(game_state)));
  
  /* Init Ship Hash */
  ship_list = g_hash_table_new (NULL, NULL);
  
  /* Load Ship Data */
  if (g_file_test (gwp_game_state_get_full_path(game_state, 
						sdata_dat_file->str),
		   G_FILE_TEST_EXISTS)) {
    if ((sdata =
	 fopen (gwp_game_state_get_full_path(game_state, sdata_dat_file->str),
		"r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, sdata_dat_file->str));
      exit (-1);
    }
  } else {
    sdata_dat_file = g_string_down (sdata_dat_file);
    if (g_file_test (gwp_game_state_get_full_path(game_state, sdata_dat_file->str),
		     G_FILE_TEST_EXISTS)) {
      if ((sdata =
	   fopen (gwp_game_state_get_full_path(game_state, sdata_dat_file->str),
		  "r")) == NULL) {
	g_message ("ERROR trying to open %s file.",
		   gwp_game_state_get_full_path(game_state, sdata_dat_file->str));
	exit (-1);
      }
    } else {
      g_message ("ERROR: %s file not found.\n",
		 gwp_game_state_get_full_path(game_state, sdata_dat_file->str));
      exit (-1);
    }
  }
  rewind (sdata);
  /* How many ships? */
  fread (&ships_nr, sizeof (gint16), 1, sdata);

  for (i = 0; i < ships_nr; i++) {
    /* Read Ship data from file */
    fread (buffer, 107, 1, sdata);
    
    /*  Instantiate new ship */
    s = gwp_ship_new();

    /* Load Ship Data on struct */
    gwp_object_set_id (GWP_OBJECT(s), getWord(buffer));
    gwp_ship_set_owner (s, getWord(buffer + 2));

    /* Friendly code assembly */
    fc_tmp = g_malloc (sizeof(gchar)*4);
    fc_tmp[0] = buffer[4];
    fc_tmp[1] = buffer[5];
    fc_tmp[2] = buffer[6];
    fc_tmp[3] = '\0';
    gwp_ship_set_fcode(s, fc_tmp);
    g_free(fc_tmp);

    gwp_flying_object_set_speed (GWP_FLYING_OBJECT(s), getWord(buffer + 7));
    gwp_ship_set_x_to_waypoint (s, getWord(buffer + 9));
    gwp_ship_set_y_to_waypoint (s, getWord(buffer + 11));
    gwp_object_set_x_coord (GWP_OBJECT(s), getWord(buffer + 13));
    gwp_object_set_y_coord (GWP_OBJECT(s), getWord(buffer + 15));

    gwp_ship_set_engines_type (s, getWord(buffer + 17));
    gwp_ship_set_hull_type (s, getWord(buffer + 19));
    gwp_ship_set_beams_type (s, getWord(buffer + 21));
    gwp_ship_set_beams (s, getWord(buffer + 23));
    gwp_ship_set_fighter_bays (s, getWord(buffer + 25));

    /* Check if its a torp or carrier ship */
    if (gwp_ship_get_fighter_bays (s) == 0) {
      gwp_ship_set_torps_type (s, getWord(buffer + 27));
      gwp_ship_set_torps (s, getWord(buffer + 29));
      gwp_ship_set_torps_launchers (s, getWord(buffer + 31));
    } else {
      gwp_ship_set_torps_type (s, 0);
      gwp_ship_set_fighters (s, getWord(buffer + 29));
      gwp_ship_set_torps_launchers (s, 0);      
    }

    gwp_ship_set_mission (s, getWord(buffer + 33));
    gwp_ship_set_primary_enemy (s, getWord(buffer + 35));
    gwp_ship_set_tow_ship_id (s, getWord(buffer + 37));
    gwp_ship_set_damage (s, getWord(buffer + 39));
    gwp_ship_set_crew (s, getWord(buffer + 41));
    gwp_ship_set_colonists (s, getWord(buffer + 43));

    name_tmp = g_malloc (sizeof(gchar)*21);
    for (idx = 0; idx <= 19; idx++) {
      name_tmp[idx] = buffer[45+idx];
    }
    name_tmp[20] = '\0';
    gwp_object_set_name (GWP_OBJECT(s), g_string_new(name_tmp)->str);
    g_free(name_tmp);

    gwp_ship_set_neutronium (s, getWord(buffer + 65));
    gwp_ship_set_tritanium (s, getWord(buffer + 67));
    gwp_ship_set_duranium (s, getWord(buffer + 69));
    gwp_ship_set_molybdenum (s, getWord(buffer + 71));
    gwp_ship_set_supplies (s, getWord(buffer + 73));

    gwp_ship_set_unload_neutronium (s, getWord(buffer + 75));
    gwp_ship_set_unload_tritanium (s, getWord(buffer + 77));
    gwp_ship_set_unload_duranium (s, getWord(buffer + 79));
    gwp_ship_set_unload_molybdenum (s, getWord(buffer + 81));
    gwp_ship_set_unload_colonists (s, getWord(buffer + 83));
    gwp_ship_set_unload_supplies (s, getWord(buffer + 85));
    gwp_ship_set_unload_planet_id (s, getWord(buffer + 87));

    gwp_ship_set_transfer_neutronium (s, getWord(buffer + 89));
    gwp_ship_set_transfer_tritanium (s, getWord(buffer + 91));
    gwp_ship_set_transfer_duranium (s, getWord(buffer + 93));
    gwp_ship_set_transfer_molybdenum (s, getWord(buffer + 95));
    gwp_ship_set_transfer_colonists (s, getWord(buffer + 97));
    gwp_ship_set_transfer_supplies (s, getWord(buffer + 99));
    gwp_ship_set_transfer_ship_id (s, getWord(buffer + 101));

    gwp_ship_set_intercept_ship_id (s, getWord(buffer + 103));
    gwp_ship_set_megacredits (s, getWord(buffer + 105));
    
    /* Calculate heading from other data */
    gwp_flying_object_set_heading(GWP_FLYING_OBJECT(s), gwp_ship_calculate_heading(s));

    /* Add ship to list */
    g_hash_table_insert (ship_list, 
			 (gpointer)(gint)gwp_object_get_id (GWP_OBJECT(s)), s);
  }

  /* Now add the rest unknown ships */
  for (i = 0; i < g_list_length (shipxy_list); i++) {

    /* Check if we have not this ship */
    if (gwp_ship_get (ship_list, i + 1) == NULL) {

      s = gwp_ship_new();

      /* If we have more data on TARGETx.DAT, we add it */
      if ((target_reg =
	   g_hash_table_lookup (target_list,
				(gconstpointer) (i + 1))) != NULL) {
	gwp_object_set_id (GWP_OBJECT(s), target_reg->id);
	gwp_object_set_name (GWP_OBJECT(s), g_string_new(target_reg->name)->str);
	gwp_flying_object_set_speed (GWP_FLYING_OBJECT(s), target_reg->warp_factor);
	gwp_flying_object_set_heading (GWP_FLYING_OBJECT(s), target_reg->heading);
	gwp_ship_set_hull_type (s, target_reg->hull_type);
	gwp_ship_set_owner (s, target_reg->owner);
      }

      coords = g_list_nth_data (shipxy_list, i);
      gwp_object_set_x_coord (GWP_OBJECT(s), coords->x);
      gwp_object_set_y_coord (GWP_OBJECT(s), coords->y);
      gwp_ship_set_mass_if_unknown (s, coords->mass);
      
      /* Add ship to list */
      g_hash_table_insert (ship_list, (gpointer)(i + 1), s);
    } 
  }
  fclose (sdata);
  return ship_list;
}

/*
 * Loads Planetary Data on a GHashTable
 */
GHashTable * load_pdata (void)
{
  GList *xyplanet_list;
  GString *pdata_dat_file;
  FILE *pdata = NULL;
  VpXYPlanReg *coords = NULL;
  GHashTable *planet_list = NULL;
  GList *pnames = NULL;
  gint16 planets_nr;
  gint i;
  gchar buffer[85];
  GwpPlanet *p;
  gchar *fc_tmp;

  /* Load temp planets coord data */
  xyplanet_list = load_xyplan(XYPLAN);
  g_message ("XYPLAN loaded...");

  pdata_dat_file =
    g_string_new (g_strdup_printf ("PDATA%d.DAT", gwp_game_state_get_race(game_state)));

  /* Init Planet Hash */
  planet_list = g_hash_table_new (NULL, NULL);

  /* Load Additional Data */
  pnames = load_pnames_file(PNAMES);

  /* Load Planet Data... */
  if (g_file_test (gwp_game_state_get_full_path(game_state, pdata_dat_file->str),
		   G_FILE_TEST_EXISTS)) {
    if ((pdata =
	 fopen (gwp_game_state_get_full_path(game_state, pdata_dat_file->str),
		"r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, pdata_dat_file->str));
      exit (-1);
    }
  } else {
    pdata_dat_file = g_string_down (pdata_dat_file);
    if (g_file_test (gwp_game_state_get_full_path(game_state, pdata_dat_file->str),
		     G_FILE_TEST_EXISTS)) {
      if ((pdata =
	   fopen (gwp_game_state_get_full_path(game_state, pdata_dat_file->str),
		  "r")) == NULL) {
	g_message ("ERROR trying to open %s file.\n",
		   gwp_game_state_get_full_path(game_state, pdata_dat_file->str));
	exit (-1);
      }
    } else {
      g_message ("ERROR: %s file not found.\n",
		 gwp_game_state_get_full_path(game_state, pdata_dat_file->str));
      exit (-1);
    }
  }
  
  rewind (pdata);

  /* How many planets? */
  fread (&planets_nr, sizeof (gint16), 1, pdata);

  for (i = 0; i < planets_nr; i++) {

    /* Instantiate new planet */
    p = gwp_planet_new();

    /* Set known flag */
    gwp_planet_set_is_known (p, TRUE);

    /* Read Planet data from file */
    fread (buffer, 85, 1, pdata);
    
    /* Load Planet Data on object */
    gwp_planet_set_owner (p, getWord (buffer));
    gwp_object_set_id (GWP_OBJECT(p), getWord (buffer+2));

    /* Friendly code assembly */
    fc_tmp = g_malloc(sizeof(gchar)*4);    
    fc_tmp[0] = buffer[4];
    fc_tmp[1] = buffer[5];
    fc_tmp[2] = buffer[6];
    fc_tmp[3] = '\0';
    gwp_planet_set_fcode (p, fc_tmp);
    g_free(fc_tmp);

    gwp_planet_set_mines (p, getWord(buffer+7));
    gwp_planet_set_factories (p, getWord(buffer+9));
    gwp_planet_set_defense_posts (p, getWord(buffer+11));
    gwp_planet_set_mined_neutronium (p, getDWord(buffer+13));
    gwp_planet_set_mined_tritanium (p, getDWord(buffer+17));
    gwp_planet_set_mined_duranium (p, getDWord(buffer+21));
    gwp_planet_set_mined_molybdenum (p, getDWord(buffer+25));
    gwp_planet_set_colonists (p, getDWord(buffer+29));
    gwp_planet_set_supplies (p, getDWord(buffer+33));
    gwp_planet_set_megacredits (p, getDWord(buffer+37));
    gwp_planet_set_ground_neutronium (p, getDWord(buffer+41));
    gwp_planet_set_ground_tritanium (p, getDWord(buffer+45));
    gwp_planet_set_ground_duranium (p, getDWord(buffer+49));
    gwp_planet_set_ground_molybdenum (p, getDWord(buffer+53));
    gwp_planet_set_dens_neutronium (p, getWord(buffer+57));
    gwp_planet_set_dens_tritanium (p, getWord(buffer+59));
    gwp_planet_set_dens_duranium (p, getWord(buffer+61));
    gwp_planet_set_dens_molybdenum (p, getWord(buffer+63));
    gwp_planet_set_tax_colonists (p, getWord(buffer+65));
    gwp_planet_set_tax_natives (p, getWord(buffer+67));
    gwp_planet_set_happiness_colonists (p, getWord(buffer+69));
    gwp_planet_set_happiness_natives (p, getWord(buffer+71));
    gwp_planet_set_natives_spi (p, getWord(buffer+73));
    gwp_planet_set_natives (p, getDWord(buffer+75));

    /* Dear Tim, please send me consistent data... */
    /* WARNING!!: This was eliminated just in case THOST don't like it */
    /*     if (gwp_planet_get_natives(p) > 0)  */
    /*       gwp_planet_set_natives_spi (p, getWord(buffer+73)); */
    /*     else */
    /*       gwp_planet_set_natives_spi (p, 0); */
    
    gwp_planet_set_natives_race (p, getWord(buffer+79));

    gwp_planet_set_temperature (p, getWord(buffer+81));
    gwp_planet_set_build_base (p, getWord(buffer+83));

    coords = g_list_nth_data (xyplanet_list, gwp_object_get_id(GWP_OBJECT(p))-1);
    gwp_object_set_x_coord (GWP_OBJECT(p), coords->x);
    gwp_object_set_y_coord (GWP_OBJECT(p), coords->y);
    gwp_object_set_name (GWP_OBJECT(p), g_string_new((gchar *)g_list_nth_data(pnames, (gint)gwp_object_get_id (GWP_OBJECT(p)) - 1))->str);

    /* All PDATAX.DAT planets are known (more o less) */
    gwp_planet_set_is_known (p, TRUE);

    /* Add planet to list */
    g_hash_table_insert (planet_list, (gpointer)(gint)gwp_object_get_id(GWP_OBJECT(p)), p);
  }

  /* Now add the rest unknown planets */
  for (i = 0; i < g_list_length (xyplanet_list); i++) {

    /* Check if we have not this planet */
    if (gwp_planet_get (planet_list, i + 1) == NULL) {
      p = gwp_planet_new();

      coords = g_list_nth_data (xyplanet_list, i);

      gwp_object_set_x_coord (GWP_OBJECT(p), coords->x);
      gwp_object_set_y_coord (GWP_OBJECT(p), coords->y);
      gwp_planet_set_owner (p, -1); /* Unknown owners */
      gwp_object_set_id (GWP_OBJECT(p), i+1);
      gwp_object_set_name (GWP_OBJECT(p), g_string_new((gchar *) g_list_nth_data (pnames, i))->str);

      /* Add planet to list */
      g_hash_table_insert (planet_list, (gpointer)(i+1), p);
    }
  }
  fclose (pdata);
  
  return planet_list;
}

/* X, Y coords in world coord system... */
void load_object_per_quad (gpointer obj, 
			   GSList * obj_per_quad[TOTAL_QUADS],
			   gdouble wx, gdouble wy)
{
  gint q;
  
  if (obj != NULL) {
    q = get_quadrant (wx, wy);
    obj_per_quad[q] = g_slist_append (obj_per_quad[q], obj);
  }
}

/* Returns TRUE if the race can be unpacked on given directory */
gboolean vp_can_unpack(gchar *game_dir, gint race)
{
  struct stat rst_file;
  struct stat pdata_file;
  struct stat ship_file;
  GString *pdata, *ship, *rst;
  gchar *tmp;
  gboolean ret = FALSE;

  g_assert(game_dir != NULL);

  pdata = g_string_new ("pdata");
  ship = g_string_new ("ship");
  rst = g_string_new ("player");
  
  tmp = g_strdup_printf ("%d.dat", race);
  pdata = g_string_append (pdata, tmp);
  g_free(tmp);

  tmp = g_strdup_printf ("%d.dat", race);
  ship = g_string_append (ship, tmp);
  g_free(tmp);

  tmp = g_strdup_printf ("%d.rst", race);
  rst = g_string_append (rst, tmp);
  g_free(tmp);

  pdata = g_string_prepend(pdata, g_strconcat(game_dir, "/", NULL));
  ship = g_string_prepend(ship, g_strconcat(game_dir, "/", NULL));
  rst = g_string_prepend(rst, g_strconcat(game_dir, "/", NULL));

  /* If playerN.rst exist...well... */
  if(g_file_test(rst->str, G_FILE_TEST_IS_REGULAR)) {
    stat(rst->str, &rst_file);
    /* If PDATA file exists */
    if(g_file_test(pdata->str, G_FILE_TEST_IS_REGULAR)) {
      stat(pdata->str, &pdata_file);
      /* If rst file is newer than pdata... */
      if(rst_file.st_mtime > pdata_file.st_mtime)
	ret = TRUE;
    } else if(g_file_test(ship->str, G_FILE_TEST_IS_REGULAR)) {
      stat(ship->str, &ship_file);
      /* If rst file is newer than ship... */
      if(rst_file.st_mtime > ship_file.st_mtime)
	ret = TRUE;
    } else {
      ret = TRUE;
    }
  }

  return ret;
}

/**
 * Loads race names into a list
 */
GSList *
load_race (void)
{
  FILE *race_nm = NULL;
  GString *race_file_name;
  GSList *race_list = NULL;
  gint i;

  race_file_name = g_string_new ("race.nm");

  /* Try to open RACE.NM or race.nm */
  /* Lowercase... */
  if (g_file_test (gwp_game_state_get_full_path(game_state, 
						race_file_name->str),
		   G_FILE_TEST_IS_REGULAR)) {
    race_nm = fopen (gwp_game_state_get_full_path(game_state, 
						  race_file_name->str), "rb");
  }
  /* Uppercase...*/
  else if (g_file_test (gwp_game_state_get_full_path(game_state, 
						     g_string_up(race_file_name)->str),
			G_FILE_TEST_IS_REGULAR)) {
    race_nm = fopen (gwp_game_state_get_full_path(game_state, 
						  g_string_up(race_file_name)->str),
		     "rb");
  }

  if(!race_nm) {
    g_message("ERROR trying to open %s file.",
	      gwp_game_state_get_full_path(game_state, g_string_up(race_file_name)->str));
    exit(-1);
  }
  rewind (race_nm);
  
  /* Long descriptions ... with race creation */
  for (i = 0; i < 11; i++) {
    /* Instantiate new race and add it to the list*/
    GwpRace *race = gwp_race_new ();
    race_list = g_slist_append (race_list, race);

    gchar *buffer = g_malloc (sizeof(gchar)*30+1);
    fread (buffer, 30, 1, race_nm);
    buffer[30] = '\0';
    gwp_race_set_long_desc (race, buffer);
    g_free (buffer);
  }

  /* Short descriptions */
  for (i = 0; i < 11; i++) {
    /* Get race from list instead of creating a new one */
    GwpRace *race = GWP_RACE (g_slist_nth_data(race_list, i));

    gchar *buffer = g_malloc (sizeof(gchar)*20+1);
    fread (buffer, 20, 1, race_nm);
    buffer[20] = '\0';
    gwp_race_set_short_desc (race, buffer);
    g_free (buffer);
  }

  /* Adjectives */
  for (i = 0; i < 11; i++) {
    /* Get race from list instead of creating a new one */
    GwpRace *race = GWP_RACE (g_slist_nth_data(race_list, i));

    gchar *buffer = g_malloc (sizeof(gchar)*12+1);
    fread (buffer, 12, 1, race_nm);
    buffer[12] = '\0';
    gwp_race_set_adjective (race, buffer);
    g_free (buffer);
  }

  return race_list;
}

void load_kore_data (void)
{
  FILE *kore_dat = NULL;
  GString *kore_file_name;
  gchar mf_buf[8]; /* Minefields buffer */
  gchar is_buf[12]; /* Ion Storms buffer */
  gchar avc_buf[34]; /* Additional Visual Contacts buffer */
  gint32 target_nr;
  VpTargetReg target_reg, *tmp_target_reg;
  gboolean do_warn;
  gint i;

  kore_file_name = g_string_new (g_strdup_printf("kore%d.dat",
						 gwp_game_state_get_race(game_state)));

  /* Try to open KOREx.DAT or korex.dat */
  /* Lowercase... */
  if (g_file_test (gwp_game_state_get_full_path(game_state, kore_file_name->str),
		   G_FILE_TEST_IS_REGULAR)) {
    kore_dat = fopen (gwp_game_state_get_full_path(game_state, 
						   kore_file_name->str), "r");
  } 
  /* Uppercase... */
  else if (g_file_test (gwp_game_state_get_full_path(game_state, 
					     g_string_up(kore_file_name)->str),
			  G_FILE_TEST_IS_REGULAR)) {
    kore_dat = fopen (gwp_game_state_get_full_path(game_state, 
					 g_string_up (kore_file_name)->str), 
		      "r");    
  }

  g_object_get (game_state,
		"warn-korefile", &do_warn,
		NULL);
  
  
  /* If KOREx.DAT not found, warn the user but not quit */
  if (!kore_dat) {
    /* Warn the user only once */
    if (do_warn) {
      GtkWidget *warn = NULL;
      
      warn = gwp_warning_dialog_new (game_mgr,
				     g_strdup_printf(_("KORE%d.DAT not found, some data will be missing."), 
						     gwp_game_state_get_race(game_state)),
				     _("It seems that you use the DOS RST format. The missing file provides the data about ion storms and minefields, but couldn't be found in this case. This is not a fatal error, GWP will continue loading but this data won't appear on the game."));
      gtk_dialog_run(GTK_DIALOG(warn));
      gtk_widget_destroy(warn);
      
      /* Do not bother the user with this message anymore */
      g_object_set (game_state, 
		    "warn-korefile", FALSE,
		    NULL);
    }
    /* Always write to stdout the warning */
    g_message ("ERROR trying to open %s file.",
	       gwp_game_state_get_full_path(game_state, kore_file_name->str));
    return;
  }
  rewind (kore_dat);
		    
  /* Read data from file */
  /* FIXME: Here we should load various data types...please complete */
  
  /* Load Mine fields - 500 records */
  fseek (kore_dat, 102, SEEK_SET);
  for (i = 1; i <= 500; i++) {
    fread (mf_buf, 8, 1, kore_dat);
    
    GwpMinefield *minefield = gwp_minefield_new();

    gwp_object_set_id (GWP_OBJECT(minefield), i);
    gwp_object_set_x_coord (GWP_OBJECT(minefield), getWord(mf_buf));
    gwp_object_set_y_coord (GWP_OBJECT(minefield), getWord(mf_buf + 2));
    gwp_minefield_set_radius (minefield, getWord(mf_buf + 4));
    gwp_minefield_set_owner (minefield, getWord(mf_buf + 6));

    minefield_list = g_slist_append (minefield_list, minefield);
/*    g_message ("Minefield #%d: %d,%d (%d LY) - Owner: %d", 
	       gwp_object_get_id (GWP_OBJECT(minefield)),
	       gwp_object_get_x_coord (GWP_OBJECT(minefield)),
	       gwp_object_get_y_coord (GWP_OBJECT(minefield)),
	       gwp_minefield_get_radius (minefield),
	       gwp_minefield_get_owner (minefield));
*/
  }

  /* Load Ion Storms from file */
  fseek (kore_dat, 4102, SEEK_SET);
  for (i = 1; i <= 50; i++) {
    fread (is_buf, 12, 1, kore_dat);

    GwpIonStorm *storm = gwp_ion_storm_new();

    gwp_object_set_id (GWP_OBJECT(storm), i);
    gwp_object_set_x_coord (GWP_OBJECT(storm), getWord(is_buf));
    gwp_object_set_y_coord (GWP_OBJECT(storm), getWord(is_buf + 2));
    gwp_ion_storm_set_radius (storm, getWord(is_buf + 4));
    gwp_ion_storm_set_voltage (storm, getWord(is_buf + 6));
    gwp_flying_object_set_speed (GWP_FLYING_OBJECT(storm), getWord(is_buf + 8));
    gwp_flying_object_set_heading (GWP_FLYING_OBJECT(storm), getWord(is_buf + 10));

    storm_list = g_slist_append (storm_list, storm);
/*    g_message ("Storm #%d: %d,%d (%d LY) Warp: %d Heading: %d Class: %d",
	       gwp_object_get_id (GWP_OBJECT(storm)),
	       gwp_object_get_x_coord (GWP_OBJECT(storm)),
	       gwp_object_get_y_coord (GWP_OBJECT(storm)),
	       gwp_ion_storm_get_radius (storm),
	       gwp_flying_object_get_speed (GWP_FLYING_OBJECT(storm)),
	       gwp_flying_object_get_heading (GWP_FLYING_OBJECT(storm)),
	       gwp_ion_storm_get_class (storm));
*/
  }

  /* Load Additional Visual Contacts from file */
  fseek (kore_dat, 12706, SEEK_SET);
  fread (&target_nr, sizeof(gint32), 1, kore_dat);

  for (i = 1; i <= target_nr; i++) {
    fread (avc_buf, 34, 1, kore_dat);

    target_reg.id = getWord (avc_buf);
    target_reg.owner = getWord (avc_buf + 2);
    target_reg.warp_factor = getWord (avc_buf + 4);
    target_reg.x = getWord (avc_buf + 6);
    target_reg.y = getWord (avc_buf + 8);
    target_reg.hull_type = getWord (avc_buf + 10);
    target_reg.heading = getWord (avc_buf + 12);

    /* Decrypt target name */
    gint j;
    for (j = 0; j < 20; j++) {
      target_reg.name[j] = (avc_buf[14+j] ^ (155-(j+1)));
    }
    target_reg.name[20] = '\0';

    /* Assign new memory for new target */
    tmp_target_reg = g_malloc (sizeof (VpTargetReg));
    *tmp_target_reg = target_reg;
    /* Add new target */
    g_hash_table_insert (target_list, 
			 (gpointer)(gint)tmp_target_reg->id, 
			 tmp_target_reg);
  }

  fclose (kore_dat);
}

void load_gen_data(void)
{
  FILE *gen_dat = NULL;
  GString *gen_file_name;
  gchar buffer[155];
  gchar *fullpath = NULL;

  gen_file_name = g_string_new(g_strdup_printf("gen%d.dat", 
					       gwp_game_state_get_race(game_state)));

  fullpath = gwp_game_state_get_full_path (game_state, gen_file_name->str);

  if (g_file_test(fullpath, G_FILE_TEST_EXISTS)) {
    gen_dat = fopen (fullpath, "r");
  } else {
    fullpath = gwp_game_state_get_full_path (game_state,
					     g_string_ascii_up(gen_file_name)->str);
    if (g_file_test(fullpath, G_FILE_TEST_EXISTS)) {
      gen_dat = fopen (fullpath, "r");
    }
  }
  
  if(!gen_dat) {
    g_message("ERROR trying to open %s file.",
	      gwp_game_state_get_full_path(game_state, gen_file_name->str));
    exit(-1);
  }
  rewind(gen_dat);

  /* Read data from file */
  fread(buffer, 155, 1, gen_dat);

  /* Set data to structures */
  gwp_game_state_set_turn_number(game_state, getWord(buffer + 153));

  /* Close file */
  fclose(gen_dat);
}

 void load_bdata(void)
{
  GString *bdata_dat_file;
  FILE *bdata = NULL;
  GwpStarbase *b;
  GwpPlanet *p;
  gint16 bases_nr;
  gint i, idx;
  gchar buffer[156];

  bdata_dat_file =
    g_string_new(g_strdup_printf("bdata%d.dat", 
				 gwp_game_state_get_race(game_state)));

  /* Load Base Data...*/
  if(g_file_test(gwp_game_state_get_full_path(game_state, bdata_dat_file->str),
		 G_FILE_TEST_EXISTS)) {
    if((bdata =
	fopen(gwp_game_state_get_full_path(game_state, bdata_dat_file->str),
	      "r")) == NULL) {
      g_message("ERROR trying to open %s file.",
		gwp_game_state_get_full_path(game_state, bdata_dat_file->str));
      exit(-1);
    }
  } else if(g_file_test(gwp_game_state_get_full_path(game_state, 
						     g_string_ascii_up(bdata_dat_file)->str),
			G_FILE_TEST_EXISTS)) {
    if((bdata =
	fopen(gwp_game_state_get_full_path(game_state, 
					   g_string_ascii_up(bdata_dat_file)->str),
	      "r")) == NULL) {
      g_message("ERROR trying to open %s file.",
		gwp_game_state_get_full_path(game_state, bdata_dat_file->str));
      exit(-1);
    }
  } else {
    g_message("ERROR trying to open %s file.",
	      gwp_game_state_get_full_path(game_state, bdata_dat_file->str));
    exit(-1);
  }

  rewind(bdata);

  /* Init global hash table */
  starbase_list = g_hash_table_new (NULL, NULL);

  /* How many bases? */
  fread(&bases_nr, sizeof(gint16), 1, bdata);

  for(i = 0; i < bases_nr; i++) {
    gint16 starbase_id;

    /* Read Base data from file */
    fread(buffer, 156, 1, bdata);

    /* Load Base data on struct */
    b = gwp_starbase_new();

    starbase_id = getWord (buffer);
    /* owner is skipped...it's already on planet */
    gwp_starbase_set_defense (b, getWord (buffer + 4));
    gwp_starbase_set_damage (b, getWord (buffer + 6));

    gwp_starbase_set_engines_tech (b, getWord (buffer + 8));
    gwp_starbase_set_hulls_tech (b, getWord (buffer + 10));
    gwp_starbase_set_beams_tech (b, getWord (buffer + 12));
    gwp_starbase_set_torps_tech (b, getWord (buffer + 14));

    for(idx = 0; idx <= 8; idx++) {
      gwp_starbase_set_storage_engines (b, idx, 
					getWord (buffer + (16+(idx*2))));
    }

    for(idx = 0; idx <= 19; idx++) {
      gwp_starbase_set_storage_hulls (b, idx, getWord (buffer + (34+(idx*2))));
    }

    for(idx = 0; idx <= 9; idx++) {
      gwp_starbase_set_storage_beams (b, idx, getWord (buffer + (74+(idx*2))));
    }

    for(idx = 0; idx <= 9; idx++) {
      gwp_starbase_set_storage_torp_launchers (b, idx, 
					       getWord (buffer+(94+(idx*2))));
    }

    for(idx = 0; idx <= 9; idx++) {
      gwp_starbase_set_storage_torps (b, idx, getWord (buffer+(114+(idx*2))));
    }

    gwp_starbase_set_fighters (b, getWord (buffer + 134));
    gwp_starbase_set_id_ship (b, getWord (buffer + 136));
    gwp_starbase_set_ship_action (b, getWord (buffer + 138));
    gwp_starbase_set_mission (b, getWord (buffer + 140));

    gwp_starbase_set_build_ship_type (b, getWord (buffer + 142));
    gwp_starbase_set_build_engine_type (b, getWord (buffer + 144));
    gwp_starbase_set_build_beam_type (b, getWord (buffer + 146));
    gwp_starbase_set_build_beam_count (b, getWord (buffer + 148));
    gwp_starbase_set_build_torp_type (b, getWord (buffer + 150));
    gwp_starbase_set_build_torp_count (b, getWord (buffer + 152));

    /* Add planet reference to starbase and viceversa */
    p = gwp_planet_get (planet_list, starbase_id);
    gwp_starbase_set_planet (b, p);
    gwp_planet_set_starbase (p, b);
    /* Add it to starbases global hash */
    g_hash_table_insert (starbase_list, (gpointer)(gint)gwp_starbase_get_id(b), b);
  }
  fclose(bdata);
}

GSList * load_hullspec (void)
{
  FILE *hullspec;
  GSList *hullspec_list = NULL;
  GString *hullspec_file;
  GwpHullSpec *hs;
  gint16 i, idx, hullspec_nr;
  gchar buffer[HULLSPEC_SIZE];
  gchar *name_tmp;
  
  /* Initialize file name */
  hullspec_file = g_string_new ("HULLSPEC.DAT");
  
  if ((hullspec = fopen(gwp_game_state_get_full_path(game_state, hullspec_file->str), "r")) == NULL) {
    hullspec_file = g_string_down (hullspec_file);
    if ((hullspec =
	 fopen (gwp_game_state_get_full_path(game_state, hullspec_file->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, hullspec_file->str));
      exit (-1);
    }
  }
  
  rewind (hullspec);

  hullspec_nr = 105;

  /* read registers */
  for (i = 1; i <= hullspec_nr; i++) {
    fread (buffer, HULLSPEC_SIZE, 1, hullspec);
    
    /* Instantiate new object */
    hs = gwp_hullspec_new ();

    /* Load data */
    gwp_hullspec_set_id (hs, i);

    name_tmp = g_malloc (sizeof(gchar)*31);
    for (idx = 0; idx < 30; idx++) {
      name_tmp[idx] = getWord(buffer + idx);
    }
    name_tmp[30] = '\0';
    gwp_hullspec_set_name (hs, g_string_new(g_strchomp(name_tmp))->str);
    g_free(name_tmp);

    gwp_hullspec_set_picture (hs, getWord(buffer + 30));
    gwp_hullspec_set_tritanium (hs, getWord(buffer + 34));
    gwp_hullspec_set_duranium (hs, getWord(buffer + 36));
    gwp_hullspec_set_molybdenum (hs, getWord(buffer + 38));
    
    gwp_hullspec_set_fuel_tank (hs, getWord(buffer + 40));
    gwp_hullspec_set_crew (hs, getWord(buffer + 42));
    gwp_hullspec_set_engines (hs, getWord(buffer + 44));
    gwp_hullspec_set_mass (hs, getWord(buffer + 46));
    gwp_hullspec_set_tech_level (hs, getWord(buffer + 48));
    gwp_hullspec_set_cargo (hs, getWord(buffer + 50));
    gwp_hullspec_set_fighter_bays (hs, getWord(buffer + 52));
    gwp_hullspec_set_torp_launchers (hs, getWord(buffer + 54));
    gwp_hullspec_set_beam_weapons (hs, getWord(buffer + 56));
    gwp_hullspec_set_cost (hs, getWord(buffer + 58));
    
    /* Add new hull */
    hullspec_list = g_slist_append (hullspec_list, hs);
  }
  fclose (hullspec);

  return hullspec_list;
}

GSList * load_engspec (void)
{
  FILE *engspec;
  GSList *engspec_list = NULL;
  GString *engspec_file;
  GwpEngSpec *es;
  gint16 i, idx, engspec_nr;
  gchar buffer[ENGSPEC_SIZE];
  gchar *name_tmp;
  
  /* Initialize file name */
  engspec_file = g_string_new ("ENGSPEC.DAT");
  
  if ((engspec = fopen(gwp_game_state_get_full_path(game_state, engspec_file->str), "r")) == NULL) {
    engspec_file = g_string_down (engspec_file);
    if ((engspec =
	 fopen (gwp_game_state_get_full_path(game_state, engspec_file->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, engspec_file->str));
      exit (-1);
    }
  }
  
  rewind (engspec);

  engspec_nr = 9;

  /* read registers */
  for (i = 1; i <= engspec_nr; i++) {
    fread (buffer, ENGSPEC_SIZE, 1, engspec);
    
    /* Instantiate new object */
    es = gwp_engspec_new ();

    /* Load data */
    gwp_engspec_set_id (es, i);

    name_tmp = g_malloc (sizeof(gchar)*21);
    for (idx = 0; idx < 20; idx++) {
      name_tmp[idx] = getWord(buffer + idx);
    }
    name_tmp[20] = '\0';
    gwp_engspec_set_name (es, g_string_new(g_strchomp(name_tmp))->str);
    g_free(name_tmp);

    gwp_engspec_set_cost (es, getWord(buffer + 20));
    gwp_engspec_set_tritanium (es, getWord(buffer + 22));
    gwp_engspec_set_duranium (es, getWord(buffer + 24));
    gwp_engspec_set_molybdenum (es, getWord(buffer + 26));
    
    gwp_engspec_set_tech_level (es, getWord(buffer + 28));

    for (idx = 1; idx <= 9; idx++) {
      gwp_engspec_set_fuel_usage (es, idx, getDWord(buffer + 30 + (4*(idx-1))));
    }
    
    /* Add new engine */
    engspec_list = g_slist_append (engspec_list, es);
  }
  fclose (engspec);

  return engspec_list;
}

GSList * load_torpspec (void)
{
  FILE *torpspec;
  GSList *torpspec_list = NULL;
  GString *torpspec_file;
  GwpTorpSpec *ts;
  gint16 i, idx, torpspec_nr;
  gchar buffer[TORPSPEC_SIZE];
  gchar *name_tmp;
  
  /* Initialize file name */
  torpspec_file = g_string_new ("TORPSPEC.DAT");
  
  if ((torpspec = fopen(gwp_game_state_get_full_path(game_state, torpspec_file->str), "r")) == NULL) {
    torpspec_file = g_string_down (torpspec_file);
    if ((torpspec =
	 fopen (gwp_game_state_get_full_path(game_state, torpspec_file->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, torpspec_file->str));
      exit (-1);
    }
  }
  
  rewind (torpspec);

  torpspec_nr = 10;

  /* read registers */
  for (i = 1; i <= torpspec_nr; i++) {
    fread (buffer, TORPSPEC_SIZE, 1, torpspec);
    
    /* Instantiate new object */
    ts = gwp_torpspec_new ();

    /* Load data */
    gwp_torpspec_set_id (ts, i);

    name_tmp = g_malloc (sizeof(gchar)*21);
    for (idx = 0; idx < 20; idx++) {
      name_tmp[idx] = getWord(buffer + idx);
    }
    name_tmp[20] = '\0';
    gwp_torpspec_set_name (ts, g_string_new(g_strchomp(name_tmp))->str);
    g_free(name_tmp);

    gwp_torpspec_set_ammo_cost (ts, getWord(buffer + 20));
    gwp_torpspec_set_cost (ts, getWord(buffer + 22));
    gwp_torpspec_set_tritanium (ts, getWord(buffer + 24));
    gwp_torpspec_set_duranium (ts, getWord(buffer + 26));
    gwp_torpspec_set_molybdenum (ts, getWord(buffer + 28));
    
    gwp_torpspec_set_mass (ts, getWord(buffer + 30));
    gwp_torpspec_set_tech_level (ts, getWord(buffer + 32));
    gwp_torpspec_set_kill_value (ts, getWord(buffer + 34));
    gwp_torpspec_set_damage_value (ts, getWord(buffer + 36));

    /* Add new torpedo launcher */
    torpspec_list = g_slist_append (torpspec_list, ts);
  }
  fclose (torpspec);

  return torpspec_list;
}

void load_truehull_data (void)
{
  FILE *fd;
  GString *truehull_file;
  gint i,j;
  gchar buffer[40];

  /* Init file name */
  truehull_file = g_string_new ("TRUEHULL.DAT");

  if ((fd = fopen(gwp_game_state_get_full_path(game_state, truehull_file->str), "r")) == NULL) {
    truehull_file = g_string_down (truehull_file);
    if ((fd = fopen(gwp_game_state_get_full_path(game_state, truehull_file->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, truehull_file->str));
      exit (-1);
    }
  }

  rewind (fd);

  /* Load all race data! */
  for (j = 0; j < 11; j++) {
    /* read registers */
    fread (buffer, 40, 1, fd);
    
    /* Load data on global array */
    for (i = 0; i < 20; i++) {
      truehull[j][i] = getWord (buffer + (i*2));
    }
  }
}

GSList * load_beamspec (void)
{
  FILE *beamspec;
  GSList *beamspec_list = NULL;
  GString *beamspec_file;
  GwpBeamSpec *bs;
  gint16 i, idx, beamspec_nr;
  gchar buffer[BEAMSPEC_SIZE];
  gchar *name_tmp;
  
  /* Initialize file name */
  beamspec_file = g_string_new ("BEAMSPEC.DAT");
  
  if ((beamspec = fopen(gwp_game_state_get_full_path(game_state, beamspec_file->str), "r")) == NULL) {
    beamspec_file = g_string_down (beamspec_file);
    if ((beamspec =
	 fopen (gwp_game_state_get_full_path(game_state, beamspec_file->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 gwp_game_state_get_full_path(game_state, beamspec_file->str));
      exit (-1);
    }
  }
  
  rewind (beamspec);

  beamspec_nr = 10;

  /* read registers */
  for (i = 1; i <= beamspec_nr; i++) {
    fread (buffer, BEAMSPEC_SIZE, 1, beamspec);
    
    /* Instantiate new object */
    bs = gwp_beamspec_new ();

    /* Load data */
    gwp_beamspec_set_id (bs, i);

    name_tmp = g_malloc (sizeof(gchar)*21);
    for (idx = 0; idx < 20; idx++) {
      name_tmp[idx] = getWord(buffer + idx);
    }
    name_tmp[20] = '\0';
    gwp_beamspec_set_name (bs, g_string_new(g_strchomp(name_tmp))->str);
    g_free(name_tmp);

    gwp_beamspec_set_cost (bs, getWord(buffer + 20));
    gwp_beamspec_set_tritanium (bs, getWord(buffer + 22));
    gwp_beamspec_set_duranium (bs, getWord(buffer + 24));
    gwp_beamspec_set_molybdenum (bs, getWord(buffer + 26));
    
    gwp_beamspec_set_mass (bs, getWord(buffer + 28));
    gwp_beamspec_set_tech_level (bs, getWord(buffer + 30));
    gwp_beamspec_set_kill_value (bs, getWord(buffer + 32));
    gwp_beamspec_set_damage_value (bs, getWord(buffer + 34));

    /* Add new beam weapon */
    beamspec_list = g_slist_append (beamspec_list, bs);
  }
  fclose (beamspec);

  return beamspec_list;
}

/**
 * Generates .DAT files from live objects.
 *
 * In order to generate the TRN file, modifications to the objects should
 * be dumped back to the data files.
 */
void
dump_to_dat_files (void)
{
  g_message ("Writing data files...");
  dump_to_ship_dat_file ();
  dump_to_pdata_dat_file ();
  dump_to_bdata_dat_file ();
  g_message ("...writing done!");
}

/**
 * Generate bdataX.dat file
 */
static void 
dump_to_bdata_dat_file (void)
{
  GSList *starbases_data = NULL;
  FILE *starbase_dat_file = NULL;
  FILE *gen_dat_file = NULL;
  gint i;
  gchar c;
  guchar *reg_nr = g_malloc0 (sizeof(guchar)*2);

  /* dummy value append */
  starbases_data =  g_slist_append (starbases_data, "delme!");

  g_hash_table_foreach (planet_list, (GHFunc) ghfunc_dump_starbase_data, 
			(gpointer)starbases_data);

  /* Skip first dummy value */  
  starbases_data = g_slist_next (starbases_data);

  if ((starbase_dat_file = fopen(gwp_game_state_get_dat_filename(game_state, "bdata", "dat"), "w+")) == NULL) {
    g_message ("ERROR: Could not open starbase data file for writing");
    exit(-1);
  }

  setWord(reg_nr, g_slist_length(starbases_data));

  fwrite (reg_nr, 2, 1, starbase_dat_file);

  for (i = 0; i < g_slist_length(starbases_data); i++) {
    fwrite ((guchar *)g_slist_nth_data(starbases_data, i), 156, 1, starbase_dat_file);
  }

  if ((gen_dat_file = fopen(gwp_game_state_get_dat_filename(game_state, "gen", "dat"), "r")) == NULL) {
    g_message ("ERROR: Could not open GENx.DAT data file: %s",
	       gwp_game_state_get_dat_filename(game_state, "gen", "dat"));
    exit(-1);
  }

  /* Signature 1's offset */
  fseek (gen_dat_file, 118, SEEK_SET);

  /* Do some signature */
  for (i = 1; i < 11; i++) {
    c = fgetc (gen_dat_file);
    fputc (c+i, starbase_dat_file);
  }

  fclose (gen_dat_file);
  fclose (starbase_dat_file);
}

/**
 * Generate pdataX.dat file
 */
static void 
dump_to_pdata_dat_file (void)
{
  GSList *planets_data = NULL;
  FILE *planet_dat_file = NULL;
  FILE *gen_dat_file = NULL;
  gint i;
  gchar c;
  guchar *reg_nr = g_malloc0 (sizeof(guchar)*2);

  /* dummy value append */
  planets_data =  g_slist_append (planets_data, "delme!");

  g_hash_table_foreach (planet_list, (GHFunc) ghfunc_dump_planet_data, 
			(gpointer)planets_data);

  /* Skip first dummy value */  
  planets_data = g_slist_next (planets_data);

  if ((planet_dat_file = fopen(gwp_game_state_get_dat_filename(game_state, "pdata", "dat"), "w+")) == NULL) {
    g_message ("ERROR: Could not open planet data file for writing");
    exit(-1);
  }

  setWord(reg_nr, g_slist_length(planets_data));

  fwrite (reg_nr, 2, 1, planet_dat_file);

  for (i = 0; i < g_slist_length(planets_data); i++) {
    fwrite ((guchar *)g_slist_nth_data(planets_data, i), 85, 1, planet_dat_file);
  }

  if ((gen_dat_file = fopen(gwp_game_state_get_dat_filename(game_state, "gen", "dat"), "r")) == NULL) {
    g_message ("ERROR: Could not open GENx.DAT data file: %s",
	       gwp_game_state_get_dat_filename(game_state, "gen", "dat"));
    exit(-1);
  }

  /* Signature 1's offset */
  fseek (gen_dat_file, 118, SEEK_SET);

  /* Do some signature */
  for (i = 1; i < 11; i++) {
    c = fgetc (gen_dat_file);
    fputc (c+i, planet_dat_file);
  }

  fclose (gen_dat_file);
  fclose (planet_dat_file);
}

/**
 * Generate shipX.dat file
 */
static void 
dump_to_ship_dat_file (void)
{
  GSList *ships_data = NULL;
  FILE *ship_dat_file = NULL;
  FILE *gen_dat_file = NULL;
  gint i;
  gchar c;
  guchar *reg_nr = g_malloc0 (sizeof(guchar)*2);

  /* dummy value append */
  ships_data =  g_slist_append (ships_data, "delme!");

  g_hash_table_foreach (ship_list, (GHFunc) ghfunc_dump_ship_data, 
			(gpointer)ships_data);

  /* Skip first dummy value */  
  ships_data = g_slist_next (ships_data);

  if ((ship_dat_file = fopen(gwp_game_state_get_dat_filename(game_state, "ship", "dat"), "w+")) == NULL) {
    g_message ("ERROR: Could not open ships data file for writing");
    exit(-1);
  }

  setWord(reg_nr, g_slist_length(ships_data));

  fwrite (reg_nr, 2, 1, ship_dat_file);

  for (i = 0; i < g_slist_length(ships_data); i++) {
    fwrite ((guchar *)g_slist_nth_data(ships_data, i), 107, 1, ship_dat_file);
  }

  if ((gen_dat_file = fopen(gwp_game_state_get_dat_filename(game_state, "gen", "dat"), "r")) == NULL) {
    g_message ("ERROR: Could not open GENx.DAT data file: %s",
	       gwp_game_state_get_dat_filename(game_state, "gen", "dat"));
    exit(-1);
  }

  /* Signature 1's offset */
  fseek (gen_dat_file, 118, SEEK_SET);

  /* Do some signature */
  for (i = 1; i < 11; i++) {
    c = fgetc (gen_dat_file);
    fputc (c+i, ship_dat_file);
  }

  fclose (gen_dat_file);
  fclose (ship_dat_file);
}

static void
ghfunc_dump_starbase_data (gpointer key, gpointer value, gpointer user_data)
{
  GwpPlanet *planet = GWP_PLANET(value);
  GwpStarbase *starbase = gwp_planet_get_starbase (planet);
  GSList *starbases_data = (GSList *)user_data;
  gint i;
  guchar *starbase_reg = g_malloc0 (sizeof(guchar)*156);

  if (!starbase) return;

  /* Fill the 156 byte record */
  setWord (starbase_reg+0, gwp_starbase_get_id(starbase));
  setWord (starbase_reg+2, gwp_game_state_get_race_nr(game_state));
  setWord (starbase_reg+4, gwp_starbase_get_defense(starbase));
  setWord (starbase_reg+6, gwp_starbase_get_damage(starbase));
  setWord (starbase_reg+8, gwp_starbase_get_engines_tech(starbase));
  setWord (starbase_reg+10, gwp_starbase_get_hulls_tech(starbase));
  setWord (starbase_reg+12, gwp_starbase_get_beams_tech(starbase));
  setWord (starbase_reg+14, gwp_starbase_get_torps_tech(starbase));
  for (i = 0; i < 9; i++) {
    setWord (starbase_reg+i*2+16, 
	     gwp_starbase_get_storage_engines(starbase, i));
  }
  for (i = 0; i < 20; i++) {
    setWord (starbase_reg+i*2+34, 
	     gwp_starbase_get_storage_hulls(starbase, i));
  }
  for (i = 0; i < 10; i++) {
    setWord (starbase_reg+i*2+74, 
	     gwp_starbase_get_storage_beams(starbase, i));
  }
  for (i = 0; i < 10; i++) {
    setWord (starbase_reg+i*2+94, 
	     gwp_starbase_get_storage_torp_launchers(starbase, i));
  }
  for (i = 0; i < 10; i++) {
    setWord (starbase_reg+i*2+114, 
	     gwp_starbase_get_storage_torps(starbase, i));
  }
  setWord (starbase_reg+134, gwp_starbase_get_fighters(starbase));
  setWord (starbase_reg+136, gwp_starbase_get_id_ship(starbase));
  setWord (starbase_reg+138, gwp_starbase_get_ship_action(starbase));
  setWord (starbase_reg+140, gwp_starbase_get_mission(starbase));
  setWord (starbase_reg+142, gwp_starbase_get_build_ship_type(starbase));
  setWord (starbase_reg+144, gwp_starbase_get_build_engine_type(starbase));
  setWord (starbase_reg+146, gwp_starbase_get_build_beam_type(starbase));
  setWord (starbase_reg+148, gwp_starbase_get_build_beam_count(starbase));
  setWord (starbase_reg+150, gwp_starbase_get_build_torp_type(starbase));
  setWord (starbase_reg+152, gwp_starbase_get_build_torp_count(starbase));
  setWord (starbase_reg+154, 0); /* Loser... ;-) */

  starbases_data = g_slist_append (starbases_data, (gpointer)starbase_reg);
}

static void
ghfunc_dump_planet_data (gpointer key, gpointer value, gpointer user_data)
{
  GwpPlanet *planet = GWP_PLANET(value);
  GSList *planets_data = (GSList *)user_data;
  guchar *planet_reg = g_malloc0 (sizeof(guchar)*85);

  if (gwp_planet_is_mine(planet)) {
    /* Fill the 85 byte record */
    setWord (planet_reg+0, gwp_game_state_get_race_nr(game_state));
    setWord (planet_reg+2, gwp_object_get_id(GWP_OBJECT(planet)));
    memcpy (planet_reg+4, padstr(gwp_planet_get_fcode(planet), 3), 3);
    setWord (planet_reg+7, gwp_planet_get_mines(planet));
    setWord (planet_reg+9, gwp_planet_get_factories(planet));
    setWord (planet_reg+11, gwp_planet_get_defense_posts(planet));
    setDWord (planet_reg+13, gwp_planet_get_mined_neutronium(planet));
    setDWord (planet_reg+17, gwp_planet_get_mined_tritanium(planet));
    setDWord (planet_reg+21, gwp_planet_get_mined_duranium(planet));
    setDWord (planet_reg+25, gwp_planet_get_mined_molybdenum(planet));
    setDWord (planet_reg+29, gwp_planet_get_colonists(planet));
    setDWord (planet_reg+33, gwp_planet_get_supplies(planet));
    setDWord (planet_reg+37, gwp_planet_get_megacredits(planet));
    setDWord (planet_reg+41, gwp_planet_get_ground_neutronium(planet));
    setDWord (planet_reg+45, gwp_planet_get_ground_tritanium(planet));
    setDWord (planet_reg+49, gwp_planet_get_ground_duranium(planet));
    setDWord (planet_reg+53, gwp_planet_get_ground_molybdenum(planet));
    setWord (planet_reg+57, gwp_planet_get_dens_neutronium(planet));
    setWord (planet_reg+59, gwp_planet_get_dens_tritanium(planet));
    setWord (planet_reg+61, gwp_planet_get_dens_duranium(planet));
    setWord (planet_reg+63, gwp_planet_get_dens_molybdenum(planet));
    setWord (planet_reg+65, gwp_planet_get_tax_colonists(planet));
    setWord (planet_reg+67, gwp_planet_get_tax_natives(planet));
    setWord (planet_reg+69, gwp_planet_get_happiness_colonists(planet));
    setWord (planet_reg+71, gwp_planet_get_happiness_natives(planet));
    setWord (planet_reg+73, gwp_planet_get_natives_spi(planet));
    setDWord (planet_reg+75, gwp_planet_get_natives(planet));
    setWord (planet_reg+79, gwp_planet_get_natives_race(planet));
    setWord (planet_reg+81, gwp_planet_get_temperature(planet));
    setWord (planet_reg+83, gwp_planet_get_build_base(planet));

    planets_data = g_slist_append (planets_data, (gpointer)planet_reg);
  }
}

static void
ghfunc_dump_ship_data (gpointer key, gpointer value, gpointer user_data)
{
  GwpShip *ship = GWP_SHIP(value);
  GSList *ships_data = (GSList *)user_data;
  guchar *ship_reg = g_malloc0 (sizeof(guchar)*107);

  if (gwp_ship_is_mine(ship)) {
    /* Fill the 107 byte record */
    setWord (ship_reg+0, gwp_object_get_id(GWP_OBJECT(ship)));
    setWord (ship_reg+2, gwp_game_state_get_race_nr(game_state));
    memcpy (ship_reg+4, padstr(gwp_ship_get_fcode(ship), 3), 3);
    setWord (ship_reg+7, gwp_flying_object_get_speed(GWP_FLYING_OBJECT(ship)));
    setWord (ship_reg+9, gwp_ship_get_x_to_waypoint(ship));
    setWord (ship_reg+11, gwp_ship_get_y_to_waypoint(ship));
    setWord (ship_reg+13, gwp_object_get_x_coord(GWP_OBJECT(ship)));
    setWord (ship_reg+15, gwp_object_get_y_coord(GWP_OBJECT(ship)));
    setWord (ship_reg+17, gwp_ship_get_engines_type(ship));
    setWord (ship_reg+19, gwp_ship_get_hull_type(ship));
    setWord (ship_reg+21, gwp_ship_get_beams_type(ship));
    setWord (ship_reg+23, gwp_ship_get_beams(ship));
    setWord (ship_reg+25, gwp_ship_get_fighter_bays(ship));
    setWord (ship_reg+27, gwp_ship_get_torps_type(ship));
    
    if (gwp_ship_get_torps_type(ship)>0 && 
	gwp_ship_get_torps_launchers(ship)>0) {
      setWord (ship_reg+29, gwp_ship_get_torps(ship));
    } else if (gwp_ship_get_fighter_bays(ship)>0 &&
	       gwp_ship_get_fighters(ship)>0) {
      setWord (ship_reg+29, gwp_ship_get_fighters(ship));
    } else {
      setWord (ship_reg+29, 0);
    }
    
    setWord (ship_reg+31, gwp_ship_get_torps_launchers(ship));
    setWord (ship_reg+33, gwp_ship_get_mission(ship));
    setWord (ship_reg+35, gwp_ship_get_primary_enemy(ship));
    setWord (ship_reg+37, gwp_ship_get_tow_ship_id(ship));
    setWord (ship_reg+39, gwp_ship_get_damage(ship));
    setWord (ship_reg+41, gwp_ship_get_crew(ship));
    setWord (ship_reg+43, gwp_ship_get_colonists(ship));
    memcpy (ship_reg+45, padstr(gwp_object_get_name(GWP_OBJECT(ship)),20), 20);
    setWord (ship_reg+65, gwp_ship_get_neutronium(ship));
    setWord (ship_reg+67, gwp_ship_get_tritanium(ship));
    setWord (ship_reg+69, gwp_ship_get_duranium(ship));
    setWord (ship_reg+71, gwp_ship_get_molybdenum(ship));
    setWord (ship_reg+73, gwp_ship_get_supplies(ship));
    setWord (ship_reg+75, gwp_ship_get_unload_neutronium(ship));
    setWord (ship_reg+77, gwp_ship_get_unload_tritanium(ship));
    setWord (ship_reg+79, gwp_ship_get_unload_duranium(ship));
    setWord (ship_reg+81, gwp_ship_get_unload_molybdenum(ship));
    setWord (ship_reg+83, gwp_ship_get_unload_colonists(ship));
    setWord (ship_reg+85, gwp_ship_get_unload_supplies(ship));
    setWord (ship_reg+87, gwp_ship_get_unload_planet_id(ship));
    setWord (ship_reg+89, gwp_ship_get_transfer_neutronium(ship));
    setWord (ship_reg+91, gwp_ship_get_transfer_tritanium(ship));
    setWord (ship_reg+93, gwp_ship_get_transfer_duranium(ship));
    setWord (ship_reg+95, gwp_ship_get_transfer_molybdenum(ship));
    setWord (ship_reg+97, gwp_ship_get_transfer_colonists(ship));
    setWord (ship_reg+99, gwp_ship_get_transfer_supplies(ship));
    setWord (ship_reg+101, gwp_ship_get_transfer_ship_id(ship));
    setWord (ship_reg+103, gwp_ship_get_intercept_ship_id(ship));
    setWord (ship_reg+105, gwp_ship_get_megacredits(ship));

    ships_data = g_slist_append (ships_data, (gpointer)ship_reg);
  }
}

/**
 * Scan messages for interesting data.
 *
 * Tim is so great, that many important game data only comes from the
 * game's message system, so I have to scan them to show all the good stuff, 
 * cool isn't it?
 */

void 
scan_messages (void)
{
     GwpMessages *msg_store = (GwpMessages *)gwp_messages_new ();
     gint qty = gwp_messages_getMessagesNumber (msg_store);
     gint i;

     for (i = 0; i < qty; i++) {
	  gchar *msg_hdr = g_strdup(gwp_messages_getMessageHeader (msg_store, i));

	  /* Scanner report on planets */
	  if (gwp_messages_grepMessage (msg_hdr, "-z0")) {

	       gchar *msg_body = g_strdup(gwp_messages_getMessageRaw (msg_store, i));
	       /* Search for enemy clans on planets below our ships */
	       if (gwp_messages_grepMessage (msg_body, "There are enemy colonists")) {
		    scan_messages_planet_orbit (msg_body);
	       } 
	       /* Search for enemy planets based on our sensor sweeps */
	       else if (gwp_messages_grepMessage (msg_body, "Sensors show there")) {
		    scan_messages_planet_scanned (msg_body);
	       }
	       g_free (msg_body);
	  }
/* 	  Message from your Host */
	  else if(gwp_messages_grepMessage (msg_hdr, "-g0") ||
		  gwp_messages_grepMessage (msg_hdr, "og0"))
	  {
	       gchar *msg_body = g_strdup(gwp_messages_getMessageRaw (msg_store, i));

	       if (gwp_messages_grepMessage (msg_body, "Colonize recycle rate"))
		    scan_messages_recycle_rate(msg_body);
	       else if (gwp_messages_grepMessage (msg_body, "Ground Attack Kill Ratio"))
		    scan_messages_att_rat(msg_body);
	       else if(gwp_messages_grepMessage (msg_body, "Ground Defense Kill Ratio"))
		    scan_messages_def_rat(msg_body);
	       else if(gwp_messages_grepMessage (msg_body, "Free fighters at starbases"))
		    scan_messages_fig_starb(msg_body);
	       else if(gwp_messages_grepMessage (msg_body, "Mining rates"))
		    scan_messages_min_rat(msg_body);
	       else if(gwp_messages_grepMessage (msg_body, "Tax rates"))
		    scan_messages_tax_rat(msg_body);
	       else if(gwp_messages_grepMessage (msg_body, "Col Fgtr Mine sweep"))
		    scan_messages_min_sweep(msg_body);
	       else if(gwp_messages_grepMessage (msg_body, "One engine ships tow"))
		    scan_messages_shipt_tow(msg_body);
	       else if(gwp_messages_grepMessage (msg_body, "Max income per planet"))
		    scan_messages_in_pla(msg_body);
	       else if(gwp_messages_grepMessage (msg_body, "Cobol fuel per LY"))
		    scan_messages_fuel_ly(msg_body);
	       else if(gwp_messages_grepMessage (msg_body, "FF / ff Allies"))
		    scan_messages_allies(msg_body);
	       else
		    g_message("Host's config message unknown !");

	       g_free (msg_body);
	  }
	  g_free (msg_hdr);
     }
}

void scan_messages_recycle_rate(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *r_rate, *meteor, *space_mines, *chemy_ships;
     const gchar *del_old_mess, *dis_pass, *re_b_f_spa, *co_b_f_spa;
     const gchar *ro_b_f_spa, *clo_fail, *pri_rob_clo, *emp_sen_range;

     substring = g_list_append(substring, &r_rate);
     substring = g_list_append(substring, &meteor);
     substring = g_list_append(substring, &space_mines);
     substring = g_list_append(substring, &chemy_ships);
     substring = g_list_append(substring, &del_old_mess);
     substring = g_list_append(substring, &dis_pass);
     substring = g_list_append(substring, &re_b_f_spa);
     substring = g_list_append(substring, &co_b_f_spa);
     substring = g_list_append(substring, &ro_b_f_spa);
     substring = g_list_append(substring, &clo_fail);
     substring = g_list_append(substring, &pri_rob_clo);
     substring = g_list_append(substring, &emp_sen_range);

     const gchar *regexp = ".*rate.*(\\b[0-9]+\\b).*meteor.*(\\b[0-9]+\\b).*mines.*(\\bYES|NO\\b).*ships.*(\\bYES|NO\\b).*Messages.*(\\bYES|NO\\b).*Passwords.*(\\bYES|NO\\b).*space.*(\\bYES|NO\\b).*space.*(\\bYES|NO\\b).*space.*(\\bYES|NO\\b).*failure.*(\\b[0-9]+\\b).*ships.*(\\bYES|NO\\b).*range.*(\\b\\d+\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0)
     {
/* 	  g_message(r_rate); */
/* 	  g_message(meteor); */
/* 	  g_message(space_mines); */
/* 	  g_message(chemy_ships); */
/* 	  g_message(del_old_mess); */
/* 	  g_message(dis_pass); */
/* 	  g_message(re_b_f_spa); */
/* 	  g_message(co_b_f_spa); */
/* 	  g_message(ro_b_f_spa); */
/* 	  g_message(clo_fail); */
/* 	  g_message(pri_rob_clo); */
/* 	  g_message(emp_sen_range); */

	  g_assert(GWP_IS_GAME_STATE(game_state));

	  gwp_game_state_set_host_recycle_col_ship (game_state, atoi(r_rate));
	  gwp_game_state_set_host_large_meteor_impact (game_state, atoi(meteor));
	  gwp_game_state_set_host_space_mines (game_state, YES_OR_NO(space_mines));
	  gwp_game_state_set_host_alchemy_ships (game_state, YES_OR_NO(chemy_ships));
	  gwp_game_state_set_host_delete_old_msgs (game_state, YES_OR_NO(del_old_mess));
	  gwp_game_state_set_host_disable_pwd (game_state, YES_OR_NO(dis_pass));
	  gwp_game_state_set_host_rebel_build_fighters (game_state, YES_OR_NO(re_b_f_spa));
	  gwp_game_state_set_host_colonial_build_fighters (game_state, YES_OR_NO(co_b_f_spa));
	  gwp_game_state_set_host_robots_build_fighters (game_state, YES_OR_NO(ro_b_f_spa));
	  gwp_game_state_set_host_cloak_failure (game_state, atoi(clo_fail));
	  gwp_game_state_set_host_priv_rob_cloak (game_state, YES_OR_NO(pri_rob_clo));
	  gwp_game_state_set_host_dark_sense_range (game_state, atoi(emp_sen_range));

	  g_message("Host's config loaded 1");
     }

     free_substring(substring);
}

/* 
 * FIXME: Please check this kind of regexp's, because when a game is not being
 * played by all 11 races, they don't match at all!
 * !!Warning!!: there are 4 or 5  scan_messages_*() functions with this regexp.
 */
void scan_messages_att_rat(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *ratio1, *ratio2, *ratio3, *ratio4, *ratio5;
     const gchar *ratio6, *ratio7, *ratio8, *ratio9, *ratio10, *ratio11;
     const gchar *visible, *hiss, *re_g_att, *fed_s_refit, *web_mines;

     substring = g_list_append(substring, &ratio1);
     substring = g_list_append(substring, &ratio2);
     substring = g_list_append(substring, &ratio3);
     substring = g_list_append(substring, &ratio4);
     substring = g_list_append(substring, &ratio5);
     substring = g_list_append(substring, &ratio6);
     substring = g_list_append(substring, &ratio7);
     substring = g_list_append(substring, &ratio8);
     substring = g_list_append(substring, &ratio9);
     substring = g_list_append(substring, &ratio10);
     substring = g_list_append(substring, &ratio11);
     substring = g_list_append(substring, &visible);
     substring = g_list_append(substring, &hiss);
     substring = g_list_append(substring, &re_g_att);
     substring = g_list_append(substring, &fed_s_refit);
     substring = g_list_append(substring, &web_mines);

     const gchar *regexp = ".*Fed.*(\\b\\d+\\b).*:.*Lizard.*(\\b\\d+\\b).*:.*Bird Man.*(\\b\\d+\\b).*:.*Fascist.*(\\b\\d+\\b).*:.*Privateer.*(\\b\\d+\\b).*:.*Cyborg.*(\\b\\d+\\b).*:.*Crystalline.*(\\b\\d+\\b).*:.*Empire.*(\\b\\d+\\b).*:.*Robotic.*(\\b\\d+\\b).*:.*Rebel.*(\\b\\d+\\b).*:.*Colonial.*(\\b\\d+\\b).*:.*visible at.*(\\b\\d+\\b).*mission.*(\\bYES|NO\\b).*attack.*(\\bYES|NO\\b).*refit.*(\\bYES|NO\\b).*mines.*(\\bYES|NO\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
     if (rc > 0)
     {
/* 	  g_message(ratio1); */
/* 	  g_message(ratio2); */
/* 	  g_message(ratio3); */
/* 	  g_message(ratio4); */
/* 	  g_message(ratio5); */
/* 	  g_message(ratio6); */
/* 	  g_message(ratio7); */
/* 	  g_message(ratio8); */
/* 	  g_message(ratio9); */
/* 	  g_message(ratio10); */
/* 	  g_message(ratio11); */
/* 	  g_message(visible); */
/* 	  g_message(hiss); */
/* 	  g_message(re_g_att); */
/* 	  g_message(fed_s_refit); */
/* 	  g_message(web_mines); */

	  g_assert(GWP_IS_GAME_STATE(game_state));
	  gchar **tmp;
	  gint i;
	  for(i = 0; i < 11; i++) {
	       tmp = g_list_nth_data(substring, i);
	       gwp_game_state_set_host_ground_attack_ratio (game_state, i+1, atoi(*tmp));
	  }

	  gwp_game_state_set_host_ships_visible_range(game_state, atoi(visible));
	  gwp_game_state_set_host_lizard_hiss_mission(game_state, YES_OR_NO(hiss));
	  gwp_game_state_set_host_rebel_ground_attack(game_state, YES_OR_NO(re_g_att));
	  gwp_game_state_set_host_fed_super_refit(game_state, YES_OR_NO(fed_s_refit));
	  gwp_game_state_set_host_crystal_web_mines(game_state, YES_OR_NO(web_mines));

	  g_message("Host's config loaded 2");
	  free_substring(substring);
     }
}

void scan_messages_def_rat(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *ratio1, *ratio2, *ratio3, *ratio4, *ratio5;
     const gchar *ratio6, *ratio7, *ratio8, *ratio9, *ratio10, *ratio11;
     const gchar *burn, *range, *natives, *pa_att_sh, *assimil;


     substring = g_list_append(substring, &ratio1);
     substring = g_list_append(substring, &ratio2);
     substring = g_list_append(substring, &ratio3);
     substring = g_list_append(substring, &ratio4);
     substring = g_list_append(substring, &ratio5);
     substring = g_list_append(substring, &ratio6);
     substring = g_list_append(substring, &ratio7);
     substring = g_list_append(substring, &ratio8);
     substring = g_list_append(substring, &ratio9);
     substring = g_list_append(substring, &ratio10);
     substring = g_list_append(substring, &ratio11);
     substring = g_list_append(substring, &burn);
     substring = g_list_append(substring, &range);
     substring = g_list_append(substring, &natives);
     substring = g_list_append(substring, &pa_att_sh);
     substring = g_list_append(substring, &assimil);

     const gchar *regexp = ".*Fed.*(\\b\\d+\\b).*:.*Lizard.*(\\b\\d+\\b).*:.*Bird Man.*(\\b\\d+\\b).*:.*Fascist.*(\\b\\d+\\b).*:.*Privateer.*(\\b\\d+\\b).*:.*Cyborg.*(\\b\\d+\\b).*:.*Crystalline.*(\\b\\d+\\b).*:.*Empire.*(\\b\\d+\\b).*:.*Robotic.*(\\b\\d+\\b).*:.*Rebel.*(\\b\\d+\\b).*:.*Colonial.*(\\b\\d+\\b).*:.*100kt.*(\\b\\d+\\b).*sensors.*(\\b\\d+\\b).*Natives.*(\\bYES|NO\\b).*ships.*(\\bYES|NO\\b).*rate.*(\\b\\d+\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0)
     {
/* 	  g_message(ratio1); */
/* 	  g_message(ratio2); */
/* 	  g_message(ratio3); */
/* 	  g_message(ratio4); */
/* 	  g_message(ratio5); */
/* 	  g_message(ratio6); */
/* 	  g_message(ratio7); */
/* 	  g_message(ratio8); */
/* 	  g_message(ratio9); */
/* 	  g_message(ratio10); */
/* 	  g_message(ratio11); */
/* 	  g_message(burn); */
/* 	  g_message(range); */
/* 	  g_message(natives); */
/* 	  g_message(pa_att_sh); */
/* 	  g_message(assimil); */

	  g_assert(GWP_IS_GAME_STATE(game_state));
	  gchar **tmp;
	  gint i;

	  for(i = 0; i < 11; i++) {
	       tmp = g_list_nth_data(substring, i);
	       gwp_game_state_set_host_ground_defense_ratio(game_state, i+1, atoi(*tmp));
	  }

	  gwp_game_state_set_host_cloak_fuel_use(game_state, atoi(burn));
	  gwp_game_state_set_host_sensors_range(game_state, atoi(range));
	  gwp_game_state_set_host_new_natives(game_state, YES_OR_NO(natives));
	  gwp_game_state_set_host_planets_attack_ships(game_state, YES_OR_NO(pa_att_sh));
	  gwp_game_state_set_host_borg_assimilation_rate(game_state, YES_OR_NO(assimil));

	  g_message("Host's config loaded 3");
	  free_substring(substring);
     }
}

void scan_messages_fig_starb(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *free1, *free2, *free3, *free4, *free5;
     const gchar *free6, *free7, *free8, *free9, *free10, *free11;
     const gchar *wm_decay, *m_decay, *mine_rad, *isotop, *struc_decay;

     substring = g_list_append(substring, &free1);
     substring = g_list_append(substring, &free2);
     substring = g_list_append(substring, &free3);
     substring = g_list_append(substring, &free4);
     substring = g_list_append(substring, &free5);
     substring = g_list_append(substring, &free6);
     substring = g_list_append(substring, &free7);
     substring = g_list_append(substring, &free8);
     substring = g_list_append(substring, &free9);
     substring = g_list_append(substring, &free10);
     substring = g_list_append(substring, &free11);
     substring = g_list_append(substring, &wm_decay);
     substring = g_list_append(substring, &m_decay);
     substring = g_list_append(substring, &mine_rad);
     substring = g_list_append(substring, &isotop);
     substring = g_list_append(substring, &struc_decay);

     const gchar *regexp = ".*Fed.*(\\b\\d+\\b).*Lizard.*(\\b\\d+\\b).*Bird Man.*(\\b\\d+\\b).*Fascist.*(\\b\\d+\\b).*Privateer.*(\\b\\d+\\b).*Cyborg.*(\\b\\d+\\b).*Crystalline.*(\\b\\d+\\b).*Empire.*(\\b\\d+\\b).*Robotic.*(\\b\\d+\\b).*Rebel.*(\\b\\d+\\b).*Colonial.*(\\b\\d+\\b).*web mine decay.*(\\b\\d+\\b).*mine decay.*(\\b\\d+\\b).*radius.*(\\b\\d+\\b).*TUDR.*(\\b\\d+\\b).*decay.*(\\b\\d+\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0)
     {
/* 	  g_message(free1); */
/* 	  g_message(free2); */
/* 	  g_message(free3); */
/* 	  g_message(free4); */
/* 	  g_message(free5); */
/* 	  g_message(free6); */
/* 	  g_message(free7); */
/* 	  g_message(free8); */
/* 	  g_message(free9); */
/* 	  g_message(free10); */
/* 	  g_message(free11); */
/* 	  g_message(wm_decay); */
/* 	  g_message(m_decay); */
/* 	  g_message(mine_rad); */
/* 	  g_message(isotop); */
/* 	  g_message(struc_decay); */

	  g_assert(GWP_IS_GAME_STATE(game_state));

	  gchar **tmp;
	  gint i;
	  for(i = 0; i < 11; i++) {
	       tmp = g_list_nth_data(substring, i);
	       gwp_game_state_set_host_starbase_free_fighters(game_state, i+1, atoi(*tmp));
	  }

	  gwp_game_state_set_host_webmine_decay(game_state, atoi(wm_decay));
	  gwp_game_state_set_host_mine_decay(game_state, atoi(m_decay));
	  gwp_game_state_set_host_max_mine_radius(game_state, atoi(mine_rad));
	  gwp_game_state_set_host_isotope_tudr(game_state, atoi(isotop));
	  gwp_game_state_set_host_structure_decay(game_state, atoi(struc_decay));

	  g_message("Host's config loaded 4");
	  free_substring(substring);
     }
}

void scan_messages_min_rat(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *rate1, *rate2, *rate3, *rate4, *rate5;
     const gchar *rate6, *rate7, *rate8, *rate9, *rate10, *rate11;
     const gchar *eat, *move, *mine_ly, *wmine_ly, *range;

     substring = g_list_append(substring, &rate1);
     substring = g_list_append(substring, &rate2);
     substring = g_list_append(substring, &rate3);
     substring = g_list_append(substring, &rate4);
     substring = g_list_append(substring, &rate5);
     substring = g_list_append(substring, &rate6);
     substring = g_list_append(substring, &rate7);
     substring = g_list_append(substring, &rate8);
     substring = g_list_append(substring, &rate9);
     substring = g_list_append(substring, &rate10);
     substring = g_list_append(substring, &rate11);
     substring = g_list_append(substring, &eat);
     substring = g_list_append(substring, &move);
     substring = g_list_append(substring, &mine_ly);
     substring = g_list_append(substring, &wmine_ly);
     substring = g_list_append(substring, &range);

     const gchar *regexp = ".*Fed.*(\\b\\d+\\b).*Lizard.*(\\b\\d+\\b).*Bird Man.*(\\b\\d+\\b).*Fascist.*(\\b\\d+\\b).*Privateer.*(\\b\\d+\\b).*Cyborg.*(\\b\\d+\\b).*Crystalline.*(\\b\\d+\\b).*Empire.*(\\b\\d+\\b).*Robotic.*(\\b\\d+\\b).*Rebel.*(\\b\\d+\\b).*Colonial.*(\\b\\d+\\b).*supplies?.*(\\bYES|NO\\b).*move?.*(\\bYES|NO\\b).*LY.*(\\b\\d+\\b).*LY.*(\\b\\d+\\b).*range.*(\\b\\d+\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0)
     {
/* 	  g_message(rate1); */
/* 	  g_message(rate2); */
/* 	  g_message(rate3); */
/* 	  g_message(rate4); */
/* 	  g_message(rate5); */
/* 	  g_message(rate6); */
/* 	  g_message(rate7); */
/* 	  g_message(rate8); */
/* 	  g_message(rate9); */
/* 	  g_message(rate10); */
/* 	  g_message(rate11); */
/* 	  g_message(eat); */
/* 	  g_message(move); */
/* 	  g_message(mine_ly); */
/* 	  g_message(wmine_ly); */
/* 	  g_message(range); */

	  g_assert(GWP_IS_GAME_STATE(game_state));

	  gchar **tmp;
	  gint i;
	  for(i = 0; i < 11; i++) {
	       tmp = g_list_nth_data(substring, i);
	       gwp_game_state_set_host_mining_rate(game_state, i+1, atoi(*tmp));
	  }

	  gwp_game_state_set_host_colonists_eat_supplies (game_state, YES_OR_NO(eat));
	  gwp_game_state_set_host_zero_fuel_ships_move (game_state, YES_OR_NO(move));
	  gwp_game_state_set_host_mine_hit_odds (game_state, atoi(mine_ly));
	  gwp_game_state_set_host_webmine_hit_odds(game_state, atoi(wmine_ly));
	  gwp_game_state_set_host_mine_detect_range (game_state, atoi(range));

	  g_message("Host's config loaded 5");
	  free_substring(substring);
     }
}

void scan_messages_tax_rat(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *rate1, *rate2, *rate3, *rate4, *rate5;
     const gchar *rate6, *rate7, *rate8, *rate9, *rate10, *rate11;
     const gchar *m_des_mi, *es, *es_rate;

     substring = g_list_append(substring, &rate1);
     substring = g_list_append(substring, &rate2);
     substring = g_list_append(substring, &rate3);
     substring = g_list_append(substring, &rate4);
     substring = g_list_append(substring, &rate5);
     substring = g_list_append(substring, &rate6);
     substring = g_list_append(substring, &rate7);
     substring = g_list_append(substring, &rate8);
     substring = g_list_append(substring, &rate9);
     substring = g_list_append(substring, &rate10);
     substring = g_list_append(substring, &rate11);
     substring = g_list_append(substring, &m_des_mi);
     substring = g_list_append(substring, &es);
     substring = g_list_append(substring, &es_rate);

     const gchar *regexp = ".*Fed.*(\\b\\d+\\b).*Lizard.*(\\b\\d+\\b).*Bird Man.*(\\b\\d+\\b).*Fascist.*(\\b\\d+\\b).*Privateer.*(\\b\\d+\\b).*Cyborg.*(\\b\\d+\\b).*Crystalline.*(\\b\\d+\\b).*Empire.*(\\b\\d+\\b).*Robotic.*(\\b\\d+\\b).*Rebel.*(\\b\\d+\\b).*Colonial.*(\\b\\d+\\b).*mines.*(\\bYES|NO\\b).*bonus.*(\\bYES|NO\\b).*rate.*(\\b\\d+\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0)
     {
/* 	  g_message(rate1); */
/* 	  g_message(rate2); */
/* 	  g_message(rate3); */
/* 	  g_message(rate4); */
/* 	  g_message(rate5); */
/* 	  g_message(rate6); */
/* 	  g_message(rate7); */
/* 	  g_message(rate8); */
/* 	  g_message(rate9); */
/* 	  g_message(rate10); */
/* 	  g_message(rate11); */
/* 	  g_message(m_des_mi); */
/* 	  g_message(es); */
/* 	  g_message(es_rate); */

	  g_assert(GWP_IS_GAME_STATE(game_state));

	  gchar **tmp;
	  gint i;
	  for(i = 0; i < 11; i++) {
	       tmp = g_list_nth_data(substring, i);
	       gwp_game_state_set_host_tax_rate(game_state, i+1, atoi(*tmp));
	  }

	  gwp_game_state_set_host_mines_destroy_mines(game_state, YES_OR_NO(m_des_mi));
	  gwp_game_state_set_host_es_bonus(game_state, YES_OR_NO(es));
	  gwp_game_state_set_host_es_bonus_rate(game_state, atoi(es_rate));

	  g_message("Host's config loaded 6");
	  free_substring(substring);
     }
}

void scan_messages_min_sweep(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *m_sweep, *wm_sweep, *m_rate, *wm_rate, *hiss;
     const gchar *rob_fail, *at_reb, *att_fas, *m_range, *wm_range;
     const gchar *science, *cloak_m, *cloak_prevent, *crew_bonus;

     substring = g_list_append(substring, &m_sweep);
     substring = g_list_append(substring, &wm_sweep);
     substring = g_list_append(substring, &m_rate);
     substring = g_list_append(substring, &wm_rate);
     substring = g_list_append(substring, &hiss);
     substring = g_list_append(substring, &rob_fail);
     substring = g_list_append(substring, &at_reb);
     substring = g_list_append(substring, &att_fas);
     substring = g_list_append(substring, &m_range);
     substring = g_list_append(substring, &wm_range);
     substring = g_list_append(substring, &science);
     substring = g_list_append(substring, &cloak_m);
     substring = g_list_append(substring, &cloak_prevent);
     substring = g_list_append(substring, &crew_bonus);

     const gchar *regexp = ".*sweep.*(\\b\\d+\\b).*sweep.*(\\bYES|NO\\b).*Rate.*(\\b\\d+\\b).*Rate.*(\\b\\d+\\b).*ship.*(\\b\\d+\\b).*rate.*(\\b\\d+\\b).*Reb.*(\\bYES|NO\\b).*Fas.*(\\bYES|NO\\b).*Mine Sweep Range.*(\\b\\d+\\b).*Web Sweep Range.*(\\b\\d+\\b).*Missions.*(\\bYES|NO\\b).*Odds.*(\\d{0,2}\\.\\d+).*Damage.*(\\b\\d+\\b).*Bonus.*(\\bYES|NO\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0)
     {
/* 	  g_message(m_sweep); */
/* 	  g_message(wm_sweep); */
/* 	  g_message(m_rate); */
/* 	  g_message(wm_rate); */
/* 	  g_message(hiss); */
/* 	  g_message(rob_fail); */
/* 	  g_message(at_reb); */
/* 	  g_message(att_fas); */
/* 	  g_message(m_range); */
/* 	  g_message(wm_range); */
/* 	  g_message(science); */
/* 	  g_message(cloak_m); */
/* 	  g_message(cloak_prevent); */
/* 	  g_message(crew_bonus); */

	  g_assert(GWP_IS_GAME_STATE(game_state));

	  gwp_game_state_set_host_colonial_sweep_rate(game_state, atoi(m_sweep));
	  gwp_game_state_set_host_colonial_sweep_webs(game_state, YES_OR_NO(wm_sweep));
	  gwp_game_state_set_host_mine_sweep_rate(game_state, atoi(m_range));
	  gwp_game_state_set_host_webmine_sweep_rate(game_state, atoi(wm_rate));
	  gwp_game_state_set_host_hiss_mission_effect(game_state, atoi(hiss));
	  gwp_game_state_set_host_rob_mission_failure(game_state, atoi(rob_fail));
	  gwp_game_state_set_host_planet_attack_rebel(game_state, YES_OR_NO(at_reb));
	  gwp_game_state_set_host_planet_attack_fascist(game_state, YES_OR_NO(att_fas));
	  gwp_game_state_set_host_mine_sweep_range(game_state, atoi(m_range));
	  gwp_game_state_set_host_webmine_sweep_range(game_state, atoi(wm_range));
	  gwp_game_state_set_host_science_missions(game_state, YES_OR_NO(science));
	  gwp_game_state_set_host_cloaked_mine_hit(game_state, atof(cloak_m));
	  gwp_game_state_set_host_cloak_prevent_damage(game_state, atoi(cloak_prevent));
	  gwp_game_state_set_host_fed_crew_bonus(game_state, YES_OR_NO(crew_bonus));

	  g_message("Host's config loaded 7");
     }

     free_substring(substring);
}

void scan_messages_shipt_tow(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *s_tow, *h_drive, *death_rate, *grav_wells;
     const gchar *crys_desert, *m_des_w, *clim_lim;

     substring = g_list_append(substring, &s_tow);
     substring = g_list_append(substring, &h_drive);
     substring = g_list_append(substring, &death_rate);
     substring = g_list_append(substring, &grav_wells);
     substring = g_list_append(substring, &crys_desert);
     substring = g_list_append(substring, &m_des_w);
     substring = g_list_append(substring, &clim_lim);
 
     const gchar *regexp = ".*tow.*(\\bYES|NO\\b).*ships.*(\\bYES|NO\\b).*Rate.*(\\b\\d+\\b).*wells.*(\\bYES|NO\\b).*advant.*(\\bYES|NO\\b).*webs.*(\\bYES|NO\\b).*pop.*(\\bYES|NO\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0)
     {
/* 	  g_message(s_tow); */
/* 	  g_message(h_drive); */
/* 	  g_message(death_rate); */
/* 	  g_message(grav_wells); */
/* 	  g_message(crys_desert); */
/* 	  g_message(m_des_w); */
/* 	  g_message(clim_lim); */

	  g_assert(GWP_IS_GAME_STATE(game_state));

	  gwp_game_state_set_host_one_engine_tow(game_state, YES_OR_NO(s_tow));
	  gwp_game_state_set_host_hyperdrive_ships(game_state, YES_OR_NO(h_drive));
	  gwp_game_state_set_host_climate_death_rate (game_state, atoi(death_rate));
	  gwp_game_state_set_host_gravity_well(game_state, YES_OR_NO(grav_wells));
	  gwp_game_state_set_host_crystal_desert_adv (game_state, YES_OR_NO(crys_desert));
	  gwp_game_state_set_host_mines_destroy_webs(game_state, YES_OR_NO(m_des_w));
	  gwp_game_state_set_host_climate_limit_pop(game_state, YES_OR_NO(clim_lim));


	  g_message("Host's config loaded 8");
     }

     free_substring(substring);

}

void scan_messages_in_pla(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *max_in, *storms, *chunnel, *deluxe, *storms_hide;
     const gchar *glory_dev, *anti_cloak, *gambling;
     const gchar *cloak_att, *cloning, *boarding, *imp_ass;

     substring = g_list_append(substring, &max_in);
     substring = g_list_append(substring, &storms);
     substring = g_list_append(substring, &chunnel);
     substring = g_list_append(substring, &deluxe);
     substring = g_list_append(substring, &storms_hide);
     substring = g_list_append(substring, &glory_dev);
     substring = g_list_append(substring, &anti_cloak);
     substring = g_list_append(substring, &gambling);
     substring = g_list_append(substring, &cloak_att);
     substring = g_list_append(substring, &cloning);
     substring = g_list_append(substring, &boarding);
     substring = g_list_append(substring, &imp_ass);
 
     const gchar *regexp = ".*planet.*(\\b\\d+\\b).*mc.*Storms.*(\\b\\d+\\b).*Chunnel.*(\\bYES|NO\\b).*Deluxe.*(\\bYES|NO\\b).*mines.*(\\bYES|NO\\b).*Device.*(\\bYES|NO\\b).*anti-cloak.*(\\bYES|NO\\b).*Gambling.*(\\bYES|NO\\b).*attack.*(\\bYES|NO\\b).*cloning.*(\\bYES|NO\\b).*Boarding.*(\\bYES|NO\\b).*Assault.*(\\bYES|NO\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0)
     {
/* 	  g_message(max_in); */
/* 	  g_message(storms); */
/* 	  g_message(chunnel); */
/* 	  g_message(deluxe); */
/* 	  g_message(storms_hide); */
/* 	  g_message(glory_dev); */
/* 	  g_message(anti_cloak); */
/* 	  g_message(gambling); */
/* 	  g_message(cloak_att); */
/* 	  g_message(cloning); */
/* 	  g_message(boarding); */
/* 	  g_message(imp_ass); */

	  g_assert(GWP_IS_GAME_STATE(game_state));

	  gwp_game_state_set_host_max_planet_income(game_state, atoi(max_in));
	  gwp_game_state_set_host_ion_storms(game_state, atoi(storms));
	  gwp_game_state_set_host_firecloud_chunnel(game_state, YES_OR_NO(chunnel));
	  gwp_game_state_set_host_superspy_deluxe(game_state, YES_OR_NO(deluxe));
	  gwp_game_state_set_host_storms_hide_mines(game_state, YES_OR_NO(storms_hide));
	  gwp_game_state_set_host_fascist_glory_device(game_state, YES_OR_NO(glory_dev));
	  gwp_game_state_set_host_loki_anticloak(game_state, YES_OR_NO(anti_cloak));
	  gwp_game_state_set_host_ladyroyale_gambling(game_state, YES_OR_NO(gambling));
	  gwp_game_state_set_host_cloaked_ships_attack(game_state, YES_OR_NO(cloak_att));
	  gwp_game_state_set_host_ship_cloning(game_state, YES_OR_NO(cloning));
	  gwp_game_state_set_host_boarding_party(game_state, YES_OR_NO(boarding));
	  gwp_game_state_set_host_imperial_assault(game_state, YES_OR_NO(imp_ass));

	  g_message("Host's config loaded 9");
     }

     free_substring(substring);
}

void scan_messages_fuel_ly(const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *fuel_ly, *mine_slow, *aries_fuel, *bioscanners;
     const gchar *loki_decloak, *extra_features;

     substring = g_list_append(substring, &fuel_ly);
     substring = g_list_append(substring, &mine_slow);
     substring = g_list_append(substring, &aries_fuel);
     substring = g_list_append(substring, &bioscanners);
     substring = g_list_append(substring, &loki_decloak);
     substring = g_list_append(substring, &extra_features);
 
     const gchar *regexp = ".*LY.*(\\b\\d+\\b).*kt.*slow.*(\\b\\d+\\b).*fuel.*(\\bYES|NO\\b).*Bioscanners.*(\\bYES|NO\\b).*Birds.*(\\bYES|NO\\b).*Features.*(\\bYES|NO\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0)
     {
/* 	  g_message(fuel_ly); */
/* 	  g_message(mine_slow); */
/* 	  g_message(aries_fuel); */
/* 	  g_message(bioscanners); */
/* 	  g_message(loki_decloak); */
/* 	  g_message(extra_features); */

	  g_assert(GWP_IS_GAME_STATE(game_state));

	  gwp_game_state_set_host_cobol_fuel(game_state, atoi(fuel_ly));
	  gwp_game_state_set_host_hulltech_slowed_minehits(game_state, atoi(mine_slow));
	  gwp_game_state_set_host_aries_makes_fuel(game_state, YES_OR_NO(aries_fuel));
	  gwp_game_state_set_host_bioscanners(game_state, YES_OR_NO(bioscanners));
	  gwp_game_state_set_host_loki_decloak_birds(game_state, YES_OR_NO(loki_decloak));
	  gwp_game_state_set_host_vpa_extras(game_state, YES_OR_NO(extra_features));

	  g_message("Host's config loaded 10");
     }

     free_substring(substring);
}

void scan_messages_allies(const gchar *msg_body)
{

}

/**
 * Enemy planet detected when a ship is in orbit.
 */
void 
scan_messages_planet_orbit (const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *p_id, *p_temp, *p_race, *p_clans;

     substring = g_list_append(substring, &p_id);
     substring = g_list_append(substring, &p_temp);
     substring = g_list_append(substring, &p_race);
     substring = g_list_append(substring, &p_clans);

     const gchar *regexp = "\\(-z0(.*)\\)<<<.*Temp:.*(\\b[0-9]+\\b).*(\\b\\w+\\b) race.*(\\b\\w+\\b) enemy clan";
     
     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);
    
     if (rc > 0) {

	  GwpPlanet *planet;
      
	  g_message ("MATCH: Planet #%s: %s - Temp: %s - %s clans", p_id, p_race, p_temp, p_clans);

	  planet = (GwpPlanet *)g_hash_table_lookup (planet_list, 
						     (gpointer)atoi(p_id));
	  g_assert (GWP_IS_PLANET(planet));
	  /* Assign known planet values */
	  gwp_planet_set_is_known (planet, TRUE);
	  gwp_planet_set_temperature (planet, 100-atoi(p_temp));
	  gwp_planet_set_colonists (planet, atoi(p_clans));
      
	  /* Compare func */
	  gint compare_race (gconstpointer race, gconstpointer adj) {
	       gchar *race_str = gwp_race_get_adjective(GWP_RACE(race));
	       if (strncmp(race_str, adj, strlen(adj)) == 0) 
		    return 0;
	       else
		    return 1;
	  }
	  /* Search  for the correct race object */
	  GSList *race_e = g_slist_find_custom (race_list, p_race, compare_race);
	  if (race_e != NULL) {
	       gwp_planet_set_owner (planet, g_slist_position(race_list, race_e)+1);
 
	  }
     }

     free_substring(substring);
}

/**
 * Enemy planet detected from scanners.
 */
void
scan_messages_planet_scanned (const gchar *msg_body)
{
     GList *substring = NULL;
     const gchar *p_id, *p_race;
     p_id = p_race = NULL;

     substring = g_list_append(substring, &p_id);
     substring = g_list_append(substring, &p_race);

     const gchar *regexp = ".*Planet ID#.*(\\b[0-9]+\\b).*>>> (\\b\\w+\\b)";

     gint rc = 0;
     rc = extract_from_message(msg_body, regexp, substring);

     if (rc > 0) {

	  GwpPlanet *planet;

	  g_message ("MATCH: Planet #%s: %s", p_id, p_race);
      
	  planet = (GwpPlanet *)g_hash_table_lookup (planet_list, 
						     (gpointer)atoi(p_id));
	  g_assert (GWP_IS_PLANET(planet));

	  /* Assign known planet values */
	  gwp_planet_set_is_known (planet, TRUE);
	  /* Compare func */
	  gint compare_race (gconstpointer race, gconstpointer adj) {
	       gchar *race_str = gwp_race_get_adjective(GWP_RACE(race));
	       if (strncmp(race_str, adj, strlen(adj)) == 0) 
		    return 0;
	       else
		    return 1;
	  }
	  /* Search  for the correct race object */
	  GSList *race_e = g_slist_find_custom (race_list, p_race, compare_race);
	  if (race_e != NULL) {
	       gwp_planet_set_owner (planet, g_slist_position(race_list, race_e)+1);
	  }
     }

     free_substring(substring);
}


/** 
 * This fonction extract info in message with regex
 *
 * Given a string, a pattern and a GList of string, this function call
 * pcre to extract and set the data. Don't forget to free sbstring
 * since they are unused. For this you can use free_substring
 * fonction.
 *
 * RQ: "." match all carac and newline.
 * 
 * @param msg_body the string to analyse
 * @param pattern the pattern or regex (a string)
 * @param info the list of **gchar
 *
 * @return number of substring match
 */
int extract_from_message (const gchar *msg_body, const gchar *pattern, GList *info)
{
     pcre *re;
     const gchar *error;
     gint erroffset;
     gint rc = 0;

     gint length;
     length = g_list_length(info);
     gint * ovector = malloc( ((length + 1) * 3) * sizeof(gint) );

     g_assert(msg_body != NULL);
     if(pattern == NULL)
	  g_message("regex is null");

     re = pcre_compile (pattern,      /* the pattern */
			PCRE_DOTALL, /* options
				      * "." match all carac and newline*/
			&error,      /* for error message */
			&erroffset,  /* for error offset */
			NULL);       /* use default char tables */

     if (error)
	  g_message ("WARNING: %s - offset: %d", error, erroffset);
     else 
     {
	  rc = pcre_exec (re,               /* compiled regexp */
			  NULL,             /* didn't study the pattern */
			  msg_body,         /* subject string */
			  strlen(msg_body), /* subject's length */
			  0,                /* start at offset 0 */
			  0,                /* default opts */
			  ovector,          /* offsets vector*/
			  ((length + 1) * 3));              /* ovector size */
    
	  if (rc > 0)
	  {
	       gint i;

	       for(i = 1; i <= g_list_length(info); i++)
	       {
      		    /* Get the data */
		    pcre_get_substring (msg_body, /* subject string */
					ovector,  /* offsets vector */
					rc,       /* total matches */
					i,        /* match number */
					(g_list_nth_data(info, i-1)) /* output string */
			 );
	       }
	  }
	  else
	       g_message("Error while maching message, nothing found.");
     }

     free(re);
     free(ovector);
     return rc;
}

/** 
 * Free memory used by substring in a GList, and the GList.
 *
 * Free the substring in a GList created by extract_from_message()
 * fonction. Free the GList to. If GList is NULL, simply return.
 * 
 * @param substring a GList of **gchar
 */
void free_substring(GList *substring)
{
     /* free substring */
     gint i;
     gchar **tmp;

     if (substring == NULL)
	  return;
     /* free substring */
     for(i = 0; i < g_list_length(substring); i++)
     {
	  tmp = g_list_nth_data(substring, i);
	  g_free(*tmp);
     }
     
     /* free Glist */
     g_list_free(substring);
}

static 
gchar *padstr (gchar *str, 
	       gint   qty)
{
  gchar *ret = g_malloc(qty);

  memset (ret, ' ', qty);
  if (strlen(str) < qty)
    memcpy (ret, str, strlen(str));
  else
    memcpy (ret, str, qty);

  return ret;
}
