#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef USE_CHECK

#include <check.h>

int main (void)
{
  int nf;

  g_type_init();

  Suite *s = suite_create ("GWP");
  SRunner *sr = srunner_create (s);

  /* Add module suites */
  srunner_add_suite (sr, suite_gwp_object());
  srunner_add_suite (sr, suite_gwp_ui());
/*  srunner_add_suite (sr, suite_gwp_starchart()); */

  srunner_run_all (sr, CK_VERBOSE);
  nf = srunner_ntests_failed (sr);
  srunner_free (sr);
  return nf;
}

#else

/* Fallback main() */
int main (void)
{
  printf ("Check Unit Tests are disabled, please install check software from your distribution's package system, or http://check.sourceforge.net.\n");
  return -1;
}

#endif
