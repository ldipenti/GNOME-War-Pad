#include "vcr-combat-gl.h"
#include "vcr-combat.h"
#include "vcr.h"
#include "support.h"

/* TODO */
#define FED_CREW_BONUS 0


#define VCRCGL_SIMULATION_DELAY 100000

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

  /* nomen est omen */
  vcrc_prepare_for_battle( cdata, &battle );

  /* give the user some status info about the coming battle */
  vcrc_print_combatants( cdata );

  /* try to initialize the open-gl simulation area */
  vcrcgl_init();
  vcrc_initilize_graphs( &battle );

  /* Hey Ho ... Let's GO */
  vcrc_fight( &battle );

while( gtk_events_pending() )
  gtk_main_iteration();

  /* print the most important values of each combatant after battle */
  vcrc_print_summary( &battle, cdata );
}



void vcrc_initilize_graphs( battlefield *battle )
{
  gint i;
  vcrcgl_show_beams( VCRC_SIDE_A, battle->a.beams.number );
  vcrcgl_show_beams( VCRC_SIDE_B, battle->b.beams.number );
  for( i=0; i<battle->a.beams.number; i++ )
    vcrcgl_show_beamlevel( VCRC_SIDE_A, i, battle->a.beams.beam[i].fill );
  for( i=0; i<battle->b.beams.number; i++ )
    vcrcgl_show_beamlevel( VCRC_SIDE_B, i, battle->b.beams.beam[i].fill );
  vcrcgl_show_ammulevel( VCRC_SIDE_A, battle->a.torps + battle->a.fighters.number );
  vcrcgl_show_ammulevel( VCRC_SIDE_B, battle->b.torps + battle->b.fighters.number );
  vcrcgl_show_shieldlevel( VCRC_SIDE_A, battle->a.shield );
  vcrcgl_show_shieldlevel( VCRC_SIDE_B, battle->b.shield );
  vcrcgl_show_hulllevel( VCRC_SIDE_A, battle->a.hull );
  vcrcgl_show_hulllevel( VCRC_SIDE_B, battle->b.hull );
  vcrcgl_show_crewlevel( VCRC_SIDE_A, battle->a.crew );
  vcrcgl_show_crewlevel( VCRC_SIDE_B, battle->b.crew );
}



/*
 *  this function is supposed to prepare all combat related arrays
 *  and to initialize all combat values
 */
void vcrc_prepare_for_battle( combatdata *cdata, battlefield *battle )
{
  struct timeval timenow;

  vcrc_log_str( "Preparing for Battle ...\n" );

  /* start the random generation */
  gettimeofday( &timenow, NULL );
  srandom( (unsigned int)( timenow.tv_sec + timenow.tv_usec ) );

  vcrc_prepare_battlefield( cdata, battle );
  vcrc_prepare_platforms( cdata, battle );
  vcrc_prepare_fighters( cdata, battle );
  vcrc_prepare_torpedos( cdata, battle );
  vcrc_prepare_beams( cdata, battle );
}



/*
 *  sets all global combat values
 */
void vcrc_prepare_battlefield( combatdata *cdata, battlefield *battle )
{
  battle->time = 0;
  battle->fighton = TRUE;
  battle->shieldbonus = cdata->g_shibon;
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
    battle->a.direction   = VCRC_DIRECTION_A; // moving 'right'
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
    battle->b.direction   = VCRC_DIRECTION_B;        // moving 'left'
    battle->b.speed       = VCRC_SPEED_SHIPS;        // 
    battle->b.shield      = cdata->b_shield;         //
    battle->b.hull        = cdata->b_hull;           //
    battle->b.crew        = cdata->b_crew;           //
    battle->b.mass        = vcrc_get_ships_battlemass( cdata, VCRC_SIDE_B );
  }
  else
  {
    battle->b.position    = VCRC_MAX_DISTANCE_PLANET; // starting from the 'right'
    battle->b.direction   = VCRC_DIRECTION_B;         // moving 'left'
    battle->b.speed       = VCRC_SPEED_PLANET;        // moving 'not' ;-)
    battle->b.shield      = cdata->b_shield;          // TODO: not sure if 2nd fight
    battle->b.hull        = cdata->b_hull;            // TODO: not sure if 2nd fight
    battle->b.crew        = 100000;                   // TODO: does not matter at all
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
  battle->a.bays.number = cdata->a_nmb_bays;
  battle->a.fighters.number = cdata->a_nmb_fighter;
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
      battle->a.fighters.fighter[i].shield = vcrc_get_shield_damage_for_fighter( battle->b.mass );
      battle->a.fighters.fighter[i].hull = vcrc_get_hull_damage_for_fighter( battle->b.mass );
      battle->a.fighters.fighter[i].crew = vcrc_get_crew_damage_for_fighter( battle->b.mass );
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
  battle->b.bays.number = cdata->b_nmb_bays;
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
g_message( "VCR-DEBUG: fighters %d, bays %d", battle->b.fighters.number, battle->b.bays.number );
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
      battle->b.fighters.fighter[i].shield = vcrc_get_shield_damage_for_fighter( battle->a.mass );
      battle->b.fighters.fighter[i].hull = vcrc_get_hull_damage_for_fighter( battle->a.mass );
      battle->b.fighters.fighter[i].crew = vcrc_get_crew_damage_for_fighter( battle->a.mass );
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
  battle->a.torps = cdata->a_nmb_torps;
  for( i=0; i<cdata->a_nmb_tubes; i++ )
  {
    battle->a.tubes.tube[i].load   = vcrc_get_reload_time_for_torp(   cdata->a_typ_torps );
    battle->a.tubes.tube[i].full   = vcrc_get_reload_time_for_torp(   cdata->a_typ_torps );
    battle->a.tubes.tube[i].shield = vcrc_get_shield_damage_for_torp( cdata->a_typ_torps, battle->b.mass );
    battle->a.tubes.tube[i].hull   = vcrc_get_hull_damage_for_torp(   cdata->a_typ_torps, battle->b.mass );
    battle->a.tubes.tube[i].crew   = vcrc_get_crew_damage_for_torp(   cdata->a_typ_torps, battle->b.mass );
  }

  /* combatant B */
  battle->b.tubes.number = cdata->b_nmb_tubes;
  battle->b.torps = cdata->b_nmb_torps;
  for( i=0; i<cdata->b_nmb_tubes; i++ )
  {
    battle->b.tubes.tube[i].load   = vcrc_get_reload_time_for_torp(   cdata->b_typ_torps );
    battle->b.tubes.tube[i].full   = vcrc_get_reload_time_for_torp(   cdata->b_typ_torps );
    battle->b.tubes.tube[i].shield = vcrc_get_shield_damage_for_torp( cdata->b_typ_torps, battle->a.mass );
    battle->b.tubes.tube[i].hull   = vcrc_get_hull_damage_for_torp(   cdata->b_typ_torps, battle->a.mass );
    battle->b.tubes.tube[i].crew   = vcrc_get_crew_damage_for_torp(   cdata->b_typ_torps, battle->a.mass );
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
    battle->a.beams.beam[i].type = cdata->a_typ_beams;
    if( cdata->a_shield == 100 )
      battle->a.beams.beam[i].fill = 100;
    else
      battle->a.beams.beam[i].fill = 0;
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
    battle->b.beams.beam[i].type = cdata->b_typ_beams;
    if( cdata->b_shield == 100 )
      battle->b.beams.beam[i].fill = 100;
    else
      battle->b.beams.beam[i].fill = 0;
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
      && battle->fighton )
  {
    vcrc_fight_reload_weapons( battle );
    vcrc_fight_move_platforms( battle );
    vcrc_fight_launch_fighters( battle );
    vcrc_fight_move_fighters( battle, VCRC_SIDE_A );
    vcrc_fight_attack_fighters( battle, VCRC_SIDE_A );
    vcrc_fight_move_fighters( battle, VCRC_SIDE_B );
    vcrc_fight_attack_fighters( battle, VCRC_SIDE_B );
    vcrc_fight_attack_torpedos( battle );
    vcrc_fight_attack_beams( battle );
    battle->time++;
    usleep( VCRCGL_SIMULATION_DELAY );
  }
}



void vcrc_fight_reload_weapons( battlefield *battle )
{
  gint i;

  /* side A */
  for( i=0; i<battle->a.beams.number; i++ )
  {
    if( vcrc_rand( VCRC_CHANCE_BEAM_FILL_PER_M ) )
    {
      battle->a.beams.beam[i].fill += VCRC_AMOUNT_BEAM_FILL_PER_M;
      if( battle->a.beams.beam[i].fill > 100 )
        battle->a.beams.beam[i].fill = 100;
    }
vcrcgl_show_beamlevel( VCRC_SIDE_A, i, battle->a.beams.beam[i].fill );
  }
  for( i=0; i<battle->a.tubes.number; i++ )
  {
    battle->a.tubes.tube[i].load++;
    if( battle->a.tubes.tube[i].load > 100 )
      battle->a.tubes.tube[i].load = 100;
  }

  /* side B */
  for( i=0; i<battle->b.beams.number; i++ )
  {
    if( vcrc_rand( VCRC_CHANCE_BEAM_FILL_PER_M ) )
    {
      battle->b.beams.beam[i].fill += VCRC_AMOUNT_BEAM_FILL_PER_M;
      if( battle->b.beams.beam[i].fill > 100 )
        battle->b.beams.beam[i].fill = 100;
    }
vcrcgl_show_beamlevel( VCRC_SIDE_B, i, battle->b.beams.beam[i].fill );
  }
  for( i=0; i<battle->b.tubes.number; i++ )
  {
    battle->b.tubes.tube[i].load++;
    if( battle->b.tubes.tube[i].load > 100 )
      battle->b.tubes.tube[i].load = 100;
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



void vcrc_fight_move_fighters( battlefield *battle, gint side )
{
  gint i;

  switch( side )
  {
    case VCRC_SIDE_A:
      /* SIDE A */
      if( battle->a.fighters.flying > 0 )
      for( i=0; i<battle->a.fighters.number; i++ )
      {
        if( battle->a.fighters.fighter[i].launched )
        {
//g_print( "VCR-DEBUG: fighter a %d moving from %d", i, battle->a.fighters.fighter[i].position );
          /* move this fighter */
          battle->a.fighters.fighter[i].position += battle->a.fighters.fighter[i].direction
                                                  * battle->a.fighters.fighter[i].speed;
//g_print( " to %d\n", battle->a.fighters.fighter[i].position );

          /* check if fighter has reached enemy platform and turns around */
          if( battle->a.fighters.fighter[i].position > battle->b.position )
          {
//g_print( "VCR-DEBUG: fighter a %d - turning\n", i );
            battle->a.fighters.fighter[i].position = battle->b.position;
            battle->a.fighters.fighter[i].direction *= ( -1 );
          }

          /* check if fighter has returned to carrier */
          if( battle->a.fighters.fighter[i].position <= battle->a.position &&
              battle->a.fighters.fighter[i].direction * battle->a.direction < 0 )
          {
//g_print( "VCR-DEBUG: fighter a %d - landing\n", i );
            battle->a.fighters.fighter[i].launched = FALSE;
            battle->a.fighters.flying--;
          }
        }
      }
      break;

    case VCRC_SIDE_B:
      /* SIDE B */
      if( battle->b.fighters.flying > 0 )
      for( i=0; i<battle->b.fighters.number; i++ )
      {
        if( battle->b.fighters.fighter[i].launched )
        {
//g_print( "VCR-DEBUG: fighter b %d moving from %d", i, battle->b.fighters.fighter[i].position );
          /* move this fighter */
          battle->b.fighters.fighter[i].position += battle->b.fighters.fighter[i].direction
                                                  * battle->b.fighters.fighter[i].speed;
//g_print( " to %d\n", battle->b.fighters.fighter[i].position );

          /* check if fighter has reached enemy platform and turns around */
          if( battle->b.fighters.fighter[i].position < battle->a.position )
          {
//g_print( "VCR-DEBUG: fighter b %d - turning\n", i );
            battle->b.fighters.fighter[i].position = battle->b.position;
            battle->b.fighters.fighter[i].direction *= ( -1 );
          }

          /* check if fighter has returned to carrier */
          if( battle->b.fighters.fighter[i].position >= battle->b.position &&
              battle->b.fighters.fighter[i].direction * battle->b.direction < 0 )
          {
//g_print( "VCR-DEBUG: fighter b %d - landing\n", i );
            battle->b.fighters.fighter[i].launched = FALSE;
            battle->b.fighters.flying--;
          }
        }
      }
      break;
    default:
      break;
  }
}



void vcrc_fight_launch_fighters( battlefield *battle )
{
  gint i;

  /* SIDE A */
  if( battle->a.fighters.number > battle->a.fighters.flying  && 
      battle->a.fighters.flying < VCRC_MAX_LAUNCHED_FIGHTERS )
    if( vcrc_rand( 5 * battle->a.bays.number ) )
    {
      i = 0;
      while( battle->a.fighters.fighter[i].launched &&
             battle->a.fighters.number > i )
      {
        i++;
      }
      /* launch this fighter */
//g_print( "VCR-DEBUG: fighter %d - launching at %d (time: %d)\n", i, battle->a.position, battle->time );
      battle->a.fighters.fighter[i].launched  = TRUE;
      battle->a.fighters.fighter[i].position  = battle->a.position;
      battle->a.fighters.fighter[i].direction = VCRC_DIRECTION_A;
      battle->a.fighters.fighter[i].speed     = VCRC_SPEED_FIGHTER;
      battle->a.fighters.flying++;
    }

  /* SIDE B */
  if( battle->b.fighters.number > battle->b.fighters.flying  && 
      battle->b.fighters.flying < VCRC_MAX_LAUNCHED_FIGHTERS )
    if( vcrc_rand( 5 * battle->b.bays.number ) )
    {
      i = 0;
      while( battle->b.fighters.fighter[i].launched &&
             battle->b.fighters.number > i )
      {
        i++;
      }
      /* launch this fighter */
//g_print( "VCR-DEBUG: fighter %d - launching at %d (time: %d)\n", i, battle->b.position, battle->time );
      battle->b.fighters.fighter[i].launched  = TRUE;
      battle->b.fighters.fighter[i].position  = battle->b.position;
      battle->b.fighters.fighter[i].direction = VCRC_DIRECTION_B;
      battle->b.fighters.fighter[i].speed     = VCRC_SPEED_FIGHTER;
      battle->b.fighters.flying++;
    }
}



void vcrc_fight_attack_fighters( battlefield *battle, gint side )
{
  gint i, j, k, l;

  switch( side )
  {
    case VCRC_SIDE_A:
      /* side A */
      i = 0;
      j = battle->a.fighters.flying;
      while( j>0 )
      {
        if( battle->a.fighters.fighter[i].launched )
        {
          /* check for dogfight situation */
          j--;
          k = 0;
          l = battle->b.fighters.flying;
          while( l>0 )
          {
            if( battle->b.fighters.fighter[k].launched )
            {
              if( abs( battle->a.fighters.fighter[i].position -
                       battle->b.fighters.fighter[k].position ) <= VCRC_RANGE_FIGHTER_FIGHTER )
              {
                /* two fighters, both launched, at same position */
                if( vcrc_rand( VCRC_CHANCE_FIGHTER_HIT_FIGHTER ) )
                {
//g_message( "VCR-DEBUG: fighter A destroys fighter B at %d", battle->a.fighters.fighter[i].position );
                  vcrc_fight_destroy_fighter( battle, VCRC_SIDE_B, k );
                  l--;
                } 
              }
            }
            l--;
          }
          /* check for platform-attack */
          if( abs( battle->a.fighters.fighter[i].position -
                   battle->b.position ) <= VCRC_RANGE_FIGHTER_SHIP
              && ( battle->a.fighters.fighter[i].direction *
                   battle->a.direction ) > 0 )
          {
            /* approaching enemy platform and in range */
            if( vcrc_rand( VCRC_CHANGE_FIGHTER_HIT_PLATFORM ) )
            {
//g_message( "VCR-DEBUG: fighter %d at %d (time %d) firing at %d", i, battle->a.fighters.fighter[i].position, battle->time, battle->b.position );
              /* hit it */
              vcrc_fight_hit( battle, VCRC_SIDE_B, 
                              battle->a.fighters.fighter[i].shield,
                              battle->a.fighters.fighter[i].hull,
                              battle->a.fighters.fighter[i].crew );
            }
          }
        }
        i++;
      }
      break;

    case VCRC_SIDE_B:
      /* side B */
      i = 0;
      j = battle->b.fighters.flying;
      while( j>0 )
      {
        if( battle->b.fighters.fighter[i].launched )
        {
          /* check for dogfight situation */
          j--;
          k = 0;
          l = battle->a.fighters.flying;
          while( l>0 )
          {
            if( battle->a.fighters.fighter[k].launched )
            {
              if( abs( battle->b.fighters.fighter[i].position -
                       battle->a.fighters.fighter[k].position ) <= VCRC_RANGE_FIGHTER_FIGHTER )
              {
                /* two fighters, both launched, at same position */
                if( vcrc_rand( VCRC_CHANCE_FIGHTER_HIT_FIGHTER ) )
                {
//g_message( "VCR-DEBUG: fighter B destroys fighter A at %d", battle->b.fighters.fighter[i].position );
                  vcrc_fight_destroy_fighter( battle, VCRC_SIDE_A, k );
                  l--;
                } 
              }
            }
            l--;
          }
          if( abs( battle->b.fighters.fighter[i].position -
                   battle->a.position ) <= VCRC_RANGE_FIGHTER_SHIP
              && ( battle->b.fighters.fighter[i].direction *
                   battle->b.direction ) > 0 )
          {
            /* approaching enemy platform and in range */
            if( vcrc_rand( VCRC_CHANGE_FIGHTER_HIT_PLATFORM ) )
            {
              /* hit it */
              vcrc_fight_hit( battle, VCRC_SIDE_A,
                              battle->b.fighters.fighter[i].shield,
                              battle->b.fighters.fighter[i].hull,
                              battle->b.fighters.fighter[i].crew );
            }
          }
        }
        i++;
      }
      break;
    default:
      break;
  }
}



void vcrc_fight_attack_torpedos( battlefield *battle )
{
  gint i;
  /* side A */
  if( battle->a.torps > 0 )
  {
    for( i=0; i<battle->a.tubes.number; i++ )
    {
      if( battle->a.tubes.tube[i].load >= battle->a.tubes.tube[i].full &&
          abs( battle->a.position - battle->b.position ) <= VCRC_RANGE_TORP_SHIP )
      {
          battle->a.tubes.tube[i].load = 0;
          battle->a.torps--;
          vcrcgl_show_ammulevel( VCRC_SIDE_A, battle->a.torps );
          if( vcrc_rand( VCRC_CHANCE_TORP_HIT_SHIP ) )
            vcrc_fight_hit( battle, VCRC_SIDE_B,
                            battle->a.tubes.tube[i].shield,
                            battle->a.tubes.tube[i].hull,
                            battle->a.tubes.tube[i].crew );
      }
    }
  }

  /* side B */
  if( battle->b.torps > 0 )
  {
//g_print( "VCR-DEBUG: torp fill " );
    for( i=0; i<battle->b.tubes.number; i++ )
    {
//g_print( "[%3d]", battle->b.tubes.tube[i].load );
      if( battle->b.tubes.tube[i].load >= battle->b.tubes.tube[i].full &&
          abs( battle->b.position - battle->a.position ) <= VCRC_RANGE_TORP_SHIP )
      {
//g_message( "VCR-DEBUG: FIRING TORPEDO VOLLEY ...." );
          battle->b.tubes.tube[i].load = 0;
          battle->b.torps--;
          vcrcgl_show_ammulevel( VCRC_SIDE_B, battle->b.torps );
          if( vcrc_rand( VCRC_CHANCE_TORP_HIT_SHIP ) )
            vcrc_fight_hit( battle, VCRC_SIDE_A,
                            battle->b.tubes.tube[i].shield,
                            battle->b.tubes.tube[i].hull,
                            battle->b.tubes.tube[i].crew );
      }
    }
//g_print( "\n" );
  }

}



void vcrc_fight_attack_beams( battlefield *battle )
{
  gint i, j;
  gboolean atfighter;

  /* side A */
  for( i=0; i<battle->a.beams.number; i++ )
  {
    atfighter = FALSE;
    /* ready to shoot at fighter? */
    if( battle->a.beams.beam[i].fill >= VCRC_MIN_FILL_BEAM_FIGHTER )
    {
      /* search for launched enemy fighters */
      for( j=0; j<battle->b.fighters.number; j++ )
      {
        if( battle->b.fighters.fighter[j].launched == 1 )
        {
          if( abs( battle->b.fighters.fighter[j].position - battle->a.position )
              <= VCRC_RANGE_BEAM_FIGHTER )
          {
            if( vcrc_rand( VCRC_CHANCE_BEAM_FIRE_FIGHTER ) )
            {
              if( vcrc_rand( VCRC_CHANCE_BEAM_HIT_FIGHTER ) )
                vcrc_fight_destroy_fighter( battle, VCRC_SIDE_B, j );
              battle->a.beams.beam[i].fill = 0;
            }
            /* beam aims at enemy fighter, but this is the only chance to shoot */
            atfighter = TRUE;
            j = battle->b.fighters.number;
          }
        }
      }
    }
    if( !atfighter )
    {
      /* try to shoot at enemy main platform */
      if( battle->a.beams.beam[i].fill >= VCRC_MIN_FILL_BEAM_SHIP )
      {
        if( abs( battle->b.position - battle->a.position )
            <= VCRC_RANGE_BEAM_SHIP )
        {
          if( vcrc_rand( VCRC_CHANCE_BEAM_FIRE_SHIP ) )
          {
            if( vcrc_rand( VCRC_CHANCE_BEAM_HIT_SHIP ) )
            {
              /* aimed at platform, shot, hit */
//g_message( "VCR-DEBUG: (%d, %d) beam %d firing", battle->a.position, battle->time, i );
              vcrc_fight_hit( battle, VCRC_SIDE_B,
                              vcrc_get_shield_damage_for_beam(
                                battle->a.beams.beam[i].type,
                                battle->a.beams.beam[i].fill,
                                battle->b.mass ),
                              vcrc_get_hull_damage_for_beam(
                                battle->a.beams.beam[i].type,
                                battle->a.beams.beam[i].fill,
                                battle->b.mass ),
                              vcrc_get_crew_damage_for_beam(
                                battle->a.beams.beam[i].type,
                                battle->a.beams.beam[i].fill,
                                battle->b.mass ) );
            }
            battle->a.beams.beam[i].fill = 0;
          }
        }
      }
    }
  }

  /* side B */
  for( i=0; i<battle->b.beams.number; i++ )
  {
    atfighter = FALSE;
    /* ready to shoot at fighter? */
    if( battle->b.beams.beam[i].fill >= VCRC_MIN_FILL_BEAM_FIGHTER )
    {
      /* search for launched enemy fighters */
      for( j=0; j<battle->a.fighters.number; j++ )
      {
        if( battle->a.fighters.fighter[j].launched == 1 )
        {
          if( abs( battle->a.fighters.fighter[j].position - battle->b.position )
              <= VCRC_RANGE_BEAM_FIGHTER )
          {
            if( vcrc_rand( VCRC_CHANCE_BEAM_FIRE_FIGHTER ) )
            {
              if( vcrc_rand( VCRC_CHANCE_BEAM_HIT_FIGHTER ) )
                vcrc_fight_destroy_fighter( battle, VCRC_SIDE_A, j );
              battle->b.beams.beam[i].fill = 0;
//g_message( "VCR-DEBUG (%d): beam(%d) fires at fighter", battle->time, i );
            }
            /* beam aims at enemy fighter, but this is the only chance to shoot */
            atfighter = TRUE;
            j = battle->a.fighters.number;
          }
        }
      }
    }
    if( !atfighter )
    {
      /* try to shoot at enemy main platform */
      if( battle->b.beams.beam[i].fill >= VCRC_MIN_FILL_BEAM_SHIP )
      {
        if( abs( battle->a.position - battle->b.position )
            <= VCRC_RANGE_BEAM_SHIP )
        {
          if( vcrc_rand( VCRC_CHANCE_BEAM_FIRE_SHIP ) )
          {
            if( vcrc_rand( VCRC_CHANCE_BEAM_HIT_SHIP ) )
            {
              /* aimed at platform, shot, hit */
              vcrc_fight_hit( battle, VCRC_SIDE_A,
                              vcrc_get_shield_damage_for_beam(
                                battle->b.beams.beam[i].type,
                                battle->b.beams.beam[i].fill,
                                battle->a.mass ),
                              vcrc_get_hull_damage_for_beam(
                                battle->b.beams.beam[i].type,
                                battle->b.beams.beam[i].fill,
                                battle->a.mass ),
                              vcrc_get_crew_damage_for_beam(
                                battle->b.beams.beam[i].type,
                                battle->b.beams.beam[i].fill,
                                battle->a.mass ) );
            }
            battle->b.beams.beam[i].fill = 0;
//g_message( "VCR-DEBUG (%d): beam(%d) fires at platform", battle->time, i );
          }
        }
      }
    }
  }
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
      battle->a.fighters.flying--;
      vcrcgl_show_ammulevel( VCRC_SIDE_A, battle->a.fighters.number );
      break;
    case VCRC_SIDE_B:
      n = battle->b.fighters.number;
      battle->b.fighters.fighter[id].launched  = battle->b.fighters.fighter[n].launched ;
      battle->b.fighters.fighter[id].position  = battle->b.fighters.fighter[n].position ;
      battle->b.fighters.fighter[id].direction = battle->b.fighters.fighter[n].direction;
      battle->b.fighters.fighter[id].speed     = battle->b.fighters.fighter[n].speed    ;
      battle->b.fighters.number--;
      battle->b.fighters.flying--;
      vcrcgl_show_ammulevel( VCRC_SIDE_B, battle->b.fighters.number );
      break;
    default:
      return; // something went wrong
      break;
  }
}



/*
 *  inflicts the given damage to one of the main platforms
 */
void vcrc_fight_hit( battlefield *battle, gint side, gint sdam, gint hdam, gint cdam )
{
//g_print( "VCR-DEBUG (%d): Damage inflicted on %d, [%d, %d, %d] .. ", battle->time, side, sdam, hdam, cdam );
  switch( side )
  {
    case VCRC_SIDE_A:
      if( battle->a.shield > 0 )
        battle->a.shield -= sdam;
      else
      {
        battle->a.hull -= hdam;
        battle->a.crew -= cdam;
      }
      /* clean up */
      if( battle->a.shield < 0 ) battle->a.shield = 0;
      if( battle->a.hull   < 0 ) battle->a.hull   = 0;
      if( battle->a.crew   < 0 ) battle->a.crew   = 0;
//g_print( "[%d, %d, %d]\n", battle->a.shield, battle->a.hull, battle->a.crew );
      /* update the gui */
      vcrcgl_show_shieldlevel( VCRC_SIDE_A, battle->a.shield );
      vcrcgl_show_hulllevel( VCRC_SIDE_A, battle->a.hull   );
      vcrcgl_show_crewlevel( VCRC_SIDE_A, battle->a.crew   );
      break;
    case VCRC_SIDE_B:
      if( battle->b.shield > 0 )
        battle->b.shield -= sdam;
      else
      {
        battle->b.hull -= hdam;
        battle->b.crew -= cdam;
      }
      /* clean up */
      if( battle->b.shield < 0 ) battle->b.shield = 0;
      if( battle->b.hull   < 0 ) battle->b.hull   = 0;
      if( battle->b.crew   < 0 ) battle->b.crew   = 0;
//g_print( "[%d, %d, %d]\n", battle->b.shield, battle->b.hull, battle->b.crew );
      /* update the gui */
      vcrcgl_show_shieldlevel( VCRC_SIDE_B, battle->b.shield );
      vcrcgl_show_hulllevel( VCRC_SIDE_B, battle->b.hull   );
      vcrcgl_show_crewlevel( VCRC_SIDE_B, battle->b.crew   );
      break;
    default:
      break;
  }

  /* check for destruction */
  if( battle->a.hull <= 0  ||
      battle->a.crew <= 0  ||
      battle->b.hull <= 0  ||
      battle->b.crew <= 0 )
      battle->fighton = FALSE;
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
gint vcrc_get_shield_damage_for_torp( gint type, gint mass )
{
  gint p;
  switch( type )
  {
    case 1:  p =  5; break;
    case 2:  p =  8; break;
    case 3:  p = 10; break;
    case 4:  p =  2; break;
    case 5:  p = 15; break;
    case 6:  p = 30; break;
    case 7:  p = 35; break;
    case 8:  p = 40; break;
    case 9:  p = 48; break;
    case 10: p = 55; break;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      p = 1000;
      break;
  }
  return( round( ( p * 160.0 )/( mass+1 ) ) + 1 );
}



/*
 *  returns the amount of damage a torpedo of this type
 *  inflicts on the opponents hull structure
 */
gint vcrc_get_hull_damage_for_torp( gint type, gint mass )
{
  gint p;
  switch( type )
  {
    case 1:  p =  5; break;
    case 2:  p =  8; break;
    case 3:  p = 10; break;
    case 4:  p =  2; break;
    case 5:  p = 15; break;
    case 6:  p = 30; break;
    case 7:  p = 35; break;
    case 8:  p = 40; break;
    case 9:  p = 48; break;
    case 10: p = 55; break;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      p = 1000;
      break;
  }
  return( round( round( ( p* 160.0 )/( mass+1 ) + 1 ) * (( 80.0 )/( mass+1 )) ) + 1 );
}



/*
 *  returns the amount of damage a torpedo of this type
 *  inflicts on the opponents crew members
 */
gint vcrc_get_crew_damage_for_torp( gint type, gint mass )
{
  gint p;
  switch( type )
  {
    case 1:  p =  4; break;
    case 2:  p =  6; break;
    case 3:  p =  3; break;
    case 4:  p = 15; break;
    case 5:  p =  9; break;
    case 6:  p = 13; break;
    case 7:  p = 17; break;
    case 8:  p = 23; break;
    case 9:  p = 25; break;
    case 10: p = 35; break;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      p = 1000;
      break;
  }
  return( round(( p * 160.0 )/( mass+1 )) );
}



/*
 *  returns the amount of damage a beamweapon of this type
 *  inflicts on the opponents shield
 */
gint vcrc_get_shield_damage_for_beam( gint type, gint fill, gint mass )
{
  gint p;
  switch( type )
  {
    case 1:  p =  3; break;
    case 2:  p =  1; break;
    case 3:  p = 10; break;
    case 4:  p = 25; break;
    case 5:  p = 29; break;
    case 6:  p = 20; break;
    case 7:  p = 40; break;
    case 8:  p = 35; break;
    case 9:  p = 35; break;
    case 10: p = 45; break;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      p = 1000;
      break;
  }
  return( round( ( round( (0.01*fill*p) ) * 80.0 )/( mass+1 ) ) + 1 );
}



/*
 *  returns the amount of damage a beamweapon of this type
 *  inflicts on the opponents hull structure
 */
gint vcrc_get_hull_damage_for_beam( gint type, gint fill, gint mass )
{
  gint p;
  switch( type )
  {
    case 1:  p =  3; break;
    case 2:  p =  1; break;
    case 3:  p = 10; break;
    case 4:  p = 25; break;
    case 5:  p = 29; break;
    case 6:  p = 20; break;
    case 7:  p = 40; break;
    case 8:  p = 35; break;
    case 9:  p = 35; break;
    case 10: p = 45; break;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      p = 1000;
      break;
  }
  return( round( round( ( round( (0.01*fill*p) ) * 80.0 )/( mass+1 ) + 1 ) * (( 80.0 )/( mass+1 )) ) + 1 );
}



/*
 *  returns the amount of damage a beamweapon of this type
 *  inflicts on the opponents crew members
 */
gint vcrc_get_crew_damage_for_beam( gint type, gint fill, gint mass )
{
  gint p;
  switch( type )
  {
    case 1:  p = 10; break;
    case 2:  p = 15; break;
    case 3:  p =  3; break;
    case 4:  p = 10; break;
    case 5:  p =  9; break;
    case 6:  p = 30; break;
    case 7:  p = 20; break;
    case 8:  p = 30; break;
    case 9:  p = 50; break;
    case 10: p = 35; break;
    default:
      g_message( "## Warning: VCR-Combat: one combatant seems to have invalid torpedo type (%d)", type );
      p = 1000;
      break;
  }
  return( round(( round( (0.01*fill*p) ) * 80.0 )/( mass+1 )) );
}



gint vcrc_get_shield_damage_for_fighter( gint mass )
{
  /* verified, same like in 'master at arms' */
  return( round( ( 2 * 80.0 )/( mass+1 ) ) + 1 );
}



gint vcrc_get_hull_damage_for_fighter( gint mass )
{
  /* verified, same like in 'master at arms' */
  return( round( round( ( 2 * 80.0 )/( mass+1 ) + 1 ) * (( 80.0 )/( mass+1 )) ) + 1 );
}



gint vcrc_get_crew_damage_for_fighter( gint mass )
{
  /* verified, same like in 'master at arms' */
  return( round(( 1 * 160.0 )/( mass+1 )) );
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
      if( cdata->g_b_is_ship == 1 ) /* no shield-bonus when fighting a planet */
        mass += (0.01*cdata->g_shibon) * vcrc_get_engine_price( cdata->a_typ_engines );
      /* TODO ... allow FED CREW BONUS */ 
      break;
    case VCRC_SIDE_B:
      hull = GWP_HULLSPEC( g_slist_nth_data( hullspec_list, cdata->b_typ_hull-1 ) );
      mass += gwp_hullspec_get_mass( hull );
      if( cdata->g_a_is_ship == 1 ) /* no shield-bonus when fighting a planet */
        mass += (0.01*cdata->g_shibon) * vcrc_get_engine_price( cdata->b_typ_engines );
      /* TODO ... allow FED CREW BONUS */ 
      /* TODO ... add 300kt of mass in 60% of all times ship a is a carrier */ 
      break;
    default:
      g_message( "## Warning: vcrc_get_ships_battlemass received wrong 'side'" );
      break;
  }

g_message( "VCR-DEBUG: computed battlemasses: %d", mass );

  /* done */
  return( mass );
}



void vcrc_print_summary( battlefield *battle, combatdata *cdata )
{
  vcrc_log_str( "--- Summary after " ); vcrc_log_int( battle->time ); vcrc_log_str( " microns ---\n" );
  vcrc_log_str( "Side A: Shield   " ); vcrc_log_intn( cdata->a_shield     , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->a.shield          , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "        Hull     " ); vcrc_log_intn( cdata->a_hull       , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->a.hull            , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "        Crew     " ); vcrc_log_intn( cdata->a_crew       , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->a.crew            , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "        Fighters " ); vcrc_log_intn( cdata->a_nmb_fighter, 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->a.fighters.number , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "        Torpedos " ); vcrc_log_intn( cdata->a_nmb_torps  , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->a.torps           , 4 ); vcrc_log_str( "\n" );
  if( cdata->g_b_is_ship )
  {
  vcrc_log_str( "Side B: Shield   " ); vcrc_log_intn( cdata->b_shield     , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->b.shield          , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "        Hull     " ); vcrc_log_intn( cdata->b_hull       , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->b.hull            , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "        Crew     " ); vcrc_log_intn( cdata->b_crew       , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->b.crew            , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "        Fighters " ); vcrc_log_intn( cdata->b_nmb_fighter, 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->b.fighters.number , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "        Torpedos " ); vcrc_log_intn( cdata->b_nmb_torps  , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->b.torps           , 4 ); vcrc_log_str( "\n" );
//  vcrc_log_str( "Side B Data is incorrect in case of planet/starbase fights\n" );
  }
  else
  {
  vcrc_log_str( "Side B: Shield   " ); vcrc_log_intn( cdata->b_shield     , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->b.shield          , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "        Hull     " ); vcrc_log_intn( cdata->b_hull       , 4 ); vcrc_log_str( " -> " ); vcrc_log_intn( battle->b.hull            , 4 ); vcrc_log_str( "\n" );
  }
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
