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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gnome.h>
#include <sys/stat.h>
#include <unistd.h>

#include "global.h"
#include "game_state.h"
#include "vp_utils.h"
#include "vp_types.h"
/* #include "ship.h" */
#include "planet.h"
#include "base.h"
#include "starchart.h"
#include "gwp-planet.h"
#include "gwp-starbase.h"
#include "gwp-ship.h"

/*
 * Data Loading Init Function
 */
void init_data (void)
{
  /* Game state initializations */
  game_set_starchart_zoom(game_state, 1.0);
  game_set_pnames(game_state, load_pnames_file(PNAMES));

  xyplanet_list = load_xyplan(XYPLAN);
  g_message ("XYPLAN loaded...");
  shipxy_list = load_shipxy(game_get_race(game_state));
  g_message ("SHIPXY loaded...");
  target_list = load_target(game_get_race(game_state));
  g_message ("TARGET loaded...");
  planet_list = load_pdata();
  g_message ("PDATA loaded...");
  ship_list = load_sdata();
  g_message ("SDATA loaded...");
  load_gen_data();
  g_message("GENx loaded...");
  base_list = load_bdata();
  g_message("BDATA loaded...");
}

/*
 * Helper Loading functions
 */
gint16 getWord (guchar * p)
{
  return 256 * p[1] + p[0];
}

gint32 getDWord (guchar * p)
{
  return 16777216 * p[3] + 65536 * p[2] + 256 * p[1] + p[0];
}

/*
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
    *x2 = (gdouble) 0;
    *y2 = (gdouble) 0;
  }
}

/*
 * Converts Canvas World Coord system to VP coords
 */
void vp_coord_w2v (gdouble x1, gdouble y1, gint16 * x2, gint16 * y2)
{
  /* Convert X coordinate */
  *x2 = (gint16) x1 + 1000 - CANVAS_OFFSET_INT;
  *y2 = (gint16) abs (y1 - 3000) + CANVAS_OFFSET_INT;
}

/*
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
  if ((pname = fopen (game_get_full_path(game_state, pnames_str->str), "r")) == NULL) {
    pnames_str = g_string_down (pnames_str);
    if ((pname = fopen (game_get_full_path(game_state, pnames_str->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 game_get_full_path(game_state, pnames_str->str));
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

/*
 * Loads planets coordinates into a list
 */
GList * load_xyplan (gchar * xyplan_file)
{
  FILE *xyplan;
  GList *coords_list = NULL;
  VpXYPlanReg coords, *tmp;
  GString *xyplan_str;
  
  xyplan_str = g_string_new (xyplan_file);
  xyplan_str = g_string_up (xyplan_str);
  
  if ((xyplan = fopen(game_get_full_path(game_state, xyplan_str->str), "r")) == NULL) {
    xyplan_str = g_string_down (xyplan_str);
    if ((xyplan =
	 fopen (game_get_full_path(game_state, xyplan_str->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 game_get_full_path(game_state, xyplan_str->str));
      exit (-1);
    }
  }
  
  rewind (xyplan);
  while (!feof (xyplan)) {
    fread (&coords, sizeof (VpXYPlanReg), 1, xyplan);
    
    /* Copy planet to tmp variable to assign it in GList */
    tmp = g_malloc (sizeof (VpXYPlanReg));
    *tmp = coords;

    // Append object to list
    coords_list = g_list_append (coords_list, tmp);
  }
  fclose (xyplan);

  return coords_list;
}

GHashTable * load_target (gint race)
{
  FILE *target;
  GHashTable *target_list;
  GString *target_file;
  VpTargetReg target_reg, *tmp;
  gint16 i, target_nr;
  gchar buffer[34];
  
  // Initialize hash
  target_list = g_hash_table_new (NULL, NULL);
  
  // Initialize file name
  target_file = g_string_new ("TARGET");
  target_file =
    g_string_append (target_file, g_strdup_printf ("%d.DAT", race));
  
  if ((target = fopen(game_get_full_path(game_state, target_file->str), "r")) == NULL) {
    target_file = g_string_down (target_file);
    if ((target =
	 fopen (game_get_full_path(game_state, target_file->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 game_get_full_path(game_state, target_file->str));
      exit (-1);
    }
  }
  
  rewind (target);
  fread (&target_nr, sizeof (gint16), 1, target);

  // read registers
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
    
    // Assign new memory for new target
    tmp = g_malloc (sizeof (VpTargetReg));
    *tmp = target_reg;
    // Add new target
    g_hash_table_insert (target_list, (gpointer)(gint)tmp->id, tmp);
  }
  fclose (target);

  return target_list;
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
  
  shipxy_file = g_string_new ("SHIPXY");
  shipxy_file =
    g_string_append (shipxy_file, g_strdup_printf ("%d.DAT", race));
  
  if ((shipxy = fopen(game_get_full_path(game_state, shipxy_file->str), "r")) == NULL) {
    shipxy_file = g_string_down (shipxy_file);
    if ((shipxy =
	 fopen (game_get_full_path(game_state, shipxy_file->str), "r")) == NULL) {
      g_message ("ERROR trying to open %s file.\n",
		 game_get_full_path(game_state, shipxy_file->str));
      exit (-1);
    }
  }
  
  rewind (shipxy);
  while (!feof (shipxy)) {
    fread (&coords, sizeof (VpShipXYReg), 1, shipxy);
    
    // Copy ship to tmp variable to assign it in GList
    tmp = g_malloc (sizeof (VpShipXYReg));
    *tmp = coords;
    
    // Append object to list
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
  GString *sdata_dis_file, *sdata_dat_file;
  FILE *sdata = NULL;
  VpShipReg ship;
  VpShipXYReg *coords = NULL;
  VpShipReg *tmp = NULL;
  Ship *ship_reg = NULL;
  GwpShip *s;
  GHashTable *ship_list = NULL;
  VpTargetReg *target_reg;
  gint i, idx;
  gint16 ships_nr;
  gchar buffer[107];
  gchar *fc_tmp, *name_tmp;
  struct stat dis_data;
  struct stat dat_data;
  
  sdata_dis_file =
    g_string_new (g_strdup_printf ("SHIP%d.DIS", game_get_race(game_state)));
  sdata_dat_file =
    g_string_new (g_strdup_printf ("SHIP%d.DAT", game_get_race(game_state)));
  
  // Init Ship Hash
  ship_list = g_hash_table_new (NULL, NULL);
  
  // Load Ship Data
  if (g_file_test (game_get_full_path(game_state, sdata_dis_file->str),
      G_FILE_TEST_EXISTS)) {
    if (g_file_test (game_get_full_path(game_state, sdata_dat_file->str),
	G_FILE_TEST_EXISTS)) {
      stat (game_get_full_path(game_state, sdata_dis_file->str), &dis_data);
      stat (game_get_full_path(game_state, sdata_dat_file->str), &dat_data);
      
      // Check what file to use
      if (dis_data.st_mtime > dat_data.st_mtime) {
	if ((sdata =
	     fopen (game_get_full_path(game_state, sdata_dis_file->str),
		    "r")) == NULL) {
	  g_message ("ERROR trying to open %s file.\n",
		     game_get_full_path(game_state, sdata_dis_file->str));
	  exit (-1);
	}
      } else {
	if ((sdata =
	     fopen (game_get_full_path(game_state, sdata_dat_file->str),
		    "r")) == NULL) {
	  g_message ("ERROR trying to open %s file.\n",
		     game_get_full_path(game_state, sdata_dat_file->str));
	  exit (-1);
	}
      }
    }
  } else {
    sdata_dis_file = g_string_down (sdata_dis_file);
    if (g_file_test (game_get_full_path(game_state, sdata_dis_file->str),
		     G_FILE_TEST_EXISTS)) {
      sdata_dat_file = g_string_down (sdata_dat_file);
      if (g_file_test (game_get_full_path(game_state, sdata_dat_file->str),
		       G_FILE_TEST_EXISTS)) {
	stat (game_get_full_path(game_state, sdata_dis_file->str), &dis_data);
	stat (game_get_full_path(game_state, sdata_dat_file->str), &dat_data);
	
	// Check what file to use
	if (dis_data.st_mtime > dat_data.st_mtime) {
	  if ((sdata =
	       fopen (game_get_full_path(game_state, sdata_dis_file->str),
		      "r")) == NULL) {
	    g_message ("ERROR trying to open %s file.\n",
		       game_get_full_path(game_state, sdata_dis_file->str));
	    exit (-1);
	  }
	} else {
	  if ((sdata =
	       fopen (game_get_full_path(game_state, sdata_dat_file->str),
		      "r")) == NULL) {
	    g_message ("ERROR trying to open %s file.",
		       game_get_full_path(game_state, sdata_dat_file->str));
	    exit (-1);
	  }
	}
      }
    } else {
      g_message ("ERROR: %s file not found.\n",
		 game_get_full_path(game_state, sdata_dis_file->str));
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
    /*
    ship.id = getWord (buffer);
    ship.owner = getWord (buffer + 2);
    ship.fcode[0] = buffer[4];
    ship.fcode[1] = buffer[5];
    ship.fcode[2] = buffer[6];
    ship.warp_factor = getWord (buffer + 7);
    ship.x_to_waypoint = getWord (buffer + 9);
    ship.y_to_waypoint = getWord (buffer + 11);
    ship.x_position = getWord (buffer + 13);
    ship.y_position = getWord (buffer + 15);
    */
    gwp_object_set_id (GWP_OBJECT(s), getWord(buffer));
    gwp_ship_set_owner (s, getWord(buffer + 2));

    /* Friendly code assembly */
    fc_tmp = g_malloc (sizeof(gchar)*4);
    fc_tmp[0] = buffer[4];
    fc_tmp[1] = buffer[5];
    fc_tmp[2] = buffer[6];
    fc_tmp[3] = '\0';
    gwp_ship_set_fcode(s, g_string_new(fc_tmp));
    g_free(fc_tmp);

    gwp_fo_set_speed (GWP_FLYING_OBJECT(s), getWord(buffer + 7));
    gwp_ship_set_x_to_waypoint (s, getWord(buffer + 9));
    gwp_ship_set_y_to_waypoint (s, getWord(buffer + 11));
    gwp_object_set_x_coord (GWP_OBJECT(s), getWord(buffer + 13));
    gwp_object_set_y_coord (GWP_OBJECT(s), getWord(buffer + 15));

    /*
    ship.engine_type = getWord (buffer + 17);
    ship.hull_type = getWord (buffer + 19);
    ship.beams_type = getWord (buffer + 21);
    ship.beams = getWord (buffer + 23);
    ship.fighter_bays = getWord (buffer + 25);
    */
    gwp_ship_set_engines_type (s, getWord(buffer + 17));
    gwp_ship_set_hull_type (s, getWord(buffer + 19));
    gwp_ship_set_beams_type (s, getWord(buffer + 21));
    gwp_ship_set_beams (s, getWord(buffer + 23));
    gwp_ship_set_fighter_bays (s, getWord(buffer + 25));

    /* Check if its a torp or carrier ship */
    /*
    if (ship.fighter_bays == 0)	{
      ship.torpedoes_type = getWord (buffer + 27);
      ship.torpedoes_launchers = getWord (buffer + 31);
    } else {
      ship.torpedoes_type = 0;
      ship.torpedoes_launchers = 0;
    }
    */
    if (gwp_ship_get_fighter_bays (s) == 0) {
      gwp_ship_set_torps_type (s, getWord(buffer + 27));
      gwp_ship_set_torps (s, getWord(buffer + 29));
      gwp_ship_set_torps_launchers (s, getWord(buffer + 31));
    } else {
      gwp_ship_set_torps_type (s, 0);
      gwp_ship_set_fighters (s, getWord(buffer + 29));
      gwp_ship_set_torps_launchers (s, 0);      
    }

    /*
    ship.torpedoes_fighters = getWord (buffer + 29);
    ship.mission = getWord (buffer + 33);
    ship.primary_enemy = getWord (buffer + 35);
    ship.tow_mission_ship_id = getWord (buffer + 37);
    ship.damage = getWord (buffer + 39);
    ship.crew = getWord (buffer + 41);
    ship.colonists = getWord (buffer + 43);
    */
    gwp_ship_set_mission (s, getWord(buffer + 33));
    gwp_ship_set_primary_enemy (s, getWord(buffer + 35));
    gwp_ship_set_tow_ship_id (s, getWord(buffer + 37));
    gwp_ship_set_damage (s, getWord(buffer + 39));
    gwp_ship_set_crew (s, getWord(buffer + 41));
    gwp_ship_set_colonists (s, getWord(buffer + 43));

    /*
    ship.name[0] = buffer[45];
    ship.name[1] = buffer[46];
    ship.name[2] = buffer[47];
    ship.name[3] = buffer[48];
    ship.name[4] = buffer[49];
    ship.name[5] = buffer[50];
    ship.name[6] = buffer[51];
    ship.name[7] = buffer[52];
    ship.name[8] = buffer[53];
    ship.name[9] = buffer[54];
    ship.name[10] = buffer[55];
    ship.name[11] = buffer[56];
    ship.name[12] = buffer[57];
    ship.name[13] = buffer[58];
    ship.name[14] = buffer[59];
    ship.name[15] = buffer[60];
    ship.name[16] = buffer[61];
    ship.name[17] = buffer[62];
    ship.name[18] = buffer[63];
    ship.name[19] = buffer[64];
    ship.name[20] = '\0';
    */
    name_tmp = g_malloc (sizeof(gchar)*21);
    for (idx = 0; idx <= 19; idx++) {
      name_tmp[idx] = buffer[45+idx];
    }
    name_tmp[20] = '\0';
    gwp_object_set_name (GWP_OBJECT(s), g_string_new(name_tmp));
    g_free(name_tmp);

    /*
    ship.neutronium = getWord (buffer + 65);
    ship.tritanium = getWord (buffer + 67);
    ship.duranium = getWord (buffer + 69);
    ship.molybdenum = getWord (buffer + 71);
    ship.supplies = getWord (buffer + 73);
    */
    gwp_ship_set_neutronium (s, getWord(buffer + 65));
    gwp_ship_set_tritanium (s, getWord(buffer + 67));
    gwp_ship_set_duranium (s, getWord(buffer + 69));
    gwp_ship_set_molybdenum (s, getWord(buffer + 71));
    gwp_ship_set_supplies (s, getWord(buffer + 73));

    /*
    ship.unload_neutronium = getWord (buffer + 75);
    ship.unload_tritanium = getWord (buffer + 77);
    ship.unload_duranium = getWord (buffer + 79);
    ship.unload_molybdenum = getWord (buffer + 81);
    ship.unload_colonists = getWord (buffer + 83);
    ship.unload_supplies = getWord (buffer + 85);
    ship.unload_planet_id = getWord (buffer + 87);
    */
    gwp_ship_set_unload_neutronium (s, getWord(buffer + 75));
    gwp_ship_set_unload_tritanium (s, getWord(buffer + 77));
    gwp_ship_set_unload_duranium (s, getWord(buffer + 79));
    gwp_ship_set_unload_molybdenum (s, getWord(buffer + 81));
    gwp_ship_set_unload_colonists (s, getWord(buffer + 83));
    gwp_ship_set_unload_supplies (s, getWord(buffer + 85));
    gwp_ship_set_unload_planet_id (s, getWord(buffer + 87));

    /*
    ship.transfer_neutronium = getWord (buffer + 89);
    ship.transfer_tritanium = getWord (buffer + 91);
    ship.transfer_duranium = getWord (buffer + 93);
    ship.transfer_molybdenum = getWord (buffer + 95);
    ship.transfer_colonists = getWord (buffer + 97);
    ship.transfer_supplies = getWord (buffer + 99);
    ship.transfer_ship_id = getWord (buffer + 101);
    */
    gwp_ship_set_transfer_neutronium (s, getWord(buffer + 89));
    gwp_ship_set_transfer_tritanium (s, getWord(buffer + 91));
    gwp_ship_set_transfer_duranium (s, getWord(buffer + 93));
    gwp_ship_set_transfer_molybdenum (s, getWord(buffer + 95));
    gwp_ship_set_transfer_colonists (s, getWord(buffer + 97));
    gwp_ship_set_transfer_supplies (s, getWord(buffer + 99));
    gwp_ship_set_transfer_ship_id (s, getWord(buffer + 101));

    /*
    ship.intercept_mission_ship_id = getWord (buffer + 103);
    ship.megacredits = getWord (buffer + 105);
    */
    gwp_ship_set_intercept_ship_id (s, getWord(buffer + 103));
    gwp_ship_set_megacredits (s, getWord(buffer + 105));
    
    /* Calculate heading from other data */
    gwp_fo_set_heading(GWP_FLYING_OBJECT(s), gwp_ship_calculate_heading(s));

    /* Assign new memory for new ship */
    /*
    tmp = g_malloc (sizeof (VpShipReg));
    *tmp = ship;
    */
           
    /* Generate the ship register */
    /*
    ship_reg = g_malloc (sizeof (Ship));
    ship_reg->sdata = tmp;
    ship_reg->fleet_num = 0;
    coords = g_list_nth_data (shipxy_list, ship.id - 1);
    ship_reg->x = coords->x;
    ship_reg->y = coords->y;
    ship_reg->owner = ship_reg->sdata->owner;
    ship_reg->tdata = NULL;
    */    

    /* Add ship to list */
    /*
    g_hash_table_insert (ship_list, 
			 (gpointer)(gint)ship_get_id (ship_reg), 
			 ship_reg);
    */
    g_hash_table_insert (ship_list, 
			 (gpointer)(gint)gwp_object_get_id (GWP_OBJECT(s)), s);
  }

  /* Now add the rest unknown ships */
  for (i = 0; i < g_list_length (shipxy_list); i++) {
    /* Check if we have not this ship */
    if (gwp_ship_get (ship_list, i + 1) == NULL) {

      s = gwp_ship_new();

      coords = g_list_nth_data (shipxy_list, i);
/*       ship_reg = g_malloc (sizeof (Ship)); */
/*       ship_reg->sdata = NULL; */
/*       ship_reg->x = coords->x; */
/*       ship_reg->y = coords->y; */
/*       ship_reg->owner = 0; */
      gwp_object_set_x_coord (GWP_OBJECT(s), coords->x);
      gwp_object_set_y_coord (GWP_OBJECT(s), coords->y);
      
      /* If we have more data on TARGETx.DAT, we add it */
      if ((target_reg =
	   g_hash_table_lookup (target_list,
				(gconstpointer) (i + 1))) != NULL) {
	/* ship_reg->tdata = target_reg; */
	gwp_object_set_id (GWP_OBJECT(s), target_reg->id);
	gwp_object_set_name (GWP_OBJECT(s), g_string_new(target_reg->name));
	gwp_fo_set_speed (GWP_FLYING_OBJECT(s), target_reg->warp_factor);
	gwp_fo_set_heading (GWP_FLYING_OBJECT(s), target_reg->heading);
	gwp_ship_set_hull_type (s, target_reg->hull_type);
	gwp_ship_set_owner (s, target_reg->owner);
      }
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
  GString *pdata_dis_file, *pdata_dat_file;
  FILE *pdata = NULL;
  VpXYPlanReg *coords = NULL;
  GHashTable *planet_list = NULL;
  GList *pnames = NULL;
  gint16 planets_nr;
  gint i;
  gchar buffer[85];
  struct stat dis_data;
  struct stat dat_data;
  GwpPlanet *p;
  gchar *fc_tmp;

  pdata_dis_file =
    g_string_new (g_strdup_printf ("PDATA%d.DIS", game_get_race(game_state)));
  pdata_dat_file =
    g_string_new (g_strdup_printf ("PDATA%d.DAT", game_get_race(game_state)));

  /* Init Planet Hash */
  planet_list = g_hash_table_new (NULL, NULL);

  /* Load Additional Data */
  pnames = game_get_pnames(game_state);

  /* Load Planet Data... */
  if (g_file_test (game_get_full_path(game_state, pdata_dis_file->str),
		   G_FILE_TEST_EXISTS)) {
    if (g_file_test (game_get_full_path(game_state, pdata_dat_file->str),
		     G_FILE_TEST_EXISTS)) {
      stat (game_get_full_path(game_state, pdata_dis_file->str), &dis_data);
      stat (game_get_full_path(game_state, pdata_dat_file->str), &dat_data);
      
      /* Check what file to use */
      if (dis_data.st_mtime > dat_data.st_mtime) {
	if ((pdata =
	     fopen (game_get_full_path(game_state, pdata_dis_file->str),
		    "r")) == NULL) {
	  g_message ("ERROR trying to open %s file.\n",
		     game_get_full_path(game_state, pdata_dis_file->str));
	  exit (-1);
	}
      } else {
	if ((pdata =
	     fopen (game_get_full_path(game_state, pdata_dat_file->str),
		    "r")) == NULL) {
	  g_message ("ERROR trying to open %s file.\n",
		     game_get_full_path(game_state, pdata_dat_file->str));
	  exit (-1);
	}
      }
    }
  } else {
    pdata_dis_file = g_string_down (pdata_dis_file);
    if (g_file_test (game_get_full_path(game_state, pdata_dis_file->str),
		     G_FILE_TEST_EXISTS)) {
      pdata_dat_file = g_string_down (pdata_dat_file);
      if (g_file_test (game_get_full_path(game_state, pdata_dat_file->str),
		       G_FILE_TEST_EXISTS)) {
	stat (game_get_full_path(game_state, pdata_dis_file->str), &dis_data);
	stat (game_get_full_path(game_state, pdata_dat_file->str), &dat_data);
	
	/* Check what file to use */
	if (dis_data.st_mtime > dat_data.st_mtime) {
	  if ((pdata =
	       fopen (game_get_full_path(game_state, pdata_dis_file->str),
		      "r")) == NULL) {
	    g_message ("ERROR trying to open %s file.\n",
		       game_get_full_path(game_state, pdata_dis_file->str));
	    exit (-1);
	  }
	} else {
	  if ((pdata =
	       fopen (game_get_full_path(game_state, pdata_dat_file->str),
		      "r")) == NULL) {
	    g_message ("ERROR trying to open %s file.\n",
		       game_get_full_path(game_state, pdata_dat_file->str));
	    exit (-1);
	  }
	}
      }
    } else {
      g_message ("ERROR: %s file not found.\n",
		 game_get_full_path(game_state, pdata_dis_file->str));
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
    gwp_planet_set_fcode (p, g_string_new(fc_tmp));
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

    gwp_planet_set_natives_race (p, getWord(buffer+79));

    gwp_planet_set_temperature (p, getWord(buffer+81));
    gwp_planet_set_build_base (p, getWord(buffer+83));

    coords = g_list_nth_data (xyplanet_list, gwp_object_get_id(GWP_OBJECT(p))-1);
    gwp_object_set_x_coord (GWP_OBJECT(p), coords->x);
    gwp_object_set_y_coord (GWP_OBJECT(p), coords->y);
    gwp_object_set_name (GWP_OBJECT(p), g_string_new((gchar *)g_list_nth_data(pnames, (gint)gwp_object_get_id (GWP_OBJECT(p)) - 1)));


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
      gwp_planet_set_owner (p, 0);
      gwp_object_set_id (GWP_OBJECT(p), i+1);
      gwp_object_set_name (GWP_OBJECT(p), g_string_new((gchar *) g_list_nth_data (pnames, i)));

      /* Add planet to list */
      g_hash_table_insert (planet_list, (gpointer)(i+1), p);
    }
  }
  fclose (pdata);
  
  return planet_list;
}

/* X, Y coords in world coord system... */
void load_object_per_quad (gpointer obj, GSList * obj_per_quad[TOTAL_QUADS],
			   gdouble wx, gdouble wy)
{
  gint q;
  
  if (obj != NULL) {
    q = get_quadrant (wx, wy);
    obj_per_quad[q] = g_slist_append (obj_per_quad[q], obj);
  }
}

/*
void
load_ships_per_quad (GnomeCanvasItem * ship,
		     GSList * ships_per_quad[TOTAL_QUADS])
{
  gint q;
  gdouble x, y;

  if (ship != NULL)
    {
      starchart_get_object_center_coord (ship, &x, &y);
      q = get_quadrant (x, y);
      ships_per_quad[q] = g_slist_append (ships_per_quad[q], ship);
    }
}
*/

gboolean vp_can_unpack(gchar *game_dir, gint race)
/*
 * Returns TRUE if the race can be unpacked on given directory
 */
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
  
  tmp = g_strdup_printf ("%d.dis", race);
  pdata = g_string_append (pdata, tmp);
  g_free(tmp);

  tmp = g_strdup_printf ("%d.dis", race);
  ship = g_string_append (ship, tmp);
  g_free(tmp);

  tmp = g_strdup_printf ("%d.rst", race);
  rst = g_string_append (rst, tmp);
  g_free(tmp);

  pdata = g_string_prepend(pdata, game_dir);
  ship = g_string_prepend(ship, game_dir);
  rst = g_string_prepend(rst, game_dir);

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

void load_gen_data(void)
{
  FILE *gen_dat = NULL;
  GString *gen_file_name;
  gchar buffer[155];

  gen_file_name = g_string_new(g_strdup_printf("gen%d.dat", 
					       game_get_race(game_state)));
  gen_dat = fopen(game_get_full_path(game_state, gen_file_name->str), "r");
  
  if(!gen_dat) {
    g_message("ERROR trying to open %s file.",
	      game_get_full_path(game_state, gen_file_name->str));
    exit(-1);
  }
  rewind(gen_dat);

  /* Read data from file */
  fread(buffer, 155, 1, gen_dat);

  /* Set data to structures */
  game_set_turn_number(game_state, getWord(buffer + 153));

  /* Close file */
  fclose(gen_dat);
}

GHashTable *load_bdata(void)
{
  GString *bdata_dis_file, *bdata_dat_file;
  FILE *bdata = NULL;
  Base *base;
  GwpStarbase *b;
  GwpPlanet *p;
  GHashTable *base_list = NULL;
  struct stat dis_data;
  struct stat dat_data;
  gint16 bases_nr;
  gint i, idx;
  gchar buffer[156];

  bdata_dis_file = 
    g_string_new(g_strdup_printf("bdata%d.dis", game_get_race(game_state)));
  bdata_dat_file =
    g_string_new(g_strdup_printf("bdata%d.dat", game_get_race(game_state)));

  /* Init base hash */
  base_list = g_hash_table_new(NULL, NULL);

  /* Load Base Data...*/
  if(g_file_test(game_get_full_path(game_state, bdata_dis_file->str),
		 G_FILE_TEST_EXISTS)) {
    if(g_file_test(game_get_full_path(game_state, bdata_dat_file->str),
		   G_FILE_TEST_EXISTS)) {
      /* Both files exist... */
      stat(game_get_full_path(game_state, bdata_dis_file->str), &dis_data);
      stat(game_get_full_path(game_state, bdata_dat_file->str), &dat_data);

      /* Check which file to use */
      if(dis_data.st_mtime > dat_data.st_mtime) {
	if((bdata =
	    fopen(game_get_full_path(game_state, bdata_dis_file->str),
		  "r")) == NULL) {
	  g_message("ERROR trying to open %s file.",
		    game_get_full_path(game_state, bdata_dis_file->str));
	  exit(-1);
	}
      } else {
	if((bdata =
	    fopen(game_get_full_path(game_state, bdata_dat_file->str),
		  "r")) == NULL) {
	  g_message("ERROR trying to open %s file.",
		    game_get_full_path(game_state, bdata_dat_file->str));
	  exit(-1);
	}
      }
    }
  }

  rewind(bdata);

  /* How many bases? */
  fread(&bases_nr, sizeof(gint16), 1, bdata);

  for(i = 0; i < bases_nr; i++) {
    gint16 starbase_id;

    /* Read Base data from file */
    fread(buffer, 156, 1, bdata);

    /* Load Base data on struct */
    base = base_new();
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

    /* Add starbase to list */
    g_hash_table_insert(base_list, (gpointer)(gint)gwp_starbase_get_id(b), b);
  }
  fclose(bdata);

  return base_list;
}
