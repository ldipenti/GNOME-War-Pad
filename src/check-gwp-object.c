/* TO-DO:
   -----

   gwp_object_set_name(object, NULL) 
*/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef USE_CHECK

#include <check.h>
#include "gwp-object.h"

GwpObject *object;

void setup (void)
{
  object = gwp_object_new ();
}

void teardown (void)
{
  g_object_unref (object);
}

START_TEST(object_new)
{
  fail_unless (GWP_IS_OBJECT(object),
	       "is not a GwpObject");
}
END_TEST

#define Unknown_name "Unknown name"
START_TEST(object_default_name)
{
  fail_unless (!strncmp(gwp_object_get_name(object), Unknown_name, 
		       strlen(Unknown_name)),
	       "default name must be " Unknown_name);
}
END_TEST

#define Empty_name ""
START_TEST(object_set_empty_name)
{
  gwp_object_set_name (object, Empty_name);
  fail_unless (strcmp(gwp_object_get_name(object), Empty_name),
	       "name must not be empty");
}
END_TEST

#define A_name "Pirulo"
START_TEST(object_set_get_name)
{
  gwp_object_set_name (object, A_name);
  fail_unless (!strncmp(gwp_object_get_name(object), A_name, 
		       strlen(A_name)),
	       "name must be " A_name);
}
END_TEST

START_TEST(object_get_name_trunc)
{
  gwp_object_set_name (object, A_name);

  fail_unless (!strncmp(gwp_object_get_name_trunc(object,3), A_name, 3),
	       "must return the first 3 characters of " A_name);

  gwp_object_get_name_trunc(object, -1);
  fail ("gwp_object_get_name_trunc() needs positive len parameter");
}
END_TEST

Suite *suite_gwp_object (void)
{
  Suite *s = suite_create ("GwpObject");
  TCase *tc = tcase_create ("Core");

  suite_add_tcase (s, tc);
  tcase_add_checked_fixture (tc, setup, teardown);

  tcase_add_test (tc, object_new);
  tcase_add_test (tc, object_default_name);
  tcase_add_test (tc, object_set_empty_name);
  tcase_add_test (tc, object_set_get_name);
  tcase_add_test (tc, object_get_name_trunc);

  return s;
}

#endif
