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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

/* This should be the first include, because of the Python.h */
#include "gwp-python.h"

#include <gnome.h>

#include "support.h"
#include "callbacks.h"
#include "global.h"
#include "vp_types.h"
#include "vp_utils.h"
#include "starchart.h"
#include "game_mgr.h"
#include "tables.h"

#define GWP_GLADE_XML_FILE GWP_GLADE_XML_DIR"/gwp.glade"

/* Prototypes */
void gwp_init(void);
void gwp_init_splash(void);


int main (int argc, char *argv[]) {

#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif


#ifdef USE_PYTHON
  /* Python embedded interpreter initialization */
  gwp_python_init (argv[0]);
#endif

  gwp = NULL;
  game_mgr = NULL;
  game_mgr_properties = NULL;

  gnome_program_init(PACKAGE, VERSION, LIBGNOMEUI_MODULE,
		     argc, argv,
		     /*GNOME_PARAM_APP_DATADIR, PACKAGE_DATA_DIR,*/
		     GNOME_PROGRAM_STANDARD_PROPERTIES,
		     NULL);
  
  /* Libglade init */
  glade_gnome_init();
  xml_interface = glade_xml_new(GWP_GLADE_XML_FILE, NULL, NULL);
  g_assert(xml_interface != NULL);

  glade_xml_signal_autoconnect(xml_interface);
  
  /* Init & show splash screen */
  /*
  gwp_splash_screen = glade_xml_get_widget(xml_interface, "gwp_splash_screen");
  g_assert(gwp_splash_screen);
  gwp_init_splash();
  gtk_widget_show(gwp_splash_screen);
  */

  /* Now we look where those widgets are... */
  gwp = glade_xml_get_widget(xml_interface, "gwp");
  g_assert(gwp != NULL);

  game_mgr = glade_xml_get_widget(xml_interface, "game_mgr");
  g_assert(game_mgr != NULL);

  game_mgr_properties = glade_xml_get_widget(xml_interface,
					     "game_mgr_properties");
  g_assert(game_mgr_properties != NULL);

  wait_notice = glade_xml_get_widget(xml_interface, "wait_notice");
  g_assert (wait_notice != NULL);

  /* Initialisations */
  g_type_init(); /* GLib's type system */
  gwp_init();

  /* Hide splash screen & show game manager */
  /* gtk_widget_hide(gwp_splash_screen); */
  gtk_widget_show(game_mgr);

  /* Enter main loop */
  gtk_main();
  
  return 0;
}

void gwp_init(void) 
{
  GtkWidget *notebk;

  /* Hide all tabs on notebooks */
  notebk = lookup_widget("extra_info_panel");
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebk), FALSE);
  notebk = lookup_widget("info_panel");
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebk), FALSE);
  notebk = lookup_widget("notebook_mini");
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebk), FALSE);
  notebk = lookup_widget("calc_panel");
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebk), FALSE);

  /* Hide panels */
  starchart_close_extra_panels();
  extra_panels_showed = FALSE;

  /* Game Properties Dialog Init */
  game_mgr_init();
    
  /* Tables Init */
  table_all_init();
  init_ship_panel();
}

void gwp_init_splash(void)
{
  GtkImage *splash = (GtkImage *)lookup_widget("gwp_splash_image");

  gtk_image_set_from_file(splash, GWP_IMAGES_DIR"/gwp_splash.png");
  gtk_window_set_decorated(GTK_WINDOW(gwp_splash_screen), FALSE);

  /* NOTE: This is for GTK+ 2.2, we won't use it until is necessary

  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(gwp_splash_screen), TRUE);
  gtk_window_set_skip_pager_hint(GTK_WINDOW(gwp_splash_screen), TRUE);
  */
}
