#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef USE_CHECK

#include <check.h>
#include <string.h>
#include "gwp-ui.h"

GwpUi *ui;

/* Prototypes */
void gwp_ui_setup (void);
void gwp_ui_teardown (void);
Suite *suite_gwp_object (void);

/* Tests */
void gwp_ui_setup (void)
{
  ui = gwp_ui_new ();
}

void gwp_ui_teardown (void)
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
  tcase_add_checked_fixture (tc, gwp_ui_setup, gwp_ui_teardown);

  tcase_add_test (tc, ui_new);

  return s;
}

#endif
