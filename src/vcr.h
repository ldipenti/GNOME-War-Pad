#ifndef VCR_H
#define VCR_H

#include "gwp-planet.h"

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
    TYP_ID
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





#endif
