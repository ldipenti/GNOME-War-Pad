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
#include "game_state.h"
#include "game_mgr.h"

#define GWP_GLADE_XML_FILE GWP_GLADE_XML_DIR"/gwp.glade"

// Prototypes
void gwp_init(void);
void gwp_init_splash(void);

int main (int argc, char *argv[]) {

#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif

  gwp = NULL;
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
  
  // Init & show splash screen
  gwp_splash_screen = glade_xml_get_widget(xml_interface, "gwp_splash_screen");
  g_assert(gwp_splash_screen);
  gwp_init_splash();
  gtk_widget_show(gwp_splash_screen);

  // Now we look where those widgets are...
  gwp = glade_xml_get_widget(xml_interface, "gwp");
  g_assert(gwp != NULL);

  game_mgr = glade_xml_get_widget(xml_interface, "game_mgr");
  g_assert(game_mgr != NULL);

  game_mgr_properties = glade_xml_get_widget(xml_interface,
					     "game_mgr_properties");
  g_assert(game_mgr_properties != NULL);

  // Initialisations
  gwp_init();
  
  // Hide splash screen & show game manager
  gtk_widget_hide(gwp_splash_screen);
  gtk_widget_show(game_mgr);

  // Enter main loop  
  gtk_main();
  
  return 0;
}

void gwp_init(void) 
{
  /* Gnome Config Init */
  gnome_config_push_prefix("/gwp/");

  //game_init_dir(gnome_config_get_string("General/game_dir=\"\""));

  /* Game Properties Dialog Init */
  game_mgr_init();
}

void gwp_init_splash(void)
{
  GtkImage *splash = (GtkImage *)lookup_widget("gwp_splash_image");

  gtk_image_set_from_file(splash, GWP_IMAGES_DIR"/gwp_splash.png");
  gtk_window_set_decorated(GTK_WINDOW(gwp_splash_screen), FALSE);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(gwp_splash_screen), TRUE);
  gtk_window_set_skip_pager_hint(GTK_WINDOW(gwp_splash_screen), TRUE);
}
