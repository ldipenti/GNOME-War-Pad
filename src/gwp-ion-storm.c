/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002, 2003 Lucas Di Pentima <lucas@lunix.com.ar>
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

#include "gwp-flying-object.h"
#include "gwp-ion-storm.h"

/**
 * Private data structure for the GwpIonStorm type.
 *
 * This data should be accesed directly only by the low-level get/set
 * objects's methods, the high-level ones shouldn't touch them.
 */
struct _GwpIonStormPrivate {
  gboolean dispose_has_run; /**< GType's internal control variable. */

  gint radius; /**< Storm's radius in LY. */
  gint voltage; /**< Storm's voltage in MeV. It measures the storm's
		   force. */
};

/*
 * forward definitions.
 */
static void gwp_ion_storm_init (GTypeInstance *instance, gpointer g_class);
static void gwp_ion_storm_class_init (GwpIonStormClass *klass);

GType gwp_ion_storm_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpIonStormClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_ion_storm_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpIonStorm),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_ion_storm_init /* instance_init */
    };
    type = g_type_register_static (GWP_FLYING_OBJECT_TYPE,
				   "GwpIonStorm",
				   &info, 0);
  }
  return type;
}

/**
 * Instance constructor (internal)
 */
static void gwp_ion_storm_init (GTypeInstance *instance,
				gpointer       g_class)
{
  GwpIonStorm *self = (GwpIonStorm *)instance;
  self->priv = g_new0 (GwpIonStormPrivate, 1);
  self->priv->dispose_has_run = FALSE;

  /* Private members init */
  self->priv->radius = 0;
  self->priv->voltage = 0;
}

static void gwp_ion_storm_dispose (GwpIonStorm *self)
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

static void gwp_ion_storm_finalize (GwpIonStorm *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_ion_storm_class_init (GwpIonStormClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /*
   * Register destructor methods.
   */
  gobject_class->dispose = gwp_ion_storm_dispose;
  gobject_class->finalize = gwp_ion_storm_finalize;
}

/*
 * Public method implementarions.
 */

/**
 * Instantiates a new Ion Storm.
 *
 * @return The new instantiated GwpIonStorm.
 */
GwpIonStorm * gwp_ion_storm_new (void)
{
  return g_object_new (gwp_ion_storm_get_type(), NULL);
}

/**********************/
/* High-level methods */
/**********************/

/**
 * Return the storm's class.
 *
 * Ion Storms are classified in 5 different classes, from 1 to
 * 5. Classes from 1 to 3 are harmless to starships, but class 4 or 5
 * storms can be very dangerous.
 * @param self a GwpIonStorm.
 * @return The storm's class.
 */
gint gwp_ion_storm_get_class (GwpIonStorm *self)
{
  g_assert (GWP_IS_ION_STORM(self));
  
  gint ret = 0;
  gint volt = gwp_ion_storm_get_voltage (self);

  if (volt > 0 && volt < 50) {
    ret = 1;
  } else if (volt >= 50 && volt <= 99) {
    ret = 2;
  } else if (volt >= 100 && volt <= 149) {
    ret = 3;
  } else if (volt >= 150 && volt <= 199) {
    ret = 4;
  } else if (volt > 200) {
    ret = 5;
  }
  return ret;
}

GString * gwp_ion_storm_get_class_str (GwpIonStorm *self)
{
  g_assert (GWP_IS_ION_STORM(self));

  /* Storm class names */
  gchar * class_names[] = {
    _("Inexistent Disturbance"),
    _("Harmless Disturbance"),
    _("Moderate Disturbance"),
    _("Strong Disturbance"),
    _("Dangerous Storm"),
    _("Very Dangerous Storm")
  };
  gint storm_class = gwp_ion_storm_get_class (self);
  g_assert (storm_class >= 0 && storm_class <= sizeof(class_names) - 1);

  return g_string_new (class_names[storm_class]);
}

gboolean gwp_ion_storm_is_valid (GwpIonStorm *self)
{
  g_assert (GWP_IS_ION_STORM(self));

  if (gwp_ion_storm_get_class(self) > 0 && 
      gwp_object_valid_coords(GWP_OBJECT(self))) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*******************/
/* Get-Set methods */
/*******************/

gint gwp_ion_storm_get_radius (GwpIonStorm *self)
{
  g_assert (GWP_IS_ION_STORM(self));
  return self->priv->radius;
}

void gwp_ion_storm_set_radius (GwpIonStorm *self, gint r)
{
  g_assert (GWP_IS_ION_STORM(self));
  g_assert (r >= 0);
  self->priv->radius = r;
}

gint gwp_ion_storm_get_voltage (GwpIonStorm *self)
{
  g_assert (GWP_IS_ION_STORM(self));
  return self->priv->voltage;
}

void gwp_ion_storm_set_voltage (GwpIonStorm *self, gint v)
{
  g_assert (GWP_IS_ION_STORM(self));
  g_assert (v >= 0);
  self->priv->voltage = v;
}

