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
#include "gwp-ui.h"
#include "support.h"

/*
 * Private members.
 */
struct _GwpUiPrivate {
  gboolean dispose_has_run;
};

/*
 * forward definitions.
 */
static void gwp_ui_init (GTypeInstance *instance, gpointer g_class);
static void gwp_ui_class_init (GwpUiClass *klass);

GType gwp_ui_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpUiClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_ui_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpUi),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_ui_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpUi",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_ui_init (GTypeInstance *instance,
			 gpointer       g_class)
{
  GwpUi *self = (GwpUi *)instance;
  self->priv = g_new0 (GwpUiPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
}

static void gwp_ui_dispose (GwpUi *self)
{
  if(self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
}

static void gwp_ui_finalize (GwpUi *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_ui_class_init (GwpUiClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  /* Register destructor methods. */
  gobject_class->dispose = (void *)gwp_ui_dispose;
  gobject_class->finalize = (void *)gwp_ui_finalize;
}

/* 
 * Public method implementations.
 */
GwpUi * gwp_ui_new (void)
{
  return g_object_new (gwp_ui_get_type (), NULL);
}

/**********************/
/* High-level methods */
/**********************/
void gwp_ui_set_notification (GwpUi *self, gchar *msg)
{
  static GtkWidget *notif = NULL;
  static GtkWidget *btn = NULL;
  static gboolean loaded = FALSE;
  GtkTooltips *tt = gtk_tooltips_new ();

  g_assert (GWP_IS_UI(self));
  g_assert (msg != NULL);

  if (!loaded) {
    notif = lookup_widget ("image_noti");
    btn = lookup_widget ("btn_noti");
    loaded = TRUE;
  }
  gtk_tooltips_enable (tt);
  gtk_tooltips_set_tip (tt, notif,
			msg,
			"Este es el mas groso de todos los tt.");

  gtk_tooltips_set_tip (tt, btn,
			msg,
			"Este es el mas grosssssssso de todos los tt.");

}

/*******************/
/* Get-Set methods */
/*******************/
