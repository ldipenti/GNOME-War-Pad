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

enum {
  PROP_0,
  PROP_GAME_DIR,
  PROP_GAME_NAME,
  PROP_TRN_DIR,
  PROP_RST_DIR,
  PROP_PLAYER_EMAIL,
  PROP_HOST_EMAIL,
  PROP_HOST_TYPE,
  PROP_RACE,
  PROP_STARCHART_ZOOM,
  PROP_TURN_NUMBER,
  PROP_LAST_X_COORD,
  PROP_LAST_Y_COORD,
  PROP_PLANET_NAMES,
  PROP_SCANNER_AREA,
  PROP_MINEFIELDS,
  PROP_ION_STORMS,
  PROP_CONSTELLATIONS,
  PROP_GRID,
  PROP_DISTANCE_CALC,
  PROP_X_COORD,
  PROP_Y_COORD,
  PROP_WARN_KOREFILE, 
};

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
  gint16 x_coord;
  gint16 y_coord;
  GwpPlanet *selected_planet;
  GwpShip *selected_ship;

  /*******************************/
  /* Host configuration settings */
  /*******************************/
  gint host_recycle_col_ship; /**< The percentage of minerals invested
				 in a ship's hull that are regained
				 when a ship is colonised. Default is 75%. */
  gint host_large_meteor_impact; /**< The chance that a large meteor
				    will hit one of the 500 planets in
				    the cluster. Default is 2%. */
  gboolean host_space_mines; /**< Torps can be converted to spacemines
				and laid as minefields. Default:
				YES. */
  gboolean host_alchemy_ships; /**< This enables the alchemy functions
				  for the Merlin and the Neutronic
				  Refinery Ship. Default: YES */
  gboolean host_delete_old_msgs; /**< If a player misses a turn, the
				    messages he or she received that
				    turn will be saved and sent to the
				    player again the next
				    turn. Default: NO */
  gboolean host_disable_pwd; /**< Players can protect their files
				using a password. Default: NO */
  gboolean host_rebel_build_fighters; /**< Rebels can build fighters
					 in space?. Default: YES */
  gboolean host_colonial_build_fighters; /**< Colonial can build fighters
					    in space?. Default: YES */
  gboolean host_robots_build_fighters; /**< Robots can build fighters
					  in space?. Default: YES */
  gint host_cloak_failure; /**< The chance that a cloaking device will
			      malfunction, for no apparent
			      reason. Default 0% */
  gboolean host_priv_rob_cloak; /**< The Privateers can rob cloaked
				   ships?. Default: NO */
  gint host_dark_sense_range; /**< Empire's Dark Sense range in
			    LY. Default: 200 */
  gint host_ground_attack_ratio[11]; /**< Values for every race for how
					many kills make a single dropped
					clan. Default: Lizards=30,
					Fascists=15, the rest=1 */
  gint host_ships_visible_range; /**< The detectable range of
				    non-cloaked ships in LY. Default:
				    300 */
  gboolean host_lizard_hiss_mission; /**< Default: YES */
  gboolean host_rebel_ground_attack; /**< Default: YES */
  gboolean host_fed_super_refit; /**< Default: YES */
  gboolean host_crystal_web_mines; /**< Default: YES */
  gint host_ground_defense_ratio[11]; /**< Default: Lizards=10,
					 Fascists=5, the rest=1 */
  gint host_cloak_fuel_use; /**< The amount of fuel used to cloak or
			       stay cloaked per turn, per 100 kt of
			       hullmass rounded up. Default: 5 */
  gint host_sensors_range; /**< Sensor mission range in LY. Default:
			      200 */
  gboolean host_new_natives; /**< On colonized planets thought to be
				devoid of native lifeforms, new
				natives may be discovered. Default:
				YES */
  gboolean host_planets_attack_ships; /**< Using the NUK or ATT
					 friendly code, a planet can
					 use its fighters and beams to
					 attack enemy ships. Default:
					 YES */
  gint host_borg_assimilation_rate; /**< Default: 100% */
  gint host_starbase_free_fighters[11]; /**< Default: Evils=5, the
					   rest=0 */
  gint host_webmine_decay; /**< Default: 5% */
  gint host_mine_decay; /**< Default: 5% */
  gint host_max_mine_radius; /**< Default: 150 */
  gint host_isotope_tudr; /** The rate at which new minerals are
			      formed inside a planet. For the actual
			      number of kilotons that appear, this
			      rate is multiplied by the density
			      first. Default: 5 */
  gint host_structure_decay; /**< Rate dissapearance when there are
				insufficient clans to support the
				number of structures. Default: 1 */
  gint host_mining_rate[11]; /**< Default: Fed=70, Lizard=200, the
				rest=100 */
  gboolean host_colonists_eat_supplies; /**< If enabled, part of a
					   planet's overpopulation can
					   survive the harsh climate
					   by eating
					   supply-units. Default: NO */
  gboolean host_zero_fuel_ships_move; /**< Very light ships can move
					 large distances without any
					 fuel, while heavy ships can
					 hardly move at all if they're
					 fuelless. Default: YES */
  gint host_mine_hit_odds; /**< The chance of hitting a mine for each
			      lightyear of mines a spaceship passes
			      through. Default: 1% */
  gint host_webmine_hit_odds; /**< The chance of hitting a webmine for
				 each lightyear of mines a spaceship
				 passes through. Default: 5% */
  gint host_mine_detect_range; /**< Ships on a minesweep mission will
				  detect minefield. Default: 200 */
  gint host_tax_rate[11]; /**< Colonists and natives living on planets
			     can be taxed for money. Default:
			     Feds=200, the rest=100 */
  gboolean host_mines_destroy_mines; /**< Overlapping minefields of
					non-allied races will destroy
					each other. Default: YES */
  gboolean host_es_bonus; /**< If enabled, ships gain some mass in
			     battles depending on their type of
			     engines. Default: NO */
  gint host_es_bonus_rate; /**< Default: 0% */
  gint host_colonial_sweep_rate; /**< The Colonies of Man have highly
				    skilled fighterpilots: their
				    fighters can be used to sweep
				    mines. Default: 20 */
  gboolean host_colonial_sweep_webs; /**< Default: NO */
  gint host_mine_sweep_rate; /**< Amount of mines swept by a laser
				beam. Default: 4 */
  gint host_webmine_sweep_rate; /**< Amount of webmines swept by a
				   laser beam. Default: 3 */
  gint host_hiss_mission_effect; /**< Happiness points per ship using
				   hiss mission. Default: 5 */
  gint host_rob_mission_failure; /**< There is a slight chance that
				    the Privateer rob mission will
				    fail. Default: 1% */
  gboolean host_planet_attack_rebel; /**< Default: NO */
  gboolean host_planet_attack_fascist; /**< Default: NO */
  gint host_mine_sweep_range; /**< Default: 5 */
  gint host_webmine_sweep_range; /**< Default: 0 */
  gboolean host_science_missions; /**< This setting enables the
				     terraforming functions of the
				     Eros, Bohemian and Onyx. Default:
				     YES */
  gdouble host_cloaked_mine_hit; /**< Default: 0.5% */
  gint host_cloak_prevent_damage; /**< A ship with damage cannot cloak
				     or stay cloaked. Default: 1% */
  gboolean host_fed_crew_bonus; /**< Because of the highly trained
				   crews, Federation ships receive
				   several bonuses in combat. Default:
				   YES */
  gboolean host_one_engine_tow; /**< Default: NO */
  gboolean host_hyperdrive_ships; /**< Default: YES */
  gint host_climate_death_rate; /**< Default: 10% */
  gboolean host_gravity_well; /**< Default: YES */
  gboolean host_crystal_desert_adv; /**< Crystallines love desert
				       temperatures. They have a
				       higher growth rate and maximum
				       population on hot
				       planets. Default: YES */
  gboolean host_mines_destroy_webs; /**< Default: NO */
  gboolean host_climate_limit_pop; /**< Normally, on planets with a
				      temperature below 15 degrees or
				      above 84 the number of colonists
				      that can survive is
				      limited. Default: YES */
  gint host_max_planet_income; /**< The maximum amount that can be
				  earned from natives and colonists
				  combined per planet per
				  turn. Default: 5000 MC */
  gint host_ion_storms; /**< The maximum number of Ion storms present
			   in the cluster. Default: 5 */
  gboolean host_firecloud_chunnel; /**< Default: YES */
  gboolean host_superspy_deluxe; /**< Default: YES */
  gboolean host_storms_hide_mines; /**< Default: YES */
  gboolean host_fascist_glory_device; /**< Default: YES */
  gboolean host_loki_anticloak; /**< Default: YES */
  gboolean host_ladyroyale_gambling; /**< Default: YES */
  gboolean host_cloaked_ships_attack; /**< Default: YES */
  gboolean host_ship_cloning; /**< Default: YES */
  gboolean host_boarding_party; /**< Default: YES */
  gboolean host_imperial_assault; /**< Default: YES */
  gint host_cobol_fuel; /**< The Cobol (built by the Colonies) scoops
			   up fuel from space while flying. Default:
			   2kt per turn */
  gint host_hulltech_slowed_minehits; /**< Ships with a hull of a
					 certain techlevel or higher
					 are not slowed down by
					 minehits. Default: 7 */
  gboolean host_aries_makes_fuel; /**< The Aries (built by the
				     Colonies) makes fuel out of
				     minerals without needing
				     supplies. Default: YES */
  gboolean host_bioscanners; /**< The Brynhild, the Cobol and the Pawn
				have bioscanners which scan for
				natives and temperatures of all
				planets within scanning
				range. Default: YES */
  gboolean host_loki_decloak_birds; /**< Default: NO */
  gboolean host_vpa_extras; /** Default: NO */

  /* Toggle states */
  gboolean extra_panel_open;
  gboolean planet_names;
  gboolean scanner_area;
  gboolean minefields;
  gboolean ion_storms;
  gboolean constellations;
  gboolean grid;
  gboolean distance_calc; /**< This flag tell the system if the user is 
			     measuring distance from the starchart. */
  gboolean warn_korefile; /**< Give the user a warning about missing 
			     KOREx.DAT. TRUE means warn the user. */
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
void selected_planet_notification (GObject *planet, gpointer data);
void selected_ship_notification (GObject *ship, gpointer data);

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

/**
 * Property setters
 */
static void 
gwp_game_state_set_property (GObject      *object,
			     guint         property_id,
			     const GValue *value,
			     GParamSpec   *pspec)
{
  GwpGameState *self = (GwpGameState *) object;

  switch (property_id) {
  case PROP_PLANET_NAMES:
    self->priv->planet_names = g_value_get_boolean (value);
    break;
  case PROP_SCANNER_AREA:
    self->priv->scanner_area = g_value_get_boolean (value);
    break;
  case PROP_MINEFIELDS:
    self->priv->minefields = g_value_get_boolean (value);
    break;
  case PROP_ION_STORMS:
    self->priv->ion_storms = g_value_get_boolean (value);
    break;
  case PROP_GRID:
    self->priv->grid = g_value_get_boolean (value);
    break;
  case PROP_CONSTELLATIONS:
    self->priv->constellations = g_value_get_boolean (value);
    break;
  case PROP_DISTANCE_CALC:
    self->priv->distance_calc = g_value_get_boolean (value);
    break;
  case PROP_X_COORD:
    self->priv->x_coord = g_value_get_int (value);
    break;
  case PROP_Y_COORD:
    self->priv->y_coord = g_value_get_int (value);
    break;
  case PROP_WARN_KOREFILE:
    self->priv->warn_korefile = g_value_get_boolean (value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
  }
  /* Emit a notify signal with the changed property's name */
  g_signal_emit_by_name (self, g_strconcat("property-changed::",
					   pspec->name, NULL));
}

/**
 * Property getters
 */
static void
gwp_game_state_get_property (GObject    *object,
			     guint       property_id,
			     GValue     *value,
			     GParamSpec *pspec)
{
  GwpGameState *self = (GwpGameState *) object;

  switch (property_id) {
  case PROP_PLANET_NAMES:
    g_value_set_boolean (value, self->priv->planet_names);
    break;
  case PROP_SCANNER_AREA:
    g_value_set_boolean (value, self->priv->scanner_area);
    break;
  case PROP_MINEFIELDS:
    g_value_set_boolean (value, self->priv->minefields);
    break;
  case PROP_ION_STORMS:
    g_value_set_boolean (value, self->priv->ion_storms);
    break;
  case PROP_GRID:
    g_value_set_boolean (value, self->priv->grid);
    break;
  case PROP_CONSTELLATIONS:
    g_value_set_boolean (value, self->priv->constellations);
    break;
  case PROP_DISTANCE_CALC:
    g_value_set_boolean (value, self->priv->distance_calc);
    break;
  case PROP_X_COORD:
    g_value_set_int (value, self->priv->x_coord);
    break;
  case PROP_Y_COORD:
    g_value_set_int (value, self->priv->y_coord);
    break;
  case PROP_WARN_KOREFILE:
    g_value_set_boolean (value, self->priv->warn_korefile);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
  }
}

/* Instance constructor */
static void 
gwp_game_state_init (GTypeInstance *instance,
		     gpointer       g_class)
{
  GwpGameState *self = (GwpGameState *)instance;
  self->priv = g_new0 (GwpGameStatePrivate, 1);
  self->priv->dispose_has_run = FALSE;
  gint i;

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
  self->priv->extra_panel_open = FALSE;
  self->priv->planet_names = TRUE;
  self->priv->grid = TRUE;
  self->priv->constellations = TRUE;
  self->priv->distance_calc = FALSE;
  self->priv->x_coord = 0;
  self->priv->y_coord = 0;
  self->priv->selected_planet = NULL;
  self->priv->selected_ship = NULL;
  self->priv->warn_korefile = TRUE;
#ifdef USE_PYTHON
  self->priv->plugin_mgr = NULL;
#endif

  /********************************/
  /* Host Configurations Defaults */
  /********************************/
  self->priv->host_recycle_col_ship = 75;
  self->priv->host_large_meteor_impact = 2;
  self->priv->host_space_mines = TRUE;
  self->priv->host_alchemy_ships = TRUE;
  self->priv->host_delete_old_msgs = FALSE;
  self->priv->host_disable_pwd = TRUE;
  self->priv->host_rebel_build_fighters = TRUE;
  self->priv->host_colonial_build_fighters = TRUE;
  self->priv->host_robots_build_fighters = TRUE;
  self->priv->host_cloak_failure = 0;
  self->priv->host_priv_rob_cloak = FALSE;
  self->priv->host_dark_sense_range = 200;

  for (i = 0; i < 11; i++) self->priv->host_ground_attack_ratio[i] = 1;
  self->priv->host_ground_attack_ratio[1] = 30; /* Lizards */
  self->priv->host_ground_attack_ratio[3] = 15; /* Fascists */
  
  self->priv->host_ships_visible_range = 300;
  self->priv->host_lizard_hiss_mission = TRUE;
  self->priv->host_rebel_ground_attack = TRUE;
  self->priv->host_fed_super_refit = TRUE;
  self->priv->host_crystal_web_mines = TRUE;

  for (i = 0; i < 11; i++) self->priv->host_ground_defense_ratio[i] = 1;
  self->priv->host_ground_defense_ratio[1] = 10; /* Lizards */
  self->priv->host_ground_defense_ratio[3] = 5; /* Fascists */

  self->priv->host_cloak_fuel_use = 5;
  self->priv->host_sensors_range = 200;
  self->priv->host_new_natives = TRUE;
  self->priv->host_planets_attack_ships = TRUE;
  self->priv->host_borg_assimilation_rate = 100;

  for (i = 0; i < 11; i++) self->priv->host_starbase_free_fighters[i] = 0;
  self->priv->host_starbase_free_fighters[7] = 5; /* Evils */

  self->priv->host_webmine_decay = 5;
  self->priv->host_mine_decay = 5;
  self->priv->host_max_mine_radius = 150;
  self->priv->host_isotope_tudr = 5;
  self->priv->host_structure_decay = 1;

  for (i = 0; i < 11; i++) self->priv->host_mining_rate[i] = 100;
  self->priv->host_mining_rate[0] = 70; /* Feds */
  self->priv->host_mining_rate[2] = 200; /* Lizards */

  self->priv->host_colonists_eat_supplies = FALSE;
  self->priv->host_zero_fuel_ships_move = TRUE;
  self->priv->host_mine_hit_odds = 1;
  self->priv->host_webmine_hit_odds = 5;
  self->priv->host_mine_detect_range = 200;

  for (i = 0; i < 11; i++)
    self->priv->host_tax_rate[i] = 100;
  self->priv->host_tax_rate[0] = 200; /* Feds */

  self->priv->host_mines_destroy_mines = TRUE;
  self->priv->host_es_bonus = FALSE;
  self->priv->host_es_bonus_rate = 0;
  self->priv->host_colonial_sweep_rate = 20;
  self->priv->host_colonial_sweep_webs = FALSE;
  self->priv->host_mine_sweep_rate = 4;
  self->priv->host_webmine_sweep_rate = 3;
  self->priv->host_hiss_mission_effect = 5;
  self->priv->host_rob_mission_failure = 1;
  self->priv->host_planet_attack_rebel = FALSE;
  self->priv->host_planet_attack_fascist = FALSE;
  self->priv->host_mine_sweep_range = 5;
  self->priv->host_webmine_sweep_range = 0;
  self->priv->host_science_missions = TRUE;
  self->priv->host_cloaked_mine_hit = 0.5;
  self->priv->host_cloak_prevent_damage = 1;
  self->priv->host_fed_crew_bonus = TRUE;
  self->priv->host_one_engine_tow = FALSE;
  self->priv->host_hyperdrive_ships = TRUE;
  self->priv->host_climate_death_rate = 10;
  self->priv->host_gravity_well = TRUE;
  self->priv->host_crystal_desert_adv = TRUE;
  self->priv->host_mines_destroy_webs = FALSE;
  self->priv->host_climate_limit_pop = TRUE;
  self->priv->host_max_planet_income = 5000;
  self->priv->host_ion_storms = 5;
  self->priv->host_firecloud_chunnel = TRUE;
  self->priv->host_superspy_deluxe = TRUE;
  self->priv->host_storms_hide_mines = TRUE;
  self->priv->host_fascist_glory_device = TRUE;
  self->priv->host_loki_anticloak = TRUE;
  self->priv->host_ladyroyale_gambling = TRUE;
  self->priv->host_cloaked_ships_attack = TRUE;
  self->priv->host_ship_cloning = TRUE;
  self->priv->host_boarding_party = TRUE;
  self->priv->host_imperial_assault = TRUE;
  self->priv->host_cobol_fuel = 2;
  self->priv->host_hulltech_slowed_minehits = 7;
  self->priv->host_aries_makes_fuel = TRUE;
  self->priv->host_bioscanners = TRUE;
  self->priv->host_loki_decloak_birds = FALSE;
  self->priv->host_vpa_extras = FALSE;
  /* End Host Configuration */
}

static void 
gwp_game_state_dispose (GwpGameState *self)
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
}

static void 
gwp_game_state_finalize (GwpGameState *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void 
gwp_game_state_class_init (GwpGameStateClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  /* Register destructor methods. */
  gobject_class->dispose = (void *)gwp_game_state_dispose;
  gobject_class->finalize = (void *)gwp_game_state_finalize;

  /* Signals  */
  g_signal_newv ("property-changed",
		 G_TYPE_FROM_CLASS (klass),
		 G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
		 NULL /* class closure */,
		 NULL /* accumulator */,
		 NULL /* accu_data */,
		 g_cclosure_marshal_VOID__VOID,
		 G_TYPE_NONE /* return_type */,
		 0     /* n_params */,
		 NULL  /* param_types */);

  /* Property get/set methods */
  gobject_class->set_property = gwp_game_state_set_property;
  gobject_class->get_property = gwp_game_state_get_property;

  /* Properties registrations */
  g_object_class_install_property (gobject_class, PROP_PLANET_NAMES,
				   g_param_spec_boolean ("planet-names",
							 "Planet-Names",
							 "Whether show the planet names or not",
							 TRUE,
							 G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_SCANNER_AREA,
				   g_param_spec_boolean ("scanner-area",
							 "Scanner-Area",
							 "Whether show the scanner area or not",
							 TRUE,
							 G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_MINEFIELDS,
				   g_param_spec_boolean ("minefields", 
							 "Minefields",
							 "Whether show minefields or not",
							 TRUE, 
							 G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_ION_STORMS,
				   g_param_spec_boolean ("ion-storms",
							 "Ion-Storms",
							 "Whether show ion storms or not",
							 TRUE,
							 G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_GRID,
				   g_param_spec_boolean ("grid",
							 "Grid",
							 "Whether show the grid or not",
							 TRUE,
							 G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_CONSTELLATIONS,
				   g_param_spec_boolean ("constellations",
							 "Constellations",
							 "Whether show the constellations or not",
							 TRUE,
							 G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_DISTANCE_CALC,
				   g_param_spec_boolean ("distance-calc",
							 "Distance-Calc",
							 "Whether show the distance calculator or not",
							 TRUE,
							 G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_WARN_KOREFILE,
				   g_param_spec_boolean ("warn-korefile",
							 "Warn-Korefile",
							 "Whether warn the user about the missing kore file or not",
							 TRUE,
							 G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_X_COORD,
				   g_param_spec_int ("x-coord",
						     "X-Coord",
						     "Actual pointer's X coordinate",
						     0, 3000, /* min/max */
						     0, /* default */
						     G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_Y_COORD,
				   g_param_spec_int ("y-coord",
						     "y-Coord",
						     "Actual pointer's X coordinate",
						     0, 3000, /* min/max */
						     0, /* default */
						     G_PARAM_READWRITE));
}

/*
 * Public method implementations.
 */
GwpGameState * gwp_game_state_new (void)
{
  return g_object_new (gwp_game_state_get_type (), NULL);
}

/**
 * Post-init tasks.
 *
 * The game state object requires a double initialization: first
 * it set ups several data required to load the game, later on it 
 * must have all the game data loaded to do extra stuff (like
 * connectin to planets and ships signals).
 */
void
gwp_game_state_postinit (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE(self));
  static gboolean already_run = FALSE;

  /* Check if this method already was executed */
  if (already_run)
    return;

  /* Make sure that this method is called just once */
  already_run = TRUE;

  /**********************************/
  /* Connect to interesting signals */
  /**********************************/
  /* Selected planets */
  static void planet_conn (gpointer key, gpointer value, gpointer self) {
    g_signal_connect (GWP_PLANET(value),
		      "selected",
		      G_CALLBACK(selected_planet_notification),
		      self);
  }
  g_hash_table_foreach (planet_list, (GHFunc) planet_conn, self);
  /* Selected ships */
  static void ship_conn (gpointer key, gpointer value, gpointer self) {
    g_signal_connect (GWP_SHIP(value),
		      "selected",
		      G_CALLBACK(selected_ship_notification),
		      self);
  }
  g_hash_table_foreach (ship_list, (GHFunc) ship_conn, self);
}

/*************************************/
/* Notifications callbacks (private) */
/*************************************/
/**
 * Callback connected to selected planet signal, update game state data.
 */
void
selected_planet_notification (GObject *planet, gpointer data)
{
  GwpGameState *self = GWP_GAME_STATE(data);
  self->priv->selected_planet = GWP_PLANET(planet);
}
/**
 * Callback connected to selected ship signal, updates game state data.
 */
void
selected_ship_notification (GObject *ship, gpointer data)
{
  GwpGameState *self = GWP_GAME_STATE(data);
  self->priv->selected_ship = GWP_SHIP(ship);
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
  g_object_set (self, "planet-names", show, NULL);
}

gboolean gwp_game_state_get_planet_names (GwpGameState *self)
{
  gboolean ret;

  g_object_get (self, "planet-names", &ret, NULL);
  return ret;
}

void gwp_game_state_set_scanner_area (GwpGameState *self, gboolean show)
{
  g_object_set (self, "scanner-area", show, NULL);
}

gboolean gwp_game_state_get_scanner_area (GwpGameState *self)
{
  gboolean ret;

  g_object_get (self, "scanner-area", &ret, NULL);
  return ret;
}

void gwp_game_state_set_minefields (GwpGameState *self, gboolean show)
{
  g_object_set (self, "minefields", show, NULL);
}

gboolean gwp_game_state_get_minefields (GwpGameState *self)
{
  gboolean ret;

  g_object_get (self, "minefields", &ret, NULL);
  return ret;
}

void gwp_game_state_set_ion_storms (GwpGameState *self, gboolean show)
{
  g_object_set (self, "ion-storms", show, NULL);
}

gboolean gwp_game_state_get_ion_storms (GwpGameState *self)
{
  gboolean ret;

  g_object_get (self, "ion-storms", &ret, NULL);
  return ret;
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

/**
 * Returns the current selected planet
 */
GwpPlanet *
gwp_game_state_get_selected_planet (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE(self));
  return self->priv->selected_planet;
}

/**
 * Returns the current selected ship
 */
GwpShip *
gwp_game_state_get_selected_ship (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE(self));
  return self->priv->selected_ship;
}

/**
 * Return Host's mining rate setting.
 *
 * @param self a GwpGameState object.
 * @param race the race number (1-11)
 * @return The race's mining rate or 0 in case of incorrect race number.
 */
gint
gwp_game_state_get_host_mining_rate (GwpGameState *self, gint race)
{
  g_assert (GWP_IS_GAME_STATE (self));
  g_return_val_if_fail (race > 0 && race <= 11, 0);
  return self->priv->host_mining_rate[race-1];
}

/**
 * Return Host's tax rate setting.
 *
 * @param self a GwpGameState object.
 * @param race the race number (1-11)
 * @return The race's tax rate or 0 in case of incorrect race number.
 */
gint
gwp_game_state_get_host_tax_rate (GwpGameState *self, gint race)
{
  g_assert (GWP_IS_GAME_STATE (self));
  g_return_val_if_fail (race > 0 && race <= 11, 0);
  return self->priv->host_tax_rate[race-1];
}

/**
 * Return Host's ships visible range setting in LY.
 */
gint
gwp_game_state_get_host_ships_visible_range (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE(self));
  return self->priv->host_ships_visible_range;
}

/**
 * Return Host's ships sensors range setting in LY.
 */
gint 
gwp_game_state_get_host_sensors_range (GwpGameState *self)
{
  g_assert (GWP_IS_GAME_STATE(self));
  return self->priv->host_sensors_range;  
}
