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

#include <string.h>

#include "global.h"
#include "gwp-messages.h"

#define WORKING_PATH "/home/werdge/planets/vpwork1/"
#define TMPTXTLENG 65535
#define ASCII_LF 10
#define ASCII_CR 13
#define ASCII_SP 32

#define DEBUGOUTPUT 0
/*
 * Private members.
 */
struct _GwpMessagesPrivate {
  gboolean dispose_has_run;
  gint x_coord;
  gint y_coord;
  gint id;
  GString *name;
  bool fileRead;
  int numberOfMessages;
  mdataMessages msgs;
  char *tmptxt;
  int currMsg;
};

/*
 * forward definitions.
 */
static void gwp_messages_init (GTypeInstance *instance, gpointer g_class);
static void gwp_messages_class_init (GwpMessagesClass *klass);

GType gwp_messages_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpMessagesClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_messages_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpMessages),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_messages_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpMessages",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_messages_init (GTypeInstance *instance,
			     gpointer       g_class)
{
if( DEBUGOUTPUT ) g_message("DEBUG: constructor called" );
  GwpMessages *self = (GwpMessages *)instance;
  self->priv = g_new0 (GwpMessagesPrivate, 1);
  self->priv->dispose_has_run = FALSE;
  self->pub = g_new0 (GwpMessagesPublic, 1);

  /* Private members init */
  self->priv->x_coord = 0;
  self->priv->y_coord = 0;
  self->priv->id = 0;
  self->priv->name = g_string_new("");
  self->priv->fileRead = false;
  self->priv->numberOfMessages = 0;
  self->priv->msgs.n = 0;
  self->priv->msgs.m = NULL;
  self->priv->tmptxt = (char *)malloc(TMPTXTLENG*sizeof(char));
  self->priv->currMsg = 0;
  self->pub->msgindex = (gint *)malloc(game_get_turn_number(game_state)*sizeof(gint));
  self->pub->msgexists = (gboolean *)malloc(game_get_turn_number(game_state)*sizeof(gboolean));
if( DEBUGOUTPUT ) g_message("DEBUG: constructor finished" );
  /* g_message("GwpMessages init"); */
}

static void gwp_messages_dispose (GwpMessages *self)
{
  if(self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  g_string_free (self->priv->name, TRUE);
}

static void gwp_messages_finalize (GwpMessages *self)
{
if( DEBUGOUTPUT ) g_message("DEBUG: destructor called" );
  /*
   * Here, complete object destruction.
   */
  /*g_message("GwpMessages finalize"); */
  int i;
  for( i=0; i<self->priv->msgs.n; i++ )
    free( self->priv->msgs.m[i].t );
  free( self->priv->msgs.m );
  free( self->priv->tmptxt );
  free( self->pub->msgindex );
  free( self->pub->msgexists );
  g_free (self->priv);
if( DEBUGOUTPUT ) g_message("DEBUG: destructor finished" );
}

static void gwp_messages_class_init (GwpMessagesClass *klass)
{
if( DEBUGOUTPUT ) g_message("DEBUG: class init called" );
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* g_message("GwpMessagesClass init"); */
  /* Register destructor methods. */
  gobject_class->dispose = (void *)gwp_messages_dispose;
  gobject_class->finalize = (void *)gwp_messages_finalize;
if( DEBUGOUTPUT ) g_message("DEBUG: class init finished" );
}

/* 
 * Public method implementations.
 */
GwpMessages * gwp_messages_new (void)
{
  return g_object_new (gwp_messages_get_type (), NULL);
}

/**********************/
/* High-level methods */
/**********************/

/**
 * Check if the given messages has valid coordinates
 *
 * @param self a GwpMessages
 * @return TRUE if the current messages has valid coordinates, FALSE
 * otherwise.
 */
gboolean gwp_messages_valid_coords (GwpMessages *self) 
{
  g_assert(GWP_IS_MESSAGES(self));

  if (gwp_messages_get_x_coord(self) <= STARCHART_X_MAX && 
      gwp_messages_get_x_coord(self) >= STARCHART_X_MIN &&
      gwp_messages_get_y_coord(self) <= STARCHART_Y_MAX && 
      gwp_messages_get_y_coord(self) >= STARCHART_Y_MIN) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*******************/
/* Get-Set methods */
/*******************/

gint gwp_messages_get_x_coord (GwpMessages *self)
{
  g_assert (GWP_IS_MESSAGES(self));
  return self->priv->x_coord;
}

void gwp_messages_set_x_coord (GwpMessages *self, gint x)
{
  g_assert (GWP_IS_MESSAGES(self));
  if (x >= 0 && x <= 4000) {
    self->priv->x_coord = x;
  } else {
    self->priv->x_coord = 0;
  }
}

gint gwp_messages_get_y_coord (GwpMessages *self)
{
  g_assert (GWP_IS_MESSAGES(self));
  return self->priv->y_coord;
}

void gwp_messages_set_y_coord (GwpMessages *self, gint y)
{
  g_assert (GWP_IS_MESSAGES(self));
  if (y >= 0 && y <= 4000) {
    self->priv->y_coord = y;
  } else {
    self->priv->y_coord = 0;
  }
}

gint gwp_messages_get_id (GwpMessages *self)
{
  g_assert(GWP_IS_MESSAGES(self));
  return self->priv->id;
}

void gwp_messages_set_id (GwpMessages *self, gint id)
{
  g_assert(GWP_IS_MESSAGES(self));
  self->priv->id = id;
}

GString * gwp_messages_get_name (GwpMessages *self)
{
  g_assert (GWP_IS_MESSAGES(self));
  /* CP437 (DOS format) to UTF-8 conversion is done */
  return g_string_new (g_convert(self->priv->name->str, 
				 strlen(self->priv->name->str), 
				 "UTF-8", "CP437", NULL, NULL, NULL));
}

void gwp_messages_set_name (GwpMessages *self, GString *name)
{
  g_assert (GWP_IS_MESSAGES(self));
  g_assert (name != NULL);
  g_string_free (self->priv->name, TRUE);
  self->priv->name = g_string_new(name->str);
}







bool gwp_messages_checkValidMessageId( GwpMessages *self, int *id )
{
if( DEBUGOUTPUT ) g_message("DEBUG: valid id called" );
    /* check for valid message id */
    if( *id<0 )
    {
//        g_message( "# Warning: message id of %d has to be in [0, %d]\n", *id, self->priv->msgs.n );
        *id = 0;
if( DEBUGOUTPUT ) g_message("DEBUG: valid id finished x" );
        return( false );
    }
    if( *id>=(self->priv->msgs.n) )
    {
//        g_message( "# Warning: message id of %d has to be in [0, %d]\n", *id, self->priv->msgs.n );
        *id = (self->priv->msgs.n)-1;
if( DEBUGOUTPUT ) g_message("DEBUG: valid id finished x" );
        return( false );
    }
if( DEBUGOUTPUT ) g_message("DEBUG: valid id finished" );
    return( true );
}



int gwp_messages_readFileAny( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: readFileAny called" );
    char *filename = (char *)malloc(1024*sizeof(char));
    int i;
    FILE *testfile;

    /* check if file could be opened */
    filename[0] = '\0';
//    strcat( filename, g_strdup_printf("MDATA%d.DAT", game_get_race(game_state)) );
    strcat( filename, "MDATA" );
    filename[strlen(filename)+1] = '\0';
    if( game_get_race(game_state) < 10 )
        filename[strlen(filename)+0] = game_get_race(game_state) + 48;
    else
        filename[strlen(filename)+0] = game_get_race(game_state) + 55;
    strcat( filename, ".DAT" );
    testfile = fopen( game_get_full_path(game_state, filename), "rb" );
    g_message( "### Trying '%s'", game_get_full_path(game_state, filename) );

    /* If not worked, check for lowecase */
    if (! testfile) {
      GString *lc = g_string_new(filename);
      filename = g_string_down(lc)->str;
      testfile = fopen( game_get_full_path(game_state, filename), "rb" );
      g_message( "### Trying '%s'", game_get_full_path(game_state, filename) );
      g_string_free(lc, FALSE);
    }
    
    if( testfile ) {
      fclose( testfile );
      gwp_messages_readFile( self, game_get_full_path(game_state, filename) );
      free( filename );
if( DEBUGOUTPUT ) g_message("DEBUG: readFileAny finished" );
      return( EXIT_SUCCESS );
    }

    /* no filename has been given, trying in current dir with default names */
//    g_message( "# Warning: GwpFileMdatax::readFile() called without filename\n" );
    for( i=1; i<12; i++ )
    {
        /* construct default filenames to check */
        filename[0] = '\0';
        strcat( filename, WORKING_PATH );
        strcat( filename, "mdata" );
        if( i<10 )
        {
            filename[ strlen(filename)+1 ] = '\0';
            filename[ strlen(filename)   ] = 48+i;
        }
        else
        {
            filename[ strlen(filename)+2 ] = '\0';
            filename[ strlen(filename)+1 ] = 48+ i-10;
            filename[ strlen(filename)   ] = 48 + 1;
        }
        strcat( filename, ".dat" );
//        g_message( "  - trying '%s'  ...  ", filename );

        /* check if file could be opened */
        testfile = fopen( filename, "rb" );
        if( testfile )
        {
            /* success */
//            g_message( "OK, using this one\n" );
            fclose( testfile );
            gwp_messages_readFile( self, filename );
            break;
        }
        else
        {
            /* failure */
//            g_message( "no\n" );
        }
    }
    
    free( filename );

if( DEBUGOUTPUT ) g_message("DEBUG: readFileAny finished" );
    return( EXIT_SUCCESS );
}

int gwp_messages_readFile( GwpMessages *self, char *filename )
{
//    cout << "readFile called with name '" << filename << "'" << endl;
if( DEBUGOUTPUT ) g_message("DEBUG: readFile called" );
    FILE *mdatafile;
    long adress, length;
    int i, j;

    /* try to open file for read-access */
    mdatafile = fopen( filename, "rb" );
    if( !mdatafile )
    {
//        cout << "## Error: unable to open file '" << filename << "' for read-access" << endl;
if( DEBUGOUTPUT ) g_message("DEBUG: readFile finished x" );
        return( EXIT_FAILURE );
    }

    /* read in all message info */
    self->priv->numberOfMessages = gwp_messages_readWord( self, mdatafile );
    self->priv->msgs.n = self->priv->numberOfMessages;

    self->priv->msgs.m = (mdataMessage *)malloc(self->priv->numberOfMessages*sizeof(mdataMessage));
    for( i=0; i<self->priv->numberOfMessages; i++ )
    {
        adress = gwp_messages_readDWord( self, mdatafile );
        length = gwp_messages_readWord( self, mdatafile );
        self->priv->msgs.m[i].a = adress;
        self->priv->msgs.m[i].l = length;
        self->priv->msgs.m[i].t = (char *)malloc((length+1)*sizeof(char));
//        cout << "Message # " << i << ": offset " << adress << ", length " << length << endl;
    }

    /* read in all message data */
    for( i=0; i<self->priv->numberOfMessages; i++ )
    {
        fseek( mdatafile, self->priv->msgs.m[i].a-1, SEEK_SET );
        for( j=0; j<self->priv->msgs.m[i].l; j++ )
        {
            self->priv->msgs.m[i].t[j] = fgetc( mdatafile )-13;
            if( self->priv->msgs.m[i].t[j] == 13 ) self->priv->msgs.m[i].t[j] = 10;
        }
        self->priv->msgs.m[i].t[self->priv->msgs.m[i].l]='\0';
//        cout << endl << endl << "Message # " << i << ":" << endl << msgs.m[i].t << endl;
    }
    
    /* done */
    self->priv->fileRead = true;
    fclose( mdatafile );
if( DEBUGOUTPUT ) g_message("DEBUG: readFile finished" );
    return( EXIT_SUCCESS );
}



int gwp_messages_getNumberOfMessages( GwpMessages *self )
{
    /* check if file was already read */
if( DEBUGOUTPUT ) g_message("DEBUG: getnmb called" );
    if( !self->priv->fileRead ) gwp_messages_readFileAny( self );
if( DEBUGOUTPUT ) g_message("DEBUG: getnmb finished" );
    return( self->priv->msgs.n );
}



char *gwp_messages_getMessageRaw( GwpMessages *self, int id )
{
    /* check if file was already read */
if( DEBUGOUTPUT ) g_message("DEBUG: getRaw called" );
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );
g_message( "###: MessageRaw called with ID %d", id );
    int i;

    /* check for valid message id */
    gwp_messages_checkValidMessageId( self, &id );
    self->priv->currMsg = id;

    /* create text to be returned */
    self->priv->tmptxt[0] = '\0';

    for( i=0; i<self->priv->msgs.m[id].l; i++ )
    {
        self->priv->tmptxt[i] = self->priv->msgs.m[id].t[i];
//        if( self->priv->tmptxt[i] == 13 ) self->priv->tmptxt[i] = 10;
//        else if( self->priv->tmptxt[i] < 32 ) self->priv->tmptxt[i] = 32;
    }
    self->priv->tmptxt[self->priv->msgs.m[id].l]='\0';

    /* done */
if( DEBUGOUTPUT ) g_message("DEBUG: getRaw finished" );
    return( self->priv->tmptxt );
}



char *gwp_messages_getMessageBody( GwpMessages *self, int id )
{
if( DEBUGOUTPUT ) g_message("DEBUG: getBody called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

    /* check for valid message id */
    gwp_messages_checkValidMessageId( self, &id );
    self->priv->currMsg = id;

    /* create text to be returned */
    self->priv->tmptxt[0] = '\0';
    int i=0, j=0;
    /* look for first '>' sign */
    while( self->priv->msgs.m[id].t[i] != '>' && i<self->priv->msgs.m[id].l )
        i++;
    /* jump till last of the '>' signs */
    while( self->priv->msgs.m[id].t[i] == '>' && i<self->priv->msgs.m[id].l )
        i++;
    /* skip all line-feeds, carriage-returns and spaces */
    while( ( self->priv->msgs.m[id].t[i] == ASCII_LF
          || self->priv->msgs.m[id].t[i] == ASCII_CR
          || self->priv->msgs.m[id].t[i] == ASCII_SP )
             && i<self->priv->msgs.m[id].l )
        i++;
    /* copy from here to end of message */
    while( i<self->priv->msgs.m[id].l )
    {
        self->priv->tmptxt[j] = self->priv->msgs.m[id].t[i];
        i++;
        j++;
    }
    self->priv->tmptxt[j]='\0';

    /* check if message body was retrieved */
    if( j == 0 )
    {
        /* copy whole message */
        gwp_messages_getMessageRaw( self, id );
    }

    /* done */
if( DEBUGOUTPUT ) g_message("DEBUG: getBody finished" );
    return( self->priv->tmptxt );
}



char *gwp_messages_getMessageSubject( GwpMessages *self, int id )
{
if( DEBUGOUTPUT ) g_message("DEBUG: getSub called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

    /* check for valid message id */
    gwp_messages_checkValidMessageId( self, &id );
    self->priv->currMsg = id;

    /* create text to be returned */
    self->priv->tmptxt[0] = '\0';
    int i=0, j=0;
    while( self->priv->msgs.m[id].t[i] != '<' && i<self->priv->msgs.m[id].l )
        i++;
    while( self->priv->msgs.m[id].t[i] == '<' && i<self->priv->msgs.m[id].l )
        i++;
    while( self->priv->msgs.m[id].t[i] == ' ' && i<self->priv->msgs.m[id].l )
        i++;
    while( self->priv->msgs.m[id].t[i] != '>' && i<self->priv->msgs.m[id].l )
    {
        self->priv->tmptxt[j] = self->priv->msgs.m[id].t[i];
        i++;
        j++;
    }
    while( self->priv->tmptxt[j-1] == ' ' )
        j--;
    self->priv->tmptxt[j] = '\0';

    /* check if subject is empty */
    if( j==0 )
    {
        /* get the long header instead */
        gwp_messages_getMessageHeaderLong( self, id );
    }

    /* done */
if( DEBUGOUTPUT ) g_message("DEBUG: getSub finished" );
    return( self->priv->tmptxt );
}



char *gwp_messages_getMessageHeader( GwpMessages *self, int id )
{
if( DEBUGOUTPUT ) g_message("DEBUG: getHead called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

    /* check for valid message id */
    gwp_messages_checkValidMessageId( self, &id );
    self->priv->currMsg = id;

    /* create text to be returned */
    self->priv->tmptxt[0] = '\0';
    int i=0, j=0;
    if( self->priv->msgs.m[id].t[0] == '(' )
        i++;
    else while( self->priv->msgs.m[id].t[i] != '(' && i<self->priv->msgs.m[id].l )
        i++;
    while( self->priv->msgs.m[id].t[i] != ')' && i<self->priv->msgs.m[id].l )
    {
        self->priv->tmptxt[j] = self->priv->msgs.m[id].t[i];
        i++;
        j++;
    }
    self->priv->tmptxt[j] = '\0';

    /* done */
if( DEBUGOUTPUT ) g_message("DEBUG: getHead finished" );
    return( self->priv->tmptxt );
}



char *gwp_messages_getMessageHeaderLong( GwpMessages *self, int id )
{
if( DEBUGOUTPUT ) g_message("DEBUG: getHeadLong called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

    /* check for valid message id */
    gwp_messages_checkValidMessageId( self, &id );
    self->priv->currMsg = id;

    /* get header code */
    char *header;
    header = (char *)malloc(128*sizeof(char));
    header[0] = '\0';
    strncat( header, gwp_messages_getMessageHeader( self, id ), 127 );

    /* create text to be returned */
    self->priv->tmptxt[0] = '\0';
    switch( header[1] )
    {
        case '9':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Race-specific Mission at planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'a':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Message from 3rd-party add-on, from #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'c':
            if( header[2] == '0' )
            {
                if( header[5] == header[4] == header[3] == '\0' )
                    strcat( self->priv->tmptxt, "Priority Points or Ship attacks" );
                else
                {
                    strcat( self->priv->tmptxt, "Tim Continuum attacking planet #" );
                    self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                    self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                    self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                    self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                }
                break;
            }
        case 'd':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Ship/Starbase built at planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
            else
            {
                strcat( self->priv->tmptxt, "Ship of race '" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[2];
                strcat( self->priv->tmptxt, "' surrendered at planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'e':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Emergency call from ship #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'f':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Ship or planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                strcat( self->priv->tmptxt, " has been destroyed or captured" );
                break;
            }
        case 'g':
            if( header[5] == header[4] == header[3] == header[2] == '\0' )
            {
                strcat( self->priv->tmptxt, "Host Configuration" );
                break;
            }
        case 'h':
            if( /*header[5] ==*/ header[4] == header[3] == header[2] == '\0' )
            {
                strcat( self->priv->tmptxt, "External Message" );
                break;
            }
        case 'i':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Ion Storm #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'l':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Minefield #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                strcat( self->priv->tmptxt, " laid" );
                break;
            }
        case 'm':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Minefield #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                strcat( self->priv->tmptxt, " scanned/swept" );
                break;
            }
        case 'n':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Intercepted Enemy Message (ship #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                strcat( self->priv->tmptxt, " hit a mine or planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                strcat( self->priv->tmptxt, " being pillaged/RGAed)" );
                break;
            }
        case 'p':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Message from planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
            else
            {
                strcat( self->priv->tmptxt, "Bad climate, overtaxed or new native life (" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[2];
                strcat( self->priv->tmptxt, "), at planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'r':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Anonymous Message" );
                break;
            }
            else
            {
                strcat( self->priv->tmptxt, "Message from race " );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[2];
                break;
            }
        case 's':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Message from ship #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 't':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Terraform status on planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'u':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Message about UFO #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+4] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[3];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[2];
                break;
            }
        case 'w':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Web-Mine hit on ship #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'x':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Explosion on long range sensors, sequence number #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'y':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "Meteor impact on planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        case 'z':
            if( header[2] == '0' )
            {
                strcat( self->priv->tmptxt, "(Bio-)Scanner report on planet #" );
                self->priv->tmptxt[strlen(self->priv->tmptxt)+3] = '\0';
                self->priv->tmptxt[strlen(self->priv->tmptxt)+2] = header[5];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+1] = header[4];
                self->priv->tmptxt[strlen(self->priv->tmptxt)+0] = header[3];
                break;
            }
        default:
            g_message( "# Warning: 'getMessageHeaderLong': unknown message header '%s'", header );
            break;
    }

    /* done */
    free( header );
if( DEBUGOUTPUT ) g_message("DEBUG: getHeadLong finished" );
    return( self->priv->tmptxt );
}



bool gwp_messages_messageIsOld( GwpMessages *self, int id )
{
if( DEBUGOUTPUT ) g_message("DEBUG: isOld called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

    char *header;
    bool retval = false;
    header = (char *)malloc(128*sizeof(char));
    header[0] = '\0';
    strncat( header, gwp_messages_getMessageHeader( self, id ), 127 );
    switch( header[0] )
    {
        case '-':
            retval = false;
            break;
        case 'o':
            retval = true;
            break;
        default:
            g_message( "# Warning: GwpFileMdatax::messageIsOld: unknown message id '%s'", header );
            retval = true;
            break;
    }

    /* done */
    free( header );
if( DEBUGOUTPUT ) g_message("DEBUG: isOld finished" );
    return( retval );
}



int gwp_messages_readWord( GwpMessages *self, FILE *from )
{
    int retval;
    retval = (int)fgetc( from );
    retval += 256 * (int)fgetc( from );
    return( retval );
}



long gwp_messages_readDWord( GwpMessages *self, FILE *from )
{
    long retval;
    retval = (int)fgetc( from );
    retval += 256 * (int)fgetc( from );
    retval += 256 * 256 * (int)fgetc( from );
    retval += 256 * 256 * 256 * (int)fgetc( from );
    return( retval );
}


int gwp_messages_getMessageIdFirst( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: getfirstid called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

    int retval = 0;
if( DEBUGOUTPUT ) g_message("DEBUG: getfirstid finished" );
    return( retval );
}


int gwp_messages_getMessageIdLast( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: getlastid called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

    int retval = self->priv->numberOfMessages-1;
if( DEBUGOUTPUT ) g_message("DEBUG: getlastid finished" );
    return( retval );
}


int gwp_messages_getMessageIdNext( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: getnextid called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

    int retval = self->priv->currMsg + 1;
    if( retval >= self->priv->numberOfMessages-1 ) retval = self->priv->numberOfMessages-1;
if( DEBUGOUTPUT ) g_message("DEBUG: getnextid finished" );
    return( retval );
}


int gwp_messages_getMessageIdPrev( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: getprevid called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

    int retval = self->priv->currMsg - 1;
    if( retval < 0 ) retval = 0;
if( DEBUGOUTPUT ) g_message("DEBUG: getprevid finished" );
    return( retval );
}

int gwp_messages_getMessageIdCurrent( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: getcurrid called" );
    /* check if file was already read */
    if( !self->priv->fileRead )
        gwp_messages_readFileAny( self );

if( DEBUGOUTPUT ) g_message("DEBUG: getcurrid finished" );
    return( self->priv->currMsg );
}

void gwp_messages_nextMsg( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: nextmsg called" );
    self->priv->currMsg++;
    if( self->priv->currMsg >= self->priv->numberOfMessages )
        self->priv->currMsg = self->priv->numberOfMessages - 1;
if( DEBUGOUTPUT ) g_message("DEBUG: nextmsg finished" );
}


void gwp_messages_prevMsg( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: prevmsg called" );
    self->priv->currMsg--;
    if( self->priv->currMsg < 0 )
        self->priv->currMsg = 0;
if( DEBUGOUTPUT ) g_message("DEBUG: prevmsg finished" );
}


void gwp_messages_firstMsg( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: firstmsg called" );
    self->priv->currMsg = 0;
if( DEBUGOUTPUT ) g_message("DEBUG: firstmsg finished" );
}


void gwp_messages_lastMsg( GwpMessages *self )
{
if( DEBUGOUTPUT ) g_message("DEBUG: lastmsg called" );
    self->priv->currMsg = self->priv->numberOfMessages - 1;
if( DEBUGOUTPUT ) g_message("DEBUG: lastmsg finished" );
}
