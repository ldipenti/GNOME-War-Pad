/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2004  Lucas Di Pentima <lucas@lunix.com.ar>
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

/*
 * Embedded Python on GNOME War Pad.
 */

#ifndef GWP_PYTHON_H
#define GWP_PYTHON_H

#include <Python.h>
#include <gnome.h>

void gwp_python_init (char *argv0);
void gwp_python_quit (void);
void gwp_python_event_key (GdkEventKey *event);
void gwp_python_inittab (void);
GSList * gwp_python_get_active_plugins (void);


#endif

#endif /* USE_PYTHON */
