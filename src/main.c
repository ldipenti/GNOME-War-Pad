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


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>
#include "support.h"

// My includes
#include "callbacks.h"
#include "global.h"
#include "vp_types.h"
#include "vp_utils.h"
#include "starchart.h"
#include "race_select.h"
#include "game_state.h"

#define GWP_GLADE_XML_FILE GWP_GLADE_XML_DIR"/gwp.glade"

int main (int argc, char *argv[]) {

#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif

  gwp = NULL;
  gwp_select_race_dialog = NULL;
  game_mgr = NULL;
  game_mgr_properties = NULL;

  gnome_program_init(PACKAGE, VERSION, LIBGNOMEUI_MODULE,
		     argc, argv,
		     GNOME_PARAM_APP_DATADIR, PACKAGE_DATA_DIR,
		     NULL);
  
  // Libglade init
  glade_gnome_init();
  xml_interface = glade_xml_new(GWP_GLADE_XML_FILE, NULL, NULL);
  g_assert(xml_interface != NULL);

  glade_xml_signal_autoconnect(xml_interface);
  
  // Now we look where those widgets are...
  gwp = glade_xml_get_widget(xml_interface, "gwp");
  g_assert(gwp != NULL);

  game_mgr = glade_xml_get_widget(xml_interface, "game_mgr");
  g_assert(game_mgr != NULL);

  game_mgr_properties = glade_xml_get_widget(xml_interface, "game_mgr_properties");
  g_assert(game_mgr_properties != NULL);

  /* Esto lo sacamos para darle lugar al manager mejorado
  gwp_select_race_dialog = glade_xml_get_widget(xml_interface,
						"gwp_select_race_dialog");
  g_assert(gwp_select_race_dialog != NULL);
  */
  
  // Initialisations
  gnome_config_push_prefix("/gwp/");
  game_init_dir(gnome_config_get_string("General/game_dir=\"\""));
  //init_select_dlg(gwp_select_race_dialog);
  

  /* Game Properties Dialog Init */
  {
    GtkTreeView *race_list;
    GtkListStore *store;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    
    race_list = (GtkTreeView*) lookup_widget("game_mgr_properties_race_list");
    store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Races", 
						      renderer,
						      "text", 0,
						      NULL);
    gtk_tree_view_set_model(race_list, GTK_TREE_MODEL(store));
    gtk_tree_view_append_column(race_list, column);
    // Clear the dialog
    //game_mgr_properties_dlg_clean();
}

  // Show it!
  //gtk_widget_show(gwp_select_race_dialog);
  gtk_widget_show(game_mgr);
  
  gtk_main();
  
  return 0;
}
