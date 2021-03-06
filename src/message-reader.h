/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.5  2005/05/31 13:17:39  ldipenti
    Feature: Added CVS metadata on source files

*/

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

enum {
    COL_HEADER = 0,
    COL_SUBJECT,
    COL_IDENT,
    NUM_COLS };
void message_reader_show_first_body( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_show_prev_body( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_show_next_body( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_show_last_body( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_show_body( GtkWidget *widget,
                      gpointer user_data, gint id );
void message_reader_change_messagefile( GtkWidget *widget,
				      gpointer  user_data );
void message_reader_get_msgfilename( GtkWidget *widget,
				      gpointer  user_data, char *copyhere, int turn );
void message_reader_set_current_message_id( GtkWidget *widget,
				      gpointer  user_data, gint id );
void subject_cell_data_func (GtkTreeViewColumn *col,
                             GtkCellRenderer   *renderer,
                             GtkTreeModel      *model,
                             GtkTreeIter       *iter,
                             gpointer           user_data);

#endif
