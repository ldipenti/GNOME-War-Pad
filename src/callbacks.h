#include <gnome.h>

gboolean
starchart_event_key                    (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);
gboolean
starchart_event_button_release         (GtkWidget       *widget,
                                        GdkEventButton  *event,
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
on_button_close_clicked                (GtkButton       *button,
                                        gpointer         user_data);
gboolean
on_gwp_destroy_event                   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void on_game_mgr_game_dir_changed (GtkEditable *editable,
				   gpointer user_data);

void on_game_mgr_new_game (GtkWidget *widget,
			   gpointer user_data);

void on_game_mgr_edit_game(GtkWidget *widget,
			   gpointer user_data);

void on_game_mgr_play_game (GtkWidget *widget,
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

void gwp_quit(void);

void on_about_activate(GtkWidget *widget);
void on_game_mgr_about_activate(GtkWidget *widget,
				gpointer data);
void on_starchart_about_activate(GtkWidget *widget,
				 gpointer data);

gboolean delete_event (GtkWidget *widget,
		       GdkEvent *event,
		       gpointer data);

void on_game_close_activate (GtkWidget *widget,
			     gpointer user_data);

void on_game_mgr_btn_unpack_clicked (GtkWidget *widget,
				     gpointer user_data);
