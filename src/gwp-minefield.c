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

#include "game_state.h"
#include "gwp-object.h"
#include "gwp-minefield.h"

struct _GwpMinefieldPrivate {
  gboolean dispose_has_run;
  gint radius;
  gint owner; /* Owner/Type */
};

/*
 * forward definitions.
 */
static void gwp_minefield_init (GTypeInstance *instance, gpointer g_class);
static void gwp_minefield_class_init (GwpMinefieldClass *klass);

GType gwp_minefield_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpMinefieldClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_minefield_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpMinefield),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_minefield_init /* instance_init */
    };
    type = g_type_register_static (GWP_OBJECT_TYPE, 
				   "GwpMinefield", 
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_minefield_init (GTypeInstance *instance,
				gpointer       g_class)
{
  GwpMinefield *self = (GwpMinefield *)instance;
  self->priv = g_new0 (GwpMinefieldPrivate, 1);
  self->priv->dispose_has_run = FALSE;
  /* Attributes initialization */
  self->priv->radius = 0;
  self->priv->owner = 0;
}

static void gwp_minefield_dispose (GwpMinefield *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  /* NOOP */
}

static void gwp_minefield_finalize (GwpMinefield *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_minefield_class_init (GwpMinefieldClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  /* Register destructor methods. */
  gobject_class->dispose = (void *) gwp_minefield_dispose;
  gobject_class->finalize = (void *) gwp_minefield_finalize;
}

/*
 * Public method implementations.
 */

GwpMinefield * gwp_minefield_new (void)
{
  return g_object_new (gwp_minefield_get_type(), NULL);
}

/**********************/
/* High level methods */
/**********************/

gboolean gwp_minefield_is_valid (GwpMinefield *self)
{
  g_assert (GWP_IS_MINEFIELD(self));

  if (gwp_minefield_get_radius(self) > 0 &&
      gwp_object_valid_coords(GWP_OBJECT(self))) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
 * Checks if current minefield is owned by player.
 *
 * @param self a GwpMinefield.
 * @return TRUE if minefield's owned by player, FALSE otherwise.
 */
gboolean gwp_minefield_is_mine(GwpMinefield *self)
{
  g_assert(GWP_IS_MINEFIELD(self));

  if(gwp_minefield_get_owner(self) == game_get_race(game_state) ||
     (gwp_minefield_get_owner(self) == 12 &&
      game_get_race(game_state) == RACE_CRYSTALLINE)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

gboolean gwp_minefield_is_web (GwpMinefield *self)
{
  g_assert (GWP_IS_MINEFIELD(self));
  
  if (gwp_minefield_get_owner(self) == 12) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*******************/
/* Get-Set methods */
/*******************/
gint gwp_minefield_get_radius (GwpMinefield *self)
{
  g_assert (GWP_IS_MINEFIELD(self));
  return self->priv->radius;
}

void gwp_minefield_set_radius (GwpMinefield *self, gint r)
{
  g_assert (GWP_IS_MINEFIELD(self));
  g_assert (r >= 0);
  self->priv->radius = r;
}

gint gwp_minefield_get_owner (GwpMinefield *self)
{
  g_assert (GWP_IS_MINEFIELD(self));
  return self->priv->owner;
}

void gwp_minefield_set_owner (GwpMinefield *self, gint owner)
{
  g_assert (GWP_IS_MINEFIELD(self));
  g_assert (owner >= 0 && owner <= 12);
  self->priv->owner = owner;
}
