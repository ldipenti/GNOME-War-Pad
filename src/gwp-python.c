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
  GtkWidget *plugin_slot = NULL;
  PyObject *plugin_slot_pyobj = NULL;

  /* Load 'inittab' script */
  script = fopen (GWP_SCRIPTS_DIR"/inittab.py", "r");
  PyRun_SimpleFile (script, "inittab.py");
  fclose (script);

  plugin_mgr = (PyObject *)gwp_game_state_get_plugin_mgr (game_state);

  /* Configure the plugins menu item and pass it to the PluginManager */
  plugin_menu = gtk_menu_new ();
  plugin_menu_root = gtk_menu_item_new_with_mnemonic (_("_Plugins"));
  gtk_widget_show (plugin_menu_root);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (plugin_menu_root), plugin_menu);

  menubar = lookup_widget ("menubar");
  gtk_menu_bar_insert (menubar, plugin_menu_root, 2);

  pyobj_menu = pygobject_new ((GObject *)plugin_menu);  
  PyObject_CallMethodObjArgs (plugin_mgr,
			      PyString_FromString("_PluginManager__set_menu"),
			      pyobj_menu, NULL);
  Py_DECREF (pyobj_menu);

  /*** Pass plugin_slot_* references to PluginManager ***/
  /* Panel slot */
  plugin_slot = lookup_widget ("plugin_slot_panel");
  plugin_slot_pyobj = pygobject_new ((GObject *)plugin_slot);
  PyObject_CallMethodObjArgs (plugin_mgr,
			      PyString_FromString("_PluginManager__set_plugin_slot"),
			      PyString_FromString("plugin_slot_panel"),
			      plugin_slot_pyobj,
			      NULL);
  Py_DECREF (plugin_slot_pyobj);
  /* Planet panel slot */
  plugin_slot = lookup_widget ("plugin_slot_panel_planet");
  plugin_slot_pyobj = pygobject_new ((GObject *)plugin_slot);
  PyObject_CallMethodObjArgs (plugin_mgr,
			      PyString_FromString("_PluginManager__set_plugin_slot"),
			      PyString_FromString("plugin_slot_panel_planet"),
			      plugin_slot_pyobj,
			      NULL);
  Py_DECREF (plugin_slot_pyobj);
  /* Ship panel slot */
  plugin_slot = lookup_widget ("plugin_slot_panel_ship");
  plugin_slot_pyobj = pygobject_new ((GObject *)plugin_slot);
  PyObject_CallMethodObjArgs (plugin_mgr,
			      PyString_FromString("_PluginManager__set_plugin_slot"),
			      PyString_FromString("plugin_slot_panel_ship"),
			      plugin_slot_pyobj,
			      NULL);
  Py_DECREF (plugin_slot_pyobj);
  /* Left panel slot */
  plugin_slot = lookup_widget ("plugin_slot_left");
  plugin_slot_pyobj = pygobject_new ((GObject *)plugin_slot);
  PyObject_CallMethodObjArgs (plugin_mgr,
			      PyString_FromString("_PluginManager__set_plugin_slot"),
			      PyString_FromString("plugin_slot_left"),
			      plugin_slot_pyobj,
			      NULL);
  Py_DECREF (plugin_slot_pyobj);
  /* Right panel slot */
  plugin_slot = lookup_widget ("plugin_slot_right");
  plugin_slot_pyobj = pygobject_new ((GObject *)plugin_slot);
  PyObject_CallMethodObjArgs (plugin_mgr,
			      PyString_FromString("_PluginManager__set_plugin_slot"),
			      PyString_FromString("plugin_slot_right"),
			      plugin_slot_pyobj,
			      NULL);
  Py_DECREF (plugin_slot_pyobj);

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

/**
 * Sends keypress events to the PluginManager
 */
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
    plugin_mgr = (PyObject *)gwp_game_state_get_plugin_mgr (game_state);
    
    PyObject_CallMethodObjArgs (plugin_mgr,
				PyString_FromString("manage_event_key"),
				evt_data,
				NULL);
    Py_DECREF (evt_data);
  }
}

/**
 * Returns a list with theactive plugins class names.
 *
 * @return A new GSList
 */
GSList *
gwp_python_get_active_plugins (void)
{
  PyObject *plugin_mgr = NULL;
  PyObject *pylist = NULL;
  GSList *names = NULL;
  gint i;

  plugin_mgr = (PyObject *)gwp_game_state_get_plugin_mgr (game_state);
  g_assert (plugin_mgr != NULL);

  pylist = PyObject_CallMethod (plugin_mgr,
				"get_plugin_registered_names",
				NULL);
  /* Make sure that we have a Python list */
  g_assert (PyList_Check(pylist) == 1);

  /* Assemble the GSList */
  for (i = 0; i < PyList_Size(pylist); i++) {
    PyObject *name = PyList_GetItem (pylist, i);
    g_assert (PyString_Check(name)); /* Must be a Python string */
    names = g_slist_append (names, g_strdup(PyString_AsString(name)));
  }

  Py_DECREF (pylist);

  return names;
}

/**
 * Utility function for gwp_python_set_active_plugins()
 */
static void
gfunc_build_pylist (gpointer data, gpointer user_data)
{
  PyObject *pylist = (PyObject *)user_data;
  gchar *plugin = (gchar *)data;

  PyList_Append (pylist, PyString_FromString(plugin));
}

/**
 * Set up the registered plugin list on the PluginManager
 */
void
gwp_python_set_active_plugins (GSList *names)
{
  PyObject *plugin_mgr = NULL;
  PyObject *pylist = PyList_New (0);
  PyObject *arg;
  
  plugin_mgr = (PyObject *)gwp_game_state_get_plugin_mgr (game_state);
  g_assert (plugin_mgr != NULL);

  /* Assemble Python List and send it to PluginManager */
  g_slist_foreach (names, gfunc_build_pylist, pylist);
  arg = Py_BuildValue ("O", pylist);
  PyObject_CallMethodObjArgs (plugin_mgr,
			      PyString_FromString("set_plugin_registered_names"),
			      arg,
			      NULL);
  Py_DECREF (arg);
  Py_DECREF (pylist);
}

#endif /* USE_PYTHON */
