#include <gnome.h>


void
on_new_file1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_as1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_exit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_cut1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_copy1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_paste1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_clear1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_properties1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_preferences1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
starchart_event_key                    (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

gboolean
starchart_event_button                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
starchart_event_pointer_motion         (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data);

gboolean
starchart_event_button                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
starchart_event_button                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
starchart_event_button                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
starchart_event_button                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
void
select_race_event                      (GtkButton       *button,
                                        gpointer         user_data);

void
select_race_event                      (GtkButton       *button,
                                        gpointer         user_data);

void
select_race_event                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_close_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
select_race1_event                     (GtkButton       *button,
                                        gpointer         user_data);

void
select_race2_event                     (GtkButton       *button,
                                        gpointer         user_data);

void
select_race3_event                     (GtkButton       *button,
                                        gpointer         user_data);

void
select_race_event                      (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_gwp_destroy_event                   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_vp_game_dir_browse_clicked          (GnomeFileEntry  *gnomefileentry,
                                        gpointer         user_data);

void
on_vp_game_dir_changed                 (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_vp_game_dir_changed                 (GtkEditable     *editable,
                                        gpointer         user_data);

void on_game_mgr_game_dir_changed (GtkEditable *editable,
				   gpointer user_data);

void on_game_mgr_new_game (GtkWidget *widget,
			   gpointer user_data);

void on_game_mgr_edit_game(GtkWidget *widget,
			   gpointer user_data);

void on_game_mgr_iconlist_select_icon (GnomeIconList *iconlist,
				       gint icon_idx,
				       GdkEventButton *event,
				       gpointer user_data);

void on_game_mgr_button_cancel_clicked (GtkWidget *widget,
					gpointer user_data);

void on_game_mgr_properties_race_list_row_activated (GtkWidget *widget,
						     gpointer user_data);

void on_game_mgr_delete_game (GtkWidget *widget,
			      gpointer user_data);
