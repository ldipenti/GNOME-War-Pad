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

#ifdef USE_PYTHON

#include <pygobject.h>
#include <pygtk/pygtk.h> /* WARNING: this *MUST* be after pygobject.h */

#include "gwp-python.h"
#include "gwp-ship.h"
#include "support.h"
#include "global.h"

/* Forwards */
void initgwp (void);
void gwp_register_classes (PyObject *d);

/**
 * Python embedded interpreter initialization.
 *
 * @param argv0 the program's name.
 */
void gwp_python_init (char *argv0)
{
  Py_SetProgramName (argv0);
  Py_Initialize ();

  /* Adding static modules */
  initgwp();
}

/**
 * Initializes the plugin structure for the loaded game.
 *
 * This function is executed every time a game is loaded, beware of this
 * 'little' detail...when closing any game we should clean the mess made by
 * all this code.
 */
void gwp_python_inittab (void)
{
  FILE *script;
  GtkWidget *plugin_menu = NULL;
  GtkWidget *plugin_menu_root = NULL;
  GtkWidget *menubar = NULL;
  PyObject *plugin_mgr = NULL;
  PyObject *pyobj_menu = NULL;

  /* Load 'inittab' script */
  script = fopen (GWP_SCRIPTS_DIR"/inittab.py", "r");
  PyRun_SimpleFile (script, "inittab.py");
  fclose (script);

  /* Configure the plugins menu item and pass it to the PluginManager */
  plugin_menu = gtk_menu_new ();
  plugin_menu_root = gtk_menu_item_new_with_mnemonic (_("_Plugins"));
  gtk_widget_show (plugin_menu_root);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (plugin_menu_root), plugin_menu);

  menubar = lookup_widget ("menubar");
  gtk_menu_bar_append (menubar, plugin_menu_root);

  pyobj_menu = pygobject_new (plugin_menu);
  plugin_mgr = (PyObject *)game_get_plugin_mgr (game_state);
  
  PyObject_CallMethodObjArgs (plugin_mgr,
			      PyString_FromString("set_menu"),
			      pyobj_menu, NULL);
  Py_DECREF (pyobj_menu);

  /* Load and register 'navigator' plugin */
  script = fopen (GWP_SCRIPTS_DIR"/navigator.py", "r");
  PyRun_SimpleFile (script, "navigator.py");
  fclose (script);
}

/**
 * Bye bye, plugin system...
 */
void gwp_python_quit (void)
{
  Py_Exit (0);
}

/* Include the generated type mappings */
#include "gwp-py-mappings.c"

void initgwp (void)
{
  PyObject *m, *d;

  init_pygtk ();
  init_pygobject ();

  PyImport_AddModule ("gwp");

  m = Py_InitModule ("gwp", gwp_functions);
  d = PyModule_GetDict (m);

  gwp_register_classes (d);

  if (PyErr_Occurred ()) {
    Py_FatalError ("can't initialise module gwp");
  }
}

void gwp_python_event_key (GdkEventKey *event)
{
  PyObject *plugin_mgr = NULL;
  PyObject *evt_data;

  g_assert (event != NULL);

  evt_data = Py_BuildValue ("{sisisiss}",
			    "type", (int)event->type,
			    "state", (int)event->state,
			    "keyval", (int)event->keyval,
			    "string", event->string);

  if (evt_data) {
    plugin_mgr = (PyObject *)game_get_plugin_mgr (game_state);
    
    PyObject_CallMethodObjArgs (plugin_mgr,
				PyString_FromString("manage_event_key"),
				evt_data,
				NULL);
    Py_DECREF (evt_data);
  }
}

#endif /* USE_PYTHON */
