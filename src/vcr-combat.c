#include "vcr-combat.h"


void vcr_combat_start( combatdata *cdata )
{
  init_log();
  vcrc_print_combatants( cdata );
}

void vcrc_print_combatants( combatdata *cdata )
{
  vcr_log_str( "----------------------------\n"                                             );
  vcr_log_str( "             :    A  -     B\n"                                             );
  vcr_log_str( "is a ship    : " ); vcr_log_intn( cdata->g_a_is_ship  , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->g_b_is_ship  , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "shield       : " ); vcr_log_intn( cdata->a_shield     , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_shield     , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "hull left    : " ); vcr_log_intn( cdata->a_hull       , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_hull       , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "crew members : " ); vcr_log_intn( cdata->a_crew       , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_crew       , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "type of hull : " ); vcr_log_intn( cdata->a_typ_hull   , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_typ_hull   , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "fighters     : " ); vcr_log_intn( cdata->a_nmb_fighter, 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_nmb_fighter, 4 ); vcr_log_str( "\n" );
  vcr_log_str( "fighter bays : " ); vcr_log_intn( cdata->a_nmb_bays   , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_nmb_bays   , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "torpedos     : " ); vcr_log_intn( cdata->a_nmb_torps  , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_nmb_torps  , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "torpedotubes : " ); vcr_log_intn( cdata->a_nmb_tubes  , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_nmb_tubes  , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "torpedotype  : " ); vcr_log_intn( cdata->a_typ_torps  , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_typ_torps  , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "beams        : " ); vcr_log_intn( cdata->a_nmb_beams  , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_nmb_beams  , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "beamtype     : " ); vcr_log_intn( cdata->a_typ_beams  , 4 ); vcr_log_str( "  -  " ); vcr_log_intn( cdata->b_typ_beams  , 4 ); vcr_log_str( "\n" );
  vcr_log_str( "has starbase :       -  " ); vcr_log_intn( cdata->p_has_base    , 4  ); vcr_log_str( "\n" );
  vcr_log_str( "pl. beamtype :       -  " ); vcr_log_intn( cdata->p_typ_beams   , 4  ); vcr_log_str( "\n" );
  vcr_log_str( "pl. defense  :       -  " ); vcr_log_intn( cdata->p_nmb_pdefense, 4  ); vcr_log_str( "\n" );
  vcr_log_str( "bas defense  :       -  " ); vcr_log_intn( cdata->p_nmb_bdefense, 4  ); vcr_log_str( "\n" );
  vcr_log_str( "bas fighters :       -  " ); vcr_log_intn( cdata->p_nmb_fighter , 4  ); vcr_log_str( "\n" );
  vcr_log_str( "shield bonus :     " ); vcr_log_intn( cdata->g_shibon, 4 ); vcr_log_str( "\n" );
  vcr_log_str( "----------------------------\n"                                             );
}


void vcrc_prepare_fighters( combatdata *cdata )
{
}


void vcrc_prepare_torpedos( combatdata *cdata )
{
}


void vcrc_prepare_beams( combatdata *cdata )
{
}


void vcrc_fight( combatdata *cdata )
{
}

void init_log( void )
{
  GtkTextView *view = GTK_TEXT_VIEW( lookup_widget( "vcr_textview_log" ) );
  vcr_logging_textview_buffer = gtk_text_view_get_buffer( view );
  PangoFontDescription *pfontdesc = pango_font_description_from_string( "Monospace 10" );
  gtk_widget_modify_font( view, pfontdesc );
}

void vcr_log_str( gchar *str )
{
  gtk_text_buffer_insert_at_cursor( vcr_logging_textview_buffer, str, strlen(str) );
}

void vcr_log_strn( gchar *str, gint len )
{
  gtk_text_buffer_insert_at_cursor( vcr_logging_textview_buffer, str, len );
}

void vcr_log_int( gint val )
{
  gint i=1, t=val;
  while( t>9 ) {
    t = t/10;
    i++; }
  vcr_log_intn( val, i );
}

void vcr_log_intn( gint val, gint len )
{
  gint i=1, t=val;
  while( t>9 ) {
    t = t/10;
    i++; }
  for( t=0; t<(len-i); t++ ) vcr_log_str( " " );
  gchar *txt = (gchar *)g_malloc((i+1)*sizeof(gchar));
  g_snprintf( txt, i+1, "%d", val );
  vcr_log_strn( txt, i );
  g_free( txt );
}

