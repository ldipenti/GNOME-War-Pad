#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef USE_CHECK

#include <check.h>
#include <string.h>
#include "gwp-ui.h"

GwpUi *ui;

/* Prototypes */
static void setup (void);
static void teardown (void);
Suite *suite_gwp_object (void);

/* Tests */
static void setup (void)
{
  ui = gwp_ui_new ();
}

static void teardown (void)
{
  g_object_unref (ui);
}

START_TEST(ui_new)
{
  ck_assert_true (GWP_IS_UI(ui),
		  "is not a GwpUi");
}
END_TEST

/* Suite assembling */
Suite *suite_gwp_ui (void)
{
  Suite *s = suite_create ("GwpUi");
  TCase *tc = tcase_create ("Core");

  suite_add_tcase (s, tc);
  tcase_add_checked_fixture (tc, setup, teardown);

  tcase_add_test (tc, ui_new);

  return s;
}

#endif
