/* TO-DO:
   -----

gchar * gwp_ship_get_mission_name (GwpShip *self)
gchar * gwp_ship_get_primary_enemy_name (GwpShip *self)
*/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef USE_CHECK

#include <check.h>
#include <string.h>
#include "gwp-ship.h"

GwpObject *ship;

/* Prototypes */
static void setup (void);
static void teardown (void);
Suite *suite_gwp_ship (void);

/* Tests */
static void setup (void)
{
  ship = gwp_ship_new ();
}

static void teardown (void)
{
  g_object_unref (ship);
}

START_TEST(ship_new)
{
  ck_assert_true (GWP_IS_SHIP(ship),
		  "is not a GwpShip");
}
END_TEST


/* Suite assembling */
Suite *suite_gwp_ship (void)
{
  Suite *s = suite_create ("GwpObject");
  TCase *tc = tcase_create ("Core");

  suite_add_tcase (s, tc);
  tcase_add_checked_fixture (tc, setup, teardown);

  tcase_add_test (tc, ship_new);


  return s;
}

#endif
