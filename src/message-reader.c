
#include <gnome.h>
#include <math.h>
#include <string.h>

#include "callbacks.h"
#include "gwp-messages.h"
#include "message-reader.h"
#include "global.h"
#include "support.h"

#define DEBUGOUTPUT 1



void message_reader_textview_init( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr textview init called" );
  GtkWidget *reader = lookup_widget("reader");
  gtk_widget_show(reader);
  GwpMessages *messages = (GwpMessages *)gwp_messages_new();
  g_object_set_data(G_OBJECT(reader), "message_instance", messages);

  /* set a monospace font for the message display */
  GtkWidget *textview = lookup_widget( "reader_textview" );
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

  /* declarations and preparations */
  gchar oldhead;
  gint i;
  gchar *tmph, *tmps;
  gint tmpi;
  tmph = (gchar *)g_malloc(1024*sizeof(gchar));
  tmps = (gchar *)g_malloc(1024*sizeof(gchar));
  GtkTreeStore  *treestore;
  GtkTreeIter    toplevel, child;
  GtkTreeView *message_tree;
  GtkTreeViewColumn   *col;
  GtkCellRenderer     *renderer;
  message_tree = (GtkTreeView *)lookup_widget( "message_treeview" );
  treestore = gtk_tree_store_new(NUM_COLS,
                                 G_TYPE_STRING,
                                 G_TYPE_STRING,
                                 G_TYPE_INT);
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");


  /* re-initialize treeview */
  if( gtk_tree_view_get_model( message_tree ) )
  {
    GList* list = gtk_tree_view_get_columns( message_tree );
    gtk_tree_view_remove_column( message_tree, list->next->next->data );
    gtk_tree_view_remove_column( message_tree, list->next->data );
    gtk_tree_view_remove_column( message_tree, list->data );
  }

  /* prepare the columns */
  /* The Header-Column */
  col = gtk_tree_view_column_new();
  gtk_tree_view_column_set_title(col, "Header");
  /* pack tree view column into tree view */
  gtk_tree_view_append_column(message_tree, col);
  renderer = gtk_cell_renderer_text_new();
  /* pack cell renderer into tree view column */
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  /* connect 'text' property of the cell renderer to
   *  model column that contains the message header */
  gtk_tree_view_column_add_attribute(col, renderer, "text", COL_HEADER);

  /* The Subject-Column */
  col = gtk_tree_view_column_new();
  gtk_tree_view_column_set_title(col, "Subject");
  /* pack tree view column into tree view */
  gtk_tree_view_append_column(message_tree, col);
  renderer = gtk_cell_renderer_text_new();
  /* pack cell renderer into tree view column */
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  /* connect 'text' property of the cell renderer to
   *  model column that contains the message subject */
  gtk_tree_view_column_add_attribute(col, renderer, "text", COL_SUBJECT);
  /* connect a cell data function */
  gtk_tree_view_column_set_cell_data_func(col, renderer, subject_cell_data_func, NULL, NULL);
  /* set 'weight' property of the cell renderer to
   *  bold print (we want all subjects in bold) */
  g_object_set(renderer,
              "weight", PANGO_WEIGHT_BOLD,
              "weight-set", TRUE,
               NULL);

  /* The (hidden) Identifier-Column */
  col = gtk_tree_view_column_new();
  gtk_tree_view_column_set_title(col, "#");
  /* pack tree view column into tree view */
  gtk_tree_view_append_column(message_tree, col);
  renderer = gtk_cell_renderer_text_new();
  /* pack cell renderer into tree view column */
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  /* connect 'text' property of the cell renderer to
   *  model column that contains the message subject */
  gtk_tree_view_column_add_attribute(col, renderer, "text", COL_IDENT);
  /* hide this identifier column */
  gtk_tree_view_column_set_visible( col, FALSE );


  oldhead = '\n';
  for( i=0; i<gwp_messages_getNumberOfMessages( messages ); i++ )
  {
    tmph[0] = '\0';
    strcat( tmph, gwp_messages_getMessageHeader( messages, i ) );

    if( oldhead != tmph[1] )
    {
      /* start a new message division */
      oldhead = tmph[1];
      /* create the right header/subjects */
      tmph[0] = '\0';
      strncat( tmph, gwp_messages_getMessageHeader( messages, i )+1, 1 );
      tmps[0] = '\0';
      tmpi = -i-1;
      /* Append a top level row */
      gtk_tree_store_append(treestore, &toplevel, NULL);
      gtk_tree_store_set(treestore, &toplevel,
                     COL_HEADER, tmph,
                     COL_SUBJECT, tmps,
                     COL_IDENT, tmpi,
                     -1);
    }
    /* create the right header/subjects */
    tmph[0] = '\0';
    strcat( tmph, gwp_messages_getMessageHeader( messages, i ) );
    tmps[0] = '\0';
    strcat( tmps, gwp_messages_getMessageHeaderLong( messages, i ) );
    tmpi = i+1;
    /* Append a child to the top level row, and fill in some data */
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child,
                   COL_HEADER, tmph,
                   COL_SUBJECT, tmps,
                   COL_IDENT, tmpi,
                   -1);
  }


  /* fill the treeview with this new model */
  gtk_tree_view_set_model( message_tree, GTK_TREE_MODEL( treestore ) );
  /* jump again to first message */
  gwp_messages_getMessageRaw( messages, gwp_messages_getMessageIdFirst( messages ) );
  /* make messages selectable, one at a time */
  gtk_tree_selection_set_mode(gtk_tree_view_get_selection(message_tree),
                              GTK_SELECTION_SINGLE);

  /* cleanup */
  g_free( tmph );
  g_free( tmps );
if( DEBUGOUTPUT ) g_message("DEBUG: mr treeview init finished" );
}



void subject_cell_data_func (GtkTreeViewColumn *col,
                             GtkCellRenderer   *renderer,
                             GtkTreeModel      *model,
                             GtkTreeIter       *iter,
                             gpointer           user_data)
{
  gint   ident;
  gchar  buf[1024];

  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");

  gtk_tree_model_get(model, iter, COL_IDENT, &ident, -1);
  if( ident < 0 )
  {
    /* row is parent */
    buf[0]='\0';
    strcat( buf, gwp_messages_getMessageCategory( messages, -ident-1 ) );
    g_object_set( renderer, "foreground-set", FALSE, NULL );
    g_object_set( renderer, "weight", PANGO_WEIGHT_BOLD, "weight-set", TRUE, NULL );
  }
  else
  {
    /* row is child */
    buf[0]='\0';
    strcat( buf, gwp_messages_getMessageSubject( messages, ident-1 ) );
    g_object_set( renderer, "foreground", "Black", "foreground-set", TRUE, NULL );
    g_object_set( renderer, "weight", PANGO_WEIGHT_BOLD, "weight-set", FALSE, NULL );
  }

  g_object_set(renderer, "text", buf, NULL);
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
    /* clean-fill combobox with valid turns and select current */
    while( messages->pub->msgnmb > 0 )
    {
      gtk_combo_box_remove_text( turnnmb, 0 );
      messages->pub->msgnmb--;
    }
    for( i=1; i<cur; i++ )
    {
      gtk_combo_box_insert_text( turnnmb, i, g_strdup_printf( "%d", msgindex[i] ) );
      messages->pub->msgnmb++;
    }
    gtk_combo_box_set_active( turnnmb, cur-2 );
  }

  /* cleanup */
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
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gint id = gwp_messages_getMessageIdFirst( messages );
  message_reader_show_body( widget, user_data, id );
if( DEBUGOUTPUT ) g_message("DEBUG: mr show first finished" );
}

void message_reader_show_prev_body( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr show prev called" );
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gint id = gwp_messages_getMessageIdPrev( messages );
  message_reader_show_body( widget, user_data, id );
if( DEBUGOUTPUT ) g_message("DEBUG: mr show prev finished" );
}

void message_reader_show_next_body( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr show next called" );
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gint id = gwp_messages_getMessageIdNext( messages );
  message_reader_show_body( widget, user_data, id );
if( DEBUGOUTPUT ) g_message("DEBUG: mr show next finished" );
}

void message_reader_show_last_body( GtkWidget *widget,
				      gpointer  user_data )
{
if( DEBUGOUTPUT ) g_message("DEBUG: mr show last called" );
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gint id = gwp_messages_getMessageIdLast( messages );
  message_reader_show_body( widget, user_data, id );
if( DEBUGOUTPUT ) g_message("DEBUG: mr show last finished" );
}

void message_reader_show_body( GtkWidget *widget,
                      gpointer user_data, gint id )
{
  GtkTextView *textview = (GtkTextView *)lookup_widget( "reader_textview" );
  GtkTextBuffer *buffer = gtk_text_buffer_new( NULL );
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
  gtk_text_buffer_set_text( buffer, gwp_messages_getMessageRaw( messages, id ), -1 );
  message_reader_set_current_message_id( widget, user_data, id );
  gtk_text_view_set_buffer( textview, buffer );
  GtkLabel *counter = (GtkLabel *)lookup_widget( "currmsg_label" );
  gtk_label_set_text( counter, g_strdup_printf("%d/%d", gwp_messages_getMessageIdCurrent( messages )+1, gwp_messages_getNumberOfMessages( messages ) ) );
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

  /* refresh all gui stuff */
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

void message_reader_set_current_message_id( GtkWidget *widget,
				      gpointer  user_data, gint id )
{
  GwpMessages *messages = (GwpMessages *)
    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");

  /* explicitly tell the message-model which message is the current */
  gwp_messages_setCurrMsgId( messages, id );


//  GwpMessages *messages = (GwpMessages *)
//    g_object_get_data(G_OBJECT(lookup_widget("reader")), "message_instance");
//  GtkTreeView *message_tree = (GtkTreeView *)lookup_widget( "message_treeview" );
//  GtkTreeModel *model = gtk_tree_view_get_model( message_tree );
///* TODO - question: no gtk_tree_iter_new() ??? */
//  GtkTreeIter iter;
//  GtkTreeSelection *selection = gtk_tree_view_get_selection( message_tree );
//  gtk_tree_selection_get_selected( selection, NULL, &iter );
//  gtk_tree_selection_get_selected( selection, NULL, &iter );
//  gtk_tree_model_iter_next( model, &iter );
//  gtk_tree_selection_select_iter( selection, &iter);
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
