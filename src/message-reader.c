
#include <gnome.h>
#include <math.h>
#include <string.h>

#include "callbacks.h"
#include "gwp-messages.h"
#include "message-reader.h"
#include "global.h"
#include "support.h"

#define DEBUGOUTPUT 0



void message_reader_textview_init( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr textview init called" );
  GtkWidget *reader = lookup_widget("reader");
  gtk_widget_show(reader);
  GwpMessages *messages = (GwpMessages *)gwp_messages_new();
  g_object_set_data(G_OBJECT(reader), "message_instance", messages);

  /* set a monospace font for the message display */
  GtkTextView *textview = (GtkTextView *)lookup_widget( "reader_textview" );
  PangoFontDescription *pfontdesc = pango_font_description_from_string( "Monospace 10" );
  gtk_widget_modify_font( textview, pfontdesc );

  /* display the first message */
  on_reader_firstmess_btn_clicked( reader, user_data );

  /* update message counter */
  GtkLabel *counter = (GtkLabel *)lookup_widget( "currmsg_label" );
  gtk_label_set_text( counter, g_strdup_printf("%d/%d", gwp_messages_getMessageIdCurrent( messages )+1, gwp_messages_getNumberOfMessages( messages ) ) );

  /* cleanup */
  pango_font_description_free( pfontdesc );
if( DEBUGOUTPUT ) g_message("DEBUG: mr textview init finished" );
}



void message_reader_treeview_init( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr treeview init called" );
  
  GtkTreeView *message_tree;
  GtkListStore *store;
  GtkTreeViewColumn *column;
  GtkCellRenderer *renderer;
  GtkTreeIter iter;
  int i;
  char *tmph, *tmps;
  tmph = (char *)malloc(1024*sizeof(char));
  tmps = (char *)malloc(1024*sizeof(char));
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");

  enum {
    HEADER_COLUMN,
    SUBJECT_COLUMN
  };

  message_tree = (GtkTreeView *)lookup_widget( "message_treeview" );
/* remove all old columns */
while( gtk_tree_view_get_column( message_tree, 0 ) )
  gtk_tree_view_remove_column( message_tree, gtk_tree_view_get_column( message_tree, 0 ) );
  store = gtk_list_store_new( 2,
                              G_TYPE_STRING,
                              G_TYPE_STRING );
  gtk_tree_view_set_model( message_tree, GTK_TREE_MODEL( store ));
  renderer = gtk_cell_renderer_text_new( );

  column = gtk_tree_view_column_new_with_attributes(_("Header"),
                            renderer,
                            "text", HEADER_COLUMN,
                            NULL);
  gtk_tree_view_append_column( message_tree, column );

  column = gtk_tree_view_column_new_with_attributes(_("Subject"),
                            renderer,
                            "text", SUBJECT_COLUMN,
                            NULL );
  gtk_tree_view_append_column( message_tree, column );



  for( i=0; i<gwp_messages_getNumberOfMessages( messages ); i++ )
  {
    tmph[0] = '\0';
    strcat( tmph, gwp_messages_getMessageHeader( messages, i ) );
    tmps[0] = '\0';
    strcat( tmps, gwp_messages_getMessageSubject( messages, i ) );

    gtk_list_store_append(store, &iter); /* Get iterator */
    gtk_list_store_set(store, &iter,
			 HEADER_COLUMN, tmph,
			 SUBJECT_COLUMN, tmps,
			 -1);
    }

  /* jump again to first message */
  gwp_messages_getMessageRaw( messages, gwp_messages_getMessageIdFirst( messages ) );

  /* cleanup */
  free( tmph );
  free( tmps );
if( DEBUGOUTPUT ) g_message("DEBUG: mr treeview init finished" );
}

void message_reader_combobox_init( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr combobox init called" );
  /* fill turn history selector */
  GtkComboBox *turnnmb = (GtkComboBox *)lookup_widget( "combox_turnnmb" );

  gint i, cur, max;
  FILE *msgfile;
  max = game_get_turn_number(game_state);
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gint *msgindex = messages->pub->msgindex;
  gboolean *msgexists = messages->pub->msgindex;
  gchar *tmpname = (gchar *)malloc(1024*sizeof(gchar));

  /* check for existing message history files*/
  cur = 1;
  for( i=1; i<=max; i++ )
  {
    message_reader_get_msgfilename( widget, user_data, tmpname, i );
    msgfile = fopen( tmpname, "rb" );
    if( msgfile )
    {
       msgexists[i] = true;
       msgindex[cur] = i;
       cur++;
       fclose( msgfile );
    }
    else
    {
       msgexists[i] = false;
    }
  }

  /* check for errors */
  if( cur<2 )
  {
    g_message( "# Warning: No Valid Message History was found" );
    g_message( "#          Please copy your mdataX.dat files, eg. in turn 7:" );
    g_message( "#          copy 'mdata9.dat' to './message-history/mdata9_7.dat'" );
  }
  else
  {
    /* fill combobox with valid turns and select current */
    for( i=1; i<cur; i++ )
    {
      gtk_combo_box_insert_text( turnnmb, i, g_strdup_printf( "%d", msgindex[i] ) );
    }
    gtk_combo_box_set_active( turnnmb, cur-2 );
  }

  /* cleanup */
//  free( msgindex );
//  free( msgexists );
  free( tmpname );
if( DEBUGOUTPUT ) g_message("DEBUG: mr combobox init finished" );
}



void message_reader_delete_event( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr delete event called" );
  GtkWidget *reader = lookup_widget("reader");
  gtk_widget_hide(reader);
if( DEBUGOUTPUT ) g_message("DEBUG: mr delete event finished" );
}

void message_reader_show_first_body( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr show first called" );
  GtkTextView *textview = (GtkTextView *)lookup_widget( "reader_textview" );
  GtkTextBuffer *buffer = gtk_text_buffer_new( NULL );
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gtk_text_buffer_set_text( buffer, gwp_messages_getMessageBody( messages, gwp_messages_getMessageIdFirst( messages ) ), -1 );
  gtk_text_view_set_buffer( textview, buffer );
  GtkLabel *counter = (GtkLabel *)lookup_widget( "currmsg_label" );
  gtk_label_set_text( counter, g_strdup_printf("%d/%d", gwp_messages_getMessageIdCurrent( messages )+1, gwp_messages_getNumberOfMessages( messages ) ) );
if( DEBUGOUTPUT ) g_message("DEBUG: mr show first finished" );
}

void message_reader_show_prev_body( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr show prev called" );
  GtkTextView *textview = (GtkTextView *)lookup_widget( "reader_textview" );
  GtkTextBuffer *buffer = gtk_text_buffer_new( NULL );
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gtk_text_buffer_set_text( buffer, gwp_messages_getMessageBody( messages, gwp_messages_getMessageIdPrev( messages ) ), -1 );
  gtk_text_view_set_buffer( textview, buffer );
  GtkLabel *counter = (GtkLabel *)lookup_widget( "currmsg_label" );
  gtk_label_set_text( counter, g_strdup_printf("%d/%d", gwp_messages_getMessageIdCurrent( messages )+1, gwp_messages_getNumberOfMessages( messages ) ) );
if( DEBUGOUTPUT ) g_message("DEBUG: mr show prev finished" );
}

void message_reader_show_next_body( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr show next called" );
  GtkTextView *textview = (GtkTextView *)lookup_widget( "reader_textview" );
  GtkTextBuffer *buffer = gtk_text_buffer_new( NULL );
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gtk_text_buffer_set_text( buffer, gwp_messages_getMessageBody( messages, gwp_messages_getMessageIdNext( messages ) ), -1 );
  gtk_text_view_set_buffer( textview, buffer );
  GtkLabel *counter = (GtkLabel *)lookup_widget( "currmsg_label" );
  gtk_label_set_text( counter, g_strdup_printf("%d/%d", gwp_messages_getMessageIdCurrent( messages )+1, gwp_messages_getNumberOfMessages( messages ) ) );
if( DEBUGOUTPUT ) g_message("DEBUG: mr show next finished" );
}

void message_reader_show_last_body( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr show last called" );
  GtkTextView *textview = (GtkTextView *)lookup_widget( "reader_textview" );
  GtkTextBuffer *buffer = gtk_text_buffer_new( NULL );
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gtk_text_buffer_set_text( buffer, gwp_messages_getMessageBody(messages, gwp_messages_getMessageIdLast( messages ) ), -1 );
  gtk_text_view_set_buffer( textview, buffer );
  GtkLabel *counter = (GtkLabel *)lookup_widget( "currmsg_label" );
  gtk_label_set_text( counter, g_strdup_printf("%d/%d", gwp_messages_getMessageIdCurrent( messages )+1, gwp_messages_getNumberOfMessages( messages ) ) );
if( DEBUGOUTPUT ) g_message("DEBUG: mr show last finished" );
}

void message_reader_all_init( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr init all called" );
  message_reader_textview_init( widget, user_data );
  message_reader_treeview_init( widget, user_data );
  message_reader_combobox_init( widget, user_data );
if( DEBUGOUTPUT ) g_message("DEBUG: mr init all finished" );
}

void message_reader_treeview_update( void )
{
  /* TODO */
}

void message_reader_change_messagefile( GtkWidget *widget,
				      gpointer  user_data )
{
  /* preparations */
  GtkComboBox *turnnmb = (GtkComboBox *)lookup_widget( "combox_turnnmb" );
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gint *msgindex = messages->pub->msgindex;
  gboolean *msgexists = messages->pub->msgindex;
  char *tmpname = (char *)malloc(1024*sizeof(char));

  /* read new file */
  message_reader_get_msgfilename( widget, user_data, tmpname, msgindex[gtk_combo_box_get_active( turnnmb )+1] );
  gwp_messages_readFile( messages, tmpname );

  /* refresh all gui stuff*
  /* TODO */
GtkWidget *reader = lookup_widget("reader");
/* display the first message */
on_reader_firstmess_btn_clicked( reader, user_data );
/* update message counter */
GtkLabel *counter = (GtkLabel *)lookup_widget( "currmsg_label" );
gtk_label_set_text( counter, g_strdup_printf("%d/%d", gwp_messages_getMessageIdCurrent( messages )+1, gwp_messages_getNumberOfMessages( messages ) ) );
/* update treeview */
message_reader_treeview_init( widget, user_data );

  /* cleanup */
  free( tmpname );
}



void message_reader_get_msgfilename( GtkWidget *widget,
				      gpointer  user_data, char *copyhere, int turn )
{
  if( !copyhere )
  {
    g_message( "## ERROR: from: void message_reader_get_msgfilename():" );
    g_message( "##        given char* is NULL, unable to fill it..." );
    return;
  }
  copyhere[0] = '\0';
  strcat( copyhere, game_get_full_path(game_state, "message-history") );
  strcat( copyhere, "/mdata" );
  copyhere[strlen(copyhere)+1] = '\0';
  if( game_get_race(game_state) < 10 )
    copyhere[strlen(copyhere)+0] = game_get_race(game_state) + 48;
  else
    copyhere[strlen(copyhere)+0] = game_get_race(game_state) + 55;
  strcat( copyhere, "_" );
  strcat( copyhere, g_strdup_printf( "%d", turn ) );
  strcat( copyhere, ".dat" );
}
