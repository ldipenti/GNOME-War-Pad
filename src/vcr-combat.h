#ifndef VCR_COMBAT_H
#define VCR_COMBAT_H

#include <gnome.h>


/* global fight parameters */
#define SPEED_SHIPS             100
#define MAX_DISTANCE_SHIPS    58000
#define MAX_DISTANCE_PLANET   54000
#define MIN_DISTANCE_SHIPS     3000

/* ship/planet parameters */
#define MAX_NUMBER_TUBES         10
#define MAX_NUMBER_BAYS          50
#define MAX_NUMBER_BEAMS         10
#define MAX_NUMBER_FIGHTERS      19

/* beam weapon parameters */
#define CHANCE_BEAM_FILL_PER_M   50
#define AMOUNT_BEAM_FILL_PER_M    1
#define CHANCE_BEAM_FIRE_FIGHTER 20
#define CHANCE_BEAM_FIRE_SHIP    30
#define CHANCE_BEAM_HIT_FIGHTER 100
#define CHANCE_BEAM_HIT_SHIP    100
#define MIN_FILL_BEAM_FIGHTER    40
#define MIN_FILL_BEAM_SHIP       50
#define RANGE_BEAM_SHIP       20000
#define RANGE_BEAM_FIGHTER    20000
#define CHANCE_BEAM_HIT_SHIP_INSTEAD 0.5

/* torpedo weapon parameters */
#define RANGE_TORP_SHIP       30000
#define CHANCE_TORP_HIT_SHIP     34

/* fighter weapons parameters */
#define SPEED_FIGHTER           400
#define RANGE_FIGHTER_SHIP        0 // TODO
#define RANGE_FIGHTER_FIGHTER     0 // TODO

typedef struct {
  gint position;
  gint direction;
  gint speed;
  gint shield;
  gint hull;
  gint crew;
} platform;

typedef struct {
  gint fill;
  gint shield;
  gint hull;
  gint crew;
} beamweapon;
typedef struct {
  gint number;
  beamweapon beam[MAX_NUMBER_BEAMS];
} beamarray;

typedef struct {
  gint reload;
  gint ready;
  gint shield;
  gint hull;
  gint crew;
} torpedotube;
typedef struct {
  gint number;
  torpedotube tube[MAX_NUMBER_TUBES];
} tubearray;

typedef struct {
  gint reload;
  gint fill;
} fighterbay;
typedef struct {
  gint number;
  fighterbay bay[MAX_NUMBER_BAYS];
} bayarray;

typedef struct {
  gint position;
  gint direction;
  gint speed;
} fighter;
typedef struct {
  gint number;
  gint fighter[MAX_NUMBER_FIGHTERS];
} fighterarray;

typedef struct {
  gint g_shibon;        // percentage of shield-engine-bonus
  gint g_a_is_ship;     // side a of the combat sends a ship
  gint g_b_is_ship;     // side b of the combat sends a ship
  gint a_shield;        // 0: shields gone, 100: without scratch
  gint a_hull;          // 0: destroyed, 100: without scratch
  gint a_crew;          // number of crew members left
  gint a_typ_hull;      // type of the hull (ignored if planet)
  gint a_nmb_fighter;   // number of fighters on board
  gint a_nmb_bays;      // number of fighter-bays
  gint a_nmb_torps;     // number of torpedos
  gint a_nmb_tubes;     // number of torpedo tubes
  gint a_typ_torps;     // type of torpedos
  gint a_nmb_beams;     // number of beams installed
  gint a_typ_beams;     // type of beams
  gint b_shield;        // 0: shields gone, 100: without scratch
  gint b_hull;          // 0: destroyed, 100: without scratch
  gint b_crew;          // number of crew members left
  gint b_typ_hull;      // type of the hull (ignored if planet)
  gint b_nmb_fighter;   // number of fighters on board
  gint b_nmb_bays;      // number of fighter-bays
  gint b_nmb_torps;     // number of torpedos
  gint b_nmb_tubes;     // number of torpedo tubes
  gint b_typ_torps;     // type of torpedos
  gint b_nmb_beams;     // number of beams installed
  gint b_typ_beams;     // type of beams
  gint p_has_base;      // 0: no starbase, 1: with starbase
  gint p_typ_beams;     // level of beams on starbase
  gint p_nmb_pdefense;  // number of defense on planet
  gint p_nmb_bdefense;  // number of defense on base
  gint p_nmb_fighter;   // number of fighters on starbase
} combatdata;

/* public function to start combat */
void vcrc_start( combatdata *cdata );
/* private functions */
void vcrc_print_combatants( combatdata *cdata );
void vcrc_prepare_fighters( combatdata *cdata );
void vcrc_prepare_torpedos( combatdata *cdata );
void vcrc_prepare_beams( combatdata *cdata );
void vcrc_fight( combatdata *cdata );



GtkTextBuffer *vcr_logging_textview_buffer;
void vcr_log_str( gchar *str );
void vcr_log_strn( gchar *str, gint len );
void vcr_log_int( gint val );
void vcr_log_intn( gint val, gint len );
#endif











