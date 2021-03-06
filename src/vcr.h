/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.12  2005/05/31 13:17:39  ldipenti
    Feature: Added CVS metadata on source files

*/

#ifndef VCR_H
#define VCR_H

#include <gnome.h>
#include <math.h>
#include <string.h>
#include <glib/gprintf.h>

#include "gwp-planet.h"
#include "vcr-combat-gl.h"
#include "callbacks.h"
#include "global.h"
#include "support.h"
#include "gwp-ship.h"
#include "race.h"
#include "vcr-combat.h"
#include "gwp-vcrfile.h"

#define ASCII_0   48
#define ASCII_A   65
#define ASCII_Z   90
#define ASCII_a   97
#define ASCII_SP  32
#define ASCII_TAB  9
#define ASCII_LF  10
#define ASCII_CR  13

/* target */
enum {
    SHIP_A,
    SHIP_B,
    PLANET,
    BASE
};

/* value */
enum {
    PRC_SHIELD,
    PRC_DAMAGE,
    PRC_SHIBON,
    NMB_TUBEBAY,
    NMB_TORPFIG,
    NMB_CREW,
    NMB_BEAMS,
    NMB_MASS,
    NMB_DEF,
    LVL_ENGINE,
    LVL_BEAM,
    LVL_TORP,
    TYP_RACE,
    TYP_HULL,
    TYP_ID,
    HULL_ID
};

/* what */
enum {
    VAL_MIN,
    VAL_CUR,
    VAL_MAX
};

void vcr_all_init( GtkWidget *widget, gpointer  user_data );
void vcr_delete_event( GtkWidget *widget, gpointer user_data );
void vcr_show_window( GtkWidget *widget, gpointer  user_data, gboolean show );
void vcr_start_combat( GtkWidget *widget, gpointer  user_data );
void vcr_toggle_starbase( GtkWidget *widget, gpointer  user_data );
void vcr_show_basedata( GtkWidget *widget, gpointer  user_data, gboolean show );
void vcr_set( GtkWidget *widget, gpointer user_data,
              gint target, gint value, gint what, gint setthis );
gint vcr_get( GtkWidget *widget, gpointer user_data,
              gint source, gint value, gint what );
void vcr_populate_ship_a_list( GtkWidget *widget, gpointer user_data );
void vcr_populate_beamspec_lists( GtkWidget *widget, gpointer user_data );
void vcr_populate_race_lists( GtkWidget *widget, gpointer user_data );
void vcr_populate_torps_lists( GtkWidget *widget, gpointer user_data );
void vcr_populate_hull_lists( GtkWidget *widget, gpointer user_data );
void vcr_populate_vcr_lists( GtkWidget *widget, gpointer user_data );

void vcr_ship_a_selected( GtkWidget *widget, gpointer user_data );
void vcr_ship_a_race_selected( GtkWidget *widget, gpointer user_data );
void vcr_ship_b_race_selected( GtkWidget *widget, gpointer user_data );
void vcr_ship_a_hull_selected( GtkWidget *widget, gpointer user_data );
void vcr_ship_b_hull_selected( GtkWidget *widget, gpointer user_data );
gboolean vcr_planet_selected( GtkWidget *widget, gpointer user_data );
gboolean vcr_base_selected( GtkWidget *widget, gpointer user_data );
gboolean vcr_record_selected( GtkWidget *widget, gpointer user_data );

gint str2int( char *str );
gchar *str2low( gchar *str );



#endif
