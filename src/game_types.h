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

/*  Other Game Data Types */

#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <gnome.h>

typedef struct _GameSettings GameSettings;
struct _GameSettings {
  GString *game_dir, *game_name, *trn_dir, *rst_dir;
  GString *player_email, *host_email;
  gint16 host_type; // 1=THost ; 2=PHost
  gint16 race;
};

#endif
