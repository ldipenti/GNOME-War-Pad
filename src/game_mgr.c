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
#include "game_mgr.h"
#include "game_state.h"

void game_mgr_update_race_list(char *dir) 
{
  GString *pdata, *pdata_lower;
  GtkTreeView *race_list;
  int i;

  // If dir is some string, we work
  if(dir != NULL) {

    race_list = (GtkTreeView*)lookup_widget("game_mgr_properties_race_list");

    for (i = 1; i <= 11; i++) {
      pdata = g_string_new ("PDATA");
      pdata_lower = g_string_new ("");
      pdata = g_string_append (pdata, g_strdup_printf ("%d.DIS", i));
      g_string_prepend(pdata, dir);

      pdata_lower = g_string_append (pdata_lower, pdata->str);
      pdata_lower = g_string_down (pdata_lower);
      g_string_prepend(pdata_lower, dir);
      
      if (g_file_test(game_get_full_path(pdata)->str,
		      G_FILE_TEST_EXISTS) || 
	  g_file_test(game_get_full_path(pdata_lower)->str,
		      G_FILE_TEST_EXISTS)) {
	
	// Add available races to race list
	// FIXME
	
      }
      g_string_free(pdata, 1);
      g_string_free(pdata_lower, 1);
    }    
  }
}
