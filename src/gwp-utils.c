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

#include "gwp-ship.h"
#include "gwp-utils.h"

/**
 * HIGified wrapper for warning dialogs.
 *
 * @param parent the dialog's parent window.
 * @param short_msg the dialog's main message string.
 * @param long_msg the dialog's additional message string.
 * @return The newly created dialog.
 */
GtkWidget * gwp_warning_dialog_new (GtkWidget *parent, 
				    const gchar *short_msg, 
				    const gchar *long_msg)
{
  g_assert (GTK_IS_WIDGET(parent));
  GtkWidget *warn = NULL;
  gchar *complete_msg = NULL;

  if (short_msg) {
    if (long_msg) {
      complete_msg = g_strdup_printf ("%s\n\n%s", short_msg, long_msg);

      /* FIXME: This should be used when migrating to gtk 2.4, HIG compatible
      complete_msg = g_strdup_printf ("<span weight=\"bold\" size=\"larger\">%s</span>\n\n%s", short_msg, long_msg);
      */
    } else {
      complete_msg = g_strdup_printf ("%s", short_msg);

      /* FIXME: This should be used when migrating to gtk 2.4, HIG compatible
      complete_msg = g_strdup_printf ("<span weight=\"bold\" size=\"larger\">%s</span>", short_msg); 
      */
    }
    warn = gtk_message_dialog_new ((GtkWindow *) parent,
				   GTK_DIALOG_DESTROY_WITH_PARENT,
				   GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE,
				   complete_msg);

    /* FIXME: This should be used when migrating to gtk 2.4, HIG compatible
    warn = gtk_message_dialog_new_with_markup ((GtkWindow *) parent,
					       GTK_DIALOG_DESTROY_WITH_PARENT,
					       GTK_MESSAGE_WARNING, 
					       GTK_BUTTONS_CLOSE,
					       complete_msg);
    */
  }
  return warn;
}

/**
 * Return a list of my own ship objects.
 */
void gwp_lists_get_own_ships (GSList *ships)
{
  /* Private func */
  static void insert_my_ships (gpointer key, 
			       gpointer value, 
			       gpointer own_ships)
    {
      GwpShip *ship = GWP_SHIP(value);
      GSList *list = (GSList *) own_ships;
      if (gwp_ship_is_mine(ship)) {
	list = g_slist_insert (list, ship, -1);
      }
      g_message("mis naves: %d", g_slist_length(list));
    }
  
  g_hash_table_foreach (ship_list, (GHFunc) insert_my_ships, &ships);
}

