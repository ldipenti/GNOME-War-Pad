#ifndef MESSAGE_READER_H
#define MESSAGE_READER_H

#include "gwp-planet.h"

void message_reader_all_init( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_textview_init( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_treeview_init( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_combobox_init( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_delete_event( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_treeview_update(void);

void message_reader_show_first_body( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_show_prev_body( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_show_next_body( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_show_last_body( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_change_messagefile( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_get_msgfilename( GtkWidget *widget,
				      gpointer  user_data, char *copyhere, int turn );

#endif
