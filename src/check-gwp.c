#include <check.h>
#include "gwp-starchart.h"

START_TEST(object_creation_test)
{
  fail_unless (GWP_IS_STARCHART(gwp_starchart_new()),
	       "create object");
}
END_TEST

Suite *suite (void)
{
  Suite *s = suite_create ("GWP Starchart");
  TCase *tc = tcase_create ("Core");

  suite_add_tcase (s, tc);

  tcase_add_test (tc, object_creation_test);
  return s;
}

int main (void)
{
  int nf;

  g_type_init();

  Suite *s = suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_VERBOSE);
  nf = srunner_ntests_failed (sr);
  srunner_free (sr);
  return nf;
}
