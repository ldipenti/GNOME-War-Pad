
#include "vcr.h"


#define MAXNMBSHIPS 512

/* TODO - try to eliminate as much hardcoded values as possible */
#define MAX_SHIPS_PER_RACE 20
#define NMB_OF_TORPTYPES 10
#define NMB_OF_BEAMTYPES 10

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
  vcr_populate_vcr_lists( widget, user_data );
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
  /* let's get it on ... */
  g_message( "VCR: 3, 2, 1, FIGHT!!!" );

  /* fill the data struct with battle values */
  combatdata cdata;

  /*
   *     GLOBAL
   */
  cdata.g_combat_is_vcr = 0;
  cdata.g_shibon = vcr_get( widget, user_data, SHIP_A, PRC_SHIBON, VAL_CUR );
  cdata.g_a_is_ship = 1;
  cdata.g_random_seed = -1; /* -1 means the random seed is generated later */

  /*
   *     SIDE A
   */
  cdata.a_shield = vcr_get( widget, user_data, SHIP_A, PRC_SHIELD, VAL_CUR );
  cdata.a_hull = 100 - vcr_get( widget, user_data, SHIP_A, PRC_DAMAGE, VAL_CUR );
  cdata.a_crew = vcr_get( widget, user_data, SHIP_A, NMB_CREW, VAL_CUR );
  cdata.a_typ_hull = vcr_get( widget, user_data, SHIP_A, HULL_ID, VAL_CUR );
  cdata.a_nmb_beams = vcr_get( widget, user_data, SHIP_A, NMB_BEAMS, VAL_CUR );
  cdata.a_typ_beams = vcr_get( widget, user_data, SHIP_A, LVL_BEAM, VAL_CUR );
  cdata.a_typ_engines = vcr_get( widget, user_data, SHIP_A, LVL_ENGINE, VAL_CUR );
  /* differentiate between torpedo and fighter ships */
  if( vcr_get( widget, user_data, SHIP_A, LVL_TORP, VAL_CUR ) > NMB_OF_TORPTYPES )
  {
    /* fighter carrier type */
    cdata.a_nmb_fighter = vcr_get( widget, user_data, SHIP_A, NMB_TORPFIG, VAL_CUR );
    cdata.a_nmb_bays = vcr_get( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_CUR );
    cdata.a_nmb_torps = 0;
    cdata.a_nmb_tubes = 0;
    cdata.a_typ_torps = 0;
  } else {
    /* torpedo tube type */
    cdata.a_nmb_fighter = 0;
    cdata.a_nmb_bays = 0;
    cdata.a_nmb_torps = vcr_get( widget, user_data, SHIP_A, NMB_TORPFIG, VAL_CUR );
    cdata.a_nmb_tubes = vcr_get( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_CUR );
    cdata.a_typ_torps = vcr_get( widget, user_data, SHIP_A, LVL_TORP, VAL_CUR );
  }

  /*
   *     SIDE B
   */
  if( vcr_planet_selected( widget, user_data ) == 1 )
  {
    /* side b is a planet with or without starbase */
    cdata.g_b_is_ship = 0;
    cdata.p_has_base = vcr_base_selected( widget, user_data ) ? 1 : 0;
    cdata.p_typ_beams = vcr_get( widget, user_data, BASE, LVL_BEAM, VAL_CUR );
    cdata.p_nmb_pdefense = vcr_get( widget, user_data, PLANET, NMB_DEF, VAL_CUR );
    cdata.p_nmb_bdefense = vcr_get( widget, user_data, BASE, NMB_DEF, VAL_CUR );
    cdata.p_nmb_fighter = vcr_get( widget, user_data, BASE, NMB_TORPFIG, VAL_CUR );
    cdata.b_shield = vcr_get( widget, user_data, PLANET, PRC_SHIELD, VAL_CUR );
    cdata.b_hull = 100; // TODO ... maybe allowing damage ...
    cdata.b_crew = 0;
    cdata.b_typ_hull = 0;
    cdata.b_nmb_beams = 0;
    cdata.b_typ_beams = 0;
    cdata.b_nmb_fighter = 0;
    cdata.b_nmb_bays = 0;
    cdata.b_nmb_torps = 0;
    cdata.b_nmb_tubes = 0;
    cdata.b_typ_torps = 0;
  } else {
    /* side b is a ship */
    cdata.g_b_is_ship = 1;
    cdata.b_shield = vcr_get( widget, user_data, SHIP_B, PRC_SHIELD, VAL_CUR );
    cdata.b_hull = 100 - vcr_get( widget, user_data, SHIP_B, PRC_DAMAGE, VAL_CUR );
    cdata.b_crew = vcr_get( widget, user_data, SHIP_B, NMB_CREW, VAL_CUR );
    cdata.b_typ_hull = vcr_get( widget, user_data, SHIP_B, HULL_ID, VAL_CUR );
    cdata.b_nmb_beams = vcr_get( widget, user_data, SHIP_B, NMB_BEAMS, VAL_CUR );
    cdata.b_typ_beams = vcr_get( widget, user_data, SHIP_B, LVL_BEAM, VAL_CUR );
    cdata.b_typ_engines = vcr_get( widget, user_data, SHIP_B, LVL_ENGINE, VAL_CUR );
    if( vcr_get( widget, user_data, SHIP_B, LVL_TORP, VAL_CUR ) > NMB_OF_TORPTYPES )
    {
      /* fighter carrier type */
      cdata.b_nmb_fighter = vcr_get( widget, user_data, SHIP_B, NMB_TORPFIG, VAL_CUR );
      cdata.b_nmb_bays = vcr_get( widget, user_data, SHIP_B, NMB_TUBEBAY, VAL_CUR );
      cdata.b_nmb_torps = 0;
      cdata.b_nmb_tubes = 0;
      cdata.b_typ_torps = 0;
    } else {
      /* torpedo tube type */
      cdata.b_nmb_fighter = 0;
      cdata.b_nmb_bays = 0;
      cdata.b_nmb_torps = vcr_get( widget, user_data, SHIP_B, NMB_TORPFIG, VAL_CUR );
      cdata.b_nmb_tubes = vcr_get( widget, user_data, SHIP_B, NMB_TUBEBAY, VAL_CUR );
      cdata.b_typ_torps = vcr_get( widget, user_data, SHIP_B, LVL_TORP, VAL_CUR );
    }
    cdata.p_has_base = 0;
    cdata.p_typ_beams = 0;
    cdata.p_nmb_pdefense = 0;
    cdata.p_nmb_bdefense = 0;
    cdata.p_nmb_fighter = 0;
  }

  /* try to start combat */
  vcrc_combat_start( &cdata );
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
  GtkComboBox *box;
  GtkSpinButton *spin;
  gdouble min, cur, max;

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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_torp_a" ) );
                gtk_spin_button_get_range( spin, &min, &max );
                cur = gtk_spin_button_get_value( spin );
                gtk_spin_button_set_range( spin, setthis, max );
                gtk_spin_button_set_value( spin, cur );
              break;
            case VAL_CUR:
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_torp_a" ) );
                gtk_spin_button_set_value( spin, setthis );
              break;
            case VAL_MAX:
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_torp_a" ) );
                gtk_spin_button_get_range( spin, &min, &max );
                cur = gtk_spin_button_get_value( spin );
                gtk_spin_button_set_range( spin, min, setthis );
                gtk_spin_button_set_value( spin, cur );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_torp_b" ) );
                gtk_spin_button_get_range( spin, &min, &max );
                cur = gtk_spin_button_get_value( spin );
                gtk_spin_button_set_range( spin, setthis, max );
                gtk_spin_button_set_value( spin, cur );
              break;
            case VAL_CUR:
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_torp_b" ) );
                gtk_spin_button_set_value( spin, setthis );
              break;
            case VAL_MAX:
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_torp_b" ) );
                gtk_spin_button_get_range( spin, &min, &max );
                cur = gtk_spin_button_get_value( spin );
                gtk_spin_button_set_range( spin, min, setthis );
                gtk_spin_button_set_value( spin, cur );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_bas_fig" ) );
                gtk_spin_button_set_value( spin, setthis );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_beam_a" ) );
                gtk_spin_button_get_range( spin, &min, &max );
                cur = gtk_spin_button_get_value( spin );
                gtk_spin_button_set_range( spin, setthis, max );
                gtk_spin_button_set_value( spin, cur );
              break;
            case VAL_CUR:
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_beam_a" ) );
                gtk_spin_button_set_value( spin, setthis );
              break;
            case VAL_MAX:
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_beam_a" ) );
                gtk_spin_button_get_range( spin, &min, &max );
                cur = gtk_spin_button_get_value( spin );
                gtk_spin_button_set_range( spin, min, setthis );
                gtk_spin_button_set_value( spin, cur );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_beam_b" ) );
                gtk_spin_button_get_range( spin, &min, &max );
                cur = gtk_spin_button_get_value( spin );
                gtk_spin_button_set_range( spin, setthis, max );
                gtk_spin_button_set_value( spin, cur );
              break;
            case VAL_CUR:
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_beam_b" ) );
                gtk_spin_button_set_value( spin, setthis );
              break;
            case VAL_MAX:
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_beam_b" ) );
                gtk_spin_button_get_range( spin, &min, &max );
                cur = gtk_spin_button_get_value( spin );
                gtk_spin_button_set_range( spin, min, setthis );
                gtk_spin_button_set_value( spin, cur );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_pla_def" ) );
                gtk_spin_button_set_value( spin, setthis );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_bas_def" ) );
                gtk_spin_button_set_value( spin, setthis );
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
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_a" ) );
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
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_b" ) );
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
  GtkComboBox *box;
  GtkSpinButton *spin;
  gint *idlist, selected;

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
                range = GTK_RANGE( lookup_widget( "vcr_hscale_shi_p" ) );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_torp_a" ) );
                retval = gtk_spin_button_get_value( spin );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_torp_b" ) );
                retval = gtk_spin_button_get_value( spin );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_bas_fig" ) );
                retval = gtk_spin_button_get_value( spin );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_beam_a" ) );
                retval = gtk_spin_button_get_value( spin );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_sel_beam_b" ) );
                retval = gtk_spin_button_get_value( spin );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_pla_def" ) );
                retval = gtk_spin_button_get_value( spin );
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
                spin = GTK_SPIN_BUTTON( lookup_widget( "vcr_spinbutton_bas_def" ) );
                retval = gtk_spin_button_get_value( spin );
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
                range = GTK_RANGE( lookup_widget( "vcr_hscale_eng_a" ) );
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
                range = GTK_RANGE( lookup_widget( "vcr_hscale_eng_b" ) );
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
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_a" ) );
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
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_b" ) );
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
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_bea_bas" ) );
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
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_a" ) );
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
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_b" ) );
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
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_a" ) );
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
                box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_b" ) );
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
    case HULL_ID:
      switch( source )
      {
        case SHIP_A:
          switch( what )
          {
            case VAL_MIN:
              g_message( "VCR: TODO: vcr_get( %d, %d, %d )", source, value, what );
              break;
            case VAL_CUR:
                idlist = (gint *)g_object_get_data(
                  G_OBJECT(lookup_widget("vcr_comboboxentry_sel_type_a")), "id-list" );
                selected = vcr_get( widget, user_data, SHIP_A, TYP_HULL, VAL_CUR );
                if( selected >= 0 ) // && idlist[0] > 1 )
                  retval = idlist[selected+1];
                else
                  retval = 0;
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
                idlist = (gint *)g_object_get_data(
                  G_OBJECT(lookup_widget("vcr_comboboxentry_sel_type_b")), "id-list" );
                selected = vcr_get( widget, user_data, SHIP_B, TYP_HULL, VAL_CUR );
                if( selected >= 0 ) // && idlist[0] > 1 )
                  retval = idlist[selected+1];
                else
                  retval = 0;
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

  /* test if list is already populated */
  idlist = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_ext_shp_a")), "shipidlist");
  if( idlist )
    return;
  
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
      strncat( name, gwp_object_get_name (GWP_OBJECT(ship)), 50 );
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
  gint *idlista, *idlistb, *idlistp;

  /* test if list of ship a is already populated before populating */
  idlista = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_beam_a")), "beamidlist");
  if( !idlista )
  {
    /* idlista[0] stores the number of stored values */
    idlista = (gint *)g_malloc( 1*sizeof(gint) );
    idlista[0] = 0;
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_a" ) );
    g_object_set_data( G_OBJECT( box ), "beamidlist", idlista );

    gtk_combo_box_append_text( box, "none" );
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
    idlista[0]++;

    n = g_slist_length( beamspec_list );
    for( i=0; i<n; i++ )
    {
      beams = GWP_BEAMSPEC( g_slist_nth_data( beamspec_list, i ) );
      gtk_combo_box_append_text( box, gwp_beamspec_get_name( beams ) );
      idlista[0]++;
    }
  }

  /* test if list of ship b is already populated before populating */
  idlistb = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_beam_b")), "beamidlist");
  if( !idlistb )
  {
    /* idlistb[0] stores the number of stored values */
    idlistb = (gint *)g_malloc( 1*sizeof(gint) );
    idlistb[0] = 0;
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_beam_b" ) );
    g_object_set_data( G_OBJECT( box ), "beamidlist", idlistb );

    gtk_combo_box_append_text( box, "none" );
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
    idlistb[0]++;

    n = g_slist_length( beamspec_list );
    for( i=0; i<n; i++ )
    {
      beams = GWP_BEAMSPEC( g_slist_nth_data( beamspec_list, i ) );
      gtk_combo_box_append_text( box, gwp_beamspec_get_name( beams ) );
      idlistb[0]++;
    }
  }

  /* test if list of planet/base is already populated before populating */
  idlistp = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_bea_bas")), "beamidlist");
  if( !idlistp )
  {
    /* idlistp[0] stores the number of stored values */
    idlistp = (gint *)g_malloc( 1*sizeof(gint) );
    idlistp[0] = 0;
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_bea_bas" ) );
    g_object_set_data( G_OBJECT( box ), "beamidlist", idlistp );

    gtk_combo_box_append_text( box, "none" );
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
    idlistp[0]++;

    n = g_slist_length( beamspec_list );
    for( i=0; i<n; i++ )
    {
      beams = GWP_BEAMSPEC( g_slist_nth_data( beamspec_list, i ) );
      gtk_combo_box_append_text( box, gwp_beamspec_get_name( beams ) );
      idlistp[0]++;
    }
  }
}


void vcr_populate_race_lists( GtkWidget *widget, gpointer user_data )
{
  GtkComboBox *box;
  gint *idlista, *idlistb, *idlistp;

  /* test if list of race a is already populated before populating */
  idlista = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_race_a")), "raceidlist");
  if( !idlista )
  {
    /* idlista[0] stores the number of stored values */
    idlista = (gint *)g_malloc( 1*sizeof(gint) );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_race_a" ) );
    g_object_set_data( G_OBJECT( box ), "raceidlist", idlista );

    idlista[0] = 0;
    while( race_get_name( idlista[0] ) )
    {
      gtk_combo_box_append_text( box, race_get_name( idlista[0] ) );
      idlista[0]++;
    }
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
  }

  /* test if list of race b is already populated before populating */
  idlistb = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_race_b")), "raceidlist");
  if( !idlistb )
  {
    /* idlistb[0] stores the number of stored values */
    idlistb = (gint *)g_malloc( 1*sizeof(gint) );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_race_b" ) );
    g_object_set_data( G_OBJECT( box ), "raceidlist", idlistb );

    idlistb[0] = 0;
    while( race_get_name( idlistb[0] ) )
    {
      gtk_combo_box_append_text( box, race_get_name( idlistb[0] ) );
      idlistb[0]++;
    }
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
  }

  /* test if list of race on planet is already populated before populating */
  idlistp = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_race_p")), "raceidlist");
  if( !idlistp )
  {
    /* idlistp[0] stores the number of stored values */
    idlistp = (gint *)g_malloc( 1*sizeof(gint) );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_race_p" ) );
    g_object_set_data( G_OBJECT( box ), "raceidlist", idlistp );

    idlistp[0] = 0;
    while( race_get_name( idlistp[0] ) )
    {
      gtk_combo_box_append_text( box, race_get_name( idlistp[0] ) );
      idlistp[0]++;
    }
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
  }
}


void vcr_populate_torps_lists( GtkWidget *widget, gpointer user_data )
{
  gint i, n;
  GwpTorpSpec *torp;
  GtkComboBox *box;


  gint *idlista, *idlistb;

  /* test if list of race a is already populated before populating */
  idlista = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_torp_a")), "torpidlist");
  if( !idlista )
  {
    /* idlista[0] stores the number of stored values */
    idlista = (gint *)g_malloc( 1*sizeof(gint) );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_a" ) );
    g_object_set_data( G_OBJECT( box ), "torpidlist", idlista );

    idlista[0] = 0;
    gtk_combo_box_append_text( box, "none" );
    n = g_slist_length( torpspec_list );
    for( i=0; i<n; i++ )
    {
      torp = GWP_TORPSPEC( g_slist_nth_data( torpspec_list, i ) );
      gtk_combo_box_append_text( box, gwp_torpspec_get_name( torp ) );
      idlista[0]++;
    }
    gtk_combo_box_append_text( box, "Fighters" );
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
  }

  /* test if list of race a is already populated before populating */
  idlistb = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_torp_b")), "torpidlist");
  if( !idlistb )
  {
    /* idlistb[0] stores the number of stored values */
    idlistb = (gint *)g_malloc( 1*sizeof(gint) );
    box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_torp_b" ) );
    g_object_set_data( G_OBJECT( box ), "torpidlist", idlistb );

    idlistb[0] = 0;
    gtk_combo_box_append_text( box, "none" );
    n = g_slist_length( torpspec_list );
    for( i=0; i<n; i++ )
    {
      torp = GWP_TORPSPEC( g_slist_nth_data( torpspec_list, i ) );
      gtk_combo_box_append_text( box, gwp_torpspec_get_name( torp ) );
      idlistb[0]++;
    }
    gtk_combo_box_append_text( box, "Fighters" );
    gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
  }
}


void vcr_populate_hull_lists( GtkWidget *widget, gpointer user_data )
{
  GtkComboBox *box;

  gint *nmb1 = (gint *)g_malloc(MAX_SHIPS_PER_RACE*sizeof( gint ));
  nmb1[0] =  1; // one entry in list, which will be "none"
  nmb1[1] = -1; // id of "none"
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_a" ) );
  gtk_combo_box_append_text( box, "none" );
  g_object_set_data( G_OBJECT( box ), "id-list", nmb1 );
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );


  gint *nmb2 = (gint *)g_malloc(MAX_SHIPS_PER_RACE*sizeof( gint ));
  nmb2[0] =  1; // one entry in list, which will be "none"
  nmb2[1] = -1; // id of "none"
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_b" ) );
  gtk_combo_box_append_text( GTK_COMBO_BOX( box ), "none" );
  g_object_set_data( G_OBJECT( box ), "id-list", nmb2 );
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
}


void vcr_populate_vcr_lists( GtkWidget *widget, gpointer user_data )
{
  gint i, n;
  GtkComboBox *box;
  GString *name;
  GString *title = g_string_new( NULL );
  GwpVCRFile *vcrfile = (GwpVCRFile *)gwp_vcrfile_new();
  gwp_vcrfile_read( vcrfile );

  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_vcr" ) );

  gtk_combo_box_append_text( box, "custom simulation" );
  n = gwp_vcrfile_get_number_of_combats( vcrfile );

  for( i=1; i<=n; i++ )
  {
    gwp_vcrfile_set_current_combat( vcrfile, i );
    g_string_truncate( title, 0 );
    g_string_append( title, gwp_vcrfile_get_shipname( vcrfile, VCRC_SIDE_A ) );
    g_string_append( title, "  VS.  " );
    g_string_append( title, gwp_vcrfile_get_shipname( vcrfile, VCRC_SIDE_B ) );
    gtk_combo_box_append_text( box, title->str );
  }
  gtk_combo_box_set_active( GTK_COMBO_BOX( box ), 0 );
}


void vcr_ship_a_selected( GtkWidget *widget, gpointer user_data )
{
  GtkComboBoxEntry *entry;
  GwpShip *ship;
  gint *idlist;
  gint i, type;

  entry = GTK_COMBO_BOX_ENTRY( lookup_widget( "vcr_comboboxentry_sel_ext_shp_a" ) );

  idlist = (gint *)g_object_get_data(G_OBJECT(lookup_widget("vcr_comboboxentry_sel_ext_shp_a")), "shipidlist");
  gint selected = gtk_combo_box_get_active( GTK_COMBO_BOX( entry ) );

  ship = gwp_ship_get(ship_list, idlist[(selected+1)] );
  if( ship==NULL )
    g_message( "## ERROR: gwp_ship_get returned NULL" );

/* TODO 
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
    if( gwp_ship_get_fighter_bays( ship ) > 0 )
      vcr_set( widget, user_data, SHIP_A, LVL_TORP, VAL_CUR, NMB_OF_TORPTYPES + 1 );
    else
      vcr_set( widget, user_data, SHIP_A, LVL_TORP, VAL_CUR, 0 );
  }


  /* update all gui stuff to show ships values */
  vcr_set( widget, user_data, SHIP_A, TYP_RACE, VAL_CUR, gwp_ship_get_owner( ship ) );

  /* prevent this function from being called too early */
  idlist = (gint *)g_object_get_data(
    G_OBJECT(lookup_widget("vcr_comboboxentry_sel_type_a")), "id-list" );
  if( idlist != NULL )
  {
    type = gwp_ship_get_hull_type( ship );
    for( i=1; i<idlist[0]; i++ )
      if( type == idlist[i] )
        vcr_set( widget, user_data, SHIP_A, TYP_HULL, VAL_CUR, i-1 );
  }
  vcr_set( widget, user_data, SHIP_A, NMB_BEAMS, VAL_CUR, gwp_ship_get_beams( ship ) );
  vcr_set( widget, user_data, SHIP_A, NMB_TORPFIG, VAL_MAX,gwp_ship_get_hull_cargo( ship )  );
  vcr_set( widget, user_data, SHIP_A, LVL_BEAM, VAL_CUR, gwp_ship_get_beams_type( ship ) );
  vcr_set( widget, user_data, SHIP_A, LVL_ENGINE, VAL_CUR, gwp_ship_get_engines_type( ship )+1 );
}


void vcr_ship_a_race_selected( GtkWidget *widget, gpointer user_data )
{
  gint i, id, race;
  GwpHullSpec *hull;
  GtkComboBox *box;
  gint *idlist;

  /* find out what race was selected */
  race = vcr_get( widget, user_data, SHIP_A, TYP_RACE, VAL_CUR ) - 1;

  /*
   * Fill The Hulls
   */
  /* find out how many entries are (at least "should be") in hulls-list */
  idlist = (gint *)g_object_get_data(
    G_OBJECT(lookup_widget("vcr_comboboxentry_sel_type_a")), "id-list" );

  /* make sure this function is not called too early */
  if( idlist == NULL )
  {
    g_message( "# Warning: vcr_ship_a_race_selected() called too early" );
    return;
  }


  /* clear hulls-list */
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_a" ) );
  for( i=0; i<idlist[0]; i++ )
    gtk_combo_box_remove_text( box, 0 );
  /* idlist[0] stores the number of listed hulls */
  idlist[0] = 0;

  /* fill ship-type list with race specific hulls */
  if( race < 0 )
  {
    /* TODO */
    /* maybe selecting 'none' as race should
       show all possible hulls for all races
    */
    idlist[0] =  1; // just one entry, called "none"
    idlist[1] = -1; // id of hull "none"
    gtk_combo_box_append_text( box, str2low( "None" ) );
    gtk_combo_box_set_active( box, 0 );
  }
  else
  {
    i = 0;
    id = truehull[race][i];
    do {
      hull = GWP_HULLSPEC( g_slist_nth_data( hullspec_list, id-1 ) );
      gtk_combo_box_append_text( box, str2low( gwp_hullspec_get_name_trunc( hull, 30 ) ) );
      idlist[0]++;
      i++;
      idlist[i] = id;
      id = truehull[race][i];
    } while( id>0 && i< MAX_SHIPS_PER_RACE );
  }
  //  gtk_combo_box_set_active( box, 0 );
}


void vcr_ship_b_race_selected( GtkWidget *widget, gpointer user_data )
{
  gint i, id, race;
  GwpHullSpec *hull;
  GtkComboBox *box;
  gint *idlist;

  /* find out what race was selected */
  race = vcr_get( widget, user_data, SHIP_B, TYP_RACE, VAL_CUR ) - 1;

  /*
   * Fill The Hulls
   */
  /* find out how many entries are (at least "should be") in hulls-list */
  idlist = (gint *)g_object_get_data(
    G_OBJECT(lookup_widget("vcr_comboboxentry_sel_type_b")), "id-list" );

  /* make sure this function is not called too early */
  if( idlist == NULL )
  {
    g_message( "# Warning: vcr_ship_b_race_selected() called too early" );
    return;
  }


  /* clear hulls-list */
  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_sel_type_b" ) );
  for( i=0; i<idlist[0]; i++ )
    gtk_combo_box_remove_text( box, 0 );
  /* idlist[0] stores the number of hulls listed */
  idlist[0] = 0;

  /* fill ship-type list with race specific hulls */
  if( race < 0 )
  {
    /* TODO */
    /* maybe selecting 'none' as race should
       show all possible hulls for all races
    */
    idlist[0] =  1; // just one entry, called "none"
    idlist[1] = -1; // id of hull "none"
    gtk_combo_box_append_text( box, str2low( "None" ) );
    gtk_combo_box_set_active( box, 0 );
  }
  else
  {
    i = 0;
    id = truehull[race][i];
    do {
      hull = GWP_HULLSPEC( g_slist_nth_data( hullspec_list, id-1 ) );
      gtk_combo_box_append_text( box, str2low( gwp_hullspec_get_name_trunc( hull, 30 ) ) );
      idlist[0]++;
      i++;
      idlist[i] = id;
      id = truehull[race][i];
    } while( id>0 && i< MAX_SHIPS_PER_RACE );
  }
  //  gtk_combo_box_set_active( box, 0 );
}


void vcr_ship_a_hull_selected( GtkWidget *widget, gpointer user_data )
{
  gint *idlist;
  gint hullid;
  gint selected;
  GwpHullSpec *hull;

  hullid = -1;
  idlist = (gint *)g_object_get_data(
    G_OBJECT(lookup_widget("vcr_comboboxentry_sel_type_a")), "id-list" );

  /* prevent this function from being called too early */
  if( idlist == NULL )
  {
    g_message( "# Warning: vcr_ship_a_hull_selected() called too early" );
    return;
  }

  /* find out what hull has been selected */
  selected = vcr_get( widget, user_data, SHIP_A, TYP_HULL, VAL_CUR );
  if( selected >= 0 )
    hullid = idlist[selected+1];

  /* set maximum values according to selected hull */
  hull = g_slist_nth_data( hullspec_list, hullid-1 );
  if( hull )
  {
    if( gwp_hullspec_get_fighter_bays( hull ) > 0 ) {
      vcr_set( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_MAX, gwp_hullspec_get_fighter_bays( hull ) );
      vcr_set( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_CUR, gwp_hullspec_get_fighter_bays( hull ) );
      vcr_set( widget, user_data, SHIP_A, LVL_TORP, VAL_CUR, NMB_OF_TORPTYPES + 1 );
    }
    else {
      vcr_set( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_MAX, gwp_hullspec_get_torp_launchers( hull ) );
      vcr_set( widget, user_data, SHIP_A, NMB_TUBEBAY, VAL_CUR, gwp_hullspec_get_torp_launchers( hull ) );
    }
    vcr_set( widget, user_data, SHIP_A, NMB_TORPFIG, VAL_MAX, gwp_hullspec_get_cargo( hull ) );
    vcr_set( widget, user_data, SHIP_A, NMB_CREW, VAL_MAX, gwp_hullspec_get_crew( hull ) );
    vcr_set( widget, user_data, SHIP_A, NMB_BEAMS, VAL_MAX, gwp_hullspec_get_beam_weapons( hull ) );
    /* assume a ship in 'good' shape */
    vcr_set( widget, user_data, SHIP_A, NMB_CREW, VAL_CUR, gwp_hullspec_get_crew( hull ) );
    vcr_set( widget, user_data, SHIP_A, NMB_BEAMS, VAL_CUR, gwp_hullspec_get_beam_weapons( hull ) );
  }
}


void vcr_ship_b_hull_selected( GtkWidget *widget, gpointer user_data )
{
  gint *idlist;
  gint hullid;
  gint selected;
  GwpHullSpec *hull;

  hullid = -1;
  idlist = (gint *)g_object_get_data(
    G_OBJECT(lookup_widget("vcr_comboboxentry_sel_type_b")), "id-list" );

  /* prevent this function from being called too early */
  if( idlist == NULL )
  {
    g_message( "# Warning: vcr_ship_b_hull_selected() called too early" );
    return;
  }

  /* find out what hull has been selected */
  selected = vcr_get( widget, user_data, SHIP_B, TYP_HULL, VAL_CUR );
  if( selected >= 0 )
    hullid = idlist[selected+1];

  /* set maximum values according to selected hull */
  hull = g_slist_nth_data( hullspec_list, hullid-1 );
  if( hull )
  {
    if( gwp_hullspec_get_fighter_bays( hull ) > 0 ) {
      vcr_set( widget, user_data, SHIP_B, NMB_TUBEBAY, VAL_MAX, gwp_hullspec_get_fighter_bays( hull ) );
      vcr_set( widget, user_data, SHIP_B, NMB_TUBEBAY, VAL_CUR, gwp_hullspec_get_fighter_bays( hull ) );
      vcr_set( widget, user_data, SHIP_B, LVL_TORP, VAL_CUR, NMB_OF_TORPTYPES + 1 );
    }
    else {
      vcr_set( widget, user_data, SHIP_B, NMB_TUBEBAY, VAL_MAX, gwp_hullspec_get_torp_launchers( hull ) );
      vcr_set( widget, user_data, SHIP_B, NMB_TUBEBAY, VAL_CUR, gwp_hullspec_get_torp_launchers( hull ) );
    }
    vcr_set( widget, user_data, SHIP_B, NMB_TORPFIG, VAL_MAX, gwp_hullspec_get_cargo( hull ) );
    vcr_set( widget, user_data, SHIP_B, NMB_CREW, VAL_MAX, gwp_hullspec_get_crew( hull ) );
    vcr_set( widget, user_data, SHIP_B, NMB_BEAMS, VAL_MAX, gwp_hullspec_get_beam_weapons( hull ) );
    /* assume a ship in 'good' shape */
    vcr_set( widget, user_data, SHIP_B, NMB_CREW, VAL_CUR, gwp_hullspec_get_crew( hull ) );
    vcr_set( widget, user_data, SHIP_B, NMB_BEAMS, VAL_CUR, gwp_hullspec_get_beam_weapons( hull ) );
  }
}


gboolean vcr_planet_selected( GtkWidget *widget, gpointer user_data )
{
  GtkNotebook *book = GTK_NOTEBOOK( lookup_widget( "vcr_notebook_sel_shppla" ) );
  if( gtk_notebook_get_current_page( book ) == 0 )
    return( FALSE );
  return( TRUE );
}


gboolean vcr_base_selected( GtkWidget *widget, gpointer user_data )
{
  if( vcr_planet_selected( widget, user_data ) )
  {
    GtkCheckButton *button = GTK_CHECK_BUTTON( lookup_widget( "vcr_checkbutton_base" ) );
    return( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( button ) ) );
  }
  return( FALSE );
}


gboolean vcr_record_selected( GtkWidget *widget, gpointer user_data )
{
  gint selected_vcr;
  GtkComboBox *box;
  combatdata cdata;
  GwpVCRFile *vcrfile = (GwpVCRFile *)gwp_vcrfile_new();

  box = GTK_COMBO_BOX( lookup_widget( "vcr_comboboxentry_vcr" ) );
  selected_vcr = gtk_combo_box_get_active( box );

  gwp_vcrfile_set_current_combat( vcrfile, selected_vcr );

  g_message( "TODO: VCR combobox changed to %d", selected_vcr );

  if( selected_vcr <= 0 )
    return( TRUE );
/*
gint gwp_vcrfile_get_random_seed( GwpVCRFile *self );
gboolean gwp_vcrfile_2nd_side_is_planet( GwpVCRFile *self );
gint gwp_vcrfile_get_mass( GwpVCRFile *self, gint side );
gchar* gwp_vcrfile_get_shipname( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_damage( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_shields( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_crew( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_shipid( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_owner( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_type_of_beams( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_beams( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_bays( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_type_of_torpedos( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_torpedos( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_fighters( GwpVCRFile *self, gint side );
gint gwp_vcrfile_get_number_of_tubes( GwpVCRFile *self, gint side );
*/

  cdata.g_combat_is_vcr = 1;
  cdata.g_random_seed     = gwp_vcrfile_get_random_seed( vcrfile );
  /* TODO: get if globally from somewhere else :-), for the moment use the gui-stuff */ 
  cdata.g_shibon = vcr_get( widget, user_data, SHIP_A, PRC_SHIBON, VAL_CUR );
  cdata.g_a_is_ship       = 1; /* future stuff, maybe side a is not a ship */
  if( gwp_vcrfile_2nd_side_is_planet( vcrfile ) )
    cdata.g_b_is_ship     = 0;
  else
    cdata.g_b_is_ship     = 1;

  cdata.a_shield          = gwp_vcrfile_get_shields( vcrfile, VCRC_SIDE_A );
  cdata.a_hull            = 100 - gwp_vcrfile_get_damage( vcrfile, VCRC_SIDE_A );
  cdata.a_crew            = gwp_vcrfile_get_crew( vcrfile, VCRC_SIDE_A );
  cdata.a_mass            = gwp_vcrfile_get_mass( vcrfile, VCRC_SIDE_A );
  cdata.a_typ_hull        = 1; /* is not interesting for vcr's */
  cdata.a_nmb_fighter     = gwp_vcrfile_get_number_of_fighters( vcrfile, VCRC_SIDE_A );
  cdata.a_nmb_bays        = gwp_vcrfile_get_number_of_bays( vcrfile, VCRC_SIDE_A );
  cdata.a_nmb_torps       = gwp_vcrfile_get_number_of_torpedos( vcrfile, VCRC_SIDE_A );
  cdata.a_nmb_tubes       = gwp_vcrfile_get_number_of_tubes( vcrfile, VCRC_SIDE_A );
  cdata.a_typ_torps       = gwp_vcrfile_get_type_of_torpedos( vcrfile, VCRC_SIDE_A );
  cdata.a_nmb_beams       = gwp_vcrfile_get_number_of_beams( vcrfile, VCRC_SIDE_A );
  cdata.a_typ_beams       = gwp_vcrfile_get_type_of_beams( vcrfile, VCRC_SIDE_A );
  cdata.a_typ_engines     = 1; /* not interesting either */

  cdata.b_shield          = gwp_vcrfile_get_shields( vcrfile, VCRC_SIDE_B );
  cdata.b_hull            = 100 - gwp_vcrfile_get_damage( vcrfile, VCRC_SIDE_B );
  cdata.b_crew            = gwp_vcrfile_get_crew( vcrfile, VCRC_SIDE_B );
  cdata.b_mass            = gwp_vcrfile_get_mass( vcrfile, VCRC_SIDE_B );
  cdata.b_typ_hull        = 1; /* is not interesting for vcr's */
  cdata.b_nmb_fighter     = gwp_vcrfile_get_number_of_fighters( vcrfile, VCRC_SIDE_B );
  cdata.b_nmb_bays        = gwp_vcrfile_get_number_of_bays( vcrfile, VCRC_SIDE_B );
  cdata.b_nmb_torps       = gwp_vcrfile_get_number_of_torpedos( vcrfile, VCRC_SIDE_B );
  cdata.b_nmb_tubes       = gwp_vcrfile_get_number_of_tubes( vcrfile, VCRC_SIDE_B );
  cdata.b_typ_torps       = gwp_vcrfile_get_type_of_torpedos( vcrfile, VCRC_SIDE_B );
  cdata.b_nmb_beams       = gwp_vcrfile_get_number_of_beams( vcrfile, VCRC_SIDE_B );
  cdata.b_typ_beams       = gwp_vcrfile_get_type_of_beams( vcrfile, VCRC_SIDE_B );
  cdata.b_typ_engines     = 1; /* not interesting either */

  cdata.p_has_base        = 0;  /* we could only guess by looking at the other values */
  cdata.p_typ_beams       = 1;  /* not interesting in case of vcr */
  cdata.p_nmb_pdefense    = 10; /* not interesting in case of vcr */
  cdata.p_nmb_bdefense    = 10; /* not interesting in case of vcr */
  cdata.p_nmb_fighter     = 10; /* not interesting in case of vcr */

g_message( "till here" );
  /* try to start combat */
  vcrc_combat_start( &cdata );
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


/* quick'n dirty */
/* converts every char A-Z to lowercase exept after tab, sp, lf, cr */
gchar *str2low( gchar *str )
{
  gint i;
  gint o = ASCII_SP;
  gint n = strlen( str );

  for( i=0; i<n; i++ )
  {
    if( str[i]>=ASCII_A && str[i]<=ASCII_Z )
      if( o!=ASCII_TAB && o!=ASCII_SP && o!=ASCII_LF && o!=ASCII_CR )
        str[i] = str[i] - ASCII_A + ASCII_a;
    o = str[i];
  }
  return( str );
}








