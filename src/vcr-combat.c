#include "vcr-combat.h"
#include "vcr.h"
#include "support.h"

/* TODO */
#define FED_CREW_BONUS 0



/*
 *  this is the MAIN PUBLIC function.
 *  it receives the combatdata struct with all necessary pre-fight
 *  informations and calls all appropriate subfunctions to calculate
 *  and simulate the battle
 */
void vcrc_combat_start( combatdata *cdata )
{
  /* switch to combat view */
  gtk_notebook_set_current_page( GTK_NOTEBOOK( lookup_widget( "vcr_notebook_main" ) ), 1 );
  /* initialize the logging */
  init_log();

  /* the combat will take place in this central structure */
  battlefield battle;

  vcrc_prepare_for_battle( cdata, &battle );

  vcrc_print_combatants( cdata );

  /* try to initialize the open-gl simulation area */
  vcrcgl_init();

  /* Hey Ho ... Let's GO */
  vcrc_fight( &battle );
}



/*
 *  this function is supposed to prepare all combat related arrays
 *  and to initialize all combat values
 */
void vcrc_prepare_for_battle( combatdata *cdata, battlefield *battle )
{
  vcrc_log_str( "Preparing for Battle ...\n" );

  /* start the random generation TODO (i know, i know)*/
  srandom( 47110815 );

  /* initialize the battlefield */
  battle->time = 0;

  vcrc_prepare_platforms( cdata, battle );
  vcrc_prepare_fighters( cdata, battle );
  vcrc_prepare_torpedos( cdata, battle );
  vcrc_prepare_beams( cdata, battle );
}



/*
 *  a 'platform' is either a fighting main-ship or a planet
 *  this function is supposed to prepare both battle sides
 */
void vcrc_prepare_platforms( combatdata *cdata, battlefield *battle )
{
  vcrc_log_str( "Preparing Platforms ............ " );

  if( cdata->g_a_is_ship == 1 )
  {
    battle->a.position    = 0;                // starting from the 'left'
    battle->a.direction   = 1;                // moving 'right'
    battle->a.speed       = VCRC_SPEED_SHIPS; // 
    battle->a.shield      = cdata->a_shield;  //
    battle->a.hull        = cdata->a_hull;    //
    battle->a.crew        = cdata->a_crew;    //
    battle->a.mass        = vcrc_get_ships_battlemass( cdata, VCRC_SIDE_A );
  }
  else
  {
    vcrc_log_str( "\n###   WARNING: Side A has to be a Ship   ###\n" );
  }

  if( cdata->g_b_is_ship == 1 )
  {
    battle->b.position    = VCRC_MAX_DISTANCE_SHIPS; // starting from the 'right'
    battle->b.direction   = -1;                      // moving 'left'
    battle->b.speed       = VCRC_SPEED_SHIPS;        // 
    battle->b.shield      = cdata->b_shield;         //
    battle->b.hull        = cdata->b_hull;           //
    battle->b.crew        = cdata->b_crew;           //
    battle->b.mass        = 200;                     // TODO
  }
  else
  {
    battle->b.position    = VCRC_MAX_DISTANCE_PLANET; // starting from the 'right'
    battle->b.direction   = -1;                       // moving 'left'
    battle->b.speed       = 0;                        // 
    battle->b.shield      = 100;                      // TODO: not sure if 2nd fight
    battle->b.hull        = 100;                      // TODO: not sure if 2nd fight
    battle->b.crew        = 100;                      // TODO: no idea
    battle->b.mass        = vcrc_get_planets_battlemass( cdata );
  }
  vcrc_log_str( "OK\n" );
}



/*
 *  fighters are the small vessels launched by fighter-bays
 */
void vcrc_prepare_fighters( combatdata *cdata, battlefield *battle )
{
  gint i;
  vcrc_log_str( "Preparing Fighters and Bays .... " );

  /* combatant A */
  battle->a.fighters.flying = 0;
  if( cdata->a_nmb_bays > 0 )
  {
    /* fighters */
    battle->a.fighters.number = cdata->a_nmb_fighter;
    for( i=0; i<cdata->a_nmb_fighter; i++ )
    {
      battle->a.fighters.fighter[i].launched = FALSE;
      battle->a.fighters.fighter[i].position = 0;
      battle->a.fighters.fighter[i].direction = 0;
      battle->a.fighters.fighter[i].speed = 0;
    }
    /* bays */
    battle->a.bays.number = cdata->a_nmb_bays;
    for( i=0; i<cdata->a_nmb_bays; i++ )
    {
      battle->a.bays.bay[i].reload = 0; // TODO ... unused
      battle->a.bays.bay[i].fill   = 0; // TODO ... unused
    }
  }

  /* combatant B */
  battle->b.fighters.flying = 0;
  if( cdata->g_b_is_ship == 1 )
  {
    /* SHIP */
    battle->b.fighters.number = cdata->b_nmb_fighter;
    battle->b.bays.number = cdata->b_nmb_bays;
  }
  else
  {
    /* PLANET */
    battle->b.fighters.number = round( sqrt( cdata->p_nmb_pdefense - 0.75 ) );
    battle->b.bays.number = (gint)( sqrt( cdata->p_nmb_pdefense ) );
    if( cdata->p_has_base == 1 )
    {
      /* STARBASE */
      battle->b.fighters.number += cdata->p_nmb_fighter;
      battle->b.bays.number += 5;
    }
  }

  if( cdata->a_nmb_bays > 0 )
  {
    /* fighters */
    for( i=0; i<battle->b.fighters.number; i++ )
    {
      battle->b.fighters.fighter[i].launched = FALSE;
      battle->b.fighters.fighter[i].position = 0;
      battle->b.fighters.fighter[i].direction = 0;
      battle->b.fighters.fighter[i].speed = 0;
    }
    /* bays */
    for( i=0; i<battle->b.bays.number; i++ )
    {
      battle->b.bays.bay[i].reload = 0; // TODO ... unused
      battle->b.bays.bay[i].fill   = 0; // TODO ... unused
    }
  }

  vcrc_log_str( "OK\n" );
}



/*
 *  torpedos are the weapons deployed by torpedo-tubes
 */
void vcrc_prepare_torpedos( combatdata *cdata, battlefield *battle )
{
  gint i;
  vcrc_log_str( "Preparing Torpedos and Tubes ... " );

  /* combatant A */
  battle->a.tubes.number = cdata->a_nmb_tubes;
  for( i=0; i<cdata->a_nmb_tubes; i++ )
  {
    battle->a.tubes.tube[i].reload = vcrc_get_reload_time_for_torp(   cdata->a_typ_torps );
    battle->a.tubes.tube[i].fill   = vcrc_get_reload_time_for_torp(   cdata->a_typ_torps );
    battle->a.tubes.tube[i].shield = vcrc_get_shield_damage_for_torp( cdata->a_typ_torps );
    battle->a.tubes.tube[i].hull   = vcrc_get_hull_damage_for_torp(   cdata->a_typ_torps );
    battle->a.tubes.tube[i].crew   = vcrc_get_crew_damage_for_torp(   cdata->a_typ_torps );
  }

  /* combatant B */
  battle->b.tubes.number = cdata->b_nmb_tubes;
  for( i=0; i<cdata->b_nmb_tubes; i++ )
  {
    battle->b.tubes.tube[i].reload = vcrc_get_reload_time_for_torp(   cdata->b_typ_torps );
    battle->b.tubes.tube[i].fill   = vcrc_get_reload_time_for_torp(   cdata->b_typ_torps );
    battle->b.tubes.tube[i].shield = vcrc_get_shield_damage_for_torp( cdata->b_typ_torps );
    battle->b.tubes.tube[i].hull   = vcrc_get_hull_damage_for_torp(   cdata->b_typ_torps );
    battle->b.tubes.tube[i].crew   = vcrc_get_crew_damage_for_torp(   cdata->b_typ_torps );
  }

  vcrc_log_str( "OK\n" );
}



/*
 *  a beam weapon is a laser like ... blah ... self-explaining :-)
 */
void vcrc_prepare_beams( combatdata *cdata, battlefield *battle )
{
  gint i;
  gint beamtype;
  vcrc_log_str( "Preparing all Beam Weapons ..... " );

  /* combatant A */
  battle->a.beams.number = cdata->a_nmb_beams;
  beamtype = cdata->a_typ_beams;
  for( i=0; i<cdata->a_nmb_beams; i++ )
  {
    if( cdata->a_shield == 100 )
      battle->a.beams.beam[i].fill = 100;
    else
      battle->a.beams.beam[i].fill = 0;
    battle->a.beams.beam[i].shield = vcrc_get_shield_damage_for_beam( beamtype );
    battle->a.beams.beam[i].hull   = vcrc_get_hull_damage_for_beam(   beamtype );
    battle->a.beams.beam[i].crew   = vcrc_get_crew_damage_for_beam(   beamtype );
  }

  /* combatant B */
  if( cdata->g_b_is_ship == 1 )
  {
    /* SHIP */
    battle->b.beams.number = cdata->b_nmb_beams;
    beamtype = cdata->a_typ_beams;
  }
  else
  {
    if( cdata->p_has_base == 1 )
    {
      /* with starbase */
      battle->b.beams.number = round( sqrt( ( cdata->p_nmb_pdefense + cdata->p_nmb_bdefense ) / 3.0 ) );
      beamtype = round( sqrt( cdata->p_nmb_pdefense * 0.5 ) );
      if( cdata->b_typ_beams > beamtype )
        beamtype = cdata->b_typ_beams;
    }
    else
    {
      /* without starbase */
      battle->b.beams.number = round( sqrt( ( cdata->p_nmb_pdefense ) / 3.0 ) );
      beamtype = round( sqrt( cdata->p_nmb_pdefense * 0.5 ) );
    }
  }

  for( i=0; i<battle->b.beams.number; i++ )
  {
    if( cdata->b_shield == 100 )
      battle->b.beams.beam[i].fill = 100;
    else
      battle->b.beams.beam[i].fill = 0;
    battle->b.beams.beam[i].shield = vcrc_get_shield_damage_for_beam( beamtype );
    battle->b.beams.beam[i].hull   = vcrc_get_hull_damage_for_beam(   beamtype );
    battle->b.beams.beam[i].crew   = vcrc_get_crew_damage_for_beam(   beamtype );
  }

  vcrc_log_str( "OK\n" );
}



/*
 *  this is the MAIN PRIVATE function
 *  it should be called after all preparations are finished
 *  and is supposed to do the actual battle simulation
 */
void vcrc_fight( battlefield *battle )
{
  g_message( "THE FUN BEGINS" );

  while( battle->time <= VCRC_COMBAT_TIMEOUT
      && battle->a.hull > 0
      && battle->b.hull > 0 )
  {
    vcrc_fight_move_platforms( battle );
    vcrc_fight_launch_fighters( battle );
    vcrc_fight_move_fighters( battle );
    vcrc_fight_attack_fighters( battle );
    vcrc_fight_attack_torpedos( battle );
    vcrc_fight_attack_beams( battle );
    battle->time++;
  }
}
void vcrc_fight_move_platforms( battlefield *battle )
{
//g_print( "VCR-DEBUG: time %4d, moving A from %6d", battle->time, battle->a.position );
  /* move side A */
  battle->a.position += battle->a.direction * battle->a.speed;
  if( battle->b.position - battle->a.position < VCRC_MIN_DISTANCE_SHIPS )
    battle->a.position = battle->b.position - VCRC_MIN_DISTANCE_SHIPS;
//g_print( " to %6d\n", battle->a.position );

//g_print( "VCR-DEBUG: time %4d, moving B from %6d", battle->time, battle->b.position );
  /* move side B */
  battle->b.position += battle->b.direction * battle->b.speed;
  if( battle->b.position - battle->a.position < VCRC_MIN_DISTANCE_SHIPS )
    battle->b.position = battle->a.position + VCRC_MIN_DISTANCE_SHIPS;
//g_print( " to %6d\n", battle->b.position );
}



void vcrc_fight_move_fighters( battlefield *battle )
{
  gint i;

  /* SIDE A */
  for( i=0; i<battle->a.fighters.number; i++ )
  {
    if( battle->a.fighters.fighter[i].launched )
    {
//g_print( "VCR-DEBUG: fighter %d moving from %d", i, battle->a.fighters.fighter[i].position );
      /* move this fighter */
      battle->a.fighters.fighter[i].position += battle->a.fighters.fighter[i].direction
                                              * battle->a.fighters.fighter[i].speed;
//g_print( " to %d\n", battle->a.fighters.fighter[i].position );

      /* check if fighter has reached enemy platform and turns around */
      if( battle->a.fighters.fighter[i].position > battle->b.position )
      {
//g_print( "VCR-DEBUG: fighter %d - turning\n", i );
        battle->a.fighters.fighter[i].position = battle->b.position;
        battle->a.fighters.fighter[i].direction *= ( -1 );
      }

      /* check if fighter has returned to carrier */
      if( battle->a.fighters.fighter[i].position <= battle->a.position &&
          battle->a.fighters.fighter[i].direction * battle->a.direction < 0 )
      {
//g_print( "VCR-DEBUG: fighter %d - landing\n", i );
        battle->a.fighters.fighter[i].launched = FALSE;
        battle->a.fighters.flying--;
      }
    }
  }

  /* SIDE B */
  for( i=0; i<battle->b.fighters.number; i++ )
  {
    if( battle->b.fighters.fighter[i].launched )
    {
      /* move this fighter */
      battle->b.fighters.fighter[i].position += battle->b.fighters.fighter[i].direction
                                              * battle->b.fighters.fighter[i].speed;

      /* check if fighter has reached enemy platform and turns around */
      if( battle->b.fighters.fighter[i].position < battle->a.position )
      {
        battle->b.fighters.fighter[i].position = battle->b.position;
        battle->b.fighters.fighter[i].direction *= ( -1 );
      }

      /* check if fighter has returned to carrier */
      if( battle->b.fighters.fighter[i].position >= battle->b.position &&
          battle->b.fighters.fighter[i].direction * battle->b.direction < 0 )
      {
        battle->b.fighters.fighter[i].launched = FALSE;
        battle->b.fighters.flying--;
      }
    }
  }
}



void vcrc_fight_launch_fighters( battlefield *battle )
{
  gint i, j;

  /* SIDE A */
  if( battle->a.fighters.number > battle->a.fighters.flying  && 
      battle->a.fighters.flying < VCRC_MAX_LAUNCHED_FIGHTERS )
    for( j=0; j<battle->a.bays.number; j++ )
    {
      if( vcrc_rand( VCRC_CHANCE_LAUNCH ) )
      {
        i = 0;
        while( battle->a.fighters.fighter[i].launched &&
               battle->a.fighters.number > i )
        {
          i++;
        }
        if( j >= battle->a.fighters.number ) return; // something went wrong
        /* launch this fighter */
//g_print( "VCR-DEBUG: fighter %d - launching at %d\n", i, battle->a.position );
        battle->a.fighters.fighter[i].launched  = TRUE;
        battle->a.fighters.fighter[i].position  = battle->a.position;
        battle->a.fighters.fighter[i].direction = 1;
        battle->a.fighters.fighter[i].speed     = VCRC_SPEED_FIGHTER;
        battle->a.fighters.flying++;
        /* break this loop, launch just one fighter at a time */
        j = battle->a.bays.number;
      }
    }

  /* SIDE B */
  if( battle->b.fighters.number > battle->b.fighters.flying  && 
      battle->b.fighters.flying < VCRC_MAX_LAUNCHED_FIGHTERS )
    for( i=0; i<battle->b.bays.number; i++ )
    {
      if( vcrc_rand( VCRC_CHANCE_LAUNCH ) )
      {
        j = 0;
        while( battle->b.fighters.fighter[j].launched &&
               battle->b.fighters.number > j )
        {
          j++;
        }
        if( j >= battle->b.fighters.number ) return; // something went wrong
        /* launch this fighter */
        battle->b.fighters.fighter[i].launched  = TRUE;
        battle->b.fighters.fighter[i].position  = battle->b.position;
        battle->b.fighters.fighter[i].direction = -1;
        battle->b.fighters.fighter[i].speed     = VCRC_SPEED_FIGHTER;
        battle->b.fighters.flying++;
        /* break this loop, launch just one fighter at a time */
        i = battle->b.bays.number;
      }
    }
}
void vcrc_fight_attack_fighters( battlefield *battle )
{
}
void vcrc_fight_attack_torpedos( battlefield *battle )
{
}
void vcrc_fight_attack_beams( battlefield *battle )
{
}
void vcrc_fight_destroy_fighter( battlefield *battle, gint side, gint id )
{
  gint n;
  switch( side )
  {
    case VCRC_SIDE_A:
      n = battle->a.fighters.number;
      battle->a.fighters.fighter[id].launched  = battle->a.fighters.fighter[n].launched ;
      battle->a.fighters.fighter[id].position  = battle->a.fighters.fighter[n].position ;
      battle->a.fighters.fighter[id].direction = battle->a.fighters.fighter[n].direction;
      battle->a.fighters.fighter[id].speed     = battle->a.fighters.fighter[n].speed    ;
      battle->a.fighters.number--;
      break;
    case VCRC_SIDE_B:
      n = battle->b.fighters.number;
      battle->b.fighters.fighter[id].launched  = battle->b.fighters.fighter[n].launched ;
      battle->b.fighters.fighter[id].position  = battle->b.fighters.fighter[n].position ;
      battle->b.fighters.fighter[id].direction = battle->b.fighters.fighter[n].direction;
      battle->b.fighters.fighter[id].speed     = battle->b.fighters.fighter[n].speed    ;
      battle->b.fighters.number--;
      break;
    default:
      return; // something went wrong
      break;
  }
}



/*
 *  returns the time (number of microns) a torpedo-tube of this
 *  type needs to be ready to fire again
 */
gint vcrc_get_reload_time_for_torp( gint type )
{
  switch( type )
  {
    case 1:  return 42;
    case 2:  return 39;
    case 3:  return 36;
    case 4:  return 34;
    case 5:  return 33;
    case 6:  return 33;
    case 7:  return 32;
    case 8:  return 32;
    case 9:  return 31;
    case 10: return 31;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      return 1000;
  }
}



/*
 *  returns the amount of damage a torpedo of this type
 *  inflicts on the opponents shield
 */
gint vcrc_get_shield_damage_for_torp( gint type )
{
  switch( type )
  {
    case 1:  return  5;
    case 2:  return  8;
    case 3:  return 10;
    case 4:  return  3;
    case 5:  return 14;
    case 6:  return 28;
    case 7:  return 32;
    case 8:  return 36;
    case 9:  return 43;
    case 10: return 50;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      return 1000;
  }
}



/*
 *  returns the amount of damage a torpedo of this type
 *  inflicts on the opponents hull structure
 */
gint vcrc_get_hull_damage_for_torp( gint type )
{
  switch( type )
  {
    case 1:  return  3;
    case 2:  return  5;
    case 3:  return  5;
    case 4:  return  2;
    case 5:  return  7;
    case 6:  return 13;
    case 7:  return 15;
    case 8:  return 17;
    case 9:  return 20;
    case 10: return 23;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      return 1000;
  }
}



/*
 *  returns the amount of damage a torpedo of this type
 *  inflicts on the opponents crew members
 */
gint vcrc_get_crew_damage_for_torp( gint type )
{
  switch( type )
  {
    case 1:  return  4;
    case 2:  return  5;
    case 3:  return  3;
    case 4:  return 13;
    case 5:  return  8;
    case 6:  return 11;
    case 7:  return 15;
    case 8:  return 20;
    case 9:  return 22;
    case 10: return 31;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      return 1000;
  }
}



/*
 *  returns the amount of damage a beamweapon of this type
 *  inflicts on the opponents shield
 */
gint vcrc_get_shield_damage_for_beam( gint type )
{
  switch( type )
  {
    case 1:  return  2;
    case 2:  return  1;
    case 3:  return  5;
    case 4:  return 12;
    case 5:  return 14;
    case 6:  return 10;
    case 7:  return 19;
    case 8:  return 16;
    case 9:  return 16;
    case 10: return 21;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      return 1000;
  }
}



/*
 *  returns the amount of damage a beamweapon of this type
 *  inflicts on the opponents hull structure
 */
gint vcrc_get_hull_damage_for_beam( gint type )
{
  switch( type )
  {
    case 1:  return  2;
    case 2:  return  1;
    case 3:  return  3;
    case 4:  return  6;
    case 5:  return  7;
    case 6:  return  5;
    case 7:  return  9;
    case 8:  return  8;
    case 9:  return  8;
    case 10: return 10;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      return 1000;
  }
}



/*
 *  returns the amount of damage a beamweapon of this type
 *  inflicts on the opponents crew members
 */
gint vcrc_get_crew_damage_for_beam( gint type )
{
  switch( type )
  {
    case 1:  return  4;
    case 2:  return  7;
    case 3:  return  1;
    case 4:  return  4;
    case 5:  return  4;
    case 6:  return 13;
    case 7:  return  9;
    case 8:  return 13;
    case 9:  return 22;
    case 10: return 15;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      return 1000;
  }
}



/*
 *  returns the price of one of those engines
 */
gint vcrc_get_engine_price( gint type )
{
  switch( type )
  {
    case 1:  return   1;
    case 2:  return   2;
    case 3:  return   3;
    case 4:  return  10;
    case 5:  return  25;
    case 6:  return  53;
    case 7:  return 170;
/*  case 8:  return 0;     There's no engine with this level */
    case 9:  return 200;
    case 10: return 300;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid engine type (%d)", type );
      return 0;
  }
}



/*
 *  computes the battlemass for the involved planet
 */
gint vcrc_get_planets_battlemass( combatdata *cdata )
{
  gint mass = 0;

  /* just compute if b is a planet (not a ship) */
  if( !cdata->g_b_is_ship )
  {
    mass += 100;
    mass += cdata->p_nmb_pdefense;
    if( cdata->p_has_base )
      mass += cdata->p_nmb_bdefense;
  }

  /* done */
  return( mass );
}



/*
 *  computes the battlemass for the involved ship
 */
gint vcrc_get_ships_battlemass( combatdata *cdata, gint side )
{
  gint mass = 0;
  GwpHullSpec *hull;

  switch( side )
  {
    case VCRC_SIDE_A:
      hull = GWP_HULLSPEC( g_slist_nth_data( hullspec_list, cdata->a_typ_hull-1 ) );
      mass += gwp_hullspec_get_mass( hull );
      mass += cdata->g_shibon * vcrc_get_engine_price( cdata->a_typ_engines );
      /* TODO ... allow FED CREW BONUS */ 
      break;
    case VCRC_SIDE_B:
      hull = GWP_HULLSPEC( g_slist_nth_data( hullspec_list, cdata->b_typ_hull-1 ) );
      mass += gwp_hullspec_get_mass( hull );
      mass += cdata->g_shibon * vcrc_get_engine_price( cdata->b_typ_engines );
      /* TODO ... allow FED CREW BONUS */ 
      /* TODO ... add 300kt of mass in 60% of all times ship a is a carrier */ 
      break;
    default:
      g_message( "## Warning: vcrc_get_ships_battlemass received wrong 'side'" );
      break;
  }


  /* done */
  return( mass );
}



/*
 *  initializes the logging textview
 */
void init_log( void )
{
  GtkTextView *view = GTK_TEXT_VIEW( lookup_widget( "vcr_textview_log" ) );
  vcr_logging_textview_buffer = gtk_text_view_get_buffer( view );
  PangoFontDescription *pfontdesc = pango_font_description_from_string( "Monospace 10" );
  gtk_widget_modify_font( GTK_WIDGET( view ), pfontdesc );
}



/*
 *  prints a combat situation summary to the logging textview
 */
void vcrc_print_combatants( combatdata *cdata )
{
  vcrc_log_str( "----------------------------\n"                                             );
  vcrc_log_str( "             :    A  -     B\n"                                             );
  vcrc_log_str( "is a ship    : "          ); vcrc_log_intn( cdata->g_a_is_ship   , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->g_b_is_ship  , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "shield       : "          ); vcrc_log_intn( cdata->a_shield      , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_shield     , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "hull left    : "          ); vcrc_log_intn( cdata->a_hull        , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_hull       , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "crew members : "          ); vcrc_log_intn( cdata->a_crew        , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_crew       , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "type of hull : "          ); vcrc_log_intn( cdata->a_typ_hull    , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_typ_hull   , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "fighters     : "          ); vcrc_log_intn( cdata->a_nmb_fighter , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_nmb_fighter, 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "fighter bays : "          ); vcrc_log_intn( cdata->a_nmb_bays    , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_nmb_bays   , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "torpedos     : "          ); vcrc_log_intn( cdata->a_nmb_torps   , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_nmb_torps  , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "torpedotubes : "          ); vcrc_log_intn( cdata->a_nmb_tubes   , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_nmb_tubes  , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "torpedotype  : "          ); vcrc_log_intn( cdata->a_typ_torps   , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_typ_torps  , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "beams        : "          ); vcrc_log_intn( cdata->a_nmb_beams   , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_nmb_beams  , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "beamtype     : "          ); vcrc_log_intn( cdata->a_typ_beams   , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_typ_beams  , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "enginetype   : "          ); vcrc_log_intn( cdata->a_typ_engines , 4 ); vcrc_log_str( "  -  " ); vcrc_log_intn( cdata->b_typ_engines, 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "has starbase :       -  " ); vcrc_log_intn( cdata->p_has_base    , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "pl. beamtype :       -  " ); vcrc_log_intn( cdata->p_typ_beams   , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "pl. defense  :       -  " ); vcrc_log_intn( cdata->p_nmb_pdefense, 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "bas defense  :       -  " ); vcrc_log_intn( cdata->p_nmb_bdefense, 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "bas fighters :       -  " ); vcrc_log_intn( cdata->p_nmb_fighter , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "shield bonus :     " ); vcrc_log_intn( cdata->g_shibon, 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "----------------------------\n"                                             );
}


/*
 *  prints a gchar* string to the logging textview
 */
void vcrc_log_str( gchar *str )
{
  gtk_text_buffer_insert_at_cursor( vcr_logging_textview_buffer, str, strlen(str) );
}



/*
 *  prints n characters of a gchar* string to the logging textview
 */
void vcrc_log_strn( gchar *str, gint len )
{
  gtk_text_buffer_insert_at_cursor( vcr_logging_textview_buffer, str, len );
}



/*
 *  prints an integer value to the logging textview
 */
void vcrc_log_int( gint val )
{
  gint i=1, t=val;
  while( t>9 ) {
    t = t/10;
    i++; }
  vcrc_log_intn( val, i );
}



/*
 *  prints an integer value to the logging textview
 *  using exatly n characters, right justified, space padded if necessary
 */
void vcrc_log_intn( gint val, gint len )
{
  gint i=1, t=val;
  while( t>9 ) {
    t = t/10;
    i++; }
  for( t=0; t<(len-i); t++ ) vcrc_log_str( " " );
  gchar *txt = (gchar *)g_malloc((i+1)*sizeof(gchar));
  g_snprintf( txt, i+1, "%d", val );
  vcrc_log_strn( txt, i );
  g_free( txt );
}




/*
 *  returns true in n percent of all calls
 */
gboolean vcrc_rand( gint n )
{
  gdouble t;
  gint r;

  t = (gdouble)random() / (gdouble)RAND_MAX;
  r = (gint)( t * 100 );
  /* just in case */
  if( r == 100 ) r--;

  if( r < n )
    return( TRUE );
  else
    return( FALSE );
}
