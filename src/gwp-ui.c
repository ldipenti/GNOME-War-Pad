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

#include "gwp-ui.h"
#include "global.h"
#include "support.h"



/* FIXME: Test concept function, to make a notification area for plugins */
void gwp_ui_set_notification (gchar *msg)
{
  static GtkWidget *notif = NULL;
  static GtkWidget *btn = NULL;
  static gboolean loaded = FALSE;
  static const gchar *icon[] = {"16 16 6 1",
				"       c None",
				".      c #000000",
				"+      c #0000FF",
				"@      c #008080",
				"#      c #C0C0C0",
				"$      c #808080",
				"       ..       ",
				"     ..++.      ",
				"   ..+++++.     ",
				" ..++++++++.    ",
				".@#+++++++++.   ",
				".+@#+++++++++.  ",
				".++@#+++++++++. ",
				".+++@#++++++++..",
				".++++@#+++++..@$",
				" .++++@#++..@#@$",
				"  .++++@..@###..",
				"   .+++.@####.. ",
				"    .++.###..   ",
				"     .+.@..     ",
				"      ...       ",
				"                "};
  
  GdkPixmap *pixmap;
  GdkBitmap *mask;

  GtkTooltips *tt = gtk_tooltips_new ();

  g_assert (msg != NULL);

  if (!loaded) {
    notif = lookup_widget ("image_noti");
    btn = lookup_widget ("btn_noti");
    loaded = TRUE;
  }

  pixmap = gdk_pixmap_create_from_xpm_d (btn->window, &mask, NULL, &icon);
  gtk_image_set_from_pixmap (GTK_IMAGE(notif), pixmap, mask);

  gtk_tooltips_enable (tt);
  gtk_tooltips_set_tip (tt, notif,
			msg,
			"Este es el mas groso de todos los tt.");

  gtk_tooltips_set_tip (tt, btn,
			msg,
			"Este es el mas grosssssssso de todos los tt.");

}

