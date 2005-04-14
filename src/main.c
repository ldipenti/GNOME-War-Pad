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
#ifdef USE_PYTHON
#  include "gwp-python.h"
#endif

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
void init_fc_widgets (void);

int main (int argc, char *argv[]) {

#ifdef ENABLE_NLS
  bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
  textdomain (PACKAGE);
#endif


#ifdef USE_PYTHON
  /* Python embedded interpreter initialization */
  gwp_python_init (argv[0]);
#endif

  /* Random number generation init */
  srand ((guint32) time(NULL));

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

  init_fc_widgets();
    
  /* Tables Init */
  table_all_init();
  init_ship_panel();
}

void gwp_init_splash(void)
{
  GtkImage *splash = (GtkImage *)lookup_widget("gwp_splash_image");

  gtk_image_set_from_file(splash, GWP_IMAGES_DIR"/gwp_splash.png");
  gtk_window_set_decorated(GTK_WINDOW(gwp_splash_screen), FALSE);

  /* FIXME: This is for GTK+ 2.2, we won't use it until is necessary

  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(gwp_splash_screen), TRUE);
  gtk_window_set_skip_pager_hint(GTK_WINDOW(gwp_splash_screen), TRUE);
  */
}

void
init_fc_widgets (void)
{
  GtkEntry *entry = NULL;
  GtkWidget *combo_planet_fc = lookup_widget ("combo_planet_fc");
  GtkWidget *combo_ship_fc = lookup_widget ("combo_ship_fc");
  GtkListStore *store = NULL;
  GtkTreeIter iter;
  gint i;
  GtkCellRenderer *renderer = NULL;
  gchar *planet_codes[][3] = {
    {"ATT", "<b>ATT</b> ", _("<i>Attack ships with fuel in orbit</i>")},
    {"NUK", "<b>NUK</b> ", _("<i>Attack any ship in orbit</i>")},
    {"bum", "<b>bum</b> ", _("<i>Beam up megacredits</i>")},
    {"con", "<b>con</b> ", _("<i>Get Host configuration settings</i>")},
  };

  gchar *ship_codes[][3] = {
    {"bdm", "<b>bdm</b> ", _("<i>Beam down megacredits</i>")},
    {"btf", "<b>btf</b> ", _("<i>Transfer fighters to ships at this location</i>")},
    {"btm", "<b>btm</b> ", _("<i>Transfer MC to ships at this location</i>")},
    {"btt", "<b>btt</b> ", _("<i>Transfer torpedoes to ships at this location</i>")},
    {"md1", "<b>md1</b> ", _("<i>Use 10 torpedoes to lay mine field</i>")},
    {"md2", "<b>md1</b> ", _("<i>Use 20 torpedoes to lay mine field</i>")},
    {"md3", "<b>md1</b> ", _("<i>Use 30 torpedoes to lay mine field</i>")},
    {"md4", "<b>md1</b> ", _("<i>Use 40 torpedoes to lay mine field</i>")},
    {"md5", "<b>md1</b> ", _("<i>Use 50 torpedoes to lay mine field</i>")},
    {"md6", "<b>md1</b> ", _("<i>Use 60 torpedoes to lay mine field</i>")},
    {"md7", "<b>md1</b> ", _("<i>Use 70 torpedoes to lay mine field</i>")},
    {"md8", "<b>md1</b> ", _("<i>Use 80 torpedoes to lay mine field</i>")},
    {"md9", "<b>md1</b> ", _("<i>Use 90 torpedoes to lay mine field</i>")},
    {"md0", "<b>md1</b> ", _("<i>Use 100 torpedoes to lay mine field</i>")},
    {"ee1", "<b>ee1</b> ", _("<i>Cancel alliance with The Feds</i>")},
    {"ee2", "<b>ee2</b> ", _("<i>Cancel alliance with The Lizards</i>")},
    {"ee3", "<b>ee3</b> ", _("<i>Cancel alliance with The Bird Men</i>")},
    {"ee4", "<b>ee4</b> ", _("<i>Cancel alliance with The Fascists</i>")},
    {"ee5", "<b>ee5</b> ", _("<i>Cancel alliance with The Privateers</i>")},
    {"ee6", "<b>ee6</b> ", _("<i>Cancel alliance with The Cyborgs</i>")},
    {"ee7", "<b>ee7</b> ", _("<i>Cancel alliance with The Crystal People</i>")},
    {"ee8", "<b>ee8</b> ", _("<i>Cancel alliance with The Evil Empire</i>")},
    {"ee9", "<b>ee9</b> ", _("<i>Cancel alliance with The Robots</i>")},
    {"eea", "<b>eea</b> ", _("<i>Cancel alliance with The Rebels</i>")},
    {"eeb", "<b>eeb</b> ", _("<i>Cancel alliance with The Colonies</i>")},
    {"ff1", "<b>ff1</b> ", _("<i>Offer/accept alliance with The Feds</i>")},
    {"ff2", "<b>ff2</b> ", _("<i>Offer/accept alliance with The Lizards</i>")},
    {"ff3", "<b>ff3</b> ", _("<i>Offer/accept alliance with The Bird Men</i>")},
    {"ff4", "<b>ff4</b> ", _("<i>Offer/accept alliance with The Fascists</i>")},
    {"ff5", "<b>ff5</b> ", _("<i>Offer/accept alliance with The Privateers</i>")},
    {"ff6", "<b>ff6</b> ", _("<i>Offer/accept alliance with The Cyborgs</i>")},
    {"ff7", "<b>ff7</b> ", _("<i>Offer/accept alliance with The Crystal People</i>")},
    {"ff8", "<b>ff8</b> ", _("<i>Offer/accept alliance with The Evil Empire</i>")},
    {"ff9", "<b>ff9</b> ", _("<i>Offer/accept alliance with The Robots</i>")},
    {"ffa", "<b>ffa</b> ", _("<i>Offer/accept alliance with The Rebels</i>")},
    {"feb", "<b>ffb</b> ", _("<i>Offer/accept alliance with The Colonies</i>")},
    {"gs1", "<b>gs1</b> ", _("<i>Give ship to The Feds</i>")},
    {"gs2", "<b>gs2</b> ", _("<i>Give ship to The Lizards</i>")},
    {"gs3", "<b>gs3</b> ", _("<i>Give ship to The Bird Men</i>")},
    {"gs4", "<b>gs4</b> ", _("<i>Give ship to The Fascists</i>")},
    {"gs5", "<b>gs5</b> ", _("<i>Give ship to The Privateers</i>")},
    {"gs6", "<b>gs6</b> ", _("<i>Give ship to The Cyborgs</i>")},
    {"gs7", "<b>gs7</b> ", _("<i>Give ship to The Crystal People</i>")},
    {"gs8", "<b>gs8</b> ", _("<i>Give ship to The Evil Empire</i>")},
    {"gs9", "<b>gs9</b> ", _("<i>Give ship to The Robots</i>")},
    {"gsa", "<b>gsa</b> ", _("<i>Give ship to The Rebels</i>")},
    {"gsb", "<b>gsb</b> ", _("<i>Give ship to The Colonies</i>")},
    {"HYP", "<b>HYP</b> ", _("<i>Activate Hyperdrive</i>")},
    {"NTP", "<b>NTP</b> ", _("<i>Don't use fighters or torps in battle</i>")},
    {"pop", "<b>pop</b> ", _("<i>Explode Glory Device after movement</i>")},
    {"trg", "<b>trg</b> ", _("<i>Explode Glory Device when detecting a cloaked ship</i>")},
  };
  
  /* Configure FC's GtkEntrys (max 3 chars) */
  entry = GTK_ENTRY (GTK_BIN(combo_planet_fc)->child);
  gtk_entry_set_max_length (entry, 3);
  entry = GTK_ENTRY (GTK_BIN(combo_ship_fc)->child);
  gtk_entry_set_max_length (entry, 3);

  /*** Configure default set of Planet's FCs ***/
  store = gtk_list_store_new (3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  /* 4 different planetary FCodes */
  for (i = 0; i < 4; i++) {
    gtk_list_store_append (store, &iter);
    gtk_list_store_set (store, &iter,
			0, planet_codes[i][0],
			1, planet_codes[i][1],
			2, planet_codes[i][2],
			-1);
  }

  gtk_combo_box_set_model (GTK_COMBO_BOX(combo_planet_fc),
			   GTK_TREE_MODEL(store));

  gtk_cell_layout_clear(GTK_CELL_LAYOUT(combo_planet_fc));

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT(combo_planet_fc), 
			      renderer, FALSE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo_planet_fc), 
				  renderer,
				  "markup", 1,
				  NULL);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT(combo_planet_fc), 
			      renderer, FALSE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo_planet_fc), 
				  renderer,
				  "markup", 2,
				  NULL);


  /*** Configure default set of Planet's FCs ***/
  store = gtk_list_store_new (3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  /* 51 different ship FCodes */
  for (i = 0; i < 41; i++) {
    gtk_list_store_append (store, &iter);
    gtk_list_store_set (store, &iter,
			0, ship_codes[i][0],
			1, ship_codes[i][1],
			2, ship_codes[i][2],
			-1);
  }

  gtk_combo_box_set_model (GTK_COMBO_BOX(combo_ship_fc),
			   GTK_TREE_MODEL(store));

  gtk_cell_layout_clear(GTK_CELL_LAYOUT(combo_ship_fc));

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT(combo_ship_fc), 
			      renderer, FALSE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo_ship_fc), 
				  renderer,
				  "markup", 1,
				  NULL);

  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT(combo_ship_fc), 
			      renderer, FALSE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo_ship_fc), 
				  renderer,
				  "markup", 2,
				  NULL);
}
