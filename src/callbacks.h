/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2004 Lucas Di Pentima <lucas@lunix.com.ar>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

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

void on_ships_list_cursor_changed (GtkWidget *widget,
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
gchar* on_hscale_tax_format_value(GtkScale *scale, gdouble value);

void on_online_help_activate (GtkWidget *widget,
			      gpointer user_data);

void on_button_zoom_in_clicked (GtkWidget *widget,
				gpointer user_data);

void on_button_zoom_out_clicked (GtkWidget *widget,
				gpointer user_data);

void on_togglebutton_grid_toggled (GtkToggleButton *button,
				   gpointer user_data);

void on_view_toolbar_activate (GtkCheckMenuItem *menuitem,
			       gpointer user_data);
void on_view_pnames_activate (GtkCheckMenuItem *menuitem,
				  gpointer user_data);
void on_view_scanner_area_activate (GtkCheckMenuItem *menuitem,
				    gpointer user_data);
void on_view_minefields_activate (GtkCheckMenuItem *menuitem,
				  gpointer user_data);
void on_view_ion_storms_activate (GtkCheckMenuItem *menuitem,
				  gpointer user_data);


void on_view_message_reader_activate (GtkWidget *widget,
				      gpointer  user_data);
void on_reader_delete_event( GtkWidget *widget,
				      gpointer  user_data );
void on_reader_firstmess_btn_clicked (GtkWidget *widget,
				      gpointer  user_data);
void on_reader_prev_btn_clicked (GtkWidget *widget,
				 gpointer  user_data);
void on_reader_next_btn_clicked (GtkWidget *widget,
				 gpointer  user_data);
void on_reader_lastmess_btn_clicked (GtkWidget *widget,
				     gpointer  user_data);
void on_combox_turnnmb_changed( GtkWidget *widget,
				     gpointer user_data);
void on_message_treeview_select_cursor_row( GtkWidget *widget,
				     gpointer user_data);
void on_message_treeview_row_activated( GtkWidget *widget,
				     gpointer user_data);
void on_message_treeview_cursor_changed( GtkWidget *widget,
				     gpointer user_data);
void on_ships_list_row_activated (GtkTreeView *ships_list,
				  GtkTreePath *path,
				  GtkTreeViewColumn *col,
				  gpointer user_data);
void on_vcr_activate( GtkWidget *widget,
                      gpointer  user_data );
void on_vcr_delete_event( GtkWidget *widget,
                          gpointer  user_data );
void on_vcr_button_start_combat_pressed( GtkWidget *widget,
                                         gpointer  user_data );
void on_vcr_checkbutton_base_toggled( GtkWidget *widget,
                                      gpointer  user_data );
void on_vcr_comboboxentry_sel_ext_shp_a_changed( GtkWidget *widget,
                                                 gpointer  user_data );
void on_vcr_comboboxentry_sel_race_a_changed( GtkWidget *widget,
                                              gpointer  user_data );
void on_vcr_comboboxentry_sel_race_b_changed( GtkWidget *widget,
                                              gpointer  user_data );
void on_vcr_comboboxentry_sel_type_a_changed( GtkWidget *widget,
                                              gpointer  user_data );
void on_vcr_comboboxentry_sel_type_b_changed( GtkWidget *widget,
                                              gpointer  user_data );

void on_vcr_comboboxentry_sel_vcr_changed( GtkWidget *widget,
                                           gpointer  user_data );

void on_TESTBUTTON_pressed( GtkWidget *widget, gpointer user_data );

void on_view_python_console_activate (GtkWidget *widget,
				      gpointer user_data);
