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

/* Forwards */
void initgwp (void);

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

void gwp_python_quit (void)
{
  Py_Exit (0);
}

/* A static module */
static PyObject * gwp_pymod_somemethod (PyObject *self, PyObject *args)
{
  return PyInt_FromLong (42L);
}

/* Add methods to module */
static PyMethodDef gwp_methods[] = {
  {"somemethod", gwp_pymod_somemethod, METH_NOARGS,
   "Return the meaning of everything."},
  {NULL, NULL} /* sentinel */
};

void initgwp (void)
{
  PyImport_AddModule ("gwp");
  Py_InitModule ("gwp", gwp_methods);
}

#endif
