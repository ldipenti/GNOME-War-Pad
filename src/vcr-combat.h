#ifndef VCR_COMBAT_H
#define VCR_COMBAT_H

#include <gnome.h>
#include <glib.h>
#include <math.h>
#include <sys/time.h>
#include <stdio.h>

/* global defines */
#define VCRC_SIDE_A                         1
#define VCRC_SIDE_B                         2
#define VCRC_DIRECTION_A                    1
#define VCRC_DIRECTION_B                   -1

/* global fight parameters */
#define VCRC_SPEED_SHIPS                  100
#define VCRC_SPEED_PLANET                   0
#define VCRC_MAX_DISTANCE_SHIPS         58000
#define VCRC_MAX_DISTANCE_PLANET        54000
#define VCRC_MIN_DISTANCE_SHIPS          3000
#define VCRC_COMBAT_TIMEOUT              2000

/* ship/planet parameters */
#define VCRC_MAX_NUMBER_TUBES              10
#define VCRC_MAX_NUMBER_BAYS               13   // 10 + Fed Crew Bonus of 3
#define VCRC_MAX_NUMBER_BEAMS              10
#define VCRC_MAX_ABOARD_FIGHTERS          500
#define VCRC_MAX_LAUNCHED_FIGHTERS         19

/* beam weapon parameters */
#define VCRC_CHANCE_BEAM_FILL_PER_M        50
#define VCRC_AMOUNT_BEAM_FILL_PER_M         1
#define VCRC_CHANCE_BEAM_FIRE_FIGHTER      20
#define VCRC_CHANCE_BEAM_FIRE_SHIP         30
#define VCRC_CHANCE_BEAM_HIT_FIGHTER      100
#define VCRC_CHANCE_BEAM_HIT_SHIP         100
#define VCRC_MIN_FILL_BEAM_FIGHTER         40
#define VCRC_MIN_FILL_BEAM_SHIP            50
#define VCRC_RANGE_BEAM_SHIP            20000
#define VCRC_RANGE_BEAM_FIGHTER         58000   // TODO ... logic?
#define VCRC_CHANCE_BEAM_HIT_SHIP_INSTEAD 0.5

/* torpedo weapon parameters */
#define VCRC_RANGE_TORP_SHIP            30000
#define VCRC_CHANCE_TORP_HIT_SHIP          66

/* fighter weapons parameters */
#define VCRC_SPEED_FIGHTER                400
#define VCRC_RANGE_FIGHTER_SHIP          3500 // TODO Guessed
#define VCRC_RANGE_FIGHTER_FIGHTER          0 // TODO 99% sure
#define VCRC_CHANCE_LAUNCH                  5 // TODO (unsure about this value)
#define VCRC_CHANCE_FIGHTER_HIT_FIGHTER    50
#define VCRC_CHANGE_FIGHTER_HIT_PLATFORM  100 // TODO (unsure)

typedef struct {
  gint fill;
  gint type;
} beamweapon;
typedef struct {
  gint number;
  beamweapon beam[VCRC_MAX_NUMBER_BEAMS];
} beamarray;

typedef struct {
  gint load;
  gint full;
  gint shield;
  gint hull;
  gint crew;
} torpedotube;
typedef struct {
  gint number;
  torpedotube tube[VCRC_MAX_NUMBER_TUBES];
} tubearray;

typedef struct {
  gint reload;
  gint fill;
} fighterbay;
typedef struct {
  gint number;
  fighterbay bay[VCRC_MAX_NUMBER_BAYS];
} bayarray;

typedef struct {
  gboolean launched;
  gint position;
  gint direction;
  gint speed;
  gint shield;  /* damage inflicted on opponents shield */
  gint hull;    /* damage inflicted on opponents hull */
  gint crew;    /* damage inflicted on opponents crew */
} fightertype;
typedef struct {
  gint number;
  gint flying;
  fightertype fighter[VCRC_MAX_ABOARD_FIGHTERS];
} fighterarray;

typedef struct {
  gint position;
  gint direction;
  gint speed;
  gint shield;
  gint hull;
  gint crew;
  gint mass;
  fighterarray fighters;
  bayarray bays;
  gint torps;
  tubearray tubes;
  beamarray beams;
} platform;

typedef struct {
  platform a;
  platform b;
  gint time;
  gboolean fighton;
  gint shieldbonus;
} battlefield;

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
  gint a_typ_engines;   // type of the engines
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
  gint b_typ_engines;   // type of the engines
  gint p_has_base;      // 0: no starbase, 1: with starbase
  gint p_typ_beams;     // level of beams on starbase
  gint p_nmb_pdefense;  // number of defense on planet
  gint p_nmb_bdefense;  // number of defense on base
  gint p_nmb_fighter;   // number of fighters on starbase
} combatdata;

/* public function to start combat */
void vcrc_combat_start( combatdata *cdata );

/* private functions */
void vcrc_initilize_graphs( battlefield *battle );

void vcrc_prepare_for_battle( combatdata *cdata, battlefield *battle );
void vcrc_prepare_battlefield( combatdata *cdata, battlefield *battle );
void vcrc_prepare_platforms( combatdata *cdata, battlefield *battle );
void vcrc_prepare_fighters( combatdata *cdata, battlefield *battle );
void vcrc_prepare_torpedos( combatdata *cdata, battlefield *battle );
void vcrc_prepare_beams( combatdata *cdata, battlefield *battle );

void vcrc_fight( battlefield *battle );
void vcrc_fight_reload_weapons( battlefield *battle );
void vcrc_fight_move_platforms( battlefield *battle );
void vcrc_fight_move_fighters( battlefield *battle, gint side );
void vcrc_fight_launch_fighters( battlefield *battle );
void vcrc_fight_attack_fighters( battlefield *battle, gint side );
void vcrc_fight_attack_torpedos( battlefield *battle );
void vcrc_fight_attack_beams( battlefield *battle );
void vcrc_fight_destroy_fighter( battlefield *battle, gint side, gint id );
void vcrc_fight_hit( battlefield *battle, gint side, gint sdam, gint hdam, gint cdam );

gint vcrc_get_reload_time_for_torp( gint type );
gint vcrc_get_shield_damage_for_torp( gint type, gint mass );
gint vcrc_get_hull_damage_for_torp( gint type, gint mass );
gint vcrc_get_crew_damage_for_torp( gint type, gint mass );
gint vcrc_get_shield_damage_for_beam( gint type, gint fill, gint mass );
gint vcrc_get_hull_damage_for_beam( gint type, gint fill, gint mass );
gint vcrc_get_crew_damage_for_beam( gint type, gint fill, gint mass );
gint vcrc_get_shield_damage_for_fighter( gint mass );
gint vcrc_get_hull_damage_for_fighter( gint mass );
gint vcrc_get_crew_damage_for_fighter( gint mass );
gint vcrc_get_engine_price( gint type );
gint vcrc_get_planets_battlemass( combatdata *cdata );
gint vcrc_get_ships_battlemass( combatdata *cdata, gint side );

void vcrc_print_summary( battlefield *battle, combatdata *cdata );
GtkTextBuffer *vcr_logging_textview_buffer;
void init_log( void );
void vcrc_print_combatants( combatdata *cdata );
void vcrc_log_str( gchar *str );
void vcrc_log_strn( gchar *str, gint len );
void vcrc_log_int( gint val );
void vcrc_log_intn( gint val, gint len );
gboolean vcrc_rand( gint n );
#endif











