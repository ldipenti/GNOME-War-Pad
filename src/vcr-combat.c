#include "vcr-combat.h"
#include "support.h"

/* TODO */
#define FED_CREW_BONUS 0

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
}


void vcrc_prepare_for_battle( combatdata *cdata, battlefield *battle )
{
  vcrc_log_str( "Preparing for Battle ...\n" );
  /* initialize the battlefield */
  battle->time = 0;

  vcrc_prepare_platforms( cdata, battle );
  vcrc_prepare_fighters( cdata, battle );
  vcrc_prepare_torpedos( cdata, battle );
  vcrc_prepare_beams( cdata, battle );
}


void vcrc_prepare_platforms( combatdata *cdata, battlefield *battle )
{
  if( cdata->g_a_is_ship == 1 )
  {
    vcrc_log_str( "Preparing Platforms ...\n" );
    battle->a.position    = 0;                // starting from the 'left'
    battle->a.direction   = 1;                // moving 'right'
    battle->a.speed       = SPEED_SHIPS;      // 
    battle->a.shield      = cdata->a_shield;  //
    battle->a.hull        = cdata->a_hull;    //
    battle->a.crew        = cdata->a_crew;    //
    battle->a.mass        = 200;              // TODO
  }
  else
  {
    vcrc_log_str( "\n###   WARNING: Side A has to be a Ship   ###\n" );
  }

  if( cdata->g_b_is_ship == 1 )
  {
    battle->b.position    = MAX_DISTANCE_SHIPS; // starting from the 'right'
    battle->b.direction   = -1;                 // moving 'left'
    battle->b.speed       = SPEED_SHIPS;        // 
    battle->b.shield      = cdata->b_shield;    //
    battle->b.hull        = cdata->b_hull;      //
    battle->b.crew        = cdata->b_crew;      //
    battle->b.mass        = 200;                // TODO
  }
  else
  {
    vcrc_log_str( "\n###   WARNING: Side B has to be a Ship   ###\n" );
  }
}


void vcrc_prepare_fighters( combatdata *cdata, battlefield *battle )
{
  vcrc_log_str( "Preparing Fighters ...\n" );
}


void vcrc_prepare_torpedos( combatdata *cdata, battlefield *battle )
{
  vcrc_log_str( "Preparing Torpedos ...\n" );
}


void vcrc_prepare_beams( combatdata *cdata, battlefield *battle )
{
  vcrc_log_str( "Preparing Beamweapons ...\n" );
}


void vcrc_fight( battlefield *battle )
{
}

void init_log( void )
{
  GtkTextView *view = GTK_TEXT_VIEW( lookup_widget( "vcr_textview_log" ) );
  vcr_logging_textview_buffer = gtk_text_view_get_buffer( view );
  PangoFontDescription *pfontdesc = pango_font_description_from_string( "Monospace 10" );
  gtk_widget_modify_font( GTK_WIDGET( view ), pfontdesc );
}

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
  vcrc_log_str( "has starbase :       -  " ); vcrc_log_intn( cdata->p_has_base    , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "pl. beamtype :       -  " ); vcrc_log_intn( cdata->p_typ_beams   , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "pl. defense  :       -  " ); vcrc_log_intn( cdata->p_nmb_pdefense, 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "bas defense  :       -  " ); vcrc_log_intn( cdata->p_nmb_bdefense, 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "bas fighters :       -  " ); vcrc_log_intn( cdata->p_nmb_fighter , 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "shield bonus :     " ); vcrc_log_intn( cdata->g_shibon, 4 ); vcrc_log_str( "\n" );
  vcrc_log_str( "----------------------------\n"                                             );
}

void vcrc_log_str( gchar *str )
{
  gtk_text_buffer_insert_at_cursor( vcr_logging_textview_buffer, str, strlen(str) );
}

void vcrc_log_strn( gchar *str, gint len )
{
  gtk_text_buffer_insert_at_cursor( vcr_logging_textview_buffer, str, len );
}

void vcrc_log_int( gint val )
{
  gint i=1, t=val;
  while( t>9 ) {
    t = t/10;
    i++; }
  vcrc_log_intn( val, i );
}

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

