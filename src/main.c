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

int
main (int argc, char *argv[])
{

#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif

  gwp = NULL;
  gwp_select_race_dialog = NULL;

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

  gwp_select_race_dialog = glade_xml_get_widget(xml_interface,
						"gwp_select_race_dialog");
  g_assert(gwp_select_race_dialog != NULL);
  
  // Initialisations
  gnome_config_push_prefix("/gwp/");
  game_init_dir(gnome_config_get_string("General/game_dir=\"\""));
  init_select_dlg(gwp_select_race_dialog);
  
  // Show it!
  gtk_widget_show(gwp_select_race_dialog);
  
  gtk_main();
  
  return 0;
}
