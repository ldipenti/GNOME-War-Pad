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

/*  VGA Planets Data Types */

#ifndef VP_TYPES_H
#define VP_TYPES_H

#include <gnome.h>

/*
 * Structures
 */
typedef struct _VpXYPlanReg VpXYPlanReg;
struct _VpXYPlanReg {
	gint16 x, y;
	gint16 owner;
};

typedef struct _VpTargetReg VpTargetReg;
struct _VpTargetReg {
	gint16 id;
	gint16 owner;
	gint16 warp_factor;
	gint16 x, y;
	gint16 hull_type;
	gint16 heading;
	gchar name[21];
};

typedef struct _VpShipXYReg VpShipXYReg;
struct _VpShipXYReg {
	gint16 x, y;
	gint16 owner;
	gint16 mass;	// Mass in kt
};

typedef struct _VpShipReg VpShipReg;
struct _VpShipReg {
	gint16 id;
	gint16 owner;
	guchar fcode[3];
	
	// Sometimes this is set to a negative value by the host.
	gint16 warp_factor;	// range 0..9
	
	gint16 x_to_waypoint, y_to_waypoint;	// range -3000..3000
	gint16 x_position, y_position;
	
	gint16 engine_type;		// range 1..9
	gint16 hull_type;		// range 1..105
	gint16 beams_type;		// range 1..10 (0 = none)
	gint16 beams;			// Number of beam weapons
	gint16 fighter_bays;		// Number of fighter bays
	gint16 torpedoes_type;		// range 1..10 (0 = none)
	gint16 torpedoes_fighters;	// Number of torpedoes/fighters
	gint16 torpedoes_launchers;	// Number of torps launchers
	
	gint16 mission;
	gint16 primary_enemy;
	
	// Ship to tow (or first mission argument)
	gint16 tow_mission_ship_id;
	
	gint16 damage;			// % - range 1..149
	gint16 crew;
	gint16 colonists;		// Clans (100 people each)
	gchar name[21];		// Ship Name
	
	gint16 neutronium, tritanium, duranium, molybdenum, supplies;
	
	// Unload cargo to planet
	gint16 unload_neutronium, unload_tritanium, unload_duranium;
	gint16 unload_molybdenum, unload_colonists, unload_supplies;
	gint16 unload_planet_id;	// 0 = Jettison
	
	// Transfer to enemy ship
	gint16 transfer_neutronium, transfer_tritanium, transfer_duranium;
	gint16 transfer_molybdenum, transfer_colonists, transfer_supplies;
	gint16 transfer_ship_id;
	
	// Intercept Mission arg (or second mission arg)
	gint16 intercept_mission_ship_id;	// Valid ship ID or zero.
	
	gint16 megacredits;	// range 1..10000
};

typedef struct _VpPlanetReg VpPlanetReg;
struct _VpPlanetReg {
	gint16 owner;	// 0 for unowned planets
	gint16 id;
	guchar fcode[3];
	
	gint16 mines;
	gint16 factories;
	gint16 defense_posts;
	
	/* Mined Minerals */
	gint32 mined_neutronium;
	gint32 mined_tritanium;
	gint32 mined_duranium;
	gint32 mined_molybdenum;
	
	gint32 colonists;	// Clans (100 people each)

	gint32 supplies;
	gint32 megacredits;
	
	/* Minerals in ground:
	   ------------------
		> 4999			abundant
		1200..4999		very common
		600..1199		common
		100..599			rare
		1..99				very rare
		0					none	*/
	gint32 ground_neutronium;
	gint32 ground_tritanium;
	gint32 ground_duranium;
	gint32 ground_molybdenum;
	
	/* Minerals density:
	   ----------------
	   70..100	large masses		1 mine extracts 1 kt
	   40..69	concentrated		2 mines extract 1 kt
	   30..39	dispersed			3 mines extract 1 kt
	   10..29	scattered			5 mines extract 1 kt
	   0..9		very scattered	10 mines extract 1 kt */
	gint16 dens_neutronium;
	gint16 dens_tritanium;
	gint16 dens_duranium;
	gint16 dens_molybdenum;
	
	gint16 tax_colonists;	// 0..100
	gint16 tax_natives;	// 0..100
	
	/* Happiness:
	   ---------
	   90..100		happy
	   70..89		calm
	   50..69		unhappy
		40..49		very angry
		20..39		rioting
		<20			fighting
		Tax collection possible for happiness >=40
		Population grows if >=70 */
	gint16 happiness_colonists;	// -300..100
	gint16 happiness_natives;	// -300..100
	
	/* Native Government: (SPI = Socio Political Index)
	   -----------------
	   0		none						  0%
	   1		Anarchy					 20%
	   2		Pre-Tribal				 40%
	   3		Early-Tribal			 60%
	   4		Tribal					 80%
	   5		Feudal					100%
	   6		Monarchy					120%
	   7		Representative		140%
	   8		Participatory			160%
	   9		Unity						180%	*/
	gint16 native_spi;
	gint32 natives;	// Clans (100 people each)
	
	/* Native Race:
	   -----------
	   0	none
	   1	Humanoid
	   2	Bovinoid
	   3	Reptilian
	   4	Avian
	   5	Amorphous
	   6	Insectoid
	   7	Amphibian
	   8	Ghipsoldal
	   9	Siliconoid	*/
	gint16 native_race;
	
	/* Planet Temperature: (T in Fahrenheit = 100 - this value)
	   ------------------
	   0..15			desert		(85..100 F)
	   16..35		tropical		(65..84 F)
	   36..60		warm			(40..64 F)
	   61..85		cool			(15..39 F)
	   86..100		arctic		(0..14 F)	*/
	gint16 temperature;
	
	gint16 build_base;		// 1 = true, 0 otherwise
};

typedef struct _VpStarbaseReg VpStarbaseReg;
struct _VpStarbaseReg {
	gint16 id;
	gint16 owner;
	gint16 defense, damage;
	gint16 engines_tech, hulls_tech, weapons_tech, torpedoes_tech;
	
	gint16 storage_engines[9], storage_hulls[20];
	gint16 storage_weapons[10], storage_torpedoes_launchers[10];
	gint16 storage_torpedoes[10];
	
	gint16 fighters;
	
	gint16 id_ship;
	gint16 ship_action; /*	0 - Nothing
							1 - Fix
							2 - Recycle */
	
	gint16 mission; /*	1 - Refuel
						2 - Max Defense
						3 - Load torps onto ships
						4 - Unload freighters
						5 - Repair base
						6 - Force a surrender */
	
	/* -- Spaceship Build -- */
	gint16 build_ship_type;
	gint16 build_engine_type;
	gint16 build_beam_type, build_beam_count;
	gint16 build_torp_type, build_torp_count;
	
	/* Fighter count (?) this should always be zero */
	gint16 fighter_count;
};


/*
 * High-level data types
 */
typedef struct _Planet Planet;
struct _Planet {
	gint16 x, y;		// Planet coordinates (VP Starchart coords)
	gint16 owner;
	gint16 id;
	VpPlanetReg *pdata;	// PDATA
	gchar name[21];
};

typedef struct _Ship Ship;
struct _Ship {
	gint16 x,y;
	gint16 owner;
	gint fleet_num; // Fleet number that ship is assigned to. 0 if none.
	VpShipReg *sdata;
	VpTargetReg *tdata;
};

#endif
