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

#include "global.h"
#include "gwp-game-state.h"
#include "game_mgr.h"

/*
 * Private members.
 */
struct _GwpGameStatePrivate {
  gboolean dispose_has_run;
  /* Game Settings */
  gchar *game_dir;
  gchar *game_name;
  gchar *trn_dir;
  gchar *rst_dir;
  gchar *player_email;
  gchar *host_email;
  gint host_type; /* 1=THost ; 2=PHost */
  gint race;
  /* General State */
  gdouble starchart_zoom;
  gint turn_number;
  gint16 last_x_coord;
  gint16 last_y_coord;
  GList *pnames;
  /* Toggle states */
  gboolean toolbar;
  gboolean extra_panel_open;
  gboolean planet_names;
  gboolean scanner_area;
  gboolean minefields;
  gboolean ion_storms;
#ifdef USE_PYTHON
  /* Pointer to Python object: PluginManager */
  void *plugin_mgr;
#endif
};

/*
 * forward definitions.
 */
static void gwp_game_state_init (GTypeInstance *instance, gpointer g_class);
static void gwp_game_state_class_init (GwpGameStateClass *klass);

GType gwp_game_state_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpGameStateClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_game_state_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpGameState),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_game_state_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpGameState",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_game_state_init (GTypeInstance *instance,
				 gpointer       g_class)
{
  GwpGameState *self = (GwpGameState *)instance;
  self->priv = g_new0 (GwpGameStatePrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->game_dir = NULL;
  self->priv->game_name = NULL;
  self->priv->trn_dir = "";
  self->priv->rst_dir = "";
  self->priv->player_email = "";
  self->priv->host_email = "";
  self->priv->host_type = 0;
  self->priv->race = 0;
  self->priv->starchart_zoom = 1.0;
  self->priv->last_x_coord = 0;
  self->priv->last_y_coord = 0;
  self->priv->turn_number = 0;
  self->priv->pnames = NULL;
  self->priv->toolbar = TRUE;
  self->priv->extra_panel_open = FALSE;
  self->priv->planet_names = TRUE;
  self->priv->minefields = TRUE;
  self->priv->ion_storms = TRUE;
#ifdef USE_PYTHON
  self->priv->plugin_mgr = NULL;
#endif
}

static void gwp_game_state_dispose (GwpGameState *self)
{
  if (self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  g_free (self->priv->game_dir);
  /* FIXME: When this is tried to be freed, the app hangs 
     (when deleting loaded icons from gconf)
     g_free (self->priv->game_name);
  */
  g_free (self->priv->trn_dir);
  g_free (self->priv->rst_dir);
  g_free (self->priv->player_email);
  g_free (self->priv->host_email);
  g_list_free (self->priv->pnames);
}

static void gwp_game_state_finalize (GwpGameState *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_game_state_class_init (GwpGameStateClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  /* Register destructor methods. */
  gobject_class->dispose = (void *)gwp_game_state_dispose;
  gobject_class->finalize = (void *)gwp_game_state_finalize;
}

/*
 * Public method implementations.
 */
GwpGameState * gwp_game_state_new (void)
{
  return g_object_new (gwp_game_state_get_type (), NULL);
}

/**********************/
/* High level methods */
/**********************/

gchar * gwp_game_state_get_full_path (GwpGameState *self, gchar *filename)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return g_strconcat (gwp_game_state_get_dir (self), "/", filename, NULL);
}

void gwp_game_state_set_last_coords (GwpGameState *self, gint16 x, gint16 y)
{
  g_assert (GWP_IS_GAME_STATE (self));
  gwp_game_state_set_last_x_coord (self, x);
  gwp_game_state_set_last_y_coord (self, y);
}

/**
 * Save game state data on GConf
 */
void gwp_game_state_save (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));

  gchar *name = g_strdup(gwp_game_state_get_name(self));
  gchar *path;

  game_mgr_game_name_mangle(name);
  path = g_strconcat(GWP_GCONF_PATH"Games/",
		     name,
		     "/", NULL);

  /* GameState data */
  gconf_client_set_float(gwp_gconf, g_strconcat(path,"starchart_zoom", NULL),
			 gwp_game_state_get_starchart_zoom(self), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"turn_number",NULL),
		       gwp_game_state_get_turn_number(self), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"last_x_coord",NULL),
		       gwp_game_state_get_last_x_coord(self), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"last_y_coord",NULL),
		       gwp_game_state_get_last_y_coord(self), NULL);
  
  /* GameSettings data */
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"player_email",NULL),
			  gwp_game_state_get_player_email(self), NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"host_email",NULL),
			  gwp_game_state_get_host_email(self), NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"game_dir",NULL),
			  gwp_game_state_get_dir(self), NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"trn_dir",NULL),
			  gwp_game_state_get_trn_dir(self), NULL);
  gconf_client_set_string(gwp_gconf, g_strconcat(path,"rst_dir",NULL),
			  gwp_game_state_get_rst_dir(self), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"host_type",NULL),
		       gwp_game_state_get_host_type(self), NULL);
  gconf_client_set_int(gwp_gconf, g_strconcat(path,"race",NULL),
		       gwp_game_state_get_race(self), NULL);
  gconf_client_set_bool(gwp_gconf, g_strconcat(path,"toolbar",NULL),
			gwp_game_state_get_toolbar(self), NULL);
}

/*******************/
/* Get/Set methods */
/*******************/

void gwp_game_state_set_name (GwpGameState *self, const gchar *name)
{
  gchar *real_name;

  g_assert (GWP_IS_GAME_STATE (self));

  real_name = g_strdup (name);
  game_mgr_game_name_demangle (real_name);
  self->priv->game_name = real_name;
}

const gchar * gwp_game_state_get_name (const GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->game_name;
}

void gwp_game_state_set_dir (GwpGameState *self, gchar *dir)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->game_dir = g_strdup (dir);
}

gchar * gwp_game_state_get_dir (const GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->game_dir;
}

void gwp_game_state_set_starchart_zoom (GwpGameState *self, gdouble zoom)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->starchart_zoom = zoom;
}

gdouble gwp_game_state_get_starchart_zoom (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->starchart_zoom;
}

void gwp_game_state_set_race (GwpGameState *self, gint race_num)
{
  g_assert (GWP_IS_GAME_STATE (self));

  if ((race_num > 0 ) && (race_num <= 11)) {
    self->priv->race = race_num;
  }
}

enum races gwp_game_state_get_race (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->race;
}

gint gwp_game_state_get_race_nr (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->race;
}

void gwp_game_state_set_last_x_coord (GwpGameState *self, gint x)
{
  g_assert (GWP_IS_GAME_STATE (self));
  /* FIXME: I should check boundaries here */
  self->priv->last_x_coord = x;
}

gint16 gwp_game_state_get_last_x_coord (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->last_x_coord;
}

void gwp_game_state_set_last_y_coord (GwpGameState *self, gint y)
{
  g_assert (GWP_IS_GAME_STATE (self));
  /* FIXME: I should check boundaries here */
  self->priv->last_y_coord = y;
}

gint16 gwp_game_state_get_last_y_coord (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->last_y_coord;
}

void gwp_game_state_set_pnames (GwpGameState *self, GList *pnames)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->pnames = pnames;
}

GList * gwp_game_state_get_pnames (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->pnames;
}

void gwp_game_state_set_turn_number (GwpGameState *self, gint turn)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->turn_number = turn;
}

gint gwp_game_state_get_turn_number (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->turn_number;
}

void gwp_game_state_set_player_email (GwpGameState *self, gchar *pe)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->player_email = g_strdup (pe);
}

gchar * gwp_game_state_get_player_email (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->player_email;
}

void gwp_game_state_set_host_email (GwpGameState *self, gchar *he)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->host_email = g_strdup (he);
}

gchar * gwp_game_state_get_host_email (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->host_email;
}

void gwp_game_state_set_trn_dir (GwpGameState *self, gchar *dir)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->trn_dir = g_strdup (dir);
}

gchar * gwp_game_state_get_trn_dir (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->trn_dir;
}

void gwp_game_state_set_rst_dir (GwpGameState *self, gchar *dir)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->rst_dir = g_strdup (dir);
}

gchar * gwp_game_state_get_rst_dir (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->rst_dir;
}

void gwp_game_state_set_host_type (GwpGameState *self, gint type)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->host_type = type;
}

gint gwp_game_state_get_host_type (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->host_type;
}

void gwp_game_state_set_planet_names (GwpGameState *self, gboolean show)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->planet_names = show;
}

gboolean gwp_game_state_get_planet_names (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->planet_names;
}

void gwp_game_state_set_scanner_area (GwpGameState *self, gboolean show)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->scanner_area = show;
}

gboolean gwp_game_state_get_scanner_area (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->scanner_area;
}

void gwp_game_state_set_minefields (GwpGameState *self, gboolean show)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->minefields = show;
}

gboolean gwp_game_state_get_minefields (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->minefields;
}

void gwp_game_state_set_ion_storms (GwpGameState *self, gboolean show)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->ion_storms = show;
}

gboolean gwp_game_state_get_ion_storms (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->ion_storms;
}

void gwp_game_state_set_extra_panel_open (GwpGameState *self, gboolean show)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->extra_panel_open = show;
}

gboolean gwp_game_state_get_extra_panel_open (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->extra_panel_open;
}

void gwp_game_state_set_toolbar (GwpGameState *self, gboolean show)
{
  g_assert (GWP_IS_GAME_STATE (self));
  self->priv->toolbar = show;
}

gboolean gwp_game_state_get_toolbar (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->toolbar;
}

#ifdef USE_PYTHON
/* Python PluginManager */
void gwp_game_state_set_plugin_mgr (GwpGameState *self, void *obj)
{
  g_assert (GWP_IS_GAME_STATE (self));
  g_assert (obj != NULL);
  self->priv->plugin_mgr = obj;
}
void * gwp_game_state_get_plugin_mgr (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE (self));
  return self->priv->plugin_mgr;
}
#endif

