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
#include "ship.h"
#include "planet.h"
#include "base.h"
#include "starchart.h"
#include "gwp-planet.h"

/*
 * Data Loading Init Function
 */
void init_data (void)
{
  /* Game state initializations */
  game_set_starchart_zoom(game_state, 1.0);
  game_set_pnames(game_state, load_pnames_file(PNAMES));

  xyplanet_list = load_xyplan(XYPLAN);
  g_message ("XYPLAN cargado...");
  shipxy_list = load_shipxy(game_get_race(game_state));
  g_message ("SHIPXY cargado...");
  target_list = load_target(game_get_race(game_state));
  g_message ("TARGET cargado...");
  planet_list = load_pdata();
  g_message ("PDATA cargado...");
  ship_list = load_sdata();
  g_message ("SDATA cargado...");
  load_gen_data();
  g_message("GENx cargado...");
  base_list = load_bdata();
  g_message("BDATA cargado...");
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
  GHashTable *ship_list = NULL;
  VpTargetReg *target_reg;
  gint i;
  gint16 ships_nr;
  gchar buffer[107];
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
  // How many ships?
  fread (&ships_nr, sizeof (gint16), 1, sdata);

  for (i = 0; i < ships_nr; i++) {
    // Read Ship data from file
    fread (buffer, 107, 1, sdata);
    
    // Load Ship Data on struct
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
    ship.engine_type = getWord (buffer + 17);
    ship.hull_type = getWord (buffer + 19);
    ship.beams_type = getWord (buffer + 21);
    ship.beams = getWord (buffer + 23);
    ship.fighter_bays = getWord (buffer + 25);
    // Check if its a torp or carrier ship
    if (ship.fighter_bays == 0)	{
      ship.torpedoes_type = getWord (buffer + 27);
      ship.torpedoes_launchers = getWord (buffer + 31);
    } else {
      ship.torpedoes_type = 0;
      ship.torpedoes_launchers = 0;
    }
    ship.torpedoes_fighters = getWord (buffer + 29);
    ship.mission = getWord (buffer + 33);
    ship.primary_enemy = getWord (buffer + 35);
    ship.tow_mission_ship_id = getWord (buffer + 37);
    ship.damage = getWord (buffer + 39);
    ship.crew = getWord (buffer + 41);
    ship.colonists = getWord (buffer + 43);
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
    ship.neutronium = getWord (buffer + 65);
    ship.tritanium = getWord (buffer + 67);
    ship.duranium = getWord (buffer + 69);
    ship.molybdenum = getWord (buffer + 71);
    ship.supplies = getWord (buffer + 73);
    ship.unload_neutronium = getWord (buffer + 75);
    ship.unload_tritanium = getWord (buffer + 77);
    ship.unload_duranium = getWord (buffer + 79);
    ship.unload_molybdenum = getWord (buffer + 81);
    ship.unload_colonists = getWord (buffer + 83);
    ship.unload_supplies = getWord (buffer + 85);
    ship.unload_planet_id = getWord (buffer + 87);
    ship.transfer_neutronium = getWord (buffer + 89);
    ship.transfer_tritanium = getWord (buffer + 91);
    ship.transfer_duranium = getWord (buffer + 93);
    ship.transfer_molybdenum = getWord (buffer + 95);
    ship.transfer_colonists = getWord (buffer + 97);
    ship.transfer_supplies = getWord (buffer + 99);
    ship.transfer_ship_id = getWord (buffer + 101);
    ship.intercept_mission_ship_id = getWord (buffer + 103);
    ship.megacredits = getWord (buffer + 105);
    
    // Assign new memory for new ship
    tmp = g_malloc (sizeof (VpShipReg));
    *tmp = ship;
           
    // Generate the ship register
    ship_reg = g_malloc (sizeof (Ship));
    ship_reg->sdata = tmp;
    ship_reg->fleet_num = 0;  // No fleet assigned
    coords = g_list_nth_data (shipxy_list, ship.id - 1);
    ship_reg->x = coords->x;
    ship_reg->y = coords->y;
    ship_reg->owner = ship_reg->sdata->owner;
    ship_reg->tdata = NULL;
    
    // Add ship to list
    g_hash_table_insert (ship_list, 
			 (gpointer)(gint)ship_get_id (ship_reg), 
			 ship_reg);
  }

  // Now add the rest unknown ships
  for (i = 0; i < g_list_length (shipxy_list); i++) {
    // Check if we have not this ship
    if (ship_get (ship_list, i + 1) == NULL) {
      coords = g_list_nth_data (shipxy_list, i);
      ship_reg = g_malloc (sizeof (Ship));
      ship_reg->sdata = NULL;
      ship_reg->x = coords->x;
      ship_reg->y = coords->y;
      ship_reg->owner = 0;
      
      // If we have more data on TARGETx.DAT, we add it
      if ((target_reg =
	   g_hash_table_lookup (target_list,
				(gconstpointer) (i + 1))) != NULL) {
	ship_reg->tdata = target_reg;
      } else {
	ship_reg->tdata = NULL;
      }
      // Add ship to list
      g_hash_table_insert (ship_list, (gpointer)(i + 1), ship_reg);
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
  VpPlanetReg planet;
  VpXYPlanReg *coords = NULL;
  VpPlanetReg *tmp = NULL;
  Planet *planet_reg = NULL;
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
	
	// Check what file to use
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

    /* Read Planet data from file */
    fread (buffer, 85, 1, pdata);
    
    /* Load Planet Data on object */
    gwp_planet_set_owner (p, buffer);
    gwp_object_set_id (p, buffer+2);
    fc_tmp = g_malloc(sizeof(gchar)*4);
    /* Friendly code assembly */
    fc_tmp[0] = buffer[4];
    fc_tmp[1] = buffer[5];
    fc_tmp[2] = buffer[6];
    fc_tmp[3] = '\0';
    gwp_planet_set_fcode (p, g_string_new(fc_tmp));
    g_free(fc_tmp);
    gwp_planet_set_mines (p, buffer+7);
    gwp_planet_set_factories (p, buffer+9);
    gwp_planet_set_defense_posts (p, buffer+11);
    gwp_planet_set_mined_neutronium (p, buffer+13);
    gwp_planet_set_mined_tritanium (p, buffer+17);
    gwp_planet_set_mined_duranium (p, buffer+21);
    gwp_planet_set_mined_molybdenum (p, buffer+25);
    gwp_planet_set_colonists (p, buffer+29);
    gwp_planet_set_supplies (p, buffer+33);
    gwp_planet_set_megacredits (p, buffer+37);
    gwp_planet_set_ground_neutronium (p, buffer+41);
    gwp_planet_set_ground_tritanium (p, buffer+45);
    gwp_planet_set_ground_duranium (p, buffer+49);
    gwp_planet_set_ground_molybdenum (p, buffer+53);
    gwp_planet_set_dens_neutronium (p, buffer+57);
    gwp_planet_set_dens_tritanium (p, buffer+59);
    gwp_planet_set_dens_duranium (p, buffer+61);
    gwp_planet_set_dens_molybdenum (p, buffer+63);
    /*
    planet.owner = getWord (buffer);
    planet.id = getWord (buffer + 2);
    planet.fcode[0] = buffer[4];
    planet.fcode[1] = buffer[5];
    planet.fcode[2] = buffer[6];
    planet.mines = getWord (buffer + 7);
    planet.factories = getWord (buffer + 9);
    planet.defense_posts = getWord (buffer + 11);
    planet.mined_neutronium = getDWord (buffer + 13);
    planet.mined_tritanium = getDWord (buffer + 17);
    planet.mined_duranium = getDWord (buffer + 21);
    planet.mined_molybdenum = getDWord (buffer + 25);
    planet.colonists = getDWord (buffer + 29);
    planet.supplies = getDWord (buffer + 33);
    planet.megacredits = getDWord (buffer + 37);
    planet.ground_neutronium = getDWord (buffer + 41);
    planet.ground_tritanium = getDWord (buffer + 45);
    planet.ground_duranium = getDWord (buffer + 49);
    planet.ground_molybdenum = getDWord (buffer + 53);
    planet.dens_neutronium = getWord (buffer + 57);
    planet.dens_tritanium = getWord (buffer + 59);
    planet.dens_duranium = getWord (buffer + 61);
    planet.dens_molybdenum = getWord (buffer + 63);
    */
    gwp_planet_set_tax_colonists (p, buffer+65);
    gwp_planet_set_tax_natives (p, buffer+67);
    gwp_planet_set_happiness_colonists (p, buffer+69);
    gwp_planet_set_happiness_natives (p, buffer+71);
    gwp_planet_set_native_spi (p, buffer+73);
    gwp_planet_set_natives (p, buffer+75);
    gwp_planet_set_native_race (p, buffer+79);
    gwp_planet_set_temperature (p, buffer+81);
    gwp_planet_set_build_base (p, buffer+83);
    /*
    planet.tax_colonists = getWord (buffer + 65);
    planet.tax_natives = getWord (buffer + 67);
    planet.happiness_colonists = getWord (buffer + 69);
    planet.happiness_natives = getWord (buffer + 71);
    planet.native_spi = getWord (buffer + 73);
    planet.natives = getDWord (buffer + 75);
    planet.native_race = getWord (buffer + 79);
    planet.temperature = getWord (buffer + 81);
    planet.build_base = getWord (buffer + 83);
    */
    
    /* Assign new memory for new planet */
    /*
    tmp = g_malloc (sizeof (VpPlanetReg));
    *tmp = planet;
    */
    
    /* Generate the planet register */
    /*
    planet_reg = g_malloc (sizeof (Planet));
    planet_reg->pdata = tmp;
    */
    coords = g_list_nth_data (xyplanet_list, planet.id - 1);
    gwp_object_set_x_coord (p, coords->x);
    gwp_object_set_y_coord (p, coords->y);
    gwp_object_set_name (p, g_string_new((gchar *)g_list_nth_data(pnames, (gint)gwp_object_get_id (p) - 1)));
    /*
    planet_reg->x = coords->x;
    planet_reg->y = coords->y;
    planet_reg->owner = planet_reg->pdata->owner;
    planet_reg->id = planet_reg->pdata->id;
    strcpy (planet_reg->name,
	    (gchar *) g_list_nth_data (pnames, planet.id - 1));
    */

    /* Add planet to list */
    /*
    g_hash_table_insert (planet_list, (gpointer)(gint)planet_get_id (planet_reg), planet_reg);
    */
    g_hash_table_insert (planet_list, (gpointer)(gint)gwp_object_get_id(p), p);
  }

  // Now add the rest unknown planets
  for (i = 0; i < g_list_length (xyplanet_list); i++) {
    // Check if we have not this planet
    if (planet_get (planet_list, i + 1) == NULL) {
      coords = g_list_nth_data (xyplanet_list, i);
      planet_reg = g_malloc (sizeof (Planet));
      planet_reg->pdata = NULL;
      planet_reg->x = coords->x;
      planet_reg->y = coords->y;
      planet_reg->owner = 0;
      planet_reg->id = i + 1;
      strcpy (planet_reg->name, (gchar *) g_list_nth_data (pnames, i));
      
      // Add planet to list
      g_hash_table_insert (planet_list, (gpointer)(i + 1), planet_reg);
    }
  }
  fclose (pdata);
  
  return planet_list;
}

// X, Y coords in world coord system...
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
  GHashTable *base_list = NULL;
  struct stat dis_data;
  struct stat dat_data;
  gint16 bases_nr;
  gint i;
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
    /* Read Base data from file */
    fread(buffer, 156, 1, bdata);

    /* Load Base data on struct */
    base = base_new();
    base->bdata->id = getWord(buffer);
    base->bdata->owner = getWord(buffer + 2);
    base->bdata->defense = getWord(buffer + 4);
    base->bdata->damage = getWord(buffer + 6);

    base->bdata->engines_tech = getWord(buffer + 8);
    base->bdata->hulls_tech = getWord(buffer + 10);
    base->bdata->beams_tech = getWord(buffer + 12);
    base->bdata->torps_tech = getWord(buffer + 14);

    base->bdata->storage_engines[0] = getWord(buffer + 16);
    base->bdata->storage_engines[1] = getWord(buffer + 18);
    base->bdata->storage_engines[2] = getWord(buffer + 20);
    base->bdata->storage_engines[3] = getWord(buffer + 22);
    base->bdata->storage_engines[4] = getWord(buffer + 24);
    base->bdata->storage_engines[5] = getWord(buffer + 26);
    base->bdata->storage_engines[6] = getWord(buffer + 28);
    base->bdata->storage_engines[7] = getWord(buffer + 30);
    base->bdata->storage_engines[8] = getWord(buffer + 32);

    base->bdata->storage_hulls[0] = getWord(buffer + 34);
    base->bdata->storage_hulls[1] = getWord(buffer + 36);
    base->bdata->storage_hulls[2] = getWord(buffer + 38);
    base->bdata->storage_hulls[3] = getWord(buffer + 40);
    base->bdata->storage_hulls[4] = getWord(buffer + 42);
    base->bdata->storage_hulls[5] = getWord(buffer + 44);
    base->bdata->storage_hulls[6] = getWord(buffer + 46);
    base->bdata->storage_hulls[7] = getWord(buffer + 48);
    base->bdata->storage_hulls[8] = getWord(buffer + 50);
    base->bdata->storage_hulls[9] = getWord(buffer + 52);
    base->bdata->storage_hulls[10] = getWord(buffer + 54);
    base->bdata->storage_hulls[11] = getWord(buffer + 56);
    base->bdata->storage_hulls[12] = getWord(buffer + 58);
    base->bdata->storage_hulls[13] = getWord(buffer + 60);
    base->bdata->storage_hulls[14] = getWord(buffer + 62);
    base->bdata->storage_hulls[15] = getWord(buffer + 64);
    base->bdata->storage_hulls[16] = getWord(buffer + 66);
    base->bdata->storage_hulls[17] = getWord(buffer + 68);
    base->bdata->storage_hulls[18] = getWord(buffer + 70);
    base->bdata->storage_hulls[19] = getWord(buffer + 72);

    base->bdata->storage_beams[0] = getWord(buffer + 74);
    base->bdata->storage_beams[1] = getWord(buffer + 76);
    base->bdata->storage_beams[2] = getWord(buffer + 78);
    base->bdata->storage_beams[3] = getWord(buffer + 80);
    base->bdata->storage_beams[4] = getWord(buffer + 82);
    base->bdata->storage_beams[5] = getWord(buffer + 84);
    base->bdata->storage_beams[6] = getWord(buffer + 86);
    base->bdata->storage_beams[7] = getWord(buffer + 88);
    base->bdata->storage_beams[8] = getWord(buffer + 90);
    base->bdata->storage_beams[9] = getWord(buffer + 92);

    base->bdata->storage_torp_launchers[0] = getWord(buffer + 94);
    base->bdata->storage_torp_launchers[1] = getWord(buffer + 96);
    base->bdata->storage_torp_launchers[2] = getWord(buffer + 98);
    base->bdata->storage_torp_launchers[3] = getWord(buffer + 100);
    base->bdata->storage_torp_launchers[4] = getWord(buffer + 102);
    base->bdata->storage_torp_launchers[5] = getWord(buffer + 104);
    base->bdata->storage_torp_launchers[6] = getWord(buffer + 106);
    base->bdata->storage_torp_launchers[7] = getWord(buffer + 108);
    base->bdata->storage_torp_launchers[8] = getWord(buffer + 110);
    base->bdata->storage_torp_launchers[9] = getWord(buffer + 112);

    base->bdata->storage_torps[0] = getWord(buffer + 114);
    base->bdata->storage_torps[1] = getWord(buffer + 116);
    base->bdata->storage_torps[2] = getWord(buffer + 118);
    base->bdata->storage_torps[3] = getWord(buffer + 120);
    base->bdata->storage_torps[4] = getWord(buffer + 122);
    base->bdata->storage_torps[5] = getWord(buffer + 124);
    base->bdata->storage_torps[6] = getWord(buffer + 126);
    base->bdata->storage_torps[7] = getWord(buffer + 128);
    base->bdata->storage_torps[8] = getWord(buffer + 130);
    base->bdata->storage_torps[9] = getWord(buffer + 132);

    base->bdata->fighters = getWord(buffer + 134);
    base->bdata->id_ship = getWord(buffer + 136);
    base->bdata->ship_action = getWord(buffer + 138);
    base->bdata->mission = getWord(buffer + 140);

    base->bdata->build_ship_type = getWord(buffer + 142);
    base->bdata->build_engine_type = getWord(buffer + 144);
    base->bdata->build_beam_type = getWord(buffer + 146);
    base->bdata->build_beam_count = getWord(buffer + 148);
    base->bdata->build_torp_type = getWord(buffer + 150);
    base->bdata->build_torp_count = getWord(buffer + 152);

    /* This should always be zero */
    base->bdata->fighter_count = 0;

    /* Add base to list */
    g_hash_table_insert(base_list, (gpointer)(gint)base_get_id(base), base);
  }
  fclose(bdata);

  return base_list;
}
