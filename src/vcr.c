
#include <gnome.h>
#include <math.h>
#include <string.h>

#include "callbacks.h"
#include "global.h"
#include "support.h"
#include "vcr.h"
#include "gwp-ship.h"
#include "race.h"

#define ASCII_0 48
#define MAXNMBSHIPS 512
/* TODO - try to eliminate as much hardcoded values as possible */
#define MAX_SHIPS_PER_RACE 20
#define NMB_OF_TORPTYPES 10

void vcr_all_init( GtkWidget *widget,
				      gpointer  user_data )
{
  /* show window */
  vcr_show_window( widget, user_data, TRUE );
  /* populate all lists */
  vcr_populate_ship_a_list( widget, user_data );
  vcr_populate_beamspec_lists( widget, user_data );
  vcr_populate_race_lists( widget, user_data );
  vcr_populate_torps_lists( widget, user_data );
  vcr_populate_hull_lists( widget, user_data );
}


void vcr_delete_event( GtkWidget *widget,
				       gpointer  user_data )
{
  /* hide window */
  vcr_show_window( widget, user_data, FALSE );
}


void vcr_show_window( GtkWidget *widget, gpointer  user_data, 
                      gboolean show )
{
  GtkWidget *vcr = lookup_widget( "vcr" );
  if( show )
    gtk_widget_show( vcr );
  else
    gtk_widget_hide( vcr );
}


void vcr_start_combat( GtkWidget *widget, gpointer  user_data )
{
  g_message( "VCR: 3, 2, 1, FIGHT!!!" );
}


void vcr_toggle_starbase( GtkWidget *widget, gpointer  user_data )
{
  GtkWidget *basebutton = lookup_widget( "vcr_checkbutton_base" );
  if( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(basebutton) ) )
    vcr_show_basedata( widget, user_data, TRUE );
  else
    vcr_show_basedata( widget, user_data, FALSE );
}


void vcr_show_basedata( GtkWidget *widget, gpointer  user_data, gboolean show )
{
  GtkWidget *baseframe = lookup_widget( "vcr_frame_base" );
  if( show )
    gtk_widget_show_all( baseframe );
  else
    gtk_widget_hide_all( baseframe );
}


void vcr_set( GtkWidget *widget, gpointer user_data,
              gint target, gint value, gint what, gint setthis )
{
  GtkWidget *scale;
  GtkEntry *entry;
  GtkComboBox *box;

  gchar *setthistxt = (gchar *)g_malloc(64*sizeof(gchar));
  setthistxt[0] = '\0';
  g_snprintf( setthistxt, 63, "%d", setthis );
  

  switch( value )
  {
    case PRC_SHIELD:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_shi_a" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_shi_b" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_shi_p" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case PRC_DAMAGE:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_dam_a" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_dam_b" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case PRC_SHIBON:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_sbo_a" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_sbo_b" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case NMB_TUBEBAY:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_sel_torp_a" ) );
                gtk_entry_set_text( entry, setthistxt );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_sel_torp_b" ) );
                gtk_entry_set_text( entry, setthistxt );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case NMB_TORPFIG:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_trp_a" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
                scale = lookup_widget( "vcr_hscale_trp_a" );
                gtk_range_set_range( GTK_RANGE( scale ), 0, setthis );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_trp_b" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
                scale = lookup_widget( "vcr_hscale_trp_b" );
                gtk_range_set_range( GTK_RANGE( scale ), 0, setthis );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_fig_bas" ) );
                gtk_entry_set_text( entry, setthistxt );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case NMB_CREW:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_cre_a" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
                scale = lookup_widget( "vcr_hscale_cre_a" );
                gtk_range_set_range( GTK_RANGE( scale ), 0, setthis );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_cre_b" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
                scale = lookup_widget( "vcr_hscale_cre_b" );
                gtk_range_set_range( GTK_RANGE( scale ), 0, setthis );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case NMB_BEAMS:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_sel_beam_a" ) );
                gtk_entry_set_text( entry, setthistxt );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_sel_beam_b" ) );
                gtk_entry_set_text( entry, setthistxt );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case NMB_MASS:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case NMB_DEF:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_def_p" ) );
                gtk_entry_set_text( entry, setthistxt );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_def_bas" ) );
                gtk_entry_set_text( entry, setthistxt );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case LVL_ENGINE:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_eng_a" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                scale = lookup_widget( "vcr_hscale_eng_b" );
                gtk_range_set_value( GTK_RANGE( scale ), setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case LVL_BEAM:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_a" ) );
                gtk_combo_box_set_active( box, setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_b" ) );
                gtk_combo_box_set_active( box, setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_bea_bas" ) );
                gtk_combo_box_set_active( box, setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case LVL_TORP:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_a" ) );
                gtk_combo_box_set_active( box, setthis );
                break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_b" ) );
                gtk_combo_box_set_active( box, setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case TYP_RACE:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_race_a" ) );
                gtk_combo_box_set_active( box, setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_race_b" ) );
                gtk_combo_box_set_active( box, setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_race_p" ) );
                gtk_combo_box_set_active( box, setthis );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case TYP_HULL:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    case TYP_ID:
      switch( target )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d )", target, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
          break;
      }
      break;
    default:
      g_message( "VCR: TODO: vcr_set( %d, %d, %d ) - DEFAULT", target, value, what );
      break;
  }
  g_free( setthistxt );
}








gint vcr_get( GtkWidget *widget, gpointer user_data,
              gint source, gint value, gint what )
{
  gint retval = 0;
  GtkRange *range;
  GtkEntry *entry;
  GtkComboBox *box;

  switch( value )
  {
    case PRC_SHIELD:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_shi_a" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_shi_b" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case PRC_DAMAGE:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_dam_a" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_dam_b" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case PRC_SHIBON:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_sbo_a" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_sbo_b" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case NMB_TUBEBAY:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_sel_torp_a" ) );
                retval = str2int( gtk_entry_get_text( entry ) );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_sel_torp_b" ) );
                retval = str2int( gtk_entry_get_text( entry ) );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case NMB_TORPFIG:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_trp_a" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_trp_b" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                entry = GTK_ENTRY( lookup_widget( "vcr_entry_fig_bas" ) );
                retval = str2int( gtk_entry_get_text( entry ) );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case NMB_CREW:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_cre_a" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                range = GTK_RANGE( lookup_widget( "vcr_hscale_cre_b" ) );
                retval = (gint)gtk_range_get_value( range );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case NMB_BEAMS:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case NMB_DEF:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case NMB_MASS:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case LVL_ENGINE:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case LVL_BEAM:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case LVL_TORP:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case TYP_RACE:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_race_a" ) );
                retval = gtk_combo_box_get_active( box );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_race_b" ) );
                retval = gtk_combo_box_get_active( box );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_race_p" ) );
                retval = gtk_combo_box_get_active( box );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case TYP_HULL:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    case TYP_ID:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case SHIP_B:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case PLANET:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        case BASE:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_MAX:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            default:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
              break;
          }
          break;
        default:
          g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
          break;
      }
      break;
    default:
      g_message( "VCR: TODO: vcr_get( %d, %d, %d ) - DEFAULT", source, value, what );
      break;
  }
  return( retval );
}


void vcr_populate_ship_a_list( GtkWidget *widget, gpointer user_data )
{
  gchar *name;
  gint *idlist;
  static void foreach_func( gpointer key, gpointer value, gpointer user_data );

  name = (gchar *)g_malloc(64*sizeof(gchar));
  idlist = (gint *)g_malloc(MAXNMBSHIPS*sizeof(gint));

  /* idlist[0] stores the number of stored values */
  idlist[0] = 0;

  GtkWidget *combox = lookup_widget("vcr_comboboxentry_sel_ext_shp_a");
  g_object_set_data(G_OBJECT(combox), "shipidlist", idlist );

  void foreach_func( gpointer key, gpointer value, gpointer user_data )
  {
    GwpShip *ship = GWP_SHIP( value );
    GtkComboBox *box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_ext_shp_a" ) );
    gint *idlist = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_ext_shp_a")), "shipidlist");
    gint curr = idlist[0];

    if( gwp_ship_is_mine( ship ) )
    {
      curr++;
      idlist[curr] = gwp_object_get_id( GWP_OBJECT(ship) );
      idlist[0]++;
      g_sprintf( name, "%03d: ", idlist[curr] );
      strncat( name, gwp_object_get_name (GWP_OBJECT(ship))->str, 50 );
      gtk_combo_box_append_text( box, name );
    }
  }

  g_hash_table_foreach( ship_list, (GHFunc) foreach_func, user_data );

  g_free( name );
}


void vcr_populate_beamspec_lists( GtkWidget *widget, gpointer user_data )
{
  gint i, n;
  GwpBeamSpec *beams;
  GtkComboBox *box;

  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_a" ) );
  gtk_combo_box_append_text( box, "none" );
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_b" ) );
  gtk_combo_box_append_text( box, "none" );
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
  n = g_slist_length( beamspec_list );
  for( i=0; i<n; i++ )
  {
	beams = GWP_BEAMSPEC( g_slist_nth_data( beamspec_list, i ) );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_a" ) );
    gtk_combo_box_append_text( box, gwp_beamspec_get_name( beams )->str );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_b" ) );
    gtk_combo_box_append_text( box, gwp_beamspec_get_name( beams )->str );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_bea_bas" ) );
    gtk_combo_box_append_text( box, gwp_beamspec_get_name( beams )->str );
  }
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_bea_bas" ) );
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
}


void vcr_populate_race_lists( GtkWidget *widget, gpointer user_data )
{
  gint i;
  GtkComboBox *box;

  i = 0;
  while( race_get_name( i ) )
  {
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_race_a" ) );
    gtk_combo_box_append_text( box, race_get_name( i ) );
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_race_b" ) );
    gtk_combo_box_append_text( box, race_get_name( i ) );
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_race_p" ) );
    gtk_combo_box_append_text( box, race_get_name( i ) );
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
    i++;
  }
}


void vcr_populate_torps_lists( GtkWidget *widget, gpointer user_data )
{
  gint i, n;
  GwpTorpSpec *torp;
  GtkComboBox *box;

  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_a" ) );
  gtk_combo_box_append_text( box, "none" );
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_b" ) );
  gtk_combo_box_append_text( box, "none" );
  n = g_slist_length( torpspec_list );
  for( i=0; i<n; i++ )
  {
	torp = GWP_TORPSPEC( g_slist_nth_data( torpspec_list, i ) );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_a" ) );
    gtk_combo_box_append_text( box, gwp_torpspec_get_name( torp )->str );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_b" ) );
    gtk_combo_box_append_text( box, gwp_torpspec_get_name( torp )->str );
  }
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_a" ) );
  gtk_combo_box_append_text( box, "Fighters" );
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_b" ) );
  gtk_combo_box_append_text( box, "Fighters" );
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
}


void vcr_populate_hull_lists( GtkWidget *widget, gpointer user_data )
{
  GtkComboBox *box;

  gint *nmb1 = (gint *)g_malloc(1*sizeof( gint ));
  nmb1[0] = 1;
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_a" ) );
  gtk_combo_box_append_text( box, "none" );
  g_object_set_data( G_OBJECT( box ), "nmb_of_hulls", nmb1 );
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );


  gint *nmb2 = (gint *)g_malloc(1*sizeof( gint ));
  nmb2[0] = 1;
  box = GTK_COMBO_BOX_ENTRY( lookup_widget( "vcr_comboboxentry_sel_type_b" ) );
  gtk_combo_box_append_text( GTK_COMBO_BOX( box ), "none" );
  g_object_set_data( G_OBJECT( box ), "nmb_of_hulls", nmb2 );
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );

}


void vcr_ship_a_selected( GtkWidget *widget, gpointer user_data )
{
  GtkComboBoxEntry *entry;
  GwpShip *ship;

  entry = GTK_COMBO_BOX_ENTRY( lookup_widget( "vcr_comboboxentry_sel_ext_shp_a" ) );

  gint *idlist = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_ext_shp_a")), "shipidlist");
  gint selected = gtk_combo_box_get_active( GTK_COMBO_BOX( entry ) );

//  ship = GWP_SHIP( g_hash_table_lookup( ship_list, (gconstpointer)(selected+1) ) );
  ship = gwp_ship_get(ship_list, idlist[(selected+1)] );
  if( ship==NULL )
    g_message( "## ERROR: gwp_ship_get returned NULL" );

/* TODO 
  vcr_set( widget, user_data, SHIP_A, TYP_HULL, VAL_CUR, 
  vcr_set( widget, user_data, SHIP_A, PRC_SHIBON, VAL_CUR, 0 );
 */
  vcr_set( widget, user_data, SHIP_A, PRC_SHIELD, VAL_CUR, 100 );
  vcr_set( widget, user_data, SHIP_A, NMB_CREW, VAL_MAX, gwp_ship_get_hull_crew( ship ) );
  vcr_set( widget, user_data, SHIP_A, NMB_CREW, VAL_CUR, gwp_ship_get_crew( ship )  );
  vcr_set( widget, user_data, SHIP_A, PRC_DAMAGE, VAL_CUR, gwp_ship_get_damage( ship ) );
  if( gwp_ship_has_torp_weapons( ship ) )
  {
    vcr_set( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_CUR, gwp_ship_get_torps_launchers( ship ) );
    vcr_set( widget, user_data, SHIP_A, NMB_TORPFIG, VAL_CUR, gwp_ship_get_torps_launchers( ship ) );
    vcr_set( widget, user_data, SHIP_A, LVL_TORP, VAL_CUR, gwp_ship_get_torps_type( ship ) );
  }
  else
  {
    vcr_set( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_CUR, gwp_ship_get_fighter_bays( ship ) );
    vcr_set( widget, user_data, SHIP_A, NMB_TORPFIG, VAL_CUR, gwp_ship_get_fighters( ship ) );
/* TODO: exchange hardcoded values of "fighters" and "none" entries in list */
    if( gwp_ship_get_fighter_bays( ship ) > 0 )
      vcr_set( widget, user_data, SHIP_A, LVL_TORP, VAL_CUR, 11 );
    else
      vcr_set( widget, user_data, SHIP_A, LVL_TORP, VAL_CUR, 0 );
  }
  vcr_set( widget, user_data, SHIP_A, NMB_BEAMS, VAL_CUR, gwp_ship_get_beams( ship ) );
  vcr_set( widget, user_data, SHIP_A, NMB_TORPFIG, VAL_MAX,gwp_ship_get_hull_cargo( ship )  );
  vcr_set( widget, user_data, SHIP_A, LVL_BEAM, VAL_CUR, gwp_ship_get_beams_type( ship ) );
  vcr_set( widget, user_data, SHIP_A, TYP_RACE, VAL_CUR, gwp_ship_get_owner( ship ) );
  vcr_set( widget, user_data, SHIP_A, LVL_ENGINE, VAL_CUR, gwp_ship_get_engines_type( ship )+1 );
}


void vcr_ship_b_race_selected( GtkWidget *widget, gpointer user_data )
{
  gint i, id, race;
  GwpHullSpec *hull;
  GtkComboBox *box;
  gint *nmbpt;

  /* find out what race was selected */
  race = vcr_get( widget, user_data, SHIP_B, TYP_RACE, VAL_CUR ) - 1;
  g_message( "selected race is : %d", race );

  /*
   * Fill The Hulls
   */
  /* find out how many entries are (at least "should be") in hulls-list */
  nmbpt = (gint *)g_object_get_data(
    G_OBJECT(lookup_widget("vcr_comboboxentry_sel_type_a")), "nmb_of_hulls" );

  /* make sure this function is not called too early */
  if( nmbpt == NULL )
  {
    g_message( "# Warning: vcr_ship_b_race_selected() called too early" );
    return;
  }
  else
    g_message( "+++ race b selected ok" );


  /* clear hulls-list */
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_b" ) );
  for( i=0; i<nmbpt[0]; i++ )
    gtk_combo_box_remove_text( box, 0 );
  nmbpt[0] = 0;

  /* fill ship-type list with race specific hulls */
  if( race < 0 )
  {
    /* TODO */
    /* maybe selecting 'none' as race should
       show all possible hulls for all races
    */
  }
  else
  {
    i = 0;
    id = truehull[race][i];
    do {
      hull = GWP_HULLSPEC( g_slist_nth_data( hullspec_list, id-1 ) );
      gtk_combo_box_append_text( box, gwp_hullspec_get_name_trunc( hull, 18 )->str );
      nmbpt[0]++;
      i++;
      id = truehull[race][i];
    } while( id>0 && i< MAX_SHIPS_PER_RACE );
  }
  gtk_combo_box_set_active( box, 0 );
}


gint str2int( char *str )
{
  gint val = 0;
  gint sign = 1;
  gint i = 0;

  if( str[i] == '-' ) {
    sign = -1;
    i++; }

  while( str[i]-ASCII_0 >= 0 && str[i]-ASCII_0 <= 9 ) {
      val = val*10 + (str[i]-ASCII_0);
      i++; }

  return( val*sign );
}



