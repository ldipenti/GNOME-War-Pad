/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002 Lucas Di Pentima <lucas@lunix.com.ar>
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
#define GTK_DISABLE_DEPRECATED
#define GNOME_DISABLE_DEPRECATED

#include <gnome.h>
#include "support.h"
#include "global.h"
#include "race_select.h"
#include "game_state.h"

void
init_select_dlg (GtkWidget * gwp_select_dlg)
{
  GtkEntry *game_dir_entry;

  game_dir_entry = (GtkEntry *) lookup_widget("vp_game_dir");
  g_assert(game_dir_entry != NULL);

  gtk_entry_set_text(game_dir_entry, 
  		     gnome_config_get_string("General/game_dir="));
  update_select_dlg(gwp_select_dlg);
}

void update_select_dlg (GtkWidget * gwp_select_dlg)
{
  GString *pdata, *pdata_lower, *ship, *button, *label;
  GtkWidget *btn_widget, *lbl_widget;
  gint i;
  ship = g_string_new ("SHIP");
  
  for (i = 1; i <= 11; i++) {
    pdata = g_string_new ("PDATA");
    pdata_lower = g_string_new ("");
    pdata = g_string_append (pdata, g_strdup_printf ("%d.DIS", i));
    pdata_lower = g_string_append (pdata_lower, pdata->str);
    pdata_lower = g_string_down (pdata_lower);
    
    button = g_string_new (g_strdup_printf ("button_race%d", i));
    label = g_string_new (g_strdup_printf("label_race%d", i));
    
    btn_widget = lookup_widget (button->str);
    lbl_widget = lookup_widget (label->str);
    
    if (g_file_test(game_get_full_path(pdata)->str,
		    G_FILE_TEST_EXISTS) || 
	g_file_test(game_get_full_path(pdata_lower)->str,
		    G_FILE_TEST_EXISTS)) {
      
      gtk_widget_set_sensitive (btn_widget, TRUE);
      gtk_widget_set_sensitive (lbl_widget, TRUE);
    } else {
      gtk_widget_set_sensitive (btn_widget, FALSE);
      gtk_widget_set_sensitive (lbl_widget, FALSE);
    }
  }
}
