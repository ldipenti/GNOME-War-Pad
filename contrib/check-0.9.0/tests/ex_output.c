#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>

START_TEST(test_pass)
{
  fail_unless (1==1, "Shouldn't see this");
}
END_TEST

START_TEST(test_fail)
{
  fail("Failure");
}
END_TEST

START_TEST(test_exit)
{
  exit(1);
}
END_TEST

static Suite *make_suite (void)
{
  Suite *s;
  TCase *tc;

  s = suite_create("Master");
  tc = tcase_create ("Core");
  suite_add_tcase(s, tc);
  tcase_add_test (tc, test_pass);
  tcase_add_test (tc, test_fail);
  tcase_add_test (tc, test_exit);

  return s;
}

static void run_tests (int printmode)
{
  SRunner *sr;
  Suite *s;

  s = make_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, printmode);
}

int main (int argc, char **argv)
{
  
  if (argc != 2) {
    printf ("Usage: ex_output (CK_SILENT | CK_MINIMAL | CK_NORMAL | CK_VERBOSE)\n");
    return EXIT_FAILURE;
  }

  if (strcmp (argv[1], "CK_SILENT") == 0)
    run_tests(CK_SILENT);
  else if (strcmp (argv[1], "CK_MINIMAL") == 0)
    run_tests(CK_MINIMAL);
  else if (strcmp (argv[1], "CK_NORMAL") == 0)
    run_tests(CK_NORMAL);
  else if (strcmp (argv[1], "CK_VERBOSE") == 0)
    run_tests(CK_VERBOSE);
  else {
    printf ("Usage: ex_output (CK_SILENT | CK_MINIMAL | CK_NORMAL | CK_VERBOSE)\n");
    return EXIT_FAILURE;
  }    
    

  return EXIT_SUCCESS;
}
  
