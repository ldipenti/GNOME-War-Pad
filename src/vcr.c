
#include <gnome.h>
#include <math.h>
#include <string.h>

#include "callbacks.h"
#include "global.h"
#include "support.h"
#include "vcr.h"

void vcr_all_init( GtkWidget *widget,
				      gpointer  user_data )
{
  /* show window */
  vcr_show_window( widget, user_data, TRUE );
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
  GtkWidget *entry;
  GtkWidget *box;

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
                entry = lookup_widget( "vcr_entry_sel_torp_a" );
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
                entry = lookup_widget( "vcr_entry_sel_torp_b" );
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
                entry = lookup_widget( "vcr_entry_fig_bas" );
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
                entry = lookup_widget( "vcr_entry_sel_beam_a" );
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
                entry = lookup_widget( "vcr_entry_sel_beam_b" );
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
                entry = lookup_widget( "vcr_entry_def_p" );
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
                entry = lookup_widget( "vcr_entry_def_bas" );
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
                box = lookup_widget( "vcr_comboboxentry_sel_beam_a" );
                gtk_combo_box_set_active( GTK_COMBO_BOX( box ), setthis );
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
                box = lookup_widget( "vcr_comboboxentry_sel_beam_b" );
                gtk_combo_box_set_active( GTK_COMBO_BOX( box ), setthis );
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
                box = lookup_widget( "vcr_comboboxentry_bea_bas" );
                gtk_combo_box_set_active( GTK_COMBO_BOX( box ), setthis );
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
                box = lookup_widget( "vcr_comboboxentry_sel_torp_a" );
                gtk_combo_box_set_active( GTK_COMBO_BOX( box ), setthis );
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
                box = lookup_widget( "vcr_comboboxentry_sel_torp_b" );
                gtk_combo_box_set_active( GTK_COMBO_BOX( box ), setthis );
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
                box = lookup_widget( "vcr_comboboxentry_sel_race_a" );
                gtk_combo_box_set_active( GTK_COMBO_BOX( box ), setthis );
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
                box = lookup_widget( "vcr_comboboxentry_sel_race_b" );
                gtk_combo_box_set_active( GTK_COMBO_BOX( box ), setthis );
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
                box = lookup_widget( "vcr_comboboxentry_race_p" );
                gtk_combo_box_set_active( GTK_COMBO_BOX( box ), setthis );
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




