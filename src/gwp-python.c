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

#include "gwp-python.h"
#include <pygobject.h>
#include "gwp-ship.h"
#include "global.h"
/*#include "game_state.h"*/

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

  /* Import module to have GWP's methods available */
  PyRun_SimpleString ("import gwp");
}

void gwp_python_inittab (void)
{
  FILE *script;

  /* Load 'inittab' script */
  script = fopen (GWP_SCRIPTS_DIR"/inittab.py", "r");
  PyRun_SimpleFile (script, "inittab.py");
  fclose (script);
}

void gwp_python_quit (void)
{
  Py_Exit (0);
}

/* Include the generated type mappings */
#include "gwp-py-mappings.c"

void initgwp (void)
{
  PyObject *m, *d;

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
  PyObject *res;

  g_assert (event != NULL);

  plugin_mgr = (PyObject *)game_get_plugin_mgr (game_state);

  res = PyObject_CallMethod (plugin_mgr, "manage_key_event", 
			     "({sisisiss})",
			     PyString_FromString("type"), 
			     PyInt_FromLong(event->type),
			     PyString_FromString("state"),
			     PyInt_FromLong(event->state),
			     PyString_FromString("keyval"),
			     PyInt_FromLong(event->keyval),
			     PyString_FromString("string"),
			     PyString_FromStringAndSize(event->string,
							event->length));

  Py_DECREF (res);
}

#endif /* USE_PYTHON */
