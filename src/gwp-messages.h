/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2004  Lucas Di Pentima <lucas@lunix.com.ar>
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

/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.13  2005/05/31 13:17:38  ldipenti
    Feature: Added CVS metadata on source files

*/

/*
 * GwpMessages:
 * ---------
 *
 * Read the Planet Messages
 */

#ifndef GWP_MESSAGES_H
#define GWP_MESSAGES_H

#include <glib.h>
#include <glib-object.h>

enum{
  GWP_MESSAGE_IS_NORMAL,
  GWP_MESSAGE_IS_URGENT,
  GWP_MESSAGE_IS_INTERESTING,
  GWP_MESSAGE_IS_POSITIVE,
  GWP_MESSAGE_IS_NEGATIVE
};

typedef struct
{
  long a;  /**< Message address+1 in MDATA */
  int l;   /**< Message length in bytes */
  char *t; /**< Message contents */
  char *p; /**< Message path (?) */
} mdataMessage;

typedef struct
{
  int n;           /**< Number of messages */
  mdataMessage *m; /**< Messages array */
} mdataMessages;

/*
 * Type macros.
 */

typedef struct _GwpMessages GwpMessages;
typedef struct _GwpMessagesClass GwpMessagesClass;
typedef struct _GwpMessagesPrivate GwpMessagesPrivate;
typedef struct _GwpMessagesPublic {
  gint *msgindex;
  gboolean *msgexists;
  gint *msgnmb;
} GwpMessagesPublic;

struct _GwpMessages {
  GObject parent;

  /* instance members */

  /* private */
  GwpMessagesPrivate *priv;
  GwpMessagesPublic *pub;
};

struct _GwpMessagesClass {
  GObjectClass parent;
  /* class members */
};

/* used by GWP_MESSAGES_TYPE */
GType gwp_messages_get_type (void);

/*
 * Public method definitions.
 */
GwpMessages *gwp_messages_new (void);

/*******************/
/* Get-Set methods */
/*******************/
gboolean gwp_messages_checkValidMessageId( GwpMessages *self, int *id );
int gwp_messages_readFileAny( GwpMessages *self );
int gwp_messages_readFile( GwpMessages *self, char *filename );
int gwp_messages_getNumberOfMessages( GwpMessages *self );
char *gwp_messages_getMessageRaw( GwpMessages *self, int id );
char *gwp_messages_getMessageBody( GwpMessages *self, int id );
char *gwp_messages_getMessageSubject( GwpMessages *self, int id );
char *gwp_messages_getMessageHeader( GwpMessages *self, int id );
char *gwp_messages_getMessageHeaderLong( GwpMessages *self, int id );
char *gwp_messages_getMessageCategory( GwpMessages *self, int id );
gint gwp_messages_getSubjectColour( GwpMessages *self, gint id );
gboolean gwp_messages_messageIsOld( GwpMessages *self, int id );
int gwp_messages_getMessageIdFirst( GwpMessages *self );
int gwp_messages_getMessageIdLast( GwpMessages *self );
int gwp_messages_getMessageIdNext( GwpMessages *self );
int gwp_messages_getMessageIdPrev( GwpMessages *self );
int gwp_messages_getMessageIdCurrent( GwpMessages *self );
void gwp_messages_nextMsg( GwpMessages *self );
void gwp_messages_prevMsg( GwpMessages *self );
void gwp_messages_firstMsg( GwpMessages *self );
void gwp_messages_lastMsg( GwpMessages *self );
void gwp_messages_setCurrMsgId( GwpMessages *self, gint id );
void gwp_messages_sortByCategory( GwpMessages *self );
char *gwp_messages_getMessagePath( GwpMessages *self, gint id );
void gwp_messages_setMessagePath( GwpMessages *self, gint id, char *path );
gboolean gwp_messages_grepMessage( gchar *message, gchar *text );
gint gwp_messages_getMessagesNumber (GwpMessages *self);

/*
 * Standard defines.
 */
#define GWP_MESSAGES_TYPE            (gwp_messages_get_type())
#define GWP_MESSAGES(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GWP_MESSAGES_TYPE, GwpMessages))
#define GWP_MESSAGES_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GWP_MESSAGES_TYPE, GwpMessageClass))
#define GWP_IS_MESSAGES(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GWP_MESSAGES_TYPE))
#define GWP_IS_MESSAGES_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GWP_MESSAGES_TYPE))
#define GWP_MESSAGES_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GWP_MESSAGES_TYPE, GwpMessagesClass))

#endif
